#!/bin/bash
#
for i in \
'"./AnalysisOutputs_Loop1ndRD.root"','"../../ThisAna_back/Inclusive/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_Xi_Default"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"../../ThisAna_back/Inclusive/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_Omega_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"../../ThisAna_back/Inclusive/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_Xi_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"../../ThisAna_back/Inclusive/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_Omega_Default"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../ThisAna_back/Inclusive/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Xi_Default"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../ThisAna_back/Inclusive/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Omega_Default"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
