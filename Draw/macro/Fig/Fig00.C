#include "./SourceFun.h"

void Fig00(){

  auto f = TFile::Open("./pp.root", "read");
  auto lK = (TList*)f->Get(Form("Kshort"));
  auto lL = (TList*)f->Get(Form("Lambda_sum"));
  auto lX = (TList*)f->Get(Form("Xi"));
  auto lO = (TList*)f->Get(Form("Omega"));
  f->Close();
  
  auto hK0 = (TH1D*)lK->FindObject(Form("InclCen")); hK0->SetName("hK0");
  auto hK1 = (TH1D*)lK->FindObject(Form("JECen"));   hK1->SetName("hK1");
  auto hK2 = (TH1D*)lK->FindObject(Form("UECen"));   hK2->SetName("hK2");
  auto gK0 = (TGraphErrors*)lK->FindObject(Form("Inclerr")); gK0->SetName("gK0");
  auto gK1 = (TGraphErrors*)lK->FindObject(Form("JEerr"));   gK1->SetName("gK1");
  auto gK2 = (TGraphErrors*)lK->FindObject(Form("UEerr"));   gK2->SetName("gK2");
 
  auto hL0 = (TH1D*)lL->FindObject(Form("InclCen")); hL0->SetName("hL0");
  auto hL1 = (TH1D*)lL->FindObject(Form("JECen"));   hL1->SetName("hL1");
  auto hL2 = (TH1D*)lL->FindObject(Form("UECen"));   hL2->SetName("hL2");
  auto gL0 = (TGraphErrors*)lL->FindObject(Form("Inclerr")); gL0->SetName("gL0");
  auto gL1 = (TGraphErrors*)lL->FindObject(Form("JEerr"));   gL1->SetName("gL1");
  auto gL2 = (TGraphErrors*)lL->FindObject(Form("UEerr"));   gL2->SetName("gL2");
  
  auto hX0 = (TH1D*)lX->FindObject(Form("InclCen")); hX0->SetName("hX0");
  auto hX1 = (TH1D*)lX->FindObject(Form("JECen"));   hX1->SetName("hX1");
  auto hX2 = (TH1D*)lX->FindObject(Form("UECen"));   hX2->SetName("hX2");
  auto gX0 = (TGraphErrors*)lX->FindObject(Form("Inclerr")); gX0->SetName("gX0");
  auto gX1 = (TGraphErrors*)lX->FindObject(Form("JEerr"));   gX1->SetName("gX1");
  auto gX2 = (TGraphErrors*)lX->FindObject(Form("UEerr"));   gX2->SetName("gX2");
  
  auto hO0 = (TH1D*)lO->FindObject(Form("InclCen")); hO0->SetName("hO0");
  auto hO1 = (TH1D*)lO->FindObject(Form("JECen"));   hO1->SetName("hO1");
  auto hO2 = (TH1D*)lO->FindObject(Form("UECen"));   hO2->SetName("hO2");
  auto gO0 = (TGraphErrors*)lO->FindObject(Form("Inclerr")); gO0->SetName("gO0");
  auto gO1 = (TGraphErrors*)lO->FindObject(Form("JEerr"));   gO1->SetName("gO1");
  auto gO2 = (TGraphErrors*)lO->FindObject(Form("UEerr"));   gO2->SetName("gO2");
  
  auto h0 = new TH1D("h0","", 130, -0.5, 12.5);
  SetFrame( h0, "#it{p}_{T}(GeT/#it{c})", "d#rho/d#it{p}_{T}");
  h0->GetXaxis()->SetRangeUser(-0.1, 12.5); 
  h0->GetYaxis()->SetRangeUser(1e-6, 1.); 
  
  TCanvas *can = nullptr;
  can = MakeBigCanvas("can");
  can->cd();
  TPad *p1= nullptr; TPad *p2= nullptr; TPad *p3= nullptr; TPad *p4 = nullptr;
  
  p1 = MakePadTL("p1"); can->cd();
  p2 = MakePadTR("p2"); can->cd();
  p3 = MakePadBL("p3"); can->cd();
  p4 = MakePadBR("p4"); can->cd();
  p1->SetLogy(); p2->SetLogy(); p3->SetLogy(); p4->SetLogy();

  TLegend *leg = nullptr;
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  leg->SetTextSize(gStyle->GetTextSize()); 
  
  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);

  p1->cd();
  DrawHisto(h0, cLine[0], sMark[0], "same");
  DrawHisto(hK0, cLine[0], sMark[0], "same"); DrawGraph(gK0, cLine[0], "E2"); leg->AddEntry(hK0, "Inclusive");
  DrawHisto(hK1, cLine[1], sMark[1], "same"); DrawGraph(gK1, cLine[1], "E2"); leg->AddEntry(hK1, "JE");
  DrawHisto(hK2, cLine[2], sMark[2], "same"); DrawGraph(gK2, cLine[2], "E2"); leg->AddEntry(hK2, "UE");
  leg->AddEntry(gK0, "Sys.Error", "f");
  h0->GetXaxis()->CenterTitle(kTRUE);
  tex->DrawLatex(0.25, 0.1, "K^{0}_{S}");
  can->cd();
  
  p2->cd();
  DrawHisto(h0, cLine[0], sMark[0], "same");
  DrawHisto(hL0, cLine[0], sMark[0], "same"); DrawGraph(gL0, cLine[0], "E2"); //leg->AddEntry(hL0, "Inclusive");
  DrawHisto(hL1, cLine[1], sMark[1], "same"); DrawGraph(gL1, cLine[1], "E2"); //leg->AddEntry(hL1, "JE");
  DrawHisto(hL2, cLine[2], sMark[2], "same"); DrawGraph(gL2, cLine[2], "E2"); //leg->AddEntry(hL2, "UE");
  can->cd();
  
  p3->cd();
  DrawHisto(h0, cLine[0], sMark[0], "same");
  DrawHisto(hX0, cLine[0], sMark[0], "same"); DrawGraph(gX0, cLine[0], "E2"); //leg->AddEntry(hX0, "Inclusive");
  DrawHisto(hX1, cLine[1], sMark[1], "same"); DrawGraph(gX1, cLine[1], "E2"); //leg->AddEntry(hX1, "JE");
  DrawHisto(hX2, cLine[2], sMark[2], "same"); DrawGraph(gX2, cLine[2], "E2"); //leg->AddEntry(hX2, "UE");
  can->cd();
  
  p4->cd();
  DrawHisto(h0, cLine[0], sMark[0], "same");
  DrawHisto(hO0, cLine[0], sMark[0], "same"); DrawGraph(gO0, cLine[0], "E2"); //leg->AddEntry(hO0, "Inclusive");
  DrawHisto(hO1, cLine[1], sMark[1], "same"); DrawGraph(gO1, cLine[1], "E2"); //leg->AddEntry(hO1, "JE");
  DrawHisto(hO2, cLine[2], sMark[2], "same"); DrawGraph(gO2, cLine[2], "E2"); //leg->AddEntry(hO2, "UE");
  leg->Draw();
  can->cd();

//  tex->DrawLatex(0.15, 0.83, "Jet: Anti-#it{k}_{T}, #it{R} = 0.4");
//  tex->DrawLatex(0.15, 0.75, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#it{#eta}_{jet}| < 0.35");
//  tex->DrawLatex(0.15, 0.63, Form("#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}"));
//  tex->DrawLatex(0.15, 0.63, Form("#frac{#Xi + #bar{#Xi}}{2K^{0}_{S}}"));
//
  gStyle->SetOptStat("");

  //can->SaveAs(Form("./figure/ThisAna/Xi_toKRatio_DataPy.eps"));
  CanvasEnd(can);

  return;

}


