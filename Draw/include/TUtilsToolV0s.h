TH1D *CalcRatioVarV0(TH1D *hKshort, TH1D *hLambda, TH1D *hAntiLa)
{
  if (!(hKshort || hLambda || hAntiLa)) return 0x0;
//=============================================================================

  TH1D *hRatioV = (TH1D*)hKshort->Clone("hRatioV"); hRatioV->Reset();

  for (Int_t k=1; k<=hRatioV->GetNbinsX(); k++) {
    Double_t dVarLambda = hLambda->GetBinContent(k);
    Double_t dErrLambda = hLambda->GetBinError(k);

    Double_t dVarAntiLa = hAntiLa->GetBinContent(k);
    Double_t dErrAntiLa = hAntiLa->GetBinError(k);

    Double_t dVarL = dVarLambda + dVarAntiLa; if (TMath::Abs(dVarL)<1e-12) dVarL = 1e-12;
    Double_t dErrL = TMath::Sqrt(dErrLambda*dErrLambda + dErrAntiLa*dErrAntiLa) / dVarL;

    Double_t dVarK = hKshort->GetBinContent(k); if (TMath::Abs(dVarK)<1e-12) dVarK = 1e-12;
    Double_t dErrK = hKshort->GetBinError(k) / dVarK;

    Double_t dVarR = 0.5 * dVarL / dVarK;
    Double_t dErrR = dVarR * TMath::Sqrt(dErrK*dErrK + dErrL*dErrL);
    hRatioV->SetBinContent(k, dVarR); hRatioV->SetBinError(k, dErrR);
  }

  return hRatioV;
}

//_____________________________________________________________________________
TH1D *CalcRatioErrV0(TH1D *hKshortErr, TH1D *hLambdaErr, TH1D *hAntiLaErr,
                                       TH1D *hLambdaVar, TH1D *hAntiLaVar)
{
  TH1D *hRatioV = (TH1D*)hLambdaVar->Clone("hRatioV"); hRatioV->Reset();

  for (Int_t k=1; k<=hRatioV->GetNbinsX(); k++) {
    Double_t dBin = hLambdaVar->GetBinCenter(k);
    UInt_t   kBin = hKshortErr->FindBin(dBin);

    Double_t dVarLambda = hLambdaVar->GetBinContent(k);
    Double_t dVarAntiLa = hAntiLaVar->GetBinContent(k);

    Double_t dErrLambda = hLambdaErr->GetBinContent(kBin) * dVarLambda;
    Double_t dErrAntiLa = hAntiLaErr->GetBinContent(kBin) * dVarAntiLa;

    Double_t dVarL = dVarLambda + dVarAntiLa; if (TMath::Abs(dVarL)<1e-12) dVarL = 1e-12;
    Double_t dErrL = TMath::Sqrt(dErrLambda*dErrLambda + dErrAntiLa*dErrAntiLa) / dVarL;

    Double_t dErrK = hKshortErr->GetBinContent(kBin);
    Double_t dErrR = TMath::Sqrt(dErrK*dErrK + dErrL*dErrL);

    hRatioV->SetBinContent(k, dErrR);
  }

  return hRatioV;
}

//_____________________________________________________________________________
void AddHistoVar(TH1D *ht, TH1D *hi)
{
  for (Int_t k=1; k<=ht->GetNbinsX(); k++) {
    Double_t dtv = ht->GetBinContent(k);
    Double_t dte = ht->GetBinError(k);

    Double_t div = hi->GetBinContent(k);
    Double_t die = hi->GetBinError(k);

    ht->SetBinContent(k, dtv+div);
    ht->SetBinError(k, TMath::Sqrt(dte*dte + die*die));
  }

  return;
}

//_____________________________________________________________________________
void AddHistoErr(TH1D *ht, TH1D *hi, Double_t dw)
{
  for (Int_t k=1; k<=ht->GetNbinsX(); k++) {
    Double_t dte = ht->GetBinContent(k);
    Double_t die = hi->GetBinContent(k);

    ht->SetBinContent(k, dte + dw*die);
  }

  return;
}

//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================

//_____________________________________________________________________________
TH1D *GetV0NormArHD(const TString   sPathMB,
                    const TString   sPathJE,
                    const TString   sV0,
                    const TString   sCut,
                    const TString   sPtJ,
                    const TString   sOpt,
                    const Int_t     nPtBin,
                    const Double_t *dPtBin=0x0,
                    const Double_t  dEtaMin=-0.75,
                    const Double_t  dEtaMax= 0.75,
                    const Double_t  dAdd = -1.)
{
  if ((sPathMB.IsNull()) ||
      (sPathJE.IsNull()) ||
          (sV0.IsNull()) ||
         (sCut.IsNull()) ||
         (sPtJ.IsNull()) ||
         (sOpt.IsNull())) return 0x0;

  if ((nPtBin<=0) || (!dPtBin)) return 0x0;
//=============================================================================

  TString sUE = sPtJ;
  if (sOpt.Contains("NJ")) sUE = "PtJ05";
  TH1D *hJC = (TH1D*)GetV0NormArJE(sPathMB, sPathJE, sV0, sCut, sPtJ, "JC", nPtBin, dPtBin, dEtaMin, dEtaMax); hJC->SetName("hJC");
  TH1D *hUE = (TH1D*)GetV0NormArJE(sPathMB, sPathJE, sV0, sCut, sUE,  sOpt, nPtBin, dPtBin, dEtaMin, dEtaMax); hUE->SetName("hUE");
  TH1D *hHD = (TH1D*)hJC->Clone("hHD"); hHD->Add(hUE, dAdd);

  return hHD;
}

//_____________________________________________________________________________
TH1D *GetV0NormArHD(const Int_t     nc,
                    const TString  *scMB,
                    const TString  *scJE,
                    const TString   sPath,
                    const TString   sV0,
                    const TString   sCut,
                    const TString   sPtJ,
                    const TString   sOpt,
                    const Int_t     nPtBin,
                    const Double_t *dPtBin=0x0,
                    const Double_t  dEtaMin=-0.75,
                    const Double_t  dEtaMax= 0.75,
                    const Double_t  dAdd = -1.)
{
  if ((sPath.IsNull()) ||
        (sV0.IsNull()) ||
       (sCut.IsNull()) ||
       (sPtJ.IsNull()) ||
       (sOpt.IsNull())) return 0x0;

  if ((nPtBin<=0) || (!dPtBin)) return 0x0;
//=============================================================================

  TString sUE = sPtJ;
  if (sOpt.Contains("NJ")) sUE = "PtJ05";
  TH1D *hJC = (TH1D*)GetV0NormArJE(nc, scMB, scJE, sPath, sV0, sCut, sPtJ, "JC", nPtBin, dPtBin, dEtaMin, dEtaMax); hJC->SetName("hJC");
  TH1D *hUE = (TH1D*)GetV0NormArJE(nc, scMB, scJE, sPath, sV0, sCut, sUE,  sOpt, nPtBin, dPtBin, dEtaMin, dEtaMax); hUE->SetName("hUE");
  TH1D *hHD = (TH1D*)hJC->Clone("hHD"); hHD->Add(hUE, dAdd);

  return hHD;
}

