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
  void TreeWriter::InitializeStatsBBBarTree(TTree * _hTree, StatsData & data)
	{

		_hTree->Branch("qMCcostheta", data._qMCcostheta, "qMCcostheta[2]/F");
		_hTree->Branch("MCMass", &data._MCMass, "MCMass/F");
		_hTree->Branch("MCPDG", &data._MCPDG, "MCPDG/F");
		//_hTree->Branch("MCPt", &data._MCPt, "MCPt/F");
		_hTree->Branch("B1momentum", &data._B1momentum, "B1momentum/F");
		_hTree->Branch("B2momentum", &data._B2momentum, "B2momentum/F");
		_hTree->Branch("B1Jetmomentum", &data._B1Jetmomentum, "B1Jetmomentum/F");
		_hTree->Branch("B2Jetmomentum", &data._B2Jetmomentum, "B2Jetmomentum/F");
		_hTree->Branch("B1mass", &data._B1mass, "B1mass/F");
		_hTree->Branch("B2mass", &data._B2mass, "B2mass/F");
		_hTree->Branch("B1btag", &data._B1btag, "B1btag/F");
		_hTree->Branch("B2btag", &data._B2btag, "B2btag/F");
		_hTree->Branch("B1chargeBalance", &data._B1chargeBalance, "B1chargeBalance/F");
		_hTree->Branch("B2chargeBalance", &data._B2chargeBalance, "B2chargeBalance/F");
		_hTree->Branch("B1charge", &data._B1charge, "B1charge/I");
		_hTree->Branch("B2charge", &data._B2charge, "B2charge/I");
		_hTree->Branch("B1VtxTag", &data._B1VtxTag, "B1VtxTag/I");
		_hTree->Branch("B2VtxTag", &data._B2VtxTag, "B2VtxTag/I");
		_hTree->Branch("B1KaonTag", &data._B1KaonTag, "B1KaonTag/I");
		_hTree->Branch("B2KaonTag", &data._B2KaonTag, "B2KaonTag/I");
		_hTree->Branch("B1costheta", &data._B1costheta, "B1costheta/F");
		_hTree->Branch("B2costheta", &data._B2costheta, "B2costheta/F");
		_hTree->Branch("B1truthAngle", &data._B1truthAngle, "B1truthAngle/F");
		_hTree->Branch("bbbarAngle", &data._bbbarAngle, "bbbarAngle/F");
		_hTree->Branch("bbbarPt", &data._bbbarPt, "bbbarPt/F");
		_hTree->Branch("bbbarP", &data._bbbarP, "bbbarP/F");
		_hTree->Branch("bbbar4JetMass", &data._bbbar4JetMass, "bbbar4JetMass/F");
		_hTree->Branch("InvMass", &data._InvMass, "InvMass/F");
		_hTree->Branch("Sphericity", &data._Sphericity, "Sphericity/F");
		_hTree->Branch("Thrust", &data._Thrust, "Thrust/F");
		_hTree->Branch("B1Y", &data._B1Y, "B1Y/F");
		_hTree->Branch("B2Y", &data._B2Y, "B2Y/F");
		_hTree->Branch("ZZMass1", &data._ZZMass1, "ZZMass1/F");
		_hTree->Branch("ZZMass2", &data._ZZMass2, "ZZMass2/F");
		_hTree->Branch("maxPhotonEnergy", &data._maxPhotonEnergy, "maxPhotonEnergy/F");
		_hTree->Branch("kaonMomentum", &data._kaonMomentum, "kaonMomentum/F");
		_hTree->Branch("maxPhotonCostheta", &data._maxPhotonCostheta, "maxPhotonCostheta/F");
		_hTree->Branch("qCostheta", data._qCostheta, "qCostheta[2]/F");
		_hTree->Branch("qCostheta1", &data._qCostheta1, "qCostheta1/F");
		_hTree->Branch("qCostheta2", &data._qCostheta2, "qCostheta2/F");
		_hTree->Branch("methodUsed", &data._methodUsed, "methodUsed/I");
		_hTree->Branch("methodRefused", &data._methodRefused, "methodRefused/I");
		_hTree->Branch("methodZero", &data._methodZero, "methodZero/I");
		_hTree->Branch("methodCorrect", &data._methodCorrect, "methodCorrect/I");
		_hTree->Branch("methodSameCharge", data._methodSameCharge, "methodSameCharge[methodRefused]/I");
		_hTree->Branch("methodZeroCharge", data._methodZeroCharge, "methodZeroCharge[methodZero]/I");
		_hTree->Branch("methodTaken", data._methodTaken, "methodTaken[methodUsed]/I");
		
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
		_hTree->Branch("MCBWcorrect", &data._MCBWcorrect, "MCBWcorrect/I");
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
		_hTree->Branch("Top1bmomentum", &data._Top1bmomentum, "Top1bmomentum/F");
		_hTree->Branch("Top1bdistance", &data._Top1bdistance, "Top1bdistance/F");
		_hTree->Branch("Top1costheta", &data._Top1costheta, "Top1costheta/F");
		_hTree->Branch("Top1bcostheta", &data._Top1bcostheta, "Top1bcostheta/F");
		_hTree->Branch("Top1truthAngle", &data._Top1truthAngle, "Top1truthAngle/F");
		_hTree->Branch("Top1bntracks", &data._Top1bntracks, "Top1bntracks/I");
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
		_hTree->Branch("Top2bcostheta", &data._Top2bcostheta, "Top2bcostheta/F");
		_hTree->Branch("Top2bTVCM", &data._Top2bTVCM, "Top2bTVCM/I");
		_hTree->Branch("Top2bntracks", &data._Top2bntracks, "Top2bntracks/I");
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
