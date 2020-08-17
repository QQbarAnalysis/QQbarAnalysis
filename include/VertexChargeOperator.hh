#ifndef VertexChargeOperator_h
#define VertexChargeOperator_h 

#include <vector>
#include <ctime>
#include <cstdlib>
#include "MathOperator.hh"
#include "TopQuark.hh"
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
    float GetAsymmetryTVCM(TopQuark * top, TopQuark * top2); //TernaryVertexChargeMeasurement
    int GetResultingB();
    int CountKaons(TopQuark * top, TopQuark * top2);
    std::vector< EVENT::ReconstructedParticle * > GetKaons(RecoJet * top);
    float ComputeCharge(RecoJet * top);
    EVENT::ReconstructedParticle * __getKaonsCheat( EVENT::ReconstructedParticle * &particle);
    EVENT::ReconstructedParticle * __getHadronsCheat( EVENT::ReconstructedParticle * &particle, int pdg);
    bool __magicBall(float threshold, float seed = 0.0);
    bool isKaon(EVENT::ReconstructedParticle *particle);
    bool isKaonCheat(EVENT::ReconstructedParticle *particle);
    int getPDGtrack(EVENT::ReconstructedParticle *particle);
    
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
    EVENT::Vertex * getTernaryVertex(TopQuark * top);
    EVENT::ReconstructedParticle * getFlavourParticle(EVENT::Vertex * ternary);
    EVENT::ReconstructedParticle * __getKaonCheat(EVENT::Vertex * ternary);
    std::vector< EVENT::ReconstructedParticle * > __filterOutCheat(std::vector< EVENT::ReconstructedParticle * > particles, int type);
    std::vector< EVENT::ReconstructedParticle * > __getKaonsCheat(const std::vector< EVENT::ReconstructedParticle * > & particles);
    EVENT::ReconstructedParticle * getKaon(EVENT::Vertex * ternary);
    std::vector< EVENT::ReconstructedParticle * > getKaons(const std::vector< EVENT::ReconstructedParticle * > & particles);
    float checkAsymmetry(TopQuark * top, EVENT::Vertex * vertex1, EVENT::ReconstructedParticle * kaon1, float & top1costheta);
  };
} /* QQbarProcessor */

#endif
