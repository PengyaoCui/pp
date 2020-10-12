#!/bin/bash


######################################################################
#

for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Xi\"" \
"\"Omega\"" \

do

echo .q | sleep 2 | root -l DrawUEUncer.C\(${i}\)
done
#
exit


