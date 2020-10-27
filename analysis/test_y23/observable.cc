/////////////////////////
// 2020.Aug            //
// Seidai Tairafune    //
/////////////////////////

#define observable_cxx
#include "observable.h"
#include "TPad.h"
#include <TTree.h>
#include <TBranch.h>

void observable::ContaminationQuarkSelectionBKG(int n_entries) {
  
  std::cout << "########## ContaminationLightQuarkSelection ##########" << std::endl;
  int Nbbj[4][10]={0};
  int Nbb[4][10]={0};


 
  Long64_t nentries;
  if(n_entries>0) nentries = n_entries;
  else nentries = fChain->GetEntriesFast();
  Long64_t nbytes=0, nb=0;
  
  //Event loop
  for(Long64_t jentry=0; jentry<nentries; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if(ientry<0) break;
    nb = fChain->GetEntry(jentry); 
    nbytes += nb;
    if (jentry>100000 && jentry%100000==0) std::cout << "Progress: " << 100.*jentry/nentries << "%" << std::endl;

    float ISR_E = mc_ISR_E[0]+mc_ISR_E[1];
    /*    float costheta;
    std::vector<float> p_bbar;
    p_bbar.push_back(jet_px[0]-jet_px[1]);
    p_bbar.push_back(jet_py[0]-jet_py[1]);
    p_bbar.push_back(jet_pz[0]-jet_pz[1]);
    costheta=fabs(GetCostheta(p_bbar));
    */
    for(int i=0; i<10; i++) {
      for(int j=0; j<4; j++) {
	if(  PreSelection(j,(i+1.0)*5.) ==true) {
	  if(ISR_E<(i+1.0)*5.) {
	    Nbb[j][i]++;
	    if(njets_ycut_cambridge[10]==3)  Nbbj[j][i]++;
	  }
	}
      }
    }
  }
  

  for(int j=0; j<4; j++) {
    cout<<"STEP : "<<j<<endl;
    for(int i=0; i<10; i++) {
      cout<<"ISR_E="<<(i+1.0)*5.<<" N: "<<Nbb[j][i]<<" N3j: "<<Nbbj[j][i]<<endl;  
    }
  }

}
  

void observable::ContaminationLightQuarkSelection(int n_entries) {
  
  std::cout << "########## ContaminationLightQuarkSelection ##########" << std::endl;
  int Nbbj[4][10]={0};
  int Nbb[4][10]={0};
  int Nccj[4][10]={0};
  int Ncc[4][10]={0};
  int Nllj[4][10]={0};
  int Nll[4][10]={0};
  int Nbbj_rad[4][10]={0};
  int Nbb_rad[4][10]={0};
  int Nccj_rad[4][10]={0};
  int Ncc_rad[4][10]={0};
  int Nllj_rad[4][10]={0};
  int Nll_rad[4][10]={0};

 
  Long64_t nentries;
  if(n_entries>0) nentries = n_entries;
  else nentries = fChain->GetEntriesFast();
  Long64_t nbytes=0, nb=0;
  
  //Event loop
  for(Long64_t jentry=0; jentry<nentries; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if(ientry<0) break;
    nb = fChain->GetEntry(jentry); 
    nbytes += nb;
    if (jentry>100000 && jentry%100000==0) std::cout << "Progress: " << 100.*jentry/nentries << "%" << std::endl;

    float ISR_E = mc_ISR_E[0]+mc_ISR_E[1];
    /*    float costheta;
    std::vector<float> p_bbar;
    p_bbar.push_back(jet_px[0]-jet_px[1]);
    p_bbar.push_back(jet_py[0]-jet_py[1]);
    p_bbar.push_back(jet_pz[0]-jet_pz[1]);
    costheta=fabs(GetCostheta(p_bbar));
    */
    for(int i=0; i<10; i++) {
      for(int j=0; j<4; j++) {
	if(  PreSelection(j,(i+1.0)*5.) ==true) {
	  if(ISR_E<(i+1.0)*5.) {
	    if(fabs(mc_quark_pdg[0])==5) Nbb[j][i]++;
	    if(fabs(mc_quark_pdg[0])==4) Ncc[j][i]++;
	    if(fabs(mc_quark_pdg[0])<4) Nll[j][i]++;
	    
	    if(njets_ycut_cambridge[10]==3) {
	      if(fabs(mc_quark_pdg[0])==5) Nbbj[j][i]++;
	      if(fabs(mc_quark_pdg[0])==4) Nccj[j][i]++;
	      if(fabs(mc_quark_pdg[0])<4) Nllj[j][i]++;
	    }
	  } else {
	    if(fabs(mc_quark_pdg[0])==5) Nbb_rad[j][i]++;
	    if(fabs(mc_quark_pdg[0])==4) Ncc_rad[j][i]++;
	    if(fabs(mc_quark_pdg[0])<4) Nll_rad[j][i]++;
	    
	    if(njets_ycut_cambridge[10]==3) {
	      if(fabs(mc_quark_pdg[0])==5) Nbbj_rad[j][i]++;
	      if(fabs(mc_quark_pdg[0])==4) Nccj_rad[j][i]++;
	      if(fabs(mc_quark_pdg[0])<4) Nllj_rad[j][i]++;
	    }
	    
	  }
	}
      }
    }
  }

  for(int j=0; j<4; j++) {
    cout<<"STEP : "<<j<<endl;
    for(int i=0; i<10; i++) {
    cout<<"ISR_E="<<(i+1.0)*5.<<" Nll: "<<Nll[j][i]<<" Nllj: "<<Nllj[j][i]<<" Ncc: "<<Ncc[j][i]<<" Nccj: "<<Nccj[j][i]<<" Nbb: "<<Nbb[j][i]<<" Nbbj: "<<Nbbj[j][i]<<" | radret  Nll: "<<Nll_rad[j][i]<<" Nllj: "<<Nllj_rad[j][i]<<" Ncc: "<<Ncc_rad[j][i]<<" Nccj: "<<Nccj_rad[j][i]<<" Nbb: "<<Nbb_rad[j][i]<<" Nbb: "<<Nbbj_rad[j][i]<<endl;  
  }
  cout<<" ---------------- "<<endl;
   for(int i=0; i<10; i++) {
     cout<<"ISR_E="<<(i+1.0)*5.<<" R3l_signal: "<<float(Nllj[j][i])/float(Nllj[j][i])<<
       " R3l_c_cont: "<<(float(Nllj[j][i])+float(Nccj[j][i]))/(float(Nll[j][i])+float(Ncc[j][i]))<<
       " R3l_b_cont: "<<(float(Nllj[j][i])+float(Nbbj[j][i]))/(float(Nll[j][i])+float(Nbb[j][i]))<<
       " R3l_cont: "<<(float(Nllj[j][i])+float(Nccj[j][i])+float(Nbbj[j][i]))/(float(Nll[j][i])+float(Nbb[j][i])+float(Ncc[j][i]))<<
       "  |  R3l_l_rad: "<<(float(Nllj[j][i])+float(Nllj_rad[j][i]))/(float(Nll[j][i])+float(Nll_rad[j][i]))<<
       " R3l_c_rad: "<<(float(Nllj[j][i])+float(Nccj_rad[j][i]))/(float(Nll[j][i])+float(Ncc_rad[j][i]))<<
       " R3l_b_rad: "<<(float(Nllj[j][i])+float(Nbbj_rad[j][i]))/(float(Nll[j][i])+float(Nbb_rad[j][i]))<<
       " R3l_rad: "<<(float(Nllj[j][i])+float(Nllj_rad[j][i])+float(Nccj_rad[j][i])+float(Nbbj_rad[j][i]))/(float(Nll[j][i])+float(Nll_rad[j][i])+float(Nbb_rad[j][i])+float(Ncc_rad[j][i])+float(Ncc_rad[j][i]))<<
       " || R3l_all: "<<(float(Nllj[j][i])+float(Nllj_rad[j][i])+float(Nccj[j][i])+float(Nbbj[j][i])+float(Nccj_rad[j][i])+float(Nbbj_rad[j][i]))/(float(Nll[j][i])+float(Nll_rad[j][i])+float(Nbb[j][i])+float(Ncc[j][i])+float(Nbb_rad[j][i])+float(Ncc_rad[j][i]))<<endl;
   }
  }

}
	
void observable::ContaminationBQuarkSelection(int n_entries) {
  
  std::cout << "########## ContaminationBQuarkSelection ##########" << std::endl;
  int Nbbj[4][10]={0};
  int Nbb[4][10]={0};
  int Nccj[4][10]={0};
  int Ncc[4][10]={0};
  int Nllj[4][10]={0};
  int Nll[4][10]={0};
  int Nbbj_rad[4][10]={0};
  int Nbb_rad[4][10]={0};
  int Nccj_rad[4][10]={0};
  int Ncc_rad[4][10]={0};
  int Nllj_rad[4][10]={0};
  int Nll_rad[4][10]={0};

 
  Long64_t nentries;
  if(n_entries>0) nentries = n_entries;
  else nentries = fChain->GetEntriesFast();
  Long64_t nbytes=0, nb=0;
  
  //Event loop
  for(Long64_t jentry=0; jentry<nentries; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if(ientry<0) break;
    nb = fChain->GetEntry(jentry); 
    nbytes += nb;
    if (jentry>100000 && jentry%100000==0) std::cout << "Progress: " << 100.*jentry/nentries << "%" << std::endl;

    float ISR_E = mc_ISR_E[0]+mc_ISR_E[1];
    /*
    float costheta;
    std::vector<float> p_bbar;
    p_bbar.push_back(jet_px[0]-jet_px[1]);
    p_bbar.push_back(jet_py[0]-jet_py[1]);
    p_bbar.push_back(jet_pz[0]-jet_pz[1]);
    costheta=fabs(GetCostheta(p_bbar));
    */

    for(int i=0; i<10; i++) {
          for(int j=0; j<4; j++) {
	    if(  PreSelection(j,(i+1.0)*5.) ==true ) {
	      if(ISR_E<(i+1.0)*5.) {
		if(fabs(mc_quark_pdg[0])==5) Nbb[j][i]++;
		if(fabs(mc_quark_pdg[0])==4) Ncc[j][i]++;
		if(fabs(mc_quark_pdg[0])<4) Nll[j][i]++;
		
		if(njets_ycut_cambridge[10]==3) {
		  if(fabs(mc_quark_pdg[0])==5) Nbbj[j][i]++;
		  if(fabs(mc_quark_pdg[0])==4) Nccj[j][i]++;
		  if(fabs(mc_quark_pdg[0])<4) Nllj[j][i]++;
		}
	      } else {
		if(fabs(mc_quark_pdg[0])==5) Nbb_rad[j][i]++;
		if(fabs(mc_quark_pdg[0])==4) Ncc_rad[j][i]++;
		if(fabs(mc_quark_pdg[0])<4) Nll_rad[j][i]++;
		
		if(njets_ycut_cambridge[10]==3) {
		  if(fabs(mc_quark_pdg[0])==5) Nbbj_rad[j][i]++;
		  if(fabs(mc_quark_pdg[0])==4) Nccj_rad[j][i]++;
		  if(fabs(mc_quark_pdg[0])<4) Nllj_rad[j][i]++;
		}
		
	      }
	    }
	  }
    }
  }

  for(int j=0; j<4; j++) {
    cout<<" STEP: "<<j<<endl;
    for(int i=0; i<10; i++) {
      cout<<"ISR_E="<<(i+1.0)*5.<<" Nbb: "<<Nbb[j][i]<<" Nbbj: "<<Nbbj[j][i]<<" Ncc: "<<Ncc[j][i]<<" Nccj: "<<Nccj[j][i]<<" Nll: "<<Nll[j][i]<<" Nllj: "<<Nllj[j][i]<<" | radret  Nbb: "<<Nbb_rad[j][i]<<" Nbbj: "<<Nbbj_rad[j][i]<<" Ncc: "<<Ncc_rad[j][i]<<" Nccj: "<<Nccj_rad[j][i]<<" Nll: "<<Nll_rad[j][i]<<" Nll: "<<Nllj_rad[j][i]<<endl;  
    }
    cout<<" ---------------- "<<endl;
    for(int i=0; i<10; i++) {
      cout<<"ISR_E="<<(i+1.0)*5.<<" R3b_signal: "<<float(Nbbj[j][i])/(float(Nbb[j][i]))<<
	" R3b_c_cont: "<<(float(Nbbj[j][i])+float(Nccj[j][i]))/(float(Nbb[j][i])+float(Ncc[j][i]))<<
	" R3b_b_cont: "<<(float(Nbbj[j][i])+float(Nllj[j][i]))/(float(Nbb[j][i])+float(Nll[j][i]))<<
	" R3b_cont: "<<(float(Nbbj[j][i])+float(Nccj[j][i])+float(Nllj[j][i]))/(float(Nbb[j][i])+float(Nll[j][i])+float(Ncc[j][i])+float(Ncc[j][i]))<<
	"  |  R3b_l_rad: "<<(float(Nbbj[j][i])+float(Nbbj_rad[j][i]))/(float(Nbb[j][i])+float(Nbb_rad[j][i]))<<
	" R3b_c_rad: "<<(float(Nbbj[j][i])+float(Nccj_rad[j][i]))/(float(Nbb[j][i])+float(Ncc_rad[j][i]))<<
	" R3b_b_rad: "<<(float(Nbbj[j][i])+float(Nllj_rad[j][i]))/(float(Nbb[j][i])+float(Nll_rad[j][i]))<<
	" R3b_rad: "<<(float(Nbbj[j][i])+float(Nbbj_rad[j][i])+float(Nccj_rad[j][i])+float(Nllj_rad[j][i]))/(float(Nbb[j][i])+float(Nbb_rad[j][i])+float(Nll_rad[j][i])+float(Ncc_rad[j][i])+float(Ncc_rad[j][i]))<<
	" || R3b_all: "<<(float(Nbbj[j][i])+float(Nbbj_rad[j][i])+float(Nccj[j][i])+float(Nllj[j][i])+float(Nccj_rad[j][i])+float(Nllj_rad[j][i]))/(float(Nbb[j][i])+float(Nbb_rad[j][i])+float(Nll[j][i])+float(Ncc[j][i])+float(Nll_rad[j][i])+float(Ncc_rad[j][i]))<<endl;
    }
  }

}
	

