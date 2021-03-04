#include "QQbarMCOperator.hh"
using std::vector;
using std::string;
using EVENT::LCCollection;
using EVENT::MCParticle;
using EVENT::ReconstructedParticle;
using IMPL::MCParticleImpl;
using UTIL::LCRelationNavigator;
using EVENT::LCObject;


namespace QQbarProcessor
{
  QQbarMCOperator:: QQbarMCOperator (LCCollection * col, LCCollection * rel)
  {
    myCollection = col;
    myRelCollection = rel;
  }

  vector< MCParticle * > QQbarMCOperator::GetQQbarQuarksPS()
  {

    int number = myCollection->getNumberOfElements();
    vector< MCParticle * > bbbar_ps;

    // find the process simulated (which quark is in the ps)
    int pdg = 0;
    if(number<3) return bbbar_ps;
    

    for (int i = 0; i < number; i++) {
      MCParticle * particle = dynamic_cast<MCParticle*>( myCollection->getElementAt(i) );
      if( (particle->getPDG() == 92 || particle->getPDG() == 91) && particle->isOverlay()==false) {
	vector <MCParticle * > parents = particle->getParents();
	for(int j=0; j<parents.size(); j++) {
	  MCParticle * parent = parents.at(j);
	  bbbar_ps.push_back(parent);
	}
      }
    }
    return bbbar_ps;

  }

  //Added by Seidai in 2020.Sep.16
  vector<vector<MCParticle*>>QQbarMCOperator::GetQQbarStables() {
    //std::cout << "##################################" << std::endl;
    //std::cout << "##         Stable level         ##" << std::endl;
    //std::cout << "##################################" << std::endl;


    int number = myCollection -> getNumberOfElements();
    vector<vector<MCParticle*>> stables;
    if(number<3) return stables; //return empty                                                      
    vector<MCParticle*> stable_stables;
    vector<MCParticle*> isr_stables;
    vector<MCParticle*> overlay_stables;
    int istable;// the border of stableization

    int isrphotons[2];
    isrphotons[0]=-1;
    isrphotons[1]=-1;

    vector<MCParticle*> pairISR;
    for(int i=2; i<number; i++) {
      MCParticle* particle = dynamic_cast<MCParticle*>(myCollection->getElementAt(i));
      if (particle->getPDG() == 22 && pairISR.size()<2 && particle->getGeneratorStatus()==1) {
	pairISR.push_back(particle);
	isrphotons[pairISR.size()-1]=i;
      }

    }
    for(int i=isrphotons[pairISR.size()-1]+1; i<number; i++) {


      MCParticle* particle = dynamic_cast<MCParticle*>(myCollection->getElementAt(i));
      vector<MCParticle*> daughters = particle->getDaughters();
     
      streamlog_out(DEBUG)<<"\n MCCollection, particle:"<<i;
      streamlog_out(DEBUG)<<" pdg="<<particle->getPDG();
      streamlog_out(DEBUG)<<" satus="<<particle->getGeneratorStatus();
      streamlog_out(DEBUG)<<" Ndaughters="<<daughters.size();
      streamlog_out(DEBUG)<<" E="<<particle->getEnergy();
      streamlog_out(DEBUG)<<" px="<<particle->getMomentum()[0];
      streamlog_out(DEBUG)<<" py="<<particle->getMomentum()[1];
      streamlog_out(DEBUG)<<" pz="<<particle->getMomentum()[2];
      streamlog_out(DEBUG)<<" m="<<particle->getMass();
      streamlog_out(DEBUG)<<" charge="<<particle->getCharge();
      if(daughters.size()==0 && particle->isOverlay()==true) {
        overlay_stables.push_back(particle);
	streamlog_out(DEBUG)<<" ----> IS OVERLAY";
      }
      
      if(daughters.size()==0 && particle->isOverlay()==false) {

	int ISRstable=0;

	vector<MCParticle*> parents = particle->getParents();
	for(int j=0; j<parents.size(); j++) {
	  if(parents.at(j) == pairISR.at(0) || parents.at(j) == pairISR.at(1)) {
	    ISRstable=1;
	  } else {
	    vector<MCParticle*> parents2 = parents.at(j)->getParents();
	    for(int j2=0; j2<parents2.size(); j2++) {
	      if(parents2.at(j2) == pairISR.at(0) || parents2.at(j2) == pairISR.at(1)) { 
		ISRstable=1;
	      } else {
		vector<MCParticle*> parents3 = parents2.at(j2)->getParents();
		for(int j3=0; j3<parents3.size(); j3++) {
		  if(parents3.at(j3) == pairISR.at(0) || parents3.at(j3) == pairISR.at(1)) { 
		    ISRstable=1;
		  }
		}
	      }
	    }
	  }
	}
	
	if(ISRstable==0) {
	  stable_stables.push_back(particle);
	  streamlog_out(DEBUG)<<" ----> IS STABLE";
	}

	if(ISRstable==1) {
	  isr_stables.push_back(particle);
	  streamlog_out(DEBUG)<<" ----> IS ISR";
	}
      }
    }

    stables.push_back(stable_stables);
    stables.push_back(isr_stables);
    stables.push_back(overlay_stables);
    return stables;
  }//GetQQbarStables()


