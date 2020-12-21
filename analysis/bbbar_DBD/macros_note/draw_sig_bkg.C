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
  if(pol=="eL")QQBARLabel2(0.3,0.965, "e_{L}^{-}e_{R}^{+}#rightarrow b#bar{b}(#scale[0.7]{#int}L=250fb^{-1})",kGray+2);
  if(pol=="eR")QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+}#rightarrow b#bar{b}( #scale[0.7]{#int}L=250fb^{-1})",kGray+2);

}

void draw_sig_bkg() {

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
  
  for(int j=12; j<13; j++) {

    
  TString pol="eR";
  TString cuts = TString::Format("cuts%i",j);
   
  TFile *f = new TFile("../output_20200427/bbbar_Kgamma35_genkt_restorer_"+cuts+"_250GeV_"+pol+"_btag1_0.8_btag2_0.8_nbins40.root");
  TH1F *h_parton = (TH1F*)f->Get("parton");
  TH1F *h_reco = (TH1F*)f->Get("reco");
  TH1F *h_bkg_qq = (TH1F*)f->Get("bkg_qq");
  TH1F *h_bkg_cc = (TH1F*)f->Get("bkg_cc");

  f = new TFile("../output_20200427/bbbar_Kgamma35_radret_genkt_R125_"+cuts+"_250GeV_"+pol+"_btag1_0.8_btag2_0.8_nbins40.root");
  TH1F *h_bkg_radreturn = (TH1F*)f->Get("bkg_radreturn");

  f = new TFile("../output_20200427/bkg_Kgamma35_ZZ_genkt_restorer_"+cuts+"_250GeV_"+pol+"_btag1_0.8_btag2_0.8_nbins40.root");
  TH1F *h_bkg_zz = (TH1F*)f->Get("reco");

  f = new TFile("../output_20200427/bkg_Kgamma35_WW_genkt_restorer_"+cuts+"_250GeV_"+pol+"_btag1_0.8_btag2_0.8_nbins40.root");
  TH1F *h_bkg_ww = (TH1F*)f->Get("reco");

  f = new TFile("../output_20200427/bkg_Kgamma35_HZ_genkt_restorer_"+cuts+"_250GeV_"+pol+"_btag1_0.8_btag2_0.8_nbins40.root");
  TH1F *h_bkg_hz = (TH1F*)f->Get("reco");
  
  if(pol=="eL") {
    h_parton->Scale(250./266.5);
    h_reco->Scale(250./266.5);
    h_bkg_qq->Scale(250./266.5);
    h_bkg_cc->Scale(250./266.5);
    h_bkg_radreturn->Scale(250./13.15);
    
    h_bkg_ww->Scale(250./72.2);
    h_bkg_hz->Scale(250./353.);
  }

  if(pol=="eR") {
    h_parton->Scale(250./276.9);
    h_reco->Scale(250./276.9);
    h_bkg_qq->Scale(250./276.9);
    h_bkg_cc->Scale(250./276.9);
    h_bkg_radreturn->Scale(250./19.9);
    
    h_bkg_hz->Scale(250./550.);
  }

  double reco=h_reco->Integral()/h_parton->Integral();
  double qq=h_bkg_qq->Integral()/h_reco->Integral();
  double cc=h_bkg_cc->Integral()/h_reco->Integral();
  double radreturn=h_bkg_radreturn->Integral()/h_reco->Integral();
  double zz=h_bkg_zz->Integral()/h_reco->Integral();
  double ww=h_bkg_ww->Integral()/h_reco->Integral();
  double hz=h_bkg_hz->Integral()/h_reco->Integral();


  cout<<j<<" "<<reco<<" "<<qq<<" "<<cc<<" "<<radreturn<<" "<<zz<<" "<<ww<<" "<<hz<<endl;
  h_reco->Add(h_bkg_qq);
  h_reco->Add(h_bkg_cc);
  h_reco->Add(h_bkg_radreturn);
  h_reco->Add(h_bkg_zz);
  h_reco->Add(h_bkg_ww);
  h_reco->Add(h_bkg_hz);

  
  TH1F *h_bkg_other = new TH1F("other","other",40,-1,1);
  //  h_bkg_other->Add(h_bkg_radreturn);
  h_bkg_other->Add(h_bkg_zz);
  h_bkg_other->Add(h_bkg_ww);
  h_bkg_other->Add(h_bkg_hz);
  h_bkg_other->Add(h_bkg_qq);
  h_bkg_other->Add(h_bkg_cc);

  THStack * hreco = new THStack("Reco","Reco");

  hreco->Add(h_bkg_other);
  hreco->Add(h_bkg_radreturn);
  // hreco->Add(h_bkg_cc);
  hreco->Add(h_reco);

 
  TCanvas * canvas = new TCanvas ("canvas","canvas",800,800);
  canvas->cd(1);

  h_reco->SetLineColor(1);
  h_reco->SetMarkerColor(1);
  
  /* h_bkg_hz->SetLineColor(3);
  h_bkg_hz->SetFillColor(3);
  h_bkg_hz->SetFillStyle(3005);
  
  h_bkg_ww->SetLineColor(kGray+2);
  h_bkg_ww->SetFillColor(kGray+2);
  h_bkg_ww->SetFillStyle(3006);
  
  h_bkg_zz->SetLineColor(2);
  h_bkg_zz->SetFillColor(2);
  h_bkg_zz->SetFillStyle(3001);

  h_bkg_radreturn->SetLineColor(4);
  h_bkg_radreturn->SetFillColor(4);
  h_bkg_radreturn->SetFillStyle(3004);*/

  h_bkg_other->SetLineColor(4);
  h_bkg_other->SetFillColor(4);
  h_bkg_other->SetFillStyle(3004);
    
  h_bkg_radreturn->SetLineColor(kGreen+1);
  h_bkg_radreturn->SetFillColor(kGreen+1);
  h_bkg_radreturn->SetFillStyle(1001);

  h_bkg_cc->SetLineColor(kGray);
  h_bkg_cc->SetFillColor(kGray);
  h_bkg_cc->SetFillStyle(1001);
  // h_reco->Draw("histo");

  hreco->Draw("histo");
  // bkg->GetYaxis()->SetRangeUser(0,10000);
  hreco->GetXaxis()->SetTitle("cos#theta_{b}");
  hreco->GetYaxis()->SetTitle("Entries / 0.05");
  // hreco->GetYaxis()->SetTitleOffset(1.6);
  hreco->GetYaxis()->SetRangeUser(0,h_reco->GetMaximum()*1.3);
  hreco->Draw("histo");
  //  h_reco->Draw("histosame");

  canvas->Update();
  canvas->Modified();

  cout<<h_reco->GetMaximum()*1.2<<endl;

  QQBARLabel(0.86,0.952,"");
  //  h_bkg_qq->
  TLegend *leg = new TLegend(0.18,0.83,0.6,0.93);
  leg->SetTextSize(0.03);
  leg->SetTextFont(42);
  leg->SetHeader("Selection Efficiency");
  leg->AddEntry(h_reco,TString::Format("e^{-}e^{+}#rightarrow b#bar{b} (K_{#gamma}<35 GeV) : %0.1f",reco*100)+"%","l");

  TLegend *leg2 = new TLegend(0.18,0.65,0.6,0.82);
  leg2->SetTextSize(0.025);
  leg2->SetTextFont(42);
  leg2->SetHeader("Background / Signal ");
  // leg2->AddEntry(h_bkg_cc,TString::Format("e^{-}e^{+}#rightarrow q#bar{q}(q=c,K_{#gamma}<35 GeV) : %0.1f",cc*100)+"%","f");
  leg2->AddEntry(h_bkg_radreturn,TString::Format("e^{-}e^{+}#rightarrow q#bar{q} (q=udsc, K_{#gamma}>35 GeV) : %0.1f",radreturn*100)+"%","f");
  leg2->AddEntry(h_bkg_other,TString::Format("Others: %0.2f",(qq+cc+hz+ww+zz)*100)+"%","f");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();
  
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();

  Labels(pol);
  
  //canvas->Print("reco_2tags_"+pol+".eps");
  
  
  }
}

