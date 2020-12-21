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
void Labels(int i=0, TString pol="eL"){

  QQBARLabel(0.86,0.952,"");
  QQBARLabel2(0.25,0.96, "LO EW matrix element - Whizard 1.95",kGray+2);
  //QQBARLabel2(0.1,0.05, "250 GeV, 250fb^{-1}",kGray+2);

  //  if(pol=="eL")QQBARLabel2(0.1,0.05, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  // if(pol=="eR")QQBARLabel2(0.1,0.05, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
}



void Kgamma() {

  int cuts=0;
  TString Kgamma="35";
  TString pol="eL";
  TString sel="_";//"_tight_";
  TString folder=TString::Format("../output_20200427/IdentifyRR_cuts%i_",cuts);
  TString kt="genkt_restorer";//"_genkt";//"_tight_";

  TH1F *h_K_parton[2];
  TH1F *h_costhetaparton[2];

  TH1F *h_K_parton_b[2];
  TH1F *h_costhetaparton_b[2];
  
  for(int ipol=0; ipol<2; ipol++){
    float norm=13.15;
    if(ipol==1) norm=19.9;
    
    if(ipol==1) pol="eR";
    TString filename = folder+"bbbar_radret_genkt_R125_Kgamma"+Kgamma+"_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
    cout<<filename<<endl;
    TFile *f = new TFile(filename);
    h_K_parton[ipol] = (TH1F*)f->Get("h_gamma_K_parton");
    h_costhetaparton[ipol] = (TH1F*)f->Get("h_gamma_costhetaparton");

    h_K_parton_b[ipol] = (TH1F*)f->Get("h_gamma_K_parton_b");
    h_costhetaparton_b[ipol] = (TH1F*)f->Get("h_gamma_costhetaparton_b");

    h_K_parton[ipol]->Scale(250./norm);
    h_costhetaparton[ipol]->Scale(250./norm);

    h_K_parton_b[ipol]->Scale(250./norm);
    h_costhetaparton_b[ipol]->Scale(250./norm);
  }
  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.5);

  TCanvas * canvasK = new TCanvas("canvas_K","canvas_K",800,800);
  canvasK->cd(1);
  // gPad->SetLogy();
    
  h_K_parton[0]->GetYaxis()->SetTitle("Entries / GeV");
  h_K_parton[0]->GetYaxis()->SetTitleOffset(1.9);
  h_K_parton[0]->GetXaxis()->SetTitleOffset(1.5);
  h_K_parton[0]->GetXaxis()->SetTitle("E_{#gamma} [GeV]");
  h_K_parton[0]->GetXaxis()->SetRangeUser(0,130);
  h_K_parton[0]->SetLineColor(4);
  h_K_parton[0]->SetLineWidth(2);
  h_K_parton[0]->Draw("histo");

  h_K_parton[1]->SetLineColor(2);
  h_K_parton[1]->SetLineWidth(2);
  h_K_parton[1]->Draw("histosame");

  /* h_K_parton_b[0]->SetLineColor(4);
  h_K_parton_b[0]->SetLineWidth(2);
  h_K_parton_b[0]->SetLineStyle(2);
  h_K_parton_b[0]->Draw("histosame");

  h_K_parton_b[1]->SetLineColor(2);
  h_K_parton_b[1]->SetLineWidth(2);
  h_K_parton_b[1]->SetLineStyle(2);
  h_K_parton_b[1]->Draw("histosame");*/

  TLegend *leg1 = new TLegend(0.3,0.75,0.5,0.93);//(0.4,0.3,0.5,0.6);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->SetHeader("250 GeV, 250fb^{-1}");
  leg1->AddEntry(h_K_parton[0],"e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb","l");
  leg1->AddEntry(h_K_parton[1],"e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb","l");
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();

  Labels(cuts,pol);

  TCanvas * canvascostheta = new TCanvas("canvas_costheta","canvas_costheta",800,800);
  canvascostheta->cd(1);
  // gPad->SetLogy();
    
  h_costhetaparton[0]->GetYaxis()->SetTitle("Entries / 0.01");
  h_costhetaparton[0]->GetYaxis()->SetTitleOffset(1.9);
  h_costhetaparton[0]->GetXaxis()->SetTitleOffset(1.5);
  h_costhetaparton[0]->GetXaxis()->SetTitle("cos#theta_{#gamma}");
  h_costhetaparton[0]->GetXaxis()->SetRangeUser(-1,1);
  h_costhetaparton[0]->SetLineColor(4);
  h_costhetaparton[0]->SetLineWidth(2);
  h_costhetaparton[0]->Draw("histo");

  h_costhetaparton[1]->SetLineColor(2);
  h_costhetaparton[1]->SetLineWidth(2);
  h_costhetaparton[1]->Draw("histosame");

  // h_costhetaparton_b[0]->SetLineColor(4);
  // h_costhetaparton_b[0]->SetLineWidth(2);
  // h_costhetaparton_b[0]->SetLineStyle(2);
  // h_costhetaparton_b[0]->Draw("histosame");

  // h_costhetaparton_b[1]->SetLineColor(2);
  // h_costhetaparton_b[1]->SetLineWidth(2);
  // h_costhetaparton_b[1]->SetLineStyle(2);
  // h_costhetaparton_b[1]->Draw("histosame");

 
  leg1->Draw();

  Labels(cuts,pol);

  
}
