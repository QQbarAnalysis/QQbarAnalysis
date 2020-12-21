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

void Labels(){

  QQBARLabel(0.86,0.952,"");
  QQBARLabel2(0.25,0.96, "LO EW matrix element - Whizard 1.95",kGray+2);

}

TH1F *polarized_histo(TH1F *left, TH1F* right, TString pol="left") {

  TH1F* histo = new TH1F("polarized_histo_"+pol,"polarized_histo_"+pol,40,-1,1);
   
  /* if(pol=="left") {
    left->Scale(0.58);
    right->Scale(0.035);
  } else {
    right->Scale(0.58);
    left->Scale(0.035);
    }*/
 if(pol=="left") {
   histo->Add(left,0.58/(266.*0.05));
   histo->Add(right,0.035/(277.*0.05));
 } else {
   histo->Add(left,0.035/(266.*0.05));
   histo->Add(right,0.58/(277.*0.05));
 }
  return histo;
}

void AfbCalc_fixedK() {

  cout<<" ######################## "<<endl;

  TString pol="eL";
  TH1F *g_Afbb[2];

  TH1F *g_Afbb_pol[2];


  for(int ipol=0; ipol<2; ipol++){
    cout<< " ******************************* "<<endl;
    cout<< "  "<<endl;
    float x[30],yb[30], yc[30];
    float ex[30],eyb[30], eyc[30];

    if(ipol==1) pol="eR";

    TString folder="../output_20200427/";
    TString filename = TString::Format("%sbbbar_Kgamma35_genkt_restorer_cuts11_250GeV_%s_btag1_0.8_btag2_0.8_nbins40.root",folder.Data(),pol.Data());
    TFile *f = new TFile(filename);

    
    g_Afbb[ipol] = (TH1F*)f->Get("parton");
    g_Afbb[ipol]->Sumw2();

  }

  g_Afbb_pol[0]=polarized_histo(g_Afbb[0],g_Afbb[1],"left");
  g_Afbb_pol[1]=polarized_histo(g_Afbb[0],g_Afbb[1],"right");

  
  g_Afbb[0]->Scale(1./(266.*0.05));
  g_Afbb[1]->Scale(1./(277.*0.05));


  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);

  gStyle->SetTitleX(0.2); 
  gStyle->SetTitleY(0.9);
  
  TGaxis::SetMaxDigits(3);

  TCanvas * canvasAfb = new TCanvas("canvas_Afb","canvas_Afb",800,800);
  canvasAfb->cd(1);
  //  gPad->SetLogz();

  //g_Afbb[0]->SetTitle("Predicted A^{b}_{FB}");
  g_Afbb[0]->GetYaxis()->SetTitle("cross section [fb/0.05]");
  g_Afbb[0]->GetXaxis()->SetTitle("cos#theta_{b}");
  g_Afbb[0]->SetLineColor(4);
  g_Afbb[0]->GetYaxis()->SetTitleOffset(1.95);
  g_Afbb[0]->GetXaxis()->SetRangeUser(-0.99,0.98);
  g_Afbb[0]->SetLineColor(4);
  g_Afbb[0]->SetMarkerColor(4);
  g_Afbb[0]->SetLineWidth(3);
  g_Afbb[0]->SetLineStyle(1);
  g_Afbb[0]->Draw("histol");
  
  g_Afbb[1]->SetLineColor(2);
  g_Afbb[1]->SetMarkerColor(2);
  g_Afbb[1]->SetLineWidth(3);
  g_Afbb[1]->SetLineStyle(1);
  g_Afbb[1]->Draw("histolsame");
  
  Labels();

  TLegend *leg = new TLegend(0.3,0.7,0.5,0.9);//(0.4,0.3,0.5,0.6);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(g_Afbb[0],"#frac{d#sigma_{e_{L}^{-}e_{R}^{+}#rightarrowb#bar{b}}}{dcos#theta_{b}}(E_{#gamma}<35GeV)","l");
  leg->AddEntry(g_Afbb[1],"#frac{d#sigma_{e_{R}^{-}e_{L}^{+}#rightarrowb#bar{b}}}{dcos#theta_{b}}(E_{#gamma}<35GeV)","l");//e_{R}^{-}e_{L}^{+}#rightarrowb#bar{b}","l");
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);
  leg->SetLineColor(0);
  leg->SetBorderSize(0);
  leg->Draw();

   TCanvas * canvasAfb2 = new TCanvas("canvas_Afb2","canvas_Afb2",800,800);
  canvasAfb2->cd(1);
  //  gPad->SetLogz();

  //g_Afbb_pol[0]->SetTitle("Predicted A^{b}_{FB}");
  g_Afbb_pol[0]->GetYaxis()->SetTitle("cross section [fb/0.05]");
  g_Afbb_pol[0]->GetXaxis()->SetTitle("cos#theta_{b}");
  g_Afbb_pol[0]->SetLineColor(4);
  g_Afbb_pol[0]->GetYaxis()->SetTitleOffset(1.8);
  g_Afbb_pol[0]->GetXaxis()->SetRangeUser(-0.99,0.98);
  g_Afbb_pol[0]->SetLineColor(4);
  g_Afbb_pol[0]->SetMarkerColor(4);
  g_Afbb_pol[0]->SetLineWidth(3);
  g_Afbb_pol[0]->SetLineStyle(1);
  g_Afbb_pol[0]->Draw("histol");
  
  g_Afbb_pol[1]->SetLineColor(2);
  g_Afbb_pol[1]->SetMarkerColor(2);
  g_Afbb_pol[1]->SetLineWidth(3);
  g_Afbb_pol[1]->SetLineStyle(1);
  g_Afbb_pol[1]->Draw("histolsame");
  
  Labels();

  TLegend *leg2 = new TLegend(0.17,0.73,0.5,0.93);//(0.4,0.3,0.5,0.6);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->AddEntry(g_Afbb[0],"#frac{d#sigma_{e_{P}^{-}e_{P'}^{+}#rightarrowb#bar{b}}}{dcos#theta_{b}}(E_{#gamma}<35GeV)  (P,P')=(+80%,-30%)","l");
  leg2->AddEntry(g_Afbb[1],"#frac{d#sigma_{e_{P}^{-}e_{P'}^{+}#rightarrowb#bar{b}}}{dcos#theta_{b}}(E_{#gamma}<35GeV)  (P,P')=(-80%,+30%)","l");//e_{R}^{-}e_{L}^{+}#rightarrowb#bar{b}","l");
  //leg2->AddEntry(g_Afbb_pol[0],"e_{L}^{-}e_{R}^{+}#rightarrowb#bar{b} Pol(+80,-30) ","l");
  //leg2->AddEntry(g_Afbb_pol[1],"e_{R}^{-}e_{L}^{+}#rightarrowb#bar{b} Pol(-80,+30)","l");
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();


  
  
}
