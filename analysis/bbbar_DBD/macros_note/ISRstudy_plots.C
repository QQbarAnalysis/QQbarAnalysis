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
void Labels(int i=0, TString pol="eL",int rad=0){

  QQBARLabel(0.79,0.954,"");
  if(i==2) QQBARLabel2(0.04,0.075, "K_{reco}<35 GeV & m_{2jets}>130 GeV",kOrange+3);
  if(i==-1) {
    QQBARLabel2(0.04,0.075, "K_{reco}<35 GeV & m_{2jets}>130 GeV",kOrange+3);
    QQBARLabel2(0.04,0.03, "& neutraleness jets < 0.85",kOrange+3);
  }
  if(i==-2) {
    QQBARLabel2(0.04,0.075, "K_{reco}<35 GeV & m_{2jets}>130 GeV",kOrange+3);
    QQBARLabel2(0.04,0.03, "& neutraleness jets < 0.85 & N_{nPFO} jets > 5",kOrange+3);
  }

  if(rad==0) QQBARLabel2(0.17,0.965, "e^{-}e^{+} #rightarrow b#bar{b} (E_{#gamma}<35 GeV)",kGray+2);
  else QQBARLabel2(0.17,0.965, "e^{-}e^{+} #rightarrow b#bar{b} (E_{#gamma}>35 GeV)",kGray+2);

  //  if(pol=="eL")QQBARLabel2(0.3,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  //if(pol=="eR")QQBARLabel2(0.3,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);

}



