#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int AFBb(TString pol="eL"){

  TString kt="radret_genkt_R125";
  TString file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_250GeV_DBD_"+pol+"_"+kt+".root ";
  
  cout<< " ######################################################################### "<<endl; 
  cout<< "  #### "<<pol<<" POLARISATION "<<endl;
  cout<< " "<<endl;
  cout<< file << endl;
    
  observable ss_0(file);
  ss_0.process=TString::Format("bbbar_radret_%s",kt.Data());
  ss_0.AFBb_parton(-1,pol);
  
  gSystem->Exit(0);

  return 0;
}
