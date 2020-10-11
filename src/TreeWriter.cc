#include "TreeWriter.hh"
using std::string;
using std::vector;

namespace QQbarProcessor 
{
  TreeWriter:: TreeWriter() {}
  void TreeWriter::InitializeSummaryTree(TTree * _hSumTree, SummaryData & data)
  {	
    _hSumTree->Branch("nEvents", &data._nEvt, "nEvents/I");
    _hSumTree->Branch("nGenUsed", &data._nGenUsed, "nGenUsed/I");
    _hSumTree->Branch("nBkgUsed", &data._nBkgUsed, "nBkgUsed/I");
    _hSumTree->Branch("nAfterGenMassCuts", &data._nAfterGenMassCuts, "nAfterGenMassCuts/I");
    _hSumTree->Branch("nAfterLeptonCuts", &data._nAfterLeptonCuts, "nAfterLeptonCuts/I");
    _hSumTree->Branch("nAfterBtagCuts", &data._nAfterBtagCuts, "nAfterBtagCuts/I");
    _hSumTree->Branch("nKaons", &data._nKaons, "nKaons/I");
    _hSumTree->Branch("nChargedB", &data._nChargedB, "nChargedB/I");
    _hSumTree->Branch("nAfterKinematicCuts", &data._nAfterKinematicCuts, "nAfterKinematicCuts/I");
    _hSumTree->Branch("nAfterMassCuts", &data._nAfterMassCuts, "nAfterMassCuts/I");

  }