void ISRstudy_plots() {

  cout<< "bb qq radreturn ww zz hz "<<endl;

  int cuts=-2;
  
  TString pol="eL";
  TString sel="_";//"_tight_";
  TString folder=TString::Format("../output_20200427/IdentifyRR_cuts%i_",cuts);
  TString kt="genkt_restorer";//"_genkt";//"_tight_";
    
  TString filename = folder+"bbbar_genkt_restorer_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
  filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";

  cout<<filename<<endl;
  
  TFile *f = new TFile(filename);
  TH2F *h_cos_parton_rad = (TH2F*)f->Get("h_costheta_parton_0");
  TH2F *h_ISR_rad = (TH2F*)f->Get("h_ISR_E2d_0");
  TH2F *h_PFOphoton_E_costheta_rad = (TH2F*)f->Get("h_PFOphoton_E_costheta_0");
  TH2F *h_PFOphoton_npfo_ratio_2d_rad = (TH2F*)f->Get("h_PFOphoton_npfo_ratio_2d_0");
  TH1F *h_PFOphoton_all_costheta_rad = (TH1F*)f->Get("h_PFOphoton_all2_costheta_0");

  TH2F *h_cos_parton = (TH2F*)f->Get("h_costheta_parton_1");
  TH2F *h_ISR = (TH2F*)f->Get("h_ISR_E2d_1");
  TH2F *h_PFOphoton_E_costheta = (TH2F*)f->Get("h_PFOphoton_E_costheta_1");
  TH2F *h_PFOphoton_npfo_ratio_2d = (TH2F*)f->Get("h_PFOphoton_npfo_ratio_2d_1");
  TH1F *h_PFOphoton_all_costheta = (TH1F*)f->Get("h_PFOphoton_all2_costheta_1");

  TH2F *h_cos_reco_rad = (TH2F*)f->Get("h_costheta_reco_0");
  TH2F *h_cos_reco = (TH2F*)f->Get("h_costheta_reco_1");

  
  TH2F *h_nPFO_ratio_rad = (TH2F*)f->Get("h_PFOphoton_ratio_2d_0");
  TH2F *h_nPFO_ratio = (TH2F*)f->Get("h_PFOphoton_ratio_2d_1");

  TH2F *h_nPFO_ratio_E_rad = (TH2F*)f->Get("h_PFOphoton_ratio_E_2d_0");
  TH2F *h_nPFO_ratio_E = (TH2F*)f->Get("h_PFOphoton_ratio_E_2d_1");


  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleY(1.0);
  gStyle->SetMarkerSize(1.5);
  gStyle->SetPadRightMargin(0.12);
  gStyle->SetTitleSize(0.05,"xy");

  TGaxis::SetMaxDigits(3);

  
  ///////////////////////////

  double x[2], y[2];
  x[0]=-1; x[1]=2;
  y[0]=0.85; y[1]=0.85;
  TGraph *cut1_1= new TGraph(2,x,y);

  x[0]=0.85; x[1]=0.85;
  y[0]=-1; y[1]=2;
  TGraph *cut1_2= new TGraph(2,x,y);
  
  TCanvas * canvas_4_1 = new TCanvas("canvas_4_1","canvas_4_1",800,800);
  canvas_4_1->cd(1);
  // gPad->SetLogz();

  h_nPFO_ratio_rad->SetTitle("Radiative Return BKG");
  
  h_nPFO_ratio_rad->GetYaxis()->SetTitle("neutraleness jet_{1}");//"#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{2}}}");
  h_nPFO_ratio_rad->GetXaxis()->SetTitle("neutraleness jet_{2}");//"#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{1}}}");
  h_nPFO_ratio_rad->GetXaxis()->SetTitleOffset(1.3);
  h_nPFO_ratio_rad->GetYaxis()->SetTitleOffset(1.3);
  h_nPFO_ratio_rad->GetXaxis()->SetTitleSize(0.05);
  h_nPFO_ratio_rad->GetYaxis()->SetTitleSize(0.05);
  
  h_nPFO_ratio_rad->GetXaxis()->SetRangeUser(0,1);
  h_nPFO_ratio_rad->GetYaxis()->SetRangeUser(0,1);
  h_nPFO_ratio_rad->Draw("colz");

  cut1_1->SetLineColor(kMagenta);
  cut1_1->SetLineWidth(3);
  cut1_2->SetLineColor(kMagenta);
  cut1_2->SetLineWidth(3);
  cut1_1->Draw("l");
  cut1_2->Draw("l");

  Labels(cuts,pol,1);
  
  if(cuts==2)canvas_4_1->Print("plots/neutraleness_rad_cut0.eps");
    
  TCanvas * canvas_4_2 = new TCanvas("canvas_4_2","canvas_4_2",800,800);
  canvas_4_2->cd(2);
  
  // gPad->SetLogz();
  h_nPFO_ratio->SetTitle("Signal");
  
  h_nPFO_ratio->GetYaxis()->SetTitle("neutraleness jet_{1}");//#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{2}}}");
  h_nPFO_ratio->GetXaxis()->SetTitle("neutraleness jet_{2}");//"#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{1}}}");
  h_nPFO_ratio->GetXaxis()->SetRangeUser(0,1);
  h_nPFO_ratio->GetYaxis()->SetRangeUser(0,1);
  h_nPFO_ratio->GetXaxis()->SetTitleOffset(1.3);
  h_nPFO_ratio->GetYaxis()->SetTitleOffset(1.3);
  h_nPFO_ratio->GetXaxis()->SetTitleSize(0.05);
  h_nPFO_ratio->GetYaxis()->SetTitleSize(0.05);
  h_nPFO_ratio->Draw("colz");
  h_nPFO_ratio->Draw("colz");
  cut1_1->Draw("l");
  cut1_2->Draw("l");
  
  Labels(cuts,pol,0);
  if(cuts==2)canvas_4_2->Print("plots/neutraleness_cut0.eps");

  /// CUT 2
  //-------------------------------------------------------------
  x[0]=-1; x[1]=2;
  y[0]=6; y[1]=6;
  TGraph *cut2_1= new TGraph(2,x,y);


  
  TCanvas * canvas_7_1 = new TCanvas("canvas_7_1","canvas_7_1",800,800);
  canvas_7_1->cd(1);

  h_PFOphoton_npfo_ratio_2d_rad->SetTitle("Radiative Return BKG");
  h_PFOphoton_npfo_ratio_2d_rad->GetYaxis()->SetTitle("N_{nPFO}");
  h_PFOphoton_npfo_ratio_2d_rad->GetXaxis()->SetTitle("neutraleness jet");//"#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{1}}}");
  h_PFOphoton_npfo_ratio_2d_rad->GetXaxis()->SetRangeUser(0,1);
  h_PFOphoton_npfo_ratio_2d_rad->GetYaxis()->SetRangeUser(0,250);
  h_PFOphoton_npfo_ratio_2d_rad->GetXaxis()->SetTitleOffset(1.3);
  h_PFOphoton_npfo_ratio_2d_rad->GetYaxis()->SetTitleOffset(1.3);
  h_PFOphoton_npfo_ratio_2d_rad->GetXaxis()->SetTitleSize(0.05);
  h_PFOphoton_npfo_ratio_2d_rad->GetYaxis()->SetTitleSize(0.05);

  h_PFOphoton_npfo_ratio_2d_rad->Draw("colz");
  cut2_1->SetLineColor(kMagenta);
  cut2_1->SetLineWidth(3);
  cut2_1->Draw("l");
  
  Labels(cuts,pol,1);
  if(cuts==-1)canvas_7_1->Print("plots/nPFOs_rad_cut1.eps");

  TCanvas * canvas_7_2 = new TCanvas("canvas_7_2","canvas_7_2",800,800);
  canvas_7_2->cd(2);
  
  // gPad->SetLogz();
  h_PFOphoton_npfo_ratio_2d->SetTitle("Signal");
  h_PFOphoton_npfo_ratio_2d->GetYaxis()->SetTitle("N_{nPFO}");
  h_PFOphoton_npfo_ratio_2d->GetXaxis()->SetTitle("neutraleness jet");//#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{1}}}");
  h_PFOphoton_npfo_ratio_2d->GetXaxis()->SetRangeUser(0,1);
  h_PFOphoton_npfo_ratio_2d->GetYaxis()->SetRangeUser(0,250);
  h_PFOphoton_npfo_ratio_2d->GetXaxis()->SetTitleOffset(1.3);
  h_PFOphoton_npfo_ratio_2d->GetYaxis()->SetTitleOffset(1.3);
  h_PFOphoton_npfo_ratio_2d->GetXaxis()->SetTitleSize(0.05);
  h_PFOphoton_npfo_ratio_2d->GetYaxis()->SetTitleSize(0.05);
  h_PFOphoton_npfo_ratio_2d->Draw("colz");
  cut2_1->Draw("l");

  Labels(cuts,pol,0);
  if(cuts==-1)canvas_7_2->Print("plots/nPFOs_cut1.eps");

  //CUT 3
  // ----------------------------------------
  x[0]=-0.99; x[1]=-0.99;
  y[0]=35; y[1]=200;
  TGraph *cut3_1= new TGraph(2,x,y);

  x[0]=0.99; x[1]=0.99;
  y[0]=35; y[1]=200;
  TGraph *cut3_2= new TGraph(2,x,y);

  x[0]=-2; x[1]=-0.99;
  y[0]=35; y[1]=35;
  TGraph *cut3_3= new TGraph(2,x,y);

  x[0]=0.99; x[1]=2;
  y[0]=35; y[1]=35;
  TGraph *cut3_4= new TGraph(2,x,y);
  
  TCanvas * canvas_6_1 = new TCanvas("canvas_6_1","canvas_6_1",800,800);
  canvas_6_1->cd(1);
  
  h_PFOphoton_E_costheta_rad->SetTitle("Radiative Return BKG");
  h_PFOphoton_E_costheta_rad->GetYaxis()->SetTitle("E_{nPFO}");
  h_PFOphoton_E_costheta_rad->GetXaxis()->SetTitle("cos #theta_{nPFO}");
  h_PFOphoton_E_costheta_rad->GetXaxis()->SetRangeUser(0,1);
  h_PFOphoton_E_costheta_rad->GetYaxis()->SetRangeUser(0,250);
  h_PFOphoton_E_costheta_rad->GetXaxis()->SetTitleOffset(1.3);
  h_PFOphoton_E_costheta_rad->GetYaxis()->SetTitleOffset(1.3);
  h_PFOphoton_E_costheta_rad->GetXaxis()->SetTitleSize(0.05);
  h_PFOphoton_E_costheta_rad->GetYaxis()->SetTitleSize(0.05);
  h_PFOphoton_E_costheta_rad->Draw("colz");
  cut3_1->SetLineColor(kMagenta);
  cut3_1->SetLineWidth(3);
  cut3_2->SetLineColor(kMagenta);
  cut3_2->SetLineWidth(3);
  cut3_3->SetLineColor(kMagenta);
  cut3_3->SetLineWidth(3);
  cut3_4->SetLineColor(kMagenta);
  cut3_4->SetLineWidth(3);
  cut3_1->Draw("l");
  cut3_2->Draw("l");
  cut3_3->Draw("l");
  cut3_4->Draw("l");
  
  Labels(cuts,pol,1);
  if(cuts==-2)canvas_6_1->Print("plots/anglePFOs_rad_cut2.eps");

  TCanvas * canvas_6_2 = new TCanvas("canvas_6_2","canvas_6_2",800,800);
  canvas_6_2->cd(2);
  
  // gPad->SetLogz();
  h_PFOphoton_E_costheta->SetTitle("Signal");
  h_PFOphoton_E_costheta->GetYaxis()->SetTitle("E_{nPFO}");
  h_PFOphoton_E_costheta->GetXaxis()->SetTitle("cos #theta_{nPFO}");
  h_PFOphoton_E_costheta->GetXaxis()->SetRangeUser(0,1);
  h_PFOphoton_E_costheta->GetYaxis()->SetRangeUser(0,250);
  h_PFOphoton_E_costheta->GetXaxis()->SetTitleOffset(1.3);
  h_PFOphoton_E_costheta->GetYaxis()->SetTitleOffset(1.3);
  h_PFOphoton_E_costheta->GetXaxis()->SetTitleSize(0.05);
  h_PFOphoton_E_costheta->GetYaxis()->SetTitleSize(0.05);
  h_PFOphoton_E_costheta->Draw("colz");
  cut3_1->Draw("l");
  cut3_2->Draw("l");
  cut3_3->Draw("l");
  cut3_4->Draw("l");
  
  Labels(cuts,pol,0);
  if(cuts==-2)canvas_6_2->Print("plots/anglePFOs_cut2.eps");

}
