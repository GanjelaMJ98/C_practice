#include <stdio.h>
#include <stdlib.h>

struct  intQueue{
	int size;
	int* data;
	int cnt;
	int cnt1;
};

int initQueue (struct intQueue *q, int size){
	q->data = (int*)malloc(size);
		if(q->data == NULL)
			return -1;
	q->size = size;
	q->cnt = 0;
	q->cnt1 = 0;
	return 0;
}

int push(struct intQueue *q, int el){
	if(q->cnt < q->size){
		q->data[q->cnt] = el;
		q->cnt ++;
	}
	else{
		printf("Error, Queue is full");
		return 0;
		}	 
return 0;		 
}
int pop(struct intQueue *q){
	int buf;
		if(q->cnt > 0){
			buf = q->data[q->cnt1];
			q->cnt --;
			q->cnt1 ++;
		}
	return buf;	
}


int main(){
	struct intQueue test;

	initQueue(&test,10);
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