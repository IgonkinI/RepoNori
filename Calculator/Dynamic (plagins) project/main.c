#include "stdio.h"
#include "stdlib.h"
#include "dlfcn.h"
#include "string.h"
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char const *argv[])
{
	DIR *dir;
    struct dirent *entry;

    dir = opendir("plagins");
   
    if (!dir) {
        perror("diropen");
        exit(1);
    };

   char test_name_of_functions[10][20];
   int num = 0;
   char functions[10][20];
   
    while ( (entry = readdir(dir)) != NULL) {

        strncpy(test_name_of_functions[num],entry->d_name, 20);
        num++;
      	};

    closedir(dir);
    int mid = 0;
    char function_names[10][30];

    for (int i = 0; i < 10; i++){
    	for (int j = 0; j < 30; ++j)
    	{
    		function_names[i][j]=0;
    	}
    }
  	for (int i = 0; i < 10; i++){
    	
    	for (int j = 0; j < 20; ++j)
    	{
    		functions[i][j]=0;
    	}
    }
    
    for (int i = 0; i < num; ++i)
    {
    	if(!strncmp(test_name_of_functions[i], "lib",3)){

    		strncpy(function_names[mid],"plagins/",8);
    		function_names[mid][8]=0;
    		strncat(function_names[mid],test_name_of_functions[i],20);
    		strncpy(functions[mid],test_name_of_functions[i], 20);
     		mid++;
    	}
    }

    void *ptr[10];

    for (int i = 0; i < mid; ++i)
    {
    	ptr[i] = dlopen(function_names[i],RTLD_LAZY);

    		if (!ptr) { 
		fprintf(stderr, "dlopen failure: %s\n", dlerror()); 
        exit (EXIT_FAILURE); 
       }
    }

    int choice;
   
    while (1){

    	puts("\nMenu");
    	for (int i = 0; i < mid; ++i)
    	{
    		printf("%d.%s\n",i+1, function_names[i]);
    	}
    	printf("%d.Exit\n",mid+1);
    	scanf("%d", &choice);
    	

    	if (choice == (mid + 1)){
    		break;
    	}
  
    	float a, b, y;

   		printf("\nEnter a = ");
		scanf("%f",&a);
		printf("\nEnter b = ");
		scanf("%f",&b);

		
		
		float (*wt_func)(float*, float*);
		
		
		char questions[10][20];
		// Зануляем все элементы
		for (int i = 0; i < 10; i++){
    	for (int j = 0; j < 20; ++j)
    	{
    		questions[i][j]=0;
    	}
  		  }

		for (int k = 0; k < mid; k++){
			for (int i = 3; i < strlen(functions[k]) - 3; i++){

				questions[k][i-3] = functions[k][i];

			}
	}
		
		wt_func = dlsym(ptr[choice-1],questions[choice-1]);
		
		if (!wt_func) { 
				fprintf(stderr, "dlsym failure: %s\n", dlerror()); 
				exit (EXIT_FAILURE);
				}

		y = wt_func(&a,&b);
		printf("\nAnswer is: %f\n", y);
    }

    printf("\nThanks!\n");
	return 0;
}
