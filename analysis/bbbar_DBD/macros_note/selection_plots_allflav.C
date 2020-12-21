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
void Labels(int i=0, TString pol="eL", int j=1){

  QQBARLabel(0.86,0.952,"");
  if(i==0) QQBARLabel2(0.04,0.07, "[No Cuts]",kOrange+3);
  if(i==1) QQBARLabel2(0.04,0.07, "K_{reco}<35 GeV",kOrange+3);
  if(i==2) QQBARLabel2(0.04,0.07, "K_{reco}<35 GeV & m_{j_{1},j_{2}}>130 GeV",kOrange+3);
  if(i==3) {
    QQBARLabel2(0.04,0.075, "K_{reco}<35 GeV & m_{j_{1},j_{2}}>130 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& photon veto cuts",kOrange+3);
  }
  if(i==4) {
    QQBARLabel2(0.04,0.075, "K_{reco,geom}<35 GeV & m_{j_{1},j_{2}}>130 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& photon veto cuts & y_{23}<0.015",kOrange+3);
  }

  float x=0.25;
  if(j==2) x=0.16;
  if(pol=="eL")QQBARLabel2(x,0.965, "e_{L}^{-}e_{R}^{+}, #scale[0.7]{#int}L=250 fb^{-1}",kGray+2);
  if(pol=="eR")QQBARLabel2(x,0.965, "e_{R}^{-}e_{L}^{+}, #scale[0.7]{#int}L=250 fb^{-1}",kGray+2);
}



