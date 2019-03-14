#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int test_angular(TString pol ="eL"){
  
  TString file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_250GeV_DBD_"+pol+"_260fb_genkt_restorer.root";//BBbar_20180911_7637.root";
  
  cout<< " ######################################################################### "<<endl;
  cout<< file << endl;
  observable ss0(file);
  ss0.btag1=0.9;
  ss0.btag2=0.2;
  ss0.process="bbbar_genkt_restorer";
  ss0.AngularDistributions(-1,pol);
  
  if(pol=="eR") gSystem->Exit(0);
  
  file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_250GeV_DBD_"+pol+"_260fb_genkt_norestorer.root";//BBbar_20180911_7637.root";
  
  cout<< " ######################################################################### "<<endl;
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss1(file);
  ss1.btag1=0.9;
  ss1.btag2=0.2;
  ss1.process="bbbar_genkt_norestorer";
  ss1.AngularDistributions(-1,pol);
  
  gSystem->Exit(0);

  return 1;
}

