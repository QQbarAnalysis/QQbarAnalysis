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
#include <EVENT/MCParticle.h> 
#include <EVENT/LCCollection.h> 
#include <IMPL/LCCollectionVec.h>
// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"
#include "marlin/Processor.h"
#include "lcio.h"
#include <string>
#include <TFile.h>
#include <TTree.h>

#include "QQbarAnalysis.hh"


using namespace lcio ;
using namespace marlin ;


namespace QQbarProcessor 
{
  enum ANALYSIS_TYPE
    {
      QQbar = 0
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

    QQbarAnalysis _qqbaranalysis;

	  
    /** Input collection name.
     */
    int _type;
    std::string _hfilename;
    ANALYSIS_TYPE _analysisType ;
    std::string _colName ;
    std::string _MCColName ;
    std::string _JetsColName ;
    std::string _JetsRelColName ;
    std::string _colRelName;
    std::string _initialJetsColName;
    std::string _versionPID;
    bool _boolDBDanalysis;

    float _Rparam_jet_ps;
    float _pparam_jet_ps;

    int _nRun ;

  } ;
		
} /* TTbarAnalisys */

#endif



