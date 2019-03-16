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
#include "../style/Style.C"
#include "../style/Labels.C"

void resolution() {

  bool norm=true;
 
  TFile *f = new TFile("../output/kt/angular_bbbar_genkt_restorer_250GeV_eL_btag1_0.9_btag2_0.2.root");

  TH1F *h_jet =(TH1F*)f->Get("h_cos_jet_test6");
  TH1F *h_quark =(TH1F*)f->Get("h_cos_q");
  TH1F *h_jet_tracks =(TH1F*)f->Get("h_cos_jet_track_test6");
  // h_jet->Divide(h_quark);
  cout<<h_jet->Integral()<<" "<<h_jet_tracks->Integral()<<" "<<h_jet->Integral()/h_jet_tracks->Integral()<<endl;
  TH2F *h_jet_quark =(TH2F*)f->Get("h_cos_quark_jet_test6");
  TH2F *h2_jet_quark =(TH2F*)f->Get("h_cos_quark_jettracks_test6");
  h_quark->Scale(h_jet_tracks->Integral()/h_quark->Integral());
  h_jet->Scale(h_jet_tracks->Integral()/h_jet->Integral());

  // TFile *f2 = new TFile("../output/kt/angular_bbbar_genkt_norestorer_250GeV_eL_btag1_0.9_btag2_0.2.root");
  // TH2F *h22_jet_quark =(TH2F*)f2->Get("h_cos_quark_jettracks_test6");
  // TH1F *h_jet_tracks2 =(TH1F*)f2->Get("h_cos_jet_track_test1");
  // //h_jet_tracks2->Scale(h_jet_tracks->GetEntries()/h_jet_tracks2->GetEntries());

  
  /*  for(int i=0; i<10; i++) {
    double int_j=0;
    for(int j=0; j<10;j++) int_j+=h_jet_quark->GetBinContent(i+1,j+1);
    for(int j=0; j<10;j++) h_jet_quark->SetBinContent(i+1,j+1,h_jet_quark->GetBinContent(i+1,j+1)/int_j);
    }*/

  /* for(int j=0; j<10; j++) {
    double int_i=0;
    for(int i=0; i<10;i++) int_i+=h_jet_quark->GetBinContent(i+1,j+1);
    for(int i=0; i<10;i++) h_jet_quark->SetBinContent(i+1,j+1,h_jet_quark->GetBinContent(i+1,j+1)/int_i);
    }*/

      
  SetIrlesStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.3);
  gStyle->SetTitleY(1.0);
  gStyle->SetMarkerSize(1.5);

  
  TCanvas * canvas = new TCanvas("canvas","canvas",1000,1000);
  canvas->cd(1);
  h_jet->SetTitle("All e^{+}e^{-}#rightarrow Z #rightarrow q#bar{q} events");
  h_jet->GetYaxis()->SetTitle("entries");
  h_jet->GetXaxis()->SetTitle("cos(#theta)_{j}");
  h_jet->SetLineColor(1);
  h_jet->Draw("histo");
  h_quark->SetLineColor(2);
  h_quark->Draw("histosame");
  h_jet_tracks->SetLineColor(4);
  h_jet_tracks->Draw("histosame");
  // h_jet_tracks2->SetLineColor(3);
  //h_jet_tracks2->Draw("histosame");
  TLegend * leg = new TLegend(0.3,0.5,0.6,0.8);
  leg->AddEntry(h_quark,"j=q/#bar{q}","l");
  leg->AddEntry(h_jet,"j=jet (from PFOs)","l");
  leg->AddEntry(h_jet_tracks,"j=jet (direction from secondary tracks)","l");
  //leg->AddEntry(h_jet_tracks2,"j=jet (direction from secondary tracks)","l");
  leg->Draw();

  // TCanvas * canvas2 = new TCanvas("canvas2","canvas2",600,600);
  // canvas2->cd(1);
  // // h_jet_quark->SetTitle("columns normalized to 1");
  // h_jet_quark->GetYaxis()->SetTitle("cos(#theta)_{jet}");
  // h_jet_quark->GetXaxis()->SetTitle("cos(#theta)_{quark}");
  // //h_jet_quark->GetZaxis()->SetRangeUser(0.001,1);
  // h_jet_quark->SetMarkerSize(1.2);
  // h_jet_quark->Draw("colztext");

  // //  h2_jet_quark->Divide(h22_jet_quark);
  // TCanvas * canvas3 = new TCanvas("canvas3","canvas3",1400,1400);
  // canvas3->cd(1);
  // h2_jet_quark->SetTitle("jet direction only from tracks");
  // h2_jet_quark->GetXaxis()->SetTitle("cos(#theta)_{quark}");
  // h2_jet_quark->GetYaxis()->SetTitle("cos(#theta)_{jet}");
  // //  h2_jet_quark->GetZaxis()->SetRangeUser(0.9,1.1);
  // h2_jet_quark->SetMarkerSize(1.2);
  // h2_jet_quark->Draw("colztext");


  
}

