#include "./SourceFun.h"

void XLRatio(){


  TString sPath = "./result";
  TString sFile = "PtSpect_Eta_Full.root";
  TString sList = "";
  
  TString sX[] = {"hPtIncl_Xi", "hPtJE_Xi", "hPtPC_Xi"};
  TString sL[] = {"hPtIncl_Lambda", "hPtJC_Lambda", "hPtPC_Lambda"};
  TString sA[] = {"hPtIncl_AntiLa", "hPtJC_AntiLa", "hPtPC_AntiLa"};
 
  TString sLeg[] = {"Incl", "JE", "UE"};

  auto sLatex("40-100%  #Xi to #Lambda ratio");
  Double_t XMin = 0.6;
  Double_t XMax = 12;
  //-----------------------------------
 
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;

  //TFile *f = TFile::Open("./result/PtSpect_HalfStat_Final.root", "UPDATE");
  can = MakeCanvas("can");

  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(sX)/sizeof(TString);
  
  TH1D* hL = nullptr;
  TH1D* hA = nullptr;
  TH1D* hX = nullptr;
  TH1D* hRatio = nullptr;

  //Double_t dBin[] = {0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 4.2, 6.0, 8.0};
  //Int_t nBin = sizeof(dBin)/sizeof(Double_t) - 1;
  //auto *h = new TH1D("h", "", nBin, dBin);

  for (Int_t i = 0; i< nHist; ++i){
    for(Int_t j = 0; j< sizeof(sX)/sizeof(TString); ++j){
      TString sMyPath = sPath; 
      TString sMyFile = sFile; 
      TString sMyList = sList; 
      TString sMyHistL = sL[j]; 
      TString sMyHistA = sA[j]; 
      TString sMyHistX = sX[j]; 

      hX = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistX.Data());
      hX->SetName(Form("Xi_%d%d", i, j)); 
      //DeNormHistBinWidth(hX); 
      //hX=RebinTH1D(hX, h);

      hL = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistL.Data());
      hL->SetName(Form("Lambda_%d%d", i, j)); 
      //DeNormHistBinWidth(hL); 
      //hL=RebinTH1D(hL, hX);
      
      hA = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistA.Data());
      hA->SetName(Form("AntiLa_%d%d", i, j)); 
      //DeNormHistBinWidth(hA); 
      //hA=RebinTH1D(hA, hX);
      hL->Add(hA);
      
      hRatio = (TH1D*) hX->Clone(Form("hRatio_%d", i)); hRatio->Reset();
      hRatio->Divide(hX, hL);
      hRatio->SetName(Form("hratio_%d%d", i, j));
      //f->cd(); hRatio->Write(Form("XLRatio"), TObject::kSingleKey);
      
      auto dMini = hRatio->GetMinimum();
      auto dMaxi = hRatio->GetMaximum();
      hRatio->GetYaxis()->SetRangeUser(0.0, 0.5);
      hRatio->GetXaxis()->SetRangeUser(0.0, 12.);
      DrawHisto(hRatio, cLine[j], sMark[j], "same");
      leg->AddEntry(hRatio, sLeg[j], "lp");
      SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", "#Xi/#Lambda");
    }
  }
  //f->Close();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  CanvasEnd(can);
  //can->SaveAs(Form("./figure/XitoLambdaRatio_40100.eps"));
  return;
}
