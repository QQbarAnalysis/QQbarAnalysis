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
 
  if(pol=="eL")QQBARLabel2(0.16,0.965, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q} (q=udscb, K_{#gamma}<35 GeV)",kGray+2);
  if(pol=="eR")QQBARLabel2(0.16,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q} (q=udscb, K_{#gamma}<35 GeV)",kGray+2);
  if(pol=="both")QQBARLabel2(0.16,0.965, "e^{-}e^{+} #rightarrow q#bar{q} (q=udscb, K_{#gamma}<35 GeV)",kGray+2);

}

void quark_tagging_both() {

    
    SetQQbarStyle();
    gStyle->SetOptFit(0); 
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    
    gStyle->SetTitleBorderSize(0);
    gStyle->SetTitleStyle(0);
    gStyle->SetMarkerSize(1.5);
    //  gStyle->SetTitleOffset(1.3,"y");
    gStyle->SetTitleY(1);
    gStyle->SetTitleX(0.15);

    
  TString pol="eL";

  for(int ipol=0; ipol<3; ipol++) {
    if(ipol==1) pol="eR";
    if(ipol==2) pol="both";

    TString filename = "../output/eff_purity_tag_"+pol+".root";
    cout<<filename<<endl;
    TFile *f = new TFile(filename);

    TGraphErrors *c_purity = (TGraphErrors*)f->Get("cquark_purity");
    TGraphErrors *c_eff = (TGraphErrors*)f->Get("cquark_eff");

    c_eff->SetLineColor(1);
    c_eff->SetLineWidth(2);

    c_purity->SetLineColor(1);
    c_purity->SetLineStyle(2);
    c_purity->SetLineWidth(2);
        
    TGraphErrors *b_purity = (TGraphErrors*)f->Get("bquark_purity");
    TGraphErrors *b_eff = (TGraphErrors*)f->Get("bquark_eff");
    
    TGraphErrors *b_purity2 = (TGraphErrors*)f->Get("bquark_purity_cut_mom");
    TGraphErrors *b_eff2 = (TGraphErrors*)f->Get("bquark_eff_cut_mom");
    
    

  TCanvas * canvas_b = new TCanvas("canvas_b"+pol,"canvas_b"+pol,800,800);
  canvas_b->cd(1);
  b_eff->SetTitle("b-quark tagging");
  b_eff->GetYaxis()->SetRangeUser(0.,1.);
  b_eff->GetXaxis()->SetRangeUser(0,1.);
  b_eff->GetXaxis()->SetTitle("b_{tag} value");
  b_eff->GetYaxis()->SetTitleOffset(1.4);
  //  b_eff->GetYaxis()->SetTitleColor(2);

  b_eff->SetLineColor(2);
  b_eff->SetLineWidth(2);
  b_eff->Draw("ac");

  b_purity->SetLineColor(4);
  b_purity->SetLineStyle(1);
  b_purity->SetLineWidth(2);
  b_purity->Draw("c");

  b_eff2->SetLineColor(2);
  b_eff2->SetLineWidth(2);
  b_eff2->SetLineStyle(2);
  b_eff2->Draw("c");

  b_purity2->SetLineColor(4);
  b_purity2->SetLineStyle(2);
  b_purity2->SetLineWidth(2);
  b_purity2->Draw("c");
  
  Labels(pol);


  TLegend *leg1 = new TLegend(0.4,0.45,0.6,0.55);//(0.4,0.3,0.5,0.6);
  leg1->SetTextSize(0.035);
  leg1->AddEntry(b_eff,"#font[42]{Efficiency}","l");
  leg1->AddEntry(b_purity,"#font[42]{Purity}","l");
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  //  leg1->SetShadowColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();

  TLegend *leg2 = new TLegend(0.4,0.35,0.6,0.45);//(0.4,0.3,0.5,0.6);
  leg2->SetTextSize(0.035);
  leg2->AddEntry(c_eff,"#font[42]{Only b_{tag}>0.8}","l");
  leg2->AddEntry(c_purity,"#font[42]{b_{tag}>0.8 & |#vec{p}_{vertex}|>25 GeV}","l");
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  //  leg2->SetShadowColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();
  
  //canvas_c->Print("ctag_eff_purity.eps");
  canvas_b->Print("btag_eff_purity_"+pol+".eps");

  }  
}
