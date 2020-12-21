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

void Labels(TString pol="eL"){

  QQBARLabel(0.86,0.953,"");
  if(pol=="eL")QQBARLabel2(0.3,0.965, "e_{L}^{-}e_{R}^{+}#rightarrow b#bar{b}(K_{#gamma}<35 GeV, #scale[0.7]{#int}L=250fb^{-1})",kGray+2);
  if(pol=="eR")QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+}#rightarrow b#bar{b}(K_{#gamma}<35 GeV, #scale[0.7]{#int}L=250fb^{-1})",kGray+2);

}

void purity_global() {

   
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);
  
      
  TString pol="eL";
  TString folder="../output_20200427/";

 
  //------------------------------------------------------------
  // DBD

  TFile *f3 = new TFile(folder+"bbbar_Kgamma35_genkt_restorer_cuts12_250GeV_eL_btag1_0.8_btag2_0.8_nbins40.root");

  TH1F *h_p_value_BcBc_DBD = (TH1F*)f3->Get("p_value_BcBc");
  TH1F *h_p_value_KcKc_DBD = (TH1F*)f3->Get("p_value_KcKc");
  TH1F *h_p_value_BcKc_DBD = (TH1F*)f3->Get("p_value_BcKc");
  TH1F *h_p_value_KcBc_DBD = (TH1F*)f3->Get("p_value_KcBc");
  TH1F *h_p_value_BcKc_same1_DBD = (TH1F*)f3->Get("p_value_BcKc_same1");
  TH1F *h_p_value_BcKc_same2_DBD = (TH1F*)f3->Get("p_value_BcKc_same2");

  TH1F *h_reco_BcBc_DBD = (TH1F*)f3->Get("reco_BcBc");
  TH1F *h_reco_KcKc_DBD = (TH1F*)f3->Get("reco_KcKc");
  TH1F *h_reco_BcKc_DBD = (TH1F*)f3->Get("reco_BcKc");
  TH1F *h_reco_KcBc_DBD = (TH1F*)f3->Get("reco_KcBc");
  TH1F *h_reco_BcKc_same1_DBD = (TH1F*)f3->Get("reco_BcKc_same1");
  TH1F *h_reco_BcKc_same2_DBD = (TH1F*)f3->Get("reco_BcKc_same2");

  double x[4], y[5], ex[5], ey[5];
  
  for(int i=0; i<4; i++) {
    x[i]=i;
    ex[i]=0.5;
    y[i]-0;
    ey[i]=0;
  }

  y[0]=h_p_value_BcBc_DBD->GetBinContent(5);
  ey[0]=h_p_value_BcBc_DBD->GetBinError(5)/2.;

  y[1]=h_p_value_KcKc_DBD->GetBinContent(5);
  ey[1]=h_p_value_KcKc_DBD->GetBinError(5)/2.;

  double a = h_p_value_BcKc_DBD->GetBinContent(5)*h_reco_BcKc_DBD->GetEntries() + h_p_value_KcBc_DBD->GetBinContent(5)*h_reco_KcBc_DBD->GetEntries();
  double b = h_reco_BcKc_DBD->GetEntries() + h_reco_KcBc_DBD->GetEntries();
  y[2]=a/b;
  a = h_p_value_BcKc_DBD->GetBinError(5)/2.*h_reco_BcKc_DBD->GetEntries() + h_p_value_KcBc_DBD->GetBinError(5)/2.*h_reco_KcBc_DBD->GetEntries();
  ey[2] = a/b;

  a = h_p_value_BcKc_same1_DBD->GetBinContent(5)*h_reco_BcKc_same1_DBD->GetEntries() + h_p_value_BcKc_same2_DBD->GetBinContent(5)*h_reco_BcKc_same2_DBD->GetEntries();
  b = h_reco_BcKc_same1_DBD->GetEntries() + h_reco_BcKc_same2_DBD->GetEntries();
  y[3]=a/b;
  a = h_p_value_BcKc_same1_DBD->GetBinError(5)/2.*h_reco_BcKc_same1_DBD->GetEntries() + h_p_value_BcKc_same2_DBD->GetBinError(5)/2.*h_reco_BcKc_same2_DBD->GetEntries();
  ey[3] = a/b;

  TGraphErrors *pvalue_DBD = new TGraphErrors(4,x,y,ex,ey);

  //---------------------------------------------------------------

  TCanvas * canvas2 = new TCanvas("canvas2","canvas2",1000,800);

  
  pvalue_DBD->SetTitle("");
  pvalue_DBD->GetYaxis()->SetTitle("purity");
  pvalue_DBD->GetXaxis()->SetTitle("category");
  pvalue_DBD->GetYaxis()->SetRangeUser(0.3,1.15);
  pvalue_DBD->GetXaxis()->SetRangeUser(-0.5,3.5);
  pvalue_DBD->GetXaxis()->SetNdivisions(5);
  pvalue_DBD->SetLineColor(kGray+2);
  pvalue_DBD->SetMarkerColor(kGray+2);
  pvalue_DBD->SetMarkerStyle(1);
  pvalue_DBD->SetLineWidth(2);
  pvalue_DBD->Draw("ape");



  QQBARLabel(0.2,0.2,"Work in progress",1);
  
  TLegend *leg2 = new TLegend(0.5,0.7,0.9,0.9);
  leg2->SetTextFont(42);
  leg2->AddEntry(pvalue_DBD,"DBD, 250 GeV","lep");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();

  canvas2->Update();
  //  canvas2->Print("../plots/purity.C");
}

