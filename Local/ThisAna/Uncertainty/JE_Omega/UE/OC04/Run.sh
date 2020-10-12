#!/bin/bash

cd Kshort

nohup root -l -b -q runLocalStrangeJets.C &> out&

cd ../Lambda

nohup root -l -b -q runLocalStrangeJets.C &> out&

cd ../AntiLa

nohup root -l -b -q runLocalStrangeJets.C &> out&
cd ../Xi

nohup root -l -b -q runLocalStrangeJets.C &> out&

cd ../Omega

nohup root -l -b -q runLocalStrangeJets.C &> out&
