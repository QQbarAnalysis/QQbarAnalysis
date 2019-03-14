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

void purity() {
      
  TString pol="eL";
  TString folder="../output/";
  TFile *f = new TFile(folder+"bbbar_genkt_restorer_cuts6_250GeV_"+pol+"_btag1_0.9_btag2_0.2_nbins40.root");

  TH1F *h_p_value_BcBc_restorer = (TH1F*)f->Get("p_value_BcBc");
  TH1F *h_p_value_KcKc_restorer = (TH1F*)f->Get("p_value_KcKc");
  TH1F *h_p_value_BcKc_restorer = (TH1F*)f->Get("p_value_BcKc");
  TH1F *h_p_value_KcBc_restorer = (TH1F*)f->Get("p_value_KcBc");
  TH1F *h_p_value_BcKc_same1_restorer = (TH1F*)f->Get("p_value_BcKc_same1");
  TH1F *h_p_value_BcKc_same2_restorer = (TH1F*)f->Get("p_value_BcKc_same2");

  TFile *f2 = new TFile(folder+"bbbar_genkt_norestorer_cuts6_250GeV_"+pol+"_btag1_0.9_btag2_0.2_nbins40.root");

  TH1F *h_p_value_BcBc_novertex = (TH1F*)f2->Get("p_value_BcBc");
  TH1F *h_p_value_KcKc_novertex = (TH1F*)f2->Get("p_value_KcKc");
  TH1F *h_p_value_BcKc_novertex = (TH1F*)f2->Get("p_value_BcKc");
  TH1F *h_p_value_KcBc_novertex = (TH1F*)f2->Get("p_value_KcBc");
  TH1F *h_p_value_BcKc_same1_novertex = (TH1F*)f2->Get("p_value_BcKc_same1");
  TH1F *h_p_value_BcKc_same2_novertex = (TH1F*)f2->Get("p_value_BcKc_same2");

 
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);
  
  TCanvas * canvas = new TCanvas("canvas","canvas",2400,1200);
  canvas->Divide(3,2);
  
  canvas->cd(3);
  gPad->SetGridy();
  gPad->SetGridx();
  h_p_value_BcKc_same1_restorer->SetTitle("BcKc (highest btag jet)");
  h_p_value_BcKc_same1_restorer->GetYaxis()->SetTitle("purity");
  h_p_value_BcKc_same1_restorer->GetXaxis()->SetTitle("|cos(#theta)|");
  h_p_value_BcKc_same1_restorer->GetYaxis()->SetRangeUser(0.4,1.05);
  h_p_value_BcKc_same1_restorer->GetXaxis()->SetRangeUser(0,1);
  h_p_value_BcKc_same1_restorer->SetLineColor(4);
  h_p_value_BcKc_same1_restorer->Draw("l");
  h_p_value_BcKc_same1_novertex->SetLineColor(2);
  h_p_value_BcKc_same1_novertex->Draw("lsame");
  

  TLegend *leg = new TLegend(0.6,0.2,0.9,0.3);
  leg->AddEntry(h_p_value_BcKc_same1_novertex,"No vertex restoring","l");
  leg->AddEntry(h_p_value_BcKc_same1_restorer,"Vertex restoring","l");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  canvas->cd(4);
  gPad->SetGridy();
  gPad->SetGridx();
  h_p_value_BcKc_same2_restorer->SetTitle("BcKc (lowest btag jet)");
  h_p_value_BcKc_same2_restorer->GetYaxis()->SetTitle("purity");
  h_p_value_BcKc_same2_restorer->GetXaxis()->SetTitle("|cos(#theta)|");
  h_p_value_BcKc_same2_restorer->GetYaxis()->SetRangeUser(0.4,1.05);
  h_p_value_BcKc_same2_restorer->GetXaxis()->SetRangeUser(0,1);
  h_p_value_BcKc_same2_restorer->SetLineColor(4);
  h_p_value_BcKc_same2_restorer->Draw("l");
  h_p_value_BcKc_same2_novertex->SetLineColor(2);
  h_p_value_BcKc_same2_novertex->Draw("lsame");
  leg->Draw();
  
  canvas->cd(1);
  gPad->SetGridy();
  gPad->SetGridx();
  h_p_value_BcBc_restorer->SetTitle("BcBc");
  h_p_value_BcBc_restorer->GetYaxis()->SetTitle("purity");
  h_p_value_BcBc_restorer->GetXaxis()->SetTitle("|cos(#theta)|");
  h_p_value_BcBc_restorer->GetYaxis()->SetRangeUser(0.4,1.05);
  h_p_value_BcBc_restorer->GetXaxis()->SetRangeUser(0,1);
  h_p_value_BcBc_restorer->SetLineColor(4);
  h_p_value_BcBc_restorer->Draw("l");
  h_p_value_BcBc_novertex->SetLineColor(2);
  h_p_value_BcBc_novertex->Draw("lsame");
  leg->Draw();
  
  canvas->cd(2);
  gPad->SetGridy();
  gPad->SetGridx();
  h_p_value_KcKc_restorer->SetTitle("KcKc");
  h_p_value_KcKc_restorer->GetYaxis()->SetTitle("purity");
  h_p_value_KcKc_restorer->GetXaxis()->SetTitle("|cos(#theta)|");
  h_p_value_KcKc_restorer->GetYaxis()->SetRangeUser(0.4,1.05);
  h_p_value_KcKc_restorer->GetXaxis()->SetRangeUser(0,1);
  h_p_value_KcKc_restorer->SetLineColor(4);
  h_p_value_KcKc_restorer->Draw("l");
  h_p_value_KcKc_novertex->SetLineColor(2);
  h_p_value_KcKc_novertex->Draw("lsame");
  leg->Draw();

  canvas->cd(5);
  gPad->SetGridy();
  gPad->SetGridx();
  h_p_value_BcKc_restorer->SetTitle("BcKc");
  h_p_value_BcKc_restorer->GetYaxis()->SetTitle("purity");
  h_p_value_BcKc_restorer->GetXaxis()->SetTitle("|cos(#theta)|");
  h_p_value_BcKc_restorer->GetYaxis()->SetRangeUser(0.4,1.05);
  h_p_value_BcKc_restorer->GetXaxis()->SetRangeUser(0,1);
  h_p_value_BcKc_restorer->SetLineColor(4);
  h_p_value_BcKc_restorer->Draw("l");
  h_p_value_BcKc_novertex->SetLineColor(2);
  h_p_value_BcKc_novertex->Draw("lsame");
  leg->Draw();


  canvas->cd(6);
  gPad->SetGridy();
  gPad->SetGridx();
  h_p_value_KcBc_restorer->SetTitle("KcBc");
  h_p_value_KcBc_restorer->GetYaxis()->SetTitle("purity");
  h_p_value_KcBc_restorer->GetXaxis()->SetTitle("|cos(#theta)|");
  h_p_value_KcBc_restorer->GetYaxis()->SetRangeUser(0.4,1.05);
  h_p_value_KcBc_restorer->GetXaxis()->SetRangeUser(0,1);
  h_p_value_KcBc_restorer->SetLineColor(4);
  h_p_value_KcBc_restorer->Draw("l");
  h_p_value_KcBc_novertex->SetLineColor(2);
  h_p_value_KcBc_novertex->Draw("lsame");
  leg->Draw();

 
  
}

