#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <netinet/ip.h> 
#include <unistd.h>
#define PORT 7777 
#define MAX_SIZE 1024
//Сервер и клиент работают в бесконечном цикле.
int main(int argc, char const *argv[])
{
	int sockfd;
	 if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket error");
        exit(EXIT_FAILURE);
    } 	
    struct sockaddr_in server_stats;
    server_stats.sin_family = AF_INET;
    server_stats.sin_addr.s_addr = INADDR_ANY;
    server_stats.sin_port = htons(PORT); 
    if (bind(sockfd, (const struct sockaddr *)&server_stats, sizeof(server_stats)) < 0){
    	 perror("bind failed");
         exit(EXIT_FAILURE);
    }
    struct ip_mreqn imr;
    imr.imr_multiaddr.s_addr = inet_addr("224.0.0.1");
    imr.imr_address.s_addr = INADDR_ANY;
    imr.imr_ifindex = 0;
    setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &imr, sizeof(imr));
    while(1){
	int n, len;
    char buffer[MAX_SIZE];
    n = recvfrom(sockfd, (char *)buffer, MAX_SIZE, MSG_WAITALL, (struct sockaddr *) &server_stats, &len);
    buffer[n] = '\0'; 
    printf("\n Message recieved on client is - %s\n",buffer);
}
    close(sockfd); 
	return 0;
}