#!/bin/bash
#
for i in \
'"./Kshort/AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_Kshort_Default"' \
'"./Kshort/AnalysisOutputs_Loop2ndRD.root"','"./AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_Kshort_Default"' \
'"./Kshort/AnalysisOutputs_LoopIncMC.root"','"./AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Kshort_Default"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
