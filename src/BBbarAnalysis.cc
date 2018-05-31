#include "BBbarAnalysis.hh"

using namespace lcio ;
//using namespace marlin ;
using std::vector;
using std::string;
using std::abs;
using EVENT::Track;
using IMPL::ReconstructedParticleImpl;
using EVENT::ParticleID;
using IMPL::ParticleIDImpl;

namespace QQbarProcessor
{
  BBbarAnalysis:: BBbarAnalysis() {}

  void BBbarAnalysis::Init(std::string _hfilename, float masscut) 
  { 

    _lowBTagCutparameter = 0.3;
    _highBTagCutparameter = 0.8;

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

    
    writer.InitializeStatsBBBarTree(_hTree, _stats);

    _massCutparameter=masscut;
    
  }


  vector< MCParticle * > BBbarAnalysis::AnalyseGeneratorBBBar(QQBarMCOperator & opera)
  {
    vector <MCParticle *> genfinalstate;// = opera.GetPairParticles(5);
    for (unsigned int i = 5; i > 0; i--) 
      {
	genfinalstate = opera.GetPairParticles(i);
	if (genfinalstate.size() == 2) 
	  {
	    break;
	  }
      }
    for (unsigned int i = 0; i < genfinalstate.size(); i++) 
      {
	QQbarTools::PrintParticle(genfinalstate[i]);
      }
    if (genfinalstate.size() == 2) 
      {
	MCParticle * Z = opera.CombineParticles(genfinalstate[0],genfinalstate[1]);
	_stats._MCMass = Z->getMass();
	_stats._MCPDG = abs(genfinalstate[0]->getPDG());
	_stats._MCquarkAngle =  MathOperator::getAngleBtw(genfinalstate[0]->getMomentum(), genfinalstate[1]->getMomentum());
	_stats._MCPt = 0.0;
	for (unsigned int i = 0; i < 3; i++) 
	  {
	    _stats._MCPt += std::pow(genfinalstate[0]->getMomentum()[i]+genfinalstate[1]->getMomentum()[i],2);
	  }
	_stats._MCPt = std::sqrt(_stats._MCPt);
	for (unsigned int i = 0; i < genfinalstate.size(); i++) 
	  {
	    vector<float> direction = MathOperator::getDirection(genfinalstate[i]->getMomentum());
	    int charge = genfinalstate[i]->getCharge() / std::abs(genfinalstate[i]->getCharge());
	    _stats._qMCcostheta[i] = - std::cos( MathOperator::getAngles(direction)[1]) * charge;
	  }
	if (Z->getMass() > _massCutparameter && _stats._MCPDG == 5) 
	  {
	    _summary._nAfterGenMassCuts++;
	  }
	std::cout << "Generated mass: " << Z->getMass() << " Sp: " << _stats._MCPt << " angle: " << _stats._MCquarkAngle << "\n";
	if (_stats._MCPDG == 5) 
	  {
	    _summary._nGenUsed++;
	  }
	_hGenTree->Fill();
	delete Z;
      }
 
    return genfinalstate;
		
  }

  void BBbarAnalysis::AnalyseBBBar(LCEvent * evt, 
				    std::string _colName ,
				    std::string _JetsColName ,
				    std::string _JetsRelColName ,
				    std::string _MCColName ,
				    std::string _IsoLeptonColName ,
				    std::string _colRelName  ) 
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
	LCCollection * jetcol = evt->getCollection(_JetsColName);
	LCCollection * jetrelcol = evt->getCollection(_JetsRelColName);
	LCCollection * mccol = evt->getCollection(_MCColName);
	//LCCollection * mcvtxcol = evt->getCollection(_MCVtxColName);
	LCCollection * pfocol = evt->getCollection(_colName);
	QQBarMCOperator opera(mccol);
	vector < MCParticle * > mcbs = AnalyseGeneratorBBBar(opera);
	VertexChargeOperator vtxOperator(evt->getCollection(_colName),evt->getCollection(_colRelName));
	vector< RecoJet * > * jets = QQbarTools::getJets(jetcol, jetrelcol);
	//std::sort(jets->begin(), jets->end(), sortByBtag);

	if (jets->size() != 2 ) return;

	if (jets->size() ==2 && (jets->at(0)->GetBTag() < jets->at(1)->GetBTag()) )
	  std::cout<< "  ALERT, BTAG2>BTAG1  -->  btag1: "<<jets->at(0)->GetBTag()<<" btag2: "<<jets->at(1)->GetBTag()<<"\n";

