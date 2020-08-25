#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>


const char *version = "0.1";
GMainLoop *mainloop;

#define DBUS_BUS_NAME			"org.example.TestServer"
#define DBUS_OBJ_PATH			"/org/example/TestObject"
#define DBUS_INTERFACE_NAME		"org.example.TestInterface"



int dbus_call_method_ping(DBusConnection * dbus_conn, DBusError* dbus_error){

	DBusMessage * dbus_msg = NULL;
	DBusMessage * dbus_reply = NULL;

	char* ans;

	// Compose remote procedure call
	if ( NULL == (dbus_msg = dbus_message_new_method_call(DBUS_BUS_NAME, DBUS_OBJ_PATH, DBUS_INTERFACE_NAME, "Ping")) ) {
		dbus_connection_unref(dbus_conn);
		printf("ERROR: ::dbus_message_new_method_call - Unable to allocate memory for the message!");

	// Invoke remote procedure call, block for response
	} else if ( NULL == (dbus_reply = dbus_connection_send_with_reply_and_block(dbus_conn, dbus_msg, DBUS_TIMEOUT_USE_DEFAULT, dbus_error)) ) {
		dbus_message_unref(dbus_msg);
		dbus_connection_unref(dbus_conn);
		perror(dbus_error->name);
		perror(dbus_error->message);

	// Parse response
	} else if ( !dbus_message_get_args(dbus_reply, dbus_error,
										DBUS_TYPE_STRING, &ans,
										DBUS_TYPE_INVALID) ) {
		dbus_message_unref(dbus_msg);
		dbus_message_unref(dbus_reply);
		dbus_connection_unref(dbus_conn);
		perror(dbus_error->name);
		perror(dbus_error->message);
	}else{
		dbus_message_unref(dbus_msg);
		dbus_message_unref(dbus_reply);
		printf("Ping Ans: %s\n", ans);
	}

	return 0;
}

int dbus_call_method_echo(DBusConnection * dbus_conn, DBusError* dbus_error){

	DBusMessage * dbus_msg = NULL;
	DBusMessage * dbus_reply = NULL;

	char* ans;
	char *hello = "Hello!";

	// Compose remote procedure call
	if ( NULL == (dbus_msg = dbus_message_new_method_call(DBUS_BUS_NAME, DBUS_OBJ_PATH, DBUS_INTERFACE_NAME, "Echo")) ) {
		dbus_connection_unref(dbus_conn);
		printf("ERROR: ::dbus_message_new_method_call - Unable to allocate memory for the message!");
	} else {

		dbus_message_append_args (dbus_msg, DBUS_TYPE_STRING, &hello, DBUS_TYPE_INVALID);

		if ( NULL == (dbus_reply = dbus_connection_send_with_reply_and_block(dbus_conn, dbus_msg, DBUS_TIMEOUT_USE_DEFAULT, dbus_error)) ) {
			dbus_message_unref(dbus_msg);
			dbus_connection_unref(dbus_conn);
			perror(dbus_error->name);
			perror(dbus_error->message);
		// Parse response
		} else if ( !dbus_message_get_args(dbus_reply, dbus_error,
											DBUS_TYPE_STRING, &ans,
											DBUS_TYPE_INVALID) ) {
			dbus_message_unref(dbus_msg);
			dbus_message_unref(dbus_reply);
			dbus_connection_unref(dbus_conn);
			perror(dbus_error->name);
			perror(dbus_error->message);
		}else{
			dbus_message_unref(dbus_msg);
			dbus_message_unref(dbus_reply);
			printf("Echo Ans: %s\n", ans);
		}
	}

	return 0;
}



int main(int argc, char const *argv[])
{
	DBusError dbus_error;
	DBusConnection * dbus_conn = NULL;

	// Initialize D-Bus error
	dbus_error_init(&dbus_error);

	// Connect to D-Bus
	if ( NULL == (dbus_conn = dbus_bus_get(DBUS_BUS_SESSION, &dbus_error)) ) {
		printf("%s :Connect Name Error (%s)\n", __func__, dbus_error.name);
		printf("%s :Message Error (%s)\n",__func__, dbus_error.message);
		dbus_error_free(&dbus_error);
	}
	else{
		dbus_call_method_ping(dbus_conn, &dbus_error);
		dbus_call_method_echo(dbus_conn, &dbus_error);
	}

	dbus_connection_unref(dbus_conn);

	return 0;
}
