#include "./SourceFun.h"


void FitXi(TString sCone = "Incl");
void FitXiSpect(){
  FitXi("Incl");
  //FitXi("JC");
  FitXi("PCL");
  FitXi("PCU");
  //FitXi("OC");
  //FitXi("NJ");
}
void FitXi(TString sCone = "Incl"){
  //-----------------------------------
  TCanvas *can = nullptr;
  can = MakeCanvas("can");
  can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.8,0.9,1.0,0.65);    
  //-----------------------------------

  TH1D *h0 = new TH1D("h0", "", 120, 0., 14.); 
  h0->GetYaxis()->SetRangeUser(1e-8, 1e0); 
  h0->Draw("same");
  
  TH1D* h1;
  TString sList;
  if(sCone == "Incl") sList = "listResults_Xi_Default";
  if(sCone != "Incl") sList = Form("listResults_Xi_Default_%s", sCone.Data());
  h1 = (TH1D*)GetTH1D("./", "AnalysisOutputs_Results.root", sList, "hNco");
  h1->SetName(Form("h1_%s", sCone.Data()));
  TH1D* hEvent = (TH1D*)GetTH1D("./", "AnalysisOutputs_Results.root", sList, "hEvent");
  hEvent->SetName(Form("hEvent_%s", sCone.Data()));
  auto nEvent = hEvent->GetEntries();
  NormHistBinWidth(h1);
  Double_t dBins[] = {0.6, 1.6, 2.2, 2.8, 3.7, 5, 8., 12.};
  auto nBins = (Int_t)sizeof(dBins)/sizeof(Double_t)-1;
  TH1D* h2 = new TH1D("h2", "", nBins, dBins);
  h2->SetName(Form("h2_%s", sCone.Data()));
  for(Int_t i =1; i<= h1->GetNbinsX(); i++){
    h2->SetBinContent(i, h1->GetBinContent(i));
    h2->SetBinError(i, h1->GetBinError(i));
  }
  h2->Draw("same");

  TF1* fLevyFunc = new TF1("fLevyFunc",  "[0]*(([1]-1)*([1]-2)/([1]*[2]*([1]*[2]+1.32171*([1]-2))))*x*TMath::Power(1+((TMath::Sqrt(1.32171*1.32171+x*x)-1.32171)/([1]*[2])), -[1])", 3., 8.);
  fLevyFunc->SetParameter(0, 3.1e-03);
  fLevyFunc->SetParameter(1, 9.9e+08);
  fLevyFunc->SetParameter(2, 5.7e-01);
  h1->Fit("fLevyFunc","RN");//, "QREM0");
  //h1->Fit("fLevyFunc","QREM0");
  Double_t dChisquare = fLevyFunc->GetChisquare();
  Double_t       dNDF = fLevyFunc->GetNDF();
  Double_t dChisOverNDF = dChisquare/dNDF;

  TF1* fLevyFitFunc = new TF1("fLevyFitFunc",  "[0]*(([1]-1)*([1]-2)/([1]*[2]*([1]*[2]+1.32171*([1]-2))))*x*TMath::Power(1+((TMath::Sqrt(1.32171*1.32171+x*x)-1.32171)/([1]*[2])), -[1])", 0., 40.);
  fLevyFitFunc->FixParameter(0, fLevyFunc->GetParameter(0));
  fLevyFitFunc->FixParameter(1, fLevyFunc->GetParameter(1));
  fLevyFitFunc->FixParameter(2, fLevyFunc->GetParameter(2)); 
  fLevyFitFunc->Draw("same");

  //Extend the bin content(mean value)
  for (Int_t k=h1->GetNbinsX()+1; k<=h2->GetNbinsX(); k++){
    Double_t dVal = (fLevyFunc->Integral(h2->GetBinLowEdge(k), h2->GetBinLowEdge(k+1)))/(h2->GetBinWidth(k));
    Double_t dErr = TMath::Abs(fLevyFunc->Eval(h2->GetBinCenter(k))- fLevyFunc->Eval(h2->GetBinCenter(k)));
    //cout<<dVal<<endl;
    //h2->SetBinContent(k, dVal);
    //h2->SetBinError(k, dErr);
  }

  //Extend the bin error(sigma value)
  TH1D* hRMS1 = new TH1D(Form("hRMS1_%s", sCone.Data()), "", 10000, 0., 10e-3);
  //-----------------------------------
  for (Int_t k = 0; k<1000; k++){
    TH1D* hRandom = new TH1D(Form("hRandom_%d", k), "", nBins, dBins);
    for (Int_t i=1; i<=h1->GetNbinsX(); i++){
      Double_t dVarH1 = h1->GetBinContent(i);
      Double_t dErrH1 = h1->GetBinError(i);
      Double_t dRand  = gRandom->Gaus(dVarH1, dErrH1);
      hRandom->SetBinContent(i, dRand);
    }
    //hRandom->Draw("same");
    hRandom->Fit("fLevyFunc","RN");
    TF1* fLevyFitFunc = new TF1(Form("fLevyFitFunc_%d", k),  "[0]*(([1]-1)*([1]-2)/([1]*[2]*([1]*[2]+1.32171*([1]-2))))*x*TMath::Power(1+((TMath::Sqrt(1.32171*1.32171+x*x)-1.32171)/([1]*[2])), -[1])", 0., 40.);
    fLevyFitFunc->FixParameter(0, fLevyFunc->GetParameter(0));
    fLevyFitFunc->FixParameter(1, fLevyFunc->GetParameter(1));
    fLevyFitFunc->FixParameter(2, fLevyFunc->GetParameter(2));
    //fLevyFitFunc->Draw("same");
    hRMS1->Fill(fLevyFitFunc->Eval(h2->GetBinCenter(h1->GetNbinsX()+1)));
    //hRMS2->Fill(fLevyFitFunc->Eval(h2->GetBinCenter(h1->GetNbinsX()+2)));
    //hRMS3->Fill(fLevyFitFunc->Eval(h2->GetBinCenter(h1->GetNbinsX()+3)));
  }
  Double_t dVal = hRMS1->GetMean();
  Double_t dErr = hRMS1->GetRMS();
  h2->SetBinContent(h1->GetNbinsX()+1, dVal);
  h2->SetBinError(h1->GetNbinsX()+1, dErr);
  DeNormHistBinWidth(h2);
  if(sCone == "Incl" || sCone == "NJ")h2->Scale(nEvent*2.*0.75*TMath::TwoPi());
  if(sCone == "JC")h2->Scale(nEvent*2.*0.75*TMath::TwoPi()*0.06);
  if(sCone == "PCL" || sCone == "PCU")h2->Scale(nEvent*2.*0.75*TMath::TwoPi()*0.27);
  if(sCone == "OC")h2->Scale(nEvent*2.*0.75*TMath::TwoPi()*0.94);
  TFile *file = TFile::Open("XiSpect.root", "UPDATE");
  file->cd();
  fLevyFitFunc->Write(Form("FitFun_%s", sCone.Data()), TObject::kSingleKey);
  h2->Write(Form("%s_Xi", sCone.Data()), TObject::kSingleKey);
  file->Close();


  gStyle->SetOptStat("");

  //can->SaveAs(Form("./figure/Xi_DiffConePt.eps"));
  //can->SaveAs(Form("./figure/Xi_PtSpect_JE.eps"));
  CanvasEnd(can);
  return;
}
