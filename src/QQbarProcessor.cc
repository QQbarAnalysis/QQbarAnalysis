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
      // case TTBarSemileptonic:
      // 	writer.InitializeStatsTree(_hTree, _stats);
      // 	std::cout << "Initialize TTBarSemileptonicTree, _analysisType= " << _analysisType << "\n";
      // 	break;
      case BBbar:
	std::cout << "Initialize BBarTree, _analysisType= " << _analysisType << "\n";
	_bbbaranalysis.Init(_hfilename, _massCutparameter);
	break;
      // case TTBarHadronic:
      // 	writer.InitializeStatsHadronicTree(_hTree, _stats);
      // 	std::cout << "Initialize TTBarHadronicTree, _analysisType= " << _analysisType << "\n";
      // 	break;
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
      // case TTBarSemileptonic:
      // 	TTbarAnalysis ttbarAnalysis;
      // 	ttbarAnalysis.AnalyseTTBarSemiLeptonic(evt);
      // 	break;
      case BBbar:
	_bbbaranalysis.AnalyseBBBar(evt,
				    _colName ,
				    _JetsColName ,
				    _JetsRelColName ,
				    _MCColName ,
				    _IsoLeptonColName ,
				    _colRelName);
	break;
      // case TTBarHadronic:
      // 	TTbarAnalysis ttbarAnalysis;
      // 	ttbarAnalysis.AnalyseTTBarHadronic(evt);
      // 	break;
      }
    //AnalyseTTBarSemiLeptonic(evt);
  }

  void QQbarProcessor::check( LCEvent * evt ) 
  {
  }


   void QQbarProcessor::end()
  {   

    switch(_analysisType)
      {
      case BBbar:
	std::cout << "End BBarTree, _analysisType= " << _analysisType << "\n";
	_bbbaranalysis.End();
	break;
      }
    //    _hSumTree->Fill();
    // _hfile->Write();
    //   _hfile->Close();
  }

}
