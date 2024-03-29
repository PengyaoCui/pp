#include "./inc/TStrangeJet.h"

//-------------------------------------------------------------
void CentVal(){

  TString Path = "/home/cuipengyao/study/pp/Local/ThisAna/JE_OmegaBins";
  TFile *file = TFile::Open("./result/CentVal.root", "UPDATE");
  TList *listIn = (TList*)file->Get(Form("listIn"));             if (!listIn){listIn = new TList();}

  TList *listJC = (TList*)file->Get(Form("listJC"));     if (!listJC){listJC = new TList();}
  TList *listPC = (TList*)file->Get(Form("listPC"));     if (!listPC){listPC = new TList();}
  TList *listJE = (TList*)file->Get(Form("listJE"));     if (!listJE){listJE = new TList();}
  TList *listOC04 = (TList*)file->Get(Form("listOC04")); if (!listOC04){listOC04 = new TList();}
  TList *listNJ = (TList*)file->Get(Form("listNJ"));     if (!listNJ){listNJ = new TList();}
  
  TH1D* h = nullptr;
  TString sType[] = {"Kshort", "Lambda", "AntiLa", "Xi", "Omega"};
  for(Int_t i = 0; i< sizeof(sType)/sizeof(TString); i++){
    h = GetInclPtSpect(sType[i]); listIn->Add(h); 
  
  }
  for(Int_t i = 0; i< sizeof(sType)/sizeof(TString)-1; i++){
    h = GetJCPtSpect(sType[i]); listJC->Add(h); 
    h = GetPCPtSpect(sType[i]); listPC->Add(h); 
    h = GetJEPtSpect(sType[i]); listJE->Add(h); 
    h = GetOC04PtSpect(sType[i]); listOC04->Add(h); 
    h = GetNJPtSpect(sType[i]); listNJ->Add(h); 
  }

  h = GetJCPtSpect(sType[4],  Path);   listJC->Add(h); 
  h = GetPCPtSpect(sType[4],  Path);   listPC->Add(h); 
  h = GetJEPtSpect(sType[4],  Path);   listJE->Add(h); 
  h = GetOC04PtSpect(sType[4], Path); listOC04->Add(h); 
  h = GetNJPtSpect(sType[4], Path);   listNJ->Add(h); 
  
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
  
  h = GetPCRatioLK();   listPC->Add(h); 
  h = GetPCRatioXK();   listPC->Add(h); 
  h = GetPCRatioXL();   listPC->Add(h); 
  h = GetPCRatioOK();   listPC->Add(h); 
  h = GetPCRatioOL();   listPC->Add(h); 
  h = GetPCRatioOX();   listPC->Add(h); 
  
  h = GetJERatioLK();   listJE->Add(h);
  h = GetJERatioXK();   listJE->Add(h);
  h = GetJERatioXL();   listJE->Add(h);
  h = GetJERatioOK();   listJE->Add(h);
  h = GetJERatioOL();   listJE->Add(h);
  h = GetJERatioOX();   listJE->Add(h);

  h = GetOC04RatioLK();   listOC04->Add(h);
  h = GetOC04RatioXK();   listOC04->Add(h);
  h = GetOC04RatioXL();   listOC04->Add(h);
  h = GetOC04RatioOK();   listOC04->Add(h);
  h = GetOC04RatioOL();   listOC04->Add(h);
  h = GetOC04RatioOX();   listOC04->Add(h);

  h = GetNJRatioLK();   listNJ->Add(h);
  h = GetNJRatioXK();   listNJ->Add(h);
  h = GetNJRatioXL();   listNJ->Add(h);
  h = GetNJRatioOK();   listNJ->Add(h);
  h = GetNJRatioOL();   listNJ->Add(h);
  h = GetNJRatioOX();   listNJ->Add(h);

 
 
  
  file->cd();
  listIn->Write(Form("listIn"), TObject::kSingleKey );
  
  listJC->Write(Form("listJC"), TObject::kSingleKey );
  listPC->Write(Form("listPC"), TObject::kSingleKey );
  listJE->Write(Form("listJE"), TObject::kSingleKey );
  listOC04->Write(Form("listOC04"), TObject::kSingleKey );
  listNJ->Write(Form("listNJ"), TObject::kSingleKey );
  
  file->Close();

}
