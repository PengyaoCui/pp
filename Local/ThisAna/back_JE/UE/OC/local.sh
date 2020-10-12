#!/bin/bash
#
for i in \
0,100 #0,10 10,40 40,100 
do
root -l -b -q runLocalStrangeJets.C\(${i}\)
done
#
exit 0

