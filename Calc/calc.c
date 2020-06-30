#include "stdio.h"
void getNumber(int *a, int *b){
	printf("\nEnter a = ");
	scanf("%d",&*a);
	printf("\nEnter b = ");
	scanf("%d",&*b);
}

void sum(int a, int b, int *y){
	*y = a + b;
}

void difference(int a, int b, int *y){
	*y = a - b;
}

void devide(int a, int b, int *y){
	*y = a / b;
}

void mult(int a, int b, int *y){
	*y = a * b;
}

void printAnswer(int *y){
	printf("\nAnswer is %d\n", *y);
}