#!/bin/bash
#


######################################################################
echo ==========================================
echo run particle ratio uncertainty 


echo .q | sleep 0 | root -l LKRatioUncer.C
echo .q | sleep 0 | root -l XKRatioUncer.C
echo .q | sleep 0 | root -l OKRatioUncer.C
echo .q | sleep 0 | root -l XLRatioUncer.C
echo .q | sleep 0 | root -l OLRatioUncer.C
echo .q | sleep 0 | root -l OXRatioUncer.C

exit 0

