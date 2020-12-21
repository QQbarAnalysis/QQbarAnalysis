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
#include "correction.h"
#include "../../style/Style.C"
#include "../../style/Labels.C"

int nbins=40;
TString pol = "eR";
TString folder = "../../output_20200427";//output/kt_20190202";
TString sample = "genkt_restorer";//"radret_genkt_R125"

Double_t asymmetry_f(Double_t *x, Double_t *par)
{
  
  Double_t fitval = par[0]*(1+x[0]*x[0]) + par[1]*x[0];
  return fitval;
}

std::vector<float> Afb_v(TF1* func) {

  float plus = func->Integral(0,1);
  float minus = func->Integral(-1,0);
  float plus_e = func->IntegralError(0,1);
  float minus_e = func->IntegralError(-1,0);
  
  float afb=0, dafb=0;
  
  // if(plus>0 && minus>0) 
  afb= (plus-minus)/(plus+minus);
  
    //  if(plus>0 && minus>0) 
  dafb= 2 / ((plus+minus)*(plus+minus)) * sqrt(plus*plus*plus_e*plus_e + minus*minus*minus_e*minus_e);

  std::vector<float> result;
  result.push_back(afb);
  result.push_back(dafb);
  result.push_back(func->GetParameter(0));
  result.push_back(func->GetParError(0));
  result.push_back(func->GetParameter(1));
  result.push_back(func->GetParError(1));
  return result;

}


TF1 * fit_histo(TH1F * histo, bool debug=true) {
  
  double x[40], ex[40], y[40], ey[40];
  for(int i=0; i<nbins; i++) {
    x[i]=0;
    ex[i]=0;
    y[i]=0;
    ey[i]=0;
    x[i]=histo->GetBinCenter(i+1);
    //ex[i]=0.025;
    float error_p=sqrt(histo->GetBinError(i+1)*histo->GetBinError(i+1) - histo->GetBinContent(i+1));

    y[i]=histo->GetBinContent(i+1);
    ey[i]=histo->GetBinError(i+1);//sqrt(eff*histo->GetBinContent(i+1));//histo->GetBinError(i+1)/sqrt(eff);// lumi_factor*error_p*error_p + lumi_factor*histo->GetBinContent(i+1));//histo->GetBinError(i+1);//sqrt(2*histo->GetBinContent(i+1)+error_p*error_p);// histo->GetBinError(i+1);//sqrt(histo->GetBinContent(i+1));
  }

  TGraphErrors * g_histo = new TGraphErrors(nbins,x,y,ex,ey);
  float range_up=0.80;
  float range_down=-0.80;

  TF1 *func_fit = new TF1("asymmetry_f",asymmetry_f,range_down,range_up,2);
  func_fit->SetParNames("S","A");
 
  TFitResultPtr r = g_histo->Fit("asymmetry_f", "QRS");

  g_histo->Draw("alp");
  TF1 *func = new TF1("asymmetry_f",asymmetry_f,-1,1,2);
  func->SetParNames("S","A");
  func->SetParameter(0,func_fit->GetParameter(0));
  func->SetParameter(1,func_fit->GetParameter(1));
  func->SetParError(0,func_fit->GetParError(0));
  func->SetParError(1,func_fit->GetParError(1));



  if(debug==true) {
    // results
    std::vector<float> Afbv=Afb_v(func);
    float Afb=Afbv.at(0);
    float dAfb=Afbv.at(1);
    
    float S=func_fit->GetParameter(0);
    float dS=func_fit->GetParError(0);
    float A=func_fit->GetParameter(1);
    float dA=func_fit->GetParError(1);
    cout << "Afb = "<< Afb<< " +- " << dAfb << "  ( "<<100.*dAfb/Afb<<" %)"<< endl;
    cout << "S/bin_size = "<< S*2./nbins<< " +- " << dS*2./nbins << "  ( "<<100.*dS/S<<" %)"<< endl;
    cout << "A/bin_size = "<< A*2./nbins<< " +- " << dA*2./nbins << "  ( "<<100.*dA/A<<" %)"<< endl;
    cout << "Correl = "<<r->GetCorrelationMatrix()[0][1]<< endl;
    cout << "Chi2 = "<<func_fit->GetChisquare()<<", NDF ="<<func_fit->GetNDF()<<" Chi2/NDF= "<<func_fit->GetChisquare()/func_fit->GetNDF()<<endl;
  }

  TF1 *func_return = new TF1("asymmetry_f",asymmetry_f,-1,1,2);
  func_return->SetParNames("S","A");
  func_return->SetParameter(0,func_fit->GetParameter(0));
  func_return->SetParameter(1,func_fit->GetParameter(1));
  func_return->SetParError(0,func_fit->GetParError(0));
  func_return->SetParError(1,func_fit->GetParError(1));
  return func_return;


}


