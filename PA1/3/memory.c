#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<time.h>
#define threads 1
clock_t start,end; 

#define GB 1000000000 

double latency;
void write8Bytesfile(char *p)
{
    FILE *f;
    time_t start,end,duration;
    char buffer[8],buffer1[15],buffer2[15],ch;
    char *ch1=p;
    int len;
    if (ch1!=NULL)
    {
     
       memset(ch1,'A',8);
       printf("Sequential Write is Done.\n");
       len=strlen(ch1);
       memcpy(buffer1,ch1,8);
       printf("Sequential Read is Done.%s\n",buffer1);
    }
}

void *initialize(void *args)
{
   	
	char *t = (char *)args;
	start =clock();
	write8Bytesfile(t);
	end=clock();
	latency = (double)((end-start)/CLOCKS_PER_SEC);
	printf("latency is %f\n",latency);
        
    
    return (NULL);
}

int main()
{
    char *p;
    int count =threads,i;
    pthread_t th;
    p =malloc(GB);
    for(i=0;i<GB;i++)
    {
      ((char *)p)[i] ='B'; 
    }
    pthread_create(&th,NULL,initialize,(char *)p);
    pthread_join(th,NULL);
    free(p);
    return 0;
}
