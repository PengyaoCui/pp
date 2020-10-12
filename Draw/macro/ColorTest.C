void ColorTest()
{
  TH1 *h1 = new TH1F("h1","h",3,0,3);
  TH1 *h2 = (TH1*) h1->Clone("h2");
  TH1 *h3 = (TH1*) h1->Clone("h3");
  h1->Fill(0.0,3.0);
  h2->Fill(1,2);
  h3->Fill(2,1);

  TColor *c1 = new TColor(9001,1,0.5,0); //is this your color?
  TColor *c2 = new TColor(9002,0,1,0); //green
  TColor *c3 = new TColor(9003,0,0,1); //blue

  h1->SetFillColor(9001);
  h2->SetFillColor(9002);
  h3->SetFillColor(9003);

  h1->Draw("hist");
  h2->Draw("histsame");
  h3->Draw("histsame");
}

