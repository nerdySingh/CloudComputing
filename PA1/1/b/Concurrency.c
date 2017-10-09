#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>
#define numb_threds 1
#define Max_iterations 100000000
int g =0;
double gflops1=0.0,gflops2=0.0,gflops3;

void *threadFunctionFlop1()
{
    double d  = pow(2,-128);
    clock_t start,end;
    double cpu_time_used;
    int i;
    long iterations = Max_iterations / numb_threds;
    start = clock();
    for(i=0;i<Max_iterations;i++)
    {
        d = d /d ;
    }
    for(i=0;i<Max_iterations;i++)
    {
        d = d + d ;
    }
    for(i=0;i<Max_iterations;i++)
    {
        d = d - d ;
    }
    for(i=0;i<Max_iterations;i++)
    {
        d = d * d ;
    }
    end = clock();
    cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
    printf("\nTime: %f s\n",cpu_time_used);
    double Flops=(Max_iterations)/(double)(cpu_time_used);
    long gFlops=(double)Flops/1000000000;// Calculate Giga Flops Formula: F lops * 10raised to (-9).
    gflops2 = Flops;
    
    return NULL;
}





void *threadFunctionFlop(void *arg)
{
    //printf("This is thread executing the IOPS instruction for Concurrency.%d\n ",(int)arg);
    long d  = 0x3fd5555555555555L;
    clock_t start,end;
    double cpu_time_used;
    int *myid = (int *)arg;
    int i;
    long iterations = Max_iterations / numb_threds;
    start = clock();
    for(i=0;i<Max_iterations;i++)
    {
        d = d /d ;
    }
    for(i=0;i<Max_iterations;i++)
    {
        d = d + d ;
    }
    for(i=0;i<Max_iterations;i++)
    {
        d = d - d ;
    }
    for(i=0;i<Max_iterations;i++)
    {
        d = d * d ;
    }
    end = clock();
    cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
    //printf("Thread ID: %d\n", *myid);
    //printf("Time: %f s\n",cpu_time_used);
    double Flops=(Max_iterations)/(double)(cpu_time_used);
    long gFlops=(double)Flops/1000000000;// Calculate Giga Flops Formula: F lops * 10raised to (-9).
    gflops1 = Flops +gflops1;
    threadFunctionFlop1();
    //printf("GFLOPS : %f\n",gFlops);
    return NULL;
}


int main()
{
    
    int i,no_threads;
    no_threads = numb_threds;
    
    while(no_threads < 2)
    {
        pthread_t th[no_threads];
        for(i=0;i<no_threads;i++)
        {
            pthread_create(&th[i],NULL,threadFunctionFlop,&i);
        }
        for(i=0;i<no_threads;i++)
        {
            pthread_join(th[i],NULL);
        }
	printf("No of threads exexuted:%d\n",i);
	printf("\n"); 
       no_threads = no_threads * 2;
    }
   
    gflops1 = gflops1 /1000000000;
    gflops2 = gflops2 / 1000000000;
    printf("GFLOPS : %f\n",gflops1);
    printf("GFLOPS : %f\n",gflops2);
 

    return 0;
}
