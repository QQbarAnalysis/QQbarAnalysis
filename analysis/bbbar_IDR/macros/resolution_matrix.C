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

void resolution_matrix() {

  bool norm=true;
 
  TFile *f = new TFile("../output/angular_bbbar_500GeV_eL_l5_valencia1.4_btag1_0.9_btag2_0.2.root");

  TH2F *h_jet_quark =(TH2F*)f->Get("h_cos_quark_jet_test2");
  TH2F *h2_jet_quark =(TH2F*)f->Get("h_cos_quark_jettracks_test2");
     
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.3);
  gStyle->SetTitleY(1.0);
  gStyle->SetMarkerSize(1.5);

  
  TCanvas * canvas2 = new TCanvas("canvas2","canvas2",1200,600);
  canvas2->Divide(2,1);
  canvas2->cd(1);
  h_jet_quark->SetTitle("jet direction");
  h_jet_quark->GetYaxis()->SetTitle("cos(#theta)_{jet}");
  h_jet_quark->GetXaxis()->SetTitle("cos(#theta)_{quark}");
  h_jet_quark->SetMarkerSize(1.2);
  h_jet_quark->Draw("colztext");

  canvas2->cd(2);
  h2_jet_quark->SetTitle("jet direction only from tracks");
  h2_jet_quark->GetXaxis()->SetTitle("cos(#theta)_{quark}");
  h2_jet_quark->GetYaxis()->SetTitle("cos(#theta)_{jet}");
  h2_jet_quark->SetMarkerSize(1.2);
  h2_jet_quark->Draw("colztext");


  
}

