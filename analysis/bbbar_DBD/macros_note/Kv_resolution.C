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


void rms90(TH1F* h) {
  TAxis* axis = h->GetXaxis();
  Int_t nbins = axis->GetNbins();
  int imean = axis->FindBin(h->GetMean());
  Double_t entries =0.68*h->Integral();

  int imax=0;
  int jmax=0;
  Double_t mindist=9999999;
  for (int i=imean;i>0;i--) {
      for (int j=imean;j<nbins;j++) {
	if(h->Integral(i,j) < entries) {
	  imax=i;
	  jmax=j;
	}
      }
      if(fabs(h->GetBinCenter(imax)-h->GetBinCenter(jmax))<mindist)
	mindist=fabs(h->GetBinCenter(imax)-h->GetBinCenter(jmax));
  }
  Double_t result= mindist/2;
  cout<<"RMS of central 68% = "<<result<<" , RMS total = "<<h->GetRMS()<<endl;
}



void Labels( TString pol="eL"){

  QQBARLabel(0.86,0.954,"");
  if(pol=="eL") QQBARLabel2(0.25,0.965, "e_{L}^{-}e_{R}^{+} #rightarrow b#bar{b} (E_{#gamma}<35 GeV, #scale[0.7]{#int}L=250 fb^{-1})",kGray+2);
  if(pol=="eR") QQBARLabel2(0.25,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow b#bar{b} (E_{#gamma}<35 GeV, #scale[0.7]{#int}L=250 fb^{-1})",kGray+2);
  if(pol=="") QQBARLabel2(0.25,0.965, "e^{-}e^{+} #rightarrow b#bar{b} (E_{#gamma}<35 GeV, #scale[0.7]{#int}L=250 fb^{-1})",kGray+2);

}

void Kv_resolution() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(4);
  TGaxis::SetMaxDigits(3);

  
  int cuts=0;
  
  TString pol="eL";
  TString sel="_";//"_tight_";
  TString folder=TString::Format("../output_20200427/selection_cuts%i_",cuts);
  
  TString filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
  TFile *f = new TFile(filename);
  TH1F *h_resol = (TH1F*)f->Get("h_K_res");
  h_resol->Rebin(10);


  cuts=3;
  folder=TString::Format("../output_20200427/selection_cuts%i_",cuts);
  filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
  f = new TFile(filename);
  TH1F *h_resol2 = (TH1F*)f->Get("h_K_res");
  h_resol2->Rebin(10);

  cuts=5;
  folder=TString::Format("../output_20200427/selection_cuts%i_",cuts);
  filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
  f = new TFile(filename);
  TH1F *h_resol3 = (TH1F*)f->Get("h_K_res");
  h_resol3->Rebin(10);


  /*  pol="eR";
  folder=TString::Format("../output_20200427/selection_cuts%i_",cuts);
  
  filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
  f = new TFile(filename);
  TH1F *h_resol2 = (TH1F*)f->Get("h_K_res");*/
  

  TCanvas * canvasresol = new TCanvas("canvas_resol","canvas_resol",800,800);
  canvasresol->cd(1);
    
  h_resol->GetYaxis()->SetTitle("Entries / GeV");
  h_resol->GetXaxis()->SetTitle("E_{#gamma}-K_{reco}");
  h_resol->SetLineColor(1);
  h_resol->SetLineStyle(2);
  h_resol->GetXaxis()->SetRangeUser(-100,40);
  h_resol->Draw("histo");

  h_resol2->SetLineColor(4);
  h_resol2->Draw("histosame");

  h_resol3->SetLineColor(2);
  h_resol3->Draw("histosame");
  /*  h_resol2->SetLineColor(2);
      h_resol2->Draw("lsame");*/
  //  rms90(h_resol2);

  Labels(pol);
  
  TLegend *leg2 = new TLegend(0.2,0.65,0.4,0.8);//(0.4,0.3,0.5,0.6);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->AddEntry(h_resol,"No Cuts (RMS_{68%}=7.1 GeV)","l");
  leg2->AddEntry(h_resol2,"Cuts 1-2 (RMS_{68%}=4.5 GeV)","l");
  leg2->AddEntry(h_resol3,"Cuts 1-4 (RMS_{68%}=4.2 GeV)","l");
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();
  
  // canvasresol->Print(TString::Format("plots/resol_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));
  
}
