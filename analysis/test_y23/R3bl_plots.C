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
#include "../style/Style.C"
#include "../style/Labels.C"


void R3bl_plots() {

  TString folder="./";

  TString filename = folder+"R3_cambridge_signal_eR.root";
  TFile *f = new TFile(filename);

  TGraphErrors *R3b_ps[4];
  TGraphErrors *R3l_ps[4];
  TGraphErrors *R3bl_ps[4];

  TGraphErrors *R3b_reco[4];
  TGraphErrors *R3l_reco[4];
  TGraphErrors *R3bl_reco[4];

  double yR3bl_ps[4], yR3bl_reco[4];
  double eyR3bl_ps[4], eyR3bl_reco[4];
  double x[4];

  for(int i=0; i<4; i++ ) {
    R3b_ps[i]=(TGraphErrors*)f->Get(TString::Format("R3b_PS_step%i",i));
    R3l_ps[i]=(TGraphErrors*)f->Get(TString::Format("R3l_PS_step%i",i));
    R3bl_ps[i]=(TGraphErrors*)f->Get(TString::Format("R3bl_PS_step%i",i));

    R3b_reco[i]=(TGraphErrors*)f->Get(TString::Format("R3b_reco_step%i",i));
    R3l_reco[i]=(TGraphErrors*)f->Get(TString::Format("R3l_reco_step%i",i));
    R3bl_reco[i]=(TGraphErrors*)f->Get(TString::Format("R3bl_reco_step%i",i));

    Double_t *y_ps = R3bl_ps[i]->GetY();
    Double_t *ey_ps = R3bl_ps[i]->GetEY();
    yR3bl_ps[i]=y_ps[10];
    eyR3bl_ps[i]=ey_ps[10];

    Double_t *y_reco = R3bl_reco[i]->GetY();
    Double_t *ey_reco = R3bl_reco[i]->GetEY();
    yR3bl_reco[i]=y_reco[10];
    eyR3bl_reco[i]=ey_reco[10];

    x[i]=i;
  }

  TGraphErrors *R3_ps_step = new TGraphErrors(4,yR3bl_ps,x,eyR3bl_ps,0);
  TGraphErrors *R3_reco_step = new TGraphErrors(4,yR3bl_reco,x,eyR3bl_reco,0);

					      
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.5);
  // TGaxis::SetMaxDigits(2); 


  TCanvas * canvas1 = new TCanvas("R3bl_ps","R3bl_ps",800,800);
  canvas1->cd(1);
  //  gPad->SetLogy();
  TLegend *leg1 = new TLegend(0.3,0.2,0.65,0.35);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  
  for(int i=0; i<4; i++ ) {
    
    if(i==0) {
      R3bl_ps[i]->GetYaxis()->SetTitle("R_{3}^{bl}");
      R3bl_ps[i]->GetYaxis()->SetRangeUser(0.7,1.4);
      R3bl_ps[i]->GetXaxis()->SetTitle("y_{cut}");
    }
    R3bl_ps[i]->SetLineColor(1+i);
    R3bl_ps[i]->SetLineWidth(1+i);
    R3bl_ps[i]->SetLineStyle(1+i);
  if(i==0) R3bl_ps[i]->Draw("ac");
  else R3bl_ps[i]->Draw("c");

  leg1->AddEntry(R3bl_ps[i],TString::Format("PS - Cambridge --> Selection Step %i",i),"l");

  }

  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  //  leg1->SetShadowColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();


  // ---------------------------------------

   TCanvas * canvas2 = new TCanvas("R3bl_reco","R3bl_reco",800,800);
  canvas2->cd(1);
  //  gPad->SetLogy();
  TLegend *leg2 = new TLegend(0.3,0.2,0.65,0.35);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  
  for(int i=0; i<4; i++ ) {
    
    if(i==0) {
      R3bl_reco[i]->GetYaxis()->SetTitle("R_{3}^{bl}");
      R3bl_reco[i]->GetYaxis()->SetRangeUser(0.7,1.4);
      R3bl_reco[i]->GetXaxis()->SetTitle("y_{cut}");
    }
    R3bl_reco[i]->SetLineColor(1+i);
    R3bl_reco[i]->SetLineWidth(1+i);
    R3bl_reco[i]->SetLineStyle(1+i);
  if(i==0) R3bl_reco[i]->Draw("ac");
  else R3bl_reco[i]->Draw("c");

  leg2->AddEntry(R3bl_reco[i],TString::Format("RECO - Cambridge --> Selection Step %i",i),"l");

  }

  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  //  leg2->SetShadowColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();


    // ---------------------------------------

  TCanvas * canvas3 = new TCanvas("R3bl_001","R3bl_001",800,800);
  canvas3->cd(1);
  //  gPad->SetLogy();
  TLegend *leg3 = new TLegend(0.2,0.7,0.55,0.85);
  leg3->SetTextSize(0.035);
  leg3->SetTextFont(42);
  
  
  R3_reco_step->GetYaxis()->SetTitle("Reconstruction step");
  R3_reco_step->GetXaxis()->SetRangeUser(0.5,1.4);
  R3_reco_step->GetYaxis()->SetRangeUser(-0.5,4);
  R3_reco_step->GetXaxis()->SetTitle("R_{3}^{bl}(ycut=0.01)");

  R3_reco_step->SetLineColor(1);
  R3_reco_step->SetLineWidth(2);
  R3_reco_step->SetLineStyle(1);
  R3_reco_step->SetMarkerStyle(21);
  R3_reco_step->Draw("aep");

  R3_ps_step->SetLineColor(2);
  R3_ps_step->SetLineWidth(2);
  R3_ps_step->SetLineStyle(1);
  R3_ps_step->SetMarkerStyle(22);
  R3_ps_step->SetMarkerColor(2);
  R3_ps_step->Draw("ep");
  
  leg3->AddEntry(R3_ps_step ,"Parton Shower","lep");
  leg3->AddEntry(R3_reco_step ,"Reco Objects","lep");

  

  leg3->SetFillStyle(0);
  leg3->SetLineWidth(0);
  leg3->SetLineColor(0);
  //  leg3->SetShadowColor(0);
  leg3->SetBorderSize(0);
  leg3->Draw();




  
}
