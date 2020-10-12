#include "./SourceFun.h"

void QA(){

  TString sPath = "/home/cuipengyao/study/pp/Local/QADiffPeriod";
  const TString sRatio = "18o as Ref";
  TString sPathNu[] = {"18b", "18d", "18e", "18f", "18g", "18h", "18i", "18k", "18l", "18m"};
  //TString sPathNu[] = { "17c", "17e", "17f", "17g", "17h", "17i", "17j", "17k", "17l", "17m", "17o", "17r" };
  //TString sPathNu[] = { "16d", "16e", "16g", "16h", "16i", "16k", "16l", "16o", "16p"};
  //TString sPathNu[] = { "18", "17" };

  TString sPathDe = "/home/cuipengyao/study/pp/Local/QADiffPeriod/18o";
  TString sFile = "AnalysisOutputs_FitCbinRD.root";
  TString sList = "listFitCbinRD_Xi_Default";
  TString sHist = "hS";
  //TString sFile = "AnalysisOutputs_LoopJetRD.root";
  //TString sList = "listLoopJetRD_Xi_Default_JC";
  //TString sHist = "hJetPtAfter";

  TString sLeg[] = {"LHC18b", "LHC18d", "LHC18e", "LHC18f", "LHC18g", "LHC18h", "LHC18i", "LHC18k", "LHC18l", "LHC18m"};
  //TString sLeg[] = {"18", "17", "16"};
  //Double_t nEvent[] = {677433787, 851296843, 489732981};
  Double_t nEvent[] = {1.92322e+08, 5.6664e+07, 6.84701e+07, 7.35362e+07, 1.21975e+07, 3.44775e+06, 6.16894e+07, 1.23332e+07, 8.97462e+07, 1.76404e+08, 3.87387e+07, 8.42065e+07};

  TString sLatex(Form("18o as the referene"));
  Double_t XMin = 0.; 
  Double_t XMax = 12. ;
  Double_t YMin = 1e-9;
  Double_t YMax = 1e1;
  Int_t a = 1;
  //-----------------------------------
  TCanvas *can = nullptr;
  TPad *padT = nullptr;
  TPad *padB = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;

  can = MakeCanvas("can");
  leg = new TLegend(0.4, 0.7, 1., 0.9); SetLegend(leg);
  leg->SetNColumns(3);
  //-----------------------------------
  auto nHist = sizeof(sPathNu)/sizeof(TString);
  const auto nhist = nHist;
  Double_t dBin[] = {10, 15, 20, 25, 30, 35, 40, 50, 60, 80, 100};
  //Double_t dBin[] = {0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12.};
  Int_t nBin = sizeof(dBin)/sizeof(Double_t) - 1;
  TH1D *h0 = new TH1D("h0", "", nBin, dBin);
 
  TH1D* h2 = nullptr;
  TH1D* h1 = nullptr;
  TH1D* hRatio = nullptr;

  padB = MakePadB("padB");
  can->cd();
  padT = MakePadT("padT");
  padT->SetLogy(); 
  padT->SetLogy();

  h2 = (TH1D*)GetTH1D(sPathDe.Data(), sFile.Data(), sList.Data(), sHist.Data());
  //h2->Scale(1./h2->GetEntries());
  //h2->Scale(1./h2->Integral(1, h2->GetNbinsX()));
  h2->Scale(1./nEvent[nHist]);
  //h2=RebinTH1D(h2, h0);
  h2->Rebin(a);
  h2->SetName("h2_De");
  NormHistBinWidth(h2); 
  h2->SetTitle("");
  padT->cd();
  auto dMini = h2->GetMinimum(); 
  auto dMaxi = h2->GetMaximum(); 
  h2->GetXaxis()->SetRangeUser(0, 12.);
  h2->GetYaxis()->SetRangeUser(0.1*dMini, 100.*dMaxi);
  if( dMini<= 0)h2->GetYaxis()->SetRangeUser(1e-7, 100.*dMaxi);
  h2->SetMarkerSize(1);
  DrawHisto(h2, cLine[nHist], sMark[nHist], "same");
  //SetFrame(h2, "#it{p}_{T}", "Probability density");
  SetFrame(h2, "#it{p}_{T}", "#frac{1}{N_{kINT7}} #frac{d#it{N}}{d#it{p}_{T}}");


  for (Int_t i = 0; i< nHist; ++i){
    TString sMyPath = Form("%s/%s", sPath.Data(), sPathNu[i].Data());
    TString sMyFile = sFile; 
    TString sMyList = sList; 
    TString sMyHist = sHist; 
    h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    //h1->Scale(1./h2->GetEntries());
    //h1->Scale(1./h1->Integral(1, h1->GetNbinsX()));
    h1->Scale(1./nEvent[i]);
    //h1=RebinTH1D(h1, h0);
    h1->Rebin(a);
    h1->SetName(Form("hist_%d", i)); 
    h1->SetTitle(""); 
    NormHistBinWidth(h1); 
    hRatio = (TH1D*) h2->Clone(Form("hRatio_%d", i)); hRatio->Reset();
    hRatio->Divide(h1, h2);
    hRatio->SetName(Form("hratio_%d", i));
    hRatio->GetYaxis()->SetRangeUser(0.6, 1.4);
    padT->cd();
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1, sLeg[i], "lp");
    padB->cd();
    padB->SetGridy();
    DrawHisto(hRatio, cLine[i], sMark[i], "same");
    //SetFrame(hRatio, "#varphi{jet}", sRatio, 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
    //SetFrame(hRatio, Form("%s", sHist.Data()), sRatio, 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
    SetFrame(hRatio, Form("#it{p}_{T}"), sRatio, 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
  }
  leg->AddEntry(h2, sLeg[nHist],"lp");


  padB->cd();
  //TLine* l = new TLine(XMin, 1., XMax, 1.);
  //l->SetLineColor(kRed);
  //l->SetLineWidth(2);
  //l->Draw("same");

  padT->cd();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, "Xi");
  tex->DrawLatex(0.2, 0.8, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/QAPlots/Xi_%s_18.eps", sHist.Data()));
  CanvasEnd(can);
  return;
}
