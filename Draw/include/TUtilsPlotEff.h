TCanvas* MakeCanvas(TString sName)
{
  TCanvas *c = new TCanvas(Form("c%s",sName.Data()), sName.Data(), 700, 750);
  c->Range(0., 0., 1., 1.);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(0);
  c->SetRightMargin(0.);
  c->SetLeftMargin(0.);
  c->SetTopMargin(0.);
  c->SetBottomMargin(0.);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);

  return c;
}

//_____________________________________________________________________________
void CanvasEnd(TCanvas *c)
{
  if (!c) return;

  c->Modified();
  c->cd();
  c->SetSelected(c);

  return;
}

//_____________________________________________________________________________
TPad *MakePadLower(TString sName)
{
  TPad *p = new TPad(Form("c%s_Lower",sName.Data()), Form("%s_Lower",sName.Data()), 0., 0., 1., 0.4);
  p->Range(0., 0., 1., 1.);
  p->SetFillColor(0);
  p->SetBorderMode(0);
  p->SetBorderSize(0);
  p->SetRightMargin(0.02);
  p->SetLeftMargin(0.11);
  p->SetTopMargin(0.);
  p->SetBottomMargin(0.26);
  p->SetFrameFillStyle(0);
  p->SetFrameBorderMode(0);
  p->Draw();
  p->cd();

  return p;
}

//_____________________________________________________________________________
TPad *MakePadUpper(TString sName)
{
  TPad *p = new TPad(Form("c%s_Upper",sName.Data()), Form("%s_Upper",sName.Data()), 0., 0.4, 1., 1.);
  p->Range(0., 0., 1., 1.);
  p->SetFillColor(0);
  p->SetBorderMode(0);
  p->SetBorderSize(0);
  p->SetRightMargin(0.02);
  p->SetLeftMargin(0.11);
  p->SetTopMargin(0.02);
  p->SetBottomMargin(0.);
  p->SetFrameFillStyle(0);
  p->SetFrameBorderMode(0);
  p->Draw();
  p->cd();

  return p;
}
