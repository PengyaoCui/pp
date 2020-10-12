#include "./SourceFun.h"

void Ratio(){

  const TString sRatio = "ThisAna/ALICE";
  TString sPathNu[] = {"./result"};
  TString sFileNu[] = {"PtSpect_Compare2LF.root"};
  TString sListNu[] = {""};
  TString sHistNu[] = {"hPtIncl_OmegaNeg"};

  //TString sPathDe = "./result/D_Colella";
  //TString sFileDe = "systcorrectedspectrumfittedgfcorrphyseff.root";
  //TString sListDe = "";
  //TString sHistDe = "hptcorr_norm_2";
  TString sPathDe = "./result";
  TString sFileDe = "HIST_pp.13TeV.mb.INEL.PREL_12062017.root";
  TString sListDe = "";
  TString sHistDe = "hstat_omega_pp13_sum";
  
  //TString sPathDe = "./result_pp";
  //TString sFileDe = "PtSpect_Xi.root";
  //TString sListDe = "";
  //TString sHistDe = "hPtPC_Xi";

  TString sLeg[] = {"New", "ALICE"};

  auto sLatex(Form("Lambda in underlying events"));
  Double_t XMin = 0.;
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
  auto nHist = sizeof(sHistNu)/sizeof(TString);
  const auto nhist = nHist;

  TH1D* h2 = nullptr;
  TH1D* h1 = nullptr;
  TH1D* h11 = nullptr;
  TH1D* hRatio = nullptr;

  padB = MakePadB("padB");
  can->cd();
  padT = MakePadT("padT");
  padT->SetLogy(); 

  h2 = (TH1D*)GetTH1D(sPathDe.Data(), sFileDe.Data(), sListDe.Data(), sHistDe.Data());
  h2->SetName("h2_De");
  h2->SetTitle("");
  //cout<<h2->GetXaxis()->GetBinLowEdge(1)<<endl;
  for(Int_t i = 1; i<=h2->GetNbinsX(); i++){
    h2->SetBinContent(i, h2->GetXaxis()->GetBinCenter(i)*h2->GetBinContent(i)); 
    h2->SetBinError(i, h2->GetXaxis()->GetBinCenter(i)*h2->GetBinError(i)); 
    //cout<<h2->GetXaxis()->GetBinUpEdge(i)<<endl;
  }
  //h2->Scale(1./TMath::TwoPi());
  //h2->Scale(1.1/0.7448);
  h2->Scale(1./0.7);
  ////h2->Scale(0.5);
  padT->cd();
  h2->GetXaxis()->SetRangeUser(XMin, XMax);
  h2->GetYaxis()->SetRangeUser(1e-6, 1.);
  h2->SetMarkerSize(1);
  DrawHisto(h2, cLine[nHist], sMark[nHist], "same");
  SetFrame(h2, "#it{p}_{T}", "d#rho/d#it{p}_{T}");
  leg->AddEntry(h2, sLeg[nHist],"lp");


  for (Int_t i = 0; i< nHist; ++i){
    TString sMyPath = sPathNu[i]; 
    TString sMyFile = sFileNu[i]; 
    TString sMyList = sListNu[i]; 
    TString sMyHist = sHistNu[i]; 
    h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i)); 
    h11 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), "hPtIncl_OmegaPos");
    h11->SetName(Form("hist11_%d", i));
    h1->Add(h11); 
    //DeNormHistBinWidth(h1); 
    //h1=RebinTH1D(h1, h2);
    //NormHistBinWidth(h1); 
    hRatio = (TH1D*) h2->Clone(Form("hRatio_%d", i)); hRatio->Reset();
    hRatio->Divide(h1, h2);
    hRatio->SetName(Form("hratio_%d", i));
    hRatio->GetYaxis()->SetRangeUser(0.8, 1.2);
    padT->cd();
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1, sLeg[i], "lp");
    padB->cd();
    padB->SetGridy();
    DrawHisto(hRatio, cLine[i], sMark[i], "same");
    SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", sRatio, 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
  }


  padB->cd();
  //TLine* l = new TLine(XMin, 1., XMax, 1.);
  //l->SetLineColor(kRed);
  //l->SetLineWidth(2);
  //l->Draw("same");

  padT->cd();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/Xi_wNewPileup_18g4.eps"));
  CanvasEnd(can);
  return;
}
