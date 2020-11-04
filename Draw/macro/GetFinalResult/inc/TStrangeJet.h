#include "./SourceFun.h"

//-------------------------------------------------------------
TH1D* GetInclPtSpect(TString sType = "Kshort"){

  TString sPath = Form("/home/cuipengyao/study/pp/Local/ThisAna/Incl/%s", sType.Data());

  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default", sType.Data());
  TString sHist = "hNco";

  if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda" || sType == "AntiLa") sList = Form("listMakeLaFdR_%s_Default", sType.Data());
  if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";

  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());
  
  NormHistBinWidth(h);
  h->SetName(Form("h%s", sType.Data()));

  return h;
}

//-------------------------------------------------------------
TH1D* GetPCPtSpect(TString sType = "Kshort", TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE"){

  TString sPath = Form("%s/%s", Path.Data(), sType.Data());

  TString sFile = "AnalysisOutputs_Results.root";
  TString sListL = Form("listResults_%s_Default_PCL", sType.Data());
  TString sListU = Form("listResults_%s_Default_PCU", sType.Data());
  TString sHist = "hNco";

  if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda" || sType == "AntiLa") sListL = Form("listMakeLaFdR_%s_Default_PCL", sType.Data());
  if(sType == "Lambda" || sType == "AntiLa") sListU = Form("listMakeLaFdR_%s_Default_PCU", sType.Data());
  if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";

  auto hL = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sListL.Data(), sHist.Data());
  auto hU = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sListU.Data(), sHist.Data());

  TH1D* h = (TH1D*)hL->Clone(Form("h%s", sType.Data())); h->Reset();

  h->Add(hL, hU);
  h->Scale(0.5);
  NormHistBinWidth(h);

  return h;
}

//-------------------------------------------------------------
TH1D* GetJCPtSpect(TString sType = "Kshort", TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE"){

  TString sPath = Form("%s/%s", Path.Data(), sType.Data());
  
  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default_JC", sType.Data());
  TString sHist = "hNco";
  
  if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda" || sType == "AntiLa") sList = Form("listMakeLaFdR_%s_Default_JC", sType.Data());
  if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";
  
  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());
  NormHistBinWidth(h);

  if(sType == "Lambda" || sType == "AntiLa"){
    auto hPC = GetPCPtSpect(sType, Path);
    h->Add(hPC);
  }
  h->SetName(Form("h%s", sType.Data()));

  return h;
}

//-------------------------------------------------------------
TH1D* GetJEPtSpect(TString sType = "Kshort", TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE"){

  auto hPC = GetPCPtSpect(sType, Path);
  auto hJC = GetJCPtSpect(sType, Path);
  auto h = (TH1D*)hJC->Clone(Form("h%s", sType.Data())); h->Reset();
  h->Add(hJC, hPC, 1., -1.);

  return h;
}



//-------------------------------------------------------------
TH1D* GetOC04PtSpect(TString sType = "Kshort", TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE"){

  TString sPath = Form("%s/%s", Path.Data(), sType.Data());

  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default_OC", sType.Data());
  TString sHist = "hNco";

  if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda" || sType == "AntiLa") sList = Form("listMakeLaFdR_%s_Default_OC", sType.Data());
  if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";

  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());

  NormHistBinWidth(h);
  h->SetName(Form("h%s", sType.Data()));

  return h;
}

//-------------------------------------------------------------
TH1D* GetNJPtSpect(TString sType = "Kshort", TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE"){

  TString sPath = Form("%s/%s", Path.Data(), sType.Data());

  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default_NJ", sType.Data());
  TString sHist = "hNco";

  if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda" || sType == "AntiLa") sList = Form("listMakeLaFdR_%s_Default_NJ", sType.Data());
  if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";

  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());

  NormHistBinWidth(h);
  h->SetName(Form("h%s", sType.Data()));

  return h;
}

