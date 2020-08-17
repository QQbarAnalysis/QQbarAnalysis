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

       
std::vector<float> CalculateP(TH1F* h_accepted, TH1F *h_rejected)
{

  for(int i=1; i<40/2+1; i++) {
    float accepted = h_accepted->GetBinContent(40+1-i);
    float rejected = h_rejected->GetBinContent(40+1-i);
    accepted += h_accepted->GetBinContent(i);
    float a=1;
    float b=-1;
    float c= rejected/ (2* (accepted+rejected));
    float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
    float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
  }

  std::vector<float> result_error;
  std::vector<float> result;

  for(int i=1; i<40/2+1; i++) {
    std::vector<float> result_j;
    for(int i1=-1; i1<2; i1+=2) {
      for(int i2=-1; i2<2; i2+=2) {
	for(int i3=-1; i3<2; i3+=2) {
	  float accepted = h_accepted->GetBinContent(40+1-i)+i1*sqrt(h_accepted->GetBinContent(40+1-i));
	  float rejected = h_rejected->GetBinContent(40+1-i)+i2*sqrt(h_rejected->GetBinContent(40+1-i));
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
  

  TH1F * corrected = new TH1F("corrected","corrected",40,-1,1);
  corrected->Sumw2();
  for(int i=1; i<40/2+1; i++) {
    float p=p_vect.at(i-1);
    float q=1-p;
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
    float nm_reco_error = histo->GetBinContent(i);
    float np_reco_error= histo->GetBinContent(40+1-i);
    corrected->SetBinContent(i, (np_reco_error*q*q-nm_reco_error*p*p)*weight );
    corrected->SetBinContent(40+1-i,-(np_reco_error*p*p-nm_reco_error*q*q)*weight );

    //calcualte average
    float av_i=0;
    float av_41i=0;
    float n=0;
    for(int i1=-1; i1<2; i1+=1) {
      for(int i2=-1; i2<2; i2+=1) {
	float nm_reco_error = histo->GetBinContent(i)+i1*histo->GetBinError(i);
	float np_reco_error= histo->GetBinContent(40+1-i)+i2*histo->GetBinError(40+1-i);
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
	float np_reco_error= histo->GetBinContent(40+1-i)+i2*histo->GetBinError(40+1-i);
	error_i+=pow( (np_reco_error*q*q-nm_reco_error*p*p)*weight -av_i ,2);
	error_41i+=pow( -(np_reco_error*p*p-nm_reco_error*q*q)*weight  - av_41i, 2);
	n++;
      }
    }
    error_i=sqrt(error_i/(n-1.));
    error_41i=sqrt(error_41i/(n-1.));
    corrected->SetBinError(i,error_i );
    corrected->SetBinError(40+1-i,error_41i );
  }
  
  return corrected;

}


TH1F* MakeCorrection(TH1F* h_reco, TH1F* h_rejected) {
  
  std::vector<float> p_b_vect=CalculateP(h_reco,h_rejected);
  TH1F * p_b = new TH1F("p","p",40/2,0,1);
  p_b->Sumw2();
  for(unsigned i=0; i<p_b_vect.size()/2; i++) {
    p_b->SetBinContent(40/2-i,p_b_vect.at(i));
    p_b->SetBinError(40/2-i,p_b_vect.at(i+40/2));
  }
  TH1F* result=CorrectHistoDoubleTag(h_reco,p_b_vect);
  return result;
  
}

TH1F* MakeCorrectionSyst(TH1F* h_reco, TH1F* h_rejected, TH1F* bkg_reco, TH1F* bkg_rejected,float variation=0.01, bool global =false) {
   
  std::vector<float> p_b_vect=CalculateP(h_reco,h_rejected);
  TH1F * p_b = new TH1F("p","p",40/2,0,1);
  p_b->Sumw2();

  for(unsigned i=0; i<p_b_vect.size()/2; i++) {
    p_b->SetBinContent(40/2-i,p_b_vect.at(i));
    p_b->SetBinError(40/2-i,p_b_vect.at(i+40/2));
  }

  if(global==false) {
    for(int i=0; i<40; i++) {
      TRandom1 *r = new TRandom1();
      double reco_value=bkg_reco->GetBinContent(i+1)-r->Gaus(bkg_reco->GetBinContent(i+1),bkg_reco->GetBinContent(i+1)*variation);
      h_reco->SetBinContent(i+1,h_reco->GetBinContent(i+1)+reco_value);
      
      TRandom1 *r2 = new TRandom1();
      double rejected_value=bkg_rejected->GetBinContent(i+1)-r2->Gaus(bkg_rejected->GetBinContent(i+1),bkg_rejected->GetBinContent(i+1)*variation);
      h_rejected->SetBinContent(i+1,h_rejected->GetBinContent(i+1)+rejected_value);
    }
  }else {
    for(int i=0; i<40; i++) {
      double reco_value=bkg_reco->GetBinContent(i+1)*variation;
      h_reco->SetBinContent(i+1,h_reco->GetBinContent(i+1)+reco_value);
      
      double rejected_value=bkg_rejected->GetBinContent(i+1)*variation;
      h_rejected->SetBinContent(i+1,h_rejected->GetBinContent(i+1)+rejected_value);
    }
  }
    
  TH1F* result=CorrectHistoDoubleTag(h_reco,p_b_vect);
  return result;
  
}


TH1F* Correction(TString folder, TString pol="eL") {

  TString filename = TString::Format("%s/bbbar_Kgamma35_genkt_restorer_cuts12_250GeV_%s_btag1_0.8_btag2_0.8_nbins40.root",folder.Data(),pol.Data());
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

TH1F* CorrectionBkg(TString folder, TString pol="eL",float variation=0.01, bool global=false) {

  //---------------------- BBBAR --------------------------------------------------
  TString filename = TString::Format("%s/bbbar_Kgamma35_genkt_restorer_cuts12_250GeV_%s_btag1_0.8_btag2_0.8_nbins40.root",folder.Data(),pol.Data());
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

  filename = TString::Format("%s/bbbar_Kgamma35_genkt_radret_R125_cuts12_250GeV_%s_btag1_0.8_btag2_0.8_nbins40.root",folder.Data(),pol.Data());
  f = new TFile(filename);
  
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
  filename = TString::Format("%s/bkg_ZZ_Kgamma35_genkt_restorer_cuts12_250GeV_%s_btag1_0.8_btag2_0.8_nbins40.root",folder.Data(),pol.Data());
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
  filename = TString::Format("%s/bkg_HZ_Kgamma35_genkt_restorer_cuts12_250GeV_%s_btag1_0.8_btag2_0.8_nbins40.root",folder.Data(),pol.Data());
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
  
