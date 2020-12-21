#include <stdlib.h>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <EVENT/MCParticle.h>
#include <IMPL/MCParticleImpl.h>
#include <EVENT/LCCollection.h>
#include "MathOperator.hh"

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
    QQbarMCOperator (EVENT::LCCollection * col);
    virtual ~QQbarMCOperator () {};
    //
    //	Methods
    //
    //DO NOT USE THAT ON T-QUARKS!!!
    std::vector< EVENT::MCParticle * > GetBBbarQuarksPS();
    std::vector< EVENT::MCParticle * > GetPairParticles(int pdg);
    std::vector<EVENT::MCParticle*> GetBBbarHadrons(); //Added by Seidai
    bool IsEvent();//function to check that the event is not gamma gamma overlay bkg
    
    //top quark methods
    std::vector< EVENT::MCParticle * > GetTopPairParticles(float & topBangle, float & topBarBangle);
    std::vector< EVENT::MCParticle * > GetFinalState();
    std::vector< EVENT::MCParticle * > GetFinalStateBkg();
    EVENT::MCParticle * CombineParticles(EVENT::MCParticle * b, EVENT::MCParticle * w);
    EVENT::MCParticle * FindParticle(int pdg);
    std::vector< EVENT::MCParticle * > GetBquarkPair();
    std::vector< EVENT::MCParticle * > GetWPair();
    EVENT::MCParticle * GetNeutrino();
    EVENT::MCParticle * GetTauLepton();
    
  private:
    //
    //	Data
    //
    EVENT::LCCollection * myCollection;
    std::vector< EVENT::MCParticle * > myBquarkPair;
    std::vector< EVENT::MCParticle * > myWPair;
    EVENT::MCParticle * myNeutrino;
    //
    //	Private methods
    //
  };
}
#endif
