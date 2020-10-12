#!/bin/bash
#

###########################################################
rm result/PtSpect_ThisAna.root
for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Xi\"" \
"\"Omega\"" \

do

echo .q | sleep 2 | root -l InclPtSpect.C\(${i}\)
done
#################

for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Xi\"" \

do

echo .q | sleep 2 | root -l JEPtSpect.C\(${i}\)
done
#################

for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Xi\"" \
"\"Omega\"" \

do

echo .q | sleep 2 | root -l JEOmegaBin.C\(${i}\)
done

#################



#
###########################################################
exit 0

