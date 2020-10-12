#include "./SourceFun.h"

void PartoLRatio(){

  TString SaveName = "OLRatio";
  TString sPath[] = {"./result"};
  TString sFile[] = {"PtSpect_ThisAna.root"};
  TString sList[] = {""};
  
  TString sP[] =  {"hPtIncl_Omega", "hPtJE_Omega", "hPtPC_Omega", "hPtOC_Omega", "hPtNJ_Omega"};
  TString sL0[] = {"hPtIncl_Lambda", "hPtJC_Lambda", "hPtPC_Lambda", "hPtOC_Lambda", "hPtNJ_Lambda"};
  TString sL1[] = {"hPtIncl_AntiLa", "hPtJC_AntiLa", "hPtPC_AntiLa", "hPtOC_AntiLa", "hPtNJ_AntiLa"};

  TString sLeg[] = {"Incl", "JE", "PC", "OC", "NJ"};

  auto sLatex("pp at #sqrt{s} = 13 TeV");
  Double_t XMin = 0.; Double_t XMax = 6.;
  Double_t YMin = 0.; Double_t YMax = 0.1;
  //-----------------------------------
 
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;

  TFile *f = TFile::Open("./result/PLRatio.root", "UPDATE");
  can = MakeCanvas("can");

  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(sP)/sizeof(TString);
  
  TH1D* hP = nullptr;
  TH1D* hL0 = nullptr;
  TH1D* hL1 = nullptr;
  TH1D* hRatio = nullptr;


  for (Int_t i = 0; i< nHist; ++i){
    TString sMyPath = sPath[0]; 
    TString sMyFile = sFile[0]; 
    TString sMyList = sList[0]; 
    TString sMyHistP = sP[i]; 
    TString sMyHistL0 = sL0[i]; 
    TString sMyHistL1 = sL1[i]; 


    hP = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistP.Data());
    hP->SetName(Form("Particle_%d", i)); 
    DeNormHistBinWidth(hP); 
    NormHistBinWidth(hP);
    
    hL0 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistL0.Data());
    hL0->SetName(Form("Lambda_%d", i)); 
    DeNormHistBinWidth(hL0); 
    hL0=RebinTH1D(hL0, hP);
    NormHistBinWidth(hL0);
    
    hL1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistL1.Data());
    hL1->SetName(Form("AntiLa_%d", i)); 
    DeNormHistBinWidth(hL1); 
    hL1=RebinTH1D(hL1, hP);
    NormHistBinWidth(hL1);
    hL0->Add(hL1);
   
    hRatio = (TH1D*) hP->Clone(Form("hRatio_%d", i)); hRatio->Reset();
    hRatio->Divide(hP, hL0);
    hRatio->SetName(Form("hratio_%d", i));
    f->cd(); hRatio->Write(Form("%s_%s", SaveName.Data(), sLeg[i].Data()), TObject::kSingleKey);
    
    auto dMini = hRatio->GetMinimum();
    auto dMaxi = hRatio->GetMaximum();
    //hRatio->GetYaxis()->SetRangeUser(0., 1.5*dMaxi);
    hRatio->GetXaxis()->SetRangeUser(XMin, XMax);
    hRatio->GetYaxis()->SetRangeUser(YMin, YMax);
    DrawHisto(hRatio, cLine[i], sMark[i], "same");
    leg->AddEntry(hRatio, sLeg[i], "lp");
    //SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", "#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}");
    SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", "#Omega to #Lambda ratio");
  }
  f->Close();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  CanvasEnd(can);
  //can->SaveAs(Form("./figure/ThisAna/LKRatio_woUncertainty.eps"));
  return;
}
