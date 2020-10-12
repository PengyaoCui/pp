/**************************************************************************
 * Copyright(c) 1998-2008, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/////////////////////////////////////////////////////////////
//
// AliAnalysisTaskSE for RecoDecay object (K0 short, Lambda, Cascade ...) filtering
//
/////////////////////////////////////////////////////////////
#include <iostream>
#include <assert.h>

#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TMath.h>
#include <THnSparse.h>
#include <TClonesArray.h>
#include <TParticle.h>

#include "AliStack.h"
#include "AliESDEvent.h"
#include "AliAODEvent.h"
#include "AliMCEvent.h"

#include "AliHeader.h"
#include "AliInputEventHandler.h"
#include "AliGenDPMjetEventHeader.h"

#include "AliAODv0.h"
#include "AliESDv0.h"
#include "AliAODcascade.h"
#include "AliESDcascade.h"
#include "AliV0vertexer.h"
#include "AliCascadeVertexer.h"

#include "AliESDtrack.h"
#include "AliAODTrack.h"
#include "AliMCParticle.h"
#include "AliAODMCParticle.h"

#include "AliPIDResponse.h"
#include "AliAnalysisUtils.h"

#include "AliCentrality.h"
#include "AliMultSelection.h"

#include "AliPicoBase.h"
#include "AliPicoV0RD.h"
#include "AliPicoV0MC.h"

#include "AliPicoBaseDev.h"
#include "AliPicoCascade.h"
#include "AliPicoCascadeRD.h"
#include "AliPicoCascadeMC.h"

#include "AliAnalysisTaskSEStrangeMaker.h"

ClassImp(AliAnalysisTaskSEStrangeMaker)
//=============================================================================

//_____________________________________________________________________________
AliAnalysisTaskSEStrangeMaker::AliAnalysisTaskSEStrangeMaker() :
AliAnalysisTaskSE(),
fTriggerMask(0),
fCollisionType(0),
fIsAnaUseMC(kFALSE),
fIsDPMjetMC(kFALSE),
fUseMultOld(kFALSE),
fUseAnaUtils(kFALSE),
fIsSkipFastOnly(kFALSE),
fIsRefitV0sESD(kFALSE),
fIsRefitCascadeESD(kFALSE),
fRapidityShift(0.),
fMultEstDef(""),
fCutMinMult(0.),
fCutMaxMult(0.),
fCutMinV0Pt(0.),
fCutMaxV0Pt(0.),
fCutMinV0Rap(0.),
fCutMaxV0Rap(0.),
fCutMinDauPt(0.),
fCutMinDauEta(0.),
fCutMaxDauEta(0.),
fCutMaxV0Chi2(0.),
fCutMinV0Radius(0.),
fCutMaxV0Radius(0.),
fCutMaxDausDCA(0.),
fCutMinDauDCAtoPV(0.),
fCutMinDauXrowsTPC(0.),
fCutMinDauXrowsOverFindableClusTPC(0.),
fCutMaxKshortSigmaTPC(0.),
fCutMinKshortCosPA(0.),
fCutMaxKshortCtau(0.),
fCutMaxKshortArmFrac(0.),
fCutMinKshortDeltaM(0.),
fCutMaxLambdaSigmaTPC(0.),
fCutMinLambdaCosPA(0.),
fCutMaxLambdaCtau(0.),
fCutMaxLambdaArmFrac(0.),
fCutMinLambdaDeletaM(0.),
fCutMinCascadePt(0.),
fCutMaxCascadePt(0.),
fCutMinCascadeRap(0.),
fCutMaxCascadeRap(0.),
fCutMaxCascadeChi2(0.),
fCutMinCascadeRadius(0.),
fCutMaxCascadeRadius(0.),
fCutMaxDauV0Chi2(0.), 
fCutMinDauV0Radius(0.),
fCutMaxDauV0Radius(0.),
fCutMaxDauLaCtau(0.),
fCutMaxV0DausDCA(0.),
fCutMaxV0BachDCA(0.),
fCutMinPosV0DausDCAtoPV(0.),
fCutMinNegV0DausDCAtoPV(0.),
fCutMinDauV0DCAtoPV(0.),
fCutMinBachDCAtoPV(0.),
fCutMinCascadeCosPA(0.),
fCutMinDauV0CosPA(0.),
fCutMaxCascadeSigmaTPC(0.),
fCutMinXiDeletaM(0.),
fCutMinOmegaDeletaM(0.),
fCutMinDauLaDeletaM(0.),
fEventAOD(nullptr),
fEventESD(nullptr),
fRespoPID(nullptr),
fAliEventCuts(kFALSE),
fEventAcptMask(0),
fMultEsti(),
fPicoV0sClArr(nullptr),
fCascadeClArr(nullptr),
fOutputListEH(nullptr),
fOutputListMC(nullptr)
{
//
// Default constructor
//

  for (auto &d : fPrimaryVtx) d = -999.;
}

//_____________________________________________________________________________
AliAnalysisTaskSEStrangeMaker::AliAnalysisTaskSEStrangeMaker(const char *name, Bool_t bIsMC) :
AliAnalysisTaskSE(name),
fTriggerMask(AliVEvent::kAny),
fCollisionType(AliPicoBase::kPP),
fIsAnaUseMC(bIsMC),
fIsDPMjetMC(kFALSE),
fUseMultOld(kFALSE),
fUseAnaUtils(kFALSE),
fIsSkipFastOnly(kFALSE),
fIsRefitV0sESD(kFALSE),
fIsRefitCascadeESD(kFALSE),
fRapidityShift(0.),
fMultEstDef(""),
fCutMinMult(-99999.),
fCutMaxMult(999999.),
fCutMinV0Pt(0.),
fCutMaxV0Pt(100.),
fCutMinV0Rap(-10.),
fCutMaxV0Rap(10.),
fCutMinDauPt(0.),
fCutMinDauEta(-10.),
fCutMaxDauEta(10.),
fCutMaxV0Chi2(33.),
fCutMinV0Radius(0.3),
fCutMaxV0Radius(200.),
fCutMaxDausDCA(1.5),
fCutMinDauDCAtoPV(0.05),
fCutMinDauXrowsTPC(70.),
fCutMinDauXrowsOverFindableClusTPC(0.8),
fCutMaxKshortSigmaTPC(-1.),
fCutMinKshortCosPA(0.95),
fCutMaxKshortCtau(30.),
fCutMaxKshortArmFrac(-1.),
fCutMinKshortDeltaM(0.003),
fCutMaxLambdaSigmaTPC(7.),
fCutMinLambdaCosPA(0.993),
fCutMaxLambdaCtau(40.),
fCutMaxLambdaArmFrac(-1.),
fCutMinLambdaDeletaM(-1.),
fCutMinCascadePt(0.),
fCutMaxCascadePt(100.),
fCutMinCascadeRap(-10.),
fCutMaxCascadeRap(10.),
fCutMaxCascadeChi2(33.),
fCutMinCascadeRadius(0.),
fCutMaxCascadeRadius(200.),
fCutMaxDauV0Chi2(33.),
fCutMinDauV0Radius(0.2),
fCutMaxDauV0Radius(200.),
fCutMaxV0DausDCA(2.5),
fCutMaxV0BachDCA(2.),
fCutMinPosV0DausDCAtoPV(0.01),
fCutMinNegV0DausDCAtoPV(0.01),
fCutMinDauV0DCAtoPV(0.01),
fCutMinBachDCAtoPV(0.01),
fCutMinCascadeCosPA(0.95),
fCutMinDauV0CosPA(0.9),
fCutMaxCascadeSigmaTPC(-3),
fCutMinXiDeletaM(0.),
fCutMinOmegaDeletaM(0.),
fCutMinDauLaDeletaM(0.),
fEventAOD(nullptr),
fEventESD(nullptr),
fRespoPID(nullptr),
fAliEventCuts(kFALSE),
fEventAcptMask(0),
fMultEsti(),
fPicoV0sClArr(nullptr),
fCascadeClArr(nullptr),
fOutputListEH(nullptr),
fOutputListMC(nullptr)
{
//
// Constructor
//

  for (auto &d : fPrimaryVtx) d = -999.;

  DefineOutput(1, TList::Class());
  if (fIsAnaUseMC) DefineOutput(2, TList::Class());
}

//_____________________________________________________________________________
AliAnalysisTaskSEStrangeMaker::~AliAnalysisTaskSEStrangeMaker()
{
//
// Default destructor
//

  if (fEventAOD) { delete fEventAOD; fEventAOD = nullptr; }
  if (fEventESD) { delete fEventESD; fEventESD = nullptr; }
  if (fRespoPID) { delete fRespoPID; fRespoPID = nullptr; }

  if (fPicoV0sClArr) { delete fPicoV0sClArr; fPicoV0sClArr = nullptr; }
  if (fCascadeClArr) { delete fCascadeClArr; fCascadeClArr = nullptr; }
  if (fOutputListEH) { delete fOutputListEH; fOutputListEH = nullptr; }
  if (fOutputListMC) { delete fOutputListMC; fOutputListMC = nullptr; }
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::Init()
{
//
//  AliAnalysisTaskSEStrangeMaker::Init
//

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::UserCreateOutputObjects()
{
//
//  AliAnalysisTaskSEStrangeMaker::UserCreateOutputObjects
//

  InitAnalysis();
  //fAliEventCuts.SetManualMode(1);
  //fAliEventCuts.SetupRun2pp();
//=============================================================================

  if (fPicoV0sClArr) { delete fPicoV0sClArr; fPicoV0sClArr = nullptr; }
  if (fCascadeClArr) { delete fCascadeClArr; fCascadeClArr = nullptr; }

  if (fIsAnaUseMC) {
    fPicoV0sClArr = new TClonesArray("AliPicoV0MC");
    fPicoV0sClArr->SetName("PicoV0s");
    fCascadeClArr = new TClonesArray("AliPicoCascadeMC");
    fCascadeClArr->SetName("PicoCascade");
  } else {
    fPicoV0sClArr = new TClonesArray("AliPicoV0RD");
    fPicoV0sClArr->SetName("PicoV0s");
    fCascadeClArr = new TClonesArray("AliPicoCascadeRD");
    fCascadeClArr->SetName("PicoCascade");
  }
  //=============================================================================

  if (fOutputListEH) {
    delete fOutputListEH;
    fOutputListEH = nullptr;
  }

  fOutputListEH = new TList();
  fOutputListEH->SetOwner();

  fAliEventCuts.AddQAplotsToList(fOutputListEH);
  CreateHistogramsEH();
  PostData(1, fOutputListEH);
//=============================================================================

  if (fIsAnaUseMC) {
    if (fOutputListMC) {
      delete fOutputListMC;
      fOutputListMC = nullptr;
    }

    fOutputListMC = new TList();
    fOutputListMC->SetOwner();

    CreateHistogramsMC();
    PostData(2, fOutputListMC);
  }
//=============================================================================

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::UserExec(Option_t */*opt*/)
{
//
//  AliAnalysisTaskSEStrangeMaker::UserExec
//


  fPicoV0sClArr->Delete();
  fCascadeClArr->Delete();
//=============================================================================
  if (IsEventNotAcpt()) return;
  
  if (!(InputEvent()->FindListObject("PicoV0s"))) InputEvent()->AddObject(fPicoV0sClArr);
  if (!(InputEvent()->FindListObject("PicoCascade"))) InputEvent()->AddObject(fCascadeClArr);

//=============================================================================
  FillHistogramsEH();
//=============================================================================
  //if(IsEventNotINEL()) return;
//=============================================================================
  //if (IsEventNotMBsa()) return;
 
  if(!fAliEventCuts.AcceptEvent(InputEvent())) return;  
  if (fIsAnaUseMC) FillHistogramsMC();
  const auto h(static_cast<TH1D*>(fOutputListEH->FindObject("hEventNumber")));
  h->Fill(1.);
//=============================================================================

  FillPicoV0s();
  FillCascades(); 
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::Terminate(Option_t */*opt*/)
{
//
//  AliAnalysisTaskSEStrangeMaker::Terminate
//

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::NotifyRun()
{
//
//  AliAnalysisTaskSEStrangeMaker::NotifyRun
//

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::FillPicoV0s()
{
//
//  AliAnalysisTaskSEStrangeMaker::FillPicoRecoV0s
//

  const auto nV0s(fEventAOD ? fEventAOD->GetNumberOfV0s() : fEventESD->GetNumberOfV0s());
  if (nV0s<=0) return;
//=============================================================================

  auto nAt(fPicoV0sClArr->GetEntriesFast());
  auto hKshortPtInvM(static_cast<TH2D*>(fOutputListEH->FindObject("hKshortPtInvM")));
  auto hLambdaPtInvM(static_cast<TH2D*>(fOutputListEH->FindObject("hLambdaPtInvM")));
  auto hAntiLaPtInvM(static_cast<TH2D*>(fOutputListEH->FindObject("hAntiLaPtInvM")));
//=============================================================================

  for (auto iV0=0; iV0<nV0s; ++iV0) {
    AliPicoV0RD *pV0RD(nullptr);
    AliPicoV0MC *pV0MC(nullptr);

    if (fEventAOD) {
      auto pV0(fEventAOD->GetV0(iV0));
      if (!pV0) continue;

      if (fIsAnaUseMC) {
        pV0MC = SelectV0CandidateMC(pV0);
      } else {
        pV0RD = SelectV0CandidateRD(pV0);
      }
    }

    if (fEventESD) {
      auto pV0(fEventESD->GetV0(iV0));
      if (!pV0) continue;

      if (fIsAnaUseMC) {
        pV0MC = SelectV0CandidateMC(pV0);
      } else {
        pV0RD = SelectV0CandidateRD(pV0);
      }
    }
//=============================================================================

    if (pV0RD) {
      pV0RD->FillKshortPtInvM(hKshortPtInvM);
      pV0RD->FillLambdaPtInvM(hLambdaPtInvM);
      pV0RD->FillAntiLaPtInvM(hAntiLaPtInvM);
      new ((*fPicoV0sClArr)[nAt++]) AliPicoV0RD(*pV0RD);
      delete pV0RD; pV0RD=nullptr;
    }

    if (pV0MC) {
      pV0MC->FillKshortPtInvM(hKshortPtInvM);
      pV0MC->FillLambdaPtInvM(hLambdaPtInvM);
      pV0MC->FillAntiLaPtInvM(hAntiLaPtInvM);
      new ((*fPicoV0sClArr)[nAt++]) AliPicoV0MC(*pV0MC);
      delete pV0MC; pV0MC=nullptr;
    }
  }
//=============================================================================

  return;
}
//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::FillCascades()
{
//
//  AliAnalysisTaskSECascadeMaker::FillCascades
//

  const auto nCascades(fEventAOD ? fEventAOD->GetNumberOfCascades() :
                                   fEventESD->GetNumberOfCascades());
  if (nCascades<=0) return;
//=============================================================================

  auto nAt(fCascadeClArr->GetEntriesFast());
  auto hXiNegPtInvM(static_cast<TH2D*>(fOutputListEH->FindObject("hXiNegPtInvM")));
  auto hXiPosPtInvM(static_cast<TH2D*>(fOutputListEH->FindObject("hXiPosPtInvM")));
  auto hOmegaNegPtInvM(static_cast<TH2D*>(fOutputListEH->FindObject("hOmegaNegPtInvM")));
  auto hOmegaPosPtInvM(static_cast<TH2D*>(fOutputListEH->FindObject("hOmegaPosPtInvM")));
//=============================================================================

  for (auto iCascade=0; iCascade<nCascades; ++iCascade) {
    AliPicoCascadeRD* pCascadeRD(nullptr);
    AliPicoCascadeMC* pCascadeMC(nullptr);

    if(fEventAOD){
      auto pCascadesAOD(fEventAOD->GetCascade(iCascade));
      if (!pCascadesAOD) continue;

      if (fIsAnaUseMC) {
        pCascadeMC = SelectCascadeCandidateMC(pCascadesAOD);
      } else {
        pCascadeRD = SelectCascadeCandidateRD(pCascadesAOD);
      }
    }
    if (fEventESD) {
    //  auto pCascadesESD(fEventESD->GetCascade(iCascade));
    //  if (!pCascadesESD) continue;

    //  if (fIsAnaUseMC) {
    //    pCascadeMC = SelectCascadeCandidateMC(pCascadesESD);
    //  } else {
    //    pCascadeRD = SelectCascadeCandidateRD(pCascadesESD);
    //  }
    }
//=============================================================================

    if (pCascadeRD){
      pCascadeRD->FillXiPosPtInvM(hXiPosPtInvM);
      pCascadeRD->FillXiNegPtInvM(hXiNegPtInvM);
      pCascadeRD->FillOmegaPosPtInvM(hOmegaPosPtInvM);
      pCascadeRD->FillOmegaNegPtInvM(hOmegaNegPtInvM);
      new ((*fCascadeClArr)[nAt++]) AliPicoCascadeRD(*pCascadeRD);
      delete pCascadeRD; pCascadeRD=nullptr;
    }

    if (pCascadeMC) {
      pCascadeMC->FillXiPosPtInvM(hXiPosPtInvM);
      pCascadeMC->FillXiNegPtInvM(hXiNegPtInvM);
      pCascadeMC->FillOmegaPosPtInvM(hOmegaPosPtInvM);
      pCascadeMC->FillOmegaNegPtInvM(hOmegaNegPtInvM);
      new ((*fCascadeClArr)[nAt++]) AliPicoCascadeMC(*pCascadeMC);
      delete pCascadeMC; pCascadeMC=nullptr;
    }
  }

  return;
}

//_____________________________________________________________________________
AliPicoV0RD *AliAnalysisTaskSEStrangeMaker::SelectV0CandidateRD(AliAODv0 const *pV0)
{
//
//  AliAnalysisTaskSEStrangeMaker::SelectV0CandidateRD
//

  if  (pV0->GetOnFlyStatus()) return nullptr;
  if ((pV0->Chi2V0())>fCutMaxV0Chi2) return nullptr;
//=============================================================================

  const auto dV0Pt(pV0->Pt()); if ((dV0Pt<fCutMinV0Pt) || (dV0Pt>fCutMaxV0Pt)) return nullptr;
  const auto dKaRap(pV0->RapK0Short()); if ((dKaRap<fCutMinV0Rap) || (dKaRap>fCutMaxV0Rap)) return nullptr;
  const auto dLaRap(pV0->RapLambda());  if ((dLaRap<fCutMinV0Rap) || (dLaRap>fCutMaxV0Rap)) return nullptr;
//=============================================================================

  Double_t dV0Vtx[3]; pV0->GetXYZ(dV0Vtx);
  const auto dV0Radius(TMath::Sqrt(dV0Vtx[0]*dV0Vtx[0] + dV0Vtx[1]*dV0Vtx[1]));
  if ((dV0Radius<fCutMinV0Radius) || (dV0Radius>fCutMaxV0Radius)) return nullptr;

  const auto dDausDCA(pV0->DcaV0Daughters()); if (dDausDCA>fCutMaxDausDCA) return nullptr;
  const auto dPosDCAtoPV(pV0->DcaPosToPrimVertex()); if (dPosDCAtoPV<fCutMinDauDCAtoPV) return nullptr;
  const auto dNegDCAtoPV(pV0->DcaNegToPrimVertex()); if (dNegDCAtoPV<fCutMinDauDCAtoPV) return nullptr;
//=============================================================================

  auto pDauPos(static_cast<AliAODTrack*>(pV0->GetDaughter(0))); if (!pDauPos) return nullptr;
  auto pDauNeg(static_cast<AliAODTrack*>(pV0->GetDaughter(1))); if (!pDauNeg) return nullptr;

  if (!(pDauPos->GetStatus() & AliESDtrack::kTPCrefit)) return nullptr;
  if (!(pDauNeg->GetStatus() & AliESDtrack::kTPCrefit)) return nullptr;
  //if ((!((pDauPos->IsOn(AliAODTrack::kITSrefit)) || (pDauPos->IsOn(AliAODTrack::kTOFout)))) && 
  //    (!((pDauNeg->IsOn(AliAODTrack::kITSrefit)) || (pDauNeg->IsOn(AliAODTrack::kTOFout))))) return nullptr;
  //======================= 
  auto NegTOFExpTDiff = (Double_t)(pDauNeg->GetTOFExpTDiff(fEventAOD->GetMagneticField()));
  auto PosTOFExpTDiff = (Double_t)(pDauPos->GetTOFExpTDiff(fEventAOD->GetMagneticField()));
  if( !(pDauNeg->GetStatus() & AliESDtrack::kITSrefit) && !(pDauPos->GetStatus() & AliESDtrack::kITSrefit) && (NegTOFExpTDiff==-2500) && (PosTOFExpTDiff==-2500)) return nullptr; //OOB
  //======================= 
  //ESD 
  //AliESDtrack *pTrack=((AliESDEvent*)lESDevent)->GetTrack((UInt_t)TMath::Abs(v0->GetPindex()));
  //AliESDtrack *nTrack=((AliESDEvent*)lESDevent)->GetTrack((UInt_t)TMath::Abs(v0->GetNindex()));
  //fV0_NegTrackStatus = pTrack->GetStatus();
  //fV0_PosTrackStatus = nTrack->GetStatus();
  //fV0_NegTOFExpTDiff = nTrack->GetTOFExpTDiff( lMagField );
  //fV0_PosTOFExpTDiff  = pTrack->GetTOFExpTDiff( lMagField );
  //if( !(fV0_NegTrackStatus & AliESDtrack::kITSrefit) && !(fV0_PosTrackStatus & AliESDtrack::kITSrefit) && (fV0_NegTOFExpTDiff==-2500) && (fV0_PosTOFExpTDiff==-2500)) return kFALSE; //OOB

  //======================= 
  


  if ((pDauPos->GetProdVertex()->GetType())==((Char_t)AliAODVertex::kKink)) return nullptr;
  if ((pDauNeg->GetProdVertex()->GetType())==((Char_t)AliAODVertex::kKink)) return nullptr;

  const auto dPosXrowsTPC(pDauPos->GetTPCClusterInfo(2,1));
  const auto dNegXrowsTPC(pDauNeg->GetTPCClusterInfo(2,1));
  const auto dDauXrowsTPC((dPosXrowsTPC<dNegXrowsTPC) ? dPosXrowsTPC : dNegXrowsTPC);
  if (dDauXrowsTPC<fCutMinDauXrowsTPC) return nullptr;

  const auto wPosTPCNClsF(pDauPos->GetTPCNclsF()); if (wPosTPCNClsF<=0) return nullptr;
  const auto wNegTPCNClsF(pDauNeg->GetTPCNclsF()); if (wNegTPCNClsF<=0) return nullptr;
  const auto dPosXrowsOverFindableClusTPC( ((Double_t)dPosXrowsTPC) / ((Double_t)wPosTPCNClsF) );
  const auto dNegXrowsOverFindableClusTPC( ((Double_t)dNegXrowsTPC) / ((Double_t)wNegTPCNClsF) );

  const auto dDauXrowsOverFindableClusTPC((dPosXrowsOverFindableClusTPC<dNegXrowsOverFindableClusTPC) ?  dPosXrowsOverFindableClusTPC : dNegXrowsOverFindableClusTPC);
  if (dDauXrowsOverFindableClusTPC<fCutMinDauXrowsOverFindableClusTPC) return nullptr;
//=============================================================================

  const auto nPosCharge(pDauPos->Charge());
  const auto nNegCharge(pDauNeg->Charge());
  if ((nPosCharge==0) || (nNegCharge==0) || (nPosCharge==nNegCharge)) return nullptr;

  Double_t dPosPxPyPz[3] = { 0., 0., 0. };
  Double_t dNegPxPyPz[3] = { 0., 0., 0. };
  if ((nPosCharge<0) && (nNegCharge>0)) {
    pDauPos = (AliAODTrack*)pV0->GetDaughter(1);
    pDauNeg = (AliAODTrack*)pV0->GetDaughter(0);

    dPosPxPyPz[0] = pV0->MomNegX(); dPosPxPyPz[1] = pV0->MomNegY(); dPosPxPyPz[2] = pV0->MomNegZ();
    dNegPxPyPz[0] = pV0->MomPosX(); dNegPxPyPz[1] = pV0->MomPosY(); dNegPxPyPz[2] = pV0->MomPosZ();
  } else {
    dPosPxPyPz[0] = pV0->MomPosX(); dPosPxPyPz[1] = pV0->MomPosY(); dPosPxPyPz[2] = pV0->MomPosZ();
    dNegPxPyPz[0] = pV0->MomNegX(); dNegPxPyPz[1] = pV0->MomNegY(); dNegPxPyPz[2] = pV0->MomNegZ();
  }

  const TVector3 v3Pos(dPosPxPyPz);
  const TVector3 v3Neg(dNegPxPyPz);
  if ((v3Pos.Pt()<fCutMinDauPt) || (v3Neg.Pt()<fCutMinDauPt)) return nullptr;
  const auto dPosEta(v3Pos.Eta()); if ((dPosEta<fCutMinDauEta) || (dPosEta>fCutMaxDauEta)) return nullptr;
  const auto dNegEta(v3Neg.Eta()); if ((dNegEta<fCutMinDauEta) || (dNegEta>fCutMaxDauEta)) return nullptr;
//=============================================================================

  auto bIsKshort(kTRUE);
  auto bIsLambda(kTRUE);
  auto bIsAntiLa(kTRUE);
  const auto dPosPionSigmaTPC(fRespoPID->NumberOfSigmasTPC(pDauPos,AliPID::kPion));
  const auto dNegPionSigmaTPC(fRespoPID->NumberOfSigmasTPC(pDauNeg,AliPID::kPion));

  const auto dPosProtonSigmaTPC(fRespoPID->NumberOfSigmasTPC(pDauPos,AliPID::kProton));
  const auto dNegProtonSigmaTPC(fRespoPID->NumberOfSigmasTPC(pDauNeg,AliPID::kProton));

  if (fCutMaxKshortSigmaTPC>0.) {
    bIsKshort = ((TMath::Abs(dPosPionSigmaTPC)<fCutMaxKshortSigmaTPC) &&
                 (TMath::Abs(dNegPionSigmaTPC)<fCutMaxKshortSigmaTPC));
  }

  if (fCutMaxLambdaSigmaTPC>0.) {
    bIsLambda = ((TMath::Abs(dPosProtonSigmaTPC)<fCutMaxLambdaSigmaTPC) &&
                 (TMath::Abs(dNegPionSigmaTPC)  <fCutMaxLambdaSigmaTPC));

    bIsAntiLa = ((TMath::Abs(dPosPionSigmaTPC)  <fCutMaxLambdaSigmaTPC) &&
                 (TMath::Abs(dNegProtonSigmaTPC)<fCutMaxLambdaSigmaTPC));
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  const auto dV0CosPA(pV0->CosPointingAngle(fPrimaryVtx));

  if (bIsKshort) if (dV0CosPA<fCutMinKshortCosPA) {
    bIsKshort = kFALSE;
  }

  if (bIsLambda || bIsAntiLa) if (dV0CosPA<fCutMinLambdaCosPA) {
    bIsLambda = kFALSE;
    bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  auto dV0DistToPV(0.);
  for (auto i=0; i<3; ++i) dV0DistToPV +=  ((dV0Vtx[i]-fPrimaryVtx[i]) * (dV0Vtx[i]-fPrimaryVtx[i]));
  const auto dV0DistToPVoverP(TMath::Sqrt(dV0DistToPV) / (pV0->P()+1e-10));

  if (bIsKshort) if ((dV0DistToPVoverP*AliPicoBase::MassKshort())>fCutMaxKshortCtau) {
    bIsKshort = kFALSE;
  }

  if (bIsLambda || bIsAntiLa) if ((dV0DistToPVoverP*AliPicoBase::MassLambda())>fCutMaxLambdaCtau) {
    bIsLambda = kFALSE;
    bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  const auto dV0ArmFrac(pV0->PtArmV0() / (TMath::Abs(pV0->AlphaV0())+1e-12));
  if (bIsKshort && (fCutMaxKshortArmFrac>0.)) if (dV0ArmFrac>fCutMaxKshortArmFrac) {
    bIsKshort = kFALSE;
  }

  if ((bIsLambda || bIsAntiLa) && fCutMaxLambdaArmFrac>0.) if (dV0ArmFrac>fCutMaxLambdaArmFrac) {
    bIsLambda = kFALSE;
    bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  TLorentzVector vPosPion; vPosPion.SetVectM(v3Pos, AliPicoBase::MassPion());
  TLorentzVector vNegPion; vNegPion.SetVectM(v3Neg, AliPicoBase::MassPion());

  TLorentzVector vPosProton; vPosProton.SetVectM(v3Pos, AliPicoBase::MassProton());
  TLorentzVector vNegProton; vNegProton.SetVectM(v3Neg, AliPicoBase::MassProton());

  const auto dKshortInvM((vPosPion  +vNegPion).M());
  const auto dLambdaInvM((vPosProton+vNegPion).M());
  const auto dAntiLaInvM((vNegProton+vPosPion).M());
  if (bIsKshort) if ((dKshortInvM<(0.430006 - 0.0110029*dV0Pt)) || (dKshortInvM>(0.563707 + 0.0114979*dV0Pt))) bIsKshort = kFALSE;

  if (bIsLambda || bIsAntiLa) {
    const auto dLower(1.09501 - 0.00523272*dV0Pt - 0.075269*TMath::Exp(-3.46339*dV0Pt));
    const auto dUpper(1.13688 + 0.00527838*dV0Pt + 0.084222*TMath::Exp(-3.80595*dV0Pt));
    if (bIsLambda) if ((dLambdaInvM<dLower) || (dLambdaInvM>dUpper)) bIsLambda = kFALSE;
    if (bIsAntiLa) if ((dAntiLaInvM<dLower) || (dAntiLaInvM>dUpper)) bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  if (bIsKshort && (fCutMinKshortDeltaM>0.)) {
    if ((TMath::Abs(dLambdaInvM-AliPicoBase::MassLambda())<fCutMinKshortDeltaM) ||
        (TMath::Abs(dAntiLaInvM-AliPicoBase::MassLambda())<fCutMinKshortDeltaM)) bIsKshort = kFALSE;
  }

  if ((bIsLambda || bIsAntiLa) && (fCutMinLambdaDeletaM>0.)) {
    if ((TMath::Abs(dKshortInvM-AliPicoBase::MassKshort())<fCutMinLambdaDeletaM)) {
      bIsLambda = kFALSE;
      bIsAntiLa = kFALSE;
    }
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  UInt_t wMask(0);
  if (bIsKshort) wMask |= AliPicoBase::kKshort;
  if (bIsLambda) wMask |= AliPicoBase::kLambda;
  if (bIsAntiLa) wMask |= AliPicoBase::kAntiLambda;
//=============================================================================

  auto bPosInJC(kFALSE);
  auto bNegInJC(kFALSE);
  return (new AliPicoV0RD(wMask,
                          dV0Radius,
                          dV0CosPA,
                          dV0DistToPVoverP,
                          dDausDCA,
                          dPosDCAtoPV,
                          dNegDCAtoPV,
                          dDauXrowsTPC,
                          dDauXrowsOverFindableClusTPC,
                          v3Pos.Px(), v3Pos.Py(), v3Pos.Pz(),
                          v3Neg.Px(), v3Neg.Py(), v3Neg.Pz(),
                          bPosInJC, bNegInJC,
                          dPosPionSigmaTPC, dPosProtonSigmaTPC,
                          dNegPionSigmaTPC, dNegProtonSigmaTPC));
}

//_____________________________________________________________________________
AliPicoV0RD *AliAnalysisTaskSEStrangeMaker::SelectV0CandidateRD(AliESDv0 const *pV0)
{
//
//  AliAnalysisTaskSEStrangeMaker::SelectV0CandidateRD
//

  if (pV0->GetOnFlyStatus()) return nullptr;
  if (pV0->GetChi2V0()>fCutMaxV0Chi2) return nullptr;
//=============================================================================

  const auto dV0Pt(pV0->Pt()); if ((dV0Pt<fCutMinV0Pt) || (dV0Pt>fCutMaxV0Pt)) return nullptr;
  const auto dKaRap(pV0->RapK0Short()); if ((dKaRap<fCutMinV0Rap) || (dKaRap>fCutMaxV0Rap)) return nullptr;
  const auto dLaRap(pV0->RapLambda());  if ((dLaRap<fCutMinV0Rap) || (dLaRap>fCutMaxV0Rap)) return nullptr;
//=============================================================================

  Double_t dV0Vtx[3];  pV0->GetXYZ(dV0Vtx[0], dV0Vtx[1], dV0Vtx[2]);
  const auto dV0Radius(TMath::Sqrt(dV0Vtx[0]*dV0Vtx[0] + dV0Vtx[1]*dV0Vtx[1]));
  if ((dV0Radius<fCutMinV0Radius) || (dV0Radius>fCutMaxV0Radius)) return nullptr;

  const auto dDausDCA(pV0->GetDcaV0Daughters()); if (dDausDCA>fCutMaxDausDCA) return nullptr;
//=============================================================================

  const auto nPosIndex(pV0->GetPindex()); if (nPosIndex<0) return nullptr;
  const auto nNegIndex(pV0->GetNindex()); if (nNegIndex<0) return nullptr;

  auto pDauPos(fEventESD->GetTrack(nPosIndex)); if (!pDauPos) return nullptr;
  auto pDauNeg(fEventESD->GetTrack(nNegIndex)); if (!pDauNeg) return nullptr;

  const auto dMegField(fEventESD->GetMagneticField());
  const auto dPosDCAtoPV(TMath::Abs(pDauPos->GetD(fPrimaryVtx[0],fPrimaryVtx[1],dMegField)));
  if (dPosDCAtoPV<fCutMinDauDCAtoPV) return nullptr;

  const auto dNegDCAtoPV(TMath::Abs(pDauNeg->GetD(fPrimaryVtx[0],fPrimaryVtx[1],dMegField)));
  if (dNegDCAtoPV<fCutMinDauDCAtoPV) return nullptr;
//=============================================================================

  if (!(pDauPos->GetStatus() & AliESDtrack::kTPCrefit)) return nullptr;
  if (!(pDauNeg->GetStatus() & AliESDtrack::kTPCrefit)) return nullptr;
  //if ((!((pDauPos->IsOn(AliAODTrack::kITSrefit)) || (pDauPos->IsOn(AliAODTrack::kTOFout)))) && 
  //    (!((pDauNeg->IsOn(AliAODTrack::kITSrefit)) || (pDauNeg->IsOn(AliAODTrack::kTOFout))))) return nullptr;
  //======================= 
  auto NegTOFExpTDiff = (Double_t)(pDauNeg->GetTOFExpTDiff(fEventESD->GetMagneticField()));
  auto PosTOFExpTDiff = (Double_t)(pDauPos->GetTOFExpTDiff(fEventESD->GetMagneticField()));
  if( !(pDauNeg->GetStatus() & AliESDtrack::kITSrefit) && !(pDauPos->GetStatus() & AliESDtrack::kITSrefit) && (NegTOFExpTDiff==-2500) && (PosTOFExpTDiff==-2500)) return nullptr; //OOB
  if ((pDauPos->GetKinkIndex(0)>0) || (pDauNeg->GetKinkIndex(0)>0)) return nullptr;

  const auto dPosXrowsTPC(pDauPos->GetTPCClusterInfo(2,1));
  const auto dNegXrowsTPC(pDauNeg->GetTPCClusterInfo(2,1));
  const auto dDauXrowsTPC((dPosXrowsTPC<dNegXrowsTPC) ? dPosXrowsTPC : dNegXrowsTPC);
  if (dDauXrowsTPC<fCutMinDauXrowsTPC) return nullptr;

  const auto wPosTPCNClsF(pDauPos->GetTPCNclsF()); if (wPosTPCNClsF<=0) return nullptr;
  const auto wNegTPCNClsF(pDauNeg->GetTPCNclsF()); if (wNegTPCNClsF<=0) return nullptr;
  const auto dPosXrowsOverFindableClusTPC( ((Double_t)dPosXrowsTPC) / ((Double_t)wPosTPCNClsF) );
  const auto dNegXrowsOverFindableClusTPC( ((Double_t)dNegXrowsTPC) / ((Double_t)wNegTPCNClsF) );

  const auto dDauXrowsOverFindableClusTPC((dPosXrowsOverFindableClusTPC<dNegXrowsOverFindableClusTPC) ?
                                           dPosXrowsOverFindableClusTPC :
                                           dNegXrowsOverFindableClusTPC);
  if (dDauXrowsOverFindableClusTPC<fCutMinDauXrowsOverFindableClusTPC) return nullptr;
//=============================================================================

  const auto nPosCharge(pDauPos->Charge());
  const auto nNegCharge(pDauNeg->Charge());
  if ((nPosCharge==0) || (nNegCharge==0) || (nPosCharge==nNegCharge)) return nullptr;

  Double_t dPosPxPyPz[3] = { 0., 0., 0. };
  Double_t dNegPxPyPz[3] = { 0., 0., 0. };
  if ((nPosCharge<0) && (nNegCharge>0)) {
    pDauPos = fEventESD->GetTrack(nNegIndex);
    pDauNeg = fEventESD->GetTrack(nPosIndex);

    pV0->GetNPxPyPz(dPosPxPyPz[0], dPosPxPyPz[1], dPosPxPyPz[2]);
    pV0->GetPPxPyPz(dNegPxPyPz[0], dNegPxPyPz[1], dNegPxPyPz[2]);
  } else {
    pV0->GetPPxPyPz(dPosPxPyPz[0], dPosPxPyPz[1], dPosPxPyPz[2]);
    pV0->GetNPxPyPz(dNegPxPyPz[0], dNegPxPyPz[1], dNegPxPyPz[2]);
  }

  const TVector3 v3Pos(dPosPxPyPz);
  const TVector3 v3Neg(dNegPxPyPz);
  if ((v3Pos.Pt()<fCutMinDauPt) || (v3Neg.Pt()<fCutMinDauPt)) return nullptr;
  const auto dPosEta(v3Pos.Eta()); if ((dPosEta<fCutMinDauEta) || (dPosEta>fCutMaxDauEta)) return nullptr;
  const auto dNegEta(v3Neg.Eta()); if ((dNegEta<fCutMinDauEta) || (dNegEta>fCutMaxDauEta)) return nullptr;
//=============================================================================

  auto bIsKshort(kTRUE);
  auto bIsLambda(kTRUE);
  auto bIsAntiLa(kTRUE);
  const auto dPosPionSigmaTPC(fRespoPID->NumberOfSigmasTPC(pDauPos,AliPID::kPion));
  const auto dNegPionSigmaTPC(fRespoPID->NumberOfSigmasTPC(pDauNeg,AliPID::kPion));

  const auto dPosProtonSigmaTPC(fRespoPID->NumberOfSigmasTPC(pDauPos,AliPID::kProton));
  const auto dNegProtonSigmaTPC(fRespoPID->NumberOfSigmasTPC(pDauNeg,AliPID::kProton));

  if (fCutMaxKshortSigmaTPC>0.) {
    bIsKshort = ((TMath::Abs(dPosPionSigmaTPC)<fCutMaxKshortSigmaTPC) &&
                 (TMath::Abs(dNegPionSigmaTPC)<fCutMaxKshortSigmaTPC));
  }

  if (fCutMaxLambdaSigmaTPC>0.) {
    bIsLambda = ((TMath::Abs(dPosProtonSigmaTPC)<fCutMaxLambdaSigmaTPC) &&
                 (TMath::Abs(dNegPionSigmaTPC)  <fCutMaxLambdaSigmaTPC));

    bIsAntiLa = ((TMath::Abs(dPosPionSigmaTPC)  <fCutMaxLambdaSigmaTPC) &&
                 (TMath::Abs(dNegProtonSigmaTPC)<fCutMaxLambdaSigmaTPC));
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  const auto dV0CosPA(pV0->GetV0CosineOfPointingAngle(fPrimaryVtx[0],fPrimaryVtx[1],fPrimaryVtx[2]));

  if (bIsKshort) if (dV0CosPA<fCutMinKshortCosPA) {
    bIsKshort = kFALSE;
  }

  if (bIsLambda || bIsAntiLa) if (dV0CosPA<fCutMinLambdaCosPA) {
    bIsLambda = kFALSE;
    bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  auto dV0DistToPV(0.);
  for (auto i=0; i<3; ++i) dV0DistToPV +=  ((dV0Vtx[i]-fPrimaryVtx[i]) * (dV0Vtx[i]-fPrimaryVtx[i]));
  const auto dV0DistToPVoverP(TMath::Sqrt(dV0DistToPV) / (pV0->P()+1e-10));

  if (bIsKshort) if ((dV0DistToPVoverP*AliPicoBase::MassKshort())>fCutMaxKshortCtau) {
    bIsKshort = kFALSE;
  }

  if (bIsLambda || bIsAntiLa) if ((dV0DistToPVoverP*AliPicoBase::MassLambda())>fCutMaxLambdaCtau) {
    bIsLambda = kFALSE;
    bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  const auto dV0ArmFrac(pV0->PtArmV0() / (TMath::Abs(pV0->AlphaV0())+1e-12));
  if (bIsKshort && (fCutMaxKshortArmFrac>0.)) if (dV0ArmFrac>fCutMaxKshortArmFrac) {
    bIsKshort = kFALSE;
  }

  if ((bIsLambda && bIsAntiLa) && (fCutMaxLambdaArmFrac>0.)) if (dV0ArmFrac>fCutMaxLambdaArmFrac) {
    bIsLambda = kFALSE;
    bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  TLorentzVector vPosPion; vPosPion.SetVectM(v3Pos, AliPicoBase::MassPion());
  TLorentzVector vNegPion; vNegPion.SetVectM(v3Neg, AliPicoBase::MassPion());

  TLorentzVector vPosProton; vPosProton.SetVectM(v3Pos, AliPicoBase::MassProton());
  TLorentzVector vNegProton; vNegProton.SetVectM(v3Neg, AliPicoBase::MassProton());

  const auto dKshortInvM((vPosPion  +vNegPion).M());
  const auto dLambdaInvM((vPosProton+vNegPion).M());
  const auto dAntiLaInvM((vNegProton+vPosPion).M());
  if (bIsKshort) if ((dKshortInvM<(0.430006 - 0.0110029*dV0Pt)) ||
                     (dKshortInvM>(0.563707 + 0.0114979*dV0Pt))) bIsKshort = kFALSE;

  if (bIsLambda || bIsAntiLa) {
    const auto dLower(1.09501 - 0.00523272*dV0Pt - 0.075269*TMath::Exp(-3.46339*dV0Pt));
    const auto dUpper(1.13688 + 0.00527838*dV0Pt + 0.084222*TMath::Exp(-3.80595*dV0Pt));
    if (bIsLambda) if ((dLambdaInvM<dLower) || (dLambdaInvM>dUpper)) bIsLambda = kFALSE;
    if (bIsAntiLa) if ((dAntiLaInvM<dLower) || (dAntiLaInvM>dUpper)) bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  if (bIsKshort && (fCutMinKshortDeltaM>0.)) {
    if ((TMath::Abs(dLambdaInvM-AliPicoBase::MassLambda())<fCutMinKshortDeltaM) ||
        (TMath::Abs(dAntiLaInvM-AliPicoBase::MassLambda())<fCutMinKshortDeltaM)) {
      bIsKshort = kFALSE;
    }
  }

  if ((bIsLambda || bIsAntiLa) && (fCutMinLambdaDeletaM>0.)) {
    if ((TMath::Abs(dKshortInvM-AliPicoBase::MassKshort())<fCutMinLambdaDeletaM)) {
      bIsLambda = kFALSE;
      bIsAntiLa = kFALSE;
    }
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  UInt_t wMask(0);
  if (bIsKshort) wMask |= AliPicoBase::kKshort;
  if (bIsLambda) wMask |= AliPicoBase::kLambda;
  if (bIsAntiLa) wMask |= AliPicoBase::kAntiLambda;
//=============================================================================

  auto bPosInJC(kFALSE);
  auto bNegInJC(kFALSE);
/*if (fJetContisClArr) {
    const auto idPos(pDauPos->GetID());
    const auto idNeg(pDauNeg->GetID());
    for (auto i=0; i<fJetContisClArr->GetEntriesFast(); ++i) {
      auto pTrk(fJetContisClArr->At(i)); if (!pTrk) continue;

      const auto id(pTrkAOD->GetID());
      if (idPos==id) bPosInJC = kTRUE;
      if (idNeg==id) bNegInJC = kTRUE;
      if (bPosInJC && bNegInJC) break;
    }
  }*/
//=============================================================================

  return (new AliPicoV0RD(wMask,
                          dV0Radius,
                          dV0CosPA,
                          dV0DistToPVoverP,
                          dDausDCA,
                          dPosDCAtoPV,
                          dNegDCAtoPV,
                          dDauXrowsTPC,
                          dDauXrowsOverFindableClusTPC,
                          v3Pos.Px(), v3Pos.Py(), v3Pos.Pz(),
                          v3Neg.Px(), v3Neg.Py(), v3Neg.Pz(),
                          bPosInJC, bNegInJC,
                          dPosPionSigmaTPC, dPosProtonSigmaTPC,
                          dNegPionSigmaTPC, dNegProtonSigmaTPC));
}

//_____________________________________________________________________________
AliPicoV0MC *AliAnalysisTaskSEStrangeMaker::SelectV0CandidateMC(AliAODv0 const *pV0RD)
{
//
//  AliAnalysisTaskSEStrangeMaker::SelectV0CandidateMC
//

  if (pV0RD->GetOnFlyStatus()) return nullptr;
  if ((pV0RD->Chi2V0())>fCutMaxV0Chi2) return nullptr;

  const auto dV0Pt(pV0RD->Pt()); if ((dV0Pt<fCutMinV0Pt) || (dV0Pt>fCutMaxV0Pt)) return nullptr;
//=============================================================================

  Double_t dV0Vtx[3]; pV0RD->GetXYZ(dV0Vtx);
  const auto dV0Radius(TMath::Sqrt(dV0Vtx[0]*dV0Vtx[0] + dV0Vtx[1]*dV0Vtx[1]));
  if ((dV0Radius<fCutMinV0Radius) || (dV0Radius>fCutMaxV0Radius)) return nullptr;

  const auto dDausDCA(pV0RD->DcaV0Daughters()); if (dDausDCA>fCutMaxDausDCA) return nullptr;
  const auto dPosDCAtoPV(pV0RD->DcaPosToPrimVertex()); if (dPosDCAtoPV<fCutMinDauDCAtoPV) return nullptr;
  const auto dNegDCAtoPV(pV0RD->DcaNegToPrimVertex()); if (dNegDCAtoPV<fCutMinDauDCAtoPV) return nullptr;
//=============================================================================

  auto pDauPosRD(static_cast<AliAODTrack*>(pV0RD->GetDaughter(0))); if (!pDauPosRD) return nullptr;
  auto pDauNegRD(static_cast<AliAODTrack*>(pV0RD->GetDaughter(1))); if (!pDauNegRD) return nullptr;

  if (!(pDauPosRD->GetStatus() & AliESDtrack::kTPCrefit)) return nullptr;
  if (!(pDauNegRD->GetStatus() & AliESDtrack::kTPCrefit)) return nullptr;
  //if ((!((pDauPosRD->IsOn(AliAODTrack::kITSrefit)) || (pDauPosRD->IsOn(AliAODTrack::kTOFout)))) && 
  //    (!((pDauNegRD->IsOn(AliAODTrack::kITSrefit)) || (pDauNegRD->IsOn(AliAODTrack::kTOFout))))) return nullptr;
  //======================= 
  auto NegTOFExpTDiff = (Double_t)(pDauNegRD->GetTOFExpTDiff(fEventAOD->GetMagneticField()));
  auto PosTOFExpTDiff = (Double_t)(pDauPosRD->GetTOFExpTDiff(fEventAOD->GetMagneticField()));
  if( !(pDauNegRD->GetStatus() & AliESDtrack::kITSrefit) && !(pDauPosRD->GetStatus() & AliESDtrack::kITSrefit) && (NegTOFExpTDiff==-2500) && (PosTOFExpTDiff==-2500)) return nullptr; //OOB

  if ((pDauPosRD->GetProdVertex()->GetType())==((Char_t)AliAODVertex::kKink)) return nullptr;
  if ((pDauNegRD->GetProdVertex()->GetType())==((Char_t)AliAODVertex::kKink)) return nullptr;

  const auto dPosXrowsTPC(pDauPosRD->GetTPCClusterInfo(2,1));
  const auto dNegXrowsTPC(pDauNegRD->GetTPCClusterInfo(2,1));
  const auto dDauXrowsTPC(dPosXrowsTPC<dNegXrowsTPC ? dPosXrowsTPC : dNegXrowsTPC);
  if (dDauXrowsTPC<fCutMinDauXrowsTPC) return nullptr;

  const auto wPosTPCNClsF(pDauPosRD->GetTPCNclsF()); if (wPosTPCNClsF<=0) return nullptr;
  const auto wNegTPCNClsF(pDauNegRD->GetTPCNclsF()); if (wNegTPCNClsF<=0) return nullptr;
  const auto dPosXrowsOverFindableClusTPC( ((Double_t)dPosXrowsTPC) / ((Double_t)wPosTPCNClsF) );
  const auto dNegXrowsOverFindableClusTPC( ((Double_t)dNegXrowsTPC) / ((Double_t)wNegTPCNClsF) );

  const auto dDauXrowsOverFindableClusTPC(dPosXrowsOverFindableClusTPC<dNegXrowsOverFindableClusTPC ?
                                          dPosXrowsOverFindableClusTPC :
                                          dNegXrowsOverFindableClusTPC);
  if (dDauXrowsOverFindableClusTPC<fCutMinDauXrowsOverFindableClusTPC) return nullptr;
//=============================================================================

  const auto nPosCharge(pDauPosRD->Charge());
  const auto nNegCharge(pDauNegRD->Charge());
  if ((nPosCharge==0) || (nNegCharge==0) || (nPosCharge==nNegCharge)) return nullptr;

  Double_t dPosPxPyPz[3] = { 0., 0., 0. };
  Double_t dNegPxPyPz[3] = { 0., 0., 0. };
  if ((nPosCharge<0) && (nNegCharge>0)) {
    pDauPosRD = (AliAODTrack*)pV0RD->GetDaughter(1);
    pDauNegRD = (AliAODTrack*)pV0RD->GetDaughter(0);

    dPosPxPyPz[0] = pV0RD->MomNegX(); dPosPxPyPz[1] = pV0RD->MomNegY(); dPosPxPyPz[2] = pV0RD->MomNegZ();
    dNegPxPyPz[0] = pV0RD->MomPosX(); dNegPxPyPz[1] = pV0RD->MomPosY(); dNegPxPyPz[2] = pV0RD->MomPosZ();
  } else {
    dPosPxPyPz[0] = pV0RD->MomPosX(); dPosPxPyPz[1] = pV0RD->MomPosY(); dPosPxPyPz[2] = pV0RD->MomPosZ();
    dNegPxPyPz[0] = pV0RD->MomNegX(); dNegPxPyPz[1] = pV0RD->MomNegY(); dNegPxPyPz[2] = pV0RD->MomNegZ();
  }

  const TVector3 v3Pos(dPosPxPyPz);
  const TVector3 v3Neg(dNegPxPyPz);
  if ((v3Pos.Pt()<fCutMinDauPt) || (v3Neg.Pt()<fCutMinDauPt)) return nullptr;
  const auto dPosEta(v3Pos.Eta()); if ((dPosEta<fCutMinDauEta) || (dPosEta>fCutMaxDauEta)) return nullptr;
  const auto dNegEta(v3Neg.Eta()); if ((dNegEta<fCutMinDauEta) || (dNegEta>fCutMaxDauEta)) return nullptr;
//=============================================================================

  const auto inp(TMath::Abs(pDauPosRD->GetLabel())); if (inp<0) return nullptr;
  auto pDauPosMC(static_cast<AliAODMCParticle*>(MCEvent()->GetTrack(inp))); if (!pDauPosMC) return nullptr;
  const auto imp(pDauPosMC->GetMother()); if (imp<0) return nullptr;

  const auto inn(TMath::Abs(pDauNegRD->GetLabel())); if (inn<0) return nullptr;
  const auto pDauNegMC(static_cast<AliAODMCParticle*>(MCEvent()->GetTrack(inn))); if (!pDauNegMC) return nullptr;
  const auto imn(pDauNegMC->GetMother()); if (imn<0) return nullptr;

  if (imp != imn) return nullptr;
  const auto pV0MC(static_cast<AliAODMCParticle*>(MCEvent()->GetTrack(imp))); if (!pV0MC) return nullptr;
  if (((pV0MC->Y())<fCutMinV0Rap) || ((pV0MC->Y())>fCutMaxV0Rap)) return nullptr;

  const auto idvMC(pV0MC->GetPdgCode());
  const auto idp(pDauPosMC->GetPdgCode());
  const auto idn(pDauNegMC->GetPdgCode());
  auto bIsKshort((idp==211)  && (idn==-211)  && (idvMC== 310));
  auto bIsLambda((idp==2212) && (idn==-211)  && (idvMC== 3122));
  auto bIsAntiLa((idp==211)  && (idn==-2212) && (idvMC==-3122));
  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  UInt_t wsvMC(0);
  if (pV0MC->IsPrimary())                wsvMC |= AliPicoBase::kPrimary;
  if (pV0MC->IsPhysicalPrimary())        wsvMC |= AliPicoBase::kPhysicalPrimary;
  if (pV0MC->IsSecondaryFromWeakDecay()) wsvMC |= AliPicoBase::kSecondaryFromWeakDecay;
  if (pV0MC->IsSecondaryFromMaterial())  wsvMC |= AliPicoBase::kSecondaryFromMaterial;

  auto idmMC(0);
  UInt_t wsmMC(0);
  auto dMotherPt(0.);
  auto dMotherEta(0.);
  auto dMotherRap(0.);
  if (bIsLambda || bIsAntiLa) {
    const auto imv(pV0MC->GetMother());

    if (imv>=0) {
      const auto pMother(static_cast<AliAODMCParticle*>(MCEvent()->GetTrack(imv)));

      if (pMother) {
        idmMC = pMother->GetPdgCode();
        if ((bIsLambda && ((idmMC== 3312) || (idmMC== 3322))) ||
            (bIsAntiLa && ((idmMC==-3312) || (idmMC==-3322)))) {
          dMotherPt  = pMother->Pt();
          dMotherEta = pMother->Eta();
          dMotherRap = pMother->Y();

          if (pMother->IsPrimary())                wsmMC |= AliPicoBase::kPrimary;
          if (pMother->IsPhysicalPrimary())        wsmMC |= AliPicoBase::kPhysicalPrimary;
          if (pMother->IsSecondaryFromWeakDecay()) wsmMC |= AliPicoBase::kSecondaryFromWeakDecay;
          if (pMother->IsSecondaryFromMaterial())  wsmMC |= AliPicoBase::kSecondaryFromMaterial;
        }
      }
    }
  }
//=============================================================================

  const auto dV0CosPA(pV0RD->CosPointingAngle(fPrimaryVtx));

  if (bIsKshort) if (dV0CosPA<fCutMinKshortCosPA) {
    bIsKshort = kFALSE;
  }

  if (bIsLambda || bIsAntiLa) if (dV0CosPA<fCutMinLambdaCosPA) {
    bIsLambda = kFALSE;
    bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  auto dV0DistToPV(0.);
  for (auto i=0; i<3; ++i) dV0DistToPV +=  ((dV0Vtx[i]-fPrimaryVtx[i]) * (dV0Vtx[i]-fPrimaryVtx[i]));
  const auto dV0DistToPVoverP(TMath::Sqrt(dV0DistToPV) / (pV0RD->P()+1e-10));

  if (bIsKshort) if ((dV0DistToPVoverP*AliPicoBase::MassKshort())>fCutMaxKshortCtau) {
    bIsKshort = kFALSE;
  }

  if (bIsLambda || bIsAntiLa) if ((dV0DistToPVoverP*AliPicoBase::MassLambda())>fCutMaxLambdaCtau) {
    bIsLambda = kFALSE;
    bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  const auto dV0ArmFrac(pV0RD->PtArmV0() / (TMath::Abs(pV0RD->AlphaV0())+1e-12));

  if (bIsKshort && (fCutMaxKshortArmFrac>0.)) if (dV0ArmFrac>fCutMaxKshortArmFrac) {
    bIsKshort = kFALSE;
  }

  if ((bIsLambda || bIsAntiLa) && fCutMaxLambdaArmFrac>0.) if (dV0ArmFrac>fCutMaxLambdaArmFrac) {
    bIsLambda = kFALSE;
    bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  UInt_t wMask(0);
  if (bIsKshort) {
    TLorentzVector vPosPion; vPosPion.SetVectM(v3Pos, AliPicoBase::MassPion());
    TLorentzVector vNegPion; vNegPion.SetVectM(v3Neg, AliPicoBase::MassPion());

    const auto dKshortInvM((vPosPion+vNegPion).M());
    if ((dKshortInvM<(0.430006-0.0110029*dV0Pt)) ||
        (dKshortInvM>(0.563707+0.0114979*dV0Pt))) return nullptr;

    if (fCutMinKshortDeltaM>0.) {
      TLorentzVector vPosProton; vPosProton.SetVectM(v3Pos, AliPicoBase::MassProton());
      TLorentzVector vNegProton; vNegProton.SetVectM(v3Neg, AliPicoBase::MassProton());
      if ((TMath::Abs((vPosProton+vNegPion).M()-AliPicoBase::MassLambda())<fCutMinKshortDeltaM) ||
          (TMath::Abs((vNegProton+vPosPion).M()-AliPicoBase::MassLambda())<fCutMinKshortDeltaM)) return nullptr;
    }

    wMask = AliPicoBase::kKshort;
  }

  if (bIsLambda) {
    TLorentzVector vPosProton; vPosProton.SetVectM(v3Pos, AliPicoBase::MassProton());
    TLorentzVector vNegPion;   vNegPion.SetVectM(v3Neg, AliPicoBase::MassPion());

    const auto dLambdaInvM((vPosProton+vNegPion).M());
    if ((dLambdaInvM<(1.09501 - 0.00523272*dV0Pt - 0.075269*TMath::Exp(-3.46339*dV0Pt))) ||
        (dLambdaInvM>(1.13688 + 0.00527838*dV0Pt + 0.084222*TMath::Exp(-3.80595*dV0Pt)))) return nullptr;

    if (fCutMinLambdaDeletaM>0.) {
      TLorentzVector vPosPion; vPosPion.SetVectM(v3Pos, AliPicoBase::MassPion());
      if ((TMath::Abs((vPosPion+vNegPion).M()-AliPicoBase::MassKshort())<fCutMinLambdaDeletaM)) return nullptr;
    }

    wMask = AliPicoBase::kLambda;
  }

  if (bIsAntiLa) {
    TLorentzVector vNegProton; vNegProton.SetVectM(v3Neg, AliPicoBase::MassProton());
    TLorentzVector vPosPion;   vPosPion.SetVectM(v3Pos, AliPicoBase::MassPion());

    const auto dAntiLaInvM((vNegProton+vPosPion).M());
    if ((dAntiLaInvM<(1.09501 - 0.00523272*dV0Pt - 0.075269*TMath::Exp(-3.46339*dV0Pt))) ||
        (dAntiLaInvM>(1.13688 + 0.00527838*dV0Pt + 0.084222*TMath::Exp(-3.80595*dV0Pt)))) return nullptr;

    if (fCutMinLambdaDeletaM>0.) {
      TLorentzVector vNegPion; vNegPion.SetVectM(v3Neg, AliPicoBase::MassPion());
      if ((TMath::Abs((vPosPion+vNegPion).M()-AliPicoBase::MassKshort())<fCutMinLambdaDeletaM)) return nullptr;
    }

    wMask = AliPicoBase::kAntiLambda;
  }
//=============================================================================

  auto bPosInJC(kFALSE);
  auto bNegInJC(kFALSE);
  return (new AliPicoV0MC(wMask,
                          dV0Radius,
                          dV0CosPA,
                          dV0DistToPVoverP,
                          dDausDCA,
                          dPosDCAtoPV,
                          dNegDCAtoPV,
                          dDauXrowsTPC,
                          dDauXrowsOverFindableClusTPC,
                          v3Pos.Px(), v3Pos.Py(), v3Pos.Pz(),
                          v3Neg.Px(), v3Neg.Py(), v3Neg.Pz(),
                          bPosInJC, bNegInJC,
                          idvMC, wsvMC, pV0MC->Px(), pV0MC->Py(), pV0MC->Pz(), pV0MC->E(),
                          idmMC, wsmMC, dMotherPt, dMotherEta, dMotherRap));
}

//_____________________________________________________________________________
AliPicoV0MC *AliAnalysisTaskSEStrangeMaker::SelectV0CandidateMC(AliESDv0 const *pV0RD)
{
//
//  AliAnalysisTaskSEStrangeMaker::SelectV0CandidateMC
//

  const auto pStack(MCEvent()->Stack()); if (!pStack) return nullptr;
//=============================================================================

  if (pV0RD->GetOnFlyStatus()) return nullptr;
  if (pV0RD->GetChi2V0()>fCutMaxV0Chi2) return nullptr;

  const auto dV0Pt(pV0RD->Pt()); if ((dV0Pt<fCutMinV0Pt) || (dV0Pt>fCutMaxV0Pt)) return nullptr;
//=============================================================================

  Double_t dV0Vtx[3];  pV0RD->GetXYZ(dV0Vtx[0], dV0Vtx[1], dV0Vtx[2]);
  const auto dV0Radius(TMath::Sqrt(dV0Vtx[0]*dV0Vtx[0] + dV0Vtx[1]*dV0Vtx[1]));
  if ((dV0Radius<fCutMinV0Radius) || (dV0Radius>fCutMaxV0Radius)) return nullptr;

  const auto dDausDCA(pV0RD->GetDcaV0Daughters()); if (dDausDCA>fCutMaxDausDCA) return nullptr;
//=============================================================================

  const auto nPosIndex(TMath::Abs(pV0RD->GetPindex())); if (nPosIndex<0) return nullptr;
  const auto nNegIndex(TMath::Abs(pV0RD->GetNindex())); if (nNegIndex<0) return nullptr;

  auto pDauPosRD(fEventESD->GetTrack(nPosIndex)); if (!pDauPosRD) return nullptr;
  auto pDauNegRD(fEventESD->GetTrack(nNegIndex)); if (!pDauNegRD) return nullptr;

  const auto dMegField(fEventESD->GetMagneticField());
  const auto dPosDCAtoPV(TMath::Abs(pDauPosRD->GetD(fPrimaryVtx[0],fPrimaryVtx[1],dMegField)));
  if (dPosDCAtoPV<fCutMinDauDCAtoPV) return nullptr;

  const auto dNegDCAtoPV(TMath::Abs(pDauNegRD->GetD(fPrimaryVtx[0],fPrimaryVtx[1],dMegField)));
  if (dNegDCAtoPV<fCutMinDauDCAtoPV) return nullptr;
//=============================================================================

  if (!(pDauPosRD->GetStatus() & AliESDtrack::kTPCrefit)) return nullptr;
  if (!(pDauNegRD->GetStatus() & AliESDtrack::kTPCrefit)) return nullptr;
  //if ((!((pDauPosRD->IsOn(AliAODTrack::kITSrefit)) || (pDauPosRD->IsOn(AliAODTrack::kTOFout)))) && 
  //    (!((pDauNegRD->IsOn(AliAODTrack::kITSrefit)) || (pDauNegRD->IsOn(AliAODTrack::kTOFout))))) return nullptr;
  //======================= 
  auto NegTOFExpTDiff = (Double_t)(pDauNegRD->GetTOFExpTDiff(fEventAOD->GetMagneticField()));
  auto PosTOFExpTDiff = (Double_t)(pDauPosRD->GetTOFExpTDiff(fEventAOD->GetMagneticField()));
  if( !(pDauNegRD->GetStatus() & AliESDtrack::kITSrefit) && !(pDauPosRD->GetStatus() & AliESDtrack::kITSrefit) && (NegTOFExpTDiff==-2500) && (PosTOFExpTDiff==-2500)) return nullptr; //OOB
  if ((pDauPosRD->GetKinkIndex(0)>0) || (pDauNegRD->GetKinkIndex(0)>0)) return nullptr;

  const auto dPosXrowsTPC(pDauPosRD->GetTPCClusterInfo(2,1));
  const auto dNegXrowsTPC(pDauNegRD->GetTPCClusterInfo(2,1));
  const auto dDauXrowsTPC((dPosXrowsTPC<dNegXrowsTPC) ? dPosXrowsTPC : dNegXrowsTPC);
  if (dDauXrowsTPC<fCutMinDauXrowsTPC) return nullptr;

  const auto wPosTPCNClsF(pDauPosRD->GetTPCNclsF()); if (wPosTPCNClsF<=0) return nullptr;
  const auto wNegTPCNClsF(pDauNegRD->GetTPCNclsF()); if (wNegTPCNClsF<=0) return nullptr;
  const auto dPosXrowsOverFindableClusTPC( ((Double_t)dPosXrowsTPC) / ((Double_t)wPosTPCNClsF) );
  const auto dNegXrowsOverFindableClusTPC( ((Double_t)dNegXrowsTPC) / ((Double_t)wNegTPCNClsF) );

  const auto dDauXrowsOverFindableClusTPC((dPosXrowsOverFindableClusTPC<dNegXrowsOverFindableClusTPC) ?
                                           dPosXrowsOverFindableClusTPC :
                                           dNegXrowsOverFindableClusTPC);
  if (dDauXrowsOverFindableClusTPC<fCutMinDauXrowsOverFindableClusTPC) return nullptr;
//=============================================================================

  const auto nPosCharge(pDauPosRD->Charge());
  const auto nNegCharge(pDauNegRD->Charge());
  if ((nPosCharge==0) || (nNegCharge==0) || (nPosCharge==nNegCharge)) return nullptr;

  Double_t dPosPxPyPz[3] = { 0., 0., 0. };
  Double_t dNegPxPyPz[3] = { 0., 0., 0. };
  if ((nPosCharge<0) && (nNegCharge>0)) {
    pDauPosRD = fEventESD->GetTrack(nNegIndex);
    pDauNegRD = fEventESD->GetTrack(nPosIndex);

    pV0RD->GetNPxPyPz(dPosPxPyPz[0], dPosPxPyPz[1], dPosPxPyPz[2]);
    pV0RD->GetPPxPyPz(dNegPxPyPz[0], dNegPxPyPz[1], dNegPxPyPz[2]);
  } else {
    pV0RD->GetPPxPyPz(dPosPxPyPz[0], dPosPxPyPz[1], dPosPxPyPz[2]);
    pV0RD->GetNPxPyPz(dNegPxPyPz[0], dNegPxPyPz[1], dNegPxPyPz[2]);
  }

  const TVector3 v3Pos(dPosPxPyPz);
  const TVector3 v3Neg(dNegPxPyPz);
  if ((v3Pos.Pt()<fCutMinDauPt) || (v3Neg.Pt()<fCutMinDauPt)) return nullptr;
  const auto dPosEta(v3Pos.Eta()); if ((dPosEta<fCutMinDauEta) || (dPosEta>fCutMaxDauEta)) return nullptr;
  const auto dNegEta(v3Neg.Eta()); if ((dNegEta<fCutMinDauEta) || (dNegEta>fCutMaxDauEta)) return nullptr;
//=============================================================================

  AliMCParticle *pDauTmpMC(nullptr);
  const auto inp(TMath::Abs(pDauPosRD->GetLabel())); if (inp<0) return nullptr;
  pDauTmpMC = static_cast<AliMCParticle*>(MCEvent()->GetTrack(inp)); if (!pDauTmpMC) return nullptr;
  const auto pDauPosMC(pDauTmpMC->Particle()); if (!pDauPosMC) return nullptr;
  const auto imp(pDauPosMC->GetFirstMother()); if (imp<0) return nullptr;

  const auto inn(TMath::Abs(pDauNegRD->GetLabel())); if (inn<0) return nullptr;
  pDauTmpMC = static_cast<AliMCParticle*>(MCEvent()->GetTrack(inn)); if (!pDauTmpMC) return nullptr;
  const auto pDauNegMC(pDauTmpMC->Particle()); if (!pDauNegMC) return nullptr;
  const auto imn(pDauNegMC->GetFirstMother()); if (imn<0) return nullptr;

  if (imp != imn) return nullptr;
  pDauTmpMC = static_cast<AliMCParticle*>(MCEvent()->GetTrack(imp)); if (!pDauTmpMC) return nullptr;
  const auto pV0MC(pDauTmpMC->Particle()); if (!pV0MC) return nullptr;
  if (((pV0MC->Y())<fCutMinV0Rap) || ((pV0MC->Y())>fCutMaxV0Rap)) return nullptr;

  const auto idvMC(pV0MC->GetPdgCode());
  const auto idp(pDauPosMC->GetPdgCode());
  const auto idn(pDauNegMC->GetPdgCode());
  auto bIsKshort((idp==211)  && (idn==-211)  && (idvMC== 310));
  auto bIsLambda((idp==2212) && (idn==-211)  && (idvMC== 3122));
  auto bIsAntiLa((idp==211)  && (idn==-2212) && (idvMC==-3122));
  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  UInt_t wsvMC(0);
  if (imp<pStack->GetNprimary())             wsvMC |= AliPicoBase::kPrimary;
  if (pStack->IsPhysicalPrimary(imp))        wsvMC |= AliPicoBase::kPhysicalPrimary;
  if (pStack->IsSecondaryFromWeakDecay(imp)) wsvMC |= AliPicoBase::kSecondaryFromWeakDecay;
  if (pStack->IsSecondaryFromMaterial(imp))  wsvMC |= AliPicoBase::kSecondaryFromMaterial;

  auto   idmMC(0);
  UInt_t wsmMC(0);
  auto dMotherPt(0.);
  auto dMotherEta(0.);
  auto dMotherRap(0.);
  if (bIsLambda || bIsAntiLa) {
    const auto imv(pV0MC->GetFirstMother());

    if (imv>=0) {
      pDauTmpMC = static_cast<AliMCParticle*>(MCEvent()->GetTrack(imv));

      if (pDauTmpMC) {
        auto pMother(pDauTmpMC->Particle());

        if (pMother) {
          idmMC = pMother->GetPdgCode();
          if ((bIsLambda && ((idmMC== 3312) || (idmMC== 3322))) ||
              (bIsAntiLa && ((idmMC==-3312) || (idmMC==-3322)))) {
            dMotherPt  = pMother->Pt();
            dMotherEta = pMother->Eta();
            dMotherRap = pMother->Y();

            if (imp<pStack->GetNprimary())             wsmMC |= AliPicoBase::kPrimary;
            if (pStack->IsPhysicalPrimary(imv))        wsmMC |= AliPicoBase::kPhysicalPrimary;
            if (pStack->IsSecondaryFromWeakDecay(imv)) wsmMC |= AliPicoBase::kSecondaryFromWeakDecay;
            if (pStack->IsSecondaryFromMaterial(imv))  wsmMC |= AliPicoBase::kSecondaryFromMaterial;
          }
        }
      }
    }
  }
//=============================================================================

  const auto dV0CosPA(pV0RD->GetV0CosineOfPointingAngle(fPrimaryVtx[0],fPrimaryVtx[1],fPrimaryVtx[2]));

  if (bIsKshort) if (dV0CosPA<fCutMinKshortCosPA) {
    bIsKshort = kFALSE;
  }

  if (bIsLambda || bIsAntiLa) if (dV0CosPA<fCutMinLambdaCosPA) {
    bIsLambda = kFALSE;
    bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  auto dV0DistToPV(0.);
  for (auto i=0; i<3; ++i) dV0DistToPV +=  ((dV0Vtx[i]-fPrimaryVtx[i]) * (dV0Vtx[i]-fPrimaryVtx[i]));
  const auto dV0DistToPVoverP(TMath::Sqrt(dV0DistToPV) / (pV0RD->P()+1e-10));

  if (bIsKshort) if ((dV0DistToPVoverP*AliPicoBase::MassKshort())>fCutMaxKshortCtau) {
    bIsKshort = kFALSE;
  }

  if (bIsLambda || bIsAntiLa) if ((dV0DistToPVoverP*AliPicoBase::MassLambda())>fCutMaxLambdaCtau) {
    bIsLambda = kFALSE;
    bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  const auto dV0ArmFrac(pV0RD->PtArmV0() / (TMath::Abs(pV0RD->AlphaV0())+1e-12));

  if (bIsKshort && (fCutMaxKshortArmFrac>0.)) if (dV0ArmFrac>fCutMaxKshortArmFrac) {
    bIsKshort = kFALSE;
  }

  if ((bIsLambda && bIsAntiLa) && (fCutMaxLambdaArmFrac>0.)) if (dV0ArmFrac>fCutMaxLambdaArmFrac) {
    bIsLambda = kFALSE;
    bIsAntiLa = kFALSE;
  }

  if (!(bIsKshort || bIsLambda || bIsAntiLa)) return nullptr;
//=============================================================================

  UInt_t wMask(0);
  if (bIsKshort) {
    TLorentzVector vPosPion; vPosPion.SetVectM(v3Pos, AliPicoBase::MassPion());
    TLorentzVector vNegPion; vNegPion.SetVectM(v3Neg, AliPicoBase::MassPion());

    const auto dKshortInvM((vPosPion+vNegPion).M());
    if ((dKshortInvM<(0.430006 - 0.0110029*dV0Pt)) ||
        (dKshortInvM>(0.563707 + 0.0114979*dV0Pt))) return nullptr;

    if (fCutMinKshortDeltaM>0.) {
      TLorentzVector vPosProton; vPosProton.SetVectM(v3Pos, AliPicoBase::MassProton());
      TLorentzVector vNegProton; vNegProton.SetVectM(v3Neg, AliPicoBase::MassProton());
      if ((TMath::Abs((vPosProton+vNegPion).M()-AliPicoBase::MassLambda())<fCutMinKshortDeltaM) ||
          (TMath::Abs((vNegProton+vPosPion).M()-AliPicoBase::MassLambda())<fCutMinKshortDeltaM)) return nullptr;
    }

    wMask = AliPicoBase::kKshort;
  }

  if (bIsLambda) {
    TLorentzVector vPosProton; vPosProton.SetVectM(v3Pos, AliPicoBase::MassProton());
    TLorentzVector vNegPion; vNegPion.SetVectM(v3Neg, AliPicoBase::MassPion());

    const auto dLambdaInvM((vPosProton+vNegPion).M());
    if ((dLambdaInvM<(1.09501 - 0.00523272*dV0Pt - 0.075269*TMath::Exp(-3.46339*dV0Pt))) ||
        (dLambdaInvM>(1.13688 + 0.00527838*dV0Pt + 0.084222*TMath::Exp(-3.80595*dV0Pt)))) return nullptr;

    if (fCutMinLambdaDeletaM>0.) {
      TLorentzVector vPosPion; vPosPion.SetVectM(v3Pos, AliPicoBase::MassPion());
      if ((TMath::Abs((vPosPion+vNegPion).M()-AliPicoBase::MassKshort())<fCutMinLambdaDeletaM)) return nullptr;
    }

    wMask = AliPicoBase::kLambda;
  }

  if (bIsAntiLa) {
    TLorentzVector vNegProton; vNegProton.SetVectM(v3Neg, AliPicoBase::MassProton());
    TLorentzVector vPosPion; vPosPion.SetVectM(v3Pos, AliPicoBase::MassPion());

    const auto dAntiLaInvM((vNegProton+vPosPion).M());
    if ((dAntiLaInvM<(1.09501 - 0.00523272*dV0Pt - 0.075269*TMath::Exp(-3.46339*dV0Pt))) ||
        (dAntiLaInvM>(1.13688 + 0.00527838*dV0Pt + 0.084222*TMath::Exp(-3.80595*dV0Pt)))) return nullptr;

    if (fCutMinLambdaDeletaM>0.) {
      TLorentzVector vNegPion; vNegPion.SetVectM(v3Neg, AliPicoBase::MassPion());
      if ((TMath::Abs((vPosPion+vNegPion).M()-AliPicoBase::MassKshort())<fCutMinLambdaDeletaM)) return nullptr;
    }

    wMask = AliPicoBase::kAntiLambda;
  }
//=============================================================================

  auto bPosInJC(kFALSE);
  auto bNegInJC(kFALSE);
  return (new AliPicoV0MC(wMask,
                          dV0Radius,
                          dV0CosPA,
                          dV0DistToPVoverP,
                          dDausDCA,
                          dPosDCAtoPV,
                          dNegDCAtoPV,
                          dDauXrowsTPC,
                          dDauXrowsOverFindableClusTPC,
                          v3Pos.Px(), v3Pos.Py(), v3Pos.Pz(),
                          v3Neg.Px(), v3Neg.Py(), v3Neg.Pz(),
                          bPosInJC, bNegInJC,
                          idvMC, wsvMC, pV0MC->Px(), pV0MC->Py(), pV0MC->Pz(), pV0MC->Energy(),
                          idmMC, wsmMC, dMotherPt, dMotherEta, dMotherRap));
}

//_____________________________________________________________________________
AliPicoCascadeRD *AliAnalysisTaskSEStrangeMaker::SelectCascadeCandidateRD(AliAODcascade const *xi)
{
//
//  AliAnalysisTaskSEStrangeMaker::SelectCascadeCandidateRD
//

  if (!xi) return nullptr;
  //if (xi->GetOnFlyStatus()) return 0x0;
//=============================================================================

  auto pTrkXi(static_cast<AliAODTrack*>(xi->GetDaughter(0))); if (!pTrkXi) return nullptr;
  auto nTrkXi(static_cast<AliAODTrack*>(xi->GetDaughter(1))); if (!nTrkXi) return nullptr;
  auto bTrkXi(static_cast<AliAODTrack*>(xi->GetDecayVertexXi()->GetDaughter(0))); if (!bTrkXi) return nullptr;
  
  if (!(pTrkXi->IsOn(AliAODTrack::kTPCrefit))) return nullptr;
  if (!(nTrkXi->IsOn(AliAODTrack::kTPCrefit))) return nullptr;
  if (!(bTrkXi->IsOn(AliAODTrack::kTPCrefit))) return nullptr;
  
  //if ((!((pTrkXi->IsOn(AliAODTrack::kITSrefit)) || (pTrkXi->IsOn(AliAODTrack::kTOFout)))) &&
  //    (!((nTrkXi->IsOn(AliAODTrack::kITSrefit)) || (nTrkXi->IsOn(AliAODTrack::kTOFout)))) &&
  //    (!((bTrkXi->IsOn(AliAODTrack::kITSrefit)) || (bTrkXi->IsOn(AliAODTrack::kTOFout))))) return nullptr;
  //======================= 
  auto pTOFExpTDiff = (Double_t)(pTrkXi->GetTOFExpTDiff(fEventAOD->GetMagneticField()));
  auto nTOFExpTDiff = (Double_t)(nTrkXi->GetTOFExpTDiff(fEventAOD->GetMagneticField()));
  auto bTOFExpTDiff = (Double_t)(bTrkXi->GetTOFExpTDiff(fEventAOD->GetMagneticField()));
  if( !(pTrkXi->GetStatus() & AliESDtrack::kITSrefit) && !(nTrkXi->GetStatus() & AliESDtrack::kITSrefit) && !(bTrkXi->GetStatus() & AliESDtrack::kITSrefit) && (pTOFExpTDiff==-2500) && (nTOFExpTDiff==-2500) && (bTOFExpTDiff==-2500)) return nullptr; //OOB
  
  //if (!(AODTrack->GetTOFBunchCrossing() == 0)) return nullptr; 

  std::map<int, int> labels;
  //looking for global tracks and saving their numbers to copy from them PID information to TPC-only tracks in the main loop over tracks
  auto NumofTracks(fEventAOD->GetNumberOfTracks());
  for (int i = 0; i < NumofTracks; i++) {
    const AliAODTrack *AODTrack = dynamic_cast<const AliAODTrack *>(fEventAOD->GetTrack(i));
    assert(AODTrack && "Not a standard AOD");
    if (!AODTrack->TestFilterBit(1<<7)) {
      // Skip TPC-only tracks
      if (AODTrack->GetID() < 0) continue;
      labels[AODTrack->GetID()] = i;
    }
  }
  const auto idxPosXi( (UInt_t)(pTrkXi->TestFilterBit(1<<7)) ? (labels[-1 - pTrkXi->GetID()]) : pTrkXi->GetID());
  const auto idxNegXi( (UInt_t)(nTrkXi->TestFilterBit(1<<7)) ? (labels[-1 - nTrkXi->GetID()]) : nTrkXi->GetID());
  const auto idxBach ( (UInt_t)(bTrkXi->TestFilterBit(1<<7)) ? (labels[-1 - bTrkXi->GetID()]) : bTrkXi->GetID());
  if(idxBach == idxNegXi || idxBach == idxPosXi) return nullptr;

  const auto pCrossedRowsTPC(pTrkXi->GetTPCClusterInfo(2,1)); if (pCrossedRowsTPC < fCutMinDauXrowsTPC) return nullptr;
  const auto nCrossedRowsTPC(nTrkXi->GetTPCClusterInfo(2,1)); if (nCrossedRowsTPC < fCutMinDauXrowsTPC) return nullptr;
  const auto dDauXrowsTPC(pCrossedRowsTPC < nCrossedRowsTPC ? pCrossedRowsTPC : nCrossedRowsTPC);
  const auto bCrossedRowsTPC(bTrkXi->GetTPCClusterInfo(2,1)); if (bCrossedRowsTPC < fCutMinDauXrowsTPC) return nullptr;


  const auto pTPCNClsF(pTrkXi->GetTPCNclsF()); if (pTPCNClsF <= 0) return nullptr;
  const auto nTPCNClsF(nTrkXi->GetTPCNclsF()); if (nTPCNClsF <= 0) return nullptr;
  const auto bTPCNClsF(bTrkXi->GetTPCNclsF()); if (bTPCNClsF <= 0) return nullptr;

  const auto pXrowsOverFindableClusTPC( ((Double_t)pCrossedRowsTPC) / ((Double_t)pTPCNClsF));
  const auto nXrowsOverFindableClusTPC( ((Double_t)nCrossedRowsTPC) / ((Double_t)nTPCNClsF));
  const auto dDauXrowsOverFindableClusTPC( pXrowsOverFindableClusTPC < nXrowsOverFindableClusTPC ? pXrowsOverFindableClusTPC: nXrowsOverFindableClusTPC);
  if (dDauXrowsOverFindableClusTPC<fCutMinDauXrowsOverFindableClusTPC) return nullptr;

  const auto bXrowsOverFindableClusTPC( ((Double_t)bCrossedRowsTPC) / ((Double_t)bTPCNClsF));
  if(bXrowsOverFindableClusTPC < fCutMinDauXrowsOverFindableClusTPC) return nullptr;

//=============================================================================

  //Daughter tracks PID with TPC only:
  auto isBachelorPionForTPC(kFALSE);
  auto isBachelorKaonForTPC(kFALSE);
  auto isNegPionForTPC(kFALSE);
  auto isPosPionForTPC(kFALSE);
  auto isNegProtonForTPC(kFALSE);
  auto isPosProtonForTPC(kFALSE);
  auto bIsLambda(kTRUE);
  auto bIsAntiLa(kTRUE);
  auto bIsXiNeg(kTRUE);
  auto bIsXiPos(kTRUE);
  auto bIsOmegaNeg(kTRUE);
  auto bIsOmegaPos(kTRUE);

  //Xi bach 
  const auto dBachPionSigmaTPC(fRespoPID->NumberOfSigmasTPC(bTrkXi, AliPID::kPion));
  const auto dBachKaonSigmaTPC(fRespoPID->NumberOfSigmasTPC(bTrkXi, AliPID::kKaon));

  //Negative V0 daughter                                                               
  const auto dNegPionSigmaTPC(fRespoPID->NumberOfSigmasTPC(nTrkXi, AliPID::kPion));
  const auto dNegProtonSigmaTPC(fRespoPID->NumberOfSigmasTPC(nTrkXi,AliPID::kProton));
  //Positive V0 daughter                                                               
  const auto dPosPionSigmaTPC(fRespoPID->NumberOfSigmasTPC(pTrkXi,AliPID::kPion));
  const auto dPosProtonSigmaTPC(fRespoPID->NumberOfSigmasTPC(pTrkXi,AliPID::kProton));
  if (fCutMaxCascadeSigmaTPC > 0.){
    isBachelorKaonForTPC = (TMath::Abs(dBachKaonSigmaTPC)<fCutMaxCascadeSigmaTPC);
    isBachelorPionForTPC = (TMath::Abs(dBachPionSigmaTPC)<fCutMaxCascadeSigmaTPC);
    
    isNegPionForTPC      = (TMath::Abs(dNegPionSigmaTPC) <fCutMaxCascadeSigmaTPC);
    isPosPionForTPC      = (TMath::Abs(dPosPionSigmaTPC) <fCutMaxCascadeSigmaTPC);
    
    isNegProtonForTPC    = (TMath::Abs(dNegProtonSigmaTPC)<fCutMaxCascadeSigmaTPC);
    isPosProtonForTPC    = (TMath::Abs(dPosProtonSigmaTPC)<fCutMaxCascadeSigmaTPC);
  } else{
    isBachelorKaonForTPC = kTRUE;
    isBachelorPionForTPC = kTRUE;
   
    isNegPionForTPC      = kTRUE;
    isPosPionForTPC      = kTRUE;
  
    isNegProtonForTPC    = kTRUE;
    isPosProtonForTPC    = kTRUE;
  }

  bIsLambda = isPosProtonForTPC && isNegPionForTPC;
  bIsAntiLa = isNegProtonForTPC && isPosPionForTPC;
  bIsXiNeg = bIsLambda && isBachelorPionForTPC;
  bIsXiPos = bIsAntiLa && isBachelorPionForTPC;
  bIsOmegaNeg = bIsLambda && isBachelorKaonForTPC;
  bIsOmegaPos = bIsAntiLa && isBachelorKaonForTPC;

  const auto iChargeXi(xi->ChargeXi());
  if (bIsXiNeg && iChargeXi>0) return nullptr;
  if (bIsXiPos && iChargeXi<0) return nullptr;
  if (bIsOmegaNeg && iChargeXi>0) return nullptr;
  if (bIsOmegaPos && iChargeXi<0) return nullptr;
  if (!(bIsXiNeg || bIsXiPos || bIsOmegaNeg || bIsOmegaPos)) return nullptr;

//=============================================================================
  if (xi->Chi2Xi()>fCutMaxCascadeChi2) return nullptr;//Chi2Xi
  if (xi->Chi2V0()>fCutMaxDauV0Chi2) return nullptr;//Chi2V0

  //Cascade Momentum
  const auto XiPx(xi->MomXiX());
  const auto XiPy(xi->MomXiY());
  const auto XiPz(xi->MomXiZ());
  const auto XiRap(xi->RapXi());
  const auto OmegaRap(xi->RapOmega());
  const Double_t dXiMom[3] = {XiPx, XiPy, XiPz};
  const TVector3 v3Xi(dXiMom);
  const auto XiPt(v3Xi.Pt());
  const auto XiEta(v3Xi.Eta());
  const auto XiPtot(TMath::Sqrt(XiPx*XiPx + XiPy*XiPy + XiPz*XiPz));
  //if ( (XiPt < fCutMinXiPt) || (XiPt > fCutMaxXiPt) ) return 0x0; 

  //V0 Momentum
  const auto V0Px(xi->MomV0X());
  const auto V0Py(xi->MomV0Y());
  const auto V0Pz(xi->MomV0Z());
  const Double_t dV0Mom[3] = {V0Px, V0Py, V0Pz};
  const TVector3 v3V0(dV0Mom);
  //Double_t   V0Pt = TMath::Sqrt(V0Px*V0Px + V0Py*V0Py);
  const auto V0Ptot(TMath::Sqrt(V0Px*V0Px + V0Py*V0Py + V0Pz*V0Pz));

  //Bachlor Momentum
  const auto bachPx(xi->MomBachX());
  const auto bachPy(xi->MomBachY());
  const auto bachPz(xi->MomBachZ());
  const Double_t dBachMom[3] = {bachPx, bachPy, bachPz};
  const TVector3 v3Bach(dBachMom);

  //Pos Momentum
  const auto dPosMomX(xi->MomPosX());
  const auto dPosMomY(xi->MomPosY());
  const auto dPosMomZ(xi->MomPosZ());
  const Double_t dPosMom[3] = {dPosMomX, dPosMomY, dPosMomZ};
  const TVector3 v3Pos(dPosMom);

  //Neg Momentum
  const auto dNegMomX(xi->MomNegX());
  const auto dNegMomY(xi->MomNegY());
  const auto dNegMomZ(xi->MomNegZ());
  const Double_t dNegMom[3] = {dNegMomX, dNegMomY, dNegMomZ};
  const TVector3 v3Neg(dNegMom);

//=============================================================================

  const auto dPtPos(v3Pos.Pt());   if (dPtPos <fCutMinDauPt) return nullptr;
  const auto dPtNeg(v3Neg.Pt());   if (dPtNeg <fCutMinDauPt) return nullptr;
  const auto dPtBach(v3Bach.Pt()); if (dPtBach<fCutMinDauPt) return nullptr;
//=============================================================================

  const auto dEtaPos(pTrkXi->Eta());  if ((dEtaPos<fCutMinDauEta) || (dEtaPos>fCutMaxDauEta)) return nullptr;
  const auto dEtaNeg(nTrkXi->Eta());  if ((dEtaNeg<fCutMinDauEta) || (dEtaNeg>fCutMaxDauEta)) return nullptr;
  const auto dEtaBach(bTrkXi->Eta()); if ((dEtaBach<fCutMinDauEta) || (dEtaBach>fCutMaxDauEta)) return nullptr;
//=============================================================================

  //Cascade Decay radius
  Double_t posXi[3] = {-1000., -1000., -1000.};
  posXi[0] = xi->DecayVertexXiX();
  posXi[1] = xi->DecayVertexXiY();
  posXi[2] = xi->DecayVertexXiZ();
  const auto XiRadius(TMath::Sqrt(posXi[0]*posXi[0] +posXi[1]*posXi[1])); //Xi Decay radius
  //if(XiRadius < fCutMinCascadeRadius || XiRadius > fCutMaxCascadeRadius) return nullptr;
  if(XiRadius < fCutMinCascadeRadius) return nullptr;

  //V0 Decay radius
  Double_t posV0Xi[3] = {-1000., -1000., -1000.};
  posV0Xi[0] = xi->DecayVertexV0X();
  posV0Xi[1] = xi->DecayVertexV0Y();
  posV0Xi[2] = xi->DecayVertexV0Z();
  const auto V0Radius(TMath::Sqrt(posV0Xi[0]*posV0Xi[0] + posV0Xi[1]*posV0Xi[1]));
  //if(V0Radius < fCutMinDauV0Radius || V0Radius > fCutMaxDauV0Radius) return nullptr;
  if(V0Radius < fCutMinDauV0Radius) return nullptr;

  auto dV0DistToSecVtx(0.);
  for (Int_t i=0; i<3; ++i) dV0DistToSecVtx +=  ((posV0Xi[i]-posXi[i]) * (posV0Xi[i]-posXi[i]));
  const auto dV0DistToSecVtxoverP(TMath::Sqrt(dV0DistToSecVtx) / (V0Ptot+1e-10));
  const auto dV0MLoverP(dV0DistToSecVtxoverP * AliPicoBaseDev::MassLambda());

  auto dXiDistToPV(0.);
  for (Int_t i=0; i<3; ++i) dXiDistToPV +=  ((posXi[i]-fPrimaryVtx[i]) * (posXi[i] - fPrimaryVtx[i]));
  const auto dXiDistToPVoverP(TMath::Sqrt(dXiDistToPV) / (XiPtot+1e-10));
//=============================================================================
  const auto rapXi(xi->RapXi()); if ((rapXi<fCutMinCascadeRap) || (rapXi>fCutMaxCascadeRap)) return nullptr;//RapXi
  const auto rapOmega(xi->RapOmega()); if ((rapOmega<fCutMinCascadeRap) || (rapOmega>fCutMaxCascadeRap)) return nullptr;//RapXi

  const auto dcaXitoPV(xi->DcaXiToPrimVertex());  //DCA Cascade to PV
  const auto dcaXiDaughters(xi->DcaXiDaughters());  if (dcaXiDaughters > fCutMaxV0BachDCA) return nullptr; //DCA between Xi daughter(V0 to bach)
  const auto dcaV0ToPrimaryVtxXi(xi->DcaV0ToPrimVertex()); if (dcaV0ToPrimaryVtxXi < fCutMinDauV0DCAtoPV) return nullptr; //DCA V0 to PrimaryVtx
  const auto dcaBachToPrimaryVtxXi(xi->DcaBachToPrimVertex()); if (dcaBachToPrimaryVtxXi < fCutMinBachDCAtoPV) return nullptr; //DCA Bach to PrimaryVtx
  const auto dcaV0DaughtersXi(xi->DcaV0Daughters()); if (dcaV0DaughtersXi > fCutMaxV0DausDCA) return nullptr; //DCA between V0 daughters
  const auto dcaPosToPrimaryVtxXi(xi->DcaPosToPrimVertex()); if (dcaPosToPrimaryVtxXi < fCutMinPosV0DausDCAtoPV) return nullptr; //DCA Positive to PV
  const auto dcaNegToPrimaryVtxXi(xi->DcaNegToPrimVertex()); if (dcaNegToPrimaryVtxXi < fCutMinNegV0DausDCAtoPV) return nullptr; //DCA Negative to PV
  const Double_t dDcaChargeToPV[2] = {dcaPosToPrimaryVtxXi, dcaNegToPrimaryVtxXi};

  const auto XiCosOfPointingAngle(xi->CosPointingAngleXi(fPrimaryVtx[0], fPrimaryVtx[1], fPrimaryVtx[2])); if(XiCosOfPointingAngle < fCutMinCascadeCosPA) return nullptr;//CPA Cascade
  const auto V0CosOfPointingAngleXi(xi->CosPointingAngle(xi->GetDecayVertexXi())); if(V0CosOfPointingAngleXi < fCutMinDauV0CosPA) return nullptr; //CPA V0

//=============================================================================
  //AliAODVertex *rAODVertexXi = xi->GetDecayVertexXi();  //ZY: not used?
  //AliAODVertex *rAODVertexV0 = xi->GetSecondaryVtx(); //ZY: not used?
//=============================================================================
  if (bIsXiNeg || bIsXiPos) {
    const auto dMassOmega(xi->MassOmega());
    if ((fCutMinXiDeletaM>0) && (TMath::Abs(dMassOmega - AliPicoBaseDev::MassOmega())<fCutMinXiDeletaM)){
      bIsXiNeg = kFALSE;
      bIsXiPos = kFALSE;
    }
  }

  if (bIsOmegaNeg || bIsOmegaPos) {
    const auto dMassXi(xi->MassXi());
    if ((fCutMinOmegaDeletaM>0) && (TMath::Abs(dMassXi - AliPicoBaseDev::MassXi())<fCutMinOmegaDeletaM)){
      bIsOmegaNeg = kFALSE;
      bIsOmegaPos = kFALSE;
    }
  }
  if (!(bIsXiNeg || bIsXiPos || bIsOmegaNeg || bIsOmegaPos)) return nullptr;

  UInt_t wV0Mask = 0;
  UInt_t wXiMask = 0;
  if (bIsLambda) wV0Mask |= AliPicoBaseDev::kLambda;
  if (bIsAntiLa) wV0Mask |= AliPicoBaseDev::kAntiLambda;

  if (bIsXiNeg)  wXiMask |= AliPicoBaseDev::kXiNeg;
  if (bIsXiPos)  wXiMask |= AliPicoBaseDev::kXiPos;

  if (bIsOmegaNeg)  wXiMask |= AliPicoBaseDev::kOmegaNeg;
  if (bIsOmegaPos)  wXiMask |= AliPicoBaseDev::kOmegaPos;

  auto bPosInJC(kFALSE);
  auto bNegInJC(kFALSE);

  AliPicoV0RD *pV0rd = new AliPicoV0RD(wV0Mask,
                                       V0Radius,
                                       V0CosOfPointingAngleXi,
                                       dV0DistToSecVtxoverP,
                                       dcaV0DaughtersXi,
                                       dcaPosToPrimaryVtxXi,
                                       dcaNegToPrimaryVtxXi,
                                       dDauXrowsTPC,
                                       dDauXrowsOverFindableClusTPC,
                                       v3Pos.Px(), v3Pos.Py(), v3Pos.Pz(),
                                       v3Neg.Px(), v3Neg.Py(), v3Neg.Pz(),
                                       bPosInJC, bNegInJC,
                                       dPosPionSigmaTPC, dPosProtonSigmaTPC,
                                       dNegPionSigmaTPC, dNegProtonSigmaTPC);


  //return (new AliPicoCascadeRD());
  return (new AliPicoCascadeRD(wXiMask,
                               pV0rd,
                               XiRadius,
                               XiCosOfPointingAngle,
                               dXiDistToPVoverP,
                               dcaXitoPV,
                               dcaV0ToPrimaryVtxXi,
                               dcaXiDaughters,
                               dcaBachToPrimaryVtxXi,
                               bCrossedRowsTPC,
                               bXrowsOverFindableClusTPC,
                               v3Bach.Px(), v3Bach.Py(), v3Bach.Pz(),
                               dBachPionSigmaTPC, dBachKaonSigmaTPC));

}

//_____________________________________________________________________________
AliPicoCascadeMC *AliAnalysisTaskSEStrangeMaker::SelectCascadeCandidateMC(AliAODcascade const *xi)
{
//
//  AliAnalysisTaskSEStrangeMaker::SelectCascadeCandidateMC
//

  if (!xi) return nullptr;
  //if (xi->GetOnFlyStatus()) return 0x0;
//=============================================================================

  auto arrayMC((TClonesArray*) fEventAOD->GetList()->FindObject(AliAODMCParticle::StdBranchName()));
//=============================================================================

  auto pTrkXi(static_cast<AliAODTrack*>(xi->GetDaughter(0))); if (!pTrkXi) return nullptr;
  auto nTrkXi(static_cast<AliAODTrack*>(xi->GetDaughter(1))); if (!nTrkXi) return nullptr;
  auto bTrkXi(static_cast<AliAODTrack*>(xi->GetDecayVertexXi()->GetDaughter(0))); if (!bTrkXi) return nullptr;

  if (!(pTrkXi->IsOn(AliAODTrack::kTPCrefit))) return nullptr;
  if (!(nTrkXi->IsOn(AliAODTrack::kTPCrefit))) return nullptr;
  if (!(bTrkXi->IsOn(AliAODTrack::kTPCrefit))) return nullptr;
  
  //if ((!((pTrkXi->IsOn(AliAODTrack::kITSrefit)) || (pTrkXi->IsOn(AliAODTrack::kTOFout)))) &&
  //    (!((nTrkXi->IsOn(AliAODTrack::kITSrefit)) || (nTrkXi->IsOn(AliAODTrack::kTOFout)))) &&
  //    (!((bTrkXi->IsOn(AliAODTrack::kITSrefit)) || (bTrkXi->IsOn(AliAODTrack::kTOFout))))) return nullptr;
  //======================= 
  auto pTOFExpTDiff = (Double_t)(pTrkXi->GetTOFExpTDiff(fEventAOD->GetMagneticField()));
  auto nTOFExpTDiff = (Double_t)(nTrkXi->GetTOFExpTDiff(fEventAOD->GetMagneticField()));
  auto bTOFExpTDiff = (Double_t)(bTrkXi->GetTOFExpTDiff(fEventAOD->GetMagneticField()));
  if( !(pTrkXi->GetStatus() & AliESDtrack::kITSrefit) && !(nTrkXi->GetStatus() & AliESDtrack::kITSrefit) && !(bTrkXi->GetStatus() & AliESDtrack::kITSrefit) && (pTOFExpTDiff==-2500) && (nTOFExpTDiff==-2500) && (bTOFExpTDiff==-2500)) return nullptr; //OOB
  //UInt_t idxPosXi  = (UInt_t) (pTrkXi->GetID()>=0) ? pTrkXi->GetID() : (-1-(pTrkXi->GetID()));
  //UInt_t idxNegXi  = (UInt_t) (nTrkXi->GetID()>=0) ? nTrkXi->GetID() : (-1-(nTrkXi->GetID()));
  //UInt_t idxBach   = (UInt_t) (bTrkXi->GetID()>=0) ? bTrkXi->GetID() : (-1-(bTrkXi->GetID()));

  std::map<int, int> labels;
  //looking for global tracks and saving their numbers to copy from them PID information to TPC-only tracks in the main loop over tracks
  auto NumofTracks(fEventAOD->GetNumberOfTracks());
  for (int i = 0; i < NumofTracks; i++) {
    const AliAODTrack *AODTrack = dynamic_cast<const AliAODTrack *>(fEventAOD->GetTrack(i));
    assert(AODTrack && "Not a standard AOD");
    if (!AODTrack->TestFilterBit(1<<7)) {
      // Skip TPC-only tracks
      if (AODTrack->GetID() < 0) continue;
      labels[AODTrack->GetID()] = i;
    }
  }

  const auto idxPosXi( (UInt_t)(pTrkXi->TestFilterBit(1<<7)) ? (labels[-1 - pTrkXi->GetID()]) : pTrkXi->GetID());
  const auto idxNegXi( (UInt_t)(nTrkXi->TestFilterBit(1<<7)) ? (labels[-1 - nTrkXi->GetID()]) : nTrkXi->GetID());
  const auto idxBach ( (UInt_t)(bTrkXi->TestFilterBit(1<<7)) ? (labels[-1 - bTrkXi->GetID()]) : bTrkXi->GetID());
  if(idxBach == idxNegXi || idxBach == idxPosXi) return nullptr;

  const auto pCrossedRowsTPC(pTrkXi->GetTPCClusterInfo(2,1)); if (pCrossedRowsTPC < fCutMinDauXrowsTPC) return nullptr;
  const auto nCrossedRowsTPC(nTrkXi->GetTPCClusterInfo(2,1)); if (nCrossedRowsTPC < fCutMinDauXrowsTPC) return nullptr;
  const auto dDauXrowsTPC(pCrossedRowsTPC < nCrossedRowsTPC ? pCrossedRowsTPC : nCrossedRowsTPC);
  const auto bCrossedRowsTPC(bTrkXi->GetTPCClusterInfo(2,1)); if (bCrossedRowsTPC < fCutMinDauXrowsTPC) return nullptr;

  const auto pTPCNClsF(pTrkXi->GetTPCNclsF()); if (pTPCNClsF <= 0) return nullptr;
  const auto nTPCNClsF(nTrkXi->GetTPCNclsF()); if (nTPCNClsF <= 0) return nullptr;
  const auto bTPCNClsF(bTrkXi->GetTPCNclsF()); if (bTPCNClsF <= 0) return nullptr;

  const auto pXrowsOverFindableClusTPC( ((Double_t)pCrossedRowsTPC) / ((Double_t)pTPCNClsF));
  const auto nXrowsOverFindableClusTPC( ((Double_t)nCrossedRowsTPC) / ((Double_t)nTPCNClsF));
  const auto dDauXrowsOverFindableClusTPC( pXrowsOverFindableClusTPC < nXrowsOverFindableClusTPC ? pXrowsOverFindableClusTPC: nXrowsOverFindableClusTPC);
  if (dDauXrowsOverFindableClusTPC<fCutMinDauXrowsOverFindableClusTPC) return nullptr;
  const auto bXrowsOverFindableClusTPC( ((Double_t)bCrossedRowsTPC) / ((Double_t)bTPCNClsF));
  if(bXrowsOverFindableClusTPC < fCutMinDauXrowsOverFindableClusTPC) return nullptr;

//=============================================================================

  //Daughter tracks PID with TPC only:
  //Bool_t isBachelorKaonForTPC = kFALSE;
  //Daughter tracks PID with TPC only:
  auto isBachelorPionForTPC(kFALSE);
  auto isBachelorKaonForTPC(kFALSE);
  auto isNegPionForTPC(kFALSE);
  auto isPosPionForTPC(kFALSE);
  auto isNegProtonForTPC(kFALSE);
  auto isPosProtonForTPC(kFALSE);
  auto bIsLambda(kFALSE);
  auto bIsAntiLa(kFALSE);
  auto bIsXiNeg(kFALSE);
  auto bIsXiPos(kFALSE);
  auto bIsOmegaNeg(kFALSE);
  auto bIsOmegaPos(kFALSE);

  //Xi bach 
  const auto dBachPionSigmaTPC(fRespoPID->NumberOfSigmasTPC(bTrkXi, AliPID::kPion));
  const auto dBachKaonSigmaTPC(fRespoPID->NumberOfSigmasTPC(bTrkXi, AliPID::kKaon));

  //Negative V0 daughter                                                               
  const auto dNegPionSigmaTPC(fRespoPID->NumberOfSigmasTPC(nTrkXi, AliPID::kPion));
  const auto dNegProtonSigmaTPC(fRespoPID->NumberOfSigmasTPC(nTrkXi,AliPID::kProton));
  //Positive V0 daughter                                                               
  const auto dPosPionSigmaTPC(fRespoPID->NumberOfSigmasTPC(pTrkXi,AliPID::kPion));
  const auto dPosProtonSigmaTPC(fRespoPID->NumberOfSigmasTPC(pTrkXi,AliPID::kProton));
  if (fCutMaxCascadeSigmaTPC > 0.){
    isBachelorKaonForTPC = (TMath::Abs(dBachKaonSigmaTPC)<fCutMaxCascadeSigmaTPC);
    
    isBachelorPionForTPC = (TMath::Abs(dBachPionSigmaTPC)<fCutMaxCascadeSigmaTPC);
    isNegPionForTPC      = (TMath::Abs(dNegPionSigmaTPC) <fCutMaxCascadeSigmaTPC);
    isPosPionForTPC      = (TMath::Abs(dPosPionSigmaTPC) <fCutMaxCascadeSigmaTPC);
    
    isNegProtonForTPC    = (TMath::Abs(dNegProtonSigmaTPC)<fCutMaxCascadeSigmaTPC);
    isPosProtonForTPC    = (TMath::Abs(dPosProtonSigmaTPC)<fCutMaxCascadeSigmaTPC);
  } else{
    isBachelorKaonForTPC = kTRUE;
   
    isBachelorPionForTPC = kTRUE;
    isNegPionForTPC      = kTRUE;
    isPosPionForTPC      = kTRUE;
  
    isNegProtonForTPC    = kTRUE;
    isPosProtonForTPC    = kTRUE;
  }

  bIsLambda = isPosProtonForTPC && isNegPionForTPC;
  bIsAntiLa = isNegProtonForTPC && isPosPionForTPC;
  bIsXiNeg = bIsLambda && isBachelorPionForTPC;
  bIsXiPos = bIsAntiLa && isBachelorPionForTPC;
  bIsOmegaNeg = bIsLambda && isBachelorKaonForTPC;
  bIsOmegaPos = bIsAntiLa && isBachelorKaonForTPC;

  const auto iChargeXi(xi->ChargeXi());
  if (bIsXiNeg && iChargeXi>0) return nullptr;
  if (bIsXiPos && iChargeXi<0) return nullptr;
  if (bIsOmegaNeg && iChargeXi>0) return nullptr;
  if (bIsOmegaPos && iChargeXi<0) return nullptr;

  if (!(bIsXiNeg || bIsXiPos || bIsOmegaNeg || bIsOmegaPos)) return nullptr;


//=============================================================================

  // - MC perfect PID

  const auto inp(TMath::Abs(pTrkXi->GetLabel()));
  const auto inn(TMath::Abs(nTrkXi->GetLabel()));
  const auto inb(TMath::Abs(bTrkXi->GetLabel()));
  if (pTrkXi->GetLabel() == -1 || nTrkXi->GetLabel() == -1 || bTrkXi->GetLabel() == -1) return nullptr;

  //Level of the tracks
  const auto pDauPosMC((AliAODMCParticle*)arrayMC->At(inp));
  const auto pDauNegMC((AliAODMCParticle*)arrayMC->At(inn));
  const auto pDauBachMC((AliAODMCParticle*)arrayMC->At(inb));
  const auto iPdgBach(pDauBachMC->GetPdgCode());

  //Level of the V0
  const auto iV0p(pDauPosMC->GetMother()); if (iV0p<0) return nullptr;//this particle is primary, no mother
  const auto iV0n(pDauNegMC->GetMother()); if (iV0n<0) return nullptr;//this particle is primary, no mother
  if (iV0p != iV0n) return nullptr;//same mother
  const auto iV0 = iV0p;
  const auto pV0MC((AliAODMCParticle*)arrayMC->At(iV0)); if (!pV0MC) return nullptr;
  const auto iPdgV0(pV0MC->GetPdgCode());


  //Level of the Xi
  const auto iXiV(pV0MC->GetMother());      if (iXiV<0) return nullptr;//this particle is primary, no mother
  const auto iXib(pDauBachMC->GetMother()); if (iXib<0) return nullptr;//this particle is primary, no mother
  if (iXib != iXiV) return nullptr;//same mother
  const auto iXi(iXib);
  const auto pXiMC((AliAODMCParticle*)arrayMC->At(iXi)); if (!pXiMC) return nullptr;
  const auto iPdgXi(pXiMC ->GetPdgCode());

//=============================================================================

  const auto bIsXiMinus((iPdgXi == 3312  && iPdgV0 == 3122   && iPdgBach == -211));
  const auto bIsXiPlus((iPdgXi == -3312  && iPdgV0 == -3122  && iPdgBach == 211 ));
  const auto bIsOmegaMinus((iPdgXi == 3334  && iPdgV0 == 3122   && iPdgBach == -321));
  const auto bIsOmegaPlus((iPdgXi == -3334  && iPdgV0 == -3122  && iPdgBach == 321 ));
  if (!(bIsXiPlus || bIsXiMinus || bIsOmegaMinus || bIsOmegaPlus)) return nullptr;

  if (((pXiMC->Y())<fCutMinCascadeRap) || ((pXiMC->Y())>fCutMaxCascadeRap)) return nullptr;
//=============================================================================

  auto  idXiMC(0);
  UInt_t wsXiMC(0);
  UInt_t wsV0MC(0);

  auto dXiPxMC(0.);
  auto dXiPyMC(0.);
  auto dXiPzMC(0.);
  auto dXiPtMC(0.);
  auto dXiEngMC(0.);
  auto dXiEtaMC(0.);
  auto dXiRapMC(0.);
  if (pXiMC) {
    idXiMC = pXiMC->GetPdgCode();
    if ((bIsXiMinus  && (idXiMC== 3312))    ||
        (bIsXiPlus && (idXiMC==-3312))      ||
        (bIsOmegaMinus && (idXiMC == 3334)) ||
        (bIsOmegaPlus && (idXiMC == -3334)))
    {
      dXiPxMC  = pXiMC->Px();
      dXiPyMC  = pXiMC->Py();
      dXiPzMC  = pXiMC->Pz();
      dXiPtMC  = pXiMC->Pt();
      dXiEngMC = pXiMC->E();
      dXiEtaMC = pXiMC->Eta();
      dXiRapMC = pXiMC->Y();
      if (pXiMC->IsPrimary())                wsXiMC |= AliPicoBaseDev::kPrimary;
      if (pXiMC->IsPhysicalPrimary())        wsXiMC |= AliPicoBaseDev::kPhysicalPrimary;
      if (pXiMC->IsSecondaryFromWeakDecay()) wsXiMC |= AliPicoBaseDev::kSecondaryFromWeakDecay;
      if (pXiMC->IsSecondaryFromMaterial())  wsXiMC |= AliPicoBaseDev::kSecondaryFromMaterial;
      //if (!(pXiMC->IsPhysicalPrimary())) return nullptr;

      if (pV0MC->IsPrimary())                wsV0MC |= AliPicoBaseDev::kPrimary;
      if (pV0MC->IsPhysicalPrimary())        wsV0MC |= AliPicoBaseDev::kPhysicalPrimary;
      if (pV0MC->IsSecondaryFromWeakDecay()) wsV0MC |= AliPicoBaseDev::kSecondaryFromWeakDecay;
      if (pV0MC->IsSecondaryFromMaterial())  wsV0MC |= AliPicoBaseDev::kSecondaryFromMaterial;
    }
  }
//=============================================================================
  if (xi->Chi2Xi()>fCutMaxCascadeChi2) return nullptr;//Chi2Xi
  if (xi->Chi2V0()>fCutMaxDauV0Chi2) return nullptr;//Chi2V0

  //Cascade Momentum
  const auto XiPx(xi->MomXiX());
  const auto XiPy(xi->MomXiY());
  const auto XiPz(xi->MomXiZ());
  const auto XiRap(xi->RapXi());
  const auto OmegaRap(xi->RapOmega());
  const Double_t dXiMom[3] = {XiPx, XiPy, XiPz};
  const TVector3 v3Xi(dXiMom);
  const auto XiPt(v3Xi.Pt());
  const auto XiEta(v3Xi.Eta());
  const auto XiPtot(TMath::Sqrt(XiPx*XiPx + XiPy*XiPy + XiPz*XiPz));
  //if ( (XiPt < fCutMinXiPt) || (XiPt > fCutMaxXiPt) ) return 0x0; 

  //V0 Momentum
  const auto V0Px(xi->MomV0X());
  const auto V0Py(xi->MomV0Y());
  const auto V0Pz(xi->MomV0Z());
  const Double_t dV0Mom[3] = {V0Px, V0Py, V0Pz};
  const TVector3 v3V0(dV0Mom);
  const auto V0Pt(TMath::Sqrt(V0Px*V0Px + V0Py*V0Py));
  const auto V0Ptot(TMath::Sqrt(V0Px*V0Px + V0Py*V0Py + V0Pz*V0Pz));

  //Bachlor Momentum
  const auto bachPx(xi->MomBachX());
  const auto bachPy(xi->MomBachY());
  const auto bachPz(xi->MomBachZ());
  const Double_t dBachMom[3] = {bachPx, bachPy, bachPz};
  const TVector3 v3Bach(dBachMom);

  //Pos Momentum
  const auto dPosMomX(xi->MomPosX());
  const auto dPosMomY(xi->MomPosY());
  const auto dPosMomZ(xi->MomPosZ());
  const Double_t dPosMom[3] = {dPosMomX, dPosMomY, dPosMomZ};
  const TVector3 v3Pos(dPosMom);

  //Neg Momentum
  const auto dNegMomX(xi->MomNegX());
  const auto dNegMomY(xi->MomNegY());
  const auto dNegMomZ(xi->MomNegZ());
  const Double_t dNegMom[3] = {dNegMomX, dNegMomY, dNegMomZ};
  const TVector3 v3Neg(dNegMom);

//=============================================================================

  const auto dPtPos(v3Pos.Pt());   if (dPtPos <fCutMinDauPt) return nullptr;
  const auto dPtNeg(v3Neg.Pt());   if (dPtNeg <fCutMinDauPt) return nullptr;
  const auto dPtBach(v3Bach.Pt()); if (dPtBach<fCutMinDauPt) return nullptr;
//=============================================================================

  const auto dEtaPos(pTrkXi->Eta());  if ((dEtaPos<fCutMinDauEta) || (dEtaPos>fCutMaxDauEta)) return nullptr;
  const auto dEtaNeg(nTrkXi->Eta());  if ((dEtaNeg<fCutMinDauEta) || (dEtaNeg>fCutMaxDauEta)) return nullptr;
  const auto dEtaBach(bTrkXi->Eta()); if ((dEtaBach<fCutMinDauEta) || (dEtaBach>fCutMaxDauEta)) return nullptr;
//=============================================================================

  //Cascade Decay radius
  Double_t posXi[3] = {-1000., -1000., -1000.};
  posXi[0] = xi->DecayVertexXiX();
  posXi[1] = xi->DecayVertexXiY();
  posXi[2] = xi->DecayVertexXiZ();
  const auto XiRadius(TMath::Sqrt(posXi[0]*posXi[0] +posXi[1]*posXi[1])); //Xi Decay radius
  //if(XiRadius < fCutMinCascadeRadius || XiRadius > fCutMaxCascadeRadius) return nullptr;
  if(XiRadius < fCutMinCascadeRadius) return nullptr;

  //V0 Decay radius
  Double_t posV0Xi[3] = {-1000., -1000., -1000.};
  posV0Xi[0] = xi->DecayVertexV0X();
  posV0Xi[1] = xi->DecayVertexV0Y();
  posV0Xi[2] = xi->DecayVertexV0Z();
  const auto V0Radius(TMath::Sqrt(posV0Xi[0]*posV0Xi[0] + posV0Xi[1]*posV0Xi[1]));
  //if(V0Radius < fCutMinDauV0Radius || V0Radius > fCutMaxDauV0Radius) return nullptr;
  if(V0Radius < fCutMinDauV0Radius) return nullptr;

  auto dV0DistToSecVtx(0.);
  for (Int_t i=0; i<3; ++i) dV0DistToSecVtx +=  ((posV0Xi[i]-posXi[i]) * (posV0Xi[i]-posXi[i]));
  const auto dV0DistToSecVtxoverP(TMath::Sqrt(dV0DistToSecVtx) / (V0Ptot+1e-10));
  const auto dV0MLoverP(dV0DistToSecVtxoverP * AliPicoBaseDev::MassLambda());
  //if ((dV0DistToSecVtxoverP*fgkMassLambda)>fCutMaxDauLaCtau) return nullptr; 

  auto dXiDistToPV(0.);
  for (Int_t i=0; i<3; ++i) dXiDistToPV +=  ((posXi[i]-fPrimaryVtx[i]) * (posXi[i] - fPrimaryVtx[i]));
  const auto dXiDistToPVoverP(TMath::Sqrt(dXiDistToPV) / (XiPtot+1e-10));
//=============================================================================

  const auto rapXi(xi->RapXi()); if ((rapXi<fCutMinCascadeRap) || (rapXi>fCutMaxCascadeRap)) return nullptr;//RapXi
  const auto rapOmega(xi->RapOmega()); if ((rapOmega<fCutMinCascadeRap) || (rapOmega>fCutMaxCascadeRap)) return nullptr;//RapXi

  const auto dcaXitoPV(xi->DcaXiToPrimVertex());  //DCA Cascade to PV
  const auto dcaXiDaughters(xi->DcaXiDaughters());  if (dcaXiDaughters > fCutMaxV0BachDCA) return nullptr; //DCA between Xi daughter(V0 to bach)
  const auto dcaV0ToPrimaryVtxXi(xi->DcaV0ToPrimVertex()); if (dcaV0ToPrimaryVtxXi < fCutMinDauV0DCAtoPV) return nullptr; //DCA V0 to PrimaryVtx
  const auto dcaBachToPrimaryVtxXi(xi->DcaBachToPrimVertex()); if (dcaBachToPrimaryVtxXi < fCutMinBachDCAtoPV) return nullptr; //DCA Bach to PrimaryVtx
  const auto dcaV0DaughtersXi(xi->DcaV0Daughters()); if (dcaV0DaughtersXi > fCutMaxV0DausDCA) return nullptr; //DCA between V0 daughters
  const auto dcaPosToPrimaryVtxXi(xi->DcaPosToPrimVertex()); if (dcaPosToPrimaryVtxXi < fCutMinPosV0DausDCAtoPV) return nullptr; //DCA Positive to PV
  const auto dcaNegToPrimaryVtxXi(xi->DcaNegToPrimVertex()); if (dcaNegToPrimaryVtxXi < fCutMinNegV0DausDCAtoPV) return nullptr; //DCA Negative to PV
  const Double_t dDcaChargeToPV[2] = {dcaPosToPrimaryVtxXi, dcaNegToPrimaryVtxXi};

  const auto XiCosOfPointingAngle(xi->CosPointingAngleXi(fPrimaryVtx[0], fPrimaryVtx[1], fPrimaryVtx[2])); if(XiCosOfPointingAngle < fCutMinCascadeCosPA) return nullptr;//CPA Cascade
  const auto V0CosOfPointingAngleXi(xi->CosPointingAngle(xi->GetDecayVertexXi())); if(V0CosOfPointingAngleXi < fCutMinDauV0CosPA) return nullptr; //CPA V0

//=============================================================================
  //AliAODVertex *rAODVertexXi = xi->GetDecayVertexXi();  //ZY: not used?
  //AliAODVertex *rAODVertexV0 = xi->GetSecondaryVtx(); //ZY: not used?
//=============================================================================
  if (bIsXiNeg || bIsXiPos) {
    const auto dMassOmega(xi->MassOmega());
    if ((fCutMinXiDeletaM>0) && (TMath::Abs(dMassOmega - AliPicoBaseDev::MassOmega())<fCutMinXiDeletaM)){
      bIsXiNeg = kFALSE;
      bIsXiPos = kFALSE;
    }
  }

  if (bIsOmegaNeg || bIsOmegaPos) {
    const auto dMassXi(xi->MassXi());
    if ((fCutMinOmegaDeletaM>0) && (TMath::Abs(dMassXi - AliPicoBaseDev::MassXi())<fCutMinOmegaDeletaM)){
      bIsOmegaNeg = kFALSE;
      bIsOmegaPos = kFALSE;
    }
  }
  if (!(bIsXiNeg || bIsXiPos || bIsOmegaNeg || bIsOmegaPos)) return nullptr;

  UInt_t wV0Mask = 0;
  UInt_t wXiMask = 0;
  if (bIsLambda) wV0Mask |= AliPicoBaseDev::kLambda;
  if (bIsAntiLa) wV0Mask |= AliPicoBaseDev::kAntiLambda;

  if (bIsXiNeg)  wXiMask |= AliPicoBaseDev::kXiNeg;
  if (bIsXiPos)  wXiMask |= AliPicoBaseDev::kXiPos;

  if (bIsOmegaNeg)  wXiMask |= AliPicoBaseDev::kOmegaNeg;
  if (bIsOmegaPos)  wXiMask |= AliPicoBaseDev::kOmegaPos;

  auto bPosInJC(kFALSE);
  auto bNegInJC(kFALSE);

//=============================================================================
AliPicoV0MC *pV0mc = new AliPicoV0MC(wV0Mask,
                                     V0Radius,
                                     V0CosOfPointingAngleXi,
                                     dV0DistToSecVtxoverP,
                                     dcaV0DaughtersXi,
                                     dcaPosToPrimaryVtxXi,
                                     dcaNegToPrimaryVtxXi,
                                     dDauXrowsTPC,
                                     dDauXrowsOverFindableClusTPC,
                                     v3Pos.Px(), v3Pos.Py(), v3Pos.Pz(),
                                     v3Neg.Px(), v3Neg.Py(), v3Neg.Pz(),
                                     bPosInJC, bNegInJC,
                                     iPdgV0, wsV0MC, pV0MC->Px(), pV0MC->Py(), pV0MC->Pz(), pV0MC->E(),
                                     idXiMC, wsXiMC, dXiPtMC, dXiEtaMC, dXiRapMC);

  return (new AliPicoCascadeMC(wXiMask,
                               pV0mc,
                               XiRadius,
                               XiCosOfPointingAngle,
                               dXiDistToPVoverP,
                               dcaXitoPV,
                               dcaV0ToPrimaryVtxXi,
                               dcaXiDaughters,
                               dcaBachToPrimaryVtxXi,
                               bCrossedRowsTPC,
                               bXrowsOverFindableClusTPC,
                               v3Bach.Px(), v3Bach.Py(), v3Bach.Pz(),
                               idXiMC, wsXiMC,
                               dXiPxMC, dXiPyMC, dXiPzMC, dXiEngMC));

}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskSEStrangeMaker::IsEventNotAcpt()
{
//
//  AliAnalysisTaskSEStrangeMaker::IsEventNotAcpt
//

  fEventAcptMask = 0;
  if (!InputEvent())  return kTRUE;
  if (!fInputHandler) return kTRUE;

  fEventAOD = dynamic_cast<AliAODEvent*>(InputEvent());
  fEventESD = dynamic_cast<AliESDEvent*>(InputEvent());
  if ((!fEventAOD) && (!fEventESD)) return kTRUE;
//=============================================================================

  fRespoPID = fInputHandler->GetPIDResponse(); if (!fRespoPID) return kTRUE;
//=============================================================================

  if (fIsAnaUseMC) {
    if (MCEvent()) {
      if (MCEvent()->GetNumberOfTracks()<=0) return kTRUE;
    } else {
      return kTRUE;
    }

    const auto pHeader(MCEvent()->Header()); if (!pHeader) return kTRUE;

    if (fIsDPMjetMC) {
      const auto pDPMjetH(dynamic_cast<AliGenDPMjetEventHeader*>(pHeader->GenEventHeader()));

      if (pDPMjetH) {
        auto nd0(0), nd1(0), nd2(0);
        pDPMjetH->GetNDiffractive(nd1, nd2, nd0);
        if ((nd1+nd2) != (pDPMjetH->ProjectileParticipants() + pDPMjetH->TargetParticipants())) return kTRUE;
      }
    }
  }

  fEventAcptMask |= AliPicoBase::kEventCheck;
//=============================================================================

  if ((fMultEsti.GetEntries()>0) || (!fMultEstDef.IsNull())) {
    Float_t dMult(-999.);

    if (fUseMultOld) {
      auto pCentSel(InputEvent()->GetCentrality());
      if (!pCentSel) { fEventAcptMask=0; return kTRUE; }
      if (pCentSel->GetQuality()!=0) return kFALSE;

      if (fMultEsti.GetEntries()>0) {
        TObjString *ps(nullptr);
        const auto next(fMultEsti.MakeIterator());
        while ((ps = static_cast<TObjString*>((*next)()))) {
          const auto s(ps->String());
          const auto p(static_cast<TParameter<Float_t>*>((fMultEsti(s.Data()))));
          if (p) p->SetVal(pCentSel->GetCentralityPercentile(s.Data()));
        }
      }

      if (!fMultEstDef.IsNull()) dMult = pCentSel->GetCentralityPercentile(fMultEstDef.Data());
    } else {
      auto pMultSel(static_cast<AliMultSelection*>(InputEvent()->FindListObject("MultSelection")));
      if (!pMultSel) { fEventAcptMask=0; return kTRUE; }

      if (fMultEsti.GetEntries()>0) {
        TObjString *ps(nullptr);
        const auto next(fMultEsti.MakeIterator());
        while (((ps = static_cast<TObjString*>((*next)())))) {
          const auto s(ps->String());
          const auto p(static_cast<TParameter<Float_t>*>(fMultEsti(s.Data())));
          if (p) p->SetVal(pMultSel->GetMultiplicityPercentile(s.Data()));
        }
      }

      if (!fMultEstDef.IsNull()) dMult = pMultSel->GetMultiplicityPercentile(fMultEstDef.Data());
    }

    if (!fMultEstDef.IsNull()) if ((dMult<fCutMinMult) || (dMult>=fCutMaxMult)) return kTRUE;
  }

  fEventAcptMask |= AliPicoBase::kEventMult;
//=============================================================================

  const UInt_t wMask(fInputHandler->IsEventSelected());
  if ((wMask & fTriggerMask) != fTriggerMask) return kTRUE;
  if (fIsSkipFastOnly) if ((wMask & AliVEvent::kFastOnly) == AliVEvent::kFastOnly) return kTRUE;

  fEventAcptMask |= AliPicoBase::kEventTrigger;
//=============================================================================
  const auto pVertex(InputEvent()->GetPrimaryVertex());
  if (!pVertex) return kTRUE;
  pVertex->GetXYZ(fPrimaryVtx);

  if (fUseAnaUtils) {
    auto pUtils(new AliAnalysisUtils());
    pUtils->SetMinVtxContr(2);
    if (pUtils->IsSPDClusterVsTrackletBG(InputEvent())) return kTRUE;
    if (pUtils->IsPileUpEvent(InputEvent())) return kTRUE;
    if (!pUtils->IsVertexSelected2013pA(InputEvent()))  return kTRUE;

    if ((fCollisionType==(AliPicoBase::kPA)) ||
        (fCollisionType==(AliPicoBase::kAP))) {
      if (pUtils->IsFirstEventInChunk(InputEvent())) return kFALSE;
    }
  }

  fEventAcptMask |= AliPicoBase::kEventVertex;
//=============================================================================

  if (fIsRefitV0sESD && fEventESD) {
    Double_t dCuts[7] = { fCutMaxV0Chi2,
                          fCutMinDauDCAtoPV,
                          fCutMinDauDCAtoPV,
                          fCutMaxDausDCA,
                          fCutMinKshortCosPA,
                          fCutMinV0Radius,
                          fCutMaxV0Radius };

    fEventESD->ResetV0s();
    AliV0vertexer aV0vtxer;
    aV0vtxer.SetDefaultCuts(dCuts);
    aV0vtxer.Tracks2V0vertices(fEventESD);
  }
//=============================================================================
  if (fIsRefitCascadeESD && fEventESD) {
    Double_t dCutsXi[8] = { fCutMaxCascadeChi2,
                          fCutMinDauV0DCAtoPV,
                          fCutMinDauLaDeletaM,
                          fCutMinBachDCAtoPV,
                          fCutMaxV0BachDCA,
                          fCutMinCascadeCosPA,
                          fCutMinCascadeRadius,
                          fCutMaxCascadeRadius };

    fEventESD->ResetCascades();
    AliCascadeVertexer aCascvtxer;
    //aCascvtxer.SetDefaultCuts(dCutsXi);
    aCascvtxer.SetCuts(dCutsXi);
    aCascvtxer.V0sTracks2CascadeVertices(fEventESD);
  }

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskSEStrangeMaker::IsEventNotINEL()
{
//
//  AliAnalysisTaskSEStrangeMaker::IsEventNotINEL
//

  if ((fEventAcptMask & AliPicoBase::kEventCheck) != AliPicoBase::kEventCheck) return kTRUE;
  if ((fEventAcptMask & AliPicoBase::kEventMult)  != AliPicoBase::kEventMult)  return kTRUE;

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t AliAnalysisTaskSEStrangeMaker::IsEventNotMBsa()
{
//
//  AliAnalysisTaskSEStrangeMaker::IsEventNotMBsa
//

  if (IsEventNotINEL()) return kTRUE;
  if ((fEventAcptMask & AliPicoBase::kEventTrigger) != AliPicoBase::kEventTrigger) return kTRUE;
  if ((fEventAcptMask & AliPicoBase::kEventVertex)  != AliPicoBase::kEventVertex)  return kTRUE;

  return kFALSE;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::FillHistogramsEH()
{
//
//  AliAnalysisTaskSEStrangeMaker::FillHistogramsEH
//

  const auto h(static_cast<TH1D*>(fOutputListEH->FindObject("hEventCheck")));

  if (fEventAcptMask==0) h->Fill(0.);
  if ((fEventAcptMask & AliPicoBase::kEventCheck)   == AliPicoBase::kEventCheck)   h->Fill(1.);
  if ((fEventAcptMask & AliPicoBase::kEventMult)    == AliPicoBase::kEventMult)    h->Fill(2.);
  if ((fEventAcptMask & AliPicoBase::kEventTrigger) == AliPicoBase::kEventTrigger) h->Fill(3.);
  if ((fEventAcptMask & AliPicoBase::kEventVertex)  == AliPicoBase::kEventVertex)  h->Fill(4.);

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::FillHistogramsMC()
{
//
//  AliAnalysisTaskSEStrangeMaker::FillHistogramsMC
//

  auto nPrimary(0);
  AliStack *pStack(nullptr);

  if (fEventESD) {
    pStack   = MCEvent()->Stack(); if (!pStack) return;
    nPrimary = pStack->GetNprimary();
  }
//=============================================================================

  if (fMultEsti.GetEntries()>0) {
    auto pMultSel(static_cast<AliMultSelection*>(InputEvent()->FindListObject("MultSelection")));
    if (!pMultSel) return;
    TObjString *ps(nullptr);
    const auto next(fMultEsti.MakeIterator());
    while (((ps = static_cast<TObjString*>((*next)())))) {
      const auto s(ps->String());
      const auto p(static_cast<TParameter<Float_t>*>(fMultEsti(s.Data())));
      if (p) p->SetVal(pMultSel->GetMultiplicityPercentile(s.Data()));
    }
  }

  const auto n(6+fMultEsti.GetEntries());
  //const auto dEvType(IsEventNotMBsa() ? 1.5 : 0.5);
  const auto dEvType(0.5);
  auto hsV0(static_cast<THnSparseD*>(fOutputListMC->FindObject("hsV0")));
  auto hsXi(static_cast<THnSparseD*>(fOutputListMC->FindObject("hsXi")));

  if (!(hsV0 && hsXi)) {
    AliFatal("Cannot find hsV0 or hsXi; should not happen");
    return;
  }
//=============================================================================

  for (auto i=0; i<MCEvent()->GetNumberOfTracks(); ++i) {
    TParticle *pESD(nullptr);
    AliAODMCParticle *pAOD(nullptr);

    if (fEventAOD) {
      pAOD = static_cast<AliAODMCParticle*>(MCEvent()->GetTrack(i));
      if (!pAOD) continue;
    }

    if (fEventESD) {
      const auto pMC(static_cast<AliMCParticle*>(MCEvent()->GetTrack(i))); if (!pMC) continue;
      pESD = pMC->Particle(); if (!pESD) continue;
    }
//=============================================================================

    const auto bPri(pAOD ? pAOD->IsPrimary() : (i<nPrimary));
    const auto bPhy(pAOD ? pAOD->IsPhysicalPrimary() : pStack->IsPhysicalPrimary(i));
    if (!(bPri || bPhy)) continue;
//=============================================================================

    const auto id(pAOD ? pAOD->GetPdgCode() : pESD->GetPdgCode());

    //const auto bXi(bPri && ((id==3312) || (id==-3312)));
    const auto bXi(bPhy && ((id==3312) || (id==-3312) || (id == 3334) || (id == -3334)));
    const auto bV0(bPhy && ((id==3122) || (id==-3122) || (id==310)));
    if (!(bXi || bV0)) continue;
//=============================================================================

    const auto dEta(pAOD ? pAOD->Eta() : pESD->Eta());
    if ((dEta<-5.) || (dEta>=5.)) continue;

    const auto dRapLab(pAOD ? pAOD->Y() : pESD->Y());
    if ((dRapLab<-5.) || (dRapLab>=5.)) continue;

    const auto dRapCMS(dRapLab + fRapidityShift);
    if ((dRapCMS<-5.) || (dRapCMS>=5.)) continue;
//=============================================================================

    Double_t dVar[n];
    dVar[0] = (pAOD ? pAOD->Pt() : pESD->Pt());

    dVar[1] = dEta;
    dVar[2] = dRapLab;
    dVar[3] = dRapCMS;
    dVar[4] = dEvType;

    auto l(6);
    TObjString *ps(nullptr);
    const auto next(fMultEsti.MakeIterator());
    while ((ps = static_cast<TObjString*>((*next)()))) {
      const auto s(ps->String());
      const auto p(static_cast<TParameter<Float_t>*>(fMultEsti(s.Data())));
      if (p) dVar[l++] = p->GetVal();
    }

    if (bV0) {
      if (id== 310 ) dVar[5] = 0.;
      if (id== 3122) dVar[5] = 1.;
      if (id==-3122) dVar[5] = 2.;
      hsV0->Fill(dVar);
    }

    if (bXi) {
      if (id== 3312) dVar[5] = 0.;
      if (id==-3312) dVar[5] = 1.;
      if (id== 3334) dVar[5] = 2.;
      if (id==-3334) dVar[5] = 3.;
      hsXi->Fill(dVar);
    }
  }
//=============================================================================

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::CreateHistogramsEH()
{
//
//  AliAnalysisTaskSEStrangeMaker::CreateHistogramsEH
//

  const auto b(TH1::AddDirectoryStatus());
  TH1::AddDirectory(kFALSE);
//=============================================================================

  fOutputListEH->Add(new TH1D("hEventCheck", "", 5, -0.5, 4.5));
  fOutputListEH->Add(new TH1D("hEventNumber", "", 5, -0.5, 4.5));
  //fOutputListEH->Add(new TH1D("TOFExpTDiff", "", 1000, 0, 100));
  fOutputListEH->Add(new TH2D("hKshortPtInvM", "", 1000, 0., 100., 300, AliPicoBase::MassKshort()-0.15, AliPicoBase::MassKshort()+0.15));
  fOutputListEH->Add(new TH2D("hLambdaPtInvM", "", 1000, 0., 100., 200, AliPicoBase::MassLambda()-0.10, AliPicoBase::MassLambda()+0.10));
  fOutputListEH->Add(new TH2D("hAntiLaPtInvM", "", 1000, 0., 100., 200, AliPicoBase::MassLambda()-0.10, AliPicoBase::MassLambda()+0.10));
  fOutputListEH->Add(new TH2D("hXiNegPtInvM", "", 1000, 0., 100., 200, AliPicoBaseDev::MassXi()-0.10, AliPicoBaseDev::MassXi()+0.10));
  fOutputListEH->Add(new TH2D("hXiPosPtInvM", "", 1000, 0., 100., 200, AliPicoBaseDev::MassXi()-0.10, AliPicoBaseDev::MassXi()+0.10));
  fOutputListEH->Add(new TH2D("hOmegaNegPtInvM", "", 1000, 0., 100., 200, AliPicoBaseDev::MassOmega()-0.10, AliPicoBaseDev::MassOmega()+0.10));
  fOutputListEH->Add(new TH2D("hOmegaPosPtInvM", "", 1000, 0., 100., 200, AliPicoBaseDev::MassOmega()-0.10, AliPicoBaseDev::MassOmega()+0.10));


  TH1 *h(nullptr);
  TListIter next(fOutputListEH);
  //while ((h = static_cast<TH1*>(next()))) h->Sumw2();

  TH1::AddDirectory(b);
  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::CreateHistogramsMC()
{
//
//  AliAnalysisTaskSEStrangeMaker::CreateHistogramsMC
//

  const auto b(TH1::AddDirectoryStatus());
  TH1::AddDirectory(kFALSE);
//=============================================================================

  const auto nr(5); // 0: Pt
                    // 1: eta
                    // 2: rap in Lab
                    // 3: rap in CMS
                    // 4: Event type
                    //    ==0.5, INEL
                    //    ==1.5, MB
                    // 5: particle type
                    //   V0
                    //     ==0, Kshort
                    //     ==1, Lambda
                    //     ==2, AntiLa
                    //   Xi
                    //     ==0, XiNeg
                    //     ==1, XiPos
                    //     ==2, OmegaNeg
                    //     ==3, OmegaPos

  const Int_t    nBin[nr] = { 1000, 100, 100, 100, 2  };
  const Double_t dMin[nr] = {   0., -5., -5., -5., 0. };
  const Double_t dMax[nr] = { 100.,  5.,  5.,  5., 2. };
  const auto ns(1 + nr + fMultEsti.GetEntries());
//=============================================================================

  Int_t nV0Bin[ns], nXiBin[ns];
  Double_t dV0Min[ns], dV0Max[ns];
  Double_t dXiMin[ns], dXiMax[ns];

  for (auto i=0; i<ns; ++i) {
    if (i<nr) {
      nV0Bin[i] = nXiBin[i] = nBin[i];
      dV0Min[i] = dXiMin[i] = dMin[i];
      dV0Max[i] = dXiMax[i] = dMax[i];
    }

    if (i==nr) {
      nV0Bin[i] = 3; dV0Min[i] = -0.5; dV0Max[i] = 2.5;
      nXiBin[i] = 4; dXiMin[i] = -0.5; dXiMax[i] = 3.5;
    }

    if (i>nr) {
      nV0Bin[i] = nXiBin[i] =  110;
      dV0Min[i] = dXiMin[i] =  -5.;
      dV0Max[i] = dXiMax[i] = 105.;
    }
  }
//=============================================================================

  const TString sa[nr+1] { "pT", "eta", "y_lab", "y_cms", "evt_t", "par_t" };
  fOutputListMC->Add(new THnSparseD("hsV0", "", ns, nV0Bin, dV0Min, dV0Max));
  fOutputListMC->Add(new THnSparseD("hsXi", "", ns, nXiBin, dXiMin, dXiMax));

  TObjString *ps(nullptr);
  THnSparseD *hs(nullptr);
  TListIter next(fOutputListMC);
  const auto pn(fMultEsti.MakeIterator());
  while ((hs = static_cast<THnSparseD*>(next()))) {
    for (auto i=0; i<=nr; ++i) hs->GetAxis(i)->SetName(sa[i].Data());

    auto l(nr+1);
    while ((ps = static_cast<TObjString*>((*pn)()))) {
      const auto s(ps->String());
      const auto p(hs->GetAxis(l++));
      if (p) p->SetName(s.Data());
    }
  }
//=============================================================================

  TH1::AddDirectory(b);

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::InitAnalysis()
{
//
//  AliAnalysisTaskSEStrangeMaker::InitAnalysis
//

  if (fCollisionType==(AliPicoBase::kPP)) InitParamsPP();
  if (fCollisionType==(AliPicoBase::kPA)) InitParamsPA();
  if (fCollisionType==(AliPicoBase::kAP)) InitParamsAP();
  if (fCollisionType==(AliPicoBase::kAA)) InitParamsAA();

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::InitParamsPP()
{
//
//  AliAnalysisTaskSEStrangeMaker::InitParametersPP
//

  fRapidityShift = 0.;
//=============================================================================

  fCutMaxV0Chi2   = 33.;
  fCutMinV0Radius = 0.3;   // default: >0.5; uncertainty: >0.3, 0.4, 0.6, 0.7;
  fCutMaxV0Radius = 200.;  // default: not applied in pp
//=============================================================================

  fCutMaxDausDCA                     = 1.5;  // default: <1;    uncertainty: <0.5, 0.75, 1.25, 1.5
  fCutMinDauDCAtoPV                  = 0.05; // default: >0.06; uncertainty: >0.05, 0.055, 0.07, 0.08
  fCutMinDauXrowsTPC                 = 70.;  // default: >70;   uncertainty: >75, 80
  fCutMinDauXrowsOverFindableClusTPC = 0.8;  // default: >0.8;  uncertainty: >0.95
//=============================================================================

  fCutMaxKshortSigmaTPC = -1.;   // default: <5;     uncertainty: w/o cut
  fCutMinKshortCosPA    = 0.95;  // default: >0.97;  uncertainty: >0.95, 0.96, 0.98, 0.99
  fCutMaxKshortCtau     = 30.;   // default: <20;    uncertainty: <12, 30
  fCutMaxKshortArmFrac  = -1.;   // default: not applied in pp
  fCutMinKshortDeltaM   = 0.003; // default: >0.005; uncertainty: >0.003, 0.006
//=============================================================================

  fCutMaxLambdaSigmaTPC  = 7.;    // default: <5;     uncertainty: 4, 6, 7
  fCutMinLambdaCosPA     = 0.993; // default: >0.995; uncertainty: >0.993, 0.994, 0.996, 0.997
  fCutMaxLambdaCtau      = 40.;   // default: <30;    uncertainty: <20, 40
  fCutMaxLambdaArmFrac   = -1.;   // default: not applied in pp
  fCutMinLambdaDeletaM   = -1.;   // default: >0.01;  uncertainty: w/o rejection

//=============================================================================
  fCutMaxCascadeChi2 = 33.;
  fCutMinCascadeRadius = 0.1;  // default: >0.5; uncertainty: >0.3, 0.4, 0.6, 0.7;
  fCutMaxCascadeRadius = 100.;  // default: not applied in pp
  fCutMaxDauV0Chi2 = 33.;
  fCutMinDauV0Radius = 0.1;  // default: >0.5; uncertainty: >0.3, 0.4, 0.6, 0.7;
  fCutMaxDauV0Radius = 200.;  // default: not applied in pp
//=============================================================================

  fCutMaxDauLaCtau = 200.;  // default: not applied in pp
//=============================================================================

  fCutMaxV0DausDCA = 2.5;
  fCutMaxV0BachDCA   = 2.5;
  fCutMinPosV0DausDCAtoPV = 0.01;
  fCutMinNegV0DausDCAtoPV = 0.01;
  fCutMinDauV0DCAtoPV   = 0.01;
  fCutMinBachDCAtoPV = 0.01;
  fCutMinCascadeCosPA     = 0.9;
  fCutMinDauV0CosPA    = 0.9;  // default: >0.97;  uncertainty: >0.95, 0.96, 0.98, 0.99
//=============================================================================

  fCutMinXiDeletaM = -1.;
  fCutMinOmegaDeletaM = -1.;
  fCutMinDauLaDeletaM = -1.;
//=============================================================================
  fCutMaxCascadeSigmaTPC  = 7.;   // default: <5;     uncertainty: w/o cut

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::InitParamsPA()
{
//
//  AliAnalysisTaskSEStrangeMaker::InitParametersPA
//

  InitParamsPP();

  fRapidityShift = 0.465;

  fCutMaxLambdaSigmaTPC = 6;  // default: <5; uncertaity: <4, 6
  fCutMaxCascadeSigmaTPC  = 6.;   // default: <5;     uncertainty: w/o cut

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::InitParamsAP()
{
//
//  AliAnalysisTaskSEStrangeMaker::InitParametersAP
//

  InitParamsPP();

  fRapidityShift = -0.465;

  fCutMaxLambdaSigmaTPC = 6;  // default: <5; uncertaity: <4, 6

  return;
}

//_____________________________________________________________________________
void AliAnalysisTaskSEStrangeMaker::InitParamsAA()
{
//
//  AliAnalysisTaskSEStrangeMaker::InitParametersAA
//

  InitParamsPP();

  fCutMinV0Radius = 0.9;  // default: 5; uncertainty: varying around
  fCutMaxV0Radius = 100.;

//fCutMinDauPt      = 0.16;  // default: 0.16
  fCutMinDauDCAtoPV = 0.08;  // default: 0.1; uncertainty: 0.08, 0.12

  fCutMaxKshortSigmaTPC = 6;      // default: <5;     uncertainty: <4, 6;
  fCutMinKshortCosPA    = 0.997;  // default: >0.998; uncertainty: 0.997, 0.999
  fCutMaxKshortArmFrac  = 0.2;    // default: <0.2

  fCutMaxLambdaSigmaTPC = 6;      // default: <5;     uncertaity: <4, 6
  fCutMinLambdaCosPA    = 0.997;  // default: >0.998; uncertainty: 0.997, 0.999
  fCutMinLambdaDeletaM  = 0.008;  // default: >0.01;  uncertainty: 0.008, 0.012

  return;
}
