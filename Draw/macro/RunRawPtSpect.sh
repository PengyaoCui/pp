#!/bin/bash
#
for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Xi\"" \
"\"Omega\"" \

do

echo .q | sleep 2 | root -l RawPtSpect.C\(${i}\)
done
#
exit 0

