#!/bin/bash


######################################################################
echo ==========================================
echo run UEUncer

rm result/UEUncer.root
for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Xi\"" \
"\"Omega\"" \

do

echo .q | sleep 0 | root -l UEUncer.C\(${i}\)
done

exit
