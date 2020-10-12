#!/bin/bash
#
for i in \
'"./AnalysisOutputs_LoopJetRD.root"','"../AnalysisOutputs_LoopJetRD_X.root"','"listLoopJetRD_Xi_Default_PCL"' \
'"./AnalysisOutputs_LoopJetRD.root"','"../AnalysisOutputs_LoopJetRD_O.root"','"listLoopJetRD_Omega_Default_PCL"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
