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
  QQBARLabel2(0.04,0.07, "Cuts 1-4",kOrange+3);
  /*  if(i==0) QQBARLabel2(0.04,0.07, "[No Cuts]",kOrange+3);
  if(i==1) QQBARLabel2(0.04,0.07, "K_{reco,geom}<35 GeV",kOrange+3);
  if(i==2) QQBARLabel2(0.04,0.07, "K_{reco,geom}<35 GeV & m_{j_{1},j_{2}}>130 GeV",kOrange+3);
  if(i==3) QQBARLabel2(0.04,0.07, "K_{reco,geom}<35 GeV & 80GeV<m_{j_{1},j_{2}}<100GeV",kOrange+3);
  if(i==4) QQBARLabel2(0.04,0.07, "K_{reco,geom}<35 GeV & 150GeV<m_{j_{1},j_{2}}<160GeV",kOrange+3);
  if(i==5) QQBARLabel2(0.04,0.07, "K_{reco,geom}<35 GeV & m_{j_{1},j_{2}}>240 GeV",kOrange+3);
  if(i==6) {
    QQBARLabel2(0.04,0.085, "K_{reco,geom}<35 GeV & m_{j_{1},j_{2}}>130 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& #frac{#Sigma_{i=nPFOs} E_{i}}{E_{jet}}>0.85 (both jets)",kOrange+3);
  }
  if(i==7) {
    QQBARLabel2(0.04,0.085, "K_{reco,geom}<35 GeV & m_{j_{1},j_{2}}>130 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& #frac{#Sigma_{i=nPFOs} E_{i}}{E_{jet}}>0.85 & E_{jet}>55GeV (both jets)",kOrange+3);
  }
  if(i==8) {
    QQBARLabel2(0.04,0.085, "K_{reco,geom}<35 GeV & m_{j_{1},j_{2}}>130 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& #frac{#Sigma_{i=nPFOs} E_{i}}{E_{jet}}>0.85 & E_{jet}>55GeV (both jets) &y_{23}<0.015",kOrange+3);
    }*/
  
  //  QQBARLabel2(0.04,0.08, "Preselection",kOrange+3);

  if(pol=="eL")QQBARLabel2(0.2,0.965, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, #scale[0.7]{#int}L=250 fb^{-1}",kGray+2);
  if(pol=="eR")QQBARLabel2(0.2,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, #scale[0.7]{#int}L=250 fb^{-1}",kGray+2);

}


void effpreselection() {

  cout<< "bb qq radreturn ww zz hz "<<endl;

  for(int step=5; step<6; step++) {
    
  TH1F *h_costheta_bb[2]; 
  TH1F *h_costheta_cc[2]; 
  TH1F *h_costheta_qq[2]; 
  TH1F *h_costheta_radreturn[2]; 
  TH1F *h_costheta_ww[2]; 
  TH1F *h_costheta_zz[2]; 
  TH1F *h_costheta_hz[2]; 


  TString pol="eL";

  for(int i=0; i<2; i++) {

  int cuts=0;
  if(i==0) cuts=0;
  if(i==1) cuts=step;

  TString folder=TString::Format("../output_20200427/selection_cuts%i_",cuts);

  //----------------------------------
  TString filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
  //  if(i==0) filename = folder+"bbbar_radret_genkt_R100_Kgamma35_250GeV_"+pol+".root";
  cout<<" Radiative return file: "<<filename<<endl;
  TFile *f = new TFile(filename);
  h_costheta_radreturn[i] = (TH1F*)f->Get("h_costheta_radreturn");
  if(pol=="eL") h_costheta_radreturn[i]->Scale(250./12.9);
  if(pol=="eR") h_costheta_radreturn[i]->Scale(250./17.95);

  //----------------------------------
  // filename = folder+"bbbar_radret_genkt_R150_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
  filename = folder+"bbbar_genkt_restorer_Kgamma35_250GeV_"+pol+".root";
  cout<<" Z-->qq file: "<<filename<<endl;
  TFile *f1 = new TFile(filename);
  h_costheta_bb[i] = (TH1F*)f1->Get("h_costheta_bb");
  h_costheta_qq[i] = (TH1F*)f1->Get("h_costheta_qq");
  h_costheta_cc[i] = (TH1F*)f1->Get("h_costheta_cc");
  if(pol=="eL" ) { 
     h_costheta_bb[i]->Scale(250./266.5);
     h_costheta_qq[i]->Scale(250./266.5);
     h_costheta_cc[i]->Scale(250./266.5);
  }
  if(pol=="eR" ) {
    h_costheta_bb[i]->Scale(250./276.9);
    h_costheta_cc[i]->Scale(250./276.9);
    h_costheta_qq[i]->Scale(250./276.9);
  }

  //----------------------------------
  filename = folder+"bkg_genkt_restorer_Kgamma35_HZ_250GeV_"+pol+".root";
  cout<<" HZ file: "<<filename<<endl;
  TFile *f3 = new TFile(filename);
  h_costheta_hz[i] = (TH1F*)f3->Get("h_costheta_bb");
  if(pol=="eL") h_costheta_hz[i]->Scale(250./353.);
  if(pol=="eR") h_costheta_hz[i]->Scale(250./550.);

  //----------------------------------
  filename = folder+"bkg_genkt_restorer_Kgamma35_ZZ_250GeV_"+pol+".root";
  cout<<" ZZ file: "<<filename<<endl;
  TFile *f4 = new TFile(filename);
  h_costheta_zz[i] = (TH1F*)f4->Get("h_costheta_bb");

  //----------------------------------
  filename = folder+"bkg_genkt_restorer_Kgamma35_WW_250GeV_"+pol+".root";
  cout<<" WW file: "<<filename<<endl;
  TFile *f5 = new TFile(filename);
  h_costheta_ww[i] = (TH1F*)f5->Get("h_costheta_bb");
  if(pol=="eL") h_costheta_ww[i]->Scale(250./72.2);

  
  }
  
  
  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);

  TCanvas * canvas1 = new TCanvas("canvas1","canvas1",800,800);
  gPad->SetLogy();
  canvas1->cd(1);
  h_costheta_bb[0]->GetYaxis()->SetTitle("N_{events}");
  h_costheta_bb[0]->GetYaxis()->SetRangeUser(10,10000000);
  h_costheta_bb[0]->GetXaxis()->SetRangeUser(0,1.);
  h_costheta_bb[0]->GetXaxis()->SetTitle("|cos#theta_{q}|");
  h_costheta_bb[0]->GetYaxis()->SetTitleOffset(1.3);

  h_costheta_bb[0]->SetLineColor(4);
  h_costheta_bb[0]->Draw("histo");

  h_costheta_qq[0]->SetLineColor(1);
  h_costheta_qq[0]->Draw("histosame");
  h_costheta_cc[0]->SetLineStyle(2);
  h_costheta_cc[0]->Draw("histosame");
  h_costheta_radreturn[0]->SetLineColor(2);
  h_costheta_radreturn[0]->Draw("histosame");

  /*  h_costheta_ww[0]->SetLineColor(5);
  h_costheta_ww[0]->Draw("histosame");
  h_costheta_zz[0]->SetLineColor(6);
  h_costheta_zz[0]->Draw("histosame");
  h_costheta_hz[0]->SetLineColor(7);
  h_costheta_hz[0]->Draw("histosame");*/

  QQBARLabel(0.8,0.951,"");
  QQBARLabel2(0.05,0.07, "[No Cuts]",kOrange+3);
  

  if(pol=="eL")QQBARLabel2(0.2,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250GeV, 250fb^{-1}",kGray+2);
  if(pol=="eR")QQBARLabel2(0.2,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250GeV, 250fb^{-1}",kGray+2);

  TLegend *leg0 = new TLegend(0.6,0.2,0.9,0.4);//(0.4,0.3,0.5,0.6);
  leg0->SetTextSize(0.035);
  leg0->AddEntry(h_costheta_bb[0],"#font[42]{b#bar{b}}","l");
  leg0->AddEntry(h_costheta_cc[0],"#font[42]{c#bar{c}}","l");
  leg0->AddEntry(h_costheta_qq[0],"#font[42]{q#bar{q} (q=uds)}","l");
  /* leg0->AddEntry(h_costheta_radreturn[0],"#font[42]{#gammaZ#rightarrow #gammaq#bar{q} (q=udscb)}","l");
     leg0->AddEntry(h_costheta_hz[0],"#font[42]{HZ}","l");
  leg0->AddEntry(h_costheta_zz[0],"#font[42]{ZZ}","l");
  leg0->AddEntry(h_costheta_ww[0],"#font[42]{WW}","l");*/
  leg0->SetFillStyle(0);
  leg0->SetLineWidth(0);
  leg0->SetLineColor(0);
  //  leg0->SetShadowColor(0);
  leg0->SetBorderSize(0);
  leg0->Draw();

  canvas1->Print(TString::Format("plots/N_all_%s.eps",pol.Data()));

  h_costheta_radreturn[1]->Divide(h_costheta_bb[1]);
   h_costheta_zz[1]->Divide(h_costheta_bb[1]);
  h_costheta_hz[1]->Divide(h_costheta_bb[1]);
  h_costheta_ww[1]->Divide(h_costheta_bb[1]);

  h_costheta_radreturn[1]->Scale(100.);
    h_costheta_zz[1]->Scale(100.);
  h_costheta_hz[1]->Scale(100.);
  h_costheta_ww[1]->Scale(100.);

  h_costheta_bb[1]->Divide(h_costheta_bb[0]);
  h_costheta_cc[1]->Divide(h_costheta_cc[0]);
  h_costheta_qq[1]->Divide(h_costheta_qq[0]);
  
  TCanvas * canvas2 = new TCanvas(TString::Format("canvas_cut%i",step),TString::Format("canvas_cut%i",step),800,800);
  canvas2->cd(1);
  h_costheta_bb[1]->GetYaxis()->SetTitle("#varepsilon_{had}^{q#bar{q}}");
  h_costheta_bb[1]->GetYaxis()->SetRangeUser(0,1.4);
  h_costheta_bb[1]->GetXaxis()->SetRangeUser(0,1.);
  h_costheta_bb[1]->GetXaxis()->SetTitle("|cos#theta_{q}|");
  h_costheta_bb[1]->GetYaxis()->SetTitleOffset(1.3);

  h_costheta_bb[1]->SetLineColor(4);
  h_costheta_bb[1]->Draw("histo");

  h_costheta_qq[1]->SetLineColor(1);
  h_costheta_qq[1]->Draw("histosame");
  h_costheta_cc[1]->SetLineStyle(2);
  h_costheta_cc[1]->Draw("histosame");
  h_costheta_radreturn[1]->SetLineColor(2);
  h_costheta_radreturn[1]->Draw("histosame");

  Labels(step,pol);

  TLegend *leg1 = new TLegend(0.6,0.8,0.9,0.9);//(0.4,0.3,0.5,0.6);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(h_costheta_bb[1],"#font[52]{q}=b-quark","l");
  leg1->AddEntry(h_costheta_cc[1],"#font[52]{q}=c-quark","l");
  leg1->AddEntry(h_costheta_qq[1],"#font[52]{q}=uds-quarks","l");
  /* leg1->AddEntry(h_costheta_radreturn[1],"#font[42]{#gammaZ#rightarrow #gammaq#bar{q} (q=udscb)}","l");
  leg1->AddEntry(h_costheta_hz[1],"#font[42]{HZ}","l");
  leg1->AddEntry(h_costheta_zz[1],"#font[42]{ZZ}","l");
  leg1->AddEntry(h_costheta_ww[1],"#font[42]{WW}","l");*/
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  //  leg1->SetShadowColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();
  
  canvas2->Print(TString::Format("plots/epsilonhad_cuts%i_%s.eps",step,pol.Data()));

  TCanvas * canvas3 = new TCanvas(TString::Format("canvas3_cut%i",step),TString::Format("canvas3_cut%i",step),800,800);
  canvas3->cd(1);
  gPad->SetLogy();
  h_costheta_radreturn[1]->GetYaxis()->SetTitle("Bkg / S [%]");
  h_costheta_radreturn[1]->GetYaxis()->SetRangeUser(0.1,10000);
  h_costheta_radreturn[1]->GetXaxis()->SetRangeUser(0,1.);
  h_costheta_radreturn[1]->GetXaxis()->SetTitle("|cos#theta_{q}|");
  h_costheta_radreturn[1]->GetYaxis()->SetTitleOffset(1.3);

  h_costheta_radreturn[1]->SetLineColor(2);
  h_costheta_radreturn[1]->Draw("histo");

  h_costheta_ww[1]->SetLineColor(5);
  h_costheta_ww[1]->Draw("histosame");
  h_costheta_zz[1]->SetLineColor(6);
  h_costheta_zz[1]->Draw("histosame");
  h_costheta_hz[1]->SetLineColor(7);
  h_costheta_hz[1]->Draw("histosame");

  Labels(step,pol);
  
  TLegend *leg2 = new TLegend(0.57,0.83,0.85,0.93);//(0.4,0.3,0.5,0.6);
  leg2->SetTextSize(0.035);
  leg2->AddEntry(h_costheta_radreturn[1],"#font[42]{#gammaZ#rightarrow #gammaq#bar{q} (q=udscb)}","l");
  leg2->AddEntry(h_costheta_hz[1],"#font[42]{HZ}","l");
  leg2->AddEntry(h_costheta_zz[1],"#font[42]{ZZ}","l");
  leg2->AddEntry(h_costheta_ww[1],"#font[42]{WW}","l");
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  //  leg2->SetShadowColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();

  canvas3->Print(TString::Format("plots/B_S_cuts%i_%s.eps",step,pol.Data()));

  }
  
}
