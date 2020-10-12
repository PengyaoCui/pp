#include "./SourceFun.h"

void PartoKRatio(){

  TString SaveName = "LKRatio";
  TString sPath[] = {"./result"};
  TString sFile[] = {"PtSpect_ThisAna.root"};
  TString sList[] = {""};
  
  TString sK[] = {"hPtIncl_Kshort", "hPtJE_Kshort", "hPtPC_Kshort"};
  TString sP[] = {"hPtIncl_Lambda", "hPtJC_Lambda", "hPtPC_Lambda"};
  TString sA[] = {"hPtIncl_AntiLa", "hPtJC_AntiLa", "hPtPC_AntiLa"};

  TString sLeg[] = {"Incl", "JE", "PC", "OC", "NJ"};

  auto sLatex("pp at #sqrt{s} = 13 TeV");
  Double_t XMin = 0.; Double_t XMax = 12.;
  Double_t YMin = 0.; Double_t YMax = 1.5;
  //-----------------------------------
 
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;

  TFile *f = TFile::Open("./result/PKRatio.root", "UPDATE");
  can = MakeCanvas("can");

  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(sK)/sizeof(TString);
  
  TH1D* hP = nullptr;
  TH1D* hA = nullptr;
  TH1D* hK = nullptr;
  TH1D* hRatio = nullptr;


  for (Int_t i = 0; i< nHist; ++i){
    TString sMyPath = sPath[0]; 
    TString sMyFile = sFile[0]; 
    TString sMyList = sList[0]; 
    TString sMyHistP = sP[i]; 
    TString sMyHistA = sA[i]; 
    TString sMyHistK = sK[i]; 


    hP = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistP.Data());
    hP->SetName(Form("Lambda_%d", i)); 
    DeNormHistBinWidth(hP); 
    NormHistBinWidth(hP);
    
    hA = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistA.Data());
    hA->SetName(Form("Lambda_%d", i)); 
    DeNormHistBinWidth(hA); 
    hA=RebinTH1D(hA, hP);
    NormHistBinWidth(hA);
    hP->Add(hA);
    
    hK = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistK.Data());
    hK->SetName(Form("Kshort_%d", i)); 
    hK=RebinTH1D(hK, hP);
    hK->Scale(2.); 
   
    hRatio = (TH1D*) hK->Clone(Form("hRatio_%d", i)); hRatio->Reset();
    hRatio->Divide(hP, hK);
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
    SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", "#Lambda to K^{0}_{S} ratio");
  }
  //f->Close();
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
