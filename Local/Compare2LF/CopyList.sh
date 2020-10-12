#!/bin/bash
#
for i in \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Kshort_Default"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Lambda_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./AnalysisOutputs_Loop2ndRD_back.root"','"listLoop2ndRD_Kshort_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./AnalysisOutputs_Loop2ndRD_back.root"','"listLoop2ndRD_Lambda_Default"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
