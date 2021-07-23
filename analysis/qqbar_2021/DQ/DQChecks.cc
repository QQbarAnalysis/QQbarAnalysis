#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"
#include "TApplication.h"
#include "TSystem.h"

//int analysis(TString file, float btag1=0.8, float btag2=0.8, bool inclusive=true){

int DQChecks(TString file="/mnt/HardDrive/cernbox_hd/QQbar/processor_output_2021/15161_eLpR.root",TString output="test",float KISR=35){ 
  //processor_output_2020/bbbar15161_radret_250GeV_mc2020_eL_genkt_R1.25_cambridge.root",float KISR=35){
  //bbbar_radret_250GeV_DBD_eL_genkt_R1.25_cambridge_norestorer.root",float KISR=35){

	     //"/home/airqui/nextcloud_cernbox/QQbar/processor_output_2020/15162_000.root", float KISR=35){
  std::cout << "" << std::endl;
  std::cout << "Input : " << file << std::endl;
  
  QQbarAnalysisClass obs(file);
  // obs.selection_hypothesis=option;
  obs.DQChecks(-1,KISR,output);
  gSystem -> Exit(0);

  return 0;
}

/*void analysis(){

  for(int option=1; option<2; option++) {

    cout<<" **************************************** "<<endl;
    cout<<"  OPTION " << option<<endl;
    cout<<" ****************            LEFT          **************- "<<endl;
    ana("/home/airqui/nextcloud_cernbox/QQbar/processor_output/bbbar_250GeV_DBD_eL_genkt_R1.25_cambridge.root",0.8,0.8,50,option);
    // cout<<" ****************            RIGHT          **************- "<<endl;
    //ana("/home/airqui/nextcloud_cernbox/QQbar/processor_output/bbbar_250GeV_DBD_eR_genkt_R1.25_cambridge.root",0.8,0.8,50,option);

  }
  

  }*/
