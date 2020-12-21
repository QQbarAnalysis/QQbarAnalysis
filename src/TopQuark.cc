#include "TopQuark.hh"
using EVENT::ReconstructedParticle;
using IMPL::ReconstructedParticleImpl;
namespace QQbarProcessor 
{
  TopQuark::TopQuark(RecoJet * b, ReconstructedParticle * w)
  {
    myResultTVCM = 0;
    myB = b;
    myW = w;
    addParticle (b);
    addParticle (w);
    //float mB = b->getMass();
    //float mW = w->getMass();
    //float EB = b->getEnergy();
    //float EW = w->getEnergy();
    //const double * pB = b->getMomentum();
    //const double * pW = w->getMomentum();
    for (int i = 0; i < 3; i++) 
      {
	_momentum[i] = b->getMomentum()[i] + w->getMomentum()[i];
      }
    double pT = MathOperator::getModule(_momentum);
    _energy = b->getEnergy() + w->getEnergy();
    float charge = b->GetHadronCharge();
    _charge = (abs(charge) > 0.1)? charge / abs(charge) : 0.0;
    float topbeta = pT / _energy;
    float topgamma = 1.0 / std::sqrt(1.0- topbeta * topbeta);
    myRecoVertices = b->GetRecoVertices();
    myBTag = b->GetBTag();
    myCTag = b->GetCTag();
    //_mass = std::sqrt(mB*mB + mW*mW +2.0*(EB*EW - pB[0]*pW[0] - pB[1]*pW[1] - pB[2]*pW[2]));
    //_mass = std::sqrt(mB*mB + mW*mW +2.0*(EB*EW - pB[0]*pW[0] - pB[1]*pW[1] - pB[2]*pW[2]));
    _mass = std::sqrt(_energy * _energy - _momentum[0] * _momentum[0] - _momentum[1]*_momentum[1] - _momentum[2] * _momentum[2] );
    std::cout << "Top charge: " << charge << " p: " << pT << " m: " << _mass <<"\n";
  }
  TopQuark::TopQuark(RecoJet * b)
  {
    myResultTVCM = 0;
    myB = b;
    addParticle (b);
    for (int i = 0; i < 3; i++) 
      {
	_momentum[i] = b->getMomentum()[i];
      }
    float charge = b->GetHadronCharge();
    _charge = (abs(charge) > 0.1)? charge / abs(charge) : 0.0;
    myRecoVertices = b->GetRecoVertices();
    myBTag = b->GetBTag();
    myCTag = b->GetCTag();
    _mass=  b->getMass();
    double pT = MathOperator::getModule(_momentum);
    std::cout << "Top charge: " << charge << " p: " << pT << " m: " << _mass <<"\n";
  }
  RecoJet * TopQuark::GetB()
  {
    return myB;
  }
  ReconstructedParticle * TopQuark::GetW()
  {
    return myW;
  }
  float TopQuark::getMass()
  {
    return _mass;
  }
  bool IsHadronic();
  int TopQuark::GetResultTVCM()
  {
    return myResultTVCM;
  }
  void TopQuark::SetResultTVCM(int used)
  {
    myResultTVCM = used;
  }
	
} /* TTBarAnalisys */
