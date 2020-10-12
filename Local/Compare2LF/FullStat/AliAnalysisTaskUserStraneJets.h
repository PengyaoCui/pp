#ifndef ALIANALYSISTASKUSERPICOJETV0S_H
#define ALIANALYSISTASKUSERPICOJETV0S_H

#include <TNamed.h>
#include <TString.h>
#include <TMath.h>

class TH2D;
class TVector3;
class TChian;
class AliAODEvent;
class AliPicoHeaderJet;
class AliMultSelection;
class AliPicoJet;
class AliMultSelection;
class AliAnalysisTaskUserStraneJets : public TNamed {

 public :

  AliAnalysisTaskUserStraneJets(const char *name);
  ~AliAnalysisTaskUserStraneJets();
//=============================================================================

  enum {
    kPP = 0,  // pp    collisions
    kPA = 1,  // p-Pb  collisions
    kAP = 2,  // Pb-p  collisions
    kAA = 3   // Pb-Pb collisions
  };
  
  void PrintConfigs(TString sOpt="A");

  void AnaJetSparse(const TString sJet);
  void AnaJetSparse(const TString sJet, const TString sRef);

  void AnaV0MakeNtuple();

  void AnaLoop1RD(const TString sOpt);
  void AnaLoop2RD(const TString sOpt);
  void AnaLoopsMC(const TString sOpt);
  void AnaLoopJet(const TString sOpt, const TString sJet, const TString sRef="00");
  void AnaLoopNJ(const TString sOpt, const TString sJet, const TString sRef="00");

  void AnaFitInvM(const TString sOpt, const Bool_t bIsMC=kFALSE);
  void AnaFitCbin(const TString sOpt);

  void AnaInclEff(const TString sOpt, TH1D *hPtKineFB);
  void AnaResults(const Double_t dNorm);
  void AnaMakeFd(TH1D *hPtXiMeas);
  //void AnaMakeFdR(TH1D *hPtXiMeas, TH1D *hPtXiKineFB, TH1D *hEvent);
  void AnaMakeFdR(TH1D *hPtXiMeas, TH1D *hPtXiKineFB, const Double_t dNorm);
  void AnaMakeFdRJC(TH1D *hPtXiMeas, TH1D *hPtXiKineFB, TH1D *hPtLaMeas, const Double_t dNorm);
  void AnaCorrEff(TH2D *hPtEtaKineFB, const TString sOpt="I");
  void AnaWghtEff(TH2D *hPtEtaKineFB);
  //void RunAnalyzeUE(const TString sOpt,const TString sJet);

  void AnaDeltaVJ(const TString sOpt, const TString sJet);
//=============================================================================

  void SetTriggerMask(UInt_t w)   { fTriggerMask  = w; }
  void SetTriggerClass(TString s) { fTriggerClass = s; }

  void SetCentralityEstimator(TString s) { fCentralityEstimator = s; }
  void SetCentralityClass(Float_t dMin, Float_t dMax) { fCentralityMin = dMin; fCentralityMax = dMax; }
//=============================================================================

  void SetJetIsUseEstiPt(Bool_t b) { fJetUseEstiPt = b; }

  void SetJetMultiplicityRange(Int_t min, Int_t max=-1) { fJetCutMinMulti     = min;           fJetCutMaxMulti = max;               }
  void SetJetPtRange(Double_t dMin, Double_t dMax=-1.)  { fJetCutMinPt        = dMin,          fJetCutMaxPt    = dMax;              }
  void SetJetMaxEtaAbs(Double_t d)                      { fJetCutMaxEta       = TMath::Abs(d); fJetCutMinEta   = -1.*fJetCutMaxEta; }
  void SetJetEtaRange(Double_t dMin, Double_t dMax)     { fJetCutMinEta       = dMin,          fJetCutMaxEta   = dMax;              }
  void SetJetPhiRange(Double_t dMin, Double_t dMax)     { fJetCutMinPhi       = dMin,          fJetCutMaxPhi   = dMax;              }
  void SetJetMinAreaFrac(Double_t d)                    { fJetCutMinAreaFrac  = d; }
  void SetJetMinLeadingPt(Double_t d)                   { fJetCutMinLeadingPt = d; }

