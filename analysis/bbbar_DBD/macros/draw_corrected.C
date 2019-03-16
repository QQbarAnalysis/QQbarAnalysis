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


void draw_corrected() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  gStyle->SetTitleX(0.25); 
  gStyle->SetTitleY(1); 

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(0);
  
    
  cout<<" ######################## "<<endl;
  cout<<"Left Handed polarization "<< endl;

  TString pol="eR";
 
  TFile *f = new TFile("../output/bbbar_genkt_restorer_cuts6_250GeV_"+pol+"_btag1_0.9_btag2_0.2_nbins40.root");

  TH1F *h_parton = (TH1F*)f->Get("parton");

  TH1F *h_reco_BcBc = (TH1F*)f->Get("reco_BcBc");
  TH1F *h_reco_KcKc = (TH1F*)f->Get("reco_KcKc");
  TH1F *h_reco_BcKc = (TH1F*)f->Get("reco_BcKc");
  TH1F *h_reco_KcBc = (TH1F*)f->Get("reco_KcBc");
  TH1F *h_reco_BcKc_same1 = (TH1F*)f->Get("reco_BcKc_same1");
  TH1F *h_reco_BcKc_same2 = (TH1F*)f->Get("reco_BcKc_same2");

  TH1F *h_truth_BcBc = (TH1F*)f->Get("truth_BcBc");
  TH1F *h_truth_KcKc = (TH1F*)f->Get("truth_KcKc");
  TH1F *h_truth_BcKc = (TH1F*)f->Get("truth_BcKc");
  TH1F *h_truth_KcBc = (TH1F*)f->Get("truth_KcBc");
  TH1F *h_truth_BcKc_same1 = (TH1F*)f->Get("truth_BcKc_same1");
  TH1F *h_truth_BcKc_same2 = (TH1F*)f->Get("truth_BcKc_same2");

  TH1F *h_corrected_BcBc = (TH1F*)f->Get("corrected_BcBc");
  TH1F *h_corrected_KcKc = (TH1F*)f->Get("corrected_KcKc");
  TH1F *h_corrected_BcKc = (TH1F*)f->Get("corrected_BcKc");
  TH1F *h_corrected_KcBc = (TH1F*)f->Get("corrected_KcBc");
  TH1F *h_corrected_BcKc_same1 = (TH1F*)f->Get("corrected_BcKc_same1");
  TH1F *h_corrected_BcKc_same2 = (TH1F*)f->Get("corrected_BcKc_same2");

  h_corrected_BcBc->Divide(h_parton);
  h_truth_BcBc->Divide(h_parton);

  h_corrected_KcKc->Divide(h_parton);
  h_truth_KcKc->Divide(h_parton);

  h_corrected_BcKc->Divide(h_parton);
  h_truth_BcKc->Divide(h_parton);
  
  h_corrected_KcBc->Divide(h_parton);
  h_truth_KcBc->Divide(h_parton);

  h_corrected_BcKc_same1->Divide(h_parton);
  h_truth_BcKc_same1->Divide(h_parton);
  
  h_corrected_BcKc_same2->Divide(h_parton);
  h_truth_BcKc_same2->Divide(h_parton);
 
  TCanvas * canvas = new TCanvas ("canvas","canvas",1000,800);
  canvas->Divide(3,2);
  canvas->cd(1);
  h_corrected_BcBc->GetXaxis()->SetTitle("cos(#theta)");
  h_corrected_BcBc->GetYaxis()->SetTitle("entries / 0.05 rad");
  h_corrected_BcBc->GetYaxis()->SetTitleOffset(1.6);
  h_corrected_BcBc->SetTitle("BcBc");
  h_corrected_BcBc->SetLineColor(2);
  h_corrected_BcBc->SetMarkerColor(2);
  h_corrected_BcBc->Draw("l");
  h_truth_BcBc->Draw("same");

  canvas->cd(2);
  h_corrected_KcKc->GetXaxis()->SetTitle("cos(#theta)");
  h_corrected_KcKc->GetYaxis()->SetTitle("entries / 0.05 rad");
  h_corrected_KcKc->GetYaxis()->SetTitleOffset(1.6);
  h_corrected_KcKc->SetTitle("KcKc");
  h_corrected_KcKc->SetLineColor(2);
  h_corrected_KcKc->SetMarkerColor(2);
  h_corrected_KcKc->Draw("l");
  h_truth_KcKc->Draw("same");

  canvas->cd(3);
  h_corrected_BcKc->GetXaxis()->SetTitle("cos(#theta)");
  h_corrected_BcKc->GetYaxis()->SetTitle("entries / 0.05 rad");
  h_corrected_BcKc->GetYaxis()->SetTitleOffset(1.6);
  h_corrected_BcKc->SetTitle("BcKc");
  h_corrected_BcKc->SetLineColor(2);
  h_corrected_BcKc->SetMarkerColor(2);
  h_corrected_BcKc->Draw("l");
  h_truth_BcKc->Draw("same");

  canvas->cd(4);
  h_corrected_KcBc->GetXaxis()->SetTitle("cos(#theta)");
  h_corrected_KcBc->GetYaxis()->SetTitle("entries / 0.05 rad");
  h_corrected_KcBc->GetYaxis()->SetTitleOffset(1.6);
  h_corrected_KcBc->SetTitle("KcBc");
  h_corrected_KcBc->SetLineColor(2);
  h_corrected_KcBc->SetMarkerColor(2);
  h_corrected_KcBc->Draw("l");
  h_truth_KcBc->Draw("same");

  canvas->cd(5);
  h_corrected_BcKc_same1->GetXaxis()->SetTitle("cos(#theta)");
  h_corrected_BcKc_same1->GetYaxis()->SetTitle("entries / 0.05 rad");
  h_corrected_BcKc_same1->GetYaxis()->SetTitleOffset(1.6);
  h_corrected_BcKc_same1->SetTitle("BcKc_same1");
  h_corrected_BcKc_same1->SetLineColor(2);
  h_corrected_BcKc_same1->SetMarkerColor(2);
  h_corrected_BcKc_same1->Draw("l");
  h_truth_BcKc_same1->Draw("same");


  canvas->cd(6);
  h_corrected_BcKc_same2->GetXaxis()->SetTitle("cos(#theta)");
  h_corrected_BcKc_same2->GetYaxis()->SetTitle("entries / 0.05 rad");
  h_corrected_BcKc_same2->GetYaxis()->SetTitleOffset(1.6);
  h_corrected_BcKc_same2->SetTitle("BcKc_same2");
  h_corrected_BcKc_same2->SetLineColor(2);
  h_corrected_BcKc_same2->SetMarkerColor(2);
  h_corrected_BcKc_same2->Draw("l");
  h_truth_BcKc_same2->Draw("same");
 


  
  
}

