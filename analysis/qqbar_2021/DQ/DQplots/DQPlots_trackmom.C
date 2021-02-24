#include "DQPlots.h"


void DQPlots_trackmom() {

    
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.5);
  TGaxis::SetMaxDigits(3);

  TString file="../DQ_250GeV_15162.root";

  std::vector<TString> leg;
  leg.push_back("Pions");
  leg.push_back("Kaons");
  leg.push_back("Protons");

 
  //b
  std::vector<TH1F *> histos_bsec;
  histos_bsec.push_back(getHisto("reco",file,"sectrack_mom_Pi_b"));
  histos_bsec.push_back(getHisto("reco",file,"sectrack_mom_K_b"));
  histos_bsec.push_back(getHisto("reco",file,"sectrack_mom_p_b"));

  Compare_3Histos("b-secondary tracks",histos_bsec,false,leg,"momentum [GeV]","entries");

  //c
  std::vector<TH1F *> histos_csec;
  histos_csec.push_back(getHisto("reco",file,"sectrack_mom_Pi_c"));
  histos_csec.push_back(getHisto("reco",file,"sectrack_mom_K_c"));
  histos_csec.push_back(getHisto("reco",file,"sectrack_mom_p_c"));

  Compare_3Histos("c-secondary tracks",histos_csec,false,leg,"momentum [GeV]","entries");

  //c-primar
  std::vector<TH1F *> histos_cprim;
  histos_cprim.push_back(getHisto("reco",file,"primtrack_mom_Pi_c"));
  histos_cprim.push_back(getHisto("reco",file,"primtrack_mom_K_c"));
  histos_cprim.push_back(getHisto("reco",file,"primtrack_mom_p_c"));

  Compare_3Histos("c-primary tracks",histos_cprim,false,leg,"momentum [GeV]","entries");


  //uds
  std::vector<TH1F *> histos_udssec;
  histos_udssec.push_back(getHisto("reco",file,"sectrack_mom_Pi_uds"));
  histos_udssec.push_back(getHisto("reco",file,"sectrack_mom_K_uds"));
  histos_udssec.push_back(getHisto("reco",file,"sectrack_mom_p_uds"));

  Compare_3Histos("s-secondary tracks",histos_udssec,false,leg,"momentum [GeV]","entries");

  //uds-primar
  std::vector<TH1F *> histos_udsprim;
  histos_udsprim.push_back(getHisto("reco",file,"primtrack_mom_Pi_uds"));
  histos_udsprim.push_back(getHisto("reco",file,"primtrack_mom_K_uds"));
  histos_udsprim.push_back(getHisto("reco",file,"primtrack_mom_p_uds"));

  Compare_3Histos("s-primary tracks",histos_udsprim,false,leg,"momentum [GeV]","entries");
  
  
}
