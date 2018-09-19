#include "TTbarAnalysis.hh"

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
    _hGenTree->Branch("MCBcostheta", _stats._qMCBcostheta, "MCBcostheta[2]/F");
    _hGenTree->Branch("MCLeptonPDG", &_stats._MCLeptonPDG, "MCLeptonPDG/I");
    _hTree = new TTree( "Stats", "tree" );

    
    if(type==0) writer.InitializeStatsTree(_hTree, _stats);
    else if(type==1) writer.InitializeStatsHadronicTree(_hTree, _stats);
    
    _massCutparameter=masscut;

    _lowBTagCutparameter = 0.3;
    _highBTagCutparameter = 0.8;
    _WMassparameter = 80.3;
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
	
  vector< MCParticle * > TTbarAnalysis::AnalyseGenerator(QQbarMCOperator & opera)
  {
    std::vector< EVENT::MCParticle * > mctops = opera.GetTopPairParticles(_stats._MCTopBangle, _stats._MCTopcosWb);

    if (mctops.size() < 2) 
      {
	_stats._mctag = 0;
	return mctops;
      }
    _summary._nGenUsed++;
    MCParticle * top = mctops[0];
    MCParticle * topbar = mctops[1];
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
    vector< EVENT::MCParticle * > mcb = opera.GetBquarkPair();
    vector<float> bdirection = MathOperator::getDirection(mcb[0]->getMomentum());
    vector<float> bdirectionbar = MathOperator::getDirection(mcb[1]->getMomentum());
    _stats._qMCBcostheta[0] =  std::cos( MathOperator::getAngles(bdirection)[1] );
    _stats._qMCBcostheta[1] =  std::cos( MathOperator::getAngles(bdirectionbar)[1] );
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
						 std::string _JetsVtxColName ,
						 std::string _IsoLeptonColName,
						 std::string _MCVtxColName ,
						 std::string _colRelName
						 )


  {
    LCCollection * mcvtxcol = NULL;
    try
      {
	//mcvtxcol = evt->getCollection(_MCVtxColName);
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
	for (unsigned int i = 0; i < bjets->size(); i++) 
	  {
	    TopQuark * candidate = new TopQuark(bjets->at(i), wHadronic);
	    float chi2 = getChi2(candidate);
	    if (chi2 < chimin) 
	      {
		topHadronic = candidate;
		chimin = chi2;
		chosen = i;
		_stats._Top1cosWb = std::cos( MathOperator::getAngle(candidate->GetB()->getMomentum(), candidate->GetW()->getMomentum()) );
	      }
	  }
	if (chosen && wLeptonic) 
	  {
	    topLeptonic = new TopQuark(bjets->at(0), wLeptonic);
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
	_stats._W1mass = wHadronic->getMass();
	_stats._W1momentum = MathOperator::getModule(wHadronic->getMomentum());
	_stats._W2momentum = MathOperator::getModule(wLeptonic->getMomentum());
	_stats._Top1mass = topHadronic->getMass();
	_stats._Top1energy = topHadronic->getEnergy();
	//_stats._chiHad = getChi2(topHadronic);
	Match(mctops, topHadronic);
	vector< EVENT::MCParticle * > mcbquarks = opera.GetBquarkPair();
	MatchB(mcbquarks, topHadronic, topLeptonic, mcvtxcol);
	ComputeCharge(topHadronic, topLeptonic);
	ComputeChargeTVCM(topHadronic, topLeptonic, vtxOperator);

	DecideOnAsymmetry(topHadronic, topLeptonic);
	if (_stats._methodUsed && wHadronic->getMass() < 110 && topHadronic->getMass() < 200) 
	  {
	    _summary._nAfterMassCuts++;
	  }
	//test(topHadronic, topLeptonic);
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
    //_stats._qCostheta[0] =  costheta;
    //_stats._Top1bTVCM = top->GetResultTVCM();
    //_stats._Top2bTVCM = top2->GetResultTVCM();
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
    for (unsigned int i = 0; i < kaons1.size(); i++) 
      {
	_stats._Top1KaonCharges[i] = kaons1[i]->getCharge();
	_stats._Top1KaonMomentum[i] = MathOperator::getModule(kaons1[i]->getMomentum());
	//std::cout << "\tq: " <<  kaons1[i]->getCharge() << " p: " << MathOperator::getModule(kaons1[i]->getMomentum()) <<"\n";
      }
    //std::cout << "Kaons 2 :\n";
    for (unsigned int i = 0; i < kaons2.size(); i++) 
      {
	_stats._Top2KaonCharges[i] = kaons2[i]->getCharge();
	_stats._Top2KaonMomentum[i] = MathOperator::getModule(kaons2[i]->getMomentum());
	//std::cout << "\tq: " <<  kaons2[i]->getCharge() << " p: " << MathOperator::getModule(kaons2[i]->getMomentum()) <<"\n";
      }
    /*vector<float> directionTop = MathOperator::getDirection(top->getMomentum());
      _stats._Top1costheta =  std::cos( MathOperator::getAngles(directionTop)[1] );
      _stats._Top1bdistance = top->GetMaxHadronDistance();
      _stats._Top2bdistance = top2->GetMaxHadronDistance();
      _stats._Top1bntracks = top->GetNumberOfVertexParticles();
      _stats._Top2bntracks = top2->GetNumberOfVertexParticles();
    */
    _stats._qCostheta[0] = -2;
    std::cout << "\t Costheta: " << _stats._Top1costheta << "\n";
    if (top->GetComputedCharge().ByTVCM) 
      {
	int top1charge = *(top->GetComputedCharge().ByTVCM );
	_stats._qCostheta[0] = (top1charge < 0)? _stats._Top1costheta : -_stats._Top1costheta;
	_stats._methodUsed = 1;
	_stats._methodCorrect = top->__GetMCCharge() * top1charge < 0;
	_summary._nAfterKinematicCuts++;
      }
    if (top2->GetComputedCharge().ByTVCM) 
      {
	int top2charge = *(top2->GetComputedCharge().ByTVCM );
	_stats._qCostheta[0] = (top2charge < 0)? -_stats._Top1costheta : _stats._Top1costheta;
	_stats._methodUsed = 2;
	_stats._methodCorrect = top2->__GetMCCharge() * top2charge < 0;
	_summary._nAfterKinematicCuts++;
      }
    if (top2->GetComputedCharge().ByTVCM && top->GetComputedCharge().ByTVCM) 
      {
	int top1charge = *(top->GetComputedCharge().ByTVCM );
	int top2charge = *(top2->GetComputedCharge().ByTVCM );
	if (top1charge * top2charge < 0) 
	  {
	    _stats._qCostheta[0] = (top1charge < 0)? _stats._Top1costheta : -_stats._Top1costheta;
	  }
	_stats._methodUsed = 3;
	_stats._methodCorrect = top->__GetMCCharge() * top1charge < 0;
	_summary._nAfterKinematicCuts++;
      }
    std::cout << "\t Costheta final: " << _stats._qCostheta[0]  << "\n";
  }
  /*
  void TTbarAnalysis::test(TopQuark * top, TopQuark * top2)
  {	
    _totalEnergy = top->getEnergy() + top2->getEnergy();
    _missedEnergy = 2*_EBeamparameter - _totalEnergy;
    }*/
  void TTbarAnalysis::ComputeCharge(TopQuark * top1, TopQuark * top2)
  {
    //Top hadronic
    _stats._qCostheta[0] = -2.;
    _stats._Top1bcharge = top1->GetHadronCharge();
    _stats._Top1bmomentum = top1->GetHadronMomentum();
    _stats._Top1bdistance = top1->GetMinHadronDistance();
    vector<float> direction = MathOperator::getDirection(top1->getMomentum());
    _stats._Top1costheta =  std::cos( MathOperator::getAngles(direction)[1] );
    _stats._Top1bntracks = top1->GetNumberOfVertexParticles();
    _stats._Top1btag = top1->GetBTag();
    float Top1nvtx = top1->GetNumberOfVertices();
    vector<float> bdirection = MathOperator::getDirection(top1->GetB()->getMomentum());
    _stats._Top1bcostheta =std::abs( std::cos( MathOperator::getAngles(bdirection)[1] ));
    std::cout << "Top charge: " << _stats._Top1bcharge
	      << " top pB: " << _stats._Top1bmomentum
	      << " top W: " <<  MathOperator::getModule(top1->GetW()->getMomentum())//_stats._Top1bmomentum
	      << " top bntracks: " << _stats._Top1bntracks
	      << " top btag: " << _stats._Top1btag
	      << " top bcostheta: " << _stats._Top1bcostheta
	      << "\n";
    //Top Leptonic
    _stats._Top2bmomentum = top2->GetHadronMomentum();
    _stats._Top2bdistance = top2->GetMinHadronDistance();
    _stats._Top2bcharge = top2->GetHadronCharge();
    vector<float> direction2 = MathOperator::getDirection(top2->getMomentum());
    _stats._Top2costheta =  std::cos( MathOperator::getAngles(direction2)[1] );
    _stats._Top2bntracks = top2->GetNumberOfVertexParticles();
    _stats._Top2leptonCharge = top2->GetW()->getCharge();
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
		
    bool trustTop1 = false;
    bool trustTop2 = false;
    //float pcut = 15.0;
    //float pcut2 = 15.0;
    //float btagcut = 0.8;
    //float btagcut2 = 0.8;
    int nvtxcut = 0;
    int nvtxcut2 = 0;
    if (_stats._Top1bntracks %2 == 1 && _stats._Top1bntracks != 3) 
      {
	nvtxcut = 1;
	//pcut = 20.;
	//btagcut = 0.99;
      }
    if (_stats._Top2bntracks %2 == 1 && _stats._Top2bntracks != 3) 
      {
	nvtxcut2 = 1;
	//pcut2 = 20.;
	//btagcut2 = 0.99;
      }
    if (//_stats._Top1bmomentum > pcut && 
	abs( _stats._Top1bcharge) > 0 && 
	_stats._Top1bntracks > 2 //&& 

	//top1->GetB()->__GetMCNtracks() > 0 &&
	//Top1nvtx > nvtxcut &&
	//_stats._Top1bntracks < 9 &&
	//_stats._Top1bntracks != 7 &&
	///_stats._Top1bcostheta < 0.9 &&
	//_stats._Top1bdistance > 0.5 &&
	//(_stats._Top1bntracks %2 == 0 || _stats._Top1bntracks == 3) && 
	//_stats._Top1btag > btagcut 
	)  //  _stats._Top1bntracks < 7 
      {
	std::cout << "Use top 1!\n";
	trustTop1 = true;
	_stats._Top1Vtx = 1;
	JetCharge & topCharge = top1->GetComputedCharge();
	topCharge.ByTrackCount = new int(top1->GetHadronCharge());
			
      }
    if (//_stats._Top2bmomentum > pcut2 && 
	abs( _stats._Top2bcharge) > 0 && 
	_stats._Top2bntracks > 2 //&& 
	//top2->GetB()->__GetMCNtracks() > 0 &&
	//Top2nvtx > nvtxcut2 &&
	//_stats._Top2bntracks < 9 &&
	//_stats._Top2bntracks != 7 &&
	//_stats._Top2bcostheta < 0.9 &&
	//_stats._Top2bdistance > 0.5 &&
	//(_stats._Top2bntracks %2 == 0 || _stats._Top2bntracks == 3) && 
	//_stats._Top2btag > btagcut2 
	) 
      {
	std::cout << "Use top 2!\n";
	trustTop2 = true;
	_stats._Top2Vtx = 1;
	JetCharge & topCharge = top2->GetComputedCharge();
	topCharge.ByTrackCount = new int(top2->GetHadronCharge());
      }
    std::cout << "\tTop1 weighted charge: " << top1->GetHadronCharge(true) << "\n";
    std::cout << "\tTop2 weighted charge: " << top2->GetHadronCharge(true) << "\n";
    if ( _stats._Top2bcharge != 0 ||  _stats._Top1bcharge != 0) 
      {
	_summary._nChargedB++;
      }
    if (trustTop1 || trustTop2) 
      {
	//_summary._nAfterKinematicCuts++;
      }
    if (top2->GetW()) 
      {
	top2->GetComputedCharge().ByLepton = new int(top2->GetW()->getCharge());
      }
    bool useLepton = (_ePolarization > 0)? false : true; //Lepton by default
    /*if (trustTop2 && _stats._Top2bcharge * top2->GetW()->getCharge() < 0.0) 
      {
      _stats._qCostheta[0] = (_stats._Top2bcharge > 0)? _stats._Top1costheta : -_stats._Top1costheta;
      }
      if (trustTop1 && _stats._Top1bcharge * top2->GetW()->getCharge() > 0.0) 
      {
      _stats._qCostheta[0] = (_stats._Top1bcharge < 0)? _stats._Top1costheta : -_stats._Top1costheta;
      }
		
    //*/
    if (trustTop1 && !trustTop2 && !useLepton) 
      {
	_stats._qCostheta[0] = (_stats._Top1bcharge < 0)? _stats._Top1costheta : -_stats._Top1costheta;
      }
    if (trustTop2 && !trustTop1 && !useLepton) 
      {
	_stats._qCostheta[0] = (_stats._Top2bcharge > 0)? _stats._Top1costheta : -_stats._Top1costheta;
      }
    if (trustTop1 && trustTop2 && !useLepton) 
      {
	if (_stats._Top1bntracks < _stats._Top2bntracks || (_stats._Top1bntracks % 2 == 0 && _stats._Top2bntracks % 2 == 1)) 
	  {
	    _stats._qCostheta[0] = (_stats._Top1bcharge < 0)? _stats._Top1costheta : -_stats._Top1costheta;
	  }
	if (_stats._Top1bntracks > _stats._Top2bntracks || ( _stats._Top1bntracks % 2 == 1 && _stats._Top2bntracks % 2 == 0)) 
	  {
	    _stats._qCostheta[0] = (_stats._Top2bcharge > 0)? _stats._Top1costheta : -_stats._Top1costheta;
	  }
	if (_stats._Top2bntracks == _stats._Top1bntracks) 
	  {
	    if (Top1nvtx == 2 && Top2nvtx == 1) 
	      {
		_stats._qCostheta[0] = (_stats._Top1bcharge < 0)? _stats._Top1costheta : -_stats._Top1costheta;
	      }
	    if (Top2nvtx == 2 && Top1nvtx == 1) 
	      {
		_stats._qCostheta[0] = (_stats._Top2bcharge > 0)? _stats._Top1costheta : -_stats._Top1costheta;
	      }
	    if (_stats._Top1bmomentum > _stats._Top2bmomentum && Top1nvtx == Top2nvtx) 
	      {
		_stats._qCostheta[0] = (_stats._Top1bcharge < 0)? _stats._Top1costheta : -_stats._Top1costheta;
	      }
	    if (_stats._Top2bmomentum > _stats._Top1bmomentum && Top2nvtx == Top1nvtx) 
	      {
		_stats._qCostheta[0] = (_stats._Top2bcharge > 0)? _stats._Top1costheta : -_stats._Top1costheta;
	      }

	  }
      }//*/
    if ((trustTop1 ||  trustTop2) && _stats._qCostheta[0] < -1.0) 
      {
	std::cout << "ERROR!\n";
      }
    if (!trustTop1 && !trustTop2 && !useLepton) 
      {
	if (_stats._Top2bcharge * top2->GetW()->getCharge() < 0.0) 
	  {
	    //_stats._qCostheta[0] = (_stats._Top2bcharge > 0)? _stats._Top1costheta : -_stats._Top1costheta;
	  }
      }
    if (useLepton) // || _stats._chiHad < 20) 
      {
	//_stats._qCostheta[0] = (top2->GetW()->getCharge() > 0)? -_stats._Top1costheta : _stats._Top1costheta;
      }
  }
  void TTbarAnalysis::DecideOnAsymmetry(TopQuark * top1, TopQuark * top2)
  {
    //Print
		
    std::cout << "\t\tTracks\tTVCM\tLepton\n";
    //std::cout << "Top1:\t" << (top1->GetComputedCharge().ByTrackCount)?top1->GetComputedCharge().ByTrackCount:"NAN\t"
    //			<< (top1->GetComputedCharge().ByTVCM)?top1->GetComputedCharge().ByTVCM:"NAN\t"
    //			<< (top1->GetComputedCharge().ByLepton)?top1->GetComputedCharge().ByLepton:"NAN\t"
    std::cout << "Top1:\t" << QQbarTools::intToStr(top1->GetComputedCharge().ByTrackCount)  <<"\t"
	      << QQbarTools::intToStr(top1->GetComputedCharge().ByTVCM) <<"\t"
	      << QQbarTools::intToStr(top1->GetComputedCharge().ByLepton) <<"\n";
    std::cout << "Top2:\t" << QQbarTools::intToStr(top2->GetComputedCharge().ByTrackCount) <<"\t"
	      << QQbarTools::intToStr(top2->GetComputedCharge().ByTVCM) <<"\t"
	      << QQbarTools::intToStr(top2->GetComputedCharge().ByLepton) <<"\n";
    _stats._qCostheta[0] = -2.;

    vector<float> direction = MathOperator::getDirection(top1->getMomentum());
    float costheta =  std::cos( MathOperator::getAngles(direction)[1] );
    //float m = top1->getMass();
    //float e = top1->getEnergy();
    float btagcut = 0.8;
    float pcut = 20.;
    vector<int> samecharge;
    vector<int> goodcharge;
    vector<int> chargevalue;
    //if (e/m > _GammaTparameter -0.1 && top2->GetComputedCharge().ByLepton) 
    //Track charge * Track charge
    if (top2->GetComputedCharge().ByTrackCount && top1->GetComputedCharge().ByTrackCount) 
      {
	int top1charge = *(top1->GetComputedCharge().ByTrackCount );
	int top2charge = *(top2->GetComputedCharge().ByTrackCount );
	if (top1charge * top2charge < 0 && _stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut) 
	  {
	    _stats._qCostheta[0] = (top1charge < 0)? costheta: - costheta;
	    std::cout << "Two vertices are used!\n";
	    _stats._methodUsed = 1;
	    chargevalue.push_back(top1charge);
	    goodcharge.push_back(1);
	    _stats._methodCorrect = top1->__GetMCCharge() * top1charge < 0;
	    if (!_stats._methodCorrect) 
	      {
		std::cout << "Not Correct!\n";
	      }
	    _summary._nAfterKinematicCuts++;
	    return;
	  }
	if (top1charge * top2charge > 0 && _stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut)
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
	    _stats._qCostheta[0] = (top1charge < 0)? costheta: - costheta;
	    std::cout << "Two kaons are used!\n";
	    chargevalue.push_back(top1charge);
	    _stats._methodUsed = 2;
	    goodcharge.push_back(2);
	    _stats._methodCorrect = top1->__GetMCCharge() * top1charge < 0;
	    if (!_stats._methodCorrect) 
	      {
		std::cout << "Not Correct!\n";
	      }
	    _summary._nAfterKinematicCuts++;
	    return;
	  }
	if (top1charge * top2charge > 0)
	  {
	    samecharge.push_back(2);
	  }
      }//*/
    //Track charge + Kaon
    if (top1->GetComputedCharge().ByTrackCount && top1->GetComputedCharge().ByTVCM) 
      {
	int top1charge = *(top1->GetComputedCharge().ByTrackCount );
	int top1kaon = *(top1->GetComputedCharge().ByTVCM );
	if (top1charge * top1kaon > 0 && _stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut) 
	  {
	    _stats._qCostheta[0] = (top1charge < 0)? costheta: -costheta; 
	    std::cout << "Vertex + kaon for top1 is used!\n";
	    _stats._methodUsed = 3;
	    chargevalue.push_back(top1charge);
	    goodcharge.push_back(3);
	    _stats._methodCorrect = top1->__GetMCCharge() * top1charge < 0;
	    if (!_stats._methodCorrect) 
	      {
		std::cout << "Not Correct!\n";
	      }
	    _summary._nAfterKinematicCuts++;
	    return;
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
	    _stats._qCostheta[0] = (top2charge > 0)? costheta: - costheta; 
	    std::cout << "Vertex + kaon for top2 is used!\n";
	    _stats._methodUsed = 4;
	    goodcharge.push_back(4);
	    chargevalue.push_back(-top2charge);
	    _stats._methodCorrect = top1->__GetMCCharge() * top2charge > 0;
	    if (!_stats._methodCorrect) 
	      {
		std::cout << "Not Correct!\n";
	      }
	    _summary._nAfterKinematicCuts++;
	    return;
	  }
	if (top2charge * top2kaon < 0 && _stats._Top2btag > btagcut && _stats._Top2bmomentum > pcut) 
	  {
	    samecharge.push_back(4);
	  }
      }
    if (top1->GetComputedCharge().ByTrackCount && top2->GetComputedCharge().ByTVCM) 
      {
	int top1charge = *(top1->GetComputedCharge().ByTrackCount );
	int top2kaon = *(top2->GetComputedCharge().ByTVCM );
	if (top1charge * top2kaon < 0 &&  _stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut) 
	  {
	    _stats._qCostheta[0] = (top1charge < 0)? costheta: - costheta; 
	    std::cout << "Vertex1 + kaon2 is used!\n";
	    _stats._methodUsed = 5;
	    chargevalue.push_back(top1charge);
	    goodcharge.push_back(5);
	    _stats._methodCorrect = top1->__GetMCCharge() *  top1charge < 0;
	    if (!_stats._methodCorrect) 
	      {
		std::cout << "Not Correct!\n";
	      }
	    _summary._nAfterKinematicCuts++;
	    return;
	  }
	if (top1charge * top2kaon > 0 &&  _stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut)
	  {
	    samecharge.push_back(5);
	  }
      }
    if (top2->GetComputedCharge().ByTrackCount && top1->GetComputedCharge().ByTVCM) 
      {
	int top2charge = *(top2->GetComputedCharge().ByTrackCount );
	int top1kaon = *(top1->GetComputedCharge().ByTVCM );
	if (top2charge * top1kaon < 0 &&  _stats._Top2btag > btagcut && _stats._Top2bmomentum > pcut) 
	  {
	    _stats._qCostheta[0] = (top2charge > 0)? costheta: - costheta; 
	    std::cout << "Vertex2 + kaon1 is used!\n";
	    _stats._methodUsed = 6;
	    goodcharge.push_back(6);
	    chargevalue.push_back(-top2charge);
	    if (!_stats._methodCorrect) 
	      {
		std::cout << "Not Correct!\n";
	      }
	    _stats._methodCorrect = top1->__GetMCCharge() * top1kaon< 0;
	    _summary._nAfterKinematicCuts++;
	    return;
	  }
	if (top2charge * top1kaon > 0 &&  _stats._Top2btag > btagcut && _stats._Top2bmomentum > pcut) 
	  {
	    samecharge.push_back(6);
	  }
      }//*/
    //LEPTON
    /*if (top2->GetComputedCharge().ByLepton && top2->GetComputedCharge().ByTrackCount)
      {
      int top2lepton = *(top2->GetComputedCharge().ByLepton );
      int top2charge = *(top2->GetComputedCharge().ByTrackCount );
      if (top2charge * top2lepton < 0  &&  _stats._Top2btag > btagcut && _stats._Top2bmomentum > pcut)
      {
      std::cout << "Vertex + lepton for top2 is used!\n";
      goodcharge.push_back(7);
      chargevalue.push_back(-top2charge);
      _stats._methodCorrect = top1->__GetMCCharge() * top2charge < 0;
      _summary._nAfterKinematicCuts++;
      }
      }
      if (top2->GetComputedCharge().ByLepton && top1->GetComputedCharge().ByTrackCount)
      {
      int top2lepton = *(top2->GetComputedCharge().ByLepton );
      int top1charge = *(top1->GetComputedCharge().ByTrackCount );
      if (top1charge * top2lepton > 0 &&  _stats._Top1btag > btagcut && _stats._Top1bmomentum > pcut)
      {
      std::cout << "Vertex + lepton for top1 is used!\n";
      goodcharge.push_back(7);
      chargevalue.push_back(top1charge);
      _stats._methodCorrect = top1->__GetMCCharge() * top1charge < 0;
      }
      }//
      if (top2->GetComputedCharge().ByLepton && top1->GetComputedCharge().ByTVCM)
      {
      int top2lepton = *(top2->GetComputedCharge().ByLepton );
      int top1charge = *(top1->GetComputedCharge().ByTVCM );
      if (top1charge * top2lepton > 0)
      {
      std::cout << "Vertex + lepton for top1 is used!\n";
      goodcharge.push_back(8);
      chargevalue.push_back(top1charge);
      _stats._methodCorrect = top1->__GetMCCharge() * top1charge < 0;
      }
      }
      if (top2->GetComputedCharge().ByLepton && top2->GetComputedCharge().ByTrackCount)
      {
      int top2lepton = *(top2->GetComputedCharge().ByLepton );
      int top2charge = *(top1->GetComputedCharge().ByTrackCount );
      if (top2charge * top2lepton < 0)
      {
      std::cout << "Vertex + lepton for top1 is used!\n";
      goodcharge.push_back(8);
      chargevalue.push_back(-top2charge);
      _stats._methodCorrect = top1->__GetMCCharge() * top1charge < 0;
      }
      }
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
      _stats._qCostheta[0] = (sum < 0)? _stats._Top1costheta: - _stats._Top1costheta;
      _stats._qCostheta1 = (sum < 0)? _stats._Top1costheta: - _stats._Top1costheta;
      }
      }
      // Lepton only
      _stats._gammaT = e/m;
      if (top2->GetComputedCharge().ByLepton && _stats._chiHad < 15) 
      {
      int top2lepton = *(top2->GetComputedCharge().ByLepton );
      _stats._qCostheta[0] = (top2lepton < 0)? costheta: - costheta;
      _stats._methodUsed = 8;
      _summary._nAfterKinematicCuts++;
      return;
      }//*/
    //if (_stats._methodUsed < 1 && samecharge > 0) 
    {
      //_stats._methodSameCharge = 1;
    }
    _stats._methodUsed = 0;
		
  }
  void TTbarAnalysis::AnalyseTTbarHadronic( LCEvent * evt ,
						 std::string _colName ,
						 std::string _MCColName ,
						 std::string _JetsColName ,
						 std::string _JetsRelColName ,
						 std::string _JetsVtxColName ,
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
	//LCCollection * mcvtxcol = evt->getCollection(_MCVtxColName);
	QQbarMCOperator opera(mccol);
	VertexChargeOperator vtxOperator(evt->getCollection(_colName),evt->getCollection(_colRelName));
	vector < MCParticle * > mctops = AnalyseGenerator(opera);
	vector< RecoJet * > * jets = QQbarTools::getJets(jetcol, jetrelcol);
	//std::sort(jets->begin(), jets->end(), sortByBtag);
	vector< RecoJet * > * wjets = new vector< RecoJet * >();
	vector< RecoJet * > * bjets = QQbarTools::getBTagJets(jets, wjets);
	//b-tag cut
	//if ( bjets->at(0)->GetBTag() < _highBTagCutparameter ||  bjets->at(1)->GetBTag() < _lowBTagCutparameter) 
	//{
	//	return;	
	//}
	//_summary._nAfterBtagCuts++;
	vector< RecoJet * > * wbosons = formW(wjets);
	vector< TopQuark * > * tops = composeTops(bjets,wbosons);
	//Kinematic cut
	//if ( tops->at(0)->getMass() < 140 || tops->at(0)->getMass() > 210 || tops->at(1)->getMass() < 140 || tops->at(1)->getMass() > 210 ){
	//	return;
	//}
	//if ( wbosons->at(0)->getMass() < 60 || wbosons->at(0)->getMass() > 100 || wbosons->at(1)->getMass() < 60 || wbosons->at(1)->getMass() > 100 ){
	//	return;
	//}
	//_summary._nAfterKinematicCuts++;
	//Chi2 cut
	//if ( std::min(getChi2(tops->at(0)),getChi2(tops->at(1))) > 20 || std::max(getChi2(tops->at(0)),getChi2(tops->at(1))) > 40 ){
	//	return;
	//}
	//_summary._nAfterLeptonCuts++;  //temporary use nAfterLeptonCuts instead of chi2cut
	ComputeTopParameters( tops->at(0), tops->at(1) );
	_hTree->Fill();
	ClearVariables();
      }
    catch(DataNotAvailableException &e)
      {
	std::cout << e.what() <<"\n";
      }
  }
  vector< TopQuark * > * TTbarAnalysis::composeTops(vector< RecoJet * > * bjets, vector< RecoJet * > * wjets)
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
  vector< RecoJet * > * TTbarAnalysis::formW(vector< RecoJet * > * wjets)
  {
    vector< RecoJet * > * result = new vector< RecoJet * > ();
    float bestdifference = 1000.;
    int icandidate = -1;
    int jcandidate = -1;
    int kcandidate = -1;
    int lcandidate = -1;
    for (unsigned int i = 0; i < wjets->size(); i++) 
      {
	for (unsigned int j = 0; j < i; j++) 
	  {
	    TopQuark * candidate1 = new TopQuark(wjets->at(i), wjets->at(j));
	    float mass1 = candidate1->getMass();
	    vector<int> ncandidates = getOpposite(i,j);
	    TopQuark * candidate2 = new TopQuark(wjets->at(ncandidates[0]), wjets->at(ncandidates[1]));
	    float mass2 = candidate2->getMass();
	    std::cout << "W candidate masses: " << mass1 << " " << mass2 << "\n";
	    //float ctag1 = wjets->at(i)->GetCTag();
	    //float ctag2 = wjets->at(j)->GetCTag();
	    //float ctag3 = wjets->at(ncandidates[0])->GetCTag();
	    //float ctag4 = wjets->at(ncandidates[1])->GetCTag();
	    std::cout << "W candidate c-tags: " << wjets->at(i)->GetCTag() << " " << wjets->at(j)->GetCTag() << "\n";
	    if (std::abs(mass1 + mass2 - 2*_WMassparameter) < bestdifference)// && 
	      //(!(ctag1 > _lowBTagCutparameter &&  ctag2 > _lowBTagCutparameter) &&
	      //!(ctag3 > _lowBTagCutparameter && ctag4 > _lowBTagCutparameter) 
	      //|| ctag1+ctag2+ctag3 > 3*_lowBTagCutparameter)) 
	      {
		bestdifference = std::abs(mass1+mass2 - 2*_WMassparameter);
		icandidate = i;
		jcandidate = j;
		kcandidate = ncandidates[0];
		lcandidate = ncandidates[1];
	      }

	  }
      }
    result->push_back(new TopQuark(wjets->at(icandidate), wjets->at(jcandidate)));
    _stats._W1mass = result->at(0)->getMass();
    std::cout << "i: " << icandidate << " j: " << jcandidate  << " k: " << kcandidate  << " l: " << lcandidate <<"\n";
    result->push_back(new TopQuark(wjets->at(kcandidate), wjets->at(lcandidate)));
    _stats._W2mass = result->at(1)->getMass();
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
    float chi2 = chiTopMass + chiTopE + chiPbstar; // + chiCosWb + chiGammaT ;
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
  float TTbarAnalysis::getChi2(TopQuark * canditate )
  {
    vector<float> eachchi2 ;
    return getChi2( canditate, eachchi2 );
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

  void TTbarAnalysis::Match(std::vector< EVENT::MCParticle * > & mctops, TopQuark * topHadronic, TopQuark * top2)
  {
    _stats._Top1truthAngle = 4.0;
    float charge = 0.0;

    for (unsigned int i = 0; i < mctops.size(); i++) 
      {
	MCParticle * mctop = mctops[i];
	float angle =  MathOperator::getAngle(mctop->getMomentum(), topHadronic->getMomentum());
	if (angle < _stats._Top1truthAngle) 
	  {
	    _stats._Top1truthAngle = angle;
	    charge = mctop->getCharge();
	    topHadronic->__SetMCCharge(charge);
	  }
      }
    std::cout << "Truth Angle: " << _stats._Top1truthAngle << " charge: " << charge << "\n";
    if (top2) 
      {
	top2->__SetMCCharge(-charge);
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

  void TTbarAnalysis::ComputeTopParameters(TopQuark * top1, TopQuark * top2){
    _stats._totalEnergy = top1->getEnergy() + top2->getEnergy();
    _stats._missedEnergy = 2*_EBeamparameter - _stats._totalEnergy;
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

  void TTbarAnalysis::End()
  {   
    _hSumTree->Fill();
    _hfile->Write();
    _hfile->Close();
  }


}
