   //MC
  TH1F* h_quark_phi[10];
  TH1F* h_quark_theta[10];
  TH1F* h_quark_mom[10];
  
  TH1F* h_ISR_phi[10];
  TH1F* h_ISR_theta[10];
  TH1F* h_ISR_mom[10];

  TH1F* h_quark_afterps_phi[10];
  TH1F* h_quark_afterps_theta[10];
  TH1F* h_quark_afterps_mom[10];
  
  TH1F* h_QCDFSR_phi[10];
  TH1F* h_QCDFSR_theta[10];
  TH1F* h_QCDFSR_mom[10];
  TH1F* h_QCDFSR_n[10];

  TH1F* h_particle_phi[10];
  TH1F* h_particle_theta[10];
  TH1F* h_particle_mom[10];
  TH1F* h_particle_n[10];

  TH1F* h_overlay_phi[10];
  TH1F* h_overlay_theta[10];
  TH1F* h_overlay_mom[10];
  TH1F* h_overlay_n[10];

  //tracks & PFOs
  TH1F* h_nvtx[10];
  TH1F* h_vtx_ntrack[10]; 
  TH1F* h_nprimtrack[10]; 

  TH1F* h_primtrack_phi[10]; 
  TH1F* h_primtrack_theta[10];
  TH1F* h_primtrack_mom[10];
  TH1F* h_primtrack_d0[10];
  TH1F* h_primtrack_z0[10];
  TH1F* h_primtrack_z0error[10];
  TH1F* h_primtrack_d0error[10];

  TH1F* h_sectrack_phi[10]; 
  TH1F* h_sectrack_theta[10];
  TH1F* h_sectrack_mom[10];
  TH1F* h_sectrack_d0[10];
  TH1F* h_sectrack_z0[10];
  TH1F* h_sectrack_z0error[10];
  TH1F* h_sectrack_d0error[10];

  TH1F* h_primtrack_mom_K[10];
  TH1F* h_primtrack_mom_Pi[10];
  TH1F* h_primtrack_mom_p[10];

  TH1F* h_sectrack_mom_K[10];
  TH1F* h_sectrack_mom_Pi[10];
  TH1F* h_sectrack_mom_p[10];

  TH1F* h_PFO_phi[10]; 
  TH1F* h_PFO_theta[10];
  TH1F* h_PFO_mom[10];
  TH1F* h_PFO_njet[10];

  TH1F* h_PFOoverlay_phi[10]; 
  TH1F* h_PFOoverlay_theta[10];
  TH1F* h_PFOoverlay_mom[10];
  TH1F* h_PFOoverlay_njet[10];

  TH1F* h_PFOisr_phi[10]; 
  TH1F* h_PFOisr_theta[10];
  TH1F* h_PFOisr_mom[10];
  TH1F* h_PFOisr_njet[10];

  TH1F* h_Jet_phi[10]; 
  TH1F* h_Jet_theta[10];
  TH1F* h_Jet_mom[10];
  TH1F* h_Jet_btag[10];
  TH1F* h_Jet_ctag[10];


