#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include<ctype.h>
#include <pthread.h>
#define threads 8 //Change the number of threads on the server here.
void *start(void *args)
{
    char buffer[6400];
    socklen_t addr_size, client_addr_size;
    struct sockaddr_storage serverStorage;
    addr_size = sizeof(serverStorage);
    int nBytes,i;
    int udpSocket = (int)args;
    while(1)
    {
        nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
       
        printf("Data is %s",buffer);
       
        sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
      }
}

int main(){
  int udpSocket, nBytes;
  char buffer[6400];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  pthread_t th[threads];
  int i;
  udpSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(&serverAddr,0,sizeof(serverAddr));
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  
  addr_size = sizeof serverStorage;
  for (i=0;i<threads;i++)
  {
      pthread_create(&th[i],NULL,start,(void *)udpSocket);
      pthread_join(th[i],NULL);
  }


 

  return 0;
}