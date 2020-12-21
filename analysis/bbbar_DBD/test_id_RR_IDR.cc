#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int test_id_RR_IDR(TString pol, int type, float Kv, float btag1, float btag2){

  TString s_type=TString::Format("cuts%i_",type);

  TString file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_500GeV_IDR_l5_valencia2.0_may2020_eL.root";
  
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss3(file);
  ss3.process=s_type+"bbbar_IDR500GeV"+TString::Format("_Kgamma%i",int(Kv));
  ss3.btag1=btag1;
  ss3.btag2=btag2;
  ss3.IdentifyRR(-1,type,pol,Kv);
  
  gSystem->Exit(0);

  return 0;
}
