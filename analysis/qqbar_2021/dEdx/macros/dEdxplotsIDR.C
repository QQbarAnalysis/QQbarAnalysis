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
#include "../../../style/Style.C"
#include "../../../style/Labels.C"


void Labels(){

  QQBARLabel(0.86,0.952,"");
  //  QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow q#bar{q} (q=udcsb, K_{#gamma}<35 GeV)",kGray+2);

  /* if(i==0) QQBARLabel2(0.04,0.07, "[No Cuts]",kOrange+3);
  if(i==1) QQBARLabel2(0.04,0.07, "Photon veto",kOrange+3);
  if(i==2) QQBARLabel2(0.04,0.07, "Photon veto & K_{reco}<35 GeV",kOrange+3);
  if(i==3) {
    QQBARLabel2(0.04,0.082, "Photon veto & K_{reco}<35 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& m_{j_{1},j_{2}}>130 GeV",kOrange+3);
  }
  if(i==4) {
    QQBARLabel2(0.04,0.082, "Photon veto & K_{reco}<35 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& m_{j_{1},j_{2}}>130 GeV & y23<0.015",kOrange+3);
  }
  if(i==5) {
    QQBARLabel2(0.04,0.082, "Photon veto & K_{reco}<35 GeV & m_{j_{1},j_{2}}>130 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& y23<0.015 & (m_{j1}+m_{j2})<100 GeV",kOrange+3);
  }
   

  if(pol=="eL")QQBARLabel2(0.3,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  if(pol=="eR")QQBARLabel2(0.3,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  */
}



void dEdxplotsIDR() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  gStyle->SetPadLeftMargin(0.2);

 
  TString filename = "../l5.root";
  //../output_250_all_250GeV_DBD_eL_norestorer.root";
//output_250_all_250GeV_mc2020-15162_eL_lcfi_VVB1.17_norestorer.root";
//output_250_all_250GeV_DBD_eL_norestorer.root";
  //output_250_all_250GeV_mc2020-15162_eL_lcfi_VVB1.17_norestorer.root";//output_250_all_250GeV_mc2020-15161_eL_lcfi_VVB1.17_norestorer.root";//output_250_all_250GeV_DBD_eL_norestorer.root";
  TFile *f = new TFile(filename);

  
  TGraphErrors* proton_proj = (TGraphErrors*) f->Get("mean_proton");
  TGraphErrors* pion_proj = (TGraphErrors*) f->Get("mean_pion");
  TGraphErrors* kaon_proj = (TGraphErrors*) f->Get("mean_kaon");

  TGraphErrors* proton_proj2 = (TGraphErrors*) f->Get("RMSnorm_proton");
  TGraphErrors* pion_proj2 = (TGraphErrors*) f->Get("RMSnorm_pion");
  TGraphErrors* kaon_proj2 = (TGraphErrors*) f->Get("RMSnorm_kaon");

  double x[200], y1[200], y2[200], ex[200], ey1[200], ey2[200];
  int n=0;

  Double_t *xpi=pion_proj->GetX();
  Double_t *ypi=pion_proj->GetY();
  Double_t *expi=proton_proj->GetEX();
  Double_t *ypr=proton_proj->GetY();
  Double_t *yk=kaon_proj->GetY();
  Double_t *sypi=pion_proj->GetEY();
  Double_t *sypr=proton_proj->GetEY();
  Double_t *syk=kaon_proj->GetEY();

  Double_t *eyk=kaon_proj->GetEY();

  
  for(int i=0; i<pion_proj->GetN(); i++) {

    x[i]=xpi[i];
    ex[i]=expi[i]/2.;
    y1[i]=fabs(ypi[i]-yk[i])/sqrt(0.5*(pow(sypi[i],2)+pow(syk[i],2)));
    y2[i]=fabs(ypr[i]-yk[i])/sqrt(0.5*(pow(sypr[i],2)+pow(syk[i],2)));
    ey1[i]=sqrt(pow(syk[i],2))/sqrt(pow(sypi[i],2)+pow(syk[i],2));
    ey2[i]=sqrt(pow(syk[i],2))/sqrt(pow(sypi[i],2)+pow(syk[i],2));
    n++;
  }
  
  TGraphErrors* sep_pion = new TGraphErrors(n,x,y1,ex,ey1);
  TGraphErrors* sep_proton = new TGraphErrors(n,x,y2,ex,ey2);

  //  f2->SetParameters(0,0);
  //f2->SetParameters(1,0.0191653);

  
  TCanvas* c_proj = new TCanvas("c_proj","c_proj",800,800);
  gPad->SetLogx();
  gStyle->SetPadLeftMargin(0.16);

  sep_pion->GetXaxis()->SetTitle("p [GeV]");
  sep_pion->GetYaxis()->SetTitle("separation power");
  // sep_pion->GetYaxis()->SetTitleOffset(1.9);
  sep_pion->GetXaxis()->SetRangeUser(0.8,50);
  sep_pion->GetYaxis()->SetRangeUser(0,5);

  sep_pion->SetMarkerColor(4);
  sep_pion->SetMarkerStyle(21);
  sep_pion->SetMarkerSize(1.2);
  sep_pion->SetLineColor(4);
  sep_pion->Draw("alpe");
  
  sep_proton->SetMarkerColor(kGreen+1);
  sep_proton->SetMarkerStyle(22);
  sep_proton->SetMarkerSize(1.2);
  sep_proton->SetLineColor(kGreen+1);
  sep_proton->Draw("lpe");
  

  Labels();
  
  TLegend *leg2 = new TLegend(0.7,0.8,0.8,0.9);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->AddEntry(sep_pion,"K/#pi","lp");
  //  leg2->AddEntry(kaon_dEdx_truth,"K","lp");
  leg2->AddEntry(sep_proton,"K/p","lp");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();
  
   

}
