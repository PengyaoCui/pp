#include "./SourceFun.h"

void MergeCent(){

  const TString sRatio = "Merged/Paper";
  const TString CentMin = "0";
  const TString CentMax = "100";
  TString sPathNu = "./result";
  TString sFileNu = "PtSpect_Eta_Test.root";
  TString sListNu = "";
  TString sHistNu1 = "hPtJE_Kshort_010"; 
  TString sHistNu2 = "hPtJE_Kshort_1040"; 
  TString sHistNu3 = "hPtJE_Kshort_4090"; 

  TString sPathDe = "./published";
  TString sFileDe = "AnalysisResults_XM.root";
  TString sListDe = "listHD_JC04_JR04_PtJ10";
  //TString sListDe = "listIn";
  TString sHistDe = "hKshort_Stat";
  TString sHistSyst = "hKshort_Syst";

  TString sLeg[] = {"Merged", "Paper"};

  auto sLatex(Form("Inclsive Lambda %s-%s%%", CentMin.Data(), CentMax.Data()));
  Double_t XMin = 0.6;
  Double_t XMax = 12.;
  //-----------------------------------
  TCanvas *can = nullptr;
  TPad *padT = nullptr;
  TPad *padB = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;

  can = MakeCanvas("can");
 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(sHistNu1)/sizeof(TString);
  const auto nhist = nHist;

  TH1D* h2 = nullptr;
  TH1D* h1 = nullptr;
  TH1D* hRatio = nullptr;

  padB = MakePadB("padB");
  can->cd();
  padT = MakePadT("padT");
  padT->SetLogy();

  h2 = (TH1D*)GetTH1D(sPathDe.Data(), sFileDe.Data(), sListDe.Data(), sHistDe.Data());
  h2->SetName("h2_De");
  h2->SetTitle("");

  auto h3 = (TH1D*)GetTH1D(sPathDe.Data(), sFileDe.Data(), sListDe.Data(), sHistSyst.Data());
  h3->SetName("h3_De");
  h3->SetTitle("");
  for(Int_t j = 1; j<=h3->GetNbinsX(); ++j){

    auto StatErr = (Double_t) h2->GetBinError(j);
    auto SystErr = (Double_t) h3->GetBinContent(j);
    auto Content = (Double_t) h2->GetBinContent(j);
    auto TotErr = TMath::Sqrt(StatErr*StatErr + (SystErr*SystErr*Content*Content));
    h2->SetBinError(j, TotErr);
  }
  NormHistBinWidth(h2);

  leg->AddEntry(h2, sLeg[1],"lp");
  padT->cd();
  h2->GetXaxis()->SetRangeUser(XMin, XMax);
  h2->GetYaxis()->SetRangeUser(1e-5, 1.);
  SetFrame(h2, "#it{p}_{T}", "d#rho/d#it{p}_{T}(#it{c}/GeV)");
  DrawHisto(h2, cLine[1], sMark[1], "same");


  auto h11 = (TH1D*)GetTH1D(sPathNu.Data(), sFileNu.Data(), sListNu.Data(), sHistNu1.Data());
  h11->SetName(Form("hist_11"));                                                    
  auto h12 = (TH1D*)GetTH1D(sPathNu.Data(), sFileNu.Data(), sListNu.Data(), sHistNu2.Data());
  h12->SetName(Form("hist_12"));                                                    
  auto h13 = (TH1D*)GetTH1D(sPathNu.Data(), sFileNu.Data(), sListNu.Data(), sHistNu3.Data());
  h13->SetName(Form("hist_13"));
  h1 = (TH1D*) h11->Clone("hist_1"); h1->Reset();
  
  h1->Add(h11, h12, 272797./(272797. + 635673. + 431924.), 635673./(272797. + 635673. + 431924.));
  h1->Add(h13, 431924./(272797. + 635673. + 431924.)); 
  
  h1 = RebinTH1D(h1, h2);
  //h1->Scale(2.);
  hRatio = (TH1D*) h2->Clone(Form("hRatio_0")); hRatio->Reset();
  hRatio->Divide(h1, h2);
  hRatio->SetName(Form("hratio_0"));
  hRatio->GetYaxis()->SetRangeUser(0.5, 1.2);
  padT->cd();
  DrawHisto(h1, cLine[0], sMark[0], "same");
  leg->AddEntry(h1, sLeg[0], "lp");
  padB->cd();
  padB->SetGridy();
  DrawHisto(hRatio, cLine[0], sMark[0], "same");
  SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", sRatio, 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
  padB->cd();

  padT->cd();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs("./figure/Lambda_MB_MergedtoPaper_XM.eps");
  CanvasEnd(can);
  return;
}
