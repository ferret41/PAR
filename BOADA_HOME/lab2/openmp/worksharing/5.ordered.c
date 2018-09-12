#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>	/* OpenMP */
#define N 16

/* Q1: Can you explain the order in which printf appear?                   */
/* Q2: How can you ensure that a thread always executes two consecutive    */
/*     iterations in order during the execution of the ordered part of the */
/*     loop body?                                                          */

int main() 
{
    int i;

    omp_set_num_threads(8);
    #pragma omp parallel 
    {
        #pragma omp for schedule(dynamic) ordered
        for (i=0; i < N; i++) {
		int id=omp_get_thread_num();
		printf("Before ordered - (%d) gets iteration %d\n",id,i);	
		#pragma omp ordered
		printf("Inside ordered - (%d) gets iteration %d\n",id,i);	
        }
    }

    return 0;
}
