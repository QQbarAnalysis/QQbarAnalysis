#include <TPaveStats.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <TFitResult.h>
#include <TF1.h>
#include <TSpectrum.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TSystemFile.h"
#include "../../style/Style.C"
#include "../../style/Labels.C"

void quark_tagging() {

  TString filename = "../eff_purity_tag_eR.root";
  cout<<filename<<endl;
  TFile *f = new TFile(filename);

  TGraphErrors *c_purity = (TGraphErrors*)f->Get("cquark_purity");
  TGraphErrors *c_eff = (TGraphErrors*)f->Get("cquark_eff");

  TGraphErrors *b_purity = (TGraphErrors*)f->Get("bquark_purity");
  TGraphErrors *b_eff = (TGraphErrors*)f->Get("bquark_eff");
    
  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);
  //  gStyle->SetTitleOffset(1.3,"y");
  gStyle->SetTitleY(1);
  gStyle->SetTitleX(0.15);

  TCanvas * canvas_c = new TCanvas("canvas_c","canvas_c",800,800);
  /*    TGaxis *axis7 = new TGaxis(16,220,16,260,0.45,0.818,10,"+L");
  axis7->SetName("axis7");
  axis7->SetLabelOffset(0.01);
  axis7->SetTitle("Threshold [MIP]");
  axis7->SetTitleOffset(1.4);
  axis7->Draw();
  
  Int_t font=42; // Helvetica
  Double_t tsize=0.04;
  axis7->SetTextFont(font);

  axis7->SetTextSize(tsize);
  axis7->SetLabelFont(font);*/
  
  canvas_c->cd(1);
  c_eff->SetTitle("c-quark tagging");
  c_eff->GetYaxis()->SetRangeUser(0.,1.0);
  c_eff->GetXaxis()->SetRangeUser(0,1.);
  c_eff->GetXaxis()->SetTitle("c-tag value");
  c_eff->GetYaxis()->SetTitleOffset(1.3);
  //  c_eff->GetYaxis()->SetTitleColor(2);

  c_eff->SetLineColor(2);
  c_eff->SetLineWidth(2);
  c_eff->Draw("ac");

  c_purity->SetLineColor(4);
  c_purity->SetLineStyle(2);
  c_purity->SetLineWidth(4);
  c_purity->Draw("c");
  
  QQBARLabel(0.2,0.2,"Preliminary");
  QQBARLabel2(0.55,0.96, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250GeV",kGray+2);
  //"c-quark tagging",kGray+2);

  TLegend *leg0 = new TLegend(0.72,0.6,0.88,0.7);//(0.4,0.3,0.5,0.6);
  leg0->SetTextSize(0.035);
  leg0->AddEntry(c_eff,"#font[42]{Efficiency}","l");
  leg0->AddEntry(c_purity,"#font[42]{Purity}","l");
  leg0->SetFillStyle(0);
  leg0->SetLineWidth(0);
  leg0->SetLineColor(0);
  //  leg0->SetShadowColor(0);
  leg0->SetBorderSize(0);
  leg0->Draw();

  TCanvas * canvas_b = new TCanvas("canvas_b","canvas_b",800,800);
  canvas_b->cd(1);
  b_eff->SetTitle("b-quark tagging");
  b_eff->GetYaxis()->SetRangeUser(0.,1.);
  b_eff->GetXaxis()->SetRangeUser(0,1.);
  b_eff->GetXaxis()->SetTitle("b-tag value");
  b_eff->GetYaxis()->SetTitleOffset(1.3);
  //  b_eff->GetYaxis()->SetTitleColor(2);

  b_eff->SetLineColor(2);
  b_eff->SetLineWidth(2);
  b_eff->Draw("ac");

  b_purity->SetLineColor(4);
  b_purity->SetLineStyle(2);
  b_purity->SetLineWidth(4);
  b_purity->Draw("c");
  
  QQBARLabel(0.2,0.2,"Preliminary");
  QQBARLabel2(0.55,0.96, "125 GeV jets",kGray+2);

  TLegend *leg1 = new TLegend(0.72,0.5,0.88,0.6);//(0.4,0.3,0.5,0.6);
  leg1->SetTextSize(0.035);
  leg1->AddEntry(b_eff,"#font[42]{Efficiency}","l");
  leg1->AddEntry(b_purity,"#font[42]{Purity}","l");
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  //  leg1->SetShadowColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();

  canvas_c->Print("ctag_eff_purity.eps");
  canvas_b->Print("btag_eff_purity.eps");

  
}
