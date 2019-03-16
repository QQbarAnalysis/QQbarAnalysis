#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(TString pol="eL",TString kt="l5", int cuts=4){
  TString file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_500GeV_IDR_"+kt+"_"+pol+".root";//BBbar_20180911_7637.root";
  
  cout<< " ######################################################################### "<<endl; 
  cout<< "  #### "<<pol<<" POLARISATION "<<endl;
  cout<<" --------------------  btag1= 0.9, btag2=0.2   ---------------------------- "<<endl;
  cout<< " "<<endl;
  cout<< file << endl;
    
  observable ss_0(file);
  ss_0.process=TString::Format("bbbar_%s_cuts%i",kt.Data(),cuts);
  ss_0.Analysis(-1,pol,20,cuts);


  gSystem->Exit(0);
  return 0;
}
