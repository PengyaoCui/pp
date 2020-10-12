#include "./SourceFun.h"

void DeltaPt(){

  TString sPath[] = {"./output", "./output"};
  TString sFile[] = {"AnalysisResults_JetQA.root", "AnalysisResults_JetQA.root"};
  TString sList[] = {"AliAnalysisTaskDeltaPt_tracks_Rho_R040_TPC_histos", "AliAnalysisTaskDeltaPt_tracks_Rho_R040_TPC_histos"};
  TString sHist[] = {"fHistDeltaPtRCExLJ_2", "fHistDeltaPtRCRand_2"};
  TString sLeg[] = {"RCExLJ", "RCRandEtaPhi", "Random Cone"};

  auto sLatex("p-Pb at #sqrt{s_{NN}} = 5.02 TeV");
  //-----------------------------------
  TCanvas *can = nullptr;

  can = MakeCanvas("can");
  can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.7,0.9,1.0,0.6);    
  //-----------------------------------
  //TH2D* h0 = (TH2D*)GetTH2D(sPath[0], sFile[0], sList[0], "fHistDeltaPtRCvsEP_2");
  //h0->SetName("HIST");
  //auto h2 = h0->ProjectionY();
  //h2->Scale(1./h2->GetEntries());
  //h2->SetTitle(""); 
  //h2->GetYaxis()->SetRangeUser(10e-7, 1.);
  //h2->GetXaxis()->SetRangeUser(-20., 100.);
  //h2->GetYaxis()->SetRangeUser(10e-7, 1.);
  //h2->GetXaxis()->SetRangeUser(-20., 100.);
  //leg->AddEntry(h2,sLeg[2],"lp");
  //DrawHisto(h2, cLine[0], sMark[0], "same");
  //SetFrame(h2, "#delta #it{p}_{T}(GeV/#it{c})", "Probability density");
  
  auto nHist = sizeof(sHist)/sizeof(TString);
  for (Int_t i = 0; i< 1; i++){
    //TString sMyPath = Form("%s_%s", Path.Data(), sPath[i].Data()); 
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    TH1D* h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i));
    h1->Scale(1./h1->GetEntries());
    h1->SetTitle(""); 
    h1->GetYaxis()->SetRangeUser(10e-7, 1.);
    h1->GetXaxis()->SetRangeUser(-20., 100.);
    h1->GetYaxis()->SetRangeUser(10e-7, 1.);
    h1->GetXaxis()->SetRangeUser(-20., 100.);
    DrawHisto(h1, cLine[0], sMark[0], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
    SetFrame(h1, "#delta #it{p}_{T}(GeV/#it{c})", "Probability density");
  }

  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  tex->DrawLatex(0.16, 0.91, sLatex);
  //tex->DrawLatex(0.16, 0.8, "0-100%");
  leg->Draw();
  gStyle->SetOptStat("");

  can->SaveAs("./figure/DeltaPt_RCExLJ_2.eps");
  CanvasEnd(can);
  return;
}
