#!/bin/bash/

cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Omega/CompetMass/Loose
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Omega/SigExtrac/Loose
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Omega/SigExtrac/Tight
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Omega/TPCPID/Tight
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Omega/TPCPID/VTight
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Omega/Topological/Loose
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Omega/Topological/Tight
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Omega/Topological/VLoose
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Omega/Topological/VTight
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Omega/Topological/VvTight
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Omega/TrackQuality/Tight
root -l -b -q runLocalStrangeJets.C 
