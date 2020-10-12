#!/bin/bash
#

rm ./result/JetPtUncertainty.root
for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Xi\"" \
"\"Omega\"" \

do

#root -l UnctSource.C\{${i}\)
#root -l MakeRatio.C\(${i}\)
echo .q | sleep 2 | root -l UncerJet.C\(${i}\)
done
#
exit 0

