#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<time.h>
#define threads 1
clock_t start,end; 

#define GB 1000000000 

double latency,throughput;


void randomWrite80MB(char *p)
{
	int size = 160000000,i,len=1;
	char *ch =p;
	for(i=80000000;i<size;i++)
	{
		((char *)ch)[i+len] = 'K';
		len =rand()%3;
	}

}

void randomWrite8MB(char *p)
{

	int size = 16000000,i,len=1;
	char *ch2 =p;
	for(i=8000000;i<size;i++)
	{
	 ((char *)ch2)[i+len]= 'F';
	  len =rand()%3;
	}
}

void randomWrite8KB(char *p)
{

	int size =16000,i,len=1;
	char *ch2 = p;
	for(i=8000;i<size;i++)
	{
		((char *)ch2)[i*len] ='E';
		len =rand()%3;
	}
}


void randomWrite8Bytes(char *p)
{
	int size =16,i,len=1;
	char *ch = malloc(8);
	char *ch2 = p;
	for(i=0;i<size;i++)
	{
		((char *)ch2)[2*len]='C';
		len =len*2;
	}
	//printf("Random write done.\n");		
}

void write80MBfile(char *p)
{
    FILE *f;
    time_t start,end,duration;
    char buffer[8],buffer1[80],buffer2[15],ch;
    char *ch1=p;
    char *ch2 = p;
    int len,i;
    if (ch1!=NULL)
    {
     
       memset(ch1,'A',80000000);
       //printf("Sequential Write is Done.\n");
       len=strlen(ch1);
       memcpy(ch2,ch1,80000000);
       //printf("%d\n",len);
       
      // printf("Sequential Read is Done.\n");
    }
}

void write8MBfile(char *p)
{
    FILE *f;
    time_t start,end,duration;
    char buffer[8],buffer1[8000000],buffer2[15],ch;
    char *ch1=p;
    int len;
    if (ch1!=NULL)
    {
     
       memset(ch1,'A',8000000);
       //printf("Sequential Write is Done.\n");
       len=strlen(ch1);
       memcpy(buffer1,ch1,8000000);
       //printf("Sequential Read is Done.\n");
    }
}

//8kb file is this.
void write8KBfile(char *p)
{
    FILE *f;
    time_t start,end,duration;
    char buffer[8],buffer1[8000],buffer2[15],ch;
    char *ch1=p;
    int len;
    if (ch1!=NULL)
    {
     
       memset(ch1,'A',8000);
       //printf("Sequential Write is Done.\n");
       len=strlen(ch1);
       memcpy(buffer1,ch1,8000);
       //printf("Sequential Read is Done.\n");
    }
}



// 8 bytes file starts here
void write8Bytesfile(char *p)
{
    FILE *f;
<<<<<<< HEAD
    time_t start,end,duration;
    char buffer[8],buffer1[15],buffer2[15],ch;
    char *ch1=p;
    int len;
    if (ch1!=NULL)
    {
     
       memset(ch1,'A',8);
       //printf("Sequential Write is Done.\n");
       len=strlen(ch1);
       memcpy(buffer1,ch1,8);
       //printf("Sequential Read is Done.\n");
    }
=======
    char buffer[8000000],buffer1[15000000],buffer2[15000000],ch;
    int len,i;
    start = clock();
    double latency;
    f = fopen("8MB.txt","r"); //Conducting Read + Write Operation
    if (f==NULL)
    {
        f = fopen("8MB.txt","w");
        memset(buffer,'A',8000000);
        fprintf(f,"%s",buffer);
        fclose(f);
    }
    else
    {
        i=0;
        memset(buffer,0,8000000);
        while((ch =fgetc(f))!=EOF)
        {
            buffer2[i] = ch;
            i +=1;
        }
        //printf("Values:%s\n",buffer2);
        memcpy(buffer1,buffer2,strlen(buffer2)+1);
        //printf("The Contents of the file as read are:%s\n",buffer1);
        fclose(f);
        end = clock();
    }

    latency = (double)(end-start)/CLOCKS_PER_SEC;
    printf("latency of 8Kbytes sequential Read + Write in seconds is %f\n",latency);

>>>>>>> 83e16af849841b4b9c6e9f97a398f2054667c592
}

void *initialize(void *args)
{
   	int count = 0;
	double d;
	char *t = (char *)args;
	start =clock();
	while(count<10)
	{
	   write8Bytesfile(t);
           count = count+1;
	}
	
	end =clock();
	d = (double)((end-start)/CLOCKS_PER_SEC);
	write8KBfile(t);
	//end=clock();
        write8MBfile(t);
	write80MBfile(t);
	randomWrite8Bytes(t);
	randomWrite8KB(t);
	randomWrite8MB(t);
	randomWrite80MB(t);    
	//end=clock();
	//latency = (double)((end-start)/CLOCKS_PER_SEC);
	latency=d+latency;
	
 
    return (NULL);
}

int main()
{
    char *p,*r;
    int count =threads,i,k;
    p =malloc(GB);
    r =malloc(GB);
    for(i=0;i<GB;i++)
    {
      ((char *)p)[i] ='B'; 
    }
 
    while(count <6)
    {
    	pthread_t th[count];
	for(i=0;i<count;i++)
	{
		pthread_create(&th[i],NULL,initialize,(char *)p);
	}
	for(i=0;i<count;i++)
	{
    		pthread_join(th[i],NULL);
	}
     	count = count *2;
     }
	
    free(p);
    latency =latency/1000;
    throughput = (8/1000000) * latency;
    throughput = throughput + (8/1000) * latency;
    throughput = throughput + 8*latency;
    throughput = throughput + 80 * latency;
    printf("latency is :%f\n",latency);
    printf("Throughput is :%f\n",throughput);

    return 0;
}
