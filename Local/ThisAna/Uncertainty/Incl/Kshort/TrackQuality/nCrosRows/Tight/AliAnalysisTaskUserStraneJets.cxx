#include <iostream>
#include <iomanip>

#include <TFile.h>
#include <TList.h>
#include <TClonesArray.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <THnSparse.h>
#include <TMath.h>
#include <TVector3.h>
#include <TRandom3.h>
#include <TChain.h>
#include <TNtuple.h>
#include <TDatabasePDG.h>

#include "AliAODEvent.h"
#include "AliVEventHandler.h"

#include "AliPicoV0RD.h"
#include "AliPicoV0MC.h"

#include "AliPicoJet.h"
#include "AliPicoHeaderJet.h"
#include "AliMultSelection.h"

#include "AliPicoBaseDev.h"
#include "AliPicoCascade.h"
#include "AliPicoCascadeRD.h"
#include "AliPicoCascadeMC.h"

#include "AliAnalysisTaskUserStraneJets.h"

ClassImp(AliAnalysisTaskUserStraneJets)

//_____________________________________________________________________________
AliAnalysisTaskUserStraneJets::AliAnalysisTaskUserStraneJets(const char *name) :
TNamed(name,name),
fIon(0),
fChainRD(0x0),
fEventRD(0x0),
fChainMC(0x0),
fEventMC(0x0),
fHeader(0x0),
fMult(0x0),
fV0sClArr(0x0),
fCascadesClArr(0x0),
fJetsRD02ClArr(0x0),
fJetsRD03ClArr(0x0),
fJetsRD04ClArr(0x0),
fJetsMC02ClArr(0x0),
fJetsMC03ClArr(0x0),
fJetsMC04ClArr(0x0),
fHistoDetectorRM(0x0),
fTriggerMask(0),
fTriggerClass(""),
fCentralityMin(0.),
fCentralityMax(100.),
fCentralityEstimator(""),
fJetUseEstiPt(kFALSE),
fJetCutMinMulti(-1),
fJetCutMaxMulti(-1),
fJetCutMinPt(0.),
fJetCutMaxPt(-1.),
fJetCutMinEta(-1.),
fJetCutMaxEta(1.),
fJetCutMinPhi(-10.),
fJetCutMaxPhi(10.),
fJetCutMinAreaFrac(-1.),
fJetCutMinLeadingPt(-1.),
fRefCutMinMulti(-1),
fRefCutMaxMulti(-1),
fRefCutMinPt(0.),
fRefCutMaxPt(-1.),
fRefCutMinEta(-1.),
fRefCutMaxEta(1.),
fRefCutMinPhi(-10.),
fRefCutMaxPhi(10.),
fRefCutMinAreaFrac(-1.),
fRefCutMinLeadingPt(-1.),
fV0IsCutEta(kFALSE),
fV0IsCutRap(kFALSE),
fV0CutMinEta(-10.),
fV0CutMaxEta(10.),
fV0CutMinRap(-10.),
fV0CutMaxRap(10.),
fV0CutMinDauEta(-10.),
fV0CutMaxDauEta(10.),
fKaCutNS(6.),
fLaCutNS(6.),
fCascadeIsCutEta(kFALSE),
fCascadeIsCutRap(kFALSE),
fCascadeCutMinEta(-10.),
fCascadeCutMaxEta(10.),
fCascadeCutMinRap(-10.),
fCascadeCutMaxRap(10.),
fCutMinTrkEta(-10.),
fCutMaxTrkEta(10.),
fXiCutNS(4.),
fOmegaCutNS(4.),
fIsStrangeInJet(kFALSE),
fIsStrangeInPCL(kFALSE),
fIsStrangeInPCU(kFALSE),
fInJetCutR(0.4),
fBkgParCutR(0.6),
fJetPtBinN(0),
fJetPtBinA(0),
fKaPtBinN(0),
fKaPtBinA(0),
fLaPtBinN(0),
fLaPtBinA(0),
fXiPtBinN(0),
fXiPtBinA(0),
fOmegaPtBinN(0),
fOmegaPtBinA(0),
fFileLoop1st(""),
fFileLoop2nd(""),
fFileLoopJet(""),
fFileLoopsMC(""),
fFileFitInvM(""),
fFileFitCbin(""),
fFileMakeEff(""),
fFileResults(""),
fFileMakeFdR(""),
fListLoop1st(""),
fListLoop2nd(""),
fListLoopJet(""),
fListLoopsMC(""),
fListFitInvM(""),
fListFitCbin(""),
fListMakeEff(""),
fListResults(""),
fListMakeFdR("")
{
//
//  AliAnalysisTaskUserStraneJets::AliAnalysisTaskUserStraneJets
//

  for (Int_t i=0; i<9; i++) { fKaCuts[i] = 0.; fLaCuts[i] = 0.; }
  for (Int_t i=0; i<20; i++) { fXiCuts[i] = 0.; fOmegaCuts[i] = 0.; }
}

//_____________________________________________________________________________
AliAnalysisTaskUserStraneJets::~AliAnalysisTaskUserStraneJets()
{
//
//  AliAnalysisTaskUserStraneJets::~AliAnalysisTaskUserStraneJets
//

  if (fChainRD) { delete fChainRD; fChainRD = 0; }
  if (fEventRD) { delete fEventRD; fEventRD = 0; }

  if (fChainMC) { delete fChainMC; fChainMC = 0; }
  if (fEventMC) { delete fEventMC; fEventMC = 0; }


  if (fHeader) { delete fHeader; fHeader = 0; }
  if (fMult)   { delete fMult;   fMult = 0; }

  if (fV0sClArr) { delete fV0sClArr; fV0sClArr = 0; }
  if (fCascadesClArr) { delete fCascadesClArr; fCascadesClArr = 0; }

  if (fJetsRD02ClArr) { delete fJetsRD02ClArr; fJetsRD02ClArr = 0; }
  if (fJetsRD03ClArr) { delete fJetsRD03ClArr; fJetsRD03ClArr = 0; }
  if (fJetsRD04ClArr) { delete fJetsRD04ClArr; fJetsRD04ClArr = 0; }

  if (fJetsMC02ClArr) { delete fJetsMC02ClArr; fJetsMC02ClArr = 0; }
  if (fJetsMC03ClArr) { delete fJetsMC03ClArr; fJetsMC03ClArr = 0; }
  if (fJetsMC04ClArr) { delete fJetsMC04ClArr; fJetsMC04ClArr = 0; }


  if (fHistoDetectorRM) { delete fHistoDetectorRM; fHistoDetectorRM = 0; }


  if (fJetPtBinA) { delete [] fJetPtBinA; fJetPtBinA = 0; }
  if (fKaPtBinA)  { delete [] fKaPtBinA;  fKaPtBinA  = 0; }
  if (fLaPtBinA)  { delete [] fLaPtBinA;  fLaPtBinA  = 0; }
  if (fXiPtBinA)  { delete [] fXiPtBinA;  fXiPtBinA  = 0; }
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaJetSparse(const TString sJet)
{
//
//  AliAnalysisTaskUserStraneJets::AnaJetSparse
//
  if (sJet.IsNull()) return;
//=============================================================================

  TFile *file = TFile::Open("AnalysisOutputs_JetSparse.root", "NEW"); TList *list = new TList();

                             // 0: CL1
                             // 1: V0A
                             // 2: ZNA
                             // 3: jet area
                             // 4: jet eta
                             // 5: jet meas pT
                             // 6: jet esti pT
  const Int_t    nVar   = 8; // 7: jet corr pT
  const Int_t    nBin[] = { 210,  210,  210, 300,  80,   200,   200,   200  };
  const Double_t dMin[] = { -10., -10., -10.,  0., -2., -100., -100., -100. };
  const Double_t dMax[] = { 200., 200., 200.,  3.,  2.,  100.,  100.,  100. };
  THnSparseD *hsJet = new THnSparseD("hsJet", "", nVar, nBin, dMin, dMax); list->Add(hsJet);
//=============================================================================

  TH1D *hEvent = new TH1D("hEvent","",5,-0.5,4.5); hEvent->Sumw2();list->Add(hEvent);
  TH1D *hPt    = new TH1D("hPt","",100,0,100); hPt->Sumw2();list->Add(hPt);
  Int_t iEvent = 0;
  Double_t dVar[nVar];
  TClonesArray *pJetsClArr = 0;
    
  while(fChainRD->GetEntry(iEvent++)) if (InitEvent("J")) {
    if(iEvent%1000000==0) cout<<"event = "<<iEvent/1000000<<"M"<<endl;//每一百万event输出一次 
    pJetsClArr  = GetJets(sJet); if (!pJetsClArr) continue;
    Int_t nJets = pJetsClArr->GetEntriesFast(); if (nJets<=0) { pJetsClArr = 0; continue; }
//=============================================================================
    Double_t dcCL1 = fMult->GetMultiplicityPercentile("CL1");
    Double_t dcV0A = fMult->GetMultiplicityPercentile("V0A");
    Double_t dcZNA = fMult->GetMultiplicityPercentile("ZNA");
    Double_t dBkgJ = fHeader->BackgroundRho();

   hEvent->Fill(0);
//=============================================================================
    AliPicoJet *pJet = 0;
    for (Int_t j=0; j<nJets; j++) {
      pJet = (AliPicoJet*)pJetsClArr->At(j); if (!pJet) continue;
      if (IsJetNotSelected(pJet,sJet)) { pJet = 0; continue; }
//=============================================================================
      
      Double_t dJetArea = pJet->Area();
      Double_t dJetEta  = pJet->Kine().Eta();
      Double_t dPtMeas  = pJet->Kine().Pt();
      Double_t dPtEsti  = dPtMeas - (dJetArea * dBkgJ);
      Double_t dPtCorr = -0.5;
      hPt->Fill(dPtMeas);
      continue;
      pJet=0;
      continue;
//=============================================================================
   dVar[0] = dcCL1;
   dVar[1] = dcV0A;
   dVar[2] = dcZNA;
   dVar[3] = dJetArea;
   dVar[4] = dJetEta;
   dVar[5] = dPtMeas;
   dVar[6] = dPtEsti;
   dVar[7] = dPtCorr;
   hsJet->Fill(dVar);
//=============================================================================

      pJet = 0;
    }

    pJetsClArr = 0;
  }
//=============================================================================

  file->cd(); list->Write("listSparseJet", TObject::kSingleKey); file->Close();
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaJetSparse(const TString sJet, const TString sRef)
{
//
//  AliAnalysisTaskUserStraneJets::AnaJetSparse
//

  if (sJet.IsNull() || sRef.IsNull() || (sJet==sRef)) return;
//=============================================================================

  TFile *file = TFile::Open("AnalysisOutputs_JetSparse.root", "UPDATE");
  TList *list = (TList*)file->Get("listSparseRje"); if (list) { file->Close(); return; } else { list = new TList(); }

                            //  0: CL1
                            //  1: V0A
                            //  2: ZNA
                            //  3: jet area
                            //  4: jet eta
                            //  5: jet pT meas
                            //  6: jet pT esti
                            //  7: ref area
                            //  8: ref eta
                            //  9: ref pT meas
                            // 10: ref pT esti
  const Int_t    nVar = 12; // 11: ref pT esti / jet pT esti
  const Int_t    nBin[] = { 210,  210,  210, 300,  80,   200,   200, 300,  80,   200,   200, 6000   };
  const Double_t dMin[] = { -10., -10., -10.,  0., -2., -100., -100.,  0., -2., -100., -100.,  -1.  };
  const Double_t dMax[] = { 200., 200., 200.,  3.,  2.,  100.,  100.,  3.,  2.,  100.,  100.,   5.  };
  THnSparseD *hsJet = new THnSparseD("hsJet", "", nVar, nBin, dMin, dMax); list->Add(hsJet);
//=============================================================================

  Int_t iEvent = 0;
  Double_t dVar[nVar];
  TClonesArray *pJetsClArr = 0;
  TClonesArray *pRefsClArr = 0;


  while(fChainRD->GetEntry(iEvent++)) if (InitEvent("J")) {
    pJetsClArr  = GetJets(sJet); if (!pJetsClArr) continue;
    Int_t nJets = pJetsClArr->GetEntriesFast();
    if (nJets<=0) { pJetsClArr = 0; continue; }
    if (!pRefsClArr) { pJetsClArr = 0;  continue; }
    Int_t nRefs = pRefsClArr->GetEntriesFast(); if (nRefs<=0) { pJetsClArr = 0; pRefsClArr = 0; continue; }
//=============================================================================

    Double_t dcCL1 = fMult->GetMultiplicityPercentile("CL1");
    Double_t dcV0A = fMult->GetMultiplicityPercentile("V0A");
    Double_t dcZNA = fMult->GetMultiplicityPercentile("ZNA");
    Double_t dBkgJ = fHeader->BackgroundRho();
    Double_t dBkgR = fHeader->BackgroundRho();
//=============================================================================

    AliPicoJet *pJet = 0;
    AliPicoJet *pRef = 0;
    for (Int_t j=0; j<nJets; j++) {
      pJet = (AliPicoJet*)pJetsClArr->At(j); if (!pJet) continue;
      if (IsJetNotSelected(pJet,sJet)) { pJet = 0; continue; }

      pRef = GetMatchedJet(pJet,pRefsClArr,sJet,sRef); if (!pRef) { pJet = 0; continue; }
      if (IsRefNotSelected(pRef,sRef)) { pRef = 0; pJet = 0; continue; }
//=============================================================================

      Double_t dJetEta  = pJet->Kine().Eta();
      Double_t dJetArea = pJet->Area();
      Double_t dJetMeas = pJet->Kine().Pt();
      Double_t dJetEsti = dJetMeas - (dJetArea * dBkgJ);
//=============================================================================

      Double_t dRefEta  = pRef->Kine().Eta();
      Double_t dRefArea = pRef->Area();
      Double_t dRefMeas = pRef->Kine().Pt();
      Double_t dRefEsti = dRefMeas - (dRefArea * dBkgR);
      Double_t dRefFrac = dRefEsti / dJetEsti;

      if (dRefFrac< 0.) dRefFrac = -0.5;
      if (dRefFrac>=5.) dRefFrac =  4.9;
//=============================================================================

      dVar[ 0] = dcCL1;
      dVar[ 1] = dcV0A;
      dVar[ 2] = dcZNA;
      dVar[ 3] = dJetArea;
      dVar[ 4] = dJetEta;
      dVar[ 5] = dJetMeas;
      dVar[ 6] = dJetEsti;
      dVar[ 7] = dRefArea;
      dVar[ 8] = dRefEta;
      dVar[ 9] = dRefMeas;
      dVar[10] = dRefEsti;
      dVar[11] = dRefFrac;
      hsJet->Fill(dVar);
//=============================================================================

      pRef = 0;
      pJet = 0;
    }

    pRefsClArr = 0;
    pJetsClArr = 0;
  }
//=============================================================================

  file->cd(); list->Write("listSparseRje", TObject::kSingleKey); file->Close();
  return;
}


//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaV0MakeNtuple()
{
//
//  AliAnalysisTaskUserStraneJets::AnaV0MakeNTuple
//

  const Int_t n = 20;
  const TString sVar[n] = {
    "fV0Radius", "fV0CosPA", "fV0DistOverP", "fDausDCA", "fPosDCAtoPV",  "fNegDCAtoPV",
    "fDauXrowsTPC", "fDauXoverFrowsTPC",
    "fPosPionSigmaTPC", "fNegPionSigmaTPC", "fPosProtonSigmaTPC", "fNegProtonSigmaTPC",
    "fPtRD", "fRapKa", "fRapLa", "fKaInvM", "fLaInvM", "fALInvM", "fPosEta", "fNegEta"
  };

  TString sList;
  TFile *file = TFile::Open("AnalysisV0Ntuple.root", "NEW");
  for (Int_t i=0; i<n; i++) { sList += sVar[i]; if (i<(n-1)) sList += ":"; }
  TNtuple *ntKshort = new TNtuple("ntKshortJErd", "", sList.Data());
  TNtuple *ntLambda = new TNtuple("ntLambdaJErd", "", sList.Data());
  TNtuple *ntAntiLa = new TNtuple("ntAntiLaJErd", "", sList.Data());
//=============================================================================

  Float_t dVar[n];
  Int_t iEvent = 0;
  while(fChainRD->GetEntry(iEvent++)) if (InitEvent("P")) {

    AliPicoV0RD *pV0 = 0;
    for (Int_t i=0; i<fV0sClArr->GetEntriesFast(); i++) {
      pV0 = (AliPicoV0RD*)fV0sClArr->At(i); if (!pV0) continue;
      if (!pV0->IsDausInEtaAcc(fV0CutMinDauEta,fV0CutMaxDauEta)) { pV0 = 0; continue; }
      if (fV0IsCutEta) { if (!pV0->IsV0InEtaAcc(fV0CutMinEta,fV0CutMaxEta)) { pV0 = 0; continue; } }

      Bool_t bKshort = kTRUE;
      Bool_t bLambda = kTRUE;
      Bool_t bAntiLa = kTRUE;

      if (fV0IsCutRap) {
        bKshort = pV0->IsKaInRapAcc(fV0CutMinRap,fV0CutMaxRap);
        bLambda = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap);
        bAntiLa = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap);
      }

      if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }
      if (bKshort) { if (pV0->IsKshort(fKaCuts)) ntKshort->Fill(dVar); }
      if (bLambda) { if (pV0->IsLambda(fLaCuts)) ntLambda->Fill(dVar); }
      if (bAntiLa) { if (pV0->IsAntiLa(fLaCuts)) ntAntiLa->Fill(dVar); }

      pV0 = 0;
    }
  }
//=============================================================================

  file->cd();
  ntKshort->Write();
  ntLambda->Write();
  ntAntiLa->Write();
  file->Close();
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaLoop1RD(const TString sOpt)
{
//
//  AliAnalysisTaskUserV0s::AnaLoop1RD
//
  
  if (fFileLoop1st.IsNull() || fListLoop1st.IsNull()) return;
  if ((sOpt!="Kshort") && (sOpt!="Lambda") && (sOpt!="AntiLa")
       && (sOpt!="Xi") && (sOpt!="XiNeg") && (sOpt!="XiPos")
       && (sOpt!="Omega") && (sOpt!="OmegaNeg") && (sOpt!="OmegaPos")) return;

  if (sOpt == "Kshort")  if ((fKaPtBinN<=0) || (!fKaPtBinA)) return; 
  if ((sOpt == "Lambda") || (sOpt == "AntiLa"))  if ((fLaPtBinN<=0) || (!fLaPtBinA)) return;
  if ((sOpt == "Xi") || (sOpt == "XiPos") || (sOpt == "XiNeg"))  if ((fXiPtBinN<=0) || (!fXiPtBinA)) return;
  if ((sOpt == "Omega") || (sOpt == "OmegaPos") || (sOpt == "OmegaNeg"))  if ((fOmegaPtBinN<=0) || (!fOmegaPtBinA)) return;

  cout << "Analyzing inclusive " << sOpt.Data() << " 1st loop in RD..." << endl;
//=============================================================================
  
  TFile *file = TFile::Open(Form("%s.root",fFileLoop1st.Data()), "UPDATE");

  TList *list = (TList*)file->Get(fListLoop1st.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

  TH2D *hPtInvM = 0;
  if (sOpt=="Kshort") {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(310)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fKaPtBinN, fKaPtBinA, 300, dMass-0.15, dMass+0.15);
  }
  if ((sOpt == "Lambda") || (sOpt == "AntiLa")) {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(3122)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fLaPtBinN, fLaPtBinA, 200, dMass-0.10, dMass+0.10);
  } 
  if ((sOpt == "XiPos") || (sOpt == "XiNeg") || (sOpt == "Xi")) {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(3312)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fXiPtBinN, fXiPtBinA, 400, dMass-0.15, dMass+0.25);
  }
  if ((sOpt == "OmegaPos") || (sOpt == "OmegaNeg") || (sOpt == "Omega")) {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(3334)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fOmegaPtBinN, fOmegaPtBinA, 400, dMass-0.15, dMass+0.25);
  }
  hPtInvM->Sumw2(); list->Add(hPtInvM);

  TH1D *hEvent = new TH1D("hEvent", "", 100, 0., 100.); hEvent->Sumw2(); list->Add(hEvent);
  TH1D *hStrEvent = new TH1D("hStrEvent", "", 100, 0., 100.); hStrEvent->Sumw2(); list->Add(hStrEvent);
//=============================================================================

  Int_t iEvent = 0;

  cout<<fChainRD->GetEntries() <<endl;
  while (fChainRD->GetEntry(iEvent++)) if (InitEvent("P")) {

   if(iEvent%1000000==0) cout<<iEvent/1000000<< " = M"<<endl; 
    Float_t dCent = 0.;
      if (fCentralityEstimator=="V0M") dCent = fMult->GetMultiplicityPercentile("V0M");
      if (fCentralityEstimator=="V0A") dCent = fMult->GetMultiplicityPercentile("V0A");
      if (fCentralityEstimator=="CL1") dCent = fMult->GetMultiplicityPercentile("CL1");
      if (fCentralityEstimator=="ZNA") dCent = fMult->GetMultiplicityPercentile("ZNA");
    hEvent->Fill(dCent);//All Event Number
    
    Int_t nV0s = 0;
    if((sOpt == "Kshort") || (sOpt == "Lambda") || (sOpt == "AntiLa")){
      nV0s = fV0sClArr->GetEntriesFast(); if (nV0s<=0) continue;
      hStrEvent->Fill(dCent);
      AliPicoV0RD *pV0 = 0;
      for (Int_t i=0; i<nV0s; i++) {
        pV0 = (AliPicoV0RD*)fV0sClArr->At(i); if (!pV0) continue;
        if (!pV0->IsDausInEtaAcc(fV0CutMinDauEta,fV0CutMaxDauEta)) { pV0 = 0; continue; }
        if (fV0IsCutEta) { if (!pV0->IsV0InEtaAcc(fV0CutMinEta,fV0CutMaxEta)) { pV0 = 0; continue; } }

        Bool_t bKshort = kFALSE;
        Bool_t bLambda = kFALSE;
        Bool_t bAntiLa = kFALSE;
        if (sOpt=="Kshort") { if (fV0IsCutRap) { bKshort = pV0->IsKaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bKshort = kTRUE; } }
        if (sOpt=="Lambda") { if (fV0IsCutRap) { bLambda = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bLambda = kTRUE; } }
        if (sOpt=="AntiLa") { if (fV0IsCutRap) { bAntiLa = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bAntiLa = kTRUE; } }
        if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }

        if (bKshort) { if (pV0->IsKshort(fKaCuts)) pV0->FillKshortPtInvM(hPtInvM); }
        if (bLambda) { if (pV0->IsLambda(fLaCuts)) pV0->FillLambdaPtInvM(hPtInvM); }
        if (bAntiLa) { if (pV0->IsAntiLa(fLaCuts)) pV0->FillAntiLaPtInvM(hPtInvM); }

        pV0 = 0;
      }
    }
    
