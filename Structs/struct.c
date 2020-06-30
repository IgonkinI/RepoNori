#include "stdio.h"
#include "string.h"
struct client
{
	char firstName[16];
	char lastName[16];
	long number;

};
void addClient(struct client *book, int *numOfClient){

			char *point;
			printf("\nEnter firstname and lastName\n");
			
			point = book[*numOfClient].firstName;
			
			while((*point++=getchar()) != ' ');
			
				*point = '\0'; 

			point = book[*numOfClient].lastName;
			
			while((*point++=getchar()) != '\n');
			
				*point = '\0'; 
			
			printf("\nEnter telephone\n");
			
			scanf("%ld", &book[*numOfClient].number); 

}

void printBook(struct client *book, int numOfClientInBook){
	
		printf("\n_______________________________________________");
	for (int i = 0; i < numOfClientInBook; ++i)
	{	
		printf("\n");
		char str[32];
		strcpy(str,book[i].firstName);
		strcat(str," ");
		strcat(str,book[i].lastName);
		puts(str);
		printf("%ld", book[i].number);
		printf("\n_______________________________________________");
	}
}

void deleteClient(struct client *book, int numOfClientInBook, long long deleteNumber){
	
		
	for (int i = 0; i < numOfClientInBook; ++i)
	{		
		if (book[i].number == deleteNumber)
		{
			book[i].number = 0;
			strcpy(book[i].firstName,"DELETED");
			strcpy(book[i].lastName,"DELETED");
		}
	}
}

void searchClient(struct client *book, int numOfClientInBook, long long deleteNumber){
	
		printf("\n");
	for (int i = 0; i < numOfClientInBook; ++i)
	{		
		if (book[i].number == deleteNumber)
		{
			char str[32];
			strcpy(str,book[i].firstName);
			strcat(str," ");
			strcat(str,book[i].lastName);
			puts(str);
			printf("%ld", book[i].number);
		}
	}
}