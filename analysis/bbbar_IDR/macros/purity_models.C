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

void purity_models(bool DBD=false) {
      
  TString pol="eL";
  TString folder="../output/";

  //------------------------------------------------------------
  // l5
  
  TFile *f = new TFile(folder+"bbbar_l5_valencia2.0_cuts3_500GeV_eL_btag1_0.9_btag2_0.2_nbins20.root");

  TH1F *h_p_value_BcBc_l5 = (TH1F*)f->Get("p_value_BcBc");
  TH1F *h_p_value_KcKc_l5 = (TH1F*)f->Get("p_value_KcKc");
  TH1F *h_p_value_BcKc_l5 = (TH1F*)f->Get("p_value_BcKc");
  TH1F *h_p_value_KcBc_l5 = (TH1F*)f->Get("p_value_KcBc");
  TH1F *h_p_value_BcKc_same1_l5 = (TH1F*)f->Get("p_value_BcKc_same1");
  TH1F *h_p_value_BcKc_same2_l5 = (TH1F*)f->Get("p_value_BcKc_same2");

  TH1F *h_reco_BcBc_l5 = (TH1F*)f->Get("reco_BcBc");
  TH1F *h_reco_KcKc_l5 = (TH1F*)f->Get("reco_KcKc");
  TH1F *h_reco_BcKc_l5 = (TH1F*)f->Get("reco_BcKc");
  TH1F *h_reco_KcBc_l5 = (TH1F*)f->Get("reco_KcBc");
  TH1F *h_reco_BcKc_same1_l5 = (TH1F*)f->Get("reco_BcKc_same1");
  TH1F *h_reco_BcKc_same2_l5 = (TH1F*)f->Get("reco_BcKc_same2");

  double x[4], y[4], ex[4], ey[4];
  for(int i=0; i<4; i++) {
    x[i]=i;
    ex[i]=0.5;
    y[i]-0;
    ey[i]=0;
  }

  y[0]=h_p_value_BcBc_l5->GetBinContent(5);
  ey[0]=h_p_value_BcBc_l5->GetBinError(5);

  y[1]=h_p_value_KcKc_l5->GetBinContent(5);
  ey[1]=h_p_value_KcKc_l5->GetBinError(5)/3.;

  double a = h_p_value_BcKc_l5->GetBinContent(5)*h_reco_BcKc_l5->GetEntries() + h_p_value_KcBc_l5->GetBinContent(5)*h_reco_KcBc_l5->GetEntries();
  double b = h_reco_BcKc_l5->GetEntries() + h_reco_KcBc_l5->GetEntries();
  y[2]=a/b;
  a = 0.5*(h_p_value_BcKc_l5->GetBinError(5)*h_reco_BcKc_l5->GetEntries() + h_p_value_KcBc_l5->GetBinError(5)*h_reco_KcBc_l5->GetEntries());
  ey[2] = a/b;

  a = h_p_value_BcKc_same1_l5->GetBinContent(5)*h_reco_BcKc_same1_l5->GetEntries() + h_p_value_BcKc_same2_l5->GetBinContent(5)*h_reco_BcKc_same2_l5->GetEntries();
  b = h_reco_BcKc_same1_l5->GetEntries() + h_reco_BcKc_same2_l5->GetEntries();
  y[3]=a/b;
  a = 0.5*(h_p_value_BcKc_same1_l5->GetBinError(5)*h_reco_BcKc_same1_l5->GetEntries() + h_p_value_BcKc_same2_l5->GetBinError(5)*h_reco_BcKc_same2_l5->GetEntries());
  ey[3] = a/b;

  TGraphErrors *pvalue_l5 = new TGraphErrors(4,x,y,ex,ey);

   //------------------------------------------------------------
  // s5
  //folder="../assym/";
  TFile *f2 = new TFile(folder+"bbbar_s5_valencia2.0_cuts3_500GeV_eL_btag1_0.9_btag2_0.2_nbins20.root");

  TH1F *h_p_value_BcBc_s5 = (TH1F*)f2->Get("p_value_BcBc");
  TH1F *h_p_value_KcKc_s5 = (TH1F*)f2->Get("p_value_KcKc");
  TH1F *h_p_value_BcKc_s5 = (TH1F*)f2->Get("p_value_BcKc");
  TH1F *h_p_value_KcBc_s5 = (TH1F*)f2->Get("p_value_KcBc");
  TH1F *h_p_value_BcKc_same1_s5 = (TH1F*)f2->Get("p_value_BcKc_same1");
  TH1F *h_p_value_BcKc_same2_s5 = (TH1F*)f2->Get("p_value_BcKc_same2");

  TH1F *h_reco_BcBc_s5 = (TH1F*)f2->Get("reco_BcBc");
  TH1F *h_reco_KcKc_s5 = (TH1F*)f2->Get("reco_KcKc");
  TH1F *h_reco_BcKc_s5 = (TH1F*)f2->Get("reco_BcKc");
  TH1F *h_reco_KcBc_s5 = (TH1F*)f2->Get("reco_KcBc");
  TH1F *h_reco_BcKc_same1_s5 = (TH1F*)f2->Get("reco_BcKc_same1");
  TH1F *h_reco_BcKc_same2_s5 = (TH1F*)f2->Get("reco_BcKc_same2");

  for(int i=0; i<4; i++) {
    x[i]=i;
    ex[i]=0.5;
    y[i]-0;
    ey[i]=0;
  }

  y[0]=h_p_value_BcBc_s5->GetBinContent(5);
  ey[0]=h_p_value_BcBc_s5->GetBinError(5);

  y[1]=h_p_value_KcKc_s5->GetBinContent(5);
  ey[1]=h_p_value_KcKc_s5->GetBinError(5)/3.;

  a = h_p_value_BcKc_s5->GetBinContent(5)*h_reco_BcKc_s5->GetEntries() + h_p_value_KcBc_s5->GetBinContent(5)*h_reco_KcBc_s5->GetEntries();
  b = h_reco_BcKc_s5->GetEntries() + h_reco_KcBc_s5->GetEntries();
  y[2]=a/b;
  a = 0.5*(h_p_value_BcKc_s5->GetBinError(5)*h_reco_BcKc_s5->GetEntries() + h_p_value_KcBc_s5->GetBinError(5)*h_reco_KcBc_s5->GetEntries());
  ey[2] = a/b;

  a = h_p_value_BcKc_same1_s5->GetBinContent(5)*h_reco_BcKc_same1_s5->GetEntries() + h_p_value_BcKc_same2_s5->GetBinContent(5)*h_reco_BcKc_same2_s5->GetEntries();
  b = h_reco_BcKc_same1_s5->GetEntries() + h_reco_BcKc_same2_s5->GetEntries();
  y[3]=a/b;
  a = 0.5*(h_p_value_BcKc_same1_s5->GetBinError(5)*h_reco_BcKc_same1_s5->GetEntries() + h_p_value_BcKc_same2_s5->GetBinError(5)*h_reco_BcKc_same2_s5->GetEntries());
  ey[3] = a/b;

  TGraphErrors *pvalue_s5 = new TGraphErrors(4,x,y,ex,ey);

  //---------------------------------------------------------------


  //------------------------------------------------------------
  // DBD
  // if(DBD==true) {
  TFile *f3 = new TFile("../../bbbar_DBD/output/bbbar_genkt_restorer_cuts6_250GeV_eL_btag1_0.9_btag2_0.2_nbins40.root");

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

  a = h_p_value_BcKc_DBD->GetBinContent(5)*h_reco_BcKc_DBD->GetEntries() + h_p_value_KcBc_DBD->GetBinContent(5)*h_reco_KcBc_DBD->GetEntries();
  b = h_reco_BcKc_DBD->GetEntries() + h_reco_KcBc_DBD->GetEntries();
  y[2]=a/b;
  a = h_p_value_BcKc_DBD->GetBinError(5)/2.*h_reco_BcKc_DBD->GetEntries() + h_p_value_KcBc_DBD->GetBinError(5)/2.*h_reco_KcBc_DBD->GetEntries();
  ey[2] = a/b;

  a = h_p_value_BcKc_same1_DBD->GetBinContent(5)*h_reco_BcKc_same1_DBD->GetEntries() + h_p_value_BcKc_same2_DBD->GetBinContent(5)*h_reco_BcKc_same2_DBD->GetEntries();
  b = h_reco_BcKc_same1_DBD->GetEntries() + h_reco_BcKc_same2_DBD->GetEntries();
  y[3]=a/b;
  a = h_p_value_BcKc_same1_DBD->GetBinError(5)/2.*h_reco_BcKc_same1_DBD->GetEntries() + h_p_value_BcKc_same2_DBD->GetBinError(5)/2.*h_reco_BcKc_same2_DBD->GetEntries();
  ey[3] = a/b;

  TGraphErrors *pvalue_DBD = new TGraphErrors(4,x,y,ex,ey);
  // }
  //---------------------------------------------------------------
 
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);
  
  TCanvas * canvas2 = new TCanvas("canvas2","canvas2",1000,800);

  pvalue_l5->SetTitle("");
  pvalue_l5->GetYaxis()->SetTitle("purity");
  pvalue_l5->GetXaxis()->SetTitle("category");
  pvalue_l5->GetYaxis()->SetRangeUser(0.3,1.15);
  // pvalue_l5->GetXaxis()->SetRangeUser(-0.5,3.5);
  // pvalue_l5->GetXaxis()->SetNdivisions(5);
  
  TAxis *ax = pvalue_l5->GetHistogram()->GetXaxis();
  Double_t x1 = ax->GetBinLowEdge(1);
  Double_t x2 = ax->GetBinUpEdge(ax->GetNbins());
  pvalue_l5->GetHistogram()->GetXaxis()->Set(5,x1+0.5,x2+0.5);
  
  pvalue_l5->GetHistogram()->GetXaxis()->SetBinLabel(1, "Vtx+Vtx");
  pvalue_l5->GetHistogram()->GetXaxis()->SetBinLabel(2, "K+K");
  pvalue_l5->GetHistogram()->GetXaxis()->SetBinLabel(3, "Vtx+K (diff. jet)");
  pvalue_l5->GetHistogram()->GetXaxis()->SetBinLabel(4, "Vtx+K (same jet)");
  pvalue_l5->GetXaxis()->SetRangeUser(-0.2,3.2);


  pvalue_l5->SetLineColor(4);
  pvalue_l5->SetMarkerColor(4);
  pvalue_l5->SetMarkerStyle(21);
  pvalue_l5->SetLineWidth(2);
  pvalue_l5->Draw("ape");

   pvalue_s5->SetLineColor(2);
  pvalue_s5->SetMarkerColor(2);
  pvalue_s5->SetMarkerStyle(22);
  pvalue_s5->SetLineStyle(2);
  pvalue_s5->SetLineWidth(2);
  pvalue_s5->Draw("pe");

  if(DBD==true){ 
    pvalue_DBD->SetLineColor(kGray+2);
    pvalue_DBD->SetMarkerColor(kGray+2);
    pvalue_DBD->SetMarkerStyle(1);
    pvalue_DBD->SetLineWidth(2);
    pvalue_DBD->Draw("pe");
  }
    
  //QQBARLabel(0.2,0.2,"Work in progress",1);
  QQBARLabel(0.2,0.2,"",1);

  TLegend *leg2 = new TLegend(0.5,0.7,0.9,0.9);
  leg2->SetTextFont(42);
  if(DBD==true) leg2->AddEntry(pvalue_DBD,"DBD, 250 GeV","lep");
  leg2->AddEntry(pvalue_l5,"IDR-L, 500 GeV","lep");
  leg2->AddEntry(pvalue_s5,"IDR-S, 500 GeV","lep");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();

  canvas2->Update();
  canvas2->Print("../plots/purity_v2.C");
  canvas2->Print("../plots/purity_v2.eps");

}

