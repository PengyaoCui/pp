#!/bin/bash
#
for i in \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Kshort_Default_JC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Lambda_Default_JC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_AntiLa_Default_JC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Xi_Default_JC"' \
                                     
do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
