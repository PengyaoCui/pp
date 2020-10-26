#ifndef ALIANALYSISTASKSESTRANGEMAKER_H
#define ALIANALYSISTASKSESTRANGEMAKER_H

//*************************************************************************
// Class AliAnalysisTaskSEStrangeMaker
// AliAnalysisTaskSE for Strangeness (K0 short, Lambda, Cascade... ) filtering
//*************************************************************************

#include <TMap.h>
#include <TObjString.h>
#include <TParameter.h>

#include "AliAnalysisTaskSE.h"
#include "AliEventCuts.h"

#include "AliPicoBaseDev.h"
#include "AliPicoCascade.h"
#include "AliPicoCascadeRD.h"
#include "AliPicoCascadeMC.h"

class TClonesArray;

class AliAODv0;
class AliESDv0;
class AliAODEvent;
class AliESDEvent;
class AliPIDResponse;
class AliPicoV0RD;
class AliPicoV0MC;

class AliAnalysisTaskSEStrangeMaker : public AliAnalysisTaskSE {

 public :

  AliAnalysisTaskSEStrangeMaker();
  AliAnalysisTaskSEStrangeMaker(const char *name, Bool_t bIsMC);
  virtual ~AliAnalysisTaskSEStrangeMaker();

  virtual void Init();
  virtual void LocalInit() { Init(); }
  virtual void UserCreateOutputObjects();
  virtual void UserExec(Option_t *opt);
  virtual void Terminate(Option_t *opt);
  virtual void NotifyRun();
//=============================================================================

  void SetTriggerMask(UInt_t w)       { fTriggerMask   = w; }
  void SetCollitionType(UInt_t w)     { fCollisionType = w; }

  void OldMultEstimator(const Bool_t b=kTRUE) { fUseMultOld = b; }
  void AddMultEstimator(const TString s) {
    fMultEsti.Add(new TObjString(s.Data()),
                  new TParameter<Float_t>(s.Data(), -999.));
    return;
  }

  void SetMultRange(const Double_t dMin,
                    const Double_t dMax,
                    const TString sEst="V0M") {
    fCutMinMult = dMin;
    fCutMaxMult = dMax;
    fMultEstDef = sEst;
    return;
  }

  void SetUseAnaUtils(const Bool_t b) { fUseAnaUtils = b; }

  void SetSkipFastOnly() { fIsSkipFastOnly = kTRUE; }
  void SetRefitV0ESD()   { fIsRefitV0sESD  = kTRUE; }
  void SetRefitCascadeESD()   { fIsRefitCascadeESD  = kTRUE; }
  void SetDMPjetMC()     { fIsDPMjetMC     = kTRUE; }
//=============================================================================

  void SetV0PtRange(Double_t  dMin, Double_t dMax) { fCutMinV0Pt  = dMin; fCutMaxV0Pt  = dMax; }
  void SetV0RapRange(Double_t dMin, Double_t dMax) { fCutMinV0Rap = dMin; fCutMaxV0Rap = dMax; }
  void SetCascadePtRange(Double_t  dMin, Double_t dMax) { fCutMinCascadePt  = dMin; fCutMaxCascadePt  = dMax; }
  void SetCascadeRapRange(Double_t dMin, Double_t dMax) { fCutMinCascadeRap = dMin; fCutMaxCascadeRap = dMax; }


  //void SetDauV0RapRange(Double_t dMin, Double_t dMax) { fCutMinDauV0Rap = dMin; fCutMaxDauV0Rap = dMax; }
  void SetDauPtRange(Double_t d) { fCutMinDauPt = d; }
  void SetDauEtaRange(Double_t dMin, Double_t dMax) { fCutMinDauEta = dMin; fCutMaxDauEta = dMax; }
//=============================================================================

 private :

  AliAnalysisTaskSEStrangeMaker(const AliAnalysisTaskSEStrangeMaker &);
  AliAnalysisTaskSEStrangeMaker& operator=(const AliAnalysisTaskSEStrangeMaker &);
//=============================================================================

  void FillPicoV0s();
  void FillCascades();

  AliPicoV0RD *SelectV0CandidateRD(AliAODv0 const *pV0);
  AliPicoV0RD *SelectV0CandidateRD(AliESDv0 const *pV0);

  AliPicoV0MC *SelectV0CandidateMC(AliAODv0 const *pV0);
  AliPicoV0MC *SelectV0CandidateMC(AliESDv0 const *pV0);

  AliPicoCascadeRD *SelectCascadeCandidateRD(AliAODcascade const *pCascade);
  //AliPicoCascadeRD *SelectCascadeCandidateRD(AliESDcascade const *pCascade);
  
