#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>
clock_t start,end;
void write8Bytesfile()
{
    FILE *f;
    char buffer[8],buffer1[15],buffer2[15],ch;
    int len,i;
    start = clock();
    double latency;
    f = fopen("8Bytes.txt","r"); //Conducting Read + Write Operation
    if (f==NULL)
    {
        f = fopen("8Bytes.txt","w");
        memset(buffer,'A',8);
        fprintf(f,"%s",buffer);
        fclose(f);
    }
    else
    {
        i=0;
        memset(buffer,0,8);
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
    printf("latency of 8 Bytes Sequential Read + Write in seconds is %f\n",latency);
}
void write8KBytesfile()
{
    FILE *f;
    char buffer[8000],buffer1[15000],buffer2[15000],ch;
    int len,i;
    start = clock();
    double latency;
    f = fopen("8KB.txt","r"); //Conducting Read + Write Operation
    if (f==NULL)
    {
        f = fopen("8KB.txt","w");
        memset(buffer,'A',8000);
        fprintf(f,"%s",buffer);
        fclose(f);
    }
    else
    {
        i=0;
        memset(buffer,0,8000);
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

    
}

void write8MBfile()
{
    char *data;
    FILE *f;
    void *ptr1;
    int len,i;
    char *buffer;
    int bytes =  8*1024*1024;
    data = malloc(bytes);
    for(i=0;i<bytes;i++)
    {
        data[i] = 'A';
    }
    printf("Sequential write in memory is done.\n");
    memcpy(buffer,data,(strlen(data)+1));
    printf("Sequential read in memory is done.\n");

}

void *initialize()
{
    write8Bytesfile();
    write8KBytesfile();
    write8MBfile();
    return (NULL);
}

int main()
{
    pthread_t th;
    pthread_create(&th,NULL,initialize,NULL);
    pthread_join(th,NULL);
    return 0;
}