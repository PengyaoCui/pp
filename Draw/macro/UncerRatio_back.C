#include "./SourceFun.h"

void UncerRatio(const TString CentMin = "0", const TString CentMax = "10"){
  
  const TString sPK = "Kshort";
  const TString sPL = "Lambda";
  const TString sPA = "AntiLa";
  const TString sPX = "Xi";
  
  auto sPath = "./result"; 
  
  //-----------------------------------
  auto sEFile = "UncertaintyTot.root";
  auto sELK = Form("%s_UncerTot_%s%s", sPK.Data(), CentMin.Data(), CentMax.Data());
  auto sELL = Form("%s_UncerTot_%s%s", sPL.Data(), CentMin.Data(), CentMax.Data());
  auto sELA = Form("%s_UncerTot_%s%s", sPA.Data(), CentMin.Data(), CentMax.Data());
  auto sELX = Form("%s_UncerTot_%s%s", sPX.Data(), CentMin.Data(), CentMax.Data());
  
  auto sEIH = "hIErr";  
  
  //-----------------------------------
  auto sCFile = "PtSpect_Eta.root";

  auto sCIHK = Form("hPtIncl_%s_%s%s", sPK.Data(), CentMin.Data(), CentMax.Data());//Inclusive center value Hist 
  auto sCIHL = Form("hPtIncl_%s_%s%s", sPL.Data(), CentMin.Data(), CentMax.Data());
  auto sCIHA = Form("hPtIncl_%s_%s%s", sPA.Data(), CentMin.Data(), CentMax.Data());
  auto sCIHX = Form("hPtIncl_%s_%s%s", sPX.Data(), CentMin.Data(), CentMax.Data());
  
  auto sCJHK = Form("hPtJE_%s_%s%s", sPK.Data(), CentMin.Data(), CentMax.Data());//JE center value Hist 
  auto sCJHL = Form("hPtJC_%s_%s%s", sPL.Data(), CentMin.Data(), CentMax.Data());//JE center value Hist 
  auto sCJHA = Form("hPtJC_%s_%s%s", sPA.Data(), CentMin.Data(), CentMax.Data());//JE center value Hist 
  auto sCJHX = Form("hPtJE_%s_%s%s", sPX.Data(), CentMin.Data(), CentMax.Data());//JE center value Hist 
  
  auto sCUHK = Form("hPtPC_%s_%s%s", sPK.Data(), CentMin.Data(), CentMax.Data());//UE center value Hist 
  auto sCUHL = Form("hPtPC_%s_%s%s", sPL.Data(), CentMin.Data(), CentMax.Data());//UE center value Hist 
  auto sCUHA = Form("hPtPC_%s_%s%s", sPA.Data(), CentMin.Data(), CentMax.Data());//UE center value Hist 
  auto sCUHX = Form("hPtPC_%s_%s%s", sPX.Data(), CentMin.Data(), CentMax.Data());//UE center value Hist 
  
  auto sCNHK = Form("hPtNJ_%s_%s%s", sPK.Data(), CentMin.Data(), CentMax.Data());
  auto sCNHL = Form("hPtNJ_%s_%s%s", sPL.Data(), CentMin.Data(), CentMax.Data());
  auto sCNHA = Form("hPtNJ_%s_%s%s", sPA.Data(), CentMin.Data(), CentMax.Data());
  auto sCNHX = Form("hPtNJ_%s_%s%s", sPX.Data(), CentMin.Data(), CentMax.Data());
  auto sCOHK = Form("hPtOC_%s_%s%s", sPK.Data(), CentMin.Data(), CentMax.Data());
  auto sCOHL = Form("hPtOC_%s_%s%s", sPL.Data(), CentMin.Data(), CentMax.Data());
  auto sCOHA = Form("hPtOC_%s_%s%s", sPA.Data(), CentMin.Data(), CentMax.Data());
  auto sCOHX = Form("hPtOC_%s_%s%s", sPX.Data(), CentMin.Data(), CentMax.Data());
  //===================================
  auto hCIK = (TH1D*)GetTH1D(sPath, sCFile, "", sCIHK); hCIK->SetName("hCIK");
  auto hCIL = (TH1D*)GetTH1D(sPath, sCFile, "", sCIHL); hCIL->SetName("hCIL");
  auto hCIA = (TH1D*)GetTH1D(sPath, sCFile, "", sCIHA); hCIA->SetName("hCIA");
  auto hCIX = (TH1D*)GetTH1D(sPath, sCFile, "", sCIHX); hCIX->SetName("hCIX");

  auto hCJK = (TH1D*)GetTH1D(sPath, sCFile, "", sCJHK); hCJK->SetName("hCJK");
  auto hCJL = (TH1D*)GetTH1D(sPath, sCFile, "", sCJHL); hCJL->SetName("hCJL");
  auto hCJA = (TH1D*)GetTH1D(sPath, sCFile, "", sCJHA); hCJA->SetName("hCJA");
  auto hCJX = (TH1D*)GetTH1D(sPath, sCFile, "", sCJHX); hCJX->SetName("hCJX");
                                                                          
  auto hCUK = (TH1D*)GetTH1D(sPath, sCFile, "", sCUHK); hCUK->SetName("hCUK");
  auto hCUL = (TH1D*)GetTH1D(sPath, sCFile, "", sCUHL); hCUL->SetName("hCUL");
  auto hCUA = (TH1D*)GetTH1D(sPath, sCFile, "", sCUHA); hCUA->SetName("hCUA");
  auto hCUX = (TH1D*)GetTH1D(sPath, sCFile, "", sCUHX); hCUX->SetName("hCUX");
  
  auto hCOK = (TH1D*)GetTH1D(sPath, sCFile, "", sCOHK); hCOK->SetName("hCOK");
  auto hCOL = (TH1D*)GetTH1D(sPath, sCFile, "", sCOHL); hCOL->SetName("hCOL");
  auto hCOA = (TH1D*)GetTH1D(sPath, sCFile, "", sCOHA); hCOA->SetName("hCOA");
  auto hCOX = (TH1D*)GetTH1D(sPath, sCFile, "", sCOHX); hCOX->SetName("hCOX");

  auto hCNK = (TH1D*)GetTH1D(sPath, sCFile, "", sCNHK); hCNK->SetName("hCNK");
  auto hCNL = (TH1D*)GetTH1D(sPath, sCFile, "", sCNHL); hCNL->SetName("hCNL");
  auto hCNA = (TH1D*)GetTH1D(sPath, sCFile, "", sCNHA); hCNA->SetName("hCNA");
  auto hCNX = (TH1D*)GetTH1D(sPath, sCFile, "", sCNHX); hCNX->SetName("hCNX");
  //-----------------------------------
  auto hEIK = (TH1D*)GetTH1D(sPath, sEFile, sELK, sEIH); hEIK->SetName("hEIK");
  auto hEIL = (TH1D*)GetTH1D(sPath, sEFile, sELL, sEIH); hEIL->SetName("hEIL");
  auto hEIA = (TH1D*)GetTH1D(sPath, sEFile, sELA, sEIH); hEIA->SetName("hEIA");
  auto hEIX = (TH1D*)GetTH1D(sPath, sEFile, sELX, sEIH); hEIX->SetName("hEIX");

  //-----------------------------------
  TString sJFile = "JetPtUncertainty.root"; //Jet Pt Scale Uncertainty 
  TString sJELK = Form("%s_JetPt_%s%s", sPK.Data(), CentMin.Data(), CentMax.Data());
  TString sJELL = Form("%s_JetPt_%s%s", sPL.Data(), CentMin.Data(), CentMax.Data());
  TString sJELA = Form("%s_JetPt_%s%s", sPA.Data(), CentMin.Data(), CentMax.Data());
  TString sJELX = Form("%s_JetPt_%s%s", sPX.Data(), CentMin.Data(), CentMax.Data());
  TString sJH0 = "hist_0"; TString sJH1 = "hist_1";

  auto hJK0 = GetTH1D(sPath, sJFile, sJELK, sJH0);hJK0->SetName("hJK0");
  auto hJK1 = GetTH1D(sPath, sJFile, sJELK, sJH1);hJK1->SetName("hJK1");
  auto hJL0 = GetTH1D(sPath, sJFile, sJELL, sJH0);hJL0->SetName("hJL0");
  auto hJL1 = GetTH1D(sPath, sJFile, sJELL, sJH1);hJL1->SetName("hJL1");
  auto hJA0 = GetTH1D(sPath, sJFile, sJELA, sJH0);hJA0->SetName("hJA0");
  auto hJA1 = GetTH1D(sPath, sJFile, sJELA, sJH1);hJA1->SetName("hJA1");
  auto hJX0 = GetTH1D(sPath, sJFile, sJELX, sJH0);hJX0->SetName("hJX0");
  auto hJX1 = GetTH1D(sPath, sJFile, sJELX, sJH1);hJX1->SetName("hJX1");

  //-----------------------------------
  
  auto hCILKR=(TH1D*)hCIK->Clone("hCILKR"); hCILKR->Reset();
  auto hCJLKR=(TH1D*)hCJK->Clone("hCJLKR"); hCJLKR->Reset();
  auto hCULKR=(TH1D*)hCUK->Clone("hCULKR"); hCULKR->Reset();
  
  auto hEILKR=(TH1D*)hCIK->Clone("hEILKR"); hEILKR->Reset();
  auto hEJLKR=(TH1D*)hCJK->Clone("hEJLKR"); hEJLKR->Reset();
  auto hEULKR=(TH1D*)hCUK->Clone("hEULKR"); hEULKR->Reset();
  
  auto hEJCILKR=(TH1D*)hCJK->Clone("hEJCILKR"); hEJCILKR->Reset();
  auto hEJCJLKR=(TH1D*)hCJK->Clone("hEJCJLKR"); hEJCJLKR->Reset();
  auto hEJCULKR=(TH1D*)hCJK->Clone("hEJCULKR"); hEJCULKR->Reset();
  //-----------------------------------
  auto hCIXKR=(TH1D*)hCIK->Clone("hCIXKR"); hCIXKR->Reset();
  auto hCJXKR=(TH1D*)hCJK->Clone("hCJXKR"); hCJXKR->Reset();
  auto hCUXKR=(TH1D*)hCUK->Clone("hCUXKR"); hCUXKR->Reset();
  
  auto hEIXKR=(TH1D*)hCIK->Clone("hEIXKR"); hEIXKR->Reset();
  auto hEJXKR=(TH1D*)hCJK->Clone("hEJXKR"); hEJXKR->Reset();
  auto hEUXKR=(TH1D*)hCUK->Clone("hEUXKR"); hEUXKR->Reset();
  
  auto hEJCIXKR=(TH1D*)hCJK->Clone("hEJCIXKR"); hEJCIXKR->Reset();
  auto hEJCJXKR=(TH1D*)hCJK->Clone("hEJCJXKR"); hEJCJXKR->Reset();
  auto hEJCUXKR=(TH1D*)hCJK->Clone("hEJCUXKR"); hEJCUXKR->Reset();
  //-----------------------------------
  const auto nI = hCIK->GetNbinsX();
  const auto nJ = hCJK->GetNbinsX();
  
  //
  //Inclusive Uncertainty
  //
  hCILKR->Add(hCIL, hCIA); hCILKR->Divide(hCILKR, hCIK, 1., 2.); hCILKR->SetName("hCILKR");
  hCIXKR->Divide(hCIX, hCIK, 1., 2.); hCIXKR->SetName("hCIXKR");
  Double_t dEILK[nI];
  Double_t dEIXK[nI];
  for(Int_t i = 1; i<=nI; i++){
    auto dCIK = hCIK->GetBinContent(i); 
    auto dEIK = hEIK->GetBinContent(i)*dCIK;
    auto dCIL = hCIL->GetBinContent(i); 
    auto dEIL = hEIL->GetBinContent(i)*dCIL;
    auto dCIA = hCIA->GetBinContent(i); 
    auto dEIA = hEIA->GetBinContent(i)*dCIA; 
    auto dCIX = hCIX->GetBinContent(i); 
    auto dEIX = hEIX->GetBinContent(i)*dCIX;
   
    auto dCILKR = (dCIA+dCIL)/(2*dCIK);
    auto dEILKR = TMath::Sqrt((1./(4.*dCIK*dCIK))*(dEIL*dEIL + dEIA*dEIA + ((dCIL+dCIA)*(dCIL+dCIA)/(dCIK*dCIK))*dEIK*dEIK));
    dEILK[nI-1] = dEILKR; 
    hEILKR->SetBinContent(i, dEILKR/dCILKR); 
    auto dCIXKR = dCIX/(2*dCIK);
    auto dEIXKR = TMath::Sqrt((1./(4.*dCIK*dCIK))*(dEIX*dEIX + ((dCIX*dCIX)/(dCIK*dCIK))*dEIK*dEIK));
    dEIXK[nI-1] = dEIXKR; 
    hEIXKR->SetBinContent(i, dEIXKR/dCIXKR); 
  }
  
  //
  //JC Strange rec 
  //
  auto hEIJLKR = (TH1D*)hEILKR->Clone("hEIJLKR");
  DeNormHistBinWidth(hEIJLKR); 
  hEJCILKR = RebinTH1D(hEIJLKR, hEJCILKR);
  NormHistBinWidth(hEJCILKR); 
  hEJCILKR->SetName("hEJCILKR");

  auto hEIJXKR = (TH1D*)hEIXKR->Clone("hEIJXKR");
  DeNormHistBinWidth(hEIJXKR); 
  hEJCIXKR = RebinTH1D(hEIJXKR, hEJCIXKR);
  NormHistBinWidth(hEJCIXKR); 
  hEJCIXKR->SetName("hEJCIXKR");
  
  //
  //JC Jet pT scale 
  //
  auto hEJCJLKR0=(TH1D*)hEJCJLKR->Clone("hEJCJLKR0"); hEJCJLKR0->Reset();
  auto hEJCJLKR1=(TH1D*)hEJCJLKR->Clone("hEJCJLKR1"); hEJCJLKR1->Reset();
  hJL0->Add(hJA0); hJK0->Scale(2.); hJL0->Divide(hJK0); 
  hEJCJLKR0 = hJL0; 
  hJL1->Add(hJA1); hJK1->Scale(2.); hJL1->Divide(hJK1); 
  hEJCJLKR1 = hJL1;
  hCJLKR->Add(hCJL, hCJA); hCJLKR->Divide(hCJLKR, hCJK, 1., 2.); hCJLKR->SetName("hCJLKR");
  for(Int_t i = 1; i<=nJ; i++){
    auto dJ0 = hEJCJLKR0->GetBinContent(i); 
    auto dJ1 = hEJCJLKR1->GetBinContent(i); 
    auto dJ = hCJLKR->GetBinContent(i); 
    auto dEJLKR = TMath::Max(TMath::Abs(dJ0-dJ), TMath::Abs(dJ1-dJ));
    hEJCJLKR->SetBinContent(i, dEJLKR/dJ);
  }
  
  auto hEJCJXKR0=(TH1D*)hEJCJXKR->Clone("hEJCJXKR0"); hEJCJXKR0->Reset();
  auto hEJCJXKR1=(TH1D*)hEJCJXKR->Clone("hEJCJXKR1"); hEJCJXKR1->Reset();
  hJX0->Divide(hJK0); 
  hEJCJXKR0 = hJX0; 
  hJX1->Divide(hJK1); 
  hEJCJLKR1 = hJL1;
  hCJLKR->Add(hCJL, hCJA); hCJLKR->Divide(hCJLKR, hCJK, 1., 2.); hCJLKR->SetName("hCJLKR");
  for(Int_t i = 1; i<=nJ; i++){
    auto dJ0 = hEJCJLKR0->GetBinContent(i); 
    auto dJ1 = hEJCJLKR1->GetBinContent(i); 
    auto dJ = hCJLKR->GetBinContent(i); 
    auto dEJLKR = TMath::Max(TMath::Abs(dJ0-dJ), TMath::Abs(dJ1-dJ));
    hEJCJLKR->SetBinContent(i, dEJLKR/dJ);
  }
  //
  //JC UE subtract 
  //

  hCULKR->Add(hCUL, hCUA); hCULKR->Divide(hCULKR, hCUK, 1., 2.); hCULKR->SetName("hCULKR");
  auto hCNLKR=(TH1D*)hCULKR->Clone("hCNLKR"); hCNLKR->Reset();
  hCNLKR->Add(hCNL, hCNA); hCNLKR->Divide(hCNLKR, hCNK, 1., 2.); hCNLKR->SetName("hCNLKR");
  auto hCOLKR=(TH1D*)hCULKR->Clone("hCOLKR"); hCOLKR->Reset();
  hCOLKR->Add(hCOL, hCOA); hCOLKR->Divide(hCOLKR, hCOK, 1., 2.); hCOLKR->SetName("hCOLKR");
  
  for(Int_t i = 1; i<=nJ; i++){
    auto dO = hCOLKR->GetBinContent(i); 
    auto dN = hCNLKR->GetBinContent(i); 
    auto dU = hCULKR->GetBinContent(i);
    auto dJ = hCJLKR->GetBinContent(i); 
    //auto dEULKR = TMath::Max(TMath::Abs(dO-dU), TMath::Abs(dN-dU));
    auto dEULKR = TMath::Abs(dO-dU);
    hEJCULKR->SetBinContent(i, dEULKR/(TMath::Sqrt(12.)*dJ));
  }
  TH1D *hSum[] = {hEJCILKR, hEJCJLKR, hEJCULKR};
  hEJLKR = (TH1D*)QuadraticSum(3, hSum);hEJLKR->SetName("hEJLKR"); 

  auto hEIULKR = (TH1D*)hEILKR->Clone("hEIULKR");
  DeNormHistBinWidth(hEIULKR); 
  hEULKR = RebinTH1D(hEIULKR, hEULKR);
  NormHistBinWidth(hEULKR); 
  hEULKR->SetName("hEULKR"); 
  for(Int_t i = 1; i<=nJ; i++){
    auto dCU = hCULKR->GetBinContent(i);
    auto dEU = hEULKR->GetBinContent(i);
    hEULKR->SetBinContent(i, dEU/dCU);
  }

  TFile *f = TFile::Open("./result/UncertaintyRatio.root", "UPDATE");
  TList *l = new TList();
  l->Add(hCILKR);
  l->Add(hCJLKR);
  l->Add(hCULKR);
  l->Add(hCOLKR);
  l->Add(hCNLKR);
  l->Add(hEILKR);
  l->Add(hEJLKR);
  l->Add(hEULKR);
  l->Add(hEJCILKR);
  l->Add(hEJCJLKR);
  l->Add(hEJCULKR);
  
  l->Write(Form("LKR_Uncer_%s%s", CentMin.Data(), CentMax.Data()), TObject::kSingleKey);
  f->Close();

  auto sLatex(Form("p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV"));
  Double_t XMin = 0.6;
  Double_t XMax = 12.;
  
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  
  can = MakeCanvas("can");
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  DrawHisto(hEJLKR, cLine[0], sMark[0], "same"); leg->AddEntry(hEJLKR, "Total","l");
  hEJLKR->GetYaxis()->SetTitle("Relative systematic error");
  hEJLKR->GetYaxis()->SetRangeUser(0, 1);
  DrawHisto(hEJCILKR, cLine[1], sMark[1], "same");leg->AddEntry(hEJCILKR, "Strange reconstruction","l");
  DrawHisto(hEJCJLKR, cLine[2], sMark[2], "same");leg->AddEntry(hEJCJLKR, "Jet #it{p}_{T} scale","l");
  DrawHisto(hEJCULKR, cLine[3], sMark[3], "same");leg->AddEntry(hEJCULKR, "UE subtraction","l");
 
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  tex->DrawLatex(0.15, 0.83, "Jet: Anti-#it{k}_{T}, #it{R} = 0.4");
  tex->DrawLatex(0.15, 0.75, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#it{#eta}_{jet}| < 0.35");
  tex->DrawLatex(0.15, 0.63, Form("#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}} %s-%s%%", CentMin.Data(), CentMax.Data()));
  leg->Draw();
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/LKR_JCUncertCont_%s%s.eps", CentMin.Data(), CentMax.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
