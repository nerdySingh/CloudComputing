#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#define numb_threds 1
#define Max_iterations 100000
#define Time_To_Wait 1

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
    printf("\n This is Random access for %s:",filename);
    printf("\n");
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
    FILE *f;
    printf("\n This is sequential access for %s:",filename);
    f=fopen(filename,"r");
    char buffer[Max_iterations];
    if(f!=NULL)
    {
        while(fgets(buffer,Max_iterations,f));
        //printf("The sequential access data is :%s\n",buffer);
        fclose(f);
    }
    else
    {
        printf("File broken or not present\n");
    }
    randomAccess(filename);
    return NULL;
}

 void *initialize(void *arg)
 {
    int r,i;
    int *myid = (int *) arg;
    printf("\n  This is the thread %d\n",*myid);
    char filename1[] = "TestB.txt";
    char filename2[] = "TestKB.txt";
    char filename3[] = "TestMB.txt";
    char filename4[] = "Test80MB.txt";
    r=checkfile(filename1);
    if (r==1)
    {
    sequentialAccess(filename1);
    sequentialAccess(filename2);
    sequentialAccess(filename3);
    sequentialAccess(filename4);
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