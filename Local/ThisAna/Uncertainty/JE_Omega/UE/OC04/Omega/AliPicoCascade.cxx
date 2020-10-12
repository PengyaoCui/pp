#include <TH2D.h>
#include <TMath.h>
#include <TLorentzVector.h>

#include "AliPicoV0RD.h"
#include "AliPicoV0MC.h"
#include "AliPicoCascade.h"

ClassImp(AliPicoCascade)

//_____________________________________________________________________________
AliPicoCascade::AliPicoCascade() :
TObject(),
fMask(0),
fV0RD(nullptr),
fV0MC(nullptr),
fXiRadius(0.),
fXiCosPA(0.),
fXiDistToPVoverP(0.),
fXiDCAtoPV(0.),
fV0DCAtoPV(0.),
fV0toBachDCA(0.),
fBachDCAtoPV(0.),
fBachXrowsTPC(0.),
fBachXrowsOverFindableClusTPC(0.),
fBachP3()
{
//
//  AliPicoCascade::AliPicoCascade
//
}

AliPicoCascade::AliPicoCascade(UInt_t wMask,
                               AliPicoV0RD *pV0RD,
                               AliPicoV0MC *pV0MC,
                               Double_t dXiRadius,
                               Double_t dXiCosPA,
                               Double_t dXiDistToPVoverP,
                               Double_t dXiDCAtoPV,
                               Double_t dV0DCAtoPV,
                               Double_t dV0toBachDCA,
                               Double_t dBachDCAtoPV,
                               Float_t  dBachXrowsTPC,
                               Double_t dBachXrowsOverFindableClusTPC,
                               Double_t dBachPx, Double_t dBachPy, Double_t dBachPz) :
TObject(),
fMask(wMask),
fV0RD(pV0RD ? new AliPicoV0RD(*pV0RD) : nullptr),
fV0MC(pV0MC ? new AliPicoV0MC(*pV0MC) : nullptr),
fXiRadius(dXiRadius),
fXiCosPA(dXiCosPA),
fXiDistToPVoverP(dXiDistToPVoverP),
fXiDCAtoPV(dXiDCAtoPV),
fV0DCAtoPV(dV0DCAtoPV),
fV0toBachDCA(dV0toBachDCA),
fBachDCAtoPV(dBachDCAtoPV),
fBachXrowsTPC(dBachXrowsTPC),
fBachXrowsOverFindableClusTPC(dBachXrowsOverFindableClusTPC),
fBachP3(dBachPx, dBachPy, dBachPz)
{
//
//  AliPicoCascade::AliPicoCascade
//
}

//_____________________________________________________________________________
AliPicoCascade::AliPicoCascade(const AliPicoCascade &src) :
TObject(src),
fMask(src.fMask),
fV0RD(src.fV0RD ? new AliPicoV0RD(*src.fV0RD) : nullptr),
fV0MC(src.fV0MC ? new AliPicoV0MC(*src.fV0MC) : nullptr),
fXiRadius(src.fXiRadius),
fXiCosPA(src.fXiCosPA),
fXiDistToPVoverP(src.fXiDistToPVoverP),
fXiDCAtoPV(src.fXiDCAtoPV),
fV0DCAtoPV(src.fV0DCAtoPV),
fV0toBachDCA(src.fV0toBachDCA),
fBachDCAtoPV(src.fBachDCAtoPV),
fBachXrowsTPC(src.fBachXrowsTPC),
fBachXrowsOverFindableClusTPC(src.fBachXrowsOverFindableClusTPC),
fBachP3(src.fBachP3)
{
//
//  AliPicoCascade::AliPicoCascade
//
}

//_____________________________________________________________________________
AliPicoCascade& AliPicoCascade::operator=(const AliPicoCascade &src)
{
//
//  AliPicoCascade::operator=
//

  if (&src==this) return *this;

  TObject::operator=(src);

  fMask = src.fMask;

  fV0RD = (src.fV0RD ? new AliPicoV0RD(*src.fV0RD) : nullptr);
  fV0MC = (src.fV0MC ? new AliPicoV0MC(*src.fV0MC) : nullptr);

  fXiRadius  = src.fXiRadius;
  fXiCosPA   = src.fXiCosPA;
  fXiDistToPVoverP  = src.fXiDistToPVoverP;
  fXiDCAtoPV = src.fXiDCAtoPV;

  fV0DCAtoPV    = src.fV0DCAtoPV;
  fV0toBachDCA  = src.fV0toBachDCA;

  fBachDCAtoPV                  = src.fBachDCAtoPV;
  fBachXrowsTPC                 = src.fBachXrowsTPC;
  fBachXrowsOverFindableClusTPC = src.fBachXrowsOverFindableClusTPC;
  fBachP3                       = src.fBachP3;

  return *this;
}

