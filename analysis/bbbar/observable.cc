#define observable_cxx
#include "observable.h"
#include "TPad.h"
float getModule(vector< float > & v)
{
  float module = 0.0;
  for (unsigned int i = 0; i < v.size(); i++)
    {
      module += v[i]*v[i];
    }
  module = sqrt(module);
  return module;
}

std::vector< float > getDirection(vector<float> & vectorPoint)
{
  vector< float > vector1;
  float module = getModule(vectorPoint);
  for (int i = 0; i < 3; i++)
    {
      vector1.push_back( vectorPoint[i]/module);
    }
  return vector1;
}

std::vector< float > getAngles(std::vector< float > & direction)
{
  vector< float > result;
  float epsilon = 0.00001;
  float semi = 1.5708;
  float pi = 2*semi;
  float phi = 0.0;
  if (direction[0] > 0.0 && direction[1] > 0.0 - epsilon) 
    {
      phi = atan(direction[1] / direction[0]); //(direction[0] < epsilon && direction[0] > 0.0 - epsilon)?
    }
  if (direction[0] < 0.0 && direction[1] > 0.0) 
    {
      phi = semi - atan(direction[1] / direction[0]) ;
    }
  if (direction[0] < 0.0 && direction[1] < 0.0 + epsilon) 
    {
      phi =  atan(direction[1] / direction[0]) + pi;
    }
  if (direction[0] > 0.0 && direction[1] < 0.0 - epsilon) 
    {
      phi = semi - atan(direction[1] / direction[0]) + pi;
    }
  if (direction[1] > 0.0 && direction[0] < 0.0 + epsilon && direction[0] > 0.0 -  epsilon) 
    {
      phi = semi;
    }
  if (direction[1] < 0.0 && direction[0] < 0.0 + epsilon && direction[0] > 0.0 -  epsilon) 
    {
      phi = pi + semi;
    }
  float teta = acos(direction[2]);
  result.push_back(phi);
  result.push_back(teta);
  return result;
}

float GetCostheta(std::vector<float> & vectorPoint)
{
  float costheta1 =  -2.0;
  std::vector< float > d1= getDirection(vectorPoint);
  costheta1 =  std::cos( getAngles(d1).at(1) );
  return costheta1;
}

 
void observable::Analysis(int n=-1, bool all=true, TString polarization="eL"){

  std::vector<TH1F*> asymm_all;
  asymm_all = Asymm_BcKc(n,false);

  TString s_method="BcBc_KcKc_BcKc_KcBc_BcKcsame1_BcKcsame2";
  TString title = "e^{-}_{L}e^{+}_{R} #rightarrow b#bar{b}, 250 GeV, L=250 fb^{-1}";
  if(polarization=="eR")   title = "e^{-}_{R}e^{+}_{L} #rightarrow b#bar{b}, 250 GeV, L=250 fb^{-1}";
    
  //-------------------------------------
  /// efficiency
  std::vector<TH1F*> eff_corrected;
  TH1F *h_BcBc_corrected = (TH1F*)asymm_all[1]->Clone("h_BcBc_corrected");
  eff_corrected.push_back(h_BcBc_corrected);
  for(int i=1; i<6; i++) {
    eff_corrected.push_back(asymm_all[3+i*5]);
  }

  //-------------------------------------
  //reco
  asymm_all[0]->Add(asymm_all[5]);//kckc
  asymm_all[0]->Add(asymm_all[10]);//bckc
  asymm_all[0]->Add(asymm_all[15]);//kcbc
  asymm_all[0]->Add(asymm_all[20]);//bckc_same
  asymm_all[0]->Add(asymm_all[25]);//kcbc_same

  TH1F *h_bbbar = (TH1F*)asymm_all[30]->Clone("h_bbbar");
  //  h_bbbar->Draw("histo");
 
  //corrected
  asymm_all[1]->Add(asymm_all[6]);//kckc
  asymm_all[1]->Add(asymm_all[11]);//bckc
  asymm_all[1]->Add(asymm_all[16]);//kcbc
  asymm_all[1]->Add(asymm_all[21]);//bckc_same
  asymm_all[1]->Add(asymm_all[26]);//kcbc_same
 
  //bkg
  asymm_all[2]->Add(asymm_all[7]);//kckc
  asymm_all[2]->Add(asymm_all[12]);//bckc
  asymm_all[2]->Add(asymm_all[17]);//kcbc
  asymm_all[2]->Add(asymm_all[22]);//bckc_same
  asymm_all[2]->Add(asymm_all[27]);//kcbc_same
  
  //truth  
  asymm_all[3]->Add(asymm_all[8]);//kckc
  asymm_all[3]->Add(asymm_all[13]);//bckc
  asymm_all[3]->Add(asymm_all[18]);//kcbc
  asymm_all[3]->Add(asymm_all[23]);//bckc_same
  asymm_all[3]->Add(asymm_all[28]);//kcbc_same

  TFile *MyFile = new TFile(TString::Format("bbbar_250GeV_%s_260fb.root",polarization.Data()),"RECREATE");
  MyFile->cd();
  asymm_all[0]->SetName("reco");
  asymm_all[1]->SetName("corrected");
  asymm_all[2]->SetName("bkg_qq");
  asymm_all[3]->SetName("truth");
  for(int i=0; i<4; i++) asymm_all[i]->Write();
  h_bbbar->SetName("parton");
  h_bbbar->Write();
  MyFile->Close();
  
  //-------------------------------------
  /// efficiency-bis
  eff_corrected.push_back(h_bbbar);//asymm_all[3]);
  eff_corrected.push_back(h_bbbar);
  Efficiency_plot(s_method,title,eff_corrected);

  //-------------------------------------
  /// probabilities
  std::vector<TH1F*> prob;
 
  prob.push_back(asymm_all[4]);
  prob.push_back(asymm_all[9]);
  prob.push_back(asymm_all[14]);
  prob.push_back(asymm_all[19]);
  prob.push_back(asymm_all[24]);
  prob.push_back(asymm_all[29]);
  Plot_p(s_method,title,prob);


  // normalize theory
  float n_theory = 0;
  for(int i=12; i<25; i++) 
    n_theory+=h_bbbar->GetBinContent(i);
  
  float n_reco =0;
  for(int i=12; i<25; i++)
    n_reco+=asymm_all[1]->GetBinContent(i);
  
  float normaliz = n_reco/n_theory;
  h_bbbar->Scale(normaliz);

  PlotCrossSection(s_method,title,asymm_all[0],asymm_all[1],asymm_all[2],h_bbbar);

  if(all==true) {
   
    TCanvas *canvasall_ratio = new TCanvas("canvasall_ratio","canvasall_ratio",800,400);
    TGraphErrors *asymm_all_ratio_corrected=Ratio(asymm_all[1],asymm_all[3]);
    asymm_all_ratio_corrected->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
    asymm_all_ratio_corrected->SetTitle("eL");
    asymm_all_ratio_corrected->GetYaxis()->SetTitle("ratio_corrected");
    asymm_all_ratio_corrected->GetYaxis()->SetRangeUser(0.4,1.4);
    asymm_all_ratio_corrected->GetXaxis()->SetRangeUser(-1,1);
    asymm_all_ratio_corrected->GetYaxis()->SetTitleOffset(1.5);
    asymm_all_ratio_corrected->SetMarkerStyle(1);
    asymm_all_ratio_corrected->SetMarkerSize(1.5);
    asymm_all_ratio_corrected->SetMarkerColor(4);
    asymm_all_ratio_corrected->SetLineColor(4);
    asymm_all_ratio_corrected->Draw("alp");
    canvasall_ratio->Print(TString::Format("ratio_%s_btag1_%0.1f_btag2_%0.1f.eps",s_method.Data(),btag1,btag2));
  }



}

