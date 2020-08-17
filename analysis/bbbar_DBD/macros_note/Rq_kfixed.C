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

void Labels(int i=1, TString pol="left", float y=0.85){

  QQBARLabel(0.86,0.952,"");
  QQBARLabel2(0.25,0.96, "LO EW matrix element - Whizard 1.95",kGray+2);
  if(pol=="left"){
    if(i==1) QQBARLabel2(0.2,y, "#sigma^{cont.}_{e_{L}^{-}e_{R}^{+}#rightarrow q#bar{q}}(E_{#gamma}<K_{cut})",kBlack,0.05);
    if(i==2) QQBARLabel2(0.2,y, "#sigma^{cont.}_{e_{L}^{-}e_{R}^{+}#rightarrow q#bar{q}}(E_{#gamma}>K_{cut})",kBlack,0.05);
  } else {
    if(i==1) QQBARLabel2(0.2,y, "#sigma^{cont.}_{e_{R}^{-}e_{L}^{+}#rightarrow q#bar{q}}(E_{#gamma}<K_{cut})",kBlack,0.05);
    if(i==2) QQBARLabel2(0.2,y, "#sigma^{cont.}_{e_{R}^{-}e_{L}^{+}#rightarrow q#bar{q}}(E_{#gamma}>K_{cut})",kBlack,0.05);
  }
  
}

void LabelsR(int i=1, float y=0.85){

  QQBARLabel(0.86,0.952,"");
  QQBARLabel2(0.25,0.96, "LO EW matrix element - Whizard 1.95",kGray+2);
  //if(i==1) QQBARLabel2(0.2,y, "#font[42]{R}^{cont.}_{b}",kBlack,0.05);
  // if(i==2) QQBARLabel2(0.2,y, "\DeltaR",kBlack,0.05);
  
}