	double maxbtag= jets->at(0)->GetBTag();
	double minbtag= jets->at(1)->GetBTag();
	if(jets->at(1)->GetBTag()>maxbtag) {
	  maxbtag=jets->at(1)->GetBTag();
	  minbtag=jets->at(0)->GetBTag();
	}

	if (jets->size() < 2  || maxbtag<_highBTagCutparameter || minbtag<_lowBTagCutparameter )
	  {
	    return;
	  }

	std::cout << "MCPDG: " << _stats._MCPDG << "\n";
	if (_stats._MCMass > _massCutparameter && _stats._MCPDG == 5) 
	  {
	    _summary._nAfterBtagCuts++;
	  }
	std::cout << "irles--EVENT ACCEPTED--\n";
	_stats._B1momentum = jets->at(0)->GetHadronMomentum(); //MathOperator::getModule(jets->at(0)->getMomentum());
	_stats._B2momentum = jets->at(1)->GetHadronMomentum();//MathOperator::getModule(jets->at(1)->getMomentum());
	_stats._B1Jetmomentum = MathOperator::getModule(jets->at(0)->getMomentum());
	_stats._B2Jetmomentum = MathOperator::getModule(jets->at(1)->getMomentum());
	_stats._B1btag = jets->at(0)->GetBTag();
	_stats._B2btag = jets->at(1)->GetBTag();
	_stats._B1mass = jets->at(0)->getMass();
	_stats._B2mass = jets->at(1)->getMass();
	_stats._B1charge =  jets->at(0)->GetHadronCharge();
	_stats._B2charge =  jets->at(1)->GetHadronCharge();
	_stats._bbbarAngle = MathOperator::getAngleBtw(jets->at(0)->getMomentum(), jets->at(1)->getMomentum());
	RecoJet * Zboson = new TopQuark(jets->at(0), jets->at(1));
	_stats._InvMass = Zboson->getMass();
	QQbarTools::findPhoton(pfocol);
	if (_stats._InvMass > _massCutparameter-20 && _stats._maxPhotonEnergy < 40 && _stats._MCPDG == 5) //CRUNCH
	  {
	    _summary._nAfterMassCuts++;
	  }
	vector< const double * > momentums;// = {jets->at(0)->getMomentum(), jets->at(1)->getMomentum()};
	momentums.push_back(jets->at(0)->getMomentum());
	momentums.push_back(jets->at(1)->getMomentum());
	vector< ReconstructedParticle * > kaons1 = vtxOperator.GetKaons(jets->at(0));
	if (kaons1.size() > 0) 
	  {
	    _stats._kaonMomentum = MathOperator::getModule(kaons1[0]->getMomentum());
	  }
	_stats._bbbarPt = 0.0;
	_stats._bbbarP = 0.0;
	for (unsigned int i = 0; i < 3; i++) 
	  {
	    _stats._bbbarP += std::pow(jets->at(0)->getMomentum()[i] + jets->at(1)->getMomentum()[i],2);
	    _stats._bbbarPt += (i == 2)? 0.0:std::pow(jets->at(0)->getMomentum()[i] + jets->at(1)->getMomentum()[i],2);
	  }
	_stats._bbbarPt = std::sqrt(_stats._bbbarPt);
	_stats._bbbarP = std::sqrt(_stats._bbbarP);
	std::cout << "Missing pt: " << _stats._bbbarPt << "\n";
	MatchB(jets, mcbs, mcvtxcol);
	ComputeCharge(jets, vtxOperator);
	//	ClusteringOperator cloperator;
	if (jets->at(0)->GetRecoVertices() && jets->at(0)->GetRecoVertices()->size() > 0) 
	  {
	    _stats._B1Y = MathOperator::getAngleBtw(jets->at(0)->getMomentum(), jets->at(0)->GetRecoVertices()->at(0)->getAssociatedParticle()->getMomentum()); //cloperator.ClusterizeJet(jets->at(0));
	  }
	//_stats._B2Y = cloperator.ClusterizeJet(jets->at(1));
	_stats._B1chargeBalance = QQbarTools::getChargeBalance(jets->at(0));
	_stats._B2chargeBalance = QQbarTools::getChargeBalance(jets->at(1));
	_stats._Sphericity = pfocol->getParameters().getFloatVal("sphericity");
	_stats._Thrust = pfocol->getParameters().getFloatVal("majorThrustValue");
	//getZZ(evt->getCollection("FourJets"));
	//_stats._bbbar4JetMass = pfocol->getNumberOfElements();
	vector<float> axis;
	//pfocol->getParameters().getFloatVals("principleThrustAxis", axis);
	pfocol->getParameters().getFloatVals("majorThrustAxis", axis);
	//getThrust(axis, pfocol);
	_hTree->Fill();
	ClearVariables();
	delete Zboson;
	for (unsigned int i = jets->size(); i > -1; i--) 
	  {
	    RecoJet * jet = jets->at(i);
	    jets->pop_back();
	    delete jet;
	  }
	delete jets;
      }
    catch(DataNotAvailableException &e)
      {
	std::cout << e.what() <<"\n";
      }
		
  }
  void BBbarAnalysis::ComputeCharge(std::vector< RecoJet * > *jets, VertexChargeOperator & vtxOperator)
  {
    //std::sort(jets->begin(), jets->end(), sortByCostheta);
    QQbarTools::PrintJets(jets);
    if (jets->at(1)->__GetMCNtracks() != jets->at(1)->GetNumberOfVertexParticles()) 
      {
	//return;	
      }
    /*if (jets->at(0)->GetNumberOfVertexParticles() > 2) 
      {
			
      }
      JetCharge & topCharge = top2->GetComputedCharge();
      topCharge.ByTrackCount = new int(top2->GetHadronCharge());
    */	
    vector<float> bdirection1 = MathOperator::getDirection(jets->at(0)->getMomentum());
    vector<float> bdirection2 = MathOperator::getDirection(jets->at(1)->getMomentum());
    _stats._B1costheta = jets->at(0)->GetCostheta();//( std::cos( MathOperator::getAngles(bdirection1)[1] ));
    _stats._B2costheta = jets->at(1)->GetCostheta();//( std::cos( MathOperator::getAngles(bdirection2)[1] ));
    //_stats._B1costheta = ( std::cos( MathOperator::getAngles(bdirection1)[1] ));
    //_stats._B2costheta = ( std::cos( MathOperator::getAngles(bdirection2)[1] ));
    for (unsigned int i = 0; i < jets->size(); i++) 
      {
	if (jets->at(i)->GetNumberOfVertexParticles() > 2)// && abs(jets->at(i)->GetHadronCharge()) > 0 ) 
	  {
	    JetCharge & bCharge = jets->at(i)->GetComputedCharge();
	    int chargeValue = (jets->at(i)->GetHadronCharge() > -5)? jets->at(i)->GetHadronCharge() : 0;
	    bCharge.ByTrackCount = (chargeValue == 0)? new int(0): new int((float)chargeValue / abs(chargeValue));
				
	  }
	if (jets->at(i)->GetNumberOfVertexParticles() > 0) 
	  {
	    vtxOperator.ComputeCharge(jets->at(i));
	  }
	vector<float> bdirection = MathOperator::getDirection(jets->at(i)->getMomentum());
	float costheta =  std::cos( MathOperator::getAngles(bdirection)[1] );
      }
    float btagcut = .80;
    float pcut = 20.;
    RecoJet * top1 = jets->at(0);
    RecoJet * top2 = jets->at(1);
    std::cout << "Jet \t VTX \t KAON\n";
    std::cout << "B1:\t" << QQbarTools::intToStr(top1->GetComputedCharge().ByTrackCount) <<"\t"
	      << QQbarTools::intToStr(top1->GetComputedCharge().ByTVCM) <<"\n";
    //<< QQbarTools::intToStr(top1->GetComputedCharge().ByLepton) <<"\n";
    std::cout << "B2:\t" << QQbarTools::intToStr(top2->GetComputedCharge().ByTrackCount) <<"\t"
	      << QQbarTools::intToStr(top2->GetComputedCharge().ByTVCM) <<"\n";
    //<< QQbarTools::intToStr(top2->GetComputedCharge().ByLepton) <<"\n";
    if ((top1->GetComputedCharge().ByTVCM || top2->GetComputedCharge().ByTVCM) && _stats._MCMass > _massCutparameter && _stats._MCPDG ==5) 
      {
	_summary._nKaons++;
      }
    if ((top1->GetComputedCharge().ByTrackCount || top2->GetComputedCharge().ByTrackCount) && _stats._MCMass > _massCutparameter && _stats._MCPDG == 5) 
      {
	_summary._nChargedB++;
      }
    _stats._qCostheta[0] = -2.;
    _stats._qCostheta[1] = -2.;
    _stats._B1VtxTag = (top1->GetComputedCharge().ByTrackCount)? *(top1->GetComputedCharge().ByTrackCount) : -5;
    _stats._B2VtxTag = (top2->GetComputedCharge().ByTrackCount)? *(top2->GetComputedCharge().ByTrackCount) : -5;
    _stats._B1KaonTag = (top1->GetComputedCharge().ByTVCM)? *(top1->GetComputedCharge().ByTVCM) : -5;
    _stats._B2KaonTag = (top2->GetComputedCharge().ByTVCM)? *(top2->GetComputedCharge().ByTVCM) : -5;
    vector<int> samecharge;
    vector<int> goodcharge;
    vector<int> zerocharge;
    vector<int> chargevalue;
    ///BBB
    //Track charge * Track charge
    if (top2->GetComputedCharge().ByTrackCount && top1->GetComputedCharge().ByTrackCount) 
      {
	int top1charge = *(top1->GetComputedCharge().ByTrackCount );
	int top2charge = *(top2->GetComputedCharge().ByTrackCount );

	double minbtag= std::min(_stats._B1btag , _stats._B2btag );//irles
	if (top1charge * top2charge < 0 && minbtag > btagcut && _stats._B2momentum > pcut)//
	  //irles && _stats._B2btag > btagcut && _stats._B2momentum > pcut)//  && _stats._methodUsed < 1) /
	  {
	    //_stats._qCostheta[0] = (top1charge < 0)? _stats._B1costheta: - _stats._B1costheta;
	    //_stats._qCostheta[1] = (top1charge > 0)? _stats._B2costheta: - _stats._B2costheta;
	    chargevalue.push_back(top1charge);
	    std::cout << "Two vertices are used!\n";
	    //_stats._methodUsed = 1;
	    goodcharge.push_back(1);
	    _stats._methodCorrect = top1->__GetMCCharge() * top1charge > 0;
	    if (!_stats._methodCorrect) 
	      {
		std::cout << "Not Correct!\n";
	      }
	    //_summary._nAfterKinematicCuts++;
	    //return;
	  }
	if ( minbtag> btagcut && _stats._B2momentum > pcut && (top1charge == 0 || top2charge == 0)) 
	  //irles _stats._B2btag > btagcut && _stats._B2momentum > pcut && (top1charge == 0 || top2charge == 0)) 
	  {
	    zerocharge.push_back(1);
	  }
	if (top1charge * top2charge > 0  && minbtag > btagcut && _stats._B2momentum > pcut)  
	  //irles && _stats._B2btag > btagcut && _stats._B2momentum > pcut) 
	  {
	    samecharge.push_back(1);
	  }
      }
		
    //Kaon * Kaon
    if (top2->GetComputedCharge().ByTVCM && top1->GetComputedCharge().ByTVCM) 
      {
	int top1charge = *(top1->GetComputedCharge().ByTVCM );
	int top2charge = *(top2->GetComputedCharge().ByTVCM );
	bool zero = false;
	std::cout << "Start kaonkaon method. charge1="<<top1charge<< "  charge2+"<<top2charge<<"\n";

	if (top1charge * top2charge < 0)//  && _stats._methodUsed < 1) 
	  {
	    //_stats._qCostheta[0] = (top1charge < 0)? _stats._B1costheta: - _stats._B1costheta;
	    //_stats._qCostheta[1] = (top1charge > 0)? _stats._B2costheta: - _stats._B2costheta;
	    std::cout << "Two kaons are used!\n";
	    //_stats._methodUsed = 2;
	    goodcharge.push_back(2);
	    chargevalue.push_back(top1charge);
	    _stats._methodCorrect = top1->__GetMCCharge() * top1charge > 0;
	    if (!_stats._methodCorrect) 
	      {
		std::cout << "Not Correct!\n";
	      }
	    //_summary._nAfterKinematicCuts++;
	    //return;
	  }
	if (top1->GetComputedCharge().ByTrackCount && *(top1->GetComputedCharge().ByTrackCount ) == 0) 
	  {
	    zerocharge.push_back(2);
	    zero = true;
	  }
	if (top2->GetComputedCharge().ByTrackCount && *(top2->GetComputedCharge().ByTrackCount ) == 0 && !zero) 
	  {
	    zerocharge.push_back(2);
	  }
	if (top1charge * top2charge > 0) 
	  {
	    samecharge.push_back(2);
	  }
      }////
    //Track charge + Kaon
    /*if (top1->GetComputedCharge().ByTrackCount && top1->GetComputedCharge().ByTVCM) 
      {
      int top1charge = *(top1->GetComputedCharge().ByTrackCount );
      int top1kaon = *(top1->GetComputedCharge().ByTVCM );
      if (top1charge * top1kaon > 0 && _stats._B1btag > btagcut && _stats._B1momentum > pcut) 
      {
      //_stats._qCostheta[0] = (top1charge < 0)? _stats._B1costheta: -_stats._B1costheta; 
      //_stats._qCostheta[1] = (top1charge > 0)? _stats._B2costheta: - _stats._B2costheta;
      std::cout << "Vertex + kaon for B1 is used!\n";
      //_stats._methodUsed = 3;
      goodcharge.push_back(3);
      chargevalue.push_back(top1charge);
      _stats._methodCorrect = top1->__GetMCCharge() * top1charge > 0;
      if (!_stats._methodCorrect) 
      {
      std::cout << "Not Correct!\n";
      std::cout << "True VTX: " <<  top1->__GetMCCharge() << "\n";
      }
      //_summary._nAfterKinematicCuts++;
      //return;
      }
      if ( _stats._B1btag > btagcut && _stats._B1momentum > pcut && (top1charge == 0)) 
      {
      zerocharge.push_back(3);
      }
      if (top1charge * top1kaon < 0 &&_stats._B1btag > btagcut && _stats._B1momentum > pcut) 
      {
      samecharge.push_back(3);
      }

      }
      if (top2->GetComputedCharge().ByTrackCount && top2->GetComputedCharge().ByTVCM) 
      {
      int top2charge = *(top2->GetComputedCharge().ByTrackCount );
      int top2kaon = *(top2->GetComputedCharge().ByTVCM );
      if (top2charge * top2kaon > 0 && _stats._B2btag > btagcut && _stats._B2momentum > pcut ) 
      {
      //_stats._qCostheta[0] = (top2charge > 0)? _stats._B1costheta: - _stats._B1costheta; 
      //_stats._qCostheta[1] = (top2charge < 0)? _stats._B2costheta: - _stats._B2costheta;
      std::cout << "Vertex + kaon for B2 is used!\n";
      //_stats._methodUsed = 4;
      chargevalue.push_back(-top2charge);
      goodcharge.push_back(4);
      _stats._methodCorrect = top1->__GetMCCharge() * top2charge < 0;
      if (!_stats._methodCorrect) 
      {
      std::cout << "Not Correct!\n";
      std::cout << "True VTX: " <<  top2->__GetMCCharge() << "\n";
      }
      //_summary._nAfterKinematicCuts++;
      //return;
      }
      if ( _stats._B2btag > btagcut && _stats._B2momentum > pcut && (top2charge == 0)) 
      {
      zerocharge.push_back(4);
      }
      if (top2charge * top2kaon < 0 && _stats._B2btag > btagcut && _stats._B2momentum > pcut) 
      {
      samecharge.push_back(4);
      }
      }//
      if (top2->GetComputedCharge().ByTrackCount && top1->GetComputedCharge().ByTVCM) 
      {
      int top2charge = *(top2->GetComputedCharge().ByTrackCount );
      int top1kaon = *(top1->GetComputedCharge().ByTVCM );
      if (top2charge * top1kaon < 0 &&  _stats._B2btag > btagcut && _stats._B2momentum > pcut) 
      {
      //_stats._qCostheta[0] = (top2charge > 0)? _stats._B1costheta: - _stats._B1costheta; 
      //_stats._qCostheta[1] = (top2charge < 0)? _stats._B2costheta: - _stats._B2costheta;
      std::cout << "Vertex2 + kaon1 is used!\n";
      //_stats._methodUsed = 6;
      chargevalue.push_back(-top2charge);
      goodcharge.push_back(6);
      _stats._methodCorrect = top1->__GetMCCharge() * top1kaon > 0;
      if (!_stats._methodCorrect) 
      {
      std::cout << "Not Correct!\n";
      }
      //_summary._nAfterKinematicCuts++;
      //return;
      }
      if ( _stats._B2btag > btagcut && _stats._B2momentum > pcut && top1->GetComputedCharge().ByTrackCount && *(top1->GetComputedCharge().ByTrackCount ) == 0) 
      {
      zerocharge.push_back(6);
      }
      if (top2charge * top1kaon > 0 &&  _stats._B2btag > btagcut && _stats._B2momentum > pcut)
      {
      samecharge.push_back(6);
      }
      }///
      if (top1->GetComputedCharge().ByTrackCount && top2->GetComputedCharge().ByTVCM) 
      {
      int top1charge = *(top1->GetComputedCharge().ByTrackCount );
      int top2kaon = *(top2->GetComputedCharge().ByTVCM );
      if (top1charge * top2kaon < 0 &&  _stats._B1btag > btagcut && _stats._B1momentum > pcut) 
      {
      //_stats._qCostheta[0] = (top1charge < 0)? _stats._B1costheta: - _stats._B1costheta; 
      //_stats._qCostheta[1] = (top1charge > 0)? _stats._B2costheta: - _stats._B2costheta;
      std::cout << "Vertex1 + kaon2 is used!\n";
      //_stats._methodUsed = 5;
      chargevalue.push_back(top1charge);
      goodcharge.push_back(5);
      _stats._methodCorrect = top1->__GetMCCharge() *  top1charge > 0;
      if (!_stats._methodCorrect) 
      {
      std::cout << "Not Correct!\n";
      }
      //_summary._nAfterKinematicCuts++;
      //return;
      }
      if ( _stats._B1btag > btagcut && _stats._B1momentum > pcut && top2->GetComputedCharge().ByTrackCount &&  *(top2->GetComputedCharge().ByTrackCount ) == 0) 
      {
      zerocharge.push_back(5);
      }
      if (top1charge * top2kaon > 0 &&_stats._B1btag > btagcut && _stats._B1momentum > pcut) 
      {
      samecharge.push_back(5);
      }

      }//*/
    _stats._methodRefused = samecharge.size();
    _stats._methodUsed = goodcharge.size();
    _stats._methodZero = zerocharge.size();
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
    if (zerocharge.size() > 0) 
      {
	std::cout << "ZERO CHARGE: ";
	for (unsigned int i = 0; i < zerocharge.size(); i++) 
	  {
	    std::cout << " " << zerocharge[i];
	    _stats._methodZeroCharge[i] = zerocharge[i];
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
	    _stats._methodUsed = 0;
	  }
	else 
	  {
	    if ( _stats._MCMass > _massCutparameter && _stats._MCPDG == 5) 
	      {
		_summary._nAfterKinematicCuts++;
	      }
	    _stats._qCostheta[0] = (sum < 0)? _stats._B1costheta: - _stats._B1costheta;
	    _stats._qCostheta[1] = (sum > 0)? _stats._B2costheta: - _stats._B2costheta;
	    _stats._qCostheta1 = (sum < 0)? _stats._B1costheta: - _stats._B1costheta;
	    _stats._qCostheta2 = (sum > 0)? _stats._B2costheta: - _stats._B2costheta;
	  }
      }
    return;//*/
    /*if (_stats._B1charge * _stats._B2charge < 0 && _stats._B1momentum > 0 && _stats._B2momentum > 0) 
      {
      int b1charge = _stats._B1charge  / std::abs(_stats._B1charge);
      int b2charge = _stats._B2charge  / std::abs(_stats._B2charge);
      _stats._qCostheta[0] = -_stats._B1costheta * b1charge;
      _stats._qCostheta[1] = -_stats._B2costheta * b2charge;
      }*/
		
  }

  void BBbarAnalysis::MatchB(vector<RecoJet*> * bjets, vector< MCParticle * > & mcbs, LCCollection * mcvtxcol)
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

  void BBbarAnalysis::ClearVariables()
  {
    _stats._qMCcostheta[0] = -2;
    _stats._qMCcostheta[1] = -2;
    _stats._MCMass = -1;
    _stats.Clear();
  }

  void BBbarAnalysis::End()
  {   
    _hSumTree->Fill();
    _hfile->Write();
    _hfile->Close();
  }

}