//=============================================================================
    Int_t nCascades = 0;
    if((sOpt=="Xi") || (sOpt=="XiPos") || (sOpt=="XiNeg") || (sOpt=="Omega") || (sOpt=="OmegaPos") || (sOpt=="OmegaNeg")){
      nCascades = fCascadesClArr->GetEntriesFast(); if (nCascades<=0) continue;
      hStrEvent->Fill(dCent);
      AliPicoCascadeRD *pCascade = nullptr;
      for (Int_t i=0; i<nCascades; i++) {

        pCascade = (AliPicoCascadeRD*)fCascadesClArr->At(i); if (!pCascade) continue;

        auto pV0 = (AliPicoV0*)pCascade->GetV0(); if(!pV0) continue;
        if (!pV0->IsDausInEtaAcc(fCutMinTrkEta,fCutMaxTrkEta)) { pCascade = 0; continue; }
        if (!pCascade->IsBachInEtaAcc(fCutMinTrkEta,fCutMaxTrkEta)) { pCascade = 0; continue; }
        if (fCascadeIsCutEta) { if (!pCascade->IsCascadeInEtaAcc(fCascadeCutMinEta,fCascadeCutMaxEta)) { pCascade = 0; continue; } }

        auto bXiPos(kFALSE);
        auto bXiNeg(kFALSE);
        auto bXi(kFALSE);
        auto bOmegaPos(kFALSE);
        auto bOmegaNeg(kFALSE);
        auto bOmega(kFALSE);

        if (sOpt=="XiPos"){ if (fCascadeIsCutRap) { bXiPos = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else { bXiPos = kTRUE;} }
        if (sOpt=="XiNeg"){ if (fCascadeIsCutRap) { bXiNeg = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else {bXiNeg  = kTRUE;} }
        if (sOpt=="Xi")   { if (fCascadeIsCutRap) { bXi = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); }    else { bXi    = kTRUE; } }
        if (sOpt=="OmegaPos"){ if (fCascadeIsCutRap) {bOmegaPos = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else{ bOmegaPos = kTRUE;} }
        if (sOpt=="OmegaNeg"){ if (fCascadeIsCutRap) {bOmegaNeg = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else {bOmegaNeg = kTRUE;} }
        if (sOpt=="Omega")   { if (fCascadeIsCutRap) {bOmega    = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else { bOmega   = kTRUE; } }
        if (!(bXiPos || bXiNeg || bXi || bOmegaPos || bOmegaNeg || bOmega)) { pCascade = 0; continue; }

        if (bXiPos) bXiPos = pCascade->IsXiPos(fXiCuts);
        if (bXiNeg) bXiNeg = pCascade->IsXiNeg(fXiCuts);
        if (bXi) { bXi = ( pCascade->IsXiPos(fXiCuts) || pCascade->IsXiNeg(fXiCuts)); }
        if (bOmegaPos) bOmegaPos = pCascade->IsOmegaPos(fOmegaCuts);
        if (bOmegaNeg) bOmegaNeg = pCascade->IsOmegaNeg(fOmegaCuts);
        if (bOmega){ bOmega = ( pCascade-> IsOmegaPos(fOmegaCuts) || pCascade->IsOmegaNeg(fOmegaCuts)); }
        if (!(bXiPos || bXiNeg || bXi || bOmegaPos || bOmegaNeg || bOmega)) { pCascade = 0; continue; }

        if (bXiNeg) pCascade->FillXiNegPtInvM(hPtInvM);
        if (bXiPos) pCascade->FillXiPosPtInvM(hPtInvM);
        if (bXi) {pCascade->FillXiPtInvM(hPtInvM);}
        if (bOmegaNeg) pCascade->FillOmegaNegPtInvM(hPtInvM);
        if (bOmegaPos) pCascade->FillOmegaPosPtInvM(hPtInvM);
        if (bOmega) {pCascade->FillOmegaPtInvM(hPtInvM);}

        pCascade = 0;

      }
    }
  }
//=============================================================================

  file->cd(); list->Write(fListLoop1st.Data(), TObject::kSingleKey); file->Close();
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaLoop2RD(const TString sOpt)
{
//
//  AliAnalysisTaskUserStraneJets::AnaLoop2RD
//

  if (fFileFitInvM.IsNull() || fListFitInvM.IsNull()) return;
  if (fFileLoop2nd.IsNull() || fListLoop2nd.IsNull()) return;
  if ((sOpt!="Kshort") && (sOpt!="Lambda") && (sOpt!="AntiLa")
       && (sOpt!="Xi") && (sOpt!="XiNeg") && (sOpt!="XiPos")
       && (sOpt!="Omega") && (sOpt!="OmegaNeg") && (sOpt!="OmegaPos")) return;

  cout << "Analyzing inclusive " << sOpt.Data() << " 2nd loop in RD..." << endl;
//=============================================================================

  TFile *file =  TFile::Open(Form("%s.root",fFileFitInvM.Data()), "READ"); if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListFitInvM.Data()); file->Close(); if (!list) return;

  TH1D *hFitPtInvM = (TH1D*)list->FindObject("hFitPtInvM"); if (!hFitPtInvM) return;
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileLoop2nd.Data()), "UPDATE");
  list = (TList*)file->Get(fListLoop2nd.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

  TH2D  *hPtEtaI = 0;
  if (sOpt=="Kshort") hPtEtaI = new TH2D("hPtEtaI", "", fKaPtBinN, fKaPtBinA, 100, -5., 5.);
  if (sOpt == "Lambda" || sOpt == "AntiLa") hPtEtaI = new TH2D("hPtEtaI", "", fLaPtBinN, fLaPtBinA, 100, -5., 5.);
  if ((sOpt == "XiPos") || (sOpt == "XiNeg") || (sOpt == "Xi")) hPtEtaI = new TH2D("hPtEtaI", "", fXiPtBinN, fXiPtBinA, 100, -5., 5.);
  if ((sOpt == "OmegaPos") || (sOpt == "OmegaNeg") || (sOpt == "Omega")) hPtEtaI = new TH2D("hPtEtaI", "", fOmegaPtBinN, fOmegaPtBinA, 100, -5., 5.);
  hPtEtaI->Sumw2(); list->Add(hPtEtaI);

  TH1D *hCountInW = (TH1D*)hFitPtInvM->Clone("hCountInW"); hCountInW->Reset(); list->Add(hCountInW);
  TH1D *hCountInB = (TH1D*)hFitPtInvM->Clone("hCountInB"); hCountInB->Reset(); list->Add(hCountInB);

  TH1D *hEvent = new TH1D("hEvent", "", 100, 0., 100.); hEvent->Sumw2(); list->Add(hEvent);
  TH1D *hStrEvent = new TH1D("hStrEvent", "", 100, 0., 100.); hStrEvent->Sumw2(); list->Add(hStrEvent);
//=============================================================================

  Double_t dSN = fKaCutNS;
  if (sOpt == "Lambda" || sOpt == "AntiLa") dSN = fLaCutNS;
  if ((sOpt == "XiPos") || (sOpt == "XiNeg") || (sOpt == "Xi")) dSN = fXiCutNS;
  if ((sOpt == "OmegaPos") || (sOpt == "OmegaNeg") || (sOpt == "Omega")) dSN = fOmegaCutNS;

  Int_t iEvent = 0;
  while (fChainRD->GetEntry(iEvent++)) if (InitEvent("P")) {
   
    if(iEvent%1000000==0) cout<<iEvent/1000000<< " = M"<<endl; 

    Float_t dCent = 0.;
    if (fCentralityEstimator=="V0M") dCent = fMult->GetMultiplicityPercentile("V0M");
    if (fCentralityEstimator=="V0A") dCent = fMult->GetMultiplicityPercentile("V0A");
    if (fCentralityEstimator=="CL1") dCent = fMult->GetMultiplicityPercentile("CL1");
    if (fCentralityEstimator=="ZNA") dCent = fMult->GetMultiplicityPercentile("ZNA");
    hEvent->Fill(dCent);

    Int_t nV0s = 0;
    if((sOpt == "Kshort") || (sOpt == "Lambda") || (sOpt == "AntiLa")){
      nV0s = fV0sClArr->GetEntriesFast(); if (nV0s<=0) continue;
      hStrEvent->Fill(dCent);
      AliPicoV0RD *pV0 = 0;
      for (Int_t i=0; i<nV0s; i++) {
        pV0 = (AliPicoV0RD*)fV0sClArr->At(i); if (!pV0) continue;
        if (!pV0->IsDausInEtaAcc(fV0CutMinDauEta,fV0CutMaxDauEta)) { pV0 = 0; continue; }
        if (fV0IsCutEta) { if (!pV0->IsV0InEtaAcc(fV0CutMinEta,fV0CutMaxEta)) { pV0 = 0; continue; } }

        Bool_t bKshort = kFALSE;
        Bool_t bLambda = kFALSE;
        Bool_t bAntiLa = kFALSE;
        if (sOpt=="Kshort") { if (fV0IsCutRap) { bKshort = pV0->IsKaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bKshort = kTRUE; } }
        if (sOpt=="Lambda") { if (fV0IsCutRap) { bLambda = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bLambda = kTRUE; } }
        if (sOpt=="AntiLa") { if (fV0IsCutRap) { bAntiLa = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bAntiLa = kTRUE; } }
        if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }

        if (bKshort) bKshort = pV0->IsKshort(fKaCuts);
        if (bLambda) bLambda = pV0->IsLambda(fLaCuts);
        if (bAntiLa) bAntiLa = pV0->IsAntiLa(fLaCuts);
        if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }

        TLorentzVector vV0;
        if (bKshort) vV0 = pV0->KineKshort();
        if (bLambda) vV0 = pV0->KineLambda();
        if (bAntiLa) vV0 = pV0->KineAntiLa();

        Double_t dPt   = vV0.Pt();
        Double_t dEta  = vV0.Eta();
        Double_t dInvM = vV0.M();
        Int_t k = hFitPtInvM->FindBin(dPt); if (k<=0) { pV0 = 0; continue; }

        Double_t dMean  = hFitPtInvM->GetBinContent(k);
        Double_t dSigma = hFitPtInvM->GetBinError(k);

        Double_t dLowerL = dMean - 2.*dSN*dSigma;
        Double_t dUpperL = dMean - 1.*dSN*dSigma;
        Double_t dLowerR = dMean + 1.*dSN*dSigma;
        Double_t dUpperR = dMean + 2.*dSN*dSigma;

        if  ((dInvM>dUpperL) && (dInvM<dLowerR))  { hCountInW->Fill(dPt); hPtEtaI->Fill(dPt, dEta); }

        if (((dInvM>dLowerL) && (dInvM<dUpperL)) ||
            ((dInvM>dLowerR) && (dInvM<dUpperR)))   hCountInB->Fill(dPt);

        pV0 = 0;
      }
    }
    
//=============================================================================
    Int_t nCascades = 0;
    if((sOpt=="Xi") || (sOpt=="XiPos") || (sOpt=="XiNeg") || (sOpt=="Omega") || (sOpt=="OmegaPos") || (sOpt=="OmegaNeg")){
      nCascades = fCascadesClArr->GetEntriesFast(); if (nCascades<=0) continue;
      hStrEvent->Fill(dCent);
      AliPicoCascadeRD *pCascade = nullptr;
      for (Int_t i=0; i<nCascades; i++) {

        pCascade = (AliPicoCascadeRD*)fCascadesClArr->At(i); if (!pCascade) continue;

        auto pV0 = (AliPicoV0*)pCascade->GetV0(); if(!pV0) continue;
        if (!pV0->IsDausInEtaAcc(fCutMinTrkEta,fCutMaxTrkEta)) { pCascade = 0; continue; }
        if (!pCascade->IsBachInEtaAcc(fCutMinTrkEta,fCutMaxTrkEta)) { pCascade = 0; continue; }
        if (fCascadeIsCutEta) { if (!pCascade->IsCascadeInEtaAcc(fCascadeCutMinEta,fCascadeCutMaxEta)) { pCascade = 0; continue; } }

        auto bXiPos(kFALSE);
        auto bXiNeg(kFALSE);
        auto bXi(kFALSE);
        auto bOmegaPos(kFALSE);
        auto bOmegaNeg(kFALSE);
        auto bOmega(kFALSE);

        if (sOpt=="XiPos"){ if (fCascadeIsCutRap) { bXiPos = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else { bXiPos = kTRUE;} }
        if (sOpt=="XiNeg"){ if (fCascadeIsCutRap) { bXiNeg = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else {bXiNeg  = kTRUE;} }
        if (sOpt=="Xi")   { if (fCascadeIsCutRap) { bXi = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); }    else { bXi    = kTRUE; } }
        if (sOpt=="OmegaPos"){ if (fCascadeIsCutRap) {bOmegaPos = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else{ bOmegaPos = kTRUE;} }
        if (sOpt=="OmegaNeg"){ if (fCascadeIsCutRap) {bOmegaNeg = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else {bOmegaNeg = kTRUE;} }
        if (sOpt=="Omega")   { if (fCascadeIsCutRap) {bOmega    = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else { bOmega   = kTRUE; } }
        if (!(bXiPos || bXiNeg || bXi || bOmegaPos || bOmegaNeg || bOmega)) { pCascade = 0; continue; }

        if (bXiPos) bXiPos = pCascade->IsXiPos(fXiCuts);
        if (bXiNeg) bXiNeg = pCascade->IsXiNeg(fXiCuts);
        if (bXi) { bXi = ( pCascade->IsXiPos(fXiCuts) || pCascade->IsXiNeg(fXiCuts)); }
        if (bOmegaPos) bOmegaPos = pCascade->IsOmegaPos(fOmegaCuts);
        if (bOmegaNeg) bOmegaNeg = pCascade->IsOmegaNeg(fOmegaCuts);
        if (bOmega){ bOmega = ( pCascade-> IsOmegaPos(fOmegaCuts) || pCascade->IsOmegaNeg(fOmegaCuts)); }
        if (!(bXiPos || bXiNeg || bXi || bOmegaPos || bOmegaNeg || bOmega)) { pCascade = 0; continue; }

        TLorentzVector vCascade;
        if(bXiPos || bXiNeg || bXi) vCascade = pCascade->KineXi();
        if(bOmegaPos || bOmegaNeg || bOmega) vCascade = pCascade->KineOmega();

        Double_t dPt   = vCascade.Pt();
        Double_t dEta  = vCascade.Eta();
        Double_t dInvM = vCascade.M();

        Int_t k = hFitPtInvM->FindBin(dPt); if (k<=0) { pCascade = 0; continue; }

        Double_t dMean  = hFitPtInvM->GetBinContent(k);
        Double_t dSigma = hFitPtInvM->GetBinError(k);

        Double_t dLowerL = dMean - 4.*dSN*dSigma;
        Double_t dUpperL = dMean - 2.*dSN*dSigma;
        Double_t dLowerR = dMean + 2.*dSN*dSigma;
        Double_t dUpperR = dMean + 4.*dSN*dSigma;
        Double_t dLowerS = dMean - 1.*dSN*dSigma;
        Double_t dUpperS = dMean + 1.*dSN*dSigma;

        if  ((dInvM>dLowerS) && (dInvM<dUpperS))  { hCountInW->Fill(dPt); hPtEtaI->Fill(dPt, dEta); }

        if (((dInvM>dLowerL) && (dInvM<dUpperL)) || ((dInvM>dLowerR) && (dInvM<dUpperR)))   hCountInB->Fill(dPt);

        pCascade = 0;
      }
    }
  }
//=============================================================================

  file->cd(); list->Write(fListLoop2nd.Data(), TObject::kSingleKey); file->Close();
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaLoopsMC(const TString sOpt)
{
//
//  AliAnalysisTaskUserStraneJets::AnaLoopsMC
//

  if (fFileFitInvM.IsNull() || fListFitInvM.IsNull()) return;
  if (fFileLoopsMC.IsNull() || fListLoopsMC.IsNull()) return;
  if ((sOpt!="Kshort") && (sOpt!="Lambda") && (sOpt!="AntiLa")
       && (sOpt!="Xi") && (sOpt!="XiNeg") && (sOpt!="XiPos")
       && (sOpt!="Omega") && (sOpt!="OmegaNeg") && (sOpt!="OmegaPos")) return;

  if (sOpt == "Kshort")  if ((fKaPtBinN<=0) || (!fKaPtBinA)) return;
  if ((sOpt == "Lambda") || (sOpt == "AntiLa"))  if ((fLaPtBinN<=0) || (!fLaPtBinA)) return;
  if ((sOpt == "Xi") || (sOpt == "XiPos") || (sOpt == "XiNeg"))  if ((fXiPtBinN<=0) || (!fXiPtBinA)) return;
  if ((sOpt == "Omega") || (sOpt == "OmegaPos") || (sOpt == "OmegaNeg"))  if ((fOmegaPtBinN<=0) || (!fOmegaPtBinA)) return;

  cout << "Analyzing inclusive " << sOpt.Data() << " loop in MC..." << endl;
//=============================================================================

  TFile *file =  TFile::Open(Form("%s.root",fFileFitInvM.Data()), "READ"); if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListFitInvM.Data()); file->Close(); if (!list) return;

  TH1D *hFitPtInvM = (TH1D*)list->FindObject("hFitPtInvM"); if (!hFitPtInvM) return;
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileLoopsMC.Data()), "UPDATE");
  list = (TList*)file->Get(fListLoopsMC.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

  TH2D *hPtInvM = 0;
  TH2D *hPtEtaI = 0;
  if (sOpt=="Kshort") {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(310 )->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fKaPtBinN, fKaPtBinA, 300, dMass-0.15, dMass+0.15);
    hPtEtaI = new TH2D("hPtEtaI", "", fKaPtBinN, fKaPtBinA, 100, -5., 5.);
  }
  if ((sOpt == "Lambda") || (sOpt == "AntiLa")) {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(3122)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fLaPtBinN, fLaPtBinA, 200, dMass-0.10, dMass+0.10);
    hPtEtaI = new TH2D("hPtEtaI", "", fLaPtBinN, fLaPtBinA, 100, -5., 5.);
  }
  if ((sOpt == "XiPos") || (sOpt == "XiNeg") || (sOpt == "Xi")) {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(3312)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fXiPtBinN, fXiPtBinA, 400, dMass-0.15, dMass+0.25);
    hPtEtaI = new TH2D("hPtEtaI", "", fXiPtBinN, fXiPtBinA, 100, -5., 5.);
  }
  if ((sOpt == "OmegaPos") || (sOpt == "OmegaNeg") || (sOpt == "Omega")) {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(3334)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fOmegaPtBinN, fOmegaPtBinA, 400, dMass-0.15, dMass+0.25);
    hPtEtaI = new TH2D("hPtEtaI", "", fOmegaPtBinN, fOmegaPtBinA, 100, -5., 5.);
  }

  hPtEtaI->Sumw2(); list->Add(hPtEtaI);
  hPtInvM->Sumw2(); list->Add(hPtInvM);

  TH1D *hCountInW = (TH1D*)hFitPtInvM->Clone("hCountInW"); hCountInW->Reset(); list->Add(hCountInW);
  TH1D *hCountInB = (TH1D*)hFitPtInvM->Clone("hCountInB"); hCountInB->Reset(); list->Add(hCountInB);

  TH2D *hPtLaXi = 0;
  TH2D *hPtGenLaXi = 0;
  if ((sOpt == "Lambda") || (sOpt == "AntiLa")) {
    hPtLaXi = new TH2D("hPtLaXi", "", fLaPtBinN, fLaPtBinA, fXiPtBinN, fXiPtBinA);
    hPtGenLaXi = new TH2D("hPtGenLaXi", "", fLaPtBinN, fLaPtBinA, fXiPtBinN, fXiPtBinA);
    hPtLaXi->Sumw2(); list->Add(hPtLaXi);
    hPtGenLaXi->Sumw2(); list->Add(hPtGenLaXi);
  }

  TH1D *hEvent = new TH1D("hEvent", "", 100, 0., 100.); hEvent->Sumw2(); list->Add(hEvent);
//=============================================================================

  Double_t dSN = fKaCutNS;
  if (sOpt == "Lambda" || sOpt == "AntiLa") dSN = fLaCutNS;
  if ((sOpt == "XiPos") || (sOpt == "XiNeg") || (sOpt == "Xi")) dSN = fXiCutNS;
  if ((sOpt == "OmegaPos") || (sOpt == "OmegaNeg") || (sOpt == "Omega")) dSN = fOmegaCutNS;

  Int_t iEvent = 0;
  
  while (fChainMC->GetEntry(iEvent++)) if (InitEvent("P")) {
   if(iEvent%1000000==0) cout<<iEvent/1000000<< " = M"<<endl;
    
   Float_t dCent = 0.;
    if (fCentralityEstimator=="V0M") dCent = fMult->GetMultiplicityPercentile("V0M");
    if (fCentralityEstimator=="V0A") dCent = fMult->GetMultiplicityPercentile("V0A");
    if (fCentralityEstimator=="CL1") dCent = fMult->GetMultiplicityPercentile("CL1");
    if (fCentralityEstimator=="ZNA") dCent = fMult->GetMultiplicityPercentile("ZNA");
    hEvent->Fill(dCent);

    Int_t nV0s = 0;
    if((sOpt == "Kshort") || (sOpt == "Lambda") || (sOpt == "AntiLa")){
      nV0s = fV0sClArr->GetEntriesFast(); if (nV0s<=0) continue;
 
      AliPicoV0MC *pV0 = 0;
      for (Int_t i=0; i<fV0sClArr->GetEntriesFast(); i++) {
        pV0 = (AliPicoV0MC*)fV0sClArr->At(i); if (!pV0) continue;
        if (sOpt == "Lambda" && pV0->IsLambdaFd() && pV0->IsMotherPhysicalPrimary()) hPtGenLaXi->Fill(pV0->KineMC().Pt(), pV0->MotherPt());
        if (sOpt == "AntiLa" && pV0->IsAntiLaFd() && pV0->IsMotherPhysicalPrimary()) hPtGenLaXi->Fill(pV0->KineMC().Pt(), pV0->MotherPt());
        if (!pV0->IsDausInEtaAcc(fV0CutMinDauEta,fV0CutMaxDauEta)) { pV0 = 0; continue; }
        if (fV0IsCutEta) { if (!pV0->IsV0InEtaAcc(fV0CutMinEta,fV0CutMaxEta)) { pV0 = 0; continue; } }
        //if (fV0IsCutRap) { if (!pV0->IsV0InRapAcc(fV0CutMinRap,fV0CutMaxRap)) { pV0 = 0; continue; } }
        Bool_t bKshort = kFALSE;
        Bool_t bLambda = kFALSE;
        Bool_t bAntiLa = kFALSE;
        if (sOpt=="Kshort") { if (fV0IsCutRap) { bKshort = pV0->IsKaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bKshort = kTRUE; } }
        if (sOpt=="Lambda") { if (fV0IsCutRap) { bLambda = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bLambda = kTRUE; } }
        if (sOpt=="AntiLa") { if (fV0IsCutRap) { bAntiLa = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bAntiLa = kTRUE; } }
        if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }
        
	if (sOpt=="Kshort") bKshort = pV0->IsKshort(fKaCuts);
        if (sOpt=="Lambda") bLambda = pV0->IsLambda(fLaCuts);
        if (sOpt=="AntiLa") bAntiLa = pV0->IsAntiLa(fLaCuts);
        if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }

        if (bKshort) pV0->FillKshortPtInvM(hPtInvM);
        if (bLambda) pV0->FillLambdaPtInvM(hPtInvM);
        if (bAntiLa) pV0->FillAntiLaPtInvM(hPtInvM);

        Double_t dPt  = pV0->KineMC().Pt();
        Double_t dEta = pV0->KineMC().Eta();
        Int_t k = hFitPtInvM->FindBin(dPt); if (k<=0) { pV0 = 0; continue; }

        if (pV0->IsV0PhysicalPrimary()) {
          Double_t dMean  = hFitPtInvM->GetBinContent(k);
          Double_t dSigma = hFitPtInvM->GetBinError(k);

          Double_t dLowerL = dMean - 2.*dSN*dSigma;
          Double_t dUpperL = dMean - 1.*dSN*dSigma;
          Double_t dLowerR = dMean + 1.*dSN*dSigma;
          Double_t dUpperR = dMean + 2.*dSN*dSigma;

          Double_t dInvM = 0.;
          if (bKshort) dInvM = pV0->KineKshort().M();
          if (bLambda) dInvM = pV0->KineLambda().M();
          if (bAntiLa) dInvM = pV0->KineAntiLa().M();

          if  ((dInvM>dUpperL) && (dInvM<dLowerR)) { hCountInW->Fill(dPt); hPtEtaI->Fill(dPt,dEta); }

          if (((dInvM>dLowerL) && (dInvM<dUpperL)) ||
              ((dInvM>dLowerR) && (dInvM<dUpperR)))  hCountInB->Fill(dPt);
        }

        if (bLambda && pV0->IsLambdaFd() && pV0->IsMotherPhysicalPrimary()) hPtLaXi->Fill(dPt, pV0->MotherPt());

        if (bAntiLa && pV0->IsAntiLaFd() && pV0->IsMotherPhysicalPrimary()) hPtLaXi->Fill(dPt, pV0->MotherPt());
        pV0 = 0;                                                                                                                                                                                                    
      }
    }
  
