#!/bin/bash
#
for i in \
'"./AnalysisOutputs_LoopJetRD.root"','"./PCL/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_PCL"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./PCU/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_PCU"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./OC/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_OC"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./NJ/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_NJ"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
