#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>
#define numb_threds 8
#define Max_iterations 100000000
#define Time_To_Wait 1
int g =0;
int i;
long addIOP(long d)
{
    for(i=0;i<Max_iterations;i++)
    {
        d = d +d ;
    }
    return d;
}
long subtractIOP(long d)
{
    for(i=0;i<Max_iterations;i++)
    {
        d = d -d ;
    }
    return d;
}
long mulIOP(long d)
{
    for(i=0;i<Max_iterations;i++)
    {
        d = d *d ;
    }
    return d;
}
long divIOP(long d)
{
    for(i=0;i<Max_iterations;i++)
    {
        d = d /d ;
    }
    return d;
}

double add(double d)
{   
    
    for(i=0;i<Max_iterations;i++)
    {
        d = d + d ;
    }
    return d;
}
double multiply(double d)
{
    for(i=0;i<Max_iterations;i++)
    {
        d = d * d ;
    }
    return d;

}
double subtract(double d)
{
    for(i=0;i<Max_iterations;i++)
    {
        d = d - d ;
    }
    return d;
}
double divide(double d)
{
    for(i=0;i<Max_iterations;i++)
    {
        d = d /d ;
    }
    return d;
}
void *threadFunctionFlop()
{
    FILE *f;
    double d  = pow(2,-128);
    clock_t start,end;
    int count =0;
    double cpu_time_used;
    int i;
    long iterations = Max_iterations / numb_threds;
    do
    {
    start = clock();
    d = add(d);
    end =clock();
    cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
    count = count + cpu_time_used;
    if (count > 1.000000)
    {
        break;
    }
    start = clock();
    d = subtract(d);
    end =clock();
    cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
    count = count + cpu_time_used;
    if (count > 1.000000)
    {
        break;
    }

    start = clock();
    d = multiply(d);
    end =clock();
    cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
    count = count + cpu_time_used;
    if (count > 1.000000)
    {
        break;
    }
    
    start = clock();
    d = divide(d); 
    end =clock();
    cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
    count = count + cpu_time_used;
    if (count > 1.000000)
    {
        break;
    }
    printf("Before Time: %f s\n",cpu_time_used);
    }while(count==1.000000);
    f = fopen("FLOPS.dat","a");
    printf("After Time: %f s\n",cpu_time_used);
    fprintf(f,"%f\n",cpu_time_used);
    fclose(f);
    
    double Flops=(Max_iterations)/(double)(cpu_time_used);
    long gFlops=(double)Flops/1000000000;// Calculate Giga Flops Formula: F lops * 10raised to (-9).
  
    printf("GFLOPS : %f\n",gFlops);
    return NULL;
}


    void *threadFunctionIops()
    {
        FILE *f;
        long d  = 0x3fd5555555555555L;
    
        clock_t start,end;
        int count =0;
        double cpu_time_used;
        int i;
        long iterations = Max_iterations / numb_threds;
        do
        {
        start = clock();
        d = addIOP(d);
        end =clock();
        cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
        count = count + cpu_time_used;
        if (count > 1.000000)
        {
            break;
        }
        start = clock();
        d = mulIOP(d);
        end =clock();
        cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
        count = count + cpu_time_used;
        if (count > 1.000000)
        {
            break;
        }
        start = clock();
        d = subtractIOP(d);
        end =clock();
        cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
        count = count + cpu_time_used;
        if (count > 1.000000)
        {
            break;
        }
        }while(count == 1.000000);
        f = fopen("IOPS.dat","a");
        printf("After Time: %f s\n",cpu_time_used);
        fprintf(f,"%f\n",cpu_time_used);
        fclose(f);
        printf("Time: %f s\n",cpu_time_used);
        double Flops=(Max_iterations)/(double)(cpu_time_used);
        long gFlops=(double)Flops/1000000000;// Calculate Giga Flops Formula: F lops * 10raised to (-9).
      
        printf("GFLOPS : %f\n",gFlops);
        return NULL;
    }


int main()
{
    int count =600;
    pthread_t th,th1;
    clock_t last,end;
    
    double cputime;
    last = clock();
    while(count>0)
    {
            
           for(i=0;i<numb_threds;i++)
            {
                pthread_create(&th,NULL,threadFunctionFlop,&i);
                pthread_join(th,NULL);
            }
            
            for(i=0;i<numb_threds;i++)
            {
                pthread_create(&th1,NULL,threadFunctionIops,&i);
                pthread_join(th1,NULL);
            }
        count= count-1;
     }
    return 0;
}
