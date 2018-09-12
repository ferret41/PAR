#!/bin/csh
# following option makes sure the job will run in the current directory
#$ -cwd
# following option makes sure the job has the same environmnent variables as the submission shell
#$ -V

make $1

./$1 $2 $3 > $1_$2_$3.txt
