#include "./SourceFun.h"

void RatioAllCent(){
  
  TString CentMin[] = {"0", "10", "40"}; 
  TString CentMax[] = {"10", "40", "100"}; 
 
  auto n = sizeof(CentMin)/sizeof(TString); 
  
  TString sPath = "./result";
  TString sFile = "UncertaintyRatio.root";
  TString sList = Form("XKR_Uncer");

  TString sCH = "hCJXKR";//hCILKR, hCJLKR, hCULKR
  TString sEH = "hEJXKR";
  
  //TString sList1 = Form("XKR_Uncer");
  //TString sCH1 = "hCUXKR";//hCIXKR, hCJXKR, hCUXKR
  //TString sEH1 = "hEUXKR";


  auto sLatex(Form("p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV"));
  Double_t XMin = 0.6;
  Double_t XMax = 12.;
  
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
  //can->SetLogy(); 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  
  //-----------------------------------
  TH1D*h1;
  TH1D*h2;
  TGraphErrors*g;
  //TH1D*h3;
  //TH1D*h4;
  //TGraphErrors*g1;
  for(Int_t i =0; i< n; i++){ 
    h1 = (TH1D*)GetTH1D(sPath, sFile, Form("%s_%s%s", sList.Data(), CentMin[i].Data(), CentMax[i].Data()), sCH);
    h1->SetName(Form("Cen_%d", i));
    h2 = (TH1D*)GetTH1D(sPath, sFile, Form("%s_%s%s", sList.Data(), CentMin[i].Data(), CentMax[i].Data()), sEH);
    h2->SetName(Form("Err_%d", i));
    const auto nI = h1->GetNbinsX();
    h1->GetYaxis()->SetRangeUser(0., 0.3);
    h1->GetXaxis()->SetRangeUser(0., 12.);
    //h1->GetYaxis()->SetTitle("#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}");
    h1->GetYaxis()->SetTitle("#frac{#Xi + #bar{#Xi}}{2K^{0}_{S}}");
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1, Form("%s-%s%%", CentMin[i].Data(), CentMax[i].Data()));
    g = (TGraphErrors*)ConvHistogramToGraphErrors(h1, h2, nI); g->SetName(Form("gErr_%d", i));
    DrawGraph(g, cLine[i], "E2");
    
    //h3 = (TH1D*)GetTH1D(sPath, sFile, Form("%s_%s%s", sList1.Data(), CentMin[i].Data(), CentMax[i].Data()), sCH1);
    //h3->SetName(Form("XLCen_%d", i));
    //h4 = (TH1D*)GetTH1D(sPath, sFile, Form("%s_%s%s", sList1.Data(), CentMin[i].Data(), CentMax[i].Data()), sEH1);
    //h4->SetName(Form("XLErr_%d", i));
    //DrawHisto(h3, cLine[i], sMark[i], "same");
    //g1 = (TGraphErrors*)ConvHistogramToGraphErrors(h3, h4, nI); g1->SetName(Form("XigErr_%d", i));
    //DrawGraph(g1, cLine[i], "E2");
  }
  //-----------------------------------
  
  
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  tex->DrawLatex(0.15, 0.8, Form("JE #frac{#Xi + #bar{#Xi}}{2K^{0}_{S}} "));
  //tex->DrawLatex(0.15, 0.8, Form("JE #frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}} "));
  leg->AddEntry(g, "Sys.Error", "f");  
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/XKR_wSysError_JE.eps"));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
