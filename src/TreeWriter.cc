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
    // mc quak partons --> still defined at LO order... what about including the PS radiation? 
    // then I need to reconstruct jets with final state quarks + FSR radiation
    // include then the d23 parameter + the total energy carried by FSR + the difference in angles between
    // LO partons and L0+FSR 
    _hTree->Branch("mc_quark_E", data._mc_quark_E, "mc_quark_E[2]/F");
    _hTree->Branch("mc_quark_px", data._mc_quark_px, "mc_quark_px[2]/F");
    _hTree->Branch("mc_quark_py", data._mc_quark_py, "mc_quark_py[2]/F");
    _hTree->Branch("mc_quark_pz", data._mc_quark_pz, "mc_quark_pz[2]/F");
    _hTree->Branch("mc_quark_pt", data._mc_quark_pt, "mc_quark_pt[2]/F");
    _hTree->Branch("mc_quark_m", data._mc_quark_m, "mc_quark_m[2]/F");
    _hTree->Branch("mc_quark_pdg", data._mc_quark_pdg, "mc_quark_pdg[2]/F");
    _hTree->Branch("mc_quark_charge", data._mc_quark_charge, "mc_quark_charge[2]/F");
    _hTree->Branch("mc_qqbar_m", &data._mc_qqbar_m, "mc_qqbar_m/F");
    _hTree->Branch("mc_qqbar_pt", &data._mc_qqbar_pt, "mc_qqbar_pt/F");

    // mc quark and partons after PS -->  FSR included, just before starting hadronization process
    _hTree->Branch("mc_quark_ps_E", data._mc_quark_ps_E, "mc_quark_ps_E[300]/F");
    _hTree->Branch("mc_quark_ps_px", data._mc_quark_ps_px, "mc_quark_ps_px[300]/F");
    _hTree->Branch("mc_quark_ps_py", data._mc_quark_ps_py, "mc_quark_ps_py[300]/F");
    _hTree->Branch("mc_quark_ps_pz", data._mc_quark_ps_pz, "mc_quark_ps_pz[300]/F");
    _hTree->Branch("mc_quark_ps_pt", data._mc_quark_ps_pt, "mc_quark_ps_pt[300]/F");
    _hTree->Branch("mc_quark_ps_m", data._mc_quark_ps_m, "mc_quark_ps_m[300]/F");
    _hTree->Branch("mc_quark_ps_pdg", data._mc_quark_ps_pdg, "mc_quark_ps_pdg[300]/F");
    _hTree->Branch("mc_quark_ps_charge", data._mc_quark_ps_charge, "mc_quark_ps_charge[300]/F");
    _hTree->Branch("mc_quark_ps_n", &data._mc_quark_ps_n, "mc_quark_ps_n/I");

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
    _hTree->Branch("y23", &data._y23, "y23/F");
    _hTree->Branch("y12", &data._y12, "y12/F");
    _hTree->Branch("jet_E", data._jet_E, "jet_E[2]/F");
    _hTree->Branch("jet_px", data._jet_px, "jet_px[2]/F");
    _hTree->Branch("jet_py", data._jet_py, "jet_py[2]/F");
    _hTree->Branch("jet_pz", data._jet_pz, "jet_pz[2]/F");
    _hTree->Branch("jet_m", data._jet_m, "jet_m[2]/F");
    _hTree->Branch("jet_btag", data._jet_btag, "jet_btag[2]/F");
     
    
    // jets reconstructed tracks properties
    _hTree->Branch("jet_nvtx", data._jet_nvtx, "jet_nvtx[2]/I");
    _hTree->Branch("jet_vtx_isprimary", data._jet_vtx_isprimary, "jet_vtx_isprimary[2][10]/I");
    _hTree->Branch("jet_ntrack", data._jet_ntrack, "jet_ntrack[2]/I");
    _hTree->Branch("jet_vtx_ntrack", data._jet_vtx_ntrack, "jet_vtx_ntrack[2][10]/I");
    _hTree->Branch("jet_vtx_charge", data._jet_vtx_charge, "jet_vtx_charge[2][10]/F");

    _hTree->Branch("jet_track_E", data._jet_track_E, "jet_track_E[2][10][20]/F");
    _hTree->Branch("jet_track_px", data._jet_track_px, "jet_track_px[2][10][20]/F");
    _hTree->Branch("jet_track_py", data._jet_track_py, "jet_track_py[2][10][20]/F");
    _hTree->Branch("jet_track_pz", data._jet_track_pz, "jet_track_pz[2][10][20]/F");
    _hTree->Branch("jet_track_p", data._jet_track_p, "jet_track_p[2][10][20]/F");
    _hTree->Branch("jet_track_charge", data._jet_track_charge, "jet_track_charge[2][10][20]/F");
    _hTree->Branch("jet_track_iskaon", data._jet_track_iskaon, "jet_track_iskaon[2][10][20]/I");
    _hTree->Branch("jet_track_kaoncharge", data._jet_track_kaoncharge, "jet_track_kaoncharge[2][10][20]/F");
    _hTree->Branch("jet_track_z0", data._jet_track_z0, "jet_track_z0[2][10][20]/F");
    _hTree->Branch("jet_track_d0", data._jet_track_d0, "jet_track_d0[2][10][20]/F");
    _hTree->Branch("jet_track_phi", data._jet_track_phi, "jet_track_phi[2][10][20]/F");
		
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
    _hTree->Branch("Top1truthAngle", &data._Top1truthAngle, "Top1truthAngle/F");
    _hTree->Branch("Top1bntracks", &data._Top1bntracks, "Top1bntracks/I");
    _hTree->Branch("Top1bTVCM", &data._Top1bTVCM, "Top1bTVCM/I");
    _hTree->Branch("Top1cosWb", &data._Top1cosWb, "Top1cosWb/F");
    _hTree->Branch("Top1Vtx", &data._Top1Vtx, "Top1Vtx/I");
    _hTree->Branch("Top1Kaon", &data._Top1Kaon, "Top1Kaon/I");
    _hTree->Branch("Top1KaonNumber", &data._Top1KaonNumber, "Top1KaonNumber/I");
    _hTree->Branch("Top1KaonCharges", data._Top1KaonCharges, "Top1KaonCharges[Top1KaonNumber]/I");
    _hTree->Branch("Top1KaonMomentum", data._Top1KaonMomentum, "Top1KaonMomentum[Top1KaonNumber]/F");
    _hTree->Branch("Top2mass", &data._Top2mass, "Top2mass/F");
    _hTree->Branch("Top2bmomentum", &data._Top2bmomentum, "Top2bmomentum/F");
    _hTree->Branch("Top2bdistance", &data._Top2bdistance, "Top2bdistance/F");
    _hTree->Branch("Top2bcharge", &data._Top2bcharge, "Top2bcharge/I");
    _hTree->Branch("Top2bcostheta", &data._Top2bcostheta, "Top2bcostheta/F");
    _hTree->Branch("Top2bTVCM", &data._Top2bTVCM, "Top2bTVCM/I");
    _hTree->Branch("Top2bntracks", &data._Top2bntracks, "Top2bntracks/I");
    _hTree->Branch("Top2leptonCharge", &data._Top2leptonCharge, "Top2leptonCharge/I");
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
    _hTree->Branch("method", data._method, "method[6]/I");
    _hTree->Branch("qCostheta", data._qCostheta, "qCostheta[2]/F");
    //_hTree->Branch("chiHad", &data._chiHad, "chiHad/F");
    //_hTree->Branch("chiTopMass", &data._chiTopMass, "chiTopMass/F");
    //_hTree->Branch("chiTopE", &data._chiTopE, "chiTopE/F");
    //_hTree->Branch("chiPbstar", &data._chiPbstar, "chiPbstar/F");
    //_hTree->Branch("chiCosWb", &data._chiCosWb, "chiCosWb/F");
    //_hTree->Branch("chiGammaT", &data._chiGammaT, "chiGammaT/F");
    _hTree->Branch("gammaT", &data._gammaT, "gammaT/F");
		
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
