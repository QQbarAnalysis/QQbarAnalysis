#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int test_angular(TString pol ="eL", TString kt="l5"){
  
  TString file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_500GeV_IDR_"+kt+"_"+pol+".root";

  cout<< " ######################################################################### "<<endl;
  cout<< file << endl;
  observable ss0(file);
  ss0.btag1=0.9;
  ss0.btag2=0.2;
  ss0.process="bbbar_500GeV_"+pol+"_"+kt;
  ss0.AngularDistributions(-1,pol);

  gSystem->Exit(0);

  return 1;
}

