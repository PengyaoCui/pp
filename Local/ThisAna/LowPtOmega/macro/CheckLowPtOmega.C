#include "inc/PyJetUtils.h"

void CheckLowPtOmega(){

  auto f = TFile::Open("../AnalysisOutputs_Results.root", "read");
  auto l = (TList*)f->Get(Form("listResults_Omega_Default"));
  f->Close();
  TH1D *hSco = (TH1D*)l->FindObject(Form("hSco"));
  TH1D *hSuc = (TH1D*)l->FindObject(Form("hSuc"));
  TH1D *hEff = (TH1D*)l->FindObject(Form("hEff"));

  Double_t nSco1 = hSco->GetBinContent(1);
  Double_t nSco2 = hSco->GetBinContent(2);

  Double_t nSuc1 = hSuc->GetBinContent(1);
  Double_t nSuc2 = hSuc->GetBinContent(2);

  Double_t nEff1 = hEff->GetBinContent(1);
  Double_t nEff2 = hEff->GetBinContent(2);

  f = TFile:: Open("./AnalysisOutputs_Results.root", "read");
  l = (TList*)f->Get(Form("listResults_Omega_Default"));
  f->Close();
  TH1D *hSco0 = (TH1D*)l->FindObject(Form("hSco"));
  TH1D *hSuc0 = (TH1D*)l->FindObject(Form("hSuc"));
  TH1D *hEff0 = (TH1D*)l->FindObject(Form("hEff"));

  Double_t nSco0 = hSco0->GetBinContent(1);
  Double_t nSuc0 = hSuc0->GetBinContent(1);
  Double_t nEff0 = hEff0->GetBinContent(1);
  
  cout << "Corrected Yeild 0 = "<< nSco0 <<", " << "Raw Yeild 0 = "<< nSuc0 <<", "<< "Efficiency 0 = "<< nEff0 <<endl;
  cout << "Corrected Yeild 1 = "<< nSco1 <<", " << "Raw Yeild 1 = "<< nSuc1 <<", "<< "Efficiency 1 = "<< nEff1 <<endl;
  cout << "Corrected Yeild 2 = "<< nSco2 <<", " << "Raw Yeild 2 = "<< nSuc2 <<", "<< "Efficiency 2 = "<< nEff2 <<endl;
  


  return;
}

