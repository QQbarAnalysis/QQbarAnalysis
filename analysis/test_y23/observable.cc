// A. Irles
// irles @ lal.in2p3.fr
// 30 March 2020

#define observable_cxx
#include "observable.h"
#include "TPad.h"


void observable::AnalysisR3(int n_entries=-1, bool inclusive = false)
{

  double R3b_ps[4][50];// firxt index : step of reconstruction, second index: ycut value (defined in the ntuple)
  double R3l_ps[4][50];
  double Rall_b_ps[4];
  double Rall_l_ps[4];

  double R3b_reco[4][50];
  double R3l_reco[4][50];
  double Rall_b_reco[4];
  double Rall_l_reco[4];
  
  double ycut_array[50];
  double eycut_array[50];

  for(int i=0; i<4; i++) {
    Rall_b_ps[i]=0;
    Rall_l_ps[i]=0;
    Rall_b_reco[i]=0;
    Rall_l_reco[i]=0;
    
    for(int j=0; j<50; j++) {
      R3b_ps[i][j]=0;
      R3l_ps[i][j]=0;
      R3b_reco[i][j]=0;
      R3l_reco[i][j]=0;

      ycut_array[j]=0;
      eycut_array[j]=0;

    }
  }


  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();
  //  nentries=1000000;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    // Variables to perform cuts at parton level
    //
    float ISR_E=mc_ISR_E[0]+mc_ISR_E[1];
    if(ISR_E>35) continue; // exclude radiative return events from the analysis

    //write the value of ycut_array, just once (it is the same for all the events)
    if(ycut_array[10] == 0 ) {
      for(int iycut=0; iycut<50; iycut++) ycut_array[iycut]=ycut[iycut];
    }

    //how do we define costheta, in absolute value ?
    std::vector<float> pjet1;
    pjet1.push_back(jet_px[0]);
    pjet1.push_back(jet_py[0]);
    pjet1.push_back(jet_pz[0]);
    std::vector<float> pjet2;
    pjet2.push_back(jet_px[1]);
    pjet2.push_back(jet_py[1]);
    pjet2.push_back(jet_pz[1]);
    
    float costheta_reco=(fabs(GetCostheta(pjet1))+fabs(GetCostheta(pjet2)))/2.;

    //b-quark
    if(fabs(mc_quark_pdg[0])==5) {

      Rall_b_ps[0]++;
      Rall_b_reco[0]++;
      if(PreSelection(1,35)==true) {
	Rall_b_ps[1]++;
	Rall_b_reco[1]++;
      }
      if(PreSelection(2,35)==true) {
	Rall_b_ps[2]++;
	Rall_b_reco[2]++;
      }
      if(PreSelection(2,35)==true && costheta_reco<0.8) {
	Rall_b_ps[3]++;
	Rall_b_reco[3]++;
      }
      
      //    ------------------------------------------------------------------------
      for(int iycut=0; iycut<50; iycut++) {
	bool njets_condition=false;
	if(inclusive == true && mc_quark_ps_njets_ycut[iycut]>2.5 ) njets_condition=true;
	if(inclusive == false && mc_quark_ps_njets_ycut[iycut]>2.5 && mc_quark_ps_njets_ycut[iycut]<3.5) njets_condition=true;

	//parton shower level
	if(njets_condition==true) { // should we save events with EXACTLY 3 jets... or should we save events with >2 jets ???
	  R3b_ps[0][iycut]++; //step 0, no cuts
	  if(PreSelection(1,35)==true) R3b_ps[1][iycut]++; //step 1 two hadronic jets selection
	  if(PreSelection(2,35)==true) R3b_ps[2][iycut]++; //step 2 two b-jets selection
	  if(PreSelection(2,35)==true && costheta_reco<0.8) R3b_ps[3][iycut]++; //step 2 two b-jets selection but excluding very forward regions
	}

	njets_condition=false;
	if(inclusive == true && njets_ycut[iycut]>2.5 ) njets_condition=true;
	if(inclusive == false && njets_ycut[iycut]>2.5 && mc_quark_ps_njets_ycut[iycut]<3.5) njets_condition=true;

	//RECO LEVEL level
	if(njets_condition==true) { // should we save events with EXACTLY 3 jets... or should we save events with >2 jets ??? 
	  R3b_reco[0][iycut]++; //step 0, no cuts
	  if(PreSelection(1,35)==true) R3b_reco[1][iycut]++; //step 1 two hadronic jets selection
	  if(PreSelection(2,35)==true) R3b_reco[2][iycut]++; //step 2 two b-jets selection
	  if(PreSelection(2,35)==true && costheta_reco<0.8) R3b_reco[3][iycut]++; //step 2 two b-jets selection but excluding very forward regions
	}
      }
    }

    //uds-quarks
    if(fabs(mc_quark_pdg[0])<4) {
      
      Rall_l_ps[0]++;
      Rall_l_reco[0]++;
      if(PreSelection(1,35)==true) {
	Rall_l_ps[1]++;
	Rall_l_reco[1]++;
      }
      if(PreSelection(3,35)==true) {
	Rall_l_ps[2]++;
	Rall_l_reco[2]++;
      }
      if(PreSelection(3,35)==true && costheta_reco<0.8) {
	Rall_l_ps[3]++;
	Rall_l_reco[3]++;
      }
      //    ------------------------------------------------------------------------
        for(int iycut=0; iycut<50; iycut++) {
	bool njets_condition=false;
	if(inclusive == true && mc_quark_ps_njets_ycut[iycut]>2.5 ) njets_condition=true;
	if(inclusive == false && mc_quark_ps_njets_ycut[iycut]>2.5 && mc_quark_ps_njets_ycut[iycut]<3.5) njets_condition=true;

	//parton shower level
	if(njets_condition==true) { // should we save events with EXACTLY 3 jets... or should we save events with >2 jets ???
	  R3l_ps[0][iycut]++; //step 0, no cuts
	  if(PreSelection(1,35)==true) R3l_ps[1][iycut]++; //step 1 two hadronic jets selection
	  if(PreSelection(3,35)==true) R3l_ps[2][iycut]++; //step 2 two uds-jets selection
	  if(PreSelection(3,35)==true && costheta_reco<0.8) R3l_ps[3][iycut]++; //step 2 two uds-jets selection but excluding very forward regions
	}

	njets_condition=false;
	if(inclusive == true && njets_ycut[iycut]>2.5 ) njets_condition=true;
	if(inclusive == false && njets_ycut[iycut]>2.5 && mc_quark_ps_njets_ycut[iycut]<3.5) njets_condition=true;

	//RECO LEVEL level
	if(njets_condition==true) { // should we save events with EXACTLY 3 jets... or should we save events with >2 jets ??? 
	  R3l_reco[0][iycut]++; //step 0, no cuts
	  if(PreSelection(1,35)==true) R3l_reco[1][iycut]++; //step 1 two hadronic jets selection
	  if(PreSelection(3,35)==true) R3l_reco[2][iycut]++; //step 2 two uds-jets selection
	  if(PreSelection(3,35)==true && costheta_reco<0.8) R3l_reco[3][iycut]++; //step 2 two uds-jets selection but excluding very forward regions
	}
      }
    }

      
  }


  //Save results in TGraohErrors
  TString filename="output_y23_inclusive.root";
  if(inclusive==false) filename="output_y23_exclusive.root";
  TFile *MyFile = new TFile(filename,"RECREATE");
  MyFile->cd();
  
  //----------------------------------------------------
  //calculate R3b and R3q and their errors
  double eR3b_ps[4][50];
  double eR3b_reco[4][50];
  double eR3l_ps[4][50];
  double eR3l_reco[4][50];
  
  for(int i=0; i<4; i++) {
    for(int j=0; j<50; j++) {
      //b
      if(Rall_b_ps[i]>0 && R3b_ps[i][j]) {
	eR3b_ps[i][j]=(R3b_ps[i][j]/Rall_b_ps[i]) * sqrt(1./R3b_ps[i][j] + 1./Rall_b_ps[i]);
	R3b_ps[i][j]=(R3b_ps[i][j]/Rall_b_ps[i]);
      }
      else {
	eR3b_ps[i][j]=0;
	R3b_ps[i][j]=0.;
      }

      if(Rall_b_reco[i]>0 && R3b_reco[i][j]) {
	eR3b_reco[i][j]=(R3b_reco[i][j]/Rall_b_reco[i]) * sqrt(1./R3b_reco[i][j] + 1/Rall_b_reco[i]);
	R3b_reco[i][j]=(R3b_reco[i][j]/Rall_b_reco[i]);
      }
      else {
	eR3b_reco[i][j]=0;
	R3b_reco[i][j]=0.;
      }

      //l
      if(Rall_l_ps[i]>0 && R3l_ps[i][j]) {
	eR3l_ps[i][j]=(R3l_ps[i][j]/Rall_l_ps[i]) * sqrt(1./R3l_ps[i][j] + 1./Rall_l_ps[i]);
	R3l_ps[i][j]=(R3l_ps[i][j]/Rall_l_ps[i]);
      }
      else {
	eR3l_ps[i][j]=0;
	R3l_ps[i][j]=0.;
      }

      if(Rall_l_reco[i]>0 && R3l_reco[i][j]) {
	eR3l_reco[i][j]=(R3l_reco[i][j]/Rall_l_reco[i]) * sqrt(1./R3l_reco[i][j] + 1./Rall_l_reco[i]);
	R3l_reco[i][j]=(R3l_reco[i][j]/Rall_l_reco[i]);
      }
      else {
	eR3l_reco[i][j]=0;
	R3l_reco[i][j]=0.;
      }
    }
  }

  TGraphErrors * graph_R3b_ps[4];
  TGraphErrors * graph_R3l_ps[4];
  TGraphErrors * graph_R3b_reco[4];
  TGraphErrors * graph_R3l_reco[4];
  
  for(int i=0; i<4; i++) {
    graph_R3b_ps[i]= new TGraphErrors (50, ycut_array,R3b_ps[i],eycut_array,eR3b_ps[i]);
    graph_R3b_reco[i]= new TGraphErrors (50, ycut_array,R3b_reco[i],eycut_array,eR3b_reco[i]);
    graph_R3l_ps[i]= new TGraphErrors (50, ycut_array,R3l_ps[i],eycut_array,eR3l_ps[i]);
    graph_R3l_reco[i]= new TGraphErrors (50, ycut_array,R3l_reco[i],eycut_array,eR3l_reco[i]);
    graph_R3b_ps[i]->SetName(TString::Format("R3b_PS_step%i",i));
    graph_R3b_reco[i]->SetName(TString::Format("R3b_reco_step%i",i));
    graph_R3l_ps[i]->SetName(TString::Format("R3l_PS_step%i",i));
    graph_R3l_reco[i]->SetName(TString::Format("R3l_reco_step%i",i));
    graph_R3b_ps[i]->Write();
    graph_R3b_reco[i]->Write();
    graph_R3l_ps[i]->Write();
    graph_R3l_reco[i]->Write();
  }

  
  //----------------------------------------------------
  //calculate R3bl and their errors
  double R3bl_ps[4][50];
  double R3bl_reco[4][50];

  double eR3bl_ps[4][50];
  double eR3bl_reco[4][50];
  
  for(int i=0; i<4; i++) {
    for(int j=0; j<50; j++) {
      R3bl_ps[i][j]=0;
      R3bl_reco[i][j]=0;
      eR3bl_ps[i][j]=0;
      eR3bl_reco[i][j]=0;
    }
  }

  for(int i=0; i<4; i++) {
    for(int j=0; j<50; j++) {
      //Parton shower
      if(R3b_ps[i][j] && R3l_ps[i][j]>0) {
	eR3bl_ps[i][j]=(R3b_ps[i][j]/R3l_ps[i][j]) * sqrt(pow(eR3b_ps[i][j]/R3b_ps[i][j],2) + pow(eR3l_ps[i][j]/(R3l_ps[i][j]),2));
	R3bl_ps[i][j]=(R3b_ps[i][j]/R3l_ps[i][j]);
      }
      else {
	eR3bl_ps[i][j]=0;
	R3bl_ps[i][j]=0.;
      }
      //reco
      if(R3b_reco[i][j] && R3l_reco[i][j]>0) {
	eR3bl_reco[i][j]=(R3b_reco[i][j]/R3l_reco[i][j]) * sqrt(pow(eR3b_reco[i][j]/R3b_reco[i][j],2) + pow(eR3l_reco[i][j]/(R3l_reco[i][j]),2));
	R3bl_reco[i][j]=(R3b_reco[i][j]/R3l_reco[i][j]);
      }
      else {
	eR3bl_reco[i][j]=0;
	R3bl_reco[i][j]=0.;
      }
    }
  }

  TGraphErrors * graph_R3bl_ps[4];
  TGraphErrors * graph_R3bl_reco[4];
  
  for(int i=0; i<4; i++) {
    graph_R3bl_ps[i]= new TGraphErrors (50, ycut_array,R3bl_ps[i],eycut_array,eR3bl_ps[i]);
    graph_R3bl_reco[i]= new TGraphErrors (50, ycut_array,R3bl_reco[i],eycut_array,eR3bl_reco[i]);
    graph_R3bl_ps[i]->SetName(TString::Format("R3bl_PS_step%i",i));
    graph_R3bl_reco[i]->SetName(TString::Format("R3bl_reco_step%i",i));
    graph_R3bl_ps[i]->Write();
    graph_R3bl_reco[i]->Write();
  }
 
}