  void SetRefMultiplicityRange(Int_t min, Int_t max=-1) { fRefCutMinMulti     = min;           fRefCutMaxMulti = max;               }
  void SetRefPtRange(Double_t dMin, Double_t dMax=-1.)  { fRefCutMinPt        = dMin,          fRefCutMaxPt    = dMax;              }
  void SetRefMaxEtaAbs(Double_t d)                      { fRefCutMaxEta       = TMath::Abs(d); fRefCutMinEta   = -1.*fRefCutMaxEta; }
  void SetRefEtaRange(Double_t dMin, Double_t dMax)     { fRefCutMinEta       = dMin,          fRefCutMaxEta   = dMax;              }
  void SetRefPhiRange(Double_t dMin, Double_t dMax)     { fRefCutMinPhi       = dMin,          fRefCutMaxPhi   = dMax;              }
  void SetRefMinAreaFrac(Double_t d)                    { fRefCutMinAreaFrac  = d; }
  void SetRefMinLeadingPt(Double_t d)                   { fRefCutMinLeadingPt = d; }
//=============================================================================

  void SetV0EtaRange(Double_t dMin, Double_t dMax) { fV0CutMinEta = dMin, fV0CutMaxEta = dMax; fV0IsCutEta = kTRUE; }
  void SetV0RapRange(Double_t dMin, Double_t dMax) { fV0CutMinRap = dMin, fV0CutMaxRap = dMax; fV0IsCutRap = kTRUE; }
  void SetV0DauEtaRange(Double_t dMin, Double_t dMax) { fV0CutMinDauEta = dMin; fV0CutMaxDauEta = dMax; }
  
  void SetCascadeEtaRange(Double_t dMin, Double_t dMax) { fCascadeCutMinEta = dMin, fCascadeCutMaxEta = dMax; fCascadeIsCutEta = kTRUE; }
  void SetCascadeRapRange(Double_t dMin, Double_t dMax) { fCascadeCutMinRap = dMin, fCascadeCutMaxRap = dMax; fCascadeIsCutRap = kTRUE; }
  void SetTrkEtaRange(Double_t dMin, Double_t dMax) { fCutMinTrkEta = dMin; fCutMaxTrkEta = dMax; }
//=============================================================================

  void SetDefaultKaCutsPA();
  void SetDefaultLaCutsPA();
  void SetDefaultKaCutsPP();
  void SetDefaultLaCutsPP();

  void SetDefaultXiCutsPP();
  void SetDefaultXiCutsPA();
  void SetDefaultOmegaCutsPA();
  void SetDefaultOmegaCutsPP();



  void SetKaDecayRadius(Double_t d) { fKaCuts[0] = d; }
  void SetKaCosPA(Double_t d)       { fKaCuts[1] = d; }
  void SetKaDausDCA(Double_t d)     { fKaCuts[3] = d; }
  void SetKaPosDCAtoPV(Double_t d)  { fKaCuts[4] = d; }
  void SetKaNegDCAtoPV(Double_t d)  { fKaCuts[5] = d; }
  void SetKaLifeTime(Double_t d) { fKaCuts[2] = d; }
  void SetKaCompMass(Double_t d) { fKaCuts[8] = d; }
  void SetKaXrowsTPC(Double_t d) { fKaCuts[6] = d; }
  void SetKaXoverFindableRowsTPC(Double_t d) { fKaCuts[7] = d; }
  void SetKaSigmaPIDinTPC(Double_t d) { fKaCuts[9] = d; }


  void SetLaDecayRadius(Double_t d) { fLaCuts[0] = d; }
  void SetLaCosPA(Double_t d)       { fLaCuts[1] = d; }
  void SetLaDausDCA(Double_t d)     { fLaCuts[3] = d; }
  void SetLaPosDCAtoPV(Double_t d)  { fLaCuts[4] = d; }
  void SetLaNegDCAtoPV(Double_t d)  { fLaCuts[5] = d; }
  void SetLaLifeTime(Double_t d) { fLaCuts[2] = d; }
  void SetLaCompMass(Double_t d) { fLaCuts[8] = d; }
  void SetLaXrowsTPC(Double_t d) { fLaCuts[6] = d; }
  void SetLaXoverFindableRowsTPC(Double_t d) { fLaCuts[7] = d; }
  void SetLaSigmaPIDinTPC(Double_t d) { fLaCuts[9] = d; }

  void SetKaCutNS(Double_t d) { fKaCutNS = d; }
  void SetLaCutNS(Double_t d) { fLaCutNS = d; }
  void SetXiCutNS(Double_t d) { fXiCutNS = d; }
  void SetOmegaCutNS(Double_t d) { fOmegaCutNS = d; }

  void SetIsAnaIon(Bool_t b)      { fIon = b; }
  void SetIsInJetsAna(Bool_t b)   { fIsStrangeInJet = b; }
  void SetIsInJPCLAna(Bool_t b)   { fIsStrangeInPCL = b; }
  void SetIsInJPCUAna(Bool_t b)   { fIsStrangeInPCU = b; }
  void SetInJetRadius(Double_t d) { fInJetCutR = d; }
  void SetBkgParRadius(Double_t d) { fBkgParCutR = d; }
//=============================================================================