TF1 * fit_histo_difference(TH1F * histo, TH1F* histo2, float eff=0.25, float error_eff=0.01, bool debug=true) {

  histo2->Divide(histo);

  TH1F *histo3= new TH1F("hist3","histo3",40,-1,1);
  
  double max =0;
  for(int i=nbins/2; i<nbins; i++) if(histo2->GetBinContent(i+1)>max) max = histo2->GetBinContent(i+1);
  
  for(int i=0; i<nbins/2; i++) {
    histo3->SetBinContent(i+1,histo2->GetBinContent(20+i+1)/max);
    histo3->SetBinContent(20+i+1,histo2->GetBinContent(20+i+1)/max);
  }
			  
  double x[40], ex[40], y[40], ey[40];
  for(int i=0; i<nbins; i++) {
    x[i]=0;
    ex[i]=0;
    y[i]=0;
    ey[i]=0;
    x[i]=histo->GetBinCenter(i+1);
    //ex[i]=0.025;
    float error=sqrt(eff*histo->GetBinContent(i+1) + pow((histo->GetBinContent(i+1)-histo3->GetBinContent(i+1)*histo->GetBinContent(i+1))*error_eff,2));
    //    cout<< pow(histo3->GetBinContent(i+1)*histo->GetBinContent(i+1)*error,2)<<endl;
    y[i]=eff*histo->GetBinContent(i+1);
    ey[i]=error;
  }

  TGraphErrors * g_histo = new TGraphErrors(nbins,x,y,ex,ey);
  float range_up=0.80;
  float range_down=-0.80;

  TF1 *func_fit = new TF1("asymmetry_f",asymmetry_f,range_down,range_up,2);
  func_fit->SetParNames("S","A");
 
  TFitResultPtr r = g_histo->Fit("asymmetry_f", "QRS");

  g_histo->Draw("alp");
  TF1 *func = new TF1("asymmetry_f",asymmetry_f,-1,1,2);
  func->SetParNames("S","A");
  func->SetParameter(0,func_fit->GetParameter(0));
  func->SetParameter(1,func_fit->GetParameter(1));
  func->SetParError(0,func_fit->GetParError(0));
  func->SetParError(1,func_fit->GetParError(1));

  if(debug==true) {
      // results
    std::vector<float> Afbv=Afb_v(func);
    float Afb=Afbv.at(0);
    float dAfb=Afbv.at(1);
    
    float S=func_fit->GetParameter(0);
    float dS=func_fit->GetParError(0);
    float A=func_fit->GetParameter(1);
    float dA=func_fit->GetParError(1);

    cout << "Afb = "<< Afb<< " +- " << dAfb << "  ( "<<100.*dAfb/Afb<<" %)"<< endl;
    cout << "S/bin_size = "<< S*2./nbins<< " +- " << dS*2./nbins << "  ( "<<100.*dS/S<<" %)"<< endl;
    cout << "A/bin_size = "<< A*2./nbins<< " +- " << dA*2./nbins << "  ( "<<100.*dA/A<<" %)"<< endl;
    cout << "Correl = "<<r->GetCorrelationMatrix()[0][1]<< endl;
    cout << "Chi2 = "<<func_fit->GetChisquare()<<", NDF ="<<func_fit->GetNDF()<<" Chi2/NDF= "<<func_fit->GetChisquare()/func_fit->GetNDF()<<endl;
  }

  TF1 *func_return = new TF1("asymmetry_f",asymmetry_f,-1,1,2);
  func_return->SetParNames("S","A");
  func_return->SetParameter(0,func_fit->GetParameter(0));
  func_return->SetParameter(1,func_fit->GetParameter(1));
  func_return->SetParError(0,func_fit->GetParError(0));
  func_return->SetParError(1,func_fit->GetParError(1));
  return func_return;


}


