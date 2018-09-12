#!/bin/bash

#HOST=$(echo $HOSTNAME | cut -f 1 -d'.')

USAGE="\n USAGE: hardwareScript.sh queueName\n
    	queueName  = Name of the queue to submit the script to\n"

if (test $# -lt 1 || test $# -gt 1)
then
	echo -e $USAGE
        exit 0
fi

qsub -l $1 lscpu.sh 
qsub -l $1 lstopo.sh 



