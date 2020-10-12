#!/bin/bash
#
for i in \
"\"Lambda_sum\"" \
"\"Xi\"" \
"\"Omega\"" \

do

echo .q | sleep 10 | root -l DoubleRatio.C\(${i}\)
done
#
exit 0

