#include "stdio.h"
#include "stdlib.h"
#include "dlfcn.h"
#include "string.h"


int main(int argc, char const *argv[])
{	
	int choice = 0;
	// Если library_ptr == NULL, то происходит прекращение работы и вывод соответсвующего сообшения.
	void *library_ptr;	
	library_ptr = dlopen("libcalc.so", RTLD_LAZY);	
	if (!library_ptr) { 
		fprintf(stderr, "dlopen failure: %s\n", dlerror()); 
        exit (EXIT_FAILURE); 
       }
	printf("\n");
	// line_of_names содержит все функции, которые имеются в библиотеке.
	// Эту переменню должен заполнить разработчик. 
	// Названия должны соответствовать названиям функций в библиотеке.
	char *line_of_names;
	line_of_names = dlsym(library_ptr, "names");
	puts("Enter the names of the functions you need and then enter - exit");
	puts(line_of_names);
	// Калькулятор рассчитан на 10 функций, максимальная длина названия функции - 12 символов.
	char answer[10][12];
	int m = 0;
	char st[] = "exit";
	// Здесь мы узнаем, какие функции потребуются пользователю.
	while (1){	
		fgets(answer[m],12,stdin);
	// Проверяем, ввел ли пользователь "exit", если да, то выходим из цикла.
		if (!strncmp(answer[m],st,4)){
			break;
		}
		m++;
	}
	// Удаляем символ окончания строки.
	// Необходимо для обращения к функциям.
	for (int i = 0; i <= m; ++i)
	{
		answer[i][strlen(answer[i]) - 1] = 0;
	}

	while (1){
		float a, b, y;
		printf("\n\nMenu\n");
		for (int i = 0; i <= m; ++i)
		{
			printf("\n%d.%s",i + 1,answer[i] );
		}
	
		do {
			printf("\nPlease, enter function number:\n");
			scanf("%d", &choice);
			choice--;
		} while ((choice > m) || (choice < 0));
	// Проверка на выход из калькулятора.
	// Если пользователь ввел номер выхода -
	// прекращаем работу программы.
		if (!strncmp(answer[choice],st,4)){
			printf("\nThank you for using this calculator!\n");
			return 0;
		}
		float (*wt_func)(float*, float*);
		printf("\nEnter a = ");
		scanf("%f",&a);
		printf("\nEnter b = ");
		scanf("%f",&b);
		wt_func = dlsym(library_ptr,answer[choice]);
	// Если не найдем введеную пользователем функцию, программа прекратится и на экран выведется сообщение,
	// что такой функции нет.
		if (!wt_func) { 
			fprintf(stderr, "dlsym failure: %s\n", dlerror()); 
			exit (EXIT_FAILURE);
			}
		y = wt_func(&a,&b);
		printf("\nAnswer is: %f\n", y);
	}
	dlclose(library_ptr);
	return 0;
}