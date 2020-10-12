#!/bin/bash


######################################################################
echo ==========================================
echo run TotUncer
#
rm result/TotUncer.root

for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Xi\"" \
"\"Omega\"" \

do

root -l -b -q TotUncer.C\(${i}\)
done
#
exit


