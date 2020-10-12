#include <TMath.h>
#include <TLorentzVector.h>

#include "AliPicoV0MC.h"
#include "AliPicoCascadeMC.h"

ClassImp(AliPicoCascadeMC)

//_____________________________________________________________________________
AliPicoCascadeMC::AliPicoCascadeMC() :
AliPicoCascade(),
fXiPDG(0),
fXiStatus(0),
fXiKine()
{
//
//  AliPicoCascadeMC::AliPicoCascadeMC
//
}
AliPicoCascadeMC::AliPicoCascadeMC(UInt_t wMask,
                                   AliPicoV0MC *pV0,
                                   Double_t dXiRadius,
                                   Double_t dXiCosPA,
                                   Double_t dXiDistToPVoverP,
                                   Double_t dXiDCAtoPV,
                                   Double_t dV0DCAtoPV,
                                   Double_t dV0toBachDCA,
                                   Double_t dBachDCAtoPV,
                                   Float_t  dBachXrowsTPC,
                                   Double_t dBachXrowsOverFindableClusTPC,
                                   Double_t dBachPx, Double_t dBachPy, Double_t dBachPz,
                                   Int_t idV, UInt_t wsV,
                                   Double_t dXiPx,  Double_t dXiPy, Double_t dXiPz, Double_t dXiE) :
AliPicoCascade(wMask,
               nullptr,
               pV0,
               dXiRadius,
               dXiCosPA,
               dXiDistToPVoverP,
               dXiDCAtoPV,
               dV0DCAtoPV,
               dV0toBachDCA,
               dBachDCAtoPV,
               dBachXrowsTPC,
               dBachXrowsOverFindableClusTPC,
               dBachPx, dBachPy, dBachPz),
fXiPDG(idV),
fXiStatus(wsV),
fXiKine(dXiPx,dXiPy,dXiPz,dXiE)
{
//
//  AliPicoCascadeMC::AliPicoCascadeMC
//
}

//_____________________________________________________________________________
AliPicoCascadeMC::AliPicoCascadeMC(const AliPicoCascadeMC &src) :
AliPicoCascade(src),
fXiPDG(src.fXiPDG),
fXiStatus(src.fXiStatus),
fXiKine(src.fXiKine)
{
//
//  AliPicoCascadeMC::AliPicoCascadeMC
//
}

//_____________________________________________________________________________
AliPicoCascadeMC& AliPicoCascadeMC::operator=(const AliPicoCascadeMC &src)
{
//
//  AliPicoCascadeMC::operator=
//

  if (&src==this) return *this;

  AliPicoCascade::operator=(src);

  fXiPDG    = src.fXiPDG;
  fXiStatus = src.fXiStatus;
  fXiKine    = src.fXiKine;

  return *this;
}

//_____________________________________________________________________________
AliPicoCascadeMC::~AliPicoCascadeMC()
{
//
//  AliPicoCascadeMC::~AliPicoCascadeMC
//
}

//_____________________________________________________________________________
Bool_t AliPicoCascadeMC::IsXiNeg(Double_t const d[21]) const
{
//
//  Bool_t AliPicoCascadeMC::IsXiNeg(Double_t const d[21]) const
//

  if (!AliPicoCascade::IsXiNeg()) return kFALSE;
  if (!d) return kTRUE;
//=============================================================================

  if (!fV0MC) return kFALSE;
  if (!fV0MC->IsLambda(d)) return kFALSE;


  if (d[10]>0.) {
    if (TMath::Abs(fV0MC->KineLambda().M()-AliPicoBase::MassLambda())>d[10]) return kFALSE;
  }
//=============================================================================

  if (!IsXi(d[11],d[12],d[13],d[14],d[15],d[16],d[17],d[18],d[19], d[20])) return kFALSE;
//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliPicoCascadeMC::IsXiPos(Double_t const d[21]) const
{
//
//  Bool_t AliPicoCascadeMC::IsXiPos(Double_t const d[21]) const
//

  if (!AliPicoCascade::IsXiPos()) return kFALSE;
  if (!d) return kTRUE;
//=============================================================================

  if (!fV0MC) return kFALSE;
  if (!fV0MC->IsAntiLa(d)) return kFALSE;


  if (d[10]>0.) {
    if (TMath::Abs(fV0MC->KineAntiLa().M()-AliPicoBase::MassLambda())>d[10]) return kFALSE;
  }
//=============================================================================

  if (!IsXi(d[11],d[12],d[13],d[14],d[15],d[16],d[17],d[18],d[19], d[20])) return kFALSE;
//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliPicoCascadeMC::IsOmegaNeg(Double_t const d[21]) const
{
//
//  Bool_t AliPicoCascadeMC::IsOmegaNeg(Double_t const d[21]) const
//

  if (!AliPicoCascade::IsOmegaNeg()) return kFALSE;
  if (!d) return kTRUE;
//=============================================================================

  if (!fV0MC) return kFALSE;
  if (!fV0MC->IsLambda(d)) return kFALSE;


  if (d[10]>0.) {
    if (TMath::Abs(fV0MC->KineLambda().M()-AliPicoBase::MassLambda())>d[10]) return kFALSE;
  }
//=============================================================================

  if (!IsOmega(d[11],d[12],d[13],d[14],d[15],d[16],d[17],d[18],d[19], d[20])) return kFALSE;
//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliPicoCascadeMC::IsOmegaPos(Double_t const d[21]) const
{
//
//  Bool_t AliPicoCascadeMC::IsOmegaPos(Double_t const d[21]) const
//

  if (!AliPicoCascade::IsOmegaPos()) return kFALSE;
  if (!d) return kTRUE;
//=============================================================================

  if (!fV0MC) return kFALSE;
  if (!fV0MC->IsAntiLa(d)) return kFALSE;


  if (d[10]>0.) {
    if (TMath::Abs(fV0MC->KineAntiLa().M()-AliPicoBase::MassLambda())>d[10]) return kFALSE;
  }
//=============================================================================

  if (!IsOmega(d[11],d[12],d[13],d[14],d[15],d[16],d[17],d[18],d[19], d[20])) return kFALSE;
//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliPicoCascadeMC::IsXiInRapAcc(Double_t dMin, Double_t dMax)
{
//
//  Bool_t AliPicoCascadeMC::IsXiInRapAcc(Double_t dMin, Double_t dMax)
//

  const auto d(fXiKine.Rapidity());
  return ((d>=dMin) && (d<dMax));
}

//_____________________________________________________________________________
void AliPicoCascadeMC::GetControlVariables(Float_t d[28]) const
{
//
//  AliPicoCascadeMC::GetControlVariables
//

  if (fV0MC) fV0MC->GetControlVariables(d);

  d[18] = (Float_t)fXiRadius;
  d[19] = (Float_t)fXiCosPA;
  d[20] = (Float_t)fXiDCAtoPV;
  d[21] = (Float_t)fV0DCAtoPV;
  d[22] = (Float_t)fV0toBachDCA;
  d[23] = (Float_t)fBachDCAtoPV;
  d[24] = (Float_t)fBachXrowsTPC;
  d[25] = (Float_t)fBachXrowsOverFindableClusTPC;
  d[26] = (Float_t)KineV0().Eta();
  d[27] = (Float_t)fBachP3.Eta();

  return;
}
