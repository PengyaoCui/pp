void CopyList(TString File1, TString File2, TString List)
{
  
  TString sFileName1 = File1;
  TString sFileName2 = File2;
  TString  sListName = List;

  TFile*   f1 = TFile::Open(sFileName1,"UPDATE"); if (!f1->IsOpen()) return 0x0;
  TFile*   f2 = TFile::Open(sFileName2,"read"); if (!f2->IsOpen()) return 0x0;
  TList* list = (TList*)f2->Get(sListName);  if (!list) return 0x0;
  
  f2->Close();
  f1->cd();
  list->Write(sListName, TObject::kSingleKey);
  f1->Close();
  return;

}