void observable::AnalysisR3_cambridge(int n_entries, float KISR) {
  std::cout << "########## AnalysisR3_cambridge() ##########" << std::endl;


  // Parton Shower Info
  double R3b_ps[4][50]={0};   //The Number of 3b-jets event @PS level
  double R3l_ps[4][50]={0};
  double Rall_b_ps[4]={0};    //The Number of All bbbar jets event @PS level
  double Rall_l_ps[4]={0};
  double eR3b_ps[4][50]={0};  //The error of upper fraction(b-jet ratio) @PS level
  double eR3l_ps[4][50]={0};
  double R3bl_ps[4][50]={0};   //Observable @PS level
  double eR3bl_ps[4][50]={0};  //The error of observable @PS level

  // Hadron Level Info
  double R3b_hadron[4][50]={0};   //The Number of 3b-jets event @HADRON level
  double R3l_hadron[4][50]={0};
  double Rall_b_hadron[4]={0};    //The Number of All bbbar jets event @HADRON level
  double Rall_l_hadron[4]={0};
  double eR3b_hadron[4][50]={0};  //The error of upper fraction(b-jet ratio) @HADRON level
  double eR3l_hadron[4][50]={0};
  double R3bl_hadron[4][50]={0};   //Observable @HADRON level
  double eR3bl_hadron[4][50]={0};  //The error of observable @HADRON level

  
  // Reco Level (stable particles) Info
  // ONLY FOR SIGNAL !! (pdg and EISR selection)
  double R3b_reco[4][50]={0};   //The Number of 3b-jets event @RECO level
  double R3l_reco[4][50]={0};
  double Rall_b_reco[4]={0};    //The Number of All bbbar jets event @RECO level
  double Rall_l_reco[4]={0};
  double eR3b_reco[4][50]={0};  //The error of upper fraction(b-jet ratio) @RECO level
  double eR3l_reco[4][50]={0};
  double R3bl_reco[4][50]={0};   //Observable @RECO level
  double eR3bl_reco[4][50]={0};  //The error of observable @RECO level
  
  // Reco Level  Info
  // only for pdg selection but ignoring Rad Return Bkg
  double R3b_reco2[4][50]={0};   //The Number of 3b-jets event @RECO level
  double R3l_reco2[4][50]={0};
  double Rall_b_reco2[4]={0};    //The Number of All bbbar jets event @RECO level
  double Rall_l_reco2[4]={0};
  double eR3b_reco2[4][50]={0};  //The error of upper fraction(b-jet ratio) @RECO level
  double eR3l_reco2[4][50]={0};
  double R3bl_reco2[4][50]={0};   //Observable @RECO level
  double eR3bl_reco2[4][50]={0};  //The error of observable @RECO level

  // Reco Level Info
  // including mistagging and Rad Return bkg (i.e. no pdg selection, no EISR selection)
  double R3b_reco3[4][50]={0};   //The Number of 3b-jets event @RECO level
  double R3l_reco3[4][50]={0};
  double Rall_b_reco3[4]={0};    //The Number of All bbbar jets event @RECO level
  double Rall_l_reco3[4]={0};
  double eR3b_reco3[4][50]={0};  //The error of upper fraction(b-jet ratio) @RECO level
  double eR3l_reco3[4][50]={0};
  double R3bl_reco3[4][50]={0};   //Observable @RECO level
  double eR3bl_reco3[4][50]={0};  //The error of observable @RECO level
  

  double ycut_array[50]={0};//ycut values which is obtained from the Ntuple(Branch Name:ycut[50])
  double eycut_array[50]={0};

 

  TH2F* ycut_njet = new TH2F("ycut_njet", "ycut_njet; ycut; Number of Reconstructed jets", 50, 0, 0.05, 30, 0, 30);
  TH1F* h1_ycut = new TH1F("h1_ycut", "h1_ycut; ycut; Entries", 50, 0, 0.05);
  TH1F* h1_njet = new TH1F("h1_njet", "h1_njet; Number of Reconstructed jets; Entries", 30, 0, 30);
  

  Long64_t nentries;
  if(n_entries>0) nentries = n_entries;
  else nentries = fChain->GetEntriesFast();
  Long64_t nbytes=0, nb=0;
  std::cout << "Statistics : " << nentries << std::endl;
  
  //Event loop
  for(Long64_t jentry=0; jentry<nentries; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if(ientry<0) break;
    nb = fChain->GetEntry(jentry); 
    nbytes += nb;
    if (jentry>100000 && jentry%100000==0) std::cout << "Progress: " << 100.*jentry/nentries << "%" << std::endl;


    float costheta;
    std::vector<float> p_bbar;
    p_bbar.push_back(jet_px[0]-jet_px[1]);
    p_bbar.push_back(jet_py[0]-jet_py[1]);
    p_bbar.push_back(jet_pz[0]-jet_pz[1]);
    costheta=fabs(GetCostheta(p_bbar));
    


    if(ycut_array[10]==0) {
      for(int iycut=0; iycut<50; iycut++) {
        ycut_array[iycut]=ycut[iycut];
      }
    }

 //-----------------------------------------------------------------------------------------
    //No PDG choice, No Ev cut
    //count as Nbb(includes contamination from mistagging and from radiative return)
    //count as Nll(includes contamination from mistagging and from radiative return)
    Rall_b_reco3[0]++;
    Rall_l_reco3[0]++;

    if(PreSelection(1,KISR)==true) {
      Rall_b_reco3[1]++;
      Rall_l_reco3[1]++;
    }
    if(PreSelection(2,KISR)==true) Rall_b_reco3[2]++;
    if(PreSelection(2,KISR)==true && costheta<0.8) Rall_b_reco3[3]++;

    if(PreSelection(3,KISR)==true) Rall_l_reco3[2]++; 
    if(PreSelection(3,KISR)==true && costheta<0.8) Rall_l_reco3[3]++;


    //count as Nbbj or Nllj
    for(int iycut=0; iycut<50; iycut++) {
      bool njets_condition = false; //default is false
      //If the jet number on the ycut is 3, count the event.
      if(njets_ycut_cambridge[iycut]==3) njets_condition = true;
      if(njets_condition==true) {
        R3b_reco3[0][iycut]++;
        R3l_reco3[0][iycut]++;
        if(PreSelection(1,KISR)==true) {
          R3b_reco3[1][iycut]++;
          R3l_reco3[1][iycut]++;
        }
        if(PreSelection(2,KISR)==true) R3b_reco3[2][iycut]++;
        //if(PreSelection(2,KISR)==true && costheta_reco3<0.8) R3b_reco3[3][iycut]++;
        if(PreSelection(2,KISR)==true && costheta<0.8) R3b_reco3[3][iycut]++;
        if(PreSelection(3,KISR)==true) R3l_reco3[2][iycut]++;
        //if(PreSelection(3,KISR)==true && costheta_reco3<0.8) R3l_reco3[3][iycut]++;
        if(PreSelection(3,KISR)==true && costheta<0.8) R3l_reco3[3][iycut]++;
      }
    }//ycut loop

    
     float ISR_E = mc_ISR_E[0]+mc_ISR_E[1];
    if(ISR_E>KISR) continue; //Radiative return cut 

    
    //Extract bbbar event
    if(fabs(mc_quark_pdg[0])==5) {
      //--- Count the Number of bbbar event @STEP0
      Rall_b_ps[0]++;
      Rall_b_reco[0]++;
      Rall_b_hadron[0]++;
      //--- Count the Number of bbbar event @STEP1
      if(PreSelection(1,KISR)==true) {
        Rall_b_ps[1]++;
        Rall_b_reco[1]++;
        Rall_b_hadron[1]++;
      }
      //--- Count the Number of bbbar event @STEP2
      if(PreSelection(2,KISR)==true) {
        Rall_b_ps[2]++;
        Rall_b_reco[2]++;
        Rall_b_hadron[2]++;
      }
      //--- Count the Number of bbbar event @STEP2+costheta<0.8
      //if(PreSelection(2,KISR)==true && costheta_reco<0.8) {
      if(PreSelection(2,KISR)==true && costheta<0.8) {
        Rall_b_ps[3]++;
        Rall_b_reco[3]++;
        Rall_b_hadron[3]++;
      }

      for(int iycut=0; iycut<50; iycut++) {
        ycut_njet -> Fill(mc_quark_ps_ycut[iycut], mc_quark_ps_njets_ycut_cambridge[iycut]);
        h1_ycut -> Fill(mc_quark_ps_ycut[iycut]);
        h1_njet -> Fill(mc_quark_ps_njets_ycut_cambridge[iycut]);

        bool njets_condition = false;//default is false
        //Extract 3-jet events
        if(mc_quark_ps_njets_ycut_cambridge[iycut]==3) njets_condition=true;
        //--- Count the Number of 3jet event at ycut[iycut] @PS level
        if(njets_condition==true) {
          R3b_ps[0][iycut]++;
          if(PreSelection(1,KISR)==true) R3b_ps[1][iycut]++;
          if(PreSelection(2,KISR)==true) R3b_ps[2][iycut]++;
          //if(PreSelection(2,KISR)==true && costheta_reco<0.8) R3b_ps[3][iycut]++;
          if(PreSelection(2,KISR)==true && costheta<0.8) R3b_ps[3][iycut]++;
        }


        njets_condition = false;
        if(njets_ycut_cambridge[iycut]==3) njets_condition=true;
        //--- Count the Number of 3jet event at ycut[iycut] @Reco level
        if(njets_condition==true) {
          R3b_reco[0][iycut]++;
          if(PreSelection(1,KISR)==true) R3b_reco[1][iycut]++;
          if(PreSelection(2,KISR)==true) R3b_reco[2][iycut]++;
          //if(PreSelection(2,KISR)==true && costheta_reco<0.8) R3b_reco[3][iycut]++;
          if(PreSelection(2,KISR)==true && costheta<0.8) R3b_reco[3][iycut]++;
        }
        /*if(mc_quark_ps_ycut[iycut]<0.01) {
          R3b_reco[0][iycut]++;
          if(PreSelection(1,KISR)==true) R3b_reco[1][iycut]++;
          if(PreSelection(2,KISR)==true) R3b_reco[2][iycut]++;
          if(PreSelection(2,KISR)==true && costheta<0.8) R3b_reco[3][iycut]++;
        }*/


        njets_condition = false;
        if(mc_hadron_njets_ycut_cambridge[iycut]==3) njets_condition=true;
        if(njets_condition==true) {
          R3b_hadron[0][iycut]++;
          if(PreSelection(1,KISR)==true) R3b_hadron[1][iycut]++;
          if(PreSelection(2,KISR)==true) R3b_hadron[2][iycut]++;
          //if(PreSelection(2,KISR)==true && costheta_reco<0.8) R3b_hadron[3][iycut]++;
          if(PreSelection(2,KISR)==true && costheta<0.8) R3b_hadron[3][iycut]++;
        }
        /*if(mc_quark_ps_ycut[iycut]<0.01) {
          R3b_hadron[0][iycut]++;
          if(PreSelection(1,KISR)==true) R3b_hadron[1][iycut]++;
          if(PreSelection(2,KISR)==true) R3b_hadron[2][iycut]++;
          if(PreSelection(2,KISR)==true && costheta<0.8) R3b_hadron[3][iycut]++;
        }*/
      }//ycut loop
    }//bottom if


    //Extract llbar event
    if(fabs(mc_quark_pdg[0])<4) {
      //--- Count the Number of llbar event @STEP0
      Rall_l_ps[0]++;
      Rall_l_reco[0]++;
      Rall_l_hadron[0]++;
      //--- Count the Number of llbar event @STEP1
      if(PreSelection(1,KISR)==true) {
        Rall_l_ps[1]++;
        Rall_l_reco[1]++;
        Rall_l_hadron[1]++;
      }
      //--- Count the Number of llbar event @STEP2
      if(PreSelection(3,KISR)==true) {
        Rall_l_ps[2]++;
        Rall_l_reco[2]++;
        Rall_l_hadron[2]++;
      }
      //--- Count the Number of llbar event @STEP2+costheta<0.8
      //if(PreSelection(3,KISR)==true && costheta_reco<0.8) {
      if(PreSelection(3,KISR)==true && costheta<0.8) {
        Rall_l_ps[3]++;
        Rall_l_reco[3]++;
        Rall_l_hadron[3]++;
      }

      for(int iycut=0; iycut<50; iycut++) {
        bool njets_condition = false;//default is false

        if(mc_quark_ps_njets_ycut_cambridge[iycut]==3) njets_condition=true;
        //--- Count the Number of 3jet event at ycut[iycut] @PS level
        if(njets_condition==true) {
          R3l_ps[0][iycut]++;
          if(PreSelection(1,KISR)==true) R3l_ps[1][iycut]++;
          if(PreSelection(3,KISR)==true) R3l_ps[2][iycut]++;
          //if(PreSelection(3,KISR)==true && costheta_reco<0.8) R3l_ps[3][iycut]++;
          if(PreSelection(3,KISR)==true && costheta<0.8) R3l_ps[3][iycut]++;
        }

        njets_condition = false;
        if(njets_ycut_cambridge[iycut]==3) njets_condition=true;
        //--- Count the Number of 3jet event at ycut[iycut] @Reco level
        if(njets_condition==true) {
          R3l_reco[0][iycut]++;
          if(PreSelection(1,KISR)==true) R3l_reco[1][iycut]++;
          if(PreSelection(3,KISR)==true) R3l_reco[2][iycut]++;
          //if(PreSelection(3,KISR)==true && costheta_reco<0.8) R3l_reco[3][iycut]++;
          if(PreSelection(3,KISR)==true && costheta<0.8) R3l_reco[3][iycut]++;
        }


        njets_condition = false;
        if(mc_hadron_njets_ycut_cambridge[iycut]==3) njets_condition=true;
        if(njets_condition==true) {
          R3l_hadron[0][iycut]++;
          if(PreSelection(1,KISR)==true) R3l_hadron[1][iycut]++;
          if(PreSelection(3,KISR)==true) R3l_hadron[2][iycut]++;
          //if(PreSelection(3,KISR)==true && costheta_reco<0.8) R3l_hadron[3][iycut]++;
          if(PreSelection(3,KISR)==true && costheta<0.8) R3l_hadron[3][iycut]++;
        }
        /*if(mc_quark_ps_ycut[iycut]<0.01) {
          R3l_hadron[0][iycut]++;
          if(PreSelection(1,KISR)==true) R3l_hadron[1][iycut]++;
          if(PreSelection(3,KISR)==true) R3l_hadron[2][iycut]++;
          if(PreSelection(3,KISR)==true && costheta<0.8) R3l_hadron[3][iycut]++;
        }*/
      }//ycut loop
    }//uds if

 
    //-----------------------------------------------------------------------------------------
    //No PDG choice but we do remove the ISR contribution (with ISR<K)
    //count as Nbb(includes contamination from mistagging)
    //count as Nll(includes contamination from mistagging)
    //   if(ISR_E>KISR) continue; //Radiative return cut
    
    Rall_b_reco2[0]++;
    Rall_l_reco2[0]++;

    if(PreSelection(1,KISR)==true) {
      Rall_b_reco2[1]++;
      Rall_l_reco2[1]++;
    }
    if(PreSelection(2,KISR)==true) Rall_b_reco2[2]++;
    if(PreSelection(2,KISR)==true && costheta<0.8) Rall_b_reco2[3]++;

    if(PreSelection(3,KISR)==true) Rall_l_reco2[2]++; 
    if(PreSelection(3,KISR)==true && costheta<0.8) Rall_l_reco2[3]++;


    //count as Nbbj or Nllj
    for(int iycut=0; iycut<50; iycut++) {
      bool njets_condition = false; //default is false
      //If the jet number on the ycut is 3, count the event.
      if(njets_ycut_cambridge[iycut]==3) njets_condition = true;
      if(njets_condition==true) {
        R3b_reco2[0][iycut]++;
        R3l_reco2[0][iycut]++;
        if(PreSelection(1,KISR)==true) {
          R3b_reco2[1][iycut]++;
          R3l_reco2[1][iycut]++;
        }
        if(PreSelection(2,KISR)==true) R3b_reco2[2][iycut]++;
        if(PreSelection(2,KISR)==true && costheta<0.8) R3b_reco2[3][iycut]++;
        if(PreSelection(3,KISR)==true) R3l_reco2[2][iycut]++;
        if(PreSelection(3,KISR)==true && costheta<0.8) R3l_reco2[3][iycut]++;
      }
    }//ycut loop

    
  }//event loop

  /// Only signal
  // -----------------------------------------------------------------------------------------------
  //=== Calculate Observables R3b & R3l
  for(int istep=0; istep<4; istep++) {
    for(int jycut=0; jycut<50; jycut++) {
    //PS ------------------------------------------------
      //Calculate R3b and its error @PS level
      if(Rall_b_ps[istep]>0 && R3b_ps[istep][jycut]>0) {
        //R3b = (3b-jet Numbers)/(all b-jet Numbers)
        eR3b_ps[istep][jycut] = (R3b_ps[istep][jycut]/Rall_b_ps[istep])*sqrt(1./R3b_ps[istep][jycut]+1./Rall_b_ps[istep]);
        R3b_ps[istep][jycut] = (R3b_ps[istep][jycut]/Rall_b_ps[istep]);
      }
      else {
        eR3b_ps[istep][jycut]=0;
        R3b_ps[istep][jycut]=0.;
      }
      //Calculate R3l and its error @PS level
      if(Rall_l_ps[istep]>0 && R3l_ps[istep][jycut]>0) {
        //R3l = (3l-jet Numbers)/(all l-jet Numbers)
        eR3l_ps[istep][jycut] = (R3l_ps[istep][jycut]/Rall_l_ps[istep])*sqrt(1./R3l_ps[istep][jycut]+1./Rall_l_ps[istep]);
        R3l_ps[istep][jycut] = (R3l_ps[istep][jycut]/Rall_l_ps[istep]);
      }
      else {
        eR3l_ps[istep][jycut]=0;
        R3l_ps[istep][jycut]=0.;
      }
      //HADRON ------------------------------------------------
      //Calculate R3b and its error @HADRON level
      if(Rall_b_hadron[istep]>0 && R3b_hadron[istep][jycut]>0) {
        //R3b = (3b-jet Numbers)/(all b-jet Numbers)
        eR3b_hadron[istep][jycut] = (R3b_hadron[istep][jycut]/Rall_b_hadron[istep])*sqrt(1./R3b_hadron[istep][jycut]+1./Rall_b_hadron[istep]);
        R3b_hadron[istep][jycut] = (R3b_hadron[istep][jycut]/Rall_b_hadron[istep]);
      }
      else {
        eR3b_hadron[istep][jycut]=0;
        R3b_hadron[istep][jycut]=0.;
      }
      //Calculate R3l and its error @HADRON level
      if(Rall_l_hadron[istep]>0 && R3l_hadron[istep][jycut]>0) {
        //R3l = (3l-jet Numbers)/(all l-jet Numbers)
        eR3l_hadron[istep][jycut] = (R3l_hadron[istep][jycut]/Rall_l_hadron[istep])*sqrt(1./R3l_hadron[istep][jycut]+1./Rall_l_hadron[istep]);
        R3l_hadron[istep][jycut] = (R3l_hadron[istep][jycut]/Rall_l_hadron[istep]);
      }
      else {
        eR3l_hadron[istep][jycut]=0;
        R3l_hadron[istep][jycut]=0.;
      }
      //RECO ------------------------------------------------
      //Calculate R3b and its error @RECO level
      if(Rall_b_reco[istep]>0 && R3b_reco[istep][jycut]>0) {
        //R3b = (3b-jet Numbers)/(all b-jet Numbers)
        eR3b_reco[istep][jycut] = (R3b_reco[istep][jycut]/Rall_b_reco[istep])*sqrt(1./R3b_reco[istep][jycut]+1./Rall_b_reco[istep]);
        R3b_reco[istep][jycut] = (R3b_reco[istep][jycut]/Rall_b_reco[istep]);
      }
      else {
        eR3b_reco[istep][jycut]=0;
        R3b_reco[istep][jycut]=0.;
      }
      //Calculate R3l and its error @RECO level
      if(Rall_l_reco[istep]>0 && R3l_reco[istep][jycut]>0) {
        //R3l = (3l-jet Numbers)/(all l-jet Numbers)
        eR3l_reco[istep][jycut] = (R3l_reco[istep][jycut]/Rall_l_reco[istep])*sqrt(1./R3l_reco[istep][jycut]+1./Rall_l_reco[istep]);
        R3l_reco[istep][jycut] = (R3l_reco[istep][jycut]/Rall_l_reco[istep]);
      }
      else {
        eR3l_reco[istep][jycut]=0;
        R3l_reco[istep][jycut]=0.;
      }

      
    }
  }

  //=== Calculate the Observable R3bl
  //Initialize
  for(int i=0; i<4; i++) {
      for(int j=0; j<50; j++) {
        R3bl_ps[i][j]=0;
        R3bl_reco[i][j]=0;
        R3bl_hadron[i][j]=0;
        eR3bl_ps[i][j]=0;
        eR3bl_reco[i][j]=0;
        eR3bl_hadron[i][j]=0;
      }
  }

  for(int istep=0; istep<4; istep++) {
      for (int jycut=0; jycut<50; jycut++) {
	//ps ---------------------------------------
	//Observable R3bl @PS level
	if(R3b_ps[istep][jycut]>0 && R3l_ps[istep][jycut]>0) {
	  eR3bl_ps[istep][jycut]=(R3b_ps[istep][jycut]/R3l_ps[istep][jycut])*sqrt(pow(eR3b_ps[istep][jycut]/R3b_ps[istep][jycut],2)+pow(eR3l_ps[istep][jycut]/R3l_ps[istep][jycut],2));
	  R3bl_ps[istep][jycut]=(R3b_ps[istep][jycut]/R3l_ps[istep][jycut]);
	}
	else {
	  eR3bl_ps[istep][jycut]=0;
	  R3bl_ps[istep][jycut]=0;
	}
	//hadron ---------------------------------------
	//Observable R3bl @HADRON level
	if(R3b_hadron[istep][jycut]>0 && R3l_hadron[istep][jycut]>0) {
	  eR3bl_hadron[istep][jycut]=(R3b_hadron[istep][jycut]/R3l_hadron[istep][jycut])*sqrt(pow(eR3b_hadron[istep][jycut]/R3b_hadron[istep][jycut],2)+pow(eR3l_hadron[istep][jycut]/R3l_hadron[istep][jycut],2));
	  R3bl_hadron[istep][jycut]=(R3b_hadron[istep][jycut]/R3l_hadron[istep][jycut]);
	}
	else {
	  eR3bl_hadron[istep][jycut]=0;
	  R3bl_hadron[istep][jycut]=0;
	}
	//reco ---------------------------------------
	//Observable R3bl @RECO level
	if(R3b_reco[istep][jycut]>0 && R3l_reco[istep][jycut]>0) {
	  eR3bl_reco[istep][jycut]=(R3b_reco[istep][jycut]/R3l_reco[istep][jycut])*sqrt(pow(eR3b_reco[istep][jycut]/R3b_reco[istep][jycut],2)+pow(eR3l_reco[istep][jycut]/R3l_reco[istep][jycut],2));
	  R3bl_reco[istep][jycut]=(R3b_reco[istep][jycut]/R3l_reco[istep][jycut]);
	}
	else {
	  eR3bl_reco[istep][jycut]=0;
	  R3bl_reco[istep][jycut]=0;
	}

      }
  }


  //Writing the error of observables at each ycut values
  TFile* MyFile = new TFile("output_files/output_cambridge_merged_restorer_v02-01-02.root", "RECREATE");
  MyFile -> cd();

  TGraphErrors* graph_R3b_ps[4];
  TGraphErrors* graph_R3b_reco[4];
  TGraphErrors* graph_R3b_hadron[4];
  TGraphErrors* graph_R3l_ps[4];
  TGraphErrors* graph_R3l_reco[4];
  TGraphErrors* graph_R3l_hadron[4];
  TGraphErrors* graph_R3bl_ps[4];
  TGraphErrors* graph_R3bl_reco[4];
  TGraphErrors* graph_R3bl_hadron[4];

  for (int i=0; i<4; i++) {
    //TGraphErrors(Number of Point, x, y, error of x, error of y)
    graph_R3b_ps[i] = new TGraphErrors(50, ycut_array, R3b_ps[i], eycut_array, eR3b_ps[i]);
    graph_R3b_reco[i] = new TGraphErrors(50, ycut_array, R3b_reco[i], eycut_array, eR3b_reco[i]);
    graph_R3b_hadron[i] = new TGraphErrors(50, ycut_array, R3b_hadron[i], eycut_array, eR3b_hadron[i]);
    graph_R3l_ps[i] = new TGraphErrors(50, ycut_array, R3l_ps[i], eycut_array, eR3l_ps[i]);
    graph_R3l_reco[i] = new TGraphErrors(50, ycut_array, R3l_reco[i], eycut_array, eR3l_reco[i]);
    graph_R3l_hadron[i] = new TGraphErrors(50, ycut_array, R3l_hadron[i], eycut_array, eR3l_hadron[i]);
    graph_R3bl_ps[i] = new TGraphErrors(50, ycut_array, R3bl_ps[i], eycut_array, eR3bl_ps[i]);
    graph_R3bl_reco[i] = new TGraphErrors(50, ycut_array, R3bl_reco[i], eycut_array, eR3bl_reco[i]);
    graph_R3bl_hadron[i] = new TGraphErrors(50, ycut_array, R3bl_hadron[i], eycut_array, eR3bl_hadron[i]);

    graph_R3b_ps[i] -> SetName(TString::Format("R3b_PS_STEP%i", i));
    graph_R3b_reco[i] -> SetName(TString::Format("R3b_Reco_STEP%i", i));
    graph_R3b_hadron[i] -> SetName(TString::Format("R3b_Hadron_STEP%i", i));
    graph_R3l_ps[i] -> SetName(TString::Format("R3l_PS_STEP%i", i));
    graph_R3l_reco[i] -> SetName(TString::Format("R3l_Reco_STEP%i", i));
    graph_R3l_hadron[i] -> SetName(TString::Format("R3l_Hadron_STEP%i", i));
    graph_R3bl_ps[i] -> SetName(TString::Format("R3bl_PS_STEP%i", i));
    graph_R3bl_reco[i] -> SetName(TString::Format("R3bl_Reco_STEP%i", i));
    graph_R3bl_hadron[i] -> SetName(TString::Format("R3bl_Hadron_STEP%i", i));

    graph_R3b_ps[i] -> Write();
    graph_R3b_reco[i] -> Write();
    graph_R3b_hadron[i] -> Write();
    graph_R3l_ps[i] -> Write();
    graph_R3l_reco[i] -> Write();
    graph_R3l_hadron[i] -> Write();
    graph_R3bl_ps[i] -> Write();
    graph_R3bl_reco[i] -> Write();
    graph_R3bl_hadron[i] -> Write();
  }
  h1_ycut -> Write();
  h1_njet -> Write();
  ycut_njet -> Write();
  std::cout << "COMPLETE : output_files/output_cambridge_merged_restorer_v02-01-02.root" << std::endl;


  // --------------------------------------------
  // Reco but with contamination from mistagging and/or Rad Return
 /// Only signal
  // -----------------------------------------------------------------------------------------------
  //=== Calculate Observables R3b & R3l
  for(int istep=0; istep<4; istep++) {
    for(int jycut=0; jycut<50; jycut++) {
    //RECO2 ------------------------------------------------
      //Calculate R3b and its error @RECO2 level
      if(Rall_b_reco2[istep]>0 && R3b_reco2[istep][jycut]>0) {
        //R3b = (3b-jet Numbers)/(all b-jet Numbers)
        eR3b_reco2[istep][jycut] = (R3b_reco2[istep][jycut]/Rall_b_reco2[istep])*sqrt(1./R3b_reco2[istep][jycut]+1./Rall_b_reco2[istep]);
        R3b_reco2[istep][jycut] = (R3b_reco2[istep][jycut]/Rall_b_reco2[istep]);
      }
      else {
        eR3b_reco2[istep][jycut]=0;
        R3b_reco2[istep][jycut]=0.;
      }
      //Calculate R3l and its error @RECO2 level
      if(Rall_l_reco2[istep]>0 && R3l_reco2[istep][jycut]>0) {
        //R3l = (3l-jet Numbers)/(all l-jet Numbers)
        eR3l_reco2[istep][jycut] = (R3l_reco2[istep][jycut]/Rall_l_reco2[istep])*sqrt(1./R3l_reco2[istep][jycut]+1./Rall_l_reco2[istep]);
        R3l_reco2[istep][jycut] = (R3l_reco2[istep][jycut]/Rall_l_reco2[istep]);
      }
      else {
        eR3l_reco2[istep][jycut]=0;
        R3l_reco2[istep][jycut]=0.;
      }
      //RECO3 ------------------------------------------------
      //Calculate R3b and its error @RECO3 level
      if(Rall_b_reco3[istep]>0 && R3b_reco3[istep][jycut]>0) {
        //R3b = (3b-jet Numbers)/(all b-jet Numbers)
        eR3b_reco3[istep][jycut] = (R3b_reco3[istep][jycut]/Rall_b_reco3[istep])*sqrt(1./R3b_reco3[istep][jycut]+1./Rall_b_reco3[istep]);
        R3b_reco3[istep][jycut] = (R3b_reco3[istep][jycut]/Rall_b_reco3[istep]);
      }
      else {
        eR3b_reco3[istep][jycut]=0;
        R3b_reco3[istep][jycut]=0.;
      }
      //Calculate R3l and its error @RECO3 level
      if(Rall_l_reco3[istep]>0 && R3l_reco3[istep][jycut]>0) {
        //R3l = (3l-jet Numbers)/(all l-jet Numbers)
        eR3l_reco3[istep][jycut] = (R3l_reco3[istep][jycut]/Rall_l_reco3[istep])*sqrt(1./R3l_reco3[istep][jycut]+1./Rall_l_reco3[istep]);
        R3l_reco3[istep][jycut] = (R3l_reco3[istep][jycut]/Rall_l_reco3[istep]);
      }
      else {
        eR3l_reco3[istep][jycut]=0;
        R3l_reco3[istep][jycut]=0.;
      }

      
    }
  }

  //=== Calculate the Observable R3bl
  //Initialize
  for(int i=0; i<4; i++) {
      for(int j=0; j<50; j++) {
        R3bl_reco2[i][j]=0;
        R3bl_reco3[i][j]=0;
        eR3bl_reco2[i][j]=0;
        eR3bl_reco3[i][j]=0;
      }
  }

  for(int istep=0; istep<4; istep++) {
      for (int jycut=0; jycut<50; jycut++) {
	//reco2 ---------------------------------------
	//Observable R3bl @RECO2 level
	if(R3b_reco2[istep][jycut]>0 && R3l_reco2[istep][jycut]>0) {
	  eR3bl_reco2[istep][jycut]=(R3b_reco2[istep][jycut]/R3l_reco2[istep][jycut])*sqrt(pow(eR3b_reco2[istep][jycut]/R3b_reco2[istep][jycut],2)+pow(eR3l_reco2[istep][jycut]/R3l_reco2[istep][jycut],2));
	  R3bl_reco2[istep][jycut]=(R3b_reco2[istep][jycut]/R3l_reco2[istep][jycut]);
	}
	else {
	  eR3bl_reco2[istep][jycut]=0;
	  R3bl_reco2[istep][jycut]=0;
	}

	//reco3 ---------------------------------------
	//Observable R3bl @RECO3 level
	if(R3b_reco3[istep][jycut]>0 && R3l_reco3[istep][jycut]>0) {
	  eR3bl_reco3[istep][jycut]=(R3b_reco3[istep][jycut]/R3l_reco3[istep][jycut])*sqrt(pow(eR3b_reco3[istep][jycut]/R3b_reco3[istep][jycut],2)+pow(eR3l_reco3[istep][jycut]/R3l_reco3[istep][jycut],2));
	  R3bl_reco3[istep][jycut]=(R3b_reco3[istep][jycut]/R3l_reco3[istep][jycut]);
	}
	else {
	  eR3bl_reco3[istep][jycut]=0;
	  R3bl_reco3[istep][jycut]=0;
	}

      }
  }
  
  
    TFile* MyFile2 = new TFile("output_files/output_cambridge_merged_restorer_contami_v02-01-02.root", "RECREATE");
  MyFile2 -> cd();

  TGraphErrors* g_R3b_reco2[4];
  TGraphErrors* g_R3l_reco2[4];
  TGraphErrors* g_R3bl_reco2[4];

  for(int i=0; i<4; i++) {
    g_R3b_reco2[i] = new TGraphErrors(50, ycut_array, R3b_reco2[i], eycut_array, eR3b_reco2[i]);
    g_R3l_reco2[i] = new TGraphErrors(50, ycut_array, R3l_reco2[i], eycut_array, eR3l_reco2[i]);
    g_R3bl_reco2[i] = new TGraphErrors(50, ycut_array, R3bl_reco2[i], eycut_array, eR3bl_reco2[i]);

    g_R3b_reco2[i] -> SetName(TString::Format("R3b_Reco2_STEP%i",i));
    g_R3l_reco2[i] -> SetName(TString::Format("R3l_Reco2_STEP%i",i));
    g_R3bl_reco2[i] -> SetName(TString::Format("R3bl_Reco2_STEP%i",i));

    g_R3b_reco2[i] -> Write();
    g_R3l_reco2[i] -> Write();
    g_R3bl_reco2[i] -> Write();
  }

  TGraphErrors* g_R3b_reco3[4];
  TGraphErrors* g_R3l_reco3[4];
  TGraphErrors* g_R3bl_reco3[4];

  for(int i=0; i<4; i++) {
    g_R3b_reco3[i] = new TGraphErrors(50, ycut_array, R3b_reco3[i], eycut_array, eR3b_reco3[i]);
    g_R3l_reco3[i] = new TGraphErrors(50, ycut_array, R3l_reco3[i], eycut_array, eR3l_reco3[i]);
    g_R3bl_reco3[i] = new TGraphErrors(50, ycut_array, R3bl_reco3[i], eycut_array, eR3bl_reco3[i]);

    g_R3b_reco3[i] -> SetName(TString::Format("R3b_Reco3_STEP%i",i));
    g_R3l_reco3[i] -> SetName(TString::Format("R3l_Reco3_STEP%i",i));
    g_R3bl_reco3[i] -> SetName(TString::Format("R3bl_Reco3_STEP%i",i));

    g_R3b_reco3[i] -> Write();
    g_R3l_reco3[i] -> Write();
    g_R3bl_reco3[i] -> Write();
  }
    std::cout << "OUTPUT : output_files/output_cambridge_merged_restorer_contami_v02-01-02.root" << std::endl;

}//AnalysisR3_cambridge()




