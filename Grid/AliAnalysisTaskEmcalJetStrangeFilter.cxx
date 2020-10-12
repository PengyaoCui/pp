#include <TObjString.h>
#include <TClonesArray.h>

#include "AliAnalysisManager.h"

#include "AliAODHandler.h"

#include "AliEmcalJet.h"
#include "AliJetContainer.h"

#include "AliPicoV0RD.h"
#include "AliPicoV0MC.h"

#include "AliPicoBaseDev.h"
#include "AliPicoCascade.h"
#include "AliPicoCascadeRD.h"
#include "AliPicoCascadeMC.h"

#include "AliPicoJet.h"
#include "AliPicoHeaderJet.h"

#include "AliAnalysisTaskEmcalJetStrangeFilter.h"

ClassImp(AliAnalysisTaskEmcalJetStrangeFilter)

//_____________________________________________________________________________
AliAnalysisTaskEmcalJetStrangeFilter::AliAnalysisTaskEmcalJetStrangeFilter() :
AliAnalysisTaskEmcalJet(),
fMult(""),
fIsMC(kFALSE),
fV0sName(""),
fV0s(nullptr),
fCascadeName(""),
fCascade(nullptr),
fPicoHeader(nullptr),
fMapJets(),
fPicoV0sClArr(nullptr),
fCascadeClArr(nullptr),
fListUserOutputs(nullptr)
{
//
//  AliAnalysisTaskEmcalJetStrangeFilter::AliAnalysisTaskEmcalJetStrangeFilter
//
}

//_____________________________________________________________________________
AliAnalysisTaskEmcalJetStrangeFilter::AliAnalysisTaskEmcalJetStrangeFilter(const char *name, Bool_t bHistos) :
AliAnalysisTaskEmcalJet(name,bHistos),
fMult(""),
fIsMC(kFALSE),
fV0sName("PicoV0s"),
fV0s(nullptr),
fCascadeName("PicoCascade"),
fCascade(nullptr),
fPicoHeader(nullptr),
fMapJets(),
fPicoV0sClArr(nullptr),
fCascadeClArr(nullptr),
fListUserOutputs(nullptr)
{
//
//  AliAnalysisTaskEmcalJetStrangeFilter::AliAnalysisTaskEmcalJetStrangeFilter
//

  AliAnalysisTaskEmcal::fGeneralHistograms = bHistos;

//DefineOutput(1, TList::Class());
}

//_____________________________________________________________________________
AliAnalysisTaskEmcalJetStrangeFilter::~AliAnalysisTaskEmcalJetStrangeFilter()
{
//
//  AliAnalysisTaskEmcalJetStrangeFilter::~AliAnalysisTaskEmcalJetStrangeFilter
//

  if (fV0s) { delete fV0s; fV0s = nullptr; }
  if (fCascade) { delete fCascade; fCascade = nullptr; }

  if (fPicoHeader)   { delete fPicoHeader;   fPicoHeader   = nullptr; }
  if (fPicoV0sClArr) { delete fPicoV0sClArr; fPicoV0sClArr = nullptr; }
  if (fPicoHeader)   { delete fPicoHeader;   fPicoHeader   = nullptr; }
  if (fCascadeClArr) { delete fCascadeClArr; fCascadeClArr = nullptr; }


  if (fListUserOutputs) { delete fListUserOutputs; fListUserOutputs = nullptr; }
}

