#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define STREAMS_NUMBER 5
pthread_mutex_t mutex;

// Программа работает корректно, но при STREAMS_NUMBER = 500 комп улетает.

void* func(void *ptr){
	long *a;
	long tmp;

	for (int j = 0; j < 10000000; j++){
		pthread_mutex_lock(&mutex);
		a = (long*) ptr;
		tmp = *a;
		tmp++;
		*a=tmp;
		pthread_mutex_unlock(&mutex);
	}

	//printf("\n%ld\n", *a);
	return 0;
}

int main(int argc, char const *argv[])
{	pthread_mutex_init(&mutex, NULL);
	int i;
	long param = 0;
	pthread_t pthread_ID[STREAMS_NUMBER];
	for (i = 0; i<STREAMS_NUMBER;i++){
		pthread_create(&pthread_ID[i], NULL, func, &param);
	}
	for (i = 0; i<STREAMS_NUMBER;i++){
		pthread_join(pthread_ID[i], NULL);
	}
	printf("\nAnswer is %ld\n", param);
	return 0;
}