  AliPicoCascadeMC *SelectCascadeCandidateMC(AliAODcascade const *pCascade);
  //AliPicoCascadeMC *SelectCascadeCandidateMC(AliESDcascade const *pCascade);

  Bool_t IsEventNotAcpt();
  Bool_t IsEventNotINEL();
  Bool_t IsEventNotMBsa();

  void FillHistogramsEH();
  void FillHistogramsMC();

  void CreateHistogramsEH();
  void CreateHistogramsMC();

  void InitAnalysis();
  void InitParamsPP();
  void InitParamsPA();
  void InitParamsAP();
  void InitParamsAA();
//=============================================================================

  UInt_t fTriggerMask;   //
  UInt_t fCollisionType; //

  Bool_t fIsAnaUseMC; //
  Bool_t fIsDPMjetMC; //

  Bool_t fUseMultOld;
  Bool_t fUseAnaUtils; //

  Bool_t fIsSkipFastOnly; //
  Bool_t fIsRefitV0sESD;  //
  Bool_t fIsRefitCascadeESD;  //
//=============================================================================

  Double_t fRapidityShift;  //

  TString  fMultEstDef;
  Double_t fCutMinMult;
  Double_t fCutMaxMult;
//=============================================================================
  //cut for V0
  Double_t fCutMinV0Pt;   //
  Double_t fCutMaxV0Pt;   //
  Double_t fCutMinV0Rap;  //
  Double_t fCutMaxV0Rap;  //

  Double_t fCutMinDauPt;   //
  Double_t fCutMinDauEta;  //
  Double_t fCutMaxDauEta;  //

  Double_t fCutMaxV0Chi2;    //
  Double_t fCutMinV0Radius;  //
  Double_t fCutMaxV0Radius;  //

  Double_t fCutMaxDausDCA;      //
  Double_t fCutMinDauDCAtoPV;   //
  Float_t  fCutMinDauXrowsTPC;  //
  Double_t fCutMinDauXrowsOverFindableClusTPC;  //

  Float_t  fCutMaxKshortSigmaTPC;  //
  Double_t fCutMinKshortCosPA;     //
  Double_t fCutMaxKshortCtau;      //
  Double_t fCutMaxKshortArmFrac;   //
  Double_t fCutMinKshortDeltaM;    //

  Float_t  fCutMaxLambdaSigmaTPC;  //
  Double_t fCutMinLambdaCosPA;     //
  Double_t fCutMaxLambdaCtau;      //
  Double_t fCutMaxLambdaArmFrac;   //
  Double_t fCutMinLambdaDeletaM;   //

//=============================================================================
  //Cut for Xi
  Double_t fCutMinCascadePt;   //
  Double_t fCutMaxCascadePt;   //
  Double_t fCutMinCascadeRap;  //
  Double_t fCutMaxCascadeRap;  //

  Double_t fCutMaxCascadeChi2;    //
  Double_t fCutMinCascadeRadius;  //
  Double_t fCutMaxCascadeRadius;  //
 
  Double_t fCutMaxDauV0Chi2;    //
  Double_t fCutMinDauV0Radius;  //
  Double_t fCutMaxDauV0Radius;  //
  Double_t fCutMaxDauLaCtau;      //


  Double_t fCutMaxV0DausDCA; //
  Double_t fCutMaxV0BachDCA;   //
  Double_t fCutMinPosV0DausDCAtoPV;//
  Double_t fCutMinNegV0DausDCAtoPV;//
  Double_t fCutMinDauV0DCAtoPV;   //
  Double_t fCutMinBachDCAtoPV;   //
  Double_t fCutMinCascadeCosPA;   //
  Double_t fCutMinDauV0CosPA;     //

  Float_t  fCutMaxCascadeSigmaTPC;  //
  
  Double_t fCutMinXiDeletaM;   //
  Double_t fCutMinOmegaDeletaM;   //
  Double_t fCutMinDauLaDeletaM;   //


//=============================================================================

  AliAODEvent    *fEventAOD; //!
  AliESDEvent    *fEventESD; //!
  AliPIDResponse *fRespoPID; //!
  AliEventCuts   fAliEventCuts; //;

  Double_t fPrimaryVtx[3]; //!
  UInt_t fEventAcptMask;   //

  TMap fMultEsti; //
//=============================================================================

  TClonesArray *fPicoV0sClArr;  //!
  TClonesArray *fCascadeClArr;  //!

  TList *fOutputListEH;  //!
  TList *fOutputListMC;  //!
//=============================================================================

  ClassDef(AliAnalysisTaskSEStrangeMaker, 6)
};

#endif