//_____________________________________________________________________________
AliPicoCascade::~AliPicoCascade()
{
//
//  AliPicoCascade::~AliPicoCascade
//
  if (fV0RD) { delete fV0RD; fV0RD = nullptr; }
  if (fV0MC) { delete fV0MC; fV0MC = nullptr; }
}


//_____________________________________________________________________________
Bool_t AliPicoCascade::IsXi(Double_t dCutMinXiRadius,
                            Double_t dCutMinXiCosPA,
                            Double_t dCutMaxXiCtau, 
			    Double_t dCutMaxXiDCAtoPV,
                            Double_t dCutMinV0DCAtoPV,
                            Double_t dCutMaxV0toBachDCA,
                            Double_t dCutMinBachDCAtoPV,
                            Float_t  dCutMinBachXrowsTPC,
                            Double_t dCutMinBachXrowsOverFindableClusTPC,
                            Double_t dCutMinCompeteMass) const
{
//
//AliPicoCascade::IsXi
//

if(!IsCandidateSelected(dCutMinXiRadius,
			dCutMinXiCosPA,
			dCutMaxXiDCAtoPV,
			dCutMinV0DCAtoPV,
			dCutMaxV0toBachDCA,
			dCutMinBachDCAtoPV,
			dCutMinBachXrowsTPC,
			dCutMinBachXrowsOverFindableClusTPC)) return kFALSE;

if(!IsXiSelected(dCutMaxXiCtau, dCutMinCompeteMass)) return kFALSE;

return kTRUE;

}

//_____________________________________________________________________________
Bool_t AliPicoCascade::IsOmega(Double_t dCutMinXiRadius,
                               Double_t dCutMinXiCosPA,
                               Double_t dCutMaxXiCtau, 
			       Double_t dCutMaxXiDCAtoPV,
                               Double_t dCutMinV0DCAtoPV,
                               Double_t dCutMaxV0toBachDCA,
                               Double_t dCutMinBachDCAtoPV,
                               Float_t  dCutMinBachXrowsTPC,
                               Double_t dCutMinBachXrowsOverFindableClusTPC,
                               Double_t dCutMinCompeteMass) const
{
//
//AliPicoCascade::IsOmega
//

if(!IsCandidateSelected(dCutMinXiRadius,
			dCutMinXiCosPA,
			dCutMaxXiDCAtoPV,
			dCutMinV0DCAtoPV,
			dCutMaxV0toBachDCA,
			dCutMinBachDCAtoPV,
			dCutMinBachXrowsTPC,
			dCutMinBachXrowsOverFindableClusTPC)) return kFALSE;

if(!IsOmegaSelected(dCutMaxXiCtau, dCutMinCompeteMass)) return kFALSE;

return kTRUE;

}

