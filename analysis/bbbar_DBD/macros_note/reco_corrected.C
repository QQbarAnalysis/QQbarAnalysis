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

void Labels(TString pol="eL"){

  QQBARLabel(0.86,0.953,"");
  if(pol=="eL")QQBARLabel2(0.3,0.965, "e_{L}^{-}e_{R}^{+}#rightarrow b#bar{b}(K_{#gamma}<35 GeV, #scale[0.7]{#int}L=250fb^{-1})",kGray+2);
  if(pol=="eR")QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+}#rightarrow b#bar{b}(K_{#gamma}<35 GeV, #scale[0.7]{#int}L=250fb^{-1})",kGray+2);

}

void reco_corrected() {

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleX(0.25);
  gStyle->SetTitleY(1);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(0);
  gStyle->SetLegendFont(42);
  TGaxis::SetMaxDigits(3);
      
  cout<<" ######################## "<<endl;
  cout<<"Left Handed polarization "<< endl;

  TString pol = "eL";
  
  TString filename = "../output_20200427/bbbar_Kgamma35_genkt_restorer_cuts12_250GeV_"+pol+"_btag1_0.8_btag2_0.8_nbins40.root";
  cout<<filename<<endl;
  
  TFile *f = new TFile(filename);
  TH1F *h_corrected = (TH1F*)f->Get("corrected");
  h_corrected->Sumw2();
  
  TH1F *h_reco = (TH1F*)f->Get("reco_BcBc");
  TH1F *h_reco_KcKc = (TH1F*)f->Get("reco_KcKc");
  TH1F *h_reco_BcKc = (TH1F*)f->Get("reco_BcKc");
  TH1F *h_reco_KcBc = (TH1F*)f->Get("reco_KcBc");
  TH1F *h_reco_BcKc_same1 = (TH1F*)f->Get("cheatedcharge_BcKc_same1");
  TH1F *h_reco_BcKc_same2 = (TH1F*)f->Get("reco_BcKc_same2");
  h_reco->Sumw2();
  h_reco_KcKc->Sumw2();
  h_reco_BcKc->Sumw2();
  h_reco_KcBc->Sumw2();
  h_reco_BcKc_same1->Sumw2();
  h_reco_BcKc_same2->Sumw2();
  h_reco->Add(h_reco_KcKc);
  h_reco->Add(h_reco_BcKc);
  h_reco->Add(h_reco_KcBc);
  h_reco->Add(h_reco_BcKc_same1);
  h_reco->Add(h_reco_BcKc_same2);
  
  
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
  h_cheatedcharge_KcBc->Sumw2();
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
    acceptance_parton->SetBinContent(i,100*h_parton_recocuts->GetBinContent(i)/h_parton->GetBinContent(i));
    acceptance_parton->SetBinError(i,100*h_parton_recocuts->GetBinError(i)/h_parton->GetBinContent(i));
  }
  
  /*  float max=-1;
   for(int i=20; i<40; i++) {
     if(acceptance_parton->GetBinContent(i+1)>max)
       max=acceptance_parton->GetBinContent(i+1);
   }
   acceptance_parton->Scale(1./max);*/

  //  h_corrected->Divide(acceptance_parton);
  
  double integtral_parton= h_cheatedcharge->Integral(0,20);//10,30);
  double integtral_corrected= h_corrected->Integral(0,20);//10,30);
  //  h_corrected->Scale(integtral_corrected/integtral_parton);
  
  TString lumi= "250fb-1,";
  

  TCanvas * canvas0 = new TCanvas ("canvas0","canvas0",800,800);
  canvas0->cd(1);
  h_cheatedcharge->GetXaxis()->SetTitle("cos #theta");
  h_cheatedcharge->GetYaxis()->SetTitle("Entries / 0.05 rad");
  
  h_cheatedcharge->SetLineColor(kBlack);
  //  h_cheatedcharge->SetFillColor();
  // h_cheatedcharge->SetFillStyle(3003);
  h_cheatedcharge->Draw("histoe");
    
  h_corrected->SetLineColor(4);
  h_corrected->SetLineWidth(2);
  h_corrected->SetMarkerColor(4);
  h_corrected->SetMarkerStyle(1);
  h_corrected->Draw("pesame");

  h_reco->SetLineColor(1);
  h_reco->SetLineStyle(2);
  h_reco->SetLineWidth(2);
  h_reco->SetMarkerColor(1);
  h_reco->SetMarkerStyle(1);
  h_reco->Draw("pesame");

  TLegend *leg1 = new TLegend(0.2,0.6,0.55,0.8);
  leg1->AddEntry(h_cheatedcharge,"Signal (truth charge)","f");
  leg1->AddEntry(h_reco,"Signal","lep");
  leg1->AddEntry(h_corrected,"Signal (corrected charge)","lep");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();

  Labels(pol);
}

