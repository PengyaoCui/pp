#include "./inc/SourceFun.h"

void FinalSpect(const TString sType = "AntiLa", const Bool_t IsSum = kFALSE){
  
  auto sPath = "./result"; 
  auto sCFile = "CentVal.root";
  
  auto sCInclList = Form("listIn");
  auto sCJEList = Form("listJE");
  auto sCJCList = Form("listJC");
  auto sCPCList = Form("listPC04");
  auto sCP2List = Form("listPC02");
  auto sCP6List = Form("listPC06");

  auto sCHist = Form("h%s", sType.Data());
  
  auto sEFile = "TotUncer.root";
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
  if(sType == "Omega"){ XMax = 5.; YMax = 1e-1; YMin = 1e-5;}
 
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
  can->SetTickx(); can->SetTicky();
  can->SetLogy(); 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  
  //-----------------------------------
  auto hIncl1 = (TH1D*)GetTH1D(sPath, sCFile, sCInclList, sCHist); hIncl1->SetName("InclCen");
  auto hJE1   = (TH1D*)GetTH1D(sPath, sCFile, sCJEList,   sCHist); hJE1->SetName("JECen");
  auto hUE1   = (TH1D*)GetTH1D(sPath, sCFile, sCPCList,   sCHist); hUE1->SetName("UECen");
  auto hJC1   = (TH1D*)GetTH1D(sPath, sCFile, sCJCList,   sCHist); hJC1->SetName("JCCen");
  auto hP21   = (TH1D*)GetTH1D(sPath, sCFile, sCP2List,   sCHist); hP21->SetName("P2Cen");
  auto hP61   = (TH1D*)GetTH1D(sPath, sCFile, sCP6List,   sCHist); hP61->SetName("P6Cen");

  auto hIncl2 = (TH1D*)GetTH1D(sPath, sEFile, sEList, sEIHist); hIncl2->SetName("InclErr");
  auto hJE2 = (TH1D*)GetTH1D(sPath, sEFile, sEList, sEJHist); hJE2->SetName("JEErr");
  auto hUE2 = (TH1D*)GetTH1D(sPath, sEFile, sEList, sEUHist); hUE2->SetName("UEErr");
  auto hJC2 = (TH1D*)GetTH1D(sPath, sEFile, sEList, sEJCHist); hJC2->SetName("JCErr");
  auto hP22 = (TH1D*)hUE2->Clone("P2Err");
  auto hP62 = (TH1D*)hUE2->Clone("P6Err");

  if(sType == "Lambda" && IsSum){
    auto hAIncl1 = (TH1D*)GetTH1D(sPath, sCFile,sCInclList, Form("hAntiLa")); hAIncl1->SetName("AInclCen");
    auto hAJE1   = (TH1D*)GetTH1D(sPath, sCFile,sCJEList,   Form("hAntiLa")); hAJE1->SetName("AJECen");
    auto hAUE1   = (TH1D*)GetTH1D(sPath, sCFile,sCPCList,   Form("hAntiLa")); hAUE1->SetName("AUECen");
    auto hAJC1   = (TH1D*)GetTH1D(sPath, sCFile,sCJCList,   Form("hAntiLa")); hAJC1->SetName("AJCCen");
    auto hAP21   = (TH1D*)GetTH1D(sPath, sCFile,sCP2List,   Form("hAntiLa")); hAP21->SetName("AP2Cen");
    auto hAP61   = (TH1D*)GetTH1D(sPath, sCFile,sCP6List,   Form("hAntiLa")); hAP61->SetName("AP6Cen");
                                                  
    auto hAIncl2 = (TH1D*)GetTH1D(sPath, sEFile, Form("AntiLa_UncerTot"), sEIHist); hAIncl2->SetName("AInclErr");
    auto hAJE2 = (TH1D*)GetTH1D(sPath, sEFile, Form("AntiLa_UncerTot"), sEJHist); hAJE2->SetName("AJEErr");
    auto hAUE2 = (TH1D*)GetTH1D(sPath, sEFile, Form("AntiLa_UncerTot"), sEUHist); hAUE2->SetName("AUEErr");
    auto hAJC2 = (TH1D*)GetTH1D(sPath, sEFile, Form("AntiLa_UncerTot"), sEJCHist); hAJC2->SetName("AJCErr");
    auto hAP22 = (TH1D*)hAUE2->Clone("AP2Err");
    auto hAP62 = (TH1D*)hAUE2->Clone("AP6Err");
   
    hIncl1->Add(hAIncl1);
    hJE1->Add(hAJE1);
    hUE1->Add(hAUE1);
    hJC1->Add(hAJC1);
    hP21->Add(hAP21);
    hP61->Add(hAP61);
    Double_t dIncl1, dJE1, dUE1, dJC1, dP21, dP61;
    Double_t dIncl2, dJE2, dUE2, dJC2, dP22, dP62;
    Double_t dAIncl1, dAJE1, dAUE1, dAJC1, dAP21, dAP61;
    Double_t dAIncl2, dAJE2, dAUE2, dAJC2, dAP22, dAP62;
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
    for(Int_t i = 1; i<=hP22->GetNbinsX(); i++){ 
      hP22->SetBinError(i, 0); 
      dP21 =  hP21->GetBinContent(i); 
      dP22 =  hP22->GetBinContent(i);
      dAP21 = hAP21->GetBinContent(i); 
      dAP22 = hAP22->GetBinContent(i);
      hP22->SetBinContent(i, TMath::Sqrt(dP21*dP22*dP21*dP22 + dAP21*dAP22*dAP21*dAP22)/(dP21+dAP21));
    } hP22->SetName("P2Err");
    for(Int_t i = 1; i<=hP62->GetNbinsX(); i++){ 
      hP62->SetBinError(i, 0); 
      dP61 =  hP61->GetBinContent(i); 
      dP62 =  hP62->GetBinContent(i);
      dAP61 = hAP61->GetBinContent(i); 
      dAP62 = hAP62->GetBinContent(i);
      hP62->SetBinContent(i, TMath::Sqrt(dP61*dP62*dP61*dP62 + dAP61*dAP62*dAP61*dAP62)/(dP61+dAP61));
    } hP62->SetName("P6Err");
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
  //-----------------------------------
  DrawHisto(hP21, cLine[3], sMark[3], "same");
  leg->AddEntry(hP21, "P2");
  auto gP2 = (TGraphErrors*)ConvHistogramToGraphErrors(hP21, hP22, nJ); gP2->SetName("P2err");
  //DrawGraph(gP2, cLine[3], sMark[3], "P");
  DrawGraph(gP2, cLine[3], "E2");
  //-----------------------------------
  DrawHisto(hP61, cLine[3], sMark[3], "same");
  leg->AddEntry(hP61, "P6");
  auto gP6 = (TGraphErrors*)ConvHistogramToGraphErrors(hP61, hP62, nJ); gP6->SetName("P6err");
  //DrawGraph(gP6, cLine[3], sMark[3], "P");
  DrawGraph(gP6, cLine[3], "E2");

  TFile *f = TFile::Open("./result/pp.root", "UPDATE");
  TList *l = new TList();
  l->Add(hIncl1);
  l->Add(hJE1);
  l->Add(hUE1);
  l->Add(hJC1);
  l->Add(hP21);
  l->Add(hP61);
  l->Add(hIncl2);
  l->Add(hJE2);
  l->Add(hUE2);
  l->Add(hJC2);
  l->Add(hP22);
  l->Add(hP62);
  l->Add(gIncl);
  l->Add(gJE);
  l->Add(gUE);
  l->Add(gJC);
  l->Add(gP2);
  l->Add(gP6);
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
  //if(!IsSum)can->SaveAs(Form("./figure/ThisAna/%s_wSysError.eps", sType.Data()));
  //if(IsSum)can->SaveAs(Form("./figure/ThisAna/%s_sum_wSysError.eps", sType.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
