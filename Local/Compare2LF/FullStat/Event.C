void Event(){

TFile* f = TFile::Open("AnalysisOutputs_Loop1ndRD.root");
TList*l = (TList*)f->Get("listLoop1ndRD_AntiLa_Default");
TH1D*h = (TH1D*)l->FindObject("hEvent");
cout<<h->GetBinContent(1)<<endl;

return 0x0;
}
