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

  TString pol = "eL";
  
  TString filename = "../output/bbbar_genkt_restorer_cuts6_250GeV_"+pol+"_btag1_0.9_btag2_0.2_nbins40.root";
  TFile *f = new TFile(filename);
  TH1F *h_corrected = (TH1F*)f->Get("corrected");
  h_corrected->Sumw2();

  TH1F *h_reco = (TH1F*)f->Get("reco");
  h_reco->Sumw2();
  
  TH1F *h_parton = (TH1F*)f->Get("parton");
  TH1F *h_parton_recocuts = (TH1F*)f->Get("parton_recocuts");

  TH1F *h_cheatedcharge = (TH1F*)f->Get("cheatedcharge_BcBc");
  TH1F *h_cheatedcharge_KcKc = (TH1F*)f->Get("cheatedcharge_KcKc");
  TH1F *h_cheatedcharge_BcKc = (TH1F*)f->Get("cheatedcharge_BcKc");
  TH1F *h_cheatedcharge_KcBc = (TH1F*)f->Get("cheatedcharge_KcBc");
  TH1F *h_cheatedcharge_BcKc_same1 = (TH1F*)f->Get("cheatedcharge_BcKc_same1");
  TH1F *h_cheatedcharge_BcKc_same2 = (TH1F*)f->Get("cheatedcharge_BcKc_same2");
  h_cheatedcharge->Sumw2();
  h_cheatedcharge_KcKc->Sumw2();
  h_cheatedcharge_BcKc->Sumw2();
  h_cheatedcharge_BcKc_same1->Sumw2();
  h_cheatedcharge_BcKc_same2->Sumw2();

  h_cheatedcharge->Add(h_cheatedcharge_KcKc);
  h_cheatedcharge->Add(h_cheatedcharge_BcKc);
  h_cheatedcharge->Add(h_cheatedcharge_KcBc);
  h_cheatedcharge->Add(h_cheatedcharge_BcKc_same1);
  h_cheatedcharge->Add(h_cheatedcharge_BcKc_same2);


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
  
  float max=-1;
   for(int i=20; i<40; i++) {
     if(acceptance_parton->GetBinContent(i+1)>max)
       max=acceptance_parton->GetBinContent(i+1);
   }
  acceptance_parton->Scale(1./max);

  h_corrected->Divide(acceptance_parton);
  
  double integtral_parton= h_parton->Integral(5,35);//10,30);
  double integtral_cheatedcharge= h_corrected->Integral(5,35);//10,30);
  h_parton->Scale(integtral_cheatedcharge/integtral_parton);
  
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
  gStyle->SetTitleFontSize(0.03);
  gStyle->SetMarkerSize(0.3);

  TCanvas * canvas = new TCanvas ("canvas","canvas",1000,800);
  canvas->cd(1);
  acceptance_parton->SetTitle("Acceptance factor, max. normalized to 1");
  acceptance_parton->GetXaxis()->SetTitle("|cos#theta_{b}|");
  acceptance_parton->GetYaxis()->SetTitle("acceptance factor");
  acceptance_parton->GetYaxis()->SetTitleOffset(1.5);
  acceptance_parton->GetYaxis()->SetRangeUser(0.2,1.2);
  acceptance_parton->GetXaxis()->SetRangeUser(0,1);

  acceptance_parton->SetLineColor(1);
  acceptance_parton->SetLineWidth(2);
  acceptance_parton->SetMarkerStyle(1);

  acceptance_parton->Draw("p");
  QQBARLabel(0.2,0.2,"");

  
  TCanvas * canvas0 = new TCanvas ("canvas0","canvas0",1000,800);
  canvas0->cd(1);
  if(pol=="eL") h_parton->SetTitle("e_{L}^{-}e_{R}^{+}#rightarrow b#bar{b} @ 250GeV, 250 fb^{-1}");
  else h_parton->SetTitle("e_{R}^{-}e_{L}^{+}#rightarrow b#bar{b} @ 250GeV, 250 fb^{-1}");
  h_parton->GetXaxis()->SetTitle("cos(#theta)");
  h_parton->GetYaxis()->SetTitle("entries / 0.05 rad");
  h_parton->GetYaxis()->SetTitleOffset(2.05);
  h_parton->GetYaxis()->SetRangeUser(0,h_parton->GetMaximum()*1.1);

  h_parton->SetLineColor(kGreen+1);
  h_parton->SetFillColor(kGreen+1);
  h_parton->SetFillStyle(3003);
  h_parton->Draw("histo");
    
  //h_cheatedcharge->SetLineColor(4);
  //h_cheatedcharge->SetLineWidth(2);
  //h_cheatedcharge->SetMarkerColor(4);
  //h_cheatedcharge->SetMarkerStyle(1);
  //h_cheatedcharge->Draw("pesame");

  h_reco->SetLineColor(1);
  h_reco->SetLineStyle(2);
  h_reco->SetLineWidth(2);
  h_reco->SetMarkerColor(1);
  h_reco->SetMarkerStyle(1);
  h_reco->Draw("pesame");

  h_noncorrected->SetLineColor(2);
  h_noncorrected->SetLineWidth(1);
  h_noncorrected->SetMarkerColor(2);
  h_noncorrected->SetMarkerStyle(1);
  h_noncorrected->Draw("psame");
    
  QQBARLabel(0.8,0.2,"");


  TCanvas * canvas1 = new TCanvas ("canvas1","canvas1",1000,800);
  canvas1->cd(1);
  if(pol=="eL") h_parton->SetTitle("e_{L}^{+}e_{R}^{-}#rightarrow b#bar{b} @ 250GeV, 250 fb^{-1}");
  else h_parton->SetTitle("e_{R}^{+}e_{L}^{-}#rightarrow b#bar{b} @ 250GeV, 250 fb^{-1}");
  h_parton->GetXaxis()->SetTitle("cos#theta_{b}");
  h_parton->GetYaxis()->SetTitle("entries / 0.05");
  h_parton->GetYaxis()->SetTitleOffset(2.05);
  h_parton->GetXaxis()->SetRangeUser(-1,0.);
  h_parton->GetYaxis()->SetRangeUser(0,10000);

  // h_parton->SetLineColor(3);
  // h_parton->SetFillColor(3);
  // h_parton->SetFillStyle(3001);
  h_parton->Draw("histo");
    
  //h_cheatedcharge->SetLineColor(4);
  //h_cheatedcharge->SetLineWidth(2);
  //h_cheatedcharge->SetMarkerColor(4);
  //h_cheatedcharge->SetMarkerStyle(1);
  //h_cheatedcharge->Draw("pesame");


  h_reco->Draw("psame");

  h_noncorrected->SetLineColor(2);
  h_noncorrected->SetLineWidth(1);
  h_noncorrected->SetMarkerColor(2);
  h_noncorrected->SetMarkerStyle(1);
  h_noncorrected->Draw("pesame");
    
  QQBARLabel(0.8,0.2,"");

  TLegend *leg1 = new TLegend(0.2,0.65,0.55,0.8);
  leg1->AddEntry(h_parton,"parton level","f");
  leg1->AddEntry(h_reco,"signal","lep");
  leg1->AddEntry(h_noncorrected,"signal (+ charge correction)","lep");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();

  TCanvas * canvas2 = new TCanvas ("canvas2","canvas2",1000,800);
  canvas2->cd(1);
  if(pol=="eL") h_noncorrected->SetTitle("e_{L}^{+}e_{R}^{-}#rightarrow b#bar{b} @ 250GeV, 250 fb^{-1}");
  else h_noncorrected->SetTitle("e_{R}^{+}e_{L}^{-}#rightarrow b#bar{b} @ 250GeV, 250 fb^{-1}");
  h_noncorrected->GetXaxis()->SetTitle("cos#theta_{b}");
  h_noncorrected->GetYaxis()->SetTitle("entries / 0.05");
  h_noncorrected->GetYaxis()->SetTitleOffset(2.05);
  h_noncorrected->GetYaxis()->SetRangeUser(0,h_noncorrected->GetMaximum()*1.1);
    
  h_noncorrected->SetLineColor(2);
  h_noncorrected->SetLineWidth(3);
  h_noncorrected->SetMarkerColor(2);
  h_noncorrected->SetMarkerStyle(1);
  h_noncorrected->Draw("p");
  
  h_cheatedcharge->SetLineColor(4);
  h_cheatedcharge->SetLineWidth(3);
  h_cheatedcharge->SetMarkerColor(4);
  h_cheatedcharge->SetLineStyle(2);
  h_cheatedcharge->Draw("histosame");

  h_reco->Draw("pesame");
 
  QQBARLabel(0.8,0.2,"");

  TLegend *leg2 = new TLegend(0.2,0.65,0.55,0.8);
  leg2->AddEntry(h_reco,"signal","lep");
  leg2->AddEntry(h_noncorrected,"signal (+ charge correction)","lep");
  leg2->AddEntry(h_cheatedcharge,"signal (cheated charge)","l");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();

   
    

  
}

