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

echo .q | sleep 0 | root -l UEUncer_withOCandNJ.C\(${i}\)
echo .q | sleep 0 | root -l UEUncer_NonSub.C\(${i}\)
echo .q | sleep 0 | root -l UEUncer_wOC.C\(${i}\)

done

exit
