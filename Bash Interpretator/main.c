#include "stdlib.h"
#include <stdio.h>
#include "string.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
 #include <sys/stat.h>
#define MAX_LENGTH_OF_LINE 256 // Макисмальная длина строки, введеной пользователем
#define MAX_LENGTH_OF_PARAM 10 // Макисмальная длина функции/параметра

#define MSG_SIZE 2048


int main(int argc,char **argv,char **envp)
{

	pid_t pid1;
	char *line, *line1;
	line = calloc(MAX_LENGTH_OF_LINE, sizeof(char));
	printf("\nEnter command:");
	fgets(line, MAX_LENGTH_OF_LINE, stdin);
	line1 = calloc(MAX_LENGTH_OF_LINE, sizeof(char));
	strncpy(line1, "/bin/", 5);
	line[strlen(line) - 1] = '\0';	
	
	int curr_pos_fw = 0;

	for (int i = 0; i <= strlen(line); i++)
	{
		if ((line[i] == ' ') || (line[i] == '\0')){
			curr_pos_fw = i;
			break;
		}
	}

	for (int i = 0; i <= curr_pos_fw ; i++){
		line1[i+5]=line[i];
	}	

	char* arr[] = {line, NULL};
	int p[2];
	pipe(p);
	if (pid1 = fork() == 0)
	{	
		
		
		
		dup2(p[1], 1);
		close(stdout);
		write(p[1], execv(line1, arr), MSG_SIZE);
		close(p[1]);

		return 0;
		
	} else {
		wait(NULL);
			char buff[MSG_SIZE];
			read(p[0], buff, MSG_SIZE);
			printf("\n%s\n",buff );
			close(p[0]);
		
	}





	return 0;
}
