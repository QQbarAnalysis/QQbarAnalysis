#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(TString pol="eL",int n=100000){
  //, TString filename_out,TString filename_grid) {
   
  TString file = "/home/irles/WorkArea/BBbar_tests/ntuples/BBbar_20180911_7637.root";
  if(pol=="eR") file = "/home/irles/WorkArea/BBbar_tests/ntuples/BBbar_20180911_7638.root";

  // char** a;
  //TApplication *fooApp = new TApplication("fooApp",0,a);

  observable ss(file);
  ss.Analysis(n,true,pol);
  gSystem->Exit(0);
  // fooApp->Run();
  return 0;
}
