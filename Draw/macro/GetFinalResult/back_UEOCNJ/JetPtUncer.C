#include "./inc/SourceFun.h"

void JetPtUncer(const TString sType = "Kshort"){
               
  TString sCut[] = {"Tight", "Loose"}; 

  TString sPath = "/home/cuipengyao/study/pp/Local/ThisAna/Uncertainty/JE/JetPt";
  if(sType == "Omega") sPath = "/home/cuipengyao/study/pp/Local/ThisAna/Uncertainty/JE_Omega/JetPt";
 
  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = "listResults";
  TString sHist = "hNco";
  TString List = Form("%s_%s_Default_JC", sList.Data(), sType.Data());

  TString sLeg = "Total";

  auto sLatex(Form("Uncertainty of %s", sType.Data()));
  Double_t XMin = 0.6;
  Double_t XMax = 12.;
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(sCut)/sizeof(TString);
  const auto nhist = nHist;

  TH1D* h2 = nullptr;
  TH1D* hUE2 = nullptr;
  TH1D* h1 = nullptr;
  TH1D* hUE1 = nullptr;
  TH1D* hRatio = nullptr;
  TH1D* hU[nhist+1];
  if(sType != "Omega")h2 = (TH1D*)GetTH1D(Form("/home/cuipengyao/study/pp/Local/ThisAna/JE/%s", sType.Data()), sFile.Data(), List.Data(), sHist.Data());
  if(sType == "Omega")h2 = (TH1D*)GetTH1D(Form("/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins/%s", sType.Data()), sFile.Data(), List.Data(), sHist.Data());
  h2->SetName("Default");
  h2->SetTitle("");
  NormHistBinWidth(h2);  
  
  TFile *f = TFile::Open("./result/JetPtUncer.root", "UPDATE");
  TList *l = new TList();
  for (Int_t i = 0; i< nHist; ++i){
    TString sMyPath = Form("%s/%s", sPath.Data(), sCut[i].Data()); 
    TString sMyFile = sFile; 
    TString sMyList = List; 
    //TString sMyUEList = UEList; 
    TString sMyHist = sHist; 
    h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    NormHistBinWidth(h1);
    h1->SetName(Form("hist_%d", i));
    l->Add(h1);
    hRatio = (TH1D*) h2->Clone(Form("hRatio_%d", i)); hRatio->Reset();
    for(Int_t j = 1; j <= h2->GetNbinsX(); j++){
      Double_t dVar1 = h1->GetBinContent(j); 
      Double_t dErr1 = h1->GetBinError(j); 
      hRatio->SetBinContent(j, dVar1);
      hRatio->SetBinError(j, dErr1);
      hRatio->SetBinError(j, 0);
    } 
    hRatio->SetName(sCut[i]);
    //hRatio->GetYaxis()->SetRangeUser(0., 0.5);
    //DrawHisto(hRatio, cLine[i], sMark[i], "same");
    SetFrame(hRatio, "#it{p}_{T}(GeV/#it{c})", "Relative syst. on JetPt");
    leg->AddEntry(hRatio, sCut[i],"l");
    l->Add(hRatio);
    hU[i] = hRatio;
  }
  hU[nhist] = (TH1D*)h2->Clone("hRatio");
  auto hUMax = (TH1D*)MaxHistograms(nhist+1, hU);
  auto hUMin = (TH1D*)MinHistograms(nhist+1, hU);
  hUMax->Add(hUMin, -1.);
  hUMax->Divide(h2);
  hUMax->Scale(1./TMath::Sqrt(12.));
  DrawHisto(hUMax, cLine[nhist], sMark[nhist], "same");
  SetFrame(hUMax, "#it{p}_{T}(GeV/#it{c})", "Relative syst. on JetPt");
  leg->AddEntry(hUMax, "Max","l");
  l->Add(hUMax);

  TF1 *f0 = new TF1("fFit", "[0]", XMin, XMax); 
  f0->SetParameter(0, 0.1);
  hUMax->Fit(f0, "L0+");
  TH1D* hFit = (TH1D*)hUMax->Clone("hFit");hFit->Reset();
  for(Int_t n =1; n<= hFit->GetNbinsX(); n++){ hFit->SetBinContent(n, f0->GetParameter(0)); hFit->SetBinError(n, 0);}
  DrawHisto(hFit, cLine[nhist+1], sMark[nhist+1], "same");
  SetFrame(hFit, "#it{p}_{T}(GeV/#it{c})", "Relative syst. on JetPt");
  hFit->SetLineStyle(2);
  l->Add(hFit);
  
  f->cd(); 
  l->Write(Form("%s_JetPt",sType.Data()), TObject::kSingleKey);
  f->Close();

  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/Uncert/%s_JetPt.pdf", sType.Data()));
  CanvasEnd(can);
  return;
}
