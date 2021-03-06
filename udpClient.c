#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 

void main(int argc, char **argv){

  int port;
  char *ipadr;
  if(argc == 2){
    port = atoi(argv[1]);
    ipadr = "127.0.0.1";
  }else if(argc ==3){
    port = atoi(argv[1]);
    ipadr = argv[2];
  }else{
    printf("Usage: %s <port>\n", argv[0]);
    printf("Usage: %s <port> <ip>\n", argv[0]);
    exit(0);
  }



  int sockfd;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  memset(&serverAddr, '\0', sizeof(serverAddr));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = inet_addr(ipadr);

  // char buffer[] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};
  char buffer[116]; //+32 bytes in 2nd stage
  strcpy(buffer, "Hello Server\n");
 
  bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

  for(int i=0; i<72*5; i++){
    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("[%-3d]Data Send: %s", i, buffer);
    usleep(11500); // sending 72 packets per second
  }
}
