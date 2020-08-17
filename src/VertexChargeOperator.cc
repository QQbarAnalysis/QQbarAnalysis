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
  const float VertexChargeOperator::BMASS = 5.279;
  const float VertexChargeOperator::CTAU = 0.4554;
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
  int VertexChargeOperator::GetResultingB()
  {
    return myResultingB;
  }
  float VertexChargeOperator::checkAsymmetry(TopQuark * top, Vertex * vertex1,ReconstructedParticle * kaon1, float & top1costheta)
  {
    float __mccharge = top->GetB()->__GetMCCharge();
    //float bmomentum = top->GetB()->GetHadronMomentum() * 2;
    //float gamma = std::sqrt(bmomentum + BMASS) / BMASS;
    float distance = MathOperator::getModule(vertex1->getPosition());
    //int ntracks = top->GetB()->GetNumberOfVertexParticles();
    float coefficient = distance / CTAU;
    std::cout << "We have a kaon " << kaon1->getType() 
	      << " with charge " << kaon1->getCharge() 
	      << " momentum " << MathOperator::getModule(kaon1->getMomentum())
	      << "  hits " << kaon1->getTracks()[0]->getSubdetectorHitNumbers()[6]
	      << " from b with charge of " << __mccharge
	      << "\n";
    float result = (kaon1->getCharge() < 0.0) ? top1costheta : -top1costheta;
    if (__mccharge * kaon1->getCharge() < 0) 
      {
	top->SetResultTVCM(-1);
	std::cout << "FATAL: Charges are different!!!\n";
	std::cout << "N particles: " << top->GetB()->GetNumberOfVertexParticles()
		  << " Ternary charge: " << vertex1->getAssociatedParticle()->getCharge()
		  << " distance: " << MathOperator::getModule(vertex1->getPosition())
		  << "\n";
      }
    else 
      {
	top->SetResultTVCM(1);
      }
    return result;
  }

  vector< ReconstructedParticle * > VertexChargeOperator::GetKaons(RecoJet * top)
  {
    vector< Vertex * > * vertices = top->GetRecoVertices();
    vector< ReconstructedParticle * > secparticles;
    vector< ReconstructedParticle * > kaons;
    for (unsigned int i = 0; i < vertices->size(); i++) 
      {
	secparticles.reserve(secparticles.size() + vertices->at(i)->getAssociatedParticle()->getParticles().size());
	secparticles.insert(secparticles.end(), vertices->at(i)->getAssociatedParticle()->getParticles().begin(), vertices->at(i)->getAssociatedParticle()->getParticles().end());
      }
    if (doCheating) 
      {
	return __getKaonsCheat(secparticles);
      }
    return getKaons(secparticles); 
  }
  int VertexChargeOperator::CountKaons(TopQuark * top1, TopQuark * top2)
  {
    Vertex * vertex1 =  getTernaryVertex(top1);
    Vertex * vertex2 =  getTernaryVertex(top2);
    ReconstructedParticle * kaon1 = __getKaonCheat(vertex1);
    ReconstructedParticle * kaon2 = __getKaonCheat(vertex2);
    if (kaon1 || kaon2) 
      {
	return 1;
      }
    return 0;
  }
	
  float VertexChargeOperator::ComputeCharge(RecoJet * top)
  {
    float result = -2.;
    float purity = 0.95;
    float efficiency = 0.88;
    //Vertex * vertex =  getTernaryVertex(top);
    //ReconstructedParticle * kaon = getKaon(vertex);
    vector<float> direction = MathOperator::getDirection(top->getMomentum());
    float top1costheta =  std::cos( MathOperator::getAngles(direction)[1] );
    vector< ReconstructedParticle * > kaons = GetKaons(top);
    /*if (kaon) 
      {
      kaons.push_back(kaon);
      }*/
    /*if (kaons.size() == 1) 
      {
      JetCharge & topCharge = top1->GetComputedCharge();
      result = (kaons[0]->getCharge() < 0.0) ? top1costheta : -top1costheta;
      topCharge.ByTVCM = new int(kaons->getCharge());
      }*/
    int sum = 0.0;
    for (int i = 0; i < kaons.size(); i++) 
      {
	sum += kaons[i]->getCharge();
	std::cout << "\tq: " <<  kaons[i]->getCharge() << " p: " << MathOperator::getModule(kaons[i]->getMomentum()) <<"\n";
      }
    if (kaons.size() > 0 && abs(sum) > 0.0) 
      {
	JetCharge & topCharge = top->GetComputedCharge();
	result = (sum < 0.0) ? top1costheta : -top1costheta;

	int sign = sum / abs(sum);
	if (!__magicBall(efficiency, kaons[0]->getMomentum()[0]) && doCheating) 
	  {
	    std::cout << "Magic cancel\n";
	    return 0.0;
	  }
	if (!__magicBall(purity, kaons[0]->getMomentum()[1]) && doCheating) 
	  {
	    std::cout << "Magic flip\n";
	    sign = -sign;
	  }
	topCharge.ByTVCM = new int(sign);
			
      }
    return sum;
  }
  float VertexChargeOperator::GetAsymmetryTVCM(TopQuark * top1, TopQuark * top2)
  {
    std::cout << "\n\n----TVCM method is called----\n";
    Vertex * vertex1 =  getTernaryVertex(top1);
    Vertex * vertex2 =  getTernaryVertex(top2);
    //ReconstructedParticle * kaon1 = __getKaonCheat(vertex1);
    //ReconstructedParticle * kaon2 = __getKaonCheat(vertex2);
    //ReconstructedParticle * kaon1 = getKaon(vertex1);
    //ReconstructedParticle * kaon2 = getKaon(vertex2);
    //vector< ReconstructedParticle * > kaons1 = GetKaons(top1);
    //vector< ReconstructedParticle * > kaons2 = GetKaons(top2);
		
    /*if (kaon1) 
      {
      kaons1.push_back(kaon1);
      }
      if (kaon2) 
      {
      kaons2.push_back(kaon2);
      }*/
    ReconstructedParticle * winner1 = NULL;
    ReconstructedParticle * winner2 = NULL;
    vector<float> direction = MathOperator::getDirection(top1->getMomentum());
    float top1costheta =  std::cos( MathOperator::getAngles(direction)[1] );
    float result = -2.0;
    float maxp = 0;
    std::cout << "Kaons 1 :\n";
    result = ComputeCharge(top1);
    std::cout << "Kaons 2 :\n";
    result = ComputeCharge(top2);
		
    return result;
  }
  Vertex * VertexChargeOperator::getTernaryVertex(TopQuark * top)
  {
    vector< Vertex * > * vertices = top->GetRecoVertices();
    if (!vertices || vertices->size() == 0) 
      {
	return NULL;
      }
    if (vertices->size() == 1) 
      {
	std::cout << "Only one vertex is reconstructed!\n";
	return NULL;
      }
    float maxdistance = 0.0;
    Vertex * winner = NULL;
    for (int i = 0; i < vertices->size(); i++) 
      {
	Vertex * vertex  = vertices->at(i);
	float distance = MathOperator::getModule(vertex->getPosition());
	if (distance > maxdistance) 
	  {
	    winner = vertex;
	    maxdistance = distance;
	  }
      }
    return winner;
  }
  ReconstructedParticle * VertexChargeOperator::getFlavourParticle(Vertex * ternary)
  {
    if (!ternary) 
      {
	return NULL;
      }
    const vector<ReconstructedParticle *> particles = ternary->getAssociatedParticle()->getParticles();
    ReconstructedParticle * result = NULL;
    int count = 0;
    if ( particles.size() > 1) 
      {
	//return NULL;
      }
    for (int i = 0; i < particles.size(); i++) 
      {
	ReconstructedParticle * particle = particles[i];
	if (abs(particle->getType()) == 11 ||      //electron
	    abs(particle->getType()) == 13) 	   //muon
	  {
	    result = particle;
	    count++;
	  }
      }
    if (count>1) 
      {
	std::cout << "ERROR: Multiple leptons found!\n";
	return NULL;
      }
    return result;
  }
  ReconstructedParticle * VertexChargeOperator::getKaon(Vertex * ternary)
  {
    if (!ternary) 
      {
	return NULL;
      }
    const vector<ReconstructedParticle *> particles = ternary->getAssociatedParticle()->getParticles();
    ReconstructedParticle * result = NULL;
    int count = 0;
    vector< ReconstructedParticle * > kaons = getKaons(particles);
    if (kaons.size() > 1) 
      {
	std::cout << "ERROR: Multiple kaons found!\n";
	return NULL;
      }
    if (kaons.size() == 0) 
      {
	std::cout << "ERROR: No kaons found!\n";
	return NULL;
      }
    return kaons[0];
  }
  ReconstructedParticle * VertexChargeOperator::__getKaonCheat(Vertex * ternary)
  {
    if (!ternary) 
      {
	return NULL;
      }
    LCRelationNavigator navigator(myRelCollection);
    const vector<ReconstructedParticle *> particles = ternary->getAssociatedParticle()->getParticles();
    vector< ReconstructedParticle * > kaons = __getKaonsCheat(particles);
    if (kaons.size() > 1) 
      {
	std::cout << "ERROR: Multiple kaons found!\n";
	return NULL;
      }
    if (kaons.size() == 0) 
      {
	std::cout << "ERROR: No kaons found!\n";
	return NULL;
      }
    return kaons[0];
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

    //    int pid = myPIDHandler->getAlgorithmID(myAlgorithmName);
    int pdg = myPIDHandler->getParticleID(particle, pid).getPDG();
    if (abs(pdg) == 321 && abs(particle->getType()) != 11 && abs(particle->getType()) != 13) {
      streamlog_out(DEBUG) << "\t Kaons p: " << MathOperator::getModule(particle->getMomentum()) << " q: " << particle->getCharge() << "\n";
      return true;
    }
    
    return false;
  }
  
  int VertexChargeOperator::getPDGtrack(ReconstructedParticle *particle) {                                                                                                                   

    LCRelationNavigator navigator(myRelCollection);

    vector< LCObject * > obj = navigator.getRelatedToObjects(particle);
    vector< float > weights = navigator.getRelatedToWeights(particle);
    MCParticle * winner = NULL;
    float maxweight = 0.50;
    for (unsigned int i = 0; i < obj.size(); i++) {
      if (weights[i] > maxweight) { 
	winner = dynamic_cast< MCParticle * >(obj[i]);
	maxweight = weights[i];
      }
    }
    if(!winner) return 0;
    return abs(winner->getPDG());
  }
  bool VertexChargeOperator::isKaonCheat(ReconstructedParticle *particle) {

    LCRelationNavigator navigator(myRelCollection);
    
    //std::cout << "Charge: " << particle->getCharge() << "\n";
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



vector< ReconstructedParticle * > VertexChargeOperator::getKaons(const vector< ReconstructedParticle * > & particles)
{
  vector< ReconstructedParticle * > result;
  if (!myPIDHandler) 
    {
      return result;
    }
  for (unsigned int i = 0; i < particles.size(); i++) 
    {
      ReconstructedParticle * particle = particles[i];
      int pid = 0;//myPIDHandler->getAlgorithmID(myAlgorithmName);
    try                                                                                 
      {                                                                                      
	pid = myPIDHandler->getAlgorithmID(myAlgorithmName);                
      }                                                                                             
    catch(UTIL::UnknownAlgorithm &e)
      {                                                                 
	streamlog_out(DEBUG) << e.what() <<"\n";                                                   
	return result;                                                                              
      }  
    int pdg = myPIDHandler->getParticleID(particle, pid).getPDG();
    if (abs(pdg) == 321 && abs(particle->getType()) != 11 && abs(particle->getType()) != 13) 
      {
	std::cout << "\t Kaons p: " << MathOperator::getModule(particle->getMomentum()) << " q: " << particle->getCharge() << "\n";
	result.push_back(particle);
      }		
    }
  return result;
}

vector< ReconstructedParticle * > VertexChargeOperator::__getKaonsCheat(const vector< ReconstructedParticle * > & particles)
{
  LCRelationNavigator navigator(myRelCollection);
  vector< ReconstructedParticle * > result;
  for (unsigned int i = 0; i < particles.size(); i++) 
    {
      ReconstructedParticle * particle = particles[i];
      //std::cout << "Charge: " << particle->getCharge() << "\n";
      vector<float> direction = MathOperator::getDirection(particle->getMomentum());
      int tpchits = particle->getTracks()[0]->getSubdetectorHitNumbers()[6];
      float p = MathOperator::getModule(particle->getMomentum());
      float costheta =  std::abs(std::cos( MathOperator::getAngles(direction)[1] ));
      if (costheta > 0.95 || tpchits < 60) 
	{
	  continue;
	}
      vector< LCObject * > obj = navigator.getRelatedToObjects(particle);
      vector< float > weights = navigator.getRelatedToWeights(particle);
      MCParticle * winner = NULL;
      float maxweight = 0.50;
      for (unsigned int i = 0; i < obj.size(); i++) 
	{
	  if (weights[i] > maxweight) 
	    {
	      winner = dynamic_cast< MCParticle * >(obj[i]);
	      maxweight = weights[i];
	    }
	}
      if (!winner) 
	{
	  std::cout << "ERROR: no genparticle!\n";
	}
      if (winner && abs(winner->getPDG()) == 321) 
	{
	  result.push_back(particle);
	}
    }
  return result;
}


  //irles function to get Kaons from single Reconstructed Particles
  ReconstructedParticle * VertexChargeOperator::__getKaonsCheat( ReconstructedParticle * & particle)
  {
    LCRelationNavigator navigator(myRelCollection);
    
    for(int k =0; k<particle->getTracks().size(); k++) {
      streamlog_out(DEBUG)<<" Kaon test 3--:  track "<<k<<" d0 and track z0 "<<particle->getTracks()[k]->getD0()<<" "<<particle->getTracks()[k]->getZ0()<<std::endl;
    }
    streamlog_out(DEBUG) << "Charge: " << particle->getCharge() << "\n";
    vector<float> direction = MathOperator::getDirection(particle->getMomentum());
    int tpchits = particle->getTracks()[0]->getSubdetectorHitNumbers()[6];
    float costheta =  std::abs(std::cos( MathOperator::getAngles(direction)[1]));
    if (costheta > 0.95 )//|| tpchits < 60) 
      {
	streamlog_out(DEBUG) << "no candidate tracks!\n";
	return NULL;
      }
    vector< LCObject * > obj = navigator.getRelatedToObjects(particle);
    vector< float > weights = navigator.getRelatedToWeights(particle);
    MCParticle * winner = NULL;
    float maxweight = 0.50;
    for (unsigned int j = 0; j < obj.size(); j++) 
      {
	if (weights[j] > maxweight) 
	  {
	    winner = dynamic_cast< MCParticle * >(obj[j]);
	    maxweight = weights[j];
	  }
      }
    if (!winner) 
      {
	streamlog_out(DEBUG) << "ERROR: no genparticle!\n";
	return NULL;
      }
    if (winner && abs(winner->getPDG()) == 321) 
      {
	streamlog_out(DEBUG)<<" Kaon test 4:  nkaons "<<std::endl;
	return particle;
      }
    
    return NULL;

  }

  //irles function to get Hadrons from single Reconstructed Particles
  ReconstructedParticle * VertexChargeOperator::__getHadronsCheat( ReconstructedParticle * & particle, int pdg)
  {
    LCRelationNavigator navigator(myRelCollection);
    
    streamlog_out(DEBUG) << "__getHadronsCheat Charge: " << particle->getCharge() << "\n";
    vector<float> direction = MathOperator::getDirection(particle->getMomentum());
    int tpchits = particle->getTracks()[0]->getSubdetectorHitNumbers()[6];
    float costheta =  std::abs(std::cos( MathOperator::getAngles(direction)[1] ));
    if (costheta > 0.95) 
      {
	streamlog_out(DEBUG) << "__getHadronsCheat no candidate tracks!\n";
	return NULL;
      }
    vector< LCObject * > obj = navigator.getRelatedToObjects(particle);
    vector< float > weights = navigator.getRelatedToWeights(particle);
    MCParticle * winner= NULL;
    float maxweight = 0.50;
    for (unsigned int j = 0; j < obj.size(); j++) 
      {
	if (weights[j] > maxweight) 
	  {
	    winner = dynamic_cast< MCParticle * >(obj[j]);
	    maxweight = weights[j];
	  }
      }
    if (!winner) 
      {
	streamlog_out(DEBUG) << "__getHadronsCheat ERROR: no genparticle!\n";
	return NULL;
      }
    if (winner && fabs(winner->getPDG()) == pdg) 
      {
	return particle;
      }
    
    return NULL;

  }
  
  vector< ReconstructedParticle * > VertexChargeOperator::__filterOutCheat(vector< ReconstructedParticle * > particles, int type)
  {
    LCRelationNavigator navigator(myRelCollection);
    vector< ReconstructedParticle * > result;
    for (unsigned int i = 0; i < particles.size(); i++) 
      {
	ReconstructedParticle * particle = particles[i];
	vector< LCObject * > obj = navigator.getRelatedToObjects(particle);
	vector< float > weights = navigator.getRelatedToWeights(particle);
	MCParticle * winner = NULL;
	float maxweight = 0.50;
	for (unsigned int i = 0; i < obj.size(); i++) 
	  {
	    if (weights[i] > maxweight) 
	      {
		winner = dynamic_cast< MCParticle * >(obj[i]);
		maxweight = weights[i];
	      }
	  }
	if (!winner) 
	  {
	    std::cout << "ERROR: no genparticle!\n";
	  }
	if (winner && abs(winner->getPDG()) != type) 
	  {
	    result.push_back(particle);
	  }
      }
    return result;
  }

  bool VertexChargeOperator::__magicBall(float threshold, float seed)
  {
    int input = std::abs(seed) * 1000;
    srand(input);
    float random = (float)(rand()) / RAND_MAX;
    std::cout << "Time: " << input << "\n";
    std::cout << "Random: " << random << "\n";
    return random < threshold;
  }
} /* QQbarProcessor */
