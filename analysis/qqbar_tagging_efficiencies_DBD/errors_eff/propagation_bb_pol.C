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

bool debug=true;

double Nbb_left=5700.; // bb per fb-1
double Nbb_right=1280.; // bb per fb-1

double lum=900.; //fb-1

double ebb=0.74; // over 1
double ecc=0.73; // over 1
double eqq=0.73; // over 1

double e_b_b=0.668; // over 1
double rho=0.002;

double RbL=0.18;
double RcL=0.26;

double RbR=0.12;
double RcR=0.34;

double e_b_c=0.012;
double eRc=0.003;

double e_b_uds=0.0005;

//uncertainties
double erho=0.0009;
double ee_b_c=0.01;
double ee_b_b=0;//0.;//0.001*e_b_b;
double ee_b_uds=0.1;

double ebkg_H_L;
double ebkg_H_R;

double ebkg_E_L;
double ebkg_E_R;


std::vector<double> effb(double Rc, double fH, double efH, double fE, double efE) {

    
  // Rb
  TRandom *r0= new TRandom1();
  TRandom *r1 = new TRandom1();
  TRandom *r2 = new TRandom1();
  TRandom *r3 = new TRandom1();
  TRandom *r4 = new TRandom1();
  TRandom *r5 = new TRandom1();
  TRandom *r6 = new TRandom1();

  TH1F * histo = new TH1F("histo","histo",2000,0.3,0.8);

   
  for(int i=0; i<1000000; i++) {

    double fH_ = r0->Gaus(fH,efH);
    double fE_ = r1->Gaus(fE,efE);
    double Rc_ = r2->Gaus(Rc,eRc*Rc);
    double e_b_uds_ = r3->Gaus(e_b_uds,ee_b_uds*e_b_uds);
    double e_b_c_ = r4->Gaus(e_b_c,ee_b_c*e_b_c);
    double rho_ = r5->Gaus(rho,erho);

    double p1= fH_ - e_b_c_*Rc_ + (1-Rc_)*e_b_uds_;
    double p2= e_b_c_*e_b_c_*Rc_ + (1-Rc_)*e_b_uds_*e_b_uds_;

    double a= (1+rho_)*p1;
    double b= -(fE_-p2);
    double c= e_b_uds_*(fE_-p2)-e_b_uds_*e_b_uds_*p1;

    double effb_1= (-b + sqrt(b*b-4*a*c)) / (2*a);
    histo-> Fill(effb_1);
  }
  ee_b_b=histo->GetRMS()/histo->GetMean();
  e_b_b=histo->GetMean();


  //Rb

  TH1F * histo2 = new TH1F("histo2","histo2",1000,0.0,0.3);
 

  TRandom *r01= new TRandom1();
  TRandom *r11 = new TRandom1();
  TRandom *r21 = new TRandom1();
  TRandom *r31 = new TRandom1();
  TRandom *r41 = new TRandom1();
  TRandom *r51 = new TRandom1();
  TRandom *r61 = new TRandom1();

  for(int i=0; i<1000000; i++) {
   
    double fH_ = r01->Gaus(fH,efH);
    double fE_ = r11->Gaus(fE,efE);
    double Rc_ = r21->Gaus(Rc,eRc*Rc);
    double e_b_uds_ = r31->Gaus(e_b_uds,ee_b_uds*e_b_uds);
    double e_b_c_ = r41->Gaus(e_b_c,ee_b_c*e_b_c);
    double rho_ = r51->Gaus(rho,erho);
    double e_b_b_ = r61->Gaus(e_b_b,ee_b_b*e_b_b);
   

    double p1= fH_- e_b_c_*Rc_ - (1-Rc_)*e_b_uds_;
    double p2= e_b_b_ - e_b_uds_;
    
    double Rb_= p1/p2;//(-b + sqrt(b*b-4*a*c)) / (2*a);
   
    histo2-> Fill(Rb_);
  }



  // end
  

  std::vector<double> result;
  double result1 = 100.*histo->GetMean();
  double result2 = 100.*histo->GetRMS()/histo->GetMean();
  double result3 = histo2->GetMean();
  double result4 = 100.*histo2->GetRMS()/histo2->GetMean();

  result.push_back(result1);
  result.push_back(result2);
  result.push_back(result3);
  result.push_back(result4);

  return result;
  

  
}

