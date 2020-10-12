#include "./SourceFun.h"

void Ratio(){

  const TString sRatio = "New/Old";
  TString sPathNu[] = {"/home/cuipengyao/study/pp/Local/16l_wNewPileup/JE_7Bins"};
  TString sFileNu[] = {"AnalysisOutputs_LoopJetRD.root"};
  TString sListNu[] = {"listLoopJetRD_Lambda_Default_JC"};
  TString sHistNu[] = {"hJetPtAfter"};

  TString sPathDe = "/home/cuipengyao/study/QM2018_pp/Cascade_LHC16k/JC_AddJetPt";
  TString sFileDe = "AnalysisOutputs_LoopJetRD.root";
  TString sListDe = "listLoopJetRD_Xi_Default_PtJ22_JC";
  TString sHistDe = "hJetPtAfter";

  TString sLeg[] = {"16l(New FW)", "16k(Old FW)"};

  auto sLatex(Form("Jet #it{p}_{T} distrubution"));
  Double_t XMin = 0.;
  Double_t XMax = 100.;
  //-----------------------------------
  TCanvas *can = nullptr;
  TPad *padT = nullptr;
  TPad *padB = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;

  can = MakeCanvas("can");
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(sHistNu)/sizeof(TString);
  const auto nhist = nHist;

  TH1D* h2 = nullptr;
  TH1D* h1 = nullptr;
  TH1D* h11 = nullptr;
  TH1D* hRatio = nullptr;

  padB = MakePadB("padB");
  can->cd();
  padT = MakePadT("padT");
  padT->SetLogy(); 

  Double_t dBin[] = {10., 11., 12., 13., 14., 15., 16., 17., 18., 19., 20., 21., 22., 23., 24., 25., 26., 27., 28., 29., 30., 32., 34., 36., 38., 40., 42., 44., 46., 48., 50., 56., 64., 74., 85., 100.};
  Int_t nBin = sizeof(dBin)/sizeof(Double_t) - 1;
  TH1D *hPtJet = new TH1D("hPtJet", "", nBin, dBin);


  h2 = (TH1D*)GetTH1D(sPathDe.Data(), sFileDe.Data(), sListDe.Data(), sHistDe.Data());
  h2->SetName("h2_De");
  h2->SetTitle("");
  h2->Scale(1./h2->Integral(1, h2->GetNbinsX()));
  h2=RebinTH1D(h2, hPtJet);
  NormHistBinWidth(h2); 
  //cout<<h2->GetXaxis()->GetBinLowEdge(1)<<endl;
  padT->cd();
  h2->GetXaxis()->SetRangeUser(XMin, XMax);
  h2->GetYaxis()->SetRangeUser(1e-6, 10.);
  h2->SetMarkerSize(1);
  DrawHisto(h2, cLine[nHist], sMark[nHist], "same");
  SetFrame(h2, "#it{p}_{T}", "Probability Density");
  leg->AddEntry(h2, sLeg[nHist],"lp");


  for (Int_t i = 0; i< nHist; ++i){
    TString sMyPath = sPathNu[i]; 
    TString sMyFile = sFileNu[i]; 
    TString sMyList = sListNu[i]; 
    TString sMyHist = sHistNu[i]; 
    h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i)); 
    h1->Scale(1./h1->Integral(1, h1->GetNbinsX()));
    h1=RebinTH1D(h1, h2);
    NormHistBinWidth(h1); 
    hRatio = (TH1D*) h2->Clone(Form("hRatio_%d", i)); hRatio->Reset();
    hRatio->Divide(h1, h2);
    hRatio->SetName(Form("hratio_%d", i));
    hRatio->GetYaxis()->SetRangeUser(0.7, 1.3);
    padT->cd();
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1, sLeg[i], "lp");
    padB->cd();
    padB->SetGridy();
    DrawHisto(hRatio, cLine[i], sMark[i], "same");
    SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", sRatio, 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
  }


  padB->cd();
  //TLine* l = new TLine(XMin, 1., XMax, 1.);
  //l->SetLineColor(kRed);
  //l->SetLineWidth(2);
  //l->Draw("same");

  padT->cd();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/JetPt_NewOld.eps"));
  CanvasEnd(can);
  return;
}
