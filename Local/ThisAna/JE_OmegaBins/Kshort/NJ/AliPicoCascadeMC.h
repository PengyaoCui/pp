#ifndef ALIPICOCASCADEMC_H
#define ALIPICOCASCADEMC_H

#include "AliPicoCascade.h"

class AliPicoV0MC;
class AliPicoCascadeMC : public AliPicoCascade {

 public :

  //AliPicoCascadeMC() = default;
  AliPicoCascadeMC();
  AliPicoCascadeMC(UInt_t wMask,
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
                   Int_t idV, UInt_t wsV, Double_t dXiPx,  Double_t dXiPy, Double_t dXiPz, Double_t dXiE);
  AliPicoCascadeMC(const AliPicoCascadeMC &src);
  AliPicoCascadeMC& operator=(const AliPicoCascadeMC &src);
  virtual ~AliPicoCascadeMC();

  virtual Bool_t IsXiNeg(Double_t const d[21]) const;    // [ 0] V0 MinRadius,
  virtual Bool_t IsXiPos(Double_t const d[21]) const;    // [ 1] V0 MinCosPA,
  virtual Bool_t IsOmegaNeg(Double_t const d[21]) const; // [ 2] V0 MaxCtau,
  virtual Bool_t IsOmegaPos(Double_t const d[21]) const; // [ 3] V0 MaxDausDCA,
                                                         // [ 4] V0 MinPosDCAtoPV,
                                                         // [ 5] V0 MinNegDCAtoPV,
                                                         // [ 6] V0 MinDauXrowsTPC,
                                                         // [ 7] V0 MinDauXrowsOverFindableClusTPC,
                                                         // [ 8] V0 MinDauDeltaM
                                                         // [ 9] dummy: V0 max SigmaTPC
                                                         // [10] V0 MaxWindMass,
                                                         // [11] Xi MinXiRadius,
                                                         // [12] Xi MinXiCosPA,
                                                         // [13] Xi MaxXiCtau,
                                                         // [14] Xi MaxXiDCAtoPV,
                                                         // [15] Xi MinV0DCAtoPV,
                                                         // [16] Xi MaxV0toBachDCA,
                                                         // [17] Xi MinBachDCAtoPV,
                                                         // [18] Xi MinBachXrowsTPC,
                                                         // [19] Xi MinBachXrowsOverFindableClusTPC,
                                                         // [20] Xi Compete Mass

  virtual void GetControlVariables(Float_t d[28]) const;
//=============================================================================

  TLorentzVector KineMC() const { return fXiKine; }

  Bool_t IsXiInRapAcc(Double_t dMin, Double_t dMax);
  Bool_t IsXiNegMC() const { return (fXiPDG== 3312); }
  Bool_t IsXiPosMC() const { return (fXiPDG==-3312); }
//=============================================================================

  Bool_t IsXiPrimary() const {
    return ((fXiStatus & AliPicoBaseDev::kPrimary) == AliPicoBaseDev::kPrimary);
  }

  Bool_t IsXiPhysicalPrimary() const {
    return ((fXiStatus & AliPicoBaseDev::kPhysicalPrimary) == AliPicoBaseDev::kPhysicalPrimary);
  }
//=============================================================================

 private :

  Int_t  fXiPDG;     //
  UInt_t fXiStatus;  //
  TLorentzVector fXiKine;  //

  ClassDef(AliPicoCascadeMC, 3);
};

#endif
