#include "./SourceFun.h"

void DoubleRatio(const TString sType = "Lambda_sum"){

  TString sLatex(Form("p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV, pp #sqrt{#it{s}} = 13 TeV"));
 
  auto f = TFile::Open("~/study/pPb/Draw/macro/result/FinalSpect_ThisAna.root", "read");
  auto l0 = (TList*)f->Get(Form("%s_toKRatio_0100", sType.Data()));
  auto l1 = (TList*)f->Get(Form("%s_toKRatio_010", sType.Data()));
  auto l2 = (TList*)f->Get(Form("%s_toKRatio_1040", sType.Data()));
  auto l3 = (TList*)f->Get(Form("%s_toKRatio_40100", sType.Data()));
  f->Close();
  
  auto f0= TFile::Open("~/study/pp/Draw/macro/result/FinalSpect_ThisAna.root", "read");
  auto l4 = (TList*)f0->Get(Form("%s_toKRatio", sType.Data()));
  f0->Close();
  //TString sRInclC = "hInclR"; TString sRInclE = "InclRerr";
  //TString sRJEC = "hJER";     TString sRJEE = "JEerr";
  //TString sRUEC = "hUER";     TString sRUEE = "UERerr";

  auto hJE0 = (TH1D*)l0->FindObject(Form("hJER")); hJE0->SetName("hJE0");
  auto hJE1 = (TH1D*)l1->FindObject(Form("hJER")); hJE1->SetName("hJE1");
  auto hJE2 = (TH1D*)l2->FindObject(Form("hJER")); hJE2->SetName("hJE2");
  auto hJE3 = (TH1D*)l3->FindObject(Form("hJER")); hJE3->SetName("hJE3");
  auto hJE4 = (TH1D*)l4->FindObject(Form("hJER")); hJE4->SetName("hJE4");
  auto gJE0 = (TGraphErrors*)l0->FindObject(Form("JERerr")); gJE0->SetName("gJE0");
  auto gJE1 = (TGraphErrors*)l1->FindObject(Form("JERerr")); gJE1->SetName("gJE1");
  auto gJE2 = (TGraphErrors*)l2->FindObject(Form("JERerr")); gJE2->SetName("gJE2");
  auto gJE3 = (TGraphErrors*)l3->FindObject(Form("JERerr")); gJE3->SetName("gJE3");
  auto gJE4 = (TGraphErrors*)l4->FindObject(Form("JERerr")); gJE4->SetName("gJE4");
  
  auto hUE0 = (TH1D*)l0->FindObject(Form("hUER")); hUE0->SetName("hUE0");
  auto hUE1 = (TH1D*)l1->FindObject(Form("hUER")); hUE1->SetName("hUE1");
  auto hUE2 = (TH1D*)l2->FindObject(Form("hUER")); hUE2->SetName("hUE2");
  auto hUE3 = (TH1D*)l3->FindObject(Form("hUER")); hUE3->SetName("hUE3");
  auto hUE4 = (TH1D*)l4->FindObject(Form("hUER")); hUE4->SetName("hUE4");

  auto gUE0 = (TGraphErrors*)l0->FindObject(Form("UERerr")); gUE0->SetName("gUE0");
  auto gUE1 = (TGraphErrors*)l1->FindObject(Form("UERerr")); gUE1->SetName("gUE1");
  auto gUE2 = (TGraphErrors*)l2->FindObject(Form("UERerr")); gUE2->SetName("gUE2");
  auto gUE3 = (TGraphErrors*)l3->FindObject(Form("UERerr")); gUE3->SetName("gUE3");
  auto gUE4 = (TGraphErrors*)l4->FindObject(Form("UERerr")); gUE4->SetName("gUE4");

  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
  leg = new TLegend(0.8,0.9,1.0,0.6); SetLegend(leg);

  auto XMin = 0.; auto XMax = 0.; auto YMin = 0.; auto YMax = 0.;
  if(sType == "Lambda_sum"){XMax = 12.; YMax = 4;}
  if(sType == "Xi"){XMax = 8.; YMax = 8;}
  if(sType == "Omega"){XMax = 5.; YMax = 6;}
  
  auto hUEtoJE0 = (TH1D*)hUE0->Clone("hUEtoJE0"); hUEtoJE0->Divide(hUE0, hJE0);
  auto hUEtoJE1 = (TH1D*)hUE1->Clone("hUEtoJE1"); hUEtoJE1->Divide(hUE1, hJE1);
  auto hUEtoJE2 = (TH1D*)hUE2->Clone("hUEtoJE2"); hUEtoJE2->Divide(hUE2, hJE2);
  auto hUEtoJE3 = (TH1D*)hUE3->Clone("hUEtoJE3"); hUEtoJE3->Divide(hUE3, hJE3);
  auto hUEtoJE4 = (TH1D*)hUE4->Clone("hUEtoJE4"); hUEtoJE4->Divide(hUE4, hJE4);

  auto h = new TH1D("h", "", 100, XMin, XMax);;

  h->GetYaxis()->SetRangeUser(YMin, YMax);
  h->GetXaxis()->SetRangeUser(XMin, XMax);
  SetFrame(h, "#it{p}_{T}", "Double ratio: UE/JE");

  auto gUEtoJE4 = new TGraph(hUEtoJE4); gUEtoJE4->SetLineStyle(1); gUEtoJE4->SetName("gUEtoJE4");
  auto gUEtoJE3 = new TGraph(hUEtoJE3); gUEtoJE3->SetLineStyle(1); gUEtoJE3->SetName("gUEtoJE3");
  auto gUEtoJE2 = new TGraph(hUEtoJE2); gUEtoJE2->SetLineStyle(1); gUEtoJE2->SetName("gUEtoJE2");
  auto gUEtoJE1 = new TGraph(hUEtoJE1); gUEtoJE1->SetLineStyle(1); gUEtoJE1->SetName("gUEtoJE1");
  auto gUEtoJE0 = new TGraph(hUEtoJE0); gUEtoJE0->SetLineStyle(1); gUEtoJE0->SetName("gUEtoJE0");

  //-----------------------------------
  if(sType != "Omega"){
    DrawHisto(h, cLine[0], sMark[0], "same");
    //DrawHisto(hUEtoJE4, cLine[0], sMark[0], "same");leg->AddEntry(hUEtoJE4, "pp");
    //DrawHisto(hUEtoJE0, cLine[1], sMark[1], "same");leg->AddEntry(hUEtoJE0, "p-Pb");
    DrawGraph(gUEtoJE4, cLine[0], "C"); leg->AddEntry(gUEtoJE4, "pp", "L")->SetTextSizePixels(24);
    DrawGraph(gUEtoJE0, cLine[1], "C"); leg->AddEntry(gUEtoJE0, "p-Pb MB", "L")->SetTextSizePixels(24);
    DrawGraph(gUEtoJE1, cLine[2], "C"); leg->AddEntry(gUEtoJE1, "0-10%", "L")->SetTextSizePixels(24);
    DrawGraph(gUEtoJE2, cLine[3], "C"); leg->AddEntry(gUEtoJE2, "10-40%", "L")->SetTextSizePixels(24);
    DrawGraph(gUEtoJE3, cLine[4], "C"); leg->AddEntry(gUEtoJE3, "40-100%", "L")->SetTextSizePixels(24);
    //leg->AddEntry(g4, "Sys.Error", "f");
    leg->Draw();
  }else
  {
    DrawHisto(h, cLine[0], sMark[0], "same");
    DrawHisto(hUEtoJE4, cLine[0], sMark[0], "same");leg->AddEntry(hUEtoJE4, "pp");
    DrawHisto(hUEtoJE0, cLine[1], sMark[1], "same");leg->AddEntry(hUEtoJE0, "p-Pb");
    //DrawGraph(gUEtoJE4, cLine[0], "C"); leg->AddEntry(gUEtoJE4, "pp", "L")->SetTextSizePixels(24);
    //DrawGraph(gUEtoJE0, cLine[1], "C"); leg->AddEntry(gUEtoJE0, "p-Pb", "L")->SetTextSizePixels(24);
    //leg->AddEntry(g4, "Sys.Error", "f");
    leg->Draw();
  }
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  if(sType == "Lambda_sum") tex->DrawLatex(0.15, 0.8, Form("#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}"));
  if(sType == "Xi" || sType == "Omega") tex->DrawLatex(0.15, 0.8, Form("#frac{#%s + #bar{#%s}}{2K^{0}_{S}}", sType.Data(), sType.Data()));
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/%s_DoubleRatio_pp_pPb_wStaErr.eps", sType.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