void InitHistosMC(std::vector<TString> name) {

  for(unsigned int i=0; i<name.size(); i++) {    
    h_quark_phi[i] = new TH1F("quark_phi_"+name.at(i),"quark_phi_"+name.at(i),100,0,2.*TMath::Pi());
    h_quark_theta[i] = new TH1F("quark_theta_"+name.at(i),"quark_theta_"+name.at(i),100,0,TMath::Pi());
    h_quark_mom[i] = new TH1F("quark_mom_"+name.at(i),"quark_mom_"+name.at(i),251,-0.5,250.5);

    h_ISR_phi[i] = new TH1F("ISR_phi_"+name.at(i),"ISR_phi_"+name.at(i),100,0,2.*TMath::Pi());
    h_ISR_theta[i] = new TH1F("ISR_theta_"+name.at(i),"ISR_theta_"+name.at(i),100,0,TMath::Pi());
    h_ISR_mom[i] = new TH1F("ISR_mom_"+name.at(i),"ISR_mom_"+name.at(i),251,-0.5,250.5);

    h_quark_afterps_phi[i] = new TH1F("quark_afterps_phi_"+name.at(i),"quark_afterps_phi_"+name.at(i),100,0,2.*TMath::Pi());
    h_quark_afterps_theta[i] = new TH1F("quark_afterps_theta_"+name.at(i),"quark_afterps_theta_"+name.at(i),100,0,TMath::Pi());
    h_quark_afterps_mom[i] = new TH1F("quark_afterps_mom_"+name.at(i),"quark_afterps_mom_"+name.at(i),251,-0.5,250.5);
    
    h_QCDFSR_phi[i] = new TH1F("QCDFSR_phi_"+name.at(i),"QCDFSR_phi_"+name.at(i),100,0,2.*TMath::Pi());
    h_QCDFSR_theta[i] = new TH1F("QCDFSR_theta_"+name.at(i),"QCDFSR_theta_"+name.at(i),100,0,TMath::Pi());
    h_QCDFSR_mom[i] = new TH1F("QCDFSR_mom_"+name.at(i),"QCDFSR_mom_"+name.at(i),251,-0.5,250.5);
    h_QCDFSR_n[i] = new TH1F("QCDFSR_n_"+name.at(i),"QCDFSR_n_"+name.at(i),100,-0.5,99.5);

    h_particle_phi[i] = new TH1F("particle_phi_"+name.at(i),"particle_phi_"+name.at(i),100,0,2.*TMath::Pi());
    h_particle_theta[i] = new TH1F("particle_theta_"+name.at(i),"particle_theta_"+name.at(i),100,0,TMath::Pi());
    h_particle_mom[i] = new TH1F("particle_mom_"+name.at(i),"particle_mom_"+name.at(i),251,-0.5,250.5);
    h_particle_n[i] = new TH1F("particle_n_"+name.at(i),"particle_n_"+name.at(i),1000,-0.5,999.5);

    h_overlay_phi[i] = new TH1F("overlay_phi_"+name.at(i),"overlay_phi_"+name.at(i),100,0,2.*TMath::Pi());
    h_overlay_theta[i] = new TH1F("overlay_theta_"+name.at(i),"overlay_theta_"+name.at(i),100,0,TMath::Pi());
    h_overlay_mom[i] = new TH1F("overlay_mom_"+name.at(i),"overlay_mom_"+name.at(i),251,-0.5,250.5);
    h_overlay_n[i] = new TH1F("overlay_n_"+name.at(i),"overlay_n_"+name.at(i),1000,-0.5,999.5);   
  }
  
}


// ** PFOs
void InitHistosPFO(std::vector<TString> name) {

  for(unsigned int i=0; i<name.size(); i++) {
    h_PFO_phi[i] = new TH1F("PFO_phi_"+name.at(i),"PFO_phi_"+name.at(i),100,0,2.*TMath::Pi());
    h_PFO_theta[i] = new TH1F("PFO_theta_"+name.at(i),"PFO_theta_"+name.at(i),100,0,TMath::Pi());
    h_PFO_mom[i] = new TH1F("PFO_mom_"+name.at(i),"PFO_mom_"+name.at(i),251,-0.5,250.5);
    h_PFO_njet[i] = new TH1F("PFO_njet_"+name.at(i),"PFO_njet_"+name.at(i),150,-0.5,149.5);

    h_PFOoverlay_phi[i] = new TH1F("PFOoverlay_phi_"+name.at(i),"PFOoverlay_phi_"+name.at(i),100,0,2.*TMath::Pi());
    h_PFOoverlay_theta[i] = new TH1F("PFOoverlay_theta_"+name.at(i),"PFOoverlay_theta_"+name.at(i),100,0,TMath::Pi());
    h_PFOoverlay_mom[i] = new TH1F("PFOoverlay_mom_"+name.at(i),"PFOoverlay_mom_"+name.at(i),251,-0.5,250.5);
    h_PFOoverlay_njet[i] = new TH1F("PFOoverlay_njet_"+name.at(i),"PFOoverlay_njet_"+name.at(i),150,-0.5,149.5);

    h_PFOisr_phi[i] = new TH1F("PFOisr_phi_"+name.at(i),"PFOisr_phi_"+name.at(i),100,0,2.*TMath::Pi());
    h_PFOisr_theta[i] = new TH1F("PFOisr_theta_"+name.at(i),"PFOisr_theta_"+name.at(i),100,0,TMath::Pi());
    h_PFOisr_mom[i] = new TH1F("PFOisr_mom_"+name.at(i),"PFOisr_mom_"+name.at(i),251,-0.5,250.5);
    h_PFOisr_njet[i] = new TH1F("PFOisr_njet_"+name.at(i),"PFOisr_njet_"+name.at(i),150,-0.5,149.5);  
  }
  
}

