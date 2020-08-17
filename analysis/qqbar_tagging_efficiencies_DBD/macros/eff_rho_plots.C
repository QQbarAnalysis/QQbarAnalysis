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

void Labels(TString pol="eL"){

  QQBARLabel(0.86,0.952,"");
 
  if(pol=="eL")QQBARLabel2(0.17,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q} (q=udscb, K_{cut}=35 GeV)",kGray+2);
  if(pol=="eR")QQBARLabel2(0.17,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q} (q=udscb, K_{cut}=35 GeV)",kGray+2);
  if(pol=="both")QQBARLabel2(0.17,0.97, "e^{-}e^{+} #rightarrow q#bar{q} (q=udscb, K_{cut}=35 GeV)",kGray+2);

}


void eff_rho_plots() {

  for(int ipol=0; ipol<2; ipol++) {
  TString pol="eR";
  if(ipol==1) pol="eL";
  if(ipol==2) pol="both";

  TString filename = "../output/correlations_quark5_250GeV_"+pol+"_btag1_0.8_btag2_0.8_nbins40.root";
  cout<<filename<<endl;
  TFile *f = new TFile(filename);

  TGraphErrors* rho_btag= (TGraphErrors*)f->Get("rhoLEP");
  TGraphErrors* rho_Bc= (TGraphErrors*)f->Get("rhoLEP_Bc");
  TGraphErrors* rho_Kc= (TGraphErrors*)f->Get("rhoLEP_Kc");

  TGraphErrors* effb_btag= (TGraphErrors*)f->Get("effb");
  TGraphErrors* effb_Bc= (TGraphErrors*)f->Get("effb_Bc");
  TGraphErrors* effb_Kc= (TGraphErrors*)f->Get("effb_Kc");
  //  TGraphErrors* eff2j= (TGraphErrors*)f->Get("eff2j");
 
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);

  /* eff2j->SetLineStyle(1);
  eff2j->SetLineWidth(2);
  eff2j->SetLineColor(1);

  eff2jR->SetLineStyle(2);
  eff2jR->SetLineWidth(1);
  eff2jR->SetLineColor(1);*/

  TCanvas * canvas_eff = new TCanvas("canvas_eff","canvas_eff",800,800);

  canvas_eff->cd(1);
  effb_btag->GetYaxis()->SetRangeUser(0.,100);
  effb_btag->GetXaxis()->SetTitle("|cos#theta_{b}|");
  effb_btag->GetYaxis()->SetTitle("Efficiency [%]");
  effb_btag->GetYaxis()->SetTitleOffset(1.5);

  effb_btag->SetLineWidth(2);
  effb_btag->SetLineStyle(1);
  effb_btag->SetLineColor(2);
  effb_btag->SetMarkerColor(2);
  effb_btag->SetMarkerStyle(20);
  effb_btag->SetMarkerSize(1.4);
  effb_btag->Draw("alp");

  /*  effb_btagR->SetLineWidth(1);
  effb_btagR->SetLineStyle(2);
  effb_btagR->SetLineColor(2);
  effb_btagR->SetMarkerStyle(0);
  effb_btagR->Draw("l");*/
  
  effb_Bc->SetLineWidth(2);
  effb_Bc->SetLineStyle(1);
  effb_Bc->SetLineColor(kGray+3);
  effb_Bc->SetMarkerColor(kGray+3);
  effb_Bc->SetMarkerStyle(22);
  effb_Bc->SetMarkerSize(1.4);
  effb_Bc->Draw("lp");

  /*  effb_BcR->SetLineWidth(1);
  effb_BcR->SetLineStyle(2);
  effb_BcR->SetLineColor(kGray+3);
  effb_BcR->SetMarkerStyle(0);
  effb_BcR->Draw("lp");*/
  
  effb_Kc->SetLineStyle(1);
  effb_Kc->SetLineWidth(2);
  effb_Kc->SetLineColor(kGray+1);
  effb_Kc->SetMarkerColor(kGray+1);
  effb_Kc->SetMarkerStyle(21);
  effb_Kc->SetMarkerSize(1.4);
  effb_Kc->Draw("lp");

  /*  effb_KcR->SetLineStyle(2);
  effb_KcR->SetLineWidth(1);
  effb_KcR->SetLineColor(kGray+1);
  effb_KcR->SetMarkerStyle(0);
  effb_KcR->Draw("lp");*/
  
  Labels(pol);
  //  QQBARLabel(0.2,0.2,"Preliminary");
  //  QQBARLabel2(0.55,0.96, "e^{-}e^{+} #rightarrow b#bar{b}, 250GeV",kGray+2);
  //"c-quark tagging",kGray+2);

  TLegend *leg_eff = new TLegend(0.2,0.75,0.7,0.9);//(0.4,0.3,0.5,0.6);
  leg_eff->SetTextSize(0.03);
  leg_eff->SetTextFont(42);
  leg_eff->AddEntry(effb_btag,"#font[42]{b_{tag}>0.8 & |#vec{p}_{sec. vtx}|>25 GeV}","lpe");
  leg_eff->AddEntry(effb_Bc,"#font[42]{b_{tag}>0.8 & |#vec{p}_{sec. vtx}|>25 GeV & Vtx-method}","lpe");
  leg_eff->AddEntry(effb_Kc,"#font[42]{b_{tag}>0.8 & |#vec{p}_{sec. vtx}|>25 GeV & K-method}","lpe");
  leg_eff->SetFillStyle(0);
  leg_eff->SetLineWidth(0);
  leg_eff->SetLineColor(0);
  //  leg_eff->SetShadowColor(0);
  leg_eff->SetBorderSize(0);
  leg_eff->Draw();

  /* TLegend *leg_eff2 = new TLegend(0.2,0.2,0.7,0.3);//(0.4,0.3,0.5,0.6);
  leg_eff2->SetTextSize(0.03);
  leg_eff2->SetTextFont(42);
  leg_eff2->AddEntry(eff2j,"e_{L}^{-}e_{R}^{+}","l");
  leg_eff2->AddEntry(eff2jR,"e_{R}^{-}e_{L}^{+}","l");
  leg_eff2->SetFillStyle(0);
  leg_eff2->SetLineWidth(0);
  leg_eff2->SetLineColor(0);
  //  leg_eff->SetShadowColor(0);
  leg_eff2->SetBorderSize(0);
  leg_eff2->Draw();*/

  canvas_eff->Print("eff_btag_charge_"+pol+".eps");


  TCanvas * canvas_rho = new TCanvas("canvas_rho","canvas_rho",800,800);

  canvas_rho->cd(1);
  rho_btag->GetYaxis()->SetRangeUser(-20.,100);
  rho_btag->GetXaxis()->SetTitle("|cos#theta_{b}|");
  rho_btag->GetYaxis()->SetTitle("#rho [%]");
  rho_btag->GetYaxis()->SetTitleOffset(1.5);

  rho_btag->SetLineWidth(2);
  rho_btag->SetLineStyle(1);
  rho_btag->SetLineColor(2);
  rho_btag->SetMarkerColor(2);
  rho_btag->SetMarkerStyle(20);
  rho_btag->SetMarkerSize(1.4);
  rho_btag->Draw("alp");

  /*  rho_btagR->SetLineWidth(1);
  rho_btagR->SetLineStyle(2);
  rho_btagR->SetLineColor(2);
  rho_btagR->SetMarkerStyle(0);
  rho_btagR->Draw("l");*/
  
  rho_Bc->SetLineWidth(2);
  rho_Bc->SetLineStyle(1);
  rho_Bc->SetLineColor(kGray+3);
  rho_Bc->SetMarkerColor(kGray+3);
  rho_Bc->SetMarkerStyle(22);
  rho_Bc->SetMarkerSize(1.4);
  rho_Bc->Draw("lp");

  /* rho_BcR->SetLineWidth(1);
  rho_BcR->SetLineStyle(2);
  rho_BcR->SetLineColor(kGray+3);
  rho_BcR->SetMarkerStyle(0);
  rho_BcR->Draw("lp");*/
  
  rho_Kc->SetLineStyle(1);
  rho_Kc->SetLineWidth(2);
  rho_Kc->SetLineColor(kGray+1);
  rho_Kc->SetMarkerColor(kGray+1);
  rho_Kc->SetMarkerStyle(21);
  rho_Kc->SetMarkerSize(1.4);
  rho_Kc->Draw("lp");

  /* rho_KcR->SetLineStyle(2);
  rho_KcR->SetLineWidth(1);
  rho_KcR->SetLineColor(kGray+1);
  rho_KcR->SetMarkerStyle(0);
  rho_KcR->Draw("lp");*/

  Labels(pol);
  //  QQBARLabel(0.2,0.2,"Preliminary");
  //  QQBARLabel2(0.55,0.96, "e^{-}e^{+} #rightarrow b#bar{b}, 250GeV",kGray+2);
  //"c-quark tagging",kGray+2);

  TLegend *leg_rho = new TLegend(0.2,0.75,0.7,0.9);//(0.4,0.3,0.5,0.6);
  leg_rho->SetTextSize(0.03);
  leg_rho->SetTextFont(42);
  leg_rho->AddEntry(rho_btag,"#font[42]{b_{tag}>0.8 & |#vec{p}_{sec. vtx}|>25 GeV}","lpe");
  leg_rho->AddEntry(rho_Bc,"#font[42]{b_{tag}>0.8 & |#vec{p}_{sec. vtx}|>25 GeV & Vtx-method}","lpe");
  leg_rho->AddEntry(rho_Kc,"#font[42]{b_{tag}>0.8 & |#vec{p}_{sec. vtx}|>25 GeV & K-method}","lpe");
  leg_rho->SetFillStyle(0);
  leg_rho->SetLineWidth(0);
  leg_rho->SetLineColor(0);
  //  leg_rho->SetShadowColor(0);
  leg_rho->SetBorderSize(0);
  leg_rho->Draw();

  /* TLegend *leg_rho2 = new TLegend(0.2,0.5,0.7,0.6);//(0.4,0.3,0.5,0.6);
  leg_rho2->SetTextSize(0.03);
  leg_rho2->SetTextFont(42);
  leg_rho2->AddEntry(eff2j,"e_{L}^{-}e_{R}^{+}","l");
  leg_rho2->AddEntry(eff2jR,"e_{R}^{-}e_{L}^{+}","l");
  leg_rho2->SetFillStyle(0);
  leg_rho2->SetLineWidth(0);
  leg_rho2->SetLineColor(0);
  //  leg_rho->SetShadowColor(0);
  leg_rho2->SetBorderSize(0);
  leg_rho2->Draw();*/
  

  canvas_rho->Print("rho_btag_charge_"+pol+".eps");
}
  
}
