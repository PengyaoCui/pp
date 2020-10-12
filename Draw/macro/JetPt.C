#include "./SourceFun.h"

void JetPt(){

  TString sPath[] = {"/home/cuipengyao/study/pp/Local/16l_wNewPileup/JE_7Bins", "/home/cuipengyao/study/QM2018_pp/Cascade_LHC16k/JC_AddJetPt"};
  TString sFile[] = {"AnalysisOutputs_LoopJetRD.root", "AnalysisOutputs_LoopJetRD.root"};
  TString sList[] = {"listLoopJetRD_Lambda_Default_JC", "listLoopJetRD_Xi_Default_PtJ22_JC"};
  TString sHist[] = {"hJetPtAfter", "hJetPtAfter"};
  TString sLeg[] = {"New FW", "Old FW"};

  auto sLatex("Jet #it{p}_{T} distribution");
  //-----------------------------------
  TCanvas *can = nullptr;

  can = MakeCanvas("can");
  can->SetLogy();
  can->SetGridx(); can->SetGridy();

  Double_t dBin[] = {10., 11., 12., 13., 14., 15., 16., 17., 18., 19., 20., 21., 22., 23., 24., 25., 26., 27., 28., 29., 30., 31., 32., 33., 34., 35., 36., 37., 38., 39., 40., 42., 44., 46., 48., 50., 53., 56., 60., 64., 68., 73., 78., 84., 90., 100.};
  Int_t nBin = sizeof(dBin)/sizeof(Double_t) - 1;
  TH1D *hPtJet = new TH1D("hPtJet", "", nBin, dBin);

  auto leg = new TLegend(0.8,0.9,1.0,0.7);    
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
    TH1D* h2 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), "hEvent");
    h2->SetName(Form("hEvent_%d", i));
    //h1 = (TH1D*) h1-> Rebin(nBin, "h1", dBin);
    //h1->Scale(1./h2->GetEntries());
    h1->Scale(1./h1->Integral(1, h1->GetNbinsX()));
    h1 = RebinTH1D(h1, hPtJet);
    NormHistBinWidth(h1);
    auto dMini = h1->GetMinimum(); 
    auto dMaxi = h1->GetMaximum(); 
    //h1->GetYaxis()->SetRangeUser(0.1*dMini, 100*dMaxi);
    h1->GetYaxis()->SetRangeUser(1e-6, 10.);
    //SetFrame(h1, "#it{p}_{T}(GeV/#it{c})", "1/#it{N}_{ev} #times d#it{N}/d#it{p}_{T} (GeV/#it{c})");
    SetFrame(h1, "#it{p}_{T}(GeV/#it{c})", "Probability Density");
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  tex->DrawLatex(0.16, 0.8, sLatex);
  tex->DrawLatex(0.16, 0.91, "pp at #sqrt{s} = 13 TeV");
  leg->Draw();
  gStyle->SetOptStat("");

  can->SaveAs("./figure/JetPt_OldNew.eps");
  CanvasEnd(can);
  return;
}
