#include "stdio.h"
#include "string.h"
#include "struct.h"
#include <malloc.h>
#include <stdlib.h>

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

void deleteClient(struct client *book, int *numOfClientInBook, long long deleteNumber){
	
	int numToDelete = -1;
		
	for (int i = 0; i < *numOfClientInBook; ++i)
	{		
		if (book[i].number == deleteNumber)
		{
			numToDelete = i;
		}
	}
	if (numToDelete == -1)
	{
		printf("\nNumber does not exist!\n");
		return;
	}
	
	for (int i = numToDelete; i < *numOfClientInBook - 1 ; ++i)
	{
		
			book[i].number = book[i+1].number;
			strcpy(book[i].firstName,book[i+1].firstName);
			strcpy(book[i].lastName,book[i+1].lastName);

	}
			*numOfClientInBook = *numOfClientInBook - 1;
			//book = realloc(book, (*numOfClientInBook) * sizeof(struct client));
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
			printf("\n_______________________________________________");
			puts(str);
			printf("%ld", book[i].number);
			printf("\n_______________________________________________");
		}
	}
}