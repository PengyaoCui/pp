#!/bin/bash
#

#####################################################################
echo ==========================================
##Strange reconstruct uncertainy
echo run StrangeRecUncer 
##########
rm result/StrangeRecUncer.root

for i in \
  "\"Kshort\"","\"CompetMass\"" \
  "\"Kshort\"","\"MLoverP\"" \
  "\"Kshort\"","\"SigExtrac\"" \
  "\"Kshort\"","\"Topological\"" \
  "\"Kshort\"","\"TPCPID\"" \
  "\"Kshort\"","\"TrackQuality\"" \
  "\"Lambda\"","\"SigExtrac\"" \
  "\"Lambda\"","\"MLoverP\"" \
  "\"Lambda\"","\"Topological\"" \
  "\"Lambda\"","\"TPCPID\"" \
  "\"Lambda\"","\"TrackQuality\"" \
  "\"AntiLa\"","\"SigExtrac\"" \
  "\"AntiLa\"","\"MLoverP\"" \
  "\"AntiLa\"","\"Topological\"" \
  "\"AntiLa\"","\"TPCPID\"" \
  "\"AntiLa\"","\"TrackQuality\"" \
  "\"Xi\"","\"SigExtrac\"" \
  "\"Xi\"","\"Topological\"" \
  "\"Xi\"","\"TPCPID\"" \
  "\"Xi\"","\"TrackQuality\"" \
  "\"Omega\"","\"Topological\"" \
  "\"Omega\"","\"TPCPID\"" \
  "\"Omega\"","\"SigExtrac\"" \
  "\"Omega\"","\"TrackQuality\"" \

do

  root -l -b -q StrangeRecUncer.C\(${i}\)

done

exit 0