void observable::AnalysisR3_y23(int n_entries, float KISR) {
  std::cout << "########## AnalysisR3_y23() ##########" << std::endl;
  double R3b_ps[4]; //The index indicates each STEPs
  double R3l_ps[4];
  double Rall_b_ps[4];
  double Rall_l_ps[4];
  double R3b_reco[4]; 
  double R3l_reco[4];
  double Rall_b_reco[4];
  double Rall_l_reco[4];
  //Initialize
  for(int i=0; i<4; i++) {
    Rall_b_ps[i]=0;
    Rall_l_ps[i]=0;
    Rall_b_reco[i]=0;
    Rall_l_reco[i]=0;
    R3b_ps[i]=0;
    R3l_ps[i]=0;
    R3b_reco[i]=0;
    R3l_reco[i]=0;
  }

  TH1F* hist_isr_cut[4];
  TH1F* hist_Kv_cut[4];
  TH1F* hist_residual_cut[4];
  for(int i=0; i<4; i++) {
    hist_isr_cut[i] = new TH1F(TString::Format("hist_isr_cut_%i", i), TString::Format("hist_isr_cut_%i", i), 100, 0, 250);
    hist_Kv_cut[i] = new TH1F(TString::Format("hist_Kv_cut_%i", i), TString::Format("hist_Kv_cut_%i", i), 100, 0, 250);
    hist_residual_cut[i] = new TH1F(TString::Format("hist_residual_cut_%i", i), TString::Format("hist_residual_cut_%i", i), 100, 0, 250);
  }

  
  Long64_t nentries;
  if(n_entries>0) nentries = n_entries;
  else nentries = fChain->GetEntriesFast();
  Long64_t nbytes=0, nb=0;

  //Event loop
  for(Long64_t jentry=0; jentry<nentries; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if(ientry<0) break;
    nb = fChain->GetEntry(jentry); 
    nbytes += nb;
    if (jentry>100000 && jentry%100000==0) std::cout << "Progress: " << 100.*jentry/nentries << "%" << std::endl;

    float ISR_E = mc_ISR_E[0]+mc_ISR_E[1];
    if(ISR_E>KISR) continue;  

    std::vector<float> pjet1;
    pjet1.push_back(jet_px[0]);
    pjet1.push_back(jet_py[0]);
    pjet1.push_back(jet_pz[0]);
    float costheta_reco0 = fabs(GetCostheta(pjet1));
    //float costheta_reco = fabs(GetCostheta(pjet1)+GetCostheta(pjet2))/2.;
    float mag_pjet1 = sqrt(pjet1[0]*pjet1[0]+pjet1[1]*pjet1[1]+pjet1[2]*pjet1[2]);
    std::vector<float> pjet2;
    pjet2.push_back(jet_px[1]);
    pjet2.push_back(jet_py[1]);
    pjet2.push_back(jet_pz[1]);
    float costheta_reco1 = fabs(GetCostheta(pjet2));
    float mag_pjet2 = sqrt(pjet2[0]*pjet2[0]+pjet2[1]*pjet2[1]+pjet2[2]*pjet2[2]);

    std::vector<float> cross;
    cross.push_back(pjet1[1]*pjet2[2]-pjet1[2]*pjet2[1]);
    cross.push_back(pjet1[2]*pjet2[0]-pjet1[0]*pjet2[2]);
    cross.push_back(pjet1[0]*pjet2[1]-pjet1[1]*pjet2[0]);
    float mag_cross = sqrt(cross[0]*cross[0]+cross[1]*cross[1]+cross[2]*cross[2]);
    float sinpsi_acol = mag_cross/(mag_pjet1*mag_pjet2);
    float Kv = 250.*sinpsi_acol/(sinpsi_acol+sqrt(1-costheta_reco0*costheta_reco0)+sqrt(1-costheta_reco1*costheta_reco1));

 
    float PFO_energy[2];
    if(jet_E[0]>0.8 || jet_E[1]>0.8) {
      for(int ijet=0; ijet<2; ijet++) {
        PFO_energy[ijet]=0;
        for(int ipfo=0; ipfo<100; ipfo++) {
          if(jet_pfo_E[ijet][ipfo]>0.1) {
            PFO_energy[ijet]+=jet_pfo_E[ijet][ipfo];
          }//PFO in each jet if
        }//PFO loop
      }//jet loop
    }//jet energy if
    

    //Extract bbbar signal
    if(fabs(mc_quark_pdg[0])==5) {
      Rall_b_ps[0]++;
      Rall_b_reco[0]++;

      /*hist_isr_cut[0]->Fill(ISR_E);
      hist_Kv_cut[0]->Fill(Kv);
      hist_residual_cut[0]->Fill(250.-(PFO_energy[0]+PFO_energy[1]));*/
      if(PreSelection(1,KISR)==true) {
        Rall_b_ps[1]++;
        Rall_b_reco[1]++;

        /*hist_isr_cut[1]->Fill(ISR_E);
        hist_Kv_cut[1]->Fill(Kv);
        hist_residual_cut[1]->Fill(250.-(PFO_energy[0]+PFO_energy[1]));*/
      }
      if(PreSelection(2,KISR)==true) {
        Rall_b_ps[2]++;
        Rall_b_reco[2]++;

        /*hist_isr_cut[2]->Fill(ISR_E);
        hist_Kv_cut[2]->Fill(Kv);
        hist_residual_cut[2]->Fill(250.-(PFO_energy[0]+PFO_energy[1]));*/
      }
      if(PreSelection(2,KISR)==true && costheta_reco0<0.8) {
        Rall_b_ps[3]++;
        Rall_b_reco[3]++;

        /*hist_isr_cut[3]->Fill(ISR_E);
        hist_Kv_cut[3]->Fill(Kv);
        hist_residual_cut[3]->Fill(250.-(PFO_energy[0]+PFO_energy[1]));*/
      }

      //Count jet events @PS level
      if(mc_quark_ps_y23*jet_R_norm>0.01) {
        R3b_ps[0]++;
        if(PreSelection(1,KISR)==true) R3b_ps[1]++;
        if(PreSelection(2,KISR)==true) R3b_ps[2]++;
        if(PreSelection(2,KISR)==true && costheta_reco0<0.8) R3b_ps[3]++;
      }
      //Count jet events @Reco level
      if(y23*jet_R_norm>0.01) {
        R3b_reco[0]++;
        if(PreSelection(1,KISR)==true) R3b_reco[1]++;
        if(PreSelection(2,KISR)==true) R3b_reco[2]++;
        if(PreSelection(2,KISR)==true && costheta_reco0<0.8) R3b_reco[3]++;
      }
    }//bottom if

    //Extract llbar signal
    if(fabs(mc_quark_pdg[0])<4) {
      Rall_l_ps[0]++;
      Rall_l_reco[0]++;

      hist_isr_cut[0]->Fill(ISR_E);
      hist_Kv_cut[0]->Fill(Kv);
      hist_residual_cut[0]->Fill(250.-(PFO_energy[0]+PFO_energy[1]));
      if(PreSelection(1,KISR)==true) {
        Rall_l_ps[1]++;
        Rall_l_reco[1]++;

        hist_isr_cut[1]->Fill(ISR_E);
        hist_Kv_cut[1]->Fill(Kv);
        hist_residual_cut[1]->Fill(250.-(PFO_energy[0]+PFO_energy[1]));
      }
      if(PreSelection(3,KISR)==true) {
        Rall_l_ps[2]++;
        Rall_l_reco[2]++;

        hist_isr_cut[2]->Fill(ISR_E);
        hist_Kv_cut[2]->Fill(Kv);
        hist_residual_cut[2]->Fill(250.-(PFO_energy[0]+PFO_energy[1]));
      }
      if(PreSelection(3,KISR)==true && costheta_reco0<0.8) {
        Rall_l_ps[3]++;
        Rall_l_reco[3]++;

        hist_isr_cut[3]->Fill(ISR_E);
        hist_Kv_cut[3]->Fill(Kv);
        hist_residual_cut[3]->Fill(250.-(PFO_energy[0]+PFO_energy[1]));
      }

      //Count jet events @PS level
      if(mc_quark_ps_y23*jet_R_norm>0.01) {
        R3l_ps[0]++;
        if(PreSelection(1,KISR)==true) R3l_ps[1]++;
        if(PreSelection(3,KISR)==true) R3l_ps[2]++;
        if(PreSelection(3,KISR)==true && costheta_reco0<0.8) R3l_ps[3]++;
      }
      //Count jet events @Reco level
      if(y23*jet_R_norm>0.01) {
        R3l_reco[0]++;
        if(PreSelection(1,KISR)==true) R3l_reco[1]++;
        if(PreSelection(3,KISR)==true) R3l_reco[2]++;
        if(PreSelection(3,KISR)==true && costheta_reco0<0.8) R3l_reco[3]++;
      }
    }//uds if
  }//event loop

  std::cout << "### ycut = 0.01" << std::endl;
  TFile* MyFile = new TFile("radiative_return_cut_ll.root", "RECREATE");
  MyFile->cd();
  //=== Calculaton
  for(int i=0; i<4; i++) {
    std::cout << "### Results for Selection STEP " << i << std::endl;
    std::cout << " 3b-jet Number @PS level = " << R3b_ps[i] << std::endl;
    std::cout << " all b-jet Number @PS level = " << Rall_b_ps[i] << std::endl;
    std::cout << " 3l-jet Number @PS level = " << R3l_ps[i] << std::endl;
    std::cout << " all l-jet Number @PS level = " << Rall_l_ps[i] << std::endl;
    std::cout << "PS level : R3b = " << R3b_ps[i]/Rall_b_ps[i] << " R3l = " << R3l_ps[i]/Rall_l_ps[i] << " ---> R3bl = " << (R3b_ps[i]/Rall_b_ps[i])/(R3l_ps[i]/Rall_l_ps[i]) << std::endl; 

    std::cout << " 3b-jet Number @Reco level = " << R3b_reco[i] << std::endl;
    std::cout << " all b-jet Number @Reco level = " << Rall_b_reco[i] << std::endl;
    std::cout << " 3l-jet Number @Reco level = " << R3l_reco[i] << std::endl;
    std::cout << " all l-jet Number @Reco level = " << Rall_l_reco[i] << std::endl;
    std::cout << "Reco level : R3b = " << R3b_reco[i]/Rall_b_reco[i] << " R3l = " << R3l_reco[i]/Rall_l_reco[i] << " ---> R3bl = " << (R3b_reco[i]/Rall_b_reco[i])/(R3l_reco[i]/Rall_l_reco[i]) << std::endl;
    std::cout << "" << std::endl;

    hist_isr_cut[i] -> Write();
    hist_Kv_cut[i] -> Write();
    hist_residual_cut[i] -> Write();
  }
  MyFile->Close();
}//AnalysisR3_y23()



