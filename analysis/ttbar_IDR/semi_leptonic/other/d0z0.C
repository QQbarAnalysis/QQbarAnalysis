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
//#include "../style/Style.C"
//#include "../style/Labels.C"

void plot(TH1F* hist_l, TH1F* hist_s, string title) {

  hist_l->GetXaxis()->SetTitle(title.c_str());
  hist_l->SetLineColor(kBlue);
  hist_l->DrawNormalized("histo");
  hist_s->SetLineColor(kRed);
  hist_s->DrawNormalized("histosame");

}

void d0z0() {

  bool norm=true;
	int token=0;

	cout << "0 = yyxylv" << endl;
	cout << "1 = yyxyev" << endl;
	cout << "Choose from 0-1: ";
	cin  >> token;
	cout << endl;

	string VR_l5 = "";
	string VR_s5 = "";

	switch(token){
		case 0 : VR_l5 = "/home/ilc/yokugawa/run_preset/root_merge/VertexRestore_out/VR_l5_yyxylv.root";
						 VR_s5 = "/home/ilc/yokugawa/run_preset_small/root_merge/VertexRestore_out/VR_s5_yyxylv.root";
						 break;
		case 1 : VR_l5 = "/home/ilc/yokugawa/run_preset/root_merge/VertexRestore_out/VR_l5_yyxyev.root";
						 VR_s5 = "/home/ilc/yokugawa/run_preset_small/root_merge/VertexRestore_out/VR_s5_yyxyev.root";
						 break;
	}
 
  TFile *f_Large = new TFile(VR_l5.c_str());
  TTree *Stats_Large = (TTree*)f_Large->Get("Stats");

  TH1F * missed_Z0_Large = new TH1F("missed_Z0_Large","missed_Z0",400,-20,20);
  TH1F * missed_D0_Large = new TH1F("missed_D0_Large","missed_D0",400,-20,20);
  TH1F * missed_Z0Error_Large = new TH1F("missed_Z0Error_Large","missed_Z0Error",5000,0,5);
  TH1F * missed_D0Error_Large = new TH1F("missed_D0Error_Large","missed_D0Error",5000,0,5);
  Stats_Large->Draw("missedZ0>>missed_Z0_Large","missedMomentum > 1. && missedObs > 0");
  Stats_Large->Draw("missedD0>>missed_D0_Large","missedMomentum > 1. && missedObs > 0");
  Stats_Large->Draw("missedZ0Error>>missed_Z0Error_Large","missedMomentum > 1. && missedObs > 0");
  Stats_Large->Draw("missedD0Error>>missed_D0Error_Large","missedMomentum > 1. && missedObs > 0");
  TH1F * missed_sigZ0_Large = new TH1F("missed_sigZ0_Large","missed_sigZ0",80,0,40);
  TH1F * missed_sigD0_Large = new TH1F("missed_sigD0_Large","missed_sigD0",80,0,40);
  Stats_Large->Draw("fabs(missedZ0)/sqrt(missedZ0Error)>>missed_sigZ0_Large","missedMomentum > 1.&& missedObs > 0");
  Stats_Large->Draw("fabs(missedD0)/sqrt(missedD0Error)>>missed_sigD0_Large","missedMomentum > 1.&& missedObs > 0");

  TH1F * missed_angle_Large = new TH1F("missed_angle_Large","missed_angle",500,0,1);
  Stats_Large->Draw("missedAngle>>missed_angle_Large","missedMomentum > 1. && missedObs > 0");
  
  TH1F * bkg_Z0_Large = new TH1F("bkg_Z0_Large","bkg_Z0",400,-20,20);
  TH1F * bkg_D0_Large = new TH1F("bkg_D0_Large","bkg_D0",400,-20,20);
  TH1F * bkg_Z0Error_Large = new TH1F("bkg_Z0Error_Large","bkg_Z0Error",5000,0,5);
  TH1F * bkg_D0Error_Large = new TH1F("bkg_D0Error_Large","bkg_D0Error",5000,0,5);
  Stats_Large->Draw("fakeZ0>>bkg_Z0_Large","fakeMomentum > 1. && fakeObs > 0");
  Stats_Large->Draw("fakeD0>>bkg_D0_Large","fakeMomentum > 1. && fakeObs > 0");
  Stats_Large->Draw("fakeZ0Error>>bkg_Z0Error_Large","fakeMomentum > 1. && fakeObs > 0");
  Stats_Large->Draw("fakeD0Error>>bkg_D0Error_Large","fakeMomentum > 1. && fakeObs > 0");
  TH1F * bkg_sigZ0_Large = new TH1F("bkg_sigZ0_Large","bkg_sigZ0",80,0,40);
  TH1F * bkg_sigD0_Large = new TH1F("bkg_sigD0_Large","bkg_sigD0",80,0,40);
  Stats_Large->Draw("fabs(fakeZ0)/sqrt(fakeZ0Error)>>bkg_sigZ0_Large","fakeMomentum > 1.&& fakeObs > 0");
  Stats_Large->Draw("fabs(fakeD0)/sqrt(fakeD0Error)>>bkg_sigD0_Large","fakeMomentum > 1.&& fakeObs > 0");

  TH1F * bkg_angle_Large = new TH1F("bkg_angle_Large","bkg_angle",500,0,1);
  Stats_Large->Draw("fakeAngle>>bkg_angle_Large","fakeMomentum > 1. && fakeObs > 0");


  //-------------------------------------
  TFile *f_Small = new TFile(VR_s5.c_str());//home/irles/WorkArea/BBbar_tests/ntuples/trackrestoring/Small_vertex_reprocessed/VertexRestorer_eL_s5_merged.root");//
  TTree *Stats_Small = (TTree*)f_Small->Get("Stats");
  
  TH1F * missed_Z0_Small = new TH1F("missed_Z0_Small","missed_Z0",400,-20,20);
  TH1F * missed_D0_Small = new TH1F("missed_D0_Small","missed_D0",400,-20,20);
  TH1F * missed_Z0Error_Small = new TH1F("missed_Z0Error_Small","missed_Z0Error",5000,0,5);
  TH1F * missed_D0Error_Small = new TH1F("missed_D0Error_Small","missed_D0Error",5000,0,5);
  Stats_Small->Draw("missedZ0>>missed_Z0_Small","missedMomentum > 1. && missedObs > 0");
  Stats_Small->Draw("missedD0>>missed_D0_Small","missedMomentum > 1. && missedObs > 0");
  Stats_Small->Draw("missedZ0Error>>missed_Z0Error_Small","missedMomentum > 1. && missedObs > 0");
  Stats_Small->Draw("missedD0Error>>missed_D0Error_Small","missedMomentum > 1. && missedObs > 0");
  TH1F * missed_sigZ0_Small = new TH1F("missed_sigZ0_Small","missed_sigZ0",80,0,40);
  TH1F * missed_sigD0_Small = new TH1F("missed_sigD0_Small","missed_sigD0",80,0,40);
  Stats_Small->Draw("fabs(missedZ0)/sqrt(missedZ0Error)>>missed_sigZ0_Small","missedMomentum > 1.&& missedObs > 0");
  Stats_Small->Draw("fabs(missedD0)/sqrt(missedD0Error)>>missed_sigD0_Small","missedMomentum > 1.&& missedObs > 0");

  TH1F * missed_angle_Small = new TH1F("missed_angle_Small","missed_angle",500,0,1);
  Stats_Small->Draw("missedAngle>>missed_angle_Small","missedMomentum > 1. && missedObs > 0");
  
  TH1F * bkg_Z0_Small = new TH1F("bkg_Z0_Small","bkg_Z0",400,-20,20);
  TH1F * bkg_D0_Small = new TH1F("bkg_D0_Small","bkg_D0",400,-20,20);
  TH1F * bkg_Z0Error_Small = new TH1F("bkg_Z0Error_Small","bkg_Z0Error",5000,0,5);
  TH1F * bkg_D0Error_Small = new TH1F("bkg_D0Error_Small","bkg_D0Error",5000,0,5);
  Stats_Small->Draw("fakeZ0>>bkg_Z0_Small","fakeMomentum > 1. && fakeObs > 0");
  Stats_Small->Draw("fakeD0>>bkg_D0_Small","fakeMomentum > 1. && fakeObs > 0");
  Stats_Small->Draw("fakeZ0Error>>bkg_Z0Error_Small","fakeMomentum > 1. && fakeObs > 0");
  Stats_Small->Draw("fakeD0Error>>bkg_D0Error_Small","fakeMomentum > 1. && fakeObs > 0");
  TH1F * bkg_sigZ0_Small = new TH1F("bkg_sigZ0_Small","bkg_sigZ0",80,0,40);
  TH1F * bkg_sigD0_Small = new TH1F("bkg_sigD0_Small","bkg_sigD0",80,0,40);
  Stats_Small->Draw("fabs(fakeZ0)/sqrt(fakeZ0Error)>>bkg_sigZ0_Small","fakeMomentum > 1.&& fakeObs > 0");
  Stats_Small->Draw("fabs(fakeD0)/sqrt(fakeD0Error)>>bkg_sigD0_Small","fakeMomentum > 1.&& fakeObs > 0");

  TH1F * bkg_angle_Small = new TH1F("bkg_angle_Small","bkg_angle",500,0,1);
  Stats_Small->Draw("fakeAngle>>bkg_angle_Small","fakeMomentum > 1. && fakeObs > 0");

  
  //SetIrlesStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.3);
  gStyle->SetMarkerSize(1.5);

  
  TCanvas * canvas = new TCanvas("canvas","canvas",1000,1000);
  canvas->Divide(2,2);
  canvas->cd(1);
  gPad->SetLogy();
	plot(missed_Z0_Large, missed_Z0_Small, "Z0");

  TLegend * leg = new TLegend(0.6,0.65,0.75,0.75);
  leg->SetHeader("t#bar{t} @ 500GeV");
  leg->AddEntry(missed_Z0_Large,"Large");
  leg->AddEntry(missed_Z0_Small,"Small");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();
  
  canvas->cd(2);
  gPad->SetLogy();
  plot(missed_D0_Large, missed_D0_Small, "D0");
  leg->Draw();

  canvas->cd(3);
  gPad->SetLogy();
	plot(missed_Z0Error_Large, missed_Z0Error_Small, "Z0Error");
  leg->Draw();

  canvas->cd(4);
  gPad->SetLogy();
	plot(missed_D0Error_Large, missed_D0Error_Small, "D0Error");
  leg->Draw();

  TCanvas * canvas2 = new TCanvas("canvas2","canvas2",1000,1000);
  canvas2->Divide(2,2);

  canvas2->cd(1);
  gPad->SetLogy();
	plot(bkg_Z0_Large, bkg_Z0_Small, "Z0");
  leg->Draw();
  
  canvas2->cd(2);
  gPad->SetLogy();
  plot(bkg_D0_Large, bkg_D0_Small, "D0");
  leg->Draw();

  canvas2->cd(3);
  gPad->SetLogy();
  plot(bkg_Z0Error_Large, bkg_Z0Error_Small, "Z0Error");
  leg->Draw();

  canvas2->cd(4);
  gPad->SetLogy();
  plot(bkg_D0Error_Large, bkg_D0Error_Small, "D0Error");
  leg->Draw();
  
   TCanvas * canvas3 = new TCanvas("canvas3","canvas3",1500,1000);
  canvas3->Divide(3,2);
  canvas3->cd(1);
  gPad->SetLogy();
  plot(missed_sigZ0_Large, missed_sigZ0_Small, "Z0/eZ0");
  leg->Draw();
  
  canvas3->cd(2); 
  gPad->SetLogy();
  plot(missed_sigD0_Large, missed_sigD0_Small, "D0/eD0");
  leg->Draw();

  canvas3->cd(3);
  gPad->SetLogy();
  plot(missed_angle_Large, missed_angle_Small, "#alpha");
	leg->Draw();


  canvas3->cd(4);
  gPad->SetLogy();
  plot(bkg_sigZ0_Large, bkg_sigZ0_Small, "Z0/eZ0");
  leg->Draw();
  
  canvas3->cd(5); 
  gPad->SetLogy();
  plot(bkg_sigD0_Large, bkg_sigD0_Small, "D0/eD0");
  leg->Draw();

  canvas3->cd(6);
  gPad->SetLogy();
  plot(bkg_angle_Large, bkg_angle_Small, "#alpha");
	leg->Draw();




  
}

