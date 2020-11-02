#include "./inc/SourceFun.h"

void UEUncer(const TString sType = "Xi"){
  
  TString sPath = Form("/home/cuipengyao/study/pp/Local/ThisAna/JE/%s", sType.Data()); 
  if(sType == "Omega") sPath = Form("/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins/%s", sType.Data()); 
  TString sPC[] = {"PC02", "PC06"};
  TString sUncerPath[2];
  for(Int_t i = 0; i<=1; i++){
    sUncerPath[i] = Form("/home/cuipengyao/study/pp/Local/ThisAna/Uncertainty/JE/UE/%s", sPC[i].Data());
    if(sType == "Omega") sUncerPath[i] = Form("/home/cuipengyao/study/pp/Local/ThisAna/Uncertainty/JE_Omega/UE/%s", sPC[i].Data());
  }
  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = "listResults";
  TString sHist = "hNco";

  TString List = Form("%s_%s_Default_JC", sList.Data(), sType.Data());
  TString PCLList = Form("%s_%s_Default_PCL", sList.Data(), sType.Data());
  TString PCUList = Form("%s_%s_Default_PCU", sList.Data(), sType.Data());
  
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
  TH1D* h3 = nullptr;
  TH1D* hUE[3];//PC02, PC06, PC04
  TH1D* hue = nullptr;
  h1 = (TH1D*)GetTH1D(sPath, sFile, List, sHist);
  h1->SetName("JC");
  NormHistBinWidth(h1); 
  h1->SetTitle("");
  h2 = (TH1D*)h1->Clone("h2");h2->Reset(); 
  h3 = (TH1D*)h1->Clone("h3");h3->Reset(); 
  
  hUE[2] = (TH1D*)GetTH1D(sPath, sFile, PCLList, sHist);
  hue = (TH1D*)GetTH1D(sPath, sFile, PCUList, sHist);hue->SetName("uePC04");
  hUE[2]->Add(hue);
  hUE[2]->Scale(0.5);
  NormHistBinWidth(hUE[2]); 
 
  for(Int_t i = 0; i<=1; i++){
    hUE[i] = (TH1D*)GetTH1D(sUncerPath[i], sFile, PCLList, sHist);
    hue = (TH1D*)GetTH1D(sUncerPath[i], sFile, PCUList, sHist); hue->SetName(Form("ue%s", sPC[i].Data()));
    hUE[i]->Add(hue);
    hUE[i]->Scale(0.5);
    NormHistBinWidth(hUE[i]); 
  } 

  for(Int_t i = 1; i<=h1->GetNbinsX(); i++){
    auto V1 = h1->GetBinContent(i);
    auto E1 = h1->GetBinError(i);
    auto V2 = hUE[2]->GetBinContent(i); //PC04
    auto E2 = hUE[2]->GetBinError(i);

    auto V3 = hUE[0]->GetBinContent(i); //PC02
    auto E3 = hUE[0]->GetBinError(i);
    auto V4 = hUE[1]->GetBinContent(i); //PC06
    auto E4 = hUE[1]->GetBinError(i);
    h2->SetBinContent(i, TMath::Abs(V3-V2)/(TMath::Sqrt(12.)*(V1-V2))); 
    h2->SetBinError(i, TMath::Sqrt(E3*E3 + E2*E2)/TMath::Sqrt(12.)); 
    h3->SetBinContent(i, TMath::Abs(V4-V2)/(TMath::Sqrt(12.)*(V1-V2))); 
    h3->SetBinError(i, TMath::Sqrt(E4*E4 + E2*E2)/TMath::Sqrt(12.)); 
  }

  TH1D* hU[] = {h2, h3};
  auto hUMax = (TH1D*)MaxHistograms(2, hU);
  DrawHisto(hUMax, cLine[0], sMark[0], "same");
  SetFrame(hUMax, "#it{p}_{T}(GeV/#it{c})", "Relative syst. on UE");
  hUMax->GetYaxis()->SetRangeUser(0, 1.05);
  leg->AddEntry(hUMax, "Max","l");
   
  TFile *f = TFile::Open("./result/UEUncer.root", "UPDATE");
  TList *l = new TList();
  l->Add(hUMax);
  l->Write(Form("%s_UESub",sType.Data()), TObject::kSingleKey);
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