// ** Jets
void InitHistosJet(std::vector<TString> name) {

  for(unsigned int i=0; i<name.size(); i++) {
    h_Jet_phi[i] = new TH1F("Jet_phi_"+name.at(i),"Jet_phi_"+name.at(i),100,0,2.*TMath::Pi());
    h_Jet_theta[i] = new TH1F("Jet_theta_"+name.at(i),"Jet_theta_"+name.at(i),100,0,TMath::Pi());
    h_Jet_mom[i] = new TH1F("Jet_mom_"+name.at(i),"Jet_mom_"+name.at(i),251,-0.5,250.5);
    h_Jet_btag[i] = new TH1F("Jet_btag_"+name.at(i),"Jet_btag_"+name.at(i),1000,0,1);
    h_Jet_ctag[i] = new TH1F("Jet_ctag_"+name.at(i),"Jet_ctag_"+name.at(i),1000,0,1);
  }
  
}

void InitHistosTrack(std::vector<TString> name) {

  for(unsigned int i=0; i<name.size(); i++) {
    h_nvtx[i] = new TH1F("nvtx_"+name.at(i),"nvtx_"+name.at(i),10,-0.5,9.5);
    h_vtx_ntrack[i] = new TH1F("vtx_ntrack_"+name.at(i),"vtx_ntrack_"+name.at(i),15,-0.5,14.5);
    h_nprimtrack[i] = new TH1F("nprimtrack_"+name.at(i),"nprimtrack_"+name.at(i),15,-0.5,14.5);

    h_sectrack_phi[i] = new TH1F("sectrack_phi_"+name.at(i),"sectrack_phi_"+name.at(i),100,0,2.*TMath::Pi());
    h_sectrack_theta[i] = new TH1F("sectrack_theta_"+name.at(i),"sectrack_theta_"+name.at(i),100,0,TMath::Pi());
    h_sectrack_mom[i] = new TH1F("sectrack_mom_"+name.at(i),"sectrack_mom_"+name.at(i),251,-0.5,250.5);
    h_sectrack_d0[i] = new TH1F("sectrack_d0_"+name.at(i),"sectrack_d0_"+name.at(i),400,-20,20);
    h_sectrack_z0[i] = new TH1F("sectrack_z0_"+name.at(i),"sectrack_z0_"+name.at(i),400,-20,20);
    h_sectrack_d0error[i] = new TH1F("sectrack_d0error_"+name.at(i),"sectrack_d0error_"+name.at(i),4000,0,1);
    h_sectrack_z0error[i] = new TH1F("sectrack_z0error_"+name.at(i),"sectrack_z0error_"+name.at(i),4000,0,1);
  
    h_primtrack_phi[i] = new TH1F("primtrack_phi_"+name.at(i),"primtrack_phi_"+name.at(i),100,0,2.*TMath::Pi());
    h_primtrack_theta[i] = new TH1F("primtrack_theta_"+name.at(i),"primtrack_theta_"+name.at(i),100,0,TMath::Pi());
    h_primtrack_mom[i] = new TH1F("primtrack_mom_"+name.at(i),"primtrack_mom_"+name.at(i),251,-0.5,250.5);
    h_primtrack_d0[i] = new TH1F("primtrack_d0_"+name.at(i),"primtrack_d0_"+name.at(i),400,-20,20);
    h_primtrack_z0[i] = new TH1F("primtrack_z0_"+name.at(i),"primtrack_z0_"+name.at(i),400,-20,20);
    h_primtrack_d0error[i] = new TH1F("primtrack_d0error_"+name.at(i),"primtrack_d0error_"+name.at(i),4000,0,1);
    h_primtrack_z0error[i] = new TH1F("primtrack_z0error_"+name.at(i),"primtrack_z0error_"+name.at(i),4000,0,1);

    
  }
}

