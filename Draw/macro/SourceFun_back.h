//
//TH1*  GetTH1FromFile(const TString sPath, const TString sFile, const TString sList,const TString sObject)
//TH2*  GetTH2FromList(const TString sPath, const TString sFile, const TString sList,const TString sObject)
//TF1*  GetTF1FromList(const TString sPath, const TString sFile, const TString sList,const TString sObject)
//TH1*  GetTH1FromFile(const TString sPath, const TString sFile, const TString sObject)
//TGraphErrors* GetTGraphFromFile(const TString sPath, const TString sFile, const TString sObject)
//********************************************************************
//Int_t GetEventNum(TH1D* hEvent)//Sum of hEvent every bin contant
//********************************************************************
//void NormBinSize(TH1D* hNormBinSize)
//TH1D* NormIncl(TH1D* hIncl, TH1D* hEvent)//Used to normalise Inclusive V0s and NJ V0s
//TH1D* NormJC(TH1D* hJC, TH1D* hEvent, Double_t R = 0.4)
//TH1D* NormPC(TH1D* hPCL, TH1D* hPCU,  TH1D* hEvent, Double_t R = 0.4)
//TH1D* NormOC(TH1D* hOC, TH1D* hEvent, Double_t R = 0.4)
//TH1D* NormNJ(TH1D* hNJ, TH1D* hEvent)
//TH1D* RatioTH1D(TH1D* hSpect, TH1D* hEff) //hSpect/hEff
//TH1D* TimesTH1D(TH1D* hSpect, TH1D* hEff) //hSpect*hEff
//TH1D *CalcRatioVarV0(TH1D *hKshort, TH1D *hLambda, TH1D *hAntiLa)(Lambda+AntiLa/2K)
//TH1D* Subtract(TH1D* h1, TH1D* h2)//return h1-h2
//
//********************************************************************
//void SetStyle()
//void SetCanv(TCanvas* c)
//void SetLine(TH1D* hObject,Color_t Color = kBlack,Int_t MakerStyle = 20)//21,22
//void SetLegend(TLegend *l)
//void SetAxis(TH1D* hObject, Double_t YMin=1, Double_t YMax=1e8, Double_t XMin=0.6, Double_t XMax=12,  String sYTitle = "dN/d#it{p}_{T}(c/GeV)", TString sXTitle = "#it{p}_{T}(GeV/c)")
//void SetAxis(TH2D* hObject, Double_t YMin=1, Double_t YMax=1e8, Double_t XMin=0.6, Double_t XMax=12,  String sYTitle = "dN/d#it{p}_{T}(c/GeV)", TString sXTitle = "#it{p}_{T}(GeV/c)")
//TH1D * RebinTH1D(TH1D const *hF, TH1D const *hR)//Rebin TH1D*hF to TH1D*hR 
//TH2D * RebinTH2D(TH2D const *hF, TH2D const *hR)//Rebin TH2D*hF to TH2D*hR

const Color_t cLine[] = { kBlack,  kRed+1,  kBlue+1, kGreen+3, kMagenta+1, kOrange-1, kCyan+2, kYellow+2,  kGray+1, kRed-10, kBlue-9, kGreen-8, kMagenta-9, kOrange-9, kCyan-8, kYellow-7};
//const Color_t wcf[] = { kGray+1, kRed-10, kBlue-9, kGreen-8, kMagenta-9, kOrange-9, kCyan-8, kYellow-7 };
const Style_t sMark[] = { kFullCircle, kOpenSquare, kFullSquare,  kOpenCircle, kFullCross, kOpenDiamond, kFullDiamond, kOpenCross, kFullStar, kOpenStar};

//____________________________________________________________________
//TH1* GetTH1FromList(const TString sPath,
TH1* GetTH1FromFile(const TString sPath,
		      const TString sFile,
		      const TString sList,
		      const TString sObject){
  if (!(sPath && sFile && sList && sObject)) return 0x0;
  TString File = Form("%s/%s",sPath.Data(),sFile.Data());
  TFile*   file = TFile::Open(File.Data(),"read"); if (!file->IsOpen()) return 0x0;
  TList*   list = (TList*)file->Get(sList.Data());  if (!list) return 0x0;
  file->Close();
  TH1* hObject = (TH1*)list->FindObject(sObject);
 // hObject->Draw();
  return hObject;
}

//_____________________________________________________________________
TH2* GetTH2FromList(const TString sPath,
                      const TString sFile,
                      const TString sList,
                      const TString sObject){
  if (!(sPath && sFile && sList && sObject)) return 0x0;
  TString File = Form("%s/%s",sPath.Data(),sFile.Data());
  TFile*   file = TFile::Open(File.Data(),"read"); if (!file->IsOpen()) return 0x0;
  TList*   list = (TList*)file->Get(sList.Data());  if (!list) return 0x0;
  file->Close();
  TH2* hObject = (TH2*)list->FindObject(sObject.Data());

  return hObject;
}

