#!/bin/bash

cp ./Kshort/AnalysisOutputs_Loop1ndRD.root ./merged/AnalysisOutputs_Loop1ndRD_K.root
cp ./Kshort/AnalysisOutputs_Loop2ndRD.root ./merged/AnalysisOutputs_Loop2ndRD_K.root

cp ./Lambda/AnalysisOutputs_Loop1ndRD.root ./merged/AnalysisOutputs_Loop1ndRD_L.root
cp ./Lambda/AnalysisOutputs_Loop2ndRD.root ./merged/AnalysisOutputs_Loop2ndRD_L.root

cp ./AntiLa/AnalysisOutputs_Loop1ndRD.root ./merged/AnalysisOutputs_Loop1ndRD_A.root
cp ./AntiLa/AnalysisOutputs_Loop2ndRD.root ./merged/AnalysisOutputs_Loop2ndRD_A.root

cp ./Xi/AnalysisOutputs_Loop1ndRD.root ./merged/AnalysisOutputs_Loop1ndRD_X.root
cp ./Xi/AnalysisOutputs_Loop2ndRD.root ./merged/AnalysisOutputs_Loop2ndRD_X.root

cp ./Omega/AnalysisOutputs_Loop1ndRD.root ./merged/AnalysisOutputs_Loop1ndRD_O.root
cp ./Omega/AnalysisOutputs_Loop2ndRD.root ./merged/AnalysisOutputs_Loop2ndRD_O.root

hadd ./AnalysisOutputs_Loop1ndRD.root ./merged/AnalysisOutputs_Loop1ndRD_*.root
hadd ./AnalysisOutputs_Loop2ndRD.root ./merged/AnalysisOutputs_Loop2ndRD_*.root
