#include "stdlib.h"
#include <stdio.h>
#include <stdint.h>
#include "string.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define MAX_LENGTH_OF_LINE 256  // Макисмальная длина строки, введеной пользователем
#define MAX_LENGTH_OF_PARAM 16  // Макисмальная длина функции/параметра
#define MAX_NUM_OF_PARAM 10
#define MSG_SIZE 4096

int main(int argc, char **argv, char **envp) {
  while (1) {
    char *line;

    line = calloc(MAX_LENGTH_OF_LINE, sizeof(char));
    int curr_pos_read = 0;

    while ((line[curr_pos_read] = getc(stdin)) != '\n') {
      curr_pos_read++;
    }
    line[curr_pos_read] = ' ';

    char *command_line;
    command_line = calloc(5, sizeof(char));
    strncpy(command_line, "/bin/", 5);

    int i = 0;
    while (line[i] != ' ') {
      if (!realloc(command_line, i + 1 + 5)) {
        free(command_line);
        free(line);
        perror("realloc");
        exit(1);
      }
      command_line[i + 5] = line[i];
      i++;
    }
    i++;
    int lstrt = i;

    char request[MAX_NUM_OF_PARAM][MAX_LENGTH_OF_PARAM];

    i = lstrt;
    int curr_num = 0;

    while (line[i] != '\0') {
      if (line[i] == ' ') {
        int curr_num2 = 0;
        for (int j = lstrt; j < i; j++) {
          request[curr_num][curr_num2] = line[j];
          curr_num2++;
        }
        request[curr_num][curr_num2] = '\0';
        curr_num++;

        i++;
        lstrt = i;
      }
      i++;
    }

    char **arr;
    arr = calloc(1, sizeof(char *));

    arr[0] = command_line;
    for (int j = 0; j <= curr_num; j++) {
      if (!realloc(arr, (2 + j) * sizeof(char *))) {
        free(command_line);
        free(line);
        perror("realloc");
        exit(1);
      }
      arr[j + 1] = request[j];
    }

    arr[curr_num + 1] = NULL;

    int p[2];
    pipe(p);
    pid_t pid1;

    if (pid1 = fork() == 0) {
      dup2(p[1], 1);
      close((uintptr_t)stdout);
      write(p[1], (void *)(uintptr_t)execv(command_line, arr), MSG_SIZE);
      close(p[1]);

      return 0;

    } else {
      wait(NULL);
      char *buff;
      buff = calloc(MSG_SIZE, MSG_SIZE * sizeof(char));
      read(p[0], buff, MSG_SIZE);
      printf("\n%s\n", buff);
      close(p[0]);
      free(buff);
    }

    free(command_line);
    free(line);

    free(arr);
  }
  return 0;
}
