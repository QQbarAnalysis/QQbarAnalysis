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

void reco_corrected() {
      
  cout<<" ######################## "<<endl;
  cout<<"Left Handed polarization "<< endl;

  TString pol = "eR";
  
  TString filename = "../output/bbbar_genkt_restorer_cuts6_250GeV_"+pol+"_btag1_0.9_btag2_0.2_nbins40.root";
  TFile *f = new TFile(filename);
  TH1F *h_corrected = (TH1F*)f->Get("corrected");
  h_corrected->Sumw2();

  TH1F *h_reco = (TH1F*)f->Get("reco");
  h_reco->Sumw2();
  
  TH1F *h_parton = (TH1F*)f->Get("parton");
  TH1F *h_parton_recocuts = (TH1F*)f->Get("parton_recocuts");

  TH1F *h_truth = (TH1F*)f->Get("truth");

  h_truth->Sumw2();
  
  TH1F *h_noncorrected = new TH1F("h_noncorrected","h_noncorrected",40,-1,1);

  for(int i=0; i<40; i++) {  
    //    h_eff->SetBinError(i,sqrt(pow(h_eff->GetBinError(i),2)+pow(0.1*(1-h_eff->GetBinContent(i)),2)));
    h_noncorrected->SetBinContent(i,h_corrected->GetBinContent(i));
    h_noncorrected->SetBinError(i,h_corrected->GetBinError(i));
  }
 
  TH1F *acceptance_parton = new TH1F("acceptance","acceptance",40,-1,1);
  for(int i=1; i<41; i++) {
    acceptance_parton->SetBinContent(i,h_parton_recocuts->GetBinContent(i)/h_parton->GetBinContent(i));
    acceptance_parton->SetBinError(i,h_parton_recocuts->GetBinError(i)/h_parton->GetBinContent(i));
  }
  
  float min=9999;
  min=acceptance_parton->GetBinContent(30);
  acceptance_parton->Scale(1./min);
      
  double integtral_parton= h_parton->Integral(5,20);//10,30);
  double integtral_truth= h_parton_recocuts->Integral(5,20);//10,30);
  h_parton->Scale(integtral_truth/integtral_parton);
  
  TString lumi= "250fb-1,";

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  gStyle->SetTitleX(0.2); 
  gStyle->SetTitleY(0.9); 
  gStyle->SetLegendFont(42);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(0.3);

  TCanvas * canvas = new TCanvas ("canvas","canvas",1000,800);
  canvas->cd(1);
  if(pol=="eL") acceptance_parton->SetTitle("Acceptance factor, normalized to 1");
  else acceptance_parton->SetTitle("Acceptance factor, normalized to 1");
  acceptance_parton->GetXaxis()->SetTitle("|cos(#theta)|");
  acceptance_parton->GetYaxis()->SetTitle("acceptance factor");
  acceptance_parton->GetYaxis()->SetTitleOffset(2.05);
  acceptance_parton->GetYaxis()->SetRangeUser(0.56,1.12);
  acceptance_parton->GetXaxis()->SetRangeUser(0,1);

  acceptance_parton->SetLineColor(1);
  acceptance_parton->Draw("p");
  
  
  TCanvas * canvas0 = new TCanvas ("canvas0","canvas0",1000,800);
  canvas0->cd(1);
  if(pol=="eL") h_parton->SetTitle("e_{L}^{+}e_{R}^{-}#rightarrow b#bar{b} @ 250GeV, 250 fb^{-1}");
  else h_parton->SetTitle("e_{R}^{+}e_{L}^{-}#rightarrow b#bar{b} @ 250GeV, 250 fb^{-1}");
  h_parton->GetXaxis()->SetTitle("cos(#theta)");
  h_parton->GetYaxis()->SetTitle("entries / 0.05 rad");
  h_parton->GetYaxis()->SetTitleOffset(2.05);
  h_parton->GetYaxis()->SetRangeUser(0,h_parton->GetMaximum()*1.1);

  h_parton->SetLineColor(3);
  h_parton->SetFillColor(3);
  h_parton->SetFillStyle(3001);
  h_parton->Draw("histo");
    
  //h_truth->SetLineColor(4);
  //h_truth->SetLineWidth(2);
  //h_truth->SetMarkerColor(4);
  //h_truth->SetMarkerStyle(1);
  //h_truth->Draw("pesame");

  h_reco->SetLineColor(1);
  h_reco->SetLineWidth(2);
  h_reco->SetMarkerColor(1);
  h_reco->SetMarkerStyle(1);
  h_reco->Draw("pesame");

  h_noncorrected->SetLineColor(2);
  h_noncorrected->SetLineWidth(1);
  h_noncorrected->SetMarkerColor(2);
  h_noncorrected->SetMarkerStyle(1);
  h_noncorrected->Draw("psame");
    
  QQBARLabel(0.6,0.2,"Work in progress");


  TCanvas * canvas1 = new TCanvas ("canvas1","canvas1",1000,800);
  canvas1->cd(1);
  if(pol=="eL") h_parton->SetTitle("e_{L}^{+}e_{R}^{-}#rightarrow b#bar{b} @ 250GeV, 250 fb^{-1}");
  else h_parton->SetTitle("e_{R}^{+}e_{L}^{-}#rightarrow b#bar{b} @ 250GeV, 250 fb^{-1}");
  h_parton->GetXaxis()->SetTitle("cos(#theta)");
  h_parton->GetYaxis()->SetTitle("entries / 0.05 rad");
  h_parton->GetYaxis()->SetTitleOffset(2.05);
  h_parton->GetYaxis()->SetRangeUser(0,h_parton->GetMaximum()*1.1);

  h_parton->SetLineColor(3);
  h_parton->SetFillColor(3);
  h_parton->SetFillStyle(3001);
  h_parton->Draw("histo");
    
  //h_truth->SetLineColor(4);
  //h_truth->SetLineWidth(2);
  //h_truth->SetMarkerColor(4);
  //h_truth->SetMarkerStyle(1);
  //h_truth->Draw("pesame");

  h_parton_recocuts->SetLineColor(1);
  h_parton_recocuts->SetLineWidth(2);
  h_parton_recocuts->SetMarkerColor(1);
  h_parton_recocuts->SetMarkerStyle(1);
  h_parton_recocuts->Draw("histossame");

  h_noncorrected->SetLineColor(2);
  h_noncorrected->SetLineWidth(1);
  h_noncorrected->SetMarkerColor(2);
  h_noncorrected->SetMarkerStyle(1);
  h_noncorrected->Draw("psame");
    
  QQBARLabel(0.6,0.2,"Work in progress");

  TLegend *leg1 = new TLegend(0.2,0.65,0.55,0.8);
  leg1->AddEntry(h_parton,"parton level","f");
  leg1->AddEntry(h_parton_recocuts,"parton level (reco cuts)","l");
  leg1->AddEntry(h_noncorrected,"signal (+ charge correction)","lep");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();

  TCanvas * canvas2 = new TCanvas ("canvas2","canvas2",1000,800);
  canvas2->cd(1);
  if(pol=="eL") h_truth->SetTitle("e_{L}^{+}e_{R}^{-}#rightarrow b#bar{b} @ 250GeV, 250 fb^{-1}");
  else h_truth->SetTitle("e_{R}^{+}e_{L}^{-}#rightarrow b#bar{b} @ 250GeV, 250 fb^{-1}");
  h_truth->GetXaxis()->SetTitle("cos(#theta)");
  h_truth->GetYaxis()->SetTitle("entries / 0.05 rad");
  h_truth->GetYaxis()->SetTitleOffset(2.05);
  h_truth->GetYaxis()->SetRangeUser(0,h_truth->GetMaximum()*1.1);
   
  h_truth->SetLineColor(4);
  h_truth->SetLineWidth(1);
  h_truth->SetMarkerColor(4);
  h_truth->SetMarkerStyle(1);
  h_truth->Draw("histo");

  h_reco->SetLineColor(1);
  h_reco->SetLineWidth(2);
  h_reco->SetMarkerColor(1);
  h_reco->SetMarkerStyle(1);
  h_reco->Draw("pesame");
  
  h_noncorrected->SetLineColor(2);
  h_noncorrected->SetLineWidth(1);
  h_noncorrected->SetMarkerColor(2);
  h_noncorrected->SetMarkerStyle(1);
  h_noncorrected->Draw("psame");
    
  QQBARLabel(0.6,0.2,"Work in progress");

  TLegend *leg2 = new TLegend(0.2,0.65,0.55,0.8);
  leg2->AddEntry(h_reco,"signal (raw)","lep");
  leg2->AddEntry(h_noncorrected,"signal (+ charge correction)","lep");
  leg2->AddEntry(h_truth,"signal (cheated charge)","lep");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();

   
    

  
}

