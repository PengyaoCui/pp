const auto useGrid(kFALSE);  // local or grid
const char* gridMode = "full";  // set the grid run mode (can be "full", "test", "offline", "submit" or "terminate")
const char* uniqueName = "LHC16l";//

const auto isMC(kTRUE);   // trigger, if MC handler should be used
//const char* pattern = "/AOD/*AOD.root";  //MC
//const char* gridDir = "/alice/sim/2017/LHC17j5b/";  //MC
const char* pattern = "/pass1/AOD208/*AOD.root"; //RD
const char* gridDir = "/alice/data/2018/LHC18b"; //RD

const char* runNumbers = "285365"; 

const char* dataType = "AOD";   // set the analysis type, AOD, ESD or sESD
UInt_t numLocalFiles = 50;  // number of files analyzed locally  
const char* addCXXs = "AliPicoBaseDev.cxx  AliPicoCascade.cxx  AliPicoCascadeMC.cxx  AliPicoCascadeRD.cxx AliAnalysisTaskSEStrangeMaker.cxx AliAnalysisTaskEmcalJetStrangeFilter.cxx";
const char* addHs   = "AliPicoBaseDev.h    AliPicoCascade.h    AliPicoCascadeMC.h    AliPicoCascadeRD.h    AliAnalysisTaskSEStrangeMaker.h   AliAnalysisTaskEmcalJetStrangeFilter.h";
Int_t maxFilesPerWorker = 10;
Int_t workerTTL = 30000;

const Bool_t bUseVtxAOD = kFALSE;
const char *AliPhysics = "vAN-20190201_ROOT6-1";
//=============================================================================

//===> Input Data Type
const Bool_t bIsInfoAOD = kTRUE;
//===>AOD input not need physical selection
const Bool_t bIsPhysSel = kTRUE;
//===>pp Off Pb-Pb Pb-p/p-Pb On
const Bool_t bIsCentSel = kFALSE;
const Bool_t bIsEvPnSel = kFALSE;
const Bool_t bIsRespPID = kTRUE;

const Bool_t bAnaJetRD = kTRUE;
//===> 
const auto wTriggerMask(AliVEvent::kINT7);
//=============================================================================

const TString sCentEsti = "V0A";  // "V0M"; "V0A"; "V0C"
const Double_t dCentMin =   0.;
const Double_t dCentMax = 100.;
//=============================================================================
const Double_t dTrkPtCut = 0.15;
const Double_t dCluEnCut = 0.;

const Double_t dJetRadius = 0.4;

const Bool_t bFullJet = kFALSE;

const TString  sAnaType    = "TPCFID";  // "TPC"; "EMCAL"; "USER" Eta
const Double_t dJetPtCut   = 0.;
const Double_t dJetAreaCut = 0.0;
const Double_t ghostArea   = 0.005;
//=============================================================================

const TString sUsedRhoRD = "";  // "RhoRD"
const TString sUsedRhoMC = "";// "RhoMC"
//=============================================================================

#include "AliPicoBaseDev.cxx++g"
#include "AliPicoCascade.cxx++g"
#include "AliPicoCascadeRD.cxx++g"
#include "AliPicoCascadeMC.cxx++g"
#include "AliAnalysisTaskSEStrangeMaker.cxx++g"
#include "AliAnalysisTaskEmcalJetStrangeFilter.cxx++g"

class AliAnalysisGrid;//load class
class AliAnalysisManager;
class AliAnalysisAlien;
//=============================================================================

Bool_t LoadLibraries();

AliAnalysisGrid* CreateAlienHandler( const char* uniqueName, const char* gridDir, const char* gridMode, const char* runNumbers, const char* pattern, TString additionalCode, TString additionalHeaders, Int_t maxFilesPerWorker, Int_t workerTTL, Bool_t isMC);
//=============================================================================

