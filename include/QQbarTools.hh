#ifndef _QQbarTools_hh_
#define _QQbarTools_hh_
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
#include "lcio.h"
#include <string>
#include <TFile.h>
#include <TTree.h>

#include "MathOperator.hh"
#include "VertexChargeOperator.hh"
#include "RecoJet.hh"
#include "TreeWriter.hh"
#include "TreeStructures.hh"
using namespace lcio ;

namespace QQbarProcessor 
{
	class QQbarTools 
	{
	public:
	  //
	  //	Constants
	  //
	  
	  //
	  //	Constructors
	  //
	  QQbarTools ();
	  virtual ~QQbarTools ();
	  //
	  //	Methods
	  //
	  
	  static std::vector< RecoJet * > * getJets(LCCollection * jetcol, LCCollection *jetrelcol);
          static std::vector< Vertex * > * convert(const std::vector< LCObject * > & objs);
	  static void PrintJet(RecoJet * jet);
	  static void PrintParticle(ReconstructedParticle * jet);
	  static void PrintParticle(MCParticle * jet);
	  static void PrintJets(std::vector< RecoJet * > *jets);

	  static bool sortByBtag(RecoJet *lhs, RecoJet *rhs) 
	  {
	    return lhs->GetBTag() > rhs->GetBTag(); 
	  }

	  static bool sortByCostheta(RecoJet *lhs, RecoJet *rhs)
	  {
	    return std::abs(lhs->GetCostheta()) >  std::abs(rhs->GetCostheta()); 
	  }

	  static bool sortByEnergy(EVENT::ReconstructedParticle *lhs, EVENT::ReconstructedParticle *rhs) 
	  {
	    return std::abs(lhs->getEnergy()) >  std::abs(rhs->getEnergy()); 
	  }
	  

	private:
	  
	};
}
#endif
