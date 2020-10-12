#!/bin/bash
#
for i in \
"\"Omega\"" \
"\"Xi\"" \
"\"Lambda_sum\"" \

do

#root -l UnctSource.C\{${i}\)
#root -l MakeRatio.C\(${i}\)
echo .q | sleep 5 | root -l UncerRatio_MaxMin.C\(${i}\)
done
#
exit 0

