#include "./inc/SourceFun.h"

void TotUncer(const TString sType = "Lambda"){
  
  auto sPath = "./result"; 
  auto sCFile = "CentVal.root";
 
  auto sCInclList = "listIn"; 
  auto sCInclHist = Form("h%s", sType.Data());
  auto sEInclFile = "InclUncer.root";
  auto sEInclHist = Form("%s_InclUncer", sType.Data());
  
  auto sCJEList = "listJE"; 
  auto sCJetHist = Form("h%s", sType.Data());

  auto sCJCList = "listJC"; 
  auto sCJCHist = Form("h%s", sType.Data());
  
  auto sEJetFile = "JetPtUncer.root";
  auto sEJetList = Form("%s_JetPt", sType.Data());
  
  auto sCPCList = "listPC04"; 
  auto sCUEHist = Form("h%s", sType.Data());
  auto sEUEFile = "UEUncer.root";
  auto sEUEList = Form("%s_UESub", sType.Data());

  auto sLatex(Form("pp #sqrt{#it{s}} = 13 TeV"));
  Double_t XMin = 0.6;
  Double_t XMax = 12.;
  
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  
  //const auto dMaterial = 0.04; 
  //-----------------------------------
  auto hIncl1 = (TH1D*)GetTH1D(sPath, sCFile, sCInclList, sCInclHist); hIncl1->SetName("InclCen");
  auto hIncl2 = (TH1D*)GetTH1D(sPath, sEInclFile, "", sEInclHist); hIncl2->SetName("InclErr");
  auto hIncl3 = (TH1D*)hIncl1->Clone("InclErrAbs");//Inclusive Abs Uncer
  auto hIErr = (TH1D*)hIncl1->Clone("hIErr"); hIErr->Reset();//Inclusve Relative Uncer 
  
  auto hUE1   = (TH1D*)GetTH1D(sPath, sCFile, sCPCList, sCUEHist); hUE1->SetName("UECen");
  auto hUE2 = (TH1D*)GetTH1D(sPath, sEUEFile, sEUEList, "hMax"); hUE2->SetName("UEErrAbs");
  auto hUE3 = (TH1D*)hUE2->Clone("UEErr");//UE Abs Uncer
  auto hUErr = (TH1D*)hUE1->Clone("hUErr"); hUErr->Reset();//UE Relative Uncer
  
  auto hJE1  = (TH1D*)GetTH1D(sPath, sCFile, sCJEList, sCJetHist); hJE1->SetName("JECen");
  auto hJE2 = (TH1D*)GetTH1D(sPath, sEJetFile, sEJetList, "hMax"); hJE2->SetName("JCErr");
  auto hJE3 = (TH1D*)hJE1->Clone("JEErr"); hJE3->Reset();//JE Abs Uncer
  auto hJErr = (TH1D*)hJE1->Clone("hJErr"); hJErr->Reset();//JE Relative Uncer
  
  auto hJC1  = (TH1D*)GetTH1D(sPath, sCFile, sCJCList, sCJCHist); hJC1->SetName("JCCen");
  auto hJCErr = (TH1D*)hJC1->Clone("hJCErr"); hJCErr->Reset();//JC Relative Uncer


  auto hJErrContI = (TH1D*)hJE1->Clone("hJErrContI"); hJErrContI->Reset();//Strange reconstruction Uncertainty contribution to JE spectrum 
  auto hJErrContU = (TH1D*)hJE1->Clone("hJErrContU"); hJErrContU->Reset();//UE substruction Uncertainty contribution to JE spectrum 
  auto hJErrContJ = (TH1D*)hJE2->Clone("hJErrContJ"); //Jet pT Scale Uncertainty contribution to JE spectrum 

 
  //-----------------------------------
  const auto nI = hIncl1->GetNbinsX();
  const auto nJ = hJE1->GetNbinsX();
  
  //
  //Inclusive Uncertainty
  //
  Double_t InclErr[nI]; 
  for(Int_t i = 1; i<=nI; i++){
    auto CIncl = hIncl1->GetBinContent(i); 
    auto EIncl = hIncl2->GetBinContent(i);
    hIErr->SetBinContent(i, EIncl);//Relative uncertainty of Inclusive spectrum
    InclErr[i-1] = CIncl*EIncl;
    hIncl3->SetBinContent(i, InclErr[i-1]);//Absolut vaule of Inclusive Uncertainty
  }
  hIErr->SetName("hIErr");
  auto hIJ3 = (TH1D*)hJE1->Clone("IJErr"); hIJ3->Reset();//Inclusive Abs Uncer with JC bins
  DeNormHistBinWidth(hIncl3); 
  hIJ3 = RebinTH1D(hIncl3, hIJ3);//Convert Inclusvie Abs vaule to JC bins
  NormHistBinWidth(hIJ3); 

  Double_t JetPtErr[nJ];
  Double_t UESubErr[nJ];
  for(Int_t i = 1; i<=nJ; i++){
    //
    //Jet pT scale Uncertainty
    //
    auto CJC = hJC1->GetBinContent(i);
    auto CJE = hJE1->GetBinContent(i);
    auto EJE = hJE2->GetBinContent(i);
    JetPtErr[i-1] = CJC*EJE;
    hJE3->SetBinContent(i, JetPtErr[i-1]);
    hJErrContJ->SetBinContent(i, JetPtErr[i-1]/CJE);
    //Inclusive Uncertainty
    auto IJabs = hIJ3->GetBinContent(i);
    auto IJRel = IJabs/CJE;
    hJErrContI->SetBinContent(i, IJRel);//
    //
    //UE substructed contribution
    //
    auto CUE = hUE1->GetBinContent(i);
    auto EUE = hUE2->GetBinContent(i);
    UESubErr[i-1] = EUE;
    hJErrContU->SetBinContent(i, EUE/CJE);//
    hJErrContJ->SetBinError(i, 0); 
  }
  TH1D *hSum[] = {hJErrContI, hJErrContJ, hJErrContU};
  hJErr = (TH1D*)QuadraticSum(3, hSum); 
  for(Int_t i = 1; i<=nJ; i++){hJErr->SetBinError(i, 0);}
  hJErr->SetName("hJErr");
  
  //
  //JC Uncertainty
  //
  //Inclusive
  auto hIJCErr = (TH1D*)hIJ3->Clone("hIJCErr");
  for(Int_t i = 1; i<=nJ; i++){hIJCErr->SetBinContent(i, (hIJCErr->GetBinContent(i))/(hJC1->GetBinContent(i)));}
  //Jet pt hJE2 
  TH1D *hsum[] = {hIJCErr, hJE2};
  hJCErr = (TH1D*)QuadraticSum(2, hsum);
  hJCErr->SetName("hJCErr");
  for(Int_t i = 1; i<=nJ; i++){hJCErr->SetBinError(i, 0);}

  //
  //UE Uncertainty
  //
  auto hIUErr = (TH1D*)hIErr->Clone("hIUErr");
  DeNormHistBinWidth(hIUErr); 
  hUErr = RebinTH1D(hIUErr, hUErr);//Relative uncertainty of UE spectrum
  NormHistBinWidth(hUErr); 
  hUErr->SetName("hUErr");
  
  TFile *f = TFile::Open("./result/TotUncer.root", "UPDATE");
  TList *l = new TList();
  l->Add(hIErr);
  l->Add(hJErr);
  l->Add(hUErr);
  l->Add(hJCErr);
  l->Add(hJErrContI);
  l->Add(hJErrContJ);
  l->Add(hJErrContU);
  l->Write(Form("%s_UncerTot",sType.Data()), TObject::kSingleKey);
  f->Close();
  
  can = MakeCanvas("can");
  leg = new TLegend(0.65,0.9,1.0,0.6); SetLegend(leg);
  DrawHisto(hJErr, cLine[0], sMark[0], "same"); leg->AddEntry(hJErr, "Total","l");
  hJErr->GetYaxis()->SetTitle("Relative systematic error");
  hJErr->GetYaxis()->SetRangeUser(0, 0.5);
  DrawHisto(hJErrContI, cLine[1], sMark[1], "same");leg->AddEntry(hJErrContI, "Strange reconstruction","l");
  DrawHisto(hJErrContJ, cLine[2], sMark[2], "same");leg->AddEntry(hJErrContJ, "Jet #it{p}_{T} scale","l");
  DrawHisto(hJErrContU, cLine[3], sMark[3], "same");leg->AddEntry(hJErrContU, "UE subtraction","l");
 
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  tex->DrawLatex(0.15, 0.83, "Jet: Anti-#it{k}_{T}, #it{R} = 0.4");
  tex->DrawLatex(0.15, 0.75, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#it{#eta}_{jet}| < 0.35");
  tex->DrawLatex(0.15, 0.65, Form("%s", sType.Data()));
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/Uncert/%s_JCUncert.pdf", sType.Data()));
  can->SaveAs(Form("./figure/Uncert/%s_JCUncert.eps", sType.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
