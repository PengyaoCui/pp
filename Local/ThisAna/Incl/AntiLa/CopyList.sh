#!/bin/bash
#
for i in \
'"./AntiLa/AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_AntiLa_Default"' \
'"./AntiLa/AnalysisOutputs_Loop2ndRD.root"','"./AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_AntiLa_Default"' \
'"./AntiLa/AnalysisOutputs_LoopIncMC.root"','"./AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_AntiLa_Default"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
