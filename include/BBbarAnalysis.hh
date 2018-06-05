#ifndef BBbarAnalysis_hh
#define BBbarAnalysis_hh

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

//#include <EVENT/LCObject.h>
#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/Vertex.h>
#include <UTIL/LCRelationNavigator.h>
#include <UTIL/PIDHandler.h>
#include <IMPL/ReconstructedParticleImpl.h>

// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"
#include "marlin/Processor.h"
#include "lcio.h"
#include <string>
#include <TFile.h>
#include <TTree.h>
#include "QQbarTools.hh"
#include "QQbarMCOperator.hh"

using namespace lcio ;
using namespace marlin ;


namespace QQbarProcessor 
{

	class BBbarAnalysis 
	{
	  
	public:
	  
	  BBbarAnalysis ();
	  virtual ~BBbarAnalysis () {};
	  
	  //METHODS
	  
	  void Init(std::string _hfilename, float masscut) ;
	  std::vector< MCParticle * > AnalyseGeneratorBBBar(QQbarMCOperator & opera);
	  void AnalyseBBBar(LCEvent * evt, 
			    std::string _colName ,
			    std::string _JetsColName ,
			    std::string _JetsRelColName ,
			    std::string _MCColName ,
			    std::string _IsoLeptonColName ,
			    std::string _colRelName  ) ;

	  void ClearVariables();
	  void End();
    
		    
	private:

	  void ComputeCharge(std::vector< RecoJet * > *jets, VertexChargeOperator & vtxOperator);
	  void MatchB(std::vector<RecoJet*> * bjets, std::vector< MCParticle * > & mcbs, LCCollection * mcvtxcol);

	  float _massCutparameter;
	  float _lowBTagCutparameter;
	  float _highBTagCutparameter;
	  
	  TFile * _hfile;
	  TTree * _hTree;
	  TTree * _hGenTree;
	  TTree * _hSumTree;
	  //TTree * _hBkgTree;

	  // int _bkgPDGs[4];

	  SummaryData _summary;
	  StatsData _stats;
	} ;
		
} /* TTbarAnalisys */

#endif



