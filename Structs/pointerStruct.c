#include "stdio.h"


struct test
{
	char a;
	int b;
};

struct test1
{
	char a;
	int b;
}__attribute__((packed));


int main(int argc, char const *argv[])
{
	
	// Указатель на неупакованную структуру и действия с ним
	char *str;
	struct test my_test;


	str = (char*)&my_test;
	my_test.a = 'A';
	my_test.b = 45;
	printf("%ld\n", sizeof(struct test));
	printf("%d\n", *str);
	str++;
	// После перехода на следующий байт, мы получаем значение paddinga идущего после первого байта (char). Вроде бы, так.
	printf("%d\n", *str);
	printf("\n\n\n\n");
	
	//При packed у нас получается, что после первого байта, принадлежащего char a, сразу же идет int b = 56
	struct test1 my_test1;
	char *ptr;
	ptr = (char*)&my_test1;
	
	my_test1.a = 'A';
	my_test1.b = 56;
	printf("%ld\n", sizeof(struct test1));
	
	printf("%d\n", *ptr);
	ptr++;
	printf("%d\n", *ptr);
	return 0;

}