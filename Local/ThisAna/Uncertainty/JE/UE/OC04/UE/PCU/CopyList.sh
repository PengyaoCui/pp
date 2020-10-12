#!/bin/bash
#
for i in \
'"./AnalysisOutputs_LoopJetRD.root"','"../PCU_back/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_PCU"' \
'"./AnalysisOutputs_LoopJetRD.root"','"../PCU_back/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Omega_Default_PCU"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
