#!/bin/bash

#####################################################################
echo ==========================================
echo run Final Spectra
#
rm result/pp.root

for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Lambda\","kTRUE"" \
"\"Xi\"" \
"\"Omega\"" \

do

echo .q | sleep 0 | root -l FinalSpect.C\(${i}\)
done

exit
