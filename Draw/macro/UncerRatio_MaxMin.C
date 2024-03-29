#include "./SourceFun.h"

void UncerRatio_MaxMin(const TString sType = "Xi"){
  
  const TString sK = "Kshort";
  auto sPath = "./result"; 
  auto sFile = "FinalSpect_ThisAna.root";  
  auto sList = Form("%s", sType.Data()); 
  auto sKList = Form("%s", sK.Data()); 
  auto sInclCen  = "InclCen";
  auto sInclErr  = "InclErr";
  auto sJCCen  = "JCCen";
  auto sJCErr  = "JCErr";
  auto sJECen  = "JECen";
  auto sJEErr  = "JEErr";
  auto sUECen  = "UECen";
  auto sUEErr  = "UEErr";

  //--------------------------GetCentSpect 
  auto hInclK = (TH1D*)GetTH1D(sPath, sFile, sKList, sInclCen); hInclK->SetName("hInclK");
  //auto hJCK = (TH1D*)GetTH1D(sPath, sFile, sKList, sJCCen); hJCK->SetName("hJCK");
  auto hJEK = (TH1D*)GetTH1D(sPath, sFile, sKList, sJECen); hJEK->SetName("hJEK");
  auto hUEK = (TH1D*)GetTH1D(sPath, sFile, sKList, sUECen); hUEK->SetName("hUEK");
  
  auto hIncl = (TH1D*)GetTH1D(sPath, sFile, sList, sInclCen); hIncl->SetName("hIncl");
  //auto hJC  = (TH1D*)GetTH1D(sPath, sFile, sList,  sJCCen); hJC->SetName("hJC");
  auto hJE  = (TH1D*)GetTH1D(sPath, sFile, sList,  sJECen); hJE->SetName("hJE");
  auto hUE  = (TH1D*)GetTH1D(sPath, sFile, sList,  sUECen); hUE->SetName("hUE");

  //---------------------------GetCentRatio
  auto hInclR = (TH1D*)hIncl->Clone("hInclR"); hInclR->Reset();
  DeNormHistBinWidth(hInclK); 
  hInclK = RebinTH1D(hInclK, hInclR); 
  NormHistBinWidth(hInclK);
  hInclR->Divide(hIncl, hInclK, 1., 2.);

  
  auto hJER = (TH1D*)hJE->Clone("hJER"); hJER->Reset();
  DeNormHistBinWidth(hJEK); 
  hJEK = RebinTH1D(hJEK, hJER); 
  NormHistBinWidth(hJEK);
  hJER->Divide(hJE, hJEK, 1., 2.);

  auto hUER = (TH1D*)hUE->Clone("hUER"); hUER->Reset();
  DeNormHistBinWidth(hUEK); 
  hUEK = RebinTH1D(hUEK, hUER); 
  NormHistBinWidth(hUEK);
  hUER->Divide(hUE, hUEK, 1., 2.);
 
  //---------------------------InclUncer
  auto heInclK = (TH1D*)GetTH1D(sPath, sFile, sKList, sInclErr); heInclK->SetName("heInclK");
  auto heIncl = (TH1D*)GetTH1D(sPath, sFile, sList, sInclErr); heIncl->SetName("heIncl");
  heInclK = CancleMaterBudget(hInclK);
  heIncl = CancleMaterBudget(hIncl);
  auto heInclR = (TH1D*)heIncl->Clone("heInclR");heInclR->Reset(); // relative sys. error
  DeNormHistBinWidth(heInclK); 
  heInclK = RebinTH1D(heInclK, heInclR); 
  NormHistBinWidth(heInclK);
  TH1D* heInclr[] = {heInclK, heIncl}; 
  heInclR = (TH1D*)QuadraticSum(2, heInclr); heInclR->SetName("heInclR");
  for(Int_t i = 1; i<= heInclR->GetNbinsX(); i++){heInclR->SetBinError(i, 0);} 
  auto gInclR = (TGraphErrors*)ConvHistogramToGraphErrors(hInclR, heInclR, hInclR->GetNbinsX()); gInclR->SetName("InclRerr");
  //---------------------------UEUncer

  auto heUEK = (TH1D*)GetTH1D(sPath, sFile, sKList, sUEErr); heUEK->SetName("heUEK");
  auto heUE = (TH1D*)GetTH1D(sPath, sFile, sList, sUEErr); heUE->SetName("heUE");
  heUEK = CancleMaterBudget(heUEK);
  heUE = CancleMaterBudget(heUE);

  auto heUER = (TH1D*)heUE->Clone("heUER");heUER->Reset(); // relative sys. error
  DeNormHistBinWidth(heUEK);
  heUEK = RebinTH1D(heUEK, heUER);
  NormHistBinWidth(heUEK);
  TH1D* heUEr[] = {heUEK, heUE};
  heUER = (TH1D*)QuadraticSum(2, heUEr); heUER->SetName("heUER");
  for(Int_t i = 1; i<= heUER->GetNbinsX(); i++){heUER->SetBinError(i, 0);} 
  auto gUER = (TGraphErrors*)ConvHistogramToGraphErrors(hUER, heUER, hUER->GetNbinsX()); gUER->SetName("UERerr");
 
  //---------------------------JEUncer
  auto sFile2 = "PtSpect_ThisAna.root";  
  
  //===========================StrangeRec
  auto heJEI = (TH1D*)hJER->Clone("heJEI");heJEI->Reset();
  auto heJEi = (TH1D*)heInclR->Clone("heJEi");
  DeNormHistBinWidth(heJEi);
  //heUEK = RebinTH1D(heJEi, heJEI);
  heJEi = RebinTH1D(heJEi, heJEI);
  NormHistBinWidth(heJEi);
  heJEI = heJEi;heJEI->SetName("heJEI");
  for(Int_t i = 1; i<= heJEI->GetNbinsX(); i++){heJEI->SetBinError(i, 0);} 

  //===========================UESub
  auto hJCK = (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtJC_Kshort")); hJCK->SetName("hJCK");
  auto hNJK = (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtNJ_Kshort")); hNJK->SetName("hNJK");
  auto hOCK = (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtOC_Kshort")); hOCK->SetName("hOCK");
  auto hPCK = (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtPC_Kshort")); hPCK->SetName("hPCK");

  TH1D* hJC = nullptr;
  TH1D* hNJ = nullptr;
  TH1D* hOC = nullptr; 
  TH1D* hPC = nullptr;
  if(sType != "Lambda_sum"){
    hJC =  (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtJC_%s", sType.Data()));hJC->SetName("hJC");
    hNJ =  (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtNJ_%s", sType.Data()));hNJ->SetName("hNJ");
    hOC =  (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtOC_%s", sType.Data()));hOC->SetName("hOC");
    hPC =  (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtPC_%s", sType.Data()));hNJ->SetName("hPC");
  }
  if(sType == "Lambda_sum"){
    hJC = (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtJC_Lambda")); hJC->SetName("hJC");
    auto hJC2 = (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtJC_AntiLa"));hJC2->SetName("hJC2");  
    hJC->Add(hJC2);hJC->SetName("hJC");

    hNJ = (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtNJ_Lambda")); hNJ->SetName("hNJ");
    auto hNJ2 = (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtNJ_AntiLa"));hNJ2->SetName("hNJ2");  
    hNJ->Add(hNJ2);hNJ->SetName("hNJ");
    hOC = (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtOC_Lambda")); hOC->SetName("hOC");
    auto hOC2 = (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtOC_AntiLa")); hOC2->SetName("hOC2");
    hOC->Add(hOC2);hOC->SetName("hOC");
    
    hPC = (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtPC_Lambda")); hPC->SetName("hPC");
    auto hPC2 = (TH1D*)GetTH1D(sPath, sFile2, "", Form("hPtPC_AntiLa"));hPC2->SetName("hPC2");  
    hPC->Add(hPC2);hPC->SetName("hPC");
    
    hJC->Add(hPC); hJC->SetName("hJC");
  }
  auto hJCR = (TH1D*)hJC->Clone("hJCR"); hJCR->Reset();
  DeNormHistBinWidth(hJCK); 
  hJCK = RebinTH1D(hJCK, hJCR); 
  NormHistBinWidth(hJCK);
  hJCR->Divide(hJC, hJCK, 1., 2.);

  auto hNJR = (TH1D*)hNJ->Clone("hNJR");hNJR->Reset();  
  auto hOCR = (TH1D*)hOC->Clone("hOCR");hOCR->Reset();
  auto hPCR = (TH1D*)hPC->Clone("hPCR");hPCR->Reset();
  
  DeNormHistBinWidth(hNJK); hNJK = (TH1D*)RebinTH1D(hNJK, hNJR); NormHistBinWidth(hNJK);
  DeNormHistBinWidth(hOCK); hOCK = (TH1D*)RebinTH1D(hOCK, hNJR); NormHistBinWidth(hOCK);
  DeNormHistBinWidth(hPCK); hPCK = (TH1D*)RebinTH1D(hPCK, hNJR); NormHistBinWidth(hPCK);
 
  TH1D* hJCNJ = (TH1D*) hJC->Clone("hJCNJ"); TH1D* hJCNJK = (TH1D*) hJCK->Clone("hJCNJK");
  TH1D* hJCOC = (TH1D*) hJC->Clone("hJCOC"); TH1D* hJCOCK = (TH1D*) hJCK->Clone("hJCOCK");
  TH1D* hJCPC = (TH1D*) hJC->Clone("hJCPC"); TH1D* hJCPCK = (TH1D*) hJCK->Clone("hJCPCK");
  DeNormHistBinWidth(hJCNJK); hJCNJK = (TH1D*)RebinTH1D(hJCNJK, hNJR); NormHistBinWidth(hJCNJK);
  DeNormHistBinWidth(hJCOCK); hJCOCK = (TH1D*)RebinTH1D(hJCOCK, hNJR); NormHistBinWidth(hJCOCK);
  DeNormHistBinWidth(hJCPCK); hJCPCK = (TH1D*)RebinTH1D(hJCPCK, hNJR); NormHistBinWidth(hJCPCK);
  hJCNJ->Add(hNJ, -1.); hJCOC->Add(hOC, -1.);  hJCPC->Add(hPC, -1.); 
  hJCNJK->Add(hNJK, -1.); hJCOCK->Add(hOCK, -1.);  hJCPCK->Add(hPCK, -1.); 
  hNJR->Divide(hJCNJ, hJCNJK, 1., 2.);  
  hOCR->Divide(hJCOC, hJCOCK, 1., 2.);
  hPCR->Divide(hJCPC, hJCPCK, 1., 2.);

  auto heNJR = (TH1D*)hJER->Clone("heNJR");
  auto heOCR = (TH1D*)hJER->Clone("heOCR");
  auto hePCR = (TH1D*)hJER->Clone("hePCR");
  for(Int_t i = 1; i<= hNJR->GetNbinsX(); i++){
    auto dJER = hJER->GetBinContent(i);
    auto dNJR = hNJR->GetBinContent(i);
    auto dOCR = hOCR->GetBinContent(i);
    auto dPCR = hPCR->GetBinContent(i);
    //auto dOCR = hNJR->GetBinContent(i);
    heNJR->SetBinContent(i, TMath::Abs(dNJR)/TMath::Sqrt(12.)); 
    heOCR->SetBinContent(i, TMath::Abs(dOCR)/TMath::Sqrt(12.)); 
    hePCR->SetBinContent(i, TMath::Abs(dPCR)/TMath::Sqrt(12.)); 
  }

  TH1D* hU[] = {hePCR, heNJR, heOCR};
  auto hUMax = (TH1D*)MaxHistograms(3, hU); 
  auto hUMin = (TH1D*)MinHistograms(3, hU);
  hUMax->Add(hUMin, -1.); 
  auto heJEU = (TH1D*)hJER->Clone("heJEU");heJEU->Reset(); 
  heJEU->Divide(hUMax, hJER, 1., 1.);heJEU->SetName("heJEU");
  for(Int_t i = 1; i<= heJEU->GetNbinsX(); i++){heJEU->SetBinError(i, 0);} 

  //===========================JetPt
  TString sFile3 = "JetPtUncertainty.root"; //Jet Pt Scale Uncertainty 
  auto hJPt0K = (TH1D*)GetTH1D(sPath, sFile3, Form("Kshort_JetPt"), "hist_0"); hJPt0K->SetName("hJPt0K");
  auto hJPt1K = (TH1D*)GetTH1D(sPath, sFile3, Form("Kshort_JetPt"), "hist_1"); hJPt1K->SetName("hJPt1K");
  TH1D* hJPt0 = nullptr;
  TH1D* hJPt1 = nullptr;
  if(sType != "Lambda_sum"){
    hJPt0 =(TH1D*)GetTH1D(sPath, sFile3, Form("%s_JetPt", sType.Data()), "hist_0"); hJPt0->SetName("hJPt0");
    hJPt1 =(TH1D*)GetTH1D(sPath, sFile3, Form("%s_JetPt", sType.Data()), "hist_1"); hJPt1->SetName("hJPt1");
  }else{
    hJPt0 =(TH1D*)GetTH1D(sPath, sFile3, Form("Lambda_JetPt"), "hist_0"); hJPt0->SetName("hJPt0");
    hJPt1 =(TH1D*)GetTH1D(sPath, sFile3, Form("Lambda_JetPt"), "hist_1"); hJPt1->SetName("hJPt1");
    auto hJPt00 =(TH1D*)GetTH1D(sPath, sFile3, Form("AntiLa_JetPt"), "hist_0"); hJPt00->SetName("hJPt00");
    auto hJPt11 =(TH1D*)GetTH1D(sPath, sFile3, Form("AntiLa_JetPt"), "hist_1"); hJPt11->SetName("hJPt11");
    hJPt0->Add(hJPt00);hJPt0->SetName("hJPt0");  hJPt1->Add(hJPt11);hJPt1->SetName("hJPt1");
  }
  DeNormHistBinWidth(hJPt0K); hJPt0K = (TH1D*)RebinTH1D(hJPt0K, hJPt0); NormHistBinWidth(hJPt0K);  
  DeNormHistBinWidth(hJPt1K); hJPt1K = (TH1D*)RebinTH1D(hJPt1K, hJPt1); NormHistBinWidth(hJPt1K);  
  auto hJPt0R = (TH1D*)hJPt0->Clone("hJPt0R");hJPt0R->Reset();
  auto hJPt1R = (TH1D*)hJPt1->Clone("hJPt1R");hJPt1R->Reset();
  hJPt0R->Divide(hJPt0, hJPt0K, 1., 2.); hJPt1R->Divide(hJPt1, hJPt1K, 1., 2.);

  auto heJPt0R = (TH1D*)hJCR->Clone("heJPt0R");heJPt0R->Reset();  
  auto heJPt1R = (TH1D*)hJCR->Clone("heJPt1R");heJPt1R->Reset();
  for(Int_t i = 1; i<= hJPt0R->GetNbinsX(); i++){
    auto dJER = hJCR->GetBinContent(i);
    auto dJPt0R = hJPt0R->GetBinContent(i);
    auto dJPt1R = hJPt1R->GetBinContent(i);
    heJPt0R->SetBinContent(i, TMath::Abs(dJPt0R));
    heJPt1R->SetBinContent(i, TMath::Abs(dJPt1R));
  }
  TH1D* hJPt[] = {heJPt0R, heJPt1R, hJCR};
  auto hJPtMax = (TH1D*)MaxHistograms(3, hJPt);
  auto hJPtMin = (TH1D*)MinHistograms(3, hJPt);
  hJPtMax->Add(hJPtMin, -1.);
  hJPtMax->Scale(1./TMath::Sqrt(12.));
  auto heJEJ = (TH1D*)hJER->Clone("heJEJ");heJEJ->Reset();
  heJEJ->Divide(hJPtMax, hJER, 1., 1.);heJEJ->SetName("heJEJ");
  for(Int_t i = 1; i<= heJEJ->GetNbinsX(); i++){heJEJ->SetBinError(i, 0);} 

  auto heJER = (TH1D*)heJEJ->Clone("heJER");heJER->Reset();
  TH1D *hSumJ[] = {heJEI, heJEU, heJEJ};
  heJER = (TH1D*)QuadraticSum(3, hSumJ);heJER->SetName("heJER"); 
  for(Int_t i = 1; i<= heJER->GetNbinsX(); i++){heJER->SetBinError(i, 0);} 
  auto gJER = (TGraphErrors*)ConvHistogramToGraphErrors(hJER, heJER, hJER->GetNbinsX()); gJER->SetName("JERerr");

  //---------------------------JCUncer

  //===========================StrangeRec
  auto heJCI = (TH1D*)hJCR->Clone("heJCI");heJCI->Reset();
  auto heJCi = (TH1D*)heInclR->Clone("heJCi");
  DeNormHistBinWidth(heJCi);
  //heUEK = RebinTH1D(heJCi, heJCI);
  heJCi = RebinTH1D(heJCi, heJCI);
  NormHistBinWidth(heJCi);
  heJCI = heJCi;heJCI->SetName("heJCI");
  for(Int_t i = 1; i<= heJCI->GetNbinsX(); i++){heJCI->SetBinError(i, 0);}

  //===========================JetPt
  auto heJCJ = (TH1D*)hJCR->Clone("heJCJ");heJCJ->Reset();
  heJCJ->Divide(hJPtMax, hJCR, 1., 1.);heJCJ->SetName("heJCJ");
  for(Int_t i = 1; i<= heJCJ->GetNbinsX(); i++){heJCJ->SetBinError(i, 0);} 

  auto heJCR = (TH1D*)heJCJ->Clone("heJCR");heJCR->Reset();
  TH1D *hsumJ[] = {heJCI, heJCJ};
  heJCR = (TH1D*)QuadraticSum(2, hsumJ);heJCR->SetName("heJCR"); 
  for(Int_t i = 1; i<= heJCR->GetNbinsX(); i++){heJCR->SetBinError(i, 0);} 
  auto gJCR = (TGraphErrors*)ConvHistogramToGraphErrors(hJCR, heJCR, hJCR->GetNbinsX()); gJCR->SetName("JCRerr");
  
  
  
  //TFile *f = TFile::Open("./result/FinalSpect_ThisAna.root", "UPDATE");
  //TList *l = new TList();
 
  //l->Add(hInclR);
  //l->Add(hJCR);
  //l->Add(hJER);
  //l->Add(hUER);

  //l->Add(heInclR);
  //l->Add(heJCR);
  //l->Add(heJER);
  //l->Add(heUER);

  //l->Add(gInclR);
  //l->Add(gJCR);
  //l->Add(gJER);
  //l->Add(gUER);

  //l->Add(heJCI);
  //l->Add(heJCJ);
  //
  //l->Add(heJEI);
  //l->Add(heJEJ);
  //l->Add(heJEU);
 
  //l->Write(Form("%s_toKRatio",sType.Data()), TObject::kSingleKey);
  //f->Close();
  

  //-----------------------------------
  TString sLatex(Form("pp #sqrt{#it{s}} = 13 TeV"));
  Double_t XMin = 0.;
  Double_t YMin = 0.;
  Double_t XMax = 0.;
  Double_t YMax = 0.;

  if(sType == "Lambda_sum"){XMax = 12.; YMax = 1.;}
  if(sType == "Xi"){XMax = 8.; YMax = 0.2;}
  if(sType == "Omega"){XMax = 5.; YMax = 0.05;}

  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  
  can = MakeCanvas("can");
  can->SetTickx(); can->SetTicky();
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  
  hInclR->GetXaxis()->SetRangeUser(XMin, XMax);
  hInclR->GetYaxis()->SetRangeUser(YMin, YMax);
  if(sType == "Lambda_sum"){
    hInclR->GetYaxis()->SetTitle("#Lambda/K^{0}_{S}");
  }else{
    hInclR->GetYaxis()->SetTitle(Form("#%s/K^{0}_{S}", sType.Data()));
  }
  DrawHisto(hInclR, cLine[0], sMark[0], "same");
  DrawGraph(gInclR, cLine[0], "E2"); 
  leg->AddEntry(hInclR, "Incl");
  DrawHisto(hJCR, cLine[1], sMark[1], "same");
  DrawGraph(gJCR, cLine[1], "E2"); 
  leg->AddEntry(hJCR, "JC");
  DrawHisto(hJER, cLine[2], sMark[2], "same");
  DrawGraph(gJER, cLine[2], "E2"); 
  leg->AddEntry(hJER, "JE");
  DrawHisto(hUER, cLine[3], sMark[3], "same");
  DrawGraph(gUER, cLine[3], "E2");
  leg->AddEntry(hUER, "UE");
  leg->AddEntry(gInclR, "Sys.Error", "f");  
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  tex->DrawLatex(0.15, 0.83, "Jet: Anti-#it{k}_{T}, #it{R} = 0.4");
  tex->DrawLatex(0.15, 0.75, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#it{#eta}_{jet}| < 0.35");
  if(sType == "Lambda_sum")tex->DrawLatex(0.15, 0.63, Form("#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}"));
  if(sType == "Xi" || sType == "Omega")tex->DrawLatex(0.15, 0.63, Form("#frac{#%s + #bar{#%s}}{2K^{0}_{S}}", sType.Data(), sType.Data()));
  leg->Draw();
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/ThisAna/%s_toKRatio.eps", sType.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  
  TCanvas *can1 = nullptr;
  TLatex* tex1 = nullptr;
  TLegend *leg1 = nullptr;
  can1 = MakeCanvas("can1");
  can1->SetTickx(); can1->SetTicky();
  leg1 = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg1);
 
  heJEI->GetYaxis()->SetTitle("Relative systematice error");
  heJEI->GetYaxis()->SetRangeUser(0., 1);
  DrawHisto(heJEI, cLine[1], sMark[1], "same"); leg1->AddEntry(heJEI, "Strange rec","l");
  DrawHisto(heJEJ, cLine[2], sMark[2], "same"); leg1->AddEntry(heJEJ, "Jet #it{p}_{T} sale","l");
  DrawHisto(heJEU, cLine[3], sMark[3], "same"); leg1->AddEntry(heJEU, "UE estimation","l");
  DrawHisto(heJER, cLine[0], sMark[0], "same"); leg1->AddEntry(heJER, "Total","l");

  
  //-----------------------------------
  tex1 =  new TLatex();
  tex1->SetNDC();
  tex1->SetTextSizePixels(24);
  tex1->DrawLatex(0.15, 0.9, sLatex);
  tex1->DrawLatex(0.15, 0.83, "Jet: Anti-#it{k}_{T}, #it{R} = 0.4");
  tex1->DrawLatex(0.15, 0.75, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#it{#eta}_{jet}| < 0.35");
  if(sType == "Lambda_sum")tex->DrawLatex(0.15, 0.63, Form("#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}"));
  if(sType == "Xi" || sType == "Omega")tex->DrawLatex(0.15, 0.63, Form("#frac{#%s + #bar{#%s}}{2K^{0}_{S}}", sType.Data(), sType.Data()));
  leg1->Draw();
  gStyle->SetOptStat("");
  can1->SaveAs(Form("./figure/CheckUEsubUncer/%s_toK_Uncert_Max-Min.eps", sType.Data()));
  can1->SaveAs(Form("./figure/CheckUEsubUncer/%s_toK_Uncert_Max-Min.pdf", sType.Data()));
  can1->SaveAs(Form("./figure/CheckUEsubUncer/%s_toK_Uncert_Max-Min.png", sType.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can1);
  return;
}