//_____________________________________________________________________________
Bool_t AliPicoCascade::IsXiSelected(Double_t dCutMaxXiCtau, Double_t dCutMinCompeteMass) const
{
//
//AliPicoCascade::IsXiSelected
//
if ((fXiDistToPVoverP*AliPicoBaseDev::MassXi())>dCutMaxXiCtau) return kFALSE;

  if (dCutMinCompeteMass>0.) {
    const auto d(KineOmega().M());
    if (TMath::Abs(d-AliPicoBaseDev::MassOmega())<dCutMinCompeteMass) return kFALSE;
  }

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliPicoCascade::IsOmegaSelected(Double_t dCutMaxXiCtau, Double_t dCutMinCompeteMass) const
{
//
//AliPicoCascade::IsOmegaSelected
//
if ((fXiDistToPVoverP*AliPicoBaseDev::MassOmega())>dCutMaxXiCtau) return kFALSE;

  if (dCutMinCompeteMass>0.) {
    const auto d(KineXi().M());
    if (TMath::Abs(d-AliPicoBaseDev::MassXi())<dCutMinCompeteMass) return kFALSE;
  }

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t AliPicoCascade::IsCandidateSelected(Double_t dCutMinXiRadius,
                                           Double_t dCutMinXiCosPA,
                                           Double_t dCutMaxXiDCAtoPV,
                                           Double_t dCutMinV0DCAtoPV,
                                           Double_t dCutMaxV0toBachDCA,
                                           Double_t dCutMinBachDCAtoPV,
                                           Float_t  dCutMinBachXrowsTPC,
                                           Double_t dCutMinBachXrowsOverFindableClusTPC) const
{
//
//  AliPicoCascade::IsCandidateSelected
//

  if (fXiRadius < dCutMinXiRadius) return kFALSE;
  if (fXiCosPA  < dCutMinXiCosPA)  return kFALSE;

  if ((dCutMaxXiDCAtoPV>0.) && (fXiDCAtoPV>dCutMaxXiDCAtoPV)) return kFALSE;

  if (fV0DCAtoPV   < dCutMinV0DCAtoPV)   return kFALSE;
  if (fV0toBachDCA > dCutMaxV0toBachDCA) return kFALSE;
  if (fBachDCAtoPV < dCutMinBachDCAtoPV) return kFALSE;

  if (fBachXrowsTPC<dCutMinBachXrowsTPC) return kFALSE;
  if (fBachXrowsOverFindableClusTPC<dCutMinBachXrowsOverFindableClusTPC) return kFALSE;

  //if (dCutMinCompeteMass>0.) {
  //  const auto d(KineOmega().M());
  //  if (TMath::Abs(d-AliPicoBaseDev::MassOmega())<dCutMinCompeteMass) return kFALSE;
  //}

  return kTRUE;
}

//_____________________________________________________________________________
void AliPicoCascade::FillXiNegPtInvM(TH2D* const h, Double_t const *dCuts) const
{
//
//  void AliPicoCascade::FillXiNegPtInvM(TH2D* const h, Double_t const *dCuts) const
//

  if (!h) return;
  if (!IsXiNeg(dCuts)) return;
//=============================================================================

  const auto v(KineXi());
  const auto d(v.Pt());
  if (d<h->GetXaxis()->GetBinLowEdge(1)) return;
//=============================================================================

  h->Fill(d, v.M());
  return;
}

//_____________________________________________________________________________
void AliPicoCascade::FillXiPosPtInvM(TH2D* const h, Double_t const *dCuts) const
{
//
//  void AliPicoCascade::FillXiPosPtInvM(TH2D* const h, Double_t const *dCuts) const
//

  if (!h) return;
  if (!IsXiPos(dCuts)) return;
//=============================================================================

  const auto v(KineXi());
  const auto d(v.Pt());
  if (d<h->GetXaxis()->GetBinLowEdge(1)) return;
//=============================================================================

  h->Fill(d, v.M());
  return;
}

//_____________________________________________________________________________
void AliPicoCascade::FillXiPtInvM(TH2D* const h, Double_t const *dCuts) const
{
//
//  void AliPicoCascade::FillXiPtInvM(TH2D* const h, Double_t const *dCuts) const
//

  if (!h) return;
  if (!(IsXiNeg(dCuts) || IsXiPos(dCuts))) return;
//=============================================================================

  const auto v(KineXi());
  const auto d(v.Pt());
  if (d<h->GetXaxis()->GetBinLowEdge(1)) return;
//=============================================================================

  h->Fill(d, v.M());
  return;
}

//_____________________________________________________________________________
void AliPicoCascade::FillOmegaNegPtInvM(TH2D* const h, Double_t const *dCuts) const
{
//
//  void AliPicoCascade::FillOmegaNegPtInvM(TH2D* const h, Double_t const *dCuts) const
//

  if (!h) return;
  if (!IsOmegaNeg(dCuts)) return;
//=============================================================================

  const auto v(KineOmega());
  const auto d(v.Pt());
  if (d<h->GetXaxis()->GetBinLowEdge(1)) return;
//=============================================================================

  h->Fill(d, v.M());
  return;
}

//_____________________________________________________________________________
void AliPicoCascade::FillOmegaPosPtInvM(TH2D* const h, Double_t const *dCuts) const
{
//
//  void AliPicoCascade::FillOmegaPosPtInvM(TH2D* const h, Double_t const *dCuts) const
//

  if (!h) return;
  if (!IsOmegaPos(dCuts)) return;
//=============================================================================

  const auto v(KineOmega());
  const auto d(v.Pt());
  if (d<h->GetXaxis()->GetBinLowEdge(1)) return;
//=============================================================================

  h->Fill(d, v.M());
  return;
}

//_____________________________________________________________________________
void AliPicoCascade::FillOmegaPtInvM(TH2D* const h, Double_t const *dCuts) const
{
//
//  void AliPicoCascade::FillOmegaNegPtInvM(TH2D* const h, Double_t const *dCuts) const
//

  if (!h) return;
  if (!(IsOmegaNeg(dCuts) || IsOmegaNeg(dCuts))) return;
//=============================================================================

  const auto v(KineOmega());
  const auto d(v.Pt());
  if (d<h->GetXaxis()->GetBinLowEdge(1)) return;
//=============================================================================

  h->Fill(d, v.M());
  return;
}

//_____________________________________________________________________________
Bool_t AliPicoCascade::IsXiInRapAcc(Double_t dMin, Double_t dMax)
{
//
//  Bool_t AliPicoCascade::IsXiInRapAcc(Double_t dMin, Double_t dMax)
//

  const auto d(RapidityXi());
  return ((d>=dMin) && (d<dMax));
}

//_____________________________________________________________________________
Bool_t AliPicoCascade::IsOmegaInRapAcc(Double_t dMin, Double_t dMax)
{
//
//  Bool_t AliPicoCascade::IsOmegaInRapAcc(Double_t dMin, Double_t dMax)
//

  const auto d(RapidityOmega());
  return ((d>=dMin) && (d<dMax));
}

//_____________________________________________________________________________
Bool_t AliPicoCascade::IsCascadeInEtaAcc(Double_t dMin, Double_t dMax)
{
//
//  Bool_t AliPicoCascade::IsCascadeInEtaAcc(Double_t dMin, Double_t dMax)
//

  const auto d(KineRD().Eta());
  return ((d>=dMin) && (d<dMax));
}

//_____________________________________________________________________________
Bool_t AliPicoCascade::IsBachInEtaAcc(Double_t dMin, Double_t dMax)
{
//
//  Bool_t AliPicoCascade::IsBachInEtaAcc(Double_t dMin, Double_t dMax)
//

  const auto d(fBachP3.Eta());
  return ((d>=dMin) && (d<dMax));
}

//_____________________________________________________________________________
const Double_t AliPicoCascade::RapidityXi() const
{
//
//  const Double_t AliPicoCascade::RapidityXi() const
//

  TLorentzVector v;
  v.SetVectM(KineRD(), AliPicoBaseDev::MassXi());

  return v.Rapidity();
}

//_____________________________________________________________________________
const Double_t AliPicoCascade::RapidityOmega() const
{
//
//  const Double_t AliPicoCascade::RapidityOmega() const
//

  TLorentzVector v;
  v.SetVectM(KineRD(), AliPicoBaseDev::MassOmega());

  return v.Rapidity();
}

//_____________________________________________________________________________
const TLorentzVector AliPicoCascade::KineXi() const
{
//
//  const TLorentzVector AliPicoCascade::KineXi() const
//

  TLorentzVector vt;
  vt.SetVectM(fBachP3, AliPicoBaseDev::MassPion());

  TLorentzVector vv;
  vv.SetVectM(KineV0(), AliPicoBaseDev::MassLambda());
//=============================================================================

  return (vt + vv);
}

//_____________________________________________________________________________
const TLorentzVector AliPicoCascade::KineOmega() const
{
//
//  const TLorentzVector AliPicoCascade::KineOmega() const
//

  TLorentzVector vt;
  vt.SetVectM(fBachP3, AliPicoBaseDev::MassKaon());

  TLorentzVector vv;
  vv.SetVectM(KineV0(), AliPicoBaseDev::MassLambda());
//=============================================================================

  return (vt + vv);
}

//_____________________________________________________________________________
const TVector3 AliPicoCascade::KineV0() const
{
//
//  const TVector3 AliPicoCascade::KineV0() const
//

  auto pV0(GetV0());
  if (!pV0) {
    ::Error("AliPicoCascade::KineV0", "V0 is not set!!!");
    return fBachP3;
  }
//=============================================================================

  return (pV0->KineRD());
}

//_____________________________________________________________________________
const AliPicoV0 *AliPicoCascade::GetV0() const
{
//
//  const AliPicoV0 *AliPicoCascade::GetV0()
//

  if (fV0RD) return static_cast<AliPicoV0*>(fV0RD);
  if (fV0MC) return static_cast<AliPicoV0*>(fV0MC);

  return nullptr;
}