TF1 * fit_histo_difference2(TH1F * histo, TH1F* histo2, float eff=0.25, float error_eff=0.01, bool debug=true) {
	  
  double x[40], ex[40], y[40], ey[40];
  for(int i=0; i<nbins; i++) {
    x[i]=0;
    ex[i]=0;
    y[i]=0;
    ey[i]=0;
    x[i]=histo->GetBinCenter(i+1);
    //ex[i]=0.025;
    float error=sqrt(eff*histo->GetBinContent(i+1) + histo2->GetBinContent(i+1)*error_eff);
    //    cout<< pow(histo3->GetBinContent(i+1)*histo->GetBinContent(i+1)*error,2)<<endl;
    y[i]=eff*histo->GetBinContent(i+1);
    ey[i]=error;
  }

  TGraphErrors * g_histo = new TGraphErrors(nbins,x,y,ex,ey);
  float range_up=0.80;
  float range_down=-0.80;

  TF1 *func_fit = new TF1("asymmetry_f",asymmetry_f,range_down,range_up,2);
  func_fit->SetParNames("S","A");
 
  TFitResultPtr r = g_histo->Fit("asymmetry_f", "QRS");

  g_histo->Draw("alp");
  TF1 *func = new TF1("asymmetry_f",asymmetry_f,-1,1,2);
  func->SetParNames("S","A");
  func->SetParameter(0,func_fit->GetParameter(0));
  func->SetParameter(1,func_fit->GetParameter(1));
  func->SetParError(0,func_fit->GetParError(0));
  func->SetParError(1,func_fit->GetParError(1));

  if(debug==true) {
      // results
    std::vector<float> Afbv=Afb_v(func);
    float Afb=Afbv.at(0);
    float dAfb=Afbv.at(1);
    
    float S=func_fit->GetParameter(0);
    float dS=func_fit->GetParError(0);
    float A=func_fit->GetParameter(1);
    float dA=func_fit->GetParError(1);

    cout << "Afb = "<< Afb<< " +- " << dAfb << "  ( "<<100.*dAfb/Afb<<" %)"<< endl;
    cout << "S/bin_size = "<< S*2./nbins<< " +- " << dS*2./nbins << "  ( "<<100.*dS/S<<" %)"<< endl;
    cout << "A/bin_size = "<< A*2./nbins<< " +- " << dA*2./nbins << "  ( "<<100.*dA/A<<" %)"<< endl;
    cout << "Correl = "<<r->GetCorrelationMatrix()[0][1]<< endl;
    cout << "Chi2 = "<<func_fit->GetChisquare()<<", NDF ="<<func_fit->GetNDF()<<" Chi2/NDF= "<<func_fit->GetChisquare()/func_fit->GetNDF()<<endl;
  }

  TF1 *func_return = new TF1("asymmetry_f",asymmetry_f,-1,1,2);
  func_return->SetParNames("S","A");
  func_return->SetParameter(0,func_fit->GetParameter(0));
  func_return->SetParameter(1,func_fit->GetParameter(1));
  func_return->SetParError(0,func_fit->GetParError(0));
  func_return->SetParError(1,func_fit->GetParError(1));
  return func_return;


}


