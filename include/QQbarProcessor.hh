#ifndef QQbarProcessor_h
#define QQbarProcessor_h 1
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

//#include "MathOperator.hh"
//#include "ClusteringOperator.hh"
//#include "VertexChargeOperator.hh"
//#include "QQBarMCOperator.hh"
//#include "TopQuark.hh"
//#include "RecoJet.hh"
//#include "TreeWriter.hh"
//#include "TreeStructures.hh"
#include "BBbarAnalysis.hh"
//#include "QQbarTools.hh"

using namespace lcio ;
using namespace marlin ;


namespace QQbarProcessor 
{
	enum ANALYSIS_TYPE
	{
		TTBarSemileptonic = 0,
		TTBarHadronic = 1,
		BBbar = 2
	};
	class QQbarProcessor : public Processor 
	{
	  
	 public:
	  
	  virtual Processor*  newProcessor() { return new QQbarProcessor ; }
	  
	  
	  QQbarProcessor() ;
	  
	  /** Called at the begin of the job before anything is read.
	   * Use to initialize the processor, e.g. book histograms.
	   */
	  virtual void init() ;
	  
	  /** Called for every run.
	   */
	  virtual void processRunHeader( LCRunHeader* run ) ;
	  
	  /** Called for every event - the working horse.
	   */
	  virtual void processEvent( LCEvent * evt ) ; 
	  
	  
	  virtual void check( LCEvent * evt ) ; 
	  
	  
	  /** Called after data processing for clean up.
	   */
	  virtual void end() ;

	  BBbarAnalysis _bbbaranalysis;
	  
	  /** Input collection name.
	   */
	  int _type;
	  std::string _hfilename;
	  ANALYSIS_TYPE _analysisType ;
	  std::string _colName ;
	  std::string _MCColName ;
	  std::string _JetsColName ;
	  std::string _JetsRelColName ;
	  std::string _JetsVtxColName ;
	  std::string _IsoLeptonColName;
	  std::string _MCVtxColName ;
	  std::string _colRelName;
	  int _ePolarization;
	  float _massCutparameter;


	  int _nRun ;

	} ;

  /*
	bool sortByBtag(RecoJet *lhs, RecoJet *rhs) {return lhs->GetBTag() > rhs->GetBTag(); }
	bool sortByCostheta(RecoJet *lhs, RecoJet *rhs) 
	{
	  	return std::abs(lhs->GetCostheta()) >  std::abs(rhs->GetCostheta()); 
	}
	bool sortByEnergy(EVENT::ReconstructedParticle *lhs, EVENT::ReconstructedParticle *rhs) 
	{
	  	return std::abs(lhs->getEnergy()) >  std::abs(rhs->getEnergy()); 
		}*/
		
} /* TTbarAnalisys */

#endif



