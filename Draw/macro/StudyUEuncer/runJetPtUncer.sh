#!/bin/bash
#
#####################################################################
echo ==========================================
 Jet pT uncertainy
echo run JetPtUncer 
rm result/JetPtUncer.root
for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Xi\"" \
"\"Omega\"" \

do

root -l -b -q JetPtUncer.C\(${i}\)
done

exit

