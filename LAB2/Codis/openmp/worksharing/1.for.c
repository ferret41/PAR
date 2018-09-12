#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>	/* OpenMP */
#define N 16


/* Q1: How many and which iterations from the loop are executed by each    */
/*     thread? Which kind of \texttt{schedule} is applied by default?      */
/* Q2: Add a directive so that the first "printf" is executed only once    */
/*     by the first thread that finds it.                                  */

int main() 
{
    int i;

    omp_set_num_threads(8);
    #pragma omp parallel 
    {
	#pragma omp single 
	printf("Going to distribute iterations in first loop ...\n");
	#pragma omp for 
        for (i=0; i < N; i++) {
		int id=omp_get_thread_num();
		printf("(%d) gets iteration %d\n",id,i);	
        }
    }

    return 0;
}
