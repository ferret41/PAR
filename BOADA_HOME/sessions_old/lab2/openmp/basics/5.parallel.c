#include <stdio.h>
#include <omp.h>
#define N 8
#define NUM_THREADS 4

/* Q1: How many messages the program prints? Which iterations      */
/*     of the loop is each thread executing?                       */
/* Q2: Change the for loop to ensure that its iterations are       */
/*     distributed among all participating threads                 */

int main() 
{
    #pragma omp parallel num_threads(NUM_THREADS) 
    {
	int id=omp_get_thread_num();
        for (int i=id; i < N; i=i+1) {
		printf("Thread ID %d Iter %d\n",id,i);	
        }
    }
    return 0;
}
