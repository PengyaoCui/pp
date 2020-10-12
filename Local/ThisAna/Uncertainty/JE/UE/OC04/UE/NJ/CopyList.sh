#!/bin/bash
#
for i in \
'"./AnalysisOutputs_LoopJetRD.root"','"../OC_back/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_OC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"../OC_back/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Omega_Default_OC"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