  Bool_t SetInputEventsRD(TChain *chain);
  Bool_t SetInputEventsMC(TChain *chain);

  void SetDetectorRM(TH2D const *h) { fHistoDetectorRM =  new TH2D(*h); }

  Bool_t SetJetPtBinning(const Int_t n, Double_t const *d);
  Bool_t SetKaPtBinning( const Int_t n, Double_t const *d);
  Bool_t SetLaPtBinning( const Int_t n, Double_t const *d);
  Bool_t SetXiPtBinning( const Int_t n, Double_t const *d);
  Bool_t SetOmegaPtBinning( const Int_t n, Double_t const *d);

  void SetDataLoop1st(TString sFile, TString sList) { fFileLoop1st = sFile; fListLoop1st = sList; }
  void SetDataLoop2nd(TString sFile, TString sList) { fFileLoop2nd = sFile; fListLoop2nd = sList; }
  void SetDataLoopJet(TString sFile, TString sList) { fFileLoopJet = sFile; fListLoopJet = sList; }
  void SetDataLoopsMC(TString sFile, TString sList) { fFileLoopsMC = sFile; fListLoopsMC = sList; }
  void SetDataFitInvM(TString sFile, TString sList) { fFileFitInvM = sFile; fListFitInvM = sList; }
  void SetDataFitCbin(TString sFile, TString sList) { fFileFitCbin = sFile; fListFitCbin = sList; }
  void SetDataMakeEff(TString sFile, TString sList) { fFileMakeEff = sFile; fListMakeEff = sList; }
  void SetDataResults(TString sFile, TString sList) { fFileResults = sFile; fListResults = sList; }
  void SetDataMakeFdR(TString sFile, TString sList) { fFileMakeFdR = sFile; fListMakeFdR = sList; }
//=============================================================================

 private :

  AliAnalysisTaskUserStraneJets(const AliAnalysisTaskUserStraneJets &);
  AliAnalysisTaskUserStraneJets& operator=(const AliAnalysisTaskUserStraneJets &);
//=============================================================================

  void SetKaCuts(Double_t d[10]) { for (Int_t i=0; i<10; i++) fKaCuts[i] = d[i]; }
  void SetLaCuts(Double_t d[10]) { for (Int_t i=0; i<10; i++) fLaCuts[i] = d[i]; }
  void SetXiCuts(Double_t d[21]) { for (Int_t i=0; i<21; i++) fXiCuts[i] = d[i]; }
  void SetOmegaCuts(Double_t d[21]) {for (Int_t i=0; i<21; i++) fOmegaCuts[i] = d[i]; }

  Bool_t InitEvent(const TString sOpt);

  Bool_t IsJetNotInMultRange(TClonesArray const *pJetsClArr, const TString sJet);
  Bool_t IsRefNotInMultRange(TClonesArray const *pRefsClArr, const TString sRef);

  Int_t  SelectedJetsN(TClonesArray const *pJetsClArr, const TString sJet);
  Int_t  SelectedRefsN(TClonesArray const *pRefsClArr, const TString sRef);


  Bool_t IsBadJet(AliPicoJet const *pJet, const TString sJet);

  Bool_t IsJetNotSelected(AliPicoJet const *pJet, const TString sJet);
  Bool_t IsRefNotSelected(AliPicoJet const *pRef, const TString sRef);

  Bool_t IsStrangeInJetRange(TVector3 vStrange, TClonesArray const *pJetsClArr, const TString sJet);

  TClonesArray* GetJets(const TString sJet);
  TClonesArray* GetJets(const TString sJet, const TString sRef);

  AliPicoJet* GetMatchedJet(AliPicoJet   const *pJet,
                            TClonesArray const *pRefsClArr,
                            const TString sJet,
                            const TString sRef);

  Double_t BackgroundStrangeFit(Double_t const *x,  Double_t const *par);
  Double_t BackgroundStrangeVal(Double_t const *x,  Double_t const *par);
  Double_t RoundToThousandth(const Double_t d) { return (1e-3 * TMath::Nint(1e3*d)); }

  TH1D* RebinTH1D(TH1D const *hFB, TH1D const *hRB);
  TH2D* RebinTH2D(TH2D const *hFB, TH2D const *hRB);
//=============================================================================


  Bool_t       fIon;

//============================================================================

  TChain      *fChainRD;
  AliAODEvent *fEventRD;

