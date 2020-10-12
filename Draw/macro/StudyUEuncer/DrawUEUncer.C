#include "./inc/SourceFun.h"

void DrawUEUncer(const TString sType = "Lambda"){
  
  auto sPath = "./result"; 
  auto sCFile = "CentVal.root";
 
  auto sCJEList = "listJE"; 
  auto sCJetHist = Form("h%s", sType.Data());
  
  auto sEUEFile = "UEUncer.root";
  auto sEUEList0 = Form("%s_UESub_wOCandNJ", sType.Data());
  auto sEUEList1 = Form("%s_UESub_wOC", sType.Data());
  auto sEUEList2 = Form("%s_UESub_NonSub", sType.Data());

  auto sLatex(Form("pp #sqrt{#it{s}} = 13 TeV"));
  
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  
  
  auto hJE1  = (TH1D*)GetTH1D(sPath, sCFile, sCJEList, sCJetHist); hJE1->SetName("JECen");
  auto hUE2 = (TH1D*)GetTH1D(sPath, sEUEFile, sEUEList0, "hMax"); hUE2->SetName("UEErrAbs");
  auto hUE2_OC = (TH1D*)GetTH1D(sPath, sEUEFile, sEUEList1, "hMax"); hUE2_OC->SetName("UEErrAbs_OC");
  auto hUE2_No = (TH1D*)GetTH1D(sPath, sEUEFile, sEUEList2, "hMax"); hUE2_No->SetName("UEErrAbs_NonSub");
  const auto nJ = hJE1->GetNbinsX();
 
  auto hJErrContU = (TH1D*)hJE1->Clone("hJErrContU"); hJErrContU->Reset();
  auto hJErrContUOC = (TH1D*)hJE1->Clone("hJErrContUOC"); hJErrContUOC->Reset();
  auto hJErrContUNo = (TH1D*)hJE1->Clone("hJErrContUNo"); hJErrContUNo->Reset();

  for(Int_t i = 1; i<=nJ; i++){
    auto CJE = hJE1->GetBinContent(i);
    auto EUE = hUE2->GetBinContent(i);
    auto EUEOC = hUE2_OC->GetBinContent(i);
    auto EUENo = hUE2_No->GetBinContent(i);
    hJErrContU->SetBinContent(i, EUE/CJE);//
    hJErrContUOC->SetBinContent(i, EUEOC/CJE);//
    hJErrContUNo->SetBinContent(i, EUENo/CJE);//
    hJErrContU->SetBinError(i, 0); 
    hJErrContUOC->SetBinError(i, 0); 
    hJErrContUNo->SetBinError(i, 0); 
  }
  
  
  can = MakeCanvas("can");
  leg = new TLegend(0.65,0.9,1.0,0.6); SetLegend(leg);
  hJErrContU->GetYaxis()->SetTitle("Relative systematic error");
  hJErrContU->GetXaxis()->SetTitle("#it{p}_{T}");
  hJErrContU->GetYaxis()->SetRangeUser(0, 1.);

  DrawHisto(hJErrContU, cLine[0], sMark[0], "same");leg->AddEntry(hJErrContU, "Old","l");
  DrawHisto(hJErrContUOC, cLine[1], sMark[1], "same");leg->AddEntry(hJErrContUOC, "OC08","l");
  DrawHisto(hJErrContUNo, cLine[2], sMark[2], "same");leg->AddEntry(hJErrContUNo, "Non-sub","l");
 
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  tex->DrawLatex(0.15, 0.8, Form("%s", sType.Data()));
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/%s_JCUncert_UE_3.pdf", sType.Data()));
  can->SaveAs(Form("./figure/%s_JCUncert_UE_3.eps", sType.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
