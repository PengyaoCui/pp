#include "./SourceFun.h"

void Ratio_7_13(){

  TString sType = "Lambda_sum";
  TString sCone = "JE";
 
  TString sLatex(Form("pp at #sqrt{#it{s}} = 13 TeV and 7 TeV"));
 
  auto f = TFile::Open("./result/FinalSpect_ThisAna.root", "read");
  auto l0 = (TList*)f->Get(Form("%s_toKRatio", sType.Data()));
  f->Close();
  auto h0 = (TH1D*)l0->FindObject(Form("h%sR", sCone.Data())); h0->SetName("h0");
  auto g0 = (TGraphErrors*)l0->FindObject(Form("%sRerr", sCone.Data())); g0->SetName("g0");
   

  auto f0= TFile::Open("./result/pp7Results.root", "read");
  auto l1 = (TList*)f0->Get(Form("pplistHD_JC04_JR04_PtJ10"));
  f0->Close();
  auto h1 = (TH1D*)l1->FindObject(Form("hRatioV_Stat")); h1->SetName("h1");
  auto h1Sys = (TH1D*)l1->FindObject(Form("hRatioV_Syst")); h1Sys->SetName("h1Sys");
  DeNormHistBinWidth(h1Sys);
  h1Sys = RebinTH1D(h1Sys, h1);
  NormHistBinWidth(h1Sys);
  h1Sys->Divide(h1);h1Sys->SetName("h1Sys");
  auto g1 = (TGraphErrors*)ConvHistogramToGraphErrors(h1, h1Sys, h1->GetNbinsX()); g1->SetName("g1");
  //-----------------------------------

  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
  can->SetTickx(); can->SetTicky();

  leg = new TLegend(0.7,0.9,1.0,0.7); SetLegend(leg);


  h0->GetYaxis()->SetRangeUser(0, 1.2);
  h0->GetXaxis()->SetRangeUser(0, 12);
  h0->GetYaxis()->SetTitle("#Lambda/K^{0}_{S}");

  //-----------------------------------
  DrawHisto(h0, cLine[0], sMark[0], "same"); DrawGraph(g0, cLine[0], "E2"); leg->AddEntry(h0, "13 TeV");
  DrawHisto(h1, cLine[1], sMark[1], "same"); DrawGraph(g1, cLine[1], "E2"); leg->AddEntry(h1, "7 TeV");
  leg->AddEntry(g0, "Sys.Error", "f");
  leg->Draw();
  
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
 
  if(sCone != "Incl"){
    tex->DrawLatex(0.15, 0.83, "Jet: Anti-#it{k}_{T}, #it{R} = 0.4");
    tex->DrawLatex(0.15, 0.75, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#it{#eta}_{jet}| < 0.35");
    tex->DrawLatex(0.15, 0.63, Form("%s #frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}", sCone.Data()));
  }else{
    tex->DrawLatex(0.15, 0.83, "Inclusive");
    tex->DrawLatex(0.15, 0.75, "|#it{#eta}| < 0.75");
    tex->DrawLatex(0.15, 0.63, Form("#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}"));
  } 
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/ThisAna/%s_toKRatio_7_13_%s.eps", sType.Data(), sCone.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
