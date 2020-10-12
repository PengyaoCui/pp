#!/bin/bash
#
for i in \
'"./AnalysisOutputs_Loop1ndRD.root"','"./Kshort/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_Kshort_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./Kshort/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_Kshort_Default"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Kshort/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_JC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Kshort/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_PCL"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Kshort/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_PCU"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Kshort/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_OC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Kshort/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_NJ"' \
'"./AnalysisOutputs_LoopIncMC.root"','"./Kshort/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Kshort_Default"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./Lambda/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_Lambda_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./Lambda/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_Lambda_Default"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Lambda/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_JC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Lambda/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_PCL"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Lambda/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_PCU"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Lambda/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_OC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Lambda/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_NJ"' \
'"./AnalysisOutputs_LoopIncMC.root"','"./Lambda/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Lambda_Default"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AntiLa/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_AntiLa_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./AntiLa/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_AntiLa_Default"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AntiLa/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_JC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AntiLa/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_PCL"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AntiLa/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_PCU"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AntiLa/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_OC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AntiLa/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_NJ"' \
'"./AnalysisOutputs_LoopIncMC.root"','"./AntiLa/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_AntiLa_Default"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./Xi/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_Xi_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./Xi/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_Xi_Default"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Xi/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_JC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Xi/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_PCL"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Xi/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_PCU"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Xi/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_OC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Xi/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_NJ"' \
'"./AnalysisOutputs_LoopIncMC.root"','"./Xi/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Xi_Default"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./Omega/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_Omega_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./Omega/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_Omega_Default"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Omega/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Omega_Default_JC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Omega/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Omega_Default_PCL"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Omega/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Omega_Default_PCU"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Omega/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Omega_Default_OC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Omega/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Omega_Default_NJ"' \
'"./AnalysisOutputs_LoopIncMC.root"','"./Omega/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Omega_Default"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
