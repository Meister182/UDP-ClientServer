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
  char buffer[] = {
//  ---- 9 bytes : only CAN msg ----
    // 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
//  ---- 16 bytes : CAN info + CAN msg ----
    //  0x00, 0x08, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
    //  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
// ---- 36 bytes : Header + CAN info + CAN msg ----
    0x00, 0x24, 0x00, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
// // ---- Adding a Second CAN package ----    
//     0x00, 0x24, 0x00, 0x80, 0x00, 0x00, 
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
//     0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
// // ---- UDP header + 2 can messages ----
//     0x00, 0x24, 0x00, 0x80, 0x00, 0x00, 
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
//     0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    // 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}; // + 9 bytes
    // 0x00, 0x08, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
    // 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}; //+ 16 bytes
  
  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  memset(&serverAddr, '\0', sizeof(serverAddr));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = inet_addr(ipadr);

  //strcpy(buffer, "Hello Server\n");
 
  for(int i=0; i<2; i++){
    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("[+]Data Send: %s\n", buffer);
  }
}