//=============================================================================
    Int_t nCascades = 0;
    if((sOpt=="Xi") || (sOpt=="XiPos") || (sOpt=="XiNeg") || (sOpt=="Omega") || (sOpt=="OmegaPos") || (sOpt=="OmegaNeg")){
      nCascades = fCascadesClArr->GetEntriesFast(); if (nCascades<=0) continue;
      AliPicoCascadeMC *pCascade = 0;
      for (Int_t i=0; i<nCascades; i++) {
        pCascade = (AliPicoCascadeMC*)fCascadesClArr->At(i); if (!pCascade) continue;

        auto pV0 = (AliPicoV0*)pCascade->GetV0(); if(!pV0) continue;
        if (!pV0->IsDausInEtaAcc(fCutMinTrkEta,fCutMaxTrkEta)) { pCascade = 0; continue; }
        if (!pCascade->IsBachInEtaAcc(fCutMinTrkEta,fCutMaxTrkEta)) { pCascade = 0; continue; }
        if (fCascadeIsCutEta) { if (!pCascade->IsCascadeInEtaAcc(fCascadeCutMinEta,fCascadeCutMaxEta)) { pCascade = 0; continue; } }

        auto bXiPos(kFALSE);
        auto bXiNeg(kFALSE);
        auto bXi(kFALSE);
        auto bOmegaPos(kFALSE);
        auto bOmegaNeg(kFALSE);
        auto bOmega(kFALSE);

        if (sOpt=="XiPos"){ if (fCascadeIsCutRap) { bXiPos = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else { bXiPos = kTRUE;} }
        if (sOpt=="XiNeg"){ if (fCascadeIsCutRap) { bXiNeg = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else {bXiNeg  = kTRUE;} }
        if (sOpt=="Xi")   { if (fCascadeIsCutRap) { bXi = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); }    else { bXi    = kTRUE; } }
        if (sOpt=="OmegaPos"){ if (fCascadeIsCutRap) {bOmegaPos = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else{ bOmegaPos = kTRUE;} }
        if (sOpt=="OmegaNeg"){ if (fCascadeIsCutRap) {bOmegaNeg = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else {bOmegaNeg = kTRUE;} }
        if (sOpt=="Omega")   { if (fCascadeIsCutRap) {bOmega    = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else { bOmega   = kTRUE; } }
        if (!(bXiPos || bXiNeg || bXi || bOmegaPos || bOmegaNeg || bOmega)) { pCascade = 0; continue; }

        if (bXiPos) bXiPos = pCascade->IsXiPos(fXiCuts);
        if (bXiNeg) bXiNeg = pCascade->IsXiNeg(fXiCuts);
        if (bXi) { bXi = ( pCascade->IsXiPos(fXiCuts) || pCascade->IsXiNeg(fXiCuts)); }
        if (bOmegaPos) bOmegaPos = pCascade->IsOmegaPos(fOmegaCuts);
        if (bOmegaNeg) bOmegaNeg = pCascade->IsOmegaNeg(fOmegaCuts);
        if (bOmega){ bOmega = ( pCascade-> IsOmegaPos(fOmegaCuts) || pCascade->IsOmegaNeg(fOmegaCuts)); }
        if (!(bXiPos || bXiNeg || bXi || bOmegaPos || bOmegaNeg || bOmega)) { pCascade = 0; continue; }

        if (bXiNeg) pCascade->FillXiNegPtInvM(hPtInvM);
        if (bXiPos) pCascade->FillXiPosPtInvM(hPtInvM);
        if (bXi) {pCascade->FillXiPtInvM(hPtInvM);}
        if (bOmegaNeg) pCascade->FillOmegaNegPtInvM(hPtInvM);
        if (bOmegaPos) pCascade->FillOmegaPosPtInvM(hPtInvM);
        if (bOmega) {pCascade->FillOmegaPtInvM(hPtInvM);}

        Double_t dPt = pCascade->KineMC().Pt();
        Double_t dEta  = pCascade->KineMC().Eta();
        Double_t dInvM = 0.;
        if(sOpt == "XiPos" || sOpt == "XiNeg" || sOpt == "Xi") dInvM = pCascade->KineXi().M();
        if(sOpt == "OmegaPos" || sOpt == "OmegaNeg" || sOpt == "Omega") dInvM = pCascade->KineOmega().M();

        Int_t k = hFitPtInvM->FindBin(dPt); if (k<=0) { pCascade = 0; continue; }
        if (pCascade->IsXiPhysicalPrimary()) {
          Double_t dMean  = hFitPtInvM->GetBinContent(k);
          Double_t dSigma = hFitPtInvM->GetBinError(k);

          Double_t dLowerL = dMean - 4.*dSN*dSigma;
          Double_t dUpperL = dMean - 2.*dSN*dSigma;
          Double_t dLowerR = dMean + 2.*dSN*dSigma;
          Double_t dUpperR = dMean + 4.*dSN*dSigma;
          Double_t dLowerS = dMean - 1.*dSN*dSigma;
          Double_t dUpperS = dMean + 1.*dSN*dSigma;

          if  ((dInvM>dLowerS) && (dInvM<dUpperS))  { hCountInW->Fill(dPt); hPtEtaI->Fill(dPt, dEta); }
          if (((dInvM>dLowerL) && (dInvM<dUpperL)) || ((dInvM>dLowerR) && (dInvM<dUpperR)))   hCountInB->Fill(dPt);

        }
        pCascade = 0;
      }
    }
  }
//=============================================================================

  file->cd(); list->Write(fListLoopsMC.Data(), TObject::kSingleKey); file->Close();
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaLoopJet(const TString sOpt, const TString sJet, const TString sRef)
{
//
//  AliAnalysisTaskUserStraneJets::AnaLoopJet
//

  if (sJet.IsNull()) return;
  if (fFileFitInvM.IsNull() || fListFitInvM.IsNull()) return;
  if (fFileLoop2nd.IsNull() || fListLoop2nd.IsNull()) return;
  if (fFileLoopJet.IsNull() || fListLoopJet.IsNull()) return;

  if ((sOpt!="Kshort") && (sOpt!="Lambda") && (sOpt!="AntiLa")
       && (sOpt!="Xi") && (sOpt!="XiNeg") && (sOpt!="XiPos")
       && (sOpt!="Omega") && (sOpt!="OmegaNeg") && (sOpt!="OmegaPos")) return;

  if (sOpt == "Kshort")  if ((fKaPtBinN<=0) || (!fKaPtBinA)) return;
  if ((sOpt == "Lambda") || (sOpt == "AntiLa"))  if ((fLaPtBinN<=0) || (!fLaPtBinA)) return;
  if ((sOpt == "Xi") || (sOpt == "XiPos") || (sOpt == "XiNeg"))  if ((fXiPtBinN<=0) || (!fXiPtBinA)) return;
  if ((sOpt == "Omega") || (sOpt == "OmegaPos") || (sOpt == "OmegaNeg"))  if ((fOmegaPtBinN<=0) || (!fOmegaPtBinA)) return;
  
  cout << "Analyzing " << sOpt.Data() << " in jets " << sJet.Data();
  if (!sRef.Contains("00")) cout << " w/ refs " << sRef.Data(); cout << "..." << endl;
//=============================================================================

  TFile *file =  TFile::Open(Form("%s.root",fFileFitInvM.Data()), "READ"); if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListFitInvM.Data()); file->Close(); if (!list) return;

  TH1D *hFitPtInvM = (TH1D*)list->FindObject("hFitPtInvM"); if (!hFitPtInvM) return;
//=============================================================================

  file =  TFile::Open(Form("%s.root",fFileLoop2nd.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListLoop2nd.Data()); file->Close(); if (!list) return;

  TH2D *hPtEtaI = (TH2D*)list->FindObject("hPtEtaI"); if (!hPtEtaI) return;
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileLoopJet.Data()), "UPDATE");
  list = (TList*)file->Get(fListLoopJet.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

  TH2D *hPtInvM = 0;
  TH2D *hPtEtaJ = 0;
  Double_t dMass = 0.;
  if (sOpt=="Kshort") {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(310)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fKaPtBinN, fKaPtBinA, 300, dMass-0.15, dMass+0.15);
    hPtEtaJ = new TH2D("hPtEtaJ", "", fKaPtBinN, fKaPtBinA, 100, -5., 5.);
  }
  if ((sOpt == "Lambda") || (sOpt == "AntiLa")) {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(3122)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fLaPtBinN, fLaPtBinA, 200, dMass-0.10, dMass+0.10);
    hPtEtaJ = new TH2D("hPtEtaJ", "", fLaPtBinN, fLaPtBinA, 100, -5., 5.);
  }
  if ((sOpt == "XiPos") || (sOpt == "XiNeg") || (sOpt == "Xi")) {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(3312)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fXiPtBinN, fXiPtBinA, 400, dMass-0.15, dMass+0.25);
    hPtEtaJ = new TH2D("hPtEtaJ", "", fXiPtBinN, fXiPtBinA, 100, -5., 5.);
  }
  if ((sOpt == "OmegaPos") || (sOpt == "OmegaNeg") || (sOpt == "Omega")) {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(3334)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fOmegaPtBinN, fOmegaPtBinA, 400, dMass-0.15, dMass+0.25);
    hPtEtaJ = new TH2D("hPtEtaJ", "", fOmegaPtBinN, fOmegaPtBinA, 100, -5., 5.);
  }

  list->Add(hPtEtaI);
  hPtEtaJ->Sumw2(); list->Add(hPtEtaJ);
  hPtInvM->Sumw2(); list->Add(hPtInvM);

  TH1D *hCountInW = (TH1D*)hFitPtInvM->Clone("hCountInW"); hCountInW->Reset(); list->Add(hCountInW);
  TH1D *hCountInB = (TH1D*)hFitPtInvM->Clone("hCountInB"); hCountInB->Reset(); list->Add(hCountInB);

  TH1D *hEvent = new TH1D("hEvent", "", 100, 0., 100.); hEvent->Sumw2(); list->Add(hEvent);

  TProfile *hProfAcc = new TProfile("hProfAcc", "", 3, -0.5, 2.5); list->Add(hProfAcc);
//=============================================================================
  //TH1D *hJetPtBefore   = new TH1D("hJetPtBefore", "", 10000, -10., 100.);hJetPtBefore->Sumw2(); list->Add(hJetPtBefore);
  //TH1D *hJetPtAfter    = new TH1D("hJetPtAfter", "", 10000, -10., 100.);  hJetPtAfter->Sumw2(); list->Add(hJetPtAfter);
  //TH1D *hJetEta        = new TH1D("hJetEta", "", 100, -5., 5.);         hJetEta ->Sumw2();     list->Add(hJetEta);
  //TH1D *hJetPhi        = new TH1D("hJetPhi", "", 200, -7., 7.);         hJetPhi ->Sumw2();     list->Add(hJetPhi);
  //TH1D *hJetArea       = new TH1D("hJetArea", "", 100, 0., 1.);         hJetArea->Sumw2();     list->Add(hJetArea);
  //TH1D *hJetLeadTrkPt  = new TH1D("hJetLeadTrkPt", "", 300, 0., 30.);   hJetLeadTrkPt->Sumw2();list->Add(hJetLeadTrkPt);
  //TH2D *hCentRho  = new TH2D("CentRho", "", 100, 0., 100., 1000, 0., 100.); hCentRho->Sumw2();list->Add(hCentRho);

  Double_t dSN = fKaCutNS;
  if (sOpt == "Lambda" || sOpt == "AntiLa") dSN = fLaCutNS;
  if ((sOpt == "XiPos") || (sOpt == "XiNeg") || (sOpt == "Xi")) dSN = fXiCutNS;
  if ((sOpt == "OmegaPos") || (sOpt == "OmegaNeg") || (sOpt == "Omega")) dSN = fOmegaCutNS;

  TRandom3 rdm3(0);
  Int_t iEvent = 0;
  TClonesArray *pJetsClArr = 0;
  TClonesArray *pRefsClArr = 0;
  const Bool_t bR = (!sRef.Contains("00"));

  while (fChainRD->GetEntry(iEvent++)) if (InitEvent("PJ")) {
    if(iEvent%1000000==0) cout<<"event = "<<iEvent/1000000<<"M"<<endl; 

    pJetsClArr = GetJets(sJet);
    Int_t nJets=pJetsClArr->GetEntriesFast();
    if(pJetsClArr->GetEntriesFast()  <=  0){pJetsClArr = 0; continue;}
    if(IsJetNotInMultRange(pJetsClArr,sJet)){pJetsClArr = 0; continue;}

    Float_t dCent = 0.;
    if (fCentralityEstimator=="V0M") dCent = fMult->GetMultiplicityPercentile("V0M");
    if (fCentralityEstimator=="V0A") dCent = fMult->GetMultiplicityPercentile("V0A");
    if (fCentralityEstimator=="CL1") dCent = fMult->GetMultiplicityPercentile("CL1");
    if (fCentralityEstimator=="ZNA") dCent = fMult->GetMultiplicityPercentile("ZNA");
    hEvent->Fill(dCent);

    AliPicoJet *pJet = 0;
    //hCentRho->Fill(dCent, fHeader->BackgroundRho());

    //for (Int_t j=0; j<nJets; j++) {
    //  pJet = (AliPicoJet*)pJetsClArr->At(j); if (!pJet) continue;
    //  Double_t dPt = pJet->Kine().Pt();
    //  hJetPtBefore->Fill(dPt);
    //  dPt -= (pJet->Area() * fHeader->BackgroundRho());
    //  if (IsJetNotSelected(pJet,sJet)) {  pJet = 0; continue; }
    //  hJetPtAfter->Fill(dPt);
    //  Double_t dEta = pJet->Kine().Eta();
    //  Double_t dPhi = pJet->Kine().Phi();
    //  Double_t dArea=pJet->Area();
    //  hJetEta->Fill(dEta);
    //  hJetPhi->Fill(dPhi);
    //  hJetArea->Fill(dArea);
    //  Double_t dLeadTrkPt=pJet->LeadingPt();
    //  hJetLeadTrkPt->Fill(dLeadTrkPt);
    //}
//=============================================================================
    if (bR) {
      pRefsClArr = GetJets(sRef);
      if (pRefsClArr->GetEntriesFast()  <=  0)  { pRefsClArr = 0; pJetsClArr = 0; continue; }
      if (IsRefNotInMultRange(pRefsClArr,sRef)) { pRefsClArr = 0; pJetsClArr = 0; continue; }

      pJetsClArr = 0;
      pJetsClArr = GetJets(sJet,sRef);
      if (pJetsClArr->GetEntriesFast()  <=  0)  { pJetsClArr->Delete(); delete pJetsClArr; pJetsClArr = 0; pRefsClArr = 0; continue; }
      if (IsJetNotInMultRange(pJetsClArr,sJet)) { pJetsClArr->Delete(); delete pJetsClArr; pJetsClArr = 0; pRefsClArr = 0; continue; }
    }
//=============================================================================
//    Float_t dCent = 0.;
//=============================================================================

    Int_t nV0s = 0;
    if((sOpt == "Kshort") || (sOpt == "Lambda") || (sOpt == "AntiLa")){
      nV0s = fV0sClArr->GetEntriesFast(); if (nV0s<=0) continue;
      AliPicoV0RD *pV0 = 0;
      for (Int_t i=0; i<nV0s; i++) {
        pV0 = (AliPicoV0RD*)fV0sClArr->At(i); if (!pV0) continue;
        if (!pV0->IsDausInEtaAcc(fV0CutMinDauEta,fV0CutMaxDauEta)) { pV0 = 0; continue; }
        if (fV0IsCutEta) { if (!pV0->IsV0InEtaAcc(fV0CutMinEta,fV0CutMaxEta)) { pV0 = 0; continue; } }
//===============================================================================

        Bool_t bKshort = kFALSE;
        Bool_t bLambda = kFALSE;
        Bool_t bAntiLa = kFALSE;
        if (sOpt=="Kshort") { if (fV0IsCutRap) { bKshort = pV0->IsKaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bKshort = kTRUE; } }
        if (sOpt=="Lambda") { if (fV0IsCutRap) { bLambda = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bLambda = kTRUE; } }
        if (sOpt=="AntiLa") { if (fV0IsCutRap) { bAntiLa = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bAntiLa = kTRUE; } }
        if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }
//===============================================================================

        if (bKshort) bKshort = pV0->IsKshort(fKaCuts);
        if (bLambda) bLambda = pV0->IsLambda(fLaCuts);
        if (bAntiLa) bAntiLa = pV0->IsAntiLa(fLaCuts);
        if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }
//===============================================================================

        if (IsStrangeInJetRange(pV0->KineRD(),pJetsClArr,sJet)) {
          if (!fIsStrangeInJet) { pV0 = 0; continue; }
        } else {
          if  (fIsStrangeInJet) { pV0 = 0; continue; }
        }
//===============================================================================
        TLorentzVector vV0;
        if (bKshort) vV0 = pV0->KineKshort();
        if (bLambda) vV0 = pV0->KineLambda();
        if (bAntiLa) vV0 = pV0->KineAntiLa();

        Double_t dPt   = vV0.Pt();
        Double_t dEta  = vV0.Eta();
        Double_t dInvM = vV0.M();
        Int_t k = hFitPtInvM->FindBin(dPt); if (k<=0) { pV0 = 0; continue; }

        Double_t dMean  = hFitPtInvM->GetBinContent(k);
        Double_t dSigma = hFitPtInvM->GetBinError(k);

        Double_t dLowerL = dMean - 2.*dSN*dSigma;
        Double_t dUpperL = dMean - 1.*dSN*dSigma;
        Double_t dLowerR = dMean + 1.*dSN*dSigma;
        Double_t dUpperR = dMean + 2.*dSN*dSigma;

        if (bKshort) pV0->FillKshortPtInvM(hPtInvM);
        if (bLambda) pV0->FillLambdaPtInvM(hPtInvM);
        if (bAntiLa) pV0->FillAntiLaPtInvM(hPtInvM);

        if  ((dInvM>dUpperL) && (dInvM<dLowerR)) { hCountInW->Fill(dPt); hPtEtaJ->Fill(dPt,dEta); }

        if (((dInvM>dLowerL) && (dInvM<dUpperL)) || ((dInvM>dLowerR) && (dInvM<dUpperR)))  hCountInB->Fill(dPt);

        pV0 = 0;
      }
    }

//=============================================================================
    Int_t nCascades = 0;
    if((sOpt=="Xi") || (sOpt=="XiPos") || (sOpt=="XiNeg") || (sOpt=="Omega") || (sOpt=="OmegaPos") || (sOpt=="OmegaNeg")){
      nCascades = fCascadesClArr->GetEntriesFast(); if (nCascades<=0) continue;
      AliPicoCascadeRD *pCascade = nullptr;
      for (Int_t i=0; i<nCascades; i++) {
        pCascade = (AliPicoCascadeRD*)fCascadesClArr->At(i); if (!pCascade) continue;
        auto pV0 = (AliPicoV0*)pCascade->GetV0(); if(!pV0) continue;
        if (!pV0->IsDausInEtaAcc(fCutMinTrkEta,fCutMaxTrkEta)) { pCascade = 0; continue; }
        if (!pCascade->IsBachInEtaAcc(fCutMinTrkEta,fCutMaxTrkEta)) { pCascade = 0; continue; }
        if (fCascadeIsCutEta) { if (!pCascade->IsCascadeInEtaAcc(fCascadeCutMinEta,fCascadeCutMaxEta)) { pCascade = 0; continue; } }

        auto bXiPos(kFALSE);
        auto bXiNeg(kFALSE);
        auto bXi(kFALSE);
        auto bOmegaPos(kFALSE);
        auto bOmegaNeg(kFALSE);
        auto bOmega(kFALSE);

        if (sOpt=="XiPos"){ if (fCascadeIsCutRap) { bXiPos = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else { bXiPos = kTRUE;} }
        if (sOpt=="XiNeg"){ if (fCascadeIsCutRap) { bXiNeg = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else {bXiNeg  = kTRUE;} }
        if (sOpt=="Xi")   { if (fCascadeIsCutRap) { bXi = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); }    else { bXi    = kTRUE; } }
        if (sOpt=="OmegaPos"){ if (fCascadeIsCutRap) {bOmegaPos = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else{ bOmegaPos = kTRUE;} }
        if (sOpt=="OmegaNeg"){ if (fCascadeIsCutRap) {bOmegaNeg = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else {bOmegaNeg = kTRUE;} }
        if (sOpt=="Omega")   { if (fCascadeIsCutRap) {bOmega    = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else { bOmega   = kTRUE; } }
        if (!(bXiPos || bXiNeg || bXi || bOmegaPos || bOmegaNeg || bOmega)) { pCascade = 0; continue; }

        if (bXiPos) bXiPos = pCascade->IsXiPos(fXiCuts);
        if (bXiNeg) bXiNeg = pCascade->IsXiNeg(fXiCuts);
        if (bXi) { bXi = ( pCascade->IsXiPos(fXiCuts) || pCascade->IsXiNeg(fXiCuts)); }
        if (bOmegaPos) bOmegaPos = pCascade->IsOmegaPos(fOmegaCuts);
        if (bOmegaNeg) bOmegaNeg = pCascade->IsOmegaNeg(fOmegaCuts);
        if (bOmega){ bOmega = ( pCascade-> IsOmegaPos(fOmegaCuts) || pCascade->IsOmegaNeg(fOmegaCuts)); }
        if (!(bXiPos || bXiNeg || bXi || bOmegaPos || bOmegaNeg || bOmega)) { pCascade = 0; continue; }

//=============================================================================
        TLorentzVector vCascade;
        if(bXiPos || bXiNeg || bXi) vCascade = pCascade->KineXi();
        if(bOmegaPos || bOmegaNeg || bOmega) vCascade = pCascade->KineOmega();
     
        if (IsStrangeInJetRange(pCascade->KineRD(),pJetsClArr,sJet)) {
          if (!fIsStrangeInJet) { pCascade = 0; continue; }
        } else {
          if  (fIsStrangeInJet) { pCascade = 0; continue; }
        }
//=============================================================================

        Double_t dPt   = vCascade.Pt();
        Double_t dEta  = vCascade.Eta();
        Double_t dInvM = vCascade.M();
        Int_t k = hFitPtInvM->FindBin(dPt); if (k<=0) { pCascade = 0; continue; }

        Double_t dMean  = hFitPtInvM->GetBinContent(k);
        Double_t dSigma = hFitPtInvM->GetBinError(k);

	Double_t dLowerL = dMean - 4.*dSN*dSigma;
        Double_t dUpperL = dMean - 2.*dSN*dSigma;
        Double_t dLowerR = dMean + 2.*dSN*dSigma;
        Double_t dUpperR = dMean + 4.*dSN*dSigma;
        Double_t dLowerS = dMean - 1.*dSN*dSigma;
        Double_t dUpperS = dMean + 1.*dSN*dSigma;


        if (bXiNeg) pCascade->FillXiNegPtInvM(hPtInvM);
        if (bXiPos) pCascade->FillXiPosPtInvM(hPtInvM);
        if (bXi) {pCascade->FillXiPtInvM(hPtInvM);}
        if (bOmegaNeg) pCascade->FillOmegaNegPtInvM(hPtInvM);
        if (bOmegaPos) pCascade->FillOmegaPosPtInvM(hPtInvM);
        if (bOmega) {pCascade->FillOmegaPtInvM(hPtInvM);}

        if  ((dInvM>dLowerS) && (dInvM<dUpperS))  { hCountInW->Fill(dPt); hPtEtaJ->Fill(dPt, dEta); }
        if (((dInvM>dLowerL) && (dInvM<dUpperL)) || ((dInvM>dLowerR) && (dInvM<dUpperR)))   hCountInB->Fill(dPt);

        pCascade = 0;
      }
    }
 //=============================================================================

    TVector3 v3;
    Double_t dAll = 0.;
    Double_t dInC = 0.;
    Double_t dOut = 0.;
    const Int_t ns = 1000;
    for (Int_t i=0; i<ns; i++) {
      Double_t dPt=0., dEta=0.; hPtEtaI->GetRandom2(dPt,dEta);
      v3.SetPtEtaPhi(dPt, dEta, rdm3.Uniform(0.,TMath::TwoPi()));
      if (IsStrangeInJetRange(v3,pJetsClArr,sJet)) { dInC += 1.; } else { dOut += 1.; } dAll += 1.;
    }

    hProfAcc->Fill(0., dAll);
    hProfAcc->Fill(1., dOut);
    hProfAcc->Fill(2., dInC);

//=============================================================================

    if (bR) {
      pJetsClArr->Delete(); delete pJetsClArr; pJetsClArr = 0; pRefsClArr = 0;
    } else {
      pJetsClArr = 0;
    }
  }
//=============================================================================

  file->cd(); list->Write(fListLoopJet.Data(), TObject::kSingleKey); file->Close();
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaLoopNJ(const TString sOpt, const TString sJet, const TString sRef)
{
//
//  AliAnalysisTaskUserStraneJets::AnaLoopNJ
//

  if (sJet.IsNull()) return;
  if (fFileFitInvM.IsNull() || fListFitInvM.IsNull()) return;
  if (fFileLoop2nd.IsNull() || fListLoop2nd.IsNull()) return;
  if (fFileLoopJet.IsNull() || fListLoopJet.IsNull()) return;

  if ((sOpt!="Kshort") && (sOpt!="Lambda") && (sOpt!="AntiLa")
       && (sOpt!="Xi") && (sOpt!="XiNeg") && (sOpt!="XiPos")
       && (sOpt!="Omega") && (sOpt!="OmegaNeg") && (sOpt!="OmegaPos")) return;

  if (sOpt == "Kshort")  if ((fKaPtBinN<=0) || (!fKaPtBinA)) return;
  if ((sOpt == "Lambda") || (sOpt == "AntiLa"))  if ((fLaPtBinN<=0) || (!fLaPtBinA)) return;
  if ((sOpt == "Xi") || (sOpt == "XiPos") || (sOpt == "XiNeg"))  if ((fXiPtBinN<=0) || (!fXiPtBinA)) return;
  if ((sOpt == "Omega") || (sOpt == "OmegaPos") || (sOpt == "OmegaNeg"))  if ((fOmegaPtBinN<=0) || (!fOmegaPtBinA)) return;

  cout << "Analyzing " << sOpt.Data() << " in jets " << sJet.Data();
  if (!sRef.Contains("00")) cout << " w/ refs " << sRef.Data(); cout << "..." << endl;
//=============================================================================

  TFile *file =  TFile::Open(Form("%s.root",fFileFitInvM.Data()), "READ"); if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListFitInvM.Data()); file->Close(); if (!list) return;

  TH1D *hFitPtInvM = (TH1D*)list->FindObject("hFitPtInvM"); if (!hFitPtInvM) return;
//=============================================================================

  file =  TFile::Open(Form("%s.root",fFileLoop2nd.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListLoop2nd.Data()); file->Close(); if (!list) return;

  TH2D *hPtEtaI = (TH2D*)list->FindObject("hPtEtaI"); if (!hPtEtaI) return;
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileLoopJet.Data()), "UPDATE");
  list = (TList*)file->Get(fListLoopJet.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

  TH2D *hPtInvM = 0;
  TH2D *hPtEtaJ = 0;
  Double_t dMass = 0.;
  if (sOpt=="Kshort") {
    dMass = TDatabasePDG::Instance()->GetParticle(310 )->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fKaPtBinN, fKaPtBinA, 300, dMass-0.15, dMass+0.15);
    hPtEtaJ = new TH2D("hPtEtaJ", "", fKaPtBinN, fKaPtBinA, 100, -5., 5.);
  }
  if ((sOpt == "Lambda") || (sOpt == "AntiLa")) {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(3122)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fLaPtBinN, fLaPtBinA, 200, dMass-0.10, dMass+0.10);
    hPtEtaJ = new TH2D("hPtEtaJ", "", fLaPtBinN, fLaPtBinA, 100, -5., 5.);
  }
  if ((sOpt == "XiPos") || (sOpt == "XiNeg") || (sOpt == "Xi")) {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(3312)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fXiPtBinN, fXiPtBinA, 400, dMass-0.15, dMass+0.25);
    hPtEtaJ = new TH2D("hPtEtaJ", "", fXiPtBinN, fXiPtBinA, 100, -5., 5.);
  }
  if ((sOpt == "OmegaPos") || (sOpt == "OmegaNeg") || (sOpt == "Omega")) {
    Double_t dMass = TDatabasePDG::Instance()->GetParticle(3334)->Mass();
    hPtInvM = new TH2D("hPtInvM", "", fOmegaPtBinN, fOmegaPtBinA, 400, dMass-0.15, dMass+0.25);
    hPtEtaJ = new TH2D("hPtEtaJ", "", fOmegaPtBinN, fOmegaPtBinA, 100, -5., 5.);
  }

  list->Add(hPtEtaI);
  hPtEtaJ->Sumw2(); list->Add(hPtEtaJ);
  hPtInvM->Sumw2(); list->Add(hPtInvM);

  TH1D *hCountInW = (TH1D*)hFitPtInvM->Clone("hCountInW"); hCountInW->Reset(); list->Add(hCountInW);
  TH1D *hCountInB = (TH1D*)hFitPtInvM->Clone("hCountInB"); hCountInB->Reset(); list->Add(hCountInB);

  TH1D *hEvent = new TH1D("hEvent", "", 100, 0., 100.); hEvent->Sumw2(); list->Add(hEvent);

  TProfile *hProfAcc = new TProfile("hProfAcc", "", 3, -0.5, 2.5); list->Add(hProfAcc);
