void ccan()
{
//=========Macro generated from canvas: ccan/can
//=========  (Fri Jul  3 16:45:22 2020) by ROOT version 6.16/00
   TCanvas *ccan = new TCanvas("ccan", "can",87,85,700,500);
   gStyle->SetOptStat(0);
   ccan->Range(0,0,1,1);
   ccan->SetFillColor(0);
   ccan->SetBorderMode(0);
   ccan->SetBorderSize(0);
   ccan->SetLeftMargin(0.13);
   ccan->SetRightMargin(0.03);
   ccan->SetTopMargin(0.02);
   ccan->SetBottomMargin(0.15);
   ccan->SetFrameFillStyle(0);
   ccan->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: cp1_R
   TPad *cp1_R = new TPad("cp1_R", "cp1_R",0.07951289,0.4501062,0.5393983,0.9808917);
   cp1_R->Draw();
   cp1_R->cd();
   cp1_R->Range(0.05714286,-18.07229,12.36937,102.4096);
   cp1_R->SetFillColor(0);
   cp1_R->SetBorderMode(0);
   cp1_R->SetBorderSize(0);
   cp1_R->SetTickx(1);
   cp1_R->SetTicky(1);
   cp1_R->SetLeftMargin(0);
   cp1_R->SetRightMargin(0.03);
   cp1_R->SetTopMargin(0.02);
   cp1_R->SetBottomMargin(0.15);
   cp1_R->SetFrameFillStyle(0);
   cp1_R->SetFrameBorderMode(0);
   cp1_R->SetFrameFillStyle(0);
   cp1_R->SetFrameBorderMode(0);
   Double_t xAxis1[22] = {0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5, 6, 8, 12}; 
   
   TH1D *h0__1 = new TH1D("h0__1","",21, xAxis1);
   h0__1->SetBinContent(1,0.05045545);
   h0__1->SetBinContent(2,0.04527223);
   h0__1->SetBinContent(3,0.03944501);
   h0__1->SetBinContent(4,0.03374971);
   h0__1->SetBinContent(5,0.02858129);
   h0__1->SetBinContent(6,0.02413924);
   h0__1->SetBinContent(7,0.01885239);
   h0__1->SetBinContent(8,0.01359765);
   h0__1->SetBinContent(9,0.009904106);
   h0__1->SetBinContent(10,0.007259082);
   h0__1->SetBinContent(11,0.005281507);
   h0__1->SetBinContent(12,0.003909619);
   h0__1->SetBinContent(13,0.00291906);
   h0__1->SetBinContent(14,0.002213365);
   h0__1->SetBinContent(15,0.001493513);
   h0__1->SetBinContent(16,0.0008600238);
   h0__1->SetBinContent(17,0.0004852739);
   h0__1->SetBinContent(18,0.0002530088);
   h0__1->SetBinContent(19,0.0001122156);
   h0__1->SetBinContent(20,3.899677e-05);
   h0__1->SetBinContent(21,7.683383e-06);
   h0__1->SetBinError(1,6.131727e-05);
   h0__1->SetBinError(2,5.313183e-05);
   h0__1->SetBinError(3,4.602787e-05);
   h0__1->SetBinError(4,3.98577e-05);
   h0__1->SetBinError(5,3.459734e-05);
   h0__1->SetBinError(6,3.024389e-05);
   h0__1->SetBinError(7,1.775052e-05);
   h0__1->SetBinError(8,1.399309e-05);
   h0__1->SetBinError(9,1.126093e-05);
   h0__1->SetBinError(10,9.285155e-06);
   h0__1->SetBinError(11,7.675484e-06);
   h0__1->SetBinError(12,6.499427e-06);
   h0__1->SetBinError(13,5.516631e-06);
   h0__1->SetBinError(14,4.799254e-06);
   h0__1->SetBinError(15,2.792601e-06);
   h0__1->SetBinError(16,1.930152e-06);
   h0__1->SetBinError(17,1.494455e-06);
   h0__1->SetBinError(18,8.958572e-07);
   h0__1->SetBinError(19,5.659279e-07);
   h0__1->SetBinError(20,2.611459e-07);
   h0__1->SetBinError(21,9.414728e-08);
   h0__1->SetMinimum(1e-06);
   h0__1->SetMaximum(100);
   h0__1->SetEntries(42);
   h0__1->SetDirectory(0);
   h0__1->SetFillStyle(0);
   h0__1->SetLineWidth(2);
   h0__1->SetMarkerStyle(20);
   h0__1->GetXaxis()->SetTitle("#it{p}_{T}(GeV/c)");
   h0__1->GetXaxis()->SetRange(0,21);
   h0__1->GetXaxis()->SetLabelFont(42);
   h0__1->GetXaxis()->SetLabelSize(0.05);
   h0__1->GetXaxis()->SetTitleSize(0.06);
   h0__1->GetXaxis()->SetTitleOffset(1.1);
   h0__1->GetXaxis()->SetTitleFont(42);
   h0__1->GetYaxis()->SetTitle("d#rho/d#it{p}_{T}");
   h0__1->GetYaxis()->SetNdivisions(505);
   h0__1->GetYaxis()->SetLabelFont(42);
   h0__1->GetYaxis()->SetLabelSize(0.05);
   h0__1->GetYaxis()->SetTitleSize(0.06);
   h0__1->GetYaxis()->SetTitleOffset(1);
   h0__1->GetYaxis()->SetTitleFont(42);
   h0__1->GetZaxis()->SetLabelFont(42);
   h0__1->GetZaxis()->SetLabelSize(0.035);
   h0__1->GetZaxis()->SetTitleSize(0.035);
   h0__1->GetZaxis()->SetTitleOffset(1);
   h0__1->GetZaxis()->SetTitleFont(42);
   h0__1->Draw("");
   
   Double_t g0_fx1001[21] = {
   0.65,
   0.75,
   0.85,
   0.95,
   1.05,
   1.15,
   1.3,
   1.5,
   1.7,
   1.9,
   2.1,
   2.3,
   2.5,
   2.7,
   3,
   3.45,
   3.95,
   4.6,
   5.5,
   7,
   10};
   Double_t g0_fy1001[21] = {
   0.05045545,
   0.04527223,
   0.03944501,
   0.03374971,
   0.02858129,
   0.02413924,
   0.01885239,
   0.01359765,
   0.009904106,
   0.007259082,
   0.005281507,
   0.003909619,
   0.00291906,
   0.002213365,
   0.001493513,
   0.0008600238,
   0.0004852739,
   0.0002530088,
   0.0001122156,
   3.899677e-05,
   7.683383e-06};
   Double_t g0_fex1001[21] = {
   0.05,
   0.05,
   0.05,
   0.05,
   0.05,
   0.05,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1};
   Double_t g0_fey1001[21] = {
   0.002202289,
   0.002023084,
   0.001717054,
   0.001430783,
   0.001210086,
   0.001033351,
   0.0008387847,
   0.0005978156,
   0.0004381642,
   0.0003365763,
   0.0002415089,
   0.0001752098,
   0.0001294463,
   9.643508e-05,
   6.460797e-05,
   3.682525e-05,
   2.054398e-05,
   1.101983e-05,
   4.724788e-06,
   1.627192e-06,
   3.209063e-07};
   TGraphErrors *gre = new TGraphErrors(21,g0_fx1001,g0_fy1001,g0_fex1001,g0_fey1001);
   gre->SetName("g0");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetFillStyle(0);
   gre->SetLineWidth(2);
   
   TH1F *Graph_g01001 = new TH1F("Graph_g01001","Graph",100,0,11.05);
   Graph_g01001->SetMinimum(6.626229e-06);
   Graph_g01001->SetMaximum(0.05792278);
   Graph_g01001->SetDirectory(0);
   Graph_g01001->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_g01001->SetLineColor(ci);
   Graph_g01001->GetXaxis()->SetLabelFont(42);
   Graph_g01001->GetXaxis()->SetLabelSize(0.035);
   Graph_g01001->GetXaxis()->SetTitleSize(0.035);
   Graph_g01001->GetXaxis()->SetTitleOffset(1);
   Graph_g01001->GetXaxis()->SetTitleFont(42);
   Graph_g01001->GetYaxis()->SetLabelFont(42);
   Graph_g01001->GetYaxis()->SetLabelSize(0.035);
   Graph_g01001->GetYaxis()->SetTitleSize(0.035);
   Graph_g01001->GetYaxis()->SetTitleFont(42);
   Graph_g01001->GetZaxis()->SetLabelFont(42);
   Graph_g01001->GetZaxis()->SetLabelSize(0.035);
   Graph_g01001->GetZaxis()->SetTitleSize(0.035);
   Graph_g01001->GetZaxis()->SetTitleOffset(1);
   Graph_g01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_g01001);
   
   gre->Draw("e2");
   cp1_R->Modified();
   ccan->cd();
  
