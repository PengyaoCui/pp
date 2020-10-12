#!/bin/bash
#
for i in \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Kshort_Default_0100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Kshort_Default_090"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Kshort_Default_010"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Kshort_Default_1040"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Kshort_Default_4090"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Kshort_Default_40100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Lambda_Default_0100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Lambda_Default_090"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Lambda_Default_010"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Lambda_Default_1040"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Lambda_Default_4090"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Lambda_Default_40100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_AntiLa_Default_0100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_AntiLa_Default_090"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_AntiLa_Default_010"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_AntiLa_Default_1040"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_AntiLa_Default_4090"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_AntiLa_Default_40100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Omega_Default_0100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Omega_Default_090"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Omega_Default_010"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Omega_Default_1040"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Omega_Default_4090"' \
'"./AnalysisOutputs_LoopIncMC.root"','"../../MLoverPforV0/Default/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Omega_Default_40100"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0



