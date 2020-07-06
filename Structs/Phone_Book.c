#include "struct.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define N 1


int main(int argc, char const *argv[])
{
	struct client *book;
	book = (struct client*)malloc(N * sizeof(struct client));

	int choice;
	int condition = 0;
	long numberToSearch;
	int countAdd = 0;
	do
	{
		printf("\nPhone book\n1.Add client\n2.Show book\n3.Delete client\n4.Search client\n5.Exit\n");
		scanf("%d", &choice);

		switch(choice){

			case 1:
			addClient(book, &condition);
			condition++;
			countAdd++;
			if ((condition >= N)&&(condition >= countAdd)) {
				book = realloc(book, (condition + 1) * sizeof(struct client));
			}
			break;

			case 2:
			printBook(book,condition);
			break;

			case 3:
			printf("\nEnter number of client: ");
			scanf("%ld",&numberToSearch);
			deleteClient(book, &condition, numberToSearch);
			break;

			case 4:
			printf("\nEnter number of client: ");
			scanf("%ld",&numberToSearch);
			searchClient(book, condition, numberToSearch);
			break;
		}

		
	} while (choice!=5);

	free(book);
	
	return 0;
}


