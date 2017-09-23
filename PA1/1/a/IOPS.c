#include<stdio.h>
#include<pthread.h>
#include<stdint.h>
#include<stdlib.h>
#define numb_threds 1
#define Max_iterations 100000000
int g =0;
void *threadFunctionFlop()
{
    int64_t  d  = 0x0000444400004444LL;
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
  
    printf("GFLOPS : %f\n",gFlops);
    return NULL;
}


int main()
{
    
    int i;
    for(i=0;i<numb_threds;i++)
    {
        threadFunctionFlop();
    }
    return 0;
}
