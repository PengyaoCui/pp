#ifndef ALIPICOCASCADE_H
#define ALIPICOCASCADE_H

#include "TObject.h"
#include "AliPicoBaseDev.h"

class AliPicoV0;
class AliPicoV0RD;
class AliPicoV0MC;

class AliPicoCascade : public TObject {

 public :

  //AliPicoCascade() = default;
  AliPicoCascade();
  AliPicoCascade(UInt_t wMask,
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
                 Double_t dBachPx, Double_t dBachPy, Double_t dBachPz);
  AliPicoCascade(const AliPicoCascade &src);
  AliPicoCascade& operator=(const AliPicoCascade &src);
  virtual ~AliPicoCascade();
//=============================================================================

  const AliPicoV0 *GetV0()   const;
  const TVector3  KineV0()   const;
  const TVector3  KineRD()   const { return (fBachP3 + KineV0()); }
  const TVector3 &KineBach() const { return fBachP3; }

  const TLorentzVector KineXi() const;
  const TLorentzVector KineOmega() const;

  const Double_t RapidityXi() const;
  const Double_t RapidityOmega() const;
//=============================================================================

  virtual Bool_t IsXiNeg(Double_t const */*dCuts*/=nullptr) const {
    return ((fMask & AliPicoBaseDev::kXiNeg) == AliPicoBaseDev::kXiNeg);
  }

  virtual Bool_t IsXiPos(Double_t const */*dCuts*/=nullptr) const {
    return ((fMask & AliPicoBaseDev::kXiPos) == AliPicoBaseDev::kXiPos);
  }

  virtual Bool_t IsOmegaNeg(Double_t const */*dCuts*/=nullptr) const {
    return ((fMask & AliPicoBaseDev::kOmegaNeg) == AliPicoBaseDev::kOmegaNeg);
  }

  virtual Bool_t IsOmegaPos(Double_t const */*dCuts*/=nullptr) const {
    return ((fMask & AliPicoBaseDev::kOmegaPos) == AliPicoBaseDev::kOmegaPos);
  }

  Bool_t IsXiInRapAcc(Double_t dMin, Double_t dMax);
  Bool_t IsOmegaInRapAcc(Double_t dMin, Double_t dMax);

  Bool_t IsCascadeInEtaAcc(Double_t dMin, Double_t dMax);
  Bool_t IsBachInEtaAcc(Double_t dMin, Double_t dMax);

  virtual void GetControlVariables(Float_t */*d*/=nullptr) const = 0;
//=============================================================================

  void FillXiNegPtInvM(TH2D* const h, Double_t const *dCuts=nullptr) const;
  void FillXiPosPtInvM(TH2D* const h, Double_t const *dCuts=nullptr) const;
  void FillXiPtInvM(TH2D* const h, Double_t const *dCuts=nullptr) const;

  void FillOmegaNegPtInvM(TH2D* const h, Double_t const *dCuts=nullptr) const;
  void FillOmegaPosPtInvM(TH2D* const h, Double_t const *dCuts=nullptr) const;
  void FillOmegaPtInvM(TH2D* const h, Double_t const *dCuts=nullptr) const;
//=============================================================================

 protected :

  Bool_t IsCandidateSelected(Double_t dCutMinXiRadius,
                             Double_t dCutMinXiCosPA,
                             Double_t dCutMaxXiDCAtoPV,
                             Double_t dCutMinV0DCAtoPV,
                             Double_t dCutMaxV0toBachDCA,
                             Double_t dCutMinBachDCAtoPV,
                             Float_t  dCutMinBachXrowsTPC,
                             Double_t dCutMinBachXrowsOverFindableClusTPC) const;

  Bool_t IsXi(Double_t dCutMinXiRadius,
              Double_t dCutMinXiCosPA,
              Double_t dCutMaxXiCtau,
              Double_t dCutMaxXiDCAtoPV,
              Double_t dCutMinV0DCAtoPV,
              Double_t dCutMaxV0toBachDCA,
              Double_t dCutMinBachDCAtoPV,
              Float_t  dCutMinBachXrowsTPC,
              Double_t dCutMinBachXrowsOverFindableClusTPC,
              Double_t dCutMinCompeteMass) const;

  Bool_t IsOmega(Double_t dCutMinXiRadius,
                 Double_t dCutMinXiCosPA,
                 Double_t dCutMaxXiCtau,
		 Double_t dCutMaxXiDCAtoPV,
                 Double_t dCutMinV0DCAtoPV,
                 Double_t dCutMaxV0toBachDCA,
                 Double_t dCutMinBachDCAtoPV,
                 Float_t  dCutMinBachXrowsTPC,
                 Double_t dCutMinBachXrowsOverFindableClusTPC,
                 Double_t dCutMinCompeteMass) const;

  Bool_t IsXiSelected (Double_t dCutMaxXiCtau, Double_t dCutMinCompeteMass) const;
  Bool_t IsOmegaSelected (Double_t dCutMaxXiCtau, Double_t dCutMinCompeteMass) const;

//=============================================================================

  UInt_t fMask = 0;  //

  AliPicoV0RD *fV0RD = nullptr; //
  AliPicoV0MC *fV0MC = nullptr; //

  Double_t fXiRadius  = 0.;  //
  Double_t fXiCosPA   = 0.;  //
  Double_t fXiDistToPVoverP  = 0.;  //
  Double_t fXiDCAtoPV = 0.; //

  Double_t fV0DCAtoPV   = 0.; //
  Double_t fV0toBachDCA = 0.; //

  Double_t fBachDCAtoPV  = 0.; //
  Float_t  fBachXrowsTPC = 0.; //
  Double_t fBachXrowsOverFindableClusTPC = 0.; //
  TVector3 fBachP3; //

  ClassDef(AliPicoCascade, 3);
};

#endif