  ///DO NOT USE THAT ON T-QUARKS!!!
  bool QQbarMCOperator::IsEvent() {
  
    //    std::cout<<"GetPairParticles("<<pdg<<")"<< "\n";
    int number = myCollection->getNumberOfElements();
    MCParticle * p1 = NULL;
    MCParticle * p2 = NULL;

    bool event=true;
    for (int i = 0; i < 2; i++) {
      MCParticle * particle = dynamic_cast<MCParticle*>( myCollection->getElementAt(i) );
      if(particle->getPDG() !=22) event=false;
    }
 
    int pdgqqbar=0;
    for (int i = 2; i < 4; i++) { 
      MCParticle * particle = dynamic_cast<MCParticle*>( myCollection->getElementAt(i) );
      pdgqqbar+=particle->getPDG();
      if(fabs(particle->getPDG()) >5) event=false;                                                                                                             
    } 
    if(pdgqqbar!=0)  {
      event=false;
      streamlog_out(DEBUG) << "Event is not QQbar: pdgqqbar="<<pdgqqbar<<"\n";                            
    }
    return event;
  }

  //DO NOT USE THAT ON T-QUARKS!!!
  vector< MCParticle * > QQbarMCOperator::GetPairParticles(int pdg) {
    pdg = abs(pdg);
    vector< MCParticle * > pair;
    if (pdg < 1) {
      return pair;
    }
    //    std::cout<<"GetPairParticles("<<pdg<<")"<< "\n";
    int number = myCollection->getNumberOfElements();
    MCParticle * b = NULL;
    MCParticle * bbar = NULL;

    bool bool_bbbar[2]={false};

    bool recorded=false;
    int j=0;
    for (int i = 0; i < number; i++) {
      if(pdg==22) {
	MCParticle * particle = dynamic_cast<MCParticle*>( myCollection->getElementAt(i) );
	if (particle->getPDG() == 22 && particle->getGeneratorStatus()==1) {
	  pair.push_back(particle);
	} 
	if(pair.size()==2) break;
	
      } else {      
	MCParticle * particle = dynamic_cast<MCParticle*>( myCollection->getElementAt(i) );
	if(fabs(particle->getPDG())<6) {
	  if(particle->getPDG()>0) b=particle;
	  else bbar=particle;
	  bool_bbbar[j]=true;
	  j++;
	}
	if(bool_bbbar[1]==true) break;

      }
    }
    
    if(pdg==22) return pair;
    if(bool_bbbar[0]==true && bool_bbbar[1]==true) {
      pair.push_back(b);
      pair.push_back(bbar);
      return pair;
    } else return pair;

  }

  // *****************************************************************************************
  // PFO to MC relations
  MCParticle * QQbarMCOperator::getMCParticle(EVENT::ReconstructedParticle *particle) {
    
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

  
  int QQbarMCOperator::isOverlay(MCParticle * winner) {

    if(winner==NULL) return 0;
    return winner->isOverlay();
  }

  
  int QQbarMCOperator::getPDG(MCParticle * winner) {                     
    
    if(winner==NULL) return 0;
    return abs(winner->getPDG());
  }

}
