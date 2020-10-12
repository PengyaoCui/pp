#include "./SourceFun.h"

void Ratio(){

  Double_t XMin = 0.;
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

  auto f = TFile::Open("../AnalysisOutputs_Results.root", "read");
  auto l = (TList*)f->Get(Form("listResults_Omega_Default"));
  f->Close();
  TH1D *h = (TH1D*)l->FindObject(Form("hSco"));

  Double_t n1 = h->GetBinContent(1); Double_t w1 = h->GetBinWidth(1);
  Double_t n2 = h->GetBinContent(2); Double_t w2 = h->GetBinWidth(2);

  f = TFile:: Open("./AnalysisOutputs_Results.root", "read");
  l = (TList*)f->Get(Form("listResults_Omega_Default"));
  f->Close();

  TH1D *h1 = (TH1D*)l->FindObject(Form("hSco"));
  Double_t n3 = h1->GetBinContent(1);
  h = RebinTH1D(h, h1);
  
  auto hRatio = (TH1D*) h->Clone("hRatio");
  hRatio->Divide(h1);
  
  padB = MakePadB("padB");
  can->cd();
  padT = MakePadT("padT");
  padT->SetLogy(); 
  padT->cd();
  h->GetXaxis()->SetRangeUser(0., 6.);
  h->GetYaxis()->SetRangeUser(1e5, 1e7);
  h->SetMarkerSize(1);
  DrawHisto(h, cLine[0], sMark[0], "same");
  DrawHisto(h1, cLine[1], sMark[1], "same");
  SetFrame(h, "#it{p}_{T}", "Yield");
  leg->AddEntry(h, "0.6-0.9-2.2","lp");
  leg->AddEntry(h1, "0.6-2.2","lp");


  padB->cd();
  //TLine* l = new TLine(XMin, 1., XMax, 1.);
  //l->SetLineColor(kRed);
  //l->SetLineWidth(2);
  //l->Draw("same");

  DrawHisto(hRatio, cLine[0], sMark[0], "same");
  hRatio->GetXaxis()->SetRangeUser(0., 6.);
  hRatio->GetYaxis()->SetRangeUser(0.5, 1.5);
  SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", "Ratio", 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
   
  padT->cd();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, "pp at #sqrt{s} = 13 TeV");
  tex->DrawLatex(0.2, 0.8, "#Omega corrected yield");
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/Omega_LowPtbin_pp.eps"));
  can->SaveAs(Form("./figure/Omega_LowPtbin_pp.pdf"));
  CanvasEnd(can);
  return;
}
