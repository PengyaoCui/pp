#include "./SourceFun.h"

TCanvas* makeCanvas(TString sName);
void V0EtaInJet(){

  TString sPath[] = {"./output/JE", "./output/JE"};
  TString sFile[] = {"AnalysisOutputs_LoopJetRD.root", "AnalysisOutputs_LoopJetRD.root"};
  TString sList[] = {"listLoopJetRD_Kshort_010_JC", "listLoopJetRD_Kshort_010_JC"};
  TString sHist[] = {"hPtEtaI", "hPtEtaJ"};
  TString sLeg[] = {"Inclusive", "JC"};

  auto sLatex("p-Pb at #sqrt{s_{NN}} = 5.02 TeV 0-10%");
  //-----------------------------------
  TCanvas *can = nullptr;

  can = makeCanvas("can");
  //can->SetLogy();
  can->SetGridx(); can->SetGridy();
  auto leg = new TLegend(0.8,0.9,1.0,0.6);    

  //-----------------------------------
  auto nHist = sizeof(sHist)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    //TString sMyPath = Form("%s_%s", Path.Data(), sPath[i].Data()); 
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    TH2D* h1 = (TH2D*)GetTH2D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i));
    h1->GetYaxis()->SetRangeUser(-0.8, 0.8);
    auto binMin = (Int_t)h1->GetXaxis()->FindBin(0.6); 
    auto binMax = (Int_t)h1->GetXaxis()->FindBin(1.); 
    auto h2 = (TH1D*)h1->ProjectionY(Form("Hist_%d", i), binMin, binMax); 
    h2->Scale(1./h2->GetEntries());
    h2->GetYaxis()->SetRangeUser(0., 0.2);
    SetFrame(h2, "#eta", "Probability density");
    DrawHisto(h2, cLine[i], sMark[i], "same");
    h2->Draw("same"); 
    leg->AddEntry(h2,sLeg[i],"lp");
    //h1->Draw("same colz");
  }

  SetLegend(leg);
  leg->Draw();
  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.91, sLatex);
  tex->DrawLatex(0.16, 0.81, "0.6 < #it{p}_{T, K^{0}_{S}} < 1");
  gStyle->SetOptStat("");

  can->SaveAs("./figure/KshortEtaIJ.eps");
  CanvasEnd(can);
  return;
}

TCanvas* makeCanvas(TString sName)
{
  TCanvas *c = new TCanvas(Form("c%s",sName.Data()), sName.Data(), 700, 500);
  c->Range(0., 0., 1., 1.);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(0);
  c->SetRightMargin(0.1);
  c->SetLeftMargin(0.13);
  c->SetTopMargin(0.1);
  c->SetBottomMargin(0.15);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);

  return c;
}

