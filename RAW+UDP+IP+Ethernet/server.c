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
#include <netpacket/packet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <net/ethernet.h>
#define MAMAX_SIZEX_SIZE 1000
#define SPORT 5001
#define DPORT 5008

#define DEFAULT_IF "wlp3s0"
int main(int argc, char const *argv[]) {
  char data[MAMAX_SIZEX_SIZE];
  int sockfd;
  if ((sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) < 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  struct ifreq if_idx;
  struct ifreq if_mac;
  char ifName[IFNAMSIZ];

  if (argc > 1)
    strcpy(ifName, argv[1]);
  else
    strcpy(ifName, DEFAULT_IF);

  strncpy(if_idx.ifr_name, ifName, IFNAMSIZ - 1);
  if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0)
    perror("SIOCGIFINDEX");

  strncpy(if_mac.ifr_name, ifName, IFNAMSIZ - 1);
  if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0)
    perror("SIOCGIFHWADDR");

  int tx_len = 0;
  struct ether_header *ethdr = (struct ether_header *)data;
  ethdr->ether_dhost[0] = 0x00;
  ethdr->ether_dhost[1] = 0x01;
  ethdr->ether_dhost[2] = 0x03;
  ethdr->ether_dhost[3] = 0x50;
  ethdr->ether_dhost[4] = 0x10;
  ethdr->ether_dhost[5] = 0x40;

  ethdr->ether_shost[0] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[0];
  ethdr->ether_shost[1] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[1];
  ethdr->ether_shost[2] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[2];
  ethdr->ether_shost[3] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[3];
  ethdr->ether_shost[4] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[4];
  ethdr->ether_shost[5] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[5];
  ethdr->ether_type = htons(ETH_P_IP);

  tx_len += sizeof(ethdr);

  struct sockaddr_ll server_stats;
  server_stats.sll_halen = ETH_ALEN;
  server_stats.sll_addr[0] = 0x00;
  server_stats.sll_addr[1] = 0x01;
  server_stats.sll_addr[2] = 0x03;
  server_stats.sll_addr[3] = 0x50;
  server_stats.sll_addr[4] = 0x10;
  server_stats.sll_addr[5] = 0x40;
  server_stats.sll_ifindex = if_idx.ifr_ifindex;
  struct udphdr *udph = (struct udphdr *)(data + sizeof(struct iphdr) +
                                          sizeof(struct ether_header));
  struct iphdr *iph = (struct iphdr *)(data + sizeof(struct ether_header));
  iph->ihl = 5;
  iph->version = 4;
  iph->tos = 16;
  iph->id = htonl(54321);
  iph->frag_off = 0;
  iph->ttl = 255;
  iph->protocol = 17;
  iph->check = 0;
  iph->saddr = inet_addr("192.168.101.197");
  iph->daddr = inet_addr("192.111.133.5");
  iph->tot_len = htons(sizeof(data) - sizeof(struct ether_header));

  tx_len += sizeof(struct iphdr);

  udph->uh_sport = htons(SPORT);
  udph->uh_dport = htons(DPORT);
  udph->uh_ulen =
      htons(sizeof(data) - sizeof(struct iphdr) - sizeof(struct ether_header));
  udph->uh_sum = 0;
  udph->len =
      htons(sizeof(data) - sizeof(struct iphdr) - sizeof(struct ether_header));
  tx_len += sizeof(struct udphdr);
  tx_len++;
  char *mes = "Message from server is cavabanga!\0";
  int i = 0;
  tx_len++;
  tx_len++;
  do {
    data[tx_len] = mes[i];
    i++;
    tx_len++;
  } while (i < strlen(mes));
  int m = 0;
  while (m <= 100) {
    if (sendto(sockfd, data, MAMAX_SIZEX_SIZE, 0,
               (struct sockaddr *)&server_stats,
               sizeof(struct sockaddr_ll)) < 0) {
      perror("sendto failed");
    }
    printf("All is ok!\n");
    m++;
  }
  close(sockfd);
  return 0;
}