#include "QQbarProcessor.hh"
#include "IMPL/LCEventImpl.h"
#include "IMPL/LCRunHeaderImpl.h"
#include "IMPL/LCGenericObjectImpl.h"
#include "IMPL/LCCollectionVec.h"
#include <marlin/ProcessorMgr.h>
#include "marlin/Exceptions.h"

using namespace lcio;
using namespace marlin;
using EVENT::ParticleID;
using EVENT::Track;
using IMPL::MCParticleImpl;
using IMPL::ParticleIDImpl;
using IMPL::ReconstructedParticleImpl;
using std::abs;
using std::string;
using std::vector;

namespace QQbarProcessor
{
	QQbarProcessor aQQbarProcessor;

	QQbarProcessor::QQbarProcessor() : Processor("QQbarProcessor")
	{

		// modify processor description

		// register steering parameters: name, description, class-variable, default value
		registerProcessorParameter("ROOTFileName",
								   "Output ROOT File Name",
								   _hfilename,
								   string("QQbarProcessor.root"));
		registerProcessorParameter("AnalysisType",
								   "Analysis Type (0= default qqbar, -1 backgrounds -started by A. Irles)",
								   _analysisType,
								   0);
		registerProcessorParameter("DBDanalysis",
								   "It is a DBD analysis?",
								   _boolDBDanalysis,
								   true);
		registerInputCollection(LCIO::RECONSTRUCTEDPARTICLE,
								"PFOCollection",
								"PFO collection name",
								_colName,
								string("PandoraPFOs"));
		registerInputCollection(LCIO::RECONSTRUCTEDPARTICLE,
								"JetCollectionName",
								"Name of the Jet collection",
								_JetsColName,
								std::string("RefinedJets"));
		registerInputCollection(LCIO::LCRELATION,
								"JetRelCollectionName",
								"Name of the PrimaryVertex collection",
								_JetsRelColName,
								std::string("FinalJets_rel"));

		registerInputCollection(LCIO::RECONSTRUCTEDPARTICLE,
								"SecondJetCollectionName",
								"Name of the second Jet collection created by LCFIPlus, with improved weights",
								_JetsColName2,
								std::string("RefinedJets2"));
		registerInputCollection(LCIO::LCRELATION,
								"JetRelCollectionNames",
								"Name of the PrimaryVertex collection, for second set of jets",
								_JetsRelColName2,
								std::string("RefinedJets2_rel"));								

		registerInputCollection(LCIO::RECONSTRUCTEDPARTICLE,
								"FourJetCollectionName",
								"Name of the 4 Jet collection",
								_FourJetsColName,
								std::string("FourJets"));						

		
		registerInputCollection(LCIO::MCPARTICLE,
								"MCCollectionName",
								"Name of the MC collection",
								_MCColName,
								std::string("MCParticles"));
		registerInputCollection(LCIO::LCRELATION,
								"RecoMcTruthCollectionName",
								"Name of the RecoMcTruth collection",
								_colRelName,
								std::string("RecoMCTruthLink"));
		registerInputCollection(LCIO::RECONSTRUCTEDPARTICLE,
								"initialJetCollectionName",
								"Name of the initialJet collection, only used for DBD analysis",
								_initialJetsColName,
								std::string("InitialJets"));
		registerProcessorParameter("PIDVersionTag",
								   "version of the PID Method to use (v1, v2, ...)",
								   _versionPID,
								   std::string("_v2"));
		registerProcessorParameter("PIDVersionTag2",
								   "version of the improved PID Method to use (v1, v2, ...) ,.",
								   _versionPID2,
								   std::string("_v3"));
		registerProcessorParameter("StableParticlesCollectionName",
								   "name of the stable particle collection, which is supossed to be used for thrust calculation at particle level",
								   _stablePartCol,
									std::string("StableParticles"));
		registerProcessorParameter("Rparam_jet_ps",
								   "R parameter of the ee_gentkt algorithm (for parton + shower analysis)",
								   _Rparam_jet_ps,
								   (float)1.5);
		registerProcessorParameter("pparam_jet_ps",
								   "p parameter of the ee_gentkt algorithm (for parton + shower analysis)",
								   _pparam_jet_ps,
								   (float)1.0);
	}

	void QQbarProcessor::init()
	{
		// usually a good idea to

		printParameters();
		_nRun = 0;

		// Initialize sum
		std::cout << "Initialize QQbarTree, _analysisType= " << _analysisType << "\n";
		_qqbaranalysis.Init(_hfilename);
	}
	void QQbarProcessor::processRunHeader(LCRunHeader *run)
	{
		_nRun++;
	}

	void QQbarProcessor::processEvent(LCEvent *evt)
	{
		_qqbaranalysis.AnalyseQQbar(evt,
									_boolDBDanalysis,
									_colName,
									_colRelName,
									_initialJetsColName,
									_JetsColName,
									_JetsColName2,
									_FourJetsColName,
									_JetsRelColName,
									_JetsRelColName2,
									_MCColName,
									_versionPID,
									_versionPID2,
									_stablePartCol,
									_Rparam_jet_ps,
									_pparam_jet_ps,
									_analysisType);
	}

	void QQbarProcessor::check(LCEvent *evt)
	{
	}

	void QQbarProcessor::end()
	{

		_qqbaranalysis.End();
	}

}
