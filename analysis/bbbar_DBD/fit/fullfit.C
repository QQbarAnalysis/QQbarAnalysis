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

int nbins=40;
TString pol = "eL";
TString folder = "../output/";//output/kt_20190202";

Double_t asymmetry_f(Double_t *x, Double_t *par)
{
  
  Double_t fitval = par[0]*(1+x[0]*x[0]) + par[1]*x[0];
  return fitval;
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

       
std::vector<float> CalculateP(TH1F* h_accepted, TH1F *h_rejected)
{

  for(int i=1; i<nbins/2+1; i++) {
    float accepted = h_accepted->GetBinContent(nbins+1-i);
    float rejected = h_rejected->GetBinContent(nbins+1-i);
    accepted += h_accepted->GetBinContent(i);
    float a=1;
    float b=-1;
    float c= rejected/ (2* (accepted+rejected));
    float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
    float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
  }

  std::vector<float> result_error;
  std::vector<float> result;

  for(int i=1; i<nbins/2+1; i++) {
    std::vector<float> result_j;
    for(int i1=-1; i1<2; i1+=2) {
      for(int i2=-1; i2<2; i2+=2) {
	for(int i3=-1; i3<2; i3+=2) {
	  float accepted = h_accepted->GetBinContent(nbins+1-i)+i1*sqrt(h_accepted->GetBinContent(nbins+1-i));
	  float rejected = h_rejected->GetBinContent(nbins+1-i)+i2*sqrt(h_rejected->GetBinContent(nbins+1-i));
	  accepted += h_accepted->GetBinContent(i)+i3*sqrt(h_accepted->GetBinContent(i));
	  
	  float a=1;
	  float b=-1;
	  float c= rejected/ (2* (accepted+rejected));
	  float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
	  float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
	  if(p>0.99) p=0;
	  if(p2>0.99) p2=0;
	  if(p>0 || p2>0 ) result_j.push_back(max(p,p2));
	}
      }
    }
    float average=0;
    float n=0;
    for(unsigned j=0; j<result_j.size(); j++) {
      if(result_j.at(j)>0) {
	average+=result_j.at(j);
	n++;
      }
    }
    average/=n;
 
    if(average!=0) {
      result.push_back(average);
      float std_dev=0;
      for(unsigned j=0; j<result_j.size(); j++) {
	if(result_j.at(j)>0) {
	  std_dev+=pow(result_j.at(j)-average,2);
	}
      }
      std_dev=sqrt(std_dev/(n-1));
      result_error.push_back(std_dev);
    } else {
      result_error.push_back(0);
      result.push_back(0);
    }
  }

  for(unsigned i=0; i<result_error.size(); i++) {
    if(result_error.at(i)>0) 
      result.push_back(result_error.at(i));
    else
      result.push_back(0);
  }


  return result;
   
}


TH1F* CorrectHistoDoubleTag(TH1F* histo, std::vector<float> p_vect) {
  

  TH1F * corrected = new TH1F("corrected","corrected",nbins,-1,1);
  corrected->Sumw2();
  for(int i=1; i<nbins/2+1; i++) {
    float p=p_vect.at(i-1);
    float q=1-p;
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
    float nm_reco_error = histo->GetBinContent(i);
    float np_reco_error= histo->GetBinContent(nbins+1-i);
    corrected->SetBinContent(i, (np_reco_error*q*q-nm_reco_error*p*p)*weight );
    corrected->SetBinContent(nbins+1-i,-(np_reco_error*p*p-nm_reco_error*q*q)*weight );

    //calcualte average
    float av_i=0;
    float av_41i=0;
    float n=0;
    for(int i1=-1; i1<2; i1+=1) {
      for(int i2=-1; i2<2; i2+=1) {
	float nm_reco_error = histo->GetBinContent(i)+i1*histo->GetBinError(i);
	float np_reco_error= histo->GetBinContent(nbins+1-i)+i2*histo->GetBinError(nbins+1-i);
	av_i+= (np_reco_error*q*q-nm_reco_error*p*p)*weight ;
	av_41i+= -(np_reco_error*p*p-nm_reco_error*q*q)*weight ;
	n++;
      }
    }
    av_i/=n;
    av_41i/=n;


    //calculate error
    float error_i=0;
    float error_41i=0;
    n=0;
    for(int i1=-1; i1<2; i1+=1) {
      for(int i2=-1; i2<2; i2+=1) {
	float nm_reco_error = histo->GetBinContent(i)+i1*histo->GetBinError(i);
	float np_reco_error= histo->GetBinContent(nbins+1-i)+i2*histo->GetBinError(nbins+1-i);
	error_i+=pow( (np_reco_error*q*q-nm_reco_error*p*p)*weight -av_i ,2);
	error_41i+=pow( -(np_reco_error*p*p-nm_reco_error*q*q)*weight  - av_41i, 2);
	n++;
      }
    }
    error_i=sqrt(error_i/(n-1.));
    error_41i=sqrt(error_41i/(n-1.));
    corrected->SetBinError(i,error_i );
    corrected->SetBinError(nbins+1-i,error_41i );
  }
  
  return corrected;

}


TH1F* MakeCorrection(TH1F* h_reco, TH1F* h_rejected) {
  
  std::vector<float> p_b_vect=CalculateP(h_reco,h_rejected);
  TH1F * p_b = new TH1F("p","p",nbins/2,0,1);
  p_b->Sumw2();
  for(unsigned i=0; i<p_b_vect.size()/2; i++) {
    p_b->SetBinContent(nbins/2-i,p_b_vect.at(i));
    p_b->SetBinError(nbins/2-i,p_b_vect.at(i+nbins/2));
  }
  TH1F* result=CorrectHistoDoubleTag(h_reco,p_b_vect);
  return result;
  
}


TH1F* MakeCorrectionSyst(TH1F* h_reco, TH1F* h_rejected, TH1F* bkg_reco, TH1F* bkg_rejected,float variation=0.01, bool global =false) {

  if(global==false) {
    for(int i=0; i<nbins; i++) {
      TRandom1 *r = new TRandom1();
      double reco_value=bkg_reco->GetBinContent(i+1)-r->Gaus(bkg_reco->GetBinContent(i+1),bkg_reco->GetBinContent(i+1)*variation);
      h_reco->SetBinContent(i+1,h_reco->GetBinContent(i+1)+reco_value);
      
      TRandom1 *r2 = new TRandom1();
      double rejected_value=bkg_rejected->GetBinContent(i+1)-r2->Gaus(bkg_rejected->GetBinContent(i+1),bkg_rejected->GetBinContent(i+1)*variation);
      h_rejected->SetBinContent(i+1,h_rejected->GetBinContent(i+1)+rejected_value);
    }
  }else {
    for(int i=0; i<nbins; i++) {
      double reco_value=bkg_reco->GetBinContent(i+1)*variation;
      h_reco->SetBinContent(i+1,h_reco->GetBinContent(i+1)+reco_value);
      
      double rejected_value=bkg_rejected->GetBinContent(i+1)*variation;
      h_rejected->SetBinContent(i+1,h_rejected->GetBinContent(i+1)+rejected_value);
  }
  }
    
  std::vector<float> p_b_vect=CalculateP(h_reco,h_rejected);
  TH1F * p_b = new TH1F("p","p",nbins/2,0,1);
  p_b->Sumw2();

  for(unsigned i=0; i<p_b_vect.size()/2; i++) {
    p_b->SetBinContent(nbins/2-i,p_b_vect.at(i));
    p_b->SetBinError(nbins/2-i,p_b_vect.at(i+nbins/2));
  }
  
  TH1F* result=CorrectHistoDoubleTag(h_reco,p_b_vect);
  return result;
  
}


TH1F* Correction() {

  TString filename = TString::Format("%s/bbbar_genkt_restorer_cuts6_250GeV_%s_btag1_0.9_btag2_0.2_nbins%i.root",folder.Data(),pol.Data(),nbins);
  TFile *f = new TFile(filename);
  TH1F *reco_BcBc = (TH1F*)f->Get("reco_BcBc");
  TH1F *reco_KcKc = (TH1F*)f->Get("reco_KcKc");
  TH1F *reco_BcKc = (TH1F*)f->Get("reco_BcKc");
  TH1F *reco_KcBc = (TH1F*)f->Get("reco_KcBc");
  TH1F *reco_BcKc_same1 = (TH1F*)f->Get("reco_BcKc_same1");
  TH1F *reco_BcKc_same2 = (TH1F*)f->Get("reco_BcKc_same2");
  reco_BcBc->Sumw2();
  reco_KcKc->Sumw2();
  reco_BcKc->Sumw2();
  reco_KcBc->Sumw2();
  reco_BcKc_same1->Sumw2();
  reco_BcKc_same2->Sumw2();

  TH1F *rejected_BcBc = (TH1F*)f->Get("rejected_BcBc");
  TH1F *rejected_KcKc = (TH1F*)f->Get("rejected_KcKc");
  TH1F *rejected_BcKc = (TH1F*)f->Get("rejected_BcKc");
  TH1F *rejected_KcBc = (TH1F*)f->Get("rejected_KcBc");
  TH1F *rejected_BcKc_same1 = (TH1F*)f->Get("rejected_BcKc_same1");
  TH1F *rejected_BcKc_same2 = (TH1F*)f->Get("rejected_BcKc_same2");
  rejected_BcBc->Sumw2();
  rejected_KcKc->Sumw2();
  rejected_BcKc->Sumw2();
  rejected_KcBc->Sumw2();
  rejected_BcKc_same1->Sumw2();
  rejected_BcKc_same2->Sumw2();
  
  
  TH1F* result_BcBc = MakeCorrection(reco_BcBc,rejected_BcBc);
  TH1F* result_KcKc = MakeCorrection(reco_KcKc,rejected_KcKc);
  TH1F* result_BcKc = MakeCorrection(reco_BcKc,rejected_BcKc);
  TH1F* result_KcBc = MakeCorrection(reco_KcBc,rejected_KcBc);
  TH1F* result_BcKc_same1 = MakeCorrection(reco_BcKc_same1,rejected_BcKc_same1);
  TH1F* result_BcKc_same2 = MakeCorrection(reco_BcKc_same2,rejected_BcKc_same2);  
  result_BcBc->Add(result_KcKc);
  result_BcBc->Add(result_BcKc);
  result_BcBc->Add(result_KcBc);
  result_BcBc->Add(result_BcKc_same1);
  result_BcBc->Add(result_BcKc_same2);
  
  return result_BcBc;
}

TH1F* CorrectionBkg(float variation=0.05, bool global=false) {

  //---------------------- BBBAR --------------------------------------------------
  TString filename = TString::Format("%s/bbbar_genkt_restorer_cuts6_250GeV_%s_btag1_0.9_btag2_0.2_nbins%i.root",folder.Data(),pol.Data(),nbins);
  TFile *f = new TFile(filename);

  TH1F *reco_BcBc = (TH1F*)f->Get("reco_BcBc");
  TH1F *reco_KcKc = (TH1F*)f->Get("reco_KcKc");
  TH1F *reco_BcKc = (TH1F*)f->Get("reco_BcKc");
  TH1F *reco_KcBc = (TH1F*)f->Get("reco_KcBc");
  TH1F *reco_BcKc_same1 = (TH1F*)f->Get("reco_BcKc_same1");
  TH1F *reco_BcKc_same2 = (TH1F*)f->Get("reco_BcKc_same2");
 
  TH1F *rejected_BcBc = (TH1F*)f->Get("rejected_BcBc");
  TH1F *rejected_KcKc = (TH1F*)f->Get("rejected_KcKc");
  TH1F *rejected_BcKc = (TH1F*)f->Get("rejected_BcKc");
  TH1F *rejected_KcBc = (TH1F*)f->Get("rejected_KcBc");
  TH1F *rejected_BcKc_same1 = (TH1F*)f->Get("rejected_BcKc_same1");
  TH1F *rejected_BcKc_same2 = (TH1F*)f->Get("rejected_BcKc_same2");

  //---------------------- BKG QQ/rad return --------------------------------------------------
  TH1F *bkg_qq_BcBc = (TH1F*)f->Get("bkg_qq_BcBc");
  TH1F *bkg_qq_KcKc = (TH1F*)f->Get("bkg_qq_KcKc");
  TH1F *bkg_qq_BcKc = (TH1F*)f->Get("bkg_qq_BcKc");
  TH1F *bkg_qq_KcBc = (TH1F*)f->Get("bkg_qq_KcBc");
  TH1F *bkg_qq_BcKc_same1 = (TH1F*)f->Get("bkg_qq_BcKc_same1");
  TH1F *bkg_qq_BcKc_same2 = (TH1F*)f->Get("bkg_qq_BcKc_same2");

  TH1F *bkg_qq_rejected_BcBc = (TH1F*)f->Get("bkg_qq_rejected_BcBc");
  TH1F *bkg_qq_rejected_KcKc = (TH1F*)f->Get("bkg_qq_rejected_KcKc");
  TH1F *bkg_qq_rejected_BcKc = (TH1F*)f->Get("bkg_qq_rejected_BcKc");
  TH1F *bkg_qq_rejected_KcBc = (TH1F*)f->Get("bkg_qq_rejected_KcBc");
  TH1F *bkg_qq_rejected_BcKc_same1 = (TH1F*)f->Get("bkg_qq_rejected_BcKc_same1");
  TH1F *bkg_qq_rejected_BcKc_same2 = (TH1F*)f->Get("bkg_qq_rejected_BcKc_same2");
  
  TH1F *bkg_radreturn_BcBc = (TH1F*)f->Get("bkg_radreturn_BcBc");
  TH1F *bkg_radreturn_KcKc = (TH1F*)f->Get("bkg_radreturn_KcKc");
  TH1F *bkg_radreturn_BcKc = (TH1F*)f->Get("bkg_radreturn_BcKc");
  TH1F *bkg_radreturn_KcBc = (TH1F*)f->Get("bkg_radreturn_KcBc");
  TH1F *bkg_radreturn_BcKc_same1 = (TH1F*)f->Get("bkg_radreturn_BcKc_same1");
  TH1F *bkg_radreturn_BcKc_same2 = (TH1F*)f->Get("bkg_radreturn_BcKc_same2");

  TH1F *bkg_radreturn_rejected_BcBc = (TH1F*)f->Get("bkg_radreturn_rejected_BcBc");
  TH1F *bkg_radreturn_rejected_KcKc = (TH1F*)f->Get("bkg_radreturn_rejected_KcKc");
  TH1F *bkg_radreturn_rejected_BcKc = (TH1F*)f->Get("bkg_radreturn_rejected_BcKc");
  TH1F *bkg_radreturn_rejected_KcBc = (TH1F*)f->Get("bkg_radreturn_rejected_KcBc");
  TH1F *bkg_radreturn_rejected_BcKc_same1 = (TH1F*)f->Get("bkg_radreturn_rejected_BcKc_same1");
  TH1F *bkg_radreturn_rejected_BcKc_same2 = (TH1F*)f->Get("bkg_radreturn_rejected_BcKc_same2");
  
 //---------------------- ZZ --------------------------------------------------
  filename = TString::Format("%s/bkg_ZZ_genkt_restorer_cuts6_250GeV_%s_btag1_0.9_btag2_0.2_nbins%i.root",folder.Data(),pol.Data(),nbins);
  f = new TFile(filename);

  TH1F *bkg_ZZ_BcBc = (TH1F*)f->Get("reco_BcBc");
  TH1F *bkg_ZZ_KcKc = (TH1F*)f->Get("reco_KcKc");
  TH1F *bkg_ZZ_BcKc = (TH1F*)f->Get("reco_BcKc");
  TH1F *bkg_ZZ_KcBc = (TH1F*)f->Get("reco_KcBc");
  TH1F *bkg_ZZ_BcKc_same1 = (TH1F*)f->Get("reco_BcKc_same1");
  TH1F *bkg_ZZ_BcKc_same2 = (TH1F*)f->Get("reco_BcKc_same2");
 
  TH1F *bkg_ZZ_rejected_BcBc = (TH1F*)f->Get("rejected_BcBc");
  TH1F *bkg_ZZ_rejected_KcKc = (TH1F*)f->Get("rejected_KcKc");
  TH1F *bkg_ZZ_rejected_BcKc = (TH1F*)f->Get("rejected_BcKc");
  TH1F *bkg_ZZ_rejected_KcBc = (TH1F*)f->Get("rejected_KcBc");
  TH1F *bkg_ZZ_rejected_BcKc_same1 = (TH1F*)f->Get("rejected_BcKc_same1");
  TH1F *bkg_ZZ_rejected_BcKc_same2 = (TH1F*)f->Get("rejected_BcKc_same2");


  //---------------------- HZ --------------------------------------------------
  filename = TString::Format("%s/bkg_HZ_genkt_restorer_cuts6_250GeV_%s_btag1_0.9_btag2_0.2_nbins%i.root",folder.Data(),pol.Data(),nbins);
  f = new TFile(filename);

  TH1F *bkg_HZ_BcBc = (TH1F*)f->Get("reco_BcBc");
  TH1F *bkg_HZ_KcKc = (TH1F*)f->Get("reco_KcKc");
  TH1F *bkg_HZ_BcKc = (TH1F*)f->Get("reco_BcKc");
  TH1F *bkg_HZ_KcBc = (TH1F*)f->Get("reco_KcBc");
  TH1F *bkg_HZ_BcKc_same1 = (TH1F*)f->Get("reco_BcKc_same1");
  TH1F *bkg_HZ_BcKc_same2 = (TH1F*)f->Get("reco_BcKc_same2");
 
  TH1F *bkg_HZ_rejected_BcBc = (TH1F*)f->Get("rejected_BcBc");
  TH1F *bkg_HZ_rejected_KcKc = (TH1F*)f->Get("rejected_KcKc");
  TH1F *bkg_HZ_rejected_BcKc = (TH1F*)f->Get("rejected_BcKc");
  TH1F *bkg_HZ_rejected_KcBc = (TH1F*)f->Get("rejected_KcBc");
  TH1F *bkg_HZ_rejected_BcKc_same1 = (TH1F*)f->Get("rejected_BcKc_same1");
  TH1F *bkg_HZ_rejected_BcKc_same2 = (TH1F*)f->Get("rejected_BcKc_same2");
  
  //---------------------- UP --------------------------------------------------

  bkg_qq_BcBc->Add(bkg_radreturn_BcBc); bkg_qq_BcBc->Add(bkg_ZZ_BcBc); bkg_qq_BcBc->Add(bkg_HZ_BcBc);
  bkg_qq_KcKc->Add(bkg_radreturn_KcKc); bkg_qq_KcKc->Add(bkg_ZZ_KcKc); bkg_qq_KcKc->Add(bkg_HZ_KcKc);
  bkg_qq_BcKc->Add(bkg_radreturn_BcKc); bkg_qq_BcKc->Add(bkg_ZZ_BcKc); bkg_qq_BcKc->Add(bkg_HZ_BcKc);
  bkg_qq_KcBc->Add(bkg_radreturn_KcBc); bkg_qq_KcBc->Add(bkg_ZZ_KcBc); bkg_qq_KcBc->Add(bkg_HZ_KcBc);
  bkg_qq_BcKc_same1->Add(bkg_radreturn_BcKc_same1); bkg_qq_BcKc_same1->Add(bkg_ZZ_BcKc_same1); bkg_qq_BcKc_same1->Add(bkg_HZ_BcKc_same1);
  bkg_qq_BcKc_same2->Add(bkg_radreturn_BcKc_same2); bkg_qq_BcKc_same2->Add(bkg_ZZ_BcKc_same2); bkg_qq_BcKc_same2->Add(bkg_HZ_BcKc_same2);

  bkg_qq_rejected_BcBc->Add(bkg_radreturn_rejected_BcBc); bkg_qq_rejected_BcBc->Add(bkg_ZZ_rejected_BcBc); bkg_qq_rejected_BcBc->Add(bkg_HZ_rejected_BcBc);
  bkg_qq_rejected_KcKc->Add(bkg_radreturn_rejected_KcKc); bkg_qq_rejected_KcKc->Add(bkg_ZZ_rejected_KcKc); bkg_qq_rejected_KcKc->Add(bkg_HZ_rejected_KcKc);
  bkg_qq_rejected_BcKc->Add(bkg_radreturn_rejected_BcKc); bkg_qq_rejected_BcKc->Add(bkg_ZZ_rejected_BcKc); bkg_qq_rejected_BcKc->Add(bkg_HZ_rejected_BcKc);
  bkg_qq_rejected_KcBc->Add(bkg_radreturn_rejected_KcBc); bkg_qq_rejected_KcBc->Add(bkg_ZZ_rejected_KcBc); bkg_qq_rejected_KcBc->Add(bkg_HZ_rejected_KcBc);
  bkg_qq_rejected_BcKc_same1->Add(bkg_radreturn_rejected_BcKc_same1); bkg_qq_rejected_BcKc_same1->Add(bkg_ZZ_rejected_BcKc_same1); bkg_qq_rejected_BcKc_same1->Add(bkg_HZ_rejected_BcKc_same1);
  bkg_qq_rejected_BcKc_same2->Add(bkg_radreturn_rejected_BcKc_same2); bkg_qq_rejected_BcKc_same2->Add(bkg_ZZ_rejected_BcKc_same2); bkg_qq_rejected_BcKc_same2->Add(bkg_HZ_rejected_BcKc_same2);

  
  TH1F* result_BcBc = MakeCorrectionSyst(reco_BcBc,rejected_BcBc,bkg_qq_BcBc,bkg_qq_rejected_BcBc,variation,global);
  TH1F* result_KcKc = MakeCorrectionSyst(reco_KcKc,rejected_KcKc,bkg_qq_KcKc,bkg_qq_rejected_KcKc,variation,global);
  TH1F* result_BcKc = MakeCorrectionSyst(reco_BcKc,rejected_BcKc,bkg_qq_BcKc,bkg_qq_rejected_BcKc,variation,global);
  TH1F* result_KcBc = MakeCorrectionSyst(reco_KcBc,rejected_KcBc,bkg_qq_KcBc,bkg_qq_rejected_KcBc,variation,global);
  TH1F* result_BcKc_same1 = MakeCorrectionSyst(reco_BcKc_same1,rejected_BcKc_same1,bkg_qq_BcKc_same1,bkg_qq_rejected_BcKc_same1,variation,global);
  TH1F* result_BcKc_same2 = MakeCorrectionSyst(reco_BcKc_same2,rejected_BcKc_same2,bkg_qq_BcKc_same2,bkg_qq_rejected_BcKc_same2,variation,global);

  result_BcBc->Add(result_KcKc);
  result_BcBc->Add(result_BcKc);
  result_BcBc->Add(result_KcBc);
  result_BcBc->Add(result_BcKc_same1);
  result_BcBc->Add(result_BcKc_same2);
  
  return result_BcBc;
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

  TF1 *func_return = new TF1("asymmetry_f",asymmetry_f,-0.80,0.80,2);
  func_return->SetParNames("S","A");
  func_return->SetParameter(0,func_fit->GetParameter(0));
  func_return->SetParameter(1,func_fit->GetParameter(1));
  func_return->SetParError(0,func_fit->GetParError(0));
  func_return->SetParError(1,func_fit->GetParError(1));
  return func_return;

}


void fullfit() {

  cout<<" ######################## "<<endl;
  TCanvas * canvasdead = new TCanvas ("canvasdead","canvasdead",1000,800);
  canvasdead->cd();

  TString filename = TString::Format("%s/bbbar_genkt_restorer_cuts6_250GeV_%s_btag1_0.9_btag2_0.2_nbins%i.root",folder.Data(),pol.Data(),nbins);
  TFile *f = new TFile(filename);
  TH1F *h_corrected_default = (TH1F*)f->Get("corrected");
  TH1F *h_corrected_default01 = new TH1F("h_corrected_default01","h_corrected_default01",nbins,-1,1);
  TH1F *h_corrected_default001 = new TH1F("h_corrected_default001","h_corrected_default001",nbins,-1,1);

  TH1F *h_corrected = Correction();
  TH1F *h_corrected_bkg001 = CorrectionBkg(0.01);
  TH1F *h_corrected_bkg01 = CorrectionBkg(0.1);

  TH1F *h_corrected_bkg001p = CorrectionBkg(+0.01,true);
  TH1F *h_corrected_bkg001m = CorrectionBkg(-0.01,true);

  TH1F *h_corrected_bkg01p = CorrectionBkg(+0.1,true);
  TH1F *h_corrected_bkg01m = CorrectionBkg(-0.1,true);
  
  TH1F *h_parton = (TH1F*)f->Get("parton");

  TH1F *h_eff = (TH1F*)f->Get("parton_recocuts");
  h_eff->Divide(h_parton);

  double max =0;
  for(int i=nbins/2; i<nbins; i++) if(h_eff->GetBinContent(i+1)>max) max = h_eff->GetBinContent(i+1);
  h_eff->Scale(1./max);

  for(int i=0; i<nbins+2; i++) {  

    double error = (h_corrected_default->GetBinContent(i)/h_eff->GetBinContent(i))*sqrt(pow(h_corrected_default->GetBinError(i)/h_corrected_default->GetBinContent(i),2)+0.25*pow(h_eff->GetBinError(i) /h_eff->GetBinContent(i),2));
    h_corrected_default->SetBinError(i,error);
	
    double error001= sqrt(error*error +  0.01*0.01*pow(h_corrected_default->GetBinContent(i)/h_eff->GetBinContent(i)-h_corrected_default->GetBinContent(i),2));
    double error01= sqrt(error*error +  0.1*0.1*pow(h_corrected_default->GetBinContent(i)/h_eff->GetBinContent(i)-h_corrected_default->GetBinContent(i),2));

    h_corrected_default001->SetBinError(i,error001);
    h_corrected_default001->SetBinContent(i,h_corrected_default->GetBinContent(i)/(h_eff->GetBinContent(i)));

    h_corrected_default01->SetBinError(i,error01);
    h_corrected_default01->SetBinContent(i,h_corrected_default->GetBinContent(i)/(h_eff->GetBinContent(i)));

    h_corrected_default->SetBinContent(i,h_corrected_default->GetBinContent(i)/(h_eff->GetBinContent(i)));

    //-----------
    error = (h_corrected->GetBinContent(i)/h_eff->GetBinContent(i))*sqrt(pow(h_corrected->GetBinError(i)/h_corrected->GetBinContent(i),2)+0.25*pow(h_eff->GetBinError(i) /h_eff->GetBinContent(i),2));
    h_corrected->SetBinError(i,error);
    h_corrected->SetBinContent(i,h_corrected->GetBinContent(i)/(h_eff->GetBinContent(i)));

    //-----------
    error = (h_corrected_bkg001->GetBinContent(i)/h_eff->GetBinContent(i))*sqrt(pow(h_corrected_bkg001->GetBinError(i)/h_corrected_bkg001->GetBinContent(i),2)+0.25*pow(h_eff->GetBinError(i) /h_eff->GetBinContent(i),2));
    h_corrected_bkg001->SetBinError(i,error);
    h_corrected_bkg001->SetBinContent(i,h_corrected_bkg001->GetBinContent(i)/(h_eff->GetBinContent(i)));

    //-----------
    error = (h_corrected_bkg01->GetBinContent(i)/h_eff->GetBinContent(i))*sqrt(pow(h_corrected_bkg01->GetBinError(i)/h_corrected_bkg01->GetBinContent(i),2)+0.25*pow(h_eff->GetBinError(i) /h_eff->GetBinContent(i),2));
    h_corrected_bkg01->SetBinError(i,error);
    h_corrected_bkg01->SetBinContent(i,h_corrected_bkg01->GetBinContent(i)/(h_eff->GetBinContent(i)));

     //-----------
    error = (h_corrected_bkg01p->GetBinContent(i)/h_eff->GetBinContent(i))*sqrt(pow(h_corrected_bkg01p->GetBinError(i)/h_corrected_bkg01p->GetBinContent(i),2)+0.25*pow(h_eff->GetBinError(i) /h_eff->GetBinContent(i),2));
    h_corrected_bkg01p->SetBinError(i,error);
    h_corrected_bkg01p->SetBinContent(i,h_corrected_bkg01p->GetBinContent(i)/(h_eff->GetBinContent(i)));

    //-----------
    error = (h_corrected_bkg01m->GetBinContent(i)/h_eff->GetBinContent(i))*sqrt(pow(h_corrected_bkg01m->GetBinError(i)/h_corrected_bkg01m->GetBinContent(i),2)+0.25*pow(h_eff->GetBinError(i) /h_eff->GetBinContent(i),2));
    h_corrected_bkg01m->SetBinError(i,error);
    h_corrected_bkg01m->SetBinContent(i,h_corrected_bkg01m->GetBinContent(i)/(h_eff->GetBinContent(i)));

    //-----------
    error = (h_corrected_bkg001p->GetBinContent(i)/h_eff->GetBinContent(i))*sqrt(pow(h_corrected_bkg001p->GetBinError(i)/h_corrected_bkg001p->GetBinContent(i),2)+0.25*pow(h_eff->GetBinError(i) /h_eff->GetBinContent(i),2));
    h_corrected_bkg001p->SetBinError(i,error);
    h_corrected_bkg001p->SetBinContent(i,h_corrected_bkg001p->GetBinContent(i)/(h_eff->GetBinContent(i)));

    //-----------
    error = (h_corrected_bkg001m->GetBinContent(i)/h_eff->GetBinContent(i))*sqrt(pow(h_corrected_bkg001m->GetBinError(i)/h_corrected_bkg001m->GetBinContent(i),2)+0.25*pow(h_eff->GetBinError(i) /h_eff->GetBinContent(i),2));
    h_corrected_bkg001m->SetBinError(i,error);
    h_corrected_bkg001m->SetBinContent(i,h_corrected_bkg001m->GetBinContent(i)/(h_eff->GetBinContent(i)));
   }
  
  double integral_parton= h_parton->Integral(8,32);//nbins/2-nbins/3,nbins/2+nbins/3);//
  double integral_cheatedcharge= h_corrected_default->Integral(8,32);//nbins/2-nbins/3,nbins/2+nbins/3);//
  h_parton->Scale(integral_cheatedcharge/integral_parton);
  
  TString lumi= "250fb-1,";
  int ilumi=1;
  
  if(pol=="eL") cout<<" ####### LEFT POLARIZATION " <<endl;
  else cout<<" ####### RIGHT POLARIZATION " <<endl;
  cout<<" ------------------------ "<<endl;
  cout<<lumi+" parton level distribution "<<endl;
  TF1 * fitresult1 = fit_histo(h_parton,ilumi);
  
  cout<<"  "<<endl;
  cout<<lumi+" reco + acceptance correction (only stats) "<<endl; 
  TF1 * fitresult2 = fit_histo(h_corrected_default,ilumi);

  cout<<"  "<<endl;
  cout<<lumi+" reco + acceptance correction (stats +1% unc in correction) "<<endl; 
  TF1 * fitresult3 = fit_histo(h_corrected_default001,ilumi);

  cout<<"  "<<endl;
  cout<<lumi+" reco + acceptance correction (stats +10% unc in correction) "<<endl; 
  TF1 * fitresult3bis = fit_histo(h_corrected_default01,ilumi);
  
  cout<<"  "<<endl;
  cout<<"     PSEUDO EXPERIMENS FOR BKG unc DETERMINATION    "<<endl;
  cout<<"  "<<endl;
  cout<<lumi+" ( reference ) "<<endl; 
  TF1 * fitresult4 = fit_histo(h_corrected,ilumi);

  cout<<"  "<<endl;
  cout<<lumi+" bkg 1% (bin by bin)"<<endl; 
  TF1 * fitresult5 = fit_histo(h_corrected_bkg001,ilumi);

  cout<<"  "<<endl;
  cout<<lumi+" bkg 10% (bin by bin) "<<endl; 
  TF1 * fitresult6 = fit_histo(h_corrected_bkg01,ilumi);

  cout<<"  "<<endl;
  cout<<lumi+" bkg +1% (global)"<<endl; 
  TF1 * fitresult7 = fit_histo(h_corrected_bkg001p,ilumi);

  cout<<"  "<<endl;
  cout<<lumi+" bkg -1% (global)"<<endl; 
  TF1 * fitresult8 = fit_histo(h_corrected_bkg001m,ilumi);

  cout<<"  "<<endl;
  cout<<lumi+" bkg +10% (global)"<<endl; 
  TF1 * fitresult9 = fit_histo(h_corrected_bkg01p,ilumi);

  cout<<"  "<<endl;
  cout<<lumi+" bkg -10% (global)"<<endl; 
  TF1 * fitresult10 = fit_histo(h_corrected_bkg01m,ilumi);
  
  
  
}