  void TreeWriter::InitializeStatsBBbarTree(TTree * _hTree, StatsData_BBbar & data)
  {

    //new variables
    //******************
    // defined at LO order, before PS
    _hTree->Branch("mc_quark_E", data._mc_quark_E, "mc_quark_E[2]/F");
    _hTree->Branch("mc_quark_px", data._mc_quark_px, "mc_quark_px[2]/F");
    _hTree->Branch("mc_quark_py", data._mc_quark_py, "mc_quark_py[2]/F");
    _hTree->Branch("mc_quark_pz", data._mc_quark_pz, "mc_quark_pz[2]/F");
    _hTree->Branch("mc_quark_pt", data._mc_quark_pt, "mc_quark_pt[2]/F");
    _hTree->Branch("mc_quark_m", data._mc_quark_m, "mc_quark_m[2]/F");
    _hTree->Branch("mc_quark_pdg", data._mc_quark_pdg, "mc_quark_pdg[2]/F");
    _hTree->Branch("mc_quark_charge", data._mc_quark_charge, "mc_quark_charge[2]/F");

    _hTree->Branch("mc_ISR_E", data._mc_ISR_E, "mc_ISR_E[2]/F");
    _hTree->Branch("mc_ISR_px", data._mc_ISR_px, "mc_ISR_px[2]/F");
    _hTree->Branch("mc_ISR_py", data._mc_ISR_py, "mc_ISR_py[2]/F");
    _hTree->Branch("mc_ISR_pz", data._mc_ISR_pz, "mc_ISR_pz[2]/F");
    _hTree->Branch("mc_ISR_pt", data._mc_ISR_pt, "mc_ISR_pt[2]/F");
    _hTree->Branch("mc_ISR_m", data._mc_ISR_m, "mc_ISR_m[2]/F");   
    _hTree->Branch("mc_ISR_pdg", data._mc_ISR_pdg, "mc_ISR_pdg[2]/F");
    _hTree->Branch("mc_ISR_charge", data._mc_ISR_charge, "mc_ISR_charge[2]/F");

    _hTree->Branch("mc_qqbar_m", &data._mc_qqbar_m, "mc_qqbar_m/F");
    _hTree->Branch("mc_qqbar_pt", &data._mc_qqbar_pt, "mc_qqbar_pt/F");

    // mc quark and partons after PS -->  FSR included, just before starting hadronization process
    _hTree->Branch("mc_quark_ps_n", &data._mc_quark_ps_n, "mc_quark_ps_n/I");
    _hTree->Branch("mc_quark_ps_E", data._mc_quark_ps_E, "mc_quark_ps_E[mc_quark_ps_n]/F");
    _hTree->Branch("mc_quark_ps_px", data._mc_quark_ps_px, "mc_quark_ps_px[mc_quark_ps_n]/F");
    _hTree->Branch("mc_quark_ps_py", data._mc_quark_ps_py, "mc_quark_ps_py[mc_quark_ps_n]/F");
    _hTree->Branch("mc_quark_ps_pz", data._mc_quark_ps_pz, "mc_quark_ps_pz[mc_quark_ps_n]/F");
    _hTree->Branch("mc_quark_ps_pt", data._mc_quark_ps_pt, "mc_quark_ps_pt[mc_quark_ps_n]/F");
    _hTree->Branch("mc_quark_ps_m", data._mc_quark_ps_m, "mc_quark_ps_m[mc_quark_ps_n]/F");
    _hTree->Branch("mc_quark_ps_pdg", data._mc_quark_ps_pdg, "mc_quark_ps_pdg[mc_quark_ps_n]/F");
    _hTree->Branch("mc_quark_ps_charge", data._mc_quark_ps_charge, "mc_quark_ps_charge[mc_quark_ps_n]/F");
    //_hTree->Branch("mc_quark_ps_n", &data._mc_quark_ps_n, "mc_quark_ps_n/I");

    _hTree->Branch("jet_R_norm", &data._jet_R_norm, "jet_R_norm/F");
    _hTree->Branch("mc_quark_ps_y12", &data._mc_quark_ps_y12, "mc_quark_ps_y12/F");
    _hTree->Branch("mc_quark_ps_y23", &data._mc_quark_ps_y23, "mc_quark_ps_y23/F");
    _hTree->Branch("mc_quark_ps_d12", &data._mc_quark_ps_d12, "mc_quark_ps_d12/F");
    _hTree->Branch("mc_quark_ps_d23", &data._mc_quark_ps_d23, "mc_quark_ps_d23/F");
    _hTree->Branch("mc_quark_ps_ycut", data._mc_quark_ps_ycut, "mc_quark_ps_ycut[50]/F");
    _hTree->Branch("mc_quark_ps_njets_ycut", data._mc_quark_ps_njets_ycut, "mc_quark_ps_njets_ycut[50]/F");
    _hTree->Branch("mc_quark_ps_njets_ycut_cambridge", data._mc_quark_ps_njets_ycut_cambridge, "mc_quark_ps_njets_ycut_cambridge[50]/F");
    _hTree->Branch("mc_quark_ps_jet_E", data._mc_quark_ps_jet_E, "mc_quark_ps_jet_E[2]/F");
    _hTree->Branch("mc_quark_ps_jet_px", data._mc_quark_ps_jet_px, "mc_quark_ps_jet_px[2]/F");
    _hTree->Branch("mc_quark_ps_jet_py", data._mc_quark_ps_jet_py, "mc_quark_ps_jet_py[2]/F");
    _hTree->Branch("mc_quark_ps_jet_pz", data._mc_quark_ps_jet_pz, "mc_quark_ps_jet_pz[2]/F");
    _hTree->Branch("mc_quark_ps_jet_nparticles", data._mc_quark_ps_jet_nparticles, "mc_quark_ps_nparticles[2]/I");

    _hTree->Branch("mc_quark_ps_isr_y12", &data._mc_quark_ps_isr_y12, "mc_quark_ps_isr_y12/F");
    _hTree->Branch("mc_quark_ps_isr_y23", &data._mc_quark_ps_isr_y23, "mc_quark_ps_isr_y23/F");
    _hTree->Branch("mc_quark_ps_isr_d12", &data._mc_quark_ps_isr_d12, "mc_quark_ps_isr_d12/F");
    _hTree->Branch("mc_quark_ps_isr_d23", &data._mc_quark_ps_isr_d23, "mc_quark_ps_isr_d23/F");
    _hTree->Branch("mc_quark_ps_isr_jet_E", data._mc_quark_ps_isr_jet_E, "mc_quark_ps_isr_jet_E[2]/F");
    _hTree->Branch("mc_quark_ps_isr_jet_px", data._mc_quark_ps_isr_jet_px, "mc_quark_ps_isr_jet_px[2]/F");
    _hTree->Branch("mc_quark_ps_isr_jet_py", data._mc_quark_ps_isr_jet_py, "mc_quark_ps_isr_jet_py[2]/F");
    _hTree->Branch("mc_quark_ps_isr_jet_pz", data._mc_quark_ps_isr_jet_pz, "mc_quark_ps_isr_jet_pz[2]/F");
    _hTree->Branch("mc_quark_ps_isr_jet_nparticles", data._mc_quark_ps_isr_jet_nparticles, "mc_quark_ps_isr_nparticles[2]/I");
    
    //Added by Seidai in 2020.Sep.17
    //hadron level
    _hTree->Branch("mc_hadron_n", &data._mc_hadron_n, "mc_hadron_n/I");
    _hTree->Branch("mc_hadron_E", data._mc_hadron_E, "mc_hadron_E[mc_hadron_n]/F");
    _hTree->Branch("mc_hadron_px", data._mc_hadron_px, "mc_hadron_px[mc_hadron_n]/F");
    _hTree->Branch("mc_hadron_py", data._mc_hadron_py, "mc_hadron_py[mc_hadron_n]/F");
    _hTree->Branch("mc_hadron_pz", data._mc_hadron_pz, "mc_hadron_pz[mc_hadron_n]/F");
    _hTree->Branch("mc_hadron_m", data._mc_hadron_m, "mc_hadron_m[mc_hadron_n]/F");
    _hTree->Branch("mc_hadron_pdg", data._mc_hadron_pdg, "mc_hadron_pdg[mc_hadron_n]/F");
    _hTree->Branch("mc_hadron_charge", data._mc_hadron_charge, "mc_hadron_charge[mc_hadron_n]/F");
    //    _hTree->Branch("mc_hadron_n", &data._mc_hadron_n, "mc_hadron_n/I");
    _hTree->Branch("mc_hadron_y12", &data._mc_hadron_y12, "mc_hadron_y12/F");
    _hTree->Branch("mc_hadron_y23", &data._mc_hadron_y23, "mc_hadron_y23/F");
    _hTree->Branch("mc_hadron_d12", &data._mc_hadron_d12, "mc_hadron_d12/F");
    _hTree->Branch("mc_hadron_d23", &data._mc_hadron_d23, "mc_hadron_d23/F");
    _hTree->Branch("mc_hadron_ycut", data._mc_hadron_ycut, "mc_hadron_ycut[50]/F");
    _hTree->Branch("mc_hadron_njets_ycut", data._mc_hadron_njets_ycut, "mc_hadron_njets_ycut[50]/F");
    _hTree->Branch("mc_hadron_njets_ycut_cambridge", data._mc_hadron_njets_ycut_cambridge, "mc_hadron_njets_ycut_cambridge[50]/F");

    //oscillation
    _hTree->Branch("MCBOscillation", &data._MCBOscillation, "MCBOscillation/I");
    _hTree->Branch("MCBBarOscillation", &data._MCBBarOscillation, "MCBBarOscillation/I");

    //******************
    //reco variables
    _hTree->Branch("mc_matching", &data._mc_matching, "mc_matching/I");
    //=0 if not matching between jets and quarks
    //=1 if  matching of quark[0] with jet[0] (and q[1] j[1])
    //=2 if  matching of quark[0] with jet[1] (and q[1] j[0])

    // maximum eergy reconstructed photon
    _hTree->Branch("maxenergy_photon_E", &data._maxenergy_photon_E, "maxenergy_photon_E/F");
    _hTree->Branch("maxenergy_photon_costheta", &data._maxenergy_photon_costheta, "maxenergy_photon_costheta/F");

    // jets properties
    _hTree->Branch("jet_E", data._jet_E, "jet_E[2]/F");
    _hTree->Branch("jet_px", data._jet_px, "jet_px[2]/F");
    _hTree->Branch("jet_py", data._jet_py, "jet_py[2]/F");
    _hTree->Branch("jet_pz", data._jet_pz, "jet_pz[2]/F");
    _hTree->Branch("jet_m", data._jet_m, "jet_m[2]/F");
    _hTree->Branch("jet_btag", data._jet_btag, "jet_btag[2]/F");
    _hTree->Branch("jet_ctag", data._jet_ctag, "jet_ctag[2]/F");
    _hTree->Branch("y23", &data._y23, "y23/F");
    _hTree->Branch("y12", &data._y12, "y12/F");
    _hTree->Branch("d23", &data._d23, "d23/F");
    _hTree->Branch("d12", &data._d12, "d12/F");
    _hTree->Branch("ycut", data._ycut, "ycut[50]/F");
    _hTree->Branch("njets_ycut", data._njets_ycut, "njets_ycut[50]/F");
    _hTree->Branch("njets_ycut_cambridge", data._njets_ycut_cambridge, "njets_ycut_cambridge[50]/F");
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
    _hTree->Branch("jet_pfo_E", data._pfo_E, "jet_pfo_E[2][150]/F");
    _hTree->Branch("jet_pfo_px", data._pfo_px, "jet_pfo_px[2][150]/F");
    _hTree->Branch("jet_pfo_py", data._pfo_py, "jet_pfo_py[2][150]/F");
    _hTree->Branch("jet_pfo_pz", data._pfo_pz, "jet_pfo_pz[2][150]/F");
    _hTree->Branch("jet_pfo_m", data._pfo_m, "jet_pfo_m[2][150]/F"); 
    _hTree->Branch("jet_pfo_type", data._pfo_type, "jet_pfo_type[2][150]/I");
    _hTree->Branch("jet_pfo_charge", data._pfo_charge, "jet_pfo_charge[2][150]/I");     
    _hTree->Branch("jet_pfo_n", data._pfo_n, "jet_pfo_n[2]/I");

    // jets reconstructed secondary vtx properties
    _hTree->Branch("jet_nvtx", data._jet_nvtx, "jet_nvtx[2]/I");
    _hTree->Branch("jet_vtx_isprimary", data._jet_vtx_isprimary, "jet_vtx_isprimary[2][10]/I");
    _hTree->Branch("jet_ntrack", data._jet_ntrack, "jet_ntrack[2]/I");
    _hTree->Branch("jet_vtx_ntrack", data._jet_vtx_ntrack, "jet_vtx_ntrack[2][10]/I");
    _hTree->Branch("jet_vtx_charge", data._jet_vtx_charge, "jet_vtx_charge[2][10]/F");

    _hTree->Branch("jet_track_E", data._jet_track_E, "jet_track_E[2][10][30]/F");
    _hTree->Branch("jet_track_px", data._jet_track_px, "jet_track_px[2][10][30]/F");
    _hTree->Branch("jet_track_py", data._jet_track_py, "jet_track_py[2][10][30]/F");
    _hTree->Branch("jet_track_pz", data._jet_track_pz, "jet_track_pz[2][10][30]/F");
    _hTree->Branch("jet_track_p", data._jet_track_p, "jet_track_p[2][10][30]/F");
    _hTree->Branch("jet_track_charge", data._jet_track_charge, "jet_track_charge[2][10][30]/F");
    _hTree->Branch("jet_track_dedx", data._jet_track_dedx, "jet_track_dedx[2][10][30]/F");
    _hTree->Branch("jet_track_iskaon", data._jet_track_iskaon, "jet_track_iskaon[2][10][30]/I");
    _hTree->Branch("jet_track_iskaoncheat", data._jet_track_iskaoncheat, "jet_track_iskaoncheat[2][10][30]/I");
    _hTree->Branch("jet_track_pdg", data._jet_track_pdg, "jet_track_pdg[2][10][30]/I");    
    _hTree->Branch("jet_track_z0", data._jet_track_z0, "jet_track_z0[2][10][30]/F");
    _hTree->Branch("jet_track_d0", data._jet_track_d0, "jet_track_d0[2][10][30]/F");
    _hTree->Branch("jet_track_phi", data._jet_track_phi, "jet_track_phi[2][10][30]/F");
		

  }

