#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int test_selection_bkg(TString pol, TString kt, int type, float Kv, float btag1, float btag2){

  TString s_type=TString::Format("cuts%i_",type);

  TString file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_WW_250GeV_DBD_"+pol+"_250fb_"+kt+".root";
  if(pol=="eL") file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_WW_250GeV_DBD_"+pol+"_72fb_"+ kt+".root";

  cout<< " "<<endl;
  cout<< " ######################################################################### "<<endl;
  cout<<" --------------------  btag1= "<<btag1<<" btag2="<<btag2<<"  ---------------------------- "<<endl;
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss4(file);
  ss4.process=s_type+"bkg_"+kt+TString::Format("_Kgamma%i",int(Kv))+"_WW";
  ss4.btag1=btag1;
  ss4.btag2=btag2;
  ss4.SelectionBKG(-1,type,pol,Kv);

  file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_ZZ_250GeV_DBD_"+pol+"_250fb_"+kt+".root";
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss6(file);
  ss6.process=s_type+"bkg_"+kt+TString::Format("_Kgamma%i",int(Kv))+"_ZZ";
  ss6.btag1=btag1;
  ss6.btag2=btag2;
  ss6.SelectionBKG(-1,type,pol,Kv);
  
  if(pol=="eL") file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_HZ_250GeV_DBD_"+pol+"_353fb_"+kt+".root";
  if(pol=="eR") file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_HZ_250GeV_DBD_"+pol+"_550fb_"+kt+".root";
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss2(file);
  ss2.process=s_type+"bkg_"+kt+TString::Format("_Kgamma%i",int(Kv))+"_HZ";
  ss2.btag1=btag1;
  ss2.btag2=btag2;
  ss2.SelectionBKG(-1,type,pol,Kv);
  
 
  gSystem->Exit(0);

  return 0;
}
