#include "TTbarAnalysis.hh"
#include "marlin/Exceptions.h"

using namespace lcio ;
using namespace marlin ;
using std::vector;
using std::string;
using std::abs;
using EVENT::Track;
using IMPL::ReconstructedParticleImpl;
using EVENT::ParticleID;
using IMPL::ParticleIDImpl;

namespace QQbarProcessor
{

	TTbarAnalysis:: TTbarAnalysis() {}

	void TTbarAnalysis::Init(std::string _hfilename, int type, float masscut) 
	{ 

		TreeWriter writer;
		_hfile = new TFile( _hfilename.c_str(), "RECREATE", _hfilename.c_str() ) ;
		_hSumTree = new TTree( "Summary", "tree" );
		writer.InitializeSummaryTree(_hSumTree, _summary);
		_hGenTree = new TTree( "GenTree", "tree" );
		_hGenTree->Branch("qMCcostheta", _stats._qMCcostheta, "qMCcostheta[2]/F");
		_hGenTree->Branch("MCMass", &_stats._MCMass, "MCMass/F");
		_hGenTree->Branch("MCPDG", &_stats._MCPDG, "MCPDG/F");
		_hGenTree->Branch("MCquarkAngle", &_stats._MCquarkAngle, "MCMass/F");
		_hGenTree->Branch("qMCBcostheta", _stats._qMCBcostheta, "qMCBcostheta[2]/F");
		_hGenTree->Branch("MCLeptonPDG", &_stats._MCLeptonPDG, "MCLeptonPDG/I");
		_hGenTree->Branch("singletopFlag", &_stats._singletopFlag, "singletopFlag/I");
		_hTree = new TTree( "Stats", "tree" );


		if(type==0) writer.InitializeStatsTree(_hTree, _stats);
		else if(type==1) writer.InitializeStatsHadronicTree(_hTree, _stats);

		_massCutparameter=masscut;

		_lowBTagCutparameter = 0.3;
		_highBTagCutparameter = 0.8;
		_WMassparameter = 80.3;
		_WMassSigmaparameter = 6.3;
		_TopMassparameter = 174;
		_TopMassSigmaparameter = 6.3;
		_EBeamparameter = 250.0;
		_EBeamSigmaparameter = 8;
		_PStarparameter = 68.0;
		_PStarSigmaparameter = 5;
		_CosbWparameter = 0.23;
		_CosbWSigmaparameter = 0.14;
		_GammaTparameter = 1.435;
		_GammaTSigmaparameter = 0.05;
	}

	void TTbarAnalysis::getBHadrons(vector< MCParticle * > & Bhad)
	{
		for(int iB=0; iB < Bhad.size(); iB++)
		{
			int pdg = Bhad[iB]->getPDG();
			_stats._MCBHadCharge = Bhad[iB]->getCharge();
			_stats._MCBHadNtracks = Bhad[iB]->getDaughters().size();
		}
	}

	vector< MCParticle * > TTbarAnalysis::AnalyseGenerator(QQbarMCOperator & opera)
	{
		std::vector< EVENT::MCParticle * > mctops = opera.GetTopPairParticles(_stats._MCTopBangle, _stats._MCTopcosWb);

		if (mctops.size() < 2) 
		{
			_stats._mctag = 0;
			return mctops;
		}

		_summary._nGenUsed++;
		MCParticle * top    = mctops[0];
		MCParticle * topbar = mctops[1];

		//std::cout << "mcB0 size = " << mcB0.size() << "\n";
		//std::cout << "mcBplus size = " << mcBplus.size() << "\n";

		BHadronHandler(opera);

		vector<float> direction = MathOperator::getDirection(top->getMomentum());
		vector<float> directionbar = MathOperator::getDirection(topbar->getMomentum());
		_stats._MCTopmass = top->getMass();
		_stats._MCTopBarmass = topbar->getMass();
		_stats._MCTopmomentum = MathOperator::getModule(top->getMomentum());
		_stats._MCTopBarmomentum = MathOperator::getModule(topbar->getMomentum());
		_stats._MCTopcostheta = std::cos( MathOperator::getAngles(direction)[1] );
		_stats._MCTopBarcostheta = std::cos( MathOperator::getAngles(directionbar)[1] );
		_stats._MCquarkAngle =  MathOperator::getAngleBtw(top->getMomentum(), topbar->getMomentum());
		std::cout << "Top costheta: " << _stats._MCTopcostheta << "\n";
		std::cout << "TopBar costheta: " << _stats._MCTopBarcostheta << "\n";
		if (_stats._MCTopmass > 170.0 && _stats._MCTopmass < 181.0 && _stats._MCTopBarmass > 170.0 && _stats._MCTopBarmass < 181.0) 
		{
			_stats._mctag = 1;
		}
		else 
		{
			_stats._mctag = 0;
		}

		vector< EVENT::MCParticle * > mcbs = opera.GetBquarkPair();
		vector< EVENT::MCParticle * > mcws = opera.GetWPair();

		SingleTopAnalyzer(mctops, mcbs, mcws);

		MCParticle * mcb    = mcbs[0];
		MCParticle * mcbbar = mcbs[1];

		MCParticle * mcWplus  = mcws[0];
		MCParticle * mcWminus = mcws[1];

		_stats._MCWplusmass = mcWplus->getMass();
		_stats._MCWminusmass = mcWminus->getMass();

		vector<float> bdirection = MathOperator::getDirection(mcb->getMomentum());
		vector<float> bdirectionbar = MathOperator::getDirection(mcbbar->getMomentum());

		_stats._MCBEnergy[0] = mcb->getEnergy();
		_stats._MCBEnergy[1] = mcbbar->getEnergy();

		_stats._qMCBcostheta[0] =  std::cos( MathOperator::getAngles(bdirection)[1] );
		_stats._qMCBcostheta[1] =  -std::cos( MathOperator::getAngles(bdirectionbar)[1] );
		_stats._qMCcostheta[0] = _stats._MCTopcostheta;//(std::abs(_stats._qMCBcostheta[0]) < 0.9 )? _stats._MCTopcostheta: -2;
		_stats._qMCcostheta[1] = -_stats._MCTopBarcostheta;//(std::abs(_stats._qMCBcostheta[1]) < 0.9 )? -_stats._MCTopBarcostheta : -2;
		_hGenTree->Fill();

		vector <MCParticle *> final = opera.GetFinalState();
		for (unsigned int i = 0; i < final.size(); i++) 
		{
			if (abs(final[i]->getPDG()) == 11 || abs(final[i]->getPDG()) == 13 || abs(final[i]->getPDG()) == 15) 
			{
				_stats._MCLeptonMomentum = MathOperator::getModule(final[i]->getMomentum());
				vector<float> ldirection = MathOperator::getDirection(final[i]->getMomentum());
				_stats._MCLeptonCostheta = std::cos(MathOperator::getAngles(ldirection)[1]);
				_stats._MCLeptonPDG = final[i]->getPDG();
			}
		}
		if (abs(_stats._MCLeptonPDG) == 15) 
		{
			MCParticle * newlepton = opera.GetTauLepton();
			if (newlepton) 
			{
				_stats._MCLeptonMomentum = MathOperator::getModule(newlepton->getMomentum());
				vector<float> ldirection = MathOperator::getDirection(newlepton->getMomentum());
				_stats._MCLeptonCostheta = std::cos(MathOperator::getAngles(ldirection)[1]);
			}
			else 
			{
				_stats._MCLeptonMomentum = -1;
				_stats._MCLeptonCostheta = -1;
			}
		}
		MCParticle * neutrino = opera.GetNeutrino();
		if (neutrino) 
		{
			_stats._MCNeutrinoEnergy = neutrino->getEnergy();
		}
		return mctops;
	}