// ------------>Primitives in pad: cp3_R
   TPad *cp3_R = new TPad("cp3_R", "cp3_R",0.08,0,0.54,0.53);
   cp3_R->Draw();
   cp3_R->cd();
   cp3_R->Range(0.6,-0.1800947,12.51663,1.002986);
   cp3_R->SetFillColor(0);
   cp3_R->SetBorderMode(0);
   cp3_R->SetBorderSize(0);
   cp3_R->SetTickx(1);
   cp3_R->SetTicky(1);
   cp3_R->SetLeftMargin(0);
   cp3_R->SetRightMargin(0.04335368);
   cp3_R->SetTopMargin(0.002523735);
   cp3_R->SetBottomMargin(0.1522253);
   cp3_R->SetFrameFillStyle(0);
   cp3_R->SetFrameBorderMode(0);
   cp3_R->SetFrameFillStyle(0);
   cp3_R->SetFrameBorderMode(0);
   Double_t xAxis2[8] = {0.6, 1.6, 2.2, 2.8, 3.7, 5, 8, 12}; 
   
   TH1D *h2__2 = new TH1D("h2__2","",7, xAxis2);
   h2__2->SetBinContent(1,0.06301163);
   h2__2->SetBinContent(2,0.02214102);
   h2__2->SetBinContent(3,0.01020838);
   h2__2->SetBinContent(4,0.004287663);
   h2__2->SetBinContent(5,0.001604921);
   h2__2->SetBinContent(6,0.000349455);
   h2__2->SetBinContent(7,6.929687e-05);
   h2__2->SetBinError(1,0.0002963388);
   h2__2->SetBinError(2,0.0001881416);
   h2__2->SetBinError(3,0.0001252875);
   h2__2->SetBinError(4,6.700877e-05);
   h2__2->SetBinError(5,3.55194e-05);
   h2__2->SetBinError(6,1.190726e-05);
   h2__2->SetBinError(7,5.535498e-06);
   h2__2->SetMinimum(1e-07);
   h2__2->SetMaximum(1);
   h2__2->SetEntries(14);
   h2__2->SetDirectory(0);
   h2__2->SetFillStyle(0);

   ci = TColor::GetColor("#0000cc");
   h2__2->SetLineColor(ci);
   h2__2->SetLineWidth(2);

   ci = TColor::GetColor("#0000cc");
   h2__2->SetMarkerColor(ci);
   h2__2->SetMarkerStyle(33);
   h2__2->GetXaxis()->SetTitle("#it{p}_{T}(GeV/c)");
   h2__2->GetXaxis()->SetLabelFont(42);
   h2__2->GetXaxis()->SetLabelSize(0.05);
   h2__2->GetXaxis()->SetTitleSize(0.06);
   h2__2->GetXaxis()->SetTitleOffset(1.1);
   h2__2->GetXaxis()->SetTitleFont(42);
   h2__2->GetYaxis()->SetTitle("d#rho/d#it{p}_{T}(#it{c}/GeV)");
   h2__2->GetYaxis()->SetNdivisions(505);
   h2__2->GetYaxis()->SetLabelFont(42);
   h2__2->GetYaxis()->SetLabelSize(0.05);
   h2__2->GetYaxis()->SetTitleSize(0.06);
   h2__2->GetYaxis()->SetTitleOffset(1);
   h2__2->GetYaxis()->SetTitleFont(42);
   h2__2->GetZaxis()->SetLabelFont(42);
   h2__2->GetZaxis()->SetLabelSize(0.035);
   h2__2->GetZaxis()->SetTitleSize(0.035);
   h2__2->GetZaxis()->SetTitleOffset(1);
   h2__2->GetZaxis()->SetTitleFont(42);
   h2__2->Draw("");
   
   Double_t g2_fx1002[7] = {
   1.1,
   1.9,
   2.5,
   3.25,
   4.35,
   6.5,
   10};
   Double_t g2_fy1002[7] = {
   0.06301163,
   0.02214102,
   0.01020838,
   0.004287663,
   0.001604921,
   0.000349455,
   6.929687e-05};
   Double_t g2_fex1002[7] = {
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1};
   Double_t g2_fey1002[7] = {
   0.00274932,
   0.001006192,
   0.0004516517,
   0.0001844317,
   6.914924e-05,
   1.462553e-05,
   2.894272e-06};
   gre = new TGraphErrors(7,g2_fx1002,g2_fy1002,g2_fex1002,g2_fey1002);
   gre->SetName("g2");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#0000cc");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);
   
   TH1F *Graph_g21002 = new TH1F("Graph_g21002","Graph",100,0.09,11.01);
   Graph_g21002->SetMinimum(5.976234e-05);
   Graph_g21002->SetMaximum(0.0723304);
   Graph_g21002->SetDirectory(0);
   Graph_g21002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_g21002->SetLineColor(ci);
   Graph_g21002->GetXaxis()->SetLabelFont(42);
   Graph_g21002->GetXaxis()->SetLabelSize(0.035);
   Graph_g21002->GetXaxis()->SetTitleSize(0.035);
   Graph_g21002->GetXaxis()->SetTitleOffset(1);
   Graph_g21002->GetXaxis()->SetTitleFont(42);
   Graph_g21002->GetYaxis()->SetLabelFont(42);
   Graph_g21002->GetYaxis()->SetLabelSize(0.035);
   Graph_g21002->GetYaxis()->SetTitleSize(0.035);
   Graph_g21002->GetYaxis()->SetTitleFont(42);
   Graph_g21002->GetZaxis()->SetLabelFont(42);
   Graph_g21002->GetZaxis()->SetLabelSize(0.035);
   Graph_g21002->GetZaxis()->SetTitleSize(0.035);
   Graph_g21002->GetZaxis()->SetTitleOffset(1);
   Graph_g21002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_g21002);
   
   gre->Draw("e2");
   cp3_R->Modified();
   ccan->cd();
  
