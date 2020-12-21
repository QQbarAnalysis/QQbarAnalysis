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
#include "fit.h"

float luminosity=900;

int AfbbFit(TString pol_s="",TString variable="") {

  pol=pol_s;
  bool debug=false;

  int ierror=1, ivalue=0;
  if(variable=="AFB") {
    ierror=1;
    ivalue=0;
  } else 
    if(variable=="S") {
      ierror=3;
      ivalue=2;
    } else 
      if(variable=="A") {
	ierror=5;
	ivalue=4;
      } else {
	cout<<" Tell me which variable you want to analyze!! "<<endl;
	return 1;
      }

  if(pol!="eL" && pol!="eR") {
    cout<<" Tell me which the polarization "<<endl;
    return 1;
  }
  // parton
  TH1F * parton = polarizedhisto(get_parton("eL"),get_parton("eR"),luminosity,pol);
  TF1 * fitresult_parton = fit_histo_stat(parton,0.25,debug);
  std::vector<float>stat1_v=Afb_v(fitresult_parton);
  float stat1=100.*stat1_v.at(ierror)/stat1_v.at(ivalue);

  //parton_reco 
  TH1F * parton_reco = polarizedhisto(get_parton_recocuts("eL"),get_parton_recocuts("eR"),luminosity,pol);
  TF1 * fitresult_partonreco = fit_histo(parton_reco,debug);

  float eff_unc_hypothesis=0.003; //only btag
  if(variable!="AFB") eff_unc_hypothesis=0.1; //preselection uncertainty
  TF1 * fitresult_eff= fit_histo_difference(parton,parton_reco,0.25,eff_unc_hypothesis,debug);
  std::vector<float>eff_v=Afb_v(fitresult_eff);
  float eff=100.*eff_v.at(ierror)/eff_v.at(ivalue);
  eff=sqrt(pow(eff,2)-pow(stat1,2));
  
  // reco no acceptance correction
  TH1F * reco = polarizedhisto(get_corrected("eL"),get_corrected("eR"),250,pol);
  TF1 * fitresult_reco = fit_histo(reco,debug);
  std::vector<float>stat2_v=Afb_v(fitresult_reco);
  float stat2=100.*stat2_v.at(ierror)/stat2_v.at(ivalue);


  //cheated charge
  TH1F * cheatedcharge = polarizedhisto(get_cheatedcharge("eL"),get_cheatedcharge("eR"),250,pol);
  TF1 * fitresult_cheated = fit_histo(cheatedcharge,debug);
  std::vector<float>stat3_v=Afb_v(fitresult_cheated);
  float stat3=100.*stat3_v.at(ierror)/stat3_v.at(ivalue);

  float stat23= sqrt(250./luminosity)*sqrt(fabs(stat2*stat2-stat3*stat3));

  //------------------ BKG
  // 
  TH1F * bkg = polarizedhisto(get_BKG("eL"),get_BKG("eR"),900,pol);
  TF1 * fitresult_bkg = fit_histo_difference2(parton,bkg,0.25,0.01,debug);
  std::vector<float>bkg_v=Afb_v(fitresult_bkg);
  float ebkg=100.*bkg_v.at(ierror)/bkg_v.at(ivalue);
  ebkg=sqrt(pow(ebkg,2)-pow(stat1,2));

  //------------------ Polarization
  float eleft=0.001;
  float eright=0.001;
  if(pol=="eR"){
    eleft=0.0004;
    eright=0.0014;
  }
  float x[100];
  int n=0;
  float xmean=0;
  for(int i=-1; i<2; i++) {
    for(int j=-1; j<2; j++) {
      TH1F * h_pol = polarizedhisto(get_parton("eL"),get_parton("eR"),900,pol,eleft*i,eright*j);
      TF1 * fitresult_pol = fit_histo_stat(h_pol,0.25,debug);
      std::vector<float>pol_v=Afb_v(fitresult_pol);
      x[n]= pol_v.at(ivalue);
      xmean+=x[n];
      n++;
    }
  }
  xmean/=n;
  float sigma_pol=0;
  for(int i=0; i<n; i++) {
    sigma_pol+=pow(x[i]-xmean,2);
  }
  sigma_pol=100.*sqrt(sigma_pol/n)/stat1_v.at(ivalue);


  // ###############################################################################################
  cout<<" ------------------------------------------------ "<<endl;
  cout<<" Results for : "<<pol<<"  Luminosity: "<<luminosity <<" fb-1"<<endl;
  cout<<" Variable:   :"<<variable<<endl;
  cout<< " Statistical unc = "<<sqrt(stat1*stat1+stat23*stat23) <<"%   ("<<stat1<<","<<stat23<<")"<<endl;
  cout<< " Eff unc = "<<eff <<"% "<<endl;
  cout<< " BKG unc = "<<ebkg <<"% "<<endl;
  cout<< " Pol unc = "<<sigma_pol <<"% "<<endl;

  return 0;
}