	void TTbarAnalysis::AnalyseTTbarSemiLeptonic( LCEvent * evt,
			std::string _colName ,
			std::string _MCColName ,
			std::string _JetsColName ,
			std::string _JetsRelColName ,
			std::string _IsoLeptonColName,
			std::string _MCVtxColName ,
			std::string _colRelName
			)
	{
		LCCollection * mcvtxcol = NULL;
		try
		{
			mcvtxcol = evt->getCollection(_MCVtxColName);
		}
		catch(DataNotAvailableException &e)
		{
			std::cout << e.what() <<"\n";
		}

		try
		{
			std::cout << "***************Analysis*" <<_summary._nEvt++<<"*****************\n";

			LCCollection * isoleptoncol = evt->getCollection(_IsoLeptonColName);
			LCCollection * jetcol = evt->getCollection(_JetsColName);
			LCCollection * jetrelcol = evt->getCollection(_JetsRelColName);
			LCCollection * mccol = evt->getCollection(_MCColName);
			//LCCollection * mcvtxcol = evt->getCollection(_MCVtxColName);
			QQbarMCOperator opera(mccol);
			VertexChargeOperator vtxOperator(evt->getCollection(_colName),evt->getCollection(_colRelName));
			vector < MCParticle * > mctops = AnalyseGenerator(opera);
			vector< RecoJet * > * jets = QQbarTools::getJets(jetcol, jetrelcol);
			vector< RecoJet * > * wjets = new vector< RecoJet * >();
			vector< RecoJet * > * bjets = QQbarTools::getBTagJets(jets, wjets);
			LCCollection * pfocol = evt->getCollection(_colName);
			_stats._Thrust = pfocol->getParameters().getFloatVal("majorThrustValue");


			std::cout << "B jets: \n";
			QQbarTools::PrintJets(bjets);
			std::cout << "W jets: \n";
			QQbarTools::PrintJets(wjets);
			if (!isoleptoncol || isoleptoncol->getNumberOfElements() == 0) 
			{
				std::cout << "No IsoLepton!\n";
				if (isoleptoncol) 
				{
					int IsTau = isoleptoncol->parameters().getIntVal("isLeptonFromTau");
					if (IsTau) 
					{
						std::cout << " IsoLepton is tau! \n";
					}
				}
				else 
				{
					std::cout << " No IsoLepton collection!!! \n";
				}
				return;
			}
			ReconstructedParticle * wLeptonic = NULL;
			std::cout << "\nIsoLeptons:\n";
			for (int i = 0; i < isoleptoncol->getNumberOfElements(); i++) 
			{
				ReconstructedParticle * particle = dynamic_cast< ReconstructedParticle * >(isoleptoncol->getElementAt(i));
				if (particle->getType() != 22) 
				{
					wLeptonic = particle;
				}
				QQbarTools::PrintParticle(particle);
			}
			if (!wLeptonic) 
			{
				std::cout << "No IsoLepton!!! \n";
				return;
			}
			_summary._nAfterLeptonCuts++;
			if (!bjets || bjets->size() != 2 ) 
			{
				std::cout << "No B jets!!! \n";
				return;
			}
			if ((bjets->at(0)->GetBTag() <  _lowBTagCutparameter && bjets->at(1)->GetBTag() <  _lowBTagCutparameter ) ||bjets->at(0)->GetBTag() < _highBTagCutparameter ) 
			{
				std::cout << "No high B jets!!! \n";
				return;
			}
			_summary._nAfterBtagCuts++;
			float chimin = 100000.0;
			RecoJet * wHadronic = new TopQuark(wjets->at(0), wjets->at(1));
			vector<float> direction = MathOperator::getDirection(wHadronic->getMomentum());
			_stats._W1costheta = std::cos (MathOperator::getAngles(direction)[1]);
			//if (isoleptoncol->getNumberOfElements() > 1) 
			std::cout << '\n';
			vector<float> directionL = MathOperator::getDirection(wLeptonic->getMomentum());
			_stats._W2costheta = std::cos (MathOperator::getAngles(directionL)[1]);
			TopQuark * topHadronic = NULL;
			TopQuark * topLeptonic = NULL;
			int chosen = -1;

			for (unsigned int ijet = 0; ijet < bjets->size(); ijet++) 
			{
				TopQuark * candidate = new TopQuark(bjets->at(ijet), wHadronic);
				ReconstructedParticle * bjet = bjets->at(ijet)->GetRawRecoJet();

				// access jet info
				_stats._jet_E[ijet] = bjets->at(ijet)->getEnergy();
				_stats._jet_px[ijet]= bjets->at(ijet)->getMomentum()[0];
				_stats._jet_py[ijet]= bjets->at(ijet)->getMomentum()[1];
				_stats._jet_pz[ijet]= bjets->at(ijet)->getMomentum()[2];
				_stats._jet_M[ijet] = bjets->at(ijet)->getMass();

				// access jet vetice info
				vector< Vertex * > * vertices = bjets->at(ijet)->GetRecoVertices();
				int verticeSize = vertices->size();
				_stats._jet_nvtx[ijet]=verticeSize;
				streamlog_out(DEBUG)<<"nvertices = "<<verticeSize<<std::endl;

				for(int ivtx=0; ivtx < verticeSize; ivtx++){
					streamlog_out(DEBUG)<<"   ivtx = "<<ivtx<<std::endl;

					_stats._jet_ntrack[ijet]+=vertices->at(ivtx)->getAssociatedParticle()->getParticles().size();
					_stats._jet_vtx_isprimary[ijet][ivtx]=vertices->at(ivtx)->isPrimary();
					_stats._jet_vtx_ntrack[ijet][ivtx]=vertices->at(ivtx)->getAssociatedParticle()->getParticles().size();
					_stats._jet_vtx_charge[ijet][ivtx]=vertices->at(ivtx)->getAssociatedParticle()->getCharge();

					int ntrack = vertices->at(ivtx)->getAssociatedParticle()->getParticles().size();
					streamlog_out(DEBUG)<<"   ntracks = "<<ntrack<<std::endl;

					for(int itr=0; itr< ntrack; itr++) {

						streamlog_out(DEBUG)<<"      itr= "<<itr<<std::endl;
						if(vertices->at(ivtx)->getAssociatedParticle()->getParticles().at(itr)==NULL) continue;

						ReconstructedParticle * found_track_particle = vertices->at(ivtx)->getAssociatedParticle()->getParticles().at(itr);

						_stats._jet_track_charge[ijet][ivtx][itr]=found_track_particle->getCharge();
						_stats._jet_track_E[ijet][ivtx][itr]=found_track_particle->getEnergy();
						_stats._jet_track_px[ijet][ivtx][itr]=found_track_particle->getMomentum()[0];
						_stats._jet_track_py[ijet][ivtx][itr]=found_track_particle->getMomentum()[1];
						_stats._jet_track_pz[ijet][ivtx][itr]=found_track_particle->getMomentum()[2];
						_stats._jet_track_p[ijet][ivtx][itr]=MathOperator::getModule(found_track_particle->getMomentum());

						streamlog_out(DEBUG)<<"      Tracks Test  --  "<<ivtx<<" "<<itr<<" "<<found_track_particle->getTracks().size()<<" "<<found_track_particle->getEnergy()<< " " <<found_track_particle->getTracks()[0]->getZ0()<<" "<<found_track_particle->getCharge()<<std::endl;

						_stats._jet_track_z0[ijet][ivtx][itr]=found_track_particle->getTracks()[0]->getZ0();
						_stats._jet_track_d0[ijet][ivtx][itr]=found_track_particle->getTracks()[0]->getD0();
						_stats._jet_track_phi[ijet][ivtx][itr]=found_track_particle->getTracks()[0]->getPhi();

					}//itr


				}




				float chi2 = getChi2(candidate);
				if (chi2 < chimin) 
				{
					topHadronic = candidate;
					chimin = chi2;
					chosen = ijet;
					_stats._Top1cosWb = std::cos( MathOperator::getAngle(candidate->GetB()->getMomentum(), candidate->GetW()->getMomentum()) );
				}

			} // end bjets

			if (chosen && wLeptonic) 
			{
				topLeptonic = new TopQuark(bjets->at(0), wLeptonic);
				// Yuichi Test
				//std::cout << "test begin\n";
				//std::cout << "Yuichi Test = " << bjets->at(0)->GetRecoVertices()->at(1)->getAssociatedParticle()->getParticles().size() << "\n";
			}
			if (!chosen && wLeptonic) 
			{
				topLeptonic = new TopQuark(bjets->at(1), wLeptonic);
			}
			/*if (chosen) 
				{
				topLeptonic = new TopQuark(bjets->at(0));
				}
				if (!chosen) 
				{
				topLeptonic = new TopQuark(bjets->at(1));
				}*/

			_stats._cosbjets = std::cos( MathOperator::getAngle(bjets->at(0)->getMomentum(), bjets->at(1)->getMomentum() ));

			_stats._W1mass = wHadronic->getMass();
			_stats._W1momentum = MathOperator::getModule(wHadronic->getMomentum());
			_stats._W2momentum = MathOperator::getModule(wLeptonic->getMomentum());
			_stats._Top1mass = topHadronic->getMass();
			_stats._Top1energy = topHadronic->getEnergy();
			_stats._chiHad = getChi2(topHadronic);
			float momentum[3];
			for (unsigned int i = 0; i < 3; i++) 
			{
				momentum[i] = topHadronic->getMomentum()[i]+topLeptonic->GetB()->getMomentum()[i];
			}
			_stats._hadMass = std::sqrt(pow(topHadronic->getEnergy()+topLeptonic->GetB()->getEnergy(),2) - momentum[0]* momentum[0]-momentum[1]*momentum[1]-momentum[2]*momentum[2]);
			vector< EVENT::MCParticle * > mcbquarks = opera.GetBquarkPair();
			vector< EVENT::MCParticle * > mcws = opera.GetWPair();
			Match(mctops, mcbquarks, mcws, topHadronic);
			//MatchB(mcbquarks, topHadronic, topLeptonic, mcvtxcol);
			ComputeCharge(topHadronic, topLeptonic);

			ComputeChargeTVCM(topHadronic, topLeptonic, vtxOperator);

			DecideOnAsymmetry(topHadronic, topLeptonic, 0);
			if (_stats._methodUsed && wHadronic->getMass() < 110 && topHadronic->getMass() < 200) 
			{
				_summary._nAfterMassCuts++;
			}
			test(topHadronic, topLeptonic, bjets, wjets, wLeptonic);
			//__ComputeChargeCheat(topHadronic, topLeptonic);
			_hTree->Fill();
			ClearVariables();
		}
		catch(DataNotAvailableException &e)
		{
			std::cout << e.what() <<"\n";
		}
	}
	void TTbarAnalysis::ComputeChargeTVCM(TopQuark * top, TopQuark * top2, VertexChargeOperator & vtxOperator)
	{
		vtxOperator.GetAsymmetryTVCM(top, top2);
		_stats._Top1Kaon = (top->GetComputedCharge().ByTVCM )? 1:0;
		_stats._Top2Kaon = (top2->GetComputedCharge().ByTVCM )? 1:0;
		_stats._UsedBTVCM = vtxOperator.GetResultingB();
		vector< ReconstructedParticle * > kaons1 = vtxOperator.GetKaons(top);
		vector< ReconstructedParticle * > kaons2 = vtxOperator.GetKaons(top2);
		_stats._Top1KaonNumber = kaons1.size();
		_stats._Top2KaonNumber = kaons2.size();

		if (top->GetComputedCharge().ByTVCM || top2->GetComputedCharge().ByTVCM) 
		{
			_summary._nKaons++;
		}
		//_summary._nKaons += vtxOperator.CountKaons(topHadronic, topLeptonic);
		//std::cout << "Kaons 1 :\n";

		int nkchg = 0;

		for (unsigned int i = 0; i < kaons1.size(); i++) 
		{
			_stats._Top1KaonCharges[i] = kaons1[i]->getCharge();
			nkchg += kaons1[i]->getCharge();
			_stats._Top1KaonMomentum[i] = MathOperator::getModule(kaons1[i]->getMomentum());
			//std::cout << "\tq: " <<  kaons1[i]->getCharge() << " p: " << MathOperator::getModule(kaons1[i]->getMomentum()) <<"\n";

			// kaon dEdx implementation
			_stats._Top1KaondEdx[i] = kaons1[i]->getTracks()[0]->getdEdx();

		}

		_stats._Top1TotalKaonCharge = nkchg;
		nkchg=0;

		//std::cout << "Kaons 2 :\n";
		for (unsigned int i = 0; i < kaons2.size(); i++) 
		{
			_stats._Top2KaonCharges[i] = kaons2[i]->getCharge();
			nkchg += kaons2[i]->getCharge();
			_stats._Top2KaonMomentum[i] = MathOperator::getModule(kaons2[i]->getMomentum());
			//std::cout << "\tq: " <<  kaons2[i]->getCharge() << " p: " << MathOperator::getModule(kaons2[i]->getMomentum()) <<"\n";
		}

		_stats._Top2TotalKaonCharge = nkchg;

	}
	void TTbarAnalysis::test(TopQuark * top, TopQuark * top2, vector< RecoJet * > * bjets, vector< RecoJet * > * wjets, ReconstructedParticle * lepton)
	{	
		_stats._totalEnergy = top->getEnergy() + top2->getEnergy();
		_stats._missedEnergy = 2*_EBeamparameter - _stats._totalEnergy;
		float momentum[3];
		float wmomentum[3];
		float sum = 0;
		float sum2 = 0;
		float sum3 = 0;
		for (unsigned int i = 0; i < 3; i++) 
		{
			momentum[i] = (-1)*(bjets->at(0)->getMomentum()[i] + bjets->at(1)->getMomentum()[i] + wjets->at(1)->getMomentum()[i] + wjets->at(0)->getMomentum()[i] + lepton->getMomentum()[i]);
			sum += std::pow(momentum[i] + lepton->getMomentum()[i],2);
			wmomentum[i] = momentum[i] + lepton->getMomentum()[i];
			sum2 +=  std::pow(wmomentum[i] + top2->GetB()->getMomentum()[i],2);
			sum3 += std::pow(top->GetB()->getMomentum()[i] + top2->GetB()->getMomentum()[i] ,2);
		}
		float energy = MathOperator::getModule(momentum);
		std::cout << "Np: " << MathOperator::getModule(momentum) << " diff: " << _stats._missedEnergy - MathOperator::getModule(momentum) << "\n";
		_stats._W2mass = std::sqrt( pow(energy + lepton->getEnergy(),2) - sum);
		float wenergy =std::sqrt( _stats._W2mass * _stats._W2mass + std::pow(MathOperator::getModule(wmomentum),2));
		_stats._Top2mass = std::sqrt( pow(wenergy + top2->GetB()->getEnergy(),2) - sum2);
		_stats._Top2energy = std::sqrt( _stats._Top2mass * _stats._Top2mass  +  sum2);
		_stats._Top2gamma = _stats._Top2energy / _stats._Top2mass;
		std::cout << "W2m: " << _stats._W2mass << "\n";
		_stats._bProduct = std::sqrt(sum3);
		_stats._chiTop2Mass = std::pow(_stats._Top2mass - _TopMassparameter, 2) / std::pow( _TopMassSigmaparameter, 2) ;
		_stats._chiTop2E = std::pow(_stats._Top2energy - _EBeamparameter , 2) / std::pow( _EBeamSigmaparameter, 2); 
		_stats._chiGammaT2 = std::pow( _stats._Top2gamma - _GammaTparameter, 2) / std::pow( _GammaTSigmaparameter, 2); 
	}
	void TTbarAnalysis::ComputeCharge(TopQuark * top1, TopQuark * top2)
	{
		//Top hadronic
		_stats._qCostheta[0] = -2.;
		_stats._Top1bcharge = top1->GetHadronCharge();

		_stats._Top1bmomentum = top1->GetHadronMomentum();
		//_stats._Top1bmomentum = MathOperator::getModule(top1->GetB()->getMomentum());

		_stats._Top1bdistance = top1->GetMinHadronDistance();
		vector<float> direction = MathOperator::getDirection(top1->getMomentum());
		_stats._Top1costheta =  std::cos( MathOperator::getAngles(direction)[1] );

		// Number of b tracks
		_stats._Top1bntracks = top1->GetNumberOfVertexParticles();
		_stats._Top1Genbntracks = top1->GetB()->__GetMCNtracks();
		_stats._Top1btag = top1->GetBTag();

		_stats._Top1gamma = top1->getEnergy()/top1->getMass();
		_stats._W1gamma = top1->GetW()->getEnergy()/top1->GetW()->getMass();
		float Top1nvtx = top1->GetNumberOfVertices();
		vector<float> bdirection = MathOperator::getDirection(top1->GetB()->getMomentum());
		// no abs
		//_stats._Top1bcostheta =std::abs( std::cos( MathOperator::getAngles(bdirection)[1] ));
		_stats._Top1bcostheta = std::cos( MathOperator::getAngles(bdirection)[1] );
		std::cout << "Top charge: " << _stats._Top1bcharge
			<< " top pB: " << _stats._Top1bmomentum
			<< " top W: " <<  MathOperator::getModule(top1->GetW()->getMomentum())//_stats._Top1bmomentum
			<< " top bntracks: " << _stats._Top1bntracks
			<< " top btag: " << _stats._Top1btag
			<< " top bcostheta: " << _stats._Top1bcostheta
			<< "\n";
		//Top Leptonic
		_stats._Top2bmomentum = top2->GetHadronMomentum();
		//_stats._Top2bmomentum = MathOperator::getModule(top2->GetB()->getMomentum());

		_stats._Top2bdistance = top2->GetMinHadronDistance();
		_stats._Top2bcharge = top2->GetHadronCharge();
		vector<float> direction2 = MathOperator::getDirection(top2->getMomentum());
		_stats._Top2costheta =  std::cos( MathOperator::getAngles(direction2)[1] );

		// Number of b tracks
		_stats._Top2bntracks = top2->GetNumberOfVertexParticles();
		_stats._Top2Genbntracks = top2->GetB()->__GetMCNtracks();

		_stats._Top2leptonCharge = top2->GetW()->getCharge();
		vector<float> ldirection = MathOperator::getDirection(top2->GetW()->getMomentum());
		_stats._Top2leptonE = top2->GetW()->getEnergy();
		_stats._Top2leptonCos = std::abs( std::cos( MathOperator::getAngles(ldirection)[1] ));
		_stats._Top2btag = top2->GetBTag();
		vector<float> bdirection2 = MathOperator::getDirection(top2->GetB()->getMomentum());
		_stats._Top2bcostheta =std::abs( std::cos( MathOperator::getAngles(bdirection2)[1] ));
		float Top2nvtx = top2->GetNumberOfVertices();
		std::cout << "Top charge: " << _stats._Top2bcharge
			<< " top pB: " << _stats._Top2bmomentum
			<< " top W: " << MathOperator::getModule(top2->GetW()->getMomentum())
			<< " top bntracks: " << _stats._Top2bntracks
			<< " top btag: " << _stats._Top2btag
			<< " top bcostheta: " << _stats._Top2bcostheta
			<< "\n";
		float pcut = 0;
		bool trustTop1 = false;
		bool trustTop2 = false;
		if (//_stats._Top1bmomentum > pcut && 
				abs( _stats._Top1bcharge) > 0 &&
				//_stats._Top1bmomentum > pcut
				_stats._Top1bntracks > 0 //&& 
				//_stats._Top1bntracks < 9 //&& 
			 )  //  _stats._Top1bntracks < 7 
		{
			_stats._Top1Vtx = 1;
			JetCharge & topCharge = top1->GetComputedCharge();
			topCharge.ByTrackCount = new int(top1->GetHadronCharge());
		}
		if (//_stats._Top2bmomentum > pcut2 && 
				abs( _stats._Top2bcharge) > 0 && 
				//_stats._Top2bmomentum > pcut
				_stats._Top2bntracks > 0 //&& 
				//_stats._Top2bntracks < 9 //&& 
			 ) 
		{
			_stats._Top2Vtx = 1;
			JetCharge & topCharge = top2->GetComputedCharge();
			topCharge.ByTrackCount = new int(top2->GetHadronCharge());
		}
		if ( _stats._Top2bcharge != 0 ||  _stats._Top1bcharge != 0) 
		{
			_summary._nChargedB++;
		}
		if (top2->GetW()) 
		{
			top2->GetComputedCharge().ByLepton = new int(top2->GetW()->getCharge());
		}
		bool useLepton = (_ePolarization > 0)? false : true; //Lepton by default
	}
	void TTbarAnalysis::DecideOnAsymmetry(TopQuark * top1, TopQuark * top2, int type)
	{

		float btagcut = 0.;
		float pcut = 0.;

		//Print
		if(type == 0){

			std::cout << "\t\tTracks\tTVCM\tLepton\tp\n";
			std::cout << "Top1:\t" << QQbarTools::intToStr(top1->GetComputedCharge().ByTrackCount) <<"\t"
				<< QQbarTools::intToStr(top1->GetComputedCharge().ByTVCM) <<"\t"
				<< QQbarTools::intToStr(top1->GetComputedCharge().ByLepton) <<"\t"
				<< _stats._Top1bmomentum <<"\n";
			std::cout << "Top2:\t" << QQbarTools::intToStr(top2->GetComputedCharge().ByTrackCount) <<"\t"
				<< QQbarTools::intToStr(top2->GetComputedCharge().ByTVCM) <<"\t"
				<< QQbarTools::intToStr(top2->GetComputedCharge().ByLepton) <<"\t"
				<< _stats._Top2bmomentum <<"\n";

			btagcut = 0.8;
			pcut = 25.;

		}else if(type == 1){

			std::cout << "\t\tTracks\tTVCM\tp\n";
			std::cout << "Top1:\t" << QQbarTools::intToStr(top1->GetComputedCharge().ByTrackCount) <<"\t"
				<< QQbarTools::intToStr(top1->GetComputedCharge().ByTVCM) <<"\t"
				<< _stats._Top1bmomentum <<"\n";
			std::cout << "Top2:\t" << QQbarTools::intToStr(top2->GetComputedCharge().ByTrackCount) <<"\t"
				<< QQbarTools::intToStr(top2->GetComputedCharge().ByTVCM) <<"\t"
				<< _stats._Top2bmomentum <<"\n";

			btagcut = 0.8;
			pcut = 15.;

		}

		_stats._MCTop1charge = top1->__GetMCCharge();
		_stats._MCTop2charge = top2->__GetMCCharge();
		_stats._qCostheta[0] = -2.;

		vector<float> direction = MathOperator::getDirection(top1->getMomentum());
		float costheta =  std::cos( MathOperator::getAngles(direction)[1] );
		//float m = top1->getMass();
		//float e = top1->getEnergy();
		vector<int> IsMethodCorrect;
		vector<int> samecharge;
		vector<int> goodcharge;
		vector<int> chargevalue;
		//if (e/m > _GammaTparameter -0.1 && top2->GetComputedCharge().ByLepton) 
		//Track charge * Track charge
		float gammacut1 = 1.23;

		// COMMENTED OUT

		if (top2->GetComputedCharge().ByTrackCount && top1->GetComputedCharge().ByTrackCount) 
		{
			int top1charge = *(top1->GetComputedCharge().ByTrackCount );
			int top2charge = *(top2->GetComputedCharge().ByTrackCount );
			if (top1charge * top2charge < 0 && ((_stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut) ||( _stats._Top2btag > btagcut && _stats._Top2bmomentum > pcut))) 
			{
				//_stats._qCostheta[0] = (top1charge < 0)? costheta: - costheta;
				std::cout << "Two vertices are used!\n";
				//_stats._methodUsed = 1;
				chargevalue.push_back(top1charge);
				goodcharge.push_back(1);
				_stats._methodCorrect = top1->__GetMCCharge() * top1charge < 0;
				IsMethodCorrect.push_back(_stats._methodCorrect);

				if (!_stats._methodCorrect) 
				{
					std::cout << "Not Correct!\n";
				}
				//_summary._nAfterKinematicCuts++;
				//return;
			}
			if (top1charge * top2charge > 0 && ((_stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut) || (_stats._Top2btag > btagcut && _stats._Top2bmomentum > pcut)))
			{
				samecharge.push_back(1);
			}
		}

		//Kaon * Kaon
		if (top2->GetComputedCharge().ByTVCM && top1->GetComputedCharge().ByTVCM) 
		{
			int top1charge = *(top1->GetComputedCharge().ByTVCM );
			int top2charge = *(top2->GetComputedCharge().ByTVCM );
			if (top1charge * top2charge < 0) 
			{
				//_stats._qCostheta[0] = (top1charge < 0)? costheta: - costheta;
				std::cout << "Two kaons are used!\n";
				chargevalue.push_back(top1charge);
				//_stats._methodUsed = 2;
				goodcharge.push_back(2);
				_stats._methodCorrect = top1->__GetMCCharge() * top1charge < 0;
				IsMethodCorrect.push_back(_stats._methodCorrect);

				if (!_stats._methodCorrect) 
				{
					std::cout << "Not Correct!\n";
				}
				///_summary._nAfterKinematicCuts++;
				//return;
			}
			if (top1charge * top2charge > 0)
			{
				samecharge.push_back(2);
			}
		}//
		//Track charge + Kaon
		if (top1->GetComputedCharge().ByTrackCount && top1->GetComputedCharge().ByTVCM) 
		{
			int top1charge = *(top1->GetComputedCharge().ByTrackCount );
			int top1kaon = *(top1->GetComputedCharge().ByTVCM );
			if (top1charge * top1kaon > 0 && _stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut) 
			{
				//_stats._qCostheta[0] = (top1charge < 0)? costheta: -costheta; 
				std::cout << "Vertex + kaon for top1 is used!\n";
				//_stats._methodUsed = 3;
				chargevalue.push_back(top1charge);
				goodcharge.push_back(3);
				_stats._methodCorrect = top1->__GetMCCharge() * top1charge < 0;
				IsMethodCorrect.push_back(_stats._methodCorrect);

				if (!_stats._methodCorrect) 
				{
					std::cout << "Not Correct!\n";
				}
				//_summary._nAfterKinematicCuts++;
				//return;
			}
			if (top1charge * top1kaon < 0 && _stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut) 
			{
				samecharge.push_back(3);
			}
		}
		if (top2->GetComputedCharge().ByTrackCount && top2->GetComputedCharge().ByTVCM) 
		{
			int top2charge = *(top2->GetComputedCharge().ByTrackCount );
			int top2kaon = *(top2->GetComputedCharge().ByTVCM );
			if (top2charge * top2kaon > 0 && _stats._Top2btag > btagcut && _stats._Top2bmomentum > pcut) 
			{
				//_stats._qCostheta[0] = (top2charge > 0)? costheta: - costheta; 
				std::cout << "Vertex + kaon for top2 is used!\n";
				//_stats._methodUsed = 4;
				goodcharge.push_back(3);
				chargevalue.push_back(-top2charge);
				_stats._methodCorrect = top1->__GetMCCharge() * top2charge > 0;
				IsMethodCorrect.push_back(_stats._methodCorrect);

				if (!_stats._methodCorrect) 
				{
					std::cout << "Not Correct!\n";
				}
				//_summary._nAfterKinematicCuts++;
				//return;
			}
			if (top2charge * top2kaon < 0 && _stats._Top2btag > btagcut && _stats._Top2bmomentum > pcut) 
			{
				samecharge.push_back(3);
			}
		}
		if (top1->GetComputedCharge().ByTrackCount && top2->GetComputedCharge().ByTVCM) 
		{
			int top1charge = *(top1->GetComputedCharge().ByTrackCount );
			int top2kaon = *(top2->GetComputedCharge().ByTVCM );
			if (top1charge * top2kaon < 0 &&  _stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut) 
			{
				//_stats._qCostheta[0] = (top1charge < 0)? costheta: - costheta; 
				std::cout << "Vertex1 + kaon2 is used!\n";
				//_stats._methodUsed = 5;
				chargevalue.push_back(top1charge);
				goodcharge.push_back(4);
				_stats._methodCorrect = top1->__GetMCCharge() *  top1charge < 0;
				IsMethodCorrect.push_back(_stats._methodCorrect);

				if (!_stats._methodCorrect) 
				{
					std::cout << "Not Correct!\n";
				}
				//_summary._nAfterKinematicCuts++;
				//return;
			}
			if (top1charge * top2kaon > 0 &&  _stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut)
			{
				samecharge.push_back(4);
			}
		}
		if (top2->GetComputedCharge().ByTrackCount && top1->GetComputedCharge().ByTVCM) 
		{
			int top2charge = *(top2->GetComputedCharge().ByTrackCount );
			int top1kaon = *(top1->GetComputedCharge().ByTVCM );
			if (top2charge * top1kaon < 0 &&  _stats._Top2btag > btagcut && _stats._Top2bmomentum > pcut) 
			{
				//_stats._qCostheta[0] = (top2charge > 0)? costheta: - costheta; 
				std::cout << "Vertex2 + kaon1 is used!\n";
				//_stats._methodUsed = 6;
				goodcharge.push_back(4);
				chargevalue.push_back(-top2charge);
				_stats._methodCorrect = top1->__GetMCCharge() * top1kaon< 0;
				IsMethodCorrect.push_back(_stats._methodCorrect);

				if (!_stats._methodCorrect) 
				{
					std::cout << "Not Correct!\n";
				}
				//_summary._nAfterKinematicCuts++;
				//return;
			}
			if (top2charge * top1kaon > 0 &&  _stats._Top2btag > btagcut && _stats._Top2bmomentum > pcut) 
			{
				samecharge.push_back(4);
			}
		}//

		//LEPTON
		if(type == 0){

			if (top2->GetComputedCharge().ByLepton && top2->GetComputedCharge().ByTrackCount)
			{
				int top2lepton = *(top2->GetComputedCharge().ByLepton );
				int top2charge = *(top2->GetComputedCharge().ByTrackCount );
				if (top2charge * top2lepton < 0  &&  ((_stats._Top2btag > btagcut && _stats._Top2bmomentum > pcut) || _stats._Top1gamma > gammacut1))
				{
					std::cout << "Vertex + lepton for top2 is used!\n";
					goodcharge.push_back(5);
					chargevalue.push_back(-top2charge);
					_stats._methodCorrect = top1->__GetMCCharge() * top2charge < 0;
					IsMethodCorrect.push_back(_stats._methodCorrect);

					//_summary._nAfterKinematicCuts++;
				}
				if (top2charge * top2lepton > 0 &&  _stats._Top2btag > btagcut && _stats._Top2bmomentum > pcut) 
				{
					samecharge.push_back(5);
				}
			}
			if (top2->GetComputedCharge().ByLepton && top1->GetComputedCharge().ByTrackCount)
			{
				int top2lepton = *(top2->GetComputedCharge().ByLepton );
				int top1charge = *(top1->GetComputedCharge().ByTrackCount );
				if (top1charge * top2lepton > 0 &&  ((_stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut)  || _stats._Top1gamma > gammacut1))
				{
					std::cout << "Vertex + lepton for top1 is used!\n";
					goodcharge.push_back(5);
					chargevalue.push_back(top1charge);
					_stats._methodCorrect = top1->__GetMCCharge() * top1charge < 0;
					IsMethodCorrect.push_back(_stats._methodCorrect);

				}
				if (top1charge * top2lepton < 0 &&  ((_stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut) ||_stats._Top1gamma > gammacut1)) 
				{
					samecharge.push_back(5);
				}
			}//
			if (top2->GetComputedCharge().ByLepton && top1->GetComputedCharge().ByTVCM)
			{
				int top2lepton = *(top2->GetComputedCharge().ByLepton );
				int top1charge = *(top1->GetComputedCharge().ByTVCM );
				if (top1charge * top2lepton > 0  && _stats._Top1gamma > gammacut1)
				{
					std::cout << "Vertex + lepton for top1 is used!\n";
					goodcharge.push_back(6);
					chargevalue.push_back(top1charge);
					_stats._methodCorrect = top1->__GetMCCharge() * top1charge < 0;
					IsMethodCorrect.push_back(_stats._methodCorrect);

				}
				if (top1charge * top2lepton < 0 && _stats._Top1gamma > gammacut1) 
				{
					samecharge.push_back(6);
				}
			}
			if (top2->GetComputedCharge().ByLepton && top2->GetComputedCharge().ByTVCM)
			{
				int top2lepton = *(top2->GetComputedCharge().ByLepton );
				int top2charge = *(top2->GetComputedCharge().ByTVCM );
				if (top2charge * top2lepton < 0 &&  _stats._Top1gamma > gammacut1)
				{
					std::cout << "Vertex + lepton for top1 is used!\n";
					goodcharge.push_back(6);
					chargevalue.push_back(-top2charge);
					_stats._methodCorrect = top1->__GetMCCharge() * top2charge < 0;
					IsMethodCorrect.push_back(_stats._methodCorrect);

				}
				if (top2charge * top2lepton > 0  && _stats._Top1gamma > gammacut1) 
				{
					samecharge.push_back(6);
				}
			}//

			// COMMENTED OUT

			//float chi2 = _stats._chiTopMass + _stats._chiTopE + _stats._chiGammaT + _stats._chiCosWb + _stats._chiPbstar;
			float chi2 =  _stats._chiGammaT + _stats._chiCosWb + _stats._chiPbstar;
			//if (top2->GetComputedCharge().ByLepton &&  _stats._Top1gamma > gammacut1+0.1  && goodcharge.size() == 0) 

			//if (top2->GetComputedCharge().ByLepton) 
			if (top2->GetComputedCharge().ByLepton &&  chi2 < 15) 
			{
				int top2lepton = *(top2->GetComputedCharge().ByLepton );
				//_stats._qCostheta[0] = (top2lepton < 0)? _stats._Top1costheta: -_stats._Top1costheta;
				goodcharge.push_back(7);
				chargevalue.push_back(top2lepton);
				_stats._methodCorrect = _stats._MCBWcorrect == 1;
				IsMethodCorrect.push_back(_stats._methodCorrect);

				//_stats._methodUsed = 1;
				//_stats._methodTaken[0] = 7;
				//_summary._nAfterKinematicCuts++;
				//return;
			}//
		} // if type==0

		_stats._methodRefused = samecharge.size();
		_stats._methodUsed = goodcharge.size();
		if (samecharge.size() > 0) 
		{
			std::cout << "REFUSED BY CHARGE: ";
			for (unsigned int i = 0; i < samecharge.size(); i++) 
			{
				std::cout << " " << samecharge[i];
				_stats._methodSameCharge[i] = samecharge[i];
			}
			std::cout << "\n";
		}
		if (goodcharge.size() > 0)//(_stats._methodUsed > 0 && _stats._MCMass > _massCutparameter) //CRUNCH
		{
			std::cout << "ACCEPTED BY CHARGE: ";
			for (unsigned int i = 0; i < goodcharge.size(); i++) 
			{
				std::cout << " " << goodcharge[i];
				_stats._methodTaken[i] = goodcharge[i];
				_stats._methodCheck[i] = IsMethodCorrect[i];
			}
			std::cout << "\n";
		}
		if (chargevalue.size() > 0) 
		{
			std::cout << "CHARGE VALUE: ";
			int sum = 0;

			for (unsigned int i = 0; i < chargevalue.size(); i++) 
			{
				std::cout << " " << chargevalue[i];

				_stats._chgValue[i] = chargevalue[i];

				sum += chargevalue[i];
			}
			std::cout << "\n";
			if (sum == 0) 
			{
				std::cout << "CONTRADICTING RESULT\n";
				_stats._qCostheta[0] = -2.;
				_stats._qCostheta[1] = -2.;
			}
			else 
			{
				//if ( _stats._MCMass > _massCutparameter) 
				{
					_summary._nAfterKinematicCuts++;
				}

				//qBCostheta implimented
				//_stats._qBCostheta[0] = (_stats._Top1bcharge < 0)? _stats._Top1bcostheta: - _stats._Top1bcostheta;
				//_stats._qBCostheta[0] = (_stats._Top1bcharge > 0)? -_stats._Top1bcostheta:  _stats._Top1bcostheta;

				_stats._qBCostheta[0] = (sum < 0)? _stats._Top1bcostheta: - _stats._Top1bcostheta;
				_stats._qBCostheta[0] = (sum > 0)? -_stats._Top1bcostheta:  _stats._Top1bcostheta;

				_stats._qCostheta[0] = (sum < 0)? _stats._Top1costheta: - _stats._Top1costheta;
				_stats._qCostheta[0] = (sum > 0)? -_stats._Top1costheta:  _stats._Top1costheta;
				_stats._qCostheta1 = (sum < 0)? _stats._Top1costheta: - _stats._Top1costheta;
				_stats._qCostheta1 = (sum > 0)? -_stats._Top1costheta:  _stats._Top1costheta;
			}
		}
		// Lepton only
		//_stats._gammaT = e/m;
		//if (_stats._methodUsed < 1 && samecharge > 0) 
		//{
		//_stats._methodSameCharge = 1;
		//}
		//_stats._methodUsed = 0;

	}
	void TTbarAnalysis::AnalyseTTbarHadronic( LCEvent * evt ,
			std::string _colName ,
			std::string _MCColName ,
			std::string _JetsColName ,
			std::string _JetsRelColName ,
			std::string _MCVtxColName ,
			std::string _colRelName
			)
	{
		try
		{
			std::cout << "***************Analysis*" <<_summary._nEvt++<<"*****************\n";
			LCCollection * jetcol = evt->getCollection(_JetsColName);
			LCCollection * jetrelcol = evt->getCollection(_JetsRelColName);
			LCCollection * mccol = evt->getCollection(_MCColName);
			LCCollection * mcvtxcol = evt->getCollection(_MCVtxColName);
			QQbarMCOperator opera(mccol);
			VertexChargeOperator vtxOperator(evt->getCollection(_colName),evt->getCollection(_colRelName));

			vector < MCParticle * > mctops = AnalyseGenerator(opera);
			vector< RecoJet * > * jets = QQbarTools::getJets(jetcol, jetrelcol);
			vector< RecoJet * > * wjets = new vector< RecoJet * >();
			vector< RecoJet * > * bjets = QQbarTools::getBTagJets(jets, wjets);

			if ( bjets->at(0)->GetBTag() < _highBTagCutparameter ||  bjets->at(1)->GetBTag() < _lowBTagCutparameter) 
			{
				return;	
			}
			_summary._nAfterBtagCuts++;
			
			// compare Gen and Reco top, b, w info
			vector< EVENT::MCParticle * > mcbquarks = opera.GetBquarkPair();
			vector< EVENT::MCParticle * > mcws = opera.GetWPair();


			// Reco w and top
			//vector< TopQuark * > * wbosons = formW(bjets,wjets);
			vector< TopQuark * > * wbosons = formW(wjets);
			std::cout << "running " << wbosons->size() << std::endl;
			vector< TopQuark * > * tops    = composeTops(bjets,wbosons);

			TopQuark * top1 = tops->at(0);
			TopQuark * top2 = tops->at(1);

			// Compares MC top angle with reconstructed b and W directions
			Match(mctops, mcbquarks, mcws, top1);


			ComputeTopParameters( top1, top2 );
			ComputeChargeTVCM( top1, top2, vtxOperator );

			float momentum[3];
			for (unsigned int i = 0; i < 3; i++) 
			{
				momentum[i] = top1->getMomentum()[i]+top2->GetB()->getMomentum()[i];
			}

			_stats._hadMass = std::sqrt(pow(top1->getEnergy()+top2->GetB()->getEnergy(),2) - momentum[0]* momentum[0]-momentum[1]*momentum[1]-momentum[2]*momentum[2]);

			DecideOnAsymmetry(top1, top2, 1);


			// jet info
			_stats._cosbjets = std::cos( MathOperator::getAngle(bjets->at(0)->getMomentum(), bjets->at(1)->getMomentum() ));

			for (unsigned int i = 0; i < bjets->size(); i++) 
			{
				ReconstructedParticle * bjet = bjets->at(i)->GetRawRecoJet();

				_stats._jet_E[i] = bjets->at(i)->getEnergy();
				_stats._jet_px[i]= bjets->at(i)->getMomentum()[0];
				_stats._jet_py[i]= bjets->at(i)->getMomentum()[1];
				_stats._jet_pz[i]= bjets->at(i)->getMomentum()[2];
				_stats._jet_M[i] = bjets->at(i)->getMass();
			}

			_hTree->Fill();
			ClearVariables();
		}
		catch(DataNotAvailableException &e)
		{
			std::cout << e.what() <<"\n";
		}
	}

