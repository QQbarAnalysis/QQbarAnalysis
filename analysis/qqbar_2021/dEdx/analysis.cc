#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(TString file, TString output, bool ignoreoverlay, bool angularcorrection){

  cout<< " "<<endl;
  cout<< file << endl;
  observable ss3(file);
  ss3.dEdx(-1,output,true,ignoreoverlay,angularcorrection);
  ss3.dEdx(-1,output,false,ignoreoverlay,angularcorrection);
  
  gSystem->Exit(0);

  return 0;
}