//_____________________________________________________________________________
void AliAnalysisTaskEmcalJetStrangeFilter::Init()
{
//
//  AliAnalysisTaskEmcalJetStrangeFilter::Init
//

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskEmcalJetStrangeFilter::UserCreateOutputObjects()
{
//
//  AliAnalysisTaskEmcalJetStrangeFilter::UserCreateOutputObjects
//

  AliAnalysisTaskEmcalJet::UserCreateOutputObjects();
//=============================================================================

  if (fPicoHeader) {
    delete fPicoHeader;
    fPicoHeader = nullptr;
  }

  fPicoHeader = new AliPicoHeaderJet();
  fPicoHeader->SetName("PicoHeaderJet");

  if (!fMult.IsNull()) {
    const auto aMult(fMult.Tokenize(":"));

    TIter next(aMult);
    TObjString *ps(nullptr);
    while ((ps = static_cast<TObjString*>(next()))) {
      fPicoHeader->AddMultEstimator(ps->String());
    }
  }

  AddAODBranch("AliPicoHeaderJet", &fPicoHeader);
//=============================================================================

  fMapJets.DeleteAll();
  if (fJetCollArray.GetEntriesFast()>0) {
    TIter next(&fJetCollArray);
    AliEmcalContainer *pc(nullptr);
    while ((pc = static_cast<AliEmcalContainer*>(next()))) if (pc) {
      const TString s(pc->GetName());
      auto pa(new TClonesArray("AliPicoJet"));
      pa->SetName(Form("Pico%s",s.Data()));
      fMapJets.Add(new TObjString(s.Data()), pa);
      AddAODBranch("TClonesArray", &pa);
    }
  }
//=============================================================================

  if (!fV0sName.IsNull()) {
    if (fPicoV0sClArr) {
      delete fPicoV0sClArr;
      fPicoV0sClArr = nullptr;
    }

    if (fIsMC) {
      fPicoV0sClArr = new TClonesArray("AliPicoV0MC");
      fPicoV0sClArr->SetName("PicoV0sMC");
    } else {
      fPicoV0sClArr = new TClonesArray("AliPicoV0RD");
      fPicoV0sClArr->SetName("PicoV0sRD");
    }

    AddAODBranch("TClonesArray", &fPicoV0sClArr);
  }

//=============================================================================
  if (!fCascadeName.IsNull()) {
    if (fCascadeClArr) {
      delete fCascadeClArr;
      fCascadeClArr = nullptr;
    }

    if (fIsMC) {
      fCascadeClArr = new TClonesArray("AliPicoCascadeMC");
      fCascadeClArr->SetName("PicoCascadeMC");
    } else {
      fCascadeClArr = new TClonesArray("AliPicoCascadeRD");
      fCascadeClArr->SetName("PicoCascadeRD");
    }

    AddAODBranch("TClonesArray", &fCascadeClArr);
  }

//=============================================================================

/*if (fListUserOutputs) {
    delete fListUserOutputs;
    fListUserOutputs = nullptr;
  }

  fListUserOutputs = new TList();
  fListUserOutputs->SetOwner();

  const auto b(TH1::AddDirectoryStatus());
  TH1::AddDirectory(kFALSE);
//TODO
  TH1::AddDirectory(b);
  PostData(1, fListUserOutputs);*/
//=============================================================================

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskEmcalJetStrangeFilter::Terminate(Option_t *opt)
{
//
//  AliAnalysisTaskEmcalJetStrangeFilter::Terminate
//

  AliAnalysisTaskEmcalJet::Terminate(opt);

  return;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskEmcalJetStrangeFilter::Run()
{
//
//  AliAnalysisTaskEmcalJetStrangeFilter::Run
//

  fPicoHeader->Reset();

  TObjString *ps(nullptr);
  const auto na(fMapJets.MakeIterator());
  while ((ps = static_cast<TObjString*>((*na)()))) {
    const auto s(ps->String());
    const auto p(static_cast<TClonesArray*>(fMapJets(s.Data())));
    if (p) p->Delete();
  }

  if (fPicoV0sClArr) fPicoV0sClArr->Delete();
  if (fCascadeClArr) fCascadeClArr->Delete();
//=============================================================================

  if (!AliAnalysisTaskEmcalJet::Run()) return kFALSE;
//=============================================================================

  fPicoHeader->SetEventInfo(fInputHandler);
  if (fRho) fPicoHeader->BackgroundRho(fRhoVal);
//=============================================================================

  TIter nc(&fJetCollArray);
  AliEmcalContainer *pc(nullptr);
  while ((pc = static_cast<AliEmcalContainer*>(nc()))) {
    auto pa(static_cast<TClonesArray*>(fMapJets(pc->GetName()))); if (!pa) continue;

    auto l(pa->GetEntriesFast());
    for (auto p : pc->accepted()) if (p) {
      const auto pJet(static_cast<AliEmcalJet*>(p));
      if (pJet) new ((*pa)[l++]) AliPicoJet(pJet,GetLeadingHadronPt(pJet));
    }
  }
//=============================================================================

  if (fV0s) {
    auto l(fPicoV0sClArr->GetEntriesFast());
    for (Int_t i=0; i<fV0s->GetEntriesFast(); ++i) {
      if (fIsMC) {
        const auto pV0(dynamic_cast<AliPicoV0MC*>(fV0s->At(i)));

        if (!pV0) continue;
        new ((*fPicoV0sClArr)[l++]) AliPicoV0MC(*pV0);
      } else {
        const auto pV0(dynamic_cast<AliPicoV0RD*>(fV0s->At(i)));

        if (!pV0) continue;
        new ((*fPicoV0sClArr)[l++]) AliPicoV0RD(*pV0);
      }
    }
  }
//=============================================================================

  if (fCascade) {
    auto l(fCascadeClArr->GetEntriesFast());
    for (Int_t i=0; i<fCascade->GetEntriesFast(); ++i) {
      if (fIsMC) {
        const auto pCascade(dynamic_cast<AliPicoCascadeMC*>(fCascade->At(i)));

        if (!pCascade) continue;
        new ((*fCascadeClArr)[l++]) AliPicoCascadeMC(*pCascade);
      } else {
        const auto pCascade(dynamic_cast<AliPicoCascadeRD*>(fCascade->At(i)));

        if (!pCascade) continue;
        new ((*fCascadeClArr)[l++]) AliPicoCascadeRD(*pCascade);
      }
    }
  }
//=============================================================================

  AliAnalysisManager::GetAnalysisManager()->GetOutputEventHandler()->SetFillAOD(kTRUE);
//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskEmcalJetStrangeFilter::RetrieveEventObjects()
{
//
//  AliAnalysisTaskEmcalJetStrangeFilter::RetrieveEventObjects
//

  if (!AliAnalysisTaskEmcalJet::RetrieveEventObjects()) return kFALSE;

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskEmcalJetStrangeFilter::IsEventSelected()
{
//
//  AliAnalysisTaskEmcalJetStrangeFilter::IsEventSelected
//

  if (!AliAnalysisTaskEmcalJet::IsEventSelected()) return kFALSE;
  
  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskEmcalJetStrangeFilter::FillHistograms()
{
//
//  AliAnalysisTaskEmcalJetStrangeFilter::FillHistograms
//

  if (!AliAnalysisTaskEmcalJet::FillHistograms()) return kFALSE;

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskEmcalJetStrangeFilter::FillGeneralHistograms()
{
//
//  AliAnalysisTaskEmcalJetStrangeFilter::FillGeneralHistograms
//

  if (!AliAnalysisTaskEmcalJet::FillGeneralHistograms()) return kFALSE;

  return kTRUE;
}

//_____________________________________________________________________________
void AliAnalysisTaskEmcalJetStrangeFilter::ExecOnce()
{
//
//  AliAnalysisTaskEmcalJetStrangeFilter::ExecOnce
//

  AliAnalysisTaskEmcalJet::ExecOnce();

  if (!fInitialized) return;
//=============================================================================

  if ((!fV0sName.IsNull()) && (!fV0s)) {
    fV0s = dynamic_cast<TClonesArray*>(InputEvent()->FindListObject(fV0sName.Data()));

    if (!fV0s) {
      AliError(Form("%s: Could not retrieve V0 %s!", GetName(), fV0sName.Data()));
      fInitialized = kFALSE;
      return;
    }
  }

  if ((!fCascadeName.IsNull()) && (!fCascade)) {
    fCascade = dynamic_cast<TClonesArray*>(InputEvent()->FindListObject(fCascadeName.Data()));

    if (!fCascade) {
      AliError(Form("%s: Could not retrieve %s!", GetName(), fCascadeName.Data()));
      fInitialized = kFALSE;
      return;
    }
  }

//=============================================================================

  return;
}
