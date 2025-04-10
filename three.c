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
    //all variables are shared by default unless specified otherwise.
    //private(i,tid) variables i and tid will be separate for each thread(each thread gets it own copy)
    {
        int from, to;
        tid = omp_get_thread_num();
        numt = omp_get_num_threads();

        from = (arr_size / numt ) * tid;
        to = (arr_size / numt ) * (tid + 1) - 1;
        if(tid == numt-1)
          to = arr_size - 1;
        
          printf("Hello from %d of %d, my range is from=%d to=%d\n",tid, numt, from, to);
          for(i = from; i<= to;i++)
          {
            #pragma omp critical
            sum += a[i];
          }

    }
        t2 = omp_get_wtime();
        printf("Sum of the array elements = %d. Time=%g\n", sum, t2-t1);
        return 0;
    }

    //result : Sum of the array elements = 50439450. Time=0.295696 
    //after adding pragma omp critical: time is very much more  
    //100000000. Time=2.30952 : sum is correct but time is very much more.