// ** tracks/ per particle type

void InitHistosTrackID(std::vector<TString> name) {

  for(unsigned int i=0; i<name.size(); i++) {
 
    h_sectrack_mom_K[i] = new TH1F("sectrack_mom_K_"+name.at(i),"sectrack_mom_K_"+name.at(i),100,0,100);
    h_sectrack_mom_Pi[i] = new TH1F("sectrack_mom_Pi_"+name.at(i),"sectrack_mom_Pi_"+name.at(i),100,0,100);
    h_sectrack_mom_p[i] = new TH1F("sectrack_mom_p_"+name.at(i),"sectrack_mom_p_"+name.at(i),100,0,100);
  
    h_primtrack_mom_K[i] = new TH1F("primtrack_mom_K_"+name.at(i),"primtrack_mom_K_"+name.at(i),100,0,100);
    h_primtrack_mom_Pi[i] = new TH1F("primtrack_mom_Pi_"+name.at(i),"primtrack_mom_Pi_"+name.at(i),100,0,100);
    h_primtrack_mom_p[i] = new TH1F("primtrack_mom_p_"+name.at(i),"primtrack_mom_p_"+name.at(i),100,0,100);
    
  }
}


void InitDQ() {

  std::vector<TString> name;
  name.push_back("uds");
  name.push_back("c");
  name.push_back("b");
  name.push_back("uds_rad");
  name.push_back("c_rad");
  name.push_back("b_rad");
  name.push_back("all");
  name.push_back("signal");
  name.push_back("rad");

  InitHistosMC(name);
  InitHistosTrack(name);
  InitHistosTrackID(name);
  InitHistosPFO(name);
  InitHistosJet(name);
}

// ***************** MC

