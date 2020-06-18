#include "stdio.h"

int main(int argc, char const *argv[])
{

	// Первое задание
	// В этом задание, из-за приравнивания разных типов, как я понял,
	// возникает предупреждение. Но работает.
	int a = 270533154;
	// (char*) необходимо для избежания warning
	char *ptr = (char*)&a;
// Вывод 4-х байт числа а
	for (int i = 0; i < 4; ++i)
	{
	    printf("%d - й байт числа равен %d\n", i + 1, *ptr);
	    ptr++;
	}
// Изменение второго байта числа а
	ptr = (char*)&a;
	ptr+=2;
	*ptr = 8;
	printf("\n3-й байт числа а изменен на %d\n",*ptr);

	ptr = (char*)&a;
// Вывод 4-х байт числа а
	printf("\nОбновленное число а\n");
	for (int i = 0; i < 4; ++i)
	{
	    printf("%d - й байт числа равен %d\n", i + 1, *ptr);
	    ptr++;
	}

// Второе задание

	char a2 = 'A';
	char b2 = 'B';
	char *ptr1;
	char **ptr2;

	ptr1 = &a2;
	ptr2 = &ptr1;
	// меняем значение ptr1 через ptr2
	*ptr2 = &b2;
	printf("\n\nИзмененное ptr1 = %c\n", *ptr1);


	return 0;
}