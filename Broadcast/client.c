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
        perror("socket error");
        exit(EXIT_FAILURE);
    } 	
    struct sockaddr_in server_stats;
    server_stats.sin_family = AF_INET;
    server_stats.sin_addr.s_addr = inet_addr("255.255.255.255");
    server_stats.sin_port = htons(PORT); 
    if (bind(sockfd, (const struct sockaddr *)&server_stats, sizeof(server_stats)) < 0){
    	 perror("bind failed");
         exit(EXIT_FAILURE);
    }
	int n, len;
    char buffer[MAX_SIZE];
    n = recvfrom(sockfd, (char *)buffer, MAX_SIZE, MSG_WAITALL, (struct sockaddr *) &server_stats, &len);
    buffer[n] = '\0'; 
    printf("\n Message recieved on client is - %s\n",buffer);
    close(sockfd); 
	return 0;
}