//____________________________________________________________________
TF1* GetTF1FromList(const TString sPath,
                      const TString sFile,
                      const TString sList,
                      const TString sObject){
  if (!(sPath && sFile && sList && sObject)) return 0x0;
  TString File = Form("%s/%s",sPath.Data(),sFile.Data());
  TFile*   file = TFile::Open(File.Data(),"read"); if (!file->IsOpen()) return 0x0;
  TList*   list = (TList*)file->Get(sList.Data());  if (!list) return 0x0;
  file->Close();
  TF1* fObject = (TF1*)list->FindObject(sObject.Data());

  return fObject;
}

//____________________________________________________________________
TH1* GetTH1FromFile(const TString sPath,
		    const TString sFile,
		    const TString sObject){
  if (!(sPath && sFile && sObject)) return 0x0;
  TString File = Form("%s/%s",sPath.Data(),sFile.Data());
  TFile*   file = TFile::Open(File,"read"); if (!file->IsOpen()) return 0x0;
  TH1*  hObject = (TH1*)file->Get(sObject);
  hObject->SetDirectory(0);
  file->Close();
  return hObject;
}

//____________________________________________________________________
TGraphErrors* GetTGraphFromFile(const TString sPath,
		                const TString sFile,
		                const TString sObject){
  if (!(sPath && sFile && sObject)) return 0x0;
  TString File = Form("%s/%s",sPath.Data(),sFile.Data());
  TFile*   file = TFile::Open(File,"read"); if (!file->IsOpen()) return 0x0;
  TGraphErrors*  hObject = (TGraphErrors*)file->Get(sObject);
  //hObject->SetDirectory(0);
  file->Close();
  return hObject;
}

//____________________________________________________________________
TF1* GetTF1FromList(const TString sPath,
		      const TString sFile,
		      const TString sList,
		      const TString sObject){
  if (!(sPath && sFile && sList && sObject)) return 0x0;
  TString File = Form("%s/%s",sPath.Data(),sFile.Data());
  TString sList = Form(sList.Data());
  TFile*   file = TFile::Open(File.Data(),"read"); if (!file->IsOpen()) return 0x0;
  TList*   list = (TList*)file->Get(sList.Data());  if (!list) return 0x0;
  file->Close();
  TF1* fObject = (TF1*)list->FindObject(sObject.Data());
  
  return fObject;
}
  
//____________________________________________________________________
Int_t GetEventNum(TH1D* hEvent){
  if(!(hEvent)) return 0;
  
  Int_t iEvent = 0;
  for (Int_t k=1; k<=hEvent->GetNbinsX(); k++){
     Int_t i = hEvent->GetBinContent(k);
     iEvent += i;
  } 

  return iEvent;
}

//____________________________________________________________________
void NormBinSize(TH1D* hNormBinSize){// Add Error
  if (!hNormBinSize) return;
  for (Int_t k=1; k<= hNormBinSize->GetNbinsX(); k++) {
     Double_t   dBinC = hNormBinSize->GetBinContent(k);
     Double_t dBinErr = hNormBinSize->GetBinError(k);
     Double_t dBinW = hNormBinSize->GetXaxis()->GetBinWidth(k);
     Double_t dNorm = dBinC/dBinW;
     Double_t  dErr = dBinErr/dBinW; 
     hNormBinSize->SetBinContent(k,dNorm);
     hNormBinSize->SetBinError(k,dErr);
  }
}

//____________________________________________________________________
TH1D* NormIncl(TH1D* hIncl, TH1D* hEvent){
  if(!(hIncl && hEvent)) return;
  //Double_t dEvent = hEvent->GetBinContent(11+100);
  //Double_t dEvent = hEvent->GetBinContent(1);
  Double_t dEvent = hEvent->GetEntries();
  cout<<"..............."<<"Incl Events = "<<dEvent<<"................"<<endl;

  //hIncl->Scale(1/(dEvent*2*0.75*TMath::TwoPi()));
  for (Int_t k=1; k<= hIncl->GetNbinsX(); k++){
    Double_t     dIncl = hIncl->GetBinContent(k);
    Double_t  dInclErr = hIncl->GetBinError(k);
    //Double_t dNormIncl = dIncl/(dEvent*2*0.75*TMath::TwoPi());
    //Double_t  dNormErr = dInclErr/(dEvent*2*0.75*TMath::TwoPi());
    Double_t dNormIncl = dIncl/(dEvent*2*0.75*TMath::TwoPi());
    Double_t  dNormErr = dInclErr/(dEvent*2*0.75*TMath::TwoPi());
    hIncl->SetBinContent(k, dNormIncl);
    hIncl->SetBinError(k, dNormErr); 
  }
  return hIncl;
}