  void TreeWriter::InitializeStatsTree(TTree * _hTree, StatsData & data)
  {
    //Generated
    _hTree->Branch("mctag", &data._mctag, "mctag/I");
    _hTree->Branch("MCTopmass", &data._MCTopmass, "MCTopmass/F");
    _hTree->Branch("MCquarkAngle", &data._MCquarkAngle, "MCquarkAngle/F");
    _hTree->Branch("MCTopmomentum", &data._MCTopmomentum, "MCTopmomentum/F");
    _hTree->Branch("MCTopcostheta", &data._MCTopcostheta, "MCTopcostheta/F");
    _hTree->Branch("MCTopBarmass", &data._MCTopBarmass, "MCTopBarmass/F");
    _hTree->Branch("MCTopBarmomentum", &data._MCTopBarmomentum, "MCTopBarmomentum/F");
    _hTree->Branch("MCTopBarcostheta", &data._MCTopBarcostheta, "MCTopBarcostheta/F");
    _hTree->Branch("MCTopBangle", &data._MCTopBangle, "MCTopBangle/F");
    _hTree->Branch("MCTopcosWb", &data._MCTopcosWb, "MCTopcosWb/F");
    _hTree->Branch("MCNeutrinoEnergy", &data._MCNeutrinoEnergy, "MCNeutrinoEnergy/F");
    _hTree->Branch("MCLeptonPDG", &data._MCLeptonPDG, "MCLeptonPDG/I");
    _hTree->Branch("MCLeptonMomentum", &data._MCLeptonMomentum, "MCLeptonMomentum/F");
    _hTree->Branch("MCLeptonCostheta", &data._MCLeptonCostheta, "MCLeptonCostheta/F");
    _hTree->Branch("MCBOscillation", &data._MCBOscillation, "MCBOscillation/I");
    _hTree->Branch("MCBBarOscillation", &data._MCBBarOscillation, "MCBBarOscillation/I");
    _hTree->Branch("qMCBcostheta", data._qMCBcostheta, "qMCBcostheta[2]/F");
    _hTree->Branch("qMCcostheta", data._qMCcostheta, "qMCcostheta[2]/F");

    //Reconstructed
    _hTree->Branch("totalEnergy", &data._totalEnergy, "totalEnergy/F");
    _hTree->Branch("bProduct", &data._bProduct, "bProduct/F");
    _hTree->Branch("hadMass", &data._hadMass, "hadMass/F");
    _hTree->Branch("missedEnergy", &data._missedEnergy, "missedEnergy/F");
    _hTree->Branch("W1mass", &data._W1mass, "W1mass/F");
    _hTree->Branch("W1gamma", &data._W1gamma, "W1gamma/F");
    _hTree->Branch("W1momentum", &data._W1momentum, "W1momentum/F");
    _hTree->Branch("W1costheta", &data._W1costheta, "W1costheta/F");
    _hTree->Branch("W2mass", &data._W2mass, "W2mass/F");
    _hTree->Branch("W2momentum", &data._W2momentum, "W2momentum/F");
    _hTree->Branch("W2costheta", &data._W2costheta, "W2costheta/F");
    _hTree->Branch("Top1mass", &data._Top1mass, "Top1mass/F");
    _hTree->Branch("Top1gamma", &data._Top1gamma, "Top1gamma/F");
    _hTree->Branch("Top1btag", &data._Top1btag, "Top1btag/F");
    _hTree->Branch("Top1energy", &data._Top1energy, "Top1energy/F");
    _hTree->Branch("Top1bcharge", &data._Top1bcharge, "Top1bcharge/I");
    _hTree->Branch("Top1Genbcharge", &data._Top1Genbcharge, "Top1Genbcharge/I");
    _hTree->Branch("Top1bmomentum", &data._Top1bmomentum, "Top1bmomentum/F");
    _hTree->Branch("Top1bdistance", &data._Top1bdistance, "Top1bdistance/F");
    _hTree->Branch("Top1costheta", &data._Top1costheta, "Top1costheta/F");
    _hTree->Branch("Top1bcostheta", &data._Top1bcostheta, "Top1bcostheta/F");
    _hTree->Branch("Top1truthAngle", &data._Top1truthAngle, "Top1truthAngle/F");
    _hTree->Branch("Top1bntracks", &data._Top1bntracks, "Top1bntracks/I");
    _hTree->Branch("Top1Genbntracks", &data._Top1Genbntracks, "Top1Genbntracks/I");
    _hTree->Branch("Top1bTVCM", &data._Top1bTVCM, "Top1bTVCM/I");
    _hTree->Branch("Top1cosWb", &data._Top1cosWb, "Top1cosWb/F");
    _hTree->Branch("Top1pstarb", &data._Top1pstarb, "Top1pstarb/F");
    _hTree->Branch("Top1Vtx", &data._Top1Vtx, "Top1Vtx/I");
    _hTree->Branch("Top1Kaon", &data._Top1Kaon, "Top1Kaon/I");
    _hTree->Branch("Top1KaonNumber", &data._Top1KaonNumber, "Top1KaonNumber/I");
    _hTree->Branch("Top1KaonCharges", data._Top1KaonCharges, "Top1KaonCharges[Top1KaonNumber]/I");
    _hTree->Branch("Top1KaonMomentum", data._Top1KaonMomentum, "Top1KaonMomentum[Top1KaonNumber]/F");
    _hTree->Branch("Top2mass", &data._Top2mass, "Top2mass/F");
    _hTree->Branch("Top2energy", &data._Top2energy, "Top2energy/F");
    _hTree->Branch("Top2gamma", &data._Top2gamma, "Top2gamma/F");
    _hTree->Branch("Top2btag", &data._Top2btag, "Top2btag/F");
    _hTree->Branch("Top2bmomentum", &data._Top2bmomentum, "Top2bmomentum/F");
    _hTree->Branch("Top2bdistance", &data._Top2bdistance, "Top2bdistance/F");
    _hTree->Branch("Top2bcharge", &data._Top2bcharge, "Top2bcharge/I");
    _hTree->Branch("Top2Genbcharge", &data._Top2Genbcharge, "Top2Genbcharge/I");
    _hTree->Branch("Top2bcostheta", &data._Top2bcostheta, "Top2bcostheta/F");
    _hTree->Branch("Top2bTVCM", &data._Top2bTVCM, "Top2bTVCM/I");
    _hTree->Branch("Top2bntracks", &data._Top2bntracks, "Top2bntracks/I");
    _hTree->Branch("Top2Genbntracks", &data._Top2Genbntracks, "Top2Genbntracks/I");
    _hTree->Branch("Top2leptonCharge", &data._Top2leptonCharge, "Top2leptonCharge/I");
    _hTree->Branch("Top2leptonE", &data._Top2leptonE, "Top2leptonE/F");
    _hTree->Branch("Top2leptonCos", &data._Top2leptonCos, "Top2leptonCos/F");
    _hTree->Branch("Top2leptonCorrect", &data._Top2leptonCorrect, "Top2leptonCorrect/I");
    _hTree->Branch("Top2Vtx", &data._Top2Vtx, "Top2Vtx/I");
    _hTree->Branch("Top2Kaon", &data._Top2Kaon, "Top2Kaon/I");
    _hTree->Branch("Top2KaonNumber", &data._Top2KaonNumber, "Top2KaonNumber/I");
    _hTree->Branch("Top2KaonCharges", data._Top2KaonCharges, "Top2KaonCharges[Top2KaonNumber]/I");
    _hTree->Branch("Top2KaonMomentum", data._Top2KaonMomentum, "Top2KaonMomentum[Top2KaonNumber]/F");
    _hTree->Branch("UsedBTVCM", &data._UsedBTVCM, "UsedBTVCM/I");
    _hTree->Branch("methodUsed", &data._methodUsed, "methodUsed/I");
    _hTree->Branch("methodRefused", &data._methodRefused, "methodRefused/I");
    _hTree->Branch("methodCorrect", &data._methodCorrect, "methodCorrect/I");
    _hTree->Branch("methodSameCharge", data._methodSameCharge, "methodSameCharge[methodRefused]/I");
    _hTree->Branch("methodTaken", data._methodTaken, "methodTaken[methodUsed]/I");
    _hTree->Branch("qBCostheta", data._qBCostheta, "qBCostheta[2]/F");
    _hTree->Branch("qCostheta", data._qCostheta, "qCostheta[2]/F");
    _hTree->Branch("chiHad", &data._chiHad, "chiHad/F");
    _hTree->Branch("chiTopMass", &data._chiTopMass, "chiTopMass/F");
    _hTree->Branch("chiTopE", &data._chiTopE, "chiTopE/F");
    _hTree->Branch("chiPbstar", &data._chiPbstar, "chiPbstar/F");
    _hTree->Branch("chiCosWb", &data._chiCosWb, "chiCosWb/F");
    _hTree->Branch("chiGammaT", &data._chiGammaT, "chiGammaT/F");
    _hTree->Branch("gammaT", &data._gammaT, "gammaT/F");
    _hTree->Branch("chiTop2Mass", &data._chiTop2Mass, "chiTop2Mass/F");
    _hTree->Branch("chiTop2E", &data._chiTop2E, "chiTop2E/F");
    _hTree->Branch("chiGammaT2", &data._chiGammaT2, "chiGammaT2/F");
    _hTree->Branch("Thrust", &data._Thrust, "Thrust/F");

  }

