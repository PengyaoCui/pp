void EventNumber(){
  auto f = TFile::Open(Form("./AnalysisOutputs_Loop1ndRD.root"), "read");
  auto l = (TList*)f->Get("listLoop1ndRD_Xi_Default");
  f->Close();
  auto h = (TH1D*)l->FindObject("hEvent");
  cout<< " == " <<h->GetEntries()<<endl;
  return;
}


