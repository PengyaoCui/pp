#include "./SourceFun.h"

void Draw_eta(){

  TString sPath[] = {"/home/cuipengyao/study/pp/Local/ThisAna/JE", "/home/cuipengyao/study/pp/Local/ThisAna/JE"};
  TString sFile[] = {"AnalysisOutputs_LoopJetRD.root", "AnalysisOutputs_LoopJetRD.root"};
  TString sList[] = {"listLoopJetRD_Kshort_Default_JC", "listLoopJetRD_Kshort_Default_JC"};
  TString sHist[] = {"hPtEtaI", "hPtEtaJ"};
  TString sLeg[] = {"Inclusive", "Jet"};

  TString sLatex("pp at #sqrt{s} = 13 TeV");
  //-----------------------------------
  TCanvas *can = nullptr;

  auto dYMin = -0.8; auto dYMax = 0.8; 
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
    TH2D* h0 = (TH2D*)GetTH2D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h0->SetName(Form("hist_%d", i));
    TH1D* h1 = (TH1D*)h0->ProjectionY(Form("hEta_%d",i), 1, 1); 
    h1->Scale(1./h1->Integral(1, h1->GetNbinsX())); 
    h1->GetYaxis()->SetRangeUser(0., 0.2);
    h1->GetXaxis()->SetRangeUser(-0.8, 0.8);
    SetFrame(h1, "#eta", "Propability density");
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  SetLegend(leg);
  leg->Draw();
  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.91, Form("%s  K^{0}_{S}", sLatex.Data()));
  tex->DrawLatex(0.16, 0.8, "0.6 < #it{p}_{T}^{K^{0}_{S}} < 1.6 GeV/#it{c}");
  gStyle->SetOptStat("");

  can->SaveAs("./figure/Kshort_Incl_JC_Eta.eps");
  can->SaveAs("./figure/Kshort_Incl_JC_Eta.png");
  CanvasEnd(can);
  return;
}
