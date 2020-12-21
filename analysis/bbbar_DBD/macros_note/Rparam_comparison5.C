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
  QQBARLabel2(0.2,0.2, "E^{ISR}_{#gamma}=35 GeV, K_{#gamma}^{reco.,geom.}<35 GeV",kOrange+2);
  // QQBARLabel2(0.2,0.3, "Jet Distance: d_{ij}=min(E_{i},E_{j})#frac{1-cos(#theta_{ij})}{1-cosR}",kBlue+2);

  if(pol=="eL")QQBARLabel2(0.2,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250GeV, 250fb^{-1}",kGray+2);
  if(pol=="eR")QQBARLabel2(0.2,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250GeV, 250fb^{-1}",kGray+2);
}


void Rparam_comparison5() {

  cout<< "bb qq radreturn ww zz hz "<<endl;


  TH1F *h_costheta_bb[11][2]; 
  TH1F *h_costheta_cc[11][2]; 
  TH1F *h_costheta_qq[11][2];
  TH1F *h_costheta_all[11][2]; 
  TH1F *h_costheta_radreturn[11][2]; 

  TString pol="eR";

  int iR=7;

  for(int j=0; j<3; j++) {

    TString setup="Rparam";
    if(j>0) setup="Rparam_cleanISR";
    if(j>1) setup="20200420_1";

    for(int i=0; i<2; i++) {
      int cuts=i;
      if(j==1 && i==1) cuts=2;
      if(j==2 && i==1) cuts=3;
      h_costheta_all[j][i]=new TH1F(TString::Format("h_%i_%i",j,i),TString::Format("h_%i_%i",j,i),20,0,1);
      
      TString folder=TString::Format("../output_%s/selection_cuts%i_",setup.Data(),cuts);
      TString filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";
      cout<<filename<<endl;
      TFile *f = new TFile(filename);
      h_costheta_radreturn[j][i] = (TH1F*)f->Get("h_costheta_radreturn");
      
      h_costheta_bb[j][i] = (TH1F*)f->Get("h_costheta_bb");
      h_costheta_qq[j][i] = (TH1F*)f->Get("h_costheta_qq");
      h_costheta_cc[j][i] = (TH1F*)f->Get("h_costheta_cc");
      
      h_costheta_all[j][i]->Add(h_costheta_bb[j][i]);
      h_costheta_all[j][i]->Add(h_costheta_cc[j][i]);
      h_costheta_all[j][i]->Add(h_costheta_qq[j][i]);
      
    }
    h_costheta_bb[j][1]->Divide(h_costheta_bb[j][0]);
    h_costheta_cc[j][1]->Divide(h_costheta_cc[j][0]);
    h_costheta_qq[j][1]->Divide(h_costheta_qq[j][0]);

    h_costheta_radreturn[j][1]->Divide(h_costheta_radreturn[j][0]);
    h_costheta_all[j][1]->Divide(h_costheta_all[j][0]);

  }
  
    
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
  leg1->SetHeader("Jet R-parameter=1.25");
  
   for(int j=0; j<3; j++) {
    
    h_costheta_all[j][1]->GetYaxis()->SetTitle("N_{selection}/N_{total} (Signal, all flavours)");
    h_costheta_all[j][1]->GetYaxis()->SetRangeUser(0,1.4);
    h_costheta_all[j][1]->GetXaxis()->SetRangeUser(0,1.);
    h_costheta_all[j][1]->GetXaxis()->SetTitle("|cos#theta_{q}|");
    h_costheta_all[j][1]->GetYaxis()->SetTitleOffset(1.3);
    
    if(j==2) h_costheta_all[j][1]->SetLineColor(4);
    else if(j==3) h_costheta_all[j][1]->SetLineColor(kGreen+2);
    else h_costheta_all[j][1]->SetLineColor(j+1);
    h_costheta_all[j][1]->SetLineStyle(j+1);
    h_costheta_all[j][1]->SetLineWidth(3+(j%2));
    h_costheta_all[j][1]->Draw("histosame");

    if(j==0) leg1->AddEntry(h_costheta_all[j][1],"K_{#gamma}^{reco.,geom.}<35 GeV","l");
    if(j==1) leg1->AddEntry(h_costheta_all[j][1],"Jet cleaning +K_{#gamma}^{reco.,geom.}<35 GeV + Kratios cut","l");
    if(j==2) leg1->AddEntry(h_costheta_all[j][1],"Jet cleaning +K_{#gamma}^{reco.,geom.}<35 GeV + m_{j1,j2}>130 GeV","l");
    


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
  leg2->SetHeader("Jet R-parameter=1.25");
  
  for(int j=0; j<3; j++) {

    
    h_costheta_radreturn[j][1]->GetYaxis()->SetTitle("N_{selection}/N_{total} (Rad.Ret., all flavours)");
    h_costheta_radreturn[j][1]->GetYaxis()->SetRangeUser(-1,1.4);
    h_costheta_radreturn[j][1]->GetXaxis()->SetRangeUser(0,1.);
    h_costheta_radreturn[j][1]->GetXaxis()->SetTitle("|cos#theta_{q}|");
    h_costheta_radreturn[j][1]->GetYaxis()->SetTitleOffset(1.3);
    
    if(j==2) h_costheta_radreturn[j][1]->SetLineColor(4);
    else if(j==3) h_costheta_radreturn[j][1]->SetLineColor(kGreen+2);
    else h_costheta_radreturn[j][1]->SetLineColor(j+1);
    h_costheta_radreturn[j][1]->SetLineStyle(j+1);
    h_costheta_radreturn[j][1]->SetLineWidth(3+(j%2));
    h_costheta_radreturn[j][1]->Draw("histosame");
    
    if(j==0) leg2->AddEntry(h_costheta_radreturn[j][1],"K_{#gamma}^{reco.,geom.}<35 GeV","l");
    if(j==1) leg2->AddEntry(h_costheta_radreturn[j][1],"Jet cleaning +K_{#gamma}^{reco.,geom.}<35 GeV + Kratios cut","l");
    if(j==2) leg2->AddEntry(h_costheta_radreturn[j][1],"Jet cleaning +K_{#gamma}^{reco.,geom.}<35 GeV + m_{j1,j2}>130 GeV","l");


  }
 
  Labels(pol);
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetBorderSize(0);
  leg2->Draw();
  
  // canvas2->Print(TString::Format("plots/B_S_rparam_Kcut35_%s.eps",pol.Data()));

  
  
}
