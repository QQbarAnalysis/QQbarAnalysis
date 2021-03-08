#define observable_cxx
#include "observable.h"
#include "TPad.h"

//todo:
//            std::cout<<"ERROR: nPFOs> 150: "<<components.size()<<std::endl;


void observable::InitDQ() {

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
void observable::InitHistosMC(std::vector<TString> name) {

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

void observable::WriteHistosMC() {

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


// ** PFOs
void observable::InitHistosPFO(std::vector<TString> name) {

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

void observable::WriteHistosPFO() {

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

void observable::InitHistosTrack(std::vector<TString> name) {

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

void observable::WriteHistosTrack() {

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

// ** tracks/ per particle type

void observable::InitHistosTrackID(std::vector<TString> name) {

  for(unsigned int i=0; i<name.size(); i++) {
 
    h_sectrack_mom_K[i] = new TH1F("sectrack_mom_K_"+name.at(i),"sectrack_mom_K_"+name.at(i),100,0,100);
    h_sectrack_mom_Pi[i] = new TH1F("sectrack_mom_Pi_"+name.at(i),"sectrack_mom_Pi_"+name.at(i),100,0,100);
    h_sectrack_mom_p[i] = new TH1F("sectrack_mom_p_"+name.at(i),"sectrack_mom_p_"+name.at(i),100,0,100);
  
    h_primtrack_mom_K[i] = new TH1F("primtrack_mom_K_"+name.at(i),"primtrack_mom_K_"+name.at(i),100,0,100);
    h_primtrack_mom_Pi[i] = new TH1F("primtrack_mom_Pi_"+name.at(i),"primtrack_mom_Pi_"+name.at(i),100,0,100);
    h_primtrack_mom_p[i] = new TH1F("primtrack_mom_p_"+name.at(i),"primtrack_mom_p_"+name.at(i),100,0,100);
    
  }
}

void observable::WriteHistosTrackID() {

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

// ** Jets
void observable::InitHistosJet(std::vector<TString> name) {

  for(unsigned int i=0; i<name.size(); i++) {
    h_Jet_phi[i] = new TH1F("Jet_phi_"+name.at(i),"Jet_phi_"+name.at(i),100,0,2.*TMath::Pi());
    h_Jet_theta[i] = new TH1F("Jet_theta_"+name.at(i),"Jet_theta_"+name.at(i),100,0,TMath::Pi());
    h_Jet_mom[i] = new TH1F("Jet_mom_"+name.at(i),"Jet_mom_"+name.at(i),251,-0.5,250.5);
    h_Jet_btag[i] = new TH1F("Jet_btag_"+name.at(i),"Jet_btag_"+name.at(i),1000,0,1);
    h_Jet_ctag[i] = new TH1F("Jet_ctag_"+name.at(i),"Jet_ctag_"+name.at(i),1000,0,1);
  }
  
}

void observable::WriteHistosJet() {

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

       
    
void observable::DQChecks(int n_entries=-1, float Kvcut=35, TString output="test")
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
      cout<<jentry << "NO QQBAR "<<jet_E[0]<<endl;
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

 


bool observable::PreSelection(int type=0,float Kvcut=25) {
  
  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
  if(type == 0 ) return true;

  return false;
  
}

