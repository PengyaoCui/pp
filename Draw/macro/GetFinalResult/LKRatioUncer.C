#include "./inc/SourceFun.h"

void LKRatioUncer(){
  
  auto sPath = "./result"; 
  auto sFile = "pp.root";  
  
  //---------------------------GetCentRatio
  auto CFile = "CentVal.root";
  auto CListIn = "listIn";
  auto CListJE = "listJE";
  auto CListJC = "listJC";
  auto CListPC = "listPC04";
 
  auto hInR = (TH1D*)GetTH1D(sPath, CFile, CListIn, Form("hLKRatio")); hInR->SetName("hInR"); ;
  auto hJCR = (TH1D*)GetTH1D(sPath, CFile, CListJC, Form("hLKRatio")); hJCR->SetName("hJCR"); ;
  auto hPCR = (TH1D*)GetTH1D(sPath, CFile, CListPC, Form("hLKRatio")); hPCR->SetName("hUER"); ;
  auto hJER = (TH1D*)GetTH1D(sPath, CFile, CListJE, Form("hLKRatio")); hJER->SetName("hJER"); ;


  auto sListD =  Form("Kshort");
  auto sList =  Form("Lambda_sum"); 
  //---------------------------InclUncer
  auto heInK = (TH1D*)GetTH1D(sPath, sFile, sListD, "InclErr"); heInK->SetName("heInclK");
  auto heIn = (TH1D*)GetTH1D(sPath, sFile, sList, "InclErr"); heIn->SetName("heIncl");
  heInK = CancleMaterBudget(heInK);
  heIn = CancleMaterBudget(heIn);
  auto heInR = (TH1D*)heIn->Clone("heInclR");heInR->Reset(); // relative sys. error
  DeNormHistBinWidth(heInK); 
  heInK = RebinTH1D(heInK, heInR); 
  NormHistBinWidth(heInK);
  TH1D* heInr[] = {heInK, heIn}; 
  heInR = (TH1D*)QuadraticSum(2, heInr); heInR->SetName("heInR");
  for(Int_t i = 1; i<= heInR->GetNbinsX(); i++){heInR->SetBinError(i, 0);} 
  auto gInR = (TGraphErrors*)ConvHistogramToGraphErrors(hInR, heInR, hInR->GetNbinsX()); gInR->SetName("InRerr");
 
  //---------------------------UEUncer

  auto heUEK = (TH1D*)GetTH1D(sPath, sFile, sListD, "UEErr"); heUEK->SetName("heUEK");
  auto heUE = (TH1D*)GetTH1D(sPath, sFile, sList, "UEErr"); heUE->SetName("heUE");
  heUEK = CancleMaterBudget(heUEK);
  heUE = CancleMaterBudget(heUE);

  auto heUER = (TH1D*)heUE->Clone("heUER");heUER->Reset(); // relative sys. error
  DeNormHistBinWidth(heUEK);
  heUEK = RebinTH1D(heUEK, heUER);
  NormHistBinWidth(heUEK);
  TH1D* heUEr[] = {heUEK, heUE};
  heUER = (TH1D*)QuadraticSum(2, heUEr); heUER->SetName("heUER");
  for(Int_t i = 1; i<= heUER->GetNbinsX(); i++){heUER->SetBinError(i, 0);} 
  auto gUER = (TGraphErrors*)ConvHistogramToGraphErrors(hPCR, heUER, hPCR->GetNbinsX()); gUER->SetName("UERerr");
 
  //---------------------------JEUncer
  
  //===========================StrangeRec
  auto heJEI = (TH1D*)hJER->Clone("heJEI");heJEI->Reset();
  auto heJEi = (TH1D*)heInR->Clone("heJEi");
  DeNormHistBinWidth(heJEi);
  heJEi = RebinTH1D(heJEi, heJEI);
  NormHistBinWidth(heJEi);
  heJEI = heJEi;heJEI->SetName("heJEI");
  for(Int_t i = 1; i<= heJEI->GetNbinsX(); i++){heJEI->SetBinError(i, 0);} 

  //===========================UESub
  auto hJCK = (TH1D*)GetTH1D(sPath, sFile, sListD, "JCCen") ; hJCK->SetName("hJCK");
  auto hP6K = (TH1D*)GetTH1D(sPath, sFile, sListD, "P6Cen") ; hP6K->SetName("hP6K");
  auto hP2K = (TH1D*)GetTH1D(sPath, sFile, sListD, "P2Cen") ; hP2K->SetName("hP2K");
  auto hPCK = (TH1D*)GetTH1D(sPath, sFile, sListD, "UECen") ; hPCK->SetName("hPCK");

  TH1D* hJC = (TH1D*)GetTH1D(sPath, sFile, sList, "JCCen") ; hJC->SetName("hJC");
  TH1D* hP6 = (TH1D*)GetTH1D(sPath, sFile, sList, "P6Cen") ; hP6->SetName("hP6");
  TH1D* hP2 = (TH1D*)GetTH1D(sPath, sFile, sList, "P2Cen") ; hP2->SetName("hP2"); 
  TH1D* hPC = (TH1D*)GetTH1D(sPath, sFile, sList, "UECen") ; hPC->SetName("hPC");

  auto hP6R = (TH1D*)hP6->Clone("hP6R");hP6R->Reset();
  auto hP2R = (TH1D*)hP2->Clone("hP2R");hP2R->Reset();

  DeNormHistBinWidth(hP6K); hP6K = (TH1D*)RebinTH1D(hP6K, hP6R); NormHistBinWidth(hP6K);
  DeNormHistBinWidth(hP2K); hP2K = (TH1D*)RebinTH1D(hP2K, hP6R); NormHistBinWidth(hP2K);

  TH1D* hJCP6 = (TH1D*) hJC->Clone("hJCP6"); TH1D* hJCP6K = (TH1D*) hJCK->Clone("hJCP6K");
  TH1D* hJCP2 = (TH1D*) hJC->Clone("hJCP2"); TH1D* hJCP2K = (TH1D*) hJCK->Clone("hJCP2K");
  DeNormHistBinWidth(hJCP6K); hJCP6K = (TH1D*)RebinTH1D(hJCP6K, hP6R); NormHistBinWidth(hJCP6K);
  DeNormHistBinWidth(hJCP2K); hJCP2K = (TH1D*)RebinTH1D(hJCP2K, hP6R); NormHistBinWidth(hJCP2K);

  hJCP6->Add(hP6, -1.); hJCP2->Add(hP2, -1.);
  hJCP6K->Add(hP6K, -1.); hJCP2K->Add(hP2K, -1.);

  hP6R->Divide(hJCP6, hJCP6K, 1., 2.);
  hP2R->Divide(hJCP2, hJCP2K, 1., 2.);

  
  //TH1D* heP6R = (TH1D*)hJER->Clone("heP6R");
  //TH1D* hePCR = (TH1D*)hJER->Clone("hePCR");
  //TH1D* heP2R = (TH1D*)hJER->Clone("heP2R");
  TH1D* heR = (TH1D*)hJER->Clone("heR");
  
  for(Int_t i = 1; i<= hP6R->GetNbinsX(); i++){
    auto dJER = hJER->GetBinContent(i);
    auto dP6R = hP6R->GetBinContent(i);
    auto dP2R = hP2R->GetBinContent(i);
    heR->SetBinContent(i, TMath::Abs(dP6R-dP2R)/TMath::Sqrt(12.));
    //heP6R->SetBinContent(i, TMath::Abs(dP6R)/TMath::Sqrt(12.));
    //heP2R->SetBinContent(i, TMath::Abs(dP2R)/TMath::Sqrt(12.));
    //hePCR->SetBinContent(i, TMath::Abs(dJER)/TMath::Sqrt(12.));
  }       

  //TH1D* hU[] = {hePCR, heP6R, heP2R};
  //auto hUMax = (TH1D*)MaxHistograms(3, hU);
  //auto hUMin = (TH1D*)MinHistograms(3, hU);
  //hUMax->Add(hUMin, -1.);
  auto hUMax = (TH1D*)heR->Clone("hUMax");
  auto heJEU = (TH1D*)hJER->Clone("heJEU");heJEU->Reset();
  heJEU->Divide(hUMax, hJER, 1., 1.);heJEU->SetName("heJEU");
  for(Int_t i = 1; i<= heJEU->GetNbinsX(); i++){heJEU->SetBinError(i, 0);}

  //===========================JetPt
  TString sFile3 = "JetPtUncer.root"; //Jet Pt Scale Uncertainty 
  auto hJPt0K = (TH1D*)GetTH1D(sPath, sFile3, Form("Kshort_JetPt"), "hist_0"); hJPt0K->SetName("hJPt0K");
  auto hJPt1K = (TH1D*)GetTH1D(sPath, sFile3, Form("Kshort_JetPt"), "hist_1"); hJPt1K->SetName("hJPt1K");
  TH1D* hJPt0 = nullptr;
  TH1D* hJPt1 = nullptr;
  hJPt0 =(TH1D*)GetTH1D(sPath, sFile3, Form("Lambda_JetPt"), "hist_0"); hJPt0->SetName("hJPt0");
  hJPt1 =(TH1D*)GetTH1D(sPath, sFile3, Form("Lambda_JetPt"), "hist_1"); hJPt1->SetName("hJPt1");
  auto hJPt00 =(TH1D*)GetTH1D(sPath, sFile3, Form("AntiLa_JetPt"), "hist_0"); hJPt00->SetName("hJPt00");
  auto hJPt11 =(TH1D*)GetTH1D(sPath, sFile3, Form("AntiLa_JetPt"), "hist_1"); hJPt11->SetName("hJPt11");
  hJPt0->Add(hJPt00);hJPt0->SetName("hJPt0");  hJPt1->Add(hJPt11);hJPt1->SetName("hJPt1");
  
  DeNormHistBinWidth(hJPt0K); hJPt0K = (TH1D*)RebinTH1D(hJPt0K, hJPt0); NormHistBinWidth(hJPt0K);
  DeNormHistBinWidth(hJPt1K); hJPt1K = (TH1D*)RebinTH1D(hJPt1K, hJPt1); NormHistBinWidth(hJPt1K);
  auto hJPt0R = (TH1D*)hJPt0->Clone("hJPt0R");hJPt0R->Reset();
  auto hJPt1R = (TH1D*)hJPt1->Clone("hJPt1R");hJPt1R->Reset();
  hJPt0R->Divide(hJPt0, hJPt0K, 1., 2.); hJPt1R->Divide(hJPt1, hJPt1K, 1., 2.);

  //auto heJPt0R = (TH1D*)hJCR->Clone("heJPt0R");heJPt0R->Reset();
  //auto heJPt1R = (TH1D*)hJCR->Clone("heJPt1R");heJPt1R->Reset();
  auto heJPtR = (TH1D*)hJCR->Clone("heJPtR");heJPtR->Reset();
  for(Int_t i = 1; i<= hJPt0R->GetNbinsX(); i++){
    auto dJER = hJCR->GetBinContent(i);
    auto dJPt0R = hJPt0R->GetBinContent(i);
    auto dJPt1R = hJPt1R->GetBinContent(i);
    //heJPt0R->SetBinContent(i, TMath::Abs(dJPt0R));
    //heJPt1R->SetBinContent(i, TMath::Abs(dJPt1R));
    heJPtR->SetBinContent(i, TMath::Abs(dJPt1R-dJPt0R));
  }
  //TH1D* hJPt[] = {heJPt0R, heJPt1R, hJCR};
  //auto hJPtMax = (TH1D*)MaxHistograms(3, hJPt);
  //auto hJPtMin = (TH1D*)MinHistograms(3, hJPt);
  //hJPtMax->Add(hJPtMin, -1.);
  //hJPtMax->Scale(1./TMath::Sqrt(12.));
  auto hJPtMax = (TH1D*)heJPtR->Clone("hJPtMax");
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
  auto heJCi = (TH1D*)heInR->Clone("heJCi");
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

  TFile *f = TFile::Open("./result/pp.root", "UPDATE");
  TList *l = new TList();

  l->Add(hInR);
  l->Add(hJCR);
  l->Add(hJER);
  l->Add(hPCR);

  l->Add(heInR);
  l->Add(heJCR);
  l->Add(heJER);
  l->Add(heUER);

  l->Add(gInR);
  l->Add(gJCR);
  l->Add(gJER);
  l->Add(gUER);

  l->Add(heJCI);
  l->Add(heJCJ);
  
  l->Add(heJEI);
  l->Add(heJEJ);
  l->Add(heJEU);

  l->Write(Form("Lambda_sum_toKRatio"), TObject::kSingleKey);
  f->Close();

  auto can = MakeCanvas("can");
  auto leg = new TLegend(0.65,0.9,1.0,0.6); SetLegend(leg);
  heJER->GetYaxis()->SetTitle("Relative systematic error");
  heJER->GetYaxis()->SetRangeUser(0, 0.5);
  DrawHisto(heJER, cLine[0], sMark[0], "same");leg->AddEntry(heJER, "Total","l");
  DrawHisto(heJEI, cLine[1], sMark[1], "same");leg->AddEntry(heJEI, "Strange reconstruction","l");
  DrawHisto(heJEJ, cLine[2], sMark[2], "same");leg->AddEntry(heJEJ, "Jet #it{p}_{T} scale","l");
  DrawHisto(heJEU, cLine[3], sMark[3], "same");leg->AddEntry(heJEU, "UE subtraction","l");
  
  //-----------------------------------
  auto tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, "pp at #sqrt{s} = 13 TeV");
  tex->DrawLatex(0.15, 0.83, "Jet: Anti-#it{k}_{T}, #it{R} = 0.4");
  tex->DrawLatex(0.15, 0.75, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#it{#eta}_{jet}| < 0.35");
  tex->DrawLatex(0.15, 0.65, Form("#Lambda/K^{0}_{S}"));
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/Uncert/LKRatio_JCUncert.pdf"));
  can->SaveAs(Form("./figure/Uncert/LKRatio_JCUncert.eps"));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);


  return;
}
