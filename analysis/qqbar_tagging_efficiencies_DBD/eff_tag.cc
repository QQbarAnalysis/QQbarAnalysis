#include "TROOT.h"
#include "TFile.h"
#include "effstudies.cc"
#include "TApplication.h"

int eff_tag(TString pol="eL"){


  TString kt="radret_genkt_R125";
  TString file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_250GeV_DBD_"+pol+"_"+kt+".root ";

  effstudies ss_0(file);
  ss_0.process=TString::Format("bbbar_%s_%s_test",kt.Data(),pol.Data()); 
  //  ss_0.eff_flavour(10000,pol);
  //int n_entries=-1, TString pol="eL", int quark=5, int rad=0
  ss_0.QuarkTaggingTests(-1,pol);

  //  gSystem->Exit(0);
  return 0;
}