//=== Calculate Efficiencies
void observable::Efficiencies(int n_entries) {
  std::cout << "########## Efficiencies() ###########" << std::endl;
  double n_signal[3]; //Count MC Truth
  //btagging : b-likelihood>0.8
  //c-tagging : c-likelihood>0.85
  //uds-tagging : b-likelihood<0.4 & c-likelihood<0.25
  double nbtag_selected[3]; //Count the Number the events which is tagged as b in qqbar events(q=udscb)
  double nctag_selected[3];
  double nudstag_selected[3];

  double nbtag=0;
  double nctag=0;
  double nudstag=0;
  double ndouble_signal[3];
  double ndouble_btag_selected[3];
  double ndouble_ctag_selected[3];
  double ndouble_udstag_selected[3];
  //Initialize
  for(int i=0; i<3; i++) {
    n_signal[i]=0;
    nbtag_selected[i]=0;
    nctag_selected[i]=0;
    nudstag_selected[i]=0;

    ndouble_signal[i]=0;
    ndouble_btag_selected[i]=0;
    ndouble_ctag_selected[i]=0;
    ndouble_udstag_selected[i]=0;
  }


  TH1F* btag_mc[3]; //i=0 : MC bottom, i=1 : MC charm, i=2 : MC uds
  for(int i=0; i<3; i++) {
    btag_mc[i] = new TH1F(TString::Format("btag_mc_%i", i), TString::Format("btag_mc_%i", i), 100, 0, 1);
  }

  TH1F* ctag_mc[3]; //i=0 : MC bottom, i=1 : MC charm, i=2 : MC uds
  for(int i=0; i<3; i++) {
    ctag_mc[i] = new TH1F(TString::Format("ctag_mc_%i", i), TString::Format("ctag_mc_%i", i), 100, 0, 1);
  }


  TH1F* bb_signal = new TH1F("bb_signal", "bb_signal", 20, 0, 1);
  TH1F* Eff_bb = new TH1F("Eff_bb", "Eff_bb", 20, 0, 1);

  TH1F* cc_signal = new TH1F("cc_signal", "cc_signal", 20, 0, 1);
  TH1F* Eff_cc = new TH1F("Eff_cc", "Eff_cc", 20, 0, 1);

  TH1F* ll_signal = new TH1F("ll_signal", "ll_signal", 20, 0, 1);
  TH1F* Eff_ll = new TH1F("Eff_ll", "Eff_ll", 20, 0, 1);


  Long64_t nentries;
  if(n_entries>0) nentries = n_entries;
  else nentries = fChain->GetEntriesFast();
  Long64_t nbytes=0, nb=0;

  //Event loop
  for(Long64_t jentry=0; jentry<nentries; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if(ientry<0) break;
    nb = fChain->GetEntry(jentry); 
    nbytes += nb;
    if (jentry>100000 && jentry%100000==0) std::cout << "Progress: " << 100.*jentry/nentries << "%" << std::endl;

    float ISR_E = mc_ISR_E[0]+mc_ISR_E[1];
    if(ISR_E>35) continue;
    //if(PreSelection(1,35)==false) continue;

    for(int ijet=0; ijet<2; ijet++) {
      //Extract bbbar signal
      if(fabs(mc_quark_pdg[ijet])==5) {
        n_signal[0]++;
        btag_mc[0] -> Fill(jet_btag[ijet]);
        ctag_mc[0] -> Fill(jet_ctag[ijet]);
        if(jet_btag[ijet]>0.8) nbtag_selected[0]++; //Tagged as b in bbbar event
        if(jet_ctag[ijet]>0.875) nctag_selected[0]++; //Miss-tagged as c in bbbar event
        if(jet_btag[ijet]<0.4 && jet_ctag[ijet]<0.25) nudstag_selected[0]++; //Miss-tagged as uds in bbbar event
      }//bottom if

      //Extract ccbar
      if(fabs(mc_quark_pdg[ijet])==4) {
        n_signal[1]++;
        btag_mc[1] -> Fill(jet_btag[ijet]);
        ctag_mc[1] -> Fill(jet_ctag[ijet]);
        if(jet_btag[ijet]>0.8) nbtag_selected[1]++; //Miss-tagged as b in ccbar event
        if(jet_ctag[ijet]>0.875) nctag_selected[1]++; //Tagged as c in ccbar event
        if(jet_btag[ijet]<0.4 && jet_ctag[ijet]<0.25) nudstag_selected[1]++; //Miss-tagged as uds in llbar event
      }//charm if

      //Extract llbar
      if(fabs(mc_quark_pdg[ijet])<4) {
        n_signal[2]++;
        btag_mc[2] -> Fill(jet_btag[ijet]);
        ctag_mc[2] -> Fill(jet_ctag[ijet]);
        if(jet_btag[ijet]>0.8) nbtag_selected[2]++; //Miss-tagged as b in llbar event
        if(jet_ctag[ijet]>0.875) nctag_selected[2]++; //Miss-tagged as c in llbar event
        if(jet_btag[ijet]<0.4 && jet_ctag[ijet]<0.25) nudstag_selected[2]++; //Tagged as uds in llbar event
      }//uds if
    }//jet loop


    //Double Jet-Tagging Efficiency
    if(jet_btag[0]>0.8 && jet_btag[1]>0.8) nbtag++;
    if(fabs(mc_quark_pdg[0])==5) {
      ndouble_signal[0]++; //Here, Count for only one side.
      //double b-tagged in MC b
      if(jet_btag[0]>0.8 && jet_btag[1]>0.8) ndouble_btag_selected[0]++;
      //double miss-c-tagged in MC b
      if(jet_ctag[0]>0.875 && jet_ctag[1]>0.875) ndouble_ctag_selected[0]++;
      //double miss-uds-tagged in MC b
      if(jet_btag[0]<0.4 && jet_ctag[0]<0.25 && jet_btag[1]<0.4 && jet_ctag[1]<0.25) ndouble_udstag_selected[0]++;


      std::vector<float> pjet1;
      pjet1.push_back(jet_px[0]);
      pjet1.push_back(jet_py[0]);
      pjet1.push_back(jet_pz[0]);
      std::vector<float> pjet2;
      pjet2.push_back(jet_px[1]);
      pjet2.push_back(jet_py[1]);
      pjet2.push_back(jet_pz[1]);
      //float costheta_reco = fabs(GetCostheta(pjet1)+GetCostheta(pjet2))/2.;
      float costheta_reco = fabs(GetCostheta(pjet1));
      float cosphi_reco = fabs(GetCosphi(pjet1));
      bb_signal -> Fill(cosphi_reco);
      if(PreSelection(3,35)==true) Eff_bb -> Fill(cosphi_reco); //Considering Double Jet-tagging eff?
    }//bottom if

    if(jet_ctag[0]>0.875 && jet_ctag[1]>0.875) nctag++;
    if(fabs(mc_quark_pdg[0])==4) {
      ndouble_signal[1]++;
      //double miss-b-tagged in MC c
      if(jet_btag[0]>0.8 && jet_btag[1]>0.8) ndouble_btag_selected[1]++;
      //double c-tagged in MC c
      if(jet_ctag[0]>0.875 && jet_ctag[1]>0.875) ndouble_ctag_selected[1]++;
      //double miss-uds-tagged in MC c
      if(jet_btag[0]<0.4 && jet_ctag[0]<0.25 && jet_btag[1]<0.4 && jet_ctag[1]<0.25) ndouble_udstag_selected[1]++;


      std::vector<float> pjet1;
      pjet1.push_back(jet_px[0]);
      pjet1.push_back(jet_py[0]);
      pjet1.push_back(jet_pz[0]);
      std::vector<float> pjet2;
      pjet2.push_back(jet_px[1]);
      pjet2.push_back(jet_py[1]);
      pjet2.push_back(jet_pz[1]);
      //float costheta_reco = fabs(GetCostheta(pjet1)+GetCostheta(pjet2))/2.;
      float costheta_reco = fabs(GetCostheta(pjet1));
      float cosphi_reco = fabs(GetCosphi(pjet1));
      cc_signal -> Fill(cosphi_reco);
      if(PreSelection(3,35)==true) Eff_cc -> Fill(cosphi_reco);
    }//charm if

    if(jet_btag[0]<0.4 && jet_ctag[0]<0.25 && jet_btag[1]<0.4 && jet_ctag[1]<0.25) nudstag++;
    if(fabs(mc_quark_pdg[0])<4) {
      ndouble_signal[2]++;
      //double miss-b-tagged in MC uds
      if(jet_btag[0]>0.8 && jet_btag[1]>0.8) ndouble_btag_selected[2]++;
      //double miss-c-tagged in MC uds
      if(jet_ctag[0]>0.875 && jet_ctag[1]>0.875) ndouble_ctag_selected[2]++;
      //double uds-tagged in MC uds
      if(jet_btag[0]<0.4 && jet_ctag[0]<0.25 && jet_btag[1]<0.4 && jet_ctag[1]<0.25) ndouble_udstag_selected[2]++;


      std::vector<float> pjet1;
      pjet1.push_back(jet_px[0]);
      pjet1.push_back(jet_py[0]);
      pjet1.push_back(jet_pz[0]);
      std::vector<float> pjet2;
      pjet2.push_back(jet_px[1]);
      pjet2.push_back(jet_py[1]);
      pjet2.push_back(jet_pz[1]);
      //float costheta_reco = fabs(GetCostheta(pjet1)+GetCostheta(pjet2))/2.;
      float costheta_reco = fabs(GetCostheta(pjet1));
      float cosphi_reco = fabs(GetCosphi(pjet1));
      ll_signal -> Fill(cosphi_reco);
      if(PreSelection(3,35)==true) Eff_ll -> Fill(cosphi_reco);
    }//uds if
  }//event loop


  //=== Calculation
  std::cout << "Results" << std::endl;
  std::cout << "-----------------------" << std::endl;
  std::cout << "### MC Truth" << std::endl;
  std::cout << "N b-jets(MC Truth) : " << n_signal[0] << ", N c-jets(MC Truth) : " << n_signal[1] << ", N uds-jets(MC Truth) : " << n_signal[2] << std::endl;
  std::cout << "" << std::endl;
  std::cout << "### b-tagging (b-likelihood>0.8)" << std::endl;
  std::cout << "N b-jets(tagged as b) : " << nbtag_selected[0] << ", N c-jets(miss-tagged as b) : " << nbtag_selected[1] << ", N uds-jets(miss-tagged as b) : " << nbtag_selected[2] << std::endl;
  std::cout << "### c-tagging (c-likelihood>0.875)" << std::endl;
  std::cout << "N b-jets(miss-tagged as c) : " << nctag_selected[0] << ", N c-jets(tagged as c) : " << nctag_selected[1] << ", N uds-jets(miss-tagged as c) : " << nctag_selected[2] << std::endl;
  std::cout << "### uds-tagging(b-likelihood<0.4 & c-likelihood<0.25)" << std::endl;
  std::cout << "N b-jets(miss-tagged as uds) : " << nudstag_selected[0] << ", N c-jets(miss-tagged as uds) : " << nudstag_selected[1] << ", N uds-jets(tagged as uds) : " << nudstag_selected[2] << std::endl;
  std::cout << "" << std::endl;
  std::cout << "### MC Truth" << std::endl;
  std::cout << "N b-jets(MC Truth) : " << ndouble_signal[0] << ", N c-jets(MC Truth) : " << ndouble_signal[1] << ", N uds-jets(MC Truth) : " << ndouble_signal[2] << std::endl;
  std::cout << "### double b-tagging" << std::endl;
  std::cout << "N b-jets(tagged as b) : " << ndouble_btag_selected[0] << ", N c-jets(miss-tagged as b) : " << ndouble_btag_selected[1] << ", N uds-jets(miss-tagged as b) : " << ndouble_btag_selected[2] << std::endl;
  std::cout << "### double c-tagging" << std::endl;
  std::cout << "N b-jets(miss-tagged as c) : " << ndouble_ctag_selected[0] << ", N c-jets(tagged as c) : " << ndouble_ctag_selected[1] << ", N uds-jets(miss-tagged as c) : " << ndouble_ctag_selected[2] << std::endl;
  std::cout << "### double uds-tagging" << std::endl;
  std::cout << "N b-jets(miss-tagged as uds) : " << ndouble_udstag_selected[0] << ", N c-jets(miss-tagged as uds) : " << ndouble_udstag_selected[1] << ", N uds-jets(tagged as uds) : " << ndouble_udstag_selected[2] << std::endl;
  std::cout << "" << std::endl;
  std::cout << "N b-tagged(NOT consider MC flavor) : " << nbtag << std::endl;
  std::cout << "N c-tagged(NOT consider MC flavor) : " << nctag << std::endl;
  std::cout << "N uds-tagged(NOT consider MC flavor) : " << nudstag << std::endl;


  TFile* MyFile = new TFile("Likelihood.root", "RECREATE");
  MyFile -> cd();
  for(int i=0; i<3; i++) {
    btag_mc[i] -> Write();
    ctag_mc[i] -> Write();
  }
  MyFile -> Close();

  TFile* MyFile2 = new TFile("Eff_vs_angle.root", "RECREATE");
  MyFile2 -> cd();
  Eff_bb -> Divide(bb_signal);
  Eff_bb -> Write();
  Eff_cc -> Divide(cc_signal);
  Eff_cc -> Write();
  Eff_ll -> Divide(ll_signal);
  Eff_ll -> Write();
  MyFile2 -> Close();
}//Efficiencies()



