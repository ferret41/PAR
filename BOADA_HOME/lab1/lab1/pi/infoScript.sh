#!/bin/bash

#Script used to get the cpu information about the diferent nodes on the boada machine (Could be amplified to also obtain the same information on the interactive node easly) 

#lscpu > info-"$HOSTNAME".txt (boada1-boada4)

bash hardwareScript.sh execution
bash hardwareScript.sh cuda
bash hardwareScript.sh execution2

#lstopo
 