  void TreeWriter::InitializeStatsHadronicTree(TTree * _hTree, StatsData & data ){

    //Generated
    _hTree->Branch("mctag", &data._mctag, "mctag/I");
    _hTree->Branch("MCTopmass", &data._MCTopmass, "MCTopmass/F");
    _hTree->Branch("MCquarkAngle", &data._MCquarkAngle, "MCquarkAngle/F");
    _hTree->Branch("MCTopmomentum", &data._MCTopmomentum, "MCTopmomentum/F");
    _hTree->Branch("MCTopcostheta", &data._MCTopcostheta, "MCTopcostheta/F");
    _hTree->Branch("MCTopBarmass", &data._MCTopBarmass, "MCTopBarmass/F");
    _hTree->Branch("MCTopBarmomentum", &data._MCTopBarmomentum, "MCTopBarmomentum/F");
    _hTree->Branch("MCTopBarcostheta", &data._MCTopBarcostheta, "MCTopBarcostheta/F");
    _hTree->Branch("MCTopBangle", &data._MCTopBangle, "MCTopBangle/F");
    _hTree->Branch("MCTopcosWb", &data._MCTopcosWb, "MCTopcosWb/F");
    //_hTree->Branch("MCNeutrinoEnergy", &data._MCNeutrinoEnergy, "MCNeutrinoEnergy/F");
    //_hTree->Branch("MCBOscillation", &data._MCBOscillation, "MCBOscillation/I");
    //_hTree->Branch("MCBBarOscillation", &data._MCBBarOscillation, "MCBBarOscillation/I");
    _hTree->Branch("qMCBcostheta", data._qMCBcostheta, "qMCBcostheta[2]/F");
    _hTree->Branch("qMCcostheta", data._qMCcostheta, "qMCcostheta[2]/F");

    //Reconstructed
    _hTree->Branch("totalEnergy", &data._totalEnergy, "totalEnergy/F");
    _hTree->Branch("missedEnergy", &data._missedEnergy, "missedEnergy/F");
    _hTree->Branch("W1mass", &data._W1mass, "W1mass/F");
    _hTree->Branch("W1momentum", &data._W1momentum, "W1momentum/F");
    _hTree->Branch("W1costheta", &data._W1costheta, "W1costheta/F");
    _hTree->Branch("W2mass", &data._W2mass, "W2mass/F");
    _hTree->Branch("W2momentum", &data._W2momentum, "W2momentum/F");
    _hTree->Branch("W2costheta", &data._W2costheta, "W2costheta/F");
    _hTree->Branch("Top1mass", &data._Top1mass, "Top1mass/F");
    _hTree->Branch("Top1energy", &data._Top1energy, "Top1energy/F");
    _hTree->Branch("Top1bcharge", &data._Top1bcharge, "Top1bcharge/I");
    _hTree->Branch("Top1bmomentum", &data._Top1bmomentum, "Top1bmomentum/F");
    _hTree->Branch("Top1bdistance", &data._Top1bdistance, "Top1bdistance/F");
    _hTree->Branch("Top1costheta", &data._Top1costheta, "Top1costheta/F");
    _hTree->Branch("Top1bcostheta", &data._Top1bcostheta, "Top1bcostheta/F");
    //_hTree->Branch("Top1truthAngle", &data._Top1truthAngle, "Top1truthAngle/F");
    _hTree->Branch("Top1bntracks", &data._Top1bntracks, "Top1bntracks/I");
    _hTree->Branch("Top1btag", &data._Top1btag, "Top1btag/F");
    //_hTree->Branch("Top1bTVCM", &data._Top1bTVCM, "Top1bTVCM/I");
    _hTree->Branch("Top1cosWb", &data._Top1cosWb, "Top1cosWb/F");
    //_hTree->Branch("Top1Vtx", &data._Top1Vtx, "Top1Vtx/I");
    //_hTree->Branch("Top1Kaon", &data._Top1Kaon, "Top1Kaon/I");
    //_hTree->Branch("Top1KaonNumber", &data._Top1KaonNumber, "Top1KaonNumber/I");
    //_hTree->Branch("Top1KaonCharges", data._Top1KaonCharges, "Top1KaonCharges[Top1KaonNumber]/I");
    //_hTree->Branch("Top1KaonMomentum", data._Top1KaonMomentum, "Top1KaonMomentum[Top1KaonNumber]/F");
    _hTree->Branch("Top2mass", &data._Top2mass, "Top2mass/F");
    _hTree->Branch("Top2bmomentum", &data._Top2bmomentum, "Top2bmomentum/F");
    _hTree->Branch("Top2bdistance", &data._Top2bdistance, "Top2bdistance/F");
    _hTree->Branch("Top2bcharge", &data._Top2bcharge, "Top2bcharge/I");
    _hTree->Branch("Top2costheta", &data._Top2costheta, "Top2costheta/F");
    _hTree->Branch("Top2bcostheta", &data._Top2bcostheta, "Top2bcostheta/F");
    //_hTree->Branch("Top2bTVCM", &data._Top2bTVCM, "Top2bTVCM/I");
    _hTree->Branch("Top2bntracks", &data._Top2bntracks, "Top2bntracks/I");
    _hTree->Branch("Top2btag", &data._Top2btag, "Top2btag/F");
    //_hTree->Branch("Top2Vtx", &data._Top2Vtx, "Top2Vtx/I");
    //_hTree->Branch("Top2Kaon", &data._Top2Kaon, "Top2Kaon/I");
    //_hTree->Branch("Top2KaonNumber", &data._Top2KaonNumber, "Top2KaonNumber/I");
    //_hTree->Branch("Top2KaonCharges", data._Top2KaonCharges, "Top2KaonCharges[Top2KaonNumber]/I");
    //_hTree->Branch("Top2KaonMomentum", data._Top2KaonMomentum, "Top2KaonMomentum[Top2KaonNumber]/F");
    //_hTree->Branch("UsedBTVCM", &data._UsedBTVCM, "UsedBTVCM/I");
    //_hTree->Branch("methodUsed", &data._methodUsed, "methodUsed/I");
    //_hTree->Branch("methodRefused", &data._methodRefused, "methodRefused/I");
    //_hTree->Branch("methodCorrect", &data._methodCorrect, "methodCorrect/I");
    //_hTree->Branch("methodSameCharge", data._methodSameCharge, "methodSameCharge[methodRefused]/I");
    //_hTree->Branch("methodTaken", data._methodTaken, "methodTaken[methodUsed]/I");
    //_hTree->Branch("qCostheta", data._qCostheta, "qCostheta[2]/F");
    _hTree->Branch("chiHad1", &data._chiHad1, "chiHad1/F");
    _hTree->Branch("chiTopMass1", &data._chiTopMass1, "chiTopMass1/F");
    _hTree->Branch("chiTopE1", &data._chiTopE1, "chiTopE1/F");
    _hTree->Branch("chiPbstar1", &data._chiPbstar1, "chiPbstar1/F");
    _hTree->Branch("chiCosWb1", &data._chiCosWb1, "chiCosWb1/F");
    _hTree->Branch("chiGammaT1", &data._chiGammaT1, "chiGammaT1/F");
    _hTree->Branch("chiHad2", &data._chiHad2, "chiHad2/F");
    _hTree->Branch("chiTopMass2", &data._chiTopMass2, "chiTopMass2/F");
    _hTree->Branch("chiTopE2", &data._chiTopE2, "chiTopE2/F");
    _hTree->Branch("chiPbstar2", &data._chiPbstar2, "chiPbstar2/F");
    _hTree->Branch("chiCosWb2", &data._chiCosWb2, "chiCosWb2/F");
    _hTree->Branch("chiGammaT2", &data._chiGammaT2, "chiGammaT2/F");
    //_hTree->Branch("gammaT", &data._gammaT, "gammaT/F");

  }

} /* TTBarAnalysis */
