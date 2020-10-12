#!/bin/bash
#
for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Xi\"" \

do

echo .q | sleep 2 | root -l PtSpect.C\(${i}\)
done
#
exit 0

