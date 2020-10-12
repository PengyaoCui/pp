#include "./SourceFun.h"

void DoubleRatio_7_13(){

  TString sType = "Lambda_sum";
  TString sCone = "JE";
 
  TString sLatex(Form("pp at #sqrt{#it{s}} = 13 TeV and 7 TeV"));
 
  auto f = TFile::Open("./result/FinalSpect_ThisAna.root", "read");
  auto l0 = (TList*)f->Get(Form("%s_toKRatio", sType.Data()));
  f->Close();
  auto h0 = (TH1D*)l0->FindObject(Form("h%sR", sCone.Data())); h0->SetName("h0");
  auto h0Sys = (TH1D*)l0->FindObject(Form("he%sR", sCone.Data())); h0->SetName("h0Sys");
  //auto g0 = (TGraphErrors*)l0->FindObject(Form("%sRerr", sCone.Data())); g0->SetName("g0");
   

  auto f0= TFile::Open("./result/pp7Results.root", "read");
  auto l1 = (TList*)f0->Get(Form("pplistHD_JC04_JR04_PtJ10"));
  f0->Close();
  auto h1 = (TH1D*)l1->FindObject(Form("hRatioV_Stat")); h1->SetName("h1");
  auto h1Sys = (TH1D*)l1->FindObject(Form("hRatioV_Syst")); h1Sys->SetName("h1Sys");
  DeNormHistBinWidth(h1Sys);
  h1Sys = RebinTH1D(h1Sys, h1);
  NormHistBinWidth(h1Sys);
  h1Sys->Divide(h1);h1Sys->SetName("h1Sys");
  //auto g1 = (TGraphErrors*)ConvHistogramToGraphErrors(h1, h1Sys, h1->GetNbinsX()); g1->SetName("g1");

  auto hR = (TH1D*)h0->Clone("hR"); hR->Reset();
  for(Int_t i = 1; i<= h0->GetNbinsX(); i++){
    auto V0 = h0->GetBinContent(i); 
    auto E0Stat = (Double_t)(h0->GetBinError(i))/V0; 
    auto E0Sys = h0Sys->GetBinContent(i); 
    auto E0 = TMath::Sqrt(E0Stat*E0Stat + E0Sys*E0Sys);

    auto V1 = h1->GetBinContent(i); 
    auto E1Stat = (Double_t)(h1->GetBinError(i))/V1; 
    auto E1Sys = h1->GetBinContent(i); 
    auto E1 = TMath::Sqrt(E1Stat*E1Stat + E1Sys*E1Sys);
    
    auto ER = TMath::Sqrt(E0*E0 + E1*E1);
    hR->SetBinContent(i, V0/V1);
    hR->SetBinError(i, ER*(V0/V1));
  }
  //-----------------------------------

  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
  can->SetTickx(); can->SetTicky();

  leg = new TLegend(0.7,0.9,1.0,0.7); SetLegend(leg);
  auto hSam = new TH1D("Sample", "", 120, 0, 12.);
  
  hSam->GetYaxis()->SetRangeUser(0., 5.);
  hSam->GetXaxis()->SetRangeUser(0, 12);
  hSam->GetYaxis()->SetTitle("Ratio: 13 TeV/7 TeV");
  SetFrame(hSam, "#it{p}_{T}", "Ratio: 13 TeV/7 TeV");
  DrawHisto(hSam, cLine[0], sMark[0], "same"); 

  //-----------------------------------
  DrawHisto(hR, cLine[0], sMark[0], "same");//leg->AddEntry(hR, "13 TeV");
  //leg->Draw();
  
  TLine* l = new TLine(0, 1., 12, 1.);
  l->SetLineStyle(9);
  l->SetLineColor(kRed);
  l->SetLineWidth(2);
  l->Draw("same");
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  tex->DrawLatex(0.15, 0.8, Form("#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}} in %s", sCone.Data()));
  tex->DrawLatex(0.65, 0.2, Form("error = #sqrt{stat^{2} + sys^{2}}"));
  
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/ThisAna/Double_Ratio_%s_toKRatio_7_13_%s.eps", sType.Data(), sCone.Data()));
  can->SaveAs(Form("./figure/ThisAna/Double_Ratio_%s_toKRatio_7_13_%s.png", sType.Data(), sCone.Data()));
  can->SaveAs(Form("./figure/ThisAna/Double_Ratio_%s_toKRatio_7_13_%s.pdf", sType.Data(), sCone.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
