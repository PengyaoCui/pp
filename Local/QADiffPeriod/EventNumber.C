
void EventNumber(const TString sP = "16e"){
  auto f = TFile::Open(Form("./%s/AnalysisOutputs_Loop1ndRD.root", sP.Data()), "read");
  auto l = (TList*)f->Get("listLoop1ndRD_Kshort_Default");
  f->Close();
  auto h = (TH1D*)l->FindObject("hEvent");
  cout<<sP<< " == " <<h->GetEntries()<<endl;
  return;
}