std::vector<double> Rb_estim(double Rc, double fH, double efH, double fE, double efE) {


  //Rb

  TH1F * histo2 = new TH1F("histo2","histo2",1000,0.0,0.3);
 

  TRandom *r01= new TRandom1();
  TRandom *r11 = new TRandom1();
  TRandom *r21 = new TRandom1();
  TRandom *r31 = new TRandom1();
  TRandom *r41 = new TRandom1();
  TRandom *r51 = new TRandom1();
  TRandom *r61 = new TRandom1();

  for(int i=0; i<1000000; i++) {
   
    double fH_ = r01->Gaus(fH,efH);
    double fE_ = r11->Gaus(fE,efE);
    double Rc_ = r21->Gaus(Rc,eRc*Rc);
    double e_b_uds_ = r31->Gaus(e_b_uds,ee_b_uds*e_b_uds);
    double e_b_c_ = r41->Gaus(e_b_c,ee_b_c*e_b_c);
    double rho_ = r51->Gaus(rho,erho);
    double e_b_b_ = r61->Gaus(e_b_b,ee_b_b*e_b_b);
   

    double p1= fH_- e_b_c_*Rc_ - (1-Rc_)*e_b_uds_;
    double p2= e_b_b_ - e_b_uds_;
    
    double Rb_= p1/p2;//(-b + sqrt(b*b-4*a*c)) / (2*a);
   
    histo2-> Fill(Rb_);
  }



  // end
  

  std::vector<double> result;
  double result3 = histo2->GetMean();
  double result4 = 100.*histo2->GetRMS()/histo2->GetMean();

  result.push_back(result3);
  result.push_back(result4);

  return result;
  

  
}

/*
  std::vector<double> Rb_estim(double lum, double e_b_b, double ee_b_b, double rho, double erho, double Rc, double eRc, double e_b_c, double ee_b_c, double Ruds, double e_b_uds, double ee_b_uds, double fH, double efH, double fE, double efE) {

  //Rb

  TH1F * histo2 = new TH1F("histo2","histo2",1000,0.0,0.3);

  //ee_b_b=ee_b_b*e_b_b;

  ee_b_c*=e_b_c;
  ee_b_uds*=e_b_uds;
  
  TRandom *r01= new TRandom1();
  TRandom *r11 = new TRandom1();
  TRandom *r21 = new TRandom1();
  TRandom *r31 = new TRandom1();
  TRandom *r41 = new TRandom1();
  TRandom *r51 = new TRandom1();
  TRandom *r61 = new TRandom1();

  for(int i=0; i<1000000; i++) {
   
  double fH_ = r01->Gaus(fH,efH);
  double fE_ = r11->Gaus(fE,efE);
  double Rc_ = r21->Gaus(Rc,eRc);
  double e_b_uds_ = r31->Gaus(e_b_uds,ee_b_uds);
  double e_b_c_ = r41->Gaus(e_b_c,ee_b_c);
  double rho_ = r51->Gaus(rho,erho);
  double e_b_b_ = r61->Gaus(e_b_b,ee_b_b);
   

  double p1= fH_- e_b_c_*Rc_ - (1-Rc_)*e_b_uds_;
  double p2= e_b_b_ - e_b_uds_;
    
  double Rb_= p1/p2;//(-b + sqrt(b*b-4*a*c)) / (2*a);
   
  histo2-> Fill(Rb_);
  }

 
  std::vector<double> result;
  double result3 = histo2->GetMean();
  double result4 = 100.*histo2->GetRMS()/histo2->GetMean();

  result.push_back(result3);
  result.push_back(result4);

  return result;
  
  }*/

