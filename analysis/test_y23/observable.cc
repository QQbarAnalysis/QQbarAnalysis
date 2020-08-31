// A. Irles
// irles @ lal.in2p3.fr
// 30 March 2020

#define observable_cxx
#include "observable.h"
#include "TPad.h"

void observable::AnalysisR3_cambridge(int n_entries=-1)
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
	if( mc_quark_ps_njets_ycut_cambridge[iycut]==3 ) njets_condition=true;

	//parton shower level
	if(njets_condition==true) { // should we save events with EXACTLY 3 jets... or should we save events with >2 jets ???
	  R3b_ps[0][iycut]++; //step 0, no cuts
	  if(PreSelection(1,35)==true) R3b_ps[1][iycut]++; //step 1 two hadronic jets selection
	  if(PreSelection(2,35)==true) R3b_ps[2][iycut]++; //step 2 two b-jets selection
	  if(PreSelection(2,35)==true && costheta_reco<0.8) R3b_ps[3][iycut]++; //step 2 two b-jets selection but excluding very forward regions
	}

	njets_condition=false;
	if( njets_ycut_cambridge[iycut] == 3 ) njets_condition=true;

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
	if(mc_quark_ps_njets_ycut_cambridge[iycut]==3 ) njets_condition=true;

	//parton shower level
	if(njets_condition==true) { // should we save events with EXACTLY 3 jets... or should we save events with >2 jets ???
	  R3l_ps[0][iycut]++; //step 0, no cuts
	  if(PreSelection(1,35)==true) R3l_ps[1][iycut]++; //step 1 two hadronic jets selection
	  if(PreSelection(3,35)==true) R3l_ps[2][iycut]++; //step 2 two uds-jets selection
	  if(PreSelection(3,35)==true && costheta_reco<0.8) R3l_ps[3][iycut]++; //step 2 two uds-jets selection but excluding very forward regions
	}

	njets_condition=false;
	if(njets_ycut_cambridge[iycut]==3 ) njets_condition=true;

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
  TString filename="R3_cambridge_signal.root";
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
