#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#define LENGTH_OF_QUEUE 10
#define LENGTH_OF_STRING 128
#define MAX_CLIENT 10

void* service_client(void *ptr){
  
  char string_to_change[] = "Answer from server. I destroyed your message!!!";
  int *accept_socket = (int*) ptr;
  while (1) {
    char *buff_str = calloc(LENGTH_OF_STRING, sizeof(char));

    int rcv_status = recv(*accept_socket, buff_str, LENGTH_OF_STRING, 0);

    if (rcv_status < 0) {
      perror("Receive error!");
      return 0;
    }

    if (!strncmp(buff_str, "quitserv", 8)) {
      break;
    }

    printf("%s\n", buff_str);

    strncpy(buff_str, string_to_change, strlen(string_to_change));
    int send_status = send(*accept_socket, buff_str, LENGTH_OF_STRING, 0);
    if (send_status < 0) {
      perror("Sending Error!");
      return 0;
    }
    free(buff_str);
  }
  close(*accept_socket);
}


int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Error with initilization socket!");
    return 0;
  }
  struct sockaddr_in str_sock;
  str_sock.sin_family = AF_INET;
  str_sock.sin_port = htons(5001);
  //Как я понял, INADDR_ANY - привязывает сокет ко всем доступным сетевым
  //интерфейсам (?)
  str_sock.sin_addr.s_addr = htonl(INADDR_ANY);
  int test_bind =
      bind(sock, (struct sockaddr *)&str_sock, sizeof(struct sockaddr_in));

  if (test_bind < 0) {
    perror("Bind error");
    return 0;
  }
  int test_listen = listen(sock, LENGTH_OF_QUEUE);
  if (test_listen < 0) {
    perror("Listen Error!");
    return 0;
  }
int accept_socket[MAX_CLIENT];

int curr_num_of_clients = 0;
  while(1){
  pthread_t pthread_ID;
  accept_socket[curr_num_of_clients] = accept(sock, NULL, NULL);
  if (accept_socket[curr_num_of_clients] < 0) {
    perror("Accept Error!");
    return 0;
  }
    pthread_create(&pthread_ID, NULL, service_client, &accept_socket[curr_num_of_clients]);
    curr_num_of_clients++;
}
  for (int i = 0; i < curr_num_of_clients; i++){
    close(accept_socket[curr_num_of_clients]);
  }
  close(sock);
  return 0;
}
