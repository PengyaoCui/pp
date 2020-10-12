#!/bin/bash
#
for i in \
'"./AnalysisOutputs_Loop1ndRD.root"','"./back/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_XiNeg_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./back/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_XiNeg_Default"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./back/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_XiPos_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./back/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_XiPos_Default"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./back/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_OmegaNeg_Default"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./back/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_OmegaNeg_Default"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
