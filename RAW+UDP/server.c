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
#define MAMAX_SIZEX_SIZE 1024
#define SPORT 5001
#define DPORT 5008


int main(int argc, char const *argv[])
{
    int sockfd;
  if ( (sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    } 
    char data[4080];

    
    struct sockaddr_in server_stats;
    
    server_stats.sin_family = AF_INET;
    server_stats.sin_addr.s_addr = htonl(INADDR_ANY); 
    

    struct udphdr *udph=(struct udphdr*)data;
    udph->uh_sport=htons(SPORT); 
    udph->uh_dport=htons(DPORT); 
    udph->uh_ulen=htons(strlen(data) + 4); 
    udph->uh_sum=0; 
    
    char *mes = "Message from server is cavabanga!\0";
    int i = 0;
    do {
        data[sizeof(udph) + 1 + i] = mes[i];
        i++;
    }while(mes[i]!='\0');
    
   while(1){
   sendto(sockfd, &data, sizeof(data), 0, (struct sockaddr*)&server_stats, sizeof(server_stats));
   printf ("sendto ok\n");
   
}
    close (sockfd); 
}
