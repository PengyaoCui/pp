#include "./SourceFun.h"

void EffiRatio(){


  TString path = "/home/cuipengyao/study/pp/Local/ThisAna/JE";
  TString sFileJ = "AnalysisOutputs_EffCorrJE.root";
  TString sFileI = "AnalysisOutputs_EffInclMC.root";
  
  TString Path[] = {path, Form("%s_OmegaBins", path.Data())};
  TString sListJ[] = {"listEffCorrJE_Xi_Default_JC", "listEffCorrJE_Omega_Default_JC"};
  TString sListI[] = {"listEffInclMC_Xi_Default", "listEffInclMC_Omega_Default"};
  TString sHist = "hPtEffi";
  
  TString sLeg[] = {"#Xi", "#Omega"};

  auto sLatex("Efficiency ratio of Cascades in JC to inclusive");
  //-----------------------------------
  TCanvas *can = nullptr;

  can = MakeCanvas("can");
  //can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.7,0.9,1.0,0.6);    
  //-----------------------------------
  auto nHist = sizeof(sListI)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    TString sPath = Path[i]; 
    TString sMyListJ = sListJ[i]; 
    TString sMyListI = sListI[i]; 
  
    TH1D* h1 = (TH1D*)GetTH1D(sPath.Data(), sFileJ.Data(), sMyListJ.Data(), sHist.Data());
    h1->SetName(Form("histJ_%d", i)); 
    TH1D* h2 = (TH1D*)GetTH1D(sPath.Data(), sFileI.Data(), sMyListI.Data(), sHist.Data());
    h2->SetName(Form("histI_%d", i)); 
    for(Int_t j = 1; j<= h1->GetNbinsX(); j++){
      auto dVar1 = h1->GetBinContent(j);
      auto dErr1 = h1->GetBinError(j);
      auto dVar2 = h2->GetBinContent(j);
      auto dErr2 = h2->GetBinError(j);
      h1->SetBinContent(j, dVar1/dVar2); 
      h1->SetBinError(j, TMath::Sqrt(dErr1*dErr1 - dErr2*dErr2)); 
    }
    SetFrame(h1, "#it{p}_{T} (GeV/#it{c})", "Efficiency ratio of JC/Incl");
    h1->GetYaxis()->SetRangeUser(0.8, 1.6);
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  tex->DrawLatex(0.16, 0.91, sLatex);
  //tex->DrawLatex(0.5, 0.91, "V0A multiplicity event classes");
  //tex->DrawLatex(0.16, 0.3, "-0.5 < #it{y}_{CMS} < 0");
  //tex->DrawLatex(0.16, 0.2, "p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs("./figure/JCtoIncl_EffiRatio_Cascade.eps");
  CanvasEnd(can);
  return;
}
