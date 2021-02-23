#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(TString file, TString output){

  cout<< " "<<endl;
  cout<< file << endl;
  observable ss3(file);
  ss3.dEdx(-1,output,true);
  ss3.dEdx(-1,output,false);

  
  gSystem->Exit(0);

  return 0;
}
