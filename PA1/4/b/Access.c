#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#define numb_threds 1
#define Max_iterations 100000
#define Time_To_Wait 1

void calcLatency(char filename[],char filename1[])
{
    FILE *f,*chk;
    char buffer[Max_iterations];
    char data[Max_iterations];
    int i,len;
    f = fopen(filename,"r");
    chk = fopen(filename1,"r");
    if (f!=NULL && chk!=NULL)
    {
        while(fgets(data,Max_iterations,f));
        len = strlen(data);
        for(i=0;i<len;i++)
        {
            if(data[i] == fgetc(chk))
            {
                printf("*8 byte data matches the GB memory block\n");
            }
        } 
    }
}

void writeFile(char filename[],int counter)
{
    FILE *f;
    int i,k =2;
    char data[]= "Tanveer Anand";
    f = fopen(filename,"w");
    for(int i=0;i<counter;i++)
    {
        fseek(f,i*k,SEEK_SET);
        fputs("T",f);
        k=k+1;
    }
    fclose(f);

}
void randomAccessWrite()
{
    double latency;
    clock_t start,end;
    char filename1[] = "TestB.txt";
    writeFile(filename1,3);
    char filename2[] = "TestKB.txt";
    writeFile(filename2,90);
    char filename3[] = "TestMB.txt";
    writeFile(filename3,2830);
    char filename4[] = "Test80MB.txt";
    writeFile(filename4,8945);
    start = clock();
    char filename5[] ="Test1GB.txt";
    writeFile(filename5,90000);
    calcLatency(filename1,filename5);
    end = clock();
    latency = (double)((end-start));
    printf("\n The latency of the file operation in milliseconds is %f ",latency);
}


int checkfile(char filename[])
{
    FILE *f;
    f=fopen("TestKB.txt","r");
    if (f==NULL)
    {
        printf("file doesnt exist\n");
        fclose(f);
        return 0;
    }
    else
    {   
        fclose(f);
        return 1;
    }
}

void randomAccess(char filename[])
{
    FILE *f;
    int i=1;
    f=fopen(filename,"r");
    //printf("\n This is Random access for %s:",filename);
    //printf("\n");
    char buffer[Max_iterations];
    if(f!=NULL)
    {
        while(fgetc(f)!=EOF)
        {
            fseek(f,i,SEEK_SET);
            while(fgets(buffer,Max_iterations,f));
            i = i*2;
        }
        //printf("The random access data is :%s\n",buffer);
        fclose(f);
    }
}

void *sequentialAccess(char filename[])
{
    FILE *f,*chk;
    int len,i;
    //printf("\n This is sequential access for %s:",filename);
    //printf("\n");
    f=fopen(filename,"r");
    chk = fopen("Test1GB.txt","r");
    char buffer[Max_iterations];
    if(f!=NULL && chk!=NULL)
    {
        while(fgets(buffer,Max_iterations,f));
        len = strlen(buffer);
        for (i=0;i<len;i++)
        {
            if(buffer[i]!=fgetc(chk))
            {
                break;
            }
        }
        //printf("The sequential  access data is :%s\n",buffer);
        fclose(f);
    }
    else
    {
        printf("File broken or not present\n");
    }
    //randomAccess(filename);
    return NULL;
}

 void *initialize(void *arg)
 {
    randomAccessWrite(); 
    clock_t start,end;
    int r,i;
    double throughput=0.0,latency;
    int *myid = (int *) arg;
    printf("\n  This is the thread %d\n",*myid);
    char filename1[] = "TestB.txt";
    char filename2[] = "TestKB.txt";
    char filename3[] = "TestMB.txt";
    char filename4[] = "Test80MB.txt";
    r=checkfile(filename1);
    if (r==1)
    {
    //sequentialAccess(filename1);
    start = clock();
    sequentialAccess(filename2);
    end = clock();
    throughput = throughput +(0.008 * (double)(end-start)/CLOCKS_PER_SEC);
    start = clock();
    sequentialAccess(filename3);
    end = clock();
    throughput = throughput +(0.8 * (double)(end-start)/CLOCKS_PER_SEC);
    start = clock();
    sequentialAccess(filename4);
    end = clock();
    throughput = throughput +(8 * (double)(end-start)/CLOCKS_PER_SEC);
    printf("The throughput of the disk in MB/seconds is %f \n",throughput);
    }
    return NULL;
}

int main()
{
        int i,count;
        count =numb_threds;
        
        while(count<9)
        {
        pthread_t th[count];
        for(i=0;i<count;i++)
        {
            pthread_create(&th[i],NULL,initialize,&i);   
        }
        for(i=0;i<count;i++)
        {
            pthread_join(th[i],NULL);
        }
        count = count * 2 ;
    }
    return 0;
}