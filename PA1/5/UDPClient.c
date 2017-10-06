#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include<ctype.h>
#include <pthread.h>
#define threads 8 //Change the number of threads on the client here.
void *start(void *args)
{
    int clientSocket,data,i;
    char buffer[6400];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    
    clientSocket = (int)args;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&serverAddr,0,sizeof(serverAddr));
  

    addr_size = sizeof(serverAddr);
    
    while(1){
        printf("Type a sentence to send to server:\n");
        fgets(buffer,1024,stdin);
        printf("You typed: %s",buffer);
    
        data = strlen(buffer) + 1;
        
        /*Send message to server*/
        sendto(clientSocket,buffer,data,0,(struct sockaddr *)&serverAddr,addr_size);
    
        /*Receive message from server*/
                    data = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);
    
        printf("Received from server: %s\n",buffer);
    
      }
}

int main()
{
    int clientSocket,i;
    pthread_t th[threads];
    clientSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  for (i=0;i<threads;i++)
  {
      pthread_create(&th[i],NULL,start,(void *)clientSocket);
      pthread_join(th[i],NULL);
  }
  return 0;
}