void observable::AnalysisR3_y23(int n_entries=-1)
{

  double R3b_ps[4];// firxt index : step of reconstruction, second index: ycut value (defined in the ntuple)
  double R3l_ps[4];
  double Rall_b_ps[4];
  double Rall_l_ps[4];

  double R3b_reco[4];
  double R3l_reco[4];
  double Rall_b_reco[4];
  double Rall_l_reco[4];
  
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


  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();
  //  nentries=1000000;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    // Variables to perform cuts at parton level
    //
    float ISR_E=mc_ISR_E[0]+mc_ISR_E[1];
    if(ISR_E>35) continue; // exclude radiative return events from the analysis

    //how do we define costheta, in absolute value ?
    std::vector<float> pjet1;
    pjet1.push_back(jet_px[0]);
    pjet1.push_back(jet_py[0]);
    pjet1.push_back(jet_pz[0]);
    std::vector<float> pjet2;
    pjet2.push_back(jet_px[1]);
    pjet2.push_back(jet_py[1]);
    pjet2.push_back(jet_pz[1]);
    
    float costheta_reco=(fabs(GetCostheta(pjet1))+fabs(GetCostheta(pjet2)))/2.;

    //b-quark
    if(fabs(mc_quark_pdg[0])==5) {

      Rall_b_ps[0]++;
      Rall_b_reco[0]++;
      if(PreSelection(1,35)==true) {
	Rall_b_ps[1]++;
	Rall_b_reco[1]++;
      }
      if(PreSelection(2,35)==true) {
	Rall_b_ps[2]++;
	Rall_b_reco[2]++;
      }
      if(PreSelection(2,35)==true && costheta_reco<0.8) {
	Rall_b_ps[3]++;
	Rall_b_reco[3]++;
      }
      
      //    ------------------------------------------------------------------------
      
      if( mc_quark_ps_y23*jet_R_norm >0.01 ) {
	R3b_ps[0]++; //step 0, no cuts
	if(PreSelection(1,35)==true) R3b_ps[1]++; //step 1 two hadronic jets selection
	if(PreSelection(2,35)==true) R3b_ps[2]++; //step 2 two b-jets selection
	if(PreSelection(2,35)==true && costheta_reco<0.8) R3b_ps[3]++; //step 2 two b-jets selection but excluding very forward regions
      }
      if( y23*jet_R_norm >0.01 ) {
	R3b_reco[0]++; //step 0, no cuts
	if(PreSelection(1,35)==true) R3b_reco[1]++; //step 1 two hadronic jets selection
	if(PreSelection(2,35)==true) R3b_reco[2]++; //step 2 two b-jets selection
	if(PreSelection(2,35)==true && costheta_reco<0.8) R3b_reco[3]++; //step 2 two b-jets selection but excluding very forward regions
      }
    }

    //uds-quark
    if(fabs(mc_quark_pdg[0])<4) {
      Rall_l_ps[0]++;
      Rall_l_reco[0]++;
      if(PreSelection(1,35)==true) {
	Rall_l_ps[1]++;
	Rall_l_reco[1]++;
      }
      if(PreSelection(3,35)==true) {
	Rall_l_ps[2]++;
	Rall_l_reco[2]++;
      }
      if(PreSelection(3,35)==true && costheta_reco<0.8) {
	Rall_l_ps[3]++;
	Rall_l_reco[3]++;
      }
      
      //    ------------------------------------------------------------------------
      
      if( mc_quark_ps_y23*jet_R_norm >0.01 ) {
	R3l_ps[0]++; //step 0, no cuts
	if(PreSelection(1,35)==true) R3l_ps[1]++; //step 1 two hadronic jets selection
	if(PreSelection(3,35)==true) R3l_ps[2]++; //step 2 two b-jets selection
	if(PreSelection(3,35)==true && costheta_reco<0.8) R3l_ps[3]++; //step 2 two b-jets selection but excluding very forward regions
      }
      if( y23*jet_R_norm >0.01 ) {
	R3l_reco[0]++; //step 0, no cuts
	if(PreSelection(1,35)==true) R3l_reco[1]++; //step 1 two hadronic jets selection
	if(PreSelection(3,35)==true) R3l_reco[2]++; //step 2 two b-jets selection
	if(PreSelection(3,35)==true && costheta_reco<0.8) R3l_reco[3]++; //step 2 two b-jets selection but excluding very forward regions
      }
    }


      
  }

  for(int i=0; i<4; i++) {
    cout<< "RESULTS FOR SELECTION STEP "<<i<<endl;
    cout<< "parton shower level: R3b = "<<R3b_ps[i]/Rall_b_ps[i]<<"  R3l="<<R3l_ps[i]/Rall_l_ps[i]<< " ---> R3bl="<< (R3b_ps[i]/Rall_b_ps[i]) / (R3l_ps[i]/Rall_l_ps[i])<<endl;
    cout<< "reco level: R3b = "<<R3b_reco[i]/Rall_b_reco[i]<<"  R3l="<<R3l_reco[i]/Rall_l_reco[i]<< " ---> R3bl="<< (R3b_reco[i]/Rall_b_reco[i]) / (R3l_reco[i]/Rall_l_reco[i])<<endl;
  }
 
}
void observable::Efficiencies(int n_entries=-1)
{

  double n_signal[3]; //E_ISR<35, n_signal[0] --> N reconstructed jets in bbbar events, n_signal[1] --> N reconstructed jets in ccbar events, n_signal[2] --> N reconstructed jets in uds-udsbar events
  double nbtag_selected[3];//E_ISR<35, nb_selected[0] -->N jets tagged as b-quark in bbbar events, nb_selected[1] --> N jets tagged as b-quark in ccbar events, etc
  double nctag_selected[3];// same than above but with ctag
  double nudstag_selected[3]; // same than above but with uds-tag
  for(int i=0; i<3; i++) {
    n_signal[i]=0;
    nbtag_selected[i]=0;
    nctag_selected[i]=0;
    nudstag_selected[i]=0;
  }
  
  //we define btagging as btag>0.8
  //we define ctagging as ctag>0.85
  //we define uds-tagging as btag<0.4 & ctag<0.25

    Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();
  // nentries=10000;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;
    float ISR_E=mc_ISR_E[0]+mc_ISR_E[1];

    if(ISR_E>35) continue;
    if(PreSelection(1,35)==false) continue;
    
    for(int ijet=0; ijet<2; ijet++) {
      // the event is bbbar signal (because ISR_E<35 GeV one of the parton is a b-quark -we only simulate quark pair events- )
      if(fabs(mc_quark_pdg[ijet])==5) {
	n_signal[0]++;
	if(jet_btag[ijet]>0.8) nbtag_selected[0]++;
	if(jet_ctag[ijet]>0.875) nctag_selected[0]++;
	if(jet_btag[ijet]<0.4 && jet_ctag[ijet]<0.25) nudstag_selected[0]++;
      }
      //c-quark
      if(fabs(mc_quark_pdg[ijet])==4) {
	n_signal[1]++;
	if(jet_btag[ijet]>0.8) nbtag_selected[1]++;
	if(jet_ctag[ijet]>0.875) nctag_selected[1]++;
	if(jet_btag[ijet]<0.4 && jet_ctag[ijet]<0.25) nudstag_selected[1]++;
      }
      //uds-quarks
      if(fabs(mc_quark_pdg[ijet])<4) {
	n_signal[2]++;
	if(jet_btag[ijet]>0.8) nbtag_selected[2]++;
	if(jet_ctag[ijet]>0.875) nctag_selected[2]++;
	if(jet_btag[ijet]<0.4 && jet_ctag[ijet]<0.25) nudstag_selected[2]++;
      }
    }
  }

  cout<<"Results" <<endl;
  cout<<" ---------------------------------"<<endl;
  cout<< "N B-jets (truth): "<<n_signal[0]<<"   N C-jets (truth): "<<n_signal[1]<<"   N UDS-jets (truth): "<<n_signal[2]<<endl;
  cout<< "N B-jets (tagged as b) "<<nbtag_selected[0]<<"   N B-jets (mis-tagged as c) "<<nctag_selected[0]<<"   N B-jets (mis-tagged as uds) "<<nudstag_selected[0]<<endl;
  cout<< "N C-jets (mis-tagged as b) "<<nbtag_selected[1]<<"   N C-jets (tagged as c) "<<nctag_selected[1]<<"   N C-jets (mis-tagged as uds) "<<nudstag_selected[1]<<endl;
  cout<< "N UDS-jets (mis-tagged as b) "<<nbtag_selected[2]<<"   N UDS-jets (mis-tagged as c) "<<nctag_selected[2]<<"   N UDS-jets (tagged as uds) "<<nudstag_selected[2]<<endl;

}