//____________________________________________________________________
TH1D* NormJC(TH1D* hJC, TH1D* hEvent, Double_t R = 0.4){
  if(!(hJC && hEvent)) return;
  //Double_t dJetEvent = hEvent->GetBinContent(4);
  Double_t dJetEvent = hEvent->GetEntries();
  cout<<"..............."<<"Jet Events = "<<dJetEvent<<"................"<<endl;

  //hJC->Scale(1/(dJetEvent*TMath::Pi()*R*R));
  for (Int_t k=1; k<= hJC->GetNbinsX(); k++){
    Double_t      dJC = hJC->GetBinContent(k);
    Double_t   dJCErr = hJC->GetBinError(k);
    Double_t  dNormJC = dJC/(dJetEvent*2*0.75*TMath::TwoPi()*0.06);
    Double_t  dNormErr = dJCErr/(dJetEvent*2*0.75*TMath::TwoPi()*0.06);
    hJC->SetBinContent(k, dNormJC);
    hJC->SetBinError(k, dNormErr); 
  }

  return hJC;
}

//____________________________________________________________________
TH1D* NormPC(TH1D* hPCL, TH1D* hPCU, TH1D* hEvent, Double_t R = 0.4){
  if(!(hPCL && hPCU && hEvent)) return;
  //Double_t dJetEvent = hEvent->GetBinContent(1+10);//Xaxis range is -10 to 200
  //Double_t dJetEvent = hEvent->GetBinContent(11+50);//Xaxis range is -10 to 200
  Double_t dJetEvent = hEvent->GetBinContent(4);//Xaxis range is -10 to 200
  cout<<"..............."<<"Jet Events = "<<dJetEvent<<"................"<<endl;
  
  //hPCL->Add(hPCU);
  //hPCL->Scale(1/(dJetEvent*4*TMath::Pi()*R*R));
  for (Int_t k=1; k<= hPCL->GetNbinsX(); k++){
    Double_t     dPCL = hPCL->GetBinContent(k);
    Double_t  dPCLErr = hPCL->GetBinError(k);
    Double_t     dPCU = hPCU->GetBinContent(k);
    Double_t  dPCUErr = hPCU->GetBinError(k);
    Double_t      dPC = dPCL+dPCU;
    Double_t   dPCErr = TMath::Sqrt(dPCLErr*dPCLErr + dPCUErr*dPCUErr);
    Double_t  dNormPC = dPC/(dJetEvent*2*0.75*TMath::TwoPi()*0.24);
    Double_t dNormErr = dPCErr/(dJetEvent*2*0.75*TMath::TwoPi()*0.24);
    hPCL->SetBinContent(k, dNormPC);
    hPCL->SetBinError(k, dNormErr); 
  }

  return hPCL;
}

//____________________________________________________________________
TH1D* NormOC(TH1D* hOC, TH1D* hEvent, Double_t R = 0.4){
  if(!(hOC && hEvent)) return;
  //Double_t dJetEvent = hEvent->GetBinContent(1+10);
  //Double_t dJetEvent = hEvent->GetBinContent(11+50);
  Double_t dJetEvent = hEvent->GetBinContent(4);

  //hOC->Scale(1/(dJetEvent*(2*0.75*TMath::TwoPi()-TMath::Pi()*R*R)));
  for (Int_t k=1; k<= hOC->GetNbinsX(); k++){
    Double_t      dOC = hOC->GetBinContent(k);
    Double_t   dOCErr = hOC->GetBinError(k);
    Double_t  dNormOC = dOC/(dJetEvent*2*0.75*TMath::TwoPi()*0.94);
    Double_t  dNormErr = dOCErr/(dJetEvent*2*0.75*TMath::TwoPi()*0.94);
    hOC->SetBinContent(k, dNormOC);
    hOC->SetBinError(k, dNormErr); 
  }

  return hOC;
}

//____________________________________________________________________
TH1D* NormNJ(TH1D* hNJ, TH1D* hEvent){
  if(!(hNJ && hEvent)) return;
  Double_t dEvent = hEvent->GetBinContent(5);//Xaxis range is -10 to 200
  //Double_t dEvent = hEvent->GetBinContent(11+50);//Xaxis range is -10 to 200
  cout<<"..............."<<"NJ Events = "<<dEvent<<"................"<<endl;

  //hNJ->Scale(1/(dEvent*2*0.75*TMath::TwoPi()));
  for (Int_t k=1; k<= hNJ->GetNbinsX(); k++){
    Double_t      dNJ = hNJ->GetBinContent(k);
    Double_t   dNJErr = hNJ->GetBinError(k);
    Double_t  dNormNJ = dNJ/(dEvent*2*0.75*TMath::TwoPi());
    Double_t  dNormErr = dNJErr/(dEvent*2*0.75*TMath::TwoPi());
    hNJ->SetBinContent(k, dNormNJ);
    hNJ->SetBinError(k, dNormErr); 
  }

  return hNJ;
}