//=============================================================================

  Double_t dSN = fKaCutNS;
  if (sOpt == "Lambda" || sOpt == "AntiLa") dSN = fLaCutNS;
  if ((sOpt == "XiPos") || (sOpt == "XiNeg") || (sOpt == "Xi")) dSN = fXiCutNS;
  if ((sOpt == "OmegaPos") || (sOpt == "OmegaNeg") || (sOpt == "Omega")) dSN = fOmegaCutNS;

  TRandom3 rdm3(0);
  Int_t iEvent = 0;
  TClonesArray *pJetsClArr = 0;
  TClonesArray *pRefsClArr = 0;
  const Bool_t bR = (!sRef.Contains("00"));

  while (fChainRD->GetEntry(iEvent++)) if (InitEvent("PJ")) {
    if(iEvent%1000000==0) cout<<"event = "<<iEvent/1000000<<"M"<<endl; 

//=============================================================================
    pJetsClArr = GetJets(sJet);
    Int_t nJets=pJetsClArr->GetEntriesFast();
    
    if((pJetsClArr->GetEntriesFast()  >  0) && !IsJetNotInMultRange(pJetsClArr,sJet)){pJetsClArr = 0; continue;}
    Float_t dCent = 0.;
    if (fCentralityEstimator=="V0M") dCent = fMult->GetMultiplicityPercentile("V0M");
    if (fCentralityEstimator=="V0A") dCent = fMult->GetMultiplicityPercentile("V0A");
    if (fCentralityEstimator=="CL1") dCent = fMult->GetMultiplicityPercentile("CL1");
    if (fCentralityEstimator=="ZNA") dCent = fMult->GetMultiplicityPercentile("ZNA");
    hEvent->Fill(dCent);

//=============================================================================
//    Float_t dCent = 0.;
//=============================================================================
    Int_t nV0s = 0;
    if((sOpt == "Kshort") || (sOpt == "Lambda") || (sOpt == "AntiLa")){
      nV0s = fV0sClArr->GetEntriesFast(); if (nV0s<=0) continue;
      
      AliPicoV0RD *pV0 = 0;
      for (Int_t i=0; i<nV0s; i++) {
        pV0 = (AliPicoV0RD*)fV0sClArr->At(i); if (!pV0) continue;
        if (!pV0->IsDausInEtaAcc(fV0CutMinDauEta,fV0CutMaxDauEta)) { pV0 = 0; continue; }
        if (fV0IsCutEta) { if (!pV0->IsV0InEtaAcc(fV0CutMinEta,fV0CutMaxEta)) { pV0 = 0; continue; } }

        Bool_t bKshort = kFALSE;
        Bool_t bLambda = kFALSE;
        Bool_t bAntiLa = kFALSE;
        if (sOpt=="Kshort") { if (fV0IsCutRap) { bKshort = pV0->IsKaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bKshort = kTRUE; } }
        if (sOpt=="Lambda") { if (fV0IsCutRap) { bLambda = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bLambda = kTRUE; } }
        if (sOpt=="AntiLa") { if (fV0IsCutRap) { bAntiLa = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bAntiLa = kTRUE; } }
        if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }
//=============================================================================
  
        if (bKshort) bKshort = pV0->IsKshort(fKaCuts);
        if (bLambda) bLambda = pV0->IsLambda(fLaCuts);
        if (bAntiLa) bAntiLa = pV0->IsAntiLa(fLaCuts);
        if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }
//=============================================================================
        TLorentzVector vV0;
        if (bKshort) vV0 = pV0->KineKshort();
        if (bLambda) vV0 = pV0->KineLambda();
        if (bAntiLa) vV0 = pV0->KineAntiLa();

        Double_t dPt   = vV0.Pt();
        Double_t dEta  = vV0.Eta();
        Double_t dInvM = vV0.M();
        Int_t k = hFitPtInvM->FindBin(dPt); if (k<=0) { pV0 = 0; continue; }

        Double_t dMean  = hFitPtInvM->GetBinContent(k);
        Double_t dSigma = hFitPtInvM->GetBinError(k);

        Double_t dLowerL = dMean - 2.*dSN*dSigma;
        Double_t dUpperL = dMean - 1.*dSN*dSigma;
        Double_t dLowerR = dMean + 1.*dSN*dSigma;
        Double_t dUpperR = dMean + 2.*dSN*dSigma;

        if (bKshort) pV0->FillKshortPtInvM(hPtInvM);
        if (bLambda) pV0->FillLambdaPtInvM(hPtInvM);
        if (bAntiLa) pV0->FillAntiLaPtInvM(hPtInvM);

        if  ((dInvM>dUpperL) && (dInvM<dLowerR)) { hCountInW->Fill(dPt); hPtEtaJ->Fill(dPt,dEta); }

        if (((dInvM>dLowerL) && (dInvM<dUpperL)) ||
            ((dInvM>dLowerR) && (dInvM<dUpperR)))  hCountInB->Fill(dPt);

        pV0 = 0;
      }
    }
  
//=============================================================================
    Int_t nCascades = 0;
    if((sOpt=="Xi") || (sOpt=="XiPos") || (sOpt=="XiNeg") || (sOpt=="Omega") || (sOpt=="OmegaPos") || (sOpt=="OmegaNeg")){
      nCascades = fCascadesClArr->GetEntriesFast(); if (nCascades<=0) continue;
      AliPicoCascadeRD *pCascade = nullptr;
      for (Int_t i=0; i<nCascades; i++) {

        pCascade = (AliPicoCascadeRD*)fCascadesClArr->At(i); if (!pCascade) continue;

        auto pV0 = (AliPicoV0*)pCascade->GetV0(); if(!pV0) continue;
        if (!pV0->IsDausInEtaAcc(fCutMinTrkEta,fCutMaxTrkEta)) { pCascade = 0; continue; }
        if (!pCascade->IsBachInEtaAcc(fCutMinTrkEta,fCutMaxTrkEta)) { pCascade = 0; continue; }
        if (fCascadeIsCutEta) { if (!pCascade->IsCascadeInEtaAcc(fCascadeCutMinEta,fCascadeCutMaxEta)) { pCascade = 0; continue; } }

        auto bXiPos(kFALSE);
        auto bXiNeg(kFALSE);
        auto bXi(kFALSE);
        auto bOmegaPos(kFALSE);
        auto bOmegaNeg(kFALSE);
        auto bOmega(kFALSE);

        if (sOpt=="XiPos"){ if (fCascadeIsCutRap) { bXiPos = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else { bXiPos = kTRUE;} }
        if (sOpt=="XiNeg"){ if (fCascadeIsCutRap) { bXiNeg = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else {bXiNeg  = kTRUE;} }
        if (sOpt=="Xi")   { if (fCascadeIsCutRap) { bXi = pCascade->IsXiInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); }    else { bXi    = kTRUE; } }
        if (sOpt=="OmegaPos"){ if (fCascadeIsCutRap) {bOmegaPos = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else{ bOmegaPos = kTRUE;} }
        if (sOpt=="OmegaNeg"){ if (fCascadeIsCutRap) {bOmegaNeg = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else {bOmegaNeg = kTRUE;} }
        if (sOpt=="Omega")   { if (fCascadeIsCutRap) {bOmega    = pCascade->IsOmegaInRapAcc(fCascadeCutMinRap,fCascadeCutMaxRap); } else { bOmega   = kTRUE; } }
        if (!(bXiPos || bXiNeg || bXi || bOmegaPos || bOmegaNeg || bOmega)) { pCascade = 0; continue; }

        if (bXiPos) bXiPos = pCascade->IsXiPos(fXiCuts);
        if (bXiNeg) bXiNeg = pCascade->IsXiNeg(fXiCuts);
        if (bXi) { bXi = ( pCascade->IsXiPos(fXiCuts) || pCascade->IsXiNeg(fXiCuts)); }
        if (bOmegaPos) bOmegaPos = pCascade->IsOmegaPos(fOmegaCuts);
        if (bOmegaNeg) bOmegaNeg = pCascade->IsOmegaNeg(fOmegaCuts);
        if (bOmega){ bOmega = ( pCascade-> IsOmegaPos(fOmegaCuts) || pCascade->IsOmegaNeg(fOmegaCuts)); }
        if (!(bXiPos || bXiNeg || bXi || bOmegaPos || bOmegaNeg || bOmega)) { pCascade = 0; continue; }
//=============================================================================
        TLorentzVector vCascade;
        if(bXiPos || bXiNeg || bXi) vCascade = pCascade->KineXi();
        if(bOmegaPos || bOmegaNeg || bOmega) vCascade = pCascade->KineOmega();

        Double_t dPt   = vCascade.Pt();
        Double_t dEta  = vCascade.Eta();
        Double_t dInvM = vCascade.M();
        Int_t k = hFitPtInvM->FindBin(dPt); if (k<=0) { pCascade = 0; continue; }

        Double_t dMean  = hFitPtInvM->GetBinContent(k);
        Double_t dSigma = hFitPtInvM->GetBinError(k);
       
       	Double_t dLowerL = dMean - 4.*dSN*dSigma;
        Double_t dUpperL = dMean - 2.*dSN*dSigma;
        Double_t dLowerR = dMean + 2.*dSN*dSigma;
        Double_t dUpperR = dMean + 4.*dSN*dSigma;
        Double_t dLowerS = dMean - 1.*dSN*dSigma;
        Double_t dUpperS = dMean + 1.*dSN*dSigma;

        if (bXiNeg) pCascade->FillXiNegPtInvM(hPtInvM);
        if (bXiPos) pCascade->FillXiPosPtInvM(hPtInvM);
        if (bXi) {pCascade->FillXiPtInvM(hPtInvM);}
        if (bOmegaNeg) pCascade->FillOmegaNegPtInvM(hPtInvM);
        if (bOmegaPos) pCascade->FillOmegaPosPtInvM(hPtInvM);
        if (bOmega) {pCascade->FillOmegaNegPtInvM(hPtInvM);}

        if  ((dInvM>dLowerS) && (dInvM<dUpperS))  { hCountInW->Fill(dPt); hPtEtaJ->Fill(dPt, dEta); }
        if (((dInvM>dLowerL) && (dInvM<dUpperL)) || ((dInvM>dLowerR) && (dInvM<dUpperR)))   hCountInB->Fill(dPt);
        pCascade = 0;
      }
    }
  }
//=============================================================================
  file->cd(); list->Write(fListLoopJet.Data(), TObject::kSingleKey); file->Close();
  return;
}

//=============================================================================
void AliAnalysisTaskUserStraneJets::AnaFitInvM(const TString sOpt, const Bool_t bIsMC)
{
//
//  AliAnalysisTaskUserStraneJets::AnaFitInvM
//

  if (fFileLoop1st.IsNull() || fListLoop1st.IsNull()) return;
  if (fFileFitInvM.IsNull() || fListFitInvM.IsNull()) return;

  if ((sOpt!="Kshort") && (sOpt!="Lambda") && (sOpt!="AntiLa")
       && (sOpt!="Xi") && (sOpt!="XiNeg") && (sOpt!="XiPos")
       && (sOpt!="Omega") && (sOpt!="OmegaNeg") && (sOpt!="OmegaPos")) return;

  cout << "Fit " << sOpt.Data() << " InvM..." << endl;
//=============================================================================

  TFile *file =  TFile::Open(Form("%s.root",fFileLoop1st.Data()), "READ"); if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListLoop1st.Data()); file->Close(); if (!list) return;

  TH2D *hPtInvM = (TH2D*)list->FindObject("hPtInvM"); if (!hPtInvM) return;
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileFitInvM.Data()), "UPDATE");
  list = (TList*)file->Get(fListFitInvM.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

  TH1D *hPt = hPtInvM->ProjectionX("hPt");    list->Add(hPt);
  TProfile *hProfPtInvM = hPtInvM->ProfileX("hProfInvM"); list->Add(hProfPtInvM);

  TH1D *hFitPtInvM = (TH1D*)hPt->Clone("hFitPtInvM"); hFitPtInvM->Reset(); list->Add(hFitPtInvM);
//=============================================================================

  //TF1 *fLower = 0;
  //TF1 *fUpper = 0;
  Double_t dXmin  = 0.;
  Double_t dXmax  = 0.;
  Double_t dMass  = 0.;
  Double_t dWidth = 0.;
  if (sOpt=="Kshort") {
    //fLower = new TF1("fLower", "[0]+[1]*x", 0., 100.);
    //fUpper = new TF1("fUpper", "[0]+[1]*x", 0., 100.);

    //fLower->SetParameter(0,  4.30006e-01);
    //fLower->SetParameter(1, -1.10029e-02);

    //fUpper->SetParameter(0,  5.63707e-01);
    //fUpper->SetParameter(1,  1.14979e-02);

    dWidth = 0.004;
    dMass  = TDatabasePDG::Instance()->GetParticle(310 )->Mass();

    dXmin  = dMass - 0.05;
    dXmax  = dMass + 0.05;
  } 
  if((sOpt == "Lambda") || (sOpt == "AntiLa")) {
    //fLower = new TF1("fLower", "[0]+[1]*x+[2]*TMath::Exp([3]*x)", 0., 100.);
    //fUpper = new TF1("fUpper", "[0]+[1]*x+[2]*TMath::Exp([3]*x)", 0., 100.);

    //fLower->SetParameter(0,  1.09501e+00);
    //fLower->SetParameter(1, -5.23272e-03);
    //fLower->SetParameter(2, -7.52690e-02);
    //fLower->SetParameter(3, -3.46339e+00);

    //fUpper->SetParameter(0,  1.13688e+00);
    //fUpper->SetParameter(1,  5.27838e-03);
    //fUpper->SetParameter(2,  8.42220e-02);
    //fUpper->SetParameter(3, -3.80595e+00);

    dWidth = 0.0015;
    dMass  = TDatabasePDG::Instance()->GetParticle(3122)->Mass();
    
    dXmin  = dMass - 0.02;
    dXmax  = dMass + 0.02;
  }

  if(sOpt == "XiPos" || sOpt == "XiNeg" || sOpt == "Xi") {
    dWidth = 0.002;
    dMass  = TDatabasePDG::Instance()->GetParticle(3312)->Mass();
    dXmin = dMass - 0.015; 
    dXmax = dMass + 0.015; 
  }
  if(sOpt == "OmegaPos" || sOpt == "OmegaNeg" || sOpt == "Omega") {
    dWidth = 0.002;
    dMass  = TDatabasePDG::Instance()->GetParticle(3334)->Mass();
    dXmin = dMass - 0.02; 
    dXmax = dMass + 0.02; 
  }


//=============================================================================

  TF1  *fFitInvM = 0;
  TH1D *hFitInvM = 0;
  for (Int_t k=1; k<=hFitPtInvM->GetNbinsX(); k++) {
    cout << "Fitting " << sOpt.Data() << " InvM in pT bin: " << setw(2) << k << ": ";
    hFitInvM = (TH1D*)hPtInvM->ProjectionY(Form("hFitInvM_%d",k), k, k); list->Add(hFitInvM);

    //if (sOpt=="Lambda" || sOpt == "AntiLa") {
    //  Double_t dXval  = hFitPtInvM->GetBinCenter(k);
    //  Double_t dLower = fLower->Eval(dXval);
    //  Double_t dUpper = fUpper->Eval(dXval);

    //  dXmin = 0.85*dLower + 0.15*dUpper;
    //  dXmax = 0.15*dLower + 0.85*dUpper;
    //}

    Double_t dYmax = hFitInvM->GetMaximum();
    if (bIsMC)
      fFitInvM = new TF1(Form("fFitInvM_%d",k), "[0]*TMath::Gaus(x,[1],[2])", dXmin, dXmax);
    else
      fFitInvM = new TF1(Form("fFitInvM_%d",k), "[0]*TMath::Gaus(x,[1],[2])+[3]*x+[4]", dXmin, dXmax);

    fFitInvM->SetParameter(0, 0.9*dYmax);
    fFitInvM->SetParameter(1, dMass);
    fFitInvM->SetParameter(2, dWidth);

    if (!bIsMC) {
      fFitInvM->SetParameter(3, 0.);
      fFitInvM->SetParameter(4, 0.1*dYmax);
    }

    hFitInvM->Fit(Form("fFitInvM_%d",k), "QREM0");
    hFitPtInvM->SetBinContent(k, fFitInvM->GetParameter(1));
    hFitPtInvM->SetBinError(k, TMath::Abs(fFitInvM->GetParameter(2)));
    cout << "mean = "  << std::setprecision(7) << hFitPtInvM->GetBinContent(k) << ", "
         << "sigma = " << std::setprecision(9) << hFitPtInvM->GetBinError(k)   << endl;

    hFitInvM = 0;
    fFitInvM = 0;
  }
//=============================================================================

  file->cd(); list->Write(fListFitInvM.Data(), TObject::kSingleKey); file->Close();
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaFitCbin(const TString sOpt)
{
//
//  AliAnalysisTaskUserStraneJets::AnaFitCbin
//

  if (fFileLoop1st.IsNull() || fListLoop1st.IsNull()) return;
  if (fFileLoop2nd.IsNull() || fListLoop2nd.IsNull()) return;
  if (fFileFitInvM.IsNull() || fListFitInvM.IsNull()) return;
  if (fFileFitCbin.IsNull() || fListFitCbin.IsNull()) return;
  if ((sOpt!="Kshort") && (sOpt!="Lambda") && (sOpt!="AntiLa")
       && (sOpt!="Xi") && (sOpt!="XiNeg") && (sOpt!="XiPos")
       && (sOpt!="Omega") && (sOpt!="OmegaNeg") && (sOpt!="OmegaPos")) return;

  cout << "Bin counting the " << sOpt.Data() << " candidates..." << endl;
//=============================================================================

  TFile *file =  TFile::Open(Form("%s.root",fFileLoop1st.Data()), "READ"); if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListLoop1st.Data()); file->Close(); if (!list) return;

  TH2D *hPtInvM = (TH2D*)list->FindObject("hPtInvM"); if (!hPtInvM) return;
//=============================================================================

  file =  TFile::Open(Form("%s.root",fFileLoop2nd.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListLoop2nd.Data()); file->Close(); if (!list) return;

  TH1D *hCountInW = (TH1D*)list->FindObject("hCountInW"); if (!hCountInW) return;
  TH1D *hCountInB = (TH1D*)list->FindObject("hCountInB"); if (!hCountInB) return;
//=============================================================================

  file =  TFile::Open(Form("%s.root",fFileFitInvM.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListFitInvM.Data()); file->Close(); if (!list) return;

  TH1D *hFitPtInvM = (TH1D*)list->FindObject("hFitPtInvM"); if (!hFitPtInvM) return;
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileFitCbin.Data()), "UPDATE");
  list = (TList*)file->Get(fListFitCbin.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

  TH1D *hS = (TH1D*)hCountInW->Clone("hS"); hS->Reset(); list->Add(hS);
  TH1D *hB = (TH1D*)hCountInB->Clone("hB"); hB->Reset(); list->Add(hB);
//=============================================================================

  Double_t dSN = fKaCutNS;
  if (sOpt == "Lambda" || sOpt == "AntiLa") dSN = fLaCutNS;
  if ((sOpt == "XiPos") || (sOpt == "XiNeg") || (sOpt == "Xi")) dSN = fXiCutNS;
  if ((sOpt == "OmegaPos") || (sOpt == "OmegaNeg") || (sOpt == "Omega")) dSN = fOmegaCutNS;

  if(sOpt == "Kshort" || sOpt == "Lambda" || sOpt == "AntiLa"){
    TF1  *fBkgValF = 0;
    TF1  *fFitInvM = 0;
    TH1D *hFitInvM = 0;
    for (Int_t k=1; k<=hFitPtInvM->GetNbinsX(); k++) {
      cout << "Fitting " << sOpt.Data() << " InvM in pT bin: " << setw(2) << k << endl;

      hFitInvM = (TH1D*)hPtInvM->ProjectionY(Form("hFitInvM_%d",k), k, k);

      Double_t dMean  = hFitPtInvM->GetBinContent(k);
      Double_t dSigma = hFitPtInvM->GetBinError(k);

      Double_t dLowerL = RoundToThousandth(dMean - 2.*dSN*dSigma);
      Double_t dUpperL = RoundToThousandth(dMean - 1.*dSN*dSigma);
      Double_t dLowerR = RoundToThousandth(dMean + 1.*dSN*dSigma);
      Double_t dUpperR = RoundToThousandth(dMean + 2.*dSN*dSigma);

      Double_t dCountL = hFitInvM->Integral(hFitInvM->FindBin(dLowerL+1e-9), hFitInvM->FindBin(dUpperL-1e-9));
      Double_t dCountR = hFitInvM->Integral(hFitInvM->FindBin(dLowerR+1e-9), hFitInvM->FindBin(dUpperR-1e-9));

      Double_t dB = 0.;
      Double_t dS = hCountInW->GetBinContent(k);

      if ((dCountL>10.) && (dCountR>10.)) {
        fFitInvM = new TF1(Form("fFitInvM_%d",k), this, &AliAnalysisTaskUserStraneJets::BackgroundStrangeFit,
                           dLowerL, dUpperR, 4, "AliAnalysisTaskUserStraneJets", "BackgroundStrangeFit");
        fFitInvM->SetParameter(0, 1e-3*hCountInB->GetBinContent(k)/(dLowerR-dUpperL+1e-6));
        fFitInvM->SetParameter(1, 0.);
        fFitInvM->FixParameter(2, dUpperL);
        fFitInvM->FixParameter(3, dLowerR);
        hFitInvM->Fit(Form("fFitInvM_%d",k), "QREM0");
        //hFitInvM->Fit(Form("fFitBkg_%d",k), "QLLrie+0");

        fBkgValF = new TF1(Form("fBkgVarF_%d",k), this, &AliAnalysisTaskUserStraneJets::BackgroundStrangeVal,
                           dLowerL, dUpperR, 2, "AliAnalysisTaskUserStraneJets", "BackgroundStrangeVal"); list->Add(fBkgValF);
        fBkgValF->SetParameter(0, fFitInvM->GetParameter(0));
        fBkgValF->SetParameter(1, fFitInvM->GetParameter(1));

        dB = fBkgValF->Integral(dMean-dSN*dSigma, dMean+dSN*dSigma)/1e-3;
        delete fFitInvM; fFitInvM = 0;
      } else {
        dB = dCountL + dCountR;
      }

      hS->SetBinContent(k, dS-dB);
      hS->SetBinError(k, TMath::Sqrt(dS+dB));

      hB->SetBinContent(k, dB);
      hB->SetBinError(k, TMath::Sqrt(dB));

      delete hFitInvM; hFitInvM = 0;
    }
  }
  if((sOpt == "XiPos") || (sOpt == "XiNeg") || (sOpt == "Xi") || (sOpt == "OmegaPos") || (sOpt == "OmegaNeg") || (sOpt == "Omega")){
  
    TF1  *fFitBkg = 0;
    TF1  *fBkgValF = 0;
    TF1  *fFitInvM = 0;
    TH1D *hFitInvM = 0;
    for (Int_t k=1; k<=hFitPtInvM->GetNbinsX(); k++) {
      cout << "Fitting " << sOpt.Data() << " InvM in pT bin: " << setw(2) << k << endl;

      hFitInvM = (TH1D*)hPtInvM->ProjectionY(Form("hFitInvM_%d",k), k, k);

      Double_t dMean  = hFitPtInvM->GetBinContent(k);
      Double_t dSigma = hFitPtInvM->GetBinError(k);

      Double_t dLowerL = RoundToThousandth(dMean - 4.*dSN*dSigma);
      Double_t dUpperL = RoundToThousandth(dMean - 2.*dSN*dSigma);
      Double_t dLowerR = RoundToThousandth(dMean + 2.*dSN*dSigma);
      Double_t dUpperR = RoundToThousandth(dMean + 4.*dSN*dSigma);
      Double_t dLowerS = RoundToThousandth(dMean - 1.*dSN*dSigma);
      Double_t dUpperS = RoundToThousandth(dMean + 1.*dSN*dSigma);

      Double_t dCountL = hFitInvM->Integral(hFitInvM->FindBin(dLowerL+1e-9), hFitInvM->FindBin(dUpperL-1e-9));
      Double_t dCountR = hFitInvM->Integral(hFitInvM->FindBin(dLowerR+1e-9), hFitInvM->FindBin(dUpperR-1e-9));

      Double_t dB = 0.;
      Double_t dS = hCountInW->GetBinContent(k);

      if ((dCountL>10.) && (dCountR>10.)) {
        Double_t dYmax = hFitInvM->GetMaximum();
        
	fFitBkg = new TF1(Form("fFitBkg_%d",k), this, &AliAnalysisTaskUserStraneJets::BackgroundStrangeFit, dLowerL, dUpperR, 4, "AliAnalysisTaskUserStraneJets", "BackgroundStrangeFit");

        fFitBkg->SetParameter(0,0.01*dYmax);
        //fFitBkg->SetParameter(0,1e-3*hCountInB->GetBinContent(k)/(dUpperR-dLowerR + dUpperL-dLowerL+1e-6));
        fFitBkg->SetParameter(1,0.);
        fFitBkg->FixParameter(2, dUpperL);
        fFitBkg->FixParameter(3, dLowerR);
        //hFitInvM->Fit(Form("fFitBkg_%d",k), "QLLrie+0");
        hFitInvM->Fit(Form("fFitBkg_%d",k), "QREM0");
        
        fFitInvM = new TF1(Form("fFitInvM_%d",k), "[0]*TMath::Gaus(x,[1],[2])+[3]*x+[4]", dLowerL, dUpperR);
        fFitInvM->SetParameter(0, 0.99*dYmax);
        fFitInvM->FixParameter(1, dMean);
        fFitInvM->FixParameter(2, dSigma);
        fFitInvM->SetParameter(3, fFitBkg->GetParameter(1));
        fFitInvM->SetParameter(4, fFitBkg->GetParameter(0));
        hFitInvM->Fit(Form("fFitInvM_%d",k), "QREM0");
        //Double_t dChisquare = fFitInvM->GetChisquare();
        //Double_t       dNDF = fFitInvM->GetNDF();
        //Double_t dChisOverNDF = dChisquare/dNDF;
        //cout<<"---FitCbin------------dChisOverNDF-------------"<<dChisOverNDF<<endl;

        fBkgValF = new TF1(Form("fBkgVarF_%d",k), this, &AliAnalysisTaskUserStraneJets::BackgroundStrangeVal,
                           dLowerL, dUpperR, 2, "AliAnalysisTaskUserStraneJets", "BackgroundStrangeVal"); list->Add(fBkgValF);
        fBkgValF->SetParameter(0, fFitInvM->GetParameter(4));
        fBkgValF->SetParameter(1, fFitInvM->GetParameter(3));

        dB = fBkgValF->Integral(dLowerS, dUpperS)/1e-3;
        delete fFitInvM; fFitInvM = 0;
      } else {
        //dB = dCountL + dCountR;
        dB = 0.5*(dCountL + dCountR);
        //dS = dCountS-dB;
      }

      hS->SetBinContent(k, dS-dB);
      hS->SetBinError(k, TMath::Sqrt(dS+dB));

      hB->SetBinContent(k, dB);
      hB->SetBinError(k, TMath::Sqrt(dB));

      delete hFitInvM; hFitInvM = 0;
    }
  }
//=============================================================================

  file->cd(); list->Write(fListFitCbin.Data(), TObject::kSingleKey); file->Close();
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaInclEff(const TString sOpt, TH1D *hPtKineFB)
{
//
//  AliAnalysisTaskUserStraneJets::AnaInclEff
//

  if (!hPtKineFB) return;
  if (fFileFitCbin.IsNull() || fListFitCbin.IsNull()) return;
  if (fFileMakeEff.IsNull() || fListMakeEff.IsNull()) return;

  if ((sOpt!="Kshort") && (sOpt!="Lambda") && (sOpt!="AntiLa")
       && (sOpt!="Xi") && (sOpt!="XiNeg") && (sOpt!="XiPos")
       && (sOpt!="Omega") && (sOpt!="OmegaNeg") && (sOpt!="OmegaPos")) return;

  cout << "Make efficiency... " << endl;
//=============================================================================

  TFile *file =  TFile::Open(Form("%s.root",fFileFitCbin.Data()), "READ"); if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListFitCbin.Data()); file->Close();     if (!list) return;

  TH1D *hPtReco = (TH1D*)list->FindObject("hS"); if (!hPtReco) return; hPtReco->SetName("hPtReco");
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileMakeEff.Data()), "UPDATE");
  list = (TList*)file->Get(fListMakeEff.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

  TH1D *hPtEffi = (TH1D*)hPtReco->Clone("hPtEffi"); hPtEffi->Reset();
  TH1D *hPtKine = RebinTH1D(hPtKineFB, hPtReco); if (!hPtKine) return; hPtKine->SetName("hPtKine");

  list->Add(hPtEffi);
  list->Add(hPtReco);
  list->Add(hPtKine);
  list->Add(hPtKineFB);
//=============================================================================

  Double_t dBR = 0.692;
  if (sOpt == "Lambda" || sOpt == "AntiLa") dBR =  0.639;
  if ((sOpt == "XiPos") || (sOpt == "XiNeg") || (sOpt == "Xi"))  dBR = 0.639;
  if ((sOpt == "OmegaPos") || (sOpt == "OmegaNeg") || (sOpt == "Omega"))  dBR = 0.4332;

  for (Int_t k=1; k<=hPtReco->GetNbinsX(); k++) {
    Double_t dVarReco = hPtReco->GetBinContent(k); if (TMath::Abs(dVarReco)<1e-12) dVarReco = 1e-12;
    Double_t dVarKine = hPtKine->GetBinContent(k); if (TMath::Abs(dVarKine)<1e-12) dVarKine = 1e-12;
    Double_t dVarEffi = dVarReco / dVarKine;

    hPtEffi->SetBinContent(k, dVarEffi);
    hPtEffi->SetBinError(k, TMath::Sqrt(dVarEffi * (dBR-dVarEffi) / dBR / dVarKine));
  }
//=============================================================================

  file->cd(); list->Write(fListMakeEff.Data(), TObject::kSingleKey); file->Close();
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaResults(const Double_t dNorm)
{
//
//  AliAnalysisTaskUserStraneJets::AnaResults
//
  if(!dNorm) return;
  if (fFileLoop1st.IsNull() || fListLoop1st.IsNull()) return;
  if (fFileFitCbin.IsNull() || fListFitCbin.IsNull()) return;
  if (fFileMakeEff.IsNull() || fListMakeEff.IsNull()) return;
  if (fFileResults.IsNull() || fListResults.IsNull()) return;

  cout << "Make final results..." << endl;
//=============================================================================
  TFile *file = TFile::Open(Form("%s.root",fFileLoop1st.Data()), "READ");if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListLoop1st.Data()); file->Close(); if (!list) return; 

  TH1D* hEvent = (TH1D*)list->FindObject("hEvent"); if(!hEvent) return; hEvent->SetName("hEvent");

//=============================================================================
  file =  TFile::Open(Form("%s.root",fFileFitCbin.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListFitCbin.Data()); file->Close(); if (!list) return;
  //cout<<"==========PYC===PYC============="<<endl;
  TH1D *hSuc = (TH1D*)list->FindObject("hS"); if (!hSuc) return; hSuc->SetName("hSuc");
  TH1D *hBkg = (TH1D*)list->FindObject("hB"); if (!hBkg) return; hBkg->SetName("hBkg");

//=============================================================================
  file =  TFile::Open(Form("%s.root",fFileMakeEff.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListMakeEff.Data()); file->Close(); if (!list) return;

  TH1D *hEff = (TH1D*)list->FindObject("hPtEffi"); if (!hEff) return; hEff->SetName("hEff");
//=============================================================================

  file =  TFile::Open(Form("%s.root",fFileResults.Data()), "UPDATE");
  list = (TList*)file->Get(fListResults.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

  TH1D *hSco = (TH1D*)hSuc->Clone("hSco"); hSco->Reset();
  TH1D *hSBR = (TH1D*)hSuc->Clone("hSBR"); hSBR->Reset();
  TH1D *hNco = (TH1D*)hSuc->Clone("hNco"); hNco->Reset();

  list->Add(hNco);
  list->Add(hSco);
  list->Add(hSBR);
  list->Add(hSuc);
  list->Add(hBkg);
  list->Add(hEff);
  list->Add(hEvent);
//=============================================================================
  Double_t dEvent = 0.;
  for(Int_t l = 1; l<=hEvent->GetNbinsX(); l++){dEvent += hEvent->GetBinContent(l);}
  
  for (Int_t k=1; k<=hSuc->GetNbinsX(); k++) {
    Double_t dSvar = hSuc->GetBinContent(k); if (TMath::Abs(dSvar)<1e-12) dSvar = 1e-12;
    Double_t dSerr = hSuc->GetBinError(k) / dSvar;

    Double_t dBvar = hBkg->GetBinContent(k); if (TMath::Abs(dBvar)<1e-12) dBvar = 1e-12;
    Double_t dBerr = hBkg->GetBinError(k) / dBvar;

    Double_t dEvar = hEff->GetBinContent(k); if (TMath::Abs(dEvar)<1e-12) dEvar = 1e-12;
    Double_t dEerr = hEff->GetBinError(k) / dEvar;

    Double_t dCvar = dSvar / dEvar;
    Double_t dCerr = dCvar * TMath::Sqrt(dSerr*dSerr + dEerr*dEerr);
    hSco->SetBinContent(k, dCvar); hSco->SetBinError(k, dCerr);

    Double_t dNvar = dCvar / (dEvent*dNorm);
    hNco->SetBinContent(k, dNvar); hNco->SetBinError(k, dCerr/(dEvent*dNorm));

    Double_t dRvar = dSvar / dBvar;
    hSBR->SetBinContent(k, dRvar); hSBR->SetBinError(k, dRvar * TMath::Sqrt(dSerr*dSerr + dBerr*dBerr));
  }
//=============================================================================

  file->cd(); list->Write(fListResults.Data(), TObject::kSingleKey); file->Close();
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaMakeFd(TH1D *hPtXiMeas)
{
//
//AliAnalysisTaskUserStraneJets::AnaMakeFd
//

  if (fFileLoopsMC.IsNull() || fListLoopsMC.IsNull()) return;
  if (fFileMakeFdR.IsNull() || fListMakeFdR.IsNull()) return;

  if (!hPtXiMeas) return;
  cout << "Make feeddown correction..." << endl;
//=============================================================================
  hPtXiMeas->SetName("hPtXiMeas");

  TFile *file = TFile::Open(Form("%s.root",fFileLoopsMC.Data()), "READ"); if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListLoopsMC.Data()); file->Close();    if (!list) return;

  TH2D *hPtLaXi = (TH2D*)list->FindObject("hPtLaXi"); if (!hPtLaXi) return; hPtLaXi->SetName("hPtLaXi");
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileMakeFdR.Data()), "UPDATE");
  list = (TList*)file->Get(fListMakeFdR.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

//=============================================================================
  //Rebin hPtLaXi
  Int_t nx = hPtLaXi->GetNbinsX();
  Int_t ny = hPtXiMeas->GetNbinsX();
  Double_t dx[nx+1];
  Double_t dy[ny+1];
  dx[nx] = hPtLaXi->GetXaxis()->GetBinUpEdge(nx);
  dy[ny] = hPtXiMeas->GetXaxis()->GetBinUpEdge(ny);
  for (Int_t i=0, k=1; i<nx; i++, k++) dx[i] = hPtLaXi->GetXaxis()->GetBinLowEdge(k);
  for (Int_t j=0, l=1; j<ny; j++, l++) dy[j] = hPtXiMeas->GetXaxis()->GetBinLowEdge(l);
  TH2D *hNPtLaXi = new TH2D("hNPtLaXi", "", nx, dx, ny, dy); hNPtLaXi->Sumw2(); hNPtLaXi->Reset();
  hNPtLaXi = (TH2D*)RebinTH2D(hPtLaXi, hNPtLaXi);
  hNPtLaXi->SetName("hNPtLaXi");
//=============================================================================
  TH2D *hPtLaXiNormY = (TH2D*)hNPtLaXi->Clone("hPtLaXiNormY"); hPtLaXiNormY->Reset();
  TH1D *hPtSecLa = (TH1D*)hNPtLaXi->ProjectionX("hPtSecLa"); hPtSecLa->Reset();

  list->Add(hPtSecLa);
  list->Add(hPtLaXi);
  list->Add(hNPtLaXi);
  list->Add(hPtLaXiNormY);
  list->Add(hPtXiMeas);
//=============================================================================

  TH1D *hPtLaDecay;
  TH1D *hPtXiToLa;
  for (Int_t i=1; i<= hNPtLaXi->GetNbinsY(); i++){

//=============================================================================
    //Normalize hNPtLaXi Y axis to 1
    for (Int_t iy = 1; iy <= hNPtLaXi->GetNbinsY(); iy++){
      Double_t dN = 0;
      Double_t dErr= 0;
      for (Int_t ix = 1; ix <= hNPtLaXi->GetNbinsX(); ix++){
        dN = dN + hNPtLaXi->GetBinContent(ix,iy); if(dN<=0) dN = 1e-12;
        dErr = TMath::Sqrt(dN); if(dN<=1e-12) dErr = 1e-12;
      }
      for (Int_t ix = 1; ix <= hNPtLaXi->GetNbinsX(); ix++){
        Double_t dPtLaXi      = hNPtLaXi->GetBinContent(ix,iy); if (dPtLaXi<=0) dPtLaXi = 1e-12;
        Double_t dPtLaXiNormY = dPtLaXi/dN; if (dPtLaXi<=1e-12) dPtLaXiNormY = 1e-12;
        Double_t dErrPtLXNormY= TMath::Sqrt(dPtLaXi)/dN; if (dPtLaXiNormY<=1e-12) dErrPtLXNormY = 1e-12;
        //Double_t dErrPtLXNormY= dPtLaXiNormY*TMath::Sqrt(1/dPtLaXi+1/dN); if (dPtLaXiNormY<=1e-12) dErrPtLXNormY = 0.;
        //cout<<"dErrPtLXNormY = "<< dErrPtLXNormY <<endl;
        //cout<<"dErrPtLXNormY1 = "<< dErrPtLXNormY1 <<endl;

        hPtLaXiNormY->SetBinContent(ix,iy, dPtLaXiNormY);
        hPtLaXiNormY->SetBinError(ix,iy, dErrPtLXNormY);
      }
    }

    hPtXiToLa = (TH1D*)hPtLaXiNormY->ProjectionX(Form("hPtXiToLa_%d",i), i, i);list->Add(hPtXiToLa);
//=============================================================================
    hPtLaDecay = (TH1D*)hPtXiToLa->Clone(Form("hPtLaDecay_%d",i)); hPtLaDecay->Reset();

    Double_t dXiBinWidth = hPtXiMeas->GetBinWidth(i);
    Double_t dVarXi      = hPtXiMeas->GetBinContent(i);if(dVarXi<=1e-12) dVarXi = 1e-12;
    Double_t dErrXi      = hPtXiMeas->GetBinError(i);

    for (Int_t k=1; k<= hPtLaDecay->GetNbinsX(); k++){
      Double_t dVarXiToLa = hPtXiToLa->GetBinContent(k);if(dVarXiToLa<= 1e-12) dVarXiToLa = 1e-12;
      Double_t dErrXiToLa = hPtXiToLa->GetBinError(k);
      Double_t dVarPtLaDecay = dVarXiToLa*dVarXi*dXiBinWidth;
      //Double_t dErrPtLaDecay = dVarPtLaDecay*TMath::Sqrt(dErrXiToLa*dErrXiToLa+dErrXi*dErrXi); 
      Double_t dErrPtLaDecay = dVarPtLaDecay*TMath::Sqrt(dErrXiToLa*dErrXiToLa/(dVarXiToLa*dVarXiToLa)+dErrXi*dErrXi/(dVarXi*dVarXi));
      hPtLaDecay->SetBinContent(k, dVarPtLaDecay);
      hPtLaDecay->SetBinError(k, dErrPtLaDecay);

    }
    for (Int_t k=1; k<= hPtSecLa->GetNbinsX(); k++){

      hPtSecLa->SetBinContent(k, hPtSecLa->GetBinContent(k) + hPtLaDecay->GetBinContent(k));
      hPtSecLa->SetBinError(k, TMath::Sqrt(hPtSecLa->GetBinError(k)*hPtSecLa->GetBinError(k) + hPtLaDecay->GetBinError(k)*hPtLaDecay->GetBinError(k)));
    }
  }


  file->cd(); list->Write(fListMakeFdR.Data(), TObject::kSingleKey); file->Close();

  return;
}

//_____________________________________________________________________________
//void AliAnalysisTaskUserStraneJets::AnaMakeFdR(TH1D *hPtXiMeas, TH1D *hPtXiKineFB, TH1D* hEvent)
void AliAnalysisTaskUserStraneJets::AnaMakeFdR(TH1D *hPtXiMeas, TH1D *hPtXiKineFB, const Double_t dNorm)
{
//
//  AliAnalysisTaskUserStraneJets::AnaMakeFdR
//

  if(!dNorm) return;
  if (fFileLoop1st.IsNull() || fListLoop1st.IsNull()) return;
  if (fFileLoopsMC.IsNull() || fListLoopsMC.IsNull()) return;
  if (fFileResults.IsNull() || fListResults.IsNull()) return;
  if (fFileMakeFdR.IsNull() || fListMakeFdR.IsNull()) return;

  if ((!hPtXiMeas) || (!hPtXiKineFB)) return;
  cout << "Make feeddown correction..." << endl;
//=============================================================================

  hPtXiMeas->SetName("hPtXiMeas");
  hPtXiKineFB->SetName("hPtXiKineFB");
  TH1D *hPtXiKine = RebinTH1D(hPtXiKineFB, hPtXiMeas); hPtXiKine->SetName("hPtXiKine");
//=============================================================================
  TFile *file = TFile::Open(Form("%s.root",fFileLoop1st.Data()), "READ");if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListLoop1st.Data()); file->Close(); if (!list) return; 

  TH1D* hEvent = (TH1D*)list->FindObject("hEvent"); if(!hEvent) return; hEvent->SetName("hEvent");

  file = TFile::Open(Form("%s.root",fFileLoopsMC.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListLoopsMC.Data()); file->Close();    if (!list) return;

  TH2D *hPtLaXiReco = (TH2D*)list->FindObject("hPtLaXi"); if (!hPtLaXiReco) return; hPtLaXiReco->SetName("hPtLaXiReco");
  TH2D *hPtLaXiCorr = (TH2D*)hPtLaXiReco->Clone("hPtLaXiCorr"); hPtLaXiCorr->Reset();
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileResults.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListResults.Data()); file->Close();    if (!list) return;

  TH1D *hPtLaMeas = (TH1D*)list->FindObject("hSuc"); if (!hPtLaMeas) return; hPtLaMeas->SetName("hPtLaMeas");
  TH1D *hPtLaEffi = (TH1D*)list->FindObject("hEff"); if (!hPtLaEffi) return; hPtLaEffi->SetName("hPtLaEffi");
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileMakeFdR.Data()), "UPDATE");
  list = (TList*)file->Get(fListMakeFdR.Data()); if (list) { file->Close(); return; } else { list = new TList(); }
