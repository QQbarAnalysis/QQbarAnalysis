#include "DQPlots.h"


void DQPlots_flavour() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.5);


 
  TString file="../DQ_250GeV_15162.root";
  file="DQ_250GeV_250GeV_DBD_eL_norestorer.root";
  
  std::vector<TString> leg;
  leg.push_back("b-quark");
  leg.push_back("c-quark");
  leg.push_back("uds-quark");

  //btag
  std::vector<TH1F *> histos_btag_rad;
  histos_btag_rad.push_back(getHisto("reco",file,"Jet_btag_b"));
  histos_btag_rad.push_back(getHisto("reco",file,"Jet_btag_c"));
  histos_btag_rad.push_back(getHisto("reco",file,"Jet_btag_uds"));

  Compare_3HistosStack("btag",histos_btag_rad,leg,"b-tag likelihood", "entries / normalized per flavour");

  //ctag
  std::vector<TH1F *> histos_ctag_rad;
  histos_ctag_rad.push_back(getHisto("reco",file,"Jet_ctag_b"));
  histos_ctag_rad.push_back(getHisto("reco",file,"Jet_ctag_c"));
  histos_ctag_rad.push_back(getHisto("reco",file,"Jet_ctag_uds"));

  Compare_3HistosStack("ctag",histos_ctag_rad,leg,"c-tag likelihood", "entries / normalized per flavour");
  
  
}
