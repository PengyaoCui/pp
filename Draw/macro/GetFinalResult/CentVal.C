#include "./inc/TStrangeJet.h"

//-------------------------------------------------------------
void CentVal(){

  TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins";
  TString sPC2 = "/home/cuipengyao/study/pp/Local/ThisAna/Uncertainty/JE/UE/PC02";
  TString sPC6 = "/home/cuipengyao/study/pp/Local/ThisAna/Uncertainty/JE/UE/PC06";
  TString OPC2 = "/home/cuipengyao/study/pp/Local/ThisAna/Uncertainty/JE_Omega/UE/PC02";
  TString OPC6 = "/home/cuipengyao/study/pp/Local/ThisAna/Uncertainty/JE_Omega/UE/PC06";

  TFile *file = TFile::Open("./result/CentVal.root", "UPDATE");
  TList *listIn = (TList*)file->Get(Form("listIn"));             if (!listIn){listIn = new TList();}

  TList *listJC = (TList*)file->Get(Form("listJC"));     if (!listJC){listJC = new TList();}
  TList *listJE = (TList*)file->Get(Form("listJE"));     if (!listJE){listJE = new TList();}
  TList *listPC02 = (TList*)file->Get(Form("listPC02")); if (!listPC02){listPC02 = new TList();}
  TList *listPC04 = (TList*)file->Get(Form("listPC04")); if (!listPC04){listPC04 = new TList();}
  TList *listPC06 = (TList*)file->Get(Form("listPC06")); if (!listPC06){listPC06 = new TList();}
  
  TH1D* h = nullptr;
  TString sType[] = {"Kshort", "Lambda", "AntiLa", "Xi", "Omega"};
  for(Int_t i = 0; i< sizeof(sType)/sizeof(TString); i++){
    h = GetInclPtSpect(sType[i]); listIn->Add(h); 
  
  }
  for(Int_t i = 0; i< sizeof(sType)/sizeof(TString)-1; i++){
    h = GetJCPtSpect(sType[i]); listJC->Add(h); 
    h = GetJEPtSpect(sType[i]); listJE->Add(h); 
    h = GetPCPtSpect(sType[i], sPC2); listPC02->Add(h); 
    h = GetPCPtSpect(sType[i], Path); listPC04->Add(h); 
    h = GetPCPtSpect(sType[i], sPC6); listPC06->Add(h); 
  }

  h = GetJCPtSpect(sType[4],  Path);  listJC->Add(h); 
  h = GetJEPtSpect(sType[4],  Path);  listJE->Add(h); 
  h = GetPCPtSpect(sType[4], OPC2); listPC02->Add(h); 
  h = GetPCPtSpect(sType[4], Path); listPC04->Add(h); 
  h = GetPCPtSpect(sType[4], OPC6); listPC06->Add(h); 
  
  //----------------------------
  h = GetInclRatioLK();   listIn->Add(h); 
  h = GetInclRatioXK();   listIn->Add(h); 
  h = GetInclRatioOK();   listIn->Add(h); 
  h = GetInclRatioXL();   listIn->Add(h); 
  h = GetInclRatioOL();   listIn->Add(h); 
  h = GetInclRatioOX();   listIn->Add(h); 
  
  h = GetJCRatioLK();   listJC->Add(h); 
  h = GetJCRatioXK();   listJC->Add(h); 
  h = GetJCRatioXL();   listJC->Add(h); 
  h = GetJCRatioOK();   listJC->Add(h); 
  h = GetJCRatioOL();   listJC->Add(h); 
  h = GetJCRatioOX();   listJC->Add(h); 
  
  h = GetJERatioLK();   listJE->Add(h);
  h = GetJERatioXK();   listJE->Add(h);
  h = GetJERatioXL();   listJE->Add(h);
  h = GetJERatioOK();   listJE->Add(h);
  h = GetJERatioOL();   listJE->Add(h);
  h = GetJERatioOX();   listJE->Add(h);

  h = GetPCRatioLK(sPC2);   listPC02->Add(h);
  h = GetPCRatioXK(sPC2);   listPC02->Add(h);
  h = GetPCRatioXL(sPC2);   listPC02->Add(h);
  h = GetPCRatioOK(OPC2);   listPC02->Add(h);
  h = GetPCRatioOL(OPC2);   listPC02->Add(h);
  h = GetPCRatioOX(OPC2);   listPC02->Add(h);
  
  h = GetPCRatioLK();   listPC04->Add(h); 
  h = GetPCRatioXK();   listPC04->Add(h); 
  h = GetPCRatioXL();   listPC04->Add(h); 
  h = GetPCRatioOK();   listPC04->Add(h); 
  h = GetPCRatioOL();   listPC04->Add(h); 
  h = GetPCRatioOX();   listPC04->Add(h); 
  
  h = GetPCRatioLK(sPC6);   listPC06->Add(h);
  h = GetPCRatioXK(sPC6);   listPC06->Add(h);
  h = GetPCRatioXL(sPC6);   listPC06->Add(h);
  h = GetPCRatioOK(OPC6);   listPC06->Add(h);
  h = GetPCRatioOL(OPC6);   listPC06->Add(h);
  h = GetPCRatioOX(OPC6);   listPC06->Add(h);
  
  file->cd();
  listIn->Write(Form("listIn"), TObject::kSingleKey );
  
  listJC->Write(Form("listJC"), TObject::kSingleKey );
  listJE->Write(Form("listJE"), TObject::kSingleKey );
  listPC02->Write(Form("listPC02"), TObject::kSingleKey );
  listPC04->Write(Form("listPC04"), TObject::kSingleKey );
  listPC06->Write(Form("listPC06"), TObject::kSingleKey );
  
  file->Close();

}
