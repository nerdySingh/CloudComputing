#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include<pthread.h>
#define threads 8
#define bufferSize 6400

clock_t start,end;
void *connectionTest(void *sock)
{
    int sockServer,n;
    int sockClient;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    unsigned short  serverPort;
    unsigned int clientLen;
    struct hostent *server;
    char buffer[bufferSize];
    int val;
    double latency, thru;
    

    serverPort = (unsigned short)sock;
    printf("%hu\n",serverPort);

    if ((sockServer =socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
    {
        printf("Socket Failed\n");
    }

    memset(&serverAddress,0,sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr =htonl(INADDR_ANY);
    serverAddress.sin_port=htons(serverPort);
    
    if(connect(sockServer,(struct sockaddr*) &serverAddress,sizeof(serverAddress))<0)
    {
        printf("Connect Failed\n");
    }
    
        printf("Please Enter the message to be sent\n");
        bzero(buffer,bufferSize);
        fgets(buffer,6399,stdin);
        send(sockServer,buffer,strlen(buffer),0);
        printf("Contents Sent by The Receiver are:%s\n",buffer);
        bzero(buffer,6399);
        n = read(sockServer,buffer,6399);
        if(n<0)
        {
            printf("Error writing to socket\n");
        }
        printf("Contents fFrom the Server are:%s\n",buffer);
        end =clock();
    latency = (double)(end-start)/CLOCKS_PER_SEC;
    thru = 524288 / latency;
    thru = thru / 1000000;

    printf("Latency Of the System in seconds is %f\n",latency);
    printf("The throughput of the system in Mb/second's is %f\n",thru);
    close(sockServer);
    return (NULL);  
}
int main(int argc, char *argv[])
{
    int sockServer,n,i;
    int sockClient;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    unsigned short serverPort;
    unsigned int clientLen;
    struct hostent *server;
    pthread_t th[threads];
    char buffer[bufferSize];
    if (argc<3)
    {
       fprintf(stderr,"Usage:  %s <Server Port>\n", argv[0]);
       exit(1);
    }
    serverPort = atoi(argv[2]);
    server = gethostbyname(argv[1]);
    start =clock();
    for(i=0;i<threads;i++)
    {
        pthread_create(&th[i],NULL,connectionTest,(void *)serverPort);
    }
    for(i=0;i<threads;i++)
    {
        pthread_join(th[i],NULL);
    }

    return 0;
}
