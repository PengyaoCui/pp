#ifndef ALIANALYSISTASKEMCALJETSTRANGEFILTER_H
#define ALIANALYSISTASKEMCALJETSTRANGEFILTER_H

#include <TMap.h>

#include "AliAnalysisTaskEmcalJet.h"
//=============================================================================

class TList;
class TString;
class TClonesArray;

class AliPicoHeaderJet;
//=============================================================================

class AliAnalysisTaskEmcalJetStrangeFilter : public AliAnalysisTaskEmcalJet {

 public :

  AliAnalysisTaskEmcalJetStrangeFilter();
  AliAnalysisTaskEmcalJetStrangeFilter(const char *name, const Bool_t bHistos=kTRUE);
  virtual ~AliAnalysisTaskEmcalJetStrangeFilter();

  virtual void Init();
  virtual void LocalInit() { Init(); }
  virtual void UserCreateOutputObjects();
  virtual void Terminate(Option_t *opt);
//=============================================================================

  void AddMultEsti(const TString s) {
    if (fMult.IsNull()) {
      fMult = s;
    } else {
      fMult += Form(":%s",s.Data());
    }
    return;
  }

  void SetPicoV0(const TString s, const Bool_t b=kFALSE) {
    fV0sName = s;
    fIsMC   = b;
    return;
  }
  
  void SetCascade(const TString s, const Bool_t b=kFALSE) {
    fCascadeName = s;
    fIsMC   = b;
    return;
  }

//=============================================================================

 protected :

  virtual void   ExecOnce();
  virtual Bool_t FillGeneralHistograms();
  virtual Bool_t FillHistograms();
  virtual Bool_t IsEventSelected();
  virtual Bool_t RetrieveEventObjects();
  virtual Bool_t Run();
//=============================================================================

 private :

  AliAnalysisTaskEmcalJetStrangeFilter(const AliAnalysisTaskEmcalJetStrangeFilter &);
  AliAnalysisTaskEmcalJetStrangeFilter& operator=(const AliAnalysisTaskEmcalJetStrangeFilter &);
//=============================================================================

  TString fMult; //

  Bool_t fIsMC;     //
  TString fV0sName; //
  TClonesArray *fV0s; //!

  TString fCascadeName; //
  TClonesArray *fCascade; //!

 //=============================================================================

  AliPicoHeaderJet *fPicoHeader; //!

  TMap fMapJets; //!
  TClonesArray *fPicoV0sClArr;  //!
  TClonesArray *fCascadeClArr;  //!
//=============================================================================

  TList *fListUserOutputs;  //!
//=============================================================================

  ClassDef(AliAnalysisTaskEmcalJetStrangeFilter, 3);
};

#endif
