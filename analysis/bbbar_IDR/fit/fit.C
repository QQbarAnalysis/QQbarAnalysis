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
#include "TLine.h"
#include "../../style/Style.C"
#include "../../style/Labels.C"

int nbins=20;
TString pol = "eL";
TString folder = "../output/";//output/kt_20190202";
TString model = "l5_valencia2.0";

Double_t asymmetry_f(Double_t *x, Double_t *par)
{
  
  Double_t fitval = par[0]*(1+x[0]*x[0]) + par[1]*x[0];
  return fitval;
}

void plot(TF1* func, TH1F * histo){
  
  func->SetFillColor(2);
  func->SetFillStyle(3001);

  func->Draw("E3");
  histo->Draw("HEsame");

}

float Afb_v(float plus, float minus) {
  if(plus>0 && minus>0) 
    return (plus-minus)/(plus+minus);
  else return 0;

}

float dAfb_v(float plus, float minus, float plus_e, float minus_e) {
  
  if(plus>0 && minus>0) 
    return 2 / ((plus+minus)*(plus+minus)) * sqrt(plus*plus*plus_e*plus_e + minus*minus*minus_e*minus_e);
  else return 0;

}

TF1 * fit_histo(TH1F * histo, float lumi_factor) {

  double x[40], ex[40], y[40], ey[40];
  for(int i=0; i<nbins; i++) {
    x[i]=0;
    ex[i]=0;
    y[i]=0;
    ey[i]=0;
    x[i]=histo->GetBinCenter(i+1);
    //ex[i]=0.025;
    float error_p=sqrt(histo->GetBinError(i+1)*histo->GetBinError(i+1) - histo->GetBinContent(i+1));

    y[i]=lumi_factor*histo->GetBinContent(i+1);
    ey[i]=sqrt(lumi_factor)*histo->GetBinError(i+1);
  }

  TGraphErrors * g_histo = new TGraphErrors(nbins,x,y,ex,ey);
  float range_up=0.7;
  float range_down=-0.7;

  TF1 *func_fit = new TF1("asymmetry_f",asymmetry_f,range_down,range_up,2);
  func_fit->SetParNames("S","A");
 
  TFitResultPtr r = g_histo->Fit("asymmetry_f", "QRS");
  // r->Print("V");

  g_histo->Draw("alp");
  TF1 *func = new TF1("asymmetry_f",asymmetry_f,-1,1,2);
  func->SetParNames("S","A");
  func->SetParameter(0,func_fit->GetParameter(0));
  func->SetParameter(1,func_fit->GetParameter(1));
  func->SetParError(0,func_fit->GetParError(0));
  func->SetParError(1,func_fit->GetParError(1));

  // results

  float plus = func->Integral(0,1);
  float minus = func->Integral(-1,0);
  float plus_e = func->IntegralError(0,1);
  float minus_e = func->IntegralError(1,0);
  float Afb=Afb_v(plus,minus);
  float dAfb=dAfb_v(plus,minus, plus_e, minus_e);
 
  cout << "Afb = "<< Afb<< " +- " << dAfb << "  ( "<<100.*dAfb/Afb<<" %)"<< endl;
  float S=func_fit->GetParameter(0);
  float dS=func_fit->GetParError(0);
  cout << "S/bin_size = "<< S*2./nbins<< " +- " << dS*2./nbins << "  ( "<<100.*dS/S<<" %)"<< endl;
  float A=func_fit->GetParameter(1);
  float dA=func_fit->GetParError(1);
  cout << "A/bin_size = "<< A*2./nbins<< " +- " << dA*2./nbins << "  ( "<<100.*dA/A<<" %)"<< endl;
  cout << "Correl = "<<r->GetCorrelationMatrix()[0][1]<< endl;
  cout << "Chi2 = "<<func_fit->GetChisquare()<<", NDF ="<<func_fit->GetNDF()<<" Chi2/NDF= "<<func_fit->GetChisquare()/func_fit->GetNDF()<<endl;


  TF1 *func_return = new TF1("asymmetry_f",asymmetry_f,-0.7,0.7,2);
  func_return->SetParNames("S","A");
  func_return->SetParameter(0,func_fit->GetParameter(0));
  func_return->SetParameter(1,func_fit->GetParameter(1));
  func_return->SetParError(0,func_fit->GetParError(0));
  func_return->SetParError(1,func_fit->GetParError(1));
  return func_return;


}