void Rq_kfixed() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(4);


  TString pol="eL";
  TGraph *g_Rb[2];
  TGraph *g_Rc[2];
  TGraph *g_Ruds[2];

  TGraph *g_Rb_rad[2];
  TGraph *g_Rc_rad[2];
  TGraph *g_Ruds_rad[2];

  for(int ipol=0; ipol<2; ipol++){
    cout<< " ******************************* "<<endl;
    cout<< "  "<<endl;
    float x[20], yb[20], yc[20], yuds[20];
    float yb_rad[20], yc_rad[20], yuds_rad[20];

    if(ipol==1) pol="eR";

    int nkgamma=13;

    float cross_section=129149.0;//fb (left pol)
    if(ipol==1) cross_section=71272.8;//fb (left pol)

    int Kgamma=35;
    
    cout<< " ------------------------------- "<<endl;
    cout<< "Cross Section for Kgamma="<<Kgamma<<" GeV"<<endl;

    TString folder=TString::Format("../output_20200427/selection_cuts%i_",0);
    cout<<pol<<endl;
    TString filename = TString::Format("%sbbbar_genkt_restorer_Kgamma%i_250GeV_%s.root",folder.Data(),Kgamma,pol.Data());//sbbbar_radret_genkt_R125_Kgamma%i_250GeV_%s.root",folder.Data(),Kgamma,pol.Data());
    cout<<filename<<endl;
    TFile *f = new TFile(filename);
    
    TH1F *h_cross_costheta = (TH1F*)f->Get("h_cross_costheta");
    TH1F *h_cross_costheta_bb = (TH1F*)f->Get("h_cross_costheta_bb");
    TH1F *h_cross_costheta_qq = (TH1F*)f->Get("h_cross_costheta_qq");
    TH1F *h_cross_costheta_cc = (TH1F*)f->Get("h_cross_costheta_cc");
    TH1F *h_cross_costheta_radreturn = (TH1F*)f->Get("h_cross_costheta_radreturn");
    TH1F *h_cross_costheta_radreturn_bb = (TH1F*)f->Get("h_cross_costheta_radreturn_bb");
    TH1F *h_cross_costheta_radreturn_qq = (TH1F*)f->Get("h_cross_costheta_radreturn_qq");
    TH1F *h_cross_costheta_radreturn_cc = (TH1F*)f->Get("h_cross_costheta_radreturn_cc");
    
    for(int i=0; i<20; i++) {
      x[i]=h_cross_costheta_bb->GetBinCenter(i+1);

      float Rb= h_cross_costheta_bb->GetBinContent(i+1);
      float Rc= h_cross_costheta_cc->GetBinContent(i+1);
      float Rq= h_cross_costheta_qq->GetBinContent(i+1);

      yb[i] = Rb/ (Rb+Rc+Rq);
      yc[i] = Rc/ (Rb+Rc+Rq);
      yuds[i] = Rq/ (Rb+Rc+Rq);

      
      float Rb_rad= h_cross_costheta_radreturn_bb->GetBinContent(i+1);
      float Rc_rad= h_cross_costheta_radreturn_cc->GetBinContent(i+1);
      float Rq_rad= h_cross_costheta_radreturn_qq->GetBinContent(i+1);

      yb_rad[i] = Rb_rad/ (Rb_rad+Rc_rad+Rq_rad);
      yc_rad[i] = Rc_rad/ (Rb_rad+Rc_rad+Rq_rad);
      yuds_rad[i] = Rq_rad/ (Rb_rad+Rc_rad+Rq_rad);
    }
		
    g_Rb[ipol]=new TGraph(20,x,yb);
    g_Rc[ipol]=new TGraph(20,x,yc);
    g_Ruds[ipol]=new TGraph(20,x,yuds);

    g_Rb_rad[ipol]=new TGraph(20,x,yb_rad);
    g_Rc_rad[ipol]=new TGraph(20,x,yc_rad);
    g_Ruds_rad[ipol]=new TGraph(20,x,yuds_rad);

    float Rb=0;
    float Rc=0;
    float Rq=0;
    
    float Rb_rad=0;
    float Rc_rad=0;
    float Rq_rad=0;

    for(int i=0; i<20; i++) {
      Rb+=yb[i]/20.;
      Rc+=yc[i]/20.;
      Rq+=yuds[i]/20.;

      Rb_rad+=yb_rad[i]/20.;
      Rc_rad+=yc_rad[i]/20.;
      Rq_rad+=yuds_rad[i]/20.;

    }

    cout<<Rb<<" "<<Rc<<" "<<Rq<<" "<<Rb_rad<<" "<<Rc_rad<<" "<<Rq_rad<<endl;

  }

  TGaxis::SetMaxDigits(4);

  TCanvas * canvasRb = new TCanvas("canvas_Rb","canvas_Rb",800,800);
  canvasRb->cd(1);
  //  gPad->SetLogz();
 
  g_Rb[0]->GetYaxis()->SetTitle("R_{#font[42]{b}}^{#font[42]{cont.}} [%]");
  g_Rb[0]->GetXaxis()->SetTitle("|cos #theta_{q}|");
  g_Rb[0]->SetLineColor(4);
  g_Rb[0]->GetYaxis()->SetRangeUser(0,1);
  // g_Rb[0]->GetXaxis()->SetRangeUser(0,300);
  g_Rb[0]->SetLineColor(4);
  g_Rb[0]->SetMarkerColor(4);
  g_Rb[0]->SetLineWidth(3);
  g_Rb[0]->SetLineStyle(1);
  g_Rb[0]->Draw("al");
  
  g_Rb[1]->SetLineColor(4);
  g_Rb[1]->SetMarkerColor(4);
  g_Rb[1]->SetLineWidth(3);
  g_Rb[1]->SetLineStyle(2);
  g_Rb[1]->Draw("l");
  
  
  LabelsR(1);
  
  TLegend *leg = new TLegend(0.6,0.8,0.9,0.9);//(0.4,0.3,0.5,0.6);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(g_Rb[0],"e_{L}^{-}e_{R}^{+}#rightarrowb#bar{b}","l");
  leg->AddEntry(g_Rb[1],"e_{R}^{-}e_{L}^{+}#rightarrowb#bar{b}","l");
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);
  leg->SetLineColor(0);
  leg->SetBorderSize(0);
  leg->Draw();
 
  
}