void observable::matching(int n_entries) {
  std::cout << "########## matching() ##########" << std::endl;

  TH1F* hist_method1[3];
  TH1F* hist_method2[3];
  TH2F* method1_anglereso[3]; //2D hist to examine the angular resolution of |costheta_parton-costheta_reco|
  TH2F* hist_back_parton[3]; //2D hist for back to back check @PS level
  TH2F* hist_back_reco[3]; //2D hist for back to back check @Reco level
  TH1F* back_parton0[2]; //1D hist for MC parton (corresponds to b)
  TH1F* back_parton1[2]; //1D hist for MC parton (corresponds to bbar)
  TH1F* back_reco0_1[2]; //1D hist for reco jet closer to b0-parton by method1
  TH1F* back_reco1_1[2]; //1D hist for reco jet closer to b1-parton by method1
  TH1F* back_reco0_2[2]; //1D hist for reco jet closer to b0-parton by method2
  TH1F* back_reco1_2[2]; //1D hist for reco jet closer to b1-parton by method2
  for(int i=0; i<3; i++) {
    hist_method1[i] = new TH1F(TString::Format("hist_method1_%i", i), TString::Format("hist_method1_%i", i), 100, 0, 1);
    hist_method2[i] = new TH1F(TString::Format("hist_method2_%i", i), TString::Format("hist_method2_%i", i), 100, 0, 1);
    method1_anglereso[i] = new TH2F(TString::Format("method1_anglereso_%i", i), TString::Format("method1_anglereso_%i", i), 20, -1, 1, 10, 0, 1);
    hist_back_parton[i] = new TH2F(TString::Format("hist_back_parton_%i", i), TString::Format("hist_back_parton_%i", i), 20, -1, 1, 20, -1, 1);
    hist_back_reco[i] = new TH2F(TString::Format("hist_back_reco_%i", i), TString::Format("hist_back_reco_%i", i), 20, -1, 1, 20, -1, 1);
  }
  for(int i=0; i<2; i++) {
    back_parton0[i] = new TH1F(TString::Format("back_parton0_%i", i), TString::Format("back_parton0_%i", i), 100, -1, 1);
    back_parton1[i] = new TH1F(TString::Format("back_parton1_%i", i), TString::Format("back_parton1_%i", i), 100, -1, 1);
    back_reco0_1[i] = new TH1F(TString::Format("back_reco0_1_%i", i), TString::Format("back_reco0_%i_1", i), 100, -1, 1);
    back_reco1_1[i] = new TH1F(TString::Format("back_reco1_1_%i", i), TString::Format("back_reco1_%i_1", i), 100, -1, 1);
    back_reco0_2[i] = new TH1F(TString::Format("back_reco0_2_%i", i), TString::Format("back_reco0_%i_2", i), 100, -1, 1);
    back_reco1_2[i] = new TH1F(TString::Format("back_reco1_2_%i", i), TString::Format("back_reco1_%i_2", i), 100, -1, 1);
  }
  

  Long64_t nentries;
  if(n_entries>0) nentries = n_entries;
  else nentries = fChain->GetEntriesFast();
  Long64_t nbytes=0, nb=0;

  //Event loop
  for(Long64_t jentry=0; jentry<nentries; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if(ientry<0) break;
    nb = fChain->GetEntry(jentry); 
    nbytes += nb;
    if (jentry>100000 && jentry%100000==0) std::cout << "Progress: " << 100.*jentry/nentries << "%" << std::endl;

    float ISR_E = mc_ISR_E[0]+mc_ISR_E[1];
    if(ISR_E>35) continue;
    if(fabs(mc_quark_pdg[0])==5) {
      //=== Method1 ===
      std::vector<float> pq1;
      pq1.push_back(mc_quark_px[0]);
      pq1.push_back(mc_quark_py[0]);
      pq1.push_back(mc_quark_pz[0]);
      std::vector<float> pq2;
      pq2.push_back(mc_quark_px[1]);
      pq2.push_back(mc_quark_py[1]);
      pq2.push_back(mc_quark_pz[1]);
      float costheta_parton0 = GetCostheta(pq1);
      float costheta_parton1 = GetCostheta(pq2);
      float theta_parton0 = std::acos(costheta_parton0);
      float theta_parton1 = std::acos(costheta_parton1);

      std::vector<float> pjet1;
      pjet1.push_back(jet_px[0]);
      pjet1.push_back(jet_py[0]);
      pjet1.push_back(jet_pz[0]);
      std::vector<float> pjet2;
      pjet2.push_back(jet_px[1]);
      pjet2.push_back(jet_py[1]);
      pjet2.push_back(jet_pz[1]);
      float costheta_reco0 = GetCostheta(pjet1);
      float costheta_reco1 = GetCostheta(pjet2);
      float theta_reco0 = std::acos(costheta_reco0);
      float theta_reco1 = std::acos(costheta_reco1);

      //For b0-parton
      //The Case pjet1 closer to pq1
      if(fabs(costheta_parton0-costheta_reco0)<fabs(costheta_parton0-costheta_reco1)) {
        float deltatheta = fabs(theta_parton0-theta_reco0);
        method1_anglereso[0] -> Fill(costheta_parton0, fabs(costheta_parton0-costheta_reco0));
        hist_method1[0] -> Fill(deltatheta);
        if(PreSelection(2,35)==true) {
          method1_anglereso[1] -> Fill(costheta_parton0, fabs(costheta_parton0-costheta_reco0));
          hist_method1[1] -> Fill(deltatheta);
        }
        if(PreSelection(2,35)==true && fabs(costheta_reco0)<0.8) {
          method1_anglereso[2] -> Fill(costheta_parton0, fabs(costheta_parton0-costheta_reco0));
          hist_method1[2] -> Fill(deltatheta);
        }
      }
      //The Case pjet2 closer to pq1
      if(fabs(costheta_parton0-costheta_reco1)<fabs(costheta_parton0-costheta_reco0)) {
        float deltatheta = fabs(theta_parton0-theta_reco1);
        method1_anglereso[0] -> Fill(costheta_parton0, fabs(costheta_parton0-costheta_reco1));
        hist_method1[0] -> Fill(deltatheta);
        if(PreSelection(2,35)==true) {
          method1_anglereso[1] -> Fill(costheta_parton0, fabs(costheta_parton0-costheta_reco1));
          hist_method1[1] -> Fill(deltatheta);
        }
        if(PreSelection(2,35)==true && fabs(costheta_reco1)<0.8) {
          method1_anglereso[2] -> Fill(costheta_parton0, fabs(costheta_parton0-costheta_reco1));
          hist_method1[2] -> Fill(deltatheta);
        }
      }
      //For b1-parton
      //The case pjet1 closer to pq2
      if(fabs(costheta_parton1-costheta_reco0)<fabs(costheta_parton1-costheta_reco1)) {
        float deltatheta = fabs(theta_parton1-theta_reco0);
        method1_anglereso[0] -> Fill(costheta_parton1, fabs(costheta_parton1-costheta_reco0));
        hist_method1[0] -> Fill(deltatheta);
        if(PreSelection(2,35)==true) {
          method1_anglereso[1] -> Fill(costheta_parton1, fabs(costheta_parton1-costheta_reco0));
          hist_method1[1] -> Fill(deltatheta);
        }
        if(PreSelection(2,35)==true && fabs(costheta_reco0)<0.8) {
          method1_anglereso[2] -> Fill(costheta_parton1, fabs(costheta_parton1-costheta_reco0));
          hist_method1[2] -> Fill(deltatheta);
        }
      }
      //The Case pjet2 closer to pq2
      if(fabs(costheta_parton1-costheta_reco1)<fabs(costheta_parton1-costheta_reco0)) {
        float deltatheta = fabs(theta_parton1-theta_reco1);
        method1_anglereso[0] -> Fill(costheta_parton1, fabs(costheta_parton1-costheta_reco1));
        hist_method1[0] -> Fill(deltatheta);
        if(PreSelection(2,35)==true) {
          method1_anglereso[1] -> Fill(costheta_parton1, fabs(costheta_parton1-costheta_reco1));
          hist_method1[1] -> Fill(deltatheta);
        }
        if(PreSelection(2,35)==true && fabs(costheta_reco1)<0.8) {
          method1_anglereso[2] -> Fill(costheta_parton1, fabs(costheta_parton1-costheta_reco1));
          hist_method1[2] -> Fill(deltatheta);
        }
      }


      //=== Method2 ===
      float mpq1 = sqrt(pq1[0]*pq1[0]+pq1[1]*pq1[1]+pq1[2]*pq1[2]);
      float mpq2 = sqrt(pq2[0]*pq2[0]+pq2[1]*pq2[1]+pq2[2]*pq2[2]);
      float mpjet1 = sqrt(pjet1[0]*pjet1[0]+pjet1[1]*pjet1[1]+pjet1[2]*pjet1[2]);
      float mpjet2 = sqrt(pjet2[0]*pjet2[0]+pjet2[1]*pjet2[1]+pjet2[2]*pjet2[2]);
      float costheta00 = (pq1[0]*pjet1[0]+pq1[1]*pjet1[1]+pq1[2]*pjet1[2])/(mpq1*mpjet1);
      float costheta01 = (pq1[0]*pjet2[0]+pq1[1]*pjet2[1]+pq1[2]*pjet2[2])/(mpq1*mpjet2);  
      float costheta10 = (pq2[0]*pjet1[0]+pq2[1]*pjet1[1]+pq2[2]*pjet1[2])/(mpq2*mpjet1);  
      float costheta11 = (pq2[0]*pjet2[0]+pq2[1]*pjet2[1]+pq2[2]*pjet2[2])/(mpq2*mpjet2);  

      float theta00 = std::acos(costheta00);
      float theta01 = std::acos(costheta01);
      float theta10 = std::acos(costheta10);
      float theta11 = std::acos(costheta11);

      //For b0-parton
      //The Case pjet1 closer to pq1
      if(theta00<theta01) {
        hist_method2[0] -> Fill(theta00);
        if(PreSelection(2,35)==true) hist_method2[1] -> Fill(theta00);
        if(PreSelection(2,35)==true && fabs(costheta_reco0)<0.8) hist_method2[2] -> Fill(theta00);
      }
      //The Case pjet2 closer to pq1
      if(theta01<theta00) {
        hist_method2[0] -> Fill(theta01);
        if(PreSelection(2,35)==true) hist_method2[1] -> Fill(theta01);
        if(PreSelection(2,35)==true && fabs(costheta_reco1)<0.8) hist_method2[2] -> Fill(theta01);
      }
      //The Case pjet1 closer to pq2
      if(theta10<theta11) {
        hist_method2[0] -> Fill(theta10);
        if(PreSelection(2,35)==true) hist_method2[1] -> Fill(theta10);
        if(PreSelection(2,35)==true && fabs(costheta_reco0)<0.8) hist_method2[2] -> Fill(theta10);
      }
      //The Case pjet2 closer to pq2
      if(theta11<theta10) {
        hist_method2[0] -> Fill(theta11);
        if(PreSelection(2,35)==true) hist_method2[1] -> Fill(theta11);
        if(PreSelection(2,35)==true && fabs(costheta_reco1)<0.8) hist_method2[2] -> Fill(theta11);
      }


      //Back to back check
      //2D check
      hist_back_parton[0] -> Fill(costheta_parton0, costheta_parton1);
      hist_back_reco[0] -> Fill(costheta_reco0, costheta_reco1);
      if(PreSelection(2,35)==true) {
        hist_back_parton[1] -> Fill(costheta_parton0, costheta_parton1);
        hist_back_reco[1] -> Fill(costheta_reco0, costheta_reco1);
      }
      if(PreSelection(2,35)==true && fabs(costheta_reco0)<0.8 && fabs(costheta_reco1)<0.8) {
        hist_back_parton[2] -> Fill(costheta_parton0, costheta_parton1);
        hist_back_reco[2] -> Fill(costheta_reco0, costheta_reco1);
      }

      //1D check
      back_parton0[0] -> Fill(costheta_parton0);
      back_parton1[0] -> Fill(costheta_parton1);
      if(PreSelection(2,35)==true) {
        back_parton0[1] -> Fill(costheta_parton0);
        back_parton1[1] -> Fill(costheta_parton1);
      }
      /*if(PreSelection(2,35)==true && fabs(costheta_reco0)<0.8 && fabs(costheta_reco1)<0.8) {
        back_parton0[2] -> Fill(costheta_parton0);
        back_parton1[2] -> Fill(costheta_parton1);
      }*/

      if(fabs(costheta_parton0-costheta_reco0)<fabs(costheta_parton0-costheta_reco1)) {
        back_reco0_1[0] -> Fill(costheta_reco0); //pjet1 close to pq1
        back_reco1_1[0] -> Fill(costheta_reco1); //pjet2 close to pq2
        if(PreSelection(2,35)==true) {
          back_reco0_1[1] -> Fill(costheta_reco0); //pjet1 close to pq1
          back_reco1_1[1] -> Fill(costheta_reco1); //pjet2 close to pq2
        }
        /*if(PreSelection(2,35)==true && fabs(costheta_reco0)<0.8) {
          back_reco0_1[2] -> Fill(costheta_reco0); //pjet1 close to pq1
          back_reco1_1[2] -> Fill(costheta_reco1); //pjet2 close to pq2
        }*/
      }
      if(fabs(costheta_parton0-costheta_reco1)<fabs(costheta_parton0-costheta_reco0)) {
        back_reco0_1[0] -> Fill(costheta_reco1); //pjet1 close to pq2
        back_reco1_1[0] -> Fill(costheta_reco0); //pjet2 close to pq1
        if(PreSelection(2,35)==true) {
          back_reco0_1[1] -> Fill(costheta_reco1); //pjet1 close to pq2
          back_reco1_1[1] -> Fill(costheta_reco0); //pjet2 close to pq1
        }
        /*if(PreSelection(2,35)==true && fabs(costheta_reco0)<0.8) {
          back_reco0_1[2] -> Fill(costheta_reco1); //pjet1 close to pq2
          back_reco1_1[2] -> Fill(costheta_reco0); //pjet2 close to pq1
        }*/
      }
      /*if(fabs(costheta_parton1-costheta_reco0)<fabs(costheta_parton1-costheta_reco1)) {
        //back_reco0_1[0] -> Fill(costheta_reco0); //pjet1 close to pq1
        back_reco1_1[0] -> Fill(costheta_reco0); //pjet2 close to pq2
        if(PreSelection(2,35)==true) {
          //back_reco0_1[1] -> Fill(costheta_reco0); //pjet1 close to pq1
          back_reco1_1[1] -> Fill(costheta_reco0); //pjet2 close to pq2
        }
        if(PreSelection(2,35)==true && fabs(costheta_reco0)<0.8) {
          back_reco0_1[2] -> Fill(costheta_reco0); //pjet1 close to pq1
          back_reco1_1[2] -> Fill(costheta_reco1); //pjet2 close to pq2
        }
      }*/
      /*if(fabs(costheta_parton1-costheta_reco1)<fabs(costheta_parton1-costheta_reco0)) {
        //back_reco0_1[0] -> Fill(costheta_reco0); //pjet1 close to pq1
        back_reco1_1[0] -> Fill(costheta_reco1); //pjet2 close to pq2
        if(PreSelection(2,35)==true) {
          //back_reco0_1[1] -> Fill(costheta_reco0); //pjet1 close to pq1
          back_reco1_1[1] -> Fill(costheta_reco1); //pjet2 close to pq2
        }
        if(PreSelection(2,35)==true && fabs(costheta_reco0)<0.8) {
          back_reco0_1[2] -> Fill(costheta_reco0); //pjet1 close to pq1
          back_reco1_1[2] -> Fill(costheta_reco1); //pjet2 close to pq2
        }
      }*/

      if(theta00<theta01) {
        back_reco0_2[0] -> Fill(costheta_reco0);
        //back_reco1_2[0] -> Fill(costheta_reco1);
        if(PreSelection(2,35)==true) {
          back_reco0_2[1] -> Fill(costheta_reco0);
          //back_reco1_2[1] -> Fill(costheta_reco1);
        }
      }
      if(theta01<theta00) {
        back_reco0_2[0] -> Fill(costheta_reco1);
        //back_reco1_2[0] -> Fill(costheta_reco0);
        if(PreSelection(2,35)==true) {
          back_reco0_2[1] -> Fill(costheta_reco1);
          //back_reco1_2[0] -> Fill(costheta_reco0);
        }
      }
      if(theta10<theta11) {
        back_reco1_2[0] -> Fill(costheta_reco0);
        if(PreSelection(2,35)==true) {
          back_reco1_2[1] -> Fill(costheta_reco0);
        }
      }
      if(theta11<theta10) {
        back_reco1_2[0] -> Fill(costheta_reco1);
        if(PreSelection(2,35)==true) {
          back_reco1_2[1] -> Fill(costheta_reco1);
        }
      }
    }//bottom if
  }//event loop

  TFile* MyFile = new TFile("matching.root", "RECREATE");
  MyFile -> cd();
  for(int i=0; i<3; i++) {
    hist_method1[i] -> Write();
    hist_method2[i] -> Write();
    method1_anglereso[i] -> Write(); 
    hist_back_parton[i] -> Write(); 
    hist_back_reco[i] -> Write();
  }
  for(int i=0; i<2; i++) {
    back_parton0[i] -> Write();
    back_parton1[i] -> Write();
    back_reco0_1[i] -> Write(); 
    back_reco1_1[i] -> Write(); 
    back_reco0_2[i] -> Write(); 
    back_reco1_2[i] -> Write();
  }
  MyFile -> Close();
}



