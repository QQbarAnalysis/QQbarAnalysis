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

TF1 * fit_histo(TH1F * histo, float lumi_factor,bool fiducial) {

  double x[40], ex[40], y[40], ey[40];
  for(int i=0; i<40; i++) {
    x[i]=0;
    ex[i]=0;
    y[i]=0;
    ey[i]=0;
    x[i]=histo->GetBinCenter(i+1);
    //ex[i]=0.025;
    float error_p=sqrt(histo->GetBinError(i+1)*histo->GetBinError(i+1) - histo->GetBinContent(i+1));
    // cout<<histo->GetBinError(i+1)<<" "<<sqrt(histo->GetBinContent(i+1))<<" "<<error_p<<endl;

    y[i]=lumi_factor*histo->GetBinContent(i+1);
    ey[i]=sqrt(lumi_factor)*histo->GetBinError(i+1);// lumi_factor*error_p*error_p + lumi_factor*histo->GetBinContent(i+1));//histo->GetBinError(i+1);//sqrt(2*histo->GetBinContent(i+1)+error_p*error_p);// histo->GetBinError(i+1);//sqrt(histo->GetBinContent(i+1));
  }

  TGraphErrors * g_histo = new TGraphErrors(40,x,y,ex,ey);
  float range_up=0.8;
  float range_down=-0.8;
  if(fiducial==false) {
    range_up=1;
    range_down=-1;
  }
  TF1 *func_fit = new TF1("asymmetry_f",asymmetry_f,range_down,range_up,2);
  func_fit->SetParNames("S","A");
 
  TFitResultPtr r = g_histo->Fit("asymmetry_f", "QRS");
  // r->Print("V");

  
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
  float minus_e = func->IntegralError(-1,0);
  float Afb=Afb_v(plus,minus);
  float dAfb=dAfb_v(plus,minus, plus_e, minus_e);
 
  cout << "Afb = "<< Afb<< " +- " << dAfb << "  ( "<<100.*dAfb/Afb<<" %)"<< endl;
  float S=func_fit->GetParameter(0);
  float dS=func_fit->GetParError(0);
  cout << "S = "<< S<< " +- " << dS << "  ( "<<100.*dS/S<<" %)"<< endl;
  float A=func_fit->GetParameter(1);
  float dA=func_fit->GetParError(1);
  cout << "A = "<< A<< " +- " << dA << "  ( "<<100.*dA/A<<" %)"<< endl;
  cout << "Correl = "<<r->GetCorrelationMatrix()[0][1]<< endl;
  //  if(lumi_factor==1) plot(func_fit,histo);

  return func;

}

TF1 * fit_histo_bkg(TH1F * histo, TH1F * bkg, float lumi_factor,bool fiducial) {

  double x[40], ex[40], y[40], ey[40];
  cout<< "Total bkg=" <<100.*bkg->Integral()/histo->Integral()<<" %"<<endl;

  for(int i=0; i<40; i++) {
    x[i]=0;
    ex[i]=0;
    y[i]=0;
    ey[i]=0;
    x[i]=histo->GetBinCenter(i+1);
    float error_p=sqrt(histo->GetBinError(i+1)*histo->GetBinError(i+1) - histo->GetBinContent(i+1));

    y[i]=lumi_factor*histo->GetBinContent(i+1);
    // ey[i]=sqrt(lumi_factor)*histo->GetBinError(i+1);

    ey[i]=sqrt(lumi_factor*histo->GetBinError(i+1)*histo->GetBinError(i+1)+lumi_factor*bkg->GetBinError(i+1)*bkg->GetBinError(i+1)); 
  }

  TGraphErrors * g_histo = new TGraphErrors(40,x,y,ex,ey);
  float range_up=0.8;
  float range_down=-0.8;
  if(fiducial==false) {
    range_up=1;
    range_down=-1;
  }
  TF1 *func_fit = new TF1("asymmetry_f",asymmetry_f,range_down,range_up,2);
  func_fit->SetParNames("S","A");
 
  TFitResultPtr r = g_histo->Fit("asymmetry_f", "QRS");
  // r->Print("V");

  
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
  float minus_e = func->IntegralError(-1,0);
  float Afb=Afb_v(plus,minus);
  float dAfb=dAfb_v(plus,minus, plus_e, minus_e);

  cout << "Afb = "<< Afb<< " +- " << dAfb << "  ( "<<100.*dAfb/Afb<<" %)"<< endl;
  float S=func_fit->GetParameter(0);
  float dS=func_fit->GetParError(0);
  cout << "S = "<< S<< " +- " << dS << "  ( "<<100.*dS/S<<" %)"<< endl;
  float A=func_fit->GetParameter(1);
  float dA=func_fit->GetParError(1);
  cout << "A = "<< A<< " +- " << dA << "  ( "<<100.*dA/A<<" %)"<< endl;
  cout << "Correl = "<<r->GetCorrelationMatrix()[0][1]<< endl;
  //  if(lumi_factor==1) plot(func_fit,histo);

  return func;

}

TH1F *uniform_bkg(TH1F* histo, float size, float unc) {
  TH1F * test = new TH1F("test","test",40,-1,1);

  float integral = (size/100)*histo->Integral();
  for(int i=0; i<40; i++) {
    test->SetBinContent(i+1,integral/40);
    test->SetBinError(i+1,(unc/100)*test->GetBinContent(i+1));
  }
  test->Draw("l");
  return test;
}