// ------------>Primitives in pad: cp2_R
   TPad *cp2_R = new TPad("cp2_R", "cp2_R",0.5186246,0.4501062,1,0.9808917);
   cp2_R->Draw();
   cp2_R->cd();
   cp2_R->Range(0.6,-0.1807228,12.35258,1.024096);
   cp2_R->SetFillColor(0);
   cp2_R->SetBorderMode(0);
   cp2_R->SetBorderSize(0);
   cp2_R->SetTickx(1);
   cp2_R->SetTicky(1);
   cp2_R->SetLeftMargin(0);
   cp2_R->SetRightMargin(0.03);
   cp2_R->SetTopMargin(0.02);
   cp2_R->SetBottomMargin(0.15);
   cp2_R->SetFrameFillStyle(0);
   cp2_R->SetFrameBorderMode(0);
   cp2_R->SetFrameFillStyle(0);
   cp2_R->SetFrameBorderMode(0);
   Double_t xAxis3[8] = {0.6, 1.6, 2.2, 2.8, 3.7, 5, 8, 12}; 
   
   TH1D *h1__3 = new TH1D("h1__3","",7, xAxis3);
   h1__3->SetBinContent(1,0.07143329);
   h1__3->SetBinContent(2,0.06755646);
   h1__3->SetBinContent(3,0.05423842);
   h1__3->SetBinContent(4,0.03845551);
   h1__3->SetBinContent(5,0.02330685);
   h1__3->SetBinContent(6,0.009534538);
   h1__3->SetBinContent(7,0.002872849);
   h1__3->SetBinError(1,0.0009217205);
   h1__3->SetBinError(2,0.0008299824);
   h1__3->SetBinError(3,0.0007174123);
   h1__3->SetBinError(4,0.0005086065);
   h1__3->SetBinError(5,0.0003638953);
   h1__3->SetBinError(6,0.0001764486);
   h1__3->SetBinError(7,0.0001153528);
   h1__3->SetMinimum(1e-07);
   h1__3->SetMaximum(1);
   h1__3->SetEntries(28730.98);
   h1__3->SetDirectory(0);
   h1__3->SetFillStyle(0);

   ci = TColor::GetColor("#cc0000");
   h1__3->SetLineColor(ci);
   h1__3->SetLineWidth(2);

   ci = TColor::GetColor("#cc0000");
   h1__3->SetMarkerColor(ci);
   h1__3->SetMarkerStyle(24);
   h1__3->GetXaxis()->SetTitle("#it{p}_{T}(GeV/c)");
   h1__3->GetXaxis()->SetLabelFont(42);
   h1__3->GetXaxis()->SetLabelSize(0.05);
   h1__3->GetXaxis()->SetTitleSize(0.06);
   h1__3->GetXaxis()->SetTitleOffset(1.1);
   h1__3->GetXaxis()->SetTitleFont(42);
   h1__3->GetYaxis()->SetTitle("d#rho/d#it{p}_{T}(#it{c}/GeV)");
   h1__3->GetYaxis()->SetNdivisions(505);
   h1__3->GetYaxis()->SetLabelFont(42);
   h1__3->GetYaxis()->SetLabelSize(0.05);
   h1__3->GetYaxis()->SetTitleSize(0.06);
   h1__3->GetYaxis()->SetTitleOffset(1);
   h1__3->GetYaxis()->SetTitleFont(42);
   h1__3->GetZaxis()->SetLabelFont(42);
   h1__3->GetZaxis()->SetLabelSize(0.035);
   h1__3->GetZaxis()->SetTitleSize(0.035);
   h1__3->GetZaxis()->SetTitleOffset(1);
   h1__3->GetZaxis()->SetTitleFont(42);
   h1__3->Draw("");
   
   Double_t g1_fx1003[7] = {
   1.1,
   1.9,
   2.5,
   3.25,
   4.35,
   6.5,
   10};
   Double_t g1_fy1003[7] = {
   0.07143329,
   0.06755646,
   0.05423842,
   0.03845551,
   0.02330685,
   0.009534538,
   0.002872849};
   Double_t g1_fex1003[7] = {
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1};
   Double_t g1_fey1003[7] = {
   0.00837101,
   0.003800745,
   0.002221121,
   0.001304654,
   0.0007044525,
   0.0002706398,
   7.960777e-05};
   gre = new TGraphErrors(7,g1_fx1003,g1_fy1003,g1_fex1003,g1_fey1003);
   gre->SetName("g1");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#cc0000");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#cc0000");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);
   
   TH1F *Graph_g11003 = new TH1F("Graph_g11003","Graph",100,0.09,11.01);
   Graph_g11003->SetMinimum(0.002513917);
   Graph_g11003->SetMaximum(0.08750541);
   Graph_g11003->SetDirectory(0);
   Graph_g11003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_g11003->SetLineColor(ci);
   Graph_g11003->GetXaxis()->SetLabelFont(42);
   Graph_g11003->GetXaxis()->SetLabelSize(0.035);
   Graph_g11003->GetXaxis()->SetTitleSize(0.035);
   Graph_g11003->GetXaxis()->SetTitleOffset(1);
   Graph_g11003->GetXaxis()->SetTitleFont(42);
   Graph_g11003->GetYaxis()->SetLabelFont(42);
   Graph_g11003->GetYaxis()->SetLabelSize(0.035);
   Graph_g11003->GetYaxis()->SetTitleSize(0.035);
   Graph_g11003->GetYaxis()->SetTitleFont(42);
   Graph_g11003->GetZaxis()->SetLabelFont(42);
   Graph_g11003->GetZaxis()->SetLabelSize(0.035);
   Graph_g11003->GetZaxis()->SetTitleSize(0.035);
   Graph_g11003->GetZaxis()->SetTitleOffset(1);
   Graph_g11003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_g11003);
   
   gre->Draw("e2");
   cp2_R->Modified();
   ccan->cd();
  