//=============================================================================

  Double_t dEvent = 0.;
  for(Int_t l = 1; l<=hEvent->GetNbinsX(); l++){dEvent += hEvent->GetBinContent(l);}
  
  for (Int_t k=1; k<=hPtLaXiReco->GetNbinsY(); k++) {
    Double_t dKine = hPtXiKine->GetBinContent(k); if (TMath::Abs(dKine)<1e-12) dKine = 1e-12;//MC generate Xi

    //Double_t dCorr = hPtXiMeas->GetBinWidth(k)   / dKine;
    Double_t dCorr = 1. / dKine;
    Double_t dCorV = hPtXiMeas->GetBinContent(k) * dCorr; if (TMath::Abs(dCorV)<1e-12) dCorV = 1e-12;
    Double_t dCorE = hPtXiMeas->GetBinError(k)   * dCorr / dCorV;

    for (Int_t l=1; l<=hPtLaXiReco->GetNbinsX(); l++) {
      Double_t dVarX = hPtLaXiReco->GetBinContent(l,k);  if (TMath::Abs(dVarX)<1e-12) dVarX = 1e-12;//MC reconstruct Lambda mother
      Double_t dErrX = hPtLaXiReco->GetBinError(l,k) / dVarX;

      Double_t dVarL = dVarX * dCorV;//data reconstruct lambda mother
      hPtLaXiCorr->SetBinContent(l, k, dVarL);
      hPtLaXiCorr->SetBinError(l, k, dVarL * TMath::Sqrt(dCorE*dCorE + dErrX*dErrX));
    }
  }

  TH1D *hPtLaXiFd = hPtLaXiCorr->ProjectionX("hPtLaXiFd");//data reconstruct second lambda
//=============================================================================

  //Double_t dNorm = hEvent->Integral(hEvent->FindBin(fCentralityMin + 1e-9), hEvent->FindBin(fCentralityMax - 1e-9));
  //Double_t dNorm = hEvent->GetBinContent(1) *2*0.75*TMath::TwoPi();
  TH1D *hPtLaNorm = (TH1D*)hPtLaMeas->Clone("hPtLaNorm"); //hPtLaNorm->Scale(1./dNorm);//raw Lambda
  TH1D *hPtLaSubF = (TH1D*)hPtLaNorm->Clone("hPtLaSubF"); hPtLaSubF->Add(hPtLaXiFd, -1.);//raw Lambda - reconstruct second Lambda == raw primary Lambda
  TH1D *hPtFdFrac = (TH1D*)hPtLaXiFd->Clone("hPtFdFrac"); hPtFdFrac->Divide(hPtLaNorm);//reconstruct second Lambda/raw Lambda
  TH1D *hPtLaCorr = (TH1D*)hPtLaMeas->Clone("hPtLaCorr"); hPtLaCorr->Reset();
  TH1D *hPtLaNormCorr = (TH1D*)hPtLaMeas->Clone("hPtLaNormCorr"); hPtLaNormCorr->Reset();

  for (Int_t k=1; k<=hPtLaSubF->GetNbinsX(); k++) {
    Double_t dSval = hPtLaSubF->GetBinContent(k); if (TMath::Abs(dSval)<1e-12) dSval = 1e-12;
    Double_t dSerr = hPtLaSubF->GetBinError(k) / dSval;

    Double_t dEval = hPtLaEffi->GetBinContent(k); if (TMath::Abs(dEval)<1e-12) dEval = 1e-12;
    Double_t dEerr = hPtLaEffi->GetBinError(k) / dEval;

    Double_t dCval = dSval / dEval;
    Double_t dCerr = dCval * TMath::Sqrt(dSerr*dSerr + dEerr*dEerr);
    Double_t dNvar = dCval / (dEvent*dNorm);

    hPtLaCorr->SetBinContent(k, dCval);//corrected primary Lambda
    hPtLaCorr->SetBinError(k, dCerr);
    hPtLaNormCorr->SetBinContent(k, dNvar); hPtLaNormCorr->SetBinError(k, dCerr/(dEvent*dNorm));
  }
//=============================================================================

  list->Add(hEvent);
  list->Add(hPtLaEffi);
  list->Add(hPtLaCorr);
  list->Add(hPtLaNormCorr);
  list->Add(hPtLaSubF);
  list->Add(hPtLaNorm);
  list->Add(hPtLaMeas);
  list->Add(hPtFdFrac);
  list->Add(hPtLaXiFd);
  list->Add(hPtXiMeas);
  list->Add(hPtXiKine);
  list->Add(hPtXiKineFB);
  list->Add(hPtLaXiCorr);
  list->Add(hPtLaXiReco);

  file->cd(); list->Write(fListMakeFdR.Data(), TObject::kSingleKey); file->Close();
//=============================================================================
  return;
}

