#include "./inc/SourceFun.h"

void XLRatioUncer(){
  
  auto sPath = "./result"; 
  auto sFile = "pp.root";  
  
  //---------------------------GetCentRatio
  auto CFile = "CentVal.root";
  auto CListIn = "listIn";
  auto CListJE = "listJE";
  auto CListJC = "listJC";
  auto CListPC = "listPC";
  auto CListOC = "listOC04";
  auto CListNJ = "listNJ";
 
  auto hInR = (TH1D*)GetTH1D(sPath, CFile, CListIn, Form("hXLRatio")); hInR->SetName("hInR"); ;
  auto hJCR = (TH1D*)GetTH1D(sPath, CFile, CListJC, Form("hXLRatio")); hJCR->SetName("hJCR"); ;
  auto hPCR = (TH1D*)GetTH1D(sPath, CFile, CListPC, Form("hXLRatio")); hPCR->SetName("hUER"); ;
  auto hJER = (TH1D*)GetTH1D(sPath, CFile, CListJE, Form("hXLRatio")); hJER->SetName("hJER"); ;


  auto sListD =  Form("Lambda_sum");
  auto sList =  Form("Xi"); 
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
  auto hNJK = (TH1D*)GetTH1D(sPath, sFile, sListD, "NJCen") ; hNJK->SetName("hNJK");
  auto hOCK = (TH1D*)GetTH1D(sPath, sFile, sListD, "OCCen") ; hOCK->SetName("hOCK");
  auto hPCK = (TH1D*)GetTH1D(sPath, sFile, sListD, "UECen") ; hPCK->SetName("hPCK");

  TH1D* hJC = (TH1D*)GetTH1D(sPath, sFile, sList, "JCCen") ; hJC->SetName("hJC");
  TH1D* hNJ = (TH1D*)GetTH1D(sPath, sFile, sList, "NJCen") ; hNJ->SetName("hNJ");
  TH1D* hOC = (TH1D*)GetTH1D(sPath, sFile, sList, "OCCen") ; hOC->SetName("hOC"); 
  TH1D* hPC = (TH1D*)GetTH1D(sPath, sFile, sList, "UECen") ; hPC->SetName("hPC");

  auto hNJR = (TH1D*)hNJ->Clone("hNJR");hNJR->Reset();
  auto hOCR = (TH1D*)hOC->Clone("hOCR");hOCR->Reset();

  DeNormHistBinWidth(hNJK); hNJK = (TH1D*)RebinTH1D(hNJK, hNJR); NormHistBinWidth(hNJK);
  DeNormHistBinWidth(hOCK); hOCK = (TH1D*)RebinTH1D(hOCK, hNJR); NormHistBinWidth(hOCK);

  TH1D* hJCNJ = (TH1D*) hJC->Clone("hJCNJ"); TH1D* hJCNJK = (TH1D*) hJCK->Clone("hJCNJK");
  TH1D* hJCOC = (TH1D*) hJC->Clone("hJCOC"); TH1D* hJCOCK = (TH1D*) hJCK->Clone("hJCOCK");
  DeNormHistBinWidth(hJCNJK); hJCNJK = (TH1D*)RebinTH1D(hJCNJK, hNJR); NormHistBinWidth(hJCNJK);
  DeNormHistBinWidth(hJCOCK); hJCOCK = (TH1D*)RebinTH1D(hJCOCK, hNJR); NormHistBinWidth(hJCOCK);

  hJCNJ->Add(hNJ, -1.); hJCOC->Add(hOC, -1.);
  hJCNJK->Add(hNJK, -1.); hJCOCK->Add(hOCK, -1.);

  hNJR->Divide(hJCNJ, hJCNJK, 1., 1.);
  hOCR->Divide(hJCOC, hJCOCK, 1., 1.);

  
  TH1D* heNJR = (TH1D*)hJER->Clone("heNJR");
  TH1D* hePCR = (TH1D*)hJER->Clone("hePCR");
  TH1D* heOCR = (TH1D*)hJER->Clone("heOCR");
  
  for(Int_t i = 1; i<= hNJR->GetNbinsX(); i++){
    auto dJER = hJER->GetBinContent(i);
    auto dNJR = hNJR->GetBinContent(i);
    auto dOCR = hOCR->GetBinContent(i);
    heNJR->SetBinContent(i, TMath::Abs(dNJR)/TMath::Sqrt(12.));
    heOCR->SetBinContent(i, TMath::Abs(dOCR)/TMath::Sqrt(12.));
    hePCR->SetBinContent(i, TMath::Abs(dJER)/TMath::Sqrt(12.));
  }       

  TH1D* hU[] = {hePCR, heNJR, heOCR};
  auto hUMax = (TH1D*)MaxHistograms(3, hU);
  auto hUMin = (TH1D*)MinHistograms(3, hU);
  hUMax->Add(hUMin, -1.);
  auto heJEU = (TH1D*)hJER->Clone("heJEU");heJEU->Reset();
  heJEU->Divide(hUMax, hJER, 1., 1.);heJEU->SetName("heJEU");
  for(Int_t i = 1; i<= heJEU->GetNbinsX(); i++){heJEU->SetBinError(i, 0);}

  //===========================JetPt
  TString sFile3 = "JetPtUncer.root"; //Jet Pt Scale Uncertainty 
  auto hJPt0K = (TH1D*)GetTH1D(sPath, sFile3, Form("Lambda_JetPt"), "hist_0"); hJPt0K->SetName("hJPt0K");
  auto hJPt1K = (TH1D*)GetTH1D(sPath, sFile3, Form("Lambda_JetPt"), "hist_1"); hJPt1K->SetName("hJPt1K");
  auto hJPt00 =(TH1D*)GetTH1D(sPath, sFile3, Form("AntiLa_JetPt"), "hist_0"); hJPt00->SetName("hJPt00");
  auto hJPt11 =(TH1D*)GetTH1D(sPath, sFile3, Form("AntiLa_JetPt"), "hist_1"); hJPt11->SetName("hJPt11");
  hJPt0K->Add(hJPt00);hJPt0K->SetName("hJPt0K");  hJPt1K->Add(hJPt11);hJPt1K->SetName("hJPt1K");

  
  TH1D* hJPt0 = nullptr;
  TH1D* hJPt1 = nullptr;
  hJPt0 =(TH1D*)GetTH1D(sPath, sFile3, Form("Xi_JetPt"), "hist_0"); hJPt0->SetName("hJPt0");
  hJPt1 =(TH1D*)GetTH1D(sPath, sFile3, Form("Xi_JetPt"), "hist_1"); hJPt1->SetName("hJPt1");
  
  DeNormHistBinWidth(hJPt0K); hJPt0K = (TH1D*)RebinTH1D(hJPt0K, hJPt0); NormHistBinWidth(hJPt0K);
  DeNormHistBinWidth(hJPt1K); hJPt1K = (TH1D*)RebinTH1D(hJPt1K, hJPt1); NormHistBinWidth(hJPt1K);
  auto hJPt0R = (TH1D*)hJPt0->Clone("hJPt0R");hJPt0R->Reset();
  auto hJPt1R = (TH1D*)hJPt1->Clone("hJPt1R");hJPt1R->Reset();
  hJPt0R->Divide(hJPt0, hJPt0K, 1., 1.); hJPt1R->Divide(hJPt1, hJPt1K, 1., 1.);

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

  l->Write(Form("Xi_toLRatio"), TObject::kSingleKey);
  f->Close();


  return;
}