TF1 * fit_histo_stat(TH1F * histo, float eff=0.25, bool debug=true) {
  
  double x[40], ex[40], y[40], ey[40];
  for(int i=0; i<nbins; i++) {
    x[i]=0;
    ex[i]=0;
    y[i]=0;
    ey[i]=0;
    x[i]=histo->GetBinCenter(i+1);
    //ex[i]=0.025;
    float error_p=sqrt(histo->GetBinError(i+1)*histo->GetBinError(i+1) - histo->GetBinContent(i+1));
    // cout<<histo->GetBinError(i+1)<<" "<<sqrt(histo->GetBinContent(i+1))<<" "<<error_p<<endl;

    y[i]=eff*histo->GetBinContent(i+1);
    ey[i]=sqrt(eff*histo->GetBinContent(i+1));//histo->GetBinError(i+1);//sqrt(eff*histo->GetBinContent(i+1));//histo->GetBinError(i+1)/sqrt(eff);// lumi_factor*error_p*error_p + lumi_factor*histo->GetBinContent(i+1));//histo->GetBinError(i+1);//sqrt(2*histo->GetBinContent(i+1)+error_p*error_p);// histo->GetBinError(i+1);//sqrt(histo->GetBinContent(i+1));
  }

  TGraphErrors * g_histo = new TGraphErrors(nbins,x,y,ex,ey);
  float range_up=0.80;
  float range_down=-0.80;

  TF1 *func_fit = new TF1("asymmetry_f",asymmetry_f,range_down,range_up,2);
  func_fit->SetParNames("S","A");
 
  TFitResultPtr r = g_histo->Fit("asymmetry_f", "QRS");

  g_histo->Draw("alp");
  TF1 *func = new TF1("asymmetry_f",asymmetry_f,-1,1,2);
  func->SetParNames("S","A");
  func->SetParameter(0,func_fit->GetParameter(0));
  func->SetParameter(1,func_fit->GetParameter(1));
  func->SetParError(0,func_fit->GetParError(0));
  func->SetParError(1,func_fit->GetParError(1));

  if(debug==true) {
      // results
    std::vector<float> Afbv=Afb_v(func);
    float Afb=Afbv.at(0);
    float dAfb=Afbv.at(1);
    
    float S=func_fit->GetParameter(0);
    float dS=func_fit->GetParError(0);
    float A=func_fit->GetParameter(1);
    float dA=func_fit->GetParError(1);

    cout << "Afb = "<< Afb<< " +- " << dAfb << "  ( "<<100.*dAfb/Afb<<" %)"<< endl;
    cout << "S/bin_size = "<< S*2./nbins<< " +- " << dS*2./nbins << "  ( "<<100.*dS/S<<" %)"<< endl;
    cout << "A/bin_size = "<< A*2./nbins<< " +- " << dA*2./nbins << "  ( "<<100.*dA/A<<" %)"<< endl;
    cout << "Correl = "<<r->GetCorrelationMatrix()[0][1]<< endl;
    cout << "Chi2 = "<<func_fit->GetChisquare()<<", NDF ="<<func_fit->GetNDF()<<" Chi2/NDF= "<<func_fit->GetChisquare()/func_fit->GetNDF()<<endl;
  }

  TF1 *func_return = new TF1("asymmetry_f",asymmetry_f,-1,1,2);
  func_return->SetParNames("S","A");
  func_return->SetParameter(0,func_fit->GetParameter(0));
  func_return->SetParameter(1,func_fit->GetParameter(1));
  func_return->SetParError(0,func_fit->GetParError(0));
  func_return->SetParError(1,func_fit->GetParError(1));
  return func_return;


}

TH1F *polarizedhisto(TH1F *left, TH1F* right, float lumi=900., TString pol="eL",float eleft=0, float eright=0) {

  TH1F * result = new TH1F("result","result",40,-1,1);
  
  if(pol=="eL") {
    left->Scale(0.58*(1+eleft)*lumi/250.);
    right->Scale(0.035*(1+eright)*lumi/250.);
  }
  if(pol=="eR") {
    left->Scale(0.035*(1+eleft)*lumi/250.);
    right->Scale(0.58*(1+eright)*lumi/250.);
  }
  
  result->Add(left);
  result->Add(right);
  return result;

}

