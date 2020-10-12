#!/bin/bash

cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Xi/SigExtrac/Loose
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Xi/SigExtrac/Tight
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Xi/TPCPID/Tight
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Xi/TPCPID/VTight
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Xi/Topological/Loose
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Xi/Topological/Tight
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Xi/Topological/VLoose
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Xi/Topological/VTight
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Xi/Topological/VvTight
root -l -b -q runLocalStrangeJets.C 
cd /afs/cern.ch/work/p/pcui/private/pp/Local/ThisAna_16-17_NewBins/Uncertainty/Incl/Xi/TrackQuality/Tight
root -l -b -q runLocalStrangeJets.C 