//_____________________________________________________________________________
//void AliAnalysisTaskUserStraneJets::AnaMakeFdR(TH1D *hPtXiMeas, TH1D *hPtXiKineFB, TH1D* hEvent)
void AliAnalysisTaskUserStraneJets::AnaMakeFdRJC(TH1D *hPtXiMeas, TH1D *hPtXiKineFB, TH1D *hPtLaMeas, const Double_t dNorm)
{
//
//  AliAnalysisTaskUserStraneJets::AnaMakeFdRJC
//
  if(!dNorm) return;
  if (fFileLoop1st.IsNull() || fListLoop1st.IsNull()) return;
  if (fFileLoopsMC.IsNull() || fListLoopsMC.IsNull()) return;
  if (fFileResults.IsNull() || fListResults.IsNull()) return;
  if (fFileMakeFdR.IsNull() || fListMakeFdR.IsNull()) return;

  if ((!hPtXiMeas) || (!hPtXiKineFB) || (!hPtLaMeas)) return;
  cout << "Make JC feeddown correction..." << endl;
//=============================================================================

  hPtXiMeas->SetName("hPtXiMeas");
  hPtXiKineFB->SetName("hPtXiKineFB");
  hPtLaMeas->SetName("hPtXiLaMeas"); 
  TH1D *hPtXiKine = RebinTH1D(hPtXiKineFB, hPtXiMeas); hPtXiKine->SetName("hPtXiKine");
//=============================================================================
  TFile *file = TFile::Open(Form("%s.root",fFileLoop1st.Data()), "READ");if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListLoop1st.Data()); file->Close(); if (!list) return;

  TH1D* hEvent = (TH1D*)list->FindObject("hEvent"); if(!hEvent) return; hEvent->SetName("hEvent");

  file = TFile::Open(Form("%s.root",fFileLoopsMC.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListLoopsMC.Data()); file->Close();    if (!list) return;

  TH2D *hPtLaXiReco = (TH2D*)list->FindObject("hPtLaXi"); if (!hPtLaXiReco) return; hPtLaXiReco->SetName("hPtLaXiReco");
  TH2D *hPtLaXiCorr = (TH2D*)hPtLaXiReco->Clone("hPtLaXiCorr"); hPtLaXiCorr->Reset();
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileResults.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListResults.Data()); file->Close();    if (!list) return;

  //TH1D *hPtLaMeas = (TH1D*)list->FindObject("hSuc"); if (!hPtLaMeas) return; hPtLaMeas->SetName("hPtLaMeas");
  TH1D *hPtLaEffi = (TH1D*)list->FindObject("hEff"); if (!hPtLaEffi) return; hPtLaEffi->SetName("hPtLaEffi");
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileMakeFdR.Data()), "UPDATE");
  list = (TList*)file->Get(fListMakeFdR.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

//=============================================================================

  Double_t dEvent = 0.;
  for(Int_t l = 1; l<=hEvent->GetNbinsX(); l++){dEvent += hEvent->GetBinContent(l);}

  for (Int_t k=1; k<=hPtLaXiReco->GetNbinsY(); k++) {
    Double_t dKine = hPtXiKine->GetBinContent(k); if (TMath::Abs(dKine)<1e-12) dKine = 1e-12;//MC generate Xi

    Double_t dCorr = 1. / dKine;
    Double_t dCorV = hPtXiMeas->GetBinContent(k) * dCorr; if (TMath::Abs(dCorV)<1e-12) dCorV = 1e-12;
    Double_t dCorE = hPtXiMeas->GetBinError(k)   * dCorr / dCorV;

    for (Int_t l=1; l<=hPtLaXiReco->GetNbinsX(); l++) {
      Double_t dVarX = hPtLaXiReco->GetBinContent(l,k);  if (TMath::Abs(dVarX)<1e-12) dVarX = 1e-12;//MC reconstruct Lambda mother
      Double_t dErrX = hPtLaXiReco->GetBinError(l,k) / dVarX;

      Double_t dVarL = dVarX * dCorV;//data reconstruct lambda mother
      hPtLaXiCorr->SetBinContent(l, k, dVarL);
      hPtLaXiCorr->SetBinError(l, k, dVarL * TMath::Sqrt(dCorE*dCorE + dErrX*dErrX));
    }
  }

  TH1D *hPtLaXiFd = hPtLaXiCorr->ProjectionX("hPtLaXiFd");//data reconstruct second lambda
  TH1D *hPtLaXiFdCorr = (TH1D*)hPtLaXiFd->Clone("hPtLaXiFdCorr");  hPtLaXiFdCorr->Divide(hPtLaEffi);
 //=============================================================================

  TH1D *hPtLaNorm = (TH1D*)hPtLaMeas->Clone("hPtLaNorm"); //hPtLaNorm->Scale(1./dNorm);//Corr Lambda
  TH1D *hPtLaSubF = (TH1D*)hPtLaNorm->Clone("hPtLaSubF"); hPtLaSubF->Add(hPtLaXiFdCorr, -1.);//Lambda - reconstruct second Lambda == Corr primary Lambda
  TH1D *hPtFdFrac = (TH1D*)hPtLaXiFdCorr->Clone("hPtFdFrac"); hPtFdFrac->Divide(hPtLaNorm);//second Lambda/Lambda
  TH1D *hPtLaCorr = (TH1D*)hPtLaMeas->Clone("hPtLaCorr");hPtLaCorr->Reset();
  TH1D *hPtLaNormCorr = (TH1D*)hPtLaMeas->Clone("hPtLaNormCorr"); hPtLaNormCorr->Reset();

  for (Int_t k=1; k<=hPtLaSubF->GetNbinsX(); k++) {
    Double_t dCval = hPtLaSubF->GetBinContent(k); if (TMath::Abs(dCval)<1e-12) dCval = 1e-12;
    Double_t dCerr = hPtLaSubF->GetBinError(k);

    Double_t dNvar = dCval / (dEvent*dNorm);

    hPtLaCorr->SetBinContent(k, dCval);//corrected primary Lambda
    hPtLaCorr->SetBinError(k, dCerr);
    hPtLaNormCorr->SetBinContent(k, dNvar); hPtLaNormCorr->SetBinError(k, dCerr/(dEvent*dNorm));
  }
//=============================================================================

  list->Add(hEvent);
  list->Add(hPtLaEffi);
  list->Add(hPtLaCorr);
  list->Add(hPtLaNormCorr);
  list->Add(hPtLaSubF);
  list->Add(hPtLaNorm);
  list->Add(hPtLaMeas);
  list->Add(hPtFdFrac);
  list->Add(hPtLaXiFdCorr);
  list->Add(hPtXiMeas);
  list->Add(hPtXiKine);
  list->Add(hPtXiKineFB);
  list->Add(hPtLaXiCorr);
  list->Add(hPtLaXiReco);

  file->cd(); list->Write(fListMakeFdR.Data(), TObject::kSingleKey); file->Close();
//=============================================================================
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaCorrEff(TH2D *hPtEtaKineFB, const TString sOpt)
{
//
//  AliAnalysisTaskUserStraneJets::AnaCorrEff
//

  if (fFileLoop2nd.IsNull() || fListLoop2nd.IsNull()) return;
  if (fFileLoopsMC.IsNull() || fListLoopsMC.IsNull()) return;
  if (fFileFitCbin.IsNull() || fListFitCbin.IsNull()) return;
  if (fFileMakeEff.IsNull() || fListMakeEff.IsNull()) return;

  hPtEtaKineFB->SetName("hPtEtaKineFB");
//=============================================================================

  TFile *file = TFile::Open(Form("%s.root", fFileLoop2nd.Data()), "READ"); if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListLoop2nd.Data()); file->Close();     if (!list) return;

  TH2D *hPtEtaRecoRD = 0;
  if (sOpt=="I") {
    hPtEtaRecoRD = (TH2D*)list->FindObject("hPtEtaI");
  } else {
    hPtEtaRecoRD = (TH2D*)list->FindObject("hPtEtaJ");
  } hPtEtaRecoRD->SetName("hPtEtaRecoRD");
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileLoopsMC.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListLoopsMC.Data()); file->Close();    if (!list) return;

  TH2D *hPtEtaRecoIn = (TH2D*)list->FindObject("hPtEtaI"); hPtEtaRecoIn->SetName("hPtEtaRecoIn");
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileFitCbin.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListFitCbin.Data()); file->Close();    if (!list) return;

  TH1D *hS_MC = (TH1D*)list->FindObject("hS"); hS_MC->SetName("hS_MC");
  TH1D *hB_MC = (TH1D*)list->FindObject("hB"); hB_MC->SetName("hB_MC");
//=============================================================================

  file = TFile::Open(Form("%s.root", fFileMakeEff.Data()), "UPDATE");
  list = (TList*)file->Get(fListMakeEff.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

  for (Int_t k=1; k<=hS_MC->GetNbinsX(); k++) {
    if (TMath::Abs(hS_MC->GetBinContent(k))<1e-12) { hS_MC->SetBinContent(k, 1e-12); hS_MC->SetBinError(k, 0.); }
    if (TMath::Abs(hB_MC->GetBinContent(k))<1e-12) { hB_MC->SetBinContent(k, 1e-12); hB_MC->SetBinError(k, 0.); }
  }

  TH1D *hR_MC = (TH1D*)hB_MC->Clone("hR_MC"); hR_MC->Divide(hS_MC);
//=============================================================================

  const Int_t nEtaBinI = hPtEtaRecoIn->GetYaxis()->FindBin(fV0CutMinEta + 1e-9);
  const Int_t nEtaBinF = hPtEtaRecoIn->GetYaxis()->FindBin(fV0CutMaxEta - 1e-9);
  TH2D *hPtEtaRecoMC = (TH2D*)hPtEtaRecoIn->Clone("hPtEtaRecoMC"); hPtEtaRecoMC->Reset();
  TH2D *hPtEtaKineMC = (TH2D*)hPtEtaRecoIn->Clone("hPtEtaKineMC"); hPtEtaKineMC->Reset();
  TH2D *hPtEtaKineRD = (TH2D*)hPtEtaRecoRD->Clone("hPtEtaKineRD"); hPtEtaKineRD->Reset();

  for (Int_t k=nEtaBinI; k<=nEtaBinF; k++) {
    TH1D *hPtKineFB = hPtEtaKineFB->ProjectionX(Form("hPtKineFB_%d",k), k, k);
    TH1D *hPtRecoMC = hPtEtaRecoIn->ProjectionX(Form("hPtRecoMC_%d",k), k, k);
    TH1D *hPtKineMC = RebinTH1D(hPtKineFB, hPtRecoMC); hPtKineMC->SetName(Form("hPtKineMC_%d",k));

    for (Int_t l=1; l<=hPtRecoMC->GetNbinsX(); l++) {

      Double_t dVarBkgF = hR_MC->GetBinContent(l);    if (TMath::Abs(dVarBkgF)<1e-12) dVarBkgF = 1e-12;
      Double_t dErrBkgF = hR_MC->GetBinError(l) / dVarBkgF;

      Double_t dVarRecoMC = hPtRecoMC->GetBinContent(l);  if (TMath::Abs(dVarRecoMC)<1e-12) dVarRecoMC = 1e-12;
      Double_t dErrRecoMC = hPtRecoMC->GetBinError(l) / dVarRecoMC;

      Double_t dVarKineMC = hPtKineMC->GetBinContent(l);  if (TMath::Abs(dVarKineMC)<1e-12) dVarKineMC = 1e-12;
      Double_t dErrKineMC = hPtKineMC->GetBinError(l) / dVarKineMC;

      Double_t dVarRecoRD = hPtEtaRecoRD->GetBinContent(l,k); if (TMath::Abs(dVarRecoRD)<1e-12) dVarRecoRD = 1e-12;
      Double_t dErrRecoRD = hPtEtaRecoRD->GetBinError(l,k) / dVarRecoRD;

      Double_t dVarKineRD = dVarRecoRD / (dVarRecoMC / (1. + dVarBkgF) / dVarKineMC);
      Double_t dErrKineRD = dVarKineRD * TMath::Sqrt(dErrRecoRD*dErrRecoRD + dErrRecoMC*dErrRecoMC + dErrKineMC*dErrKineMC + dErrBkgF*dErrBkgF);

      hPtEtaRecoMC->SetBinContent(l, k, dVarRecoMC); hPtEtaRecoMC->SetBinError(l, k, dErrRecoMC);
      hPtEtaKineMC->SetBinContent(l, k, dVarKineMC); hPtEtaKineMC->SetBinError(l, k, dErrKineMC);
      hPtEtaKineRD->SetBinContent(l, k, dVarKineRD); hPtEtaKineRD->SetBinError(l, k, dErrKineRD);
    }

    delete hPtKineFB; hPtKineFB = 0;
    delete hPtRecoMC; hPtRecoMC = 0;
    delete hPtKineMC; hPtKineMC = 0;
  }
//=============================================================================

  TH1D *hPtRecoRD = hPtEtaRecoRD->ProjectionX("hPtReco", nEtaBinI, nEtaBinF, "E");
  TH1D *hPtKineRD = hPtEtaKineRD->ProjectionX("hPtKine", nEtaBinI, nEtaBinF, "E");
  TH1D *hPtEffiRD = (TH1D*)hPtRecoRD->Clone("hPtEffi"); hPtEffiRD->Divide(hPtKineRD);

  TH1D *hPtRecoMC = hPtEtaRecoMC->ProjectionX("hPtRecoMC", nEtaBinI, nEtaBinF, "E");
  TH1D *hPtKineMC = hPtEtaKineMC->ProjectionX("hPtKineMC", nEtaBinI, nEtaBinF, "E");
  TH1D *hPtEffiMC = (TH1D*)hPtRecoMC->Clone("hPtEffiMC"); hPtEffiMC->Divide(hPtKineMC);
//=============================================================================

  list->Add(hPtEffiRD);
  list->Add(hPtRecoRD);
  list->Add(hPtKineRD);
  list->Add(hPtEtaRecoRD);
  list->Add(hPtEtaKineRD);

  list->Add(hPtEffiMC);
  list->Add(hPtRecoMC);
  list->Add(hPtKineMC);
  list->Add(hPtEtaRecoMC);
  list->Add(hPtEtaKineMC);

  list->Add(hPtEtaRecoIn);
  list->Add(hPtEtaKineFB);

  list->Add(hR_MC);

  file->cd(); list->Write(fListMakeEff.Data(), TObject::kSingleKey); file->Close();

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaWghtEff(TH2D *hPtEtaKineFB)
{
//
//  AliAnalysisTaskUserStraneJets::AnaWghtEff
//

  if (fFileLoopJet.IsNull() || fListLoopJet.IsNull()) return;
  if (fFileLoopsMC.IsNull() || fListLoopsMC.IsNull()) return;
  if (fFileLoop1st.IsNull() || fListLoop1st.IsNull()) return;
  if (fFileLoop2nd.IsNull() || fListLoop2nd.IsNull()) return;
  if (fFileFitCbin.IsNull() || fListFitCbin.IsNull()) return;
  if (fFileMakeEff.IsNull() || fListMakeEff.IsNull()) return;

  hPtEtaKineFB->SetName("hPtEtaKineFB");
//=============================================================================

  TFile *file = TFile::Open(Form("%s.root", fFileLoopJet.Data()), "READ"); if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListLoopJet.Data()); file->Close();     if (!list) return;

  TH2D *hPtEtaInc = (TH2D*)list->FindObject("hPtEtaI"); hPtEtaInc->SetName("hPtEtaInc");
  TH2D *hPtEtaJet = (TH2D*)list->FindObject("hPtEtaJ"); hPtEtaJet->SetName("hPtEtaJet");
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileLoopsMC.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListLoopsMC.Data()); file->Close();    if (!list) return;

  TH2D *hPtEtaReco = (TH2D*)list->FindObject("hPtEtaI"); hPtEtaReco->SetName("hPtEtaReco");
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileLoop1st.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListLoop1st.Data()); file->Close();    if (!list) return;

  TH1D *hS_MC = (TH1D*)list->FindObject("hS"); hS_MC->SetName("hS_MC");
  TH1D *hB_MC = (TH1D*)list->FindObject("hB"); hB_MC->SetName("hB_MC");
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileLoop2nd.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListLoop2nd.Data()); file->Close();    if (!list) return;

  TH1D *hS_RD = (TH1D*)list->FindObject("hS"); hS_RD->SetName("hS_RD");
  TH1D *hB_RD = (TH1D*)list->FindObject("hB"); hB_RD->SetName("hB_RD");
//=============================================================================

  file = TFile::Open(Form("%s.root",fFileFitCbin.Data()), "READ"); if (!file->IsOpen()) return;
  list = (TList*)file->Get(fListFitCbin.Data()); file->Close();    if (!list) return;

  TH1D *hS_JE = (TH1D*)list->FindObject("hS"); hS_JE->SetName("hS_JE");
  TH1D *hB_JE = (TH1D*)list->FindObject("hB"); hB_JE->SetName("hB_JE");