//____________________________________________________________________
TH1D* RatioTH1D(TH1D* hSpect, TH1D* hEff){
  if(!(hSpect && hEff)) return;
  //hSpect->Divide(hEff);
  //RebinTH1D(hSpect,hEff);
  for (Int_t k=1; k<= hEff->GetNbinsX(); k++){
    Double_t     dSpect = hSpect->GetBinContent(k); if (TMath::Abs(dSpect)<1e-12) dSpect = 1e-12;
    Double_t  dSpectErr = hSpect->GetBinError(k);
    Double_t       dEff = hEff->GetBinContent(k); if (TMath::Abs(dEff)<1e-12) dEff = 1e-12;
    Double_t    dEffErr = hEff->GetBinError(k);
    Double_t dSpectCorr = dSpect/dEff;
    Double_t   dCorrErr = dSpectCorr * TMath::Sqrt(dSpectErr*dSpectErr/(dSpect*dSpect) + dEffErr*dEffErr/(dEff*dEff));
    hSpect->SetBinContent(k, dSpectCorr); 
    hSpect->SetBinError(k, dCorrErr);
  }
  return hSpect;
}

//____________________________________________________________________
TH1D* TimesTH1D(TH1D* hSpect, TH1D* hEff){
  if(!(hSpect && hEff)) return;
  //hSpect->Divide(hEff);
  RebinTH1D(hSpect,hEff);
  for (Int_t k=1; k<= hEff->GetNbinsX(); k++){
    Double_t     dSpect = hSpect->GetBinContent(k); if (TMath::Abs(dSpect)<1e-12) dSpect = 1e-12;
    Double_t  dSpectErr = hSpect->GetBinError(k);
    Double_t       dEff = hEff->GetBinContent(k); if (TMath::Abs(dEff)<1e-12) dEff = 1e-12;
    Double_t    dEffErr = hEff->GetBinError(k);
    Double_t dSpectCorr = dSpect*dEff;
    Double_t   dCorrErr = dSpectCorr * TMath::Sqrt(dSpectErr*dSpectErr/(dSpect*dSpect) + dEffErr*dEffErr/(dEff*dEff));
    hSpect->SetBinContent(k, dSpectCorr); 
    hSpect->SetBinError(k, dCorrErr);
  }
  return hSpect;
}

//____________________________________________________________________
TH1D *CalcRatioVarV0(TH1D *hKshort, TH1D *hLambda, TH1D *hAntiLa)
{
  if (!(hKshort || hLambda || hAntiLa)) return 0x0;

  TH1D *hRatioV = (TH1D*)hKshort->Clone("hRatioV"); hRatioV->Reset();

  for (Int_t k=1; k<=hRatioV->GetNbinsX(); k++) {
    Double_t dVarLambda = hLambda->GetBinContent(k);
    Double_t dErrLambda = hLambda->GetBinError(k);

    Double_t dVarAntiLa = hAntiLa->GetBinContent(k);
    Double_t dErrAntiLa = hAntiLa->GetBinError(k);

    Double_t dVarL = dVarLambda + dVarAntiLa; if (TMath::Abs(dVarL)<1e-12) dVarL = 1e-12;
    Double_t dErrL = TMath::Sqrt(dErrLambda*dErrLambda + dErrAntiLa*dErrAntiLa) / dVarL;

    Double_t dVarK = hKshort->GetBinContent(k); if (TMath::Abs(dVarK)<1e-12) dVarK = 1e-12;
    Double_t dErrK = hKshort->GetBinError(k) / dVarK;

    Double_t dVarR = 0.5 * dVarL / dVarK;
    Double_t dErrR = dVarR * TMath::Sqrt(dErrK*dErrK + dErrL*dErrL);
    hRatioV->SetBinContent(k, dVarR); hRatioV->SetBinError(k, dErrR);
  }

  return hRatioV;
}

//____________________________________________________________________
TH1D* Subtract(TH1D* h1, TH1D* h2){
  if (!(h1 || h2)) return 0x0;

  for(Int_t k=1; k<= h1->GetNbinsX(); k++){
    Double_t   dh1 = h1->GetBinContent(k);
    Double_t dErr1 = h1->GetBinError(k);
    Double_t   dh2 = h2->GetBinContent(k);
    Double_t dErr2 = h2->GetBinError(k);

    Double_t    dh = dh1 - dh2;
    Double_t  dErr = dh * TMath::Sqrt(dErr1*dErr1+dErr2*dErr2);
    h1->SetBinContent(k, dh);
    h1->SetBinError(k, dErr);  
  }

  return h1;
}
//____________________________________________________________________
void SetStyle(){
  gStyle->SetOptStat("");
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);
  gStyle->SetLegendFont(42);
  
  return;
}

