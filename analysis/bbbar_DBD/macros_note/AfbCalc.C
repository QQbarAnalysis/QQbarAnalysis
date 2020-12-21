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

std::vector<double> fit_histo(TH1F * histo) {

  double x[40], ex[40], y[40], ey[40];
  for(int i=0; i<40; i++) {
    x[i]=0;
    ex[i]=0;
    y[i]=0;
    ey[i]=0;
    x[i]=histo->GetBinCenter(i+1);
    y[i]=histo->GetBinContent(i+1);
    ey[i]=histo->GetBinError(i+1);
  }

  TGraphErrors * g_histo = new TGraphErrors(40,x,y,ex,ey);
  float range_up=1;
  float range_down=-1;

  TF1 *func_fit = new TF1("asymmetry_f",asymmetry_f,range_down,range_up,2);
  func_fit->SetParNames("S","A");
 
  TFitResultPtr r = g_histo->Fit("asymmetry_f", "QRS");
  // r->Print("V");

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
  float minus_e = func->IntegralError(-1,0);

  float Afb=Afb_v(plus,minus);
  float dAfb=dAfb_v(plus,minus, plus_e, minus_e);
 
  //  cout << "Afb = "<< Afb<< " +- " << dAfb << "  ( "<<100.*dAfb/Afb<<" %)"<< endl;
  float S=func_fit->GetParameter(0);
  float dS=func_fit->GetParError(0);
  // cout << "S/bin_size = "<< S*2./40<< " +- " << dS*2./40 << "  ( "<<100.*dS/S<<" %)"<< endl;
  float A=func_fit->GetParameter(1);
  float dA=func_fit->GetParError(1);
  //cout << "A/bin_size = "<< A*2./40<< " +- " << dA*2./40 << "  ( "<<100.*dA/A<<" %)"<< endl;
  // cout << "Correl = "<<r->GetCorrelationMatrix()[0][1]<< endl;
  // cout << "Chi2 = "<<func_fit->GetChisquare()<<", NDF ="<<func_fit->GetNDF()<<" Chi2/NDF= "<<func_fit->GetChisquare()/func_fit->GetNDF()<<endl;

  std::vector<double> result;
  result.push_back(Afb);
  result.push_back(dAfb);
  result.push_back(S);
  result.push_back(dS);
  result.push_back(A);
  result.push_back(dA);
  result.push_back(r->GetCorrelationMatrix()[0][1]);
  result.push_back(func_fit->GetChisquare());
  result.push_back(func_fit->GetNDF());
  return result;

  //return histo;

}

