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


void plot2models() {

  int nbins=20;
  TString pol = "eL";
  TString folder = "../output/";//output/kt_20190202";
  TString model = "l5_valencia1.4";
  
 // large model
  //---------------------------------
  TString filename = TString::Format("%s/bbbar_%s_cuts4_500GeV_%s_btag1_0.9_btag2_0.2_nbins%i.root",folder.Data(),model.Data(),pol.Data(),nbins);
  TFile *f = new TFile(filename);
  TH1F *h_corrected = (TH1F*)f->Get("corrected");
  h_corrected->Sumw2();

  TH1F *h_parton = (TH1F*)f->Get("parton");
  h_parton->Sumw2();

  TH1F *h_eff = (TH1F*)f->Get("parton_recocuts");
  h_eff->Sumw2();
  h_eff->Divide(h_parton);
  
  double max =0;
  for(int i=nbins/2; i<nbins-3; i++) if(h_eff->GetBinContent(i+1)>max) max = h_eff->GetBinContent(i+1);
  h_eff->Scale(1./max);
  
  for(int i=0; i<nbins+2; i++) {  
    
    double error = sqrt( pow((h_corrected->GetBinContent(i)/h_eff->GetBinContent(i))*
			     sqrt(pow(h_corrected->GetBinError(i)/h_corrected->GetBinContent(i),2)+0.25*pow(h_eff->GetBinError(i)/h_eff->GetBinContent(i),2)),2) + 0.25*0.25*pow(h_corrected->GetBinContent(i)/h_eff->GetBinContent(i)-h_corrected->GetBinContent(i),2));
    
    if(h_eff->GetBinContent(i)>0 ) {
      h_corrected->SetBinError(i,error);
      h_corrected->SetBinContent(i,h_corrected->GetBinContent(i)/(h_eff->GetBinContent(i)));
    } else {
      h_corrected->SetBinError(i,0);
      h_corrected->SetBinContent(i,0);
    }
    
  }
  double integtral_parton= h_parton->Integral(4,16);//nbins/2-nbins/3,nbins/2+nbins/3);//
  double integtral_truth= h_corrected->Integral(4,16);
  h_parton->Scale(integtral_truth/integtral_parton);
  
  // small model
  //---------------------------------
  model="s5_valencia1.4";
  filename = TString::Format("%s/bbbar_%s_cuts4_500GeV_%s_btag1_0.9_btag2_0.2_nbins%i.root",folder.Data(),model.Data(),pol.Data(),nbins);
  TFile *f2 = new TFile(filename);
  TH1F *h2_corrected = (TH1F*)f2->Get("corrected");
  h2_corrected->Sumw2();

  TH1F *h2_parton = (TH1F*)f2->Get("parton");
  h2_parton->Sumw2();

  TH1F *h2_eff = (TH1F*)f2->Get("parton_recocuts");
  h2_eff->Sumw2();
  h2_eff->Divide(h2_parton);

  max =0;
  for(int i=nbins/2; i<nbins; i++) if(h2_eff->GetBinContent(i+1)>max) max = h2_eff->GetBinContent(i+1);
  h2_eff->Scale(1./max);
  
  for(int i=0; i<nbins+2; i++) {  
    
    double error = sqrt( pow((h2_corrected->GetBinContent(i)/h2_eff->GetBinContent(i))*
			     sqrt(pow(h2_corrected->GetBinError(i)/h2_corrected->GetBinContent(i),2)+0.25*pow(h2_eff->GetBinError(i)/h2_eff->GetBinContent(i),2)),2) + 0.25*0.25*pow(h2_corrected->GetBinContent(i)/h2_eff->GetBinContent(i)-h2_corrected->GetBinContent(i),2));
    
    if(h2_eff->GetBinContent(i)>0 ) {
      h2_corrected->SetBinError(i,error);
      h2_corrected->SetBinContent(i,h2_corrected->GetBinContent(i)/(h2_eff->GetBinContent(i)));
    } else {
      h2_corrected->SetBinError(i,0);
      h2_corrected->SetBinContent(i,0);
    }
    
  }
  
  
  integtral_parton= h2_parton->Integral(4,16);//nbins/2-nbins/3,nbins/2+nbins/3);//
  integtral_truth= h2_corrected->Integral(4,16);
  h2_parton->Scale(integtral_truth/integtral_parton);


  //-----------------------------------------------------
  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);

  gStyle->SetTitleX(0.2); 
  gStyle->SetTitleY(0.9); 
  
  TCanvas * canvas0 = new TCanvas ("canvas0","canvas0",1000,800);
  canvas0->cd(1);
  h_parton->SetTitle("e_{L}^{+}e_{R}^{-}#rightarrow b#bar{b} @ 500GeV, 46 fb^{-1}");
  h_parton->GetXaxis()->SetTitle("cos(#theta_{b#bar{b}})");
  h_parton->GetXaxis()->SetTitleOffset(1.1);
  h_parton->GetXaxis()->SetTitleFont(42);
  h_parton->GetXaxis()->SetTitleSize(0.05);
  h_parton->GetXaxis()->SetLabelSize(0.05);
  h_parton->GetXaxis()->SetLabelOffset(0.015);

  h_parton->GetYaxis()->SetTitle("entries / 0.05 rad");
  h_parton->GetYaxis()->SetTitleOffset(1.4);
  h_parton->GetYaxis()->SetTitleFont(42);
  h_parton->GetYaxis()->SetTitleSize(0.05);
  h_parton->GetYaxis()->SetLabelSize(0.05);
  h_parton->GetYaxis()->SetLabelOffset(0.015);
  h_parton->GetYaxis()->SetRangeUser(0,h_parton->GetMaximum()*1.1);

  h_parton->SetLineColor(3);
  h_parton->SetLineWidth(3);
  h_parton->Draw("histo");
    
  h_corrected->SetLineColor(4);
  h_corrected->SetLineWidth(2);
  h_corrected->SetMarkerColor(4);
  h_corrected->SetMarkerStyle(21);
  h_corrected->Draw("pesame");

  h2_corrected->SetLineColor(2);
  h2_corrected->SetLineWidth(2);
  h2_corrected->SetLineStyle(2);
  h2_corrected->SetMarkerColor(2);
  h2_corrected->SetMarkerStyle(22);
  h2_corrected->Draw("pesame");
  
  QQBARLabel(0.5,0.2,"Work in progress",1);

  TLegend *leg = new TLegend(0.2,0.65,0.55,0.8);
  leg->SetTextFont(42);
  leg->AddEntry(h_parton,"parton level","l");
  leg->AddEntry(h_corrected,"IDR-L","lep");
  leg->AddEntry(h2_corrected,"IDR-S","lep");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  canvas0->Update();
  canvas0->Print("../plots/result2models.C");

}
