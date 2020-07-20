#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* func(void *ptr){
	long *a;
	long tmp;

	for (int j = 0; j < 10000000; j++){
		a = (long*) ptr;
		tmp = *a;
		tmp++;
		*a=tmp;
	}

	printf("\n%ld\n", *a);
	return 0;
}

int main(int argc, char const *argv[])
{
	int i;
	long param = 24;
	pthread_t pthread_ID[500];
	for (i = 0; i<500;i++){
		pthread_create(&pthread_ID[i], NULL, func, &param);
	}
	for (i = 0; i<500;i++){
		pthread_join(pthread_ID[i], NULL);
	}
	printf("\nAnswer is %ld\n", param);
	return 0;
}