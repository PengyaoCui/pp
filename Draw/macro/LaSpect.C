#include "./SourceFun.h"

void LaSpect(){

  const Bool_t isIncl(kTRUE);
  const Bool_t isJC(kFALSE);

  TString sPath = "/home/cuipengyao/study/pPb/Strangeness/UPDATE_wOmega/Local/Inclusive";
  //TString sPath = "./output/JE";
  TString sFile = "";
  TString sList = "";
  TString sHist = "hPtLaNormCorr";

  if(isIncl){
    sFile = "AnalysisOutputs_MakeLaFdR.root";
    sList = "listMakeLaFdR_AntiLa";
  }

  if(isJC){
    sFile = "AnalysisOutputs_FitCbinJE.root";
    sList = "listFitCbinJE_XiPos_Default_PtJ22_JC";
  }
  TString sCent[] = {"05", "510", "1020",   "2040",   "4060", "6080",  "80100"}; 
  TString sLeg[] = {"0-5%", "5-10%", "10-20%", "20-40%", "40-60%", "60-80%", "80-100"};
  //TString sCent[] = {"1040", "40100"}; 
  //TString sLeg[] = {"10-40%", "40-100%"};

  auto sLatex("#AntiLa spectra");
  Double_t YMin = 1e-12;
  Double_t YMax = 1e12;
  Double_t XMin = 0.;
  Double_t XMax = 12.;
  //-----------------------------------
  TCanvas *can = nullptr;

  TFile *f = TFile::Open("./result/PtSpect_test.root", "UPDATE");
  can = MakeCanvas("can");
  can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.7,0.9,1.0,0.6);    
  //-----------------------------------
  auto nHist = sizeof(sCent)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    TString sMyList = Form("%s_%s", sList.Data(), sCent[i].Data()); 
    TH1D* h1 = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sMyList.Data(), sHist.Data());
    h1->SetName(Form("hist_%d", i)); 
    NormHistBinWidth(h1);
    
    for(Int_t j =1; j<= h1->GetNbinsX(); j++){
      auto dBinCent = h1->GetXaxis()->GetBinCenter(j);
      auto dContent = h1->GetBinContent(j); 
      auto dError   = h1->GetBinError(j); 
      h1->SetBinContent(j, dContent/dBinCent);
      h1->SetBinError (j, dError/dBinCent);
    }
    
    f->cd(); h1->Write(Form("hPtIncl_AntiLa_%s", sCent[i].Data()), TObject::kSingleKey);
       
    //SetFrame(h1, "#it{p}_{T}", "1/#it{N}_{ev} #times (#Delta #varphi #Delta y)^{-1} #times d#it{N}/d#it{p}_{T}(#it{c}/GeV)");
    //SetFrame(h1, "#it{p}_{T}", "1/#it{N}_{ev} #times (#Delta #varphi #Delta y)^{-1} #times d#it{N}/d#it{p}_{T}(#it{c}/GeV)");
    SetFrame(h1, "#it{p}_{T}(GeV/#it{c})", "1/2#pi 1/#it{p}_{T} 1/#it{N}_{ev} d^{2}#it{N}/(d#it{p}_{T}d#it{y})(#it{c}/GeV)^{2}");
    DrawHisto(h1, cLine[i], sMark[i], "same");
    //h1->Draw("same"); 
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  f->Close();

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  tex->DrawLatex(0.16, 0.91, sLatex);
  tex->DrawLatex(0.5, 0.91, "V0A multiplicity event classes");
  tex->DrawLatex(0.16, 0.3, "0. < y_{CMS} < 0.5");
  tex->DrawLatex(0.16, 0.2, "p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  leg->Draw();
  gStyle->SetOptStat("");

  CanvasEnd(can);
  //can->SaveAs("./figure/AntiLa_Incl.eps");
  return;
}