void runAnalysisEmcalJetStrange()
{
  const TString sPeriodIn = isMC ? "LHC15g3c3" : "LHC16l";

  if (LoadLibraries()) {
    ::Error("AnalysisTrainEmcalJetCascadeAlien.C::AnalysisTrainEmcalJetCascadeAlien","Load libraries failed!");
    return;
  }

  TString additionalCXXs(addCXXs);
  TString additionalHs(addHs);

  TString usedData(dataType); 
  TString localFiles("-1");

  AliAnalysisManager *mgr = new AliAnalysisManager("runAnalysisEmcalJetStrange", "Analysis Train EMCal Jet Cascade Alien");

//============================================================================================
  if(usedData == "AOD")
  {
    if(!isMC) localFiles = "files_aod.txt";
    else  localFiles = "files_aod_mc.txt";
  }
  else if((usedData == "ESD") || (usedData == "sESD"))
  {
    if (usedData == "ESD")
      localFiles = "files_esd.txt";
    else
      localFiles = "files_sesd.txt";
  }
  else
  {
    cout << "Data type not recognized! You have to specify ESD, AOD, or sESD!\n";
  }

  if(!useGrid)   cout << "Using " << localFiles.Data() << " as input file list.\n";
//=================================================================================================

  TString sRunPeriod(sPeriodIn);
  sRunPeriod.ToLower();

  //if (bIsInfoAOD) {
  //  TMacro addAODHandler(gSystem->ExpandPathName("$ALICE_ROOT/ANALYSIS/macros/train/AddAODHandler.C"));
  //  auto aodIH(reinterpret_cast<AliAODInputHandler*>(addAODHandler.Exec()));
  //}
  //else{
  //  TMacro addESDHandler(gSystem->ExpandPathName("$ALICE_ROOT/ANALYSIS/macros/train/AddESDHandler.C"));
  //  auto esdIH(reinterpret_cast<AliESDInputHandler*>(addESDHandler.Exec()));
  //}
  if(bIsInfoAOD){
    auto aodIH(AliAnalysisTaskEmcal::AddAODHandler());
  }else{
    auto esdIH(AliAnalysisTaskEmcal::AddESDHandler());
  }

  if (isMC && (!bIsInfoAOD)) {
    TMacro addMCHandler(gSystem->ExpandPathName("$ALICE_ROOT/ANALYSIS/macros/train/AddMCHandler.C"));
    auto mctEH(reinterpret_cast<AliMCEventHandler*>(addMCHandler.Exec("kTRUE")));
  }

  TMacro addAODOutputHandler(gSystem->ExpandPathName("$ALICE_ROOT/ANALYSIS/macros/train/AddAODOutputHandler.C"));
  auto aodOH(reinterpret_cast<AliAODHandler*>(addAODOutputHandler.Exec()));
  aodOH->SetOutputFileName("AliAOD.StrangeParJets.root");
  aodOH->SetFillAOD(kTRUE);
  aodOH->SetCreateNonStandardAOD();
  mgr->SetOutputEventHandler(aodOH);

  ((AliInputEventHandler*)mgr->GetInputEventHandler())->SetNeedField(1);
//=============================================================================

  // RUN II
  if (bIsPhysSel) {
    const TString sPhysSel(Form("%s, kTRUE",isMC ? "kTRUE" : "kFALSE"));
    TMacro addPhysSel(gSystem->ExpandPathName("$ALICE_PHYSICS/OADB/macros/AddTaskPhysicsSelection.C"));
    AliPhysicsSelectionTask *taskPhysSel = reinterpret_cast<AliPhysicsSelectionTask *>(addPhysSel.Exec(sPhysSel.Data()));
  }

  if (bIsCentSel) {
    TMacro addMultSel(gSystem->ExpandPathName("$ALICE_PHYSICS/OADB/COMMON/MULTIPLICITY/macros/AddTaskMultSelection.C"));
    AliMultSelectionTask * taskCentSel = reinterpret_cast<AliMultSelectionTask*>(addMultSel.Exec("kFALSE"));
    taskCentSel->SetSelectedTriggerClass(wTriggerMask);

    if (!isMC){
      taskCentSel->SetUseDefaultCalib(kTRUE);
      taskCentSel->SetAlternateOADBforEstimators(sPeriodIn);//(Form("myOwnOADBfor%d",sPeriodIn.Data()));
    }else{
      taskCentSel->SetUseDefaultMCCalib(kTRUE);
      taskCentSel->SetAlternateOADBforEstimators("LHC16l");//(Form("myOwnOADBfor%d",sPeriodIn.Data()));
    }
  }

  if (bIsEvPnSel) {
    TMacro addEP(gSystem->ExpandPathName("$ALICE_ROOT/ANALYSIS/macros/AddTaskEventplane.C"));
    AliEPSelectionTask *taskEventPlane = reinterpret_cast<AliEPSelectionTask*>(addEP.Exec());
    if (isMC) taskEventPlane->SetUseMCRP();
  }

  if (bIsRespPID) {
    const TString sPIDResp(Form("%s,kTRUE, kTRUE, 2, kFALSE, \"  \", kTRUE, kFALSE", isMC ? "kTRUE" : "kFALSE"));
    TMacro addPIDResp(gSystem->ExpandPathName("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C"));
    AliAnalysisTaskSE *taskRespPID = reinterpret_cast<AliAnalysisTaskSE*>(addPIDResp.Exec(sPIDResp.Data()));
  }
//=============================================================================

  AliTrackContainer::SetDefTrackCutsPeriod(sPeriodIn);
//=============================================================================
  TMacro addEmcalJet(gSystem->ExpandPathName("$ALICE_PHYSICS/PWGJE/EMCALJetTasks/macros/AddTaskEmcalJet.C"));
  TMacro addRhoSparse(gSystem->ExpandPathName("$ALICE_PHYSICS/PWGJE/EMCALJetTasks/macros/AddTaskRhoSparse.C"));
  //TMacro addRhoNew(gSystem->LoadMacro("$ALICE_PHYSICS/PWGJE/EMCALJetTasks/macros/AddTaskRhoNew.C"));

  TString kTpcAktJets ="";
  if (bAnaJetRD) {
    const TString sEmcalJetAkt(Form("\"usedefault\", \"%s\", AliJetContainer::antikt_algorithm, %f, %s, %f, %f, %f, AliJetContainer::pt_scheme, \"Jet\", %f, kFALSE, kFALSE", bFullJet ? "usedefault" : "", dJetRadius, bFullJet ? "AliJetContainer::kFullJet" : "AliJetContainer::kChargedJet", dTrkPtCut, dCluEnCut, ghostArea, dJetPtCut));
    auto taskAktRD(reinterpret_cast<AliEmcalJetTask*>(addEmcalJet.Exec(sEmcalJetAkt.Data())));

    kTpcAktJets = taskAktRD->GetName();
    taskAktRD->SelectCollisionCandidates(wTriggerMask);

    if (!sUsedRhoRD.IsNull()) {
      const TString sEmcalJetKt(Form("\"usedefault\", \"%s\", AliJetContainer::kt_algorithm, %f, %s, %f, %f, %f, AliJetContainer::pt_scheme, \"Jet\", %f, kFALSE, kFALSE", bFullJet ? "usedefault" : "", dJetRadius, bFullJet ? "AliJetContainer::kFullJet" : "AliJetContainer::kChargedJet", dTrkPtCut, dCluEnCut, ghostArea, dJetPtCut));
      auto taskKtRD(reinterpret_cast<AliEmcalJetTask*>(addEmcalJet.Exec(sEmcalJetKt.Data())));

      taskKtRD->SetMinJetPt(0.);
      taskKtRD->SelectCollisionCandidates(wTriggerMask);
      TString kTpcKtJets = taskKtRD->GetName();

      const TString sRhoSparse(Form("\"usedefault\", \"%s\", \"%s\", %f, AliEmcalJet::kTPCfid, AliJetContainer::kChargedJet, AliJetContainer::pt_scheme, kTRUE, \"%s\", \"%s\", %f, %f, 0., \" \"", bFullJet ? "usedefault" : "", sUsedRhoRD.Data(), dJetRadius, kTpcKtJets.Data(), sAnaType.Data(), dJetPtCut, dJetAreaCut));
      auto taskRhoRD(reinterpret_cast<AliAnalysisTaskRhoSparse*>(addRhoSparse.Exec(sRhoSparse.Data())));
      taskRhoRD->SetUseNewCentralityEstimation(kTRUE);
      taskRhoRD->SetNCentBins(4);

      TMacro addDeltaPt(gSystem->ExpandPathName("$ALICE_PHYSICS/PWGJE/EMCALJetTasks/macros/AddTaskDeltaPt.C"));
      const TString sDeltaPt(Form("\"tracks\", \"\", \"%s\", \"\", \"\", \"\", \"tracks\", \"\", \"%s\", %f, 0., %f, 0., \"TPC\", \"AliAnalysisTaskDeltaPt\"", kTpcAktJets.Data(), sUsedRhoRD.Data(), dJetRadius, dTrkPtCut, dCluEnCut));
      auto taskDeltaPt(reinterpret_cast<AliAnalysisTaskDeltaPt*>(addDeltaPt.Exec(sDeltaPt.Data())));
      taskDeltaPt->SelectCollisionCandidates(wTriggerMask);
      taskDeltaPt->SetForceBeamType(AliAnalysisTaskEmcal::kpp);
      taskDeltaPt->SetNeedEmcalGeom(kFALSE);
      //taskDeltaPt->SetMinNVertCont(1);
      taskDeltaPt->SetZvertexDiffValue(0.5);
      taskDeltaPt->SetRCperEvent(100);
      taskDeltaPt->SetJetMinRC2LJ(1.2);
      taskDeltaPt->SetConeRadius(0.4);
      //taskDeltaPt->SetCentralityEstimation(1);
      //taskDeltaPt->SetCentBins(bins);
    }
  }
//=============================================================================

  TString kTpcAktJetsMC ="";
  if (isMC) {
    const TString sEmcalJetMCAkt(Form("\"mcparticles\", \"%s\", AliJetContainer::antikt_algorithm, %f, %s, %f, %f, %f, AliJetContainer::pt_scheme, \"Jet\", 0., kFALSE, kFALSE", bFullJet ? "usedefault" : "", dJetRadius, bFullJet ? "AliJetContainer::kFullJet" : "AliJetContainer::kChargedJet", dTrkPtCut, dCluEnCut, ghostArea, dJetPtCut));
    auto taskAktMC(reinterpret_cast<AliEmcalJetTask*>(addEmcalJet.Exec(sEmcalJetMCAkt.Data())));

    kTpcAktJetsMC = taskAktMC->GetName();
    taskAktMC->SelectCollisionCandidates(wTriggerMask);

    if (!sUsedRhoMC.IsNull()) {
      const TString sEmcalJetMCKt(Form("\"mcparticles\", \"%s\", AliJetContainer::kt_algorithm, %f, %s, %f, %f, %f, AliJetContainer::pt_scheme, \"Jet\", 0., kFALSE, kFALSE", bFullJet ? "usedefault" : "", dJetRadius, bFullJet ? "AliJetContainer::kFullJet" : "AliJetContainer::kChargedJet", dTrkPtCut, dCluEnCut, ghostArea, dJetPtCut));
      auto taskKtMC(reinterpret_cast<AliEmcalJetTask*>(addEmcalJet.Exec(sEmcalJetMCKt.Data())));

      TString kTpcKtJetsMC = taskKtMC->GetName();
      taskKtMC->SelectCollisionCandidates(wTriggerMask);

      const TString sRhoSparseMC(Form("\"mcparticles\", \"%s\", \"%s\", %f, AliEmcalJet::kTPCfid, AliJetContainer::kChargedJet, AliJetContainer::pt_scheme, kTRUE, \"%s\", \"%s\", %f, %f, 0., \" \"", bFullJet ? "usedefault" : "", sUsedRhoMC.Data(), dJetRadius, kTpcKtJetsMC.Data(), sAnaType.Data(), dJetPtCut, dJetAreaCut));
      auto taskRhoMC(reinterpret_cast<AliAnalysisTaskRhoSparse*>(addRhoSparse.Exec(sRhoSparseMC.Data())));

      taskRhoMC->SetUseNewCentralityEstimation(kTRUE);
      taskRhoMC->SetNCentBins(4);
    }
  }
//=============================================================================

  const TString sStrangeMaker(Form("%s", isMC ? "kTRUE" : "kFALSE"));
  TMacro addStrangeMaker(gSystem->ExpandPathName("./AddTaskStrangeMaker.C"));
  auto taskStrangeMaker(reinterpret_cast<AliAnalysisTaskSEStrangeMaker*>(addStrangeMaker.Exec(sStrangeMaker.Data())));

  taskStrangeMaker->SetCollitionType(AliPicoBaseDev::kPP);
  taskStrangeMaker->SetTriggerMask(wTriggerMask);
  //taskStrangeMaker->AddMultEstimator(sCentEsti.Data());
  //taskStrangeMaker->SetMultRange(0., 100., sCentEsti.Data());
  //taskStrangeMaker->SetSkipFastOnly(kFALSE);
  //taskStrangeMaker->SetUseAnaUtils(kTRUE);
//=============================================================================

  const TString sJetStrangeFilter(Form("\"usedefault\", \"%s\" , \"%s\" ",  bFullJet ? "usedefault" : "", bFullJet ? "usedefault" : ""));
  TMacro addJetStrangeFilter(gSystem->ExpandPathName("./AddTaskEmcalJetStrangeFilter.C"));
  auto taskJetStrangeFilter(reinterpret_cast<AliAnalysisTaskEmcalJetStrangeFilter *>(addJetStrangeFilter.Exec(sJetStrangeFilter.Data())));

  taskJetStrangeFilter->SetHistoBins(600, 0., 300.);
  taskJetStrangeFilter->AddMultEsti(sCentEsti.Data());
  taskJetStrangeFilter->SetCascade("PicoCascade", isMC);
  taskJetStrangeFilter->SetPicoV0("PicoV0s", isMC);
  AliJetContainer *cJet = nullptr;
  AliParticleContainer *cPar = nullptr;
  AliClusterContainer *clus = nullptr;
  //taskJetStrangeFilter->SetForceBeamType(2);//0:pp,  1:AA; 2:pA

  cPar = taskJetStrangeFilter->GetParticleContainer();
  clus = taskJetStrangeFilter->GetClusterContainer();
  if(isMC){
    cJet = taskJetStrangeFilter->AddJetContainer(kTpcAktJetsMC.Data(), sAnaType.Data(), dJetRadius);
  }else{
    cJet = taskJetStrangeFilter->AddJetContainer(kTpcAktJets.Data(), sAnaType.Data(), dJetRadius);
  }

//=============================================================================

  if (cPar) {
    cPar->SetParticlePtCut(dTrkPtCut);
  }

  if (clus) {
    clus->SetClusECut(0.);
    clus->SetClusPtCut(0.);
    clus->SetClusNonLinCorrEnergyCut(0.);
    clus->SetClusHadCorrEnergyCut(0.3);
    clus->SetDefaultClusterEnergy(AliVCluster::kHadCorr);
  }

  if (cJet) {
    //cJet->SetPercAreaCut(0.6);  //fJetAreaCut = p*TMath::Pi()*fJetRadius*fJetRadius;
    cJet->SetPercAreaCut(0.);
    cJet->ConnectParticleContainer(cPar);
    cJet->ConnectClusterContainer(clus);

    if (!sUsedRhoRD.IsNull()) {
      cJet->SetRhoName(sUsedRhoRD.Data());
    }
  }

  TIter next(mgr->GetTasks());
  AliAnalysisTaskSE *taskSE(0x0);
  while ((taskSE = dynamic_cast<AliAnalysisTaskSE*>(next()))) {
    if (wTriggerMask) if (!(taskSE->InheritsFrom("AliPhysicsSelectionTask"))) {
      taskSE->SelectCollisionCandidates(wTriggerMask);
    }

    if (taskSE->InheritsFrom("AliAnalysisTaskEmcal")) {
      AliAnalysisTaskEmcal *taskEmcal = static_cast<AliAnalysisTaskEmcal*>(taskSE);
      taskEmcal->SetForceBeamType(AliAnalysisTaskEmcal::kpp);
      taskEmcal->SetUseBuiltinEventSelection(kFALSE);
      //taskEmcal->SetUseAliAnaUtils(kTRUE);
      //taskEmcal->SetMinVertexContrib(2);
      //taskEmcal->SetUseSPDTrackletVsClusterBG(kTRUE);
      //taskEmcal->SetVzRange(-10., 10.);
      //taskEmcal->SetZvertexDiffValue(0.5);
      if (bIsCentSel){
        taskEmcal->SetUseNewCentralityEstimation(kTRUE);
        taskEmcal->SetNCentBins(4);
        taskEmcal->SetCentRange(dCentMin, dCentMax);
        taskEmcal->SetCentralityEstimator(sCentEsti.Data());
      }
    }
  }

//=================================================================================================
  if (!mgr->InitAnalysis())    return;
  mgr->PrintStatus();
  if (useGrid){
    if (!TGrid::Connect("alien://")) {
      ::Error("runAnalysisEmcalJetStrange.C::runAnalysisEmcalJetStrange","Can not connect to the Grid!");
      return;
    }
    //cout<<uniqueName<<endl;
    AliAnalysisGrid *alienHandler = CreateAlienHandler(uniqueName, gridDir, gridMode, runNumbers, pattern, additionalCXXs, additionalHs, maxFilesPerWorker, workerTTL, isMC);
    if (!alienHandler) {
      ::Error("runAnalysisEmcalJetStrange::runAnalysisEmcalJetStrange","no Grid handler is found!");
      return;
    }
    mgr->SetGridHandler(alienHandler);
    mgr->StartAnalysis("grid");
    return;
  }else{
     TChain* chain = 0;
     const TString sChain(Form("\"%s\", %d", localFiles.Data(), numLocalFiles));
     if (usedData == "AOD")
     {
       TMacro addAODChain(gSystem->ExpandPathName("$ALICE_PHYSICS/PWG/EMCAL/macros/CreateAODChain.C"));
       chain = reinterpret_cast<TChain *>(addAODChain.Exec(sChain.Data()));
     }
     else
     {  // ESD or skimmed ESD
       TMacro addESDChain(gSystem->ExpandPathName("$ALICE_PHYSICS/PWG/EMCAL/macros/CreateESDChain.C"));
       chain = reinterpret_cast<TChain *>(addESDChain.Exec(sChain.Data()));
     }
     //cout << "Starting LOCAL Analysis...";
     //mgr->SetDebugLevel(0);
     mgr->StartAnalysis("local", chain);
  }

}

