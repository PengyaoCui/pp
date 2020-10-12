#!/bin/bash
#
for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Lambda\"",""kTRUE"" \
"\"Xi\"" \
"\"Omega\"" \

do

#root -l UnctSource.C\{${i}\)
#root -l MakeRatio.C\(${i}\)
echo .q | sleep 2 | root -l FinalSpect.C\(${i}\)
done
#
exit 0

