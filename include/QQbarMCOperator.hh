#include <stdlib.h>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <IMPL/MCParticleImpl.h>
#include <EVENT/LCCollection.h>
#include "MathOperator.hh"
#include <EVENT/LCObject.h>
#include <UTIL/LCRelationNavigator.h>

#include "marlin/VerbosityLevels.h"
#ifndef _QQbarMCOperator_hh
#define _QQbarMCOperator_hh
namespace QQbarProcessor 
{
  class QQbarMCOperator 
  {
  public:
    //
    //	Constants
    //
    
    //
    //	Constructors
    //
    QQbarMCOperator (EVENT::LCCollection * col, EVENT::LCCollection * colrel);
    virtual ~QQbarMCOperator () {};
    //
    //	Pure MC Methods
    //
    std::vector< EVENT::MCParticle * > GetQQbarQuarksPS();
    std::vector< EVENT::MCParticle * > GetPairParticles(int pdg);
    std::vector< std::vector<EVENT::MCParticle*> > GetQQbarStables();
    bool IsEvent();//function to check that the event is not gamma gamma overlay bkg
    // Relation between PFO and MC
    EVENT::MCParticle* getMCParticle(EVENT::ReconstructedParticle *particle);
    int isOverlay(EVENT::MCParticle * mctrack);
    int getPDG(EVENT::MCParticle *mctrack);
    
  private:
    //
    //	Data
    //
    EVENT::LCCollection * myCollection;
    EVENT::LCCollection * myRelCollection;
    //
    //	Private methods
    //
  };
}
#endif