//-------------------------------------------------------------
TH1D *GetInclRatioLK() 
{
  auto hK(GetInclPtSpect("Kshort"));
  auto hL(GetInclPtSpect("Lambda"));
  auto hA(GetInclPtSpect("AntiLa"));
  hL->Add(hA);
//=============================================================================

  const TString sh("hLKRatio");
  auto hR(static_cast<TH1D*>(hL->Clone(sh.Data())));
  
  hR->Reset();
  hR->Divide(hL, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetInclRatioXK()
{
  auto hK(GetInclPtSpect("Kshort"));
  auto hX(GetInclPtSpect("Xi"));
//=============================================================================

  const TString sh("hXKRatio");
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));

  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);
  
  hR->Reset();
  hR->Divide(hX, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetInclRatioOK()
{
  auto hK(GetInclPtSpect("Kshort"));
  auto hO(GetInclPtSpect("Omega"));
//=============================================================================

  const TString sh("hOKRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));

  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hO, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetInclRatioOL()
{
  auto hL(GetInclPtSpect("Lambda"));
  auto hA(GetInclPtSpect("AntiLa"));
  auto hO(GetInclPtSpect("Omega"));
//=============================================================================
  hL->Add(hA);
  const TString sh("hOLRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));

  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hO, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetInclRatioXL()
{
  auto hL(GetInclPtSpect("Lambda"));
  auto hA(GetInclPtSpect("AntiLa"));
  auto hX(GetInclPtSpect("Xi"));
//=============================================================================
  hL->Add(hA);
  const TString sh("hXLRatio");
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));

  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hX, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetInclRatioOX()
{
  auto hO(GetInclPtSpect("Omega"));
  auto hX(GetInclPtSpect("Xi"));
//=============================================================================

  const TString sh("hOXRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));

  DeNormHistBinWidth(hX);
  hX=RebinTH1D(hX, hR);
  NormHistBinWidth(hX);

  hR->Reset();
  hR->Divide(hO, hX, 1., 1.);
//=============================================================================

  return hR;
}


//-------------------------------------------------------------
TH1D *GetJCRatioLK()
{
  auto hK(GetJCPtSpect("Kshort"));
  auto hL(GetJCPtSpect("Lambda"));
  auto hA(GetJCPtSpect("AntiLa"));
//=============================================================================
  hL->Add(hA);
  const TString sh("hLKRatio");
  auto hR(static_cast<TH1D*>(hL->Clone(sh.Data())));

  hR->Reset();
  hR->Divide(hL, hK, 1., 2.);
//=============================================================================

  return hR;
}


//-------------------------------------------------------------
TH1D *GetJCRatioXK()
{
  auto hK(GetJCPtSpect("Kshort"));
  auto hX(GetJCPtSpect("Xi"));
//=============================================================================

  const TString sh("hXKRatio");
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hX, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJCRatioOK(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hK(GetJCPtSpect("Kshort", Path));
  auto hO(GetJCPtSpect("Omega", Path));
//=============================================================================

  const TString sh("hOKRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hO, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJCRatioXL()
{
  auto hL(GetJCPtSpect("Lambda"));
  auto hA(GetJCPtSpect("AntiLa"));
  auto hX(GetJCPtSpect("Xi"));
//=============================================================================
  hL->Add(hA);
  const TString sh("hXLRatio");
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hX, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJCRatioOL(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hL(GetJCPtSpect("Lambda", Path));
  auto hA(GetJCPtSpect("AntiLa", Path));
  auto hO(GetJCPtSpect("Omega",  Path));
//=============================================================================
  hL->Add(hA);
  const TString sh("hOLRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hO, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJCRatioOX(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hX(GetJCPtSpect("Xi", Path));
  auto hO(GetJCPtSpect("Omega", Path));
//=============================================================================

  const TString sh("hOXRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  
  DeNormHistBinWidth(hX);
  hX=RebinTH1D(hX, hR);
  NormHistBinWidth(hX);

  hR->Reset();
  hR->Divide(hO, hX, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetPCRatioLK(TString sPath = "/home/cuipengyao/study/pp/Local/ThisAna/JE")
{
  auto hK(GetPCPtSpect("Kshort", sPath));
  auto hL(GetPCPtSpect("Lambda", sPath));
  auto hA(GetPCPtSpect("AntiLa", sPath));
//=============================================================================
  hL->Add(hA);

  const TString sh("hLKRatio");
  auto hR(static_cast<TH1D*>(hL->Clone(sh.Data())));

  hR->Reset();
  hR->Divide(hL, hK, 1., 2.);
//=============================================================================

  return hR;
}


//-------------------------------------------------------------
TH1D *GetPCRatioXK(TString sPath = "/home/cuipengyao/study/pp/Local/ThisAna/JE")
{
  auto hK(GetPCPtSpect("Kshort", sPath));
  auto hX(GetPCPtSpect("Xi", sPath));
//=============================================================================

  const TString sh("hXKRatio");
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hX, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetPCRatioOK(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hK(GetPCPtSpect("Kshort", Path));
  auto hO(GetPCPtSpect("Omega", Path));
//=============================================================================

  const TString sh("hOKRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hO, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetPCRatioXL(TString sPath = "/home/cuipengyao/study/pp/Local/ThisAna/JE")
{
  auto hL(GetPCPtSpect("Lambda", sPath));
  auto hA(GetPCPtSpect("AntiLa", sPath));
  auto hX(GetPCPtSpect("Xi", sPath));
//=============================================================================
  hL->Add(hA);
  
  const TString sh("hXLRatio");
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hX, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetPCRatioOL(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hL(GetPCPtSpect("Lambda", Path));
  auto hA(GetPCPtSpect("AntiLa", Path));
  auto hO(GetPCPtSpect("Omega", Path));
//=============================================================================
  hL->Add(hA);

  const TString sh("hOLRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hO, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetPCRatioOX(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hX(GetPCPtSpect("Xi", Path));
  auto hO(GetPCPtSpect("Omega", Path));
//=============================================================================

  const TString sh("hOXRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  
  DeNormHistBinWidth(hX);
  hX=RebinTH1D(hX, hR);
  NormHistBinWidth(hX);

  hR->Reset();
  hR->Divide(hO, hX, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJERatioLK()
{
  auto hK(GetJEPtSpect("Kshort"));
  auto hL(GetJEPtSpect("Lambda"));
  auto hA(GetJEPtSpect("AntiLa"));
  hL->Add(hA);
//=============================================================================

  const TString sh("hLKRatio");
  auto hR(static_cast<TH1D*>(hL->Clone(sh.Data())));

  hR->Reset();
  hR->Divide(hL, hK, 1., 2.);
//=============================================================================

  return hR;
}


//-------------------------------------------------------------
TH1D *GetJERatioXK()
{
  auto hK(GetJEPtSpect("Kshort"));
  auto hX(GetJEPtSpect("Xi"));
//=============================================================================

  const TString sh("hXKRatio");
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hX, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJERatioOK(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hK(GetJEPtSpect("Kshort", Path));
  auto hO(GetJEPtSpect("Omega", Path));
//=============================================================================

  const TString sh("hOKRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hO, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJERatioXL()
{
  auto hL(GetJEPtSpect("Lambda"));
  auto hA(GetJEPtSpect("AntiLa"));
  auto hX(GetJEPtSpect("Xi"));
//=============================================================================
  hL->Add(hA);

  const TString sh("hXLRatio");
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hX, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJERatioOL(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hL(GetJEPtSpect("Lambda", Path));
  auto hA(GetJEPtSpect("AntiLa", Path));
  auto hO(GetJEPtSpect("Omega",  Path));
//=============================================================================
  hL->Add(hA);

  const TString sh("hOLRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hO, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJERatioOX(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hX(GetJEPtSpect("Xi", Path));
  auto hO(GetJEPtSpect("Omega", Path));
//=============================================================================

  const TString sh("hOXRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  
  DeNormHistBinWidth(hX);
  hX=RebinTH1D(hX, hR);
  NormHistBinWidth(hX);

  hR->Reset();
  hR->Divide(hO, hX, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetOC04RatioLK()
{
  auto hK(GetOC04PtSpect("Kshort"));
  auto hL(GetOC04PtSpect("Lambda"));
  auto hA(GetOC04PtSpect("AntiLa"));
//=============================================================================
  hL->Add(hA);

  const TString sh("hLKRatio");
  auto hR(static_cast<TH1D*>(hL->Clone(sh.Data())));

  hR->Reset();
  hR->Divide(hL, hK, 1., 2.);
//=============================================================================

  return hR;
}


//-------------------------------------------------------------
TH1D *GetOC04RatioXK()
{
  auto hK(GetOC04PtSpect("Kshort"));
  auto hX(GetOC04PtSpect("Xi"));
//=============================================================================

  const TString sh("hXKRatio");
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hX, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetOC04RatioOK(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hK(GetOC04PtSpect("Kshort", Path));
  auto hO(GetOC04PtSpect("Omega", Path));
//=============================================================================

  const TString sh("hOKRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hO, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetOC04RatioXL()
{
  auto hL(GetOC04PtSpect("Lambda"));
  auto hA(GetOC04PtSpect("AntiLa"));
  auto hX(GetOC04PtSpect("Xi"));
//=============================================================================
  hL->Add(hA);

  const TString sh("hXLRatio");
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hX, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetOC04RatioOL(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hL(GetOC04PtSpect("Lambda", Path));
  auto hA(GetOC04PtSpect("AntiLa", Path));
  auto hO(GetOC04PtSpect("Omega", Path));
//=============================================================================
  hL->Add(hA);

  const TString sh("hOLRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hO, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetOC04RatioOX(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hX(GetOC04PtSpect("Xi", Path));
  auto hO(GetOC04PtSpect("Omega", Path));
//=============================================================================

  const TString sh("hOXRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  
  DeNormHistBinWidth(hX);
  hX=RebinTH1D(hX, hR);
  NormHistBinWidth(hX);

  hR->Reset();
  hR->Divide(hO, hX, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetNJRatioLK()
{
  auto hK(GetNJPtSpect("Kshort"));
  auto hL(GetNJPtSpect("Lambda"));
  auto hA(GetNJPtSpect("AntiLa"));
//=============================================================================
  hL->Add(hA);

  const TString sh("hLKRatio");
  auto hR(static_cast<TH1D*>(hL->Clone(sh.Data())));

  hR->Reset();
  hR->Divide(hL, hK, 1., 2.);
//=============================================================================

  return hR;
}


//-------------------------------------------------------------
TH1D *GetNJRatioXK()
{
  auto hK(GetNJPtSpect("Kshort"));
  auto hX(GetNJPtSpect("Xi"));
//=============================================================================

  const TString sh("hXKRatio");
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hX, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetNJRatioOK(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hK(GetNJPtSpect("Kshort", Path));
  auto hO(GetNJPtSpect("Omega", Path));
//=============================================================================

  const TString sh("hOKRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hO, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetNJRatioXL()
{
  auto hL(GetNJPtSpect("Lambda"));
  auto hA(GetNJPtSpect("AntiLa"));
  auto hX(GetNJPtSpect("Xi"));
//=============================================================================
  hL->Add(hA);

  const TString sh("hXLRatio");
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hX, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetNJRatioOL(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hL(GetNJPtSpect("Lambda", Path));
  auto hA(GetNJPtSpect("AntiLa", Path));
  auto hO(GetNJPtSpect("Omega", Path));
//=============================================================================

  hL->Add(hA);
  const TString sh("hOLRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hO, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetNJRatioOX(TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins")
{
  auto hX(GetNJPtSpect("Xi", Path));
  auto hO(GetNJPtSpect("Omega", Path));
//=============================================================================

  const TString sh("hOXRatio");
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  
  DeNormHistBinWidth(hX);
  hX=RebinTH1D(hX, hR);
  NormHistBinWidth(hX);

  hR->Reset();
  hR->Divide(hO, hX, 1., 1.);
//=============================================================================

  return hR;
}

TH1D* RebinToOmega(TH1D* hPar, TH1D* hOmega){

  Double_t dBin[] = {0.6, 2.2, 2.8, 3.7, 5.};
  TH1D* h0 = new TH1D(Form("%s_%s", hPar->GetName(), hOmega->GetName()), "", sizeof(dBin)/sizeof(Double_t)-1, dBin);
  DeNormHistBinWidth(hPar);
  hPar = RebinTH1D(hPar, h0);
  NormHistBinWidth(hPar);

  TH1D* h = (TH1D*)hOmega->Clone(Form("h_%s_%s", hPar->GetName(), hOmega->GetName())); h->Reset();
  for(Int_t i = 1; i<= h->GetNbinsX(); i++){
    h->SetBinContent(i, hPar->GetBinContent(i)); 
    h->SetBinError(i, hPar->GetBinError(i)); 
  }
  return h;
} 
//_____________________________________________________________________________

