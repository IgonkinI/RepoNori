#include "stdio.h"
#include "string.h"

struct client
{
	char firstName[16];
	char lastName[16];
	long number;

};


int main(int argc, char const *argv[])
{
	
	struct client book[10];
	


	

	int choice = 6;
	int condition = 0;
	char *point;
	do
	{
		
		printf("\n\tMenu\n1.Add client\n2.Show clients\n3.Remove client\n4.Search the client\n5.Exit\nWould you like?\n");

		scanf("%d",&choice);

		switch(choice) {

			case 1:
			

			// Добавляем запись в наш массив структур
			printf("\nEnter firstname and lastName\n");
			
			point = book[condition].firstName;
			
			while((*point++=getchar()) != ' ');
			
				*point = '\0'; 

			point = book[condition].lastName;
			
			while((*point++=getchar()) != '\n');
			
				*point = '\0'; 
			
			printf("\nEnter telephone\n");
			
			scanf("%ld", &book[condition].number); 

			condition++;
			break;

			case 2:

			// Выводим массив структур
			for (int step = 0; step < condition; step++)
			{
				printf("\nName\tLast name\n");

				for (int i = 0; i < sizeof(book[step].firstName)/sizeof(book[step].firstName[0]); ++i)
				{
					printf("%c",book[step].firstName[i]);
				}

				printf("\t");
	
				for (int i = 0; i < sizeof(book[step].lastName)/sizeof(book[step].lastName[0]); ++i)
				{
					printf("%c",book[step].lastName[i]);
				}	

				printf("\nNumber\t%ld\n\n",book[step].number);

			}

			break;

			case 3:
			// Выполняем поиск по номеру телефона, если есть совпадение заменяем на "0" и "DELETE"
			printf("\nEnter number to delete.\n");
			long deleteNumber;
			scanf("%ld",&deleteNumber);
			short searchAnswer = 0;
			for (int i = 0; i < condition; ++i)
			{
				
				if (book[i].number == deleteNumber)
				{
					book[i].number = 0;
					
					strncpy(book[i].firstName,"DELETED",7);
					strncpy(book[i].lastName, "DELETED", 7);
					searchAnswer++;
				}
				
			}

			// Если такого номера нет, выводим сообщение, мол, нету :) и наоборот
			if (searchAnswer == 0)
				{
					printf("\nThis number does not exist\n");
				} else
				{
					printf("\nThis nimber is deleted\n");
				}

			break;


			// Выполняем поиск по номеру телефона в нашем массиве структур, если такой есть, то выводим 
			// данные о клиенте, если такого номера нет, ничего не выводим.
			case 4:

			printf("\nEnter telepone number of client\n");

			long number_to_show;

			scanf("%ld", &number_to_show);

			for (int step = 0; step < condition; ++step)
			{
				
				if (book[step].number == number_to_show)
				{
					
					printf("\nName\tLast name\n");

					for (int i = 0; i < sizeof(book[step].firstName)/sizeof(book[step].firstName[0]); ++i)
					{
						printf("%c",book[step].firstName[i]);
					}

					printf("\t");
	
					for (int i = 0; i < sizeof(book[step].lastName)/sizeof(book[step].lastName[0]); ++i)
					{
						printf("%c",book[step].lastName[i]);
					}	

					printf("\nNumber\t%ld\n\n",book[step].number);
				}
				
			}
			break;

		}

	} while (choice != 5); // Когда выполняется это условие, мы выходим из цикла и завершаем программу

	


	return 0;
}