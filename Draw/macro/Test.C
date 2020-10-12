#include "./SourceFun.h"

void Test(){
  auto Path = "~/study/pp/woJet/15f";
  auto File = "";
  TString sPath[] = {Path, Path, Path};
  TString sFile[] = {"AnalysisOutputs_FitCbinRD.root", "AnalysisOutputs_FitCbinMC.root", "AnalysisOutputs_EffInclMC.root"};
  TString sList[] = {"listFitCbinRD_XiNeg_Default", "listFitCbinMC_XiNeg_Default", "listEffInclMC_XiNeg_Default"};
  TString sHist[] = {"hS", "hS", "hPtKine"};
  TString sLeg[] = {"Incl", "MCRec", "MCGen"}; 

  auto sLatex("Kshort efficiency distribution");
  //-----------------------------------
  TCanvas *can = nullptr;

  can = MakeCanvas("can");
  //can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.8,0.9,1.0,0.65);    
  //-----------------------------------
  auto nHist = sizeof(sHist)/sizeof(TString);
  //Double_t dEvent[] = {6.983306e7, 3468210.};
  Double_t dEvent[] = {6.983306e7, 3410782};
  for (Int_t i = 0; i< nHist; i++){
    //TString sMyPath = Form("%s_%s", Path.Data(), sPath[i].Data()); 
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    TH1D* h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i));
    //for(int j =1; j<=h1->GetNbinsX(); j++){cout<<h1->GetBinLowEdge(j)<<endl;}
    h1->Scale(1./h1->Integral(1, h1->GetNbinsX()));
    NormHistBinWidth(h1);
    auto dMini = h1->GetMinimum(); 
    auto dMaxi = h1->GetMaximum(); 
    //h1->GetXaxis()->SetRangeUser(0.6, 12.);
    //h1->GetYaxis()->SetRangeUser(0., 0.6);
    h1->SetTitle(""); 
    SetFrame(h1, "#it{p}_{T}(GeV/#it{c})", "Efficiency");
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  tex->DrawLatex(0.16, 0.91, sLatex);
  tex->DrawLatex(0.26, 0.3, "|#eta| < 0.75");
  tex->DrawLatex(0.26, 0.2, "p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  leg->Draw();
  gStyle->SetOptStat("");

  //can->SaveAs("./figure/Kshort_Efficiency_JCandIncl.eps");
  CanvasEnd(can);
  return;
}