void WriteHistosMC() {

  for(int i=0; i<6; i++) {
   
    h_quark_phi[6]->Add(h_quark_phi[i]);
    h_quark_theta[6]->Add(h_quark_theta[i]);
    h_quark_mom[6]->Add(h_quark_mom[i]);
    
    h_ISR_phi[6]->Add(h_ISR_phi[i]);
    h_ISR_theta[6]->Add(h_ISR_theta[i]);
    h_ISR_mom[6]->Add(h_ISR_mom[i]);

    h_quark_afterps_phi[6]->Add(h_quark_afterps_phi[i]);
    h_quark_afterps_theta[6]->Add(h_quark_afterps_theta[i]);
    h_quark_afterps_mom[6]->Add(h_quark_afterps_mom[i]);

    h_QCDFSR_phi[6]->Add(h_QCDFSR_phi[i]);
    h_QCDFSR_theta[6]->Add(h_QCDFSR_theta[i]);
    h_QCDFSR_mom[6]->Add(h_QCDFSR_mom[i]);
    h_QCDFSR_n[6]->Add(h_QCDFSR_n[i]);

    h_particle_phi[6]->Add(h_particle_phi[i]);
    h_particle_theta[6]->Add(h_particle_theta[i]);
    h_particle_mom[6]->Add(h_particle_mom[i]);
    h_particle_n[6]->Add(h_particle_n[i]);

    h_overlay_phi[6]->Add(h_overlay_phi[i]);
    h_overlay_theta[6]->Add(h_overlay_theta[i]);
    h_overlay_mom[6]->Add(h_overlay_mom[i]);
    h_overlay_n[6]->Add(h_overlay_n[i]);

  }

  for(int i=0; i<3; i++) {
   
    h_quark_phi[7]->Add(h_quark_phi[i]);
    h_quark_theta[7]->Add(h_quark_theta[i]);
    h_quark_mom[7]->Add(h_quark_mom[i]);
    
    h_ISR_phi[7]->Add(h_ISR_phi[i]);
    h_ISR_theta[7]->Add(h_ISR_theta[i]);
    h_ISR_mom[7]->Add(h_ISR_mom[i]);

    h_quark_afterps_phi[7]->Add(h_quark_afterps_phi[i]);
    h_quark_afterps_theta[7]->Add(h_quark_afterps_theta[i]);
    h_quark_afterps_mom[7]->Add(h_quark_afterps_mom[i]);

    h_QCDFSR_phi[7]->Add(h_QCDFSR_phi[i]);
    h_QCDFSR_theta[7]->Add(h_QCDFSR_theta[i]);
    h_QCDFSR_mom[7]->Add(h_QCDFSR_mom[i]);
    h_QCDFSR_n[7]->Add(h_QCDFSR_n[i]);

    h_particle_phi[7]->Add(h_particle_phi[i]);
    h_particle_theta[7]->Add(h_particle_theta[i]);
    h_particle_mom[7]->Add(h_particle_mom[i]);
    h_particle_n[7]->Add(h_particle_n[i]);

    h_overlay_phi[7]->Add(h_overlay_phi[i]);
    h_overlay_theta[7]->Add(h_overlay_theta[i]);
    h_overlay_mom[7]->Add(h_overlay_mom[i]);
    h_overlay_n[7]->Add(h_overlay_n[i]);


  }

  for(int i=3; i<6; i++) {
   
    h_quark_phi[8]->Add(h_quark_phi[i]);
    h_quark_theta[8]->Add(h_quark_theta[i]);
    h_quark_mom[8]->Add(h_quark_mom[i]);
    
    h_ISR_phi[8]->Add(h_ISR_phi[i]);
    h_ISR_theta[8]->Add(h_ISR_theta[i]);
    h_ISR_mom[8]->Add(h_ISR_mom[i]);

    h_quark_afterps_phi[8]->Add(h_quark_afterps_phi[i]);
    h_quark_afterps_theta[8]->Add(h_quark_afterps_theta[i]);
    h_quark_afterps_mom[8]->Add(h_quark_afterps_mom[i]);

    h_QCDFSR_phi[8]->Add(h_QCDFSR_phi[i]);
    h_QCDFSR_theta[8]->Add(h_QCDFSR_theta[i]);
    h_QCDFSR_mom[8]->Add(h_QCDFSR_mom[i]);
    h_QCDFSR_n[8]->Add(h_QCDFSR_n[i]);

    h_particle_phi[8]->Add(h_particle_phi[i]);
    h_particle_theta[8]->Add(h_particle_theta[i]);
    h_particle_mom[8]->Add(h_particle_mom[i]);
    h_particle_n[8]->Add(h_particle_n[i]);

    h_overlay_phi[8]->Add(h_overlay_phi[i]);
    h_overlay_theta[8]->Add(h_overlay_theta[i]);
    h_overlay_mom[8]->Add(h_overlay_mom[i]);
    h_overlay_n[8]->Add(h_overlay_n[i]);

  }

  for(int i=0; i<9; i++) {
   
    h_quark_phi[i]->Write();
    h_quark_theta[i]->Write();
    h_quark_mom[i]->Write();

    h_ISR_phi[i]->Write();
    h_ISR_theta[i]->Write();
    h_ISR_mom[i]->Write();

    h_quark_afterps_phi[i]->Write();
    h_quark_afterps_theta[i]->Write();
    h_quark_afterps_mom[i]->Write();
    
    h_QCDFSR_phi[i]->Write();
    h_QCDFSR_theta[i]->Write();
    h_QCDFSR_mom[i]->Write();
    h_QCDFSR_n[i]->Write();

    h_particle_phi[i]->Write();
    h_particle_theta[i]->Write();
    h_particle_mom[i]->Write();
    h_particle_n[i]->Write();

    h_overlay_phi[i]->Write();
    h_overlay_theta[i]->Write();
    h_overlay_mom[i]->Write();
    h_overlay_n[i]->Write();
  }
  
}