void fit() {

 
  TString filename = TString::Format("%s/bbbar_%s_cuts3_500GeV_%s_btag1_0.9_btag2_0.2_nbins%i.root",folder.Data(),model.Data(),pol.Data(),nbins);
  TFile *f = new TFile(filename);
  TH1F *h_corrected = (TH1F*)f->Get("corrected");
  h_corrected->Sumw2();


  TH1F *h_parton = (TH1F*)f->Get("parton");
  h_parton->Sumw2();

  TH1F *h_eff = (TH1F*)f->Get("parton_recocuts");
  h_eff->Sumw2();
  h_eff->Divide(h_parton);

  double max =0;
  for(int i=nbins/2; i<nbins; i++) if(h_eff->GetBinContent(i+1)>max) max = h_eff->GetBinContent(i+1);
  h_eff->Scale(1./max);



  TH1F *h_noncorrected = new TH1F("h_noncorrected","h_noncorrected",nbins,-1,1);

  for(int i=0; i<nbins+2; i++) {  

    if(h_corrected->GetBinContent(i)<1000000 && h_corrected->GetBinError(i)>0) {
      h_noncorrected->SetBinContent(i,h_corrected->GetBinContent(i));
      h_noncorrected->SetBinError(i,h_corrected->GetBinError(i));
    } else {
      h_noncorrected->SetBinContent(i,h_corrected->GetBinContent(i));
      h_noncorrected->SetBinError(i,h_corrected->GetBinError(i));
    }

    double error = (h_corrected->GetBinContent(i)/h_eff->GetBinContent(i))*sqrt(pow(h_corrected->GetBinError(i)/h_corrected->GetBinContent(i),2)+0.25*pow(h_eff->GetBinError(i) /h_eff->GetBinContent(i),2));
    error= sqrt(error*error +  0.0*0.01*pow(h_corrected->GetBinContent(i)/h_eff->GetBinContent(i)-h_corrected->GetBinContent(i),2));
    //double error = sqrt( pow((h_corrected->GetBinContent(i)/h_eff->GetBinContent(i))*
    //			     sqrt(pow(h_corrected->GetBinError(i)/h_corrected->GetBinContent(i),2)+0.25*pow(h_eff->GetBinError(i)/h_eff->GetBinContent(i),2)),2) + 0.1*0.1*pow(h_corrected->GetBinContent(i)/h_eff->GetBinContent(i)-h_corrected->GetBinContent(i),2));
 
    if(h_eff->GetBinContent(i)>0 ) {
      h_corrected->SetBinError(i,error);
      h_corrected->SetBinContent(i,h_corrected->GetBinContent(i)/(h_eff->GetBinContent(i)));
    } else {
      h_corrected->SetBinError(i,0);
      h_corrected->SetBinContent(i,0);
    }

  }

  //  h_corrected->Divide(h_eff);
  
  double integtral_parton= h_parton->Integral(4,16);//nbins/2-nbins/3,nbins/2+nbins/3);//
  double integtral_truth= h_corrected->Integral(4,16);
  h_parton->Scale(integtral_truth/integtral_parton);
  
  TString lumi= "46fb-1,";
  int ilumi=1;
  TCanvas * canvasdead = new TCanvas ("canvasdead","canvasdead",1000,800);
  canvasdead->cd();
  if(pol=="eL") cout<<" ####### LEFT POLARIZATION " <<endl;
  else cout<<" ####### RIGHT POLARIZATION " <<endl;
  cout<<" ------------------------ "<<endl;
  cout<<lumi+" parton level distribution "<<endl;
  TF1 * fitresult1 = fit_histo(h_parton,ilumi);
  cout<<"  "<<endl;
  

  cout<<lumi+" reco + acceptance correction (+10% unc.) "<<endl; 
  TF1 * fitresult3 = fit_histo(h_corrected,ilumi);
  
  TH1F *pull = new TH1F("pull","pull",nbins,-1,1);
  TH1F *pull2 = new TH1F("pull2","pull2",nbins,-1,1);
  TH1F *pull3 = new TH1F("pull3","pull3",nbins,-1,1);
  pull->Sumw2();
  pull2->Sumw2();
  pull3->Sumw2();

  cout<<"  "<<endl;
  cout<<"  "<<endl;
  cout<<lumi+" not corrected "<<endl;
  TF1 * fitresult2 = fit_histo(h_noncorrected,ilumi);
  cout<<"  "<<endl;

  for(int i=nbins/2-1; i<nbins; i++) {
    if(h_corrected->GetBinError(i+1)>0 && h_corrected->GetBinError(-nbins/2+i+1)>0) {
      double value_a = (fitresult3->Eval(h_corrected->GetBinCenter(i+1))-h_corrected->GetBinContent(i+1)) /h_corrected->GetBinError(i+1);
      double w_a= h_corrected->GetBinContent(i+1);
      double value_b = (fitresult3->Eval(h_corrected->GetBinCenter(-nbins/2+i+1))-h_corrected->GetBinContent(-nbins/2+i+1))/h_corrected->GetBinError(-nbins/2+i+1);
      double w_b= h_corrected->GetBinContent(-nbins/2+i+1);
      pull->SetBinContent(i+1,(value_a*w_a+value_b+w_b)/(w_a+w_b));
    } else {
      pull->SetBinContent(i+1,1);
    }
    if(h_noncorrected->GetBinContent(i+1)>0 && h_noncorrected->GetBinContent(-nbins/2+i+1)>0) {
      double value_a = (fitresult2->Eval(h_noncorrected->GetBinCenter(i+1))-h_noncorrected->GetBinContent(i+1)) /h_noncorrected->GetBinError(i+1);
      double w_a= h_noncorrected->GetBinContent(i+1);
      double value_b = (fitresult2->Eval(h_noncorrected->GetBinCenter(-nbins/2+i+1))-h_noncorrected->GetBinContent(-nbins/2+i+1))/h_noncorrected->GetBinError(-nbins/2+i+1);
      double w_b= h_noncorrected->GetBinContent(-nbins/2+i+1);
      pull2->SetBinContent(i+1,(value_a*w_a+value_b+w_b)/(w_a+w_b));
    } else {
      pull2->SetBinContent(i+1,1);
    }

    if(h_parton->GetBinError(i+1)>0 && h_parton->GetBinError(-nbins/2+i+1)>0) {
      double value_a = (fitresult1->Eval(h_parton->GetBinCenter(i+1))-h_parton->GetBinContent(i+1)) /h_parton->GetBinError(i+1);
      double w_a= h_parton->GetBinContent(i+1);
      double value_b = (fitresult1->Eval(h_parton->GetBinCenter(-nbins/2+i+1))-h_parton->GetBinContent(-nbins/2+i+1))/h_parton->GetBinError(-nbins/2+i+1);
      double w_b= h_parton->GetBinContent(-nbins/2+i+1);
      pull3->SetBinContent(i+1,(value_a*w_a+value_b+w_b)/(w_a+w_b));
    } else {
      pull3->SetBinContent(i+1,1);
    }

   }



  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  gStyle->SetTitleX(0.2); 
  gStyle->SetTitleY(0.9); 
  gStyle->SetLegendFont(42);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(0.3);
      
  TCanvas * canvas0 = new TCanvas ("canvas0","canvas0",1000,800);
  canvas0->cd(1);
  if(model=="l5") h_parton->SetTitle("e_{L}^{+}e_{R}^{-}#rightarrow b#bar{b} @ 500GeV, 46 fb^{-1}, l5 model");
  else h_parton->SetTitle("e_{L}^{+}e_{R}^{-}#rightarrow b#bar{b} @ 500GeV, 46 fb^{-1}, s5 model");
  h_parton->GetXaxis()->SetTitle("cos(#theta)");
  h_parton->GetYaxis()->SetTitle("entries / 0.05 rad");
  h_parton->GetYaxis()->SetTitleOffset(2.05);
  h_parton->GetYaxis()->SetRangeUser(0,h_parton->GetMaximum()*1.1);

  h_parton->SetLineColor(3);
  h_parton->SetFillColor(3);
  h_parton->SetFillStyle(3001);
  h_parton->Draw("histo");
    
  h_corrected->SetLineColor(4);
  h_corrected->SetLineWidth(2);
  h_corrected->SetMarkerColor(4);
  h_corrected->SetMarkerStyle(1);
  h_corrected->Draw("pesame");

  h_noncorrected->SetLineColor(2);
  h_noncorrected->SetLineWidth(2);
  h_noncorrected->SetMarkerColor(2);
  h_noncorrected->SetMarkerStyle(1);
  h_noncorrected->Draw("psamel");
  
  
  // h_corrected_clone->SetLineColor(2);
  // h_corrected_clone->Draw("lpsame");
  
  fitresult3->SetLineColor(4);
  fitresult3->SetLineStyle(3);
  fitresult3->SetLineWidth(2);
  fitresult3->Draw("lsame");


  QQBARLabel(0.5,0.2,"Work in progress");

  TLegend *leg = new TLegend(0.2,0.65,0.55,0.8);
  leg->AddEntry(h_parton,"parton level","lf");
  leg->AddEntry(h_corrected,"signal (+ acceptance correction)","lep");
  leg->AddEntry(fitresult3,"fit","l");
  leg->AddEntry(h_noncorrected,"signal (w/o acceptance correction)","le");
  // leg->AddEntry(h_corrected_clone,"not corrected","lep");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  // canvas0->Print("canvas0.eps");
    TCanvas * canvas = new TCanvas ("canvas","canvas",1000,800);
  // canvas->Divide(2,1);
  canvas->cd(1);
  gPad->SetGridy();
  gPad->SetGridx();

  if(model=="l5") pull->SetTitle("IDR-L");
  else pull->SetTitle("IDR-S");
  pull->SetLineColor(4);
  pull->SetLineWidth(2);
  pull->GetXaxis()->SetTitle("#pm cos(#theta)");
  pull->GetYaxis()->SetTitle("#bar{(fit - X)/ #sigma_{X}}");
  pull->GetYaxis()->SetTitleOffset(1.6);
  pull->GetYaxis()->SetRangeUser(-10,10);
  pull->GetXaxis()->SetRangeUser(0,1);

  pull->Draw("l");
  
  pull2->SetLineColor(2);
  pull2->SetLineWidth(2);
  pull2->Draw("lsame");

  pull3->SetLineColor(3);
  pull3->SetLineWidth(3);
  pull3->Draw("lsame");

  QQBARLabel(0.2,0.2,"Work in progress");

  TLegend *leg2 = new TLegend(0.5,0.25,0.93,0.4);
  leg2->AddEntry(pull,"X = signal + full correction","l");
  leg2->AddEntry(pull2,"X = signal w/o correction","l");
  leg2->AddEntry(pull3,"X = parton level","l");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();
  

    

  
}
