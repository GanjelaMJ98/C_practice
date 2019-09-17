#include <linux/kernel.h> 				//printk()
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h> 				//put_user()

//modinfo
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pavel Ganjela");
MODULE_DESCRIPTION("My first module");
MODULE_SUPPORTED_DEVICE("test"); 		//  /dev/testdevice

#define SUCCESS 0
#define DEVICE_NAME "test"

static int device_open(struct inode*, struct file * );
static int device_release(struct inode*, struct file * );
static ssize_t device_read(struct file*, char *, size_t, loff_t * );
static ssize_t device_write(struct file*, const char*, size_t, loff_t * );

static int major_number;				//старший номер устройства
static int is_device_open = 0;			//используется ли девайс
static char text[5] = "test\n";
static char* text_ptr = text;

// Обработчики опраций на устройстве
static struct file_operations fops =
{
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

// Загрузка модуля
static int __init test_init( void ){
	printk( KERN_ALERT "TEST driver loaded!\n" );
	major_number = register_chrdev( 0, DEVICE_NAME, &fops );
	if( major_number < 0 ){
		printk( "Registering the character device failed with %d\n", major_number );
		return major_number;
	}
	printk( "Test module is loaded!\n" );
	printk( "Please, create a dev file with 'mkmod /dev/test c %d'.\n", major_number );
	return SUCCESS;
}

// Выгрузка модуля
static int __exit test_exit( void ){
	unregister_chrdev( major_number, DEVICE_NAME );
	printk( KERN_ALERT "Test module is unloaded!\n" );
	return SUCCESS;
}

module_init( test_init );
module_exit( test_exit );

static int device_open( struct inode *inode, struct file *file ){
	text_ptr = text;
	if(is_device_open)
		return -EBUSY;
	is_device_open++;
	return SUCCESS;
}

static int device_release( struct inode *inode, struct file *file ){
	is_device_open--;
	return SUCCESS;
}

static ssize_t device_write( struct file *file, const char *buf, size_t len, loff_t *off){
	printk( "Sorry, this operation is not supported" );
	return -EINVAL;
}

static ssize_t device_read( struct file *file, char *buffer, size_t length, loff_t *offset ){
	int byte_read = 0;
	if( *text_ptr == 0 ) return 0;
	while( length && *text_ptr ){
		put_user( *(text_ptr++), buffer++ );
		length--;
		byte_read++;
	}
	return byte_read;
}

/*
modinfo test.ko

Установка модуля
	insmod test.ko

Проверка
	lsmod | grep test

Логи
	dmesq | tail

Считать из модуля
	cat /dev/test

Запись в модуль
	echo 1 > /dev/test (не поддерживается)

Удаление модуля
	rmmod test
	rm /dev/test
*/