//____________________________________________________________________
void SetCanv(TCanvas* c){
  c->SetRightMargin(0.03);
  c->SetLeftMargin(0.13);
  c->SetTopMargin(0.02);
  c->SetBottomMargin(0.15);
  c->SetTickx();
  c->SetTicky();
}
//____________________________________________________________________
void SetLine(TH1D* hObject, Color_t Color = kBlack, Int_t MakerStyle = 20){
  hObject->SetLineWidth(4);
  hObject->SetLineColor(Color);
  hObject->SetMarkerColor(Color);
  hObject->SetMarkerStyle(MakerStyle);//21,23,4
  hObject->SetMarkerSize(0.8);
  
  return;
}

//____________________________________________________________________
void SetLegend(TLegend *l)
{
  l->SetFillColor(0);
  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->SetTextSize(0.8*gStyle->GetTextSize());

  return;
}

//____________________________________________________________________
void SetAxis(TH1D* hObject,
             Double_t YMin = 1,
             Double_t YMax = 1e8,
             Double_t XMin = 0.6,
             Double_t XMax = 12,
             TString sYTitle = "d#it{N}/d#it{p}_{T}(GeV/#it{c})^{-1}",
             //TString sYTitle = "1/N_{evt} #times (#Delta#eta#Delta#varphi)^{-1} #times d#it{N}/d#it{p}_{T}(GeV/#it{c})^{-1}",
             TString sXTitle = "#it{p}_{T}(GeV/#it{c})"){
  hObject->GetXaxis()->SetTitle(sXTitle);
  hObject->GetYaxis()->SetTitle(sYTitle);

  hObject->GetXaxis()->SetRangeUser(XMin,XMax);
  hObject->GetYaxis()->SetRangeUser(YMin,YMax);

  hObject->GetXaxis()->SetTitleSize(0.06);
  hObject->GetYaxis()->SetTitleSize(0.06);

  hObject->GetXaxis()->SetTitleOffset(1.);
  hObject->GetYaxis()->SetTitleOffset(1.);

  hObject->GetXaxis()->SetLabelSize(0.05);
  hObject->GetYaxis()->SetLabelSize(0.05);

  return;
}

//____________________________________________________________________
void SetAxis(TH2D* hObject,
             Double_t YMin = 1,
             Double_t YMax = 1e8,
             Double_t XMin = 0.6,
             Double_t XMax = 12,
             //TString sYTitle = "d#it{N}/d#it{p}_{T}(GeV/#it{c})^{-1}",
             TString sYTitle = "1/N_{evt} #times (#Delta#eta#Delta#varphi)^{-1} #times d#it{N}/d#it{p}_{T}(GeV/#it{c})^{-1}",
             TString sXTitle = "#it{p}_{T}(GeV/c)"){
  hObject->GetXaxis()->SetTitle(sXTitle);
  hObject->GetYaxis()->SetTitle(sYTitle);

  hObject->GetXaxis()->SetRangeUser(XMin,XMax);
  hObject->GetYaxis()->SetRangeUser(YMin,YMax);

  hObject->GetXaxis()->SetTitleSize(0.06);
  hObject->GetYaxis()->SetTitleSize(0.06);

  hObject->GetXaxis()->SetTitleOffset(1.);
  hObject->GetYaxis()->SetTitleOffset(1.);

  hObject->GetXaxis()->SetLabelSize(0.05);
  hObject->GetYaxis()->SetLabelSize(0.05);

  return;
}

//____________________________________________________________________
TH1D * RebinTH1D(TH1D const *hF, TH1D const *hR){

  if ((!hF) || (!hR)) return 0x0;
  //const Int_t nt = hR->GetNbinsX();
  //const Int_t n  = nt;
  const Int_t n  = 45;

  Double_t d[n+1];
  d[n] = hR->GetXaxis()->GetBinUpEdge(n);
  for (Int_t i=0, k=1; i<n; i++, k++) d[i] = hR->GetXaxis()->GetBinLowEdge(k);//get 的是bin的upEdge.
  
  TH1D *hN = new TH1D(Form("hN_%s_%s",hF->GetName(),hR->GetName()), "", n, d); hN->Sumw2();

  for (Int_t k=1; k<=hF->GetNbinsX(); k++) {
    Double_t dXvar = hF->GetBinCenter(k);
    if ((dXvar<d[0]) || (dXvar>=d[n])) continue;

    Double_t dYvar = hF->GetBinContent(k);
    Double_t dYerr = hF->GetBinError(k);

    Int_t nb = hN->FindBin(dXvar);
    Double_t dYsw2 = hN->GetBinError(nb);

    hN->SetBinContent(nb, dYvar + hN->GetBinContent(nb));
    hN->SetBinError(nb, TMath::Sqrt(dYerr*dYerr + dYsw2*dYsw2));
  }

  return hN;
}