TH1F *get_corrected(TString pol="eL") {

  // TH1F* result = Correction(folder, pol);
   
  TString filename = TString::Format("%s/bbbar_Kgamma35_%s_cuts12_250GeV_%s_btag1_0.8_btag2_0.8_nbins40.root",folder.Data(),sample.Data(),pol.Data());
  TFile *f = new TFile(filename);

  TH1F *h_corrected = (TH1F*)f->Get("corrected_BcBc");
  TH1F *h_corrected2 = (TH1F*)f->Get("corrected_KcKc");
  TH1F *h_corrected3 = (TH1F*)f->Get("corrected_BcKc");
  TH1F *h_corrected4 = (TH1F*)f->Get("corrected_KcBc");
  TH1F *h_corrected5 = (TH1F*)f->Get("cheatedcharge_BcKc_same1");
  TH1F *h_corrected6 = (TH1F*)f->Get("cheatedcharge_BcKc_same2");//parton_recocuts");
  h_corrected->Add(h_corrected2);
  h_corrected->Add(h_corrected3);
  h_corrected->Add(h_corrected4);
  h_corrected->Add(h_corrected5);
  h_corrected->Add(h_corrected6);
    
  h_corrected->Sumw2();

  return h_corrected;
  
}

TH1F *get_BKG(TString pol="eL") {

  TH1F* result = CorrectionBkg(folder, pol);
 
  return result;
  
}

TH1F *get_cheatedcharge(TString pol="eL") {

  TString filename = TString::Format("%s/bbbar_Kgamma35_%s_cuts12_250GeV_%s_btag1_0.8_btag2_0.8_nbins40.root",folder.Data(),sample.Data(),pol.Data());
  TFile *f = new TFile(filename);

  TH1F *h_cheatedcharge = (TH1F*)f->Get("cheatedcharge_BcBc");
  TH1F *h_cheatedcharge2 = (TH1F*)f->Get("cheatedcharge_KcKc");
  TH1F *h_cheatedcharge3 = (TH1F*)f->Get("cheatedcharge_BcKc");
  TH1F *h_cheatedcharge4 = (TH1F*)f->Get("cheatedcharge_KcBc");
  TH1F *h_cheatedcharge5 = (TH1F*)f->Get("cheatedcharge_BcKc_same1");
  TH1F *h_cheatedcharge6 = (TH1F*)f->Get("cheatedcharge_BcKc_same2");//parton_recocuts");
  h_cheatedcharge->Add(h_cheatedcharge2);
  h_cheatedcharge->Add(h_cheatedcharge3);
  h_cheatedcharge->Add(h_cheatedcharge4);
  h_cheatedcharge->Add(h_cheatedcharge5);
  h_cheatedcharge->Add(h_cheatedcharge6);
    
  h_cheatedcharge->Sumw2();

  return h_cheatedcharge;
  
}

TH1F *get_parton(TString pol="eL") {

  TString filename = TString::Format("%s/bbbar_Kgamma35_%s_cuts12_250GeV_%s_btag1_0.8_btag2_0.8_nbins40.root",folder.Data(),sample.Data(),pol.Data());
  TFile *f = new TFile(filename);

  TH1F *h_parton = (TH1F*)f->Get("parton");
  h_parton->Sumw2();

  //  for(int i=0; i<
  return h_parton;
  
}

TH1F *get_truth(TString pol="eL") {

  TString filename = TString::Format("%s/bbbar_Kgamma35_%s_cuts12_250GeV_%s_btag1_0.8_btag2_0.8_nbins40.root",folder.Data(),sample.Data(),pol.Data());
  TFile *f = new TFile(filename);

  TH1F *h_parton = (TH1F*)f->Get("truth");
  h_parton->Sumw2();

  //  for(int i=0; i<
  return h_parton;
  
}


TH1F *get_parton_recocuts(TString pol="eL") {

  TString filename = TString::Format("%s/bbbar_Kgamma35_%s_cuts12_250GeV_%s_btag1_0.8_btag2_0.8_nbins40.root",folder.Data(),sample.Data(),pol.Data());
  TFile *f = new TFile(filename);

  TH1F *h_parton = (TH1F*)f->Get("parton_recocuts");
  h_parton->Sumw2();

  return h_parton;
  
}



