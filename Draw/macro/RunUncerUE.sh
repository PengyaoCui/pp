#!/bin/bash
#
rm result/UEUncertainty.root 
for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Xi\"" \
"\"Omega\"" \

do

#root -l UnctSource.C\{${i}\)
#root -l MakeRatio.C\(${i}\)
echo .q | sleep 2 | root -l UncerUE.C\(${i}\)
done
#
exit 0

