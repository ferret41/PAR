#include "heat.h" 

/*
 * Function to copy one matrix into another
 */

void copy_mat (double *u, double *v, unsigned sizex, unsigned sizey)
{
	
	#pragma omp parallel 
    {
    int howmany = omp_get_num_threads();
    int blockid = omp_get_thread_num(); 
    
    int i_start = lowerb(blockid, howmany, sizex);
    int i_end = upperb(blockid, howmany, sizex);
    
    for (int i=max(1, i_start); i<= min(sizex-2, i_end); i++) {
      for (int j=1; j<= sizey-2; j++) {
	     v[i*sizey+j] = u[i*sizey+j];
	   }
     }
    }

	/* 
    for (int i=1; i<=sizex-2; i++)
        for (int j=1; j<=sizey-2; j++) 
           v[ i*sizey+j ] = u[ i*sizey+j ];
    */ 
}

/*
 * Blocked Jacobi solver: one iteration step
 */
double relax_jacobi (double *u, double *utmp, unsigned sizex, unsigned sizey)
{
    double diff, sum=0.0;
  
  
  
    #pragma omp parallel private(diff) reduction(+:sum)
    {
    int howmany = omp_get_num_threads();
    int blockid = omp_get_thread_num(); 
    
    int i_start = lowerb(blockid, howmany, sizex);
    int i_end = upperb(blockid, howmany, sizex);
    
    for (int i=max(1, i_start); i<= min(sizex-2, i_end); i++) {
      for (int j=1; j<= sizey-2; j++) {
	     utmp[i*sizey+j]= 0.25 * ( u[ i*sizey     + (j-1) ]+  // left
	                               u[ i*sizey     + (j+1) ]+  // right
				       u[ (i-1)*sizey + j     ]+  // top
				       u[ (i+1)*sizey + j     ]); // bottom
	     diff = utmp[i*sizey+j] - u[i*sizey + j];
	     sum += diff * diff; 
	   }
     }
    }

    return sum;
}

/*
 * Blocked Gauss-Seidel solver: one iteration step
 */
double relax_gauss (double *u, unsigned sizex, unsigned sizey)
{
    double unew, diff, sum=0.0;
    #pragma omp parallel 
    {
		
    int howmany=omp_get_num_threads();
    int howmanyC = 32;
    #pragma omp for ordered(2) private(diff, unew) reduction(+: sum)        
    for (int blocki = 0; blocki < howmany; ++blocki) {
      for (int blockj = 0; blockj < howmanyC; ++blockj) {
		int i_start = lowerb(blocki, howmany, sizex);
		int i_end = upperb(blocki, howmany, sizex);
		int j_start = lowerb(blockj, howmanyC, sizey);
		int j_end = upperb(blockj, howmanyC, sizey);
		
		#pragma omp ordered depend(sink: blocki - 1, blockj) depend(sink: blocki, blockj - 1) 
		for (int i=max(1, i_start); i<= min(sizex-2, i_end); i++) {
			for (int j=max(1, j_start); j<= min(sizey-2, j_end); j++) {
			unew= 0.25 * ( u[ i*sizey	+ (j-1) ]+  // left
				   u[ i*sizey	+ (j+1) ]+  // right
				   u[ (i-1)*sizey	+ j     ]+  // top
				   u[ (i+1)*sizey	+ j     ]); // bottom
			diff = unew - u[i*sizey+ j];
			sum += diff * diff; 
			u[i*sizey+j]=unew;
			}
        }
        #pragma omp ordered depend(source)
      }
    }
}

    return sum;
}
