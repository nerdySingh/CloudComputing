#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), connect(), recv() and send() */
#include <arpa/inet.h> /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MaxClients 5
#define threads 17
#define bufferSize 6400
struct ThreadArgs
{
    int clientsocket;
};


void HandleClient(int clientsocket)
{
    char buffer[bufferSize];
    int receivedMsg;

    if((receivedMsg =recv(clientsocket,buffer,bufferSize,0))<0)
    {
        printf("Recieve Failed");
    }
    
    while(receivedMsg >0)
    {
    
        if(send(clientsocket,buffer,receivedMsg,0)!=receivedMsg)
        {
            printf("send failed\n");
        }
        if((receivedMsg = recv(clientsocket,buffer,bufferSize,0))<0)
        {
            printf("Receive Failed");
        }
        else
        {
            
            printf("The message received is :%s\n",buffer);
            send(clientsocket,buffer,receivedMsg,0);
        }
    }
    close(clientsocket);
}
void *threadMain(void *threadArgs)
{
    int *clientsocket = (int *)threadArgs;
    HandleClient(*clientsocket);
    return (NULL);
}
int main(int argc, char *argv[])
{
    int sockServer,count = threads,i;
    int sockClient;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    unsigned short serverPort;
    unsigned int clientLen;
    pthread_t th;
    struct ThreadArgs *threadArgs;

    if (argc !=2)
    {
        fprintf(stderr, "Usage:  %s <Server Port>\n", argv[0]);
        exit(1);
    }

    serverPort = atoi(argv[1]);
    printf("Server port is: %d\n",serverPort);

    if ((sockServer =socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
    {
        printf("Socket Failed\n");
    }

    memset(&serverAddress,0,sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr =htonl(INADDR_ANY);
    serverAddress.sin_port=htons(serverPort);
    if (bind(sockServer,(struct sockaddr *) &serverAddress,sizeof(serverAddress))<0)
    {
        printf("Bind has failed\n,Try again\n");
    }

    if (listen(sockServer,MaxClients)<0)
    {
        printf("Listen has failed\n");
    }
    for(;;)
    {
        clientLen = sizeof(clientAddress);
        for(i=0;i<threads;i++)
        {
        if((sockClient =accept(sockServer,(struct sockaddr*) &clientAddress,&clientLen))<0)
        {
            printf("Accept Failed\n");
        }
        printf("Handling Client %s\n",inet_ntoa(clientAddress.sin_addr));
        if((threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs)))==NULL)
        {
            printf("Error in structure allocation of Thread Args");
        }
        threadArgs -> clientsocket = sockClient;
        pthread_create(&th,NULL,threadMain,(void *)threadArgs);
        }
       /*if (pthread_create(&th,NULL,threadMain,(void *)threadArgs)!=0)
       {
           printf("Error Creating the thread\n");
       }*/
       
    }

}