void observable::AnalysisY23(int n_entries) {
  std::cout << "########## AnalysisY23() ##########" << std::endl;
  //y23 distribution under typical Egamma cut @PS level (ISR<Egamma -> Signal , ISR>Egamma -> Radiative return)
  TH1F* h1_y23_ps_signal[4];
  TH1F* h1_y23_ps_rad[4];
  for(int i=0; i<4; i++) {
    h1_y23_ps_signal[i] = new TH1F(TString::Format("h1_y23_ps_signal_%i", i), TString::Format("h1_y23_ps_signal_%i", i), 100, 0, 0.025);
    h1_y23_ps_rad[i] = new TH1F(TString::Format("h1_y23_ps_rad_%i", i), TString::Format("h1_y23_ps_rad_%i", i), 100, 0, 0.025);
  }

  TH1F* h1_y23_ps = new TH1F("h1_y23_ps", "h1_y23_ps", 100, 0, 0.025);
  TH1F* h1_y23_ps_ISR = new TH1F("h1_y23_ps_ISR", "h1_y23_ps_ISR", 100, 0, 0.025);
  TH1F* h1_y23_reco = new TH1F("h1_y23_reco", "h1_y23_reco", 100, 0, 0.025);

  //ISR vs y23*jet_R_norm
  TH2F* h2_y23_ps_ISR = new TH2F("h2_y23_ps_ISR", "h2_y23_ps_ISR", 51, -2.5, 252.5, 100, 0, 0.025);
  TH2F* h2_y23_psISR_ISR = new TH2F("h2_y23_psISR_ISR", "h2_y23_psISR_ISR", 51, -2.5, 252.5, 100, 0, 0.025);
  TH2F* h2_y23_reco_ISR = new TH2F("h2_y23_reco_ISR", "h2_y23_reco_ISR", 51, -2.5, 252.5, 100, 0, 0.025);

  //Polar angle of object vs y23*jet_R_norm
  TH2F* h2_y23_ps_costheta = new TH2F("h2_y23_ps_costheta", "h2_y23ps_costheta", 10, 0, 1, 100, 0, 0.025);
  TH2F* h2_y23_psISR_costheta = new TH2F("h2_y23_psISR_costheta", "h2_y23psISR_costheta", 10, 0, 1, 100, 0, 0.025);
  TH2F* h2_y23_reco_costheta = new TH2F("h2_y23_reco_costheta", "h2_y23reco_costheta", 10, 0, 1, 100, 0, 0.025);

  TH1F* bb_signal = new TH1F("bb_signal", "bb_signal", 20, 0, 1); //bbbar signal
  TH1F* bb_event = new TH1F("bb_event", "bb_event", 20, 0, 1);    //selected bbbar by b-tagging
  TH1F* Eff_b = new TH1F("Eff_b", "Eff_b", 20, 0, 1);

  TH1F* cc_signal = new TH1F("cc_signal", "cc_signal", 20, 0, 1);
  TH1F* cc_event = new TH1F("cc_event", "cc_event", 20, 0, 1);
  TH1F* Eff_c = new TH1F("Eff_c", "Eff_c", 20, 0, 1);

  TH1F* ll_signal = new TH1F("ll_signal", "ll_signal", 20, 0, 1);
  TH1F* ll_event = new TH1F("ll_event", "ll_event", 20, 0, 1);
  TH1F* Eff_l = new TH1F("Eff_l", "Eff_l", 20, 0, 1);

  //y23 distribution respect with several costheta regions
  TH1F* h1_y23ps_costheta_proj[10];
  for(int i=0; i<10; i++) {
    h1_y23ps_costheta_proj[i] = new TH1F(TString::Format("h1_y23ps_costheta_%i", i), TString::Format("h1_y23ps_costheta_%i", i), 100, 0, 0.025);
  }


  Long64_t nentries;
  if(n_entries>0) nentries = n_entries;
  else nentries = fChain->GetEntriesFast();
  Long64_t nbytes=0, nb=0;

  //Event loop
  for(Long64_t jentry=0; jentry<nentries; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if(ientry<0) break;
    nb = fChain->GetEntry(jentry); 
    nbytes += nb;
    if (jentry>100000 && jentry%100000==0) std::cout << "Progress: " << 100.*jentry/nentries << "%" << std::endl;

    float ISR_E = mc_ISR_E[0]+mc_ISR_E[1];

    if(fabs(mc_quark_pdg[0])==5) {
      h2_y23_ps_ISR -> Fill(ISR_E, mc_quark_ps_y23*jet_R_norm);
      h2_y23_psISR_ISR -> Fill(ISR_E, mc_quark_ps_isr_y23*jet_R_norm);
      h2_y23_reco_ISR -> Fill(ISR_E, y23*jet_R_norm);

      //Set Egamma cut as several values : 15GeV, 35GeV, 55GeV, 75GeV
      //ISR<Egamma -> Signal , ISR>Egamma -> Radiative return
      if(ISR_E<15) h1_y23_ps_signal[0] -> Fill(mc_quark_ps_y23*jet_R_norm);
      if(ISR_E<35) h1_y23_ps_signal[1] -> Fill(mc_quark_ps_y23*jet_R_norm);
      if(ISR_E<55) h1_y23_ps_signal[2] -> Fill(mc_quark_ps_y23*jet_R_norm);
      if(ISR_E<75) h1_y23_ps_signal[3] -> Fill(mc_quark_ps_y23*jet_R_norm);

      if(ISR_E>15) h1_y23_ps_rad[0] -> Fill(mc_quark_ps_y23*jet_R_norm);
      if(ISR_E>35) h1_y23_ps_rad[1] -> Fill(mc_quark_ps_y23*jet_R_norm);
      if(ISR_E>55) h1_y23_ps_rad[2] -> Fill(mc_quark_ps_y23*jet_R_norm);
      if(ISR_E>75) h1_y23_ps_rad[3] -> Fill(mc_quark_ps_y23*jet_R_norm);
    }//bottom if

    if(ISR_E<35) {
      std::vector<float> pq1;
      pq1.push_back(mc_quark_px[0]);
      pq1.push_back(mc_quark_py[0]);
      pq1.push_back(mc_quark_pz[0]);
      std::vector<float> pq2;
      pq2.push_back(mc_quark_px[1]);
      pq2.push_back(mc_quark_py[1]);
      pq2.push_back(mc_quark_pz[1]);
      float costheta_parton = fabs(GetCostheta(pq1)+GetCostheta(pq2))/2.;

      std::vector<float> pjet1;
      pjet1.push_back(jet_px[0]);
      pjet1.push_back(jet_py[0]);
      pjet1.push_back(jet_pz[0]);
      std::vector<float> pjet2;
      pjet2.push_back(jet_px[1]);
      pjet2.push_back(jet_py[1]);
      pjet2.push_back(jet_pz[1]);
      float costheta_reco = fabs(GetCostheta(pjet1)+GetCostheta(pjet2))/2.;

      //Extract bbbar event
      if(fabs(mc_quark_pdg[0])==5) {
        bb_signal -> Fill(costheta_reco);
        if(PreSelection(3,35)==true) {
          bb_event -> Fill(costheta_reco);
          Eff_b -> Fill(costheta_reco);
        }
        h2_y23_ps_costheta -> Fill(costheta_parton, mc_quark_ps_y23*jet_R_norm);
        //h2_y23_psISR_costheta -> Fill(costheta_parton, mc_quark_ps_isr_y23*jet_R_norm);
        //h2_y23_reco_costheta -> Fill(costheta_parton, y23*jet_R_norm);

        for(int i=0; i<5; i++) {
          if(costheta_parton<0.2*(i+1) && costheta_parton>0.2*i) h1_y23ps_costheta_proj[i] -> Fill(mc_quark_ps_y23*jet_R_norm);
          h1_y23_ps -> Fill(mc_quark_ps_y23*jet_R_norm);
          h1_y23_ps_ISR -> Fill(mc_quark_ps_isr_y23*jet_R_norm);
          h1_y23_reco -> Fill(y23*jet_R_norm);
        }
      }//bottom if

      //Extract ccbar event
      if(fabs(mc_quark_pdg[0])==4) {
        cc_signal -> Fill(costheta_reco);
        if(PreSelection(3,35)==true) {
          cc_event -> Fill(costheta_reco);
          Eff_c -> Fill(costheta_reco);
        }
      }//charm if

      //Extract llbar event
      if(fabs(mc_quark_pdg[0])<4) {
        ll_signal -> Fill(costheta_reco);
        if(PreSelection(3,35)==true) {
          ll_event -> Fill(costheta_reco);
          Eff_l -> Fill(costheta_reco);
        }
      }//uds if
    }//ISR if
  }//Event loop


  //Writing results
  TFile* MyFile2 = new TFile("y23_analysis.root", "RECREATE");
  MyFile2 -> cd();
  h1_y23_ps -> Write();
  h1_y23_ps_ISR -> Write();
  h1_y23_reco -> Write();

  h2_y23_ps_ISR -> Write();
  h2_y23_psISR_ISR -> Write();
  h2_y23_reco_ISR -> Write();

  bb_signal -> Write();
  bb_event -> Write();
  Eff_b -> Divide(bb_signal);
  Eff_b -> Write();
  cc_signal -> Write();
  cc_event -> Write();
  Eff_c -> Divide(cc_signal);
  Eff_c -> Write();
  ll_signal -> Write();
  ll_event -> Write();
  Eff_l -> Divide(ll_signal);
  Eff_l -> Write();

  h2_y23_ps_costheta -> Write();
  h2_y23_psISR_costheta -> Write();
  h2_y23_reco_costheta -> Write();

  for(int i=0; i<4; i++) {
    h1_y23_ps_signal[i] -> Write();
    h1_y23_ps_rad[i] -> Write();
    h1_y23_ps_signal[i] -> Write();
    h1_y23_ps_rad[i] -> Write();
  }
  for(int i=0; i<5; i++) {
    h1_y23ps_costheta_proj[i] -> Write();
  }
  std::cout << "Writing Complete" << std::endl;

  /*TCanvas* canvas = new TCanvas("canvas", "canvas", 800, 800);
  for(int i=0; i<4; i++) {
    h1_y23_ps_signal[i] -> SetLineColor(4);
    h1_y23_ps_signal[i] -> SetLineStyle(1);
    h1_y23_ps_signal[i] -> SetLineWidth(1+i);
    h1_y23_ps_signal[i] -> DrawNormalized("same");

    h1_y23_ps_rad[i] -> SetLineColor(2);
    h1_y23_ps_rad[i] -> SetLineStyle(2);
    h1_y23_ps_rad[i] -> SetLineWidth(1+i);
    h1_y23_ps_rad[i] -> DrawNormalized("same");
  }
  canvas -> Write();

  TCanvas* canvas2 = new TCanvas("canvas2", "canvas2", 800, 800);
  TLegend* leg = new TLegend(0.7, 0.6, 0.85, 0.9);
  for(int i=0; i<5; i++) {
    if(i<3) { //0<costheta<0.6
      h1_y23ps_costheta_proj[i] -> SetLineColor(1+i);
      h1_y23ps_costheta_proj[i] -> SetLineStyle(1);
      h1_y23ps_costheta_proj[i] -> SetLineWidth(2);
      h1_y23ps_costheta_proj[i] -> DrawNormalized("same");
    } 
    else if(i<5) { //0.6<costheta<1.0
      h1_y23ps_costheta_proj[i] -> SetLineColor(kGray+i-3);
      h1_y23ps_costheta_proj[i] -> SetLineStyle(2);
      h1_y23ps_costheta_proj[i] -> SetLineWidth(2);
      h1_y23ps_costheta_proj[i] -> DrawNormalized("same");
    }
    else {
      h1_y23ps_costheta_proj[i] -> SetLineColor(1+i);
      h1_y23ps_costheta_proj[i] -> SetLineStyle(2);
      h1_y23ps_costheta_proj[i] -> SetLineWidth(3);
      h1_y23ps_costheta_proj[i] -> DrawNormalized("same");
    }
    if(i==0) leg->AddEntry(TString::Format("h1_y23_ps_costheta_%i", i), "costheta>0.0 & costheta<0.2", "l");
    if(i==1) leg->AddEntry(TString::Format("h1_y23_ps_costheta_%i", i), "costheta>0.2 & costheta<0.4", "l");
    if(i==2) leg->AddEntry(TString::Format("h1_y23_ps_costheta_%i", i), "costheta>0.4 & costheta<0.6", "l");
    if(i==3) leg->AddEntry(TString::Format("h1_y23_ps_costheta_%i", i), "costheta>0.6 & costheta<0.8", "l");
    if(i==4) leg->AddEntry(TString::Format("h1_y23_ps_costheta_%i", i), "costheta>0.8 & costheta<1.0", "l");
  }
  leg -> Draw();
  canvas2 -> Write();
  std::cout << "Writing Complete" << std::endl;*/
}//AnalysisY23()