//_____________________________________________________________________________

AliAnalysisGrid* CreateAlienHandler(const char* uniqueName, const char* gridDir, const char* gridMode, const char* runNumbers, const char* pattern, TString additionalCode, TString additionalHeaders, Int_t maxFilesPerWorker, Int_t workerTTL, Bool_t isMC)
{
  TString tmpAdditionalLibs("");
 tmpAdditionalLibs = Form("libMinuit2.so libCore.so libXMLIO.so libXMLParser.so libProof.so libProofPlayer.so libGui.so libPWGTools.so libPWGflowBase.so libPWGflowTasks.so libPWGHFbase.so libPWGHFvertexingHF.so libSTAT.so libEMCALUtils.so libCDB.so libRAWDatabase.so libRAWDatarec.so libITSbase.so libITSrec.so libTPCbase.so libTPCrec.so libTRDbase.so libTRDrec.so libTOFbase.so libHMPIDbase.so libEMCALraw.so libEMCALbase.so libEMCALrec.so libVZERObase.so libVZEROrec.so libTender.so libTenderSupplies.so  libCGAL.so libfastjet.so libsiscone.so libsiscone_spherical.so libfastjetplugins.so libfastjettools.so libfastjetcontribfragile.so libJETAN.so libFASTJETAN.so libPWGEMCAL.so libPWGJEEMCALJetTasks.so %s %s",additionalCode.Data(),additionalHeaders.Data());

  TDatime currentTime;
  TString tmpName(uniqueName);

  TString macroName("");
  TString execName("");
  TString jdlName("");
  macroName = Form("%s.C", tmpName.Data());
  execName = Form("%s.sh", tmpName.Data());
  jdlName = Form("%s.jdl", tmpName.Data());

  AliAnalysisAlien *plugin = new AliAnalysisAlien();
  plugin->SetOverwriteMode();
  plugin->SetRunMode(gridMode);
  plugin->SetAliPhysicsVersion(AliPhysics);
  
  plugin->SetGridDataDir(gridDir); // e.g. "/alice/sim/LHC10a6"
  plugin->SetDataPattern(pattern); //dir structure in run directory

  if (bUseVtxAOD) plugin->SetFriendChainName("AliAOD.VertexingHF.root");
  if (!isMC)
  plugin->SetRunPrefix("000");//real data

  plugin->AddRunList(runNumbers);

  plugin->SetGridWorkingDir(Form("work/%s",tmpName.Data()));
  plugin->SetGridOutputDir("output"); // In this case will be $HOME/work/output
  plugin->SetOutputToRunNo(kTRUE); //Use run number as output directory
  plugin->SetAnalysisSource(additionalCode.Data());
  plugin->SetAdditionalLibs(tmpAdditionalLibs.Data());

  plugin->SetDefaultOutputs(kTRUE);
  plugin->SetAnalysisMacro(macroName.Data());
  plugin->SetSplitMaxInputFileNumber(maxFilesPerWorker);
  plugin->SetExecutable(execName.Data());
  plugin->SetTTL(workerTTL);
  plugin->SetInputFormat("xml-single");
  plugin->SetJDLName(jdlName.Data());
  plugin->SetPrice(1);
  plugin->SetSplitMode("se");

//=============================================================================
  TString sIncPath = "-Wno-deprecated";
  sIncPath += " -I$ALICE_ROOT/include";
  sIncPath += " -I$ALICE_PHYSICS/include";
  sIncPath += " -I$ALICE_PHYSICS/PWGHF/vertexingHF";
  sIncPath += " -I$ALICE_PHYSICS/EMCAL";
  sIncPath += " -I$ALICE_PHYSICS/JETAN";
  sIncPath += " -I$ALICE_PHYSICS/JETAN/fastjet";
  plugin->AddIncludePath(sIncPath.Data());
//=============================================================================

  return plugin;
}

