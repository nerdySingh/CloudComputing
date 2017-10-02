#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
    int cores, FLOPS,avx;
    double max_hz;

    double tpp;

    cores = 8;
    FLOPS = 8;
    max_hz = 3.1;
    avx = 4;
    tpp = cores * FLOPS * max_hz;
    tpp =  tpp + avx * max_hz *cores;
    tpp = tpp * pow(10,6);
    printf("theoretical	peak performance of processor is: %f FLOPS/sec\n",tpp); 
    return 0;
}