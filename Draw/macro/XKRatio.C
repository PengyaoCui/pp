#include "./SourceFun.h"

void XKRatio(){


  TString sPath = "./result";
  TString sFile = "PtSpect_Eta_Full.root";
  TString sList = "";
  
  TString sK[] = {"hPtIncl_Kshort", "hPtPC_Kshort", "hPtJE_Kshort"};
  TString sL[] = {"hPtIncl_Omega", "hPtPC_Omega", "hPtJE_Omega"};
 

  TString sLeg[] = {"Incl", "PC", "JE"};

  auto sLatex("Inclusive #Xi to K^{0}_{S} ratio");
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
  auto nHist = sizeof(sK)/sizeof(TString);
  
  TH1D* hL = nullptr;
  TH1D* hA = nullptr;
  TH1D* hK = nullptr;
  TH1D* hRatio = nullptr;

  //Double_t dBin[] = {0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 4.2, 6.0, 8.0};
  //Int_t nBin = sizeof(dBin)/sizeof(Double_t) - 1;
  //auto *h = new TH1D("h", "", nBin, dBin);

  for (Int_t i = 0; i< nHist; ++i){
      TString sMyPath = sPath; 
      TString sMyFile = sFile; 
      TString sMyList = sList; 
      TString sMyHistL = sL[i]; 
      TString sMyHistK = sK[i]; 

      hK = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistK.Data());
      hK->SetName(Form("Kshort_%d", i)); 
      DeNormHistBinWidth(hK); 
      //hK=RebinTH1D(hK, h);
      hK->Scale(2.); 

      hL = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistL.Data());
      hL->SetName(Form("Xi_%d", i)); 
      DeNormHistBinWidth(hL); 
      hL=RebinTH1D(hL, hK);
      
      hRatio = (TH1D*) hK->Clone(Form("hRatio_%d", i)); hRatio->Reset();
      hRatio->Divide(hL, hK);
      hRatio->SetName(Form("hratio_%d", i));
      //f->cd(); hRatio->Write(Form("LKRatio"), TObject::kSingleKey);
      
      auto dMini = hRatio->GetMinimum();
      auto dMaxi = hRatio->GetMaximum();
      //hRatio->GetYaxis()->SetRangeUser(0.8*dMini, 1.2*dMaxi);
      hRatio->GetXaxis()->SetRangeUser(XMin, XMax);
      hRatio->GetYaxis()->SetRangeUser(0., 1.);
      DrawHisto(hRatio, cLine[i], sMark[i], "same");
      leg->AddEntry(hRatio, sLeg[i], "lp");
      SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", "#frac{#Xi + #bar{#Xi}}{2K^{0}_{S}}");
  }
  //f->Close();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  CanvasEnd(can);
  //can->SaveAs(Form("./figure/XitoKshortRatio_PC.eps"));
  return;
}
