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

void Labels(){

  QQBARLabel(0.86,0.952,"");
  QQBARLabel2(0.25,0.97, "LO EW matrix element - Whizard 1.95",kGray+2);
}

void cross_section_calc() {

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
  TGraph *g_cross[2];

  TGraph *g_dRb[2];
  TGraph *g_dcross[2];

  for(int ipol=1; ipol<2; ipol++){
    cout<< " ******************************* "<<endl;
    cout<< "  "<<endl;
    float x[6],yb[6], ycross[6];

    if(ipol==1)pol="eR";

  for(int i=0; i<6; i++) {

    float cross_section=129149.0;//fb (left pol)
    if(ipol==1) cross_section=71272.8;//fb (left pol)

    int Kgamma=5000;
    if(i==1) Kgamma=10;
    if(i==2) Kgamma=20;
    if(i==3) Kgamma=30;
    if(i==4) Kgamma=35;
    if(i==5) Kgamma=40;

    if(Kgamma==5000) x[5]=250;
    else x[i-1]=float(Kgamma);
    
    cout<< " ------------------------------- "<<endl;
    cout<< "Cross Section for Kgamma="<<Kgamma<<" GeV"<<endl;

    TString folder=TString::Format("../output_bk20200315/selection_cuts%i_",0);
    TString filename = TString::Format("%sbbbar_radret_Kgamma%i_250GeV_%s.root",folder.Data(),Kgamma,pol.Data());//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
    TFile *f = new TFile(filename);
    
    TH1F *h_cross_costheta = (TH1F*)f->Get("h_cross_costheta");
    TH1F *h_cross_costheta_bb = (TH1F*)f->Get("h_cross_costheta_bb");
    TH1F *h_cross_costheta_qq = (TH1F*)f->Get("h_cross_costheta_qq");
    TH1F *h_cross_costheta_cc = (TH1F*)f->Get("h_cross_costheta_cc");
    TH1F *h_cross_costheta_radreturn = (TH1F*)f->Get("h_cross_costheta_radreturn");
    TH1F *h_cross_costheta_radreturn_bb = (TH1F*)f->Get("h_cross_costheta_radreturn_bb");
    TH1F *h_cross_costheta_radreturn_qq = (TH1F*)f->Get("h_cross_costheta_radreturn_qq");
    TH1F *h_cross_costheta_radreturn_cc = (TH1F*)f->Get("h_cross_costheta_radreturn_cc");
    
    float total_integral = h_cross_costheta->GetEntries()+h_cross_costheta_radreturn->GetEntries();

    cout<<" bb: "<<cross_section*h_cross_costheta_bb->GetEntries()/total_integral<<"  cc: "<<cross_section*h_cross_costheta_cc->GetEntries()/total_integral<<"  qq: "<<cross_section*h_cross_costheta_qq->GetEntries()/total_integral<<"  |  Rad-bb: "<<cross_section*h_cross_costheta_radreturn_bb->GetEntries()/total_integral<<" Rad-cc: "<<cross_section*h_cross_costheta_radreturn_cc->GetEntries()/total_integral<<" Rad-qq: "<<cross_section*h_cross_costheta_radreturn_qq->GetEntries()/total_integral<<endl;
    float Rall=h_cross_costheta_bb->GetEntries()+h_cross_costheta_cc->GetEntries()+h_cross_costheta_qq->GetEntries();
    float Rb=h_cross_costheta_bb->GetEntries()/Rall;
    float Rc=h_cross_costheta_cc->GetEntries()/Rall;
    float Rq=h_cross_costheta_qq->GetEntries()/Rall;
    cout<<" Rb: "<<Rb<<"   Rc: "<<Rc<<"   Ruds: "<<Rq<<endl;

    if(Kgamma==5000) {yb[5]=100*Rb; ycross[5]=cross_section*h_cross_costheta_bb->GetEntries()/total_integral;}
    else {yb[i-1]=100*Rb; ycross[i-1]=cross_section*h_cross_costheta_bb->GetEntries()/total_integral;}

   for(int j=0; j<7; j++) {
    int cuts=j;

   
    folder=TString::Format("../output_bk20200315/selection_cuts%i_",cuts);
    filename = TString::Format("%sbbbar_radret_Kgamma%i_250GeV_%s.root",folder.Data(),Kgamma,pol.Data());;//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
    TFile *f2 = new TFile(filename);
    TH1F *h_costheta_bb = (TH1F*)f2->Get("h_costheta_bb");
    TH1F *h_costheta_qq = (TH1F*)f2->Get("h_costheta_qq");
    TH1F *h_costheta_cc = (TH1F*)f2->Get("h_costheta_cc");
    TH1F *h_costheta_radreturn_bb = (TH1F*)f2->Get("h_costheta_radreturn_bb");
    TH1F *h_costheta_radreturn_qq = (TH1F*)f2->Get("h_costheta_radreturn_qq");
    TH1F *h_costheta_radreturn_cc = (TH1F*)f2->Get("h_costheta_radreturn_cc");
    cout<< "Selection efficiency, cut"<<cuts<<endl;
    cout<<" bb: "<<100*h_costheta_bb->GetEntries()/h_cross_costheta_bb->GetEntries()<<"%   cc: "<<100.*h_costheta_cc->GetEntries()/h_cross_costheta_cc->GetEntries()<<"%   qq: "<<100.*h_costheta_qq->GetEntries()/h_cross_costheta_qq->GetEntries();
    cout<<"%    |  Rad-bb: "<<100.*h_costheta_radreturn_bb->GetEntries()/h_cross_costheta_radreturn_bb->GetEntries()<<"%  Rad-cc: "<<100.*h_costheta_radreturn_cc->GetEntries()/h_cross_costheta_radreturn_cc->GetEntries()<<"%  Rad-qq: "<<100.*h_costheta_radreturn_qq->GetEntries()/h_cross_costheta_radreturn_qq->GetEntries()<<"%"<<endl;

    
  }

        
  }
		
  g_Rb[ipol]=new TGraph(5,x,yb);
  g_cross[ipol]=new TGraph(5,x,ycross);

  double ynorm=yb[3];
  for(int iy=0; iy<6; iy++) {
      yb[iy]=100-100*yb[iy]/ynorm;
  }
  g_dRb[ipol]=new TGraph(5,x,yb);

  ynorm=ycross[3];
  for(int iy=0; iy<6; iy++) {
      ycross[iy]=100-100*ycross[iy]/ynorm;
  }
  g_dcross[ipol]=new TGraph(5,x,ycross);
  
  }

  TGaxis::SetMaxDigits(3);

  TCanvas * canvasRb = new TCanvas("canvas_Rb","canvas_Rb",800,800);
  canvasRb->cd(1);
  //  gPad->SetLogz();
 
  g_Rb[0]->GetYaxis()->SetTitle("R_{b} [%]");
  g_Rb[0]->GetXaxis()->SetTitle("K_{cut} [GeV]");
  g_Rb[0]->SetLineColor(4);
  g_Rb[0]->GetYaxis()->SetRangeUser(0,40);
  // g_Rb[0]->GetXaxis()->SetRangeUser(0,300);
  g_Rb[0]->SetLineColor(2);
  g_Rb[0]->SetMarkerColor(2);
  g_Rb[0]->SetLineWidth(2);
  g_Rb[0]->SetLineStyle(1);
  g_Rb[0]->Draw("al");
  
  g_Rb[1]->SetLineColor(2);
  g_Rb[1]->SetMarkerColor(2);
  g_Rb[1]->SetLineWidth(2);
  g_Rb[1]->SetLineStyle(2);
  g_Rb[1]->Draw("l");
  
  
  Labels();
  
  TLegend *leg = new TLegend(0.7,0.8,0.9,0.9);//(0.4,0.3,0.5,0.6);
  leg->SetTextSize(0.035);
  leg->AddEntry(g_Rb[0],"e_{L}^{-}e_{R}^{+} ","l");
  leg->AddEntry(g_Rb[1],"e_{R}^{-}e_{L}^{+} ","l");
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);
  leg->SetLineColor(0);
  leg->SetBorderSize(0);
  leg->Draw();
  
  TCanvas * canvasdRb = new TCanvas("canvas_dRb","canvas_dRb",800,800);
  canvasdRb->cd(1);
  g_dRb[0]->GetYaxis()->SetTitle("#Delta R_{b} [%]");

  g_dRb[0]->GetXaxis()->SetTitle("K_{cut} [GeV]");
  g_dRb[0]->SetLineColor(4);
  g_dRb[0]->GetYaxis()->SetRangeUser(-5,15);
  g_dRb[0]->SetLineColor(2);
  g_dRb[0]->SetMarkerColor(2);
  g_dRb[0]->SetLineWidth(2);
  g_dRb[0]->SetLineStyle(1);
  g_dRb[0]->Draw("al");
  
  g_dRb[1]->SetLineColor(2);
  g_dRb[1]->SetMarkerColor(2);
  g_dRb[1]->SetLineWidth(2);
  g_dRb[1]->SetLineStyle(2);
  g_dRb[1]->Draw("l");
  
  Labels();
  QQBARLabel2(0.2,0.88, "#font[42]{#DeltaR_{b} = (1 - #frac{R_{b}(K_{cut})}{R_{b}(35GeV)}) (%)}",kBlack);

  TLegend *leg1 = new TLegend(0.7,0.8,0.9,0.9);//(0.4,0.3,0.5,0.6);
  leg1->SetTextSize(0.035);
  //  leg1->SetHeader("#font[42]{(1 - #frac{R_{b}(K_{cut})}{R_{b}(35GeV)}) (%)}");
  leg1->AddEntry(g_dRb[0],"e_{L}^{-}e_{R}^{+} ","l");
  leg1->AddEntry(g_dRb[1],"e_{R}^{-}e_{L}^{+} ","l");
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();

  TCanvas * canvascross = new TCanvas("canvas_cross","canvas_cross",800,800);
  canvascross->cd(1);
  //  gPad->SetLogz();
 
  g_cross[0]->GetYaxis()->SetTitle("#sigma_{e^{-}e^{+}#rightarrow b#bar{b}} [fb]");
  g_cross[0]->GetXaxis()->SetTitle("K_{cut} [GeV]");
  g_cross[0]->SetLineColor(4);
  g_cross[0]->GetYaxis()->SetRangeUser(0,8500);
  // g_cross[0]->GetXaxis()->SetRangeUser(0,300);
  g_cross[0]->SetLineColor(2);
  g_cross[0]->SetMarkerColor(2);
  g_cross[0]->SetLineWidth(2);
  g_cross[0]->SetLineStyle(1);
  g_cross[0]->Draw("al");
  
  g_cross[1]->SetLineColor(2);
  g_cross[1]->SetMarkerColor(2);
  g_cross[1]->SetLineWidth(2);
  g_cross[1]->SetLineStyle(2);
  g_cross[1]->Draw("l");
  
  
  Labels();
  
  leg->Draw();
  
  TCanvas * canvasdcross = new TCanvas("canvas_dcross","canvas_dcross",800,800);
  canvasdcross->cd(1);
  g_dcross[0]->GetYaxis()->SetTitle("#Delta #sigma_{e^{-}e^{+}#rightarrow b#bar{b}} [%]");

  g_dcross[0]->GetXaxis()->SetTitle("K_{cut} [GeV]");
  g_dcross[0]->SetLineColor(4);
  g_dcross[0]->GetYaxis()->SetRangeUser(-20,50);
  g_dcross[0]->SetLineColor(2);
  g_dcross[0]->SetMarkerColor(2);
  g_dcross[0]->SetLineWidth(2);
  g_dcross[0]->SetLineStyle(1);
  g_dcross[0]->Draw("al");
  
  g_dcross[1]->SetLineColor(2);
  g_dcross[1]->SetMarkerColor(2);
  g_dcross[1]->SetLineWidth(2);
  g_dcross[1]->SetLineStyle(2);
  g_dcross[1]->Draw("l");
  
  Labels();
  QQBARLabel2(0.2,0.88, "#font[42]{#Delta#sigma_{e^{-}e^{+}#rightarrow b#bar{b}}= (1 - #frac{#sigma(K_{cut})}{#sigma(35GeV)}) (%)}",kBlack);

  leg1->Draw();

  
}
