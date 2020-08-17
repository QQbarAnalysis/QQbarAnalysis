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




void cross_section_calc_k() {

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
  TGraph *g_dRb[2];

  TGraph *g_cross[2];
  TGraph *g_cross_rad[2];
  TGraph *g_cross_c[2];
  TGraph *g_cross_rad_c[2];
  TGraph *g_cross_uds[2];
  TGraph *g_cross_rad_uds[2];


  for(int ipol=0; ipol<2; ipol++){
    cout<< " ******************************* "<<endl;
    cout<< "  "<<endl;
    float x[20],yb[20], ycross[20], ycross_rad[20], ycross_c[20], ycross_rad_c[20], ycross_uds[20], ycross_rad_uds[20];

    if(ipol==1) pol="eR";

    int nkgamma=13;
    for(int i=0; i<nkgamma; i++) {

    float cross_section=129149.0;//fb (left pol)
    if(ipol==1) cross_section=71272.8;//fb (left pol)

    int Kgamma=5;
    if(i==1) Kgamma=10;
    if(i==2) Kgamma=20;
    if(i==3) Kgamma=30;
    if(i==4) Kgamma=35;
    if(i==5) Kgamma=40;
    if(i==6) Kgamma=50;
    if(i==7) Kgamma=60;
    if(i==8) Kgamma=70;
    if(i==9) Kgamma=80;
    if(i==10) Kgamma=90;
    if(i==11) Kgamma=100;
    if(i==12) Kgamma=110;
    if(i==13) Kgamma=120;

    x[i]=float(Kgamma);
    
    cout<< " ------------------------------- "<<endl;
    cout<< "Cross Section for Kgamma="<<Kgamma<<" GeV"<<endl;

    TString folder=TString::Format("../output_20200427/selection_cuts%i_",0);
    cout<<pol<<endl;
    TString filename = TString::Format("%sbbbar_radret_genkt_R125_Kgamma%i_250GeV_%s.root",folder.Data(),Kgamma,pol.Data());
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
    
    float total_integral = h_cross_costheta->GetEntries()+h_cross_costheta_radreturn->GetEntries();

    cout<<" bb: "<<cross_section*h_cross_costheta_bb->GetEntries()/total_integral<<"  cc: "<<cross_section*h_cross_costheta_cc->GetEntries()/total_integral<<"  qq: "<<cross_section*h_cross_costheta_qq->GetEntries()/total_integral<<"  |  Rad-bb: "<<cross_section*h_cross_costheta_radreturn_bb->GetEntries()/total_integral<<" Rad-cc: "<<cross_section*h_cross_costheta_radreturn_cc->GetEntries()/total_integral<<" Rad-qq: "<<cross_section*h_cross_costheta_radreturn_qq->GetEntries()/total_integral<<endl;
    float Rall=h_cross_costheta_bb->GetEntries()+h_cross_costheta_cc->GetEntries()+h_cross_costheta_qq->GetEntries();
    float Rb=h_cross_costheta_bb->GetEntries()/Rall;
    float Rc=h_cross_costheta_cc->GetEntries()/Rall;
    float Rq=h_cross_costheta_qq->GetEntries()/Rall;
    cout<<" Rb: "<<Rb<<"   Rc: "<<Rc<<"   Ruds: "<<Rq<<endl;
    
    yb[i]=100*Rb;
    ycross[i]=cross_section*h_cross_costheta_bb->GetEntries()/total_integral;
    ycross_rad[i]=cross_section*h_cross_costheta_radreturn_bb->GetEntries()/total_integral;

    ycross_c[i]=cross_section*h_cross_costheta_cc->GetEntries()/total_integral;
    ycross_rad_c[i]=cross_section*h_cross_costheta_radreturn_cc->GetEntries()/total_integral;

    ycross_uds[i]=cross_section*h_cross_costheta_qq->GetEntries()/total_integral;
    ycross_rad_uds[i]=cross_section*h_cross_costheta_radreturn_qq->GetEntries()/total_integral;

    
   for(int j=0; j<1; j++) {
    int cuts=j;

   
    //    folder=TString::Format("../output/selection_cuts%i_",cuts);
    folder=TString::Format("../output_20200427/selection_cuts%i_",cuts);

    filename = TString::Format("%sbbbar_radret_genkt_R125_Kgamma%i_250GeV_%s.root",folder.Data(),Kgamma,pol.Data());
    cout<<filename<<endl;

    
    TFile *f2 = new TFile(filename);
    TH1F *h_costheta_bb = (TH1F*)f2->Get("h_costheta_bb");
    TH1F *h_costheta_qq = (TH1F*)f2->Get("h_costheta_qq");
    TH1F *h_costheta_cc = (TH1F*)f2->Get("h_costheta_cc");
    TH1F *h_costheta_radreturn_bb = (TH1F*)f2->Get("h_costheta_radreturn_bb");
    TH1F *h_costheta_radreturn_qq = (TH1F*)f2->Get("h_costheta_radreturn_qq");
    TH1F *h_costheta_radreturn_cc = (TH1F*)f2->Get("h_costheta_radreturn_cc");
    cout<< "Selection efficiency, cut"<<cuts<<endl;
    //cout<<" bb: "<<100*h_costheta_bb->GetEntries()/h_cross_costheta_bb->GetEntries()<<"%   cc: "<<100.*h_costheta_cc->GetEntries()/h_cross_costheta_cc->GetEntries()<<"%   qq: "<<100.*h_costheta_qq->GetEntries()/h_cross_costheta_qq->GetEntries();
    //cout<<"%    |  Rad-bb: "<<100.*h_costheta_radreturn_bb->GetEntries()/h_cross_costheta_radreturn_bb->GetEntries()<<"%  Rad-cc: "<<100.*h_costheta_radreturn_cc->GetEntries()/h_cross_costheta_radreturn_cc->GetEntries()<<"%  Rad-qq: "<<100.*h_costheta_radreturn_qq->GetEntries()/h_cross_costheta_radreturn_qq->GetEntries()<<"%"<<endl;
    
    
  }

        
  }
		
  g_Rb[ipol]=new TGraph(nkgamma,x,yb);
  g_cross[ipol]=new TGraph(nkgamma,x,ycross);
  g_cross_rad[ipol]=new TGraph(nkgamma,x,ycross_rad);

  g_cross_c[ipol]=new TGraph(nkgamma,x,ycross_c);
  g_cross_rad_c[ipol]=new TGraph(nkgamma,x,ycross_rad_c);

  g_cross_uds[ipol]=new TGraph(nkgamma,x,ycross_uds);
  g_cross_rad_uds[ipol]=new TGraph(nkgamma,x,ycross_rad_uds);
  
  double ynorm=yb[6];
  for(int iy=0; iy<nkgamma; iy++) {
      yb[iy]=100-100*yb[iy]/ynorm;
  }
  g_dRb[ipol]=new TGraph(nkgamma,x,yb);


  }

  TGaxis::SetMaxDigits(4);

  TCanvas * canvasRb = new TCanvas("canvas_Rb","canvas_Rb",800,800);
  canvasRb->cd(1);
  //  gPad->SetLogz();
 
  g_Rb[0]->GetYaxis()->SetTitle("R_{#font[42]{b}}^{#font[42]{cont.}} [%]");
  g_Rb[0]->GetXaxis()->SetTitle("K_{cut} [GeV]");
  g_Rb[0]->SetLineColor(4);
  g_Rb[0]->GetYaxis()->SetRangeUser(0,40);
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
  
  TCanvas * canvasdRb = new TCanvas("canvas_dRb","canvas_dRb",800,800);
  canvasdRb->cd(1);
  g_dRb[0]->GetYaxis()->SetTitle("#Delta R_{b} [%]");
  g_dRb[0]->GetXaxis()->SetTitle("K_{cut} [GeV]");
  g_dRb[0]->GetYaxis()->SetRangeUser(-5,15);
  g_dRb[0]->SetLineColor(4);
  g_dRb[0]->SetMarkerColor(4);
  g_dRb[0]->SetLineWidth(3);
  g_dRb[0]->SetLineStyle(1);
  g_dRb[0]->Draw("al");
  
  g_dRb[1]->SetLineColor(4);
  g_dRb[1]->SetMarkerColor(4);
  g_dRb[1]->SetLineWidth(3);
  g_dRb[1]->SetLineStyle(2);
  g_dRb[1]->Draw("l");
  
  LabelsR(2);
  QQBARLabel2(0.2,0.88, "#font[42]{#DeltaR_{b} = (1 - #frac{R_{b}(K_{cut})}{R_{b}(35GeV)}) (%)}",kBlack);

  TLegend *leg1 = new TLegend(0.7,0.8,0.9,0.9);//(0.4,0.3,0.5,0.6);
  leg1->SetTextSize(0.035);
  //  leg1->SetHeader("#font[42]{(1 - #frac{R_{b}(K_{cut})}{R_{b}(35GeV)}) (%)}");
  leg1->AddEntry(g_dRb[0],"e_{L}^{-}e_{R}^{+}#rightarrowb#bar{b}","l");
  leg1->AddEntry(g_dRb[1],"e_{R}^{-}e_{L}^{+}#rightarrowb#bar{b}","l");
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();

  TCanvas * canvascross = new TCanvas("canvas_cross","canvas_cross",800,800);
  canvascross->cd(1);
  //  gPad->SetLogz();
 
  g_cross[0]->GetYaxis()->SetTitle("cross section [fb]");
  g_cross[0]->GetXaxis()->SetTitle("K_{cut} [GeV]");
  g_cross[0]->GetYaxis()->SetRangeUser(0,30000);
  // g_cross[0]->GetXaxis()->SetRangeUser(0,300);
  g_cross[0]->SetLineColor(4);
  g_cross[0]->SetMarkerColor(4);
  g_cross[0]->SetLineWidth(3);
  g_cross[0]->SetLineStyle(1);
  g_cross[0]->Draw("al");
 
  g_cross_c[0]->SetLineColor(1);
  g_cross_c[0]->SetMarkerColor(1);
  g_cross_c[0]->SetLineWidth(2);
  g_cross_c[0]->SetLineStyle(1);
  g_cross_c[0]->Draw("l");
  
  g_cross_uds[0]->SetLineColor(1);
  g_cross_uds[0]->SetMarkerColor(1);
  g_cross_uds[0]->SetLineWidth(3);
  g_cross_uds[0]->SetLineStyle(2);
  g_cross_uds[0]->Draw("l");

  TLegend *leg2 = new TLegend(0.65,0.8,0.9,0.9);//(0.4,0.3,0.5,0.6);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  //  leg2->SetHeader("#font[42]{(1 - #frac{R_{b}(K_{cut})}{R_{b}(35GeV)}) (%)}");
  leg2->AddEntry(g_cross[0],"#font[52]{q}=b-quark","l");
  leg2->AddEntry(g_cross_c[0],"#font[52]{q}=c-quark","l");
  leg2->AddEntry(g_cross_uds[0],"#font[52]{q}=uds-quarks","l");
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();
  
  Labels(1,"left");

  TCanvas * canvascross_right= new TCanvas("canvas_cross_right","canvas_cross_right",800,800);
  canvascross_right->cd(1);
  //  gPad->SetLogz();
 
  g_cross[1]->GetYaxis()->SetTitle("cross section [fb]");
  g_cross[1]->GetXaxis()->SetTitle("K_{cut} [GeV]");
  g_cross[1]->GetYaxis()->SetRangeUser(0,30000);
  // g_cross[1]->GetXaxis()->SetRangeUser(0,300);
  g_cross[1]->SetLineColor(4);
  g_cross[1]->SetMarkerColor(4);
  g_cross[1]->SetLineWidth(3);
  g_cross[1]->SetLineStyle(1);
  g_cross[1]->Draw("al");
 
  g_cross_c[1]->SetLineColor(1);
  g_cross_c[1]->SetMarkerColor(1);
  g_cross_c[1]->SetLineWidth(2);
  g_cross_c[1]->SetLineStyle(1);
  g_cross_c[1]->Draw("l");
  
  g_cross_uds[1]->SetLineColor(1);
  g_cross_uds[1]->SetMarkerColor(1);
  g_cross_uds[1]->SetLineWidth(3);
  g_cross_uds[1]->SetLineStyle(2);
  g_cross_uds[1]->Draw("l");
  
  
  Labels(1,"right");

  leg2->Draw();


  TCanvas * canvascross_rad = new TCanvas("canvas_cross_rad","canvas_cross_rad",800,800);
  canvascross_rad->cd(1);
  //  gPad->SetLogz();
 
  g_cross_rad[0]->GetYaxis()->SetTitle("cross section [fb]");
  g_cross_rad[0]->GetXaxis()->SetTitle("K_{cut} [GeV]");
  g_cross_rad[0]->GetYaxis()->SetRangeUser(0,80000);
  // g_cross_rad[0]->GetXaxis()->SetRangeUser(0,300);
  g_cross_rad[0]->SetLineColor(4);
  g_cross_rad[0]->SetMarkerColor(4);
  g_cross_rad[0]->SetLineWidth(3);
  g_cross_rad[0]->SetLineStyle(1);
  g_cross_rad[0]->Draw("al");
 
  g_cross_rad_c[0]->SetLineColor(1);
  g_cross_rad_c[0]->SetMarkerColor(1);
  g_cross_rad_c[0]->SetLineWidth(2);
  g_cross_rad_c[0]->SetLineStyle(1);
  g_cross_rad_c[0]->Draw("l");
  
  g_cross_rad_uds[0]->SetLineColor(1);
  g_cross_rad_uds[0]->SetMarkerColor(1);
  g_cross_rad_uds[0]->SetLineWidth(3);
  g_cross_rad_uds[0]->SetLineStyle(2);
  g_cross_rad_uds[0]->Draw("l");

  leg2->Draw();
  
  Labels(2,"left");

  TCanvas * canvascross_rad_right= new TCanvas("canvas_cross_rad_right","canvas_cross_rad_right",800,800);
  canvascross_rad_right->cd(1);
  //  gPad->SetLogz();
 
  g_cross_rad[1]->GetYaxis()->SetTitle("cross section [fb]");
  g_cross_rad[1]->GetXaxis()->SetTitle("K_{cut} [GeV]");
  g_cross_rad[1]->GetYaxis()->SetRangeUser(0,80000);
  // g_cross_rad[1]->GetXaxis()->SetRangeUser(0,300);
  g_cross_rad[1]->SetLineColor(4);
  g_cross_rad[1]->SetMarkerColor(4);
  g_cross_rad[1]->SetLineWidth(3);
  g_cross_rad[1]->SetLineStyle(1);
  g_cross_rad[1]->Draw("al");
 
  g_cross_rad_c[1]->SetLineColor(1);
  g_cross_rad_c[1]->SetMarkerColor(1);
  g_cross_rad_c[1]->SetLineWidth(2);
  g_cross_rad_c[1]->SetLineStyle(1);
  g_cross_rad_c[1]->Draw("l");
  
  g_cross_rad_uds[1]->SetLineColor(1);
  g_cross_rad_uds[1]->SetMarkerColor(1);
  g_cross_rad_uds[1]->SetLineWidth(3);
  g_cross_rad_uds[1]->SetLineStyle(2);
  g_cross_rad_uds[1]->Draw("l");
  
  
  Labels(2,"right");

  leg2->Draw();

  
 
  
}
