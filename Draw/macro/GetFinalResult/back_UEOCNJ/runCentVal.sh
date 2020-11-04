#!/bin/bash
#

#####################################################################
echo ==========================================
echo run CentVal
##CentVal
rm result/CentVal.root

root -l -b -q CentVal.C

exit 0

