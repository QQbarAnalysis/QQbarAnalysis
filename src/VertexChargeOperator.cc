#include "VertexChargeOperator.hh"
using EVENT::ReconstructedParticle;
using UTIL::LCRelationNavigator;
using EVENT::MCParticle;
using EVENT::Vertex;
using EVENT::Track;
using EVENT::LCObject;
using std::vector;
using EVENT::LCCollection;
namespace QQbarProcessor 
{
  // const float VertexChargeOperator::BMASS = 5.279;
  //const float VertexChargeOperator::CTAU = 0.4554;
  VertexChargeOperator:: VertexChargeOperator(LCCollection * pfo, LCCollection * rel, bool cheating, std::string kaontaggername)
  {
    myResultingB = 0;
    doCheating = cheating;
    myRelCollection = rel;
    myAlgorithmName = kaontaggername;
    if (pfo) 
      {
	myPFOCollection = pfo;
	myPIDHandler = new UTIL::PIDHandler(myPFOCollection);
      }
  }
  bool VertexChargeOperator::isKaon(ReconstructedParticle *particle) {
    if (!myPIDHandler) {
      return false;
    }
   
    int pid=0;
    try                                                                                          
      {                                              
	pid = myPIDHandler->getAlgorithmID(myAlgorithmName); 
      }                                             
    catch(UTIL::UnknownAlgorithm &e) 
      {
	streamlog_out(DEBUG) << e.what() <<"\n";                                                
	return false;
      }    

    int pdg = myPIDHandler->getParticleID(particle, pid).getPDG();
    if (abs(pdg) == 321 && abs(particle->getType()) != 11 && abs(particle->getType()) != 13) {
      streamlog_out(DEBUG) << "\t Kaons p: " << MathOperator::getModule(particle->getMomentum()) << " q: " << particle->getCharge() << "\n";
      return true;
    }
    
    return false;
  }

  MCParticle * VertexChargeOperator::getMCParticle(ReconstructedParticle *particle) {
    
    LCRelationNavigator navigator(myRelCollection);
    streamlog_out(DEBUG) <<"getPDG: using Reconstructed collection \n";

    vector< LCObject * > obj = navigator.getRelatedToObjects(particle);
    vector< float > weights = navigator.getRelatedToWeights(particle);
    MCParticle * winner = NULL;
    MCParticle * winner2 = NULL;

    float maxweight = 0.50;
    for (unsigned int i = 0; i < obj.size(); i++) {
      if(particle->getTracks().size()!=0) {
        weights[i] = fmod(weights[i],10000)/1000.;
        streamlog_out(DEBUG) <<"getPDG : PFO is a TRACK \n";
      } else {
        streamlog_out(DEBUG) <<"getPDG : PFO is a not a TRACK \n";
      }
      //considerations on the track weigth from Mikael:      
      //The track-part of the weight of a PFO should just be a copy of the weight in the 
      //corresponding track-object (in permil) so (pfowgt%10000)/1000.0 should           
      //be the same as the track weight. Be aware of the navigators in two               
      //direction (RecoMCTruthLink and MCTruthRecoLink): They link the same              
      //objects, but the weights are different: One tells you which fraction of          
      //the PFO observation comes from which MCParticle, the other tells you             
      //which fraction of all signal produced of the MCParticle goes into the            
      //PFO in question....                                                              

      winner2 = dynamic_cast< MCParticle * >(obj[i]);

      streamlog_out(DEBUG) <<"getMCParticle "<<i<< " max weight "<<maxweight<<" weight "<<weights[i]<<" MCPDG "<<winner2->getPDG()<<" mom "<<MathOperator::getModule(winner2->getMomentum())<<" px: "<<winner2->getMomentum()[0]<< " py: "<<winner2->getMomentum()[1]<< " En\
d point (in m), x, y, z "<<winner2->getEndpoint()[0]<<" "<<winner2->getEndpoint()[1]<<" "<<winner2->getEndpoint()[2]<<"\n";
      if (weights[i] > maxweight) {
        winner = dynamic_cast< MCParticle * >(obj[i]);
        maxweight = weights[i];
      }
    }
    if(!winner) return NULL;
    streamlog_out(DEBUG) <<"end getPDG " <<maxweight<<" "<<winner->getPDG()<< "\n";
    return winner;
  }

  
  int VertexChargeOperator::isOverlay(MCParticle * winner) {

    if(winner==NULL) return 0;
    return winner->isOverlay();
  }

  
  int VertexChargeOperator::getPDG(MCParticle * winner) {                     
    
    if(winner==NULL) return 0;
    return abs(winner->getPDG());
  }

  bool VertexChargeOperator::isKaonCheat(ReconstructedParticle *particle) {
    
    LCRelationNavigator navigator(myRelCollection);
    vector<float> direction = MathOperator::getDirection(particle->getMomentum());
    int tpchits = particle->getTracks()[0]->getSubdetectorHitNumbers()[6];
    float p = MathOperator::getModule(particle->getMomentum());
    float costheta =  std::abs(std::cos( MathOperator::getAngles(direction)[1] ));
    if (costheta > 0.95 || tpchits < 60) 
      {
	return false;
      }
    vector< LCObject * > obj = navigator.getRelatedToObjects(particle);
    vector< float > weights = navigator.getRelatedToWeights(particle);
    MCParticle * winner = NULL;
    float maxweight = 0.50;
    for (unsigned int i = 0; i < obj.size(); i++) {
      weights[i] = fmod(weights[i],10000)/1000.;
      if (weights[i] > maxweight) 
	{
	  winner = dynamic_cast< MCParticle * >(obj[i]);
	  maxweight = weights[i];
	}
    }
    if (!winner) {
      std::cout << "ERROR: no genparticle!\n";
    }
    
    if (winner && abs(winner->getPDG()) == 321) {
      streamlog_out(DEBUG) << "\t Kaons, cheating p: " << MathOperator::getModule(particle->getMomentum()) << " q: " << particle->getCharge() << "\n";
      return true;
    }
    
    return false;
  }



} /* QQbarProcessor */
