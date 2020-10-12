#include "inc/PyJetUtils.h"

void OC(){
//=============================================================================

  
  auto f = TFile::Open("/home/cuipengyao/study/pp/Local/ThisAna/JE/AnalysisOutputs_Results.root", "read");
  auto l04 = (TList*)f->Get(Form("listResults_Lambda_Default_OC"));
  auto lPCL = (TList*)f->Get(Form("listResults_Lambda_Default_PCL"));
  auto lPCU = (TList*)f->Get(Form("listResults_Lambda_Default_PCU"));
  f->Close();
  auto hPC = (TH1D*) lPCL->FindObject(Form("hNco"));
  auto hPCU = (TH1D*) lPCU->FindObject(Form("hNco"));
  hPC->Add(hPCU, 1.);
  hPC->Scale(0.5);
  
   
  f = TFile::Open("/home/cuipengyao/study/pp/Local/ThisAna/Uncertainty/JE/UE/OC06/AnalysisOutputs_Results.root", "read");
  auto l06 = (TList*)f->Get(Form("listResults_Lambda_Default_OC"));
  f->Close();
  f = TFile::Open("/home/cuipengyao/study/pp/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_Results.root", "read");
  auto l08 = (TList*)f->Get(Form("listResults_Lambda_Default_OC"));
  f->Close();
  
  auto h04 = (TH1D*) l04->FindObject(Form("hNco")); NormBinningHistogram(h04); 
  auto h06 = (TH1D*) l06->FindObject(Form("hNco")); NormBinningHistogram(h06); 
  auto h08 = (TH1D*) l08->FindObject(Form("hNco")); NormBinningHistogram(h08); 
  TH1D *h0 = new TH1D("h0", "", 20, 0, 2);
  TH1D *h1 = new TH1D("h1", "", 20, 0, 2);
  
  h0->SetBinContent(h0->FindBin(0.4), h04->GetBinContent(1)); h0->SetBinError(h0->FindBin(0.4), h04->GetBinError(1));
  h0->SetBinContent(h0->FindBin(0.6), h06->GetBinContent(1)); h0->SetBinError(h0->FindBin(0.6), h06->GetBinError(1));
  h0->SetBinContent(h0->FindBin(0.8), h08->GetBinContent(1)); h0->SetBinError(h0->FindBin(0.8), h08->GetBinError(1));
  h1->SetBinContent(h1->FindBin(TMath::Pi()*0.5), hPC->GetBinContent(1)); h1->SetBinError(h1->FindBin(TMath::Pi()*0.5), hPC->GetBinError(1));

//=============================================================================
  auto dflx(0.), dfux(2.);
  auto dfly(0.0), dfuy(0.1);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.30);
  
  TString stnx("#it{R}(par, jet)");
  TString stny("d#it{#rho}/d#it{p}_{T} (#it{c}/GeV)");
  SetStyle(kTRUE);
  
  auto can(MakeCanvas(Form("OC")));
  //can->SetLogy();
  can->SetGridy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(h0, wcl[0], wmk[0], "same");
  DrawHisto(h1, wcl[1], wmk[1], "same");

  auto leg(new TLegend(0.72, 0.60, 0.98, 0.92)); SetupLegend(leg);
  leg->AddEntry(h0, "OC", "LP")->SetTextSizePixels(24);
  leg->AddEntry(h1, "PC", "LP")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "pp at #sqrt{#it{s}} = 13 TeV");
  tex->DrawLatex(0.16, 0.82, "#Lambda");
  tex->DrawLatex(0.16, 0.72, "0.6< #it{p}_{T} < 1.6");
  
  can->SaveAs(Form("./figure/UEUncer/Lambda_pp13TeV_DiffOC_Bin1.eps"));
  can->SaveAs(Form("./figure/UEUncer/Lambda_pp13TeV_DiffOC_Bin1.pdf"));
  can->SaveAs(Form("./figure/UEUncer/Lambda_pp13TeV_DiffOC_Bin1.png"));
  CanvasEnd(can);
  return;
}

