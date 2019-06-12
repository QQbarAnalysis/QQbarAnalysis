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
#include "TLine.h"
#include "../style/Style.C"
#include "../style/Labels.C"


void bjet_info() {

  //---------------------------------
  TString filename = "ttbar_bjet_info.root";
  TFile *f = new TFile(filename);
  TH1F *ttbar_bjet_p_l5 = (TH1F*)f->Get("bjet_p_l5");
  TH1F *ttbar_bjet_p_s5 = (TH1F*)f->Get("bjet_p_s5");
  ttbar_bjet_p_l5->Rebin(5);
  ttbar_bjet_p_s5->Rebin(5);

  // TH1F *ttbar_bquark_p_l5 = (TH1F*)f->Get("bquark_p_l5");
  // TH1F *ttbar_bquark_p_s5 = (TH1F*)f->Get("bquark_p_s5");
  // ttbar_bquark_p_l5->Rebin(5);
  // ttbar_bquark_p_s5->Rebin(5);
  
  filename = "bbbar_bjet_info.root";
  TFile *f2 = new TFile(filename);
  TH1F *bbbar_bjet_p_l5 = (TH1F*)f2->Get("bjet_p_l5_valencia2.0");
  TH1F *bbbar_bjet_p_s5 = (TH1F*)f2->Get("bjet_p_s5_valencia2.0");
  bbbar_bjet_p_l5->Rebin(5);
  bbbar_bjet_p_s5->Rebin(5);

  TH1F *bbbar_bquark_p_l5 = (TH1F*)f2->Get("bquark_p_l5_valencia2.0");
  TH1F *bbbar_bquark_p_s5 = (TH1F*)f2->Get("bquark_p_s5_valencia2.0");
  bbbar_bquark_p_l5->Rebin(5);
  bbbar_bquark_p_s5->Rebin(5);
  
  //-----------------------------------------------------
  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);

  gStyle->SetTitleX(0.4); 
  gStyle->SetTitleY(0.8); 
  // TGaxis::SetMaxDigits(2); //

  
  TCanvas * canvas0 = new TCanvas ("canvas0","canvas0",1000,800);
  canvas0->cd(1);
  bbbar_bjet_p_l5->GetXaxis()->SetTitle("b-jet momentum [GeV]");
  bbbar_bjet_p_l5->GetXaxis()->SetTitleOffset(1.1);
  bbbar_bjet_p_l5->GetXaxis()->SetTitleFont(42);
  bbbar_bjet_p_l5->GetXaxis()->SetTitleSize(0.05);
  bbbar_bjet_p_l5->GetXaxis()->SetLabelSize(0.05);
  bbbar_bjet_p_l5->GetXaxis()->SetLabelOffset(0.015);

  bbbar_bjet_p_l5->GetYaxis()->SetTitle("a.u.");
  bbbar_bjet_p_l5->GetYaxis()->SetTitleOffset(1.4);
  bbbar_bjet_p_l5->GetYaxis()->SetTitleFont(42);
  bbbar_bjet_p_l5->GetYaxis()->SetTitleSize(0.05);
  bbbar_bjet_p_l5->GetYaxis()->SetLabelSize(0.05);
  bbbar_bjet_p_l5->GetYaxis()->SetLabelOffset(0.015);
  bbbar_bjet_p_l5->GetYaxis()->SetRangeUser(0,bbbar_bjet_p_l5->GetMaximum()*2);

  bbbar_bjet_p_l5->SetLineWidth(4);
  bbbar_bjet_p_l5->SetLineColor(kGray+3);
  bbbar_bjet_p_l5->DrawNormalized("histo");
  
  ttbar_bjet_p_l5->SetLineWidth(4);
  ttbar_bjet_p_l5->SetLineStyle(2);
  ttbar_bjet_p_l5->SetLineColor(kGray+1);
  ttbar_bjet_p_l5->DrawNormalized("histosame");
   
  QQBARLabel(0.2,0.85,"Preliminary",1);

  TLegend *leg = new TLegend(0.4,0.6,0.9,0.75);
  leg->SetTextFont(42);
  leg->SetHeader("#font[42]{e_{L}^{+}e_{R}^{-}#rightarrow X @ 500GeV, IDR-L}");
  leg->AddEntry(bbbar_bjet_p_l5,"X=b#bar{b}","l");
  leg->AddEntry(ttbar_bjet_p_l5,"X=t#bar{t}","l");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();
  
  /*
  
  TCanvas * canvas1 = new TCanvas ("canvas1","canvas1",1000,600);
  canvas1->Divide(2,1);
  canvas1->cd(1);
  bbbar_bquark_p_l5->GetXaxis()->SetTitle("b-quark momentum [GeV]");
  bbbar_bquark_p_l5->GetXaxis()->SetTitleOffset(1.1);
  bbbar_bquark_p_l5->GetXaxis()->SetTitleFont(42);
  bbbar_bquark_p_l5->GetXaxis()->SetTitleSize(0.05);
  bbbar_bquark_p_l5->GetXaxis()->SetLabelSize(0.05);
  bbbar_bquark_p_l5->GetXaxis()->SetLabelOffset(0.015);

  bbbar_bquark_p_l5->GetYaxis()->SetTitle("a.u.");
  bbbar_bquark_p_l5->GetYaxis()->SetTitleOffset(1.4);
  bbbar_bquark_p_l5->GetYaxis()->SetTitleFont(42);
  bbbar_bquark_p_l5->GetYaxis()->SetTitleSize(0.05);
  bbbar_bquark_p_l5->GetYaxis()->SetLabelSize(0.05);
  bbbar_bquark_p_l5->GetYaxis()->SetLabelOffset(0.015);
  bbbar_bquark_p_l5->GetYaxis()->SetRangeUser(0,bbbar_bquark_p_l5->GetMaximum()*2);

  bbbar_bquark_p_l5->SetLineWidth(4);
  bbbar_bquark_p_l5->SetLineColor(4);
  bbbar_bquark_p_l5->DrawNormalized("histo");
  
  bbbar_bquark_p_s5->SetLineWidth(4);
  bbbar_bquark_p_s5->SetLineStyle(2);
  bbbar_bquark_p_s5->SetLineColor(2);
  bbbar_bquark_p_s5->DrawNormalized("histosame");
   
  QQBARLabel(0.2,0.85,"Preliminary",1);

  TLegend *leg1 = new TLegend(0.4,0.6,0.9,0.75);
  leg1->SetTextFont(42);
  leg1->SetHeader("#font[42]{e_{L}^{+}e_{R}^{-}#rightarrow b#bar{b} @ 500GeV}");
  leg1->AddEntry(bbbar_bquark_p_l5,"IDR-L","l");
  leg1->AddEntry(bbbar_bquark_p_s5,"IDR-S","l");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();

  canvas1->cd(2);
  bbbar_bjet_p_l5->GetXaxis()->SetTitle("b-jet momentum [GeV]");
  bbbar_bjet_p_l5->GetXaxis()->SetTitleOffset(1.1);
  bbbar_bjet_p_l5->GetXaxis()->SetTitleFont(42);
  bbbar_bjet_p_l5->GetXaxis()->SetTitleSize(0.05);
  bbbar_bjet_p_l5->GetXaxis()->SetLabelSize(0.05);
  bbbar_bjet_p_l5->GetXaxis()->SetLabelOffset(0.015);

  bbbar_bjet_p_l5->GetYaxis()->SetTitle("a.u.");
  bbbar_bjet_p_l5->GetYaxis()->SetTitleOffset(1.4);
  bbbar_bjet_p_l5->GetYaxis()->SetTitleFont(42);
  bbbar_bjet_p_l5->GetYaxis()->SetTitleSize(0.05);
  bbbar_bjet_p_l5->GetYaxis()->SetLabelSize(0.05);
  bbbar_bjet_p_l5->GetYaxis()->SetLabelOffset(0.015);
  bbbar_bjet_p_l5->GetYaxis()->SetRangeUser(0,bbbar_bjet_p_l5->GetMaximum()*2);

  bbbar_bjet_p_l5->SetLineWidth(4);
  bbbar_bjet_p_l5->SetLineColor(4);
  bbbar_bjet_p_l5->DrawNormalized("histo");
  
  bbbar_bjet_p_s5->SetLineWidth(4);
  bbbar_bjet_p_s5->SetLineStyle(2);
  bbbar_bjet_p_s5->SetLineColor(2);
  bbbar_bjet_p_s5->DrawNormalized("histosame");
   
  QQBARLabel(0.2,0.85,"Preliminary",1);
  leg1->Draw();*/

}
