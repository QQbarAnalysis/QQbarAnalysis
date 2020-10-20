#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"
#include "TSystem.h"

//int analysis(TString file, float btag1=0.8, float btag2=0.8, bool inclusive=true){
int analysis(TString file, float btag1=0.8, float btag2=0.8, float KISR=35){
  std::cout << "----------------- btag1= " << btag1 << ", btag2 = " << btag2 << " -------------------" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "Input : " << file << std::endl;
  
  observable ss_0(file);
  ss_0.btag1 = btag1;
  ss_0.btag2 = btag2;
  //ss_0.Efficiencies(-1);
  //ss_0.matching(-1);
  //ss_0.AnalysisY23(-1);
  //ss_0.AnalysisR3_y23(-1);
  ss_0.AnalysisR3_cambridge(-1,KISR);
  //ss_0.AnalysisR3_cambridge_contami(-1);

  gSystem -> Exit(0);

  return 0;
}
