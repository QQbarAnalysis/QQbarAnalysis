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


void purity() {

   
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);
  
  TString pol="eL";
  TString folder="../output_20200427/";
  TFile *f = new TFile(folder+"bbbar_Kgamma35_genkt_restorer_cuts12_250GeV_"+pol+"_btag1_0.8_btag2_0.8_nbins40.root");

  TH1F *h_p_value_BcBc_restorer = (TH1F*)f->Get("p_value_BcBc");
  TH1F *h_p_value_KcKc_restorer = (TH1F*)f->Get("p_value_KcKc");
  TH1F *h_p_value_BcKc_restorer = (TH1F*)f->Get("p_value_BcKc");
  TH1F *h_p_value_KcBc_restorer = (TH1F*)f->Get("p_value_KcBc");
  TH1F *h_p_value_BcKc_same1_restorer = (TH1F*)f->Get("p_value_BcKc_same1");
  TH1F *h_p_value_BcKc_same2_restorer = (TH1F*)f->Get("p_value_BcKc_same2");

 
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);
  
  
  TCanvas * canvas2 = new TCanvas("canvas2","canvas2",800,800);
  
  canvas2->cd(1);
  h_p_value_BcBc_restorer->SetTitle("");
  h_p_value_BcBc_restorer->GetYaxis()->SetTitle("P_{B}");
  h_p_value_BcBc_restorer->GetXaxis()->SetTitle("|cos#theta_{b}|");
  h_p_value_BcBc_restorer->GetYaxis()->SetRangeUser(0.4,0.9);
  h_p_value_BcBc_restorer->GetXaxis()->SetRangeUser(0,1);

  h_p_value_BcBc_restorer->SetMarkerColor(4);
  h_p_value_BcBc_restorer->SetMarkerStyle(21);
  h_p_value_BcBc_restorer->SetLineColor(4);
  h_p_value_BcBc_restorer->SetLineStyle(1);
  h_p_value_BcBc_restorer->SetLineWidth(1);
  h_p_value_BcBc_restorer->Draw("p");

  h_p_value_KcKc_restorer->SetMarkerColor(1);
  h_p_value_KcKc_restorer->SetMarkerStyle(25);
  h_p_value_KcKc_restorer->SetLineColor(1);
  h_p_value_KcKc_restorer->SetLineStyle(1);
  h_p_value_KcKc_restorer->SetLineWidth(1);
  h_p_value_KcKc_restorer->Draw("psame");

  h_p_value_BcKc_restorer->SetMarkerColor(2);
  h_p_value_BcKc_restorer->SetMarkerStyle(23);
  h_p_value_BcKc_restorer->SetLineColor(2);
  h_p_value_BcKc_restorer->SetLineStyle(1);
  h_p_value_BcKc_restorer->SetLineWidth(1);
  h_p_value_BcKc_restorer->Draw("lsame");

  h_p_value_BcKc_same1_restorer->SetMarkerColor(kGreen+1);
  h_p_value_BcKc_same1_restorer->SetMarkerStyle(22);
  h_p_value_BcKc_same1_restorer->SetLineColor(kGreen+1);
  h_p_value_BcKc_same1_restorer->SetLineStyle(1);
  h_p_value_BcKc_same1_restorer->SetLineWidth(1);
  h_p_value_BcKc_same1_restorer->Draw("lsame");
  
  
  TLegend *leg2 = new TLegend(0.2,0.35,0.75,0.6);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->AddEntry(h_p_value_BcBc_restorer,"Category 1","ple");
  leg2->AddEntry(h_p_value_KcKc_restorer,"Category 2","ple");
  leg2->AddEntry(h_p_value_BcKc_restorer,"Category 3","ple");
  leg2->AddEntry(h_p_value_BcKc_same1_restorer,"Category 4","ple");

  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();

  Labels(pol);
  
}

