const Int_t cycleL = 50;
//=============================================================================
void AnaMergeFilesLocal(TString ifList="dataset_merge.txt", TString ofName="AnalysisResults.root")
{
  if (LoadLibraries()) return;
  if (ofName.EndsWith(".root")) ofName.ReplaceAll(".root","");

  TString ifName;
  TFileMerger merger;
  TSystemFile *systFile=0;
  Int_t count=0, cycleN=0;
  ifstream dataList(ifList.Data(), ios::in);
  while (!dataList.eof()) {  // loop with the cycle length
    ifName.ReadLine(dataList,kFALSE);
    if (!ifName.EndsWith(".root")) continue;
    if (gSystem->AccessPathName(ifName.Data())) continue;
    if (merger.AddFile(ifName.Data(),kFALSE)) count++;
    if ((count%cycleL)==0) {  // merge in cycle
      cycleN = count/cycleL;  cout << "cycleN===" << cycleN << endl;
      TString previous = Form("%s_%d.root",ofName.Data(),cycleN-1);
      if (!gSystem->AccessPathName(previous.Data())) {
        merger.AddFile(previous.Data(),kFALSE);
        systFile = new TSystemFile(previous.Data(),"."); systFile->Delete(); delete systFile; systFile=0;
      } merger.OutputFile(Form("%s_%d.root",ofName.Data(),cycleN)); merger.Merge(); merger.Reset();
    }  // end merge in cycle
  }    // end loop with the cycle length
  if (count==0) { cout << "No input file!!!" << endl; return; }

  if (count<cycleL) { // the end of the day
    cout << "cycleN===" << 0 << endl;
    merger.OutputFile(Form("%s.root",ofName.Data())); merger.Merge();
  } else if ((count%cycleL)==0) {
    TString lastFileName = Form("%s_%d.root",ofName.Data(),cycleN);
    if (gSystem->AccessPathName(lastFileName.Data())) { cout << "Merging failed miserably!!!" << endl; return; }
    gSystem->Rename(lastFileName.Data(), Form("%s.root",ofName.Data()));
  } else {
    TString lastFileName = Form("%s_%d.root",ofName.Data(),cycleN);
    if (gSystem->AccessPathName(lastFileName.Data())) { cout << "Merging failed miserably!!!" << endl; return; }
    cout << "cycleN===" << cycleN+1 << endl;
    merger.AddFile(lastFileName.Data(),kFALSE); merger.OutputFile(Form("%s.root",ofName.Data())); merger.Merge();
    systFile = new TSystemFile(lastFileName.Data(),"."); systFile->Delete(); delete systFile; systFile=0;
  } return;
}
//=============================================================================
Bool_t LoadLibraries()
{
  if (gSystem->Load("libCore")       <0) return kTRUE;
  if (gSystem->Load("libTree")       <0) return kTRUE;
  if (gSystem->Load("libGeom")       <0) return kTRUE;
  if (gSystem->Load("libVMC")        <0) return kTRUE;
  if (gSystem->Load("libXMLIO")      <0) return kTRUE;
  if (gSystem->Load("libPhysics")    <0) return kTRUE;
  if (gSystem->Load("libXMLParser")  <0) return kTRUE;
  if (gSystem->Load("libProof")      <0) return kTRUE;
  if (gSystem->Load("libMinuit")     <0) return kTRUE;
  if (gSystem->Load("libGui")        <0) return kTRUE;
  if (gSystem->Load("libProofPlayer")<0) return kTRUE;
  if (gSystem->Load("libXMLParser")  <0) return kTRUE;
//=============================================================================


  return kFALSE;
}