	vector< TopQuark * > * TTbarAnalysis::composeTops(vector< RecoJet * > * bjets, vector< TopQuark * > * wjets)
	{
		vector< TopQuark * > * result = new vector< TopQuark * > ();
			std::cout << "running2" << std::endl;
		TopQuark * candidateb0w0 = new TopQuark(bjets->at(0), wjets->at(0));
		TopQuark * candidateb1w1 = new TopQuark(bjets->at(1), wjets->at(1));
			std::cout << "running3" << std::endl;
		float chi00 = getChi2(candidateb0w0);
		float chi11 = getChi2(candidateb1w1);
		std::cout << "Chi2: " << chi00 << " " << chi11 << "\n";
		//vs
		TopQuark * candidateb0w1 = new TopQuark(bjets->at(0), wjets->at(1));
		TopQuark * candidateb1w0 = new TopQuark(bjets->at(1), wjets->at(0));
		float chi01 = getChi2(candidateb0w1);
		float chi10 = getChi2(candidateb1w0);
		if (chi00 + chi11 < chi01 + chi10) 
		{
			result->push_back(candidateb0w0);
			result->push_back(candidateb1w1);
			_stats._Top1mass = candidateb0w0->getMass();
			_stats._Top2mass = candidateb1w1->getMass();
		}
		else 
		{
			result->push_back(candidateb0w1);
			result->push_back(candidateb1w0);
			_stats._Top1mass = candidateb0w1->getMass();
			_stats._Top2mass = candidateb1w0->getMass();
		}
		std::cout << "Chi2: " << chi01 << " " << chi10 << "\n";
		return result;

	}