void observable::AnalysisY23(int n_entries=-1)
{

  TH1F * h1_y23_ps_signal[4];
  TH1F * h1_y23_ps_rad[4];

  for(int i=0; i<4; i++) {
    h1_y23_ps_signal[i] = new TH1F(TString::Format("h1_y23_ps_signal_%i",i),TString::Format("h1_y23_ps_signal_%i",i),100,0,0.025);
    h1_y23_ps_rad[i] = new TH1F(TString::Format("h1_y23_ps_rad_%i",i),TString::Format("h1_y23_ps_rad_%i",i),100,0,0.025);
  }

  
  TH1F * h1_y23_ps = new TH1F("h1_y23_ps","h1_y23_ps",100,0,0.025);
  TH1F * h1_y23_ps_ISR = new TH1F("h1_y23_ps_ISR","h1_y23_ps_ISR",100,0,0.025);
  TH1F * h1_y23_reco = new TH1F("h1_y23_reco","h1_y23_reco",100,0,0.025);

  TH2F * h2_y23ps_ISR = new TH2F("h2_y23ps_ISR","h2_y23ps_ISR",51,-2.5,252.5,100,0,0.025);
  TH2F * h2_y23psISR_ISR = new TH2F("h2_y23psISR_ISR","h2_y23psISR_ISR",51,-2.5,252.5,100,0,0.025);
  TH2F * h2_y23reco_ISR = new TH2F("h2_y23reco_ISR","h2_y23reco_ISR",51,-2.5,252.5,100,0,0.025);

  TH2F * h2_y23ps_costheta = new TH2F("h2_y23ps_costheta","h2_y23ps_costheta",10,0,1,100,0,0.025);
  TH2F * h2_y23psISR_costheta = new TH2F("h2_y23psISR_costheta","h2_y23psISR_costheta",10,0,1,100,0,0.025);
  TH2F * h2_y23reco_costheta = new TH2F("h2_y23reco_costheta","h2_y23reco_costheta",10,0,1,100,0,0.025);

  TH1F * bb_signal = new TH1F("bb_signal","bb_signal",20,0,1);
  TH1F * bb_event = new TH1F("bb_event","bb_event",20,0,1);
  TH1F * Eff_b = new TH1F("Eff_b","Eff_b",20,0,1);

  TH1F * cc_signal = new TH1F("cc_signal","cc_signal",20,0,1);
  TH1F * cc_event = new TH1F("cc_event","cc_event",20,0,1);
  TH1F * Eff_c = new TH1F("Eff_c","Eff_c",20,0,1);
  
  TH1F * qq_signal = new TH1F("qq_signal","qq_signal",20,0,1);
  TH1F * qq_event = new TH1F("qq_event","qq_event",20,0,1);
  TH1F * Eff_q = new TH1F("Eff_q","Eff_q",20,0,1);
  
  TH1F * h1_y23ps_costheta_proj[10];
  for(int i=0; i<10; i++) {
    h1_y23ps_costheta_proj[i] = new TH1F(TString::Format("h1_y23ps_costheta_%i",i),TString::Format("h1_y23ps_costheta_%i",i),100,0,0.025);
  }
  
  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();
  //  nentries=1000000;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    // Variables to perform cuts at parton level
    //
    float ISR_E=mc_ISR_E[0]+mc_ISR_E[1];

    if(fabs(mc_quark_pdg[0])==5) {
      h2_y23ps_ISR->Fill(ISR_E,mc_quark_ps_y23*jet_R_norm);
      h2_y23psISR_ISR->Fill(ISR_E,mc_quark_ps_isr_y23*jet_R_norm);
      h2_y23reco_ISR->Fill(ISR_E,y23*jet_R_norm);

      if(ISR_E<15) h1_y23_ps_signal[0]->Fill(mc_quark_ps_y23*jet_R_norm);
      if(ISR_E<35) h1_y23_ps_signal[1]->Fill(mc_quark_ps_y23*jet_R_norm);
      if(ISR_E<55) h1_y23_ps_signal[2]->Fill(mc_quark_ps_y23*jet_R_norm);
      if(ISR_E<75) h1_y23_ps_signal[3]->Fill(mc_quark_ps_y23*jet_R_norm);

      if(ISR_E>15) h1_y23_ps_rad[0]->Fill(mc_quark_ps_y23*jet_R_norm);
      if(ISR_E>35) h1_y23_ps_rad[1]->Fill(mc_quark_ps_y23*jet_R_norm);
      if(ISR_E>55) h1_y23_ps_rad[2]->Fill(mc_quark_ps_y23*jet_R_norm);
      if(ISR_E>75) h1_y23_ps_rad[3]->Fill(mc_quark_ps_y23*jet_R_norm); 
    }
    //for the moment, we restrict the analysis to the cc events without radaitive return
    if(ISR_E<35) {

      //how do we define costheta, in absolute value ?
      //parton level, not including ISR or radiative return
      std::vector<float> pq1;
      pq1.push_back(mc_quark_px[0]);
      pq1.push_back(mc_quark_py[0]);
      pq1.push_back(mc_quark_pz[0]);
      std::vector<float> pq2;
      pq2.push_back(mc_quark_px[1]);
      pq2.push_back(mc_quark_py[1]);
      pq2.push_back(mc_quark_pz[1]);
      
      float costheta_parton=(fabs(GetCostheta(pq1)));//+fabs(GetCostheta(pq2)))/2.;
      // h2_y23ps_costheta->Fill(costheta_parton,mc_quark_ps_y23*jet_R_norm);

      //same at reco level
      std::vector<float> pjet1;
      pjet1.push_back(jet_px[0]);
      pjet1.push_back(jet_py[0]);
      pjet1.push_back(jet_pz[0]);
      std::vector<float> pjet2;
      pjet2.push_back(jet_px[1]);
      pjet2.push_back(jet_py[1]);
      pjet2.push_back(jet_pz[1]);

      float costheta_reco=fabs(GetCostheta(pjet1));//(fabs(GetCostheta(pjet1))+fabs(GetCostheta(pjet2)))/2.;

      if(fabs(mc_quark_pdg[0])==5) {
	bb_signal -> Fill(costheta_reco);
	if(PreSelection(3,35)==true) {
	  bb_event->Fill(costheta_reco);
	  Eff_b -> Fill(costheta_reco);
	}
	h2_y23ps_costheta->Fill(costheta_parton,mc_quark_ps_y23*jet_R_norm);
	
	for(int i=0; i<5; i++)
	  if(costheta_parton<0.2*(i+1) &&  costheta_parton>0.2*i)  h1_y23ps_costheta_proj[i]->Fill(mc_quark_ps_y23*jet_R_norm);
														       
	// //same at reco level
	// std::vector<float> pjet1;
	// pjet1.push_back(jet_px[0]);
	// pjet1.push_back(jet_py[0]);
	// pjet1.push_back(jet_pz[0]);
	// std::vector<float> pjet2;
	// pjet2.push_back(jet_px[1]);
	// pjet2.push_back(jet_py[1]);
	// pjet2.push_back(jet_pz[1]);
	
	// float costheta_reco=(fabs(GetCostheta(pjet1))+fabs(GetCostheta(pjet2)))/2.;
	
	
	//cuts at reco level to remove radiative return events
	// if(PreSelection(1,35)==false) continue;
	
	h1_y23_ps->Fill(mc_quark_ps_y23*jet_R_norm);
	h1_y23_ps_ISR->Fill(mc_quark_ps_isr_y23*jet_R_norm);
	h1_y23_reco->Fill(y23*jet_R_norm);
      }
      if(fabs(mc_quark_pdg[0])<4) {
	qq_signal -> Fill(costheta_reco);
	if(PreSelection(3,35)==true) {
	  qq_event->Fill(costheta_reco);
	  Eff_q -> Fill(costheta_reco);
	}
      }
      if(fabs(mc_quark_pdg[0])==4) {
	cc_signal -> Fill(costheta_reco);
	if(PreSelection(3,35)==true) {
	  cc_event->Fill(costheta_reco);
	  Eff_c -> Fill(costheta_reco);
	}
      }

    }
  }//end loop
  
  TFile *MyFile = new TFile("output.root","RECREATE");
  MyFile->cd();
  h1_y23_ps->Write();
  h1_y23_ps_ISR->Write();
  h1_y23_reco->Write();
  
  h2_y23ps_ISR->Write();
  h2_y23psISR_ISR->Write();
  h2_y23reco_ISR->Write();
  bb_signal -> Write();
  bb_event -> Write();
  Eff_b -> Divide(bb_signal);
  Eff_b -> Write();

  cc_signal -> Write();
  cc_event -> Write();
  Eff_c -> Divide(cc_signal);
  Eff_c -> Write();

  qq_signal -> Write();
  qq_event -> Write();
  Eff_q -> Divide(qq_signal);
  Eff_q -> Write();
    
  h2_y23ps_costheta->Write();
  h2_y23psISR_costheta->Write();
  h2_y23reco_costheta->Write();
  
  for(int i=0; i<4; i++) {
    h1_y23_ps_signal[i]->Write();
    h1_y23_ps_rad[i]->Write();
  }

  TCanvas *canvas = new TCanvas ("canvas","canvas",800,800);
  for(int i=0; i<4; i++) {
    h1_y23_ps_signal[i]->SetLineColor(4);
    h1_y23_ps_signal[i]->SetLineStyle(1);
    h1_y23_ps_signal[i]->SetLineWidth(1+i);
    h1_y23_ps_signal[i]->DrawNormalized("same");

    h1_y23_ps_rad[i]->SetLineColor(2);
    h1_y23_ps_rad[i]->SetLineStyle(2);
    h1_y23_ps_rad[i]->SetLineWidth(1+i);
    h1_y23_ps_rad[i]->DrawNormalized("same");
  }
  canvas->Write();

  TCanvas *canvas2 = new TCanvas ("canvas2","canvas2",800,800);
  TLegend *leg = new TLegend(0.7,0.6,0.85,0.9);
  for(int i=0; i<5; i++) {
    if(i<3) {
      h1_y23ps_costheta_proj[i]->SetLineColor(1+i);
      h1_y23ps_costheta_proj[i]->SetLineStyle(1);
      h1_y23ps_costheta_proj[i]->SetLineWidth(2);
      h1_y23ps_costheta_proj[i]->DrawNormalized("same");
    } else  if(i<5) {
      h1_y23ps_costheta_proj[i]->SetLineColor(kGray+i-3);
      h1_y23ps_costheta_proj[i]->SetLineStyle(2);
      h1_y23ps_costheta_proj[i]->SetLineWidth(2);
      h1_y23ps_costheta_proj[i]->DrawNormalized("same");
    } else  {
      h1_y23ps_costheta_proj[i]->SetLineColor(1+i);
      h1_y23ps_costheta_proj[i]->SetLineStyle(2);
      h1_y23ps_costheta_proj[i]->SetLineWidth(3);
      h1_y23ps_costheta_proj[i]->DrawNormalized("same");
    }
    if(i==0) leg->AddEntry(TString::Format("h1_y23ps_costheta_%i",i),"costheta>0.0 & costheta<0.2","l");
    if(i==1) leg->AddEntry(TString::Format("h1_y23ps_costheta_%i",i),"costheta>0.2 & costheta<0.4","l");
    if(i==2) leg->AddEntry(TString::Format("h1_y23ps_costheta_%i",i),"costheta>0.4 & costheta<0.6","l");
    if(i==3) leg->AddEntry(TString::Format("h1_y23ps_costheta_%i",i),"costheta>0.6 & costheta<0.8","l");
    if(i==4) leg->AddEntry(TString::Format("h1_y23ps_costheta_%i",i),"costheta>0.8 & costheta<1.0","l");
    if(i==5) leg->AddEntry(TString::Format("h1_y23ps_costheta_%i",i),"costheta>0.5 & costheta<0.6","l");
    if(i==6) leg->AddEntry(TString::Format("h1_y23ps_costheta_%i",i),"costheta>0.6 & costheta<0.7","l");
    if(i==7) leg->AddEntry(TString::Format("h1_y23ps_costheta_%i",i),"costheta>0.7 & costheta<0.8","l");
    if(i==8) leg->AddEntry(TString::Format("h1_y23ps_costheta_%i",i),"costheta>0.8 & costheta<0.9","l");
    if(i==9) leg->AddEntry(TString::Format("h1_y23ps_costheta_%i",i),"costheta>0.9 & costheta<1.0","l");	  
  }
  leg->Draw();
  canvas2->Write();
  
}
  
   

