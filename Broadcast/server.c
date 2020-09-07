#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define PORT 2048 
#define MAX_SIZE 1024
int main(int argc, char const *argv[])
{
	int sockfd;
	 if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    } 
	int val = 1;
    setsockopt(sockfd,SOL_SOCKET, SO_BROADCAST, &val, sizeof(int));
    struct sockaddr_in server_stats,client_addr;
    server_stats.sin_family = AF_INET;
    server_stats.sin_addr.s_addr = inet_addr("255.255.255.255");
    server_stats.sin_port = htons(PORT); 
    char *message = "Message from server!";
    char buffer[MAX_SIZE]; 
    sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &server_stats, sizeof(server_stats)); 
    close(sockfd); 
	return 0;
}