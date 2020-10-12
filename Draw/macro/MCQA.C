#include "./SourceFun.h"

void MCQA(){


  TString sPath[] = {"~/study/pPb/Strangeness/Local/QAana", "~/study/pPb/Strangeness/Local/QAana", "~/study/pPb/Strangeness/Local/QAana", "~/study/pPb/Strangeness/Local/QAana"};
  TString sFile[] = {"AnalysisOutputs_Loop2ndRD.root", "AnalysisOutputs_LoopIncMC_LHC17f2a.root", "AnalysisOutputs_LoopIncMC_LHC17f2b.root", "AnalysisOutputs_LoopIncMC_LHC17d14.root"};
  TString sList[] = {"listLoop2ndRD_XiNeg_Default", "listLoopIncMC_XiNeg_Default", "listLoopIncMC_XiNeg_Default", "listLoopIncMC_XiNeg_Default"};
  TString sHistSig[] = {"BeforeBachXrowsOverFindableClusTPC", "BeforeBachXrowsOverFindableClusTPC", "BeforeBachXrowsOverFindableClusTPC", "BeforeBachXrowsOverFindableClusTPC"};
  TString sHistBkg[] = {"AfterBachXrowsOverFindableClusTPC", "AfterBachXrowsOverFindableClusTPC", "AfterBachXrowsOverFindableClusTPC", "AfterBachXrowsOverFindableClusTPC"};
  TString sLeg[] = {"RD", "LHC17f2a", "LHC17f2b", "LHC17d14"};

  auto sLatex("#Xi cut parameters distribution");
  //-----------------------------------
  TCanvas *can = nullptr;

  can = MakeCanvas("can");
  can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.2,0.9,0.4,0.7); //左上    
  //auto leg = new TLegend(0.8,0.9,0.95,0.7);//右上
  //auto leg = new TLegend(0.2,0.5,0.4,0.3); //左下
  //auto leg = new TLegend(0.8,0.5,0.95,0.3);//右下
  //-----------------------------------
  auto nHist = sizeof(sHistSig)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    //TString sMyPath = Form("%s_%s", Path.Data(), sPath[i].Data()); 
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHistSig = sHistSig[i]; 
    TString sMyHistBkg = sHistBkg[i]; 
    TH1D* h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistSig.Data());
    h1->SetName(Form("hist1_%d", i)); 
    TH1D* h2 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistBkg.Data());
    h2->SetName(Form("hist2_%d", i)); 
    h1->Add(h2, -1.);
    //h1->Rebin(5);
    h1->Scale(1./h1->GetEntries());
    //SetFrame(h1, "#it{p}_{T}", "1/2#pi 1/#it{p}_{T} 1/#it{N}_{ev}d^{2}#it{N}/(d#it{p}_{T}d#it{y})(GeV/#it{c})^{-2}");
    SetFrame(h1, sHistBkg[i], "Probability density");
    for (Int_t j = 1; j <= h1->GetNbinsX(); j++) { h1->SetBinError(j, 0.); } 
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  //tex->DrawLatex(0.16, 0.91, sLatex);
  //tex->DrawLatex(0.16, 0.8, "0-100%");
  leg->Draw();
  gStyle->SetOptStat("");

  can->SaveAs(Form("./figure/QAfor_LowPt_%s.png", sHistBkg[1].Data()));
  CanvasEnd(can);
  return;
}