bool observable::PreSelection(int type=0,float Kvcut=25) {
  
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
    
    for(int ipfo=0; ipfo<100; ipfo++) {//jet_pfo_n[ijet]; ipfo++) {
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
  if(neutralPFO_ratio[0]<0.85 && neutralPFO_ratio[1]<0.85) ISR_1=false;
  
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
  // c-quarks QUARKS, no radiative return
  if(type == 3 ) if( bbmass>130 && Kv < Kvcut && ISR_1==false && ISR_2==false && ISR_3==false && (b1mass+b2mass)<100 && (jet_btag[0]<0.4 && jet_ctag[0]<0.25) && (jet_btag[1]<0.4 && jet_ctag[1]<0.25) )  return true;
  

 
  
  return false;
}

bool observable::JetBtag(int ijet) {
  //function for the optimization of the btagging

  double btagv=0;
  if(ijet==0) btagv=btag1;
  if(ijet==1) btagv=btag2;

  if(jet_btag[ijet]<btagv) return false;


  double momvertex=0;

  double mom_x=0, mom_y=0, mom_z=0;
  double e=0;
  double nt=0;
  for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
    for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
      nt++;
      e+=jet_track_E[ijet][ivtx][itrack];
      mom_x+=jet_track_px[ijet][ivtx][itrack];
      mom_y+=jet_track_py[ijet][ivtx][itrack];
      mom_z+=jet_track_pz[ijet][ivtx][itrack];
    }
  }

  double mass = sqrt(pow(e,2) - pow(mom_x,2) -  pow(mom_y,2) - pow(mom_z,2) );
  momvertex= sqrt(pow(mom_x,2) +  pow(mom_y,2) + pow(mom_z,2) );

  if(momvertex<25) return false;


  return true;
}

bool observable::JetCantitag(int ijet) {

  //function for the optimization of the anti c-tagging
  // work in progress!

  double ctagv=0;
  if(ijet==0) ctagv=ctag1;
  if(ijet==1) ctagv=ctag2;

  if(jet_ctag[ijet]>ctagv) return false;


  double momvertex=0;

  double mom_x=0, mom_y=0, mom_z=0;
  double e=0;
  double nt=0;
  for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
    for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
      nt++;
      e+=jet_track_E[ijet][ivtx][itrack];
      mom_x+=jet_track_px[ijet][ivtx][itrack];
      mom_y+=jet_track_py[ijet][ivtx][itrack];
      mom_z+=jet_track_pz[ijet][ivtx][itrack];
    }
  }

  double mass = sqrt(pow(e,2) - pow(mom_x,2) -  pow(mom_y,2) - pow(mom_z,2) );
  momvertex= sqrt(pow(mom_x,2) +  pow(mom_y,2) + pow(mom_z,2) );

  if(momvertex>35) return false;


  return true;
}