/*
  std::vector<double> Rb_estim_bkg(double lum, double e_b_b, double ee_b_b, double rho, double erho, double Rc, double eRc, double e_b_c, double ee_b_c, double Ruds, double e_b_uds, double ee_b_uds, double fH, double efH, double fE, double efE) {

  //Rb

  TH1F * histo2 = new TH1F("histo2","histo2",1000,0.0,0.3);

  ee_b_b=ee_b_b*e_b_b;

  ee_b_c*=e_b_c;
  ee_b_uds*=e_b_uds;
  
  TRandom *r01= new TRandom1();
  TRandom *r11 = new TRandom1();
  TRandom *r21 = new TRandom1();
  TRandom *r31 = new TRandom1();
  TRandom *r41 = new TRandom1();
  TRandom *r51 = new TRandom1();
  TRandom *r61 = new TRandom1();

  for(int i=0; i<1000000; i++) {
   
  double fH_ = r01->Gaus(fH,sqrt(efH*efH+0.14*fH*0.14*fH*0.01*0.01));
  double fE_ = r11->Gaus(fE,sqrt(efE*efE+0.016*fE*0.016*fE*0.01*0.01));//fE,efE);
  double Rc_ = r21->Gaus(Rc,eRc);
  double e_b_uds_ = r31->Gaus(e_b_uds,ee_b_uds);
  double e_b_c_ = r41->Gaus(e_b_c,ee_b_c);
  double rho_ = r51->Gaus(rho,erho);
  double e_b_b_ = r61->Gaus(e_b_b,ee_b_b);
   

  double p1= fH_- e_b_c_*Rc_ - (1-Rc_)*e_b_uds_;
  double p2= e_b_b_ - e_b_uds_;
    
  double Rb_= p1/p2;//(-b + sqrt(b*b-4*a*c)) / (2*a);
   
  histo2-> Fill(Rb_);
  }


  // end
  

  std::vector<double> result;
  double result3 = histo2->GetMean();
  double result4 = 100.*histo2->GetRMS()/histo2->GetMean();

  result.push_back(result3);
  result.push_back(result4);

  return result;
  }
*/