void observable::PlotCrossSection(TString s_method, TString title, TH1F* reco, TH1F* corrected, TH1F* bkg, TH1F* truth) { 
  
  TCanvas *canvasall = new TCanvas(s_method,s_method,1000,800);
  reco->GetXaxis()->SetTitle("cos_{b}(#theta)");
  reco->SetTitle(title);

  reco->GetYaxis()->SetTitle("Entries/0.05rad");
  reco->GetYaxis()->SetRangeUser(0,reco->GetMaximum()*1.5);
  reco->GetYaxis()->SetTitleOffset(1.5);
  reco->SetMarkerStyle(1);
  reco->SetMarkerSize(1.5);
  reco->SetLineColor(1);
  reco->Draw("p");
  
  truth->SetLineColor(3);
  truth->SetLineStyle(2);
  truth->SetLineWidth(2);
  truth->SetFillColor(3);
  truth->SetFillStyle(3002);
  truth->Draw("histofsame");
   
  bkg->SetLineColor(2);
  bkg->SetLineStyle(1);
  bkg->SetLineWidth(1);
  bkg->SetFillColor(2);
  bkg->SetFillStyle(3001);
  bkg->Draw("histofsame");
  
  corrected->SetMarkerStyle(1);
  corrected->SetMarkerSize(1.5);
  corrected->SetMarkerColor(4);
  corrected->SetLineColor(4);
  corrected->Draw("psame");
  IRLESLabel(0.6,0.25,"");
  
  TLegend *legall = new TLegend(0.22,0.60,0.45,0.80);
  legall->AddEntry(reco,"Reco","pl");
  legall->AddEntry(corrected,"Reco corrected","pl");

  legall->AddEntry(truth,"truth","lf");
  legall->AddEntry(bkg,"Reco, q#bar{q}-bkg","lf");
  legall->SetFillColor(0);
  legall->SetLineColor(0);
  legall->SetShadowColor(0);
  legall->Draw();

  canvasall->Print(TString::Format("%s_btag1_%0.1f_btag2_%0.1f.eps",s_method.Data(),btag1,btag2));

}


void observable::Selection(int n_entries=-1)
{

  //  gROOT->Reset();
  SetIrlesStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleX(0.2);
  //gStyle->SetTitleY(0.92);
  gStyle->SetTitleStyle(0);
  //gStyle->SetTitleFontSize(0.03);
  gStyle->SetMarkerSize(0.3);
       
  int bbbar_gen=0;
  int bbbar_gen_recoil=0;
  int qqbar_gen=0;

  TH1F * h_mjj_bb = new TH1F("h_mjj_bb","h_mjj_bb",100,0,500);
  TH1F * h_egamma_bb = new TH1F("h_egamma_bb","h_egamma_bb",100,0,500);
  TH2F * h_btag1_btag2_bb = new TH2F("h_btag1_btag2_bb","h_btag1_btag2_bb",100,0,1,100,0,1);
  TH2F * h_mj1_mj2_bb = new TH2F("h_mj1_mj2_bb","h_mj1_mj2_bb",100,0,500,100,0,500);
  TH2F * h_pj1_pj2_bb = new TH2F("h_pj1_pj2_bb","h_pj1_pj2_bb",100,0,500,100,0,500);

  TH1F * h_mjj_recoil = new TH1F("h_mjj_recoil","h_mjj_recoil",100,0,500);
  TH1F * h_egamma_recoil = new TH1F("h_egamma_recoil","h_egamma_recoil",100,0,500);
  TH2F * h_btag1_btag2_recoil = new TH2F("h_btag1_btag2_recoil","h_btag1_btag2_recoil",100,0,1,100,0,1);
  TH2F * h_mj1_mj2_recoil = new TH2F("h_mj1_mj2_recoil","h_mj1_mj2_recoil",100,0,500,100,0,500);
  TH2F * h_pj1_pj2_recoil = new TH2F("h_pj1_pj2_recoil","h_pj1_pj2_recoil",100,0,500,100,0,500);

  TH1F * h_mjj_qq = new TH1F("h_mjj_qq","h_mjj_qq",100,0,500);
  TH1F * h_egamma_qq = new TH1F("h_egamma_qq","h_egamma_qq",100,0,500);
  TH2F * h_btag1_btag2_qq = new TH2F("h_btag1_btag2_qq","h_btag1_btag2_qq",100,0,1,100,0,1);
  TH2F * h_mj1_mj2_qq = new TH2F("h_mj1_mj2_qq","h_mj1_mj2_qq",100,0,500,100,0,500);
  TH2F * h_pj1_pj2_qq = new TH2F("h_pj1_pj2_qq","h_pj1_pj2_qq",100,0,500,100,0,500);

  
  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;
    if(PreSelection()==false) continue; 

    double reco_b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
    double reco_b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
    double reco_bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));
    double bbmass= sqrt(pow(mc_quark_E[0]+mc_quark_E[1],2)-pow(mc_quark_px[0]+mc_quark_px[1],2)-pow(mc_quark_py[0]+mc_quark_py[1],2)-pow(mc_quark_pz[0]+mc_quark_pz[1],2));

    double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
    double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));
   
    if(abs(mc_quark_pdg[0])==5 && bbmass>200) {
      h_mjj_bb->Fill(reco_bbmass);
      h_egamma_bb->Fill(maxenergy_photon_E);
      h_btag1_btag2_bb->Fill(jet_btag[0],jet_btag[1]);
      h_mj1_mj2_bb->Fill(reco_b1mass,reco_b2mass);
      h_pj1_pj2_bb->Fill(jet0_p,jet1_p);
    }
    if(abs(mc_quark_pdg[0])==5 && bbmass<200) {
      h_mjj_recoil->Fill(reco_bbmass);
      h_egamma_recoil->Fill(maxenergy_photon_E);
      h_btag1_btag2_recoil->Fill(jet_btag[0],jet_btag[1]);
      h_mj1_mj2_recoil->Fill(reco_b1mass,reco_b2mass);
      h_pj1_pj2_recoil->Fill(jet0_p,jet1_p);
    }
    if(abs(mc_quark_pdg[0])!=5) {
      h_mjj_qq->Fill(reco_bbmass);
      h_egamma_qq->Fill(maxenergy_photon_E);
      h_btag1_btag2_qq->Fill(jet_btag[0],jet_btag[1]);
      h_mj1_mj2_qq->Fill(reco_b1mass,reco_b2mass);
      h_pj1_pj2_qq->Fill(jet0_p,jet1_p);
    }
    
  }

  TCanvas *canvas = new TCanvas("selection","selection",1000,1600);
  canvas->Divide(2,3);
  canvas->cd(1);
  h_mjj_qq->SetLineColor(1);
  h_mjj_qq->Draw("histo");
  h_mjj_bb->SetLineColor(2);
  h_mjj_bb->Draw("histosame");
  h_mjj_recoil->SetLineColor(4);
  h_mjj_recoil->Draw("histosame");

  canvas->cd(2);
  h_egamma_qq->SetLineColor(1);
  h_egamma_qq->Draw("histo");
  h_egamma_bb->SetLineColor(2);
  h_egamma_bb->Draw("histosame");
  h_egamma_recoil->SetLineColor(4);
  h_egamma_recoil->Draw("histosame");


  canvas->cd(3);
  h_mj1_mj2_qq->SetMarkerColor(1);
  h_mj1_mj2_qq->Draw("p");
  h_mj1_mj2_bb->SetMarkerColor(2);
  h_mj1_mj2_bb->Draw("psame");
  h_mj1_mj2_recoil->SetMarkerColor(4);
  h_mj1_mj2_recoil->Draw("psame");


  canvas->cd(4);
  h_btag1_btag2_qq->SetMarkerColor(1);
  h_btag1_btag2_qq->Draw("p");
  h_btag1_btag2_recoil->SetMarkerColor(4);
  h_btag1_btag2_recoil->Draw("psame");
  h_btag1_btag2_bb->SetMarkerColor(2);
  h_btag1_btag2_bb->Draw("psame");


  canvas->cd(5);
  h_pj1_pj2_qq->SetMarkerColor(1);
  h_pj1_pj2_qq->Draw("p");
  h_pj1_pj2_bb->SetMarkerColor(2);
  h_pj1_pj2_bb->Draw("psame");
  h_pj1_pj2_recoil->SetMarkerColor(4);
  h_pj1_pj2_recoil->Draw("psame");

   
}

