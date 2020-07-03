struct client
{
	char firstName[16];
	char lastName[16];
	long number;

};
void addClient(struct client *book, int *numOfClient);
void printBook(struct client *book, int numOfClientInBook);
void deleteClient(struct client *book, int *numOfClientInBook, long long deleteNumber);
void searchClient(struct client *book, int numOfClientInBook, long long deleteNumber);