std::vector<double> propagation_bb_pol_(TString pol="plus", int i=0, int j=0) {


  double RudsL=1-RbL-RcL;//
  double RudsR=1-RbR-RcR;//

  //uncertainties
  /*  double erho=0.0009;
      double ee_b_c=0.01;
      double ee_b_b=0;//0.;//0.001*e_b_b;
      double ee_b_uds=0.1;*/

  
  //left case
  double de=0.001;
  double dp=0.0004;
  
  double Pol_e=0.58;
  double Pol_p=0.035;
  
  Pol_e=Pol_e*(1+i*de);
  Pol_p=Pol_p*(1+j*dp);
    
  // double nev1_LL=Pol_e*lum*Nbb_left *(RbL/RbL + RcL/RbL + RudsL/RbL)*eqq* (RbL*e_b_b + RcL*e_b_c+ RudsL*e_b_uds);
  // double nev2_LL=Pol_e*Nbb_left *lum*(RbL/RbL + RcL/RbL + RudsL/RbL)*eqq* (RbL*e_b_b*e_b_b*(1+rho) + RcL*e_b_c*e_b_c+ RudsL*e_b_uds*e_b_uds);
  // double nevq_LL=Pol_e*lum*Nbb_left *eqq *(RbL/RbL + RcL/RbL + RudsL/RbL);
  
  // double nev1_LR=Pol_p*lum*Nbb_right *(RbR/RbR + RcR/RbR + RudsR/RbR)*eqq* (RbR*e_b_b + RcR*e_b_c+ RudsR*e_b_uds);
  // double nev2_LR=Pol_p*Nbb_right *lum*(RbR/RbR + RcR/RbR + RudsR/RbR)*eqq* (RbR*e_b_b*e_b_b*(1+rho) + RcR*e_b_c*e_b_c+ RudsR*e_b_uds*e_b_uds);
  // double nevq_LR=Pol_p*lum*Nbb_right *eqq *(RbR/RbR + RcR/RbR + RudsR/RbR);

  double nev1_LL=Pol_e*lum*Nbb_left *(RbL/RbL + RcL/RbL + RudsL/RbL)* (RbL*e_b_b*ebb + RcL*e_b_c*ecc+ RudsL*e_b_uds*eqq);
  double nev2_LL=Pol_e*Nbb_left *lum*(RbL/RbL + RcL/RbL + RudsL/RbL)* (RbL*e_b_b*e_b_b*(1+rho)*ebb + RcL*e_b_c*e_b_c*ecc+ RudsL*e_b_uds*e_b_uds*eqq);
  double nevq_LL=Pol_e*lum*Nbb_left *(ebb*RbL/RbL + ecc*RcL/RbL + eqq*RudsL/RbL);
  
  double nev1_LR=Pol_p*lum*Nbb_right *(RbR/RbR + RcR/RbR + RudsR/RbR)* (RbR*e_b_b*ebb + RcR*e_b_c*ecc+ RudsR*e_b_uds*eqq);
  double nev2_LR=Pol_p*Nbb_right *lum*(RbR/RbR + RcR/RbR + RudsR/RbR)* (RbR*e_b_b*e_b_b*(1+rho)*ebb + RcR*e_b_c*e_b_c*ecc+ RudsR*e_b_uds*e_b_uds*eqq);
  double nevq_LR=Pol_p*lum*Nbb_right *(ebb*RbR/RbR + ecc*RcR/RbR + eqq*RudsR/RbR);
  
  double fHL= (nev1_LL+nev1_LR)/(nevq_LL+nevq_LR);
  double fEL= (nev2_LL+nev2_LR)/(nevq_LL+nevq_LR);
  
  double efHL=fHL/sqrt(nev1_LL+nev1_LR)+ebkg_H_L*fHL;
  double efEL=fEL/sqrt(nev2_LL+nev2_LR)+ebkg_E_L*fEL;

  //------------------------------------------------------------------------------------
  //right case

  de=0.001;
  dp=0.0014;
  
  Pol_e=0.035;
  Pol_p=0.58;

  Pol_e=Pol_e*(1+i*de);
  Pol_p=Pol_p*(1+j*dp);
  
  
  double nev1_RR=Pol_p*lum*Nbb_right *(RbR/RbR + RcR/RbR + RudsR/RbR)* (RbR*e_b_b*ebb + RcR*e_b_c*ecc+ RudsR*e_b_uds*eqq);
  double nev2_RR=Pol_p*Nbb_right *lum*(RbR/RbR + RcR/RbR + RudsR/RbR)* (RbR*e_b_b*e_b_b*(1+rho)*ebb + RcR*e_b_c*e_b_c*ecc+ RudsR*e_b_uds*e_b_uds*eqq);
  double nevq_RR=Pol_p*lum*Nbb_right *(RbR/RbR*ebb + RcR/RbR*ecc + RudsR/RbR*eqq);
  
  double nev1_RL=Pol_e*lum*Nbb_left *(RbL/RbL + RcL/RbL + RudsL/RbL)* (RbL*e_b_b*ebb + RcL*e_b_c*ecc+ RudsL*e_b_uds*eqq);
  double nev2_RL=Pol_e*Nbb_left *lum*(RbL/RbL + RcL/RbL + RudsL/RbL)* (RbL*e_b_b*e_b_b*(1+rho)*ebb + RcL*e_b_c*e_b_c*ecc+ RudsL*e_b_uds*e_b_uds*eqq);
  double nevq_RL=Pol_e*lum*Nbb_left *(ebb*RbL/RbL + ecc*RcL/RbL + eqq*RudsL/RbL);


  double fHR= (nev1_RL+nev1_RR)/(nevq_RL+nevq_RR);
  double fER= (nev2_RL+nev2_RR)/(nevq_RL+nevq_RR);
  
  double efHR=sqrt(pow(fHR/sqrt(nev1_RL+nev1_RR),2)+pow(ebkg_H_R*fHR,2));
  double efER=sqrt(pow(fER/sqrt(nev2_RL+nev2_RR),2)+pow(ebkg_E_R*fER,2));

  //both
  double fH= (nev1_LL+nev1_LR+nev1_RL+nev1_RR)/(nevq_LL+nevq_LR+nevq_RL+nevq_RR);
  double fE= (nev2_LL+nev2_LR+nev2_RL+nev2_RR)/(nevq_LL+nevq_LR+nevq_RL+nevq_RR);
  
  double efH=sqrt(pow(fH/sqrt(nev1_LL+nev1_LR+nev1_RL+nev1_RR),2)+pow(ebkg_H_L*fHL,2)+pow(ebkg_H_R*fHR,2));
  double efE=sqrt(pow(fE/sqrt(nev2_LL+nev2_LR+nev2_RL+nev2_RR),2)+pow(ebkg_E_L*fEL,2)+pow(ebkg_E_R*fER,2));

  
  if(pol=="minus") {

   if(debug==true) cout<< " -----------------------------------  " <<endl;
   if(debug==true) cout<< " Polarization -+, 80/30, 900fb-1" <<endl;

    std::vector<double> result = Rb_estim(RcL,fHL, efHL, fEL, efEL);
    double Rb_calc2=result.at(0);
    double e_Rb_calc2=result.at(1);
   if(debug==true) cout<< "R_b=" <<Rb_calc2 <<"                  Rel. Error ="<<e_Rb_calc2<<" %"<<endl;
  if(debug==true)  cout<< " -----------------------------------  " <<endl;

    return result;
    
  }

  if(pol=="plus") {

   if(debug==true) cout<< " -----------------------------------  " <<endl;
   if(debug==true) cout<< " Polarization +-, 80/30, 900fb-1" <<endl;

    std::vector<double> result = Rb_estim(RcR,fHR, efHR, fER, efER);
    double Rb_calc2=result.at(0);
    double e_Rb_calc2=result.at(1);
   if(debug==true) cout<< "R_b=" <<Rb_calc2 <<"                  Rel. Error ="<<e_Rb_calc2<<" %"<<endl;
   if(debug==true)  cout<< " -----------------------------------  " <<endl;

    return result;
    
  }



  if(pol=="both") {

    if(debug==true) cout<< " -----------------------------------  " <<endl;
    if(debug==true)  cout<< " Polarization BOTH" <<endl;

    std::vector<double> result3;

    std::vector<double> result = effb(RcL, fH, efH, fE, efE);
    double effb_calc=result.at(0);
    double e_effb_calc=result.at(1);
    if(debug==true)  cout<< "Left Rs:   epsilon_b=" <<effb_calc <<" %        Rel. Error ="<<e_effb_calc<<" %"<<endl;

    std::vector<double> result2 = effb(RcR, fH, efH, fE, efE);
    double effb_calc2=result2.at(0);
    double e_effb_calc2=result2.at(1);
    if(debug==true) cout<< "Rigt Rs:   epsilon_b=" <<effb_calc <<" %        Rel. Error ="<<e_effb_calc<<" %"<<endl;


    result3.push_back((effb_calc+effb_calc)/2.);
    result3.push_back((e_effb_calc+e_effb_calc)/2.);
    return result3;
    
  }

  std::vector<double> res;
  return res;
	

}

