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
#include "../../../style/Style.C"
#include "../../../style/Labels.C"



void Labels(int i=0){

  QQBARLabel(0.25,0.952,"Work in Progress");
  /*if(i==0) QQBARLabel2(0.04,0.07, "Signal, uds-quark",kOrange+3);
  if(i==1) QQBARLabel2(0.04,0.07, "Signal, c-quark",kOrange+3);
  if(i==2) QQBARLabel2(0.04,0.07, "Signal, b-quark",kOrange+3);
  if(i==3) QQBARLabel2(0.04,0.07, "RadReturn, uds-quark",kOrange+3);
  if(i==4) QQBARLabel2(0.04,0.07, "RadReturn, c-quark",kOrange+3);
  if(i==5) QQBARLabel2(0.04,0.07, "RadReturn, b-quark",kOrange+3);
  if(i==6) QQBARLabel2(0.04,0.07, "Signal ALL",kOrange+3);*/

  float x=0.85;
  QQBARLabel2(x,0.965, "e_{L}^{-}e_{R}^{+}",kGray+2);
}

TH1F * getHisto(TString folder, TString file, TString histo, TString histo2) {

  TFile *f = new TFile(file);
  f->cd(folder);
  TH1F *h = (TH1F*)f->Get(folder+"/"+histo);
  TH1F *h2 = (TH1F*)f->Get(folder+"/"+histo2);

  h->Add(h2);
  // cout<<file<<" "<<folder+"/"+histo<<endl;
  return h;
}

TH1F * getHisto(TString folder, TString file, TString histo, TString histo2, TString histo3) {

  TFile *f = new TFile(file);
  f->cd(folder);
  TH1F *h = (TH1F*)f->Get(folder+"/"+histo);
  TH1F *h2 = (TH1F*)f->Get(folder+"/"+histo2);
  TH1F *h3 = (TH1F*)f->Get(folder+"/"+histo3);

  h->Add(h2);
  h->Add(h3);
  // cout<<file<<" "<<folder+"/"+histo<<endl;
  return h;
}


TH1F * getHisto(TString folder, TString file, TString histo) {

  TFile *f = new TFile(file);
  f->cd(folder);
  TH1F *h = (TH1F*)f->Get(folder+"/"+histo);
  // cout<<file<<" "<<folder+"/"+histo<<endl;
  return h;
}

TH1F * getHistoRemove0(TString folder, TString file, TString histo) {

  TFile *f = new TFile(file);
  f->cd(folder);
  TH1F *h = (TH1F*)f->Get(folder+"/"+histo);
  h->SetBinContent(1,0);
  // cout<<file<<" "<<folder+"/"+histo<<endl;
  return h;
}


void Compare_3Histos(TString name, std::vector<TH1F *> histos1, std::vector<TH1F *> histos2, int nfiles=2, bool normalized =true, bool log=true) {

  TCanvas * canvas1 = new TCanvas(name,name,1200,1200);

  int k=0;
  canvas1->Divide(3,6);
  for(int i=0; i<nfiles; i++) {
    int kc=0;
    for(int j=0; j<6; j++) {
      canvas1->cd(kc+1);
      gPad->SetLogy();
      histos1.at(k)->SetLineColor(i+1);
      if(i==2) histos1.at(k)->SetLineColor(4);
      histos1.at(k)->SetLineWidth(2);
      histos1.at(k)-> GetYaxis()->SetRangeUser(100,histos1.at(k)->GetMaximum()*1.2);
      if(normalized==true) histos1.at(k)-> DrawNormalized("same");
      else histos1.at(k)-> Draw("same");
      if(i== (nfiles-1) ) Labels(i);

      canvas1->cd(kc+2);
      gPad->SetLogy();
      histos1.at(k+1)->SetLineColor(i+1);
      if(i==2) histos1.at(k+1)->SetLineColor(4);
      histos1.at(k+1)->SetLineWidth(2);
      histos1.at(k+1)-> GetYaxis()->SetRangeUser(100,histos1.at(k+1)->GetMaximum()*1.2);
      if(normalized==true) histos1.at(k+1)-> DrawNormalized("same");
      else histos1.at(k+1)-> Draw("same");
      if(i== (nfiles-1) ) Labels(i);

      canvas1->cd(kc+3);
      gPad->SetLogy();
      histos1.at(k+2)->SetLineColor(i+1);
      if(i==2) histos1.at(k+2)->SetLineColor(4);
      histos1.at(k+2)->SetLineWidth(2);
      histos1.at(k+2)-> GetYaxis()->SetRangeUser(100,histos1.at(k+2)->GetMaximum()*1.2);
      if(normalized==true) histos1.at(k+2)-> DrawNormalized("same");
      else histos1.at(k+2)-> Draw("same");
      if(i== (nfiles-1) ) Labels(i);
      
      k+=3;
      kc+=3;
    }
  }


  TCanvas * canvas2 = new TCanvas(name+"_all",name+"_all",1800,600);
  canvas2->Divide(3,1);
  for(int kl=0; kl<3; kl++) {
    for(int i=0; i<nfiles; i++) {
      canvas2->cd(kl+1);
      gPad->SetLogy();
      histos2.at(kl+i*3)->SetLineColor(i+1);
      if(i==0) {
	if(kl==0) histos2.at(kl+i*3)->GetXaxis()->SetTitle("Phi [rad]");
	if(kl==1) histos2.at(kl+i*3)->GetXaxis()->SetTitle("#theta [rad]");
	if(kl==2) histos2.at(kl+i*3)->GetXaxis()->SetTitle("momentum [GeV]");
      }
      if(i==2) histos2.at(kl+i*3)->SetLineColor(4);
      histos2.at(kl+i*3)->SetLineWidth(2);
      histos2.at(kl+i*3)-> GetYaxis()->SetRangeUser(100,histos2.at(kl+i*3)->GetMaximum()*1.2);
      if(normalized==true) histos2.at(kl+i*3)-> DrawNormalized("same");
      else histos2.at(kl+i*3)-> Draw("same");
    }
    Labels(6);
  }
 


}

