#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(TString pol="eL",TString kt="genkt_norestorer", int cuts=6, float Kv=35, float btag1=0.8, float btag2=0.8){
  TString file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_250GeV_DBD_"+pol+"_260fb_"+kt+".root";//BBbar_20180911_7637.root";

  if(kt=="radret_genkt_R125") file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_250GeV_DBD_"+pol+"_"+kt+".root ";
  else {
    file = "/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_250GeV_DBD_eL_266fb_genkt_restorer.root";
    if(pol=="eR") file="/home/irles/WorkArea/BBbar_tests/ntuples/bbbar_250GeV_DBD_eR_277fb_genkt_restorer.root";
  }
  
  
  cout<< " ######################################################################### "<<endl; 
  cout<< "  #### "<<pol<<" POLARISATION "<<endl;
  cout<<" --------------------  btag1="<<btag1<<", btag2="<<btag2<<"  ---------------------------- "<<endl;
  //  cout<< " "<<endl;
  //cout<< file << endl;

  
  observable ss_0(file);
  ss_0.process=TString::Format("bbbar_Kgamma%i_%s_cuts%i",int(Kv),kt.Data(),cuts);
  ss_0.btag1=btag1;
  ss_0.btag2=btag2;
  ss_0.Analysis(-1,pol,40,cuts,Kv);

  gSystem->Exit(0);
  
  if(kt != "genkt_restorer") {
    gSystem->Exit(0);
    return 0;
  }
  
  file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_WW_250GeV_DBD_"+pol+"_250fb_"+kt+".root";
  if(pol=="eL") file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_WW_250GeV_DBD_"+pol+"_72fb_"+ kt+".root";
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss_4(file);
  ss_4.process=TString::Format("bkg_Kgamma%i_WW_%s_cuts%i",int(Kv),kt.Data(),cuts);
  ss_4.btag1=btag1;
  ss_4.btag2=btag2;
  ss_4.AnalysisBKG(-1,pol,40,cuts,Kv);


   file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_ZZ_250GeV_DBD_"+pol+"_250fb_"+kt+".root";
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss_6(file);
  ss_6.process=TString::Format("bkg_Kgamma%i_ZZ_%s_cuts%i",int(Kv),kt.Data(),cuts);
  ss_6.btag1=btag1;
  ss_6.btag2=btag2;
  ss_6.AnalysisBKG(-1,pol,40,cuts,Kv);

  if(pol=="eL") file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_HZ_250GeV_DBD_"+pol+"_353fb_"+kt+".root";
  if(pol=="eR") file = "/home/irles/WorkArea/BBbar_tests/ntuples/bkg_HZ_250GeV_DBD_"+pol+"_550fb_"+kt+".root";
  cout<< " "<<endl;
  cout<< file << endl;
  observable ss_8(file);
  ss_8.process=TString::Format("bkg_Kgamma%i_HZ_%s_cuts%i",int(Kv),kt.Data(),cuts);
  ss_8.btag1=btag1;
  ss_8.btag2=btag2;
  ss_8.AnalysisBKG(-1,pol,40,cuts,Kv);
  

  
  gSystem->Exit(0);

  return 0;
}
