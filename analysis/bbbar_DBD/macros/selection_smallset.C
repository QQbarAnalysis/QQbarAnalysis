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

void selection_smallset() {

  cout<< "bb qq recoil ww zz hz "<<endl;

  for(int cuts=0; cuts<18; cuts++) {

  TString pol="eR";
  TString sel="_";//"_tight_";
  TString folder=TString::Format("../output/kt/selection_cuts%i_",cuts);
  TString kt="genkt_restorer";//"_genkt";//"_tight_";
  
  TString filename = folder+"bbbar_"+kt+sel+"250GeV_"+pol+"_btag1_0.9_btag2_0.2.root";
  cout<<filename<<endl;
  TFile *f = new TFile(filename);

  TH1F *h_mjj_bb = (TH1F*)f->Get("h_mjj_bb");
  TH1F *h_mj1_mj2_bb = (TH1F*)f->Get("h_mj1_mj2_bb");
  TH1F *h_y12_bb = (TH1F*)f->Get("h_y12_bb");
  TH1F *h_y23_bb = (TH1F*)f->Get("h_y23_bb");
  TH1F *h_egamma_bb = (TH1F*)f->Get("h_egamma_bb");
  TH1F *h_oblateness_bb = (TH1F*)f->Get("h_oblateness_bb");
  TH1F *h_sphericity_bb = (TH1F*)f->Get("h_sphericity_bb");

  TH1F *h_mjj_qq = (TH1F*)f->Get("h_mjj_qq");
  TH1F *h_mj1_mj2_qq = (TH1F*)f->Get("h_mj1_mj2_qq");
  TH1F *h_y12_qq = (TH1F*)f->Get("h_y12_qq");
  TH1F *h_y23_qq = (TH1F*)f->Get("h_y23_qq");
  TH1F *h_egamma_qq = (TH1F*)f->Get("h_egamma_qq");
  TH1F *h_oblateness_qq = (TH1F*)f->Get("h_oblateness_qq");
  TH1F *h_sphericity_qq = (TH1F*)f->Get("h_sphericity_qq");

  TH1F *h_mjj_recoil = (TH1F*)f->Get("h_mjj_recoil");
  TH1F *h_mj1_mj2_recoil = (TH1F*)f->Get("h_mj1_mj2_recoil");
  TH1F *h_y12_recoil = (TH1F*)f->Get("h_y12_recoil");
  TH1F *h_y23_recoil = (TH1F*)f->Get("h_y23_recoil");
  TH1F *h_egamma_recoil = (TH1F*)f->Get("h_egamma_recoil");
  TH1F *h_oblateness_recoil = (TH1F*)f->Get("h_oblateness_recoil");
  TH1F *h_sphericity_recoil = (TH1F*)f->Get("h_sphericity_recoil");
  
  if(pol=="eL" ) { 
    h_mjj_bb->Scale(250./266.5);
    h_mj1_mj2_bb->Scale(250./266.5);
    h_y23_bb->Scale(250./266.5);
    h_egamma_bb->Scale(250./266.5);
    h_oblateness_bb->Scale(250./266.5);

    h_mjj_qq->Scale(250./266.5);
    h_mj1_mj2_qq->Scale(250./266.5);
    h_y23_qq->Scale(250./266.5);
    h_egamma_qq->Scale(250./266.5);
    h_oblateness_qq->Scale(250./266.5);

    h_mjj_recoil->Scale(250./266.5);
    h_mj1_mj2_recoil->Scale(250./266.5);
    h_y23_recoil->Scale(250./266.5);
    h_egamma_recoil->Scale(250./266.5);
    h_oblateness_recoil->Scale(250./266.5);
  }

  if(pol=="eR" ) { 
    h_mjj_bb->Scale(250./276.9);
    h_mj1_mj2_bb->Scale(250./276.9);
    h_y23_bb->Scale(250./276.9);
    h_egamma_bb->Scale(250./276.9);
    h_oblateness_bb->Scale(250./276.9);

    h_mjj_qq->Scale(250./276.9);
    h_mj1_mj2_qq->Scale(250./276.9);
    h_y23_qq->Scale(250./276.9);
    h_egamma_qq->Scale(250./276.9);
    h_oblateness_qq->Scale(250./276.9);

    h_mjj_recoil->Scale(250./276.9);
    h_mj1_mj2_recoil->Scale(250./276.9);
    h_y23_recoil->Scale(250./276.9);
    h_egamma_recoil->Scale(250./276.9);
    h_oblateness_recoil->Scale(250./276.9);
  }
  
  TFile *f2 = new TFile(folder+"bkg_"+kt+"_WW"+sel+"250GeV_"+pol+"_btag1_0.9_btag2_0.2.root");
  
  TH1F *h_mjj_ww = (TH1F*)f2->Get("h_mjj_bb");
  TH1F *h_mj1_mj2_ww = (TH1F*)f2->Get("h_mj1_mj2_bb");
  TH1F *h_y12_ww = (TH1F*)f2->Get("h_y12_bb");
  TH1F *h_y23_ww = (TH1F*)f2->Get("h_y23_bb");
  TH1F *h_egamma_ww = (TH1F*)f2->Get("h_egamma_bb");
  TH1F *h_oblateness_ww = (TH1F*)f2->Get("h_oblateness_bb");
  TH1F *h_sphericity_ww = (TH1F*)f2->Get("h_sphericity_bb");
  if(pol=="eL" ) {
    h_mjj_ww->Scale(250./72.2);
    h_mj1_mj2_ww->Scale(250./72.2);
    h_y23_ww->Scale(250./72.2);
    h_egamma_ww->Scale(250./72.2);
    h_oblateness_ww->Scale(250./72.2);
  }

  TFile *f3 = new TFile(folder+"bkg_"+kt+"_ZZ"+sel+"250GeV_"+pol+"_btag1_0.9_btag2_0.2.root");
  
  TH1F *h_mjj_zz = (TH1F*)f3->Get("h_mjj_bb");
  TH1F *h_mj1_mj2_zz = (TH1F*)f3->Get("h_mj1_mj2_bb");
  TH1F *h_y12_zz = (TH1F*)f3->Get("h_y12_bb");
  TH1F *h_y23_zz = (TH1F*)f3->Get("h_y23_bb");
  TH1F *h_egamma_zz = (TH1F*)f3->Get("h_egamma_bb");
  TH1F *h_oblateness_zz = (TH1F*)f3->Get("h_oblateness_bb");
  TH1F *h_sphericity_zz = (TH1F*)f3->Get("h_sphericity_bb");
  /* h_mjj_zz->Scale(250./1000.);
  h_mj1_mj2_zz->Scale(250./1000.);
  h_y23_zz->Scale(250./1000.);
  h_egamma_zz->Scale(250./1000.);
  h_oblateness_zz->Scale(250./1000.);*/
  
  TFile *f4 = new TFile(folder+"bkg_"+kt+"_HZ"+sel+"250GeV_"+pol+"_btag1_0.9_btag2_0.2.root");
  
  TH1F *h_mjj_hz = (TH1F*)f4->Get("h_mjj_bb");
  TH1F *h_mj1_mj2_hz = (TH1F*)f4->Get("h_mj1_mj2_bb");
  TH1F *h_y12_hz = (TH1F*)f4->Get("h_y12_bb");
  TH1F *h_y23_hz = (TH1F*)f4->Get("h_y23_bb");
  TH1F *h_egamma_hz = (TH1F*)f4->Get("h_egamma_bb");
  TH1F *h_oblateness_hz = (TH1F*)f4->Get("h_oblateness_bb");
  TH1F *h_sphericity_hz = (TH1F*)f4->Get("h_sphericity_bb");

  h_mjj_hz->Scale(250./1000.);
  h_mj1_mj2_hz->Scale(250./1000.);
  h_y23_hz->Scale(250./1000.);
  h_egamma_hz->Scale(250./1000.);
  h_oblateness_hz->Scale(250./1000.);

  //Efficiency y23.
  float bb_integral=0;
  float qq_integral=0;
  float recoil_integral=0;
  float zz_integral=0;
  float ww_integral=0;
  float hz_integral=0;

  for(int i=0; i<100; i++) {
    bb_integral+=h_y23_bb->GetBinContent(i+1);
    qq_integral+=h_y23_qq->GetBinContent(i+1);
    recoil_integral+=h_y23_recoil->GetBinContent(i+1);
    zz_integral+=h_y23_zz->GetBinContent(i+1);
    hz_integral+=h_y23_hz->GetBinContent(i+1);
    ww_integral+=h_y23_ww->GetBinContent(i+1);
  }
  cout<< "selection"<<cuts<<" "<< bb_integral<<" "<<qq_integral<<" "<<recoil_integral<<" "<< ww_integral<<" "<< zz_integral<<" "<< hz_integral<<endl;
  // else cout<< "selection"<<cuts<<" "<< bb_integral<<" "<<qq_integral<<" "<<recoil_integral<<" "<< ww_integral<<" "<< zz_integral<<" "<< 0<<endl;
  //  cout<< bb_integral<<endl;
  //cout<< qq_integral<<" "<<100.*qq_integral/bb_integral<<"%"<<endl;
  //cout<< recoil_integral<<" "<<100.*recoil_integral/bb_integral<<"%"<<endl;
  //cout<< ww_integral<<" "<<100.*ww_integral/bb_integral<<"%"<<endl;
  //cout<< zz_integral<<" "<<100.*zz_integral/bb_integral<<"%"<<endl;
  //cout<< hz_integral<<" "<<100.*hz_integral/bb_integral<<"%"<<endl;
  
  SetIrlesStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);
  
  TCanvas * canvas0 = new TCanvas("canvas_0","canvas_0",1200,800);
  canvas0->Divide(2,2);
  canvas0->cd(1);
  gPad->SetGridy();
  gPad->SetGridx();
  gPad->SetLogy();
  
  h_y23_bb->SetTitle("");
  h_y23_bb->GetYaxis()->SetTitle("entries");
  h_y23_bb->GetXaxis()->SetTitle("y23");
  h_y23_bb->SetLineColor(4);
  h_y23_bb->Draw("histo");

  h_y23_qq->SetLineColor(1);
  h_y23_qq->Draw("histosame");
  h_y23_recoil->SetLineColor(2);
  h_y23_recoil->Draw("histosame");
  h_y23_ww->SetLineColor(5);
  h_y23_ww->Draw("histosame");
  h_y23_zz->SetLineColor(6);
  h_y23_zz->Draw("histosame");
  h_y23_hz->SetLineColor(7);
  // 
  h_y23_hz->Draw("histosame");
  
  canvas0->cd(2);
  gPad->SetGridy();
  gPad->SetGridx();
  gPad->SetLogy();
  h_y12_bb->SetTitle("");
  h_y12_bb->GetYaxis()->SetTitle("entries");
  h_y12_bb->GetXaxis()->SetTitle("y12");
  h_y12_bb->GetXaxis()->SetRangeUser(0,160);
  h_y12_bb->SetLineColor(4);
  h_y12_bb->Draw("histo");

  h_y12_qq->SetLineColor(1);
  h_y12_qq->Draw("histosame");
  h_y12_recoil->SetLineColor(2);
  h_y12_recoil->Draw("histosame");
  h_y12_ww->SetLineColor(5);
  h_y12_ww->Draw("histosame");
  h_y12_zz->SetLineColor(6);
  h_y12_zz->Draw("histosame");
  h_y12_hz->SetLineColor(7);
  h_y12_hz->Draw("histosame");

  canvas0->cd(3);
  gPad->SetGridy();
  gPad->SetGridx();
  gPad->SetLogy();
  h_egamma_bb->SetTitle("");
  h_egamma_bb->GetYaxis()->SetTitle("entries");
  h_egamma_bb->GetXaxis()->SetTitle("E_{#gamma} [GeV]");
  h_egamma_bb->GetXaxis()->SetRangeUser(0,160);
  h_egamma_bb->SetLineColor(4);
  h_egamma_bb->Draw("histo");

  h_egamma_qq->SetLineColor(1);
  h_egamma_qq->Draw("histosame");
  h_egamma_recoil->SetLineColor(2);
  h_egamma_recoil->Draw("histosame");
  h_egamma_ww->SetLineColor(5);
  h_egamma_ww->Draw("histosame");
  h_egamma_zz->SetLineColor(6);
  h_egamma_zz->Draw("histosame");
  h_egamma_hz->SetLineColor(7);
  h_egamma_hz->Draw("histosame");

  canvas0->cd(4);
  TLegend *leg0 = new TLegend(0.2,0.2,0.9,0.9);
  leg0->AddEntry(h_y23_bb,"b#bar{b}","l");
  leg0->AddEntry(h_y23_qq,TString::Format("q#bar{q}, %0.1f",100.*qq_integral/bb_integral)+"%","l");
  leg0->AddEntry(h_y23_recoil,TString::Format("Z-recoil, %0.1f",100.*recoil_integral/bb_integral)+"%","l");
  leg0->AddEntry(h_y23_zz,TString::Format("ZZ, %0.1f",100.*zz_integral/bb_integral)+"%","l");
  leg0->AddEntry(h_y23_ww,TString::Format("WW, %0.1f",100.*ww_integral/bb_integral)+"%","l");
  leg0->AddEntry(h_y23_hz,TString::Format("HZ, %0.1f",100.*hz_integral/bb_integral)+"%","l");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  canvas0->Print(TString::Format("canvas0_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));
  
  TCanvas * canvas = new TCanvas(folder+sel,folder+sel,1200,800);
  canvas->Divide(2,2);
  
  canvas->cd(1);
  gPad->SetGridy();
  gPad->SetGridx();
  gPad->SetLogy();
  
  h_mjj_bb->SetTitle("");
  h_mjj_bb->GetYaxis()->SetTitle("entries");
  h_mjj_bb->GetXaxis()->SetTitle("m(j_{1}j_{2}) [GeV]");
  h_mjj_bb->SetLineColor(4);
  h_mjj_bb->Draw("histo");

  h_mjj_qq->SetLineColor(1);
  h_mjj_qq->Draw("histosame");
  h_mjj_recoil->SetLineColor(2);
  h_mjj_recoil->Draw("histosame");
  h_mjj_ww->SetLineColor(5);
  h_mjj_ww->Draw("histosame");
  h_mjj_zz->SetLineColor(6);
  h_mjj_zz->Draw("histosame");
  h_mjj_hz->SetLineColor(7);
  h_mjj_hz->Draw("histosame");
  
  canvas->cd(2);
  gPad->SetGridy();
  gPad->SetGridx();
  gPad->SetLogy();
  h_mj1_mj2_bb->SetTitle("");
  h_mj1_mj2_bb->GetYaxis()->SetTitle("entries");
  h_mj1_mj2_bb->GetXaxis()->SetTitle("m(j_{1})+m(j_{2}) [GeV]");
  h_mj1_mj2_bb->GetXaxis()->SetRangeUser(0,300);
  h_mj1_mj2_bb->SetLineColor(4);
  h_mj1_mj2_bb->Draw("histo");

  h_mj1_mj2_qq->SetLineColor(1);
  h_mj1_mj2_qq->Draw("histosame");
  h_mj1_mj2_recoil->SetLineColor(2);
  h_mj1_mj2_recoil->Draw("histosame");
  h_mj1_mj2_ww->SetLineColor(5);
  h_mj1_mj2_ww->Draw("histosame");
  h_mj1_mj2_zz->SetLineColor(6);
  h_mj1_mj2_zz->Draw("histosame");
  h_mj1_mj2_hz->SetLineColor(7);
  h_mj1_mj2_hz->Draw("histosame");
  
  canvas->cd(3);
  gPad->SetGridy();
  gPad->SetGridx();
  gPad->SetLogy();
  h_sphericity_bb->SetTitle("");
  h_sphericity_bb->GetYaxis()->SetTitle("entries");
  h_sphericity_bb->GetXaxis()->SetTitle("sphericity [no units]");
  h_sphericity_bb->SetLineColor(4);
  h_sphericity_bb->Draw("histo");

  h_sphericity_qq->SetLineColor(1);
  h_sphericity_qq->Draw("histosame");
  h_sphericity_recoil->SetLineColor(2);
  h_sphericity_recoil->Draw("histosame");
  h_sphericity_ww->SetLineColor(5);
  h_sphericity_ww->Draw("histosame");
  h_sphericity_zz->SetLineColor(6);
  h_sphericity_zz->Draw("histosame");
  h_sphericity_hz->SetLineColor(7);
  h_sphericity_hz->Draw("histosame");

  canvas->cd(4);
  TLegend *leg = new TLegend(0.2,0.2,0.9,0.9);
  leg->AddEntry(h_sphericity_bb,"b#bar{b}","l");
  leg->AddEntry(h_sphericity_qq,TString::Format("q#bar{q}, %0.1f",100.*qq_integral/bb_integral)+"%","l");
  leg->AddEntry(h_sphericity_recoil,TString::Format("Z-recoil, %0.1f",100.*recoil_integral/bb_integral)+"%","l");
  leg->AddEntry(h_sphericity_zz,TString::Format("ZZ, %0.1f",100.*zz_integral/bb_integral)+"%","l");
  leg->AddEntry(h_sphericity_ww,TString::Format("WW, %0.1f",100.*ww_integral/bb_integral)+"%","l");
  leg->AddEntry(h_sphericity_hz,TString::Format("HZ, %0.1f",100.*hz_integral/bb_integral)+"%","l");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  canvas->Print(TString::Format("canvas1_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));



  // float bb_integral2=0;
  // float qq_integral2=0;
  // float recoil_integral2=0;
  // float zz_integral2=0;
  // float ww_integral2=0;

  // for(int i=0; i<100; i++) {
  //   if(h_mjj_bb->GetBinCenter(i+1)>180)  bb_integral2+=h_mjj_bb->GetBinContent(i+1);
  //   if(h_mjj_qq->GetBinCenter(i+1)>180)  qq_integral2+=h_mjj_qq->GetBinContent(i+1);
  //   if(h_mjj_recoil->GetBinCenter(i+1)>180)  recoil_integral2+=h_mjj_recoil->GetBinContent(i+1);
  //   if(h_mjj_zz->GetBinCenter(i+1)>180)  zz_integral2+=h_mjj_zz->GetBinContent(i+1);
  //   if(h_mjj_ww->GetBinCenter(i+1)>180)  ww_integral2+=h_mjj_ww->GetBinContent(i+1);
  // }
  
  // cout<< " after a cut in m(jj) of 180 "<<endl;
  // cout<< "bb: "<<bb_integral2<<" "<<100*bb_integral2/bb_integral<<"%"<<endl;
  // cout<< "qq: "<<100.*qq_integral2/bb_integral2<<"%"<<endl;
  // cout<< "recoil: "<<100.*recoil_integral2/bb_integral2<<"%"<<endl;
  // cout<< "ww: "<<100.*ww_integral2/bb_integral2<<"%"<<endl;
  // cout<< "zz: "<<100.*zz_integral2/bb_integral2<<"%"<<endl;

  // bb_integral2=0;
  // qq_integral2=0;
  // recoil_integral2=0;
  // zz_integral2=0;
  // ww_integral2=0;

  // for(int i=0; i<100; i++) {
  //   if(h_sphericity_bb->GetBinCenter(i+1)<0.18)  bb_integral2+=h_sphericity_bb->GetBinContent(i+1);
  //   if(h_sphericity_qq->GetBinCenter(i+1)<0.18)  qq_integral2+=h_sphericity_qq->GetBinContent(i+1);
  //   if(h_sphericity_recoil->GetBinCenter(i+1)<0.18)  recoil_integral2+=h_sphericity_recoil->GetBinContent(i+1);
  //   if(h_sphericity_zz->GetBinCenter(i+1)<0.18)  zz_integral2+=h_sphericity_zz->GetBinContent(i+1);
  //   if(h_sphericity_ww->GetBinCenter(i+1)<0.18)  ww_integral2+=h_sphericity_ww->GetBinContent(i+1);
  // }

  // bb_integral2=0;
  // qq_integral2=0;
  // recoil_integral2=0;
  // zz_integral2=0;
  // ww_integral2=0;

  // for(int i=0; i<100; i++) {
  //   if(h_egamma_bb->GetBinCenter(i+1)<40)  bb_integral2+=h_egamma_bb->GetBinContent(i+1);
  //   if(h_egamma_qq->GetBinCenter(i+1)<40)  qq_integral2+=h_egamma_qq->GetBinContent(i+1);
  //   if(h_egamma_recoil->GetBinCenter(i+1)<40)  recoil_integral2+=h_egamma_recoil->GetBinContent(i+1);
  //   if(h_egamma_zz->GetBinCenter(i+1)<40)  zz_integral2+=h_egamma_zz->GetBinContent(i+1);
  //   if(h_egamma_ww->GetBinCenter(i+1)<40)  ww_integral2+=h_egamma_ww->GetBinContent(i+1);
  // }
  
  // cout<< " after a cut in egamma of 40"<<endl;
  // cout<< "bb: "<<bb_integral2<<" "<<100*bb_integral2/bb_integral<<"%"<<endl;
  // cout<< "qq: "<<100.*qq_integral2/bb_integral2<<"%"<<endl;
  // cout<< "recoil: "<<100.*recoil_integral2/bb_integral2<<"%"<<endl;
  // cout<< "ww: "<<100.*ww_integral2/bb_integral2<<"%"<<endl;
  // cout<< "zz: "<<100.*zz_integral2/bb_integral2<<"%"<<endl;

  // bb_integral2=0;
  // qq_integral2=0;
  // recoil_integral2=0;
  // zz_integral2=0;
  // ww_integral2=0;

  // for(int i=0; i<100; i++) {
  //   if(h_sphericity_bb->GetBinCenter(i+1)<0.18)  bb_integral2+=h_sphericity_bb->GetBinContent(i+1);
  //   if(h_sphericity_qq->GetBinCenter(i+1)<0.18)  qq_integral2+=h_sphericity_qq->GetBinContent(i+1);
  //   if(h_sphericity_recoil->GetBinCenter(i+1)<0.18)  recoil_integral2+=h_sphericity_recoil->GetBinContent(i+1);
  //   if(h_sphericity_zz->GetBinCenter(i+1)<0.18)  zz_integral2+=h_sphericity_zz->GetBinContent(i+1);
  //   if(h_sphericity_ww->GetBinCenter(i+1)<0.18)  ww_integral2+=h_sphericity_ww->GetBinContent(i+1);
  // }
  
  // cout<< " after a cut in sphericity of 0.18 "<<endl;
  // cout<< "bb: "<<bb_integral2<<" "<<100*bb_integral2/bb_integral<<"%"<<endl;
  // cout<< "qq: "<<100.*qq_integral2/bb_integral2<<"%"<<endl;
  // cout<< "recoil: "<<100.*recoil_integral2/bb_integral2<<"%"<<endl;
  // cout<< "ww: "<<100.*ww_integral2/bb_integral2<<"%"<<endl;
  // cout<< "zz: "<<100.*zz_integral2/bb_integral2<<"%"<<endl;


  // bb_integral2=0;
  // qq_integral2=0;
  // recoil_integral2=0;
  // zz_integral2=0;
  // ww_integral2=0;

  // for(int i=0; i<100; i++) {
  //   if(h_sphericity_bb->GetBinCenter(i+1)<0.03)  bb_integral2+=h_sphericity_bb->GetBinContent(i+1);
  //   if(h_sphericity_qq->GetBinCenter(i+1)<0.03)  qq_integral2+=h_sphericity_qq->GetBinContent(i+1);
  //   if(h_sphericity_recoil->GetBinCenter(i+1)<0.03)  recoil_integral2+=h_sphericity_recoil->GetBinContent(i+1);
  //   if(h_sphericity_zz->GetBinCenter(i+1)<0.03)  zz_integral2+=h_sphericity_zz->GetBinContent(i+1);
  //   if(h_sphericity_ww->GetBinCenter(i+1)<0.03)  ww_integral2+=h_sphericity_ww->GetBinContent(i+1);
  // }
  
  // cout<< " after a cut in sphericity of 0.03 "<<endl;
  // cout<< "bb: "<<bb_integral2<<" "<<100*bb_integral2/bb_integral<<"%"<<endl;
  // cout<< "qq: "<<100.*qq_integral2/bb_integral2<<"%"<<endl;
  // cout<< "recoil: "<<100.*recoil_integral2/bb_integral2<<"%"<<endl;
  // cout<< "ww: "<<100.*ww_integral2/bb_integral2<<"%"<<endl;
  // cout<< "zz: "<<100.*zz_integral2/bb_integral2<<"%"<<endl;

  
  // bb_integral2=0;
  // qq_integral2=0;
  // recoil_integral2=0;
  // zz_integral2=0;
  // ww_integral2=0;

  // for(int i=0; i<100; i++) {
  //   if(h_mj1_mj2_bb->GetBinCenter(i+1)<120)  bb_integral2+=h_mj1_mj2_bb->GetBinContent(i+1);
  //   if(h_mj1_mj2_qq->GetBinCenter(i+1)<120)  qq_integral2+=h_mj1_mj2_qq->GetBinContent(i+1);
  //   if(h_mj1_mj2_recoil->GetBinCenter(i+1)<120)  recoil_integral2+=h_mj1_mj2_recoil->GetBinContent(i+1);
  //   if(h_mj1_mj2_zz->GetBinCenter(i+1)<120)  zz_integral2+=h_mj1_mj2_zz->GetBinContent(i+1);
  //   if(h_mj1_mj2_ww->GetBinCenter(i+1)<120)  ww_integral2+=h_mj1_mj2_ww->GetBinContent(i+1);
  // }
  
  // cout<< " after a cut in m1+m2 of 120 "<<endl;
  // cout<< "bb: "<<bb_integral2<<" "<<100*bb_integral2/bb_integral<<"%"<<endl;
  // cout<< "qq: "<<100.*qq_integral2/bb_integral2<<"%"<<endl;
  // cout<< "recoil: "<<100.*recoil_integral2/bb_integral2<<"%"<<endl;
  // cout<< "ww: "<<100.*ww_integral2/bb_integral2<<"%"<<endl;
  // cout<< "zz: "<<100.*zz_integral2/bb_integral2<<"%"<<endl;
}

}