void WriteHistosPFO() {

  for(int i=0; i<6; i++) {
    h_PFO_phi[6]->Add(h_PFO_phi[i]); 
    h_PFO_theta[6]->Add(h_PFO_theta[i]);
    h_PFO_mom[6]->Add(h_PFO_mom[i]);
    h_PFO_njet[6]->Add(h_PFO_njet[i]);

    h_PFOoverlay_phi[6]->Add(h_PFOoverlay_phi[i]); 
    h_PFOoverlay_theta[6]->Add(h_PFOoverlay_theta[i]);
    h_PFOoverlay_mom[6]->Add(h_PFOoverlay_mom[i]);
    h_PFOoverlay_njet[6]->Add(h_PFOoverlay_njet[i]);

    h_PFOisr_phi[6]->Add(h_PFOisr_phi[i]); 
    h_PFOisr_theta[6]->Add(h_PFOisr_theta[i]);
    h_PFOisr_mom[6]->Add(h_PFOisr_mom[i]);
    h_PFOisr_njet[6]->Add(h_PFOisr_njet[i]);
  }

  for(int i=0; i<3; i++) {
    h_PFO_phi[7]->Add(h_PFO_phi[i]); 
    h_PFO_theta[7]->Add(h_PFO_theta[i]);
    h_PFO_mom[7]->Add(h_PFO_mom[i]);
    h_PFO_njet[7]->Add(h_PFO_njet[i]);

    h_PFOoverlay_phi[7]->Add(h_PFOoverlay_phi[i]); 
    h_PFOoverlay_theta[7]->Add(h_PFOoverlay_theta[i]);
    h_PFOoverlay_mom[7]->Add(h_PFOoverlay_mom[i]);
    h_PFOoverlay_njet[7]->Add(h_PFOoverlay_njet[i]);

    h_PFOisr_phi[7]->Add(h_PFOisr_phi[i]); 
    h_PFOisr_theta[7]->Add(h_PFOisr_theta[i]);
    h_PFOisr_mom[7]->Add(h_PFOisr_mom[i]);
    h_PFOisr_njet[7]->Add(h_PFOisr_njet[i]);
    
  }

  for(int i=3; i<6; i++) {
    h_PFO_phi[8]->Add(h_PFO_phi[i]); 
    h_PFO_theta[8]->Add(h_PFO_theta[i]);
    h_PFO_mom[8]->Add(h_PFO_mom[i]);
    h_PFO_njet[8]->Add(h_PFO_njet[i]);

    h_PFOoverlay_phi[8]->Add(h_PFOoverlay_phi[i]); 
    h_PFOoverlay_theta[8]->Add(h_PFOoverlay_theta[i]);
    h_PFOoverlay_mom[8]->Add(h_PFOoverlay_mom[i]);
    h_PFOoverlay_njet[8]->Add(h_PFOoverlay_njet[i]);

    h_PFOisr_phi[8]->Add(h_PFOisr_phi[i]); 
    h_PFOisr_theta[8]->Add(h_PFOisr_theta[i]);
    h_PFOisr_mom[8]->Add(h_PFOisr_mom[i]);
    h_PFOisr_njet[8]->Add(h_PFOisr_njet[i]); 
    
  }

  for(int i=0; i<9; i++) {
    h_PFO_phi[i]->Write(); 
    h_PFO_theta[i]->Write();
    h_PFO_mom[i]->Write();
    h_PFO_njet[i]->Write();

    h_PFOoverlay_phi[i]->Write(); 
    h_PFOoverlay_theta[i]->Write();
    h_PFOoverlay_mom[i]->Write();
    h_PFOoverlay_njet[i]->Write();

    h_PFOisr_phi[i]->Write(); 
    h_PFOisr_theta[i]->Write();
    h_PFOisr_mom[i]->Write();
    h_PFOisr_njet[i]->Write();
  }
  
}

