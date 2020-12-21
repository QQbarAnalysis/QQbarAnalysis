#include "TROOT.h"
#include "TFile.h"
#include "effstudies.cc"
#include "TApplication.h"

int analysis_rho(TString pol="eR",TString kt="genkt_restorer", int nbins_=40, int quark=5, int rad=0,float btag1=0.8, float btag2=0.8){

  TString file ="";

  if(kt=="radret_genkt_R125") file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_250GeV_DBD_"+pol+"_"+kt+".root ";
  else {
    file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_250GeV_DBD_eL_266fb_genkt_restorer.root";
    if(pol=="eR") file="/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_250GeV_DBD_eR_277fb_genkt_restorer.root";
  }
  
  cout<< " ######################################################################### "<<endl; 
  cout<< "  #### "<<pol<<" POLARISATION "<<endl;
  cout<< " "<<endl;
  cout<< file << endl;
    
  effstudies ss_0(file);
  ss_0.nbins=nbins_;
  ss_0.btag1=btag1;
  ss_0.btag2=btag2;
  ss_0.Analysis_rho_charge(-1,pol,quark,rad);
  //  ss_0.Analysis_rho_ctag(-1,pol,quark,rad);
  //  ss_0.Analysis_rho_btag(-1,pol,quark,rad);
  
  
  gSystem->Exit(0);

  return 0;
}
