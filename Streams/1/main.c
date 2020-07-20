#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
void* func(void *ptr){
	int *a = (int*) ptr;
	printf("%d,", *a);
	return 0;
}

int main(int argc, char const *argv[])
{
	int i;
	pthread_t pthread_ID[5];
	for (i = 0; i<5;i++){
		pthread_create(&pthread_ID[i], NULL, func, &i);
	}
	for (i = 0; i<5;i++){
		pthread_join(pthread_ID[i], NULL);
	}
	return 0;
}
