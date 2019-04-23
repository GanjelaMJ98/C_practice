#include <stdio.h>
#include <stdlib.h>

//Stack//

struct  intStack{
	int size;
	int* data;
	int cnt;
};


int initStack (struct intStack *st, int size){
	st->data = (int*)malloc(size);
		if(st->data == NULL)
			return -1;
	st->size = size;
	st->cnt = 0;
return 0;
}


int push(struct intStack *st, int el){
	if(st->cnt < st->size){
		st->data[st->cnt] = el;
		st->cnt ++;
	}
	else{
		printf("Error, stack is full");
		return 0;
		 }	 
return 0;		 
}



int pop(struct intStack *st){
	int buf;
		if(st->cnt > 0){
			buf = st->data[st->cnt - 1];
			st->cnt --;
		}
return buf;	
}


void test(){
	struct intStack test;

	initStack(&test,10);
	printf("Input: 1, 2, 3, 4, 5\n");
	push(&test,1);
	push(&test,2);
	push(&test,3);
	push(&test,4);
	push(&test,5);
	printf("Output:\n");
	printf("%d\n", pop(&test));
	printf("%d\n", pop(&test));
	printf("%d\n", pop(&test));
	printf("%d\n", pop(&test));
	printf("%d\n", pop(&test));
}

int main(){
	test();
}