#include "./SourceFun.h"

void JetPtThreshold(){
  const TString sRatio = "#it{p}_{T, jet} > 10 as Ref";
  TString sPathNu[] = {"/home/cuipengyao/study/pp/Local/ThisAna/Uncertainty/JE/JetPt/Loose", "/home/cuipengyao/study/pp/Local/ThisAna/Uncertainty/JE/JetPt/Tight"};
  TString sFileNu[] = {"AnalysisOutputs_Results.root", "AnalysisOutputs_Results.root"};
  TString sListNu[] = {"listResults_Xi_Default_JC", "listResults_Xi_Default_JC"};
  TString sHistNu[] = {"hNco", "hNco"};

  TString sPathDe = "/home/cuipengyao/study/pp/Local/ThisAna/JE";
  TString sFileDe = "AnalysisOutputs_Results.root";
  TString sListDe = "listResults_Xi_Default_JC";
  TString sHistDe = "hNco";
  
  TString sLeg[] = {"#it{p}_{T, jet} > 9", "#it{p}_{T, jet} > 11", "#it{p}_{T, jet} > 10"};

  auto sLatex(Form("Xi in JC with differnt jet #it{p}_{T} cut"));
  Double_t XMin = 0.;
  Double_t XMax = 8.;
  //-----------------------------------
  TCanvas *can = MakeCanvas("can");
  TPad *padT = nullptr;
  TPad *padB = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;

  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(sHistNu)/sizeof(TString);
  const auto nhist = nHist;

  TH1D* h2 = nullptr;
  TH1D* h1 = nullptr;
  TH1D* h11 = nullptr;
  TH1D* hRatio = nullptr;

  padB = MakePadB("padB");
  can->cd();
  padT = MakePadT("padT");
  padT->SetLogy(); 

  TH1D* h0 = new TH1D("h0", "", 10, 0, 12);
  DrawHisto(h0, cLine[nHist], sMark[nHist], "same");

  h2 = (TH1D*)GetTH1D(sPathDe.Data(), sFileDe.Data(), sListDe.Data(), sHistDe.Data());
  h2->SetName("h2_De");
  h2->SetTitle("");
  NormHistBinWidth(h2);
  padT->cd();
  h0->GetXaxis()->SetRangeUser(XMin, XMax);
  h0->GetYaxis()->SetRangeUser(1e-4, 1.);
  h0->SetMarkerSize(1);
  DrawHisto(h2, cLine[nHist], sMark[nHist], "same");
  SetFrame(h0, "#it{p}_{T}", "d#rho/d#it{p}_{T}");
  leg->AddEntry(h2, sLeg[nHist],"lp");

  
  for (Int_t i = 0; i< nHist; ++i){
    TString sMyPath = sPathNu[i]; 
    TString sMyFile = sFileNu[i]; 
    TString sMyList = sListNu[i]; 
    TString sMyHist = sHistNu[i]; 
    h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i)); 
    NormHistBinWidth(h1);
    hRatio = (TH1D*) h2->Clone(Form("hRatio_%d", i)); hRatio->Reset();
    hRatio->Divide(h1, h2);
    hRatio->SetName(Form("hratio_%d", i));
    padT->cd();
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1, sLeg[i], "lp");
    padB->cd();
    padB->SetGridy();
    TH1D* hR = new TH1D("hR", "", 10, 0, 12);
    hR->GetYaxis()->SetRangeUser(0.6, 1.4);
    hR->GetXaxis()->SetRangeUser(0., XMax);
    DrawHisto(hR, cLine[0], sMark[0], "same");
    SetFrame(hR, "#it{p}_{T} (GeV/#it{c})", sRatio, 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
    DrawHisto(hRatio, cLine[i], sMark[i], "same");
  }
  padT->cd();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/JetPtUncer/Xi_Spect_w_JetPtThreshold.pdf"));
  can->SaveAs(Form("./figure/JetPtUncer/Xi_Spect_w_JetPtThreshold.eps"));
  CanvasEnd(can);
  return;
}
