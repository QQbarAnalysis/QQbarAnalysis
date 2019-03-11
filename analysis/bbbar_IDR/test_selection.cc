#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int test_selection(TString pol, TString kt, int type){

  TString s_type=TString::Format("cuts%i_",type);
  
  TString file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_500GeV_IDR_"+kt+"_"+pol+".root";
  
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss3(file);
  cout<<" --------------------  btag1= 0.9, btag2=0.2   ---------------------------- "<<endl;
  ss3.process=s_type+"bbbar_"+kt;
  ss3.Selection(-1,type,pol);
  
  gSystem->Exit(0);

  return 0;
}
