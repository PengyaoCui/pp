#!/bin/bash
#
for i in \
"\"0\"","\"100\"" \
"\"0\"","\"10\"" \
"\"10\"","\"40\"" \
"\"40\"","\"100\"" \

do

#root -l UnctSource.C\{${i}\)
#root -l MakeRatio.C\(${i}\)
echo .q | sleep 2 | root -l FinalRatio.C\(${i}\)
done
#
exit 0

