#!/bin/bash
#
for i in \
'"./AnalysisOutputs_LoopJetRD.root"','"~/study/pp/Local/ThisAna/JE/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_JC"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
