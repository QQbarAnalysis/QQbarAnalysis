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
#include "../../../style/Style.C"
#include "../../../style/Labels.C"


void Labels(){

  QQBARLabel(0.86,0.952,"");
  QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow b#bar{b} (K_{#gamma}<35 GeV)",kGray+2);

}



void dEdxplots3() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  gStyle->SetPadLeftMargin(0.2);

  TString run="test";
 
  TString filename = "../output_250_secondary_tracks_"+run+".root";
  TFile *f = new TFile(filename);
  TGraphErrors* eff_purity = (TGraphErrors*) f->Get("eff_purity");
  
  filename = "../output_250_secondary_tracks_angularcorrection_"+run+".root";
  f = new TFile(filename);
  TGraphErrors* eff_purity2 = (TGraphErrors*) f->Get("eff_purity");

 
  TCanvas* c_eff_purity2 = new TCanvas("c_eff_purity2","c_eff_purity2",800,800);
  // gStyle->SetPadLeftMargin(0.16);

  eff_purity->GetXaxis()->SetTitle("K id. Eficiency [%]");
  eff_purity->GetYaxis()->SetTitle("K id. Purity [%]");
  // eff_purity->GetYaxis()->SetTitleOffset(1.9);
  //  eff_purity->GetXaxis()->SetRangeUser(75,100);
  eff_purity->GetYaxis()->SetRangeUser(0.75,1);

  eff_purity->SetMarkerColor(4);
  eff_purity->SetMarkerStyle(21);
  eff_purity->SetMarkerSize(1.2);
  eff_purity->SetLineColor(4);
  eff_purity->Draw("alp");
 
  eff_purity2->SetMarkerColor(2);
  eff_purity2->SetMarkerStyle(22);
  eff_purity2->SetMarkerSize(1.2);
  eff_purity2->SetLineColor(2);
  eff_purity2->Draw("lp");
  
  Labels();
  
  TLegend *leg1 = new TLegend(0.25,0.2,0.5,0.3);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(eff_purity,"K/#pi - 2021 Default","lp");
  leg1->AddEntry(eff_purity2,"K/#pi - 2021 Angular correction","lp");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
  
   

}
