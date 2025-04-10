#include<omp.h>
#include<stdio.h>

#define arr_size 100000000
int a[arr_size];
int main(int *argc, char *argv)
{
    int i, tid, numt, sum=0;
    double t1,t2;

    for(i=0; i<arr_size; i++)
    {
        a[i] = 1;
    }
    omp_set_num_threads(4);
    t1 = omp_get_wtime();
    #pragma omp parallel default(shared) private(i,tid)
    {
        int from, to;
        int psum=0;//introducing private variable for each thread
        tid = omp_get_thread_num();
        numt = omp_get_num_threads();

        from = (arr_size / numt ) * tid;
        to = (arr_size / numt ) * (tid + 1) - 1;
        if(tid == numt-1)
          to = arr_size - 1;
        
          printf("Hello from %d of %d, my range is from=%d to=%d\n",tid, numt, from, to);
          for(i = from; i<= to;i++)
          {
            psum += a[i];
          }
          #pragma omp critical
          sum += psum;

    }
        t2 = omp_get_wtime();
        printf("Sum of the array elements = %d. Time=%g\n", sum, t2-t1);
        return 0;
    }

    //result : Sum of the array elements = 100000000. Time=0.141926 
    //after adding psum and pragma omp critical on shared variable sum: time and sum both are now correct.