#include "./inc/SourceFun.h"

void UEUncer_NonSub(const TString sType = "Xi"){
  
  TString sPath = Form("/home/cuipengyao/study/pp/Local/ThisAna/JE/%s", sType.Data()); 
  if(sType == "Omega") sPath = Form("/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins/%s", sType.Data()); 
  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = "listResults";
  TString sHist = "hNco";
  //if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  //if(sType == "Lambda" || sType == "AntiLa") sList = "listMakeLaFdR";
  //if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";
  TString List = Form("%s_%s_Default_JC", sList.Data(), sType.Data());
  TString OCList = Form("%s_%s_Default_OC", sList.Data(), sType.Data());
  TString PCLList = Form("%s_%s_Default_PCL", sList.Data(), sType.Data());
  TString PCUList = Form("%s_%s_Default_PCU", sList.Data(), sType.Data());
  TString NJList = Form("%s_%s_Default_NJ", sList.Data(), sType.Data());

  TString sLeg = "Total";

  auto sLatex(Form("Uncertainty of %s", sType.Data()));
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------

  TH1D* h1 = nullptr;
  TH1D* h2 = nullptr;
  TH1D* hUE0 = nullptr;//PC
  TH1D* hUE00 = nullptr;
  TH1D* hUE1 = nullptr;//OC
  TH1D* hUE2 = nullptr;//NJ
  h1 = (TH1D*)GetTH1D(sPath, sFile, List, sHist);
  h1->SetName("JC");
  NormHistBinWidth(h1); 
  h1->SetTitle("");
  h2 = (TH1D*)h1->Clone("h2");h2->Reset(); 
  hUE0 = (TH1D*)GetTH1D(sPath, sFile, PCLList, sHist);
  hUE00 = (TH1D*)GetTH1D(sPath, sFile, PCUList, sHist);
  hUE0->Add(hUE00);
  hUE0->Scale(0.5);
  NormHistBinWidth(hUE0); 
  hUE1 = (TH1D*)GetTH1D(sPath, sFile, OCList, sHist);
  NormHistBinWidth(hUE1); 
  hUE2 = (TH1D*)GetTH1D(sPath, sFile, NJList, sHist);
  NormHistBinWidth(hUE2); 
  for(Int_t i = 1; i<=h1->GetNbinsX(); i++){
    auto V1 = h1->GetBinContent(i);
    auto E1 = h1->GetBinError(i);
    auto V2 = hUE0->GetBinContent(i); 
    auto E2 = hUE0->GetBinError(i);

    auto V3 = hUE1->GetBinContent(i); 
    auto E3 = hUE1->GetBinError(i);
    auto V4 = hUE2->GetBinContent(i); 
    auto E4 = hUE2->GetBinError(i);
    //h2->SetBinContent(i, TMath::Abs(V3-V2)/TMath::Sqrt(12.)); 
    //h2->SetBinError(i, TMath::Sqrt(E3*E3 + E2*E2)/TMath::Sqrt(12.)); 
    h2->SetBinContent(i, TMath::Abs(V2)/2.); 
    h2->SetBinError(i, E2/2.); 
  }
  //h2->SetBinContent(h1->GetNbinsX(), 0); 
  //h2->SetBinError(h1->GetNbinsX(), 0); 

  auto hUMax = (TH1D*)h2->Clone("hMax");
  DrawHisto(hUMax, cLine[0], sMark[0], "same");
  SetFrame(hUMax, "#it{p}_{T}(GeV/#it{c})", "Relative syst. on UE");
  hUMax->GetYaxis()->SetRangeUser(0, 0.05);
  leg->AddEntry(hUMax, "Max","l");
   
  TFile *f = TFile::Open("./result/UEUncer.root", "UPDATE");
  TList *l = new TList();
  l->Add(hUMax);
  l->Write(Form("%s_UESub_NonSub",sType.Data()), TObject::kSingleKey);
  f->Close();

  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/Uncert/%s_UESub_%s%s_OCNJ.pdf", sType.Data(), CentMin.Data(), CentMax.Data()));
  CanvasEnd(can);
  return;
}
