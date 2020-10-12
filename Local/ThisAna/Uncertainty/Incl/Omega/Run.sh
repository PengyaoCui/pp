#!/bin/bash/

cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna/Uncertainty/Omega/CompetMass/Loose
root -l -b -q  runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna/Uncertainty/Omega/SigExtrac/Loose
root -l -b -q  runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna/Uncertainty/Omega/SigExtrac/Tight
root -l -b -q  runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna/Uncertainty/Omega/TPCPID/Tight
root -l -b -q  runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna/Uncertainty/Omega/TPCPID/Loose
root -l -b -q  runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna/Uncertainty/Omega/Topological/Loose
root -l -b -q  runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna/Uncertainty/Omega/Topological/Tight
root -l -b -q  runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna/Uncertainty/Omega/Topological/VLoose
root -l -b -q  runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna/Uncertainty/Omega/Topological/VTight
root -l -b -q  runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna/Uncertainty/Omega/Topological/VvTight
root -l -b -q  runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna/Uncertainty/Omega/TrackQuality/Tight
root -l -b -q  runLocalStrangeJets.C 
