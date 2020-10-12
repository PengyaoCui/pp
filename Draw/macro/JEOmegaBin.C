#include "./SourceFun.h"

void JEOmegaBin(TString sType = "Kshort"){

  
  Bool_t IsIncl(0);	
  Bool_t   IsJC(1);	
  Bool_t   IsPC(1);	
  Bool_t   IsOC(1);	
  Bool_t   IsNJ(1);	
  TString sPath = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins";
  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = "listResults";
  TString sHist = "hNco";
  if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda" || sType == "AntiLa") sList = "listMakeLaFdR";
  if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";

  TString sLeg[] = {"Inclusive", "JC", "UE", "JE"};
  
  TString sLatex(Form("%s spectra", sType.Data()));
  //-----------------------------------
  TCanvas *can = nullptr;
  gStyle->SetOptStat("");

  auto tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  

  //-----------------------------------
  TH1D *hJC = nullptr;
  TH1D *hPC = nullptr;
  TH1D *hOC = nullptr;
  can = MakeCanvas(Form("can"));
  can->SetLogy();
  can->SetGridx(); can->SetGridy();
  auto leg = new TLegend(0.7,0.9,1.0,0.6);    
  SetLegend(leg);
  
  if(IsIncl){
    TString sInclList = Form("%s_%s_Default", sList.Data(), sType.Data());
    auto hIncl = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sInclList.Data(), sHist.Data());
    hIncl->SetName(Form("hIncl")); 
    NormHistBinWidth(hIncl);
    hIncl->GetYaxis()->SetRangeUser(1e-7, 1.); 
    //hIncl->GetXaxis()->SetRangeUser(1., 7.); 
    SetFrame(hIncl, "#it{p}_{T}(GeV/c)", "d#rho/d#it{p}_{T}");
    DrawHisto(hIncl, cLine[0], sMark[0], "same");
    leg->AddEntry(hIncl , "Inclusive","lp");
    TFile *f = TFile::Open("./result/PtSpect_ThisAna.root", "UPDATE");
    if(sType != "Omega") f->cd(); hIncl->Write(Form("hPtIncl_%s_OmegaBin", sType.Data()), TObject::kSingleKey); f->Close();
    if(sType == "Omega") f->cd(); hIncl->Write(Form("hPtIncl_%s", sType.Data()), TObject::kSingleKey); f->Close();
  }
  
  if(IsJC){
    TString sJCList = Form("%s_%s_Default_JC", sList.Data(), sType.Data()); 
    hJC = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sJCList.Data(), sHist.Data());
    hJC->SetName(Form("hJC")); 
    hJC->GetYaxis()->SetRangeUser(1e-7, 1.); 
    //hJC->GetXaxis()->SetRangeUser(0., 12.); 
    NormHistBinWidth(hJC);
    SetFrame(hJC, "#it{p}_{T}(GeV/c)", "d#rho/d#it{p}_{T}(#it{c}/GeV)");
    DrawHisto(hJC, cLine[3], sMark[3], "same");
    leg->AddEntry(hJC , "JC","lp");
    TFile *f = TFile::Open("./result/PtSpect_ThisAna.root", "UPDATE");
    if(sType != "Omega"){ f->cd(); hJC->Write(Form("hPtJC_%s_OmegaBin", sType.Data()), TObject::kSingleKey); f->Close();}
    if(sType == "Omega"){ f->cd(); hJC->Write(Form("hPtJC_%s", sType.Data()), TObject::kSingleKey); f->Close();}
  } 
  
  if(IsPC){
    TString sPCLList = Form("%s_%s_Default_PCL", sList.Data(), sType.Data()); 
    auto hPCL = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sPCLList.Data(), sHist.Data());
    hPCL->SetName(Form("hPCL")); 
    
    TString sPCUList = Form("%s_%s_Default_PCU", sList.Data(), sType.Data()); 
    auto hPCU = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sPCLList.Data(), sHist.Data());
    hPCU->SetName(Form("hPCU")); 
    hPC = (TH1D*)hPCL->Clone(Form("hPC")); hPC->Reset(); 
    hPC->Add(hPCL, hPCU, 0.5, 0.5); 
    NormHistBinWidth(hPC);
    hPC->GetYaxis()->SetRangeUser(1e-7, 1.); 
    SetFrame(hPC, "#it{p}_{T}(GeV/c)", "d#rho/d#it{p}_{T}(#it{c}/GeV)");
    DrawHisto(hPC, cLine[2], sMark[2], "same");
    leg->AddEntry(hPC , "PC","lp");
    TFile *f = TFile::Open("./result/PtSpect_ThisAna.root", "UPDATE");
    if(sType != "Omega") {f->cd(); hPC->Write(Form("hPtPC_%s_OmegaBin", sType.Data()), TObject::kSingleKey); f->Close();}
    if(sType == "Omega") {f->cd(); hPC->Write(Form("hPtPC_%s", sType.Data()), TObject::kSingleKey); f->Close();}
  }
  
  if(IsOC){
    TString sOCList = Form("%s_%s_Default_OC", sList.Data(), sType.Data()); 
    hOC = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sOCList.Data(), sHist.Data());
    hOC->SetName(Form("hOC")); 
    NormHistBinWidth(hOC);
    hOC->GetYaxis()->SetRangeUser(1e-7, 1.); 
    SetFrame(hOC, "#it{p}_{T}(GeV/c)", "d#rho/d#it{p}_{T}(#it{c}/GeV)");
    DrawHisto(hOC, cLine[4], sMark[4], "same");
    leg->AddEntry(hOC , "OC","lp");
    TFile *f = TFile::Open("./result/PtSpect_ThisAna.root", "UPDATE");
    if(sType != "Omega"){ f->cd(); hOC->Write(Form("hPtOC_%s_OmegaBin", sType.Data()), TObject::kSingleKey); f->Close();}
    if(sType == "Omega"){ f->cd(); hOC->Write(Form("hPtOC_%s", sType.Data()), TObject::kSingleKey); f->Close();}
  } 
  
  if(IsJC && IsPC){
    auto hJE = (TH1D*)hJC->Clone(Form("hJE"));
    hJE->Add(hPC, -1.); 
    leg->AddEntry(hJE , "JE","lp");
    hJE->GetYaxis()->SetRangeUser(1e-7, 1.); 
    SetFrame(hJE, "#it{p}_{T}(GeV/c)", "d#rho/d#it{p}_{T}(#it{c}/GeV)");
    DrawHisto(hJE, cLine[1], sMark[1], "same");
    TFile *f = TFile::Open("./result/PtSpect_ThisAna.root", "UPDATE");
    if(sType != "Omega") {f->cd(); hJE->Write(Form("hPtJE_%s_OmegaBin", sType.Data()), TObject::kSingleKey); f->Close();}
    if(sType == "Omega") {f->cd(); hJE->Write(Form("hPtJE_%s", sType.Data()), TObject::kSingleKey); f->Close();}
  } 
  
  if(IsNJ){
    TString sNJList = Form("%s_%s_Default_NJ", sList.Data(), sType.Data()); 
    auto hNJ = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sNJList.Data(), sHist.Data());
    hNJ->SetName(Form("hNJ")); 
    NormHistBinWidth(hNJ);
    hNJ->GetYaxis()->SetRangeUser(1e-7, 1.); 
    SetFrame(hNJ, "#it{p}_{T}(GeV/c)", "d#rho/d#it{p}_{T}(#it{c}/GeV)");
    DrawHisto(hNJ, cLine[5], sMark[5], "same");
    leg->AddEntry(hNJ , "NJ","lp");
    TFile *f = TFile::Open("./result/PtSpect_ThisAna.root", "UPDATE");
    if(sType != "Omega") {f->cd(); hNJ->Write(Form("hPtNJ_%s_OmegaBin", sType.Data()), TObject::kSingleKey); f->Close();}
    if(sType == "Omega") {f->cd(); hNJ->Write(Form("hPtNJ_%s", sType.Data()), TObject::kSingleKey); f->Close();}
  } 
     
  tex->DrawLatex(0.16, 0.91, sLatex);
  tex->DrawLatex(0.16, 0.3, "|#eta| < 0.75");
  //tex->DrawLatex(0.16, 0.3, "|y| < 0.5");
  tex->DrawLatex(0.16, 0.2, "pp #sqrt{#it{s}} = 13 TeV");
  leg->Draw();
  //can->SaveAs(Form("./figure/ThisAna/%s_woUncertainty.eps", sType.Data()));
  CanvasEnd(can);
  



  return;
}

#if 0
over pT center each bins
for(Int_t j =1; j<= h1->GetNbinsX(); j++){
  auto dBinCent = h1->GetXaxis()->GetBinCenter(j);
  auto dContent = h1->GetBinContent(j); 
  auto dError   = h1->GetBinError(j); 
  h1->SetBinContent(j, dContent/dBinCent);
  h1->SetBinError (j, dError/dBinCent);
}
#endif 
