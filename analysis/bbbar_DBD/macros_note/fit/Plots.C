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
#include "fit.h"

void Labels(TString pol="eL"){

  QQBARLabel(0.86,0.952,"");

  if(pol=="eL")QQBARLabel2(0.3,0.965, "e_{L}^{-}e_{R}^{+} #rightarrow b#bar{b} (E_{#gamma}<35 GeV, #scale[0.7]{#int}L=250fb^{-1})",kGray+2);
  if(pol=="eR")QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow b#bar{b} (E_{#gamma}<35 GeV, #scale[0.7]{#int}L=250fb^{-1})",kGray+2);

}

void Plots() {

  pol="eL";

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);

  gStyle->SetTitleX(0.2); 
  gStyle->SetTitleY(0.9); 
  TGaxis::SetMaxDigits(3);

  TH1F * h_parton = get_parton(pol);
  TH1F * h_corrected = get_corrected(pol);
  TH1F * h_eff = get_parton_recocuts(pol);
  h_eff->Divide(h_parton);

  double max =0;
  for(int i=22; i<40; i++) if(h_eff->GetBinContent(i+1)>max) max = h_eff->GetBinContent(i+1);
  h_eff->Scale(1./max);


  TH1F *h_noncorrected = new TH1F("h_noncorrected","h_noncorrected",40,-1,1);
  for(int i=0; i<40+2; i++) {  
    h_noncorrected->SetBinContent(i,h_corrected->GetBinContent(i));
    if(i>10 && i<30) h_noncorrected->SetBinContent(i,h_corrected->GetBinContent(i)/h_eff->GetBinContent(i));
    h_noncorrected->SetBinError(i,h_corrected->GetBinError(i));

    h_noncorrected->SetBinContent(i,h_corrected->GetBinContent(i)/h_eff->GetBinContent(i));
    
  }

  //  h_corrected->Divide(h_eff);
    
  double integral_parton= h_parton->Integral(8,32);//40/2-40/3,40/2+40/3);//
  double integral_cheatedcharge= h_corrected->Integral(8,32);
  h_parton->Scale(integral_cheatedcharge/integral_parton);
  h_noncorrected->Scale(integral_cheatedcharge/h_noncorrected->Integral(8,32));

  TString lumi= "250fb-1,";
  float ilumi=1;
  
  TCanvas * canvasdead = new TCanvas ("canvasdead","canvasdead",1000,800);
  canvasdead->cd();
  if(pol=="eL") cout<<" ####### LEFT POLARIZATION " <<endl;
  else cout<<" ####### RIGHT POLARIZATION " <<endl;
  cout<<" ------------------------ "<<endl;
  cout<<lumi+" parton level distribution "<<endl;
  TF1 * fitresult1 = fit_histo(h_parton);
  cout<<"  "<<endl;

  cout<<lumi+" reco + acceptance correction  "<<endl; 
  TF1 * fitresult3 = fit_histo(h_corrected);

  cout<<lumi+" reco  "<<endl; 
  TF1 * fitresult2 = fit_histo(h_noncorrected);
  TCanvas * canvas0 = new TCanvas ("canvas0","canvas0",800,800);
  canvas0->cd(1);
  h_parton->GetXaxis()->SetTitle("cos#theta_{b}");
  h_parton->GetXaxis()->SetTitleOffset(1.1);
  /*h_parton->GetXaxis()->SetTitleFont(42);
  h_parton->GetXaxis()->SetTitleSize(0.05);
  h_parton->GetXaxis()->SetLabelSize(0.04);
  h_parton->GetXaxis()->SetLabelOffset(0.015);

  h_parton->GetYaxis()->SetTitle("Entries / 0.05");
  h_parton->GetYaxis()->SetTitleOffset(1.3);
  h_parton->GetYaxis()->SetTitleFont(42);
  h_parton->GetYaxis()->SetTitleSize(0.05);
  h_parton->GetYaxis()->SetLabelSize(0.05);
  h_parton->GetYaxis()->SetLabelOffset(0.015);*/
  h_parton->GetYaxis()->SetTitle("Entries / 0.05");
  h_parton->GetYaxis()->SetRangeUser(0,h_parton->GetMaximum()*1.1);

  h_parton->SetLineColor(kGreen+2);
  h_parton->SetLineWidth(2);
  h_parton->SetFillColor(kGreen+2);
  h_parton->SetFillStyle(3001);

  h_parton->Draw("histo");
    
  h_corrected->SetLineColor(4);
  h_corrected->SetLineWidth(2);
  h_corrected->SetMarkerColor(4);
  h_corrected->SetMarkerStyle(20);
  h_corrected->SetMarkerSize(1.2);
  h_corrected->Draw("pesame");

  h_noncorrected->SetLineColor(2);
  h_noncorrected->SetLineWidth(2);
  h_noncorrected->SetMarkerColor(2);
  h_noncorrected->SetMarkerStyle(1);  
  h_noncorrected->Draw("psame");
    
  fitresult3->SetLineColor(4);
  fitresult3->SetLineStyle(3);
  fitresult3->SetLineWidth(5);
  fitresult3->Draw("lsame");

  Labels(pol);
  
  TLegend *leg = new TLegend(0.2,0.75,0.6,0.9);
  leg->SetTextSize(0.03);
  leg->SetTextFont(42);
  leg->AddEntry(h_noncorrected,"#font[42]{signal  + charge corr.}","lep");
  leg->AddEntry(h_corrected,"#font[42]{signal + ch. corr. + accep. corr.}","lep");
  leg->AddEntry(fitresult3,"#font[42]{fit: S(1+cos^{2}#theta_{b}) + A cos^{2}#theta_{b}}","l");
  leg->AddEntry(h_parton,"#font[42]{LO EW matrix element - Whizard 1.95}","lf");
 
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

}
