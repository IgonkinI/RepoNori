#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MAX_SIZE 1024
int main(int argc, char const *argv[])
{
    int sockfd;
     if ( (sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    } 
    int val = 1;
    struct sockaddr_in server_stats,client_addr;
    server_stats.sin_family = AF_INET;
    server_stats.sin_addr.s_addr = htonl(INADDR_ANY);
    server_stats.sin_port = htons(0); 
    if (bind(sockfd, (const struct sockaddr *)&server_stats, sizeof(server_stats)) < 0){
         perror("bind failed");
         exit(EXIT_FAILURE);
    }
    char *message = "Message from server!\0";
    while(1){
    sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &server_stats, sizeof(server_stats)); 
    }
    close(sockfd); 
    return 0;
}