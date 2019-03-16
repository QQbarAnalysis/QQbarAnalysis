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

void preselectioncuts() {

  cout<< "bb qq recoil ww zz hz "<<endl;

  for(int cuts=0; cuts<4; cuts++) {

  TString pol="eL";
  TString sel="_";//"_tight_";
  TString folder=TString::Format("../otuput//selection_cuts%i_",cuts);
  TString kt="l5_valencia1.4";//"_genkt";//"_tight_";
  
  TString filename = folder+"bbbar_"+kt+sel+"500GeV_"+pol+"_btag1_0.9_btag2_0.2.root";
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
  
  //Efficiency y23.
  float bb_integral=0;
  float qq_integral=0;
  float recoil_integral=0;

  for(int i=0; i<100; i++) {
    bb_integral+=h_y23_bb->GetBinContent(i+1);
    qq_integral+=h_y23_qq->GetBinContent(i+1);
    recoil_integral+=h_y23_recoil->GetBinContent(i+1);
 
  }
  cout<< "selection"<<cuts<<" "<< bb_integral<<" "<<qq_integral<<" "<<recoil_integral<<endl;

  
  SetQQbarStyle();
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

  canvas0->cd(4);
  TLegend *leg0 = new TLegend(0.2,0.2,0.9,0.9);
  leg0->AddEntry(h_y23_bb,"b#bar{b}","l");
  leg0->AddEntry(h_y23_qq,TString::Format("q#bar{q}, %0.1f",100.*qq_integral/bb_integral)+"%","l");
  leg0->AddEntry(h_y23_recoil,TString::Format("Z-recoil, %0.1f",100.*recoil_integral/bb_integral)+"%","l");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  canvas0->Update();
  canvas0->Print(TString::Format("../plots/cuts1_%s_%s_cuts%i.C",pol.Data(),kt.Data(),cuts));
  
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

  canvas->cd(4);
  TLegend *leg = new TLegend(0.2,0.2,0.9,0.9);
  leg->AddEntry(h_sphericity_bb,"b#bar{b}","l");
  leg->AddEntry(h_sphericity_qq,TString::Format("q#bar{q}, %0.1f",100.*qq_integral/bb_integral)+"%","l");
  leg->AddEntry(h_sphericity_recoil,TString::Format("Z-recoil, %0.1f",100.*recoil_integral/bb_integral)+"%","l");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  canvas->Update();
  canvas->Print(TString::Format("../plots/cuts2_%s_%s_cuts%i.C",pol.Data(),kt.Data(),cuts));

  float bb_integral2=0;
  float qq_integral2=0;
  float recoil_integral2=0;

  for(int i=0; i<100; i++) {
    if(h_mjj_bb->GetBinCenter(i+1)>180)  bb_integral2+=h_mjj_bb->GetBinContent(i+1);
    if(h_mjj_qq->GetBinCenter(i+1)>180)  qq_integral2+=h_mjj_qq->GetBinContent(i+1);
    if(h_mjj_recoil->GetBinCenter(i+1)>180)  recoil_integral2+=h_mjj_recoil->GetBinContent(i+1);
    // if(h_mjj_zz->GetBinCenter(i+1)>180)  zz_integral2+=h_mjj_zz->GetBinContent(i+1);
    // if(h_mjj_ww->GetBinCenter(i+1)>180)  ww_integral2+=h_mjj_ww->GetBinContent(i+1);
  }
  
}

}
