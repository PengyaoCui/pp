#!/bin/bash
#

#####################################################################
echo ==========================================
echo run InclUncer 
## Inclusive uncertainy
##########
rm result/InclUncer.root
for i in \
"\"Kshort\"" \
"\"Lambda\"" \
"\"AntiLa\"" \
"\"Xi\"" \
"\"Omega\"" \

do

##echo .q | sleep 2 | root -l InclUncer.C\(${i}\)
root -l -b -q InclUncer.C\(${i}\)
done

exit