	RecoJet * TTbarAnalysis::formQQ(RecoJet * qjet1, RecoJet * qjet2)
	{
		std::cout << "test" << std::endl;
	}

	vector< TopQuark * > * TTbarAnalysis::formW(vector< RecoJet * > * wjets)
	{
		vector< TopQuark * > * result = new vector< TopQuark * >();


		if( wjets->size() < 4 ){
			return result;
		}else{

			float chi2vec[3];
			
			TopQuark * candidatew0w1 = new TopQuark(wjets->at(0), wjets->at(1));
			TopQuark * candidatew2w3 = new TopQuark(wjets->at(2), wjets->at(3));

			float chi0123 = getChi2W(candidatew0w1, candidatew2w3);
			chi2vec[0] = chi0123;

			TopQuark * candidatew0w2 = new TopQuark(wjets->at(0), wjets->at(2));
			TopQuark * candidatew1w3 = new TopQuark(wjets->at(1), wjets->at(3));

			float chi0213 = getChi2W(candidatew0w2, candidatew1w3);
			chi2vec[1] = chi0213;

			TopQuark * candidatew0w3 = new TopQuark(wjets->at(0), wjets->at(3));
			TopQuark * candidatew1w2 = new TopQuark(wjets->at(1), wjets->at(2));

			float chi0312 = getChi2W(candidatew0w3, candidatew1w2);
			chi2vec[2] = chi0312;

			float minchi2 = 10000;
			int minIndex = -1;
			for(int i=0; i < 3; i++){
				if(chi2vec[i] < minchi2){
					minchi2 = chi2vec[i];
					minIndex = i;
				}
			}

			switch(minIndex) {
				case 0 :
					result->push_back(candidatew0w1);
					result->push_back(candidatew2w3);
					break;
				case 1 :
					result->push_back(candidatew0w2);
					result->push_back(candidatew1w3);
					break;
				case 2 :
					result->push_back(candidatew0w3);
					result->push_back(candidatew1w2);
					break;
			}

			std::cout << "minIndex = " << minIndex << std::endl;

			return result;
		}

	}

