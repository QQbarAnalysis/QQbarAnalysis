#ifndef VertexChargeOperator_h
#define VertexChargeOperator_h 

#include <vector>
#include <ctime>
#include <cstdlib>
#include "MathOperator.hh"
#include <UTIL/PIDHandler.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/Vertex.h>
#include <EVENT/Track.h>
#include <EVENT/MCParticle.h>
#include <EVENT/LCObject.h>
#include <UTIL/LCRelationNavigator.h>
#include <EVENT/LCCollection.h>
#include "marlin/VerbosityLevels.h"                                                                                                  

namespace QQbarProcessor 
{
  class VertexChargeOperator 
  {
  public:
    //
    //	Constants
    //
    static const float BMASS;// = 5.279; //GeV
    static const float CTAU;// = 0.4554; 
    
    //
    //	Constructors
    //
    VertexChargeOperator (EVENT::LCCollection * pfo, EVENT::LCCollection * rel = NULL, bool cheat=false, std::string kaontagger="KaonTagger") ;
    virtual ~VertexChargeOperator () { delete myPIDHandler; };
    //
    //	Methods
    //
    bool isKaon(EVENT::ReconstructedParticle *particle);
    bool isKaonCheat(EVENT::ReconstructedParticle *particle);
    EVENT::MCParticle* getMCParticle(EVENT::ReconstructedParticle *particle);
    int isOverlay(EVENT::MCParticle * mctrack);
    int getPDG(EVENT::MCParticle *mctrack);


  private:
    //
    //	Data
    //
    EVENT::LCCollection * myRelCollection;
    EVENT::LCCollection * myPFOCollection;
    int myResultingB;
    bool doCheating;
    std::string myAlgorithmName;
    UTIL::PIDHandler * myPIDHandler;
    
    //
    //	Private methods
    //

  };
} /* QQbarProcessor */

#endif