  TChain      *fChainMC;
  AliAODEvent *fEventMC;

  AliPicoHeaderJet *fHeader;
  AliMultSelection *fMult;

  TClonesArray *fV0sClArr;
  TClonesArray *fCascadesClArr;

  TClonesArray *fJetsRD02ClArr;
  TClonesArray *fJetsRD03ClArr;
  TClonesArray *fJetsRD04ClArr;

  TClonesArray *fJetsMC02ClArr;
  TClonesArray *fJetsMC03ClArr;
  TClonesArray *fJetsMC04ClArr;

  TH2D *fHistoDetectorRM;
//=============================================================================

  UInt_t  fTriggerMask;
  TString fTriggerClass;

  Float_t fCentralityMin;
  Float_t fCentralityMax;
  TString fCentralityEstimator;
//=============================================================================

  Bool_t fJetUseEstiPt;

  Int_t fJetCutMinMulti;
  Int_t fJetCutMaxMulti;
  Double_t fJetCutMinPt;
  Double_t fJetCutMaxPt;
  Double_t fJetCutMinEta;
  Double_t fJetCutMaxEta;
  Double_t fJetCutMinPhi;
  Double_t fJetCutMaxPhi;
  Double_t fJetCutMinAreaFrac;
  Double_t fJetCutMinLeadingPt;


  Int_t fRefCutMinMulti;
  Int_t fRefCutMaxMulti;
  Double_t fRefCutMinPt;
  Double_t fRefCutMaxPt;
  Double_t fRefCutMinEta;
  Double_t fRefCutMaxEta;
  Double_t fRefCutMinPhi;
  Double_t fRefCutMaxPhi;
  Double_t fRefCutMinAreaFrac;
  Double_t fRefCutMinLeadingPt;
//=============================================================================

  Bool_t fV0IsCutEta;
  Bool_t fV0IsCutRap;

  Double_t fV0CutMinEta;
  Double_t fV0CutMaxEta;

  Double_t fV0CutMinRap;
  Double_t fV0CutMaxRap;

  Double_t fV0CutMinDauEta;
  Double_t fV0CutMaxDauEta;

  Double_t fKaCuts[10];
  Double_t fLaCuts[10];  // 0: min V0 deacay radius (cm)
                         // 1: min V0 cosPA
                         // 2: max V0 ctau = mL/p (cm)
                         // 3: max V0 daus DCA (sigma)
                         // 4: min V0 pos DCA to PV
                         // 5: min V0 neg DCA to PV
                         // 6: min V0 dau Xrows in TPC
                         // 7: min V0 dau Xrows / Findable Clus in TPC
                         // 8: min delta comp mass
                         // 9: max sigma PID in TPC

  Double_t fKaCutNS;
  Double_t fLaCutNS;
  Double_t fXiCutNS;
  Double_t fOmegaCutNS;

  Bool_t   fIsStrangeInJet;
  Bool_t   fIsStrangeInPCL;
  Bool_t   fIsStrangeInPCU;
  Double_t fInJetCutR;
  Double_t fBkgParCutR;
//=============================================================================
  
  Bool_t fCascadeIsCutEta;
  Bool_t fCascadeIsCutRap;

  Double_t fCascadeCutMinEta;
  Double_t fCascadeCutMaxEta;

  Double_t fCascadeCutMinRap;
  Double_t fCascadeCutMaxRap;

  Double_t fCutMinTrkEta;
  Double_t fCutMaxTrkEta;
 
  Double_t fXiCuts[21];
  Double_t fOmegaCuts[21];

 
//=============================================================================

  Int_t     fJetPtBinN;
  Double_t *fJetPtBinA;

  Int_t     fKaPtBinN;
  Double_t *fKaPtBinA;

  Int_t     fLaPtBinN;
  Double_t *fLaPtBinA;

  Int_t     fXiPtBinN;
  Double_t *fXiPtBinA;

  Int_t     fOmegaPtBinN;
  Double_t *fOmegaPtBinA;
  
  TString fFileLoop1st;
  TString fFileLoop2nd;
  TString fFileLoopJet;
  TString fFileLoopsMC;
  TString fFileFitInvM;
  TString fFileFitCbin;
  TString fFileMakeEff;
  TString fFileResults;
  TString fFileMakeFdR;

  TString fListLoop1st;
  TString fListLoop2nd;
  TString fListLoopJet;
  TString fListLoopsMC;
  TString fListFitInvM;
  TString fListFitCbin;
  TString fListMakeEff;
  TString fListResults;
  TString fListMakeFdR;

  ClassDef(AliAnalysisTaskUserStraneJets, 1)
};

#endif
