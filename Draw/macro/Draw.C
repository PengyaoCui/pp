#include "./SourceFun.h"

void Draw(){
  TString sPath[] = {"/home/cuipengyao/study/pp/Local/ThisAna/JE", "/home/cuipengyao/study/pp/Local/ThisAna/JE"};
  TString sFile[] = {"AnalysisOutputs_EffCorrJE.root", "AnalysisOutputs_EffCorrJE.root"};
  TString sList[] = {"listEffCorrJE_Xi_Default_JC", "listEffCorrJE_Omega_Default_JC"};
  TString sHist[] = {"hPtEffi", "hPtEffi"};
  TString sLeg[] = { "#Xi", "#Omega"}; 

  Double_t XMin = 0.6;
  Double_t XMax = 8.;
  Double_t YMin = 0.;
  Double_t YMax = 0.3;

  TString sX = "#it{p}_{T}";
  TString sY = "Efficiency";
  auto sLatex("JC Cascades efficiency distribution");
  //-----------------------------------
  TCanvas *can = nullptr;

  can = MakeCanvas("can");
  //can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.75,0.9,1.0,0.65);    
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
    auto dMini = h1->GetMinimum(); 
    auto dMaxi = h1->GetMaximum(); 
    //h1->Rebin(2);
    //h1->Scale(1./h1->Integral(1, h1->GetNbinsX()));
    h1->GetXaxis()->SetRangeUser(XMin, XMax);
    h1->GetYaxis()->SetRangeUser(YMin, YMax);
    h1->SetTitle(""); 
    SetFrame(h1, sX, sY);
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  //TLine* l = new TLine(XMin, 0.15, XMax, 0.15);
  //l->SetLineColor(kRed);
  //l->SetLineStyle(2);
  //l->SetLineWidth(2);
  //l->Draw("same");
  //leg->AddEntry(l, sLeg[2], "L")->SetTextSizePixels(24);
  
  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  tex->DrawLatex(0.16, 0.91, sLatex);
  //tex->DrawLatex(0.16, 0.3, "|#eta| < 0.75");
  //tex->DrawLatex(0.16, 0.2, "pp #sqrt{#it{s}} = 13 TeV");

  leg->Draw();
  gStyle->SetOptStat("");

  can->SaveAs(Form("./figure/JC_Cascade_Efficiency.eps"));
  CanvasEnd(can);
  return;
}
