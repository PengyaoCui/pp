#!/bin/bash
#
for i in \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/PCL/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_PCL"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/PCL/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_PCL"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/PCL/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_PCL"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/PCU/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_PCU"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/PCU/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_PCU"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/PCU/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_PCU"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/PCU/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_PCU"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/PCU/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Omega_Default_PCU"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/OC/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_OC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/OC/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_OC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/OC/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_OC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/OC/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_OC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/OC/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Omega_Default_OC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/NJ/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_NJ"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/NJ/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_NJ"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/NJ/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_NJ"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/NJ/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_NJ"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./UE/NJ/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Omega_Default_NJ"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
