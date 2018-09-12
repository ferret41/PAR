#!/bin/bash

#Creates all the files needed to get the different times of pi-seq on the differnet nodes of Boada

bash submit-seq.sh
qsub -l execution submit-seq.sh
qsub -l cuda submit-seq.sh
qsub -l execution2 submit-seq.sh
