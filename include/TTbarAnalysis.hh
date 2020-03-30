#ifndef TTbarAnalysis_hh
#define TTbarAnalysis_hh

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

	class TTbarAnalysis
	{
	  
	 public:
	  
	  TTbarAnalysis ();
	  virtual ~TTbarAnalysis () {};
	  

	  //Main functions
	  void Init(std::string _hfilename, int type, float masscut) ;

	  std::vector< EVENT::MCParticle * > AnalyseGenerator(QQbarMCOperator & opera);
	  void AnalyseTTbarSemiLeptonic(LCEvent * evt,
					std::string _colName ,
					std::string _MCColName ,
					std::string _JetsColName ,
					std::string _JetsRelColName ,
					std::string _IsoLeptonColName,
					std::string _MCVtxColName ,
					std::string _colRelName
					);
	  void AnalyseTTbarHadronic(LCEvent * evt,
					std::string _colName ,
					std::string _MCColName ,
					std::string _JetsColName ,
					std::string _JetsRelColName ,
					std::string _MCVtxColName ,
					std::string _colRelName
					);

	  void ClearVariables();
	  void End();

	private:

	  // METHODS
	  std::vector< TopQuark * > * formW(std::vector< RecoJet * > * bjets,std::vector< RecoJet * > * wjets);
	  std::vector< TopQuark * > * composeTops(std::vector< RecoJet * > * bjets, std::vector< TopQuark * > * wjets);
	  
	  //void Match(std::vector< EVENT::MCParticle * > & mctops, TopQuark * topHadronic, TopQuark * top2 = NULL);
	  //void MatchB(std::vector< EVENT::MCParticle * > & mcbs, TopQuark * topHadronic, TopQuark * top2 =NULL, LCCollection * mcvtxcol = NULL);
	  //void ComputeChargeLepton(TopQuark * top, TopQuark * top2);
	  //float getChi2(TopQuark * c, std::vector<float> & eachchi2);
	  //void ComputeTopParameters(TopQuark * top1, TopQuark * top2);

	  void Match(std::vector< EVENT::MCParticle * > & mctops, std::vector< EVENT::MCParticle * > & mcbs, std::vector< EVENT::MCParticle * > & mcws, TopQuark * topHadronic,  TopQuark * top2 =NULL );
	  void MatchB(std::vector< RecoJet * > *jets, std::vector< EVENT::MCParticle * > & mcbs, LCCollection * mcvtxcol = NULL);
	  void MatchB(std::vector< EVENT::MCParticle * > & mcbs, TopQuark * topHadronic, TopQuark * top2 =NULL, LCCollection * mcvtxcol = NULL);
	  void ComputeCharge(TopQuark * top, TopQuark * top2);
	  void __ComputeChargeCheat(TopQuark * top, TopQuark * top2);
	  void ComputeChargeTVCM(TopQuark * top, TopQuark * top2, VertexChargeOperator & vtxOperator);
	  float getChi2(TopQuark * c);
	  void DecideOnAsymmetry(TopQuark * top, TopQuark * top2);
	  std::vector<int> getOpposite(int i, int j);
	  void test(TopQuark * top, TopQuark * top2, std::vector< RecoJet * > *jets = NULL, std::vector< RecoJet * > *jets2 = NULL, EVENT::ReconstructedParticle * particlei = NULL);


	  /** Input collection name.
	   */
	  std::string _hfilename;

	  int _ePolarization;
	  float _massCutparameter;
	  float _Ebeamparameter;
	  float _lowBTagCutparameter;
	  float _highBTagCutparameter;
	  float _WMassparameter;
	  float _WMassSigmaparameter;
	  float _TopMassparameter;
	  float _TopMassSigmaparameter;
	  float _EBeamparameter;
	  float _EBeamSigmaparameter;
	  float _PStarparameter;
	  float _PStarSigmaparameter;
	  float _CosbWparameter;
	  float _CosbWSigmaparameter;
	  float _GammaTparameter;
	  float _GammaTSigmaparameter;
	  
	  TFile * _hfile;
	  TTree * _hTree;
	  TTree * _hGenTree;
	  TTree * _hSumTree;
	  // TTree * _hBkgTree;

	  //int _bkgPDGs[4];

	  SummaryData _summary;
	  StatsData _stats;
	} ;

		
} /* TTbarAnalisys */

#endif



