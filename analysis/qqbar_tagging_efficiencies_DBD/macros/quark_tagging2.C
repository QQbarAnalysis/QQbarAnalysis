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

void quark_tagging2() {

  TString filename = "cc_correlations_onlyctag_quark4_250GeV_eL_ctag1_0.9_ctag2_0.9_nbins20.root";
  cout<<filename<<endl;
  TFile *f = new TFile(filename);

  TGraphErrors *ctag_rho = (TGraphErrors*)f->Get("rho");
  TGraphErrors *ctag_eff = (TGraphErrors*)f->Get("effb");

  filename = "cc_correlations_quark4_250GeV_eL_ctag1_0.9_ctag2_0.9_nbins20.root";
  cout<<filename<<endl;
  TFile *f2 = new TFile(filename);
  TGraphErrors *ccharge_rho = (TGraphErrors*)f2->Get("rho");
  TGraphErrors *ccharge_eff = (TGraphErrors*)f2->Get("effb");
    
  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);
  //  gStyle->SetTitleOffset(1.3,"y");
  gStyle->SetTitleY(1);
  gStyle->SetTitleX(0.15);

  TCanvas * canvas_c = new TCanvas("canvas_c","canvas_c",800,800); 
  canvas_c->cd(1);
  //ctag_eff->SetTitle("c-quark tagging");
  ctag_eff->GetYaxis()->SetRangeUser(0.,50);
  ctag_eff->GetXaxis()->SetRangeUser(0,1.);
  ctag_eff->GetXaxis()->SetTitle("|cos#theta_{c}|");
  ctag_eff->GetYaxis()->SetTitle("#epsilon_{c} [%]");
  ctag_eff->GetYaxis()->SetTitleOffset(1.3);
  //  ctag_eff->GetYaxis()->SetTitleColor(2);

  ctag_eff->SetLineColor(2);
  ctag_eff->SetLineWidth(2);
  ctag_eff->Draw("ale");

  ccharge_eff->SetLineColor(4);
  ccharge_eff->SetLineStyle(2);
  ccharge_eff->SetLineWidth(4);
  ccharge_eff->Draw("le");
  
  QQBARLabel(0.2,0.2,"Preliminary");
  QQBARLabel2(0.2,0.96, "e^{-}e^{+} #rightarrow c#bar{c}, 250GeV",kGray+2);
  //"c-quark tagging",kGray+2);

  TLegend *leg0 = new TLegend(0.2,0.75,0.5,0.9);//(0.4,0.3,0.5,0.6);
  leg0->SetTextSize(0.035);
  leg0->SetHeader("Efficiency, #epsilon_{c}");
  leg0->AddEntry(ctag_eff,"#font[42]{c-quark tagging}","le");
  leg0->AddEntry(ccharge_eff,"#font[42]{c-quark tagging + charge measurment}","le");
  leg0->SetFillStyle(0);
  leg0->SetLineWidth(0);
  leg0->SetLineColor(0);
  //  leg0->SetShadowColor(0);
  leg0->SetBorderSize(0);
  leg0->Draw();

  TCanvas * canvas_b = new TCanvas("canvas_b","canvas_b",800,800);
  canvas_b->cd(1);

  //ctag_rho->SetTitle("c-quark tagging");
  ctag_rho->GetYaxis()->SetRangeUser(-3.,10);
  ctag_rho->GetXaxis()->SetRangeUser(0,1.);
  ctag_rho->GetXaxis()->SetTitle("|cos#theta_{c}|");
  ctag_rho->GetYaxis()->SetTitle("#rho [%]");
  ctag_rho->GetYaxis()->SetTitleOffset(1.3);
  //  ctag_rho->GetYaxis()->SetTitleColor(2);

  ctag_rho->SetLineColor(2);
  ctag_rho->SetLineWidth(2);
  ctag_rho->Draw("ale");

  ccharge_rho->SetLineColor(4);
  ccharge_rho->SetLineStyle(2);
  ccharge_rho->SetLineWidth(4);
  ccharge_rho->Draw("le");
  
  QQBARLabel(0.2,0.2,"Preliminary");
  QQBARLabel2(0.2,0.96, "e^{-}e^{+} #rightarrow c#bar{c}, 250GeV",kGray+2);
  //"c-quark tagging",kGray+2);

  TLegend *leg1 = new TLegend(0.2,0.75,0.5,0.9);//(0.4,0.3,0.5,0.6);
  leg1->SetTextSize(0.035);
  leg1->SetHeader("Correlation factor, #rho");
  leg1->AddEntry(ctag_rho,"#font[42]{c-quark tagging}","le");
  leg1->AddEntry(ccharge_rho,"#font[42]{c-quark tagging + charge measurment}","le");
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  //  leg1->SetShadowColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();

  canvas_c->Print("epsilon_cquark_eff.eps");
  canvas_b->Print("epsilon_cquark_rho.eps");

}
