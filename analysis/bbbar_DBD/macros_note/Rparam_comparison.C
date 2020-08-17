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
  // QQBARLabel2(0.2,0.2, "E^{ISR}_{#gamma}=35 GeV, K_{#gamma}^{reco.,geom.}<35 GeV",kOrange+2);
  QQBARLabel2(0.45,0.2, "Jet Distance: d_{ij}=min(E_{i},E_{j})#frac{1-cos(#theta_{ij})}{1-cos(R)}",kGray+2);

  // if(pol=="eL")QQBARLabel2(0.2,0.97, "e_{L}^{-}e_{R}^{+}",kGray+2);
  // if(pol=="eR")QQBARLabel2(0.2,0.97, "e_{R}^{-}e_{L}^{+}",kGray+2);

  QQBARLabel2(0.04,0.075, "K_{reco}<35 GeV & m_{j_{1},j_{2}}>130 GeV ",kOrange+3);
  QQBARLabel2(0.04,0.03, "& photon veto cuts",kOrange+3);
}


void Rparam_comparison() {

  cout<< "bb qq radreturn ww zz hz "<<endl;


  TH1F *h_costheta_bb[11][2]; 
  TH1F *h_costheta_cc[11][2]; 
  TH1F *h_costheta_qq[11][2];
  TH1F *h_costheta_all[11][2]; 
  TH1F *h_costheta_radreturn[11][2]; 

  TString pol="eR";

  int iR=7;

  double x[100], ex[100], y[100], ey[100], yrad[100], eyrad[100];

  for(int j=0; j<iR; j++) {

    TString R="050";
    if(j==1) R="075";
    if(j==2) R="100";
    if(j==3) R="125";
    //if(j==4) R="130";
    //if(j==5) R="135";
    //if(j==6) R="140";
    //if(j==7) R="145";
    if(j==4) R="150";
    if(j==5) R="175";
    if(j==6) R="200";

    for(int i=0; i<2; i++) {

      int cuts=i;
      if(i==1) cuts=3;
      
      h_costheta_all[j][i]=new TH1F(TString::Format("h_%i_%i",j,i),TString::Format("h_%i_%i",j,i),20,0,1);
      
      TString folder=TString::Format("../output_20200427/selection_cuts%i_",cuts);
      TString filename = folder+"bbbar_radret_genkt_R"+R+"_Kgamma35_250GeV_"+pol+".root";
      TFile *f = new TFile(filename);
      h_costheta_radreturn[j][i] = (TH1F*)f->Get("h_costheta_radreturn");
      
      h_costheta_bb[j][i] = (TH1F*)f->Get("h_costheta_bb");
      h_costheta_qq[j][i] = (TH1F*)f->Get("h_costheta_qq");
      h_costheta_cc[j][i] = (TH1F*)f->Get("h_costheta_cc");
      
      h_costheta_all[j][i]->Add(h_costheta_bb[j][i]);
      h_costheta_all[j][i]->Add(h_costheta_cc[j][i]);
      h_costheta_all[j][i]->Add(h_costheta_qq[j][i]);
      
    }

    //if(j<4)
    x[j]=0.5+0.25*j;
    //if(j>3 && j<8) x[j]=1.3+0.05*(j-4);
    // if(j>7) x[j]=1.5+0.25*(j-8);
    
    ex[j]=0;
    y[j]=100.*h_costheta_all[j][1]->GetEntries()/h_costheta_all[j][0]->GetEntries();
    ey[j]=100.*sqrt(h_costheta_all[j][1]->GetEntries())/h_costheta_all[j][0]->GetEntries();

    yrad[j]=100.*h_costheta_radreturn[j][1]->GetEntries()/h_costheta_radreturn[j][0]->GetEntries();
    eyrad[j]=100.*sqrt(h_costheta_radreturn[j][1]->GetEntries())/h_costheta_radreturn[j][0]->GetEntries();
      
    h_costheta_bb[j][1]->Divide(h_costheta_bb[j][0]);
    h_costheta_cc[j][1]->Divide(h_costheta_cc[j][0]);
    h_costheta_qq[j][1]->Divide(h_costheta_qq[j][0]);

    h_costheta_radreturn[j][1]->Divide(h_costheta_radreturn[j][0]);
    h_costheta_all[j][1]->Divide(h_costheta_all[j][0]);

  }

  TGraphErrors *eff = new TGraphErrors(iR,x,y,ex,ey);
  TGraphErrors *eff_rad = new TGraphErrors(iR,x,yrad,ex,eyrad);

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);

  
  TCanvas * canvas1 = new TCanvas("canvas_1","canvas_1",800,800);
  canvas1->cd(1);

  TLegend *leg1 = new TLegend(0.3,0.65,0.5,0.93);//(0.4,0.3,0.5,0.6);
  leg1->SetTextSize(0.03);
  leg1->SetHeader("Jet R-parameter");
  
  for(int j=0; j<iR; j++) {

    TString R="0.5";
    if(j==1) R="0.75";
    if(j==2) R="1.0";
    if(j==3) R="1.25";
    // if(j==4) R="130";
    // if(j==5) R="135";
    // if(j==6) R="140";
    //if(j==7) R="145";
    if(j==4) R="1.5";
    if(j==5) R="1.75";
    if(j==6) R="2.0";
    
    h_costheta_all[j][1]->GetYaxis()->SetTitle("N_{selection}/N_{total} (Signal, all flavours)");
    h_costheta_all[j][1]->GetYaxis()->SetRangeUser(0,1.4);
    h_costheta_all[j][1]->GetXaxis()->SetRangeUser(0,1.);
    h_costheta_all[j][1]->GetXaxis()->SetTitle("|cos#theta_{q}|");
    h_costheta_all[j][1]->GetYaxis()->SetTitleOffset(1.3);
    
    h_costheta_all[j][1]->SetLineColor(j+1);
    h_costheta_all[j][1]->SetLineStyle(j+1);
    h_costheta_all[j][1]->SetLineWidth(1+(j%2));
    h_costheta_all[j][1]->Draw("histosame");
    
    leg1->AddEntry(h_costheta_all[j][1],"R="+R,"l");
    
  }

  Labels(pol);
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetBorderSize(0);
  leg1->Draw();
  
  //canvas1->Print(TString::Format("plots/Eff_rparam_Kcut35_%s.eps",pol.Data()));

  TCanvas * canvas2 = new TCanvas("canvas_2","canvas_2",800,800);
  canvas2->cd(1);

  TLegend *leg2 = new TLegend(0.3,0.65,0.5,0.93);//(0.4,0.3,0.5,0.6);
  leg2->SetTextSize(0.03);
  leg2->SetHeader("Jet R-parameter");
  
  for(int j=0; j<iR; j++) {

    TString R="0.5";
   if(j==1) R="0.75";
    if(j==2) R="1.0";
    if(j==3) R="1.25";
    // if(j==4) R="130";
    // if(j==5) R="135";
    // if(j==6) R="140";
    //if(j==7) R="145";
    if(j==4) R="1.5";
    if(j==5) R="1.75";
    if(j==6) R="2.0";

    
    h_costheta_radreturn[j][1]->GetYaxis()->SetTitle("N_{selection}/N_{total} (Rad.Ret., all flavours)");
    h_costheta_radreturn[j][1]->GetYaxis()->SetRangeUser(-1,1.4);
    h_costheta_radreturn[j][1]->GetXaxis()->SetRangeUser(0,1.);
    h_costheta_radreturn[j][1]->GetXaxis()->SetTitle("|cos#theta_{q}|");
    h_costheta_radreturn[j][1]->GetYaxis()->SetTitleOffset(1.3);
    
    h_costheta_radreturn[j][1]->SetLineColor(j+1);
    h_costheta_radreturn[j][1]->SetLineStyle(j+1);
    h_costheta_radreturn[j][1]->SetLineWidth(1+(j%2));
    h_costheta_radreturn[j][1]->Draw("histosame");
    
    leg2->AddEntry(h_costheta_radreturn[j][1],"R="+R,"l");
    
  }
 
  Labels(pol);
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetBorderSize(0);
  leg2->Draw();
  
  // canvas2->Print(TString::Format("plots/B_S_rparam_Kcut35_%s.eps",pol.Data()));

  TCanvas * canvas3 = new TCanvas("canvas_3","canvas_3",800,800);
  canvas3->cd(1);



  eff->GetYaxis()->SetTitle("Efficiency [%]");
  eff->GetYaxis()->SetRangeUser(60,100);
  eff->GetXaxis()->SetRangeUser(0,2.5);
  eff->GetXaxis()->SetTitle("R");
  // eff->GetYaxis()->SetTitleOffset(1.3);
  eff->SetLineColor(4);
  eff->SetLineStyle(1);
  eff->SetLineWidth(3);
  eff->SetMarkerColor(4);
  eff->SetMarkerStyle(21);
  eff->SetMarkerSize(1.5);

  eff->Draw("alp");

  /* eff_rad->SetLineColor(2);
  eff_rad->SetLineStyle(1);
  eff_rad->SetLineWidth(3);
  eff_rad->SetMarkerColor(2);
  eff_rad->SetMarkerStyle(25);
  eff_rad->SetMarkerSize(1.5);
  eff_rad->Draw("lp");*/

  TLegend *leg3 = new TLegend(0.3,0.75,0.5,0.93);//(0.4,0.3,0.5,0.6);
  leg3->SetTextSize(0.035);
  leg3->SetTextFont(42);
  leg3->AddEntry(eff,"e^{-}e^{+}#rightarrow q#bar{q} (q=udcsb,E_{#gamma}<35 GeV)","lp");
  //  leg3->AddEntry(eff_rad,"e_{R}^{-}e_{L}^{+}#rightarrow q#bar{q}(q=udcsb,E_{#gamma}>35 GeV)","lp");
 
  leg3->SetFillStyle(0);
  leg3->SetLineWidth(0);
  leg3->SetBorderSize(0);
  leg3->Draw();
  
  Labels(pol);

  TCanvas * canvas4 = new TCanvas("canvas_4","canvas_4",800,800);
  canvas4->cd(1);



  eff_rad->GetYaxis()->SetTitle("Efficiency [%]");
  eff_rad->GetYaxis()->SetRangeUser(0,2.5);
  eff_rad->GetXaxis()->SetRangeUser(0,2.5);
  eff_rad->GetXaxis()->SetTitle("R");
  // eff_rad->GetYaxis()->SetTitleOffset(1.3);
  eff_rad->SetLineColor(2);
  eff_rad->SetLineStyle(1);
  eff_rad->SetLineWidth(3);
  eff_rad->SetMarkerColor(2);
  eff_rad->SetMarkerStyle(25);
  eff_rad->SetMarkerSize(1.5);
  eff_rad->Draw("alp");

  TLegend *leg4 = new TLegend(0.3,0.75,0.5,0.93);//(0.4,0.3,0.5,0.6);
  leg4->SetTextSize(0.035);
  leg4->SetTextFont(42);
  //leg4->AddEntry(eff,"e_{R}^{-}e_{L}^{+}#rightarrow q#bar{q}(q=udcsb,E_{#gamma}<35 GeV)","lp");
  leg4->AddEntry(eff_rad,"e^{-}e^{+}#rightarrow q#bar{q} (q=udcsb,E_{#gamma}>35 GeV)","lp");
 
  leg4->SetFillStyle(0);
  leg4->SetLineWidth(0);
  leg4->SetBorderSize(0);
  leg4->Draw();
  
  Labels(pol);

  
}