void propagation_bb_pol(){

  debug=false;
  //PREDETERMINED VALUES
  lum=900.; //fb-1, per polarization (-+,+-)

  e_b_b=0.668; // b-tagging efficiency
  rho=0.002; //rho parameter

  //theoretical values
  RbL=0.18;
  RcL=0.26;
  
  RbR=0.12;
  RcR=0.34;

  //Tagging/mistagging efficiencies
  erho=0.0009; //correlation, global value! i.e. rho=(0.002 \pm 0.0009) *100 %
  
  e_b_c=0.012; //c-quartk mistaging
  ee_b_c=0.01; //relative c-quark mistagging error (i.e. 0.01 means 1% of e_b_c)

  e_b_uds=0.0005; //uds-quark mistagging
  ee_b_uds=0.1; // relative uds-quark mistagging error (i.e. 0.1 means 10% of e_b_uds)

  //Rc uncertainty
  eRc=0.003;

  //bkg uncertainties
  ebkg_H_L=0.0; //total contribution of bkg to f1, left pol
  ebkg_H_R=0.0; //total contribution of bkg to f1, right pol

  ebkg_E_L=0.0; //total contribution of bkg to f2, left pol
  ebkg_E_R=0.0; //total contribution of bkg to f2, right pol


  // ANALYSIS
  //----------------------------------------------------------
  //FIRST: check purely statistic and systematic uncertainties on the estimation of epsilon b
  eRc=0.0;
  ee_b_uds=0;
  ee_b_c=0.0;
  erho=0.0;
  std::vector<double> epsilon_stat=propagation_bb_pol_("both",0,0);
  cout<<"Stat Unc, epsilon b="<<epsilon_stat.at(1)<<" %"<<endl;
  std::vector<double> RL_stat=propagation_bb_pol_("minus",0,0);
  cout<<"Stat Unc, Rb_(-+)="<<RL_stat.at(1)<<" %"<<endl;
  std::vector<double> RR_stat=propagation_bb_pol_("plus",0,0);
  cout<<"Stat Unc, Rb_(+-)="<<RR_stat.at(1)<<" %"<<endl;

  //preselection efficiency
  ee_b_uds=0.013;
  ee_b_c=0.013;
  erho=0.;
  std::vector<double> epsilon_pres=propagation_bb_pol_("both",0,0);
  cout<<"Syst Unc (pres.), epsilon b="<<sqrt(pow(epsilon_pres.at(1),2)-pow(epsilon_stat.at(1),2))<<" %"<<endl;
  std::vector<double> RL_pres=propagation_bb_pol_("minus",0,0);
  cout<<"Pres Unc, Rb_(-+)="<<sqrt(pow(RL_pres.at(1),2)-pow(RL_stat.at(1),2))<<" %"<<endl;
  std::vector<double> RR_pres=propagation_bb_pol_("plus",0,0);
  cout<<"Pres Unc, Rb_(+-)="<<sqrt(pow(RR_pres.at(1),2)-pow(RR_stat.at(1),2))<<" %"<<endl;

  //tagging eff
  ee_b_uds=0.1;
  ee_b_c=0.01;
  erho=0.0009;
  std::vector<double> epsilon_tag=propagation_bb_pol_("both",0,0);
  cout<<"Syst Unc (tagging), epsilon b="<<sqrt(pow(epsilon_tag.at(1),2)-pow(epsilon_stat.at(1),2))<<" %"<<endl;
  std::vector<double> RL_tag=propagation_bb_pol_("minus",0,0);
  cout<<"Tag Unc, Rb_(-+)="<<sqrt(pow(RL_tag.at(1),2)-pow(RL_stat.at(1),2))<<" %"<<endl;
  std::vector<double> RR_tag=propagation_bb_pol_("plus",0,0);
  cout<<"Tag Unc, Rb_(+-)="<<sqrt(pow(RR_tag.at(1),2)-pow(RR_stat.at(1),2))<<" %"<<endl;

  //Unc on Rc
  eRc=0.003;
  ee_b_uds=0.;
  ee_b_c=0.0;
  erho=0.0;
  std::vector<double> epsilon_Rc=propagation_bb_pol_("both",0,0);
  cout<<"Syst Unc (Rc), epsilon b="<<sqrt(pow(epsilon_Rc.at(1),2)-pow(epsilon_stat.at(1),2))<<" %"<<endl;
  std::vector<double> RL_Rc=propagation_bb_pol_("minus",0,0);
  cout<<"Rc Unc, Rb_(-+)="<<sqrt(pow(RL_Rc.at(1),2)-pow(RL_stat.at(1),2))<<" %"<<endl;
  std::vector<double> RR_Rc=propagation_bb_pol_("plus",0,0);
  cout<<"Rc Unc, Rb_(+-)="<<sqrt(pow(RR_Rc.at(1),2)-pow(RR_stat.at(1),2))<<" %"<<endl;

  //BKG UNC
  eRc=0.;
  ebkg_H_L=0.0003; //total contribution of bkg to f1, left pol
  ebkg_H_R=0.0004; //total contribution of bkg to f1, right pol
  ebkg_E_L=0.0002; //total contribution of bkg to f2, left pol
  ebkg_E_R=0.0003; //total contribution of bkg to f2, right pol
  std::vector<double> epsilon_Bkg=propagation_bb_pol_("both",0,0);
  cout<<"Syst Unc (BKG), epsilon b="<<sqrt(pow(epsilon_Bkg.at(1),2)-pow(epsilon_stat.at(1),2))<<" %"<<endl;
  std::vector<double> RL_Bkg=propagation_bb_pol_("minus",0,0);
  cout<<"Bkg Unc, Rb_(-+)="<<sqrt(pow(RL_Bkg.at(1),2)-pow(RL_stat.at(1),2))<<" %"<<endl;
  std::vector<double> RR_Bkg=propagation_bb_pol_("plus",0,0);
  cout<<"Bkg Unc, Rb_(+-)="<<sqrt(pow(RR_Bkg.at(1),2)-pow(RR_stat.at(1),2))<<" %"<<endl;


  //POLARIZATION UNC

  // erho=0.0009; //correlation, global value! i.e. rho=(0.002 \pm 0.0009) *100 %

  // e_b_c=0.012; //c-quartk mistaging
  // ee_b_c=0.01; //relative c-quark mistagging error (i.e. 0.01 means 1% of e_b_c)

  // e_b_uds=0.0005; //uds-quark mistagging
  // ee_b_uds=0.1; // relative uds-quark mistagging error (i.e. 0.1 means 10% of e_b_uds)

  // //Rc uncertainty
  // eRc=0.003;

  ebkg_H_L=0.0; //total contribution of bkg to f1, left pol
  ebkg_H_R=0.0; //total contribution of bkg to f1, right pol
  ebkg_E_L=0.0; //total contribution of bkg to f2, left pol
  ebkg_E_R=0.0; //total contribution of bkg to f2, right pol
  
  
  float epsilon_b_pol_max=0;
  float epsilon_b_pol_min=100;

  float RL_b_pol_max=0;
  float RL_b_pol_min=100;
  float RR_b_pol_max=0;
  float RR_b_pol_min=100;
  
  for(int i=0; i<3; i++) {
    for(int j=0; j<3; j++) {
      std::vector<double> result=propagation_bb_pol_("both",i,j);
      if(result.at(0)>epsilon_b_pol_max) epsilon_b_pol_max=result.at(0);
      if(result.at(0)<epsilon_b_pol_min) epsilon_b_pol_min=result.at(0);

      std::vector<double> RL_pol=propagation_bb_pol_("minus",i,j);
      if(RL_pol.at(0)>RL_b_pol_max) RL_b_pol_max=RL_pol.at(0);
      if(RL_pol.at(0)<RL_b_pol_min) RL_b_pol_min=RL_pol.at(0);

      std::vector<double> RR_pol=propagation_bb_pol_("plus",i,j);
      if(RR_pol.at(0)>RR_b_pol_max) RR_b_pol_max=RR_pol.at(0);
      if(RR_pol.at(0)<RR_b_pol_min) RR_b_pol_min=RR_pol.at(0);
    }
  }
  float epsilon_b_pol=  2*(epsilon_b_pol_max - epsilon_b_pol_min) / (epsilon_b_pol_max + epsilon_b_pol_min);
  cout<<"Syst Unc (Pol), epsilon b="<<epsilon_b_pol<<" %"<<endl;
  float RL_b_pol=  2*(RL_b_pol_max - RL_b_pol_min) / (RL_b_pol_max + RL_b_pol_min);
  cout<<"Syst Unc (Pol), Rb_(-+)="<<RL_b_pol<<" %"<<endl;
  float RR_b_pol=  2*(RR_b_pol_max - RR_b_pol_min) / (RR_b_pol_max + RR_b_pol_min);
  cout<<"Syst Unc (Pol), Rb_(+-)="<<RR_b_pol<<" %"<<endl;




}
