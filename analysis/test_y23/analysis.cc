#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(TString file, float btag1=0.8, float btag2=0.8){

  cout<<" --------------------  btag1="<<btag1<<", btag2="<<btag2<<"  ---------------------------- "<<endl;
  cout<< " "<<endl;
  cout<< file << endl;
    
  observable ss_0(file);
  ss_0.btag1=btag1;
  ss_0.btag2=btag2;
  ss_0.AnalysisY23(-1);
  
  gSystem->Exit(0);

  return 0;
}