	vector< TopQuark * > * TTbarAnalysis::formW(vector< RecoJet * > * bjets,vector< RecoJet * > * wjets)

	{
		vector< TopQuark * > * result = new vector< TopQuark * > ();
		TopQuark * candidateb0w0 = new TopQuark(bjets->at(0), wjets->at(0));
		TopQuark * candidateb1w1 = new TopQuark(bjets->at(1), wjets->at(1));
		float chi00 = getChi2(candidateb0w0);
		float chi11 = getChi2(candidateb1w1);
		std::cout << "Chi2: " << chi00 << " " << chi11 << "\n";
		//vs
		TopQuark * candidateb0w1 = new TopQuark(bjets->at(0), wjets->at(1));
		TopQuark * candidateb1w0 = new TopQuark(bjets->at(1), wjets->at(0));
		float chi01 = getChi2(candidateb0w1);
		float chi10 = getChi2(candidateb1w0);
		if (chi00 + chi11 < chi01 + chi10) 
		{
			result->push_back(candidateb0w0);
			result->push_back(candidateb1w1);
			_stats._Top1mass = candidateb0w0->getMass();
			_stats._Top2mass = candidateb1w1->getMass();
		}
		else 
		{
			result->push_back(candidateb0w1);
			result->push_back(candidateb1w0);
			_stats._Top1mass = candidateb0w1->getMass();
			_stats._Top2mass = candidateb1w0->getMass();
		}
		std::cout << "Chi2: " << chi01 << " " << chi10 << "\n";
		return result;


	}

