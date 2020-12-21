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


void Labels_parton(TString pol="eL"){

  QQBARLabel(0.86,0.952,"");

  if(pol=="eL")QQBARLabel2(0.3,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250GeV, 250fb^{-1}",kGray+2);
  if(pol=="eR")QQBARLabel2(0.3,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250GeV, 250fb^{-1}",kGray+2);
}

void Labels(TString pol="eL",int i=0){

  QQBARLabel(0.86,0.952,"");
  // QQBARLabel2(0.2,0.2, "E^{ISR}_{#gamma}=35 GeV, K_{#gamma}^{reco.,geom.}<35 GeV",kOrange+2);
  if(i>-0.5) QQBARLabel2(0.1,0.05, "Jet Distance: d_{ij}=min(E_{i},E_{j})#frac{1-cos(#theta_{ij})}{1-cosR} R=1.25",kGray+2);

  if(pol=="eL")QQBARLabel2(0.3,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250GeV, 250fb^{-1}",kGray+2);
  if(pol=="eR")QQBARLabel2(0.3,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250GeV, 250fb^{-1}",kGray+2);

  if(i==0) QQBARLabel2(0.2,0.8, "Signal Events",kBlack);
  if(i==1) QQBARLabel2(0.2,0.8, "1-ISR Bkg Events",kBlack);
  if(i==2) QQBARLabel2(0.2,0.8, "2-ISR Bkg Events",kBlack);

}


void Rparam_comparison2() {
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);
  TGaxis::SetMaxDigits(3);

   
  TString pol="eR";

  TString folder=TString::Format("../output_20200420_1/kstudy_cuts%i_",1);
  TString filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";
  TFile *f = new TFile(filename);
  
  TH1F *h_KISR=(TH1F*)f->Get("h_KISR_0");
  TH1F *h_KReco1=(TH1F*)f->Get("h_KReco_1_0");
  TH1F *h_KReco2=(TH1F*)f->Get("h_KReco_2_0");
  TH1F *h_KRecoGeo=(TH1F*)f->Get("h_KReco_geom_0");

  TH1F *h_KReco1_1=(TH1F*)f->Get("h_KReco_1_1");
  TH1F *h_KReco2_1=(TH1F*)f->Get("h_KReco_2_1");
  TH1F *h_KRecoGeo_1=(TH1F*)f->Get("h_KReco_geom_1");

  TH1F *h_KReco1_2=(TH1F*)f->Get("h_KReco_1_2");
  TH1F *h_KReco2_2=(TH1F*)f->Get("h_KReco_2_2");
  TH1F *h_KRecoGeo_2=(TH1F*)f->Get("h_KReco_geom_2");

  TH1F *h_KReco_1divgeom_plus_2divgeom_0=(TH1F*)f->Get("h_KReco_1divgeom_plus_2divgeom_0");
  TH1F *h_KReco_1divgeom_plus_2divgeom_1=(TH1F*)f->Get("h_KReco_1divgeom_plus_2divgeom_1");
  TH1F *h_KReco_1divgeom_plus_2divgeom_2=(TH1F*)f->Get("h_KReco_1divgeom_plus_2divgeom_2");


  h_KReco1->Rebin(10);
  h_KReco2->Rebin(10);
  h_KRecoGeo->Rebin(10);

  h_KReco1_1->Rebin(10);
  h_KReco2_1->Rebin(10);
  h_KRecoGeo_1->Rebin(10);

  h_KReco1_2->Rebin(10);
  h_KReco2_2->Rebin(10);
  h_KRecoGeo_2->Rebin(10); 

  TCanvas * canvas1 = new TCanvas("canvas_1","canvas_1",800,800);
  canvas1->cd(1);
  
  h_KISR->GetYaxis()->SetTitle("entries");
  h_KISR->GetXaxis()->SetTitle("E^{ISR}_{#gamma}");
  h_KISR->GetYaxis()->SetTitleOffset(1.3);
  h_KISR->SetLineColor(1);
  h_KISR->SetLineStyle(1);
  h_KISR->SetLineWidth(2);
  h_KISR->Draw("histo");
   
  Labels_parton(pol);


  TCanvas * canvas2 = new TCanvas("canvas_2","canvas_2",800,800);
  canvas2->cd(1);
  
  h_KReco1->GetYaxis()->SetTitle("entries");
  h_KReco1->GetXaxis()->SetTitle("K_{#gamma}^{reco.}");
  h_KReco1->GetYaxis()->SetTitleOffset(1.3);
  h_KReco1->SetLineColor(2);
  h_KReco1->SetLineStyle(2);
  h_KReco1->SetLineWidth(2);
  h_KReco1->Draw("histosame");

  h_KReco2->SetLineColor(4);
  h_KReco2->SetLineStyle(2);
  h_KReco2->SetLineWidth(2);
  h_KReco2->Draw("histosame");

  h_KRecoGeo->SetLineColor(1);
  h_KRecoGeo->SetLineStyle(1);
  h_KRecoGeo->SetLineWidth(2);
  h_KRecoGeo->Draw("histosame");
  
  Labels(pol,0);

  TLegend *leg2 = new TLegend(0.3,0.75,0.5,0.93);
  leg2->SetTextSize(0.03);
  leg2->AddEntry(h_KReco1,"|p_{j1}| sin(acol)/sin(#theta_{j2})","l");
  leg2->AddEntry(h_KReco2,"|p_{j2}| sin(acol)/sin(#theta_{j1})","l");
  leg2->AddEntry(h_KRecoGeo,"250.* sin(acol)/(sin(acol) +sin(#theta_{j2})+ sin(#theta_{j2}))","l");
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetBorderSize(0);
  leg2->Draw();

  TCanvas * canvas3 = new TCanvas("canvas_3","canvas_3",800,800);
  canvas3->cd(1);
  
  h_KReco1_1->GetYaxis()->SetTitle("entries");
  h_KReco1_1->GetXaxis()->SetTitle("K_{#gamma}^{reco.}");
  h_KReco1_1->GetYaxis()->SetTitleOffset(1.3);
  h_KReco1_1->SetLineColor(2);
  h_KReco1_1->SetLineStyle(2);
  h_KReco1_1->SetLineWidth(2);
  h_KReco1_1->Draw("histosame");

  h_KReco2_1->SetLineColor(4);
  h_KReco2_1->SetLineStyle(2);
  h_KReco2_1->SetLineWidth(2);
  h_KReco2_1->Draw("histosame");

  h_KRecoGeo_1->SetLineColor(1);
  h_KRecoGeo_1->SetLineStyle(1);
  h_KRecoGeo->SetLineWidth(2);
  h_KRecoGeo_1->Draw("histosame");
  
  Labels(pol,1);
  leg2->Draw();

  TCanvas * canvas4 = new TCanvas("canvas_4","canvas_4",800,800);
  canvas4->cd(1);
  
  h_KReco1_2->GetYaxis()->SetTitle("entries");
  h_KReco1_2->GetXaxis()->SetTitle("K_{#gamma}^{reco.}");
  h_KReco1_2->GetYaxis()->SetTitleOffset(1.3);
  h_KReco1_2->SetLineColor(2);
  h_KReco1_2->SetLineStyle(2);
  h_KReco1_2->SetLineWidth(2);
  h_KReco1_2->Draw("histosame");

  h_KReco2_2->SetLineColor(4);
  h_KReco2_2->SetLineStyle(2);
  h_KReco2_2->SetLineWidth(2);
  h_KReco2_2->Draw("histosame");

  h_KRecoGeo_2->SetLineColor(1);
  h_KRecoGeo_2->SetLineStyle(1);
  h_KRecoGeo->SetLineWidth(2);
  h_KRecoGeo_2->Draw("histosame");
  
  Labels(pol,2);
  leg2->Draw();


  TCanvas * canvas5 = new TCanvas("canvas_5","canvas_5",800,800);
  canvas5->cd(1);
  
  h_KReco_1divgeom_plus_2divgeom_0->GetYaxis()->SetTitle("entries");
  h_KReco_1divgeom_plus_2divgeom_0->GetXaxis()->SetTitle("K_{#gamma}^{reco,1}/K_{#gamma}^{reco,Geom}+K_{#gamma}^{reco,2}/K_{#gamma}^{reco,Geom}");
  h_KReco_1divgeom_plus_2divgeom_0->GetYaxis()->SetTitleOffset(1.3);
  h_KReco_1divgeom_plus_2divgeom_0->GetXaxis()->SetRangeUser(0,4);
  h_KReco_1divgeom_plus_2divgeom_0->GetYaxis()->SetRangeUser(0,5000);
  h_KReco_1divgeom_plus_2divgeom_0->SetLineColor(1);
  h_KReco_1divgeom_plus_2divgeom_0->SetLineStyle(1);
  h_KReco_1divgeom_plus_2divgeom_0->SetLineWidth(2);
  h_KReco_1divgeom_plus_2divgeom_0->Draw("histosame");

  h_KReco_1divgeom_plus_2divgeom_1->SetLineColor(kGreen);
  h_KReco_1divgeom_plus_2divgeom_1->SetLineStyle(1);
  h_KReco_1divgeom_plus_2divgeom_1->SetLineWidth(5);
  h_KReco_1divgeom_plus_2divgeom_1->Draw("histosame");

  h_KReco_1divgeom_plus_2divgeom_2->SetLineColor(kGray+2);
  h_KReco_1divgeom_plus_2divgeom_2->SetLineStyle(1);
  h_KReco_1divgeom_plus_2divgeom_2->SetLineWidth(5);
  h_KReco_1divgeom_plus_2divgeom_2->Draw("histosame");
  
  Labels(pol,-1);
  
  TLegend *leg3 = new TLegend(0.3,0.75,0.5,0.93);
  leg3->SetTextSize(0.03);
  leg3->AddEntry(h_KReco_1divgeom_plus_2divgeom_0,TString::Format("Signal Events (E^{ISR}_{#gamma}<35 GeV): %0.f",h_KReco_1divgeom_plus_2divgeom_0->GetEntries()),"l");
  leg3->AddEntry(h_KReco_1divgeom_plus_2divgeom_1,TString::Format("BKG Events (1 #gamma with E^{ISR}_{#gamma}>35 GeV): %0.f",h_KReco_1divgeom_plus_2divgeom_1->GetEntries()),"l");
  leg3->AddEntry(h_KReco_1divgeom_plus_2divgeom_2,TString::Format("BKG Events (2 #gamma with E^{ISR}_{#gamma}>35 GeV): %0.f",h_KReco_1divgeom_plus_2divgeom_2->GetEntries()),"l");
  leg3->SetFillStyle(0);
  leg3->SetLineWidth(0);
  leg3->SetBorderSize(0);
  leg3->Draw();


  
}
