
#include "RecoJet.hh"
using EVENT::ReconstructedParticle;
using IMPL::ReconstructedParticleImpl;
using std::vector;
namespace QQbarProcessor
{
  RecoJet::RecoJet (ReconstructedParticle * rawjet, float btag,float ctag, int number)
  //: IMPL::ReconstructedParticleImpl(rawjet)
  {
    myBTag = btag;
    myCTag = ctag;
    myNumber = number;
    myMCPDG = 0;
    myRecoVertices = NULL;
    myRawRecoJet = rawjet;
    setMomentum(rawjet->getMomentum());

    setMass(rawjet->getMass());
    setEnergy(rawjet->getEnergy());
    _particles.reserve(rawjet->getParticles().size());
    _particles.insert(_particles.begin(),rawjet->getParticles().begin(),rawjet->getParticles().end());

  }
  RecoJet::RecoJet ()
  {
    myRecoVertices = NULL;
    myMCPDG = 0;
		
  }
  void RecoJet::SetRecoVertices(std::vector<  EVENT::Vertex * > * vertices)
  {
    myRecoVertices = vertices;
  }
  std::vector<  EVENT::Vertex * > * RecoJet::GetRecoVertices()
  {
    return myRecoVertices;
  }
  void RecoJet::SetBTag(float value)
  {
    myBTag = value;
  }
  void RecoJet::SetCTag(float value)
  {
    myCTag = value;
  }
  const float RecoJet::GetBTag() const
  {
    return myBTag;
  }
  const float RecoJet::GetCTag() const
  {
    return myCTag;
  }
  int RecoJet::GetNumberOfVertices()
  {
    if (myRecoVertices) 
      {
	return myRecoVertices->size();
      }
    return myNumber;
  }
  int RecoJet::GetNumberOfVertexParticles()
  {
    int sum = -1;
    if (myRecoVertices) 
      {
	sum = 0;
	for (unsigned int i = 0; i < myRecoVertices->size(); i++) 
	  {
	    sum += myRecoVertices->at(i)->getAssociatedParticle()->getParticles().size();
	  }
      }
    return sum;
  }
  ReconstructedParticle * RecoJet::GetRawRecoJet()
  {
    return myRawRecoJet;
  }
  float RecoJet::GetCostheta()
  {
    float costheta1 =  -2.0;
    vector<float> d1;
    /*if (myRecoVertices && myRecoVertices->size() > 0) 
      {
      double * pos = MathOperator::toDoubleArray(myRecoVertices->at(0)->getPosition(),3);
      d1 = MathOperator::getDirection(pos);
      delete pos;
      }
      else*/ 
    {
      d1 = MathOperator::getDirection(getMomentum());
    }
    costheta1 =  std::cos( MathOperator::getAngles(d1)[1] );
    return costheta1;
  }
  float RecoJet::GetHadronCharge(bool weight)
  {
    float charge = -5.0;
    if (myRecoVertices && myRecoVertices->size() > 0) 
      {
	charge = 0.0;
	for (unsigned int i = 0; i < myRecoVertices->size(); i++) 
	  {
	    charge += myRecoVertices->at(i)->getAssociatedParticle()->getCharge();
	  }
	if (weight) 
	  {
	    charge = 0.0;
	    for (unsigned int i = 0; i < myRecoVertices->size(); i++) 
	      {
		ReconstructedParticle * vtx = myRecoVertices->at(i)->getAssociatedParticle();
		for (unsigned int j = 0; j < vtx->getParticles().size(); j++) 
		  {
		    float p = MathOperator::getModule(vtx->getParticles()[j]->getMomentum());
		    charge += vtx->getParticles()[j]->getCharge() * p;
		  }
	      }
	  }
      }
    return charge;
  }
  float RecoJet::GetHadronMomentum()
  {
    float momentum = -1.0;
    if (myRecoVertices) 
      {
	momentum = 0.0;
	for (unsigned int i = 0; i < myRecoVertices->size(); i++)
	  {
	    momentum += MathOperator::getModule(myRecoVertices->at(i)->getAssociatedParticle()->getMomentum()); // CRUNCH!!!
	  }
      }
    return momentum;
  }
  float RecoJet::GetMinHadronDistance()
  {
    float mindistance = 1000.;
    if (myRecoVertices && myRecoVertices->size() > 0) 
      {
	for (unsigned int i = 0; i < myRecoVertices->size(); i++) 
	  {
	    float distance = MathOperator::getModule(myRecoVertices->at(i)->getPosition()); // CRUNCH!!!
	    if (distance < mindistance) 
	      {
		mindistance = distance;
	      }
	  }
      }
    return mindistance;
  }
  float RecoJet::GetMaxHadronDistance()
  {
    float maxdistance = 0.;
    if (myRecoVertices && myRecoVertices->size() > 0) 
      {
	for ( unsigned int i = 0; i < myRecoVertices->size(); i++) 
	  {
	    float distance = MathOperator::getModule(myRecoVertices->at(i)->getPosition()); // CRUNCH!!!
	    if (distance > maxdistance) 
	      {
		maxdistance = distance;
	      }
	  }
      }
    return maxdistance;
  }
  const float RecoJet::__GetMCCharge() const
  {
    return myMCCharge;
  }
  void RecoJet::__SetMCCharge( float charge)
  {
    myMCCharge = charge;
  }
  const int RecoJet::__GetMCNtracks() const
  {
    return myMCNtracks;
  }
  void RecoJet::__SetMCNtracks(int n)
  {
    myMCNtracks = n;
  }
  float RecoJet::GetHadronMass()
  {
    float mass = -1.0;
    if (myRecoVertices) 
      {
	mass = 0.0;
	for ( unsigned int i = 0; i < myRecoVertices->size(); i++) 
	  {
	    mass += myRecoVertices->at(i)->getAssociatedParticle()->getMass();
	  }
      }
    return mass;
  }
	
  int RecoJet::GetMCPDG()
  {
    return myMCPDG;
  }
  void RecoJet::SetMCPDG(int pdg)
  {
    myMCPDG = pdg;
  }
  const int RecoJet::__GetMCOscillation() const
  {
    return myMCOscillation;
  }
  void RecoJet::__SetMCOscillation(int n)
  {
    myMCOscillation = n;
  }
  JetCharge & RecoJet::GetComputedCharge()
  {
    return myComputedCharge;
  }

}