//=============================================================================

  file = TFile::Open(Form("%s.root", fFileMakeEff.Data()), "UPDATE");
  list = (TList*)file->Get(fListMakeEff.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

  for (Int_t k=1; k<=hS_MC->GetNbinsX(); k++) {
    if (TMath::Abs(hS_MC->GetBinContent(k))<1e-12) { hS_MC->SetBinContent(k, 1e-12); hS_MC->SetBinError(k, 0.); }
    if (TMath::Abs(hB_MC->GetBinContent(k))<1e-12) { hB_MC->SetBinContent(k, 1e-12); hB_MC->SetBinError(k, 0.); }

    if (TMath::Abs(hS_RD->GetBinContent(k))<1e-12) { hS_RD->SetBinContent(k, 1e-12); hS_RD->SetBinError(k, 0.); }
    if (TMath::Abs(hB_RD->GetBinContent(k))<1e-12) { hB_RD->SetBinContent(k, 1e-12); hB_RD->SetBinError(k, 0.); }

    if (TMath::Abs(hS_JE->GetBinContent(k))<1e-12) { hS_JE->SetBinContent(k, 1e-12); hS_JE->SetBinError(k, 0.); }
    if (TMath::Abs(hB_JE->GetBinContent(k))<1e-12) { hB_JE->SetBinContent(k, 1e-12); hB_JE->SetBinError(k, 0.); }
  }

  TH1D *hR_MC = (TH1D*)hB_MC->Clone("hR_MC"); hR_MC->Divide(hS_MC);
  TH1D *hR_RD = (TH1D*)hB_RD->Clone("hR_RD"); hR_RD->Divide(hS_RD);
  TH1D *hR_JE = (TH1D*)hB_JE->Clone("hR_JE"); hR_JE->Divide(hS_JE);
//=============================================================================

  TH2D *hPtEtaWgt = (TH2D*)hPtEtaJet->Clone("hPtEtaWgt"); hPtEtaWgt->Reset();

  const Int_t nEtaBinI = hPtEtaWgt->GetYaxis()->FindBin(fV0CutMinEta + 1e-9);
  const Int_t nEtaBinF = hPtEtaWgt->GetYaxis()->FindBin(fV0CutMaxEta - 1e-9);

  for (Int_t l=1; l<=hPtEtaWgt->GetNbinsX(); l++) {
    Double_t dVarBkgRD = hR_RD->GetBinContent(l); if (TMath::Abs(dVarBkgRD)<1e-12) dVarBkgRD = 1e-12;
    Double_t dErrBkgRD = hR_RD->GetBinError(l) / dVarBkgRD;

    Double_t dVarBkgJE = hR_JE->GetBinContent(l); if (TMath::Abs(dVarBkgJE)<1e-12) dVarBkgJE = 1e-12;
    Double_t dErrBkgJE = hR_JE->GetBinError(l) / dVarBkgJE;

    for (Int_t k=nEtaBinI; k<=nEtaBinF; k++) {
      Double_t dVarInc = hPtEtaInc->GetBinContent(l,k); if (TMath::Abs(dVarInc)<1e-12) dVarInc = 1e-12;
      Double_t dErrInc = hPtEtaInc->GetBinError(l,k) / dVarInc;
    
      Double_t dVarJet = hPtEtaJet->GetBinContent(l,k); if (TMath::Abs(dVarJet)<1e-12) dVarJet = 1e-12;
      Double_t dErrJet = hPtEtaJet->GetBinError(l,k) / dVarJet;

      Double_t dVarWgt = (dVarJet / (1. + dVarBkgJE)) / (dVarInc / (1. + dVarBkgRD)); 
      Double_t dErrWgt = dVarWgt * TMath::Sqrt(dErrBkgRD*dErrBkgRD + dErrBkgJE*dErrBkgJE + dErrInc*dErrInc + dErrJet*dErrJet);
      hPtEtaWgt->SetBinContent(l,k,dVarWgt); hPtEtaWgt->SetBinError(l,k,dErrWgt);
    }
  }
//=============================================================================

  TH2D *hPtEtaRecoUW = (TH2D*)hPtEtaWgt->Clone("hPtEtaRecoUW"); hPtEtaRecoUW->Reset();
  TH2D *hPtEtaKineUW = (TH2D*)hPtEtaWgt->Clone("hPtEtaKineUW"); hPtEtaKineUW->Reset();

  TH2D *hPtEtaRecoWgt = (TH2D*)hPtEtaWgt->Clone("hPtEtaRecoWgt"); hPtEtaRecoWgt->Reset();
  TH2D *hPtEtaKineWgt = (TH2D*)hPtEtaWgt->Clone("hPtEtaKineWgt"); hPtEtaKineWgt->Reset();

  TH1D *hPtReco = 0;
  TH1D *hPtKine = 0;
  TH1D *hPtKineFB = 0;
  for (Int_t k=nEtaBinI; k<=nEtaBinF; k++) {
    hPtReco   = hPtEtaReco->ProjectionX(Form("hPtReco_%d",k), k, k);
    hPtKineFB = hPtEtaKineFB->ProjectionX(Form("hPtKineFB_%d",k), k, k);
    hPtKine   = RebinTH1D(hPtKineFB, hPtReco); hPtKine->SetName(Form("hPtKine_%d",k));

    TH1D *hEtaWgt = 0;
    for (Int_t l=1; l<=hPtReco->GetNbinsX(); l++) {
      hEtaWgt = hPtEtaWgt->ProjectionY(Form("hEtaWgt_%d_%d",k,l), l, l); hEtaWgt->Scale(1./hEtaWgt->Integral());

      Double_t dVarReco = hPtReco->GetBinContent(l);  if (TMath::Abs(dVarReco)<1e-12) dVarReco = 1e-12;
      Double_t dErrReco = hPtReco->GetBinError(l) / dVarReco;

      Double_t dVarKine = hPtKine->GetBinContent(l);  if (TMath::Abs(dVarKine)<1e-12) dVarKine = 1e-12;
      Double_t dErrKine = hPtKine->GetBinError(l) / dVarKine;

      Double_t dVarBkgF = hR_MC->GetBinContent(l);    if (TMath::Abs(dVarBkgF)<1e-12) dVarBkgF = 1e-12;
      Double_t dErrBkgF = hR_MC->GetBinError(l) / dVarBkgF;

      Double_t dVarWgtJ = hEtaWgt->GetBinContent(k); if (TMath::Abs(dVarWgtJ)<1e-12) dVarWgtJ = 1e-12;
      Double_t dErrWgtJ = hEtaWgt->GetBinError(k) / dVarWgtJ;

      Double_t dVarRecoUW = dVarReco / (1. + dVarBkgF);
      Double_t dErrRecoUW = dVarRecoUW * TMath::Sqrt(dErrReco*dErrReco + dErrBkgF*dErrBkgF);
      hPtEtaRecoUW->SetBinContent(l, k, dVarRecoUW); hPtEtaRecoUW->SetBinError(l, k, dErrRecoUW);

      Double_t dVarKineUW = dVarKine;
      Double_t dErrKineUW = dVarKineUW * TMath::Sqrt(dErrKine*dErrKine);
      hPtEtaKineUW->SetBinContent(l, k, dVarKineUW); hPtEtaKineUW->SetBinError(l, k, dErrKineUW);

      Double_t dVarRecoWgt = dVarWgtJ * dVarReco / (1. + dVarBkgF);
      Double_t dErrRecoWgt = dVarRecoWgt * TMath::Sqrt(dErrWgtJ*dErrWgtJ + dErrReco*dErrReco + dErrBkgF*dErrBkgF);
      hPtEtaRecoWgt->SetBinContent(l, k, dVarRecoWgt); hPtEtaRecoWgt->SetBinError(l, k, dErrRecoWgt);

      Double_t dVarKineWgt = dVarWgtJ * dVarKine;
      Double_t dErrKineWgt = dVarKineWgt * TMath::Sqrt(dErrWgtJ*dErrWgtJ + dErrKine*dErrKine);
      hPtEtaKineWgt->SetBinContent(l, k, dVarKineWgt); hPtEtaKineWgt->SetBinError(l, k, dErrKineWgt);

      delete hEtaWgt; hEtaWgt = 0;
    }

    delete hPtReco;   hPtReco   = 0;
    delete hPtKineFB; hPtKineFB = 0;
    delete hPtKine;   hPtKine   = 0;
  }
//=============================================================================

  TH1D *hPtRecoUW = hPtEtaRecoUW->ProjectionX("hPtRecoUW", nEtaBinI, nEtaBinF, "E");
  TH1D *hPtKineUW = hPtEtaKineUW->ProjectionX("hPtKineUW", nEtaBinI, nEtaBinF, "E");
  TH1D *hPtEffiUW = (TH1D*)hPtRecoUW->Clone("hPtEffiUW"); hPtEffiUW->Divide(hPtKineUW);

  TH1D *hPtRecoWgt = hPtEtaRecoWgt->ProjectionX("hPtReco", nEtaBinI, nEtaBinF, "E");
  TH1D *hPtKineWgt = hPtEtaKineWgt->ProjectionX("hPtKine", nEtaBinI, nEtaBinF, "E");
  TH1D *hPtEffiWgt = (TH1D*)hPtRecoWgt->Clone("hPtEffi"); hPtEffiWgt->Divide(hPtKineWgt);
//=============================================================================

  list->Add(hPtEffiWgt);
  list->Add(hPtRecoWgt);
  list->Add(hPtKineWgt);
  list->Add(hPtEtaRecoWgt);
  list->Add(hPtEtaKineWgt);

  list->Add(hPtEffiUW);
  list->Add(hPtRecoUW);
  list->Add(hPtKineUW);
  list->Add(hPtEtaRecoUW);
  list->Add(hPtEtaKineUW);

  list->Add(hPtEtaReco);
  list->Add(hPtEtaKineFB);
  list->Add(hPtEtaWgt);
  list->Add(hPtEtaInc);
  list->Add(hPtEtaJet);

  list->Add(hR_RD);
  list->Add(hR_JE);
  list->Add(hR_MC);

  file->cd(); list->Write(fListMakeEff.Data(), TObject::kSingleKey); file->Close();

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::AnaDeltaVJ(const TString sOpt, const TString sJet)
{
//
//  AliAnalysisTaskUserStraneJets::AnaDeltaVJ
//

  if (fFileFitInvM.IsNull() || fListFitInvM.IsNull()) return;
  if (fFileLoopJet.IsNull() || fListLoopJet.IsNull()) return;
  if ((sOpt!="Kshort") && (sOpt!="Lambda") && (sOpt!="AntiLa")) return;
    
  cout << "Analyzeing Delta eta -- Deleta phi for " << sOpt.Data() << " candidates..." << endl;
//=============================================================================

  TFile *file =  TFile::Open(Form("%s.root",fFileFitInvM.Data()), "READ"); if (!file->IsOpen()) return;
  TList *list = (TList*)file->Get(fListFitInvM.Data()); file->Close(); if (!list) return;

  TH1D *hFitPtInvM = (TH1D*)list->FindObject("hFitPtInvM"); if (!hFitPtInvM) return;
//=============================================================================

  const Double_t dPI    = TMath::Pi();
  const Double_t dTwoPI = TMath::TwoPi();
  file = TFile::Open(Form("%s.root",fFileLoopJet.Data()), "UPDATE");

cout<<"haha3"<<endl;
  list = (TList*)file->Get(fListLoopJet.Data()); if (list) { file->Close(); return; } else { list = new TList(); }

                                 // 0: centrality
cout<<"haha2"<<endl;
                                 // 1: jet pT
                                 // 2: jet eta
  const Int_t    nJetVar   = 4;  // 3: jet phi
  const Int_t    nJetBin[] = { 210,  200,  80, 200      };
  const Double_t dJetMin[] = { -10.,   0., -2., -1.*dPI };
  const Double_t dJetMax[] = { 200., 100.,  2.,  1.*dPI };
  THnSparseD *hsJet = new THnSparseD("hsJet", "", nJetVar, nJetBin, dJetMin, dJetMax); list->Add(hsJet);
                                 // 0: centrality
                                 // 1: V0 pT
                                 // 2: V0 eta
  const Int_t    nV0sVar   = 4;  // 3: V0 phi
  const Int_t    nV0sBin[] = { 210,  200,  80, 200      };
  const Double_t dV0sMin[] = { -10.,   0., -2., -1.*dPI };
  const Double_t dV0sMax[] = { 200., 100.,  2.,  1.*dPI };
  THnSparseD *hsV0s = new THnSparseD("hsV0s", "", nV0sVar, nV0sBin, dV0sMin, dV0sMax); list->Add(hsV0s);

                                 // 0: centrality
                                 // 1: jet pT
                                 // 2: jet eta
                                 // 3: jet phi
                                 // 4: V0 pT
                                 // 5: V0 eta
                                 // 6: V0 phi
                                 // 7: Delta eta
  const Int_t    nCorVar   = 9;  // 8: Delta phi
  const Int_t    nCorBin[] = { 210,  200,  80, 200,      200,  80, 200,      80, 200       };
  const Double_t dCorMin[] = { -10.,   0., -2., -1.*dPI,   0., -2., -1.*dPI, -2., -0.5*dPI };
  const Double_t dCorMax[] = { 200., 100.,  2.,  1.*dPI, 100.,  2.,  1.*dPI,  2.,  1.5*dPI };
  THnSparseD *hsCor = new THnSparseD("hsCor", "", nCorVar, nCorBin, dCorMin, dCorMax); list->Add(hsCor);
//=============================================================================

  Double_t dSN = fKaCutNS;
  if (sOpt!="Kshort") dSN = fLaCutNS;

  Int_t iEvent = 0;
  Double_t dJetVar[nJetVar];
  Double_t dV0sVar[nV0sVar];
  Double_t dCorVar[nCorVar];
  while (fChainRD->GetEntry(iEvent++)) if (InitEvent("PJ")) {

    Float_t dCent = 0.;
    //if (fCentralityEstimator=="V0M") dCent = fHeader->CentralityV0M();
    //if (fCentralityEstimator=="V0A") dCent = fHeader->CentralityV0A();
    //if (fCentralityEstimator=="CL1") dCent = fHeader->CentralityCL1();
    //if (fCentralityEstimator=="ZNA") dCent = fHeader->CentralityZNA();
    if (fCentralityEstimator=="V0M") dCent = fMult->GetMultiplicityPercentile("V0M");
    if (fCentralityEstimator=="V0A") dCent = fMult->GetMultiplicityPercentile("V0A");
    if (fCentralityEstimator=="CL1") dCent = fMult->GetMultiplicityPercentile("CL1");
    if (fCentralityEstimator=="ZNA") dCent = fMult->GetMultiplicityPercentile("ZNA");


    AliPicoV0RD *pV0 = 0;
    for (Int_t i=0; i<fV0sClArr->GetEntriesFast(); i++) {
      pV0 = (AliPicoV0RD*)fV0sClArr->At(i); if (!pV0) continue;
      if (!pV0->IsDausInEtaAcc(fV0CutMinDauEta,fV0CutMaxDauEta)) { pV0 = 0; continue; }
      if (fV0IsCutEta) { if (!pV0->IsV0InEtaAcc(fV0CutMinEta,fV0CutMaxEta)) { pV0 = 0; continue; } }

      Bool_t bKshort = kFALSE;
      Bool_t bLambda = kFALSE;
      Bool_t bAntiLa = kFALSE;
      if (sOpt=="Kshort") { if (fV0IsCutRap) { bKshort = pV0->IsKaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bKshort = kTRUE; } }
      if (sOpt=="Lambda") { if (fV0IsCutRap) { bLambda = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bLambda = kTRUE; } }
      if (sOpt=="AntiLa") { if (fV0IsCutRap) { bAntiLa = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bAntiLa = kTRUE; } }
      if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }

      if (bKshort) bKshort = pV0->IsKshort(fKaCuts);
      if (bLambda) bLambda = pV0->IsLambda(fLaCuts);
      if (bAntiLa) bAntiLa = pV0->IsAntiLa(fLaCuts);
      if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }

      TLorentzVector vV0;
      if (bKshort) vV0 = pV0->KineKshort();
      if (bLambda) vV0 = pV0->KineLambda();
      if (bAntiLa) vV0 = pV0->KineAntiLa();

      Double_t dV0Pt = vV0.Pt();
      Double_t dInvM = vV0.M();
      Int_t k = hFitPtInvM->FindBin(dV0Pt); if (k<=0) { pV0 = 0; continue; }

      Double_t dMean  = hFitPtInvM->GetBinContent(k);
      Double_t dSigma = hFitPtInvM->GetBinError(k);

      Double_t dUpperL = dMean - 1.*dSN*dSigma;
      Double_t dLowerR = dMean + 1.*dSN*dSigma;

      if  ((dInvM>dUpperL) && (dInvM<dLowerR)) {
        dV0sVar[0] = dCent;
        dV0sVar[1] = dV0Pt;
        dV0sVar[2] = vV0.Eta();
        dV0sVar[3] = TVector2::Phi_mpi_pi(vV0.Phi());
        hsV0s->Fill(dV0sVar);
      }

      pV0 = 0;
    }
//=============================================================================

    TClonesArray *pJetsClArr = GetJets(sJet);   if (!pJetsClArr) continue;
    Int_t nJets = pJetsClArr->GetEntriesFast(); if (nJets  <= 0) continue;
    if (IsJetNotInMultRange(pJetsClArr,sJet)) continue;
//=============================================================================

    AliPicoJet *pJet = 0;
    for (Int_t j=0; j<nJets; j++) {
      pJet = (AliPicoJet*)pJetsClArr->At(j); if (!pJet) continue;
      if (IsJetNotSelected(pJet,sJet)) { pJet = 0; continue; }

      //Double_t dJePt  = pJet->Kine().Pt() - (pJet->Area() * fHeader->BackgroundRho(sJet));
      Double_t dJePt  = pJet->Kine().Pt() - (pJet->Area() * fHeader->BackgroundRho());
      Double_t dJePhi = TVector2::Phi_mpi_pi(pJet->Kine().Phi());
      Double_t dJeEta = pJet->Kine().Eta();

      dJetVar[0] = dCent;
      dJetVar[1] = dJePt;
      dJetVar[2] = dJeEta;
      dJetVar[3] = dJePhi;
      hsJet->Fill(dJetVar);

      for (Int_t i=0; i<fV0sClArr->GetEntriesFast(); i++) {
        pV0 = (AliPicoV0RD*)fV0sClArr->At(i); if (!pV0) continue;
        if (!pV0->IsDausInEtaAcc(fV0CutMinDauEta,fV0CutMaxDauEta)) { pV0 = 0; continue; }
        if (fV0IsCutEta) { if (!pV0->IsV0InEtaAcc(fV0CutMinEta,fV0CutMaxEta)) { pV0 = 0; continue; } }

        Bool_t bKshort = kFALSE;
        Bool_t bLambda = kFALSE;
        Bool_t bAntiLa = kFALSE;
        if (sOpt=="Kshort") { if (fV0IsCutRap) { bKshort = pV0->IsKaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bKshort = kTRUE; } }
        if (sOpt=="Lambda") { if (fV0IsCutRap) { bLambda = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bLambda = kTRUE; } }
        if (sOpt=="AntiLa") { if (fV0IsCutRap) { bAntiLa = pV0->IsLaInRapAcc(fV0CutMinRap,fV0CutMaxRap); } else { bAntiLa = kTRUE; } }
        if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }

        if (bKshort) bKshort = pV0->IsKshort(fKaCuts);
        if (bLambda) bLambda = pV0->IsLambda(fLaCuts);
        if (bAntiLa) bAntiLa = pV0->IsAntiLa(fLaCuts);
        if (!(bKshort || bLambda || bAntiLa)) { pV0 = 0; continue; }

        TLorentzVector vV0;

        if (bLambda) vV0 = pV0->KineLambda();
        if (bAntiLa) vV0 = pV0->KineAntiLa();

        Double_t dV0Pt = vV0.Pt();
        Double_t dInvM = vV0.M();
        Int_t k = hFitPtInvM->FindBin(dV0Pt); if (k<=0) { pV0 = 0; continue; }

        Double_t dMean  = hFitPtInvM->GetBinContent(k);
        Double_t dSigma = hFitPtInvM->GetBinError(k);

        Double_t dUpperL = dMean - 1.*dSN*dSigma;
        Double_t dLowerR = dMean + 1.*dSN*dSigma;

        if  ((dInvM>dUpperL) && (dInvM<dLowerR)) {
          Double_t dV0Eta = vV0.Eta();
          Double_t dV0Phi = TVector2::Phi_mpi_pi(vV0.Phi());

          Double_t dDeEta = dV0Eta - dJeEta;
          Double_t dDePhi = dV0Phi - dJePhi;
          if (dDePhi<-0.5*dPI) dDePhi += dTwoPI;
          if (dDePhi>=1.5*dPI) dDePhi -= dTwoPI;

          dCorVar[0] = dCent;
          dCorVar[1] = dJePt;
          dCorVar[2] = dJeEta;
          dCorVar[3] = dJePhi;
          dCorVar[4] = dV0Pt;
          dCorVar[5] = dV0Eta;
          dCorVar[6] = dV0Phi;
          dCorVar[7] = dDeEta;
          dCorVar[8] = dDePhi;
          hsCor->Fill(dCorVar);
        }

        pV0 = 0;
      }

      pJet = 0;
    }

    pJetsClArr = 0;
  }
