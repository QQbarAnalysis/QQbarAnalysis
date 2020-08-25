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


void R3bl_plots() {

  TString folder="./";

  TString filename = folder+"output_y23_inclusive_signal.root";
  TFile *f = new TFile(filename);

  TGraphErrors *R3b_ps = (TGraphErrors*)f->Get("R3b_PS_step0");
  TGraphErrors *R3l_ps = (TGraphErrors*)f->Get("R3l_PS_step0");
  TGraphErrors *R3bl_ps = (TGraphErrors*)f->Get("R3bl_PS_step0");

  TGraphErrors *R3b_reco = (TGraphErrors*)f->Get("R3b_reco_step3");
  TGraphErrors *R3l_reco = (TGraphErrors*)f->Get("R3l_reco_step3");
  TGraphErrors *R3bl_reco = (TGraphErrors*)f->Get("R3bl_reco_step3");

  filename = folder+"output_y23_inclusive_cambridge_signal.root";
  f = new TFile(filename);

  TGraphErrors *R3b_ps_cambridge = (TGraphErrors*)f->Get("R3b_PS_step0");
  TGraphErrors *R3l_ps_cambridge = (TGraphErrors*)f->Get("R3l_PS_step0");
  TGraphErrors *R3bl_ps_cambridge = (TGraphErrors*)f->Get("R3bl_PS_step0");

  TGraphErrors *R3b_reco_cambridge = (TGraphErrors*)f->Get("R3b_reco_step3");
  TGraphErrors *R3l_reco_cambridge = (TGraphErrors*)f->Get("R3l_reco_step3");
  TGraphErrors *R3bl_reco_cambridge = (TGraphErrors*)f->Get("R3bl_reco_step3");

  TGraphErrors *R3b_reco0_cambridge = (TGraphErrors*)f->Get("R3b_reco_step0");
  TGraphErrors *R3l_reco0_cambridge = (TGraphErrors*)f->Get("R3l_reco_step0");
  TGraphErrors *R3bl_reco0_cambridge = (TGraphErrors*)f->Get("R3bl_reco_step0");

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.5);
  // TGaxis::SetMaxDigits(2); 


  TCanvas * canvas1 = new TCanvas("R3b","R3b",800,800);
  canvas1->cd(1);
  //  gPad->SetLogy();

  R3b_ps->GetYaxis()->SetTitle("R_{3}^{b}");
  R3b_ps->GetYaxis()->SetRangeUser(0,1);
  R3b_ps->GetXaxis()->SetTitle("y_{cut}");
  R3b_ps->SetLineColor(2);
  R3b_ps->SetLineWidth(3);
  R3b_ps->SetLineStyle(1);
  R3b_ps->Draw("ac");

  R3b_ps_cambridge->SetLineColor(4);
  R3b_ps_cambridge->SetLineWidth(3);
  R3b_ps_cambridge->SetLineStyle(1);
  R3b_ps_cambridge->Draw("c");

  /* R3b_reco->SetLineColor(2);
  R3b_reco->SetLineWidth(2);
  R3b_reco->SetLineStyle(2);
  R3b_reco->Draw("c");

  R3b_reco_cambridge->SetLineColor(4);
  R3b_reco_cambridge->SetLineWidth(2);
  R3b_reco_cambridge->SetLineStyle(2);
  R3b_reco_cambridge->Draw("c");*/

  
  TLegend *leg1 = new TLegend(0.4,0.7,0.65,0.85);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(R3b_ps,"PS - Durham","l");
  leg1->AddEntry(R3b_ps_cambridge,"PS - Cambridge","l");
  //leg1->AddEntry(R3b_reco,"Reco (no cuts) - Durham","l");
  //leg1->AddEntry(R3b_reco_cambridge,"Reco (no cuts) - Cambridge","l");
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  //  leg1->SetShadowColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();

  TCanvas * canvas2 = new TCanvas("R3l","R3l",800,800);
  canvas2->cd(1);
  //  gPad->SetLogy();

  R3l_ps->GetYaxis()->SetTitle("R_{3}^{l}");
  R3l_ps->GetYaxis()->SetRangeUser(0,1);
  R3l_ps->GetXaxis()->SetTitle("y_{cut}");
  R3l_ps->SetLineColor(2);
  R3l_ps->SetLineWidth(3);
  R3l_ps->SetLineStyle(1);
  R3l_ps->Draw("ac");

  R3l_ps_cambridge->SetLineColor(4);
  R3l_ps_cambridge->SetLineWidth(3);
  R3l_ps_cambridge->SetLineStyle(1);
  R3l_ps_cambridge->Draw("c");

  /* R3l_reco->SetLineColor(2);
  R3l_reco->SetLineWidth(2);
  R3l_reco->SetLineStyle(2);
  R3l_reco->Draw("c");

  R3l_reco_cambridge->SetLineColor(4);
  R3l_reco_cambridge->SetLineWidth(2);
  R3l_reco_cambridge->SetLineStyle(2);
  R3l_reco_cambridge->Draw("c");*/

  
  TLegend *leg2 = new TLegend(0.4,0.7,0.65,0.85);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->AddEntry(R3l_ps,"PS - Durham","l");
  leg2->AddEntry(R3l_ps_cambridge,"PS - Cambridge","l");
  //leg2->AddEntry(R3l_reco,"Reco (no cuts) - Durham","l");
  //leg2->AddEntry(R3l_reco_cambridge,"Reco (no cuts) - Cambridge","l");
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  //  leg2->SetShadowColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();

   TCanvas * canvas3 = new TCanvas("R3bl","R3bl",800,800);
  canvas3->cd(1);
  //  gPad->SetLogy();

  R3bl_ps->GetYaxis()->SetTitle("R_{3}^{bl}");
  R3bl_ps->GetYaxis()->SetRangeUser(0.5,1.5);
  R3bl_ps->GetXaxis()->SetTitle("y_{cut}");
  R3bl_ps->SetLineColor(4);
  R3bl_ps->SetLineWidth(3);
  R3bl_ps->SetLineStyle(1);
  R3bl_ps->Draw("ac");

  R3bl_ps_cambridge->SetLineColor(5);
  R3bl_ps_cambridge->SetLineWidth(3);
  R3bl_ps_cambridge->SetLineStyle(1);
  R3bl_ps_cambridge->Draw("c");

  /* R3bl_reco->SetLineColor(2);
  R3bl_reco->SetLineWidth(2);
  R3bl_reco->SetLineStyle(2);
  R3bl_reco->Draw("c");

  R3bl_reco_cambridge->SetLineColor(4);
  R3bl_reco_cambridge->SetLineWidth(2);
  R3bl_reco_cambridge->SetLineStyle(2);
  R3bl_reco_cambridge->Draw("c");*/

  
  TLegend *leg3 = new TLegend(0.4,0.7,0.65,0.85);
  leg3->SetTextSize(0.035);
  leg3->SetTextFont(42);
  leg3->AddEntry(R3bl_ps,"PS - Cambridge (Njets > 2) ","l");
  leg3->AddEntry(R3bl_ps_cambridge,"PS - Cambridge (Njets == 3)","l");
  //leg3->AddEntry(R3bl_reco,"Reco (no cuts) - Durham","l");
  //leg3->AddEntry(R3bl_reco_cambridge,"Reco (no cuts) - Cambridge","l");
  leg3->SetFillStyle(0);
  leg3->SetLineWidth(0);
  leg3->SetLineColor(0);
  //  leg3->SetShadowColor(0);
  leg3->SetBorderSize(0);
  leg3->Draw();

  TCanvas * canvas4 = new TCanvas("R3bl_reco","R3bl_reco",800,800);
  canvas4->cd(1);
  //  gPad->SetLogy();

  R3bl_ps_cambridge->GetYaxis()->SetTitle("R_{3}^{bl}");
  R3bl_ps_cambridge->GetYaxis()->SetRangeUser(0.5,1.5);
  R3bl_ps_cambridge->GetXaxis()->SetTitle("y_{cut}");
  R3bl_ps_cambridge->SetLineColor(4);
  R3bl_ps_cambridge->SetLineWidth(3);
  R3bl_ps_cambridge->SetLineStyle(1);
  R3bl_ps_cambridge->Draw("ac");

  R3bl_reco_cambridge->SetLineColor(1);
  R3bl_reco_cambridge->SetLineWidth(3);
  R3bl_reco_cambridge->SetLineStyle(1);
  R3bl_reco_cambridge->Draw("c");

  R3bl_reco0_cambridge->SetLineColor(1);
  R3bl_reco0_cambridge->SetLineWidth(3);
  R3bl_reco0_cambridge->SetLineStyle(2);
  R3bl_reco0_cambridge->Draw("c");

  /* R3bl_reco->SetLineColor(2);
  R3bl_reco->SetLineWidth(2);
  R3bl_reco->SetLineStyle(2);
  R3bl_reco->Draw("c");

  R3bl_reco_cambridge->SetLineColor(4);
  R3bl_reco_cambridge->SetLineWidth(2);
  R3bl_reco_cambridge->SetLineStyle(2);
  R3bl_reco_cambridge->Draw("c");*/

  
  TLegend *leg4 = new TLegend(0.4,0.7,0.65,0.85);
  leg4->SetTextSize(0.035);
  leg4->SetTextFont(42);
  leg4->AddEntry(R3bl_ps_cambridge,"PS - Cambridge","l");
  leg4->AddEntry(R3bl_reco0_cambridge,"Reco (no cuts) - Cambridge","l");
  leg4->AddEntry(R3bl_reco_cambridge,"Reco (all cuts) - Cambridge","l");
    //leg4->AddEntry(R3bl_reco,"Reco (no cuts) - Durham","l");
  //leg4->AddEntry(R3bl_reco_cambridge,"Reco (no cuts) - Cambridge","l");
  leg4->SetFillStyle(0);
  leg4->SetLineWidth(0);
  leg4->SetLineColor(0);
  //  leg4->SetShadowColor(0);
  leg4->SetBorderSize(0);
  leg4->Draw();


}
