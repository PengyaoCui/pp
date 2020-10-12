#ifndef ALIPICOCASCADERD_H
#define ALIPICOCASCADERD_H

#include "AliPicoCascade.h"

class AliPicoV0RD;
class AliPicoCascadeRD : public AliPicoCascade {

 public :

  //AliPicoCascadeRD() = default;
  AliPicoCascadeRD();
  AliPicoCascadeRD(UInt_t wMask,
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
                   Float_t  dBachPionSigmaTPC, Float_t dBachKaonSigmaTPC);
  AliPicoCascadeRD(const AliPicoCascadeRD &src);
  AliPicoCascadeRD& operator=(const AliPicoCascadeRD &src);
  virtual ~AliPicoCascadeRD();

  virtual Bool_t IsXiNeg(Double_t const d[21]) const;    // [ 0] V0 MinRadius,
  virtual Bool_t IsXiPos(Double_t const d[21]) const;    // [ 1] V0 MinCosPA,
  virtual Bool_t IsOmegaNeg(Double_t const d[21]) const; // [ 2] V0 MaxCtau,
  virtual Bool_t IsOmegaPos(Double_t const d[21]) const; // [ 3] V0 MaxDausDCA,
                                                         // [ 4] V0 MinPosDCAtoPV,
                                                         // [ 5] V0 MinNegDCAtoPV,
                                                         // [ 6] V0 MinDauXrowsTPC,
                                                         // [ 7] V0 MinDauXrowsOverFindableClusTPC,
                                                         // [ 8] V0 MinDauDeltaM
                                                         // [ 9] V0 max SigmaTPC
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

  virtual void GetControlVariables(Float_t d[31]) const;
//=============================================================================

 private :

  Float_t  fBachPionSigmaTPC = 0.; //
  Float_t  fBachKaonSigmaTPC = 0.; //

  ClassDef(AliPicoCascadeRD, 3);
};

#endif
