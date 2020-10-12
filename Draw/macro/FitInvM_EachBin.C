#include "./SourceFun.h"

void FitInvM_EachBin(){

  TString sPath = "/home/cuipengyao/study/pp/Local/18b_wNewPileup/Inclusive_LHC18g4_Rap_";
  TString sFile = "AnalysisOutputs_FitInvMrd.root";
  TString sList = "listFitInvMrd_Kshort_Default";

  Double_t dXmin = 1.29;
  Double_t dXmax = 1.36;
  Double_t dYmin = 0.;
  Double_t dYmax = 0.;
  auto sLatex("#Xi");
  //-----------------------------------

  TString sPtBin[] = {"0.6", "0.8", "0.9", "1.0", "1.1", "1.2", "1.3", "1.4", "1.5", "1.7", "1.9", "2.2", "2.6", "3.1", "3.9", "4.9", "6.0", "7.2"};
  TCanvas *can = nullptr;
  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  can = MakeCanvas("can");
  can->SetLogy();
  //can->SetGridx(); can->SetGridy();
  can->Divide(3,3);

  auto leg = new TLegend(0.7,0.9,1.0,0.6);    
  //-----------------------------------
  //Int_t nBins = sizeof(sPtBins)/sizeof(TString); 
  for(Int_t i=1; i<11; i++){
    TString sObject = Form("hFitInvM_%d",i);
    can->cd(i-1);

    TH1D* hFitInvM = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sObject.Data());
    hFitInvM->SetName(Form("hFitInvM_%d", i));
    SetFrame(hFitInvM, "Inv.Mass (GeV/#it{c}^{2})", "Counts");
    DrawHisto(hFitInvM, cLine[0], sMark[0], "same");

    hFitInvM->GetXaxis()->SetRangeUser(dXmin, dXmax);

    TF1* fS = hFitInvM->GetFunction(Form("fFitInvM_%d",i));
    fS->SetLineWidth(2);
    fS->Draw("same");

    TF1* fB = (TF1*)GetTH1D(sPath, "AnalysisOutputs_FitCbinRD.root", "listFitCbinRD_Kshort_Default", Form("fBkgVarF_%d",i));
    fB->SetLineColor(kBlue);
    fB->Draw("same");

    Double_t dWidth = fS->GetParameter(2);
    Double_t dMass = fS->GetParameter(1);
    can->GetPad(i-1)->SetLogy();
    tex->DrawLatex(0.3, 0.91, Form("#Xi^{-}: %s < #it{p}_{T} < %s GeV/c", sPtBin[i-1].Data(), sPtBin[i].Data()));
  }

  gStyle->SetOptStat("");

  CanvasEnd(can);
  return;
}
