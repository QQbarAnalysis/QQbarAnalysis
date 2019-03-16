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
#include "../../style/Style.C"
#include "../../style/Labels.C"

int nbins=20;
TString pol = "eL";
TString folder = "../output/";//output/kt_20190202";

void acceptance_factor_plot(bool DBD=false) {

  //----------------------------------
  // --- large model
 
  TString filename = TString::Format("%s/bbbar_l5_valencia1.4_cuts4_500GeV_%s_btag1_0.9_btag2_0.2_nbins%i.root",folder.Data(),pol.Data(),nbins);
  TFile *f = new TFile(filename);
  TH1F *h_parton = (TH1F*)f->Get("parton");
  h_parton->Sumw2();

  TH1F *h_eff = (TH1F*)f->Get("parton_recocuts");
  h_eff->Sumw2();

  h_eff->Divide(h_parton);
  double max =0;
  for(int i=nbins/2; i<nbins; i++) if(h_eff->GetBinContent(i+1)>max) max = h_eff->GetBinContent(i+1);

  //----------------------------------
  // --- small model
  
  filename = TString::Format("%s/bbbar_s5_valencia1.4_cuts4_500GeV_%s_btag1_0.9_btag2_0.2_nbins%i.root",folder.Data(),pol.Data(),nbins);

  f = new TFile(filename);
  TH1F *h_parton2 = (TH1F*)f->Get("parton");
  h_parton2->Sumw2();

  TH1F *h_eff2 = (TH1F*)f->Get("parton_recocuts");
  h_eff2->Sumw2();

  h_eff2->Divide(h_parton2);
  max =0;
  for(int i=nbins/2; i<nbins; i++) if(h_eff2->GetBinContent(i+1)>max) max = h_eff2->GetBinContent(i+1);
    
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleX(0.2); 
  gStyle->SetTitleY(0.9); 
  gStyle->SetLegendFont(42);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.0);
  
  TCanvas * canvas = new TCanvas ("canvas","canvas",1000,800);
  canvas->cd(1);
  h_eff->GetXaxis()->SetTitle("|cos(#theta_{b#bar{b}})|");
  h_eff->GetXaxis()->SetRangeUser(0,1);
  h_eff->GetYaxis()->SetTitle("N_{reco cuts}^{parton level} / N^{parton level}");
  h_eff->GetYaxis()->SetRangeUser(0,0.35);

  h_eff->GetXaxis()->SetTitleOffset(1.1);
  h_eff->GetXaxis()->SetTitleFont(42);
  h_eff->GetXaxis()->SetTitleSize(0.05);
  h_eff->GetXaxis()->SetLabelSize(0.05);
  h_eff->GetXaxis()->SetLabelOffset(0.015);

  h_eff->GetYaxis()->SetTitleOffset(1.4);
  h_eff->GetYaxis()->SetTitleFont(42);
  h_eff->GetYaxis()->SetTitleSize(0.05);
  h_eff->GetYaxis()->SetLabelSize(0.05);
  h_eff->GetYaxis()->SetLabelOffset(0.015);
  
  h_eff->Draw("p");
  h_eff->SetLineStyle(1);
  h_eff->SetMarkerStyle(21);
  h_eff->SetMarkerColor(4);
  h_eff->SetLineColor(4);
  h_eff->SetLineWidth(2);

  h_eff2->SetLineStyle(2);
  h_eff2->SetMarkerStyle(22);
  h_eff2->SetMarkerColor(2);
  h_eff2->SetLineColor(2);
  h_eff2->SetLineWidth(2);
  h_eff2->Draw("psame");


  QQBARLabel(0.2,0.2,"Work in progress",1);
  
  TLegend *leg = new TLegend(0.2,0.65,0.65,0.8);
  leg->SetTextFont(42);
  leg->AddEntry(h_eff,"IDR-L, 500 GeV","lep");
  leg->AddEntry(h_eff2,"IDR-S, 500 GeV","lep");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);


  //----------------------------------
  // --- DBD
  if(DBD==true) {
    filename ="/home/irles/ownCloudCNRS/HeavyFlavours/macros/assym_tracks/bbbar_genkt_restorer_cuts6_250GeV_eL_btag1_0.9_btag2_0.2_nbins40.root";
    nbins=40;
    f = new TFile(filename);
    TH1F *h_parton3 = (TH1F*)f->Get("parton");
    h_parton3->Sumw2();
    
    TH1F *h_eff3 = (TH1F*)f->Get("parton_recocuts");
    h_eff3->Sumw2();
    
    h_eff3->Divide(h_parton3);
    max =0;
    for(int i=nbins/2; i<nbins; i++) if(h_eff3->GetBinContent(i+1)>max) max = h_eff3->GetBinContent(i+1);
    
    h_eff3->SetLineColor(kGray+2);
    h_eff3->SetLineWidth(2);
    h_eff3->SetMarkerStyle(1);
    h_eff3->Draw("psame");
    leg->AddEntry(h_eff3,"DBD, 250 GeV","le");

  }

  leg->Draw();


  canvas->Update();
  if(DBD==false) canvas->Print("../plots/acceptance_2models.C");
  else  canvas->Print("../plots/acceptance_2models_DBD.C");
  
}