	float TTbarAnalysis::getChi2(TopQuark * candidate , std::vector<float> & eachchi2 )
	{
		float pT = MathOperator::getModule(candidate->getMomentum());
		float mT = candidate->getMass();
		float ET = candidate->getEnergy();
		float pB = MathOperator::getModule(candidate->GetB()->getMomentum());
		float beta = pT / ET;
		float gamma =1.0 / std::sqrt( 1.0 - beta * beta);
		float cosbT = std::cos( MathOperator::getAngle(candidate->getMomentum(), candidate->GetB()->getMomentum()) );
		float bpstar = gamma * pB * ( 1.0 - beta * cosbT);
		float cosbW = std::cos( MathOperator::getAngle(candidate->GetB()->getMomentum(), candidate->GetW()->getMomentum()) );
		float chiTopMass = std::pow(mT - _TopMassparameter, 2) / std::pow( _TopMassSigmaparameter, 2) ;
		float chiTopE = std::pow(ET - _EBeamparameter , 2) / std::pow( _EBeamSigmaparameter, 2); 
		float chiPbstar = std::pow( bpstar - _PStarparameter, 2) / std::pow( _PStarSigmaparameter, 2);
		float chiGammaT = std::pow( gamma - _GammaTparameter, 2) / std::pow( _GammaTSigmaparameter, 2); 
		float chiCosWb = std::pow( cosbW - _CosbWparameter, 2) / std::pow( _CosbWSigmaparameter, 2);

		//float chi2 = chiTopMass + chiTopE + chiPbstar; // + chiCosWb + chiGammaT ;
		float chi2 = chiTopMass + chiTopE + chiPbstar + chiCosWb + chiGammaT ;

		_stats._Top1pstarb = bpstar;
		//float chi2 = std::pow( mT - _stats._TopMassparameter, 2) / std::pow( _stats._TopMassSigmaparameter, 2) + 
		//	     std::pow(ET - _EBeamparameter , 2) / std::pow( _EBeamSigmaparameter, 2) +
		//	     std::pow( bpstar - _PStarparameter, 2) / std::pow( _PStarSigmaparameter, 2) +
		//	     std::pow( gamma - _GammaTparameter, 2) / std::pow( _GammaTSigmaparameter, 2) +
		//	     std::pow( cosbW - _CosbWparameter, 2) / std::pow( _CosbWSigmaparameter, 2);
		//std::cout << " chi2: " << chi2
		//          << " chiTopMass: " << chiTopMass
		//          << " chiTopE: " << chiTopE
		//          << " chiPbstar: " << chiPbstar << std::endl;
		eachchi2.clear() ;
		eachchi2.push_back(chiTopMass) ;
		eachchi2.push_back(chiTopE) ;
		eachchi2.push_back(chiPbstar) ;
		eachchi2.push_back(chiGammaT) ;
		eachchi2.push_back(chiCosWb) ;
		return chi2;
	}

	float TTbarAnalysis::getChi2(TopQuark * candidate )
	{
		float pT = MathOperator::getModule(candidate->getMomentum());
		float mT = candidate->getMass();
		float ET = candidate->getEnergy();
		float pB = MathOperator::getModule(candidate->GetB()->getMomentum());
		float beta = pT / ET;
		float gamma =1.0 / std::sqrt( 1.0 - beta * beta);
		float cosbT = std::cos( MathOperator::getAngle(candidate->getMomentum(), candidate->GetB()->getMomentum()) );
		float bpstar = gamma * pB * ( 1.0 - beta * cosbT);
		float cosbW = std::cos( MathOperator::getAngle(candidate->GetB()->getMomentum(), candidate->GetW()->getMomentum()) );
		_stats._Top1pstarb = bpstar;

		_stats._chiTopMass = std::pow(mT - _TopMassparameter, 2) / std::pow( _TopMassSigmaparameter, 2) ;
		_stats._chiTopE = std::pow(ET - _EBeamparameter , 2) / std::pow( _EBeamSigmaparameter, 2); 
		_stats._chiPbstar = std::pow( bpstar - _PStarparameter, 2) / std::pow( _PStarSigmaparameter, 2);
		_stats._chiGammaT = std::pow( gamma - _GammaTparameter, 2) / std::pow( _GammaTSigmaparameter, 2); 
		_stats._chiCosWb = std::pow( cosbW - _CosbWparameter, 2) / std::pow( _CosbWSigmaparameter, 2);
		float chi2 = _stats._chiTopMass + _stats._chiTopE + _stats._chiPbstar  + _stats._chiCosWb + _stats._chiGammaT;
		//float chi2 = std::pow( mT - _stats._TopMassparameter, 2) / std::pow( _stats._TopMassSigmaparameter, 2) + 
		//	     std::pow(ET - _EBeamparameter , 2) / std::pow( _EBeamSigmaparameter, 2) +
		//	     std::pow( bpstar - _PStarparameter, 2) / std::pow( _PStarSigmaparameter, 2) +
		//	     std::pow( gamma - _GammaTparameter, 2) / std::pow( _GammaTSigmaparameter, 2) +
		//	     std::pow( cosbW - _CosbWparameter, 2) / std::pow( _CosbWSigmaparameter, 2);
		std::cout << " chi2: " << chi2
			<< " bpstar: " << bpstar
			<< " cosw: " << cosbW 
			<< "\n";
		return chi2;
	}

	float TTbarAnalysis::getChi2W( RecoJet * candidate1, RecoJet * candidate2 )
	{
		float mW1 = candidate1->getMass();
		float mW2 = candidate2->getMass();

		_stats._chiWMass1 = std::pow(mW1 - _WMassparameter, 2) / std::pow( _WMassSigmaparameter, 2);
		_stats._chiWMass2 = std::pow(mW2 - _WMassparameter, 2) / std::pow( _WMassSigmaparameter, 2);

		float chi2 = _stats._chiWMass1 + _stats._chiWMass2;

		return chi2;
	}

	void TTbarAnalysis::__ComputeChargeCheat(TopQuark * top1, TopQuark * top2)
	{
		//_Top1bcharge = (top1->GetB()->__GetMCCharge() > 0.0)? -1:1;
		if (top1->GetB()->__GetMCCharge() > 0.0) 
		{
			_stats._Top1bcharge = -1.0;
		}
		if (top1->GetB()->__GetMCCharge() < 0.0) 
		{
			_stats._Top1bcharge = 1.0;
		}
		//_Top1bcharge = top1->GetHadronCharge();
		//_Top2bcharge = top2->GetHadronCharge();

		_stats._Top1bmomentum = top1->GetHadronMomentum();
		//_stats._Top1bmomentum = MathOperator::getModule(top1->GetB()->getMomentum());

		vector<float> direction = MathOperator::getDirection(top1->getMomentum());
		_stats._Top1costheta =  std::cos( MathOperator::getAngles(direction)[1] );
		_stats._Top1bntracks = top1->GetNumberOfVertexParticles();
		int Top1Genbntracks = top1->GetB()->__GetMCNtracks();
		_stats._Top1btag = top1->GetBTag();
		std::cout << "Top charge: " << _stats._Top1bcharge
			<< " top pB: " << _stats._Top1bmomentum
			<< " top bntracks: " << _stats._Top1bntracks
			<< " top Gen bntracks: " << Top1Genbntracks 
			<< " top btag: " << _stats._Top1btag
			<< " top costheta: " << _stats._Top1costheta
			<< "\n";
		//Top Leptonic
		_stats._Top2bcharge = top2->__GetMCCharge();

		_stats._Top2bmomentum = top2->GetHadronMomentum();
		//_stats._Top2bmomentum = MathOperator::getModule(top2->GetB()->getMomentum());

		vector<float> direction2 = MathOperator::getDirection(top2->getMomentum());
		_stats._Top2costheta =  std::cos( MathOperator::getAngles(direction2)[1] );
		_stats._Top2bntracks = top2->GetNumberOfVertexParticles();
		int Top2Genbntracks = top2->GetB()->__GetMCNtracks();
		_stats._Top2btag = top2->GetBTag();
		std::cout << "Top charge: " << _stats._Top2bcharge
			<< " top pB: " << _stats._Top2bmomentum
			<< " top bntracks: " << _stats._Top2bntracks
			<< " top Gen bntracks: " << Top2Genbntracks 
			<< " top btag: " << _stats._Top2btag
			<< " top costheta: " << _stats._Top2costheta
			<< "\n";
		/*if (Top1Genbntracks == _stats._Top1bntracks && abs( _stats._Top1bcharge) > 0) 
			{
			_stats._qCostheta[0] = (_stats._Top1bcharge < 0)? _stats._Top1costheta : -_stats._Top1costheta;
			}
			if (Top2Genbntracks == _stats._Top2bntracks  && abs( _stats._Top2bcharge) > 0) 
			{
			_stats._qCostheta[0] = (_stats._Top2bcharge > 0)? _stats._Top1costheta : -_stats._Top1costheta;
			}*/
		_stats._qCostheta[0] = _stats._Top1costheta * _stats._Top1bcharge;

	}

