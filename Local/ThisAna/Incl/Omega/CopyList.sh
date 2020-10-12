#!/bin/bash
#
for i in \
'"./AnalysisOutputs_Loop1ndRD.root"','"../../../PaperProposal_Local/ThisAna/Inclusive/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_Kshort_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"../../../PaperProposal_Local/ThisAna/Inclusive/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_Kshort_Default"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../../PaperProposal_Local/ThisAna/Inclusive/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Kshort_Default"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"../../../PaperProposal_Local/ThisAna/Inclusive/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_Lambda_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"../../../PaperProposal_Local/ThisAna/Inclusive/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_Lambda_Default"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../../PaperProposal_Local/ThisAna/Inclusive/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Lambda_Default"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"../../../PaperProposal_Local/ThisAna/Inclusive/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_AntiLa_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"../../../PaperProposal_Local/ThisAna/Inclusive/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_AntiLa_Default"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../../PaperProposal_Local/ThisAna/Inclusive/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_AntiLa_Default"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"../../../PaperProposal_Local/ThisAna/Inclusive/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_Xi_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"../../../PaperProposal_Local/ThisAna/Inclusive/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_Xi_Default"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../../PaperProposal_Local/ThisAna/Inclusive/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Xi_Default"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
