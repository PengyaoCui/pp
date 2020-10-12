#include "./SourceFun.h"

void MakeRatio(){
               
  const TString sRatio = "ThisAna/ALICE";
  
  
  TString sPathNu = "./result";
  TString sFileNu = "PtSpect_Compare2LF.root";
  TString sListNu = "";
  TString sHistNu = "hPtIncl_XiNeg";

  TString sPathDe = "./result/D_Colella";
  TString sFileDe = "correctedspectrumfittedgfcorrphyseff.root";
  TString sListDe = "";
  TString sHistDe = Form("hptcorr_norm_0");
  TString sHistde = Form("hptcorr_norm_1");

  TString sLeg[] = {"This Ana", "ALICE preliminary"};

  auto sLatex(Form("Inclusive #Xi^{-} + #bar{#Xi}^{+}"));
  Double_t XMin = 0.6;
  Double_t XMax = 12.;
  //-----------------------------------
  TCanvas *can = nullptr;
  TPad *padT = nullptr;
  TPad *padB = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;

  can = MakeCanvas("can");
 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(sHistNu)/sizeof(TString);
  const auto nhist = nHist;

  TH1D* hRatio = nullptr;

  padB = MakePadB("padB");
  can->cd();
  padT = MakePadT("padT");
  padT->SetLogy();

  auto h2 = (TH1D*)GetTH1D(sPathDe.Data(), sFileDe.Data(), sListDe.Data(), sHistDe.Data());
  h2->SetName("h2_De");
  h2->SetTitle("");
  auto h2bar = (TH1D*)GetTH1D(sPathDe.Data(), sFileDe.Data(), sListDe.Data(),sHistde.Data() );
  h2->SetName("h2_de");
  h2->Add(h2bar);
  //for(Int_t i = 1; i<= h2->GetNbinsX(); i++){
  //  h2->SetBinContent(i, h2->GetBinContent(i)*h2->GetBinCenter(i)); 
  //  h2->SetBinError(i, h2->GetBinError(i)*h2->GetBinCenter(i)); 
  //}
  //h2->Scale(1./0.7448);
  leg->AddEntry(h2, sLeg[nHist],"lp");
  padT->cd();
  h2->GetXaxis()->SetRangeUser(XMin, XMax);
  h2->GetYaxis()->SetRangeUser(1e-5, 1.);
  SetFrame(h2, "#it{p}_{T}", "d#rho/d#it{p}_{T}(#it{c}/GeV)");
  DrawHisto(h2, cLine[nHist], sMark[nHist], "same");


  auto h1 = (TH1D*)GetTH1D(sPathNu.Data(), sFileNu.Data(), sListNu.Data(), sHistNu.Data());
  h1->SetName(Form("hist")); 
  auto h1bar = (TH1D*)GetTH1D(sPathNu.Data(), sFileNu.Data(), sListNu.Data(), "hPtIncl_XiPos");
  h1bar->SetName(Form("histbar")); 
  h1->Add(h1bar);
  DeNormHistBinWidth(h1); 
  h1=RebinTH1D(h1, h2);
  h1->Scale(TMath::TwoPi());
  NormHistBinWidth(h1); 
  hRatio = (TH1D*) h2->Clone(Form("hRatio")); hRatio->Reset();
  hRatio->Divide(h1, h2);
  hRatio->SetName(Form("hratio"));
  hRatio->GetYaxis()->SetRangeUser(0.8, 1.2);
  padT->cd();
  DrawHisto(h1, cLine[0], sMark[0], "same");
  leg->AddEntry(h1, sLeg[0], "lp");
  padB->cd();
  padB->SetGridy();
  DrawHisto(hRatio, cLine[0], sMark[0], "same");
  SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", sRatio, 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);


  padB->cd();
  TLine* l = new TLine(XMin, 1., XMax, 1.);
  l->SetLineColor(kRed);
  l->SetLineWidth(2);
  l->Draw("same");

  padT->cd();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/JCPt_woITSorTPC.eps"));
  CanvasEnd(can);
  return;
}
