#include "./SourceFun.h"

void draw_PtSpect(){
  auto Path = "./result";
  auto File = "PtSpect_Eta.root";
  TString sPath[] = {Path, Path, Path, Path};
  TString sFile[] = {File, File, File, File};
  TString sList[] = {"", "", "", ""};
  TString sHist[] = {"hPtJE_Xi_0100", "hPtJE_Xi_010", "hPtJE_Xi_1040", "hPtJE_Xi_40100"};
  TString sLeg[] = {"0-100%", "0-10%", "10-40%", "40-100%"}; 
  TString sTex = "JEusive";

  auto sLatex("#Xi spectrum");
  //-----------------------------------
  TCanvas *can = nullptr;

  can = MakeCanvas("can");
  can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.8,0.9,1.0,0.65);    
  //-----------------------------------
  auto nHist = sizeof(sHist)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    //TString sMyPath = Form("%s_%s", Path.Data(), sPath[i].Data()); 
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    TH1D* h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i));
    //for(int j =1; j<=h1->GetNbinsX(); j++){cout<<h1->GetBinLowEdge(j)<<endl;}
    h1->GetXaxis()->SetRangeUser(0.6, 12.);
    auto dMini = h1->GetMinimum(); 
    auto dMaxi = h1->GetMaximum(); 
    h1->SetTitle(""); 
    h1->GetYaxis()->SetRangeUser(1e-7, 1.);
    SetFrame(h1, "#it{p}_{T}(GeV/#it{c})", "d#rho/d#it{p}_{T}");
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  tex->DrawLatex(0.16, 0.91, sLatex);
  tex->DrawLatex(0.5, 0.91, Form("V0A : %s", sTex.Data()));
  tex->DrawLatex(0.16, 0.3, "|#eta| < 0.75");
  tex->DrawLatex(0.16, 0.2, "p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  leg->Draw();
  gStyle->SetOptStat("");

  can->SaveAs(Form("./figure/Xi_DiffConePt.eps"));
  //can->SaveAs(Form("./figure/Xi_PtSpect_JE.eps"));
  CanvasEnd(can);
  return;
}
