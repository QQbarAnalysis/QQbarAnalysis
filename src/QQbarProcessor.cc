#include "QQbarProcessor.hh"
#include "IMPL/LCEventImpl.h"
#include "IMPL/LCRunHeaderImpl.h"
#include "IMPL/LCGenericObjectImpl.h"
#include "IMPL/LCCollectionVec.h"
#include <marlin/ProcessorMgr.h> 
#include "marlin/Exceptions.h"

using namespace lcio ;
using namespace marlin ;
using std::vector;
using std::string;
using std::abs;
using EVENT::Track;
using IMPL::ReconstructedParticleImpl;
using IMPL::MCParticleImpl;
using EVENT::ParticleID;
using IMPL::ParticleIDImpl;

namespace QQbarProcessor
{
  QQbarProcessor aQQbarProcessor ;


  QQbarProcessor::QQbarProcessor() : Processor("QQbarProcessor") 
  {
	  
    // modify processor description
    
    // register steering parameters: name, description, class-variable, default value
    registerProcessorParameter( "ROOTFileName",
				"Output ROOT File Name",
				_hfilename,
				string("QQbarProcessor.root") );
    registerProcessorParameter( "ElectronPolarisation",
				"Helicity of e- beam",
				_ePolarization,
				0 );
    registerProcessorParameter( "MassCut",
				"Mass cut on qqbar",
				_massCutparameter,
				(float)200. );
    registerProcessorParameter( "AnalysisType",
				"Analysis Type (0=ttbar semileptonic, 1=ttbar hadronic, 2=bbbar)",
				_type,
				_type );
    registerProcessorParameter( "DBDanalysis",
				"It is a DBD analysis? Only for bbbar.",
				_boolDBDanalysis,
  			true
				);
    registerProcessorParameter( "KaonCheat",
				"Do we cheat in the kaon identification?",
				_boolkaoncheat,
				true
				);
    registerProcessorParameter( "KaonTaggerName",
				"Kaon Tagger PIDHandler name",
				_KaonTaggerName,
				string("KaonTagger")
				);
    registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE , 
			     "PFOCollection",
			     "PFO collection name"  ,
			     _colName ,
			     string("PandoraPFOs")
			     ) ;
    registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			     "JetCollectionName",
                             "Name of the Jet collection",
			     _JetsColName,
			     std::string("FinalJets")
                             );
    registerInputCollection( LCIO::LCRELATION,
			     "JetRelCollectionName" , 
			     "Name of the PrimaryVertex collection"  ,
			     _JetsRelColName ,
			     std::string("FinalJets_rel")
			     );
    registerInputCollection( LCIO::VERTEX,
			     "GenVtxCollectionName" , 
			     "Name of the PrimaryVertex collection"  ,
			     _MCVtxColName ,
			     std::string("MCVertex")
			     );
    registerInputCollection( LCIO::MCPARTICLE,
			     "MCCollectionName" , 
			     "Name of the MC collection"  ,
			     _MCColName ,
			     std::string("MCParticles")
			     );
    registerInputCollection( LCIO::MCPARTICLE,
			     "IsoLeptonCollectionName" , 
			     "Name of the isolepton collection"  ,
			     _IsoLeptonColName ,
			     std::string("SelectedLepton")
			     );
    registerInputCollection( LCIO::LCRELATION,
			     "RecoMcTruthCollectionName" , 
			     "Name of the RecoMcTruth collection"  ,
			     _colRelName ,
			     std::string("RecoMCTruthLink")
			     );
    registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			     "initialJetCollectionName" , 
			     "Name of the initialJet collection, only used for DBD-bbbar analysis"  ,
			     _initialJetsColName ,
			     std::string("InitialJets")
			     );

    registerProcessorParameter( "Rparam_jet_ps",
				"R parameter of the ee_gentkt algorithm (for parton + shower analysis)",
				_Rparam_jet_ps,
				(float)1.5 );  
    registerProcessorParameter( "pparam_jet_ps",
				"p parameter of the ee_gentkt algorithm (for parton + shower analysis)",
				_pparam_jet_ps,
				(float)1.0 );
  }
	
  void QQbarProcessor::init() 
  { 
    // usually a good idea to

    std::cout << "Type: " <<  _type << "\n";
    _analysisType = static_cast<ANALYSIS_TYPE>(_type);
    std::cout << "Type: " <<  _analysisType << "\n";

    printParameters() ;
    std::cout << "_analysisType: " << _analysisType << "\n";
    _nRun = 0 ;

    // Initialize sum
    switch(_analysisType)
      {
      case TTbarSemileptonic:
	std::cout << "Initialize TTbarSemileptonicTree, _analysisType= " << _analysisType << "\n";
	_ttbaranalysis.Init(_hfilename,0, _massCutparameter);
       	break;
      case BBbar:
	std::cout << "Initialize BBarTree, _analysisType= " << _analysisType << "\n";
	_bbbaranalysis.Init(_hfilename);
	break;
      case TTbarHadronic:
	std::cout << "Initialize TTbarHadronicTree, _analysisType= " << _analysisType << "\n";
	_ttbaranalysis.Init(_hfilename,1, _massCutparameter);
       	break;
      }

  }
  void QQbarProcessor::processRunHeader( LCRunHeader* run) 
  { 
    _nRun++ ;
  } 

  void QQbarProcessor::processEvent( LCEvent * evt )
  {
    switch(_analysisType)
      {
      case TTbarSemileptonic:
       	_ttbaranalysis.AnalyseTTbarSemiLeptonic(evt,
						_colName ,
						_MCColName ,
						_JetsColName ,
						_JetsRelColName ,
						_IsoLeptonColName,
						_MCVtxColName ,
						_colRelName);
       	break;

      case BBbar: 
	{ 
	  _bbbaranalysis.AnalyseBBbar(evt,
				      _boolDBDanalysis,
				      _boolkaoncheat,
				      _colName ,
				      _colRelName,
				      _initialJetsColName,
				      _JetsColName ,
				      _JetsRelColName ,
				      _MCColName,
				      _KaonTaggerName,
				      _Rparam_jet_ps,
				      _pparam_jet_ps
				      );
	}
	break;

      case TTbarHadronic:
	_ttbaranalysis.AnalyseTTbarHadronic(evt,
					    _colName ,
					    _MCColName ,
					    _JetsColName ,
					    _JetsRelColName ,
					    _MCVtxColName ,
					    _colRelName);
       	break;
      }
  }

  void QQbarProcessor::check( LCEvent * evt ) 
  {
  }


  void QQbarProcessor::end()
  {   

    switch(_analysisType)
      {

      case TTbarSemileptonic:
	_ttbaranalysis.End();
	break;

      case BBbar:
	_bbbaranalysis.End();
	break;
	
      case TTbarHadronic:
	_ttbaranalysis.End();
	break;
      }
  }
  
}
