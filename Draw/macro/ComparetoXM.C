#include "./SourceFun.h"

void ComparetoXM(){

  const TString sRatio = "ThisAna/ALICE";
  TString sPathNu[] = {"/home/cuipengyao/study/pPb/Draw/macro/result"};
  TString sFileNu[] = {"KLRatio_MiddleStep.root"};
  TString sListNu[] = {""};
  TString sHistNu[] = {Form("LKRatio_JE_MY_0100")};

  TString sPathDe = "~/study/pPb/Draw/macro/published/LK0jet-master_From_XiaomingZhang/pp_pPb/prep/data/pPb";
  TString sFileDe = "AnalysisResults_Abs.root";
  //TString sListDe = "pplistUE_JC04_JR04_PtJ10";//HD
  TString sListDe = "listHD_JC04_JR04_PtJ10";
  TString sHistDe = "hRatioV_Stat";

  TString sLeg[] = {"This Ana.", "ALICE"};

  auto sLatex(Form("#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}"));
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
  auto nHist = sizeof(sHistNu)/sizeof(TString);
  const auto nhist = nHist;

  TH1D* h2 = nullptr;
  TH1D* h1 = nullptr;
  TH1D* hRatio = nullptr;

  padB = MakePadB("padB");
  can->cd();
  padT = MakePadT("padT");
  //padT->SetLogy();

  
  h2 = (TH1D*)GetTH1D(sPathDe.Data(), sFileDe.Data(), sListDe.Data(), sHistDe.Data());
  
  //h2->Scale(0.5);
  DrawHisto(h2, cLine[nHist], sMark[nHist], "same");
  leg->AddEntry(h2, sLeg[nHist],"lp");
  padT->cd();
  h2->GetXaxis()->SetRangeUser(XMin, XMax);
  h2->GetYaxis()->SetRangeUser(1e-4, 1.);
  SetFrame(h2, "#it{p}_{T}", "#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}");


  for (Int_t i = 0; i< nHist; ++i){
    TString sMyPath = sPathNu[i]; 
    TString sMyFile = sFileNu[i]; 
    TString sMyList = sListNu[i]; 
    TString sMyHist = sHistNu[i]; 
    h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i));
 
    //h1->Scale(5978867./1873118.); 
    //DeNormHistBinWidth(h1); 
    h1=RebinTH1D(h1, h2);
    //NormHistBinWidth(h1); 
    
    hRatio = (TH1D*) h2->Clone(Form("hRatio_%d", i)); hRatio->Reset();
    hRatio->Divide(h1, h2);
    hRatio->SetName(Form("hratio_%d", i));
    hRatio->GetYaxis()->SetRangeUser(0.8, 1.4);
    padT->cd();
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1, sLeg[i], "lp");
    padB->cd();
    padB->SetGridy();
    DrawHisto(hRatio, cLine[i], sMark[i], "same");
    SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", sRatio, 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
  }
  padT->cd(); 


  padB->cd();
  //TLine* l = new TLine(XMin, 1.2, XMax, 1.2);
  //l->SetLineColor(kRed);
  //l->SetLineWidth(2);
  //l->Draw("same");

  padT->cd();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, sLatex);
  tex->DrawLatex(0.2, 0.75, "p-Pb at 5.02 TeV");
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/LKRatio_ComparetToXM_pPb.eps"));
  CanvasEnd(can);
  return;
}
