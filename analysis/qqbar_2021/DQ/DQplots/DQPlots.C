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

  QQBARLabel(0.86,0.952,"");
  if(i==0) QQBARLabel2(0.04,0.07, "Signal, uds-quark",kOrange+3);
  if(i==1) QQBARLabel2(0.04,0.07, "Signal, c-quark",kOrange+3);
  if(i==2) QQBARLabel2(0.04,0.07, "Signal, b-quark",kOrange+3);
  if(i==3) QQBARLabel2(0.04,0.07, "RadReturn, uds-quark",kOrange+3);
  if(i==4) QQBARLabel2(0.04,0.07, "RadReturn, c-quark",kOrange+3);
  if(i==5) QQBARLabel2(0.04,0.07, "RadReturn, b-quark",kOrange+3);
  if(i==6) QQBARLabel2(0.04,0.07, "Signal ALL",kOrange+3);

  float x=0.25;
  QQBARLabel2(x,0.965, "e_{L}^{-}e_{R}^{+}",kGray+2);
}

TH1F * getHisto(TString folder, TString file, TString histo) {

  TFile *f = new TFile(file);
  f->cd(folder);
  TH1F *h = (TH1F*)f->Get(folder+"/"+histo);
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


  TCanvas * canvas2 = new TCanvas(name+"_all",name+"_all",1200,600);
  canvas2->Divide(3,1);
  for(int i=0; i<nfiles; i++) {
    for(int kl=0; kl<3; kl++) {
      canvas2->cd(kl+1);
      gPad->SetLogy();
      histos2.at(kl+i*3)->SetLineColor(i+1);
      if(i==2) histos2.at(kl+i*3)->SetLineColor(4);
      histos2.at(kl+i*3)->SetLineWidth(2);
      histos2.at(kl+i*3)-> GetYaxis()->SetRangeUser(100,histos2.at(kl+i*3)->GetMaximum()*1.2);
      if(normalized==true) histos2.at(kl+i*3)-> DrawNormalized("same");
      else histos2.at(kl+i*3)-> Draw("same");
      Labels(6);
      
    }
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


void DQPlots() {


  TString folder="./";
  TString names[7];
  names[0]="_uds";
  names[1]="_c";
  names[2]="_b";
  names[3]="_uds_rad";
  names[4]="_c_rad";
  names[5]="_b_rad";
  names[6]="_all";

  
  TString file[3];
  file[0]="DQ_250GeV_250GeV_DBD_eL_norestorer.root";
  //file[0]="DQ_250GeV_250GeV_mc2020-15161_eL_lcfi_VVB1.17_norestorer.root";
  file[1]="../DQ_250GeV_test.root";//DQ_250GeV_250GeV_mc2020-15162_eL_20210219.root";
  //file[0]="DQ_250GeV_250GeV_mc2020-15161_eL_norestorer.root";
    // file[1]="DQ_250GeV_250GeV_mc2020-15161_eL_norestorer2.root";
  //  file[2]="DQ_250GeV_250GeV_DBD_eL.root";
  int nfiles=2;

  bool newfile[2];
  newfile[0]=false;
  newfile[1]=true;

  //NMC
  std::vector<TH1F *> histos_NMC;
  std::vector<TH1F *> histos_NMC_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_NMC.push_back(getHisto("MC",file[i],"QCDFSR_n"+names[j]));
      histos_NMC.push_back(getHisto("MC",file[i],"particle_n"+names[j]));
    }
    histos_NMC_all.push_back(getHisto("MC",file[i],"QCDFSR_n"+names[6]));
    histos_NMC_all.push_back(getHisto("MC",file[i],"particle_n"+names[6]));
  } 
  Compare_2Histos("NMC", histos_NMC, histos_NMC_all,nfiles);
  

  //Nreco
  std::vector<TH1F *> histos_Nreco;
  std::vector<TH1F *> histos_Nreco_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_Nreco.push_back(getHisto("reco",file[i],"nvtx"+names[j]));
      histos_Nreco.push_back(getHisto("reco",file[i],"vtx_ntrack"+names[j]));
      histos_Nreco.push_back(getHisto("reco",file[i],"PFO_njet"+names[j]));
    }
    histos_Nreco_all.push_back(getHisto("reco",file[i],"nvtx"+names[6]));
    histos_Nreco_all.push_back(getHisto("reco",file[i],"vtx_ntrack"+names[6]));
    histos_Nreco_all.push_back(getHisto("reco",file[i],"PFO_njet"+names[6]));
  } 
  Compare_3Histos("Nreco", histos_Nreco, histos_Nreco_all,nfiles);
  //quark
  std::vector<TH1F *> histos_quark;
  std::vector<TH1F *> histos_quark_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_quark.push_back(getHisto("MC",file[i],"quark_phi"+names[j]));
      histos_quark.push_back(getHisto("MC",file[i],"quark_theta"+names[j]));
      histos_quark.push_back(getHisto("MC",file[i],"quark_mom"+names[j]));
    }
    histos_quark_all.push_back(getHisto("MC",file[i],"quark_phi"+names[6]));
    histos_quark_all.push_back(getHisto("MC",file[i],"quark_theta"+names[6]));
    histos_quark_all.push_back(getHisto("MC",file[i],"quark_mom"+names[6]));
  } 
  Compare_3Histos("quark", histos_quark, histos_quark_all,nfiles);

 //quark_afterps
  std::vector<TH1F *> histos_quark_afterps;
  std::vector<TH1F *> histos_quark_afterps_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_quark_afterps.push_back(getHisto("MC",file[i],"quark_afterps_phi"+names[j]));
      histos_quark_afterps.push_back(getHisto("MC",file[i],"quark_afterps_theta"+names[j]));
      histos_quark_afterps.push_back(getHisto("MC",file[i],"quark_afterps_mom"+names[j]));
    }
    histos_quark_afterps_all.push_back(getHisto("MC",file[i],"quark_afterps_phi"+names[6]));
    histos_quark_afterps_all.push_back(getHisto("MC",file[i],"quark_afterps_theta"+names[6]));
    histos_quark_afterps_all.push_back(getHisto("MC",file[i],"quark_afterps_mom"+names[6]));
  }
  Compare_3Histos("quark_afterps", histos_quark_afterps, histos_quark_afterps_all,nfiles);


  //QCDFSR
  std::vector<TH1F *> histos_QCDFSR;
  std::vector<TH1F *> histos_QCDFSR_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_QCDFSR.push_back(getHisto("MC",file[i],"QCDFSR_phi"+names[j]));
      histos_QCDFSR.push_back(getHisto("MC",file[i],"QCDFSR_theta"+names[j]));
      histos_QCDFSR.push_back(getHisto("MC",file[i],"QCDFSR_mom"+names[j]));
    }
    histos_QCDFSR_all.push_back(getHisto("MC",file[i],"QCDFSR_phi"+names[6]));
    histos_QCDFSR_all.push_back(getHisto("MC",file[i],"QCDFSR_theta"+names[6]));
    histos_QCDFSR_all.push_back(getHisto("MC",file[i],"QCDFSR_mom"+names[6]));
  }
  Compare_3Histos("QCDFSR", histos_QCDFSR, histos_QCDFSR_all,nfiles);

  
  //ISR
  std::vector<TH1F *> histos_ISR;
  std::vector<TH1F *> histos_ISR_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_ISR.push_back(getHisto("MC",file[i],"ISR_phi"+names[j]));
      histos_ISR.push_back(getHisto("MC",file[i],"ISR_theta"+names[j]));
      histos_ISR.push_back(getHisto("MC",file[i],"ISR_mom"+names[j]));
    }
    histos_ISR_all.push_back(getHisto("MC",file[i],"ISR_phi"+names[6]));
    histos_ISR_all.push_back(getHisto("MC",file[i],"ISR_theta"+names[6]));
    histos_ISR_all.push_back(getHisto("MC",file[i],"ISR_mom"+names[6]));
  }
  Compare_3Histos("ISR", histos_ISR, histos_ISR_all,nfiles);
  
  /*
  //particle
  std::vector<TH1F *> histos_particle;
  std::vector<TH1F *> histos_particle_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_particle.push_back(getHisto("MC",file[i],"particle_phi"+names[j]));
      histos_particle.push_back(getHisto("MC",file[i],"particle_theta"+names[j]));
      histos_particle.push_back(getHisto("MC",file[i],"particle_mom"+names[j]));
    }
    histos_particle_all.push_back(getHisto("MC",file[i],"particle_phi"+names[6]));
    histos_particle_all.push_back(getHisto("MC",file[i],"particle_theta"+names[6]));
    histos_particle_all.push_back(getHisto("MC",file[i],"particle_mom"+names[6]));
  }
  Compare_3Histos("particle", histos_particle, histos_particle_all,nfiles);


  //PFO
  std::vector<TH1F *> histos_PFO;
  std::vector<TH1F *> histos_PFO_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_PFO.push_back(getHisto("reco",file[i],"PFO_phi"+names[j]));
      histos_PFO.push_back(getHisto("reco",file[i],"PFO_theta"+names[j]));
      histos_PFO.push_back(getHisto("reco",file[i],"PFO_mom"+names[j]));
    }
    histos_PFO_all.push_back(getHisto("reco",file[i],"PFO_phi"+names[6]));
    histos_PFO_all.push_back(getHisto("reco",file[i],"PFO_theta"+names[6]));
    histos_PFO_all.push_back(getHisto("reco",file[i],"PFO_mom"+names[6]));
  }
  Compare_3Histos("PFO", histos_PFO, histos_PFO_all,nfiles);
  Compare_3HistosEventNorm("PFO",histos_PFO_all, histos_quark_all,nfiles);


  //track
  std::vector<TH1F *> histos_track;
  std::vector<TH1F *> histos_track_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_track.push_back(getHisto("reco",file[i],"track_phi"+names[j]));
      histos_track.push_back(getHisto("reco",file[i],"track_theta"+names[j]));
      histos_track.push_back(getHisto("reco",file[i],"track_mom"+names[j]));
    }
    histos_track_all.push_back(getHisto("reco",file[i],"track_phi"+names[6]));
    histos_track_all.push_back(getHisto("reco",file[i],"track_theta"+names[6]));
    histos_track_all.push_back(getHisto("reco",file[i],"track_mom"+names[6]));
  }
  Compare_3Histos("track", histos_track, histos_track_all,nfiles);
  Compare_3HistosEventNorm("track",histos_track_all, histos_quark_all,nfiles);

  //track d0/z0
  std::vector<TH1F *> histos_track2;
  std::vector<TH1F *> histos_track2_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_track2.push_back(getHisto("reco",file[i],"track_d0"+names[j]));
      histos_track2.push_back(getHisto("reco",file[i],"track_z0"+names[j]));
    }
    histos_track2_all.push_back(getHisto("reco",file[i],"track_d0"+names[6]));
    histos_track2_all.push_back(getHisto("reco",file[i],"track_z0"+names[6]));
  }
  Compare_2Histos("track", histos_track2, histos_track2_all,nfiles);
  */
}