std::vector<TH1F*> observable::Asymm_BcKc(int n_entries=-1, bool reco_truth=false)
{

  //  gROOT->Reset();
  SetIrlesStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleX(0.2);
  //gStyle->SetTitleY(0.92);
  gStyle->SetTitleStyle(0);
  //gStyle->SetTitleFontSize(0.03);
  gStyle->SetMarkerSize(1.5);
       
  int bbbar_gen=0;
  int preselection=0;
  int bkg=0;

  int bbbar_KcKc_reco=0;
  int bbbar_BcBc_reco=0;
  int bbbar_BcKc_reco=0;
  int bbbar_KcBc_reco=0;

  int bbbar_BcKc_same1_reco=0;
  int bbbar_BcKc_same2_reco=0;

  TH1F * h_bbbar = new TH1F("h_bbbar","h_bbbar",40,-1.0,1.0);
  
  TH1F * h_bbbar_KcKc_reco = new TH1F("h_bbbar_KcKc_reco","h_bbbar_KcKc_reco",40,-1.0,1.0);
  TH1F * h_bbbar_KcKc_rejected = new TH1F("h_bbbar_KcKc_rejected","h_bbbar_KcKc_rejected",40,-1.0,1.0);

  TH1F * h_bbbar_BcBc_reco = new TH1F("h_bbbar_BcBc_reco","h_bbbar_BcBc_reco",40,-1.0,1.0);
  TH1F * h_bbbar_BcBc_rejected = new TH1F("h_bbbar_BcBc_rejected","h_bbbar_BcBc_rejected",40,-1.0,1.0);

  TH1F * h_bbbar_BcKc_reco = new TH1F("h_bbbar_BcKc_reco","h_bbbar_BcKc_reco",40,-1.0,1.0);
  TH1F * h_bbbar_BcKc_rejected = new TH1F("h_bbbar_BcKc_rejected","h_bbbar_BcKc_rejected",40,-1.0,1.0);

  TH1F * h_bbbar_KcBc_reco = new TH1F("h_bbbar_KcBc_reco","h_bbbar_KcBc_reco",40,-1.0,1.0);
  TH1F * h_bbbar_KcBc_rejected = new TH1F("h_bbbar_KcBc_rejected","h_bbbar_KcBc_rejected",40,-1.0,1.0);

  TH1F * h_bbbar_BcKc_same1_reco = new TH1F("h_bbbar_BcKc_same1_reco","h_bbbar_BcKc_same1_reco",40,-1.0,1.0);
  TH1F * h_bbbar_BcKc_same1_rejected = new TH1F("h_bbbar_BcKc_same1_rejected","h_bbbar_BcKc_same1_rejected",40,-1.0,1.0);

  TH1F * h_bbbar_BcKc_same2_reco = new TH1F("h_bbbar_BcKc_same2_reco","h_bbbar_BcKc_same2_reco",40,-1.0,1.0);
  TH1F * h_bbbar_BcKc_same2_rejected = new TH1F("h_bbbar_BcKc_same2_rejected","h_bbbar_BcKc_same2_rejected",40,-1.0,1.0);
    
  TH1F * asymm_BcBc[4];
  for(int i=0; i<3; i++) {
    asymm_BcBc[i]= new TH1F(TString::Format("Asymm_BcBc_%i",i),TString::Format("Asymm_BcBc_%i",i),40,-1.0,1.0);
    asymm_BcBc[i]->Sumw2();
  }

  TH1F * asymm_KcKc[4];
  for(int i=0; i<3; i++) {
    asymm_KcKc[i]= new TH1F(TString::Format("Asymm_KcKc_%i",i),TString::Format("Asymm_KcKc_%i",i),40,-1.0,1.0);
    asymm_KcKc[i]->Sumw2();
  }
  //0 == reco (bbbar), 1=truth (for reco selection), 2=bkg (no bbbar), 3= corrected

  TH1F * asymm_BcKc[4];
  for(int i=0; i<3; i++) {
    asymm_BcKc[i]= new TH1F(TString::Format("Asymm_BcKc_%i",i),TString::Format("Asymm_BcKc_%i",i),40,-1.0,1.0);
    asymm_BcKc[i]->Sumw2();
  }

  TH1F * asymm_KcBc[4];
  for(int i=0; i<3; i++) {
    asymm_KcBc[i]= new TH1F(TString::Format("Asymm_KcBc_%i",i),TString::Format("Asymm_KcBc_%i",i),40,-1.0,1.0);
    asymm_KcBc[i]->Sumw2();
  }

  TH1F * asymm_BcKc_same1[4];
  for(int i=0; i<3; i++) {
    asymm_BcKc_same1[i]= new TH1F(TString::Format("Asymm_BcKc_same1_%i",i),TString::Format("Asymm_BcKc_same1_%i",i),40,-1.0,1.0);
    asymm_BcKc_same1[i]->Sumw2();
  }

  TH1F * asymm_BcKc_same2[4];
  for(int i=0; i<3; i++) {
    asymm_BcKc_same2[i]= new TH1F(TString::Format("Asymm_BcKc_same2_%i",i),TString::Format("Asymm_BcKc_same2_%i",i),40,-1.0,1.0);
    asymm_BcKc_same2[i]->Sumw2();
  }

  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    double bbmass= sqrt(pow(mc_quark_E[0]+mc_quark_E[1],2)-pow(mc_quark_px[0]+mc_quark_px[1],2)-pow(mc_quark_py[0]+mc_quark_py[1],2)-pow(mc_quark_pz[0]+mc_quark_pz[1],2));

    std::vector<float> costheta_bbbar;

    for(int ijet=0; ijet<2; ijet++) {
      std::vector<float> p_bbar;
      p_bbar.push_back(mc_quark_px[ijet]);
      p_bbar.push_back(mc_quark_py[ijet]);
      p_bbar.push_back(mc_quark_pz[ijet]);
      costheta_bbbar.push_back(GetCostheta(p_bbar));
    }
    
    if(abs(mc_quark_pdg[0])==5 && bbmass>200) {
      bbbar_gen++;
      costheta_bbbar[0]=  (mc_quark_charge[0] < 0) ? costheta_bbbar[0]: -costheta_bbbar[0];
      costheta_bbbar[1]=  (mc_quark_charge[1] < 0) ? costheta_bbbar[1]: -costheta_bbbar[1];

      h_bbbar->Fill( (costheta_bbbar[0] + costheta_bbbar[1]) /2. );
    }

    if(PreSelection()==false) continue; 
    preselection++;

    if(abs(mc_quark_pdg[0])!=5) bkg++;

    int Kc[2];
    Kc[0]=0; Kc[1]=0;

    int Bc[2];
    Bc[0]=0; Bc[1]=0;
      
    std::vector<float> costheta_KcKc;
    std::vector<float> costheta_BcBc;
    std::vector<float> costheta_BcKc;
    std::vector<float> costheta_KcBc;
    std::vector<float> costheta_BcKc_same1;
    std::vector<float> costheta_BcKc_same2;

    for(int ijet=0; ijet<2; ijet++) {
	
      std::vector<float> p;
      p.push_back(jet_px[ijet]);
      p.push_back(jet_py[ijet]);
      p.push_back(jet_pz[ijet]);

      costheta_BcBc.push_back(GetCostheta(p));
      costheta_KcKc.push_back(GetCostheta(p));
      costheta_BcKc.push_back(GetCostheta(p));
      costheta_KcBc.push_back(GetCostheta(p));
      costheta_BcKc_same1.push_back(GetCostheta(p));
      costheta_BcKc_same2.push_back(GetCostheta(p));

      Bc[ijet]=ChargeBcJet(ijet);
      Kc[ijet]=ChargeKcJet(ijet);

    }//end ijet

    float cos_truth=-2;
      
    if(abs(mc_quark_pdg[0])==5) {
      //      costheta_bbbar[0]=  (mc_quark_charge[0] < 0) ? costheta_bbbar[0]: -costheta_bbbar[0];
      //costheta_bbbar[1]=  (mc_quark_charge[1] < 0) ? costheta_bbbar[1]: -costheta_bbbar[1];

      //  cos_truth =  (costheta_bbbar[0]-costheta_bbbar[1])/2.;

      if(mc_matching==1 && mc_quark_charge[0]<0 )
	cos_truth =(costheta_KcKc[0]-costheta_KcKc[1])/2.;
	
      if(mc_matching==1 && mc_quark_charge[0]>0 )
	cos_truth =-(costheta_KcKc[0]-costheta_KcKc[1])/2.;
	
      if(mc_matching==2 && mc_quark_charge[1]<0 )
	cos_truth =(costheta_KcKc[0]-costheta_KcKc[1])/2.;
	
      if(mc_matching==2 && mc_quark_charge[1]>0 )
	cos_truth =-(costheta_KcKc[0]-costheta_KcKc[1])/2.;
	
      if(reco_truth == true){
	cos_truth = (costheta_bbbar[0] - costheta_bbbar[1])/2.;
      }

	
      //	h_eff->Fill(cos_truth);
    }

    bool taken = false;
    bool rejected = false;


    // ------------------------------------------------------------------------
    // Bc Bc case
    // calculate asymmetry for the different categories
    if(taken ==false) {
      
      if(Bc[0]*Bc[1]<0) {
	if(Bc[0] < 0) h_bbbar_BcBc_reco->Fill( (costheta_BcBc[0]-costheta_BcBc[1])/2.);
	else h_bbbar_BcBc_reco->Fill( -(costheta_BcBc[0]-costheta_BcBc[1])/2.);
      }
      
      //Information to calculate p, for BcBc category
      if(Bc[0]*Bc[1]>0) {
	//bbbar_BcBc_rejected++;
	h_bbbar_BcBc_rejected->Fill( (costheta_BcBc[0]-costheta_BcBc[1])/2.);
	h_bbbar_BcBc_rejected->Fill( -(costheta_BcBc[0]-costheta_BcBc[1])/2.);
      }
      
      
      if(Bc[0]*Bc[1]<0) {
	
	costheta_BcBc[0]=  (Bc[0] < 0) ? costheta_BcBc[0]: -costheta_BcBc[0];
	costheta_BcBc[1]=  (Bc[1] < 0) ? costheta_BcBc[1]: -costheta_BcBc[1];
	float cos_reco= (costheta_BcBc[0]+costheta_BcBc[1])/2.;
	bbbar_BcBc_reco++;
	
	
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_BcBc[0]->Fill(cos_reco);
	  asymm_BcBc[1]->Fill(cos_truth);
	  // h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}
	
	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_BcBc[2]->Fill(cos_reco);
	}
	taken = true;

      }
    }


    // -------------------------------------------------------------------------
    //Information to calculate p, for KcKc category
       
    if(taken == false ) {
	
      if(Kc[0]*Kc[1]<0) {
	if(Kc[0] < 0) h_bbbar_KcKc_reco->Fill( (costheta_KcKc[0]-costheta_KcKc[1])/2.);
	else h_bbbar_KcKc_reco->Fill( -(costheta_KcKc[0]-costheta_KcKc[1])/2.);
      }

      if(Kc[0]*Kc[1]>0) {
	//bbbar_KcKc_rejected++;
	h_bbbar_KcKc_rejected->Fill( (costheta_KcKc[0]-costheta_KcKc[1])/2.);
	h_bbbar_KcKc_rejected->Fill( -(costheta_KcKc[0]-costheta_KcKc[1])/2.);
      }
	
      if(Kc[0]*Kc[1]<0) {
	// ------------------------------------------------------------------------
	// Kc Kc case
	// calculate asymmetry for the different categories
	  
	costheta_KcKc[0]=  (Kc[0] < 0) ? costheta_KcKc[0]: -costheta_KcKc[0];
	costheta_KcKc[1]=  (Kc[1] < 0) ? costheta_KcKc[1]: -costheta_KcKc[1];
	float cos_reco= (costheta_KcKc[0]+costheta_KcKc[1])/2.;
	bbbar_KcKc_reco++;
	  
	  
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_KcKc[0]->Fill(cos_reco);
	  asymm_KcKc[1]->Fill(cos_truth);
	  //  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}
	  
	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_KcKc[2]->Fill(cos_reco);
	}
	taken = true;
	  
      }
    }

    // ------------------------------------------------------------------------

      //Information to calculate p, for BcKc category
    if(Bc[0]*Kc[1]>0 && (Bc[1]==0 && Kc[0]==0 )){
      //bbbar_KcKc_rejected++;
      h_bbbar_BcKc_rejected->Fill( (costheta_BcKc[0]-costheta_BcKc[1])/2.);
      h_bbbar_BcKc_rejected->Fill( -(costheta_BcKc[0]-costheta_BcKc[1])/2.);
    }
    
    if(Bc[0]*Kc[1]<0 && Bc[1]==0 && Kc[0]==0){
      if(Bc[0] < 0) h_bbbar_BcKc_reco->Fill( (costheta_BcKc[0]-costheta_BcKc[1])/2.);
      else h_bbbar_BcKc_reco->Fill( -(costheta_BcKc[0]-costheta_BcKc[1])/2.);
    }
    
    if(taken == false) {
      
      if( Bc[0]*Kc[1]<0 && Bc[1]==0 && Kc[0]==0) {
	// -------------------------------------------
	//BcKc 
	//case a
	costheta_BcKc[0]=  (Bc[0] < 0) ? costheta_BcKc[0]: -costheta_BcKc[0];
	costheta_BcKc[1]=  (Kc[1] < 0) ? costheta_BcKc[1]: -costheta_BcKc[1];
	  
	bbbar_BcKc_reco++;
	  
	float cos_reco= (costheta_BcKc[0]+costheta_BcKc[1])/2.;
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_BcKc[0]->Fill(cos_reco);
	  asymm_BcKc[1]->Fill(cos_truth);
	  //	  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}
	  
	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_BcKc[2]->Fill(cos_reco);
	}
	  
	taken = true;
      }
    }

    //Information to calculate p, for BcKc category
    if(Kc[0]*Bc[1]>0 && Bc[0]==0 && Kc[1]==0) {
      //bbbar_KcKc_rejected++;
      h_bbbar_KcBc_rejected->Fill( (costheta_KcBc[0]-costheta_KcBc[1])/2.);
      h_bbbar_KcBc_rejected->Fill( -(costheta_KcBc[0]-costheta_KcBc[1])/2.);
      //      h_bbbar_BcKc_rejected->Fill( (costheta_KcBc[0]-costheta_KcBc[1])/2.);
      //h_bbbar_BcKc_rejected->Fill( -(costheta_KcBc[0]-costheta_KcBc[1])/2.);
    }
    
    if(Kc[0]*Bc[1]<0 && Bc[0]==0 && Kc[1]==0) {
      if(Kc[0] < 0) h_bbbar_KcBc_reco->Fill( (costheta_KcBc[0]-costheta_KcBc[1])/2.);
      else h_bbbar_KcBc_reco->Fill( -(costheta_KcBc[0]-costheta_KcBc[1])/2.);
      
      //      if(Kc[0] < 0) h_bbbar_BcKc_reco->Fill( (costheta_KcBc[0]-costheta_KcBc[1])/2.);
      //else h_bbbar_BcKc_reco->Fill( -(costheta_KcBc[0]-costheta_KcBc[1])/2.);
    }
    
    if(taken == false) {

      if( Kc[0]*Bc[1]<0 && Bc[0]==0 && Kc[1]==0)  {
	// -------------------------------------------
	//KcBc 
	//case b
	costheta_KcBc[0]=  (Kc[0] < 0) ? costheta_KcBc[0]: -costheta_KcBc[0];
	costheta_KcBc[1]=  (Bc[1] < 0) ? costheta_KcBc[1]: -costheta_KcBc[1];

	bbbar_KcBc_reco++;

	float cos_reco= (costheta_KcBc[0]+costheta_KcBc[1])/2.;
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_KcBc[0]->Fill(cos_reco);
	  asymm_KcBc[1]->Fill(cos_truth);
	  //	  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}

	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_KcBc[2]->Fill(cos_reco);
	}
	taken = true;
      }
    }
    
    // --------------------------------------------------------------------------
    // Same side 1
    //Information to calculate p, for BcKc category
    if(Bc[0]*Kc[0]<0 && Bc[1]==0 && Kc[1]==0){
      //bbbar_KcKc_rejected++;
      h_bbbar_BcKc_same1_rejected->Fill( (costheta_BcKc_same1[0]-costheta_BcKc_same1[1])/2.);
      h_bbbar_BcKc_same1_rejected->Fill( -(costheta_BcKc_same1[0]-costheta_BcKc_same1[1])/2.);
    }
    
    if(Bc[0]*Kc[0]>0 && Bc[1]==0 && Kc[1]==0){
      if(Bc[0] < 0) h_bbbar_BcKc_same1_reco->Fill( (costheta_BcKc_same1[0]-costheta_BcKc_same1[1])/2.);
      else h_bbbar_BcKc_same1_reco->Fill( -(costheta_BcKc_same1[0]-costheta_BcKc_same1[1])/2.);
    }
    
    if(taken == false) {
      
      if( Bc[0]*Kc[0]>0 && Bc[1]==0 && Kc[1]==0) {
	// -------------------------------------------
	//BcKc 
	//case a
	costheta_BcKc_same1[0]=  (Bc[0] < 0) ? costheta_BcKc_same1[0]: -costheta_BcKc_same1[0];
	costheta_BcKc_same1[1]=  (Bc[0] > 0) ? costheta_BcKc_same1[1]: -costheta_BcKc_same1[1];
	  
	bbbar_BcKc_same1_reco++;
	  
	float cos_reco= (costheta_BcKc_same1[0]+costheta_BcKc_same1[1])/2.;
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_BcKc_same1[0]->Fill(cos_reco);
	  asymm_BcKc_same1[1]->Fill(cos_truth);
	  //	  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}
	  
	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_BcKc_same1[2]->Fill(cos_reco);
	}
	  
	taken = true;
      }
    }


    // --------------------------------------------------------------------------
    // Same side 2
    //Information to calculate p, for BcKc category
    if(Bc[1]*Kc[1]<0 && Bc[0]==0 && Kc[0]==0){
      //bbbar_KcKc_rejected++;
      h_bbbar_BcKc_same2_rejected->Fill( (costheta_BcKc_same2[0]-costheta_BcKc_same2[1])/2.);
      h_bbbar_BcKc_same2_rejected->Fill( -(costheta_BcKc_same2[0]-costheta_BcKc_same2[1])/2.);
    }
    
    if(Bc[1]*Kc[1]>0 && Bc[0]==0 && Kc[0]==0){
      if(Bc[0] < 0) h_bbbar_BcKc_same2_reco->Fill( (costheta_BcKc_same2[0]-costheta_BcKc_same2[1])/2.);
      else h_bbbar_BcKc_same2_reco->Fill( -(costheta_BcKc_same2[0]-costheta_BcKc_same2[1])/2.);
    }
    
    if(taken == false) {      
      if( Bc[1]*Kc[1]>0 && Bc[0]==0 && Kc[0]==0) {
	// -------------------------------------------
	//BcKc 
	//case a
	costheta_BcKc_same2[0]=  (Bc[1] > 0) ? costheta_BcKc_same2[0]: -costheta_BcKc_same2[0];
	costheta_BcKc_same2[1]=  (Bc[1] < 0) ? costheta_BcKc_same2[1]: -costheta_BcKc_same2[1];
	  
	bbbar_BcKc_same2_reco++;
	  
	float cos_reco= (costheta_BcKc_same2[0]+costheta_BcKc_same2[1])/2.;
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_BcKc_same2[0]->Fill(cos_reco);
	  asymm_BcKc_same2[1]->Fill(cos_truth);
	  //	  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}
	  
	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_BcKc_same2[2]->Fill(cos_reco);
	}
	  
	taken = true;
      }
    }




  

     
  }//end loop

    /// ---****************************************************************************************
  // BcBc
  std::vector<float> p_b_vect=CalculateP(h_bbbar_BcBc_reco,h_bbbar_BcBc_rejected);

  TH1F * p_b_histo = new TH1F("p_b_histo_Kc","p_b_histo_Kc",20,-1,0);
  p_b_histo->Sumw2();
  for(unsigned i=0; i<p_b_vect.size()/2; i++) {
    p_b_histo->SetBinContent(i+1,p_b_vect.at(i));
    p_b_histo->SetBinError(i+1,p_b_vect.at(i+20));
  }
  asymm_BcBc[3]=CorrectHistoDoubleTag(asymm_BcBc[0],p_b_vect);
  asymm_BcBc[0]->Add(asymm_BcBc[2]);
  asymm_BcBc[1]->Add(asymm_BcBc[2]);
  asymm_BcBc[3]->Add(asymm_BcBc[2]);

  PlotCrossSection("BcBc","Bc/Bc case, eL",asymm_BcBc[0],asymm_BcBc[3],asymm_BcBc[2],asymm_BcBc[1]);

   /// ---****************************************************************************************
   // KcKc
  std::vector<float> p_k_vect=CalculateP(h_bbbar_KcKc_reco,h_bbbar_KcKc_rejected);
  
  TH1F * p_k_histo = new TH1F("p_k_histo_Kc","p_k_histo_Kc",20,-1,0);
  p_k_histo->Sumw2();
  for(unsigned i=0; i<p_k_vect.size()/2; i++) {
    p_k_histo->SetBinContent(i+1,p_k_vect.at(i));
    p_k_histo->SetBinError(i+1,p_k_vect.at(i+20));
  }

  asymm_KcKc[3]=CorrectHistoDoubleTag(asymm_KcKc[0],p_k_vect);
  asymm_KcKc[0]->Add(asymm_KcKc[2]);
  asymm_KcKc[1]->Add(asymm_KcKc[2]);
  asymm_KcKc[3]->Add(asymm_KcKc[2]);

  PlotCrossSection("KcKc","Kc/Kc case, eL",asymm_KcKc[0],asymm_KcKc[3],asymm_KcKc[2],asymm_KcKc[1]);


  /// ---****************************************************************************************
  // BcKc

  std::vector<float> p_bk_vect=CalculateP(h_bbbar_BcKc_reco,h_bbbar_BcKc_rejected);
  TH1F * p_bk_histo = new TH1F("p_bk_histo_Kc","p_bk_histo_Kc",20,-1,0);
  p_bk_histo->Sumw2();
  for(unsigned i=0; i<p_bk_vect.size()/2; i++) {
    p_bk_histo->SetBinContent(i+1,p_bk_vect.at(i));
    p_bk_histo->SetBinError(i+1,p_bk_vect.at(i+20));
  }
  
  asymm_BcKc[3]=CorrectHistoDoubleTag(asymm_BcKc[0],p_bk_vect);
  asymm_BcKc[0]->Add(asymm_BcKc[2]);
  asymm_BcKc[1]->Add(asymm_BcKc[2]);
  asymm_BcKc[3]->Add(asymm_BcKc[2]);

  PlotCrossSection("BcKc","Bc/Kc case, eL",asymm_BcKc[0],asymm_BcKc[3],asymm_BcKc[2],asymm_BcKc[1]);

  
  /// ---****************************************************************************************
  // KcBc
  
  std::vector<float> p_kb_vect=CalculateP(h_bbbar_KcBc_reco,h_bbbar_KcBc_rejected);
  asymm_KcBc[3]=CorrectHistoDoubleTag(asymm_KcBc[0],p_kb_vect);
  asymm_KcBc[0]->Add(asymm_KcBc[2]);
  asymm_KcBc[1]->Add(asymm_KcBc[2]);
  asymm_KcBc[3]->Add(asymm_KcBc[2]);

  TH1F * p_kb_histo = new TH1F("p_kb_histo_Kc","p_kb_histo_Kc",20,-1,0);
  p_kb_histo->Sumw2();
  for(unsigned i=0; i<p_kb_vect.size()/2; i++) {
    p_kb_histo->SetBinContent(i+1,p_kb_vect.at(i));
    p_kb_histo->SetBinError(i+1,p_kb_vect.at(i+20));
  }
      
  PlotCrossSection("KcBc","Kc/Bc case, eL",asymm_KcBc[0],asymm_KcBc[3],asymm_KcBc[2],asymm_KcBc[1]);

  /// ---****************************************************************************************
  // BcKc_same1

  std::vector<float> p_bk_same1_vect=CalculateP(h_bbbar_BcKc_same1_reco,h_bbbar_BcKc_same1_rejected);

  asymm_BcKc_same1[3]=CorrectHistoDoubleTag(asymm_BcKc_same1[0],p_bk_vect);
  asymm_BcKc_same1[0]->Add(asymm_BcKc_same1[2]);
  asymm_BcKc_same1[1]->Add(asymm_BcKc_same1[2]);
  asymm_BcKc_same1[3]->Add(asymm_BcKc_same1[2]);

  TH1F * p_bk_same1_histo = new TH1F("p_bk_same1","p_bk_same1",20,-1,0);
  p_bk_same1_histo->Sumw2();
  for(unsigned i=0; i<p_bk_same1_vect.size()/2; i++) {
    p_bk_same1_histo->SetBinContent(i+1,p_bk_same1_vect.at(i));
    p_bk_same1_histo->SetBinError(i+1,p_bk_same1_vect.at(i+20));
  }

  PlotCrossSection("BcKc_same1","Kc/Bc same1 case, eL",asymm_BcKc_same1[0],asymm_BcKc_same1[3],asymm_BcKc_same1[2],asymm_BcKc_same1[1]);

  /// ---****************************************************************************************
  // BcKc_same2
  std::vector<float> p_bk_same2_vect=CalculateP(h_bbbar_BcKc_same2_reco,h_bbbar_BcKc_same2_rejected);

  asymm_BcKc_same2[3]=CorrectHistoDoubleTag(asymm_BcKc_same2[0],p_bk_vect);
  asymm_BcKc_same2[0]->Add(asymm_BcKc_same2[2]);
  asymm_BcKc_same2[1]->Add(asymm_BcKc_same2[2]);
  asymm_BcKc_same2[3]->Add(asymm_BcKc_same2[2]);

  TH1F * p_bk_same2_histo = new TH1F("p_bk_same2","p_bk_same2",20,-1,0);
  p_bk_same2_histo->Sumw2();
  for(unsigned i=0; i<p_bk_same2_vect.size()/2; i++) {
    p_bk_same2_histo->SetBinContent(i+1,p_bk_same2_vect.at(i));
    p_bk_same2_histo->SetBinError(i+1,p_bk_same2_vect.at(i+20));
  }

  PlotCrossSection("BcKc_same2","Kc/Bc same2 case, eL",asymm_BcKc_same2[0],asymm_BcKc_same2[3],asymm_BcKc_same2[2],asymm_BcKc_same2[1]);

  // ***************************************************************  
  cout<<" Efficiencies: "<<endl;
  cout<<" Preselection: "<<100.*float(preselection)/float(bbbar_gen)<<" %     bkg: "<<100.*float(bkg)/float(preselection)<<" %"<<endl;
  cout<<" BcBc: "<<100.*float(bbbar_BcBc_reco)/float(bbbar_gen)<<" %     bkg: "<<100.*float(asymm_BcBc[2]->GetEntries())/float(asymm_BcBc[0]->GetEntries())<<" %"<<endl;
  cout<<" KcKc: "<<100.*float(bbbar_KcKc_reco)/float(bbbar_gen)<<" %     bkg: "<<100.*float(asymm_KcKc[2]->GetEntries())/float(asymm_KcKc[0]->GetEntries())<<" %"<<endl;
  cout<<" BcKc(jet1): "<<100.*float(bbbar_BcKc_same1_reco)/float(bbbar_gen)<<" %     bkg: "<<100.*float(asymm_BcKc_same1[2]->GetEntries())/float(asymm_BcKc_same1[0]->GetEntries())<<" %"<<endl;
  cout<<" BcKc(jet2): "<<100.*float(bbbar_BcKc_same2_reco)/float(bbbar_gen)<<" %     bkg: "<<100.*float(asymm_BcKc_same2[2]->GetEntries())/float(asymm_BcKc_same2[0]->GetEntries())<<" %"<<endl;
  cout<<" BcKc: "<<100.*float(bbbar_BcKc_reco)/float(bbbar_gen)<<" %     bkg: "<<100.*float(asymm_BcKc[2]->GetEntries())/float(asymm_BcKc[0]->GetEntries())<<" %"<<endl;
  cout<<" KcBc: "<<100.*float(bbbar_KcBc_reco)/float(bbbar_gen)<<" %     bkg: "<<100.*float(asymm_KcBc[2]->GetEntries())/float(asymm_KcBc[0]->GetEntries())<<" %"<<endl;

  
  // ***************************************************************  

  std::vector<TH1F*> result;
  result.push_back(asymm_BcBc[0]);//reco
  result.push_back(asymm_BcBc[3]);//corrected
  result.push_back(asymm_BcBc[2]);//bkg
  result.push_back(asymm_BcBc[1]);//true
  result.push_back(p_b_histo);
   
  result.push_back(asymm_KcKc[0]);
  result.push_back(asymm_KcKc[3]);
  result.push_back(asymm_KcKc[2]);
  result.push_back(asymm_KcKc[1]);
  result.push_back(p_k_histo);

  result.push_back(asymm_BcKc[0]);
  result.push_back(asymm_BcKc[3]);
  result.push_back(asymm_BcKc[2]);
  result.push_back(asymm_BcKc[1]);
  result.push_back(p_bk_histo);

  result.push_back(asymm_KcBc[0]);
  result.push_back(asymm_KcBc[3]);
  result.push_back(asymm_KcBc[2]);
  result.push_back(asymm_KcBc[1]);
  result.push_back(p_kb_histo);

  result.push_back(asymm_BcKc_same1[0]);
  result.push_back(asymm_BcKc_same1[3]);
  result.push_back(asymm_BcKc_same1[2]);
  result.push_back(asymm_BcKc_same1[1]);
  result.push_back(p_bk_same1_histo);

  result.push_back(asymm_BcKc_same2[0]);
  result.push_back(asymm_BcKc_same2[3]);
  result.push_back(asymm_BcKc_same2[2]);
  result.push_back(asymm_BcKc_same2[1]);
  result.push_back(p_bk_same2_histo);

  result.push_back(h_bbbar);
  return result;
}

          
std::vector<float> observable::CalculateP(TH1F* h_accepted, TH1F *h_rejected)
{


  for(int i=1; i<41; i++) {
    float accepted = h_accepted->GetBinContent(41-i);
    float rejected = h_rejected->GetBinContent(41-i);
    accepted += h_accepted->GetBinContent(i);
    // rejected += h_rejected->GetBinContent(i);
    float a=1;
    float b=-1;
    float c= rejected/ (2* (accepted+rejected));
    float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
    float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
  }

  std::vector<float> result_error;

  for(int i=1; i<21; i++) {
    std::vector<float> result_j;
    for(int i1=-1; i1<2; i1+=2) {
      for(int i2=-1; i2<2; i2+=2) {
	//	for(int i3=-1; i3<2; i3+=2) {
	float accepted = h_accepted->GetBinContent(41-i)+i1*sqrt(h_accepted->GetBinContent(21-i));
	float rejected = h_rejected->GetBinContent(41-i)+i2*sqrt(h_rejected->GetBinContent(21-i));
	accepted += h_accepted->GetBinContent(i)+i1*sqrt(h_accepted->GetBinContent(i));
	  
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
      float std_dev=0;
      for(unsigned j=0; j<result_j.size(); j++) {
	if(result_j.at(j)>0) {
	  std_dev=pow(result_j.at(j)-average,2);
	}
      }
      std_dev=sqrt(std_dev/(n-1));
      result_error.push_back(std_dev);
    } else result_error.push_back(0);
  }
    
  std::vector<float> result;
  for(int i=1; i<21; i++) {
    float accepted = h_accepted->GetBinContent(41-i);
    float rejected = h_rejected->GetBinContent(41-i);
    accepted += h_accepted->GetBinContent(i);
    float a=1;
    float b=-1;
    float c= rejected/ (2* (accepted+rejected));
    float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
    float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
    if(p>0.99) p=0;
    if(p2>0.99) p2=0;
    if(p>0 || p2>0 ) result.push_back(max(p,p2));
    else result.push_back(-1);

  } 

  float average=0;
  float n=0;
  for(unsigned i=0; i<result.size(); i++) {
    if(result.at(i)>0 && result.at(i)!=0.5) { average+=result.at(i); n++;}
  }

  
  average/=n;
  for(unsigned i=0; i<result_error.size(); i++) {
    if(result.at(i)<0) result.at(i)=average;
    if(result.at(i)==0.5) result.at(i)=average;
    if(result_error.at(i)>0) result.push_back(result_error.at(i));
    else result.push_back(0);
  }

  return result;
  
}


TGraphErrors* observable::Ratio(TH1F* histo, TH1F* histo_ref) {

  double x[20], y[20], ey[20];
  
  for(int i=0; i<20; i++) {
    x[i]=histo_ref->GetBinCenter(i+1);
    y[i]= histo->GetBinContent(i+1)/histo_ref->GetBinContent(i+1);
    ey[i]=sqrt( pow(histo->GetBinError(i+1)/histo_ref->GetBinContent(i+1),2) + pow(histo->GetBinContent(i+1)*histo_ref->GetBinError(i+1)/(2*histo_ref->GetBinContent(i+1)*histo_ref->GetBinContent(i+1)),2));
  }

  TGraphErrors * result = new TGraphErrors(20,x,y,0,ey);
  return result;
}

TH1F* observable::CorrectHistoDoubleTag(TH1F* histo, std::vector<float> p_vect) {
  
  TH1F * corrected_up = new TH1F("corrected_up","corrected_up",40,-1,1);
  corrected_up->Sumw2(); 
  for(int i=1; i<21; i++) {
    float nm_reco=histo->GetBinContent(i);
    float np_reco=histo->GetBinContent(41-i);
    
    float p=p_vect.at(i-1)+p_vect.at(40-(21-i));
    float q=1-p;
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
    corrected_up->SetBinContent(i,(np_reco*q*q-nm_reco*p*p)*weight);
    corrected_up->SetBinContent(41-i,-(np_reco*p*p-nm_reco*q*q)*weight);
  }
  
  TH1F * corrected_down = new TH1F("corrected_down","corrected_down",40,-1,1);
  corrected_down->Sumw2(); 
  for(int i=1; i<21; i++) {
    float nm_reco=histo->GetBinContent(i);
    float np_reco=histo->GetBinContent(41-i);
    
    float p=p_vect.at(i-1)-p_vect.at(40-(21-i));
    float q=1-p;
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
    corrected_down->SetBinContent(i,(np_reco*q*q-nm_reco*p*p)*weight);
    corrected_down->SetBinContent(41-i,-(np_reco*p*p-nm_reco*q*q)*weight);
  }
  

  TH1F * corrected = new TH1F("corrected","corrected",40,-1,1);
  corrected->Sumw2();
  for(int i=1; i<21; i++) {
    float p=p_vect.at(i-1);
    float q=1-p;
    float nm_reco=histo->GetBinContent(i);
    float np_reco=histo->GetBinContent(41-i);
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
    
    corrected->SetBinContent(i,(np_reco*q*q-nm_reco*p*p)*weight);
    corrected->SetBinContent(41-i,-(np_reco*p*p-nm_reco*q*q)*weight);

    float error=abs(corrected_up->GetBinContent(i) - corrected_down->GetBinContent(i));
    corrected->SetBinError(i,sqrt(pow(error,2) + (np_reco*pow(q*q,2)+nm_reco*pow(p*p,2))*weight*weight ));
    
    error=abs(corrected_up->GetBinContent(41-i) - corrected_down->GetBinContent(41-i));
    corrected->SetBinError(41-i,sqrt(pow(error,2) + (np_reco*pow(p*p,2)+nm_reco*pow(q*q,2))*weight*weight));

  }
  std::cout<<" end correction histogram " <<endl;
  return corrected;


}

void observable::Plot_p(TString s_method, TString title, std::vector<TH1F*> prob){

  TGraphErrors * g_prob[6];
  for(int i=0; i<6; i++) {
    g_prob[i]=new TGraphErrors(prob[i]);
    Double_t *ex=g_prob[i]->GetEX();
    for(int j=0; j<g_prob[i]->GetN(); j++) ex[j]=0;
  }
  
    
  TCanvas *canvas_prob = new TCanvas(s_method,s_method,1000,800);
  g_prob[0]->GetXaxis()->SetTitle("cos_{b}(#theta)");
  g_prob[0]->SetTitle(title);
  g_prob[0]->GetYaxis()->SetTitle("p");
  g_prob[0]->GetYaxis()->SetRangeUser(0,1.2);
  g_prob[0]->GetYaxis()->SetTitleOffset(1.5);
  g_prob[0]->SetMarkerStyle(21);
  g_prob[0]->SetMarkerSize(1.5);
  g_prob[0]->SetLineColor(1);
  g_prob[0]->SetMarkerColor(1);
  g_prob[0]->Draw("apl");
  for(int i=1; i<6; i++) {
    g_prob[i]->SetMarkerStyle(21+i);
    g_prob[i]->SetMarkerSize(1.5);
    g_prob[i]->SetLineColor(1+i);
    g_prob[i]->SetMarkerColor(1+i);
    g_prob[i]->Draw("pl");
  }

  IRLESLabel(0.6,0.25,"");
  
  TLegend *legall = new TLegend(0.22,0.30,0.45,0.50);
  for(int i=0; i<6; i++)legall->AddEntry(g_prob[i],TString::Format("Category %i",i+1),"pl");
  legall->SetFillColor(0);
  legall->SetLineColor(0);
  legall->SetShadowColor(0);
  legall->Draw();
  
  canvas_prob->Print(TString::Format("%s_pvalues_btag1_%0.1f_btag2_%0.1f.eps",s_method.Data(),btag1,btag2));
}


void observable::Efficiency_plot(TString s_method, TString title, std::vector<TH1F*> eff){

  TGraphErrors * g_eff[8];
  g_eff[6]=new TGraphErrors(eff[6]); // all reco
  g_eff[7]=new TGraphErrors(eff[7]); // all parton

  Double_t *y_reco=g_eff[6]->GetY();
  Double_t *ex_reco=g_eff[6]->GetEX();
  Double_t *x_reco=g_eff[6]->GetX();
  Double_t *ey_reco=g_eff[6]->GetEY();
  Double_t *y_parton=g_eff[7]->GetY();

  //  efficiency global
  double x[40], ex[40], y[40], ey[40];
  int n=0;
  for(int j=0; j<g_eff[6]->GetN(); j++) {
    n++;
    ex[j]=0;
    x[j]=x_reco[j];
    if(y_parton[j]!=0 ) {
      y[j]=y_reco[j]/y_parton[j];
      ey[j]=ey_reco[j]/y_parton[j];
    } else {
      y[j]=0;
      ey[j]=0;
    }
  }
  TGraphErrors * g_eff_global = new TGraphErrors(n,x,y,ex,ey);

  //effcieicny categories
  for(int i=0; i<6; i++) {
    g_eff[i]=new TGraphErrors(eff[i]);
    Double_t *ex=g_eff[i]->GetEX();
    Double_t *y=g_eff[i]->GetY();
    Double_t *ey=g_eff[i]->GetEY();
    for(int j=0; j<g_eff[i]->GetN(); j++) {
      ex[j]=0;
      if(y_reco[j]!=0 ) {
	y[j]=y[j]/y_reco[j];
	ey[j]=ey[j]/y_reco[j];
      } else {
	y[j]=0;
	ey[j]=0;
      }
    }
  }
  
  
    
  TCanvas *canvas_eff = new TCanvas(s_method,s_method,2600,900);
  // canvas_eff->Divide(2,1);
  //  canvas_eff->cd(1);
  g_eff[0]->GetXaxis()->SetTitle("cos_{b}(#theta)");
  g_eff[0]->SetTitle(title);
  g_eff[0]->GetYaxis()->SetTitle("N(#theta)^{reco truth}_{category} / N(#theta)^{parton}");
  g_eff[0]->GetYaxis()->SetRangeUser(-0.5,1.5);
  g_eff[0]->GetYaxis()->SetTitleOffset(1.5);
  g_eff[0]->SetMarkerStyle(21);
  g_eff[0]->SetMarkerSize(1.5);
  g_eff[0]->SetLineColor(1);
  g_eff[0]->SetMarkerColor(1);
  g_eff[0]->Draw("apl");
  for(int i=1; i<6; i++) {
    g_eff[i]->SetMarkerStyle(21+i);
    g_eff[i]->SetMarkerSize(1.5);
    g_eff[i]->SetLineColor(1+i);
    g_eff[i]->SetMarkerColor(1+i);
    g_eff[i]->Draw("pl");
  }

  IRLESLabel(0.6,0.25,"");
  
  TLegend *legall = new TLegend(0.75,0.65,0.90,0.85);
  for(int i=0; i<6; i++)legall->AddEntry(g_eff[i],TString::Format("Category %i",i+1),"pl");
  legall->SetFillColor(0);
  legall->SetLineColor(0);
  legall->SetShadowColor(0);
  legall->Draw();

  /*  canvas_eff->cd(2);
  g_eff_global->GetXaxis()->SetTitle("cos_{b}(#theta)");
  g_eff_global->SetTitle("e^{-}_{L}e^{+}_{R} #rightarrow b#bar{b}, 250 GeV, L=250 fb^{-1}");
  g_eff_global->GetYaxis()->SetTitle("N(#theta)^{reco truth}_{all} / N(#theta)^{parton}");
  g_eff_global->GetYaxis()->SetRangeUser(-0.5,1.5);
  g_eff_global->GetYaxis()->SetTitleOffset(1.5);
  g_eff_global->SetMarkerStyle(21);
  g_eff_global->SetMarkerSize(1.5);
  g_eff_global->SetLineColor(1);
  g_eff_global->SetMarkerColor(1);
  g_eff_global->Draw("apl");
  IRLESLabel(0.6,0.25,"");*/

  canvas_eff->Print(TString::Format("%s_eff_btag1_%0.1f_btag2_%0.1f.eps",s_method.Data(),btag1,btag2));
}


//-----------------------------------------------------

bool observable::PreSelection() {

  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
  double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
  double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));
   
  double b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
  double b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
  double bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

  double jj_pT= sqrt(pow(jet_px[0]+jet_px[1],2)+pow(jet_py[0]+jet_py[1],2));
   
  //if( bbmass < 180 || (b1mass+b2mass) >120 || maxenergy_photon_E>40 || jet_btag[0]<btag1 || jet_btag[1]<btag2 || jet0_p<40 || jet1_p<40) return false;
  //500GeV
  //  if(bbmass < 300 ||  maxenergy_photon_E>100 || jet_btag[0]<btag1 || jet_btag[1]<btag2) return false; 
  //250GeV
  if( bbmass < 180 ||  (b1mass+b2mass) >120 || maxenergy_photon_E>40 || jet_btag[0]<btag1 || jet_btag[1]<btag2 ) return false;
  
  return true;
}

float observable::ChargeBcJet(int ijet) {
  double charge=0;

  //  if(jet_btag[ijet] <0.8) return charge;
  
  for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
    for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
      charge+=jet_track_charge[ijet][ivtx][itrack];
    }
  }

  return charge;
}

float observable::ChargeKcJet(int ijet) {

  double charge=0;

  // if(jet_btag[ijet] <0.3) return charge;

  for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
    for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
      if(jet_track_iskaon[ijet][ivtx][itrack]==1) charge+=jet_track_kaoncharge[ijet][ivtx][itrack];
    }
  }
    
  return charge;
}

