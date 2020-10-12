#include "./SourceFun.h"

void InclUncer(const TString sType = "Kshort"){
               
  TString sCut[] = {"CompetMass", "MLoverP", "SigExtrac", "Topological", "TPCPID", "TrackQuality"}; // 
  if(sType == "Lambda" || sType == "AntiLa"){sCut[0] = "MLoverP"; sCut[1] = "SigExtrac"; sCut[2] = "Topological", sCut[3] = "TPCPID", sCut[4] = "TrackQuality";} 
  if(sType == "Xi" || sType == "Omega"){sCut[0] = "SigExtrac"; sCut[1] = "Topological", sCut[2] = "TPCPID", sCut[3] = "TrackQuality";} 
  
  
  TString sPath = "./result"; 
  TString sFile = "UncertaintySource.root";
  TString sList =""; //Kshort_Topological_0100
  TString sHist = "hMax";
 
  TString sLeg = "Total";

  auto sLatex(Form("Uncertainty of %s", sType.Data()));
  Double_t XMin = 0.6;
  Double_t XMax = 12.;
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
 
  leg = new TLegend(0.65,0.85,1.0,0.5); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(sCut)/sizeof(TString);
  if(sType == "Lambda" || sType == "AntiLa") nHist = 5;
  if(sType == "Xi" || sType == "Omega") nHist = 4;
  const auto nhist = nHist;

  TH1D* h1 = nullptr;
  TH1D* hT[nhist+1];
  TFile *f = TFile::Open("./result/InclUncertainty.root", "UPDATE");

  for (Int_t i = 0; i< nhist; ++i){
    sList = Form("%s_%s", sType.Data(), sCut[i].Data()); 
    TString sMyHist = sHist; 
    h1 = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());
    h1->SetName(Form("hist_%d", i));
    h1->GetYaxis()->SetRangeUser(0., 0.2);
    if(sType == "Omega")h1->GetYaxis()->SetRangeUser(0., 0.3);
    for(Int_t j = 1; j<=h1->GetNbinsX(); j++){h1->SetBinError(j, 0.);}
    DrawHisto(h1, cLine[i], sMark[i], "same");
    SetFrame(h1, "#it{p}_{T}(GeV/#it{c})", "Relative syst.");
    leg->AddEntry(h1, sCut[i],"l");
    hT[i] = h1;
  }
  TH1D* hMaterial = (TH1D*)h1->Clone("hMaterial"); hMaterial->Reset();
  for(Int_t j = 1; j<= h1->GetNbinsX(); j++){hMaterial->SetBinContent(j, 0.04); hMaterial->SetBinError(j, 0);}
  DrawHisto(hMaterial, cLine[nhist+1], sMark[nhist+1], "same");
  hMaterial->SetLineStyle(2);
  leg->AddEntry(hMaterial, "Material Budget", "l");
 
  hT[nhist]=hMaterial; 
  auto hTotal = (TH1D*)QuadraticSum(nhist+1, hT);
  DrawHisto(hTotal, cLine[nhist], sMark[nhist], "same");
  SetFrame(hTotal, "#it{p}_{T}(GeV/#it{c})", "Relative syst.");
  leg->AddEntry(hTotal, "Total","l");
  
  f->cd(); 
  hTotal->Write(Form("%s_InclUncer",sType.Data()), TObject::kSingleKey);
  f->Close();

 
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/Uncert/%s_InclUncer.eps", sType.Data()));
  CanvasEnd(can);
  return;
}
