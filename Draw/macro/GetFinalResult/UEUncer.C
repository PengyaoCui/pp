#include "./inc/SourceFun.h"

void UEUncer(const TString sType = "Xi"){
 
  TFile *file = TFile::Open("./result/CentVal.root", "read");
  TList *listIn = (TList*)file->Get(Form("listIn"));

  //TList *listJC = (TList*)file->Get(Form("listJC"));
  //TList *listJE = (TList*)file->Get(Form("listJE"));
  TList *listPC02 = (TList*)file->Get(Form("listPC02"));
  TList *listPC04 = (TList*)file->Get(Form("listPC04"));
  TList *listPC06 = (TList*)file->Get(Form("listPC06"));
  TH1D* hUE[3];//PC02, PC06, PC04
  hUE[0] = (TH1D*)listPC04->FindObject(Form("h%s", sType.Data()));
  hUE[1] = (TH1D*)listPC02->FindObject(Form("h%s", sType.Data()));
  hUE[2] = (TH1D*)listPC06->FindObject(Form("h%s", sType.Data()));

  auto sLatex(Form("Uncertainty of %s", sType.Data()));
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------

  TH1D* h2 = (TH1D*)hUE[0]->Clone("h2"); h2->Reset();
  TH1D* h3 = (TH1D*)hUE[0]->Clone("h3"); h3->Reset();
   
  for(Int_t i = 1; i<=h2->GetNbinsX(); i++){
    auto V0 = hUE[0]->GetBinContent(i); //PC04
    auto E0 = hUE[0]->GetBinError(i);
    auto V1 = hUE[1]->GetBinContent(i); //PC02
    auto E1 = hUE[1]->GetBinError(i);
    auto V2 = hUE[2]->GetBinContent(i); //PC06
    auto E2 = hUE[2]->GetBinError(i);
    h2->SetBinContent(i, TMath::Abs(V2-V0)/TMath::Sqrt(12.)); 
    h2->SetBinError(i, TMath::Sqrt(E2*E2 + E0*E0)/TMath::Sqrt(12.)); 
    h3->SetBinContent(i, TMath::Abs(V2-V0)/TMath::Sqrt(12.)); 
    h3->SetBinError(i, TMath::Sqrt(E2*E2 + E0*E0)/TMath::Sqrt(12.)); 
  }

  TH1D* hU[] = {h2, h3};
  auto hUMax = (TH1D*)MaxHistograms(2, hU);
  DrawHisto(hUMax, cLine[0], sMark[0], "same");
  SetFrame(hUMax, "#it{p}_{T}(GeV/#it{c})", "Relative syst. on UE");
  hUMax->GetYaxis()->SetRangeUser(0, 1.05);
  leg->AddEntry(hUMax, "Max","l");
   
  TFile *f = TFile::Open("./result/UEUncer.root", "UPDATE");
  TList *l = new TList();
  l->Add(hUMax);
  l->Write(Form("%s_UESub",sType.Data()), TObject::kSingleKey);
  f->Close();

  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/Uncert/%s_UESub_%s%s_OCNJ.pdf", sType.Data(), CentMin.Data(), CentMax.Data()));
  CanvasEnd(can);
  return;
}
