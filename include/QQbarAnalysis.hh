#ifndef QQbarAnalysis_hh
#define QQbarAnalysis_hh

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
#include <IMPL/LCCollectionVec.h>

// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"
#include "marlin/Processor.h"
#include "lcio.h"
#include <string>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h> 
#include "QQbarTools.hh"
#include "QQbarMCOperator.hh"

//---- Fastjet stuff
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include <fastjet/EECambridgePlugin.hh>
#include <fastjet/JadePlugin.hh>

using namespace lcio ;
using namespace marlin ;
using namespace fastjet;

namespace QQbarProcessor 
{

  class QQbarAnalysis 
  {
	  
  public:
	  
    QQbarAnalysis ();
    virtual ~QQbarAnalysis () {};
	  
    //METHODS
	  
    void Init(std::string _hfilename) ;
    std::vector< MCParticle * > AnalyseGeneratorQQbar(QQbarMCOperator & opera);
    void AnalyseGeneratorISR(QQbarMCOperator & opera);
    void AnalyseGeneratorQQbar_PS(QQbarMCOperator & opera, float _Rparam_jet_ps, float _pparam_jet_ps);
    void AnalyseGeneratorQQbar_Stable(QQbarMCOperator & opera, float _Rparam_jet_ps, float _pparam_jet_ps);
    bool WritePFOInfo(LCEvent * evt, ReconstructedParticle *component, int pfo_recorded, int ijet, int ivtx, std::string _colName, std::string _versionPID);
    void PFOCheatInfo(ReconstructedParticle * component, QQbarMCOperator& operaMC, std::vector<MCParticle*> isr_stable, int npfo_recorded);
    void AnalyseQQbar(LCEvent * evt,
		      bool _boolDBDanalysis,
		      std::string _colName ,
		      std::string _colRelName,
		      std::string _initialJetsColName,
		      std::string _JetsColName ,
		      std::string _JetsRelColName ,
		      std::string _MCColName,
		      std::string _versionPID,
		      float _Rparam_jet_ps,
		      float _pparam_jet_ps
		      ) ;

    void ClearVariables();
    void End();
    
		    
  private:


    TFile * _hfile;
    TTree * _hTree;
    StatsData_QQbar _stats;

  } ;
		
} /* TTbarAnalisys */

#endif



