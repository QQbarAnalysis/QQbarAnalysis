#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(TString file, TString output, bool ignoreoverlay, bool angularcorrection){

  cout<< " "<<endl;
  cout<< file << endl;
  TString folder="/mnt/HardDrive/cernbox_hd/QQbar/processor_output_2021/";
  file=folder+file;
  observable ss3(file);
  ss3.dEdx(-1,output,true,ignoreoverlay,angularcorrection);
  ss3.dEdx(-1,output,false,ignoreoverlay,angularcorrection);
  
  gSystem->Exit(0);

  return 0;
}
