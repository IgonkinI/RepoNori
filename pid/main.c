#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	printf("\nPROC 1: PID %d \t PPID \t%d\n", getpid(), getppid());
	
	pid_t pid1, pid2;
		
	// входим внутрь первого дочернего процесса
	 if ((pid1 = fork()) == 0) { 
   		 printf("\nPROC 2: PID %d \t PPID \t%d\n", getpid(), getppid());
	 
  		    	pid_t pid11;
   		 	 	if ((pid11 = fork()) == 0) { // Первый
   		 			printf("\nPROC 4: PID %d \t PPID \t%d\n", getpid(), getppid());
   				}
   		

  		}
  		// проверка, что мы вышли из первого дочернего процесса и вошли во второй
 	 if (pid1 > 0 && (pid2 = fork()) == 0) { 
   		 printf("\nPROC 3: PID %d \t PPID \t%d\n", getpid(), getppid());
   		 		pid_t pid11, pid21;
   		 		// теперь входим в первый дочерний процесс второго дочернего процесса
   		 	 	if ((pid11 = fork()) == 0) { 
   		 			printf("\nPROC 5: PID %d \t PPID \t%d\n", getpid(), getppid());
  				}
  				// входим внутрь второго дочернего процесса второго дочернего процесса
 				if (pid11 > 0 && (pid21 = fork()) == 0) { 
   				printf("\nPROC 6: PID %d \t PPID \t%d\n", getpid(), getppid());
 				}
 		}
	return 0;
}