void WriteHistosTrack() {

  for(int i=0; i<6; i++) {
    
    h_nvtx[6]->Add(h_nvtx[i]);
    h_vtx_ntrack[6]->Add(h_vtx_ntrack[i]);
    h_nprimtrack[6]->Add(h_nprimtrack[i]);

    h_sectrack_phi[6]->Add(h_sectrack_phi[i]); 
    h_sectrack_theta[6]->Add(h_sectrack_theta[i]);
    h_sectrack_mom[6]->Add(h_sectrack_mom[i]);
    h_sectrack_d0[6]->Add(h_sectrack_d0[i]);
    h_sectrack_z0[6]->Add(h_sectrack_z0[i]);
    h_sectrack_d0error[6]->Add(h_sectrack_d0error[i]);
    h_sectrack_z0error[6]->Add(h_sectrack_z0error[i]);
    
    h_primtrack_phi[6]->Add(h_primtrack_phi[i]); 
    h_primtrack_theta[6]->Add(h_primtrack_theta[i]);
    h_primtrack_mom[6]->Add(h_primtrack_mom[i]);
    h_primtrack_d0[6]->Add(h_primtrack_d0[i]);
    h_primtrack_z0[6]->Add(h_primtrack_z0[i]);
    h_primtrack_d0error[6]->Add(h_primtrack_d0error[i]);
    h_primtrack_z0error[6]->Add(h_primtrack_z0error[i]);

  }

  for(int i=0; i<3; i++) {
    
    h_nvtx[7]->Add(h_nvtx[i]);
    h_vtx_ntrack[7]->Add(h_vtx_ntrack[i]);
    h_nprimtrack[7]->Add(h_nprimtrack[i]);

    h_sectrack_phi[7]->Add(h_sectrack_phi[i]); 
    h_sectrack_theta[7]->Add(h_sectrack_theta[i]);
    h_sectrack_mom[7]->Add(h_sectrack_mom[i]);
    h_sectrack_d0[7]->Add(h_sectrack_d0[i]);
    h_sectrack_z0[7]->Add(h_sectrack_z0[i]);
    h_sectrack_d0error[7]->Add(h_sectrack_d0error[i]);
    h_sectrack_z0error[7]->Add(h_sectrack_z0error[i]);
    
    h_primtrack_phi[7]->Add(h_primtrack_phi[i]); 
    h_primtrack_theta[7]->Add(h_primtrack_theta[i]);
    h_primtrack_mom[7]->Add(h_primtrack_mom[i]);
    h_primtrack_d0[7]->Add(h_primtrack_d0[i]);
    h_primtrack_z0[7]->Add(h_primtrack_z0[i]);
    h_primtrack_d0error[7]->Add(h_primtrack_d0error[i]);
    h_primtrack_z0error[7]->Add(h_primtrack_z0error[i]);

  }

  for(int i=3; i<6; i++) {
    
    h_nvtx[8]->Add(h_nvtx[i]);
    h_vtx_ntrack[8]->Add(h_vtx_ntrack[i]);
    h_nprimtrack[8]->Add(h_nprimtrack[i]);

    h_sectrack_phi[8]->Add(h_sectrack_phi[i]); 
    h_sectrack_theta[8]->Add(h_sectrack_theta[i]);
    h_sectrack_mom[8]->Add(h_sectrack_mom[i]);
    h_sectrack_d0[8]->Add(h_sectrack_d0[i]);
    h_sectrack_z0[8]->Add(h_sectrack_z0[i]);
    h_sectrack_d0error[8]->Add(h_sectrack_d0error[i]);
    h_sectrack_z0error[8]->Add(h_sectrack_z0error[i]);
    
    h_primtrack_phi[8]->Add(h_primtrack_phi[i]); 
    h_primtrack_theta[8]->Add(h_primtrack_theta[i]);
    h_primtrack_mom[8]->Add(h_primtrack_mom[i]);
    h_primtrack_d0[8]->Add(h_primtrack_d0[i]);
    h_primtrack_z0[8]->Add(h_primtrack_z0[i]);
    h_primtrack_d0error[8]->Add(h_primtrack_d0error[i]);
    h_primtrack_z0error[8]->Add(h_primtrack_z0error[i]);

  }
  
  for(int i=0; i<9; i++) {
    h_nvtx[i]->Write();
    h_vtx_ntrack[i]->Write();
    h_nprimtrack[i]->Write();

    h_sectrack_phi[i]->Write(); 
    h_sectrack_theta[i]->Write();
    h_sectrack_mom[i]->Write();
    h_sectrack_d0[i]->Write();
    h_sectrack_z0[i]->Write();
    h_sectrack_d0error[i]->Write();
    h_sectrack_z0error[i]->Write();

    h_primtrack_phi[i]->Write(); 
    h_primtrack_theta[i]->Write();
    h_primtrack_mom[i]->Write();
    h_primtrack_d0[i]->Write();
    h_primtrack_z0[i]->Write();
    h_primtrack_d0error[i]->Write();
    h_primtrack_z0error[i]->Write();
  }
}