//=============================================================================

  file->cd(); list->Write(fListLoopJet.Data(), TObject::kSingleKey); file->Close();

  return;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskUserStraneJets::InitEvent(const TString sOpt)
{
//
//  AliAnalysisTaskUserStraneJets::IsEventSelected
//

  if (!(fChainRD || fChainMC)) return kFALSE;
  if (!(fEventRD || fEventMC)) return kFALSE;
//=============================================================================

  const Bool_t bP = sOpt.Contains("P");
  const Bool_t bJ = sOpt.Contains("J");

  if (!(bP || bJ)) return kFALSE;
//=============================================================================

  if (fEventRD) {
    fHeader = (AliPicoHeaderJet*)fEventRD->FindListObject("PicoHeaderJet");
    if (!fHeader){ cout<<"can not find header"<<endl; return kFALSE;}
    if(fIon){
      fMult = (AliMultSelection*)fEventRD->FindListObject("MultSelection");
      if (!fMult){ cout<<"can not find mult"<<endl; return kFALSE;}

      Float_t dCent = 0.;
      if (fCentralityEstimator=="V0M") dCent = fMult->GetMultiplicityPercentile("V0M");
      if (fCentralityEstimator=="V0A") dCent = fMult->GetMultiplicityPercentile("V0A");
      if (fCentralityEstimator=="CL1") dCent = fMult->GetMultiplicityPercentile("CL1");
      if (fCentralityEstimator=="ZNA") dCent = fMult->GetMultiplicityPercentile("ZNA");
      if ((dCent<fCentralityMin) || (dCent>=fCentralityMax)) return kFALSE;
    }

    if (bP) {
      fV0sClArr = (TClonesArray*)fEventRD->FindListObject("PicoV0sRD");
      if (!fV0sClArr) { cout<<"can not find v0s"<<endl; return kFALSE;}
      
      fCascadesClArr = (TClonesArray*)fEventRD->FindListObject("PicoCascadeRD");
      if (!fCascadesClArr) { cout<<"can not find Cascades"<<endl; return kFALSE;}
    }

    if (bJ) {
      fJetsRD02ClArr = (TClonesArray*)fEventRD->FindListObject("PicoJet_AKTChargedR020_tracks_pT0150_pt_scheme");
      fJetsRD03ClArr = (TClonesArray*)fEventRD->FindListObject("PicoJet_AKTChargedR030_tracks_pT0150_pt_scheme");
      fJetsRD04ClArr = (TClonesArray*)fEventRD->FindListObject("PicoJet_AKTChargedR040_tracks_pT0150_pt_scheme");
      if ((!fJetsRD02ClArr) && (!fJetsRD03ClArr) && (!fJetsRD04ClArr)){cout<<"can not find jets"<<endl; return kFALSE;}
    }
  }

  if (fEventMC) {
    fHeader = (AliPicoHeaderJet*)fEventMC->FindListObject("PicoHeaderJet");
    if (!fHeader) return kFALSE;

    if(fIon){
      fMult = (AliMultSelection*)fEventMC->FindListObject("MultSelection");
      if (!fMult){ cout<<"can not find mult"<<endl; return kFALSE;}

      Float_t dCent = 0.;
      if (fCentralityEstimator=="V0M") dCent = fMult->GetMultiplicityPercentile("V0M");
      if (fCentralityEstimator=="V0A") dCent = fMult->GetMultiplicityPercentile("V0A");
      if (fCentralityEstimator=="CL1") dCent = fMult->GetMultiplicityPercentile("CL1");
      if (fCentralityEstimator=="ZNA") dCent = fMult->GetMultiplicityPercentile("ZNA");
      if ((dCent<fCentralityMin) || (dCent>=fCentralityMax)) return kFALSE;
      
    }


    if (bP) {
      fV0sClArr  = (TClonesArray*)fEventMC->FindListObject("PicoV0sMC");
      if (!fV0sClArr) return kFALSE;
      fCascadesClArr  = (TClonesArray*)fEventMC->FindListObject("PicoCascadeMC");
      if (!fCascadesClArr) { cout<<"can not find Cascades"<<endl; return kFALSE;}

    }

    if (bJ) {
      fJetsRD02ClArr = (TClonesArray*)fEventMC->FindListObject("PicoJetsRD02");
      fJetsRD03ClArr = (TClonesArray*)fEventMC->FindListObject("PicoJetsRD03");
      fJetsRD04ClArr = (TClonesArray*)fEventMC->FindListObject("PicoJetsRD04");

      fJetsMC02ClArr = (TClonesArray*)fEventMC->FindListObject("PicoJetsMC02");
      fJetsMC03ClArr = (TClonesArray*)fEventMC->FindListObject("PicoJetsMC03");
      fJetsMC04ClArr = (TClonesArray*)fEventMC->FindListObject("PicoJetsMC04");

      if ((!fJetsRD02ClArr) && (!fJetsRD03ClArr) && (!fJetsRD04ClArr) &&
          (!fJetsMC02ClArr) && (!fJetsMC03ClArr) && (!fJetsMC04ClArr)) return kFALSE;
    }
  }
//=============================================================================


  if (fTriggerMask) {
    UInt_t wMask = fHeader->PhysSelMask();
    if ((fTriggerMask & wMask) != fTriggerMask) return kFALSE;
  }

  if (!fTriggerClass.IsNull()) {
    TString sTrigger = fHeader->FiredTriggerClass();
    if (!sTrigger.Contains(fTriggerClass)) return kFALSE;
  }

//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskUserStraneJets::IsJetNotInMultRange(TClonesArray const *pJetsClArr, const TString sJet)
{
//
//  AliAnalysisTaskUserStraneJets::IsJetNotInMultRange
//

  if ((!pJetsClArr) || sJet.IsNull()) return kTRUE;
//=============================================================================

  if (fJetCutMinMulti<0) return kFALSE;
//=============================================================================

  Int_t nJets = SelectedJetsN(pJetsClArr,sJet);

  if (nJets<fJetCutMinMulti) return kTRUE;
  if ((fJetCutMaxMulti>=fJetCutMinMulti) && (nJets>fJetCutMaxMulti)) return kTRUE;

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskUserStraneJets::IsRefNotInMultRange(TClonesArray const *pRefsClArr, const TString sRef)
{
//
//  AliAnalysisTaskUserStraneJets::IsRefNotInMultRange
//

  if ((!pRefsClArr) || sRef.IsNull()) return kTRUE;
//=============================================================================

  if (fRefCutMinMulti<0) return kFALSE;
//=============================================================================

  Int_t nRefs = SelectedRefsN(pRefsClArr,sRef);

  if (nRefs<fRefCutMinMulti) return kTRUE;
  if ((fRefCutMaxMulti>=fRefCutMinMulti) && (nRefs>fRefCutMaxMulti)) return kTRUE;

  return kFALSE;
}

//_____________________________________________________________________________
Int_t AliAnalysisTaskUserStraneJets::SelectedJetsN(TClonesArray const *pJetsClArr, const TString sJet)
{
//
//  AliAnalysisTaskUserStraneJets::SelectedJetsN
//

  if ((!pJetsClArr) || sJet.IsNull()) return -1;
//=============================================================================

  Int_t nJets = 0;
  AliPicoJet *pJet = 0;
  for (Int_t j=0; j<pJetsClArr->GetEntriesFast(); j++) {
    pJet = (AliPicoJet*)pJetsClArr->At(j); if (!pJet) continue;
    if (IsJetNotSelected(pJet,sJet)) { pJet = 0; continue; }
    nJets += 1;
    pJet = 0;
  }

  return nJets;
}

//_____________________________________________________________________________
Int_t AliAnalysisTaskUserStraneJets::SelectedRefsN(TClonesArray const *pRefsClArr, const TString sRef)
{
//
//  AliAnalysisTaskUserStraneJets::SelectedJetsN
//

  if ((!pRefsClArr) || sRef.IsNull()) return -1;
//=============================================================================

  Int_t nRefs = 0;
  AliPicoJet *pRef = 0;
  for (Int_t j=0; j<pRefsClArr->GetEntriesFast(); j++) {
    pRef = (AliPicoJet*)pRefsClArr->At(j); if (!pRef) continue;
    if (IsRefNotSelected(pRef,sRef)) { pRef = 0; continue; }
    nRefs += 1;
    pRef = 0;
  }

  return nRefs;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskUserStraneJets::IsJetNotSelected(AliPicoJet const *pJet, const TString sJet)
{
//
//  AliAnalysisTaskUserStraneJets::IsJetNotSelected
//

  if ((!pJet) || sJet.IsNull()) return kTRUE;
//=============================================================================

  Double_t dPt = pJet->Kine().Pt();

  if (fJetUseEstiPt) {
    //dPt -= (pJet->Area() * fHeader->BackgroundRho(sJet));
    dPt -= (pJet->Area() * fHeader->BackgroundRho());

    if (fHistoDetectorRM) {
      Int_t k = fHistoDetectorRM->GetXaxis()->FindBin(dPt);
      TH1D *h = fHistoDetectorRM->ProjectionY("h", k, k);
      dPt = h->GetRandom(); delete h; h = 0;
    }
  }
//=============================================================================

  if (dPt<fJetCutMinPt) return kTRUE;
  if ((fJetCutMaxPt>fJetCutMinPt) && (dPt>=fJetCutMaxPt)) return kTRUE;

  Double_t dEta = pJet->Kine().Eta();

//  if(dEta>0.48) cout<<"dEta = "<<dEta<<endl; 

  if ((dEta<fJetCutMinEta) || (dEta>=fJetCutMaxEta)) return kTRUE;

  Double_t dPhi = pJet->Kine().Phi();
  if ((dPhi<=fJetCutMinPhi) || (dPhi>=fJetCutMaxPhi)) return kTRUE;
//=============================================================================

  Double_t dJR = 0.;
  if (sJet.Contains("02")) dJR = 0.2;
  if (sJet.Contains("03")) dJR = 0.3;
  if (sJet.Contains("04")) dJR = 0.4;
  if (pJet->Area()<(fJetCutMinAreaFrac * TMath::Pi() * dJR * dJR)) return kTRUE;
//=============================================================================

  if (pJet->LeadingPt()<fJetCutMinLeadingPt) return kTRUE;

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskUserStraneJets::IsRefNotSelected(AliPicoJet const *pRef, const TString sRef)
{
//
//  AliAnalysisTaskUserStraneJets::IsRefNotSelected
//

  if ((!pRef) || sRef.IsNull()) return kTRUE;
//=============================================================================

  Double_t dPt = pRef->Kine().Pt();

  if (fJetUseEstiPt) {
    //dPt -= (pRef->Area() * fHeader->BackgroundRho(sRef));
    dPt -= (pRef->Area() * fHeader->BackgroundRho());

    if (fHistoDetectorRM) {
      Int_t k = fHistoDetectorRM->GetXaxis()->FindBin(dPt);
      TH1D *h = fHistoDetectorRM->ProjectionY("h", k, k);
      dPt = h->GetRandom(); delete h; h = 0;
    }
  }
//=============================================================================

  if (dPt<fRefCutMinPt) return kTRUE;
  if ((fRefCutMaxPt>fRefCutMinPt) && (dPt>=fRefCutMaxPt)) return kTRUE;

  Double_t dEta = pRef->Kine().Eta();
  if ((dEta<fRefCutMinEta) || (dEta>=fRefCutMaxEta)) return kTRUE;

  Double_t dPhi = pRef->Kine().Phi();
  if ((dPhi<=fRefCutMinPhi) || (dPhi>=fRefCutMaxPhi)) return kTRUE;
//=============================================================================

  Double_t dRR = 0.;
  if (sRef.Contains("02")) dRR = 0.2;
  if (sRef.Contains("03")) dRR = 0.3;
  if (sRef.Contains("04")) dRR = 0.4;
  if (pRef->Area()<(fRefCutMinAreaFrac * TMath::Pi() * dRR * dRR)) return kTRUE;
//=============================================================================

  if (pRef->LeadingPt()<fRefCutMinLeadingPt) return kTRUE;

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskUserStraneJets::IsStrangeInJetRange(TVector3 vStrange, TClonesArray const *pJetsClArr, const TString sJet)
{
//
//  AliAnalysisTaskUserStraneJets::IsStrangeInJetRange
//

  if (!pJetsClArr) return kFALSE;
//=============================================================================

  TVector3 vJet, vJPC;
  AliPicoJet *pJet = 0;
  for (Int_t j=0; j<pJetsClArr->GetEntriesFast(); j++) {
    pJet = (AliPicoJet*)pJetsClArr->At(j); if (!pJet) continue;
    if (IsJetNotSelected(pJet,sJet)) {  pJet = 0; continue; }

    vJet = pJet->Kine().Vect();
    if (fIsStrangeInPCL || fIsStrangeInPCU) {
      Double_t dPx = vJet.Px();
      Double_t dPy = vJet.Py();
      Double_t dPz = vJet.Pz();

      if (fIsStrangeInPCL) {
        vJPC.SetXYZ(dPx, dPy, dPz); vJPC.RotateZ(TMath::PiOver2());
        if (vStrange.DeltaR(vJPC)<fInJetCutR) return kTRUE;

        vJPC.SetXYZ(dPx, dPy, dPz); vJPC.RotateZ(-1.*TMath::PiOver2());
        if (vStrange.DeltaR(vJPC)<fInJetCutR) return kTRUE;
      }

      if (fIsStrangeInPCU) {
        vJPC.SetXYZ(dPx, dPy, -1.*dPz); vJPC.RotateZ(TMath::PiOver2());
        if (vStrange.DeltaR(vJPC)<fInJetCutR) return kTRUE;

        vJPC.SetXYZ(dPx, dPy, -1.*dPz); vJPC.RotateZ(-1.*TMath::PiOver2());
        if (vStrange.DeltaR(vJPC)<fInJetCutR) return kTRUE;
      }
    } else {
      Double_t dDeltaR = vStrange.DeltaR(vJet);

      if (fIsStrangeInJet) {
        if (dDeltaR<fInJetCutR) return kTRUE;
      } else {
        if (dDeltaR<fBkgParCutR) return kTRUE;
      }
    }

    pJet = 0;
  }

  return kFALSE;
}

//_____________________________________________________________________________
TClonesArray* AliAnalysisTaskUserStraneJets::GetJets(const TString sJet)
{
//
//  AliAnalysisTaskUserStraneJets::GetJets
//

  if (sJet.IsNull()) return 0x0;
//=============================================================================

  if (sJet=="RD02") return fJetsRD02ClArr;
  if (sJet=="RD03") return fJetsRD03ClArr;
  if (sJet=="RD04") return fJetsRD04ClArr;

  if (sJet=="MC02") return fJetsMC02ClArr;
  if (sJet=="MC03") return fJetsMC03ClArr;
  if (sJet=="MC04") return fJetsMC04ClArr;
//=============================================================================

  return 0x0;
}

//_____________________________________________________________________________
TClonesArray* AliAnalysisTaskUserStraneJets::GetJets(const TString sJet, const TString sRef)
{
//
//  AliAnalysisTaskUserStraneJets::MakeJetBranch
//

  if (sJet.IsNull() || sRef.IsNull()) return 0x0;
//=============================================================================

  TClonesArray *pJetsClArr = GetJets(sJet); if (!pJetsClArr) return 0x0;
  Int_t nJets = pJetsClArr->GetEntriesFast();  if (nJets<=0) { pJetsClArr = 0; return 0x0; }

  TClonesArray *pRefsClArr = GetJets(sRef); if (!pRefsClArr) { pJetsClArr = 0; return 0x0; }
  Int_t nRefs = pRefsClArr->GetEntriesFast();  if (nRefs<=0) { pRefsClArr = 0; pJetsClArr = 0; return 0x0; }
//=============================================================================

  TClonesArray *pTagsClArr = new TClonesArray("AliPicoJet");
  pTagsClArr->SetName(Form("PicoJets_%s_%s",sJet.Data(),sRef.Data()));
  Int_t ncs = pTagsClArr->GetEntriesFast(); 
//=============================================================================


  AliPicoJet *pJet = 0;
  AliPicoJet *pRef = 0;
  for (Int_t j=0; j<nJets; j++) {
    pJet = (AliPicoJet*)pJetsClArr->At(j);

    if (!pJet) continue;
    if (IsJetNotSelected(pJet,sJet))  { pJet = 0; continue; }
//=============================================================================

    pRef = GetMatchedJet(pJet,pRefsClArr,sJet,sRef);

    if (!pRef) { pJet = 0; continue; }
    if (IsRefNotSelected(pRef,sRef))  { pRef = 0; pJet = 0; continue; }
//=============================================================================

    new ((*pTagsClArr)[ncs++]) AliPicoJet(*pJet);

    pRef = 0;
    pJet = 0;
  }

  pJetsClArr = 0;
  pRefsClArr = 0;
  return pTagsClArr;
}

//_____________________________________________________________________________
AliPicoJet* AliAnalysisTaskUserStraneJets::GetMatchedJet(AliPicoJet   const *pJet,
                                                         TClonesArray const *pRefsClArr,
                                                         const TString sJet,
                                                         const TString sRef)
{
//
//  AliAnalysisTaskUserStraneJets::GetMatchedJet
//

  if ((!pJet) || (!pRefsClArr)) return 0x0;
  if (sJet.IsNull() || sRef.IsNull()) return 0x0;
//=============================================================================

  Double_t dJetR = 0.;
  if (sJet.Contains("02")) dJetR = 0.2;
  if (sJet.Contains("03")) dJetR = 0.3;
  if (sJet.Contains("04")) dJetR = 0.4;

  Double_t dRefR = 0.;
  if (sRef.Contains("02")) dRefR = 0.2;
  if (sRef.Contains("03")) dRefR = 0.3;
  if (sRef.Contains("04")) dRefR = 0.4;

  const Double_t dRing = TMath::Abs(dJetR - dRefR);
//=============================================================================

  Int_t iJ = -1;
  AliPicoJet *pRef = 0, *pTmp = 0;
  TVector3 vJet = pJet->Kine().Vect();
  for (Int_t j=0; j<pRefsClArr->GetEntriesFast(); j++) {
    pRef = (AliPicoJet*)pRefsClArr->At(j); if (!pRef) continue;
    Double_t dDeltaR = pRef->Kine().Vect().DeltaR(vJet);

    if (dDeltaR<dRing) {
      if (iJ>=0) {
        pTmp = (AliPicoJet*)pRefsClArr->At(iJ);
        if (pTmp->Kine().Vect().DeltaR(vJet)>dDeltaR) iJ = j;
        pTmp = 0;
      } else {
        iJ = j;
      }
    }

    pRef = 0;
  } if (iJ<0) return 0x0;
//=============================================================================

  pRef = (AliPicoJet*)pRefsClArr->At(iJ);
  return pRef;
}

//_____________________________________________________________________________
Double_t AliAnalysisTaskUserStraneJets::BackgroundStrangeFit(Double_t const *x,  Double_t const *par)
{
//
//  AliAnalysisTaskUserStraneJets::BackgroundStrangeFit
//

  if ((x[0]>par[2]) && (x[0]<par[3])) {
    TF1::RejectPoint();
    return 0.;
  }

  return (par[0] + par[1]*x[0]);
}

//_____________________________________________________________________________
Double_t AliAnalysisTaskUserStraneJets::BackgroundStrangeVal(Double_t const *x,  Double_t const *par)
{
//
//  AliAnalysisTaskUserStraneJets::BackgroundStrangeVal
//

  return (par[0] + par[1]*x[0]);
}

//_____________________________________________________________________________
TH1D* AliAnalysisTaskUserStraneJets::RebinTH1D(TH1D const *hF, TH1D const *hR)
{
//
//  AliAnalysisTaskUserStraneJets::RebinTH1D
//

  if ((!hF) || (!hR)) return 0x0;
//=============================================================================

  const Int_t nt = hR->GetNbinsX();
  const Int_t n  = nt;

  Double_t d[n+1];
  d[n] = hR->GetXaxis()->GetBinUpEdge(n);
  for (Int_t i=0, k=1; i<n; i++, k++) d[i] = hR->GetXaxis()->GetBinLowEdge(k);

  TH1D *hN = new TH1D(Form("hN_%s_%s",hF->GetName(),hR->GetName()), "", n, d); hN->Sumw2();

  for (Int_t k=1; k<=hF->GetNbinsX(); k++) {
    Double_t dXvar = hF->GetBinCenter(k);
    if ((dXvar<d[0]) || (dXvar>=d[n])) continue;

    Double_t dYvar = hF->GetBinContent(k);
    Double_t dYerr = hF->GetBinError(k);

    Int_t nb = hN->FindBin(dXvar);
    Double_t dYsw2 = hN->GetBinError(nb);

    hN->SetBinContent(nb, dYvar + hN->GetBinContent(nb));
    hN->SetBinError(nb, TMath::Sqrt(dYerr*dYerr + dYsw2*dYsw2));
  }

  return hN;
}

//_____________________________________________________________________________
TH2D* AliAnalysisTaskUserStraneJets::RebinTH2D(TH2D const *hF, TH2D const *hR){

  if ((!hF) || (!hR)) return 0x0;
  const Int_t nx1 = hR->GetNbinsX();
  const Int_t ny1 = hR->GetNbinsY();
  const Int_t nx = nx1;
  const Int_t ny = ny1;

  Double_t dx[nx+1];
  Double_t dy[ny+1];

  dx[nx] = hR->GetXaxis()->GetBinUpEdge(nx);
  dy[ny] = hR->GetYaxis()->GetBinUpEdge(ny);
  for (Int_t i=0, k=1; i<nx; i++, k++) dx[i] = hR->GetXaxis()->GetBinLowEdge(k);
  for (Int_t j=0, l=1; j<ny; j++, l++) dy[j] = hR->GetYaxis()->GetBinLowEdge(l);

  TH2D *hN = new TH2D(Form("hN_%s_%s",hF->GetName(),hR->GetName()), "", nx, dx, ny, dy); hN->Sumw2();
  hN->Reset();

  for (Int_t k=1; k<=hF->GetNbinsX(); k++) {
    Double_t dXvar = hF->GetXaxis()->GetBinCenter(k);
    if ((dXvar<dx[0]) || (dXvar>=dx[nx])) continue;

    for (Int_t l=1; l<=hF->GetNbinsY(); l++) {
      Double_t dYvar = hF->GetYaxis()->GetBinCenter(l);
      if ((dYvar<dy[0]) || (dYvar>=dy[ny])) continue;

      Double_t dvar = hF->GetBinContent(k, l);
      Double_t derr = hF->GetBinError(k, l);

      Int_t nbx = hN->GetXaxis()->FindBin(dXvar);
      Int_t nby = hN->GetYaxis()->FindBin(dYvar);
      Double_t dsw2 = hN->GetBinError(nbx, nby);

      hN->SetBinContent(nbx, nby, dvar + hN->GetBinContent(nbx, nby));
      hN->SetBinError(nbx, nby, TMath::Sqrt(derr*derr + dsw2*dsw2));
    }
  }

  return hN;
}
      
//_____________________________________________________________________________
Bool_t AliAnalysisTaskUserStraneJets::SetJetPtBinning(const Int_t n, Double_t const *d)
{
//
//  AliAnalysisTaskUserStraneJets::SetJetPtBinning
//

  if (n<=0) return kTRUE;

  fJetPtBinN = n;
  fJetPtBinA = new Double_t[n+1];
  for (Int_t i=0; i<=n; i++) fJetPtBinA[i] = d[i];

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskUserStraneJets::SetKaPtBinning(const Int_t n, Double_t const *d)
{
//
//  AliAnalysisTaskUserStraneJets::SetKaPtBinning
//

  if (n<=0) return kTRUE;

  fKaPtBinN = n;
  fKaPtBinA = new Double_t[n+1];
  for (Int_t i=0; i<=n; i++) fKaPtBinA[i] = d[i];

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskUserStraneJets::SetLaPtBinning(const Int_t n, Double_t const *d)
{
//
//  AliAnalysisTaskUserStraneJets::SetLaPtBinning
//

  if (n<=0) return kTRUE;

  fLaPtBinN = n;
  fLaPtBinA = new Double_t[n+1];
  for (Int_t i=0; i<=n; i++) fLaPtBinA[i] = d[i];

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskUserStraneJets::SetXiPtBinning(const Int_t n, Double_t const *d)
{
//
//  AliAnalysisTaskUserStraneJets::SetXiPtBinning
//

  if (n<=0) return kTRUE;

  fXiPtBinN = n;
  fXiPtBinA = new Double_t[n+1];
  for (Int_t i=0; i<=n; i++) fXiPtBinA[i] = d[i];

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskUserStraneJets::SetOmegaPtBinning(const Int_t n, Double_t const *d)
{
//
//  AliAnalysisTaskUserStraneJets::SetOmegaPtBinning
//

  if (n<=0) return kTRUE;

  fOmegaPtBinN = n;
  fOmegaPtBinA = new Double_t[n+1];
  for (Int_t i=0; i<=n; i++) fOmegaPtBinA[i] = d[i];

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskUserStraneJets::SetInputEventsRD(TChain *chain)
{
//
//  AliAnalysisTaskUserStraneJets::SetInputEventsRD
//
  
  fChainRD = chain; if (!fChainRD) return kTRUE;
  fChainRD->GetEntry(0);

  fEventRD = new AliAODEvent(); 

  fEventRD->ReadFromTree(fChainRD);

  //fHeader = (AliPicoHeaderCJ*)fEventRD->FindListObject("PicoHeaderCJ");
  fHeader = (AliPicoHeaderJet*)fEventRD->FindListObject("PicoHeaderJet");
  if (!fHeader){ cout<<"InputEvent can not find header"<<endl; return kFALSE;}

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskUserStraneJets::SetInputEventsMC(TChain *chain)
{
//
//  AliAnalysisTaskUserStraneJets::SetInputEventsMC
//
  
  fChainMC = chain; if (!fChainMC) return kTRUE;
  fEventMC = new AliAODEvent(); fEventMC->ReadFromTree(fChainMC);
 

  return kFALSE;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::SetDefaultKaCutsPA()
{
//
//  AliAnalysisTaskUserStraneJets::SetDelfaultKaCutsPA
//

  Double_t dCuts[] = {
    0.5,    // min Radius
    0.97,   // min cosPA
    20.,    // max ctau
    1.,     // max daus DCA
    0.06,   // min pos DCA to PV
    0.06,   // min neg DCA to PV
    70.,    // min dau Xrows TPC
    0.8,    // min dau Xrows / Findable Clus in TPC
    0.005,  // min delta comp mass
    5.      // max sigma PID in TPC
  };

  fKaCutNS = 6.;
  SetKaCuts(dCuts);

  return;
}

void AliAnalysisTaskUserStraneJets::SetDefaultKaCutsPP()
{
   Double_t dCuts[] = {
    0.5,    // min Radius
    0.97,   // min cosPA
    20.,    // max ctau
    1.,     // max daus DCA
    0.06,   // min pos DCA to PV
    0.06,   // min neg DCA to PV
    75.,    // min dau Xrows TPC
    0.8,    // min dau Xrows / Findable Clus in TPC
    0.005,  // min delta comp mass
    5.      // max sigma PID in TPC
  };

  fKaCutNS = 6.;
  SetKaCuts(dCuts);

  return;


}
//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::SetDefaultLaCutsPA()
{

  Double_t dCuts[] = {
    0.5,    // min Radius
    0.995,  // min cosPA
    30.,    // max ctau
    1.,     // max daus DCA
    0.06,   // min pos DCA to PV
    0.06,   // min neg DCA to PV
    70.,    // min dau Xrows TPC
    0.8,    // min dau Xrows / Findable Clus in TPC
    0.01,   // min delta comp mass
    5.      // max sigma PID in TPC
  };
  fLaCutNS = 6.;
  SetLaCuts(dCuts);
  return;
}
void AliAnalysisTaskUserStraneJets::SetDefaultLaCutsPP()
{
   Double_t dCuts[] = {
    0.5,    // min Radius
    0.995,  // min cosPA
    30.,    // max ctau
    1.,     // max daus DCA
    0.06,   // min pos DCA to PV
    0.06,   // min neg DCA to PV
    70.,    // min dau Xrows TPC
    0.8,    // min dau Xrows / Findable Clus in TPC
    0.01,   // min delta comp mass
    5.      // max sigma PID in TPC
  };
  fLaCutNS = 6.;
  SetLaCuts(dCuts);
  return;
}

//_____________________________________________________________________________

void AliAnalysisTaskUserStraneJets::SetDefaultXiCutsPP()
{
  Double_t dCuts[] = {1.4,   // [ 0] V0 MinRadius,
                      0.97,  // [ 1] V0 MinCosPA,
                      1000., // [ 2] V0 MaxCtau,
                      1.6,   // [ 3] V0 MaxDausDCA,
                      0.04,  // [ 4] V0 MinPosDCAtoPV,
                      0.04,  // [ 5] V0 MinNegDCAtoPV,
                      70.,   // [ 6] V0 MinDauXrowsTPC,
                      0.8,   // [ 7] V0 MinDauXrowsOverFindableClusTPC,
                      -1.,   // [ 8] V0 MinDauDeltaM
                      5.,    // [ 9] Trks(Pos, Nes, Bach) max SigmaTPC
                      0.006, // [10] V0 MaxWindMass,
                      0.8,   // [11] Xi MinXiRadius,
                      0.97,  // [12] Xi MinXiCosPA,
                      1000., // [13] Xi MaxXiCtau,
                      -1.,   // [14] Xi MaxXiDCAtoPV,
                      0.07,  // [15] Xi MinV0DCAtoPV,
                      1.6,   // [16] Xi MaxV0toBachDCA,
                      0.05,  // [17] Xi MinBachDCAtoPV,
                      70.,   // [18] Xi MinBachXrowsTPC,
                      0.8,   // [19] Xi MinBachXrowsOverFindableClusTPC,
                      0.008  // [20] Xi Compete Mass
                     };

  fXiCutNS = 3.;//Define Number of thegma(Define signal window boundary)
  SetXiCuts(dCuts);
  //PrintConfigs("C");
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::SetDefaultXiCutsPA()
{
  Double_t dCuts[] = {
                      1.2,   // [ 0] V0 MinRadius,
                      0.97,  // [ 1] V0 MinCosPA,
                      1000., // [ 2] V0 MaxCtau,
                      1.7,   // [ 3] V0 MaxDausDCA,
                      0.03,  // [ 4] V0 MinPosDCAtoPV,
                      0.03,  // [ 5] V0 MinNegDCAtoPV,
                      70.,   // [ 6] V0 MinDauXrowsTPC,
                      0.8,   // [ 7] V0 MinDauXrowsOverFindableClusTPC,
                      -1.,   // [ 8] V0 MinDauDeltaM
                      4.,    // [ 9] Trks(Pos, Nes, Bach) max SigmaTPC
                      0.008, // [10] V0 MaxWindMass,
                      0.6,   // [11] Xi MinXiRadius,
                      0.96,  // [12] Xi MinXiCosPA,
                      1000., // [13] Xi MaxXiCtau,
                      -1.,   // [14] Xi MaxXiDCAtoPV,
                      0.06,  // [15] Xi MinV0DCAtoPV,
                      1.6,   // [16] Xi MaxV0toBachDCA,
                      0.04,  // [17] Xi MinBachDCAtoPV,
                      70.,   // [18] Xi MinBachXrowsTPC,
                      0.8,   // [19] Xi MinBachXrowsOverFindableClusTPC,
                      0.008  // [20]Xi Compete Mass
                     };

  fXiCutNS = 4.;//Define Number of thegma(Define signal window boundary)
  SetXiCuts(dCuts);
  //PrintConfigs("C");
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::SetDefaultOmegaCutsPP()
{
  Double_t dCuts[] = {
                      1.4,   // [ 0] V0 MinRadius,
                      0.97,  // [ 1] V0 MinCosPA,
                      1000., // [ 2] V0 MaxCtau,
                      1.6,   // [ 3] V0 MaxDausDCA,
                      0.03,  // [ 4] V0 MinPosDCAtoPV,
                      0.03,  // [ 5] V0 MinNegDCAtoPV,
                      70.,   // [ 6] V0 MinDauXrowsTPC,
                      0.8,   // [ 7] V0 MinDauXrowsOverFindableClusTPC,
                      -1.,   // [ 8] V0 MinDauDeltaM
                      5.,    // [ 9] Trks(Pos, Nes, Bach) max SigmaTPC
                      0.008, // [10] V0 MaxWindMass,
                      0.6,   // [11] Xi MinXiRadius,
                      0.97,  // [12] Xi MinXiCosPA,
                      7.5, // [13] Xi MaxXiCtau,
                      -1.,   // [14] Xi MaxXiDCAtoPV,
                      0.07,  // [15] Xi MinV0DCAtoPV,
                      1.0,   // [16] Xi MaxV0toBachDCA,
                      0.05,  // [17] Xi MinBachDCAtoPV,
                      70.,   // [18] Xi MinBachXrowsTPC,
                      0.8,   // [19] Xi MinBachXrowsOverFindableClusTPC,
                      0.008  // [20]Xi Compete Mass
                     };

  fOmegaCutNS = 3.;//Define Number of thegma(Define signal window boundary)
  SetOmegaCuts(dCuts);
  return;
}


//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::SetDefaultOmegaCutsPA()
{
  Double_t dCuts[] = {
                      1.1,   // [ 0] V0 MinRadius,
                      0.97,  // [ 1] V0 MinCosPA,
                      1000., // [ 2] V0 MaxCtau,
                      1.7,   // [ 3] V0 MaxDausDCA,
                      0.03,  // [ 4] V0 MinPosDCAtoPV,
                      0.03,  // [ 5] V0 MinNegDCAtoPV,
                      70.,   // [ 6] V0 MinDauXrowsTPC,
                      0.8,   // [ 7] V0 MinDauXrowsOverFindableClusTPC,
                      -1.,   // [ 8] V0 MinDauDeltaM
                      4.,    // [ 9] Trks(Pos, Nes, Bach) max SigmaTPC
                      0.008, // [10] V0 MaxWindMass,
                      0.5,   // [11] Xi MinXiRadius,
                      0.96,  // [12] Xi MinXiCosPA,
                      7.5, // [13] Xi MaxXiCtau,
                      -1.,   // [14] Xi MaxXiDCAtoPV,
                      0.06,  // [15] Xi MinV0DCAtoPV,
                      1.6,   // [16] Xi MaxV0toBachDCA,
                      0.04,  // [17] Xi MinBachDCAtoPV,
                      70.,   // [18] Xi MinBachXrowsTPC,
                      0.8,   // [19] Xi MinBachXrowsOverFindableClusTPC,
                      0.008  // [20]Xi Compete Mass
                     };

  fOmegaCutNS = 4.;//Define Number of thegma(Define signal window boundary)
  SetOmegaCuts(dCuts);
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskUserStraneJets::PrintConfigs(TString sOpt)
{
//
//  AliAnalysisTaskUserStraneJets::PrintConfigs
//

  if (sOpt.Contains("A") ||
      sOpt.Contains("E")) {

    cout << "Event selections:" << endl;
    cout << "trigger mask        = " << fTriggerMask         << endl;
    cout << "trigger class       = " << fTriggerClass.Data() << endl;
    cout << "centraity estimator = " << fCentralityEstimator.Data() << ": in ["
         << fCentralityMin << ", "
         << fCentralityMax << "]" << endl;
    cout << "=============================================================================" << endl;
  }

  if (sOpt.Contains("A") ||
      sOpt.Contains("J")) {

    if (sOpt.Contains("A") ||
        sOpt.Contains("E")) cout << endl;

    cout << "Jet parameters:" << endl;

    cout << "use estimated jet pT = ";
    if (fJetUseEstiPt)
      cout << "true";
    else
      cout << "false";
    cout << endl << endl;

    cout << "jet eta in (" << fJetCutMinEta << ", " << fJetCutMaxEta << ")" << endl;
    cout << "jet phi in (" << fJetCutMinPhi << ", " << fJetCutMaxPhi << ")" << endl;

    cout << "jet pT  in [" << fJetCutMinPt  << ", ";
    if (fJetCutMaxPt>0.)
      cout << fJetCutMaxPt; 
    else
      cout << "infty";
    cout << ") (GeV/c)" << endl << endl;

    cout << "Ajet/(piR^2) >= " << fJetCutMinAreaFrac  << endl;
    cout << "leading pT   >= " << fJetCutMinLeadingPt << " (GeV/c)" << endl << endl;

    cout << "# of jet per event in [" << fJetCutMinMulti << ", ";
    if (fJetCutMaxMulti>0)
      cout << fJetCutMaxMulti << "]";
    else
      cout << "infty)";
    cout << endl;
    cout << "=============================================================================" << endl;
  }

  if (sOpt.Contains("A") ||
      sOpt.Contains("V") ||
      sOpt.Contains("K")) {

    if (sOpt.Contains("A") ||
        sOpt.Contains("E") ||
        sOpt.Contains("J")) cout << endl;

    cout << "Kshort selection cuts:" << endl;

    cout << "eta     in (" << fV0CutMinEta    << ", " << fV0CutMaxEta    << ")" << endl;
    cout << "y       in (" << fV0CutMinRap    << ", " << fV0CutMaxRap    << ")" << endl;
    cout << "dau eta in (" << fV0CutMinDauEta << ", " << fV0CutMaxDauEta << ")" << endl << endl;

    cout << "cos pointing angle        > " << fKaCuts[1] << endl;
    cout << "decay radius              > " << fKaCuts[0] << " (cm)" << endl;
    cout << "dua DCA to primary vertex > " << fKaCuts[4] << " (cm)" << endl;
    cout << "DCA between daus          < " << fKaCuts[3] << " (cm)" << endl << endl;

    cout << "life time (= mL/p) < " << fKaCuts[2] << " (sigma)" << endl;
    cout << "competition mass   > " << fKaCuts[7] << " (GeV/c)" << endl << endl;

    cout << "Xrows in TPC           > " << fKaCuts[5] << endl;
    cout << "X/Findable rows in TPC > " << fKaCuts[6] << endl;
    cout << "# of PID sigma  in TPC < " << fKaCuts[8] << endl << endl;

    cout << "# of invM sigma = " << fKaCutNS << endl;
    cout << "=============================================================================" << endl;
  }

  if (sOpt.Contains("A") ||
      sOpt.Contains("V") ||
      sOpt.Contains("L")) {

    if (sOpt.Contains("A") ||
        sOpt.Contains("V") ||
        sOpt.Contains("E") ||
        sOpt.Contains("J") ||
        sOpt.Contains("K")) cout << endl;

    cout << "Lambda (AntiLa) selection cuts:" << endl;

    cout << "eta     in (" << fV0CutMinEta    << ", " << fV0CutMaxEta    << ")" << endl;
    cout << "y       in (" << fV0CutMinRap    << ", " << fV0CutMaxRap    << ")" << endl;
    cout << "dau eta in (" << fV0CutMinDauEta << ", " << fV0CutMaxDauEta << ")" << endl << endl;

    cout << "cos pointing angle        > " << fLaCuts[1] << endl;
    cout << "decay radius              > " << fLaCuts[0] << " (cm)" << endl;
    cout << "dua DCA to primary vertex > " << fLaCuts[4] << " (cm)" << endl;
    cout << "DCA between daus          < " << fLaCuts[3] << " (cm)" << endl << endl;

    cout << "life time (= mL/p) < " << fLaCuts[2] << " (sigma)" << endl;
    cout << "competition mass   > " << fLaCuts[7] << " (GeV/c)" << endl << endl;
  
    cout << "Xrows in TPC           > " << fLaCuts[5] << endl;
    cout << "X/Findable rows in TPC > " << fLaCuts[6] << endl;
    cout << "# of PID sigma  in TPC < " << fLaCuts[8] << endl << endl;
  
    cout << "# of invM sigma = " << fLaCutNS << endl;
    cout << "=============================================================================" << endl;
  }

  if (sOpt.Contains("A") ||
     (sOpt.Contains("J") &&
     (sOpt.Contains("V") ||
      sOpt.Contains("K") ||
      sOpt.Contains("L")))) {

    cout << endl;
    cout << "DeltaR between jet & soft V0s > " << fBkgParCutR << endl;
    cout << "=============================================================================" << endl;
  }

  return;
}
