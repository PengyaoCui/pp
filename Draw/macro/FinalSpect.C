#include "./SourceFun.h"

void FinalSpect(const TString sType = "Kshort", const Bool_t IsSum = kFALSE){
  
  auto sPath = "./result"; 
  auto sCFile = "PtSpect_ThisAna.root";
  
  auto sCInclHist = Form("hPtIncl_%s", sType.Data());
  auto sCJetHist = Form("hPtJE_%s", sType.Data());
  auto sCJCHist = Form("hPtJC_%s", sType.Data());
  if(sType == "Lambda" || sType == "AntiLa") sCJetHist = Form("hPtJC_%s", sType.Data());
  auto sCUEHist = Form("hPtPC_%s", sType.Data());
  auto sCOCHist = Form("hPtOC_%s", sType.Data());
  auto sCNJHist = Form("hPtNJ_%s", sType.Data());
  
  auto sEFile = "UncertaintyTot.root";
  auto sEList = Form("%s_UncerTot", sType.Data());
  auto sEIHist = "hIErr";  
  auto sEJHist = "hJErr";  
  auto sEUHist = "hUErr";  
  auto sEJCHist = "hJCErr";  

  auto sLatex(Form("pp #sqrt{#it{s}} = 13 TeV"));
 
  Double_t XMin = 0.;
  Double_t XMax;
  Double_t YMin;
  Double_t YMax;

  if(sType == "Kshort"){ XMax = 12.; YMax = 100.; YMin = 1e-6;}
  if(sType == "Lambda" || sType == "AntiLa"){ XMax = 12.; YMax = 70.; YMin = 1e-7;}
  if(sType == "Xi"){ XMax = 8.; YMax = 10.; YMin = 1e-6;}
  if(sType == "Omega"){ XMax = 5.; YMax = 1e-1; YMin = 5e-6;}
 
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
  can->SetTickx(); can->SetTicky();
  can->SetLogy(); 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  
  //-----------------------------------
  auto hIncl1 = (TH1D*)GetTH1D(sPath, sCFile, "", sCInclHist); hIncl1->SetName("InclCen");
  auto hJE1   = (TH1D*)GetTH1D(sPath, sCFile, "", sCJetHist); hJE1->SetName("JECen");
  auto hUE1   = (TH1D*)GetTH1D(sPath, sCFile, "", sCUEHist); hUE1->SetName("UECen");
  auto hJC1   = (TH1D*)GetTH1D(sPath, sCFile, "", sCJCHist); hJC1->SetName("JCCen");
  if(sType == "Lambda" || sType == "AntiLa") hJC1->Add(hUE1); hJC1->SetName("JCCen");
  auto hOC1   = (TH1D*)GetTH1D(sPath, sCFile, "", sCOCHist); hOC1->SetName("OCCen");
  auto hNJ1   = (TH1D*)GetTH1D(sPath, sCFile, "", sCNJHist); hNJ1->SetName("NJCen");
  
  auto hIncl2 = (TH1D*)GetTH1D(sPath, sEFile, sEList, sEIHist); hIncl2->SetName("InclErr");
  auto hJE2 = (TH1D*)GetTH1D(sPath, sEFile, sEList, sEJHist); hJE2->SetName("JEErr");
  auto hUE2 = (TH1D*)GetTH1D(sPath, sEFile, sEList, sEUHist); hUE2->SetName("UEErr");
  auto hJC2 = (TH1D*)GetTH1D(sPath, sEFile, sEList, sEJCHist); hJC2->SetName("JCErr");
  auto hOC2 = (TH1D*)hUE2->Clone("OCErr");
  auto hNJ2 = (TH1D*)hUE2->Clone("NJErr");

  if(sType == "Lambda" && IsSum){
    auto hAIncl1 = (TH1D*)GetTH1D(sPath, sCFile, "", Form("hPtIncl_AntiLa")); hAIncl1->SetName("AInclCen");
    auto hAJE1   = (TH1D*)GetTH1D(sPath, sCFile, "", Form("hPtJC_AntiLa")); hAJE1->SetName("AJECen");
    auto hAUE1   = (TH1D*)GetTH1D(sPath, sCFile, "", Form("hPtPC_AntiLa")); hAUE1->SetName("AUECen");
    auto hAJC1   = (TH1D*)hAJE1->Clone("AJCCen"); hAJC1->Add(hAUE1);hAJC1->SetName("AJCCen");
    auto hAOC1   = (TH1D*)GetTH1D(sPath, sCFile, "", Form("hPtOC_AntiLa")); hAOC1->SetName("AOCCen");
    auto hANJ1   = (TH1D*)GetTH1D(sPath, sCFile, "", Form("hPtNJ_AntiLa")); hANJ1->SetName("ANJCen");
    
    auto hAIncl2 = (TH1D*)GetTH1D(sPath, sEFile, Form("AntiLa_UncerTot"), sEIHist); hAIncl2->SetName("AInclErr");
    auto hAJE2 = (TH1D*)GetTH1D(sPath, sEFile, Form("AntiLa_UncerTot"), sEJHist); hAJE2->SetName("AJEErr");
    auto hAUE2 = (TH1D*)GetTH1D(sPath, sEFile, Form("AntiLa_UncerTot"), sEUHist); hAUE2->SetName("AUEErr");
    auto hAJC2 = (TH1D*)GetTH1D(sPath, sEFile, Form("AntiLa_UncerTot"), sEJCHist); hAJC2->SetName("AJCErr");
    auto hAOC2 = (TH1D*)hAUE2->Clone("AOCErr");
    auto hANJ2 = (TH1D*)hAUE2->Clone("ANJErr");
   
    hIncl1->Add(hAIncl1);
    hJE1->Add(hAJE1);
    hUE1->Add(hAUE1);
    hJC1->Add(hAJC1);
    hOC1->Add(hAOC1);
    hNJ1->Add(hANJ1);
    Double_t dIncl1, dJE1, dUE1, dJC1, dOC1, dNJ1;
    Double_t dIncl2, dJE2, dUE2, dJC2, dOC2, dNJ2;
    Double_t dAIncl1, dAJE1, dAUE1, dAJC1, dAOC1, dANJ1;
    Double_t dAIncl2, dAJE2, dAUE2, dAJC2, dAOC2, dANJ2;
    for(Int_t i = 1; i<=hIncl2->GetNbinsX(); i++){ 
      hIncl2->SetBinError(i, 0); 
      dIncl1 =  hIncl1->GetBinContent(i); 
      dIncl2 =  hIncl2->GetBinContent(i);
      dAIncl1 = hAIncl1->GetBinContent(i); 
      dAIncl2 = hAIncl2->GetBinContent(i);
      hIncl2->SetBinContent(i, TMath::Sqrt(dIncl1*dIncl2*dIncl1*dIncl2 + dAIncl1*dAIncl2*dAIncl1*dAIncl2)/(dIncl1+dAIncl1));
    } hIncl2->SetName("InclErr");
    for(Int_t i = 1; i<=hJE2->GetNbinsX(); i++){ 
      hJE2->SetBinError(i, 0); 
      dJE1 =  hJE1->GetBinContent(i); 
      dJE2 =  hJE2->GetBinContent(i);
      dAJE1 = hAJE1->GetBinContent(i); 
      dAJE2 = hAJE2->GetBinContent(i);
      hJE2->SetBinContent(i, TMath::Sqrt(dJE1*dJE2*dJE1*dJE2 + dAJE1*dAJE2*dAJE1*dAJE2)/(dJE1+dAJE1));
    } hJE2->SetName("JEErr");
    for(Int_t i = 1; i<=hUE2->GetNbinsX(); i++){ 
      hUE2->SetBinError(i, 0); 
      dUE1 =  hUE1->GetBinContent(i); 
      dUE2 =  hUE2->GetBinContent(i);
      dAUE1 = hAUE1->GetBinContent(i); 
      dAUE2 = hAUE2->GetBinContent(i);
      hUE2->SetBinContent(i, TMath::Sqrt(dUE1*dUE2*dUE1*dUE2 + dAUE1*dAUE2*dAUE1*dAUE2)/(dUE1+dAUE1));
    } hUE2->SetName("UEErr");
    for(Int_t i = 1; i<=hJC2->GetNbinsX(); i++){ 
      hJC2->SetBinError(i, 0); 
      dJC1 =  hJC1->GetBinContent(i); 
      dJC2 =  hJC2->GetBinContent(i);
      dAJC1 = hAJC1->GetBinContent(i); 
      dAJC2 = hAJC2->GetBinContent(i);
      hJC2->SetBinContent(i, TMath::Sqrt(dJC1*dJC2*dJC1*dJC2 + dAJC1*dAJC2*dAJC1*dAJC2)/(dJC1+dAJC1));
    } hJC2->SetName("JCErr");
    for(Int_t i = 1; i<=hOC2->GetNbinsX(); i++){ 
      hOC2->SetBinError(i, 0); 
      dOC1 =  hOC1->GetBinContent(i); 
      dOC2 =  hOC2->GetBinContent(i);
      dAOC1 = hAOC1->GetBinContent(i); 
      dAOC2 = hAOC2->GetBinContent(i);
      hOC2->SetBinContent(i, TMath::Sqrt(dOC1*dOC2*dOC1*dOC2 + dAOC1*dAOC2*dAOC1*dAOC2)/(dOC1+dAOC1));
    } hOC2->SetName("OCErr");
    for(Int_t i = 1; i<=hNJ2->GetNbinsX(); i++){ 
      hNJ2->SetBinError(i, 0); 
      dNJ1 =  hNJ1->GetBinContent(i); 
      dNJ2 =  hNJ2->GetBinContent(i);
      dANJ1 = hANJ1->GetBinContent(i); 
      dANJ2 = hANJ2->GetBinContent(i);
      hNJ2->SetBinContent(i, TMath::Sqrt(dNJ1*dNJ2*dNJ1*dNJ2 + dANJ1*dANJ2*dANJ1*dANJ2)/(dNJ1+dANJ1));
    } hNJ2->SetName("NJErr");
  }

  //-----------------------------------
  const auto nI = hIncl1->GetNbinsX();
  const auto nJ = hJE1->GetNbinsX();
  //-----------------------------------
  hIncl1->GetYaxis()->SetRangeUser(YMin, YMax);
  hIncl1->GetXaxis()->SetRangeUser(XMin, XMax);
  //-----------------------------------

  DrawHisto(hIncl1, cLine[0], sMark[0], "same");
  leg->AddEntry(hIncl1, "Incl");
  auto gIncl = (TGraphErrors*)ConvHistogramToGraphErrors(hIncl1, hIncl2, nI); gIncl->SetName("Inclerr");
  //DrawGraph(gIncl, cLine[0], sMark[0], "P"); 
  DrawGraph(gIncl, cLine[0], "E2");
  //-----------------------------------
  DrawHisto(hJC1, cLine[1], sMark[1], "same");
  leg->AddEntry(hJC1, "JC");
  auto gJC = (TGraphErrors*)ConvHistogramToGraphErrors(hJC1, hJC2, nJ); gJC->SetName("JCerr");
  //DrawGraph(gJC, cLine[1], sMark[1], "P"); 
  DrawGraph(gJC, cLine[1], "E2");

  //-----------------------------------
  DrawHisto(hJE1, cLine[2], sMark[2], "same");
  leg->AddEntry(hJE1, "JE");
  auto gJE = (TGraphErrors*)ConvHistogramToGraphErrors(hJE1, hJE2, nJ); gJE->SetName("JEerr");
  //DrawGraph(gJE, cLine[2], sMark[2], "P"); 
  DrawGraph(gJE, cLine[2], "E2");
  //-----------------------------------
  DrawHisto(hUE1, cLine[3], sMark[3], "same");
  leg->AddEntry(hUE1, "UE");
  auto gUE = (TGraphErrors*)ConvHistogramToGraphErrors(hUE1, hUE2, nJ); gUE->SetName("UEerr");
  //DrawGraph(gUE, cLine[3], sMark[3], "P");
  DrawGraph(gUE, cLine[3], "E2");

  DrawHisto(hOC1, cLine[4], sMark[4], "same");
  leg->AddEntry(hOC1, "OC");
  auto gOC = (TGraphErrors*)ConvHistogramToGraphErrors(hOC1, hOC2, nJ); gOC->SetName("OCerr");
  //DrawGraph(gOC, cLine[3], sMark[3], "P");
  DrawGraph(gOC, cLine[4], "E2");
  
  DrawHisto(hNJ1, cLine[5], sMark[5], "same");
  leg->AddEntry(hNJ1, "NJ");
  auto gNJ = (TGraphErrors*)ConvHistogramToGraphErrors(hNJ1, hNJ2, nJ); gNJ->SetName("NJerr");
  //DrawGraph(gNJ, cLine[3], sMark[3], "P");
  DrawGraph(gNJ, cLine[5], "E2");
  
  TFile *f = TFile::Open("./result/FinalSpect_ThisAna.root", "UPDATE");
  TList *l = new TList();
  l->Add(hIncl1);
  l->Add(hJE1);
  l->Add(hUE1);
  l->Add(hJC1);
  l->Add(hOC1);
  l->Add(hNJ1);
  l->Add(hIncl2);
  l->Add(hJE2);
  l->Add(hUE2);
  l->Add(hJC2);
  l->Add(hOC2);
  l->Add(hNJ2);
  l->Add(gIncl);
  l->Add(gJE);
  l->Add(gUE);
  l->Add(gJC);
  l->Add(gOC);
  l->Add(gNJ);
  if(!IsSum)l->Write(Form("%s",sType.Data()), TObject::kSingleKey);
  if(IsSum)l->Write(Form("%s_sum",sType.Data()), TObject::kSingleKey);
  f->Close();
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  tex->DrawLatex(0.15, 0.83, "Jet: Anti-#it{k}_{T}, #it{R} = 0.4");
  tex->DrawLatex(0.15, 0.75, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#it{#eta}_{jet}| < 0.35");
  
  if(sType == "Kshort"){
    tex->DrawLatex(0.15, 0.3, Form("K^{0}_{S}"));
    tex->DrawLatex(0.15, 0.2, "|#it{#eta}_{K^{0}_{S}}| < 0.75, #Delta#it{R}(K^{0}_{S}, jet) < 0.4");
  }
  if(sType == "AntiLa"){
    tex->DrawLatex(0.15, 0.3, Form("#bar{#Lambda}"));
    tex->DrawLatex(0.15, 0.2, "|#it{#eta}_{#bar{#Lambda}}| < 0.75, #Delta#it{R}(#bar{#Lambda}, jet) < 0.4");
  }
  if(sType == "Lambda" && IsSum){
    tex->DrawLatex(0.15, 0.3, Form("#Lambda + #bar{#Lambda}"));
    tex->DrawLatex(0.15, 0.2, "|#it{#eta}_{#Lambda}| < 0.75, #Delta#it{R}(#Lambda, jet) < 0.4");
  }
  if((sType == "Lambda" && !IsSum) || sType == "Xi" || sType == "Omega"){
    tex->DrawLatex(0.15, 0.3, Form("#%s", sType.Data()));
    tex->DrawLatex(0.15, 0.2, Form("|#it{#eta}_{#%s}| < 0.75, #Delta#it{R}(#%s, jet) < 0.4", sType.Data(), sType.Data()));
  }
  
  leg->AddEntry(gIncl, "Sys.Error", "f");  
  leg->Draw();
  gStyle->SetOptStat("");
  //if(!IsSum) can->SaveAs(Form("./figure/ThisAna/%s_wSysError.eps", sType.Data()));
  //if(IsSum)can->SaveAs(Form("./figure/ThisAna/%s_sum_wSysError.eps", sType.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