void WriteHistosTrackID() {

  for(int i=0; i<6; i++) {
    
    h_sectrack_mom_K[6]->Add(h_sectrack_mom_K[i]); 
    h_sectrack_mom_Pi[6]->Add(h_sectrack_mom_Pi[i]);
    h_sectrack_mom_p[6]->Add(h_sectrack_mom_p[i]);

    h_primtrack_mom_K[6]->Add(h_primtrack_mom_K[i]); 
    h_primtrack_mom_Pi[6]->Add(h_primtrack_mom_Pi[i]);
    h_primtrack_mom_p[6]->Add(h_primtrack_mom_p[i]);

  }

  for(int i=0; i<3; i++) {
    h_sectrack_mom_K[7]->Add(h_sectrack_mom_K[i]); 
    h_sectrack_mom_Pi[7]->Add(h_sectrack_mom_Pi[i]);
    h_sectrack_mom_p[7]->Add(h_sectrack_mom_p[i]);
     
    h_primtrack_mom_K[7]->Add(h_primtrack_mom_K[i]); 
    h_primtrack_mom_Pi[7]->Add(h_primtrack_mom_Pi[i]);
    h_primtrack_mom_p[7]->Add(h_primtrack_mom_p[i]);

  }

  for(int i=3; i<6; i++) {
 
    h_sectrack_mom_K[8]->Add(h_sectrack_mom_K[i]); 
    h_sectrack_mom_Pi[8]->Add(h_sectrack_mom_Pi[i]);
    h_sectrack_mom_p[8]->Add(h_sectrack_mom_p[i]);
      
    h_primtrack_mom_K[8]->Add(h_primtrack_mom_K[i]); 
    h_primtrack_mom_Pi[8]->Add(h_primtrack_mom_Pi[i]);
    h_primtrack_mom_p[8]->Add(h_primtrack_mom_p[i]);
  }
  
  for(int i=0; i<9; i++) {
    h_sectrack_mom_K[i]->Write(); 
    h_sectrack_mom_Pi[i]->Write();
    h_sectrack_mom_p[i]->Write();

    h_primtrack_mom_K[i]->Write(); 
    h_primtrack_mom_Pi[i]->Write();
    h_primtrack_mom_p[i]->Write();
 
  }
}


void WriteHistosJet() {

  for(int i=0; i<6; i++) {
    h_Jet_phi[6]->Add(h_Jet_phi[i]); 
    h_Jet_theta[6]->Add(h_Jet_theta[i]);
    h_Jet_mom[6]->Add(h_Jet_mom[i]);
    h_Jet_btag[6]->Add(h_Jet_btag[i]);
    h_Jet_ctag[6]->Add(h_Jet_ctag[i]);

  }

  for(int i=0; i<3; i++) {
    h_Jet_phi[7]->Add(h_Jet_phi[i]); 
    h_Jet_theta[7]->Add(h_Jet_theta[i]);
    h_Jet_mom[7]->Add(h_Jet_mom[i]);
    h_Jet_btag[7]->Add(h_Jet_btag[i]);
    h_Jet_ctag[7]->Add(h_Jet_ctag[i]);
  }

  for(int i=3; i<6; i++) {
    h_Jet_phi[8]->Add(h_Jet_phi[i]); 
    h_Jet_theta[8]->Add(h_Jet_theta[i]);
    h_Jet_mom[8]->Add(h_Jet_mom[i]);
    h_Jet_btag[8]->Add(h_Jet_btag[i]);
    h_Jet_ctag[8]->Add(h_Jet_ctag[i]);
  }

  for(int i=0; i<9; i++) {
    h_Jet_phi[i]->Write(); 
    h_Jet_theta[i]->Write();
    h_Jet_mom[i]->Write();
    h_Jet_btag[i]->Write();
    h_Jet_ctag[i]->Write();
  }
}
