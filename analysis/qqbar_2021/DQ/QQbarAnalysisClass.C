#define QQbarAnalysisClass_cxx
#include "QQbarAnalysisClass.h"
#include "TPad.h"

    
void QQbarAnalysisClass::DQChecks(int n_entries=-1, float Kvcut=35, TString output="test")
{

  InitDQ();

 
  TFile *MyFile = new TFile(TString::Format("DQ_250GeV_%s.root",output.Data()),"RECREATE");
  MyFile->cd();

  
  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

 
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    //cout<<jentry<<endl;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 10000 && jentry % 10000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;
  
 if(PreSelection(0,Kvcut)==false) continue;

	      
    //cout<<"hola 1"<<endl;
    float gamma_e=mc_ISR_E[0]+mc_ISR_E[1];

    bool squark=false;
    int ihisto=-1;
    if(fabs(mc_quark_pdg[0])<4) ihisto=0;
    if(fabs(mc_quark_pdg[0])==4) ihisto=1;
    if(fabs(mc_quark_pdg[0])==5) ihisto=2;
    if(fabs(mc_quark_pdg[0])==3) squark=true;
    if(gamma_e>Kvcut) ihisto+=3;
    if(ihisto<0) {
      cout<<jentry<<" NO QQBAR "<<jet_E[0]<<" "<<mc_quark_pdg[0]<<endl;
      continue;
    }

    //-------------------
    //Photon Initial 2 partons
    for(int i=0; i<2; i++) {
      std::vector< float > anglesmom = CalculateAnglesMom(mc_quark_px[i],mc_quark_py[i],mc_quark_pz[i]);
      h_quark_phi[ihisto]->Fill(anglesmom.at(0));
      h_quark_theta[ihisto]->Fill(anglesmom.at(1));
      h_quark_mom[ihisto]->Fill(anglesmom.at(2));
    }
    //-------------------
    //Photon ISR parton
    for(int i=0; i<2; i++) {
      std::vector< float > anglesmom = CalculateAnglesMom(mc_ISR_px[i],mc_ISR_py[i],mc_ISR_pz[i]);
      float mom=sqrt(pow(mc_ISR_px[i],2)+pow(mc_ISR_py[i],2)+pow(mc_ISR_pz[i],2));
      if(mom>1) {
	h_ISR_phi[ihisto]->Fill(anglesmom.at(0));
	h_ISR_theta[ihisto]->Fill(anglesmom.at(1));
	h_ISR_mom[ihisto]->Fill(anglesmom.at(2));
      }
    }
    //-------------------
    //Photon FSR partons
    int npartons=0;
    for(int i=0; i<mc_quark_ps_n; i++) {
      std::vector< float > anglesmom = CalculateAnglesMom(mc_quark_ps_px[i],mc_quark_ps_py[i],mc_quark_ps_pz[i]);
      if(fabs(mc_quark_ps_pdg[i])!=fabs(mc_quark_pdg[0])) {
	h_QCDFSR_phi[ihisto]->Fill(anglesmom.at(0));
	h_QCDFSR_theta[ihisto]->Fill(anglesmom.at(1));
	h_QCDFSR_mom[ihisto]->Fill(anglesmom.at(2));
	npartons++;
      }
      if(fabs(mc_quark_ps_pdg[i])==fabs(mc_quark_pdg[0])) {
	h_quark_afterps_phi[ihisto]->Fill(anglesmom.at(0));
	h_quark_afterps_theta[ihisto]->Fill(anglesmom.at(1));
	h_quark_afterps_mom[ihisto]->Fill(anglesmom.at(2));
      }
    }
    //cout<<"hola 5"<<endl;
    h_QCDFSR_n[ihisto]->Fill(npartons);

    //cout<<"hola 6"<<endl;

    //-------------------
    //stable particle before the detector
    int nparticle=0;
    int noverlay=0;
    // cout<<mc_stable_n<<endl;
    if(mc_stable_n<10000) {
      for(int i=0; i<mc_stable_n; i++) {
	if(mc_stable_E[i]>0 && mc_stable_E[i]<250) {
	  std::vector< float > anglesmom = CalculateAnglesMom(mc_stable_px[i],mc_stable_py[i],mc_stable_pz[i]);
	  h_particle_phi[ihisto]->Fill(anglesmom.at(0));
	  h_particle_theta[ihisto]->Fill(anglesmom.at(1));
	  h_particle_mom[ihisto]->Fill(anglesmom.at(2));

	  if(mc_stable_isoverlay[i]==1) {
	    h_overlay_phi[ihisto]->Fill(anglesmom.at(0));
	    h_overlay_theta[ihisto]->Fill(anglesmom.at(1));
	    h_overlay_mom[ihisto]->Fill(anglesmom.at(2));
	    noverlay++;
	  }
	  //  cout<<" pdg:"<<mc_stable_pdg[i]<<" px:"<<mc_stable_px[i]<<" py:"<<mc_stable_py[i]<<" pz:"<<mc_stable_pz[i]<<" E:"<<mc_stable_E[i]<<" phi:"<<anglesmom.at(0)<<endl;
	  nparticle++;
	}
      }
    }
    h_particle_n[ihisto]->Fill(nparticle);
    h_overlay_n[ihisto]->Fill(noverlay);

    for(int j=0; j<2; j++) {

      std::vector< float > anglesmomjet = CalculateAnglesMom(jet_px[j],jet_py[j],jet_pz[j]);
      h_Jet_phi[ihisto]->Fill(anglesmomjet.at(0));
      h_Jet_theta[ihisto]->Fill(anglesmomjet.at(1));
      h_Jet_mom[ihisto]->Fill(anglesmomjet.at(2));
      h_Jet_btag[ihisto]->Fill(jet_btag[j]);
      h_Jet_ctag[ihisto]->Fill(jet_ctag[j]);

    }
    
    //-------------------
    //reconstructed PFOs per jet
    int nPFO1=0;
    int nPFOoverlay1=0; 
    int nPFOisr1=0;
    int ntrackprim1=0;
    int ntracksec1[5]={0};
    //jet 2
    int nPFO2=0;
    int nPFOoverlay2=0; 
    int nPFOisr2=0;
    int ntrackprim2=0;
    int ntracksec2[5]={0};

    //-------------------
    //reconstructed vtx / sec tracks per jet
    h_nvtx[ihisto]->Fill(jet_nvtx_j1);
    h_nvtx[ihisto]->Fill(jet_nvtx_j2);
    
    for(int i=0; i<pfo_n; i++) {
      std::vector< float > anglesmom = CalculateAnglesMom(pfo_px[i],pfo_py[i],pfo_pz[i]);
      
      if(pfo_isoverlay[i]==0 && pfo_isisr[i]==0){
	h_PFO_phi[ihisto]->Fill(anglesmom.at(0));
	h_PFO_theta[ihisto]->Fill(anglesmom.at(1));
	h_PFO_mom[ihisto]->Fill(anglesmom.at(2));
	if(pfo_match[i]==0) nPFO1++;
	if(pfo_match[i]==1) nPFO2++;
      }
      
      if(pfo_isoverlay[i]==1) {
	h_PFOoverlay_phi[ihisto]->Fill(anglesmom.at(0));
	h_PFOoverlay_theta[ihisto]->Fill(anglesmom.at(1));
	h_PFOoverlay_mom[ihisto]->Fill(anglesmom.at(2));
	 if(pfo_match[i]==0) nPFOoverlay1++;
	 if(pfo_match[i]==1) nPFOoverlay2++;
      }

      if(pfo_isisr[i]==1) {
	h_PFOisr_phi[ihisto]->Fill(anglesmom.at(0));
	h_PFOisr_theta[ihisto]->Fill(anglesmom.at(1));
	h_PFOisr_mom[ihisto]->Fill(anglesmom.at(2));
	if(pfo_match[i]==0) nPFOisr1++;
	if(pfo_match[i]==1) nPFOisr2++;
      }
    
      if(pfo_ntracks[i]==1 && fabs(pfo_charge[i])!=0 && pfo_vtx[i]>0) {

	if( (ihisto==0 || ihisto==3) && squark==true) {
	  if(fabs(pfo_pdgcheat[i])==321) h_sectrack_mom_K[ihisto]->Fill(anglesmom.at(2));
	  if(fabs(pfo_pdgcheat[i])==211) h_sectrack_mom_Pi[ihisto]->Fill(anglesmom.at(2));
	  if(fabs(pfo_pdgcheat[i])==2212) h_sectrack_mom_p[ihisto]->Fill(anglesmom.at(2));
	}
	if( ihisto!=0 && ihisto!=3) {
	  if(fabs(pfo_pdgcheat[i])==321) h_sectrack_mom_K[ihisto]->Fill(anglesmom.at(2));
	  if(fabs(pfo_pdgcheat[i])==211) h_sectrack_mom_Pi[ihisto]->Fill(anglesmom.at(2));
	  if(fabs(pfo_pdgcheat[i])==2212) h_sectrack_mom_p[ihisto]->Fill(anglesmom.at(2));
	}

	h_sectrack_phi[ihisto]->Fill(anglesmom.at(0));
	h_sectrack_theta[ihisto]->Fill(anglesmom.at(1));
	h_sectrack_mom[ihisto]->Fill(anglesmom.at(2));
	h_sectrack_d0[ihisto]->Fill(pfo_d0[i]);
	h_sectrack_z0[ihisto]->Fill(pfo_z0[i]);
	h_sectrack_d0error[ihisto]->Fill(pfo_d0error[i]);
	h_sectrack_z0error[ihisto]->Fill(pfo_z0error[i]);
	if(pfo_match[i]==0) ntracksec1[pfo_vtx[i]]++;
	if(pfo_match[i]==1) ntracksec2[pfo_vtx[i]]++;
      }

      if(pfo_ntracks[i]==1 && fabs(pfo_charge[i])!=0 && pfo_vtx[i]==0) {

	if( (ihisto==0 || ihisto==3) && squark==true) {
	  if(fabs(pfo_pdgcheat[i])==321) h_primtrack_mom_K[ihisto]->Fill(anglesmom.at(2));
	  if(fabs(pfo_pdgcheat[i])==211) h_primtrack_mom_Pi[ihisto]->Fill(anglesmom.at(2));
	  if(fabs(pfo_pdgcheat[i])==2212) h_primtrack_mom_p[ihisto]->Fill(anglesmom.at(2));
	}
	if( ihisto!=0 && ihisto!=3) {
	  if(fabs(pfo_pdgcheat[i])==321) h_primtrack_mom_K[ihisto]->Fill(anglesmom.at(2));
	  if(fabs(pfo_pdgcheat[i])==211) h_primtrack_mom_Pi[ihisto]->Fill(anglesmom.at(2));
	  if(fabs(pfo_pdgcheat[i])==2212) h_primtrack_mom_p[ihisto]->Fill(anglesmom.at(2));
	}

	h_primtrack_phi[ihisto]->Fill(anglesmom.at(0));
	h_primtrack_theta[ihisto]->Fill(anglesmom.at(1));
	h_primtrack_mom[ihisto]->Fill(anglesmom.at(2));
	h_primtrack_d0[ihisto]->Fill(pfo_d0[i]);
	h_primtrack_z0[ihisto]->Fill(pfo_z0[i]);
	h_primtrack_d0error[ihisto]->Fill(pfo_d0error[i]);
	h_primtrack_z0error[ihisto]->Fill(pfo_z0error[i]);
	if(pfo_match[i]==0) ntrackprim1++;
	if(pfo_match[i]==1) ntrackprim2++;
      }

      
    }

            
    h_PFO_njet[ihisto]->Fill(nPFO1);
    h_PFOoverlay_njet[ihisto]->Fill(nPFO1+nPFOisr1+nPFOoverlay1);
    h_PFOisr_njet[ihisto]->Fill(nPFO1+nPFOisr1);
    for(int i=0; i<5; i++) h_vtx_ntrack[ihisto]->Fill(ntracksec1[i]);
    h_nprimtrack[ihisto]->Fill(ntrackprim1);

    h_PFO_njet[ihisto]->Fill(nPFO2);
    h_PFOoverlay_njet[ihisto]->Fill(nPFO2+nPFOisr2+nPFOoverlay2);
    h_PFOisr_njet[ihisto]->Fill(nPFO2+nPFOisr2);
    for(int i=0; i<5; i++) h_vtx_ntrack[ihisto]->Fill(ntracksec2[i]);
    h_nprimtrack[ihisto]->Fill(ntrackprim2);

  }
  
  TDirectory *cdtof = MyFile->mkdir("MC");
  cdtof->cd();
  WriteHistosMC();
  TDirectory *cdtof2 = MyFile->mkdir("reco");
  cdtof2->cd();
  WriteHistosPFO();
  WriteHistosTrack();
  WriteHistosJet();
  WriteHistosTrackID();
  
}

 



