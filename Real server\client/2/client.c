#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define LENGTH_OF_QUEUE 10
#define LENGTH_OF_STRING 128

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Error with initilization socket!");
    return 0;
  }
  struct sockaddr_in str_sock;
  str_sock.sin_family = AF_INET;
  str_sock.sin_port = htons(5001);
  str_sock.sin_addr.s_addr = htonl(INADDR_ANY);

  int connect_status =
      connect(sock, (struct sockaddr *)&str_sock, sizeof(struct sockaddr));
  if (connect_status < 0) {
    perror("Connect Error!");
    return 0;
  }
  // Работаем пока не будет введено:
  // quitserv - выключает сервер
  // quit_client - выключает клиента
  while (1) {
    char *str = calloc(LENGTH_OF_STRING, sizeof(char));
    fputs("\nEnter string:", stdout);
    fgets(str, LENGTH_OF_STRING, stdin);
    if (!strncmp(str, "quit_client", 11)) {
      strncpy(str, "quitserv", 8);
      int send_status = send(sock, str, LENGTH_OF_STRING, 0);
      if (send_status < 0) {
        perror("Sending Error!");
        return 0;
      }
      free(str);
      break;
    }
    int send_status = send(sock, str, LENGTH_OF_STRING, 0);
    if (send_status < 0) {
      perror("Sending Error!");
      return 0;
    }
    free(str);
    str = calloc(LENGTH_OF_STRING, sizeof(char));
    int recieve_status = recv(sock, str, LENGTH_OF_STRING, 0);
    if (recieve_status < 0) {
      perror("Receive Error!");
      return 0;
    }
    fputs(str, stdout);
    free(str);
  }

  close(sock);
  return 0;
}