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
void Labels(int i=0, TString pol="eL"){

  QQBARLabel(0.86,0.952,"");
  if(i==0) QQBARLabel2(0.04,0.07, "[No Cuts]",kOrange+3);
  if(i==1) QQBARLabel2(0.04,0.07, "K_{reco,geom}<35 GeV",kOrange+3);
  if(i==2) QQBARLabel2(0.04,0.07, "K_{reco,geom}<35 GeV & m_{j_{1},j_{2}}>130 GeV",kOrange+3);
  if(i==3) {
    QQBARLabel2(0.04,0.085, "K_{reco,geom}<35 GeV & m_{j_{1},j_{2}}>130 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Cuts_{nPFOs}(all)",kOrange+3);
  }
  if(i==4) {
    QQBARLabel2(0.04,0.085, "K_{reco,geom}<35 GeV & m_{j_{1},j_{2}}>130 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Cuts_{nPFOs} & y23<0.015",kOrange+3);
  }
  if(i==5) {
    QQBARLabel2(0.04,0.085, "K_{reco,geom}<35 GeV & m_{j_{1},j_{2}}>130 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Cuts_{nPFOs} & y23<0.015 & (m_{j1}+m_{j2})<100 GeV",kOrange+3);
  }

  if(i==-1) {
    QQBARLabel2(0.04,0.085, "K_{reco,geom}<35 GeV & m_{j_{1},j_{2}}>130 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Cuts_{nPFOs}(1st cut)",kOrange+3);
  }
  if(i==-2) {
    QQBARLabel2(0.04,0.085, "K_{reco,geom}<35 GeV & m_{j_{1},j_{2}}>130 GeV ",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Cuts_{nPFOs}(1st & 2nd cut)",kOrange+3);
  }


  //  if(pol=="eL")QQBARLabel2(0.3,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  //if(pol=="eR")QQBARLabel2(0.3,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);

}



void ISRstudy() {

  cout<< "bb qq radreturn ww zz hz "<<endl;

  int cuts=0;
  
  TString pol="eL";
  TString sel="_";//"_tight_";
  TString folder=TString::Format("../output_20200427/IdentifyRR_cuts%i_",cuts);
  TString kt="genkt_restorer";//"_genkt";//"_tight_";
    
  TString filename = folder+"bbbar_genkt_restorer_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
  filename = folder+"bbbar_radret_genkt_R125_Kgamma35_250GeV_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";

  cout<<filename<<endl;
  
  TFile *f = new TFile(filename);
  TH2F *h_cos_parton_rad = (TH2F*)f->Get("h_costheta_parton_0");
  TH2F *h_ISR_rad = (TH2F*)f->Get("h_ISR_E2d_0");
  TH2F *h_PFOphoton_E_costheta_rad = (TH2F*)f->Get("h_PFOphoton_E_costheta_0");
  TH2F *h_PFOphoton_npfo_ratio_2d_rad = (TH2F*)f->Get("h_PFOphoton_npfo_ratio_2d_0");
  TH1F *h_PFOphoton_all_costheta_rad = (TH1F*)f->Get("h_PFOphoton_all2_costheta_0");

  TH2F *h_cos_parton = (TH2F*)f->Get("h_costheta_parton_1");
  TH2F *h_ISR = (TH2F*)f->Get("h_ISR_E2d_1");
  TH2F *h_PFOphoton_E_costheta = (TH2F*)f->Get("h_PFOphoton_E_costheta_1");
  TH2F *h_PFOphoton_npfo_ratio_2d = (TH2F*)f->Get("h_PFOphoton_npfo_ratio_2d_1");
  TH1F *h_PFOphoton_all_costheta = (TH1F*)f->Get("h_PFOphoton_all2_costheta_1");

  TH2F *h_cos_reco_rad = (TH2F*)f->Get("h_costheta_reco_0");
  TH2F *h_cos_reco = (TH2F*)f->Get("h_costheta_reco_1");

  
  TH2F *h_nPFO_ratio_rad = (TH2F*)f->Get("h_PFOphoton_ratio_2d_0");
  TH2F *h_nPFO_ratio = (TH2F*)f->Get("h_PFOphoton_ratio_2d_1");

  TH2F *h_nPFO_ratio_E_rad = (TH2F*)f->Get("h_PFOphoton_ratio_E_2d_0");
  TH2F *h_nPFO_ratio_E = (TH2F*)f->Get("h_PFOphoton_ratio_E_2d_1");


  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleY(1.0);
  gStyle->SetMarkerSize(1.5);
  gStyle->SetPadRightMargin(0.12);
  TCanvas * canvas_1 = new TCanvas("canvas_1","canvas_1",1700,800);
  
  canvas_1->Divide(2,1);
  canvas_1->cd(1);
  gPad->SetLogz();

  h_cos_parton_rad->SetTitle("Radiative Return BKG");
  
  h_cos_parton_rad->GetYaxis()->SetTitle("cos #theta_{b} (parton level)");
  h_cos_parton_rad->GetXaxis()->SetTitle("cos #theta_{#bar{b}} (parton level)");
  h_cos_parton_rad->GetXaxis()->SetRangeUser(-1,1);
  h_cos_parton_rad->GetYaxis()->SetRangeUser(-1,1);
  h_cos_parton_rad->Draw("colz");

  Labels(cuts,pol);

  
  canvas_1->cd(2);
  gPad->SetLogz();

  h_cos_parton->SetTitle("Signal");
  
  h_cos_parton->GetYaxis()->SetTitle("cos #theta_{b} (parton level)");
  h_cos_parton->GetXaxis()->SetTitle("cos #theta_{#bar{b}} (parton level)");
  h_cos_parton->GetXaxis()->SetRangeUser(-1,1);
  h_cos_parton->GetYaxis()->SetRangeUser(-1,1);
  h_cos_parton->GetZaxis()->SetRangeUser(10,2000);

  h_cos_parton->Draw("colz");

  Labels(cuts,pol);


  TCanvas * canvas_2 = new TCanvas("canvas_2","canvas_2",1700,800);
  
  canvas_2->Divide(2,1);
  canvas_2->cd(1);
  gPad->SetLogz();

  h_ISR_rad->SetTitle("Radiative Return BKG");
  
  h_ISR_rad->GetYaxis()->SetTitle("E_{#gamma 2}^{ISR} [GeV]");
  h_ISR_rad->GetXaxis()->SetTitle("E_{#gamma 1}^{ISR} [GeV]");
  h_ISR_rad->GetXaxis()->SetRangeUser(0,125);
  h_ISR_rad->GetYaxis()->SetRangeUser(0,125);
  h_ISR_rad->Draw("colz");

  Labels(cuts,pol);

  
  canvas_2->cd(2);
  gPad->SetLogz();

  h_ISR->SetTitle("Signal");
  
  h_ISR->GetYaxis()->SetTitle("E_{#gamma 2}^{ISR} [GeV]");
  h_ISR->GetXaxis()->SetTitle("E_{#gamma 1}^{ISR} [GeV]");
  h_ISR->GetXaxis()->SetRangeUser(0,125);
  h_ISR->GetYaxis()->SetRangeUser(0,125);
  // h_ISR->GetZaxis()->SetRangeUser(10,2000);

  h_ISR->Draw("colz");

  Labels(cuts,pol);
  
  //canvas_2->Print(TString::Format("plots/y23_%s_%s_cuts%i.eps",pol.Data(),kt.Data(),cuts));

  TCanvas * canvas_3 = new TCanvas("canvas_3","canvas_3",1700,800);
  
  canvas_3->Divide(2,1);
  canvas_3->cd(1);
  gPad->SetLogz();

  h_cos_reco_rad->SetTitle("Radiative Return BKG");
  
  h_cos_reco_rad->GetYaxis()->SetTitle("cos #theta_{j1} (reco level)");
  h_cos_reco_rad->GetXaxis()->SetTitle("cos #theta_{#bar{j2}} (reco level)");
  h_cos_reco_rad->GetXaxis()->SetRangeUser(-1,1);
  h_cos_reco_rad->GetYaxis()->SetRangeUser(-1,1);
  h_cos_reco_rad->Draw("colz");

  Labels(cuts,pol);

  
  canvas_3->cd(2);
  gPad->SetLogz();

  h_cos_reco->SetTitle("Signal");
  h_cos_reco->GetYaxis()->SetTitle("cos #theta_{j1} (reco level)");
  h_cos_reco->GetXaxis()->SetTitle("cos #theta_{#bar{j2}} (reco level)");
  h_cos_reco->GetXaxis()->SetRangeUser(-1,1);
  h_cos_reco->GetYaxis()->SetRangeUser(-1,1);
  h_cos_reco->GetZaxis()->SetRangeUser(10,2000);
  h_cos_reco->Draw("colz");

  Labels(cuts,pol);


  ///////////////////////////

  TCanvas * canvas_4 = new TCanvas("canvas_4","canvas_4",1700,800);
  
  canvas_4->Divide(2,1);
  canvas_4->cd(1);
  gPad->SetLogz();

  h_nPFO_ratio_rad->SetTitle("Radiative Return BKG");
  
  h_nPFO_ratio_rad->GetYaxis()->SetTitle("#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{2}}}");
  h_nPFO_ratio_rad->GetXaxis()->SetTitle("#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{1}}}");
  h_nPFO_ratio_rad->GetXaxis()->SetRangeUser(0,1);
  h_nPFO_ratio_rad->GetYaxis()->SetRangeUser(0,1);
  h_nPFO_ratio_rad->Draw("colz");

  Labels(cuts,pol);

  
  canvas_4->cd(2);
  
  // gPad->SetLogz();
  h_nPFO_ratio->SetTitle("Signal");
  
  h_nPFO_ratio->GetYaxis()->SetTitle("#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{2}}}");
  h_nPFO_ratio->GetXaxis()->SetTitle("#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{1}}}");
  h_nPFO_ratio->GetXaxis()->SetRangeUser(0,1);
  h_nPFO_ratio->GetYaxis()->SetRangeUser(0,1);
  h_nPFO_ratio->Draw("colz");

  h_nPFO_ratio->Draw("colz");

  Labels(cuts,pol);

   ///////////////////////////

  TCanvas * canvas_5 = new TCanvas("canvas_5","canvas_5",1700,800);
  
  canvas_5->Divide(2,1);
  canvas_5->cd(1);
  gPad->SetLogz();

  h_nPFO_ratio_E_rad->SetTitle("Radiative Return BKG");
  
  h_nPFO_ratio_E_rad->GetYaxis()->SetTitle("E_{jet_{j}}");
  h_nPFO_ratio_E_rad->GetXaxis()->SetTitle("#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{j}}}");
  h_nPFO_ratio_E_rad->GetXaxis()->SetRangeUser(0,1);
  h_nPFO_ratio_E_rad->GetYaxis()->SetRangeUser(0,250);
  h_nPFO_ratio_E_rad->Draw("colz");

  Labels(cuts,pol);

  
  canvas_5->cd(2);
  
  // gPad->SetLogz();
  h_nPFO_ratio_E->SetTitle("Signal");
  h_nPFO_ratio_E->GetYaxis()->SetTitle("E_{jet_{j}}");
  h_nPFO_ratio_E->GetXaxis()->SetTitle("#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{1}}}");
  h_nPFO_ratio_E->GetXaxis()->SetRangeUser(0,1);
  h_nPFO_ratio_E->GetYaxis()->SetRangeUser(0,250);
  h_nPFO_ratio_E->Draw("colz");


  Labels(cuts,pol);

  TCanvas * canvas_6 = new TCanvas("canvas_6","canvas_6",1700,800);
  
  canvas_6->Divide(2,1);
  canvas_6->cd(1);
  gPad->SetLogz();

  h_PFOphoton_E_costheta_rad->SetTitle("Radiative Return BKG");
  h_PFOphoton_E_costheta_rad->GetYaxis()->SetTitle("E_{nPFO}");
  h_PFOphoton_E_costheta_rad->GetXaxis()->SetTitle("cos #theta_{nPFO}");
  h_PFOphoton_E_costheta_rad->GetXaxis()->SetRangeUser(-1,1);
  h_PFOphoton_E_costheta_rad->GetYaxis()->SetRangeUser(0,250);
  h_PFOphoton_E_costheta_rad->Draw("colz");

  Labels(cuts,pol);

  
  canvas_6->cd(2);
  
  // gPad->SetLogz();
  h_PFOphoton_E_costheta->SetTitle("Signal");
  h_PFOphoton_E_costheta->GetYaxis()->SetTitle("E_{nPFO}");
  h_PFOphoton_E_costheta->GetXaxis()->SetTitle("cos #theta_{nPFO}");
  h_PFOphoton_E_costheta->GetXaxis()->SetRangeUser(-1,1);
  h_PFOphoton_E_costheta->GetYaxis()->SetRangeUser(0,250);
  h_PFOphoton_E_costheta->Draw("colz");


  Labels(cuts,pol);

  TCanvas * canvas_7 = new TCanvas("canvas_7","canvas_7",1700,800);

  canvas_7->Divide(2,1);
  canvas_7->cd(1);
  gPad->SetLogz();

  h_PFOphoton_npfo_ratio_2d_rad->SetTitle("Radiative Return BKG");
  h_PFOphoton_npfo_ratio_2d_rad->GetYaxis()->SetTitle("N_{nPFO}");
  h_PFOphoton_npfo_ratio_2d_rad->GetXaxis()->SetTitle("#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{1}}}");
  h_PFOphoton_npfo_ratio_2d_rad->GetXaxis()->SetRangeUser(0,1);
  h_PFOphoton_npfo_ratio_2d_rad->GetYaxis()->SetRangeUser(0,250);
  h_PFOphoton_npfo_ratio_2d_rad->Draw("colz");

  Labels(cuts,pol);

  
  canvas_7->cd(2);
  
  // gPad->SetLogz();
  h_PFOphoton_npfo_ratio_2d->SetTitle("Signal");
  h_PFOphoton_npfo_ratio_2d->GetYaxis()->SetTitle("N_{nPFO}");
  h_PFOphoton_npfo_ratio_2d->GetXaxis()->SetTitle("#Sigma_{i=nPFO} #frac{E_{i}}{E_{jet_{1}}}");
  h_PFOphoton_npfo_ratio_2d->GetXaxis()->SetRangeUser(0,1);
  h_PFOphoton_npfo_ratio_2d->GetYaxis()->SetRangeUser(0,250);
  h_PFOphoton_npfo_ratio_2d->Draw("colz");


  Labels(cuts,pol);

  TCanvas * canvas_8 = new TCanvas("canvas_8","canvas_8",1700,800);

  canvas_8->Divide(2,1);
  canvas_8->cd(1);
  gPad->SetLogz();

  h_PFOphoton_all_costheta_rad->SetTitle("Radiative Return BKG");
  h_PFOphoton_all_costheta_rad->GetYaxis()->SetTitle("Entries");
  h_PFOphoton_all_costheta_rad->GetXaxis()->SetTitle("cos #theta_{nPFO}");
  h_PFOphoton_all_costheta_rad->GetXaxis()->SetRangeUser(-1,1);
  h_PFOphoton_all_costheta_rad->GetYaxis()->SetRangeUser(0,h_PFOphoton_all_costheta_rad->GetMaximum()*1.1);
  h_PFOphoton_all_costheta_rad->SetLineWidth(3);
  h_PFOphoton_all_costheta_rad->Draw("histo");

  Labels(cuts,pol);

  
  canvas_8->cd(2);
  
  // gPad->SetLogz();
  h_PFOphoton_all_costheta->SetTitle("Signal");
  h_PFOphoton_all_costheta->GetYaxis()->SetTitle("Entries");
  h_PFOphoton_all_costheta->GetXaxis()->SetTitle("cos #theta_{nPFO}");
  h_PFOphoton_all_costheta->GetXaxis()->SetRangeUser(-1,1);
  h_PFOphoton_all_costheta->GetYaxis()->SetRangeUser(0,h_PFOphoton_all_costheta->GetMaximum()*1.1);
  h_PFOphoton_all_costheta->SetLineWidth(3);
  h_PFOphoton_all_costheta->Draw("histo");


  Labels(cuts,pol);
  
  
}