// ------------>Primitives in pad: cp4_R
   TPad *cp4_R = new TPad("cp4_R", "cp4_R",0.52,0,1,0.53);
   cp4_R->Draw();
   cp4_R->cd();
   cp4_R->Range(0.5277764,-0.1800947,12.38944,1.002986);
   cp4_R->SetFillColor(0);
   cp4_R->SetBorderMode(0);
   cp4_R->SetBorderSize(0);
   cp4_R->SetTickx(1);
   cp4_R->SetTicky(1);
   cp4_R->SetLeftMargin(0.006088825);
   cp4_R->SetRightMargin(0.0328319);
   cp4_R->SetTopMargin(0.002523735);
   cp4_R->SetBottomMargin(0.1522253);
   cp4_R->SetFrameFillStyle(0);
   cp4_R->SetFrameBorderMode(0);
   cp4_R->SetFrameFillStyle(0);
   cp4_R->SetFrameBorderMode(0);
   Double_t xAxis4[8] = {0.6, 1.6, 2.2, 2.8, 3.7, 5, 8, 12}; 
   
   TH1D *h2__4 = new TH1D("h2__4","",7, xAxis4);
   h2__4->SetBinContent(1,0.06301163);
   h2__4->SetBinContent(2,0.02214102);
   h2__4->SetBinContent(3,0.01020838);
   h2__4->SetBinContent(4,0.004287663);
   h2__4->SetBinContent(5,0.001604921);
   h2__4->SetBinContent(6,0.000349455);
   h2__4->SetBinContent(7,6.929687e-05);
   h2__4->SetBinError(1,0.0002963388);
   h2__4->SetBinError(2,0.0001881416);
   h2__4->SetBinError(3,0.0001252875);
   h2__4->SetBinError(4,6.700877e-05);
   h2__4->SetBinError(5,3.55194e-05);
   h2__4->SetBinError(6,1.190726e-05);
   h2__4->SetBinError(7,5.535498e-06);
   h2__4->SetMinimum(1e-07);
   h2__4->SetMaximum(1);
   h2__4->SetEntries(14);
   h2__4->SetDirectory(0);
   h2__4->SetFillStyle(0);

   ci = TColor::GetColor("#0000cc");
   h2__4->SetLineColor(ci);
   h2__4->SetLineWidth(2);

   ci = TColor::GetColor("#0000cc");
   h2__4->SetMarkerColor(ci);
   h2__4->SetMarkerStyle(33);
   h2__4->GetXaxis()->SetTitle("#it{p}_{T}(GeV/c)");
   h2__4->GetXaxis()->SetLabelFont(42);
   h2__4->GetXaxis()->SetLabelSize(0.05);
   h2__4->GetXaxis()->SetTitleSize(0.06);
   h2__4->GetXaxis()->SetTitleOffset(1.1);
   h2__4->GetXaxis()->SetTitleFont(42);
   h2__4->GetYaxis()->SetTitle("d#rho/d#it{p}_{T}(#it{c}/GeV)");
   h2__4->GetYaxis()->SetNdivisions(505);
   h2__4->GetYaxis()->SetLabelFont(42);
   h2__4->GetYaxis()->SetLabelSize(0.05);
   h2__4->GetYaxis()->SetTitleSize(0.06);
   h2__4->GetYaxis()->SetTitleOffset(1);
   h2__4->GetYaxis()->SetTitleFont(42);
   h2__4->GetZaxis()->SetLabelFont(42);
   h2__4->GetZaxis()->SetLabelSize(0.035);
   h2__4->GetZaxis()->SetTitleSize(0.035);
   h2__4->GetZaxis()->SetTitleOffset(1);
   h2__4->GetZaxis()->SetTitleFont(42);
   h2__4->Draw("");
   
   Double_t g2_fx1004[7] = {
   1.1,
   1.9,
   2.5,
   3.25,
   4.35,
   6.5,
   10};
   Double_t g2_fy1004[7] = {
   0.06301163,
   0.02214102,
   0.01020838,
   0.004287663,
   0.001604921,
   0.000349455,
   6.929687e-05};
   Double_t g2_fex1004[7] = {
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1};
   Double_t g2_fey1004[7] = {
   0.00274932,
   0.001006192,
   0.0004516517,
   0.0001844317,
   6.914924e-05,
   1.462553e-05,
   2.894272e-06};
   gre = new TGraphErrors(7,g2_fx1004,g2_fy1004,g2_fex1004,g2_fey1004);
   gre->SetName("g2");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#0000cc");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#0000cc");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);
   
   TH1F *Graph_Graph_g210021004 = new TH1F("Graph_Graph_g210021004","Graph",100,0.09,11.01);
   Graph_Graph_g210021004->SetMinimum(5.976234e-05);
   Graph_Graph_g210021004->SetMaximum(0.0723304);
   Graph_Graph_g210021004->SetDirectory(0);
   Graph_Graph_g210021004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_g210021004->SetLineColor(ci);
   Graph_Graph_g210021004->GetXaxis()->SetLabelFont(42);
   Graph_Graph_g210021004->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_g210021004->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_g210021004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_g210021004->GetXaxis()->SetTitleFont(42);
   Graph_Graph_g210021004->GetYaxis()->SetLabelFont(42);
   Graph_Graph_g210021004->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_g210021004->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_g210021004->GetYaxis()->SetTitleFont(42);
   Graph_Graph_g210021004->GetZaxis()->SetLabelFont(42);
   Graph_Graph_g210021004->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_g210021004->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_g210021004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_g210021004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_g210021004);
   
   gre->Draw("e2");
   
   TLegend *leg = new TLegend(0.7,0.6,1,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("h0","Inclusive","lpf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("h1","JE","lpf");

   ci = TColor::GetColor("#cc0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#cc0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("h2","JE","lpf");

   ci = TColor::GetColor("#0000cc");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#0000cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("h2","JE","lpf");

   ci = TColor::GetColor("#0000cc");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#0000cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("g0","Sys.Error","f");
   entry->SetFillColor(1);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   cp4_R->Modified();
   ccan->cd();
   ccan->Modified();
   ccan->cd();
   ccan->SetSelected(ccan);
}
