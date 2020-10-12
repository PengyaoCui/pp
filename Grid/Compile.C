{
  gSystem->Load("libTree");
  gSystem->Load("libGeom");
  gSystem->Load("libPhysics");
  gSystem->Load("libVMC");
  gSystem->Load("libMinuit");
  gSystem->Load("libMinuit2");

  gSystem->Load("libCore");
  gSystem->Load("libXMLIO");
  gSystem->Load("libXMLParser");
  gSystem->Load("libProof");
  gSystem->Load("libProofPlayer");
  gSystem->Load("libGui");
//=============================================================================

  gSystem->Load("libSTEERBase");
  gSystem->Load("libESD");
  gSystem->Load("libAOD");
  gSystem->Load("libANALYSIS");
  gSystem->Load("libOADB");
  gSystem->Load("libANALYSISalice");
  gSystem->Load("libCORRFW");

  gSystem->Load("libPWGTools");
  gSystem->Load("libPWGHFbase");
  gSystem->Load("libPWGmuondep");
  gSystem->Load("libPWGmuon");
//=============================================================================

  gSystem->AddIncludePath("-Wno-deprecated");
  gSystem->AddIncludePath("-I$ALICE_ROOT/include");
  gSystem->AddIncludePath("-I$ALICE_PHYSICS/include");
//=============================================================================

  gROOT->LoadMacro("./AliAnalysisTaskSEPicoV0Maker.cxx++g");
  gROOT->LoadMacro("./AddTaskPicoV0Maker.C");
  gROOT->LoadMacro("./AddTaskPicoV0MakerMC.C");

  gROOT->LoadMacro("./AliAnalysisTaskSEPicoV0Filter.cxx++g");
  gROOT->LoadMacro("./AddTaskPicoV0Filter.C");

  gROOT->LoadMacro("./AliAnalysisTaskEmcalJetV0Filter.cxx++g");
  gROOT->LoadMacro("./AddTaskEmcalJetV0Filter.C");

  gROOT->LoadMacro("AddTaskEmcalJetFilter.C");

}
