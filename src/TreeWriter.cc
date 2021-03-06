#include "TreeWriter.hh"
using std::string;
using std::vector;

namespace QQbarProcessor 
{
  TreeWriter:: TreeWriter() {}
  void TreeWriter::InitializeStatsQQbarTree(TTree * _hTree, StatsData_QQbar & data)
  {

    //new variables
    //******************
    // defined at LO order, before PS
    _hTree->Branch("mc_quark_E", data._mc_quark_E, "mc_quark_E[2]/F");
    _hTree->Branch("mc_quark_px", data._mc_quark_px, "mc_quark_px[2]/F");
    _hTree->Branch("mc_quark_py", data._mc_quark_py, "mc_quark_py[2]/F");
    _hTree->Branch("mc_quark_pz", data._mc_quark_pz, "mc_quark_pz[2]/F");
    _hTree->Branch("mc_quark_m", data._mc_quark_m, "mc_quark_m[2]/F");
    _hTree->Branch("mc_quark_pdg", data._mc_quark_pdg, "mc_quark_pdg[2]/F");
    _hTree->Branch("mc_quark_charge", data._mc_quark_charge, "mc_quark_charge[2]/F");

    _hTree->Branch("mc_ISR_E", data._mc_ISR_E, "mc_ISR_E[2]/F");
    _hTree->Branch("mc_ISR_px", data._mc_ISR_px, "mc_ISR_px[2]/F");
    _hTree->Branch("mc_ISR_py", data._mc_ISR_py, "mc_ISR_py[2]/F");
    _hTree->Branch("mc_ISR_pz", data._mc_ISR_pz, "mc_ISR_pz[2]/F");
    _hTree->Branch("mc_ISR_m", data._mc_ISR_m, "mc_ISR_m[2]/F");   
    _hTree->Branch("mc_ISR_pdg", data._mc_ISR_pdg, "mc_ISR_pdg[2]/F");
    _hTree->Branch("mc_ISR_charge", data._mc_ISR_charge, "mc_ISR_charge[2]/F");

    // mc quark and partons after PS -->  FSR included, just before starting hadronization process
    _hTree->Branch("mc_quark_ps_n", &data._mc_quark_ps_n, "mc_quark_ps_n/I");
    _hTree->Branch("mc_quark_ps_E", data._mc_quark_ps_E, "mc_quark_ps_E[mc_quark_ps_n]/F");
    _hTree->Branch("mc_quark_ps_px", data._mc_quark_ps_px, "mc_quark_ps_px[mc_quark_ps_n]/F");
    _hTree->Branch("mc_quark_ps_py", data._mc_quark_ps_py, "mc_quark_ps_py[mc_quark_ps_n]/F");
    _hTree->Branch("mc_quark_ps_pz", data._mc_quark_ps_pz, "mc_quark_ps_pz[mc_quark_ps_n]/F");
    _hTree->Branch("mc_quark_ps_m", data._mc_quark_ps_m, "mc_quark_ps_m[mc_quark_ps_n]/F");
    _hTree->Branch("mc_quark_ps_pdg", data._mc_quark_ps_pdg, "mc_quark_ps_pdg[mc_quark_ps_n]/F");
    _hTree->Branch("mc_quark_ps_charge", data._mc_quark_ps_charge, "mc_quark_ps_charge[mc_quark_ps_n]/F");

    _hTree->Branch("mc_quark_ps_y12", &data._mc_quark_ps_y12, "mc_quark_ps_y12/F");
    _hTree->Branch("mc_quark_ps_y23", &data._mc_quark_ps_y23, "mc_quark_ps_y23/F");
    _hTree->Branch("mc_quark_ps_d12", &data._mc_quark_ps_d12, "mc_quark_ps_d12/F");
    _hTree->Branch("mc_quark_ps_d23", &data._mc_quark_ps_d23, "mc_quark_ps_d23/F");
    _hTree->Branch("mc_quark_ps_jet_E", data._mc_quark_ps_jet_E, "mc_quark_ps_jet_E[2]/F");
    _hTree->Branch("mc_quark_ps_jet_px", data._mc_quark_ps_jet_px, "mc_quark_ps_jet_px[2]/F");
    _hTree->Branch("mc_quark_ps_jet_py", data._mc_quark_ps_jet_py, "mc_quark_ps_jet_py[2]/F");
    _hTree->Branch("mc_quark_ps_jet_pz", data._mc_quark_ps_jet_pz, "mc_quark_ps_jet_pz[2]/F");
   
    //Added by Seidai in 2020.Sep.17
    //stable level
    _hTree->Branch("mc_stable_n", &data._mc_stable_n, "mc_stable_n/I");
    _hTree->Branch("mc_stable_E", data._mc_stable_E, "mc_stable_E[mc_stable_n]/F");
    _hTree->Branch("mc_stable_px", data._mc_stable_px, "mc_stable_px[mc_stable_n]/F");
    _hTree->Branch("mc_stable_py", data._mc_stable_py, "mc_stable_py[mc_stable_n]/F");
    _hTree->Branch("mc_stable_pz", data._mc_stable_pz, "mc_stable_pz[mc_stable_n]/F");
    _hTree->Branch("mc_stable_m", data._mc_stable_m, "mc_stable_m[mc_stable_n]/F");
    _hTree->Branch("mc_stable_pdg", data._mc_stable_pdg, "mc_stable_pdg[mc_stable_n]/I");
    _hTree->Branch("mc_stable_charge", data._mc_stable_charge, "mc_stable_charge[mc_stable_n]/F");
    _hTree->Branch("mc_stable_isoverlay", data._mc_stable_isoverlay, "mc_stable_isoverlay[mc_stable_n]/I");
    _hTree->Branch("mc_stable_isisr", data._mc_stable_isisr, "mc_stable_isisr[mc_stable_n]/I");
    //    _hTree->Branch("mc_stable_n", &data._mc_stable_n, "mc_stable_n/I");
    _hTree->Branch("mc_stable_y12", &data._mc_stable_y12, "mc_stable_y12/F");
    _hTree->Branch("mc_stable_y23", &data._mc_stable_y23, "mc_stable_y23/F");
    _hTree->Branch("mc_stable_d12", &data._mc_stable_d12, "mc_stable_d12/F");
    _hTree->Branch("mc_stable_d23", &data._mc_stable_d23, "mc_stable_d23/F");
    _hTree->Branch("mc_stable_jet_E", data._mc_stable_jet_E, "mc_stable_jet_E[2]/F");
    _hTree->Branch("mc_stable_jet_px", data._mc_stable_jet_px, "mc_stable_jet_px[2]/F");
    _hTree->Branch("mc_stable_jet_py", data._mc_stable_jet_py, "mc_stable_jet_py[2]/F");
    _hTree->Branch("mc_stable_jet_pz", data._mc_stable_jet_pz, "mc_stable_jet_pz[2]/F");
    

    // jets properties
    _hTree->Branch("jet_E", data._jet_E, "jet_E[2]/F");
    _hTree->Branch("jet_px", data._jet_px, "jet_px[2]/F");
    _hTree->Branch("jet_py", data._jet_py, "jet_py[2]/F");
    _hTree->Branch("jet_pz", data._jet_pz, "jet_pz[2]/F");
    _hTree->Branch("jet_btag", data._jet_btag, "jet_btag[2]/F");
    _hTree->Branch("jet_ctag", data._jet_ctag, "jet_ctag[2]/F");
    _hTree->Branch("y23", &data._y23, "y23/F");
    _hTree->Branch("y12", &data._y12, "y12/F");
    _hTree->Branch("d23", &data._d23, "d23/F");
    _hTree->Branch("d12", &data._d12, "d12/F");
    _hTree->Branch("oblateness", &data._oblateness, "oblateness/F");
    _hTree->Branch("aplanarity", &data._aplanarity, "aplanarity/F");
    _hTree->Branch("major_thrust_value", &data._major_thrust_value, "major_thrust_value/F");
    _hTree->Branch("major_thrust_axis", data._major_thrust_axis, "major_thrust_axis[3]/F");
    _hTree->Branch("minor_thrust_value", &data._minor_thrust_value, "minor_thrust_value/F");
    _hTree->Branch("minor_thrust_axis", data._minor_thrust_axis, "minor_thrust_axis[3]/F");
    _hTree->Branch("principle_thrust_value", &data._principle_thrust_value, "principle_thrust_value/F");
    _hTree->Branch("principle_thrust_axis", data._principle_thrust_axis, "principle_thrust_axis[3]/F");
    _hTree->Branch("sphericity", &data._sphericity, "sphericity/F");
    _hTree->Branch("sphericity_tensor", data._sphericity_tensor, "sphericity_tensor[3]/F");

  // pfo inside the jets
    _hTree->Branch("pfo_n", &data._pfo_n, "pfo_n/I");
    _hTree->Branch("jet_nvtx", &data._nvtx, "jet_nvtx/I");
    _hTree->Branch("pfo_n_j1", &data._pfo_n_j1, "pfo_n_j1/I");
    _hTree->Branch("jet_nvtx_j1", &data._nvtx_j1, "jet_nvtx_j1/I");
    _hTree->Branch("pfo_n_j2", &data._pfo_n_j2, "pfo_n_j2/I");
    _hTree->Branch("jet_nvtx_j2", &data._nvtx_j2, "jet_nvtx_j2/I");

    _hTree->Branch("pfo_match", data._pfo_jet_match, "pfo_match[pfo_n]/I");
    _hTree->Branch("pfo_pdgcheat", data._pfo_pdgcheat, "pfo_pdgcheat[pfo_n]/I");
    _hTree->Branch("pfo_E", data._pfo_E, "pfo_E[pfo_n]/F");
    _hTree->Branch("pfo_px", data._pfo_px, "pfo_px[pfo_n]/F");
    _hTree->Branch("pfo_py", data._pfo_py, "pfo_py[pfo_n]/F");
    _hTree->Branch("pfo_pz", data._pfo_pz, "pfo_pz[pfo_n]/F");
    _hTree->Branch("pfo_m", data._pfo_m, "pfo_m[pfo_n]/F"); 
    _hTree->Branch("pfo_type", data._pfo_type, "pfo_type[pfo_n]/I");
    _hTree->Branch("pfo_isoverlay", data._pfo_isoverlay, "pfo_isoverlay[pfo_n]/I");
    _hTree->Branch("pfo_isisr", data._pfo_isisr, "pfo_isisr[pfo_n]/I");
    _hTree->Branch("pfo_vtx", data._pfo_vtx, "pfo_vtx[pfo_n]/I");     
    _hTree->Branch("pfo_charge", data._pfo_charge, "pfo_charge[pfo_n]/I");
    _hTree->Branch("pfo_ntracks", data._pfo_ntracks, "pfo_ntracks[pfo_n]/I");

    _hTree->Branch("pfo_tpc_hits", data._pfo_tpc_hits, "pfo_tpc_hits[pfo_n]/I");
    _hTree->Branch("pfo_dedx", data._pfo_dedx, "pfo_dedx[pfo_n]/F");
    _hTree->Branch("pfo_dedxerror", data._pfo_dedxerror, "pfo_dedxerror[pfo_n]/F");
    _hTree->Branch("pfo_d0", data._pfo_d0, "pfo_d0[pfo_n]/F");
    _hTree->Branch("pfo_d0error", data._pfo_d0error, "pfo_d0error[pfo_n]/F");
    _hTree->Branch("pfo_z0", data._pfo_z0, "pfo_z0[pfo_n]/F");
    _hTree->Branch("pfo_z0error", data._pfo_z0error, "pfo_z0error[pfo_n]/F");
    _hTree->Branch("pfo_phi", data._pfo_phi, "pfo_phi[pfo_n]/F");
    _hTree->Branch("pfo_phierror", data._pfo_phierror, "pfo_phierror[pfo_n]/F");
    _hTree->Branch("pfo_omega", data._pfo_omega, "pfo_omega[pfo_n]/F");
    _hTree->Branch("pfo_omegaerror", data._pfo_omegaerror, "pfo_omegaerror[pfo_n]/F");
    _hTree->Branch("pfo_tanlambda", data._pfo_tanlambda, "pfo_tanlambda[pfo_n]/F");
    _hTree->Branch("pfo_tanlambdaerror", data._pfo_tanlambdaerror, "pfo_tanlambdaerror[pfo_n]/F");
    _hTree->Branch("pfo_chi2", data._pfo_chi2, "pfo_chi2[pfo_n]/F");
    _hTree->Branch("pfo_ndf", data._pfo_ndf, "pfo_ndf[pfo_n]/F");
    _hTree->Branch("pfo_pid", data._pfo_pid, "pfo_pid[pfo_n]/I");
    _hTree->Branch("pfo_pid_likelihood", data._pfo_pid_likelihood, "pfo_pid_likelihood[pfo_n]/F");
    _hTree->Branch("pfo_pid_eprob", data._pfo_pid_eprob, "pfo_pid_eprob[pfo_n]/F");
    _hTree->Branch("pfo_pid_muprob", data._pfo_pid_muprob, "pfo_pid_muprob[pfo_n]/F");
    _hTree->Branch("pfo_pid_piprob", data._pfo_pid_piprob, "pfo_pid_piprob[pfo_n]/F");
    _hTree->Branch("pfo_pid_kprob", data._pfo_pid_kprob, "pfo_pid_kprob[pfo_n]/F");
    _hTree->Branch("pfo_pid_pprob", data._pfo_pid_pprob, "pfo_pid_pprob[pfo_n]/F");
    _hTree->Branch("pfo_pid_hprob", data._pfo_pid_hprob, "pfo_pid_hprob[pfo_n]/F");
    _hTree->Branch("pfo_piddedx", data._pfo_piddedx, "pfo_piddedx[pfo_n]/I");
    _hTree->Branch("pfo_piddedx_likelihood", data._pfo_piddedx_likelihood, "pfo_piddedx_likelihood[pfo_n]/F");
    _hTree->Branch("pfo_piddedx_eprob", data._pfo_piddedx_eprob, "pfo_piddedx_eprob[pfo_n]/F");
    _hTree->Branch("pfo_piddedx_muprob", data._pfo_piddedx_muprob, "pfo_piddedx_muprob[pfo_n]/F");
    _hTree->Branch("pfo_piddedx_piprob", data._pfo_piddedx_piprob, "pfo_piddedx_piprob[pfo_n]/F");
    _hTree->Branch("pfo_piddedx_kprob", data._pfo_piddedx_kprob, "pfo_piddedx_kprob[pfo_n]/F");
    _hTree->Branch("pfo_piddedx_pprob", data._pfo_piddedx_pprob, "pfo_piddedx_pprob[pfo_n]/F");
    _hTree->Branch("pfo_piddedx_hprob", data._pfo_piddedx_hprob, "pfo_piddedx_hprob[pfo_n]/F");




  }


} /* TTBarAnalysis */
