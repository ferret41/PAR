.SUFFIXES: -omp -debug
CC       = gcc

OPENMP	 = -fopenmp 
CFLAGS   = -Wall -std=c99 -O3 $(OPENMP) -fno-inline -I.  
CLIBS    = -L. -lm

.c-debug:
	$(CC) -D_DEBUG_ $< $(CFLAGS) -o $@ $(CLIBS) 

.c-omp:
	$(CC) $< $(CFLAGS) -o $@ $(CLIBS) 

clean:
	rm -f *-omp *-debug

ultraclean:
	rm -rf *.prv *.row *.pcf submit-extrae.sh.o* submit-extrae.sh.e* submit-omp.sh.o* submit-omp.sh.e*
