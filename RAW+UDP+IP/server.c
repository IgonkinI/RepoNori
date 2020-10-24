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
#include "netinet/ip.h"
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
    char data[MAMAX_SIZEX_SIZE];
    struct sockaddr_in server_stats;
    struct udphdr *udph=(struct udphdr*) (data + sizeof(struct iphdr));
    struct iphdr *iph = (struct iphdr*) (data);
    server_stats.sin_family = AF_INET;
    server_stats.sin_port = htons(1500);
    server_stats.sin_addr.s_addr = inet_addr("192.111.133.5");
    iph->ihl = 5;
	iph->version = 4;
	iph->tos = 16;
	iph->id = htonl (54321);	//Id of this packet
	iph->frag_off = 0;
	iph->ttl = 255;
	iph->protocol = 17;
	iph->check = 0;		 
	iph->saddr = inet_addr("192.168.101.197");	//Spoof the source ip address
	iph->daddr = server_stats.sin_addr.s_addr;
    iph->tot_len = htons(sizeof(data));
    int tx_len = 0;
    tx_len += sizeof(struct iphdr);
    udph->uh_sport=htons(SPORT); 
    udph->uh_dport=htons(DPORT); 
    udph->uh_ulen=htons( sizeof(data) - sizeof(struct iphdr)); 
    udph->uh_sum=0; 
    udph->len = htons(sizeof(data) - sizeof(struct iphdr)); // сейчас тут  
    tx_len += sizeof(struct udphdr);
    tx_len++;
    char *mes = "Message from server is cavabanga!\0";
    int i = 0;
    tx_len++;
    do
    {
        data[tx_len] = mes[i];
        i++;
        tx_len++;
    } while (i<strlen(mes));
    int m = 0;
    int one = 1;
	const int *val = &one;
	
	if (setsockopt (sockfd, IPPROTO_IP, IP_HDRINCL, val, sizeof (one)) < 0)
	{
		perror("Error setting IP_HDRINCL");
		exit(0);
	}
   
    while (m <= 100)
	{
		
		if (sendto (sockfd, data, MAMAX_SIZEX_SIZE,	0, (struct sockaddr *) &server_stats, sizeof (server_stats)) < 0)
		{
			perror("sendto failed");
		}
        printf("All is ok!\n");
    m++;

}
close(sockfd);
return 0;
 
} 