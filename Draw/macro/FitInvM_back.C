#include "./SourceFun.h"

void fitInvM(Int_t ptBin = 1, TString CentMin = "0", TString CentMax = "10");
void FitInvM(){

	fitInvM(1);
	fitInvM(2);
	fitInvM(3);
	fitInvM(4);
	fitInvM(5);
	fitInvM(6);
	fitInvM(7);
}

void fitInvM(Int_t ptBin = 1, TString CentMin = "0", TString CentMax = "5"){

  auto PtBin = ptBin;
  TString sPath = "./output"; 
  TString sFile = "AnalysisOutputs_FitInvMrd.root";
  TString sList = Form("listFitInvMrd_Lambda_%s%s", CentMin.Data(), CentMax.Data());
  TString sHist = Form("hFitInvM_%d", PtBin);

  auto sLatex(Form("Lambda Inv.Mass at centrality bin %s-%s%%", CentMin.Data(), CentMax.Data()));
  //-----------------------------------

  //TString sPtBin[] = {"0.6", "1.0", "1.6", "2.2", "3.0", "4.0", "5.5", "7.7 "};//for Xi
  TString sPtBin[] = {"0.6", "1.6", "2.2", "2.8", "3.7", "5.0", "8.0", "12.0"}; //for V0 
  TString sLeg = Form("%s < #it{p}_{T} < %s", sPtBin[PtBin -1].Data(), sPtBin[PtBin].Data());
  TCanvas *can = nullptr;
  can = MakeCanvas(Form("can_%d", ptBin));
  can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.7,0.9,1.0,0.6);    
  //-----------------------------------
  TH1D* h1 = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());
  h1->SetName("Hist"); 
  //SetFrame(h1, "d#it{p}_{T}", "1/2#pi 1/#it{p}_{T} 1/#it{N}_{ev}d^{2}#it{N}/(d#it{p}_{T}d#it{y})(GeV/#it{c})^{-2}");
  SetFrame(h1, "Inv.Mass (GeV/#it{c}^{2})", "Counts");
  //h1->GetXaxis()->SetRangeUser(1.295, 1.345);
  h1->GetXaxis()->SetRangeUser(1.09, 1.14);//for la
  //h1->GetXaxis()->SetRangeUser(0.42, 0.56);//for k 
  auto dMini = h1->GetMinimum();
  auto dMaxi = h1->GetMaximum();
  h1->GetYaxis()->SetRangeUser(0.8*dMini, 1.2*dMaxi);
  DrawHisto(h1, cLine[0], sMark[0], "same");
  leg->AddEntry(h1,sLeg,"");

  TF1* fS = h1->GetFunction(Form("fFitInvM_%d", PtBin));
  fS->SetLineWidth(2);
  fS->Draw("same");

  TF1* fB = (TF1*)GetTH1D(sPath.Data(), "AnalysisOutputs_FitCbinRD.root", Form("listFitCbinRD_Lambda_%s%s", CentMin.Data(), CentMax.Data()), Form("fBkgVarF_%d", PtBin));
  fB->SetLineColor(kBlue);
  fB->Draw("same");

  Double_t dWidth = fS->GetParameter(2);
  Double_t dMass = fS->GetParameter(1);
  TLine*   lLMin = new TLine(dMass-12*dWidth, 0, dMass-12*dWidth, dMaxi);
  lLMin->SetLineColor(kGreen);
  lLMin->SetLineWidth(2);
  lLMin->Draw("same");

  TLine*   lSMax = new TLine(dMass+6*dWidth, 0, dMass+6*dWidth, dMaxi);
  lSMax->SetLineColor(kBlack);
  lSMax->SetLineWidth(2);
  lSMax->Draw("same");

  TLine*   lSMin = new TLine(dMass-6*dWidth, 0, dMass-6*dWidth, dMaxi);
  lSMin->SetLineColor(kBlack);
  lSMin->SetLineWidth(2);
  lSMin->Draw("same");

  TLine*   lRMax = new TLine(dMass+12*dWidth,0, dMass+12*dWidth, dMaxi);
  lRMax->SetLineColor(kGreen);
  lRMax->SetLineWidth(2);
  lRMax->Draw("same");


  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  //tex->DrawLatex(0.16, 0.91, Form("#Xi Inv.Mass at centrality bin %s-%s%%", CentMin.Data(), CentMax.Data()));
  tex->DrawLatex(0.16, 0.91, sLatex);
  //tex->DrawLatex(0.5, 0.91, "V0A multiplicity event classes");
  //tex->DrawLatex(0.16, 0.3, "-0.5 < #it{y}_{CMS} < 0");
  //tex->DrawLatex(0.16, 0.2, "p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  leg->Draw();
  gStyle->SetOptStat("");

  CanvasEnd(can);
  //can->SaveAs(Form("./figure/Lambda_InvM_%s%s_%d.eps", CentMin.Data(), CentMax.Data(), ptBin));
  //TFile *f = TFile::Open("./result/FitXiInvM.root", "UPDATE");
  //f->cd(); can->Write(Form("InvM_Cent%s%s_ptBin%d", CentMin.Data(), CentMax.Data(), ptBin), TObject::kSingleKey);
  //f->Close();
  return;
}
