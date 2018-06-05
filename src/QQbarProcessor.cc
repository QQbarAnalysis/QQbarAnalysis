#include "QQbarProcessor.hh"

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
				"Analysis Type",
				_type,
				_type );
    registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE , 
			     "PFOCollection",
			     "Name of the Calorimeter hit collection"  ,
			     _colName ,
			     string("PandoraPFOs") ) ;

    registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			     "JetCollectionName" , 
			     "Name of the Jet collection"  ,
			     _JetsColName ,
			     std::string("FinalJets")
			     //std::string("RecoveredJets")
			     );
    registerInputCollection( LCIO::LCRELATION,
			     "JetRelCollectionName" , 
			     "Name of the PrimaryVertex collection"  ,
			     _JetsRelColName ,
			     std::string("FinalJets_rel")
			     //std::string("RecoveredJets_rel")
			     );
    registerInputCollection( LCIO::MCPARTICLE,
			     "MCCollectionName" , 
			     "Name of the MC collection"  ,
			     _MCColName ,
			     std::string("MCParticlesSkimmed")
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
	_bbbaranalysis.Init(_hfilename, _massCutparameter);
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
						_JetsVtxColName ,
						_IsoLeptonColName,
						_MCVtxColName ,
						_colRelName);
       	break;

      case BBbar:
	_bbbaranalysis.AnalyseBBBar(evt,
				    _colName ,
				    _JetsColName ,
				    _JetsRelColName ,
				    _MCColName ,
				    _IsoLeptonColName ,
				    _colRelName);
	break;

      case TTbarHadronic:
	_ttbaranalysis.AnalyseTTbarHadronic(evt,
					    _colName ,
					    _MCColName ,
					    _JetsColName ,
					    _JetsRelColName ,
					    _JetsVtxColName ,
					    _IsoLeptonColName,
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
