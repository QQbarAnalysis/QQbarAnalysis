#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis_rad(TString pol="eL",TString kt="genkt_norestorer", int cuts=6, float Kv=35, float btag1=0.8, float btag2=0.8){
  
  TString file = "/home/irles/ownCloudCNRS/HeavyFlavours/QQbarAnalysis_forked/analysis/kaontagging/"+pol+"_"+kt+".root";
  cout<< " ######################################################################### "<<endl;
  cout<< "  #### "<<pol<<" POLARISATION "<<endl;
  cout<<" --------------------  btag1="<<btag1<<", btag2="<<btag2<<"  ---------------------------- "<<endl;
  cout<< " "<<endl;
  cout<< file << endl;
  
  observable ss_0(file);
  ss_0.process=TString::Format("bbbar_Kgamma%i_%s_cuts%i",int(Kv),kt.Data(),cuts);
  ss_0.btag1=btag1;
  ss_0.btag2=btag2;
  ss_0.Analysis(-1,pol,40,cuts,Kv);

  gSystem->Exit(0);
  
    
  gSystem->Exit(0);

  return 0;
}