void Compare_2Histos(TString name, std::vector<TH1F *> histos1, std::vector<TH1F *> histos2, int nfiles=2, bool normalized =true, bool log=true) {

  TCanvas * canvas1 = new TCanvas(name,name,1200,1200);

  int k=0;
  canvas1->Divide(2,6);
  for(int i=0; i<nfiles; i++) {
    int kc=0;
    for(int j=0; j<6; j++) {
      canvas1->cd(kc+1);
      gPad->SetLogy();
      histos1.at(k)->SetLineColor(i+1);
      if(i==2) histos1.at(k)->SetLineColor(4);
      histos1.at(k)->SetLineWidth(2);
      histos1.at(k)-> GetYaxis()->SetRangeUser(100,histos1.at(k)->GetMaximum()*1.2);
      if(normalized==true) histos1.at(k)-> DrawNormalized("same");
      else histos1.at(k)-> Draw("same");
      if(i== (nfiles-1) ) Labels(i);

      canvas1->cd(kc+2);
      gPad->SetLogy();
      histos1.at(k+1)->SetLineColor(i+1);
      if(i==2) histos1.at(k+1)->SetLineColor(4);
      histos1.at(k+1)->SetLineWidth(2);
      histos1.at(k+1)-> GetYaxis()->SetRangeUser(100,histos1.at(k+1)->GetMaximum()*1.2);
      if(normalized==true) histos1.at(k+1)-> DrawNormalized("same");
      else histos1.at(k+1)-> Draw("same");
      if(i== (nfiles-1) ) Labels(i);
    
      k+=2;
      kc+=2;
    }
  }


  TCanvas * canvas2 = new TCanvas(name+"_all",name+"_all",1200,600);
  canvas2->Divide(2,1);
  for(int i=0; i<nfiles; i++) {
    for(int kl=0; kl<2; kl++) {
      canvas2->cd(kl+1);
      gPad->SetLogy();
      histos2.at(kl+i*2)->SetLineColor(i+1);
      if(i==2) histos2.at(kl+i*2)->SetLineColor(4);
      histos2.at(kl+i*2)->SetLineWidth(2);
      histos2.at(kl+i*2)-> GetYaxis()->SetRangeUser(100,histos2.at(kl+i*2)->GetMaximum()*1.2);
      if(normalized==true) histos2.at(kl+i*2)-> DrawNormalized("same");
      else histos2.at(kl+i*2)-> Draw("same");
      Labels(6);
      
    }
  }
 


}


void Compare_3HistosEventNorm(TString name, std::vector<TH1F *> histos1, std::vector<TH1F *> histos_quark, int nfiles=2, bool log=true) {

  for(int i=0; i<histos1.size(); i++) 
    histos1.at(i)->Scale(2./histos_quark.at(i)->GetEntries());
  
  TCanvas * canvas2 = new TCanvas(name+"_all_normevent",name+"_all_normevent",1200,600);
  canvas2->Divide(3,1);
  for(int i=0; i<nfiles; i++) {
    for(int kl=0; kl<3; kl++) {
      canvas2->cd(kl+1);
      gPad->SetLogy();
      histos1.at(kl+i*(nfiles+1))->SetLineColor(i+1);
      if(i==2) histos1.at(kl+i*(nfiles+1))->SetLineColor(4);
      histos1.at(kl+i*(nfiles+1))->SetLineWidth(2);
      histos1.at(kl+i*(nfiles+1))-> GetYaxis()->SetRangeUser(100,histos1.at(kl+i*(nfiles+1))->GetMaximum()*1.2);
      histos1.at(kl+i*(nfiles+1))-> Draw("histosame");
      Labels(6);
      
    }
  }
}

