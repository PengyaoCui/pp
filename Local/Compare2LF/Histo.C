#include <TF1.h>
//#include "style.h"
void Histo(){

  Double_t const eta=0.75;
  Double_t const dCentMin=0.;
  Double_t const dCentMax=100.;

  TFile *f1    = TFile::Open("AnalysisResults_MC.root"); 
  TList *flist = (TList *)f1->Get("listCascadeMakerMC");  
  const auto hsV0   = (THnSparseD*)flist->FindObject("hsV0");
  const auto hsXi   = (THnSparseD*)flist->FindObject("hsXi");
  
  //auto iCentMin = -1.;
  //auto iCentMax = -1.;
  //iCentMin = hsXi->GetAxis(6)->FindBin(dCentMin + 1e-12);
  //iCentMax = hsXi->GetAxis(6)->FindBin(dCentMax - 1e-12);
  
  auto dEtaMin=0;
  auto dEtaMax=0;
  dEtaMin = hsXi->GetAxis(2)->FindBin(-0.5+1e-12);
  dEtaMax = hsXi->GetAxis(2)->FindBin(0.5-1e-12);
  
  auto hsKshort = (THnSparseD*)hsV0->Clone("hsKshort");
  //hsKshort->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsKshort->GetAxis(2)->SetRange(dEtaMin, dEtaMax);
  hsKshort->GetAxis(5)->SetRange(1, 1);
  auto hPtKshort =(TH1D*)hsKshort->Projection(0);
  hPtKshort->SetName(Form("Kshort")); 
  auto hPtEtaKshort0 =(TH1D*)hsKshort->Projection(1, 0);
  auto hPtEtaKshort = new TH2D("Kshort_pT_Eta", "", 1000, 0., 100., 100, -5, 5);
  for(Int_t i=1; i<=1000; i++){for(Int_t j=42; j<=80; j++){ hPtEtaKshort->SetBinContent(i, j, hPtEtaKshort0->GetBinContent(i, j-42));}}

  auto hsLambda = (THnSparseD*)hsV0->Clone("hsLambda");
  //hsLambda->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsLambda->GetAxis(2)->SetRange(dEtaMin, dEtaMax);
  hsLambda->GetAxis(5)->SetRange(2, 2);
  auto hPtLambda =(TH1D*)hsLambda->Projection(0);
  hPtLambda->SetName(Form("Lambda")); 
  auto hPtEtaLambda0 =(TH1D*)hsLambda->Projection(1, 0);
  auto hPtEtaLambda = new TH2D("Lambda_pT_Eta", "", 1000, 0., 100., 100, -5, 5);
  for(Int_t i=1; i<=1000; i++){for(Int_t j=42; j<=80; j++){ hPtEtaLambda->SetBinContent(i, j, hPtEtaLambda0->GetBinContent(i, j-42));}}
   
  auto hsAntiLa = (THnSparseD*)hsV0->Clone("hsAntiLa");
  //hsAntiLa->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsAntiLa->GetAxis(2)->SetRange(dEtaMin, dEtaMax);
  hsAntiLa->GetAxis(5)->SetRange(3, 3);
  auto hPtAntiLa =(TH1D*)hsAntiLa->Projection(0);
  hPtAntiLa->SetName(Form("AntiLa")); 
  auto hPtEtaAntiLa0 =(TH1D*)hsAntiLa->Projection(1, 0);
  auto hPtEtaAntiLa = new TH2D("AntiLa_pT_Eta", "", 1000, 0., 100., 100, -5, 5);
  for(Int_t i=1; i<=1000; i++){for(Int_t j=42; j<=80; j++){ hPtEtaAntiLa->SetBinContent(i, j, hPtEtaAntiLa0->GetBinContent(i, j-42));}}
  
  auto hXi = (THnSparseD*)hsXi->Clone("hXi");
  //hXi->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hXi->GetAxis(2)->SetRange(dEtaMin, dEtaMax);
  hXi->GetAxis(5)->SetRange(1, 2);
  auto hPtXi =(TH1D*)hXi->Projection(0);
  hPtXi->SetName(Form("Xi")); 
  auto hPtEtaXi0 =(TH1D*)hXi->Projection(1, 0);
  auto hPtEtaXi = new TH2D("Xi_pT_Eta", "", 1000, 0., 100., 100, -5, 5);
  for(Int_t i=1; i<=1000; i++){for(Int_t j=42; j<=80; j++){ hPtEtaXi->SetBinContent(i, j, hPtEtaXi0->GetBinContent(i, j-42));}}
   
  auto hsXiNeg = (THnSparseD*)hsXi->Clone("hsXiNeg");
  //hsXiNeg->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsXiNeg->GetAxis(2)->SetRange(dEtaMin, dEtaMax);
  hsXiNeg->GetAxis(5)->SetRange(1, 1);
  auto hPtXiNeg =(TH1D*)hsXiNeg->Projection(0);
  hPtXiNeg->SetName(Form("XiNeg")); 
  auto hPtEtaXiNeg0 =(TH1D*)hsXiNeg->Projection(1, 0);
  auto hPtEtaXiNeg = new TH2D("XiNeg_pT_Eta", "", 1000, 0., 100., 100, -5, 5);
  for(Int_t i=1; i<=1000; i++){for(Int_t j=42; j<=80; j++){ hPtEtaXiNeg->SetBinContent(i, j, hPtEtaXiNeg0->GetBinContent(i, j-42));}}

  auto hsXiPos = (THnSparseD*)hsXi->Clone("hsXiPos");
  //hsXiPos->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsXiPos->GetAxis(2)->SetRange(dEtaMin, dEtaMax);
  hsXiPos->GetAxis(5)->SetRange(2, 2);
  auto hPtXiPos =(TH1D*)hsXiPos->Projection(0);
  hPtXiPos->SetName(Form("XiPos")); 
  auto hPtEtaXiPos0 =(TH1D*)hsXiPos->Projection(1, 0);
  auto hPtEtaXiPos = new TH2D("XiPos_pT_Eta", "", 1000, 0., 100., 100, -5, 5);
  for(Int_t i=1; i<=1000; i++){for(Int_t j=42; j<=80; j++){ hPtEtaXiPos->SetBinContent(i, j, hPtEtaXiPos0->GetBinContent(i, j-42));}}
  
  auto hsOmega = (THnSparseD*)hsXi->Clone("hsOmega");
  //hsOmega->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsOmega->GetAxis(2)->SetRange(dEtaMin, dEtaMax);
  hsOmega->GetAxis(5)->SetRange(3, 4);
  auto hPtOmega =(TH1D*)hsOmega->Projection(0);
  hPtOmega->SetName(Form("Omega")); 
  auto hPtEtaOmega0 =(TH1D*)hsOmega->Projection(1, 0);
  auto hPtEtaOmega = new TH2D("Omega_pT_Eta", "", 1000, 0., 100., 100, -5, 5);
  for(Int_t i=1; i<=1000; i++){for(Int_t j=42; j<=80; j++){ hPtEtaOmega->SetBinContent(i, j, hPtEtaOmega0->GetBinContent(i, j-42));}}
  
  auto hsOmegaNeg = (THnSparseD*)hsXi->Clone("hsOmegaNeg");
  //hsOmegaNeg->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsOmegaNeg->GetAxis(2)->SetRange(dEtaMin, dEtaMax);
  hsOmegaNeg->GetAxis(5)->SetRange(3, 3);
  auto hPtOmegaNeg =(TH1D*)hsOmegaNeg->Projection(0);
  hPtOmegaNeg->SetName(Form("OmegaNeg")); 
  auto hPtEtaOmegaNeg0 =(TH1D*)hsOmegaNeg->Projection(1, 0);
  auto hPtEtaOmegaNeg = new TH2D("OmegaNeg_pT_Eta", "", 1000, 0., 100., 100, -5, 5);
  for(Int_t i=1; i<=1000; i++){for(Int_t j=42; j<=80; j++){ hPtEtaOmegaNeg->SetBinContent(i, j, hPtEtaOmegaNeg0->GetBinContent(i, j-42));}}

  auto hsOmegaPos = (THnSparseD*)hsXi->Clone("hsOmegaPos");
  //hsOmegaPos->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsOmegaPos->GetAxis(2)->SetRange(dEtaMin, dEtaMax);
  hsOmegaPos->GetAxis(5)->SetRange(4, 4);
  auto hPtOmegaPos =(TH1D*)hsOmegaPos->Projection(0);
  hPtOmegaPos->SetName(Form("OmegaPos")); 
  auto hPtEtaOmegaPos0 =(TH1D*)hsOmegaPos->Projection(1, 0);
  auto hPtEtaOmegaPos = new TH2D("OmegaPos_pT_Eta", "", 1000, 0., 100., 100, -5, 5);
  for(Int_t i=1; i<=1000; i++){for(Int_t j=42; j<=80; j++){ hPtEtaOmegaPos->SetBinContent(i, j, hPtEtaOmegaPos0->GetBinContent(i, j-42));}}

//================================================================================================

  TFile *output = TFile::Open("histos.root","RECREATE"); TList *listxx = new TList();
  listxx->Add(hPtKshort);
  listxx->Add(hPtLambda);
  listxx->Add(hPtAntiLa);
  listxx->Add(hPtXi);
  listxx->Add(hPtXiNeg);
  listxx->Add(hPtXiPos);
  listxx->Add(hPtOmega);
  listxx->Add(hPtOmegaNeg);
  listxx->Add(hPtOmegaPos);
  listxx->Add(hPtEtaKshort);
  listxx->Add(hPtEtaLambda);
  listxx->Add(hPtEtaAntiLa);
  listxx->Add(hPtEtaXi);
  listxx->Add(hPtEtaXiNeg);
  listxx->Add(hPtEtaXiPos);
  listxx->Add(hPtEtaOmega);
  listxx->Add(hPtEtaOmegaNeg);
  listxx->Add(hPtEtaOmegaPos);

  output->cd(); listxx->Write(); output->Close();

}

TH1D *GetTH1D(char *file,char *list , char * name){

  TFile *f1  = TFile::Open(file);
  if(list){
    TList *flist = (TList *)f1->Get(list);
    cout<<(TH1D*)flist->FindObject(name)<<endl;
    return (TH1D*)flist->FindObject(name);
  }else{

    return (TH1D*)f1->Get(name);
  }
 cout<<(TH1D*)f1->Get(name)<<endl;
}
