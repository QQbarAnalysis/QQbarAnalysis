#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(TString pol="eL",TString kt="genkt_norestorer", int cuts=6){
  TString file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_250GeV_DBD_"+pol+"_260fb_"+kt+".root";//BBbar_20180911_7637.root";
  cout<< " ######################################################################### "<<endl; 
  cout<< "  #### "<<pol<<" POLARISATION "<<endl;
  cout<<" --------------------  btag1= 0.9, btag2=0.2   ---------------------------- "<<endl;
  cout<< " "<<endl;
  cout<< file << endl;
    
  observable ss_0(file);
  ss_0.process=TString::Format("bbbar_%s_cuts%i",kt.Data(),cuts);
  ss_0.Analysis(-1,pol,40,cuts);

  if(kt=="genkt_norestorer") gSystem->Exit(0);
  gSystem->Exit(0);
  
  file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_WW_250GeV_DBD_"+pol+"_260fb_"+kt+".root";//BBbar_20180911_7637.root";
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss_4(file);
  ss_4.process=TString::Format("bkg_WW_%s_cuts%i",kt.Data(),cuts);
  ss_4.AnalysisBKG(-1,pol,40,cuts);


  file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_ZZ_250GeV_DBD_"+pol+"_260fb_"+kt+".root";//BBbar_20180911_7637.root";
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss_6(file);
  ss_6.process=TString::Format("bkg_ZZ_%s_cuts%i",kt.Data(),cuts);
  ss_6.AnalysisBKG(-1,pol,40,cuts);

  file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_HZ_250GeV_DBD_"+pol+"_1000fb_"+kt+".root";//BBbar_20180911_7637.root";
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss_8(file);
  ss_8.process=TString::Format("bkg_HZ_%s_cuts%i",kt.Data(),cuts);
  ss_8.AnalysisBKG(-1,pol,40,cuts);
  
  
  gSystem->Exit(0);

  return 0;
}
