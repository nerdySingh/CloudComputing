#include<stdio.h>
#include<pthread.h>

#include<stdlib.h>
#define numb_threds 2
#define Max_iterations 100000000
int g =0;

void *threadFunctionFlop(void *arg)
{
  int i;
  double a=5;
  // convert string argument to long
  long iterations=strtol((char*)arg,NULL,0);
  
  for(i = 0; i < iterations; i++)
  {
    a=a+a;
    printf("%f",a);
  }
  return NULL;
}


void *mythreadFunctionFlop(int noOFThreads)
{
    clock_t start,end;
    double cpu_time_used;
    int i;
    long double a=5;
    pthread_t th[numb_threds];
    long iterations = Max_iterations / numb_threds;
    char iterationStr[20];
    printf(iterationStr,20,"%lu",iterations);
    printf("\nProgram to find FLOPS for %d threads",noOFThreads);
    start = clock();
    for(i=0;i<noOFThreads;i++)
    {
        pthread_create(&th[i],NULL,threadFunctionFlop,&iterationStr);
        pthread_join(th[i],NULL);
    }
    end = clock();
    cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC ;
    printf("\nTime: %f s\n",cpu_time_used);
    double Flops=(Max_iterations)/(double)(cpu_time_used);
    long gFlops=(double)Flops/1000000000;// Calculate Giga Flops Formula: F lops * 10raised to (-9).
  
    printf("GFLOPS : %ld\n",gFlops);
    
}

int main()
{
    mythreadFunctionFlop(numb_threds);
    return 0;

}