//____________________________________________________________________
TH2D * RebinTH2D(TH2D const *hF, TH2D const *hR){

  if ((!hF) || (!hR)) return 0x0;
  const Int_t nx1 = hR->GetNbinsX();
  const Int_t ny1 = hR->GetNbinsY();
  const Int_t nx = nx1;
  const Int_t ny = ny1;

  Double_t dx[nx+1];
  Double_t dy[ny+1];

  dx[nx] = hR->GetXaxis()->GetBinUpEdge(nx);
  dy[ny] = hR->GetYaxis()->GetBinUpEdge(ny);
  for (Int_t i=0, k=1; i<nx; i++, k++) dx[i] = hR->GetXaxis()->GetBinLowEdge(k);
  for (Int_t j=0, l=1; j<ny; j++, l++) dy[j] = hR->GetYaxis()->GetBinLowEdge(l);

  TH2D *hN = new TH2D(Form("hN_%s_%s",hF->GetName(),hR->GetName()), "", nx, dx, ny, dy); hN->Sumw2();
  hN->Reset();

  for (Int_t k=1; k<=hF->GetNbinsX(); k++) {
    Double_t dXvar = hF->GetXaxis()->GetBinCenter(k);
    if ((dXvar<dx[0]) || (dXvar>=dx[nx])) continue;

    for (Int_t l=1; l<=hF->GetNbinsY(); l++) {
      Double_t dYvar = hF->GetYaxis()->GetBinCenter(l);
      if ((dYvar<dy[0]) || (dYvar>=dy[ny])) continue;

      Double_t dvar = hF->GetBinContent(k, l);
      Double_t derr = hF->GetBinError(k, l);

      Int_t nbx = hN->GetXaxis()->FindBin(dXvar);
      Int_t nby = hN->GetYaxis()->FindBin(dYvar);
      Double_t dsw2 = hN->GetBinError(nbx, nby);

      hN->SetBinContent(nbx, nby, dvar + hN->GetBinContent(nbx, nby));
      hN->SetBinError(nbx, nby, TMath::Sqrt(derr*derr + dsw2*dsw2));
    }
  }

  return hN;
}


//////////////////////////////////////////////////////////////////////////////////
//Set line style, Maker stytle,  X range, Y range, X Title, Y Title.
//Para: Object, LineColor, MakerColor, MakerColor, MakerStyle, YMin, YMax, XMin, XMax, YTitle, XTitle
//Information!!!: Define Canvas and Set LogY!!!!!!
void SetLineStyle(TH1D* hObject,
              Color_t  LineColor = kBlack,
              Color_t  MakerColor = kBlue,
              Int_t   MakerStyle = 21,
	      Double_t      YMin = 1e2.,
	      Double_t      YMax = 1e8,
	      Double_t      XMin = 0.6,
	      Double_t      XMax = 12.,
	      TString    sYTitle = "dN/d#it{p}_{T}(c/GeV)",
	      TString    sXTitle = "#it{p}_{T}(GeV/c)"){
  //TCanvas *cV0Pt = new TCanvas("cV0Pt","");

  hObject->SetLineColor(LineColor);
  hObject->SetLineWidth(2);
  hObject->SetMarkerColor(MakerColor);
  hObject->SetMarkerStyle(MakerStyle);
  hObject->SetMarkerSize(0.4);
 
  hObject->GetXaxis()->SetTitle(sXTitle.Data());
  //hObject->GetXaxis()->SetTitle(sXTitle);
  hObject->GetYaxis()->SetTitle(sYTitle.Data());
  hObject->GetXaxis()->SetRangeUser(XMin,XMax);
  hObject->GetYaxis()->SetRangeUser(YMin,YMax);
  
  gStyle ->SetOptStat("");  
  hObject->Draw("same");

}
/////////////////////////////////////////////////////////////////////////////////
void SetAxisStyle(TH2D* Object, 
	     const TString sXaxis,
             const TString sYaxis ){
    
  Object->GetXaxis()->SetTitle(sXaxis);
  Object->GetXaxis()->SetTitleSize(0.06);
  Object->GetXaxis()->SetTitleOffset(1.5);
  Object->GetXaxis()->SetRangeUser(0.6,12);
  Object->GetXaxis()->SetLabelSize(0.05);

  Object->GetYaxis()->SetTitle(sYaxis);
  Object->GetYaxis()->SetTitleSize(0.06);
  Object->GetYaxis()->SetTitleOffset(1.5);
  Object->GetYaxis()->SetLabelSize(0.05);
}