//_____________________________________________________________________________
Bool_t LoadLibraries()
{

  if (gSystem->Load("libTree")       <0) return kTRUE;
  if (gSystem->Load("libGeom")       <0) return kTRUE;
  if (gSystem->Load("libPhysics")    <0) return kTRUE;
  if (gSystem->Load("libVMC")        <0) return kTRUE;
  if (gSystem->Load("libMinuit")     <0) return kTRUE;
  if (gSystem->Load("libMinuit2")    <0) return kTRUE;
  if (gSystem->Load("libCore")       <0) return kTRUE;
  if (gSystem->Load("libXMLIO")      <0) return kTRUE;
  if (gSystem->Load("libXMLParser")  <0) return kTRUE;
  if (gSystem->Load("libProof")      <0) return kTRUE;
  if (gSystem->Load("libProofPlayer")<0) return kTRUE;
  if (gSystem->Load("libGui")        <0) return kTRUE;
//=============================================================================

  if (gSystem->Load("libSTEERBase")         <0) return kTRUE;
  if (gSystem->Load("libESD")               <0) return kTRUE;
  if (gSystem->Load("libAOD")               <0) return kTRUE;
  if (gSystem->Load("libANALYSIS")          <0) return kTRUE;
  if (gSystem->Load("libOADB")              <0) return kTRUE;
  if (gSystem->Load("libCDB")               <0) return kTRUE;
//  if (gSystem->Load("libANALYSISalice")     <0) return kTRUE;
//  if (gSystem->Load("libANALYSISaliceBase")     <0) return kTRUE;
  if (gSystem->Load("libCORRFW")            <0) return kTRUE;
  if (gSystem->Load("libPWGTools")          <0) return kTRUE;
  if (gSystem->Load("libPWGflowBase")       <0) return kTRUE;
  if (gSystem->Load("libPWGflowTasks")      <0) return kTRUE;
  if (gSystem->Load("libPWGHFbase")         <0) return kTRUE;
  if (gSystem->Load("libPWGHFvertexingHF")  <0) return kTRUE;
  if (gSystem->Load("libSTAT")              <0) return kTRUE;
  if (gSystem->Load("libEMCALUtils")        <0) return kTRUE;

  if (gSystem->Load("libRAWDatabase")       <0) return kTRUE;
  if (gSystem->Load("libRAWDatarec")        <0) return kTRUE;
  //if (gSystem->Load("libSTEER")             <0) return kTRUE;
  if (gSystem->Load("libITSbase")           <0) return kTRUE;
  if (gSystem->Load("libITSrec")            <0) return kTRUE;
  if (gSystem->Load("libTPCbase")           <0) return kTRUE;
  if (gSystem->Load("libTPCrec")            <0) return kTRUE;
  if (gSystem->Load("libTRDbase")           <0) return kTRUE;
  if (gSystem->Load("libTRDrec")            <0) return kTRUE;
  if (gSystem->Load("libTOFbase")           <0) return kTRUE;
//if (gSystem->Load("libTOFrec")            <0) return kTRUE;
  if (gSystem->Load("libHMPIDbase")         <0) return kTRUE;
  if (gSystem->Load("libEMCALraw")          <0) return kTRUE;
  if (gSystem->Load("libEMCALbase")         <0) return kTRUE;
  if (gSystem->Load("libEMCALrec")          <0) return kTRUE;
  if (gSystem->Load("libVZERObase")         <0) return kTRUE;
  if (gSystem->Load("libVZEROrec")          <0) return kTRUE;
  if (gSystem->Load("libTender")            <0) return kTRUE;
  if (gSystem->Load("libTenderSupplies")    <0) return kTRUE;
  if (gSystem->Load("libESDfilter")         <0) return kTRUE;


  if (gSystem->Load("libCGAL")              <0) return kTRUE;
  if (gSystem->Load("libfastjet")           <0) return kTRUE;
  if(gSystem->Load("libsiscone")            <0) return kTRUE;
  if(gSystem->Load("libsiscone_spherical")  <0) return kTRUE;
  if(gSystem->Load("libfastjetplugins")     <0) return kTRUE;
  if(gSystem->Load("libfastjettools")       <0) return kTRUE;
  if(gSystem->Load("libfastjetcontribfragile") <0)return kTRUE;


  if (gSystem->Load("libJETAN")             <0) return kTRUE;
  if (gSystem->Load("libFASTJETAN")         <0) return kTRUE;
  //if (gSystem->Load("libPWGEMCAL")          <0) return kTRUE;
  if (gSystem->Load("libPWGJEEMCALJetTasks")<0) return kTRUE;
  if (gSystem->Load("libPWGJEFlavourJetTasks.so")<0) return kTRUE;


  gSystem->AddIncludePath("-Wno-deprecated");
  gSystem->AddIncludePath("-I$ALICE_ROOT/include");
  gSystem->AddIncludePath("-I$ALICE_PHYSICS/include");
  gSystem->AddIncludePath("-I$ALICE_PHYSICS/PWGHF/vertexingHF");
  gSystem->AddIncludePath("-I$ALICE_PHYSICS/EMCAL");
  gSystem->AddIncludePath("-I$ALICE_PHYSICS/JETAN");
  gSystem->AddIncludePath("-I$ALICE_PHYSICS/JETAN/fastjet");
//=============================================================================


  return kFALSE;
}