TH1F *func1_bkg(TH1F* histo, float size, float unc) {
  TH1F * test = new TH1F("test","test",40,-1,1);

  float integral = (size/100)*histo->Integral();
  float b=integral;
  for(int i=0; i<40; i++) {
    test->SetBinContent(i+1,b*(1+histo->GetBinCenter(i+1))/40.);
    test->SetBinError(i+1,(unc/100)*test->GetBinContent(i+1));
  }
  test->Draw("l");
  return test;
}

TH1F *func2_bkg(TH1F* histo, float size, float unc) {
  TH1F * test = new TH1F("test","test",40,-1,1);

  float integral = (size/100)*histo->Integral();
  float b=integral;
  for(int i=0; i<40; i++) {
    test->SetBinContent(i+1,b*(1-histo->GetBinCenter(i+1))/40.);
    test->SetBinError(i+1,(unc/100)*test->GetBinContent(i+1));
  }
  test->Draw("l");
  return test;
}

TH1F *func3_bkg(TH1F* histo, float size, float unc) {
  TH1F * test = new TH1F("test","test",40,-1,1);

  float integral = (size/100)*histo->Integral();
  float b=integral;
  for(int i=0; i<40; i++) {
    test->SetBinContent(i+1,b*(histo->GetBinCenter(i+1))/40.);
    test->SetBinError(i+1,(unc/100)*test->GetBinContent(i+1));
  }
  test->Draw("l");
  return test;
}

TH1F *func4_bkg(TH1F* histo, float size, float unc) {
  TH1F * test = new TH1F("test","test",40,-1,1);

  float integral = (size/100)*histo->Integral();
  float b=integral;
  for(int i=0; i<40; i++) {
    test->SetBinContent(i+1,-b*(histo->GetBinCenter(i+1))/40.);
    test->SetBinError(i+1,(unc/100)*test->GetBinContent(i+1));
  }
  test->Draw("l");
  return test;
}

void fit() {
      
  cout<<" ######################## "<<endl;
  cout<<"Right Handed polarization "<< endl;
  
  TFile *f = new TFile("bbbar_250GeV_eR_260fb.root");
  
  TH1F *h_corrected = (TH1F*)f->Get("corrected");
  TH1F *h_truth = (TH1F*)f->Get("truth");
  TH1F *h_parton = (TH1F*)f->Get("parton");
  TH1F *h_bkg = (TH1F*)f->Get("bkg_qq");

  for(int ilumi=1; ilumi<2; ilumi++) {
    TString lumi= "250fb-1,";
    if(ilumi==2) lumi="500fb-1,";
    if(ilumi==3) lumi="750fb-1,";
    if(ilumi==4) lumi="1000fb-1,";

    cout<<" ------------------------ "<<endl;
    cout<<lumi+" parton level distribution "<<endl;
    TF1 * fitresult1 = fit_histo(h_parton,ilumi,false);
    cout<<" ------------------------ "<<endl;
    cout<<lumi+" parton level distribution (for accepted events) "<<endl; 
    TF1 * fitresult2 = fit_histo(h_truth,ilumi,true);
    cout<<" ------------------------ "<<endl;
    cout<<lumi+" reco (and corrected) distribution "<<endl; 
    TF1 * fitresult3 = fit_histo(h_corrected,ilumi,true);
    cout<<"  "<<endl;
  }
  cout<<" ------------------------ "<<endl;
  cout<<"1000fb-1, reco (and corrected) distribution "<<endl; 
  TF1 * fitresult = fit_histo(h_corrected,4,true);
  cout<<" ------------------------ "<<endl;
  cout<<"1000fb-1, error including stat uncertainty of Z-recoil and cc bkg"<<endl; 
  TF1 * fitresult_bkg1 = fit_histo_bkg(h_corrected,h_bkg,4,true);

  cout<<" ------------------------ "<<endl;
  TH1F *h_bkg2=uniform_bkg(h_corrected,5,1);
  cout<<"1000fb-1, assuming uniform bkg with 10% unc"<<endl; 
  TF1 * fitresult_bkg2 = fit_histo_bkg(h_corrected,h_bkg2,4,true);

  cout<<" ------------------------ "<<endl;
  TH1F *h_bkg3=func1_bkg(h_corrected,5,1);
  cout<<"1000fb-1, assuming B(1+cos(theta)) bkg with 10% unc"<<endl; 
  TF1 * fitresult_bkg3 = fit_histo_bkg(h_corrected,h_bkg3,4,true);

  cout<<" ------------------------ "<<endl;
  TH1F *h_bkg4=func2_bkg(h_corrected,5,1);
  cout<<"1000fb-1, assuming B(1-cos(theta)) bkg with 10% unc"<<endl; 
  TF1 * fitresult_bkg4 = fit_histo_bkg(h_corrected,h_bkg4,4,true);

  cout<<" ------------------------ "<<endl;
  TH1F *h_bkg5=func3_bkg(h_corrected,5,1);
  cout<<"1000fb-1, assuming B(cos(theta)) bkg with 10% unc"<<endl; 
  TF1 * fitresult_bkg5 = fit_histo_bkg(h_corrected,h_bkg5,4,true);

  cout<<" ------------------------ "<<endl;
  TH1F *h_bkg6=func4_bkg(h_corrected,5,1);
  cout<<"1000fb-1, assuming B(-cos(theta)) bkg with 10% unc"<<endl; 
  TF1 * fitresult_bkg6 = fit_histo_bkg(h_corrected,h_bkg6,4,true);

}

