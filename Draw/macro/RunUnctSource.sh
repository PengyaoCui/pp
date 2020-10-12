#!/bin/bash
#
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

echo .q | sleep 5 | root -l UnctSource.C\(${i}\)
done
#
exit 0