bool observable::PreSelection(int type,float Kvcut) {
  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
  double b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
  double b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
  double bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

  TVector3 v1(jet_px[0],jet_py[0],jet_pz[0]);
  TVector3 v2(jet_px[1],jet_py[1],jet_pz[1]);
  float acol=GetSinacol(v1,v2);
  
  double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
  double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

  float costheta_j0;
  std::vector<float> p_j0;
  p_j0.push_back(jet_px[0]);
  p_j0.push_back(jet_py[0]);
  p_j0.push_back(jet_pz[0]);
  costheta_j0=fabs(GetCostheta(p_j0));

  float costheta_j1;
  std::vector<float> p_j1;
  p_j1.push_back(jet_px[1]);
  p_j1.push_back(jet_py[1]);
  p_j1.push_back(jet_pz[1]);
  costheta_j1=fabs(GetCostheta(p_j1));
  
  float Kv=250.*acol/(acol+sqrt(1-costheta_j0*costheta_j0)+sqrt(1-costheta_j1*costheta_j1));
  
   
  double  neutralPFO_max[2];
  double  neutralPFO_total[2];
  double  neutralPFO_ratio[2];

  double  neutraljet_E[2];
  double  neutraljet_costheta[2];
  
  float costheta_neutral0;
  float costheta_neutral1;
  
  
  float neut[2][3];
  
  double npfo[2];
  for(int ijet=0; ijet<2; ijet++) {
    neutralPFO_max[ijet]=0;
    neutralPFO_total[ijet]=0;
    neutralPFO_ratio[ijet]=0;
    npfo[ijet]=0;
    double jetenergy=0;
    
    neut[ijet][0]=0;
    neut[ijet][1]=0;
    neut[ijet][2]=0;
    
    for(int ipfo=0; ipfo<jet_pfo_n[ijet]; ipfo++) {
      if(jet_pfo_E[ijet][ipfo]<0.1) continue;
      
      npfo[ijet]++;
      jetenergy+=jet_pfo_E[ijet][ipfo];
      if( (jet_pfo_type[ijet][ipfo]==22 || jet_pfo_charge[ijet][ipfo]==0) && jet_pfo_E[ijet][ipfo]> neutralPFO_max[ijet]) {
  neutralPFO_max[ijet]=jet_pfo_E[ijet][ipfo]; 
      }
      if( jet_pfo_type[ijet][ipfo]==22 ||  jet_pfo_charge[ijet][ipfo]==0 ) {
  
  neut[ijet][0]+=jet_pfo_px[ijet][ipfo];
  neut[ijet][1]+=jet_pfo_py[ijet][ipfo];
  neut[ijet][2]+=jet_pfo_pz[ijet][ipfo];
  
  neutralPFO_total[ijet]+=jet_pfo_E[ijet][ipfo]; 
  neutralPFO_ratio[ijet]+=jet_pfo_E[ijet][ipfo]; 
      }
    }
    neutralPFO_ratio[ijet]/=jetenergy;
  }

  for(int ijet=0; ijet<2; ijet++) {
    neutraljet_E[ijet]=-1;
    neutraljet_costheta[ijet]=-1; 
    if(neutralPFO_ratio[ijet]>0.85) {
      neutraljet_E[ijet]=jet_E[ijet];
      if(ijet==0) neutraljet_costheta[ijet]=costheta_j0;
      if(ijet==1) neutraljet_costheta[ijet]=costheta_j1;
    }
  }

        
  std::vector<float> neutral0;
  neutral0.push_back(neut[0][0]);
  neutral0.push_back(neut[0][1]);
  neutral0.push_back(neut[0][2]);
  
  std::vector<float> neutral1;
  neutral1.push_back(neut[1][0]);
  neutral1.push_back(neut[1][1]);
  neutral1.push_back(neut[1][2]);
  
  costheta_neutral0=GetCostheta(neutral0);
  costheta_neutral1=GetCostheta(neutral1);
  
  
  bool ISR_1=true;
  if(neutralPFO_ratio[0]<0.65 && neutralPFO_ratio[1]<0.65) ISR_1=false;
  
  bool ISR_2=true;
  if(npfo[0]>5 && npfo[1]>5) ISR_2=false;
  
  bool ISR_3=false;
  if( (fabs(costheta_neutral0)>0.99 && neutralPFO_total[0]>Kvcut) || (fabs(costheta_neutral1)>0.99 && neutralPFO_total[1]>Kvcut) ) ISR_3=true;
  
  //NO SELECTION
  if(type == 0 ) return true;
  // ALL QUARKS, no radiative return
  if(type == 1 )  if( bbmass>130 && Kv < Kvcut && ISR_1==false && ISR_2==false && ISR_3==false && (b1mass+b2mass)<100)  return true;
  // B-quarks QUARKS, no radiative return
  if(type == 2 )  if( bbmass>130 && Kv < Kvcut && ISR_1==false && ISR_2==false && ISR_3==false && (b1mass+b2mass)<100 && jet_btag[0]>btag1 && jet_btag[1]>btag2)  return true;
  // light-quarks QUARKS, no radiative return
  if(type == 3 )  if( bbmass>130 && Kv < Kvcut && ISR_1==false && ISR_2==false && ISR_3==false && (b1mass+b2mass)<100 && (jet_btag[0]<0.4 && jet_ctag[0]<0.25) && (jet_btag[1]<0.4 && jet_ctag[1]<0.25)) return true;

  return false;
}//PreSelection
