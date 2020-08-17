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
  if(i==0) QQBARLabel2(0.04,0.07, "[No Cuts]",kOrange+3);
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

}



void selection_plots() {

  cout<< "bb qq radreturn ww zz hz "<<endl;

  //Efficiency y23.
  float bb_integral[100];
  float qq_integral[100];
  float cc_integral[100];
  float radreturn_integral[100];
  float zz_integral[100];
  float ww_integral[100];
  float hz_integral[100];
  for(int i=0; i<100; i++) {
    bb_integral[i]=0;
    qq_integral[i]=0;
    cc_integral[i]=0;
    radreturn_integral[i]=0;
    zz_integral[i]=0;
    ww_integral[i]=0;
    hz_integral[i]=0;
  }

    
  for(int i=0; i<1; i++) {

    //  if(i==1) i=14;

    if(i==6) i=13;
    int cuts=i;
    
    TString pol="eL";
    TString sel="_";//"_tight_";
    TString folder=TString::Format("../output_20200427/selection_cuts%i_",cuts);
    TString kt="genkt_restorer";//"_genkt";//"_tight_";
    
    TString filename = folder+"bbbar_genkt_restorer_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
    // filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
    // filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";

    TFile *f = new TFile(filename);
    TH1F *h_mjj_bb = (TH1F*)f->Get("h_mjj_bb");
    TH1F *h_mj1_mj2_bb = (TH1F*)f->Get("h_mj1_mj2_bb");
    TH1F *h_y23_bb = (TH1F*)f->Get("h_y23_bb");
    TH1F *h_costheta_bb = (TH1F*)f->Get("h_costheta_bb");
    TH1F *h_K_bb = (TH1F*)f->Get("h_K_bb");
    TH1F *h_thrust_bb = (TH1F*)f->Get("h_thrust_bb");
    TH1F *h_costhetagamma_bb = (TH1F*)f->Get("h_costhetagamma_bb");
    
    TH1F *h_mjj_cc = (TH1F*)f->Get("h_mjj_cc");
    TH1F *h_mj1_mj2_cc = (TH1F*)f->Get("h_mj1_mj2_cc");
    TH1F *h_y23_cc = (TH1F*)f->Get("h_y23_cc");
    TH1F *h_costheta_cc = (TH1F*)f->Get("h_costheta_cc");
    TH1F *h_K_cc = (TH1F*)f->Get("h_K_cc");
    TH1F *h_thrust_cc = (TH1F*)f->Get("h_thrust_cc");
    TH1F *h_costhetagamma_cc = (TH1F*)f->Get("h_costhetagamma_cc");
    
    TH1F *h_mjj_qq = (TH1F*)f->Get("h_mjj_qq");
    TH1F *h_mj1_mj2_qq = (TH1F*)f->Get("h_mj1_mj2_qq");
    TH1F *h_y23_qq = (TH1F*)f->Get("h_y23_qq");
    TH1F *h_costheta_qq = (TH1F*)f->Get("h_costheta_qq");
    TH1F *h_K_qq = (TH1F*)f->Get("h_K_qq");
    TH1F *h_thrust_qq = (TH1F*)f->Get("h_thrust_qq");
    TH1F *h_costhetagamma_qq = (TH1F*)f->Get("h_costhetagamma_qq");
    
    if(pol=="eL" ) { 
    h_mjj_bb->Scale(250./13.15);
    h_mj1_mj2_bb->Scale(250./13.15);
    h_y23_bb->Scale(250./13.15);
    h_costheta_bb->Scale(250./13.15);
    h_K_bb->Scale(250./13.15);
    h_thrust_bb->Scale(250./13.15);
    h_costhetagamma_bb->Scale(250./13.15);

    h_mjj_cc->Scale(250./13.15);
    h_mj1_mj2_cc->Scale(250./13.15);
    h_y23_cc->Scale(250./13.15);
    h_costheta_cc->Scale(250./13.15);
    h_K_cc->Scale(250./13.15);
    h_thrust_cc->Scale(250./13.15);
    h_costhetagamma_cc->Scale(250./13.15);

    h_mjj_qq->Scale(250./13.15);
    h_mj1_mj2_qq->Scale(250./13.15);
    h_y23_qq->Scale(250./13.15);
    h_costheta_qq->Scale(250./13.15);
    h_K_qq->Scale(250./13.15);
    h_thrust_qq->Scale(250./13.15);
    h_costhetagamma_qq->Scale(250./13.15);    
  }

  if(pol=="eR" ) {
    h_mjj_bb->Scale(250./19.9);
    h_mj1_mj2_bb->Scale(250./19.9);
    h_y23_bb->Scale(250./19.9);
    h_costheta_bb->Scale(250./19.9);
    h_K_bb->Scale(250./19.9);
    h_thrust_bb->Scale(250./19.9);
    h_costhetagamma_bb->Scale(250./19.9);

    h_mjj_cc->Scale(250./19.9);
    h_mj1_mj2_cc->Scale(250./19.9);
    h_y23_cc->Scale(250./19.9);
    h_costheta_cc->Scale(250./19.9);
    h_K_cc->Scale(250./19.9);
    h_thrust_cc->Scale(250./19.9);
    h_costhetagamma_cc->Scale(250./19.9);

    h_mjj_qq->Scale(250./19.9);
    h_mj1_mj2_qq->Scale(250./19.9);
    h_y23_qq->Scale(250./19.9);
    h_costheta_qq->Scale(250./19.9);
    h_K_qq->Scale(250./19.9);
    h_thrust_qq->Scale(250./19.9);
    h_costhetagamma_qq->Scale(250./19.9);
  }


  // ----------------------------------------
  // filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
  TFile *f1 = new TFile(filename);

  TH1F *h_mjj_radreturn = (TH1F*)f1->Get("h_mjj_radreturn");
  TH1F *h_mj1_mj2_radreturn = (TH1F*)f1->Get("h_mj1_mj2_radreturn");
  TH1F *h_y23_radreturn = (TH1F*)f1->Get("h_y23_radreturn");
  TH1F *h_costheta_radreturn = (TH1F*)f1->Get("h_costheta_radreturn");
  TH1F *h_K_radreturn = (TH1F*)f1->Get("h_K_radreturn");
  TH1F *h_thrust_radreturn = (TH1F*)f1->Get("h_thrust_radreturn");
  TH1F *h_costhetagamma_radreturn = (TH1F*)f1->Get("h_costhetagamma_radreturn");

  if(pol=="eL" ) { 
    h_mjj_radreturn->Scale(250./13.15);
    h_mj1_mj2_radreturn->Scale(250./13.15);
    h_y23_radreturn->Scale(250./13.15);
    h_costheta_radreturn->Scale(250./13.15);
    h_K_radreturn->Scale(250./13.15);
    h_thrust_radreturn->Scale(250./13.15);
    h_costhetagamma_radreturn->Scale(250./13.15);
  }

  if(pol=="eR" ) {
    h_mjj_radreturn->Scale(250./19.9);
    h_mj1_mj2_radreturn->Scale(250./19.9);
    h_y23_radreturn->Scale(250./19.9);
    h_costheta_radreturn->Scale(250./19.9);
    h_K_radreturn->Scale(250./19.9);
    h_thrust_radreturn->Scale(250./19.9);
    h_costhetagamma_radreturn->Scale(250./19.9);
  }

  
  TFile *f2 = new TFile(folder+"bkg_"+kt+"_Kgamma35_WW"+sel+"250GeV_"+pol+".root");
  TH1F *h_mjj_ww = (TH1F*)f2->Get("h_mjj_bb");
  TH1F *h_mj1_mj2_ww = (TH1F*)f2->Get("h_mj1_mj2_bb");
  TH1F *h_y23_ww = (TH1F*)f2->Get("h_y23_bb");
  TH1F *h_costheta_ww = (TH1F*)f2->Get("h_costheta_bb");
  TH1F *h_K_ww = (TH1F*)f2->Get("h_K_bb");
  TH1F *h_thrust_ww = (TH1F*)f2->Get("h_thrust_bb");
  TH1F *h_costhetagamma_ww = (TH1F*)f2->Get("h_costhetagamma_bb");

  if(pol=="eL" ) {
    h_mjj_ww->Scale(250./72.2);
    h_mj1_mj2_ww->Scale(250./72.2);
    h_y23_ww->Scale(250./72.2);
    h_costheta_ww->Scale(250./72.2);
    h_K_ww->Scale(250./72.2);
    h_thrust_ww->Scale(250./72.2);
    h_costhetagamma_ww->Scale(250./72.2);
  }


  TFile *f3 = new TFile(folder+"bkg_"+kt+"_Kgamma35_ZZ"+sel+"250GeV_"+pol+".root");
  
  TH1F *h_mjj_zz = (TH1F*)f3->Get("h_mjj_bb");
  TH1F *h_mj1_mj2_zz = (TH1F*)f3->Get("h_mj1_mj2_bb");
  TH1F *h_y23_zz = (TH1F*)f3->Get("h_y23_bb");
  TH1F *h_costheta_zz = (TH1F*)f3->Get("h_costheta_bb");
  TH1F *h_K_zz = (TH1F*)f3->Get("h_K_bb");
  TH1F *h_thrust_zz = (TH1F*)f3->Get("h_thrust_bb");
  TH1F *h_costhetagamma_zz = (TH1F*)f3->Get("h_costhetagamma_bb");

  TFile *f4 = new TFile(folder+"bkg_"+kt+"_Kgamma35_HZ"+sel+"250GeV_"+pol+".root");
  TH1F *h_mjj_hz = (TH1F*)f4->Get("h_mjj_bb");
  TH1F *h_mj1_mj2_hz = (TH1F*)f4->Get("h_mj1_mj2_bb");
  TH1F *h_y23_hz = (TH1F*)f4->Get("h_y23_bb");
  TH1F *h_costheta_hz = (TH1F*)f4->Get("h_costheta_bb");
  TH1F *h_K_hz = (TH1F*)f4->Get("h_K_bb");
  TH1F *h_thrust_hz = (TH1F*)f4->Get("h_thrust_bb");
  TH1F *h_costhetagamma_hz = (TH1F*)f4->Get("h_costhetagamma_bb");

  if(pol=="eL" ) {
    h_mjj_hz->Scale(250./353.);
    h_mj1_mj2_hz->Scale(250./353.);
    h_y23_hz->Scale(250./353.);
    h_costheta_hz->Scale(250./353.);
    h_K_hz->Scale(250./353.);
    h_thrust_hz->Scale(250./353.);
    h_costhetagamma_hz->Scale(250./353.);
  }
  if(pol=="eR" ) {
    h_mjj_hz->Scale(250./550.);
    h_mj1_mj2_hz->Scale(250./550.);
    h_y23_hz->Scale(250./550.);
    h_costheta_hz->Scale(250./550.);
    h_K_hz->Scale(250./550.);
    h_thrust_hz->Scale(250./550.);
    h_costhetagamma_hz->Scale(250./550.);
  }

  int index=fabs(i);
  
  //Efficiency 
  bb_integral[index+1]=h_mjj_bb->Integral();
  qq_integral[index+1]=h_mjj_qq->Integral();
  cc_integral[index+1]=h_mjj_cc->Integral();
  radreturn_integral[index+1]=h_mjj_radreturn->Integral();
  zz_integral[index+1]=h_mjj_zz->Integral();
  hz_integral[index+1]=h_mjj_hz->Integral();
  ww_integral[index+1]=h_mjj_ww->Integral();

  if(i==0) {
    bb_integral[index]=h_mjj_bb->Integral();
    qq_integral[index]=h_mjj_qq->Integral();
    cc_integral[index]=h_mjj_cc->Integral();
    radreturn_integral[index]=h_mjj_radreturn->Integral();
    zz_integral[index]=h_mjj_zz->Integral();
    hz_integral[index]=h_mjj_hz->Integral();
    ww_integral[index]=h_mjj_ww->Integral();
  }
  

  h_y23_bb->Rebin(10);
  h_y23_cc->Rebin(10);
  h_y23_qq->Rebin(10);
  h_y23_radreturn->Rebin(10);
  h_y23_zz->Rebin(10);
  h_y23_hz->Rebin(10);
  h_y23_ww->Rebin(10);

  
  h_K_bb->Rebin(10);
  h_K_cc->Rebin(10);
  h_K_qq->Rebin(10);
  h_K_radreturn->Rebin(10);
  h_K_zz->Rebin(10);
  h_K_hz->Rebin(10);
  h_K_ww->Rebin(10);

  h_thrust_bb->Rebin(10);
  h_thrust_cc->Rebin(10);
  h_thrust_qq->Rebin(10);
  h_thrust_radreturn->Rebin(10);
  h_thrust_zz->Rebin(10);
  h_thrust_hz->Rebin(10);
  h_thrust_ww->Rebin(10);

  TString cut_string= "";//Nocuts";
  /*  if(cuts==1) cut_string="$K_{reco}<35\\,GeV$";
  if(cuts==2) cut_string="$+ m_{j_{1},j_{2}}>130 \\,GeV$";
  if(cuts==3) cut_string="$+ E^{max}_{nPFO}<100 \\,GeV$";
  if(cuts==4) cut_string="$+ |cos(\\theta_{E^{max}_{nPFO}})|<0.95$";
  if(cuts==5) cut_string="mjets<90GeV";
  if(cuts==6) cut_string="$+ Thrust > 0.9$";
  if(cuts==11) cut_string="$>1\\,b-jet tagged$";
  if(cuts==12) cut_string="$2\\,b-jet tagged$";
  if(cuts==13) cut_string="$>1\\,b-jet tagged$";
  if(cuts==14) cut_string="$2\\,b-jet tagged$";*/

  //cout<< cut_string<<" & "<< bb_integral[index+1]<<" & "<<cc_integral[index+1]<<" & "<<qq_integral[index+1]<<" & "<<radreturn_integral[index+1]<<" & "<< hz_integral[index+1]<<" & "<< zz_integral[index+1]<<" & "<< ww_integral[index+1]<<" \\\\"<<endl;

  //cout<< cut_string<<" & "<<  h_mjj_bb->Integral()<<" & "<<h_mjj_cc->Integral()<<" & "<<h_mjj_qq->Integral()<<" & "<<h_mjj_radreturn->Integral()<<" & "<< h_mjj_hz->Integral()<<" & "<< h_mjj_zz->Integral()<<" & "<< h_mjj_ww->Integral()<<" \\\\"<<endl;
  
  //   cout<<std::setprecision(3)<< cut_string<<" & "<< bb_integral[index+1]<<" & "<<cc_integral[index+1]<<" & "<<qq_integral[index+1]<<" & "<<radreturn_integral[index+1]<<" & "<< hz_integral[index+1]<<" & "<< zz_integral[index+1]<<" & "<< ww_integral[index+1]<<" \\\\"<<endl;

  cout<<std::setprecision(3)<< cut_string<<" & "<< 100.*bb_integral[index+1]/bb_integral[0]<<"\\% & "<<100.*cc_integral[index+1]/cc_integral[0]<<"\\% & "<<100.*qq_integral[index+1]/qq_integral[0]<<"\\% & "<<100.*radreturn_integral[index+1]/radreturn_integral[0]<<"\\% & "<< 100.*hz_integral[index+1]/hz_integral[0]<<"\\% & "<< 100.*zz_integral[index+1]/zz_integral[0]<<"\\% & "<< 100.*ww_integral[index+1]/ww_integral[0]<<" \\\\"<<endl;

   // cout<<std::setprecision(3)<< cut_string<<" & "<< 100.*bb_integral[index+1]/bb_integral[index+1]<<" & "<<100.*cc_integral[index+1]/bb_integral[index+1]<<" & "<<100.*qq_integral[index+1]/bb_integral[index+1]<<" & "<<100.*radreturn_integral[index+1]/bb_integral[index+1]<<" & "<< 100.*hz_integral[index+1]/bb_integral[index+1]<<" & "<< 100.*zz_integral[index+1]/bb_integral[index+1]<<" & "<< 100.*ww_integral[index+1]/bb_integral[index+1]<<" \\\\"<<endl;

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.5);

  TCanvas * canvasacol = new TCanvas("canvas_y23","canvas_y23",800,800);
  canvasacol->cd(1);
  gPad->SetLogy();
    
  h_y23_bb->GetYaxis()->SetTitle("a.u. (normalized)");
  h_y23_bb->GetXaxis()->SetTitle("y_{23}");
  h_y23_bb->SetLineColor(4);
  h_y23_bb->GetYaxis()->SetRangeUser(10,h_y23_bb->GetMaximum()*10);
  h_y23_bb->GetXaxis()->SetRangeUser(0,0.1);
  h_y23_bb->DrawNormalized("histo");

  h_y23_qq->SetLineColor(1);
  h_y23_qq->DrawNormalized("histosame");
  h_y23_cc->SetLineStyle(2);
  h_y23_cc->DrawNormalized("histosame");
  h_y23_radreturn->SetLineColor(2);
  h_y23_radreturn->DrawNormalized("histosame");
  h_y23_ww->SetLineColor(5);
  h_y23_ww->DrawNormalized("histosame");
  h_y23_zz->SetLineColor(6);
  h_y23_zz->DrawNormalized("histosame");
  h_y23_hz->SetLineColor(7);
  h_y23_hz->DrawNormalized("histosame");

  Labels(i,pol);
  
  TLegend *leg1 = new TLegend(0.3,0.82,0.5,0.9);//(0.4,0.3,0.5,0.6);
  leg1->SetTextSize(0.035);
  leg1->AddEntry(h_y23_bb,"#font[42]{b#bar{b}}","l");
  leg1->AddEntry(h_y23_cc,"#font[42]{c#bar{c}}","l");
  leg1->AddEntry(h_y23_qq,"#font[42]{q#bar{q} (q=uds)}","l");
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();

  TLegend *leg2 = new TLegend(0.57,0.8,0.85,0.9);//(0.4,0.3,0.5,0.6);
  leg2->SetTextSize(0.035);
  leg2->AddEntry(h_y23_radreturn,"#font[42]{#gammaZ#rightarrow #gammaq#bar{q} (q=udscb)}","l");
  /* leg2->AddEntry(h_y23_hz,"#font[42]{HZ}","l");
  leg2->AddEntry(h_y23_zz,"#font[42]{ZZ}","l");
  leg2->AddEntry(h_y23_ww,"#font[42]{WW}","l");*/
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();
  
  canvasacol->Print(TString::Format("plots/y23_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));
  

  
  TCanvas * canvasK = new TCanvas("canvas_K","canvas_K",800,800);
  canvasK->cd(1);
  gPad->SetLogy();
    
  h_K_bb->GetYaxis()->SetTitle("a.u. (normalized)");
  h_K_bb->GetXaxis()->SetTitle("K_{reco} [GeV]");
  h_K_bb->SetLineColor(4);
  h_K_bb->GetYaxis()->SetRangeUser(10,h_K_bb->GetMaximum()*10);
  //  h_K_bb->GetYaxis()->SetRangeUser(0,h_K_bb->GetMaximum()*10);
  h_K_bb->GetXaxis()->SetRangeUser(0,125);
  h_K_bb->DrawNormalized("histo");

  h_K_qq->SetLineColor(1);
  h_K_qq->DrawNormalized("histosame");
  h_K_cc->SetLineStyle(2);
  h_K_cc->DrawNormalized("histosame");
  h_K_radreturn->SetLineColor(2);
  h_K_radreturn->DrawNormalized("histosame");
  h_K_ww->SetLineColor(5);
  h_K_ww->DrawNormalized("histosame");
  h_K_zz->SetLineColor(6);
  h_K_zz->DrawNormalized("histosame");
  h_K_hz->SetLineColor(7);
  h_K_hz->DrawNormalized("histosame");

  Labels(i,pol);
 
  leg1->Draw();
  leg2->Draw();
  
  canvasK->Print(TString::Format("plots/K_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));

  TCanvas * canvasthrust = new TCanvas("canvas_thrust","canvas_thrust",800,800);
  canvasthrust->cd(1);
  //gPad->SetLogy();
    
  h_thrust_bb->GetYaxis()->SetTitle("a.u. (normalized)");
  h_thrust_bb->GetXaxis()->SetTitle("Thrust");
  h_thrust_bb->SetLineColor(4);
  //  h_thrust_bb->GetYaxis()->SetRangeUser(10,h_thrust_bb->GetMaximum()*2);
  //  h_thrust_bb->GetYaxis()->SetRangeUser(0,h_thrust_bb->GetMaximum()*10);
  h_thrust_bb->GetXaxis()->SetRangeUser(0.6,1);
  h_thrust_bb->DrawNormalized("histo");

  h_thrust_qq->SetLineColor(1);
  h_thrust_qq->DrawNormalized("histosame");
  h_thrust_cc->SetLineStyle(2);
  h_thrust_cc->DrawNormalized("histosame");
  h_thrust_radreturn->SetLineColor(2);
  h_thrust_radreturn->DrawNormalized("histosame");
  h_thrust_ww->SetLineColor(5);
  h_thrust_ww->DrawNormalized("histosame");
  h_thrust_zz->SetLineColor(6);
  h_thrust_zz->DrawNormalized("histosame");
  h_thrust_hz->SetLineColor(7);
  h_thrust_hz->DrawNormalized("histosame");

  Labels(i,pol);

  leg1->Draw();
  leg2->Draw();
  
  canvasthrust->Print(TString::Format("plots/thrust_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));

  /*  TCanvas * canvascosthetagamma = new TCanvas("canvas_costhetagamma","canvas_costhetagamma",800,800);
  canvascosthetagamma->cd(1);
  //gPad->SetLogy();
    
  h_costhetagamma_bb->GetYaxis()->SetTitle("a.u. (normalized)");
  h_costhetagamma_bb->GetXaxis()->SetTitle("Costhetagamma");
  h_costhetagamma_bb->SetLineColor(4);
  h_costhetagamma_bb->GetYaxis()->SetRangeUser(10,h_costhetagamma_bb->GetMaximum()*10);
  //  h_costhetagamma_bb->GetYaxis()->SetRangeUser(0,h_costhetagamma_bb->GetMaximum()*10);
  h_costhetagamma_bb->GetXaxis()->SetRangeUser(-1.0,1.0);
  h_costhetagamma_bb->DrawNormalized("histo");

  h_costhetagamma_qq->SetLineColor(1);
  h_costhetagamma_qq->DrawNormalized("histosame");
  h_costhetagamma_cc->SetLineStyle(2);
  h_costhetagamma_cc->DrawNormalized("histosame");
  h_costhetagamma_radreturn->SetLineColor(2);
  h_costhetagamma_radreturn->DrawNormalized("histosame");
  // h_costhetagamma_ww->SetLineColor(5);
//  h_costhetagamma_ww->DrawNormalized("histosame");
 // h_costhetagamma_zz->SetLineColor(6);
 // h_costhetagamma_zz->DrawNormalized("histosame");
 // h_costhetagamma_hz->SetLineColor(7);
 // h_costhetagamma_hz->DrawNormalized("histosame");

  Labels(i,pol);
  
  leg1->Draw();
  leg2->Draw();
  */
  
  //  canvascosthetagamma->Print(TString::Format("plots/costhetagamma_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));

  TCanvas * canvasmjj = new TCanvas("canvas_mjj","canvas_mjj",800,800);
  canvasmjj->cd(1);
  //  gPad->SetLogy();
    
  h_mjj_bb->GetYaxis()->SetTitle("a.u. (normalized)");
  h_mjj_bb->GetXaxis()->SetTitle("m_{j_{1},j_{2}} [GeV]");
  h_mjj_bb->SetLineColor(4);
  h_mjj_bb->GetYaxis()->SetRangeUser(0,h_mjj_bb->GetMaximum()*2);
  //  h_mjj_bb->GetYaxis()->SetRangeUser(0,h_mjj_bb->GetMaximum()*10);
  //  h_mjj_bb->GetXaxis()->SetRangeUser(0,0.11);
  h_mjj_bb->DrawNormalized("histo");

  h_mjj_qq->SetLineColor(1);
  h_mjj_qq->DrawNormalized("histosame");
  h_mjj_cc->SetLineStyle(2);
  h_mjj_cc->DrawNormalized("histosame");
  h_mjj_radreturn->SetLineColor(2);
  h_mjj_radreturn->DrawNormalized("histosame");
  /*h_mjj_ww->SetLineColor(5);
  h_mjj_ww->DrawNormalized("histosame");
  h_mjj_zz->SetLineColor(6);
  h_mjj_zz->DrawNormalized("histosame");
  h_mjj_hz->SetLineColor(7);
  h_mjj_hz->DrawNormalized("histosame");*/

  Labels(i,pol);
  
  leg1->Draw();
  leg2->Draw();
  
  canvasmjj->Print(TString::Format("plots/mjj_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));


  TCanvas * canvascostheta = new TCanvas("canvas_costheta","canvas_costheta",800,800);
  canvascostheta->cd(1);
  //  gPad->SetLogy();
    
  h_costheta_bb->GetYaxis()->SetTitle("Entries / 0.05");
  h_costheta_bb->GetXaxis()->SetTitle("|cos #theta_{q}|");
  h_costheta_bb->SetLineColor(4);
  h_costheta_bb->GetYaxis()->SetRangeUser(0,h_costheta_bb->GetMaximum()*2);
  //  h_costheta_bb->GetYaxis()->SetRangeUser(0,h_costheta_bb->GetMaximum()*10);
  h_costheta_bb->GetXaxis()->SetRangeUser(0,150);
  h_costheta_bb->Draw("histo");

  h_costheta_qq->SetLineColor(1);
  h_costheta_qq->Draw("histosame");
  h_costheta_cc->SetLineStyle(2);
  h_costheta_cc->Draw("histosame");
  h_costheta_radreturn->SetLineColor(2);
  h_costheta_radreturn->Draw("histosame");
  h_costheta_ww->SetLineColor(5);
  h_costheta_ww->Draw("histosame");
  h_costheta_zz->SetLineColor(6);
  h_costheta_zz->Draw("histosame");
  h_costheta_hz->SetLineColor(7);
  h_costheta_hz->Draw("histosame");

  Labels(i,pol);

  leg1->Draw();
  leg2->Draw();
  
  // canvasegamma->Print(TString::Format("plots/egamma_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));*/

  TCanvas * canvasmj1_mj2 = new TCanvas("canvas_mj1_mj2","canvas_mj1_mj2",800,800);
  canvasmj1_mj2->cd(1);
  //  gPad->SetLogy();
    
  h_mj1_mj2_bb->GetYaxis()->SetTitle("a.u. (normalized)");
  h_mj1_mj2_bb->GetXaxis()->SetTitle("m_{j_{1}}+m_{j_{2}} [GeV]");
  h_mj1_mj2_bb->SetLineColor(4);
  h_mj1_mj2_bb->GetYaxis()->SetRangeUser(0,h_mj1_mj2_bb->GetMaximum()*2);
  //  h_mj1_mj2_bb->GetYaxis()->SetRangeUser(0,h_mj1_mj2_bb->GetMaximum()*10);
  h_mj1_mj2_bb->GetXaxis()->SetRangeUser(0,200);
  h_mj1_mj2_bb->DrawNormalized("histo");

  h_mj1_mj2_qq->SetLineColor(1);
  h_mj1_mj2_qq->DrawNormalized("histosame");
  h_mj1_mj2_cc->SetLineStyle(2);
  h_mj1_mj2_cc->DrawNormalized("histosame");
  h_mj1_mj2_radreturn->SetLineColor(2);
  h_mj1_mj2_radreturn->DrawNormalized("histosame");
  h_mj1_mj2_ww->SetLineColor(5);
  h_mj1_mj2_ww->DrawNormalized("histosame");
  h_mj1_mj2_zz->SetLineColor(6);
  h_mj1_mj2_zz->DrawNormalized("histosame");
  h_mj1_mj2_hz->SetLineColor(7);
  h_mj1_mj2_hz->DrawNormalized("histosame");

  Labels(i,pol);
  
  leg1->Draw();
  leg2->Draw();
  
  canvasmj1_mj2->Print(TString::Format("plots/mj1_mj2_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));
  

}

}
