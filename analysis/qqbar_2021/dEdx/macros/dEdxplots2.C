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

  QQBARLabel(0.86,0.952,"");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);


  if(pol=="eL")QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow b#bar{b} (K_{#gamma}<35 GeV, #scale[0.7]{#int}L=250fb^{-1})",kGray+2);
  if(pol=="eR")QQBARLabel2(0.3,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q} (K_{#gamma}<35 GeV, q=udcsb, 250fb^{-1})",kGray+2);
  
}



void dEdxplots2() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(2);

  
  TString filename = "../output_250_b_bbbar_radret_genkt_R125_both.root";
  TFile *f = new TFile(filename);

  TH1F*  p_kaon = (TH1F*)f->Get("p_kaon");
  TH1F*  p_proton = (TH1F*)f->Get("p_proton");
  TH1F*  p_pion = (TH1F*)f->Get("p_pion");

  p_kaon -> Scale(250./15);
  p_proton -> Scale(250./15);
  p_pion-> Scale(250./15);
    
  
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  p_pion->GetXaxis()->SetTitle("p [GeV]");
  p_pion->GetYaxis()->SetTitle("entries / GeV");
  p_pion->GetYaxis()->SetTitleOffset(1.25);
  p_pion->GetXaxis()->SetTitleOffset(1.);
  p_pion->GetXaxis()->SetRangeUser(0,50);

  p_pion->SetLineColor(4);
  p_pion->SetLineWidth(3);
  p_pion->SetLineStyle(2);
  p_pion->Draw("histo");
  
  p_proton->SetLineColor(kGreen+1);
  p_proton->SetLineWidth(1);
  p_proton->SetLineStyle(1);
  p_proton->Draw("histosame");
  
  p_kaon->SetLineColor(2);
  p_kaon->SetLineWidth(3);
  p_kaon->SetLineStyle(1);
  p_kaon->Draw("histosame");
  
  Labels();
  
  TLegend *leg0 = new TLegend(0.6,0.8,0.8,0.9);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(p_pion,"#pi","lp");
  leg0->AddEntry(p_kaon,"K","lp");
  leg0->AddEntry(p_proton,"p","lp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  

   

}
