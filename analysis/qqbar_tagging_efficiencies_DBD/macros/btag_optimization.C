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
 
  if(pol=="eL")QQBARLabel2(0.17,0.965, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q} (q=udscb, E_{#gamma}<35 GeV)",kGray+2);
  if(pol=="eL")QQBARLabel2(0.17,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q} (q=udscb, E_{#gamma}<35 GeV)",kGray+2);
  if(pol=="both")QQBARLabel2(0.17,0.965, "e^{-}e^{+} #rightarrow q#bar{q} (q=udscb, E_{#gamma}<35 GeV)",kGray+2);

}

void btag_optimization() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);
  gStyle->SetTitleOffset(1.8,"y");
  gStyle->SetTitleOffset(1.6,"x");
  //  gStyle->SetTitleSize(0.05,"xy");
  
  TString pol="both";
  TString filename = "../output/bjets_btag08_"+pol+".root";
  cout<<filename<<endl;
  TFile *f = new TFile(filename);

  TH1F* p_vtx_b= (TH1F*)f->Get("p_vtx_b");
  TH1F* p_vtx_c= (TH1F*)f->Get("p_vtx_c");
  TH1F* p_vtx_q= (TH1F*)f->Get("p_vtx_q");

  TH1F* p_tracks_b= (TH1F*)f->Get("p_tracks_b");
  TH1F* p_tracks_c= (TH1F*)f->Get("p_tracks_c");
  TH1F* p_tracks_q= (TH1F*)f->Get("p_tracks_q");
    
  TH1F* multiplicity_tracks_b= (TH1F*)f->Get("multiplicity_tracks_b");
  TH1F* multiplicity_tracks_c= (TH1F*)f->Get("multiplicity_tracks_c");
  TH1F* multiplicity_tracks_q= (TH1F*)f->Get("multiplicity_tracks_q");
  

  TCanvas * canvas_c = new TCanvas("canvas_c","canvas_c",800,800);
 
  canvas_c->cd(1);
  p_vtx_q->SetTitle("Jets with b_{tag}>0.8");
  p_vtx_q->GetXaxis()->SetTitle("|#vec{p}_{sec. vtx}| [GeV]");
  p_vtx_q->GetYaxis()->SetTitle("normalized distribution");
  p_vtx_q->GetYaxis()->SetTitleSize(0.04);
  p_vtx_q->GetXaxis()->SetTitleSize(0.04);

  // p_vtx_q->GetYaxis()->SetTitleOffset(1.3);
  // p_vtx_q->GetXaxis()->SetTitleOffset(1.3);
  
  p_vtx_q->SetLineWidth(2);
  p_vtx_q->SetLineStyle(2);
  p_vtx_q->SetLineColor(1);
  p_vtx_q->DrawNormalized("histo");

  p_vtx_c->SetLineWidth(2);
  p_vtx_c->SetLineStyle(1);
  p_vtx_c->SetLineColor(1);
  p_vtx_c->DrawNormalized("histosame");

  p_vtx_b->SetLineWidth(2);
  p_vtx_b->SetLineStyle(1);
  p_vtx_b->SetLineColor(4);
  p_vtx_b->DrawNormalized("histosame");
  
  Labels(pol);
  QQBARLabel2(0.2,0.9, "Jets with b_{tag}>0.8",kGray+3);

  TLegend *leg0 = new TLegend(0.55,0.65,0.7,0.8);//(0.4,0.3,0.5,0.6);
  leg0->SetTextSize(0.033);
  leg0->SetHeader("#font[42]{Jet originated by a}");
  leg0->AddEntry(p_vtx_b,"#font[42]{b-quark}","l");
  leg0->AddEntry(p_vtx_c,"#font[42]{c-quark}","l");
  leg0->AddEntry(p_vtx_q,"#font[42]{uds-quark}","l");
  leg0->SetFillStyle(0);
  leg0->SetLineWidth(0);
  leg0->SetLineColor(0);
  leg0->SetBorderSize(0);
  leg0->Draw();

  canvas_c->Print("btag_optimization_vtx_mom.eps");

  TCanvas * canvas_p = new TCanvas("canvas_p","canvas_p",800,800);
 
  canvas_p->cd(1);
  p_tracks_q->GetXaxis()->SetTitle("|#vec{p}_{sec. tracks}| [GeV]");
  p_tracks_q->GetYaxis()->SetTitle("normalized distribution");
  p_tracks_q->GetXaxis()->SetRangeUser(0,40);
  p_tracks_q->GetYaxis()->SetTitleSize(0.045);
  p_tracks_q->GetXaxis()->SetTitleSize(0.045);
  // p_tracks_q->GetYaxis()->SetTitleOffset(1.3);
  //p_tracks_q->GetXaxis()->SetTitleOffset(1.3);
  
  p_tracks_q->SetLineColor(1);
  p_tracks_q->SetLineWidth(2);
  p_tracks_q->SetLineStyle(2);
  p_tracks_q->DrawNormalized("histo");

  p_tracks_c->SetLineColor(1);
  p_tracks_c->SetLineWidth(2);
  p_tracks_c->SetLineStyle(1);
  p_tracks_c->DrawNormalized("histosame");

  p_tracks_b->SetLineColor(4);
  p_tracks_b->SetLineWidth(2);
  p_tracks_b->SetLineStyle(1);
  p_tracks_b->DrawNormalized("histosame");
  
  Labels(pol);
  // QQBARLabel2(0.2,0.9, "Jets with b-tag>0.8",kGray+3);

  TLegend *leg1 = new TLegend(0.55,0.65,0.7,0.8);//(0.4,0.3,0.5,0.6);
  leg1->SetTextSize(0.033);
  //  leg1->SetHeader("#font[42]{Secondary tracks from:}");
  leg1->AddEntry(p_tracks_b,"#font[42]{b-quark}","l");
  leg1->AddEntry(p_tracks_c,"#font[42]{c-quark}","l");
  leg1->AddEntry(p_tracks_q,"#font[42]{uds-quark}","l");
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();

  canvas_p->Print("p_tracks.eps");

  
  TCanvas * canvas_m = new TCanvas("canvas_m","canvas_m",800,800);
 
  canvas_m->cd(1);
  multiplicity_tracks_q->GetXaxis()->SetTitle("N_{sec. tracks}");
  multiplicity_tracks_q->GetYaxis()->SetTitle("normalized distribution");
  multiplicity_tracks_q->GetXaxis()->SetRangeUser(0,20);
  multiplicity_tracks_q->GetYaxis()->SetRangeUser(0,1000);
  multiplicity_tracks_q->GetYaxis()->SetTitleSize(0.045);
  multiplicity_tracks_q->GetXaxis()->SetTitleSize(0.045);
  // multiplicity_tracks_q->GetYaxis()->SetTitleOffset(1.3);
  // multiplicity_tracks_q->GetXaxis()->SetTitleOffset(1.3);
  
  multiplicity_tracks_q->SetLineColor(1);
  multiplicity_tracks_q->SetLineWidth(2);
  multiplicity_tracks_q->SetLineStyle(2);
  multiplicity_tracks_q->DrawNormalized("histo");

  multiplicity_tracks_c->SetLineColor(1);
  multiplicity_tracks_c->SetLineWidth(2);
  multiplicity_tracks_c->SetLineStyle(1);
  multiplicity_tracks_c->DrawNormalized("histosame");

  multiplicity_tracks_b->SetLineColor(4);
  multiplicity_tracks_b->SetLineWidth(2);
  multiplicity_tracks_b->SetLineStyle(1);
  multiplicity_tracks_b->DrawNormalized("histosame");
  
  Labels(pol);
  // QQBARLabel2(0.2,0.9, "Jets with b-tag>0.8",kGray+3);

  TLegend *leg2 = new TLegend(0.55,0.65,0.7,0.8);//(0.4,0.3,0.5,0.6);
  leg2->SetTextSize(0.033);
  //  leg2->SetHeader("#font[42]{Secondary tracks from:}");
  leg2->AddEntry(multiplicity_tracks_b,"#font[42]{b-quark}","l");
  leg2->AddEntry(multiplicity_tracks_c,"#font[42]{c-quark}","l");
  leg2->AddEntry(multiplicity_tracks_q,"#font[42]{uds-quark}","l");
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();

  canvas_m->Print("multiplicity_tracks.eps");
  
  
}