void Compare_3Histos(TString name, std::vector<TH1F *> histos1, bool log=true, std::vector<TString> leg={}, TString x="N", TString y="entries") {


  TCanvas * canvas2 = new TCanvas(name,name,800,800);
  canvas2->cd(1);
  if(log==true) gPad->SetLogy();
  for(int i=0; i<histos1.size(); i++) {
    if(i==0) {
      histos1.at(0)->GetXaxis()->SetTitle(x);
      histos1.at(0)->GetYaxis()->SetTitle(y);
    }
    histos1.at(i)->SetLineColor(i+1);
    if(i>0) histos1.at(i)->SetLineStyle(2);
    if(i==2) histos1.at(i)->SetLineColor(4);
    histos1.at(i)->SetLineWidth(2);
    histos1.at(i)-> GetYaxis()->SetRangeUser(100,histos1.at(i)->GetMaximum()*1.2);
    histos1.at(i)-> Draw("histosame");
  }

  if(leg.size()!=0) {
    TLegend *leg1= new TLegend(0.5,0.7,0.9,0.9);
    leg1->SetHeader(name);
    for(int i=0; i<leg.size(); i++)   leg1->AddEntry(histos1.at(i),leg.at(i),"lf");
    leg1->SetFillStyle(0);
    leg1->SetLineWidth(0);
    leg1->SetLineColor(0);
    leg1->SetBorderSize(0);
    leg1->Draw();

  }
  Labels();
  
}

void Compare_3HistosStack(TString name, std::vector<TH1F *> histos1, std::vector<TString> leg, TString x="", TString y="entries / normalized per flavour") {

  THStack *hs = new THStack("hs","");
  
  for(int i=0; i<histos1.size(); i++) {
    histos1.at(i)->Scale(1./histos1.at(i)->GetEntries());
    if(i==0) {
      histos1.at(i)->SetLineColor(kGreen+2);
      histos1.at(i)->SetFillColor(kGreen+2);
    }
    if(i==1) {
      histos1.at(i)->SetLineColor(kOrange);
      histos1.at(i)->SetFillColor(kOrange);
    }
    //  if(i>0) histos1.at(i)->SetLineStyle(2);
    if(i==2){
      histos1.at(i)->SetLineColor(kGray+2);
      histos1.at(i)->SetFillColor(kGray+2);
    }
    histos1.at(i)->SetLineWidth(2);
    //  histos1.at(i)-> Draw("histosame");
    //Labels(6);
    hs->Add(histos1.at(i));
  }
  TCanvas * canvas2 = new TCanvas(name,name,800,800);
  canvas2->cd(1);
  gPad->SetLogy();

  hs->Draw("histo");
  hs->GetXaxis()->SetTitle(x);
  hs->GetYaxis()->SetTitle(y);
  
  if(leg.size()!=0) {
    TLegend *leg1= new TLegend(0.6,0.6,0.9,0.9);
    leg1->SetHeader(name);
    for(int i=0; i<leg.size(); i++) leg1->AddEntry(histos1.at(i),leg.at(i),"lf");
    leg1->SetFillStyle(0);
    leg1->SetLineWidth(0);
    leg1->SetLineColor(0);
    leg1->SetBorderSize(0);
    leg1->Draw();

  }
  Labels();
  
}


void Compare_3Histos2Stack(TString name, std::vector<TH1F *> histos1, std::vector<TString> leg, TString x="momentum [GeV]", TString y="entries") {

  THStack *hs = new THStack("hs","");

  for(int i=1; i<histos1.size(); i++) {
    histos1.at(i)->SetLineColor(i+1);
    histos1.at(i)->SetFillColor(i+1);

    //  if(i>0) histos1.at(i)->SetLineStyle(2);
    if(i==2){
      histos1.at(i)->SetLineColor(4);
      histos1.at(i)->SetFillColor(4);
    }
    histos1.at(i)->SetLineWidth(2);
    //  histos1.at(i)-> Draw("histosame");
    //Labels(6);
    hs->Add(histos1.at(i));
  }
  TCanvas * canvas2 = new TCanvas(name,name,800,800);
  gPad->SetLogy();

  canvas2->cd(1);
  histos1.at(0)->SetLineColor(1);
  histos1.at(0)->SetFillColor(1);
  histos1.at(0)->GetXaxis()->SetTitle(x);
  histos1.at(0)->GetYaxis()->SetTitle(y);
  histos1.at(0)->Draw("histosame");
  hs->Draw("histosame");

  if(leg.size()!=0) {
    TLegend *leg1= new TLegend(0.6,0.6,0.9,0.9);
    leg1->SetHeader(name);
    for(int i=0; i<leg.size(); i++) leg1->AddEntry(histos1.at(i),leg.at(i),"lf");
    leg1->SetFillStyle(0);
    leg1->SetLineWidth(0);
    leg1->SetLineColor(0);
    leg1->SetBorderSize(0);
    leg1->Draw();

  }
  Labels();

}