void selection_plots_allflav() {

 
    
  // for(int i=0; i<1; i++) {

    //  if(i==1) i=14;

    //    if(i==5) i=13;
  // int cuts=0;
  int i=0;
  
  int cuts=i;
    TString pol="eL";
    TString sel="_";//"_tight_";
    TString folder=TString::Format("../output_20200427/selection_cuts%i_",cuts);
    TString kt="genkt_restorer";//"_genkt";//"_tight_";
    
    TString filename = folder+"bbbar_genkt_restorer_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
    // filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";

    TFile *f = new TFile(filename);
    TH1F *h_mjj_bb = (TH1F*)f->Get("h_mjj_bb");
    TH1F *h_mj1_mj2_bb = (TH1F*)f->Get("h_mj1_mj2_bb");
    TH1F *h_y23_bb = (TH1F*)f->Get("h_y23_bb");
    TH1F *h_egamma_bb = (TH1F*)f->Get("h_egamma_bb");
    TH1F *h_K_bb = (TH1F*)f->Get("h_K_bb");
    TH1F *h_thrust_bb = (TH1F*)f->Get("h_thrust_bb");
    TH1F *h_costhetagamma_bb = (TH1F*)f->Get("h_costhetagamma_bb");
    
    TH1F *h_mjj_cc = (TH1F*)f->Get("h_mjj_cc");
    TH1F *h_mj1_mj2_cc = (TH1F*)f->Get("h_mj1_mj2_cc");
    TH1F *h_y23_cc = (TH1F*)f->Get("h_y23_cc");
    TH1F *h_egamma_cc = (TH1F*)f->Get("h_egamma_cc");
    TH1F *h_K_cc = (TH1F*)f->Get("h_K_cc");
    TH1F *h_thrust_cc = (TH1F*)f->Get("h_thrust_cc");
    TH1F *h_costhetagamma_cc = (TH1F*)f->Get("h_costhetagamma_cc");
    
    TH1F *h_mjj_qq = (TH1F*)f->Get("h_mjj_qq");
    TH1F *h_mj1_mj2_qq = (TH1F*)f->Get("h_mj1_mj2_qq");
    TH1F *h_y23_qq = (TH1F*)f->Get("h_y23_qq");
    TH1F *h_egamma_qq = (TH1F*)f->Get("h_egamma_qq");
    TH1F *h_K_qq = (TH1F*)f->Get("h_K_qq");
    TH1F *h_thrust_qq = (TH1F*)f->Get("h_thrust_qq");
    TH1F *h_costhetagamma_qq = (TH1F*)f->Get("h_costhetagamma_qq");
    
    if(pol=="eL" ) { 
    h_mjj_bb->Scale(250./266);
    h_mj1_mj2_bb->Scale(250./266);
    h_y23_bb->Scale(250./266);
    h_egamma_bb->Scale(250./266);
    h_K_bb->Scale(250./266);
    h_thrust_bb->Scale(250./266);
    h_costhetagamma_bb->Scale(250./266);

    h_mjj_cc->Scale(250./266);
    h_mj1_mj2_cc->Scale(250./266);
    h_y23_cc->Scale(250./266);
    h_egamma_cc->Scale(250./266);
    h_K_cc->Scale(250./266);
    h_thrust_cc->Scale(250./266);
    h_costhetagamma_cc->Scale(250./266);

    h_mjj_qq->Scale(250./266);
    h_mj1_mj2_qq->Scale(250./266);
    h_y23_qq->Scale(250./266);
    h_egamma_qq->Scale(250./266);
    h_K_qq->Scale(250./266);
    h_thrust_qq->Scale(250./266);
    h_costhetagamma_qq->Scale(250./266);    
    }

  if(pol=="eR" ) {
    h_mjj_bb->Scale(250./19.9);
    h_mj1_mj2_bb->Scale(250./19.9);
    h_y23_bb->Scale(250./19.9);
    h_egamma_bb->Scale(250./19.9);
    h_K_bb->Scale(250./19.9);
    h_thrust_bb->Scale(250./19.9);
    h_costhetagamma_bb->Scale(250./19.9);

    h_mjj_cc->Scale(250./19.9);
    h_mj1_mj2_cc->Scale(250./19.9);
    h_y23_cc->Scale(250./19.9);
    h_egamma_cc->Scale(250./19.9);
    h_K_cc->Scale(250./19.9);
    h_thrust_cc->Scale(250./19.9);
    h_costhetagamma_cc->Scale(250./19.9);

    h_mjj_qq->Scale(250./19.9);
    h_mj1_mj2_qq->Scale(250./19.9);
    h_y23_qq->Scale(250./19.9);
    h_egamma_qq->Scale(250./19.9);
    h_K_qq->Scale(250./19.9);
    h_thrust_qq->Scale(250./19.9);
    h_costhetagamma_qq->Scale(250./19.9);
  }


  // ----------------------------------------
  //filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
  TFile *f1 = new TFile(filename);

  TH1F *h_mjj_radreturn = (TH1F*)f1->Get("h_mjj_radreturn");
  TH1F *h_mj1_mj2_radreturn = (TH1F*)f1->Get("h_mj1_mj2_radreturn");
  TH1F *h_y23_radreturn = (TH1F*)f1->Get("h_y23_radreturn");
  TH1F *h_egamma_radreturn = (TH1F*)f1->Get("h_egamma_radreturn");
  TH1F *h_K_radreturn = (TH1F*)f1->Get("h_K_radreturn");
  TH1F *h_thrust_radreturn = (TH1F*)f1->Get("h_thrust_radreturn");
  TH1F *h_costhetagamma_radreturn = (TH1F*)f1->Get("h_costhetagamma_radreturn");

  if(pol=="eL" ) { 
    h_mjj_radreturn->Scale(250./266);
    h_mj1_mj2_radreturn->Scale(250./266);
    h_y23_radreturn->Scale(250./266);
    h_egamma_radreturn->Scale(250./266);
    h_K_radreturn->Scale(250./266);
    h_thrust_radreturn->Scale(250./266);
    h_costhetagamma_radreturn->Scale(250./266);
  }

  if(pol=="eR" ) {
    h_mjj_radreturn->Scale(250./19.9);
    h_mj1_mj2_radreturn->Scale(250./19.9);
    h_y23_radreturn->Scale(250./19.9);
    h_egamma_radreturn->Scale(250./19.9);
    h_K_radreturn->Scale(250./19.9);
    h_thrust_radreturn->Scale(250./19.9);
    h_costhetagamma_radreturn->Scale(250./19.9);
  }

  h_mjj_bb->Add(h_mjj_cc);
  h_mjj_bb->Add(h_mjj_qq);

  h_mj1_mj2_bb->Add(h_mj1_mj2_cc);
  h_mj1_mj2_bb->Add(h_mj1_mj2_qq);

  h_y23_bb->Add(h_y23_cc);
  h_y23_bb->Add(h_y23_qq);

  h_egamma_bb->Add(h_egamma_cc);
  h_egamma_bb->Add(h_egamma_qq);
 
  h_K_bb->Add(h_K_cc);
  h_K_bb->Add(h_K_qq);

  h_thrust_bb->Add(h_thrust_cc);
  h_thrust_bb->Add(h_thrust_qq);

  h_costhetagamma_bb->Add(h_costhetagamma_cc);
  h_costhetagamma_bb->Add(h_costhetagamma_qq);


  h_K_bb->Rebin(10);
  h_K_radreturn->Rebin(10);
 
  h_thrust_bb->Rebin(10);
  h_thrust_radreturn->Rebin(10);

 TFile *f2 = new TFile(folder+"bkg_"+kt+"_Kgamma35_WW"+sel+"250GeV_"+pol+".root");
  TH1F *h_mjj_ww = (TH1F*)f2->Get("h_mjj_bb");
  TH1F *h_mj1_mj2_ww = (TH1F*)f2->Get("h_mj1_mj2_bb");
  TH1F *h_y23_ww = (TH1F*)f2->Get("h_y23_bb");
  TH1F *h_egamma_ww = (TH1F*)f2->Get("h_egamma_bb");
  TH1F *h_K_ww = (TH1F*)f2->Get("h_K_bb");
  TH1F *h_thrust_ww = (TH1F*)f2->Get("h_thrust_bb");
  TH1F *h_costhetagamma_ww = (TH1F*)f2->Get("h_costhetagamma_bb");

  if(pol=="eL" ) {
    h_mjj_ww->Scale(250./72.2);
    h_mj1_mj2_ww->Scale(250./72.2);
    h_y23_ww->Scale(250./72.2);
    h_egamma_ww->Scale(250./72.2);
    h_K_ww->Scale(250./72.2);
    h_thrust_ww->Scale(250./72.2);
    h_costhetagamma_ww->Scale(250./72.2);
  }


  TFile *f3 = new TFile(folder+"bkg_"+kt+"_Kgamma35_ZZ"+sel+"250GeV_"+pol+".root");
  
  TH1F *h_mjj_zz = (TH1F*)f3->Get("h_mjj_bb");
  TH1F *h_mj1_mj2_zz = (TH1F*)f3->Get("h_mj1_mj2_bb");
  TH1F *h_y23_zz = (TH1F*)f3->Get("h_y23_bb");
  TH1F *h_egamma_zz = (TH1F*)f3->Get("h_egamma_bb");
  TH1F *h_K_zz = (TH1F*)f3->Get("h_K_bb");
  TH1F *h_thrust_zz = (TH1F*)f3->Get("h_thrust_bb");
  TH1F *h_costhetagamma_zz = (TH1F*)f3->Get("h_costhetagamma_bb");

  TFile *f4 = new TFile(folder+"bkg_"+kt+"_Kgamma35_HZ"+sel+"250GeV_"+pol+".root");
  TH1F *h_mjj_hz = (TH1F*)f4->Get("h_mjj_bb");
  TH1F *h_mj1_mj2_hz = (TH1F*)f4->Get("h_mj1_mj2_bb");
  TH1F *h_y23_hz = (TH1F*)f4->Get("h_y23_bb");
  TH1F *h_egamma_hz = (TH1F*)f4->Get("h_egamma_bb");
  TH1F *h_K_hz = (TH1F*)f4->Get("h_K_bb");
  TH1F *h_thrust_hz = (TH1F*)f4->Get("h_thrust_bb");
  TH1F *h_costhetagamma_hz = (TH1F*)f4->Get("h_costhetagamma_bb");

  if(pol=="eL" ) {
    h_mjj_hz->Scale(250./353.);
    h_mj1_mj2_hz->Scale(250./353.);
    h_y23_hz->Scale(250./353.);
    h_egamma_hz->Scale(250./353.);
    h_K_hz->Scale(250./353.);
    h_thrust_hz->Scale(250./353.);
    h_costhetagamma_hz->Scale(250./353.);
  }
  if(pol=="eR" ) {
    h_mjj_hz->Scale(250./550.);
    h_mj1_mj2_hz->Scale(250./550.);
    h_y23_hz->Scale(250./550.);
    h_egamma_hz->Scale(250./550.);
    h_K_hz->Scale(250./550.);
    h_thrust_hz->Scale(250./550.);
    h_costhetagamma_hz->Scale(250./550.);
  }
  
 h_K_ww->Rebin(10);
  h_K_zz->Rebin(10);
  h_K_hz->Rebin(10);

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.5);

  TGaxis::SetMaxDigits(3);

    
  TCanvas * canvas_y23 = new TCanvas("canvas_y23","canvas_y23",800,800);
  canvas_y23->cd(1);
  gPad->SetLogy();
    
  h_y23_bb->GetYaxis()->SetTitle("Entries / area ");
  h_y23_bb->GetXaxis()->SetTitle("y_{23}");
  h_y23_bb->SetLineColor(4);
  h_y23_bb->GetYaxis()->SetRangeUser(100,h_y23_bb->GetMaximum()*30);
  h_y23_bb->GetXaxis()->SetRangeUser(0,0.11);
  h_y23_bb->DrawNormalized("histo");
  h_y23_radreturn->SetLineColor(2);
  h_y23_radreturn->DrawNormalized("histosame");
  h_y23_ww->SetLineColor(kGreen+2);
  h_y23_ww->DrawNormalized("histosame");
  h_y23_zz->SetLineColor(6);
  h_y23_zz->DrawNormalized("histosame");
  h_y23_hz->SetLineColor(7);
  h_y23_hz->DrawNormalized("histosame");
  
  Labels(i,pol,2);
  
  TLegend *leg1 = new TLegend(0.3,0.83,0.6,0.93);//(0.4,0.3,0.5,0.6);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(h_y23_bb,"e^{-}e^{+}#rightarrow q#bar{q} (q=udcsb, E_{#gamma}<35GeV)","l");
  leg1->AddEntry(h_y23_radreturn,"e^{-}e^{+}#rightarrow q#bar{q} (q=udcsb, E_{#gamma}>35GeV)","l");
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();

  TLegend *leg2 = new TLegend(0.4,0.65,0.6,0.8);//(0.4,0.3,0.5,0.6);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->AddEntry(h_y23_hz,"e^{-}e^{+}#rightarrow HZ #rightarrow hadrons","l");
  leg2->AddEntry(h_y23_zz,"e^{-}e^{+}#rightarrow ZZ #rightarrow hadrons","l");
  leg2->AddEntry(h_y23_ww,"e^{-}e^{+}#rightarrow WW #rightarrow hadrons","l");
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();

  canvas_y23->Print(TString::Format("plots/Comparison_all_flav_y23_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));

    
  TCanvas * canvasK = new TCanvas("canvas_K","canvas_K",800,800);
  canvasK->cd(1);
  // gPad->SetLogy();
    
  h_K_bb->GetYaxis()->SetTitle("Entries / GeV");
  h_K_bb->GetXaxis()->SetTitle("K_{reco} [GeV]");
  h_K_bb->SetLineColor(4);
  h_K_bb->GetYaxis()->SetRangeUser(0,h_K_bb->GetMaximum()*3.5);
  h_K_bb->GetXaxis()->SetRangeUser(0,125);
  h_K_bb->Draw("histo");

  h_K_radreturn->SetLineColor(2);
  h_K_radreturn->Draw("histosame");
  
  /*  h_K_ww->SetLineColor(kGreen+2);
  h_K_ww->Draw("histosame");
  h_K_zz->SetLineColor(6);
  h_K_zz->Draw("histosame");
  h_K_hz->SetLineColor(7);
  h_K_hz->Draw("histosame");*/

  Labels(i,pol);

  TLegend *leg3 = new TLegend(0.2,0.73,0.5,0.83);//(0.4,0.3,0.5,0.6);
  leg3->SetTextSize(0.035);
  leg3->SetTextFont(42);
  leg3->AddEntry(h_K_bb,"e^{-}e^{+}#rightarrow q#bar{q} (q=udcsb, E_{#gamma}<35GeV)","l");
  leg3->AddEntry(h_K_radreturn,"e^{-}e^{+}#rightarrow q#bar{q} (q=udcsb, E_{#gamma}>35GeV)","l");
  leg3->SetFillStyle(0);
  leg3->SetLineWidth(0);
  leg3->SetLineColor(0);
  leg3->SetBorderSize(0);
  leg3->Draw();
  // leg2->Draw();

  canvasK->Print(TString::Format("plots/Comparison_all_flav_K_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));

  TCanvas * canvasmjj = new TCanvas("canvas_mjj","canvas_mjj",800,800);
  canvasmjj->cd(1);
  //  gPad->SetLogy();
    
  h_mjj_bb->GetYaxis()->SetTitle("Entries / 5 GeV");
  h_mjj_bb->GetXaxis()->SetTitle("m_{2jets} [GeV]");
  h_mjj_bb->SetLineColor(4);
  h_mjj_bb->GetYaxis()->SetRangeUser(0,h_mjj_bb->GetMaximum()*1.2);
  h_mjj_bb->GetXaxis()->SetRangeUser(0,300);
  h_mjj_bb->Draw("histo");

  h_mjj_radreturn->SetLineColor(2);
  h_mjj_radreturn->Draw("histosame");

  /* h_mjj_ww->SetLineColor(kGreen+2);
  h_mjj_ww->Draw("histosame");
  h_mjj_zz->SetLineColor(6);
  h_mjj_zz->Draw("histosame");
  h_mjj_hz->SetLineColor(7);
  h_mjj_hz->Draw("histosame");*/
  
  Labels(i,pol);
  
  leg3->Draw();
  // leg2->Draw();

  canvasmjj->Print(TString::Format("plots/Comparison_all_flav_mjj_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));



  TCanvas * canvasmj1_mj2 = new TCanvas("canvas_mj1_mj2","canvas_mj1_mj2",800,800);
  canvasmj1_mj2->cd(1);
  //  gPad->SetLogy();
    
  h_mj1_mj2_bb->GetYaxis()->SetTitle("Entries / area");
  h_mj1_mj2_bb->GetXaxis()->SetTitle("m_{j_{1}}+m_{j_{2}} [GeV]");
  h_mj1_mj2_bb->SetLineColor(4);
  h_mj1_mj2_bb->GetYaxis()->SetRangeUser(0,h_mj1_mj2_bb->GetMaximum()*2);
  h_mj1_mj2_bb->GetYaxis()->SetTitleOffset(1.5);
  h_mj1_mj2_bb->GetXaxis()->SetRangeUser(0,200);
  h_mj1_mj2_bb->DrawNormalized("histo");

  h_mj1_mj2_radreturn->SetLineColor(2);
  h_mj1_mj2_radreturn->DrawNormalized("histosame");

  h_mj1_mj2_ww->SetLineColor(kGreen+2);
  h_mj1_mj2_ww->DrawNormalized("histosame");
  h_mj1_mj2_zz->SetLineColor(6);
  h_mj1_mj2_zz->DrawNormalized("histosame");
  h_mj1_mj2_hz->SetLineColor(7);
  h_mj1_mj2_hz->DrawNormalized("histosame");
  
  Labels(i,pol,2);
  
  leg1->Draw();
  leg2->Draw();

  canvasmj1_mj2->Print(TString::Format("plots/Comparison_all_flav_mj1_mj2_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));


  //}

}
