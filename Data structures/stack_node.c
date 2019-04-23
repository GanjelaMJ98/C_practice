#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
	float mas[2];
	float (*area)(float *);
	float (*perim)(float *);
	struct node* next;
} *pnode, node;


typedef struct stack{
	pnode head;
	int cnt;
} stack;


float area_t (float *m){
	return (m[0]*m[1]);
}

float perim_t(float *m){
	return ((m[0]+m[1])*2);
}

float area_c(float *m){

	return (m[0]*m[0]*3.14);
}

float perim_c(float *m){
	return ((m[0]*6.28));
}

float area_tr(float *m){
	return (m[0]*m[0])/2;
}

float perim_tr(float *m){
	return 2*(sqrt(m[0]*m[0]+(m[1]/2)*(m[1]/2))) + m[1];
}			 

stack *init_stack(){
	stack *new = (stack*)malloc(sizeof(stack));
	new-> head = NULL;
	new-> cnt = 0;
	return new;
}



void push (int a, int b, stack *st, int n){
	pnode new = (pnode)malloc(sizeof(node));
	if(!new){
		printf("Error in %s\n", __func__);
		return;
	}
	new->mas[0] = a;
	new->mas[1] = b;
	switch(n)
	{
		case 1:
		new->area=area_tr;
		new->perim=perim_tr;
		break;
	
		case 2:
		new->area=area_c;
		new->perim=perim_c;
		break;

		case 3:
		new->area=area_t;
		new->perim=perim_t;
		break;
	}
	new->next = st->head;
	st->head = new;
	st->cnt++;
}


void print(stack *st){
	int i = st->cnt;
	node *tmp = st->head;
	while(tmp){
		printf("№: %d\n", i);
		printf("area = %f\n",tmp->area(tmp->mas));
		printf("perim = %f\n",tmp->perim(tmp->mas));
		i --;
		tmp = tmp->next;
	}
}



int main(){
	stack *mstack = init_stack();
	int a,b,n,r=1;
	while(r){
	printf("\n\n1 - tr\n2 - cir\n3 - tet\n4 - exit\n\n");
	scanf("%d", &n);
	printf("\n");
	switch(n){
		case 1:
		printf("H = ");
		scanf("%d", &a);
		printf("\n");
		printf("A = ");
		scanf("%d", &b);
		printf("\n");
		push(a,b,mstack,n);
		break;

		case 2:
		printf("R = ");
		scanf("%d", &a);
		printf("\n");
		push(a,0,mstack,n);
		break;

		case 3:
		printf("A = ");
		scanf("%d", &a);
		printf("\n");
		printf("B = ");
		scanf("%d", &b);
		printf("\n");
		push(a,b,mstack,n);
		break;

		case 4:
		print(mstack);
		r = 1;
		break;
		}
	}
}