/////////////////////////////////////////////////////////////////////////////////
void SetAxisStyle(TH1D* Object,
             const TString sXaxis,
             const TString sYaxis ){

  Object->GetXaxis()->SetTitle(sXaxis);
  Object->GetXaxis()->SetTitleSize(0.05);
  Object->GetXaxis()->SetTitleOffset(0.8);
  Object->GetXaxis()->SetRangeUser(0.6,12);
  Object->GetXaxis()->SetLabelSize(0.05);

  Object->GetYaxis()->SetTitle(sYaxis);
  Object->GetYaxis()->SetTitleSize(0.05);
  Object->GetYaxis()->SetTitleOffset(1);
  Object->GetYaxis()->SetLabelSize(0.05);
}

/////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//_____________________________________________________________________
TH1D* GetHistFromList(const TString sPath,
		      const TString sFile,
		      const TString sList,
		      const TString sObject){
  if (!(sPath && sFile && sList && sObject)) return 0x0;
  TString File = Form("%s/%s",sPath.Data(),sFile.Data());
  TFile*   file = TFile::Open(File.Data(),"read"); if (!file->IsOpen()) return 0x0;
  TList*   list = (TList*)file->Get(sList.Data());  if (!list) return 0x0;
  file->Close();
  TH1D* hObject = (TH1D*)list->FindObject(sObject);
 // hObject->Draw();
  return hObject;
}
  
//____________________________________________________________________
TH2D* GetTH2DFromList(const TString sPath,
		      const TString sFile,
		      const TString sList,
		      const TString sObject){
  if (!(sPath && sFile && sList && sObject)) return 0x0;
  TString File = Form("%s/%s",sPath.Data(),sFile.Data());
  TFile*   file = TFile::Open(File.Data(),"read"); if (!file->IsOpen()) return 0x0;
  TList*   list = (TList*)file->Get(sList.Data());  if (!list) return 0x0;
  file->Close();
  TH2D* hObject = (TH2D*)list->FindObject(sObject.Data());
  
  return hObject;
}
//____________________________________________________________________
Int_t GetEventNum(TString sLoop2FilePath){
  if(!(sLoop2FilePath)) return 0;
  TString  sLoop2FileName = "AnalysisOutputs_Loop2ndRD.root";
  TString  sLoop2ListName = "listLoop2ndRD_Kshort_Default;1";
  TString         sObject = "hEvent";
  
  TH1D* hEvent = (TH1D*)GetHistFromList(sLoop2FilePath, sLoop2FileName, sLoop2ListName, sObject);
  if (!(hEvent)) return 0;

  Int_t iEvent = 0;
  for (Int_t k=1; k<=hEvent->GetNbinsX(); k++){
     Int_t i = hEvent->GetBinContent(k);
     iEvent += i;
  } 
  return iEvent;
}
//______________________________________________________________________________
TH1D* Ratio(TH1D* hNumerator, TH1D* hDenominator, TString sName = ""){
  if (!(hNumerator && hDenominator)) return 0x0;
  Int_t i = hNumerator->GetNbinsX();
  Int_t j = hDenominator->GetNbinsX();
  
  if (!sName){
    TH1D* hRatio = hNumerator->Clone(Form("%s_%s",hNumerator->GetName(),hDenominator->GetName()));
  }else{
    TH1D* hRatio = hNumerator->Clone(Form(sName.Data()));
  }
  hRatio->Reset();

  if (!(i==j)) return 0x0;
  for (Int_t k=1; k<= i; k++) {
     Double_t   dNumerator = hNumerator->GetBinContent(k);
     Double_t dErrLambda = hLambda->GetBinError(k);
     Double_t dDenominator = hDenominator->GetBinContent(k);
     if (dDenominator == 0.) continue;
     Double_t dRatio = dNumerator/dDenominator;
     hRatio ->SetBinContent(k,dRatio);
  }
  return hRatio;
}
//Read The FitInvMrd.root, get the One of V0s object hPt and devide its binsize.
//_________________________________________________________________________
TH1D* DrawV0Pt(const TString sPath, const TString sV0){
  if (!(sPath && sV0)) return 0x0;
  TString sFile = Form("%s/AnalysisOutputs_FitInvMrd.root",sPath.Data());
  TString sList = Form("listFitInvMrd_%s_Default;1",sV0.Data());
  TFile   *file = TFile::Open(sFile.Data(),"read"); if (!file->IsOpen()) return 0x0;
  TList   *list = (TList*)file->Get(sList.Data());  if (!list) return 0x0;
  file->Close();

  TCanvas *cV0Pt = new TCanvas("cV0Pt","");
  TH1D    *hV0Pt = (TH1D*)list->FindObject("hPt");
  NormBinSize(hV0Pt);
  hV0Pt->SetLineColor(kBlue);
  hV0Pt->SetLineWidth(2);
  hV0Pt->SetMarkerColor(kMagenta);
  hV0Pt->SetMarkerStyle(21);
  hV0Pt->SetMarkerSize(0.5);

  hV0Pt->GetXaxis()->SetTitle("#it{p}_{T}(GeV/c)");
  hV0Pt->GetYaxis()->SetTitle("dN/d#it{p}_{T}(c/GeV)");
  hV0Pt->GetXaxis()->SetRangeUser(0.6,12.);
  hV0Pt->GetYaxis()->SetRangeUser(1,1e7);

  //hV0Pt->SetTitle("K_{s}^{0} p_{T} Spectum");

  //cV0Pt ->SetLogy();
  gStyle->SetOptStat("");
  hV0Pt ->Draw();

  TLegend* leg = new TLegend(0.6,0.8,0.9,0.9);
  //leg->SetHeader("K_{s}^{0} #it{p}_{T} spectrum with FitInvM at 7 TeV"); // option "C" allows to center the header
 // leg->SetHeader("abc","c");
  leg->AddEntry(hV0Pt,Form("%s #it{p}_{T} spectrum with FitInvM at 13 TeV ",sV0.Data()),"lp");
  leg->SetFillStyle(0);
  //leg->SetShadowColor(0);
  leg->Draw();
  return hV0Pt;
}

