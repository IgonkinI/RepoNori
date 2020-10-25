#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/udp.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MAX_SIZE 4080
#define SPORT 5001
#define DPORT 5008

int main(int argc, char const *argv[]) {
  int sockfd;
  if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }
  struct sockaddr_in server_stats;
  server_stats.sin_family = AF_INET;
  server_stats.sin_addr.s_addr = inet_addr("192.111.133.5");
  server_stats.sin_port = htons(DPORT);

  int n, len;
  while (1) {
    char buffer[MAX_SIZE];
    n = recvfrom(sockfd, (char *)buffer, MAX_SIZE, MSG_WAITALL,
                 (struct sockaddr *)&server_stats, &len);
    buffer[n] = '\0';
    printf("\n Message recieved on client is:\n");
    int i = 32;
    while (buffer[i] != '\0') {
      printf("%c", buffer[i]);
      i++;
    }
  }
  close(sockfd);
  return 0;
}