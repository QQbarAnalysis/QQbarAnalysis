void purity()
{
//=========Macro generated from canvas: canvas2/canvas2
//=========  (Wed Mar 13 18:28:10 2019) by ROOT version 6.11/01
   TCanvas *canvas2 = new TCanvas("canvas2", "canvas2",1345,108,1000,800);
   gStyle->SetOptStat(0);
   canvas2->Range(-1.332608,0.1278481,3.77119,1.203797);
   canvas2->SetFillColor(0);
   canvas2->SetBorderMode(0);
   canvas2->SetBorderSize(2);
   canvas2->SetTickx(1);
   canvas2->SetTicky(1);
   canvas2->SetLeftMargin(0.16);
   canvas2->SetRightMargin(0.05);
   canvas2->SetTopMargin(0.05);
   canvas2->SetBottomMargin(0.16);
   canvas2->SetFrameBorderMode(0);
   canvas2->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1001[4] = {
   0,
   1,
   2,
   3};
   Double_t Graph0_fy1001[4] = {
   0.8405297,
   0.8038816,
   0.7861161,
   0.7907189};
   Double_t Graph0_fex1001[4] = {
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t Graph0_fey1001[4] = {
   0.002395436,
   0.004185453,
   0.007111915,
   0.005039352};
   TGraphErrors *gre = new TGraphErrors(4,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("");
   gre->SetFillColor(1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#666666");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#666666");
   gre->SetMarkerColor(ci);
   
   TH1F *Graph_Graph1001 = new TH1F("Graph_Graph1001","",100,-0.9,3.9);
   Graph_Graph1001->SetMinimum(0.3);
   Graph_Graph1001->SetMaximum(1.15);
   Graph_Graph1001->SetDirectory(0);
   Graph_Graph1001->SetStats(0);
   Graph_Graph1001->SetLineWidth(2);
   Graph_Graph1001->SetMarkerStyle(20);
   Graph_Graph1001->SetMarkerSize(1.5);
   Graph_Graph1001->GetXaxis()->SetTitle("category");
   Graph_Graph1001->GetXaxis()->SetRange(9,92);
   Graph_Graph1001->GetXaxis()->SetNdivisions(5);
   Graph_Graph1001->GetXaxis()->SetLabelFont(42);
   Graph_Graph1001->GetXaxis()->SetLabelOffset(0.015);
   Graph_Graph1001->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph1001->GetXaxis()->SetTitleOffset(1.1);
   Graph_Graph1001->GetXaxis()->SetTitleFont(42);
   Graph_Graph1001->GetYaxis()->SetTitle("purity");
   Graph_Graph1001->GetYaxis()->SetLabelFont(42);
   Graph_Graph1001->GetYaxis()->SetLabelOffset(0.015);
   Graph_Graph1001->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph1001->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph1001->GetYaxis()->SetTitleFont(42);
   Graph_Graph1001->GetZaxis()->SetLabelFont(42);
   Graph_Graph1001->GetZaxis()->SetLabelOffset(0.015);
   Graph_Graph1001->GetZaxis()->SetTitleSize(0.05);
   Graph_Graph1001->GetZaxis()->SetTitleOffset(1.1);
   Graph_Graph1001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1001);
   
   gre->Draw("ape");
   
   Double_t Graph1_fx1002[4] = {
   0,
   1,
   2,
   3};
   Double_t Graph1_fy1002[4] = {
   0.802436,
   0.7586937,
   0.7355065,
   0.7930785};
   Double_t Graph1_fex1002[4] = {
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t Graph1_fey1002[4] = {
   0.0159936,
   0.01056699,
   0.05310067,
   0.03298672};
   gre = new TGraphErrors(4,Graph1_fx1002,Graph1_fy1002,Graph1_fex1002,Graph1_fey1002);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(4);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph1002 = new TH1F("Graph_Graph1002","Graph",100,-0.9,3.9);
   Graph_Graph1002->SetMinimum(0.6680399);
   Graph_Graph1002->SetMaximum(0.8404312);
   Graph_Graph1002->SetDirectory(0);
   Graph_Graph1002->SetStats(0);
   Graph_Graph1002->SetLineWidth(2);
   Graph_Graph1002->SetMarkerStyle(20);
   Graph_Graph1002->SetMarkerSize(1.5);
   Graph_Graph1002->GetXaxis()->SetLabelFont(42);
   Graph_Graph1002->GetXaxis()->SetLabelOffset(0.015);
   Graph_Graph1002->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph1002->GetXaxis()->SetTitleOffset(1.1);
   Graph_Graph1002->GetXaxis()->SetTitleFont(42);
   Graph_Graph1002->GetYaxis()->SetLabelFont(42);
   Graph_Graph1002->GetYaxis()->SetLabelOffset(0.015);
   Graph_Graph1002->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph1002->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph1002->GetYaxis()->SetTitleFont(42);
   Graph_Graph1002->GetZaxis()->SetLabelFont(42);
   Graph_Graph1002->GetZaxis()->SetLabelOffset(0.015);
   Graph_Graph1002->GetZaxis()->SetTitleSize(0.05);
   Graph_Graph1002->GetZaxis()->SetTitleOffset(1.1);
   Graph_Graph1002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1002);
   
   gre->Draw("pe");
   
   Double_t Graph2_fx1003[4] = {
   0,
   1,
   2,
   3};
   Double_t Graph2_fy1003[4] = {
   0.8114574,
   0.7081217,
   0.702571,
   0.7860803};
   Double_t Graph2_fex1003[4] = {
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t Graph2_fey1003[4] = {
   0.01532125,
   0.01418616,
   0.06295126,
   0.03522827};
   gre = new TGraphErrors(4,Graph2_fx1003,Graph2_fy1003,Graph2_fex1003,Graph2_fey1003);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(2);
   gre->SetLineStyle(2);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(22);
   
   TH1F *Graph_Graph1003 = new TH1F("Graph_Graph1003","Graph",100,-0.9,3.9);
   Graph_Graph1003->SetMinimum(0.6209039);
   Graph_Graph1003->SetMaximum(0.8454945);
   Graph_Graph1003->SetDirectory(0);
   Graph_Graph1003->SetStats(0);
   Graph_Graph1003->SetLineWidth(2);
   Graph_Graph1003->SetMarkerStyle(20);
   Graph_Graph1003->SetMarkerSize(1.5);
   Graph_Graph1003->GetXaxis()->SetLabelFont(42);
   Graph_Graph1003->GetXaxis()->SetLabelOffset(0.015);
   Graph_Graph1003->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph1003->GetXaxis()->SetTitleOffset(1.1);
   Graph_Graph1003->GetXaxis()->SetTitleFont(42);
   Graph_Graph1003->GetYaxis()->SetLabelFont(42);
   Graph_Graph1003->GetYaxis()->SetLabelOffset(0.015);
   Graph_Graph1003->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph1003->GetYaxis()->SetTitleOffset(1.1);
   Graph_Graph1003->GetYaxis()->SetTitleFont(42);
   Graph_Graph1003->GetZaxis()->SetLabelFont(42);
   Graph_Graph1003->GetZaxis()->SetLabelOffset(0.015);
   Graph_Graph1003->GetZaxis()->SetTitleSize(0.05);
   Graph_Graph1003->GetZaxis()->SetTitleOffset(1.1);
   Graph_Graph1003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1003);
   
   gre->Draw("pe");
   TLatex *   tex = new TLatex(0.2,0.2,"ILD");
tex->SetNDC();
   tex->SetTextSize(0.08);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.305,0.2,"Work in progress");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.5,0.7,0.9,0.9,NULL,"brNDC");
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph0","DBD, 250 GeV","lep");

   ci = TColor::GetColor("#666666");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#666666");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1","IDR-L, 500 GeV","lep");
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph2","IDR-S, 500 GeV","lep");
   entry->SetLineColor(2);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   canvas2->Modified();
   canvas2->cd();
   canvas2->SetSelected(canvas2);
}