	void TTbarAnalysis::BHadronHandler(QQbarMCOperator & Bopera)
	{
		std::vector< EVENT::MCParticle * > mcB0						= Bopera.GetPairParticles(511);
		std::vector< EVENT::MCParticle * > mcBplus				= Bopera.GetPairParticles(521);
		std::vector< EVENT::MCParticle * > mcB0s 					= Bopera.GetPairParticles(531);
		std::vector< EVENT::MCParticle * > mcB0c 					= Bopera.GetPairParticles(541);
		std::vector< EVENT::MCParticle * > mcBLambda0b 		= Bopera.GetPairParticles(5122);
		std::vector< EVENT::MCParticle * > mcBXiminusb 		= Bopera.GetPairParticles(5132);
		std::vector< EVENT::MCParticle * > mcBXi0b 				= Bopera.GetPairParticles(5232);
		std::vector< EVENT::MCParticle * > mcBOmegaminusb = Bopera.GetPairParticles(5332);

		int nHadrons = 0;

		if(mcB0.size()) 					getBHadrons(mcB0); nHadrons += mcB0.size();
		if(mcBplus.size()) 				getBHadrons(mcBplus); nHadrons += mcBplus.size();
		if(mcB0s.size()) 					getBHadrons(mcB0s); nHadrons += mcB0s.size();
		if(mcB0c.size()) 					getBHadrons(mcB0c); nHadrons += mcB0c.size();
		if(mcBLambda0b.size()) 		getBHadrons(mcBLambda0b); nHadrons += mcBLambda0b.size();
		if(mcBXiminusb.size()) 		getBHadrons(mcBXiminusb); nHadrons += mcBXiminusb.size();
		if(mcBXi0b.size()) 				getBHadrons(mcBXi0b); nHadrons += mcBXi0b.size();
		if(mcBOmegaminusb.size()) getBHadrons(mcBOmegaminusb); nHadrons += mcBOmegaminusb.size();

		std::cout << "nHadrons = " << nHadrons << std::endl;

	}

	void TTbarAnalysis::Match(vector< MCParticle * > & mctops,vector< MCParticle * > &  mcbs, vector< MCParticle * > & mcws, TopQuark * topHadronic,  TopQuark * top2)
	{
		_stats._Top1truthAngle = 4.0;
		float charge = 0.0;
		float minwangle = 4.0;
		float minbangle = 4.0;
		MCParticle * whad = NULL;
		MCParticle * bhad = NULL;
		for (unsigned int i = 0; i < mcbs.size(); i++) 
		{
			float angleB =  MathOperator::getAngle(mcbs[i]->getMomentum(), topHadronic->GetB()->getMomentum());
			float angleW =  MathOperator::getAngle(mcws[i]->getMomentum(), topHadronic->GetW()->getMomentum());
			std::cout << "\tB angle: " << angleB << "\n";
			std::cout << "\tW angle: " << angleW << "\n";
			_stats._angleB = angleB;
			_stats._angleW = angleW;

			if (angleW < minwangle) 
			{
				whad = mcws[i];
				minwangle = angleW;
			}
			if (angleB < minbangle) 
			{
				bhad = mcbs[i];
				minbangle = angleB;
			}
		}
		std::cout << "Min w angle: " << minwangle << " min b angle: "  << minbangle << "\n";
		MCParticle * tophad = NULL;
		for (unsigned int i = 0; i < mctops.size(); i++) 
		{
			MCParticle * mctop = mctops[i];
			float angle =  MathOperator::getAngle(mctop->getMomentum(), topHadronic->getMomentum());
			if (angle < _stats._Top1truthAngle) 
			{
				_stats._Top1truthAngle = angle;
				charge = mctop->getCharge();
				topHadronic->__SetMCCharge(charge);
				tophad = mctop;
			}
		}
		if (whad && bhad) 
		{
			std::cout << "MC charge: " << whad->getCharge() + bhad->getCharge() << "\n";
			std::cout << "W charge: " << whad->getCharge() <<  " w had: " << whad->getGeneratorStatus() << "\n";
			_stats._MCBWcorrect = (std::abs(whad->getCharge() + bhad->getCharge()) < 1 );
		}
		else 
		{
			_stats._MCBWcorrect = -1;
		}
		std::cout << "Truth Angle: " << _stats._Top1truthAngle << " charge: " << charge << "\n";
		if (top2) 
		{
			top2->__SetMCCharge(-charge);
		}
	}

	void TTbarAnalysis::MatchB(vector<RecoJet*> * bjets, vector< MCParticle * > & mcbs, LCCollection * mcvtxcol)
	{
		float charge = 0.0;
		float angle = 4.0;
		int bgenntracks = 0;
		int bbargenntracks = 0;
		_stats._MCBOscillation = 0;
		_stats._MCBBarOscillation = 0;
		if (mcvtxcol && mcvtxcol->getNumberOfElements() > 0) 
		{
			for (int i = 0; i < mcvtxcol->getNumberOfElements(); i++) 
			{
				Vertex * vertex = dynamic_cast< Vertex * >(mcvtxcol->getElementAt(i));
				if (vertex->getParameters()[1] > 0) 
				{
					bgenntracks += vertex->getAssociatedParticle()->getParticles().size();
				}
				if (vertex->getParameters()[1] < 0) 
				{
					bbargenntracks += vertex->getAssociatedParticle()->getParticles().size();
				}
			}
			_stats._MCBBarOscillation = mcvtxcol->getParameters().getIntVal("BBarOscillation");
			_stats._MCBOscillation = mcvtxcol->getParameters().getIntVal("BOscillation");
		}
		for (unsigned int i = 0; i < mcbs.size(); i++) 
		{
			MCParticle * mcb = mcbs[i];
			float angleCurrent =  MathOperator::getAngle(mcb->getMomentum(), bjets->at(0)->getMomentum());
			if (angleCurrent < angle) 
			{ 
				angle = angleCurrent;
				charge = mcb->getCharge();
				bjets->at(0)->__SetMCCharge(charge);
			}
		}
		std::cout << "Truth Angle: " << angle << " charge: " << charge << "\n";
		_stats._B1truthAngle = angle;
		bjets->at(1)->__SetMCCharge(-charge);
		//*/
		/*float angle00 = MathOperator::getAngle(mcbs[0]->getMomentum(), bjets->at(0)->getMomentum());
			float angle11 = MathOperator::getAngle(mcbs[1]->getMomentum(), bjets->at(1)->getMomentum());
		//float energy0 = mcbs[0]->getEnergy() - bjets->at(0)->getEnergy() + mcbs[1]->getEnergy() -  bjets->at(1)->getEnergy();
		float angle01 = MathOperator::getAngle(mcbs[0]->getMomentum(), bjets->at(1)->getMomentum());
		float angle10 = MathOperator::getAngle(mcbs[1]->getMomentum(), bjets->at(0)->getMomentum());
		//float energy1 = mcbs[1]->getEnergy() - bjets->at(0)->getEnergy() + mcbs[0]->getEnergy() -  bjets->at(1)->getEnergy();
		std::cout << "Angle btw quarks: " << _stats._bbbarAngle << " a1+a2: " << angle00+angle11 << " b1+b2: " << angle01+angle10 <<"\n"; 
		if (angle00 + angle11 < angle01 + angle10) 
		{
		bjets->at(0)->__SetMCCharge(mcbs[0]->getCharge());
		bjets->at(1)->__SetMCCharge(mcbs[1]->getCharge());
		_stats._B1truthAngle = angle00 + angle11;
		}
		else 
		{
		_stats._B1truthAngle = angle01 + angle10;
		bjets->at(1)->__SetMCCharge(mcbs[0]->getCharge());
		bjets->at(0)->__SetMCCharge(mcbs[1]->getCharge());

		}*/
		if ( bjets->at(0)->__GetMCCharge() < 0) 
		{
			bjets->at(0)->__SetMCNtracks(bgenntracks);
			bjets->at(0)->__SetMCOscillation(_stats._MCBOscillation);
			bjets->at(1)->__SetMCNtracks(bbargenntracks);
			bjets->at(1)->__SetMCOscillation(_stats._MCBBarOscillation);
		}
		else 
		{
			bjets->at(0)->__SetMCNtracks(bbargenntracks);
			bjets->at(0)->__SetMCOscillation(_stats._MCBBarOscillation);
			bjets->at(1)->__SetMCNtracks(bgenntracks);
			bjets->at(1)->__SetMCOscillation(_stats._MCBOscillation);
		}
	}
	void TTbarAnalysis::MatchB(std::vector< EVENT::MCParticle * > & mcbs, TopQuark * topHadronic, TopQuark * top2, LCCollection * mcvtxcol)
	{
		float charge = 0.0;
		float angle = 4.0;
		int bgenntracks = 0;
		int bbargenntracks = 0;
		_stats._MCBOscillation = 0;
		_stats._MCBBarOscillation = 0;
		if (mcvtxcol && mcvtxcol->getNumberOfElements() > 0) 
		{
			std::cout << "nElements = " << mcvtxcol->getNumberOfElements() << "\n";
			for (int i = 0; i < mcvtxcol->getNumberOfElements(); i++) 
			{	
				Vertex * vertex = dynamic_cast< Vertex * >(mcvtxcol->getElementAt(i));

				std::cout << "getParameters = " << vertex->getParameters().size() << "\n" ;
				//std::cout << "bgenntracks = " << vertex->getAssociatedParticle()->getParticles().size() << "\n" ;
				if (!vertex->getAssociatedParticle()) {
					std::cout << "i = " << i << std::endl;
					continue;
				}

				if (vertex->getParameters()[1] > 0) 
				{
					bgenntracks += vertex->getAssociatedParticle()->getParticles().size();
				}
				if (vertex->getParameters()[1] < 0) 
				{
					bbargenntracks += vertex->getAssociatedParticle()->getParticles().size();
				}
			}

			_stats._MCBBarOscillation = mcvtxcol->getParameters().getIntVal("BBarOscillation");
			_stats._MCBOscillation = mcvtxcol->getParameters().getIntVal("BOscillation");
		}
		for (unsigned int i = 0; i < mcbs.size(); i++) 
		{
			MCParticle * mcb = mcbs[i];
			float angleCurrent =  MathOperator::getAngle(mcb->getMomentum(), topHadronic->GetB()->getMomentum());
			if (angleCurrent < angle) 
			{ 
				angle = angleCurrent;
				charge = mcb->getCharge();
				topHadronic->GetB()->__SetMCCharge(charge);
			}

		}
		std::cout << "Truth Angle: " << angle << " charge: " << charge << "\n";

		if (top2) 
		{
			if (topHadronic->GetB()->__GetMCCharge() < 0) 
			{
				topHadronic->GetB()->__SetMCNtracks(bgenntracks);
				topHadronic->GetB()->__SetMCOscillation(_stats._MCBOscillation);
				top2->GetB()->__SetMCNtracks(bbargenntracks);
				top2->GetB()->__SetMCOscillation(_stats._MCBBarOscillation);
			}
			else 
			{
				topHadronic->GetB()->__SetMCNtracks(bbargenntracks);
				topHadronic->GetB()->__SetMCOscillation(_stats._MCBBarOscillation);
				top2->GetB()->__SetMCNtracks(bgenntracks);
				top2->GetB()->__SetMCOscillation(_stats._MCBOscillation);
			}
			std::cout << "bgenntracks: " << topHadronic->GetB()->__GetMCNtracks()<< " bbargenntracks: " << top2->GetB()->__GetMCNtracks() << "\n";
			top2->GetB()->__SetMCCharge(-charge);
			if ((-charge) * top2->GetW()->getCharge() < 0) 
			{
				_stats._Top2leptonCorrect = 1;
				std::cout << "Charge correct! \n";
			}
		}
	}

