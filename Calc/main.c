#include "stdio.h"
#include "calc.h"
int main(int argc, char const *argv[])
{
	int a, b, y;
	int choice;
	// Цикл работает, пока не будет выбран пятый пункт
do {
	printf("\nCalculator\n1.Sum a+b = y\n2.Difference a - b = y\n3.Devider a / b = y\n4.Multiplication a * b = y\n5.Exit\nChoose the paragraph: ");
	scanf("%d", &choice);

	switch(choice){

		case 1:
		getNumber(&a,&b);
		sum(a,b,&y);
		printAnswer(&y);
		break;
	
		case 2:
		getNumber(&a,&b);
		difference(a,b,&y);
		printAnswer(&y);
		break;

		case 3:
		getNumber(&a,&b);
		devide(a,b,&y);
		printAnswer(&y);
		break;

	
		case 4:
		getNumber(&a,&b);
		mult(a,b,&y);
		printAnswer(&y);
		break;
	}


} while(choice != 5);
	return 0;
}