void AfbCalc() {

  cout<<" ######################## "<<endl;

  TString pol="eL";
  TGraphErrors *g_Afbb[2];
  TGraphErrors *g_dAfbb[2];

  for(int ipol=0; ipol<2; ipol++){
    cout<< " ******************************* "<<endl;
    cout<< "  "<<endl;
    float x[30],yb[30], yc[30];
    float ex[30],eyb[30], eyc[30];

    if(ipol==1)pol="eR";

    TString folder="../output_20200427/";
    TString filename = TString::Format("%sAFBb_bbbar_radret_genkt_R125_250GeV_%s_nbins40.root",folder.Data(),pol.Data());//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
    TFile *f = new TFile(filename);

    for(int i=0; i<24; i++) {
    
      x[i]=5.*(i+1);
      ex[i]=0;

  
      TH1F *h_parton = (TH1F*)f->Get(TString::Format("h_costheta_parton_rad_%i",(i+1)*5));
      h_parton->Sumw2();

      TCanvas * canvasdead = new TCanvas ("canvasdead","canvasdead",1000,800);
      canvasdead->cd();
      if(pol=="eL") cout<<" ####### LEFT POLARIZATION " <<endl;
      else cout<<" ####### RIGHT POLARIZATION " <<endl;
      cout<<" ------------------------ "<<endl;
      cout<<" parton level distribution "<<endl;
      std::vector<double> fitresult = fit_histo(h_parton);
      cout<<x[i]<<"  "<<fitresult.at(0)<<endl;

      yb[i]=100.*fitresult.at(0);
      eyb[i]=0;//100.*fitresult.at(1);
      delete  canvasdead;

    }
    g_Afbb[ipol]=new TGraphErrors(24,x,yb,ex,eyb);
    double ynorm=yb[5];
    for(int iy=0; iy<22; iy++) {
      yb[iy]=100-100*yb[iy]/ynorm;
    }
    g_dAfbb[ipol]=new TGraphErrors(24,x,yb,ex,eyb);

    
  }
  
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
  g_Afbb[0]->GetYaxis()->SetTitle("A^{b#bar{b}}_{FB} [%]");
  g_Afbb[0]->GetXaxis()->SetTitle("K_{cut} [GeV]");
  g_Afbb[0]->SetLineColor(4);
  g_Afbb[0]->GetYaxis()->SetRangeUser(0,100);
  // g_Afbb[0]->GetXaxis()->SetRangeUser(0,300);
  g_Afbb[0]->SetLineColor(4);
  g_Afbb[0]->SetMarkerColor(4);
  g_Afbb[0]->SetLineWidth(3);
  g_Afbb[0]->SetLineStyle(1);
  g_Afbb[0]->Draw("ac");
  
  g_Afbb[1]->SetLineColor(4);
  g_Afbb[1]->SetMarkerColor(4);
  g_Afbb[1]->SetLineWidth(3);
  g_Afbb[1]->SetLineStyle(2);
  g_Afbb[1]->Draw("c");
  
  Labels();

  TLegend *leg = new TLegend(0.7,0.8,0.9,0.9);//(0.4,0.3,0.5,0.6);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(g_Afbb[0],"e_{L}^{-}e_{R}^{+}#rightarrowb#bar{b}","l");
  leg->AddEntry(g_Afbb[1],"e_{R}^{-}e_{L}^{+}#rightarrowb#bar{b}","l");
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);
  leg->SetLineColor(0);
  leg->SetBorderSize(0);
  leg->Draw();

  TCanvas * canvasdAfb = new TCanvas("canvas_dAfb","canvas_dAfb",800,800);
  canvasdAfb->cd(1);
  g_dAfbb[0]->GetYaxis()->SetTitle("#Delta A^{b}_{FB}  (E^{ISR}_{#gamma}<E_{cut})  [%]");
  g_dAfbb[0]->GetXaxis()->SetTitle("E_{cut} [GeV]");
  g_dAfbb[0]->SetLineColor(4);
  g_dAfbb[0]->GetYaxis()->SetRangeUser(-5,5);
  g_dAfbb[0]->SetLineColor(4);
  g_dAfbb[0]->SetMarkerColor(4);
  g_dAfbb[0]->SetLineWidth(3);
  g_dAfbb[0]->SetLineStyle(1);
  g_dAfbb[0]->Draw("ac");
  
  g_dAfbb[1]->SetLineColor(4);
  g_dAfbb[1]->SetMarkerColor(4);
  g_dAfbb[1]->SetLineWidth(3);
  g_dAfbb[1]->SetLineStyle(2);
  g_dAfbb[1]->Draw("c");
  
  Labels();
  QQBARLabel2(0.2,0.88, "#font[42]{#DeltaA^{b}_{FB} = (1 - #frac{A^{b}_{FB}(K_{cut})}{A^{b}_{FB}(35GeV)}) (%)}",kBlack);
  
  TLegend *leg1 = new TLegend(0.7,0.8,0.9,0.9);//(0.4,0.3,0.5,0.6);
  leg1->SetTextSize(0.035);
  leg1->AddEntry(g_dAfbb[0],"e_{L}^{-}e_{R}^{+} ","l");
  leg1->AddEntry(g_dAfbb[1],"e_{R}^{-}e_{L}^{+} ","l");
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();
  

  
}
