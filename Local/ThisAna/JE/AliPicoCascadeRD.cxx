#include <TMath.h>
#include <TLorentzVector.h>

#include "AliPicoV0RD.h"
#include "AliPicoCascadeRD.h"

ClassImp(AliPicoCascadeRD)

//_____________________________________________________________________________
AliPicoCascadeRD::AliPicoCascadeRD() :
AliPicoCascade(),
fBachPionSigmaTPC(),
fBachKaonSigmaTPC()
{
//
//  AliPicoCascadeRD::AliPicoCascadeRD
//
}
AliPicoCascadeRD::AliPicoCascadeRD(UInt_t wMask,
                                   AliPicoV0RD *pV0,
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
                                   Float_t dBachPionSigmaTPC, Float_t dBachKaonSigmaTPC) :
AliPicoCascade(wMask,
               pV0,
               nullptr,
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
fBachPionSigmaTPC(dBachPionSigmaTPC),
fBachKaonSigmaTPC(dBachKaonSigmaTPC)
{
//
//  AliPicoCascadeRD::AliPicoCascadeRD
//
}

//_____________________________________________________________________________
AliPicoCascadeRD::AliPicoCascadeRD(const AliPicoCascadeRD &src) :
AliPicoCascade(src),
fBachPionSigmaTPC(src.fBachPionSigmaTPC),
fBachKaonSigmaTPC(src.fBachKaonSigmaTPC)
{
//
//  AliPicoCascadeRD::AliPicoCascadeRD
//
}

//_____________________________________________________________________________
AliPicoCascadeRD& AliPicoCascadeRD::operator=(const AliPicoCascadeRD &src)
{
//
//  AliPicoCascadeRD::operator=
//

  if (&src==this) return *this;

  AliPicoCascade::operator=(src);

  fBachPionSigmaTPC = src.fBachPionSigmaTPC;
  fBachKaonSigmaTPC = src.fBachKaonSigmaTPC;

  return *this;
}

//_____________________________________________________________________________
AliPicoCascadeRD::~AliPicoCascadeRD()
{
//
//  AliPicoCascadeRD::~AliPicoCascadeRD
//
}

//_____________________________________________________________________________
Bool_t AliPicoCascadeRD::IsXiNeg(Double_t const d[21]) const
{
//
//  Bool_t AliPicoCascadeRD::IsXiNeg(Double_t const d[21]) const
//

  if (!AliPicoCascade::IsXiNeg()) return kFALSE;
  if (!d) return kTRUE;
//=============================================================================

  if (!fV0RD) return kFALSE;
  if (!fV0RD->IsLambda(d)) return kFALSE;

  if (d[9]>0.) {
    if (TMath::Abs(fBachPionSigmaTPC)>d[9]) return kFALSE;
  }

  if (d[10]>0.) {
    if (TMath::Abs(fV0RD->KineLambda().M()-AliPicoBase::MassLambda())>d[10]) return kFALSE;
  }
//=============================================================================

  if (!IsXi(d[11],d[12],d[13],d[14],d[15],d[16],d[17],d[18],d[19], d[20])) return kFALSE;
//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliPicoCascadeRD::IsXiPos(Double_t const d[21]) const
{
//
//  Bool_t AliPicoCascadeRD::IsXiPos(Double_t const d[21]) const
//

  if (!AliPicoCascade::IsXiPos()) return kFALSE;
  if (!d) return kTRUE;
//=============================================================================

  if (!fV0RD) return kFALSE;
  if (!fV0RD->IsAntiLa(d)) return kFALSE;

  if (d[9]>0.) {
    if (TMath::Abs(fBachPionSigmaTPC)>d[9]) return kFALSE;
  }

  if (d[10]>0.) {
    if (TMath::Abs(fV0RD->KineAntiLa().M()-AliPicoBase::MassLambda())>d[10]) return kFALSE;
  }
//=============================================================================

  if (!IsXi(d[11],d[12],d[13],d[14],d[15],d[16],d[17],d[18],d[19], d[20])) return kFALSE;
//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliPicoCascadeRD::IsOmegaNeg(Double_t const d[21]) const
{
//
//  Bool_t AliPicoCascadeRD::IsOmegaNeg(Double_t const d[21]) const
//

  if (!AliPicoCascade::IsOmegaNeg()) return kFALSE;
  if (!d) return kTRUE;
//=============================================================================

  if (!fV0RD) return kFALSE;
  if (!fV0RD->IsLambda(d)) return kFALSE;

  if (d[9]>0.) {
    if (TMath::Abs(fBachKaonSigmaTPC)>d[9]) return kFALSE;
  }

  if (d[10]>0.) {
    if (TMath::Abs(fV0RD->KineLambda().M()-AliPicoBase::MassLambda())>d[10]) return kFALSE;
  }
//=============================================================================

  if (!IsOmega(d[11],d[12],d[13],d[14],d[15],d[16],d[17],d[18],d[19], d[20])) return kFALSE;
//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliPicoCascadeRD::IsOmegaPos(Double_t const d[21]) const
{
//
//  Bool_t AliPicoCascadeRD::IsXiPos(Double_t const d[21]) const
//

  if (!AliPicoCascade::IsOmegaPos()) return kFALSE;
  if (!d) return kTRUE;
//=============================================================================

  if (!fV0RD) return kFALSE;
  if (!fV0RD->IsAntiLa(d)) return kFALSE;

  if (d[9]>0.) {
    if (TMath::Abs(fBachKaonSigmaTPC)>d[9]) return kFALSE;
  }

  if (d[10]>0.) {
    if (TMath::Abs(fV0RD->KineAntiLa().M()-AliPicoBase::MassLambda())>d[10]) return kFALSE;
  }
//=============================================================================

  if (!IsOmega(d[11],d[12],d[13],d[14],d[15],d[16],d[17],d[18],d[19], d[20])) return kFALSE;
//=============================================================================

  return kTRUE;
}

//_____________________________________________________________________________
void AliPicoCascadeRD::GetControlVariables(Float_t d[31]) const
{
//
//  AliPicoCascadeRD::GetControlVariables
//

  if (fV0RD) fV0RD->GetControlVariables(d);

  d[20] = (Float_t)fXiRadius;
  d[21] = (Float_t)fXiCosPA;
  d[22] = (Float_t)fXiDCAtoPV;
  d[23] = (Float_t)fV0DCAtoPV;
  d[24] = (Float_t)fV0toBachDCA;
  d[25] = (Float_t)fBachDCAtoPV;
  d[26] = (Float_t)fBachXrowsTPC;
  d[27] = (Float_t)fBachXrowsOverFindableClusTPC;
  d[28] = (Float_t)fBachP3.Eta();
  d[29] = (Float_t)fBachPionSigmaTPC;
  d[30] = (Float_t)fBachKaonSigmaTPC;

  return;
}
