#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void main(int argc, char **argv){

  int port;
  char *ipadr;
  if(argc == 2){
    port = atoi(argv[1]);
    ipadr = "INVALID";
  }else if(argc ==3){
    port = atoi(argv[1]);
    ipadr = argv[2];
  }else{
    printf("Usage: %s <port>\n", argv[0]);
    printf("Usage: %s <port> <ip>\n", argv[0]);
    exit(0);
  }




  int sockfd;
  struct sockaddr_in si_me, si_other;
  char buffer[1024];
  socklen_t addr_size;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&si_me, '\0', sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(port);
  if(ipadr != "INVALID"){
    si_me.sin_addr.s_addr = inet_addr(ipadr);
  }else{
    si_me.sin_addr.s_addr = INADDR_ANY;
  }

  bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me));
  addr_size = sizeof(si_other);
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)& si_other, &addr_size);
  printf("[+]Data Received: %s", buffer);

}