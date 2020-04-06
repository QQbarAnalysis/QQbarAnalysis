#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int test_selection(TString pol, TString kt, int type){

  TString s_type=TString::Format("cuts%i_",type);
  
  TString file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_WW_250GeV_DBD_"+pol+"_260fb_"+kt+".root";//BBbar_20180911_7637.root";

  cout<< " "<<endl;
  cout<< " ######################################################################### "<<endl;
  cout<<" --------------------  btag1= 0.9, btag2=0.2   ---------------------------- "<<endl;
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss4(file);
  ss4.process=s_type+"bkg_"+kt+"_WW";
  ss4.SelectionBKG(-1,type,pol);

  file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_ZZ_250GeV_DBD_"+pol+"_260fb_"+kt+".root";//BBbar_20180911_7637.root";
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss6(file);
  ss6.process=s_type+"bkg_"+kt+"_ZZ";
  ss6.SelectionBKG(-1,type,pol);
  
  file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_HZ_250GeV_DBD_"+pol+"_1000fb_"+kt+".root";//BBbar_20180911_7637.root";
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss2(file);
  cout<<" --------------------  btag1= 0.9, btag2=0.2   ---------------------------- "<<endl;
  ss2.process=s_type+"bkg_"+kt+"_HZ";
  ss2.SelectionBKG(-1,type,pol);
  
  
  file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_250GeV_DBD_"+pol+"_260fb_"+kt+".root";//BBbar_20180911_7637.root";
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss3(file);
  cout<<" --------------------  btag1= 0.9, btag2=0.2   ---------------------------- "<<endl;
  ss3.process=s_type+"bbbar_"+kt;
  ss3.Selection(-1,type,pol);
  
  gSystem->Exit(0);

  return 0;
}
