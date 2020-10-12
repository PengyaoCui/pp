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

  gROOT->LoadMacro("../CascadeBase/AliCascadeBase.cxx+g");
  gROOT->LoadMacro("../CascadeBase/AliCascadeRD.cxx+g");
  gROOT->LoadMacro("../CascadeBase/AliCascadeMC.cxx+g");
  gROOT->LoadMacro("AliAnalysisTaskUserJetCascades.cxx+g");
}
