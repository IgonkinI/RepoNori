#include "struct.h"
#include "stdio.h"
#define N 10

int main(int argc, char const *argv[])
{
	struct client book[N];

	int choice;
	int condition = 0;
	long numberToSearch;
	do
	{
		printf("\nPhone book\n1.Add client\n2.Show book\n3.Delete client\n4.Search client\n5.Exit\n");
		scanf("%d", &choice);

		switch(choice){

			case 1:
			addClient(book, &condition);
			condition++;
			break;

			case 2:
			printBook(book,condition);
			break;

			case 3:
			printf("\nEnter number of client: ");
			scanf("%ld",&numberToSearch);
			deleteClient(book, condition, numberToSearch);
			break;

			case 4:
			printf("\nEnter number of client: ");
			scanf("%ld",&numberToSearch);
			searchClient(book, condition, numberToSearch);
			break;
		}

		
	} while (choice!=5);
	
	return 0;
}