//Read The FitInvMrd.root, get the all of V0s object hPt and devide its binsize.
//_____________________________________________________________________________
TH1D* DrawFitInvMV0Pt(const TString sPath, const TString sKshort, const TString sLambda, const TString sAntiLa){
  if(!(sPath || sKshort || sLambda || sAntiLa)) return 0x0;

  TString  sFile = Form("%s/AnalysisOutputs_FitInvMrd.root",sPath.Data());
  //TString sList[2]; 
  TString sListK = Form("listFitInvMrd_%s_Default;1",sKshort.Data());
  TString sListL = Form("listFitInvMrd_%s_Default;1",sLambda.Data());
  TString sListA = Form("listFitInvMrd_%s_Default;1",sAntiLa.Data());
  TFile*    file = TFile::Open(sFile.Data(),"read"); if (!file->IsOpen()) return 0x0;
  TList*   listK = (TList*)file->Get(sListK.Data());
  TList*   listL = (TList*)file->Get(sListL.Data());
  TList*   listA = (TList*)file->Get(sListA.Data());
  if (!(listK || listL || listA)) return 0x0;
  //cout<<"listK  "<<listK<<"listL  "<<listL<<"listA  "<<listA<<endl;
  file->Close();

  TCanvas *cV0Pt = new TCanvas("cV0Pt","");

  TH1D  *hKshort = (TH1D*)listK->FindObject("hPt");
  NormBinSize(hKshort);
  hKshort->SetLineColor(kBlack);  
  hKshort->SetLineWidth(2);
  hKshort->SetMarkerColor(4);
  hKshort->SetMarkerStyle(21);
  hKshort->SetMarkerSize(0.5);
  
  hKshort->GetXaxis()->SetTitle("#it{p}_{T}(GeV/c)");
  hKshort->GetYaxis()->SetTitle("dN/d#it{p}_{T}(c/GeV)");
  hKshort->GetXaxis()->SetRangeUser(0.6,12.);
  hKshort->GetYaxis()->SetRangeUser(1e2,1e7);
  //hKshort->GetXaxis()->SetLabelSize(0.05);
  
  hKshort->Draw("same");

  TH1D  *hLambda = (TH1D*)listL->FindObject("hPt");
  NormBinSize(hLambda);
  hLambda->SetLineColor(kBlue);
  hLambda->SetLineWidth(2);
  hLambda->SetMarkerColor(kMagenta);
  hLambda->SetMarkerStyle(23);
  hLambda->SetMarkerSize(0.7);
  hLambda->Draw("same");

  TH1D  *hAntiLa = (TH1D*)listA->FindObject("hPt");
  NormBinSize(hAntiLa);
  hAntiLa->SetLineColor(kRed);
  hAntiLa->SetLineWidth(2);
  hAntiLa->SetMarkerColor(kBlack);
  hAntiLa->SetMarkerStyle(4);
  hAntiLa->SetMarkerSize(0.7);
  hAntiLa->Draw("same");

  cV0Pt  ->SetLogy();
  gStyle->SetOptStat("");//delete the statistic box

  //TLegend 右上角的标注
  TLegend* leg = new TLegend(0.6,0.7,0.9,0.9);
  leg->SetHeader("V^{0}s #it{p}_{T} spectrum with FitInvM at 7 TeV"); // option "C" allows to center the header
 // leg->SetHeader("abc","c");
  leg->AddEntry(hKshort,"K_{S}^{0}","lp");
  leg->AddEntry(hLambda,"#Lambda","lp");
  leg->AddEntry(hAntiLa,"#bar{#Lambda}","lp");
  leg->SetFillStyle(0);
  //leg->SetShadowColor(0);
  leg->Draw();

  return hAntiLa;
}
