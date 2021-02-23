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

  /* if(i==0) QQBARLabel2(0.04,0.07, "[No Cuts]",kOrange+3);
  if(i==1) QQBARLabel2(0.04,0.07, "Photon veto",kOrange+3);
  if(i==2) QQBARLabel2(0.04,0.07, "Photon veto & K_{reco}<35 GeV",kOrange+3);
  if(i==3) {
    QQBARLabel2(0.04,0.082, "Photon veto & K_{reco}<35 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& m_{j_{1},j_{2}}>130 GeV",kOrange+3);
  }
  if(i==4) {
    QQBARLabel2(0.04,0.082, "Photon veto & K_{reco}<35 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& m_{j_{1},j_{2}}>130 GeV & y23<0.015",kOrange+3);
  }
  if(i==5) {
    QQBARLabel2(0.04,0.082, "Photon veto & K_{reco}<35 GeV & m_{j_{1},j_{2}}>130 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& y23<0.015 & (m_{j1}+m_{j2})<100 GeV",kOrange+3);
  }
   

  if(pol=="eL")QQBARLabel2(0.3,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  if(pol=="eR")QQBARLabel2(0.3,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  */
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

 
  TString filename = "../output_250_all_250GeV_DBD_eL_norestorer.root";
  TFile *f = new TFile(filename);
  TGraphErrors* eff_purity = (TGraphErrors*) f->Get("eff_purity");
  
  filename = "../output_250_all_250GeV_mc2020-15162_eL_lcfi_VVB1.17_2021_long.root";//output_250_all_250GeV_mc2020-15162_eL_lcfi_VVB1.17_norestorer.root";
  f = new TFile(filename);
  TGraphErrors* eff_purity2 = (TGraphErrors*) f->Get("eff_purity");

   
  TCanvas* c_eff_purity = new TCanvas("c_eff_purity","c_eff_purity",800,800);
  // gStyle->SetPadLeftMargin(0.16);

  eff_purity2->GetXaxis()->SetTitle("K id. Eficiency [%]");
  eff_purity2->GetYaxis()->SetTitle("K id. Purity [%]");
  // eff_purity->GetYaxis()->SetTitleOffset(1.9);
  //  eff_purity->GetXaxis()->SetRangeUser(0.8,50);
  eff_purity2->GetYaxis()->SetRangeUser(0.5,1);
 
  eff_purity2->SetMarkerColor(2);
  eff_purity2->SetMarkerStyle(22);
  eff_purity2->SetMarkerSize(1.2);
  eff_purity2->SetLineColor(2);
  eff_purity2->Draw("alp");
  
  Labels();
  
  /*TLegend *leg1 = new TLegend(0.7,0.8,0.8,0.9);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(eff_purity,"K/#pi - DBD","lp");
  leg1->AddEntry(eff_purity2,"K/#pi - 2020","lp");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();*/


  TCanvas* c_eff_purity2 = new TCanvas("c_eff_purity2","c_eff_purity2",800,800);
  // gStyle->SetPadLeftMargin(0.16);

  eff_purity->GetXaxis()->SetTitle("K id. Eficiency [%]");
  eff_purity->GetYaxis()->SetTitle("K id. Purity [%]");
  // eff_purity->GetYaxis()->SetTitleOffset(1.9);
  //  eff_purity->GetXaxis()->SetRangeUser(0.8,50);
  eff_purity->GetYaxis()->SetRangeUser(0.5,1);

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
  
  TLegend *leg1 = new TLegend(0.7,0.8,0.8,0.9);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(eff_purity,"K/#pi - DBD","lp");
  leg1->AddEntry(eff_purity2,"K/#pi - 2020","lp");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
  
   

}