//_____________________________________________________________________________
TH1D *GetV0NormArJE(const TString   sPathMB,
                    const TString   sPathJE,
                    const TString   sV0,
                    const TString   sCut,
                    const TString   sPtJ,
                    const TString   sOpt,
                    const Int_t     nPtBin,
                    const Double_t *dPtBin=0x0,
                    const Double_t  dEtaMin=-0.75,
                    const Double_t  dEtaMax= 0.75)
{
  if ((sPathMB.IsNull()) ||
      (sPathJE.IsNull()) ||
          (sV0.IsNull()) ||
         (sCut.IsNull()) ||
         (sPtJ.IsNull()) ||
         (sOpt.IsNull())) return 0x0;

  if ((nPtBin<=0) || (!dPtBin)) return 0x0;
//=============================================================================

  if (sOpt=="PCM") {
    TH1D *hV0M = GetV0NormArJE_PCM(sPathMB,sPathJE,sV0,sCut,sPtJ,sOpt,nPtBin,dPtBin,dEtaMin,dEtaMax);
    return hV0M;
  }
//=============================================================================

  TString sFile = Form("%s/AnalysisOutputs_LoopJetRD.root",sPathJE.Data());
  TString sList = Form("listLoopJetRD_%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),sOpt.Data());
  cout << "GetV0NormArJE:" << endl
       <<  sFile.Data()    << endl
       <<  sList.Data()    << endl;

  TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH1D     *hV0 = (TH1D*)CalcV0sCorrJE(sPathMB,sPathJE,sV0,sCut,sPtJ,sOpt,nPtBin,dPtBin,dEtaMin,dEtaMax);
  TH1D     *hEv = (TH1D*)list->FindObject("hEvent");
  TProfile *hAr = (TProfile*)list->FindObject("hProfAcc");

  Double_t dAr = 1.;
  if (sOpt.Contains("JC")) dAr = hAr->GetBinContent(3)/hAr->GetBinContent(1);
  if (sOpt.Contains("PC")) dAr = hAr->GetBinContent(3)/hAr->GetBinContent(1);
  if (sOpt.Contains("OC")) dAr = hAr->GetBinContent(2)/hAr->GetBinContent(1);
  if (sOpt.Contains("NJ")) dAr = hAr->GetBinContent(2)/hAr->GetBinContent(1);
  Double_t dNorm = hEv->Integral() * TMath::TwoPi() * (dEtaMax - dEtaMin) * dAr;

  for (Int_t k=1; k<=hV0->GetNbinsX(); k++) {
    hV0->SetBinContent(k, hV0->GetBinContent(k)/dNorm);
    hV0->SetBinError(k, hV0->GetBinError(k)/dNorm);
  }

  return hV0;
}

//_____________________________________________________________________________
TH1D *GetV0NormArJE(const Int_t     nc,
                    const TString  *scMB,
                    const TString  *scJE,
                    const TString   sPath,
                    const TString   sV0,
                    const TString   sCut,
                    const TString   sPtJ,
                    const TString   sOpt,
                    const Int_t     nPtBin,
                    const Double_t *dPtBin=0x0,
                    const Double_t  dEtaMin=-0.75,
                    const Double_t  dEtaMax= 0.75)
{
  if ((sPath.IsNull()) ||
        (sV0.IsNull()) ||
       (sCut.IsNull()) ||
       (sPtJ.IsNull()) ||
       (sOpt.IsNull())) return 0x0;

  if ((nPtBin<=0) || (!dPtBin)) return 0x0;
//=============================================================================

  if (sOpt=="PCM") {
    TH1D *hV0M = GetV0NormArJE_PCM(nc,scMB,scJE,sPath,sV0,sCut,sPtJ,sOpt,nPtBin,dPtBin,dEtaMin,dEtaMax);
    return hV0M;
  }
//=============================================================================

  TH1D *hV0 = 0;
  Double_t dNorm = 0.;
  for (Int_t i=0; i<nc; i++) {
    TString sPathMB = Form("%s/%s",sPath.Data(),scMB[i].Data());
    TString sPathJE = Form("%s/%s",sPath.Data(),scJE[i].Data());

    TString sFile = Form("%s/AnalysisOutputs_LoopJetRD.root",sPathJE.Data());
    TString sList = Form("listLoopJetRD_%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),sOpt.Data());

    TString sLegM = Form("%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),sOpt.Data());
    TString sLegN = Form("%s_%s_%s_%s_%s_%s",scMB[i].Data(),scJE[i].Data(),sV0.Data(),sCut.Data(),sPtJ.Data(),sOpt.Data());
    cout << "GetV0NormArJE:" << endl <<  sFile.Data() << endl <<  sList.Data() << endl;

    TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
    TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

    TProfile *hAr = (TProfile*)list->FindObject("hProfAcc"); hAr->SetName(Form("hAr_%s",sLegN.Data()));
    TH1D     *hEv = (TH1D*)list->FindObject("hEvent"); hEv->SetName(Form("hEv_%s",sLegN.Data()));
    TH1D     *hTm = (TH1D*)CalcV0sCorrJE(sPathMB,sPathJE,sV0,sCut,sPtJ,sOpt,nPtBin,dPtBin,dEtaMin,dEtaMax); hTm->SetName(Form("hTm_%s",sLegN.Data()));

    Double_t dAr = 1.;
    if (sOpt.Contains("JC")) dAr = hAr->GetBinContent(3)/hAr->GetBinContent(1);
    if (sOpt.Contains("PC")) dAr = hAr->GetBinContent(3)/hAr->GetBinContent(1);
    if (sOpt.Contains("OC")) dAr = hAr->GetBinContent(2)/hAr->GetBinContent(1);
    if (sOpt.Contains("NJ")) dAr = hAr->GetBinContent(2)/hAr->GetBinContent(1);
    dNorm += (hEv->Integral() * TMath::TwoPi() * (dEtaMax - dEtaMin) * dAr);

    if (i==0) { hV0 = (TH1D*)hTm->Clone(Form("hV0_%s",sLegM.Data())); hV0->Reset(); }

    for (Int_t k=1; k<=hV0->GetNbinsX(); k++) {
      Double_t dVal = hV0->GetBinContent(k);
      Double_t dErr = hV0->GetBinError(k);

      Double_t dVtm = hTm->GetBinContent(k);
      Double_t dEtm = hTm->GetBinError(k);

      hV0->SetBinContent(k, dVal+dVtm);
      hV0->SetBinError(k, TMath::Sqrt(dErr*dErr + dEtm*dEtm));
    }
  }
//=============================================================================

  for (Int_t k=1; k<=hV0->GetNbinsX(); k++) {
    hV0->SetBinContent(k, hV0->GetBinContent(k)/dNorm);
    hV0->SetBinError(k, hV0->GetBinError(k)/dNorm);
  }

  return hV0;
}

//_____________________________________________________________________________
TH1D *GetV0NormArJE_PCM(const TString   sPathMB,
                        const TString   sPathJE,
                        const TString   sV0,
                        const TString   sCut,
                        const TString   sPtJ,
                        const TString   sOpt,
                        const Int_t     nPtBin,
                        const Double_t *dPtBin=0x0,
                        const Double_t  dEtaMin=-0.75,
                        const Double_t  dEtaMax= 0.75)
{
  if ((sPathMB.IsNull()) ||
      (sPathJE.IsNull()) ||
          (sV0.IsNull()) ||
         (sCut.IsNull()) ||
         (sPtJ.IsNull()) ||
         (sOpt.IsNull())) return 0x0;

  if (sOpt!="PCM") return 0x0;
  if ((nPtBin<=0) || (!dPtBin)) return 0x0;
//=============================================================================

  TString sFileM = Form("%s/AnalysisOutputs_LoopJetRD.root",sPathJE.Data());
  TString sListL = Form("listLoopJetRD_%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),"PCL");
  TString sListU = Form("listLoopJetRD_%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),"PCU");

  TFile *fileM = TFile::Open(sFileM.Data(), "READ"); if (!fileM->IsOpen()) return 0x0;
  TList *listL = (TList*)fileM->Get(sListL.Data());  if (!listL) return 0x0;
  TList *listU = (TList*)fileM->Get(sListU.Data());  if (!listU) return 0x0;
  fileM->Close();

  TH1D     *hEvL = (TH1D*)listL->FindObject("hEvent");       hEvL->SetName("hEvL");
  TProfile *hArL = (TProfile*)listL->FindObject("hProfAcc"); hArL->SetName("hArL");

  TH1D     *hEvU = (TH1D*)listU->FindObject("hEvent");       hEvU->SetName("hEvU");
  TProfile *hArU = (TProfile*)listU->FindObject("hProfAcc"); hArU->SetName("hArU");

  TH1D *hV0L = (TH1D*)CalcV0sCorrJE(sPathMB,sPathJE,sV0,sCut,sPtJ,"PCL",nPtBin,dPtBin,dEtaMin,dEtaMax); hV0L->SetName("hV0L");
  TH1D *hV0U = (TH1D*)CalcV0sCorrJE(sPathMB,sPathJE,sV0,sCut,sPtJ,"PCU",nPtBin,dPtBin,dEtaMin,dEtaMax); hV0U->SetName("hV0U");
//=============================================================================

  Double_t dEvL = hEvL->Integral();
  Double_t dEvU = hEvU->Integral();

  Double_t dArL = hArL->GetBinContent(3) / hArL->GetBinContent(1);
  Double_t dArU = hArU->GetBinContent(3) / hArU->GetBinContent(1);
  Double_t dArM = TMath::TwoPi() * (dEtaMax - dEtaMin) * (dArL + dArU);

  TH1D *hV0M = (TH1D*)hV0L->Clone("hV0M"); hV0M->Reset();

  for (Int_t k=1; k<=hV0M->GetNbinsX(); k++) {
    Double_t dValL = hV0L->GetBinContent(k) / dEvL;
    Double_t dErrL = hV0L->GetBinError(k)   / dEvL;

    Double_t dValU = hV0U->GetBinContent(k) / dEvU;
    Double_t dErrU = hV0U->GetBinError(k)   / dEvU;

    hV0M->SetBinContent(k, (dValL+dValU)/dArM);
    hV0M->SetBinError(k, TMath::Sqrt(dErrL*dErrL + dErrU*dErrU)/dArM);
  }

  return hV0M;
}

//_____________________________________________________________________________
TH1D *GetV0NormArJE_PCM(const Int_t     nc,
                        const TString  *scMB,
                        const TString  *scJE,
                        const TString   sPath,
                        const TString   sV0,
                        const TString   sCut,
                        const TString   sPtJ,
                        const TString   sOpt,
                        const Int_t     nPtBin,
                        const Double_t *dPtBin=0x0,
                        const Double_t  dEtaMin=-0.75,
                        const Double_t  dEtaMax= 0.75)
{
  if ((sPath.IsNull()) ||
        (sV0.IsNull()) ||
       (sCut.IsNull()) ||
       (sPtJ.IsNull()) ||
       (sOpt.IsNull())) return 0x0;

  if (sOpt!="PCM") return 0x0;
  if ((nPtBin<=0) || (!dPtBin)) return 0x0;
//=============================================================================

  TH1D *hV0L = 0;
  TH1D *hV0U = 0;
  Double_t dEvL = 0.;
  Double_t dEvU = 0.;
  Double_t dArM = 0.;
  for (Int_t i=0; i<nc; i++) {
    TString sPathMB = Form("%s/%s",sPath.Data(),scMB[i].Data());
    TString sPathJE = Form("%s/%s",sPath.Data(),scJE[i].Data());

    TString sLegM = Form("%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),sOpt.Data());
    TString sLegN = Form("%s_%s_%s_%s_%s_%s",scMB[i].Data(),scJE[i].Data(),sV0.Data(),sCut.Data(),sPtJ.Data(),sOpt.Data());

    TString sFileM = Form("%s/AnalysisOutputs_LoopJetRD.root",sPathJE.Data());
    TString sListL = Form("listLoopJetRD_%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),"PCL");
    TString sListU = Form("listLoopJetRD_%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),"PCU");

    TFile *fileM = TFile::Open(sFileM.Data(), "READ"); if (!fileM->IsOpen()) return 0x0;
    TList *listL = (TList*)fileM->Get(sListL.Data());  if (!listL) return 0x0;
    TList *listU = (TList*)fileM->Get(sListU.Data());  if (!listU) return 0x0;
    fileM->Close();

    TH1D     *hEvL = (TH1D*)listL->FindObject("hEvent");       hEvL->SetName(Form("hEvL_%s",sLegN.Data()));
    TProfile *hArL = (TProfile*)listL->FindObject("hProfAcc"); hArL->SetName(Form("hArL_%s",sLegN.Data()));

    TH1D     *hEvU = (TH1D*)listU->FindObject("hEvent");       hEvU->SetName(Form("hEvU_%s",sLegN.Data()));
    TProfile *hArU = (TProfile*)listU->FindObject("hProfAcc"); hArU->SetName(Form("hArU_%s",sLegN.Data()));

    TH1D *hTmL = (TH1D*)CalcV0sCorrJE(sPathMB,sPathJE,sV0,sCut,sPtJ,"PCL",nPtBin,dPtBin,dEtaMin,dEtaMax); hTmL->SetName(Form("hV0L_%s",sLegN.Data()));
    TH1D *hTmU = (TH1D*)CalcV0sCorrJE(sPathMB,sPathJE,sV0,sCut,sPtJ,"PCU",nPtBin,dPtBin,dEtaMin,dEtaMax); hTmU->SetName(Form("hV0U_%s",sLegN.Data()));

    dEvL += hEvL->Integral();
    dEvU += hEvU->Integral();

    Double_t dArL = hArL->GetBinContent(3) / hArL->GetBinContent(1);
    Double_t dArU = hArU->GetBinContent(3) / hArU->GetBinContent(1);
    dArM += (TMath::TwoPi() * (dEtaMax - dEtaMin) * (dArL + dArU));

    if (i==0) {
      hV0L = (TH1D*)hTmL->Clone(Form("hV0L_%s",sLegM.Data())); hV0L->Reset();
      hV0U = (TH1D*)hTmU->Clone(Form("hV0U_%s",sLegM.Data())); hV0U->Reset();
    }

    for (Int_t k=1; k<=hV0L->GetNbinsX(); k++) {
      Double_t dVal = hV0L->GetBinContent(k);
      Double_t dErr = hV0L->GetBinError(k);

      Double_t dVtm = hTmL->GetBinContent(k);
      Double_t dEtm = hTmL->GetBinError(k);

      hV0L->SetBinContent(k, dVal+dVtm);
      hV0L->SetBinError(k, TMath::Sqrt(dErr*dErr + dEtm*dEtm));
    }

    for (Int_t k=1; k<=hV0U->GetNbinsX(); k++) {
      Double_t dVal = hV0U->GetBinContent(k);
      Double_t dErr = hV0U->GetBinError(k);

      Double_t dVtm = hTmU->GetBinContent(k);
      Double_t dEtm = hTmU->GetBinError(k);

      hV0U->SetBinContent(k, dVal+dVtm);
      hV0U->SetBinError(k, TMath::Sqrt(dErr*dErr + dEtm*dEtm));
    }
  }
//=============================================================================

  TH1D *hV0M = (TH1D*)hV0L->Clone(Form("hV0M_%s",hV0L->GetName())); hV0M->Reset();

  for (Int_t k=1; k<=hV0M->GetNbinsX(); k++) {
    Double_t dValL = hV0L->GetBinContent(k) / dEvL;
    Double_t dErrL = hV0L->GetBinError(k)   / dEvL;

    Double_t dValU = hV0U->GetBinContent(k) / dEvU;
    Double_t dErrU = hV0U->GetBinError(k)   / dEvU;

    hV0M->SetBinContent(k, (dValL+dValU)/dArM);
    hV0M->SetBinError(k, TMath::Sqrt(dErrL*dErrL + dErrU*dErrU)/dArM);
  }
//=============================================================================

  return hV0M;
}

//_____________________________________________________________________________
TH1D *GetV0NormArMB(const TString   sPath,
                    const TString   sV0,
                    const TString   sCut,
                    const Double_t  dEtaMin=-0.75,
                    const Double_t  dEtaMax= 0.75)
{
  if ((sPath.IsNull()) || (sV0.IsNull()) || (sCut.IsNull())) return 0x0;
//=============================================================================

  TString sFile = Form("%s/AnalysisOutputs_Loop1stRD.root",sPath.Data());
  TString sList = Form("listLoop1stRD_%s_%s",sV0.Data(),sCut.Data());
  if (sCut.Contains("Sigmas")) sList = Form("listLoop1stRD_%s_Default",sV0.Data());

  TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH1D *hEv = (TH1D*)list->FindObject("hEvent");
  TH1D *hV0 = (TH1D*)CalcV0sCorrMB(sPath,sV0,sCut,dEtaMin,dEtaMax);
  Double_t dNorm = hEv->Integral() * TMath::TwoPi() * (dEtaMax-dEtaMin);

  for (Int_t k=1; k<=hV0->GetNbinsX(); k++) {
    hV0->SetBinContent(k, hV0->GetBinContent(k)/dNorm);
    hV0->SetBinError(k, hV0->GetBinError(k)/dNorm);
  }

  return hV0;
}

//_____________________________________________________________________________
TH1D *GetV0NormArMB(const Int_t     nc,
                    const TString  *sc,
                    const TString   sPath,
                    const TString   sV0,
                    const TString   sCut,
                    const Double_t  dEtaMin=-0.75,
                    const Double_t  dEtaMax= 0.75)
{
  if ((sPath.IsNull()) || (sV0.IsNull()) || (sCut.IsNull())) return 0x0;
//=============================================================================

  TH1D *hV0 = 0;
  Double_t dNorm = 0.;
  for (Int_t i=0; i<nc; i++) {
    TString sLegN = Form("%s_%s_%s",sc[i].Data(),sV0.Data(),sCut.Data());
    TString sFile = Form("%s/%s/AnalysisOutputs_Loop1stRD.root",sPath.Data(),sc[i].Data());
    TString sList = Form("listLoop1stRD_%s_%s",sV0.Data(),sCut.Data());
    if (sCut.Contains("Sigmas")) sList = Form("listLoop1stRD_%s_Default",sV0.Data());

    TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
    TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

    TH1D *hEv = (TH1D*)list->FindObject("hEvent");
    hEv->SetName(Form("hEv_%s",sLegN.Data()));

    TH1D *hTm = (TH1D*)CalcV0sCorrMB(Form("%s/%s",sPath.Data(),sc[i].Data()),sV0,sCut,dEtaMin,dEtaMax);
    hTm->SetName(Form("hTm_%s",sLegN.Data()));

    dNorm += (hEv->Integral() * TMath::TwoPi() * (dEtaMax-dEtaMin));
    if (i==0) { hV0 = (TH1D*)hTm->Clone(Form("hV0_%s_%s",sV0.Data(),sCut.Data())); hV0->Reset(); }

    for (Int_t k=1; k<=hV0->GetNbinsX(); k++) {
      Double_t dVal = hV0->GetBinContent(k);
      Double_t dErr = hV0->GetBinError(k);

      Double_t dVtm = hTm->GetBinContent(k);
      Double_t dEtm = hTm->GetBinError(k);

      hV0->SetBinContent(k, dVal+dVtm);
      hV0->SetBinError(k, TMath::Sqrt(dErr*dErr + dEtm*dEtm));
    }
  }
//=============================================================================

  for (Int_t k=1; k<=hV0->GetNbinsX(); k++) {
    hV0->SetBinContent(k, hV0->GetBinContent(k)/dNorm);
    hV0->SetBinError(k, hV0->GetBinError(k)/dNorm);
  }
//=============================================================================

  return hV0;
}

//_____________________________________________________________________________
TH1D *GetV0NormEvJE(const TString   sPathMB,
                    const TString   sPathJE,
                    const TString   sV0,
                    const TString   sCut,
                    const TString   sPtJ,
                    const TString   sOpt,
                    const Int_t     nPtBin,
                    const Double_t *dPtBin=0x0,
                    const Double_t  dEtaMin=-0.75,
                    const Double_t  dEtaMax= 0.75)
{
  if ((sPathMB.IsNull()) ||
      (sPathJE.IsNull()) ||
          (sV0.IsNull()) ||
         (sCut.IsNull()) ||
         (sPtJ.IsNull()) ||
         (sOpt.IsNull())) return 0x0;

  if ((nPtBin<=0) || (!dPtBin)) return 0x0;
//=============================================================================

  TString sFile = Form("%s/AnalysisOutputs_LoopJetRD.root",sPathJE.Data());
  TString sList = Form("listLoopJetRD_%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),sOpt.Data());

  TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH1D *hEv = (TH1D*)list->FindObject("hEvent"); Double_t dNorm = hEv->Integral();
  TH1D *hV0 = (TH1D*)CalcV0sCorrJE(sPathMB,sPathJE,sV0,sCut,sPtJ,sOpt,nPtBin,dPtBin,dEtaMin,dEtaMax);

  for (Int_t k=1; k<=hV0->GetNbinsX(); k++) {
    hV0->SetBinContent(k, hV0->GetBinContent(k)/dNorm);
    hV0->SetBinError(k, hV0->GetBinError(k)/dNorm);
  }

  return hV0;
}

//_____________________________________________________________________________
TH1D *GetV0NormEvMB(const TString   sPath,
                    const TString   sV0,
                    const TString   sCut,
                    const Double_t  dEtaMin=-0.75,
                    const Double_t  dEtaMax= 0.75)
{
  if ((sPath.IsNull()) || (sV0.IsNull()) || (sCut.IsNull())) return 0x0;
//=============================================================================

  TString sFile = Form("%s/AnalysisOutputs_Loop1stRD.root",sPath.Data());
  TString sList = Form("listLoop1stRD_%s_%s",sV0.Data(),sCut.Data());

  TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH1D *hEv = (TH1D*)list->FindObject("hEvent"); Double_t dNorm = hEv->Integral();
  TH1D *hV0 = (TH1D*)CalcV0sCorrMB(sPath,sV0,sCut,dEtaMin,dEtaMax);

  cout << dNorm << endl;

  for (Int_t k=1; k<=hV0->GetNbinsX(); k++) {
    hV0->SetBinContent(k, hV0->GetBinContent(k)/dNorm);
    hV0->SetBinError(k, hV0->GetBinError(k)/dNorm);
  }

  return hV0;
}

//_____________________________________________________________________________
TH1D* CalcV0sCorrJE(const TString   sPathMB,
                    const TString   sPathJE,
                    const TString   sV0,
                    const TString   sCut,
                    const TString   sPtJ,
                    const TString   sOpt,
                    const Int_t     nPtBin,
                    const Double_t *dPtBin=0x0,
                    const Double_t  dEtaMin=-0.75,
                    const Double_t  dEtaMax= 0.75)
{
  if ((sPathMB.IsNull()) ||
      (sPathJE.IsNull()) ||
          (sV0.IsNull()) ||
         (sCut.IsNull()) ||
         (sPtJ.IsNull()) ||
         (sOpt.IsNull())) return 0x0;

  if ((nPtBin<=0) || (!dPtBin)) return 0x0;
//=============================================================================

  TString sFile = Form("%s/AnalysisOutputs_EffCorrJE.root",sPathJE.Data());
  TString sList = Form("listEffCorrJE_%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),sOpt.Data());
  cout << "CalcV0sCorrJE:" << endl
       <<  sFile.Data()    << endl
       <<  sList.Data()    << endl;

  TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH2D *hPtEtaRecoRD_FB = (TH2D*)list->FindObject("hPtEtaRecoRD"); hPtEtaRecoRD_FB->SetName("hPtEtaRecoRD_FB");
  TH2D *hPtEtaRecoMC_FB = (TH2D*)list->FindObject("hPtEtaRecoMC"); hPtEtaRecoMC_FB->SetName("hPtEtaRecoMC_FB");
  TH2D *hPtEtaKineMC_FB = (TH2D*)list->FindObject("hPtEtaKineMC"); hPtEtaKineMC_FB->SetName("hPtEtaKineMC_FB");

  TH2D *hPtEtaRecoRD_RB = (TH2D*)RebinX2D(hPtEtaRecoRD_FB, nPtBin, dPtBin); hPtEtaRecoRD_RB->SetName("hPtEtaRecoRD_RB");
  TH2D *hPtEtaRecoMC_RB = (TH2D*)RebinX2D(hPtEtaRecoMC_FB, nPtBin, dPtBin); hPtEtaRecoMC_RB->SetName("hPtEtaRecoMC_RB");
  TH2D *hPtEtaKineMC_RB = (TH2D*)RebinX2D(hPtEtaKineMC_FB, nPtBin, dPtBin); hPtEtaKineMC_RB->SetName("hPtEtaKineMC_RB");

  const Int_t ll = hPtEtaRecoRD_RB->GetYaxis()->FindBin(dEtaMin + 1e-6);
  const Int_t lu = hPtEtaRecoRD_RB->GetYaxis()->FindBin(dEtaMax - 1e-6);

  TH1D *hPtRecoRD_FB = (TH1D*)hPtEtaRecoRD_FB->ProjectionX("hPtRecoRD_FB", ll,lu);
  TH1D *hPtRecoRD_RB = (TH1D*)hPtRecoRD_FB->Rebin(nPtBin,  "hPtRecoRD_RB",dPtBin);
  TH1D *hPtKineRD_RB = (TH1D*)hPtRecoRD_RB->Clone("hPtKineRD_RB"); hPtKineRD_RB->Reset();
//=============================================================================

  sFile = Form("%s/AnalysisOutputs_FitCbinMC.root",sPathMB.Data());
  sList = Form("listFitCbinMC_%s_%s",sV0.Data(),sCut.Data());

  file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH1D *hSgnMC_FB = (TH1D*)list->FindObject("hS"); hSgnMC_FB->SetName("hSgnMC_FB");
  TH1D *hBkgMC_FB = (TH1D*)list->FindObject("hB"); hBkgMC_FB->SetName("hBkgMC_FB");

  TH1D *hSgnMC_RB = (TH1D*)hSgnMC_FB->Rebin(nPtBin, "hSgnMC_RB", dPtBin);
  TH1D *hBkgMC_RB = (TH1D*)hBkgMC_FB->Rebin(nPtBin, "hBkgMC_RB", dPtBin);
//=============================================================================

  sFile = Form("%s/AnalysisOutputs_FitCbinJE.root",sPathJE.Data());
  sList = Form("listFitCbinJE_%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),sOpt.Data());

  file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH1D *hSgnRD_FB = (TH1D*)list->FindObject("hS"); hSgnRD_FB->SetName("hSgnRD_FB");
  TH1D *hSgnRD_RB = (TH1D*)hSgnRD_FB->Rebin(nPtBin, "hSgnRD_RB", dPtBin);
//=============================================================================

  for (Int_t k=1; k<=hPtEtaRecoRD_RB->GetNbinsX(); k++) {

    Double_t ddv = 0., dde = 0.;
    Double_t dnv = hPtRecoRD_RB->GetBinContent(k);

    for (Int_t l=ll; l<=lu; l++) {
      Double_t dnl = hPtEtaRecoRD_RB->GetBinContent(k,l);
      Double_t dfv = 0., dfe=0.; CalcErrBino(dnl,dnv,dfv,dfe);
      if (TMath::Abs(dfv)<1e-12) dfv = 1e-12;

      Double_t drl = hPtEtaRecoMC_RB->GetBinContent(k,l);
      Double_t dgl = hPtEtaKineMC_RB->GetBinContent(k,l);
      Double_t dev = 0., dee=0.; CalcEffBino(sV0,drl,dgl,dev,dee);
      if (TMath::Abs(dev)<1e-12) dev = 1e-12;

      ddv += (dfv/dev);
      dde += (TMath::Power(dfv/dev,2.) * (TMath::Power(dfe/dfv,2.) + TMath::Power(dee/dev,2.)));
    } dde  = TMath::Sqrt(dde);

    Double_t dsv = hSgnMC_RB->GetBinContent(k);
    Double_t drv = hBkgMC_RB->GetBinContent(k) + dsv;
    Double_t dcv = 0., dce=0.; CalcErrBino(dsv,drv,dcv,dce);
    if (TMath::Abs(dcv)<1e-12) dcv = 1e-12;

    Double_t dmv = hSgnRD_RB->GetBinContent(k);
    Double_t dme = hSgnRD_RB->GetBinError(k);
    if (TMath::Abs(dmv)<1e-12) dmv = 1e-12;
    if (TMath::Abs(ddv)<1e-12) ddv = 1e-12;

    Double_t dvv = dmv * ddv / dcv;
    Double_t dve = dvv * TMath::Sqrt(TMath::Power(dme/dmv,2.) + TMath::Power(dde/ddv,2.) + TMath::Power(dce/dcv,2.));
    hPtKineRD_RB->SetBinContent(k,dvv); hPtKineRD_RB->SetBinError(k,dve);
  }

  return hPtKineRD_RB;
}

//_____________________________________________________________________________
TH1D* CalcEffCorrJE(const TString   sPathMB,
                    const TString   sPathJE,
                    const TString   sV0,
                    const TString   sCut,
                    const TString   sPtJ,
                    const TString   sOpt,
                    const Int_t     nPtBin,
                    const Double_t *dPtBin=0x0,
                    const Double_t  dEtaMin=-0.75,
                    const Double_t  dEtaMax= 0.75)
{
  if ((sPathMB.IsNull()) ||
      (sPathJE.IsNull()) ||
          (sV0.IsNull()) ||
         (sCut.IsNull()) ||
         (sPtJ.IsNull()) ||
         (sOpt.IsNull())) return 0x0;

  if ((nPtBin<=0) || (!dPtBin)) return 0x0;
//=============================================================================

  TString sFile = Form("%s/AnalysisOutputs_EffCorrJE.root",sPathJE.Data());
  TString sList = Form("listEffCorrJE_%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),sOpt.Data());

  TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH2D *hPtEtaRecoRD_FB = (TH2D*)list->FindObject("hPtEtaRecoRD"); hPtEtaRecoRD_FB->SetName("hPtEtaRecoRD_FB");
  TH2D *hPtEtaRecoMC_FB = (TH2D*)list->FindObject("hPtEtaRecoMC"); hPtEtaRecoRD_FB->SetName("hPtEtaRecoRD_FB");
  TH2D *hPtEtaKineMC_FB = (TH2D*)list->FindObject("hPtEtaKineMC"); hPtEtaKineMC_FB->SetName("hPtEtaKineMC_FB");

  TH2D *hPtEtaRecoRD_RB = (TH2D*)RebinX2D(hPtEtaRecoRD_FB, nPtBin, dPtBin); hPtEtaRecoRD_RB->SetName("hPtEtaRecoRD_RB");
  TH2D *hPtEtaRecoMC_RB = (TH2D*)RebinX2D(hPtEtaRecoMC_FB, nPtBin, dPtBin); hPtEtaRecoMC_RB->SetName("hPtEtaRecoMC_RB");
  TH2D *hPtEtaKineMC_RB = (TH2D*)RebinX2D(hPtEtaKineMC_FB, nPtBin, dPtBin); hPtEtaKineMC_RB->SetName("hPtEtaKineMC_RB");

  const Int_t ll = hPtEtaRecoRD_RB->GetYaxis()->FindBin(dEtaMin + 1e-6);
  const Int_t lu = hPtEtaRecoRD_RB->GetYaxis()->FindBin(dEtaMax - 1e-6);

  TH1D *hPtRecoRD_FB = (TH1D*)hPtEtaRecoRD_FB->ProjectionX("hPtRecoRD_FB", ll,lu);
  TH1D *hPtRecoRD_RB = (TH1D*)hPtRecoRD_FB->Rebin(nPtBin,  "hPtRecoRD_RB",dPtBin);
  TH1D *hPtEffiRD_RB = (TH1D*)hPtRecoRD_RB->Clone("hPtEffiRD_RB"); hPtEffiRD_RB->Reset();
//=============================================================================

  sFile = Form("%s/AnalysisOutputs_FitCbinMC.root",sPathMB.Data());
  sList = Form("listFitCbinMC_%s_%s",sV0.Data(),sCut.Data());

  file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH1D *hSgnMC_FB = list->FindObject("hS"); hSgnMC_FB->SetName("hSgnMC_FB");
  TH1D *hBkgMC_FB = list->FindObject("hB"); hBkgMC_FB->SetName("hBkgMC_FB");

  TH1D *hSgnMC_RB = (TH1D*)hSgnMC_FB->Rebin(nPtBin, "hSgnMC_RB", dPtBin);
  TH1D *hBkgMC_RB = (TH1D*)hBkgMC_FB->Rebin(nPtBin, "hBkgMC_RB", dPtBin);
//=============================================================================

  for (Int_t k=1; k<=hPtEtaRecoRD_RB->GetNbinsX(); k++) {

    Double_t ddv = 0., dde = 0.;
    Double_t dnv = hPtRecoRD_RB->GetBinContent(k);
    if (TMath::Abs(dnv)<1e-12) dnv = 1e-12;

    for (Int_t l=ll; l<=lu; l++) {
      Double_t dnl = hPtEtaRecoRD_RB->GetBinContent(k,l);
      Double_t dfv = 0., dfe=0.; CalcErrBino(dnl,dnv,dfv,dfe);
      if (TMath::Abs(dfv)<1e-12) dfv = 1e-12;

      Double_t drl = hPtEtaRecoMC_RB->GetBinContent(k,l);
      Double_t dgl = hPtEtaKineMC_RB->GetBinContent(k,l);
      Double_t dev = 0., dee=0.; CalcEffBino(sV0,drl,dgl,dev,dee);
      if (TMath::Abs(dev)<1e-12) dev = 1e-12;

      ddv += (dfv/dev);
      dde += (TMath::Power(dfv/dev,2.) * (TMath::Power(dfe/dfv,2.) + TMath::Power(dee/dev,2.)));
    } dde  = TMath::Sqrt(dde);

    Double_t dsv = hSgnMC_RB->GetBinContent(k);
    Double_t drv = hBkgMC_RB->GetBinContent(k) + dsv;
    Double_t dcv = 0., dce=0.; CalcErrBino(dsv,drv,dcv,dce);
    if (TMath::Abs(dcv)<1e-12) dcv = 1e-12;
    if (TMath::Abs(ddv)<1e-12) ddv = 1e-12;

    Double_t dvv = dcv / ddv;
    Double_t dve = dvv * TMath::Sqrt(TMath::Power(dce/dcv,2.) + TMath::Power(dde/ddv,2.));
    hPtEffiRD_RB->SetBinContent(k,dvv); hPtEffiRD_RB->SetBinError(k,dve);
  }

  return hPtEffiRD_RB;
}

//_____________________________________________________________________________
TH1D* CalcV0sCorrMB(const TString  sPath,
                    const TString  sV0,
                    const TString  sCut="Default",
                    const Double_t dEtaMin=-0.75,
                    const Double_t dEtaMax= 0.75)
{
  if ((sPath.IsNull()) || (sV0.IsNull()) || (sCut.IsNull())) return 0x0;
//=============================================================================

  TString sFile = Form("%s/AnalysisOutputs_EffCorrMC.root",sPath.Data());
  TString sList = Form("listEffCorrMC_%s_%s",sV0.Data(),sCut.Data());

  TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH2D *hPtEtaRecoRD = (TH2D*)list->FindObject("hPtEtaRecoRD");
  TH2D *hPtEtaRecoMC = (TH2D*)list->FindObject("hPtEtaRecoMC");
  TH2D *hPtEtaKineMC = (TH2D*)list->FindObject("hPtEtaKineMC");

  const Int_t ll = hPtEtaRecoRD->GetYaxis()->FindBin(dEtaMin + 1e-6);
  const Int_t lu = hPtEtaRecoRD->GetYaxis()->FindBin(dEtaMax - 1e-6);

  TH1D *hPtRecoRD = (TH1D*)hPtEtaRecoRD->ProjectionX("hPtRecoRD",ll,lu);
  TH1D *hPtKineRD = (TH1D*)hPtRecoRD->Clone("hPtKineRD"); hPtKineRD->Reset();
//=============================================================================

  sFile = Form("%s/AnalysisOutputs_FitCbinMC.root",sPath.Data());
  sList = Form("listFitCbinMC_%s_%s",sV0.Data(),sCut.Data());

  file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH1D *hSgnMC = (TH1D*)list->FindObject("hS"); hSgnMC->SetName("hSgnMC");
  TH1D *hBkgMC = (TH1D*)list->FindObject("hB"); hBkgMC->SetName("hBkgMC");
//=============================================================================

  sFile = Form("%s/AnalysisOutputs_FitCbinRD.root",sPath.Data());
  sList = Form("listFitCbinRD_%s_%s",sV0.Data(),sCut.Data());

  file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH1D *hSgnRD = (TH1D*)list->FindObject("hS"); hSgnRD->SetName("hSgnRD");
//=============================================================================

  for (Int_t k=1; k<=hPtEtaRecoRD->GetNbinsX(); k++) {

    Double_t ddv = 0., dde = 0.;
    Double_t dnv = hPtRecoRD->GetBinContent(k);

    for (Int_t l=ll; l<=lu; l++) {
      Double_t dnl = hPtEtaRecoRD->GetBinContent(k,l);
      Double_t dfv = 0., dfe=0.; CalcErrBino(dnl,dnv,dfv,dfe);
      if (TMath::Abs(dfv)<1e-12) dfv = 1e-12;

      Double_t drl = hPtEtaRecoMC->GetBinContent(k,l);
      Double_t dgl = hPtEtaKineMC->GetBinContent(k,l);
      Double_t dev = 0., dee=0.; CalcEffBino(sV0,drl,dgl,dev,dee);
      if (TMath::Abs(dev)<1e-12) dev = 1e-12;

      ddv += (dfv/dev);
      dde += (TMath::Power(dfv/dev,2.) * (TMath::Power(dfe/dfv,2.) + TMath::Power(dee/dev,2.)));
    } dde  = TMath::Sqrt(dde);

    Double_t dsv = hSgnMC->GetBinContent(k);
    Double_t drv = hBkgMC->GetBinContent(k) + dsv;
    Double_t dcv = 0., dce=0.; CalcErrBino(dsv,drv,dcv,dce);
      if (TMath::Abs(dcv)<1e-12) dcv = 1e-12;

    Double_t dmv = hSgnRD->GetBinContent(k);
    Double_t dme = hSgnRD->GetBinError(k);

    Double_t dvv = dmv * ddv / dcv;
    Double_t dve = dvv * TMath::Sqrt(TMath::Power(dme/dmv,2.) + TMath::Power(dde/ddv,2.) + TMath::Power(dce/dcv,2.));
    hPtKineRD->SetBinContent(k,dvv); hPtKineRD->SetBinError(k,dve);
  }

  return hPtKineRD;
}

//_____________________________________________________________________________
TH1D* CalcEffCorrMB(const TString  sPath,
                    const TString  sV0,
                    const TString  sCut="Default",
                    const Double_t dEtaMin=-0.75,
                    const Double_t dEtaMax= 0.75)
{
  if ((sPath.IsNull()) || (sV0.IsNull()) || (sCut.IsNull())) return 0x0;
//=============================================================================

  TString sFile = Form("%s/AnalysisOutputs_EffCorrMC.root",sPath.Data());
  TString sList = Form("listEffCorrMC_%s_%s",sV0.Data(),sCut.Data());

  TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH2D *hPtEtaRecoRD = (TH2D*)list->FindObject("hPtEtaRecoRD");
  TH2D *hPtEtaRecoMC = (TH2D*)list->FindObject("hPtEtaRecoMC");
  TH2D *hPtEtaKineMC = (TH2D*)list->FindObject("hPtEtaKineMC");

  const Int_t ll = hPtEtaRecoRD->GetYaxis()->FindBin(dEtaMin + 1e-6);
  const Int_t lu = hPtEtaRecoRD->GetYaxis()->FindBin(dEtaMax - 1e-6);

  TH1D *hPtRecoRD = (TH1D*)hPtEtaRecoRD->ProjectionX("hPtRecoRD", ll, lu);
  TH1D *hPtEffiRD = (TH1D*)hPtRecoRD->Clone("hPtEffiRD"); hPtEffiRD->Reset();
//=============================================================================

  sFile = Form("%s/AnalysisOutputs_FitCbinMC.root",sPath.Data());
  sList = Form("listFitCbinMC_%s_%s",sV0.Data(),sCut.Data());

  file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH1D *hSgnMC = (TH1D*)list->FindObject("hS");
  TH1D *hBkgMC = (TH1D*)list->FindObject("hB");
//=============================================================================

  for (Int_t k=1; k<=hPtEtaRecoRD->GetNbinsX(); k++) {

    Double_t ddv = 0., dde = 0.;
    Double_t dnv = hPtRecoRD->GetBinContent(k);
    if (TMath::Abs(dnv)<1e-12) dnv = 1e-12;

    for (Int_t l=ll; l<=lu; l++) {
      Double_t dnl = hPtEtaRecoRD->GetBinContent(k,l);
      Double_t dfv = 0., dfe=0.; CalcErrBino(dnl,dnv,dfv,dfe);

      Double_t drl = hPtEtaRecoMC->GetBinContent(k,l);
      Double_t dgl = hPtEtaKineMC->GetBinContent(k,l);
      Double_t dev = 0., dee=0.; CalcEffBino(sV0,drl,dgl,dev,dee);

      ddv += (dfv/dev);
      dde += (TMath::Power(dfv/dev,2.) * (TMath::Power(dfe/dfv,2.) + TMath::Power(dee/dev,2.)));
    } dde  = TMath::Sqrt(dde);

    Double_t dsv = hSgnMC->GetBinContent(k);
    Double_t drv = hBkgMC->GetBinContent(k) + dsv;
    Double_t dcv = 0., dce=0.; CalcErrBino(dsv,drv,dcv,dce);

    Double_t dvv = dcv / ddv;
    Double_t dve = dvv * TMath::Sqrt(TMath::Power(dce/dcv,2.) + TMath::Power(dde/ddv,2.));
    hPtEffiRD->SetBinContent(k,dvv); hPtEffiRD->SetBinError(k,dve);
  }

  return hPtEffiRD;
}

//_____________________________________________________________________________
TH1D* CalcEffInclMB(const TString sPath,
                    const TString sV0,
                    const TString sCut="Default")
{
  if ((sPath.IsNull()) || (sV0.IsNull()) || (sCut.IsNull())) return 0x0;
//=============================================================================

  const TString sFile = Form("%s/AnalysisOutputs_EffInclMC.root",sPath.Data());
  const TString sList = Form("listEffInclMC_%s_%s",sV0.Data(),sCut.Data());
//=============================================================================

  TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();
//=============================================================================

  TH1D *hReco = (TH1D*)list->FindObject("hPtReco");
  TH1D *hKine = (TH1D*)list->FindObject("hPtKine");
  TH1D *hEffi = (TH1D*)hReco->Clone("hEffi"); hEffi->Reset();
//=============================================================================

  for (Int_t k=1; k<=hEffi->GetNbinsX(); k++) {
    Double_t dr = hReco->GetBinContent(k);
    Double_t dg = hKine->GetBinContent(k);

    Double_t dv=0., de=0.;  CalcEffBino(sV0,dr,dg,dv,de);
    hEffi->SetBinContent(k,dv); hEffi->SetBinError(k,de);
  }

  return hEffi;
}

//_____________________________________________________________________________
TH1D* CalcEffInclMB(const TString  sPath,
                    const TString  sV0,
                    const TString  sCut,
                    const TString *sc, const Int_t nc)
{
  if ((sPath.IsNull()) || (sV0.IsNull()) || (sCut.IsNull())) return 0x0;
//=============================================================================

  TFile *file = 0;
  TList *list = 0;
  TH1D *hReco = 0;
  TH1D *hKine = 0;
  TH1D *histo = 0;
  TString sFile, sList;
  for (Int_t i=0; i<nc; i++) {
    sFile = Form("%s/%s/AnalysisOutputs_EffInclMC.root",sPath.Data(),sc[i].Data());
    sList = Form("listEffInclMC_%s_%s",sV0.Data(),sCut.Data());

    file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
    list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

    histo = (TH1D*)list->FindObject("hPtReco"); histo->SetName(Form("hPtReco_%d",i));
    if (i==0) { hReco = (TH1D*)histo->Clone("hRecoMB"); } else { hReco->Add(histo); }

    histo = (TH1D*)list->FindObject("hPtKine"); histo->SetName(Form("hPtKine_%d",i));
    if (i==0) { hKine = (TH1D*)histo->Clone("hKineMB"); } else { hKine->Add(histo); }
  }

  TH1D *hEffi = (TH1D*)hReco->Clone("hEffi"); hEffi->Reset();
//=============================================================================

  for (Int_t k=1; k<=hEffi->GetNbinsX(); k++) {
    Double_t dr = hReco->GetBinContent(k);
    Double_t dg = hKine->GetBinContent(k);

    Double_t dv=0., de=0.;  CalcEffBino(sV0,dr,dg,dv,de);
    hEffi->SetBinContent(k,dv); hEffi->SetBinError(k,de);
  }

  return hEffi;
}

//_____________________________________________________________________________
TH1D* CalcEffInclMB(const TString   sPath,
                    const TString   sV0,
                    const TString   sCut,
                    const TString  *sc, const Int_t nc,
                    const Double_t *db, const Int_t nb)
{
  if ((sPath.IsNull()) || (sV0.IsNull()) || (sCut.IsNull())) return 0x0;
//=============================================================================

  TFile *file = 0;
  TList *list = 0;
  TH1D *histo = 0;
  TH1D *hRecoFB = 0;
  TH1D *hKineFB = 0;
  TString sFile, sList;
  for (Int_t i=0; i<nc; i++) {
    sFile = Form("%s/%s/AnalysisOutputs_EffInclMC.root",sPath.Data(),sc[i].Data());
    sList = Form("listEffInclMC_%s_%s",sV0.Data(),sCut.Data());

    file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
    list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

    histo = (TH1D*)list->FindObject("hPtReco"); histo->SetName(Form("hPtReco_%d",i));
    if (i==0) { hRecoFB = (TH1D*)histo->Clone("hRecoFB"); } else { hRecoFB->Add(histo); }

    histo = (TH1D*)list->FindObject("hPtKine"); histo->SetName(Form("hPtKine_%d",i));
    if (i==0) { hKineFB = (TH1D*)histo->Clone("hKineFB"); } else { hKineFB->Add(histo); }
  }

  TH1D *hReco = (TH1D*)hRecoFB->Rebin(nb, "hRecoMB", db);
  TH1D *hKine = (TH1D*)hKineFB->Rebin(nb, "hKineMB", db);
  TH1D *hEffi = (TH1D*)hReco->Clone("hEffi"); hEffi->Reset();
//=============================================================================

  for (Int_t k=1; k<=hEffi->GetNbinsX(); k++) {
    Double_t dr = hReco->GetBinContent(k);
    Double_t dg = hKine->GetBinContent(k);

    Double_t dv=0., de=0.;  CalcEffBino(sV0,dr,dg,dv,de);
    hEffi->SetBinContent(k,dv); hEffi->SetBinError(k,de);
  }

  return hEffi;
}

//_____________________________________________________________________________
void CalcEffBino(const TString sV0, Double_t dn, Double_t dd, Double_t &dv, Double_t &de)
{
  if (TMath::Abs(dd)<1e-12) dd = 1e-12;
  const Double_t db = ((sV0=="Kshort") ? 0.692 : 0.639);

  dv = dn / dd;
  de = TMath::Sqrt(dv * (db-dv) / db / dd);
  return;
}

//_____________________________________________________________________________
void CalcErrBino(Double_t dn, Double_t dd, Double_t &dv, Double_t &de)
{
  if (TMath::Abs(dd)<1e-12) dd = 1e-12;

  dv = dn / dd;
  de = TMath::Sqrt(dv * (1.-dv) / dd);
  return;
}

//_____________________________________________________________________________
TH2D* RebinX2D(TH2D *h2_FB, const Int_t nx, const Double_t *dx)
{
  if ((nx<=0) || (!dx)) return 0x0;
//=============================================================================

  const Int_t my = h2_FB->GetNbinsY();
  const Int_t ny = my;

  Double_t dy[ny+1]; dy[ny] = h2_FB->GetYaxis()->GetBinUpEdge(ny);
  for (Int_t i=0, k=1; i<ny; i++, k++) dy[i] = h2_FB->GetYaxis()->GetBinLowEdge(k);

  TH2D *h2_RB = new TH2D("h2_RB", "", nx, dx, ny, dy); h2_RB->Sumw2();
//=============================================================================

  TH1D *hx_FB = 0;
  TH1D *hx_RB = 0;
  for (Int_t k=1; k<=ny; k++) {
    hx_FB = (TH1D*)h2_FB->ProjectionX(Form("hx_FB_%d",k),k,k);
    hx_RB = (TH1D*)hx_FB->Rebin(nx,   Form("hx_RB_%d",k), dx);

    for (Int_t l=1; l<=nx; l++) {
      h2_RB->SetBinContent(l,k,hx_RB->GetBinContent(l));
      h2_RB->SetBinError(l,k, hx_RB->GetBinError(l));
    }

    delete hx_RB; hx_RB = 0;
    delete hx_FB; hx_FB = 0;
  }

  return h2_RB;
}

//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================

//_____________________________________________________________________________
void FeeddownSubtraction(TH1D *hLambdaI, TH1D *hAntiLaI, const Int_t n, const Int_t nBin=0, const Double_t *dBin=0x0)
{
  const char *sDataset = "20140301";
  const char *sWorkDir = gSystem->WorkingDirectory();
  const char *sPckgDir = gSystem->DirName(sWorkDir);
  const char *sDataDir = Form("%s/data/%s", sPckgDir, sDataset);
//=============================================================================

  Int_t iTmpI = 0, iTmpF = 0;
  if (n==0) { iTmpI = 0; iTmpF = 1; }
  if (n==1) { iTmpI = 2; iTmpF = 3; }
  if (n==2) { iTmpI = 4; iTmpF = 6; }
  if (n==3) { iTmpI = 0; iTmpF = 6; }

  const Int_t iBinI = iTmpI;
  const Int_t iBinF = iTmpF;
  const TString sFileFd[] = {
    Form("%s/LF_Incl_V0A_000_005/AnalysisOutputs_MakeLaFdR.root", sDataDir),
    Form("%s/LF_Incl_V0A_005_010/AnalysisOutputs_MakeLaFdR.root", sDataDir),
    Form("%s/LF_Incl_V0A_010_020/AnalysisOutputs_MakeLaFdR.root", sDataDir),
    Form("%s/LF_Incl_V0A_020_040/AnalysisOutputs_MakeLaFdR.root", sDataDir),
    Form("%s/LF_Incl_V0A_040_060/AnalysisOutputs_MakeLaFdR.root", sDataDir),
    Form("%s/LF_Incl_V0A_060_080/AnalysisOutputs_MakeLaFdR.root", sDataDir),
    Form("%s/LF_Incl_V0A_080_100/AnalysisOutputs_MakeLaFdR.root", sDataDir) };
//=============================================================================

  TFile *file = 0;
  TH1D *histo = 0;
  TH1D *hLambdaN_FB = 0, *hLambdaF_FB = 0;
  TH1D *hAntiLaN_FB = 0, *hAntiLaF_FB = 0;
  for (Int_t k=iBinI, i=0; k<=iBinF; k++, i++) {
    file = TFile::Open(sFileFd[k].Data(), "READ");
    histo = (TH1D*)((TList*)file->Get("listMakeLaFdR_Lambda_Default"))->FindObject("hPtLaNorm");
    histo->SetName(Form("hLambdaN_%d",i)); if (i==0) hLambdaN_FB = (TH1D*)histo->Clone("hLambdaN_FB"); else hLambdaN_FB->Add(histo); histo = 0;

    histo = (TH1D*)((TList*)file->Get("listMakeLaFdR_Lambda_Default"))->FindObject("hPtLaXiFd");
    histo->SetName(Form("hLambdaF_%d",i)); if (i==0) hLambdaF_FB = (TH1D*)histo->Clone("hLambdaF_FB"); else hLambdaF_FB->Add(histo); histo = 0;


    histo = (TH1D*)((TList*)file->Get("listMakeLaFdR_AntiLa_Default"))->FindObject("hPtLaNorm");
    histo->SetName(Form("hAntiLaN_%d",i)); if (i==0) hAntiLaN_FB = (TH1D*)histo->Clone("hAntiLaN_FB"); else hAntiLaN_FB->Add(histo); histo = 0;

    histo = (TH1D*)((TList*)file->Get("listMakeLaFdR_AntiLa_Default"))->FindObject("hPtLaXiFd");
    histo->SetName(Form("hAntiLaF_%d",i)); if (i==0) hAntiLaF_FB = (TH1D*)histo->Clone("hAntiLaF_FB"); else hAntiLaF_FB->Add(histo); histo = 0;
  }
//=============================================================================

  if ((nBin>0) && (dBin)) {
    TH1D *hLambdaN = hLambdaN_FB->Rebin(nBin-1, "hLambdaN", dBin);
    TH1D *hLambdaF = hLambdaF_FB->Rebin(nBin-1, "hLambdaF", dBin); hLambdaF->Divide(hLambdaN);

    TH1D *hAntiLaN = hAntiLaN_FB->Rebin(nBin-1, "hAntiLaN", dBin);
    TH1D *hAntiLaF = hAntiLaF_FB->Rebin(nBin-1, "hAntiLaF", dBin); hAntiLaF->Divide(hAntiLaN);

    Double_t dLambdaF = 0.;
    Double_t dAntiLaF = 0.;
    for (Int_t k=1; k<=nBin-1; k++) {
      dLambdaF = 1. - hLambdaF->GetBinContent(k); if (TMath::Abs(dLambdaF)<1e-12) dLambdaF = 1e-12;
      hLambdaI->SetBinContent(k, dLambdaF * hLambdaI->GetBinContent(k));
      hLambdaI->SetBinError(k, dLambdaF * hLambdaI->GetBinError(k));

      dAntiLaF = 1. - hAntiLaF->GetBinContent(k); if (TMath::Abs(dAntiLaF)<1e-12) dAntiLaF = 1e-12;
      hAntiLaI->SetBinContent(k, dAntiLaF * hAntiLaI->GetBinContent(k));
      hAntiLaI->SetBinError(k, dAntiLaF * hAntiLaI->GetBinError(k));
    }

    dLambdaF = 1. - hLambdaF->GetBinContent(nBin-1); if (TMath::Abs(dLambdaF)<1e-12) dLambdaF = 1e-12;
    dAntiLaF = 1. - hAntiLaF->GetBinContent(nBin-1); if (TMath::Abs(dAntiLaF)<1e-12) dAntiLaF = 1e-12;

    hLambdaI->SetBinContent(nBin, dLambdaF * hLambdaI->GetBinContent(k));
    hLambdaI->SetBinError(nBin, dLambdaF * hLambdaI->GetBinError(k));

    hAntiLaI->SetBinContent(nBin, dAntiLaF * hAntiLaI->GetBinContent(k));
    hAntiLaI->SetBinError(nBin, dAntiLaF * hAntiLaI->GetBinError(k));
  } else {
    TH1D *hLambdaN = (TH1D*)hLambdaN_FB->Clone("hLambdaN");
    TH1D *hLambdaF = (TH1D*)hLambdaF_FB->Clone("hLambdaF"); hLambdaF->Divide(hLambdaN);

    TH1D *hAntiLaN = (TH1D*)hAntiLaN_FB->Clone("hAntiLaN");
    TH1D *hAntiLaF = (TH1D*)hAntiLaF_FB->Clone("hAntiLaF"); hAntiLaF->Divide(hAntiLaN);

    Double_t dLambdaF = 0.;
    Double_t dAntiLaF = 0.;
    for (Int_t k=1; k<=20; k++) {
      dLambdaF = 1. - hLambdaF->GetBinContent(k); if (TMath::Abs(dLambdaF)<1e-12) dLambdaF = 1e-12;
      hLambdaI->SetBinContent(k, dLambdaF * hLambdaI->GetBinContent(k));
      hLambdaI->SetBinError(k, dLambdaF * hLambdaI->GetBinError(k));

      dAntiLaF = 1. - hAntiLaF->GetBinContent(k); if (TMath::Abs(dAntiLaF)<1e-12) dAntiLaF = 1e-12;
      hAntiLaI->SetBinContent(k, dAntiLaF * hAntiLaI->GetBinContent(k));
      hAntiLaI->SetBinError(k, dAntiLaF * hAntiLaI->GetBinError(k));
    }

    dLambdaF = 1. - hLambdaF->GetBinContent(20); if (TMath::Abs(dLambdaF)<1e-12) dLambdaF = 1e-12;
    dAntiLaF = 1. - hAntiLaF->GetBinContent(20); if (TMath::Abs(dAntiLaF)<1e-12) dAntiLaF = 1e-12;

    for (Int_t k=21; k<=21; k++) {
      hLambdaI->SetBinContent(k, dLambdaF * hLambdaI->GetBinContent(k));
      hLambdaI->SetBinError(k, dLambdaF * hLambdaI->GetBinError(k));

      hAntiLaI->SetBinContent(k, dAntiLaF * hAntiLaI->GetBinContent(k));
      hAntiLaI->SetBinError(k, dAntiLaF * hAntiLaI->GetBinError(k));
    }
  }

  return;
}

//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================

//_____________________________________________________________________________
TH1D* GetV0CbinJE(const TString sPath,
                  const TString sV0,
                  const TString sPtJ,
                  const TString sOpt,
                  const TString sCut="Default")
{

  if ((sPath.IsNull()) ||
        (sV0.IsNull()) ||
       (sCut.IsNull()) ||
       (sPtJ.IsNull()) ||
       (sOpt.IsNull())) return 0x0;
//=============================================================================

  TString sFile = Form("%s/AnalysisOutputs_FitCbinJE.root",sPath.Data());
  TString sList = Form("listFitCbinJE_%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),sOpt.Data());

  TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();
//=============================================================================

  TH1D *h = (TH1D*)list->FindObject("hS"); h->SetName(Form("h_%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),sOpt.Data()));

  return h;
}

//_____________________________________________________________________________
TH1D* GetV0CbinMB(const TString sPath,
                  const TString sV0,
                  const TString sCut="Default")
{
  if ((sPath.IsNull()) || (sV0.IsNull()) || (sCut.IsNull())) return 0x0;
//=============================================================================

  TString sFile = Form("%s/AnalysisOutputs_FitCbinRD.root",sPath.Data());
  TString sList = Form("listFitCbinRD_%s_%s",sV0.Data(),sCut.Data());

  TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();
//=============================================================================

  TH1D *h = (TH1D*)list->FindObject("hS"); h->SetName(Form("h_%s_%s",sV0.Data(),sCut.Data()));

  return h;
}

//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================

//_____________________________________________________________________________
Double_t GetNormArMB(const TString   sPath,
                     const TString   sV0,
                     const TString   sCut,
                     const Double_t  dEtaMin=-0.75,
                     const Double_t  dEtaMax= 0.75)
{
  if ((sPath.IsNull()) || (sV0.IsNull()) || (sCut.IsNull())) return 0x0;
//=============================================================================

  TString sFile = Form("%s/AnalysisOutputs_Loop1stRD.root",sPath.Data());
  TString sList = Form("listLoop1stRD_%s_%s",sV0.Data(),sCut.Data());
  if (sCut.Contains("Sigmas")) sList = Form("listLoop1stRD_%s_Default",sV0.Data());

  TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH1D *hEv = (TH1D*)list->FindObject("hEvent");
  Double_t dNorm = hEv->Integral() * TMath::TwoPi() * (dEtaMax-dEtaMin);

  return dNorm;
}

//_____________________________________________________________________________
Double_t GetNormArJE(const TString   sPath,
                     const TString   sV0,
                     const TString   sCut,
                     const TString   sPtJ,
                     const TString   sOpt,
                     const Double_t  dEtaMin=-0.75,
                     const Double_t  dEtaMax= 0.75)
{
  if ((sPath.IsNull()) ||
        (sV0.IsNull()) ||
       (sCut.IsNull()) ||
       (sPtJ.IsNull()) ||
       (sOpt.IsNull())) return 0.;
//=============================================================================

  TString sFile = Form("%s/AnalysisOutputs_LoopJetRD.root",sPath.Data());
  TString sList = Form("listLoopJetRD_%s_%s_%s_%s",sV0.Data(),sCut.Data(),sPtJ.Data(),sOpt.Data());

  TFile *file = TFile::Open(sFile.Data(), "READ"); if (!file->IsOpen()) return 0x0;
  TList *list = (TList*)file->Get(sList.Data());   if (!list) return 0x0; file->Close();

  TH1D     *hEv = (TH1D*)list->FindObject("hEvent");
  TProfile *hAr = (TProfile*)list->FindObject("hProfAcc");

  Double_t dAr = 1.;
  if (sOpt.Contains("JC")) dAr = hAr->GetBinContent(3)/hAr->GetBinContent(1);
  if (sOpt.Contains("PC")) dAr = hAr->GetBinContent(3)/hAr->GetBinContent(1);
  if (sOpt.Contains("OC")) dAr = hAr->GetBinContent(2)/hAr->GetBinContent(1);
  if (sOpt.Contains("NJ")) dAr = hAr->GetBinContent(2)/hAr->GetBinContent(1);

  Double_t dNorm = hEv->Integral() * TMath::TwoPi() * (dEtaMax - dEtaMin) * dAr;

  return dNorm;
}