	void TTbarAnalysis::ComputeTopParameters(TopQuark * top1, TopQuark * top2){
		_stats._totalEnergy = top1->getEnergy() + top2->getEnergy();
		_stats._missedEnergy = 2*_EBeamparameter - _stats._totalEnergy;

		_stats._Top1gamma = top1->getEnergy()/top1->getMass();

		_stats._W1mass = top1->GetW()->getMass();
		_stats._W1momentum = MathOperator::getModule(top1->GetW()->getMomentum());
		vector<float> Wdirection1 = MathOperator::getDirection(top1->GetW()->getMomentum());
		_stats._W1costheta = std::cos (MathOperator::getAngles(Wdirection1)[1]);
		_stats._W2mass = top2->GetW()->getMass();
		_stats._W2momentum = MathOperator::getModule(top2->GetW()->getMomentum());
		vector<float> Wdirection2 = MathOperator::getDirection(top2->GetW()->getMomentum());
		_stats._W2costheta = std::cos (MathOperator::getAngles(Wdirection2)[1]);

		_stats._Top1energy = top1->getEnergy();

		_stats._Top1bcharge = top1->GetHadronCharge();
		_stats._Top1bmomentum = top1->GetHadronMomentum();
		_stats._Top1bdistance = top1->GetMinHadronDistance();
		vector<float> direction1 = MathOperator::getDirection(top1->getMomentum());
		_stats._Top1costheta =  std::cos( MathOperator::getAngles(direction1)[1] );
		_stats._Top1bntracks = top1->GetNumberOfVertexParticles();
		_stats._Top1btag = top1->GetBTag();
		vector<float> bdirection1 = MathOperator::getDirection(top1->GetB()->getMomentum());
		_stats._Top1bcostheta = std::cos( MathOperator::getAngles(bdirection1)[1] );
		//_stats._Top1bTVCM = top1->GetResultTVCM();
		_stats._Top1cosWb = std::cos( MathOperator::getAngle(top1->GetB()->getMomentum(), top1->GetW()->getMomentum()) );
		//_stats._Top1Kaon = (top1->GetComputedCharge().ByTVCM )? 1:0;
		//std::cout << "Top charge: " << _stats._Top1bcharge
		//          << " top pB: " << _stats._Top1bmomentum
		//          << " top W: " <<  MathOperator::getModule(top1->GetW()->getMomentum())
		//          << " top bntracks: " << _stats._Top1bntracks
		//          << " top btag: " << _stats._Top1btag
		//          << " top bcostheta: " << _stats._Top1bcostheta << std::endl;
		
		
		_stats._Top2bcharge = top2->GetHadronCharge();
		_stats._Top2bmomentum = top2->GetHadronMomentum();
		_stats._Top2bdistance = top2->GetMinHadronDistance();
		vector<float> direction2 = MathOperator::getDirection(top2->getMomentum());
		_stats._Top2costheta =  std::cos( MathOperator::getAngles(direction2)[1] );
		_stats._Top2bntracks = top2->GetNumberOfVertexParticles();
		_stats._Top2btag = top2->GetBTag();
		vector<float> bdirection2 = MathOperator::getDirection(top2->GetB()->getMomentum());
		_stats._Top2bcostheta = std::cos( MathOperator::getAngles(bdirection2)[1] );
		//_stats._Top2bTVCM = top2->GetResultTVCM();
		_stats._Top1cosWb = std::cos( MathOperator::getAngle(top2->GetB()->getMomentum(), top2->GetW()->getMomentum()) );
		//_stats._Top2Kaon = (top2->GetComputedCharge().ByTVCM )? 1:0;
		
		if ( abs( _stats._Top1bcharge) > 0 && _stats._Top1bntracks > 0 )
		{
			_stats._Top1Vtx = 1;
			JetCharge & topCharge = top1->GetComputedCharge();
			topCharge.ByTrackCount = new int(top1->GetHadronCharge());
		}
		if ( abs( _stats._Top2bcharge) > 0 && _stats._Top2bntracks > 0 ) 
		{
			_stats._Top2Vtx = 1;
			JetCharge & topCharge = top2->GetComputedCharge();
			topCharge.ByTrackCount = new int(top2->GetHadronCharge());
		}

		if ( _stats._Top2bcharge != 0 ||  _stats._Top1bcharge != 0) 
		{
			_summary._nChargedB++;
		}

		vector<float> eachchi2;
		_stats._chiHad1 = getChi2(top1, eachchi2);
		_stats._chiTopMass1 = eachchi2[0] ;
		_stats._chiTopE1 = eachchi2[1] ;
		_stats._chiPbstar1 = eachchi2[2] ;
		_stats._chiCosWb1 = eachchi2[3] ;
		_stats._chiGammaT1 = eachchi2[4] ;
		std::cout << "chiHad1:" << _stats._chiHad1 << " chiTopMass1:" << _stats._chiTopMass1 << " chiTopE1:" << _stats._chiTopE1 << " chiPbstar1:" << _stats._chiPbstar1 << std::endl;
		_stats._chiHad2 = getChi2(top2, eachchi2);
		_stats._chiTopMass2 = eachchi2[0] ;
		_stats._chiTopE2 = eachchi2[1] ;
		_stats._chiPbstar2 = eachchi2[2] ;
		_stats._chiCosWb2 = eachchi2[3] ;
		_stats._chiGammaT2 = eachchi2[4] ;
		std::cout << "chiHad2:" << _stats._chiHad2 << " chiTopMass2:" << _stats._chiTopMass2 << " chiTopE2:" << _stats._chiTopE2 << " chiPbstar2:" << _stats._chiPbstar2 << std::endl;
		std::cout << "_qMCBcostheta = " << _stats._qMCBcostheta[0] << std::endl;
	}

	void TTbarAnalysis::ClearVariables()
	{
		_stats._qMCcostheta[0] = -2;
		_stats._qMCcostheta[1] = -2;
		_stats._MCMass = -1;
		_stats.Clear();
	}

	vector<int>  TTbarAnalysis::getOpposite(int icandidate, int jcandidate)
	{
		vector<int> result;
		int kcandidate = -1;
		int lcandidate = -1;
		for ( int i = 0; i < 4; i++) 
		{
			if (icandidate != i && jcandidate != i && kcandidate < 0) 
			{
				kcandidate = i;
			}
			if (jcandidate != i && icandidate != i &&  lcandidate < 0 && kcandidate != i)
			{
				lcandidate = i;
			}
		}
		result.push_back(kcandidate);
		result.push_back(lcandidate);
		return result;
	}

	void TTbarAnalysis::SingleTopAnalyzer( std::vector< EVENT::MCParticle * > mctops, std::vector< EVENT::MCParticle * > mcbs, std::vector< EVENT::MCParticle * > mcws)
	{
		// get mc partiles
		MCParticle * mctop    = mctops[0];
		MCParticle * mctopbar = mctops[1];

		MCParticle * mcb    = mcbs[0];
		MCParticle * mcbbar = mcbs[1];

		MCParticle * mcWplus  = mcws[0];
		MCParticle * mcWminus = mcws[1];

		// get mc particle momentum
		
		float bWp_momentum = 0;
		float bbarWm_momentum = 0;
		float bWp_energy = 0;
		float bbarWm_energy = 0;
		
		// b/W+ energy / momentum
		bWp_energy = mcb->getEnergy() + mcWplus->getEnergy();
		for (int i = 0; i < 3; i++)
		{
			float p = 0;
			p = mcb->getMomentum()[i] + mcWplus->getMomentum()[i];
			bWp_momentum += p*p;
		}

		// bbar/W- energy / momentum
		bbarWm_energy = mcbbar->getEnergy() + mcWminus->getEnergy();
		for (int i = 0; i < 3; i++)
		{
			float p = 0;
			p = mcbbar->getMomentum()[i] + mcWminus->getMomentum()[i];
			bbarWm_momentum += p*p;
		}

		float bWp_mass = 0;
		float bbarWm_mass = 0;

		float mctop_mass = mctop->getMass();
		float mctopbar_mass = mctopbar->getMass();

		bWp_mass = std::sqrt( bWp_energy*bWp_energy - bWp_momentum );
		bbarWm_mass = std::sqrt( bbarWm_energy*bbarWm_energy - bbarWm_momentum );

		//float dtop_mass = abs( bWp_mass - mctop_mass );
		//float dtopbar_mass = abs( bbarWm_mass - mctopbar_mass);

		float dtop_mass = abs( bWp_mass - _TopMassparameter );
		float dtopbar_mass = abs( bbarWm_mass - _TopMassparameter);

		std::cout << "dtop_mass = " << dtop_mass << std::endl;
		std::cout << "dtopber_mass = " << dtopbar_mass << std::endl;

		if( (dtop_mass > 15) || (dtopbar_mass > 15) ){
			_stats._singletopFlag = 1;
		}else{
			_stats._singletopFlag = 0;
		}

	}

#if 1 // RY Test
	MCParticle* TTbarAnalysis::getBestMCParticleOf(ReconstructedParticle* p, LCRelationNavigator* nav)
	{
		// getting MC information
		int nrel = nav->getRelatedToObjects(p).size();

		double wmax;
		MCParticle *best = 0;
		for (int imc = 0; imc < nrel; imc++ ) {

			MCParticle *mcp = dynamic_cast<MCParticle*>(nav->getRelatedToObjects(p)[imc]);

			double trkw = double((int(nav->getRelatedToWeights(p)[imc])%10000)/1000.);
			double calw = double((int(nav->getRelatedToWeights(p)[imc])/10000)/1000.);

			if (imc==0) {
				if (trkw>calw) wmax = trkw;
				else           wmax = calw;
				best = mcp;
			} else {
				if (trkw > wmax) {
					wmax = trkw;
					best = mcp;
				}
				if (calw > wmax) {
					wmax = calw;
					best = mcp;
				}
			}
		}
		return best;
	}
#endif

	void TTbarAnalysis::End()
	{   
		_hSumTree->Fill();
		_hfile->Write();
		_hfile->Close();
	}


}
