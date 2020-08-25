#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(TString file, float btag1=0.8, float btag2=0.8, bool inclusive=true){

  cout<<" --------------------  btag1="<<btag1<<", btag2="<<btag2<<"  ---------------------------- "<<endl;
  cout<< " "<<endl;
  cout<< file << endl;
    
  observable ss_0(file);
  ss_0.btag1=btag1;
  ss_0.btag2=btag2;
  ss_0.AnalysisR3(-1,inclusive);
  ss_0.AnalysisR3_cambridge(-1,inclusive);
  
  /*  if(inclusive!=false) {
    ss_0.Efficiencies(-1);
    ss_0.AnalysisY23(-1);
    ss_0.AnalysisR3_y23(-1);
    }*/
  

 
  
  gSystem->Exit(0);

  return 0;
}
