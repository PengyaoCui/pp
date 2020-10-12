#include "./SourceFun.h"

TCanvas* makeCanvas(TString sName);
void Draw_2D(){

  TString sPath[] = {"/home/cuipengyao/study/pp/Local/ThisAna/JE"};
  TString sFile[] = {"AnalysisOutputs_LoopJetRD.root"};
  TString sList[] = {"listLoopJetRD_Kshort_Default_JC"};
  TString sHist[] = {"hPtEtaJ"};

  auto sLatex("pp at #sqrt{s} = 13 TeV");
  //-----------------------------------
  TCanvas *can = nullptr;

  auto dYMin = -0.8; auto dYMax = 0.8; 
  can = makeCanvas("can");
  //can->SetLogy();
  can->SetGridx(); can->SetGridy();

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
    auto dMini = h1->GetMinimum(); 
    auto dMaxi = h1->GetMaximum(); 
    h1->GetYaxis()->SetRangeUser(dYMin, dYMax);
    //SetFrame(h1, "#it{p}_{T}", "Fd Fraction");
    //DrawHisto(h1, cLine[i], sMark[i], "same");
    //h1->GetXaxis()->SetRangeUser(0.6, 12.);
    h1->GetXaxis()->SetTitle("#it{p}_{T}(GeV/#it{c})");
    h1->GetYaxis()->SetTitle("#eta");
    h1->GetXaxis()->SetLabelSize(0.05);
    h1->GetYaxis()->SetLabelSize(0.05);

    h1->GetXaxis()->SetTitleSize(0.06);
    h1->GetYaxis()->SetTitleSize(0.06);

    h1->GetXaxis()->SetTitleOffset(1.);
    h1->GetYaxis()->SetTitleOffset(1.);
    h1->Draw("same colz");
  }

  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  //tex->DrawLatex(0.16, 0.91, sLatex);
  tex->DrawLatex(0.16, 0.91, "JC K^{0}_{S}");
  gStyle->SetOptStat("");

  can->SaveAs("./figure/Kshort_JC_PtEta.eps");
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

