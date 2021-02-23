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
    _hTree->Branch("jet_pfo_n", &data._pfo_n, "jet_pfo_n/I");
    _hTree->Branch("jet_nvtx", &data._nvtx, "jet_nvtx/I");
    _hTree->Branch("jet_pfo_n_j1", &data._pfo_n_j1, "jet_pfo_n_j1/I");
    _hTree->Branch("jet_nvtx_j1", &data._nvtx_j1, "jet_nvtx_j1/I");
    _hTree->Branch("jet_pfo_n_j2", &data._pfo_n_j2, "jet_pfo_n_j2/I");
    _hTree->Branch("jet_nvtx_j2", &data._nvtx_j2, "jet_nvtx_j2/I");

    _hTree->Branch("jet_pfo_match", data._pfo_jet_match, "jet_pfo_match[jet_pfo_n]/I");
    _hTree->Branch("jet_pfo_pdgcheat", data._pfo_pdgcheat, "jet_pfo_pdgcheat[jet_pfo_n]/I");
    _hTree->Branch("jet_pfo_E", data._pfo_E, "jet_pfo_E[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_px", data._pfo_px, "jet_pfo_px[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_py", data._pfo_py, "jet_pfo_py[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_pz", data._pfo_pz, "jet_pfo_pz[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_m", data._pfo_m, "jet_pfo_m[jet_pfo_n]/F"); 
    _hTree->Branch("jet_pfo_type", data._pfo_type, "jet_pfo_type[jet_pfo_n]/I");
    _hTree->Branch("jet_pfo_isoverlay", data._pfo_isoverlay, "jet_pfo_isoverlay[jet_pfo_n]/I");
    _hTree->Branch("jet_pfo_isisr", data._pfo_isisr, "jet_pfo_isisr[jet_pfo_n]/I");
    _hTree->Branch("jet_pfo_istrack", data._pfo_istrack, "jet_pfo_istrack[jet_pfo_n]/I");
    _hTree->Branch("jet_pfo_vtx", data._pfo_vtx, "jet_pfo_vtx[jet_pfo_n]/I");     
    _hTree->Branch("jet_pfo_charge", data._pfo_charge, "jet_pfo_charge[jet_pfo_n]/I");

    _hTree->Branch("jet_pfo_tpc_hits", data._pfo_tpc_hits, "jet_pfo_tpc_hits[jet_pfo_n]/I");
    _hTree->Branch("jet_pfo_dedx", data._pfo_dedx, "jet_pfo_dedx[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_dedxerror", data._pfo_dedxerror, "jet_pfo_dedxerror[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_d0", data._pfo_d0, "jet_pfo_d0[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_d0error", data._pfo_d0error, "jet_pfo_d0error[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_z0", data._pfo_z0, "jet_pfo_z0[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_z0error", data._pfo_z0error, "jet_pfo_z0error[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_phi", data._pfo_phi, "jet_pfo_phi[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_phierror", data._pfo_phierror, "jet_pfo_phierror[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_omega", data._pfo_omega, "jet_pfo_omega[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_omegaerror", data._pfo_omegaerror, "jet_pfo_omegaerror[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_tanlambda", data._pfo_tanlambda, "jet_pfo_tanlambda[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_tanlambdaerror", data._pfo_tanlambdaerror, "jet_pfo_tanlambdaerror[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_chi2", data._pfo_chi2, "jet_pfo_chi2[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_ndf", data._pfo_ndf, "jet_pfo_ndf[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_pid", data._pfo_pid, "jet_pfo_pid[jet_pfo_n]/I");
    _hTree->Branch("jet_pfo_pid_likelihood", data._pfo_pid_likelihood, "jet_pfo_pid_likelihood[jet_pfo_n]/F");
    _hTree->Branch("jet_pfo_piddedx", data._pfo_piddedx, "jet_pfo_piddedx[jet_pfo_n]/I");
    _hTree->Branch("jet_pfo_piddedx_likelihood", data._pfo_piddedx_likelihood, "jet_pfo_piddedx_likelihood[jet_pfo_n]/F");



  }


} /* TTBarAnalysis */
