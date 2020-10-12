#include "./SourceFun.h"

void UncerJet(const TString sType = "Kshort"){
               
  TString sCut[] = {"Tight", "Loose"}; 
  
  TString sPath = "/home/cuipengyao/study/pp/Local/ThisAna/Uncertainty/JE/JetPt"; 
  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = "listResults";
  TString sHist = "hNco";
  //if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  //if(sType == "Lambda" || sType == "AntiLa") sList = "listMakeLaFdR";
  //if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";
  TString List = Form("%s_%s_Default_JC", sList.Data(), sType.Data());
  //TString UEList = Form("%s_%s_Default_PCL", sList.Data(), sType.Data());

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
  TH1D* hU[nhist];
  h2 = (TH1D*)GetTH1D(Form("/home/cuipengyao/study/pp/Local/ThisAna/JE"), sFile.Data(), List.Data(), sHist.Data());
  h2->SetName("Default");
  h2->SetTitle("");
  NormHistBinWidth(h2);  
  //if(sType != "Lambda" && sType != "AntiLa"){
  //  hUE2 = (TH1D*)GetTH1D(Form("/home/cuipengyao/study/pp/Local/ThisAna/JE"), sFile.Data(), UEList.Data(), sHist.Data());
  //  hUE2->SetName("DefaultUE");
  //  hUE2->SetTitle("");
  //  NormHistBinWidth(hUE2);
  //  h2->Add(hUE2, -1.);
  //}
  TFile *f = TFile::Open("./result/JetPtUncertainty.root", "UPDATE");
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
    //if(sType != "Lambda" && sType != "AntiLa"){
    //  hUE1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyUEList.Data(), sMyHist.Data());
    //  hUE1->SetName(Form("UEhist_%d", i));
    //  NormHistBinWidth(hUE1);
    //  h1->Add(hUE1, -1.); 
    //}
    l->Add(h1);
    hRatio = (TH1D*) h2->Clone(Form("hRatio_%d", i)); hRatio->Reset();
    for(Int_t j = 1; j <= h2->GetNbinsX(); j++){
      Double_t dVar1 = h1->GetBinContent(j); 
      Double_t dErr1 = h1->GetBinError(j); 
      Double_t dVar2 = h2->GetBinContent(j);
      Double_t dErr2 = h2->GetBinError(j);
      Double_t dVar = TMath::Abs((dVar1 - dVar2)/(TMath::Sqrt(12.)*dVar2)); 
      //Double_t dErr = TMath::Sqrt((dVar1*dVar1)*(dErr2*dErr2) + (dVar2*dVar2)*(dErr1*dErr1)); 
      Double_t dErr = TMath::Sqrt(TMath::Abs((dErr2*dErr2) - (dErr1*dErr1))/12.); 
      if (TMath::Abs(dVar1 - dVar2)/(TMath::Sqrt(TMath::Abs(dErr1*dErr1 - dErr2*dErr2))+1e-12) > 1 ){
        hRatio->SetBinContent(j, dVar);
        hRatio->SetBinError(j, dErr);
        hRatio->SetBinError(j, 0);
      }else{
        hRatio->SetBinContent(j, 0.);
        hRatio->  SetBinError(j, 0.);
      }
      hRatio->SetBinContent(j, dVar);
      hRatio->SetBinError(j, dErr);
    } 
    hRatio->SetName(sCut[i]);
    hRatio->GetYaxis()->SetRangeUser(0., 0.5);
    DrawHisto(hRatio, cLine[i], sMark[i], "same");
    SetFrame(hRatio, "#it{p}_{T}(GeV/#it{c})", "Relative syst. on JetPt");
    leg->AddEntry(hRatio, sCut[i],"l");
    l->Add(hRatio);
    hU[i] = hRatio;
  }
  auto hUMax = (TH1D*)MaxHistograms(nhist, hU);
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
  can->SaveAs(Form("./figure/Uncert/%s_JetPt.eps", sType.Data()));
  CanvasEnd(can);
  return;
}
