#include "ClusteringOperator.hh"
using std::string;
using std::vector;
using EVENT::ReconstructedParticle;

namespace QQbarProcessor 
{
  ClusteringOperator:: ClusteringOperator() {}
  float ClusteringOperator::ClusterizeJet(RecoJet * jet)
  {
    float Evis = jet->getEnergy();
    vector<ReconstructedParticle * > particles;
    particles.reserve(jet->getParticles().size());
    particles.insert(particles.begin(), jet->getParticles().begin(), jet->getParticles().end());//v= vector(jet->getParticles());
    std::sort(particles.begin(), particles.end(), sortByP);
    float ymean = 0.0;
    int number = 0;
    for (unsigned int i = 0; i < particles.size(); i++) 
      {
	for (unsigned int j = 0; j < i; j++) 
	  {
	    float y = ComputeY( particles[i],particles[j], Evis);
	    //std::cout << "Y: " << y*1000 << "\n";
	    ymean += y;
	    number++;
	  }
      }
    ymean /= number;
    std::cout << "Ye-3: " << ymean*1000 << "\n";
    return ymean;
  }
  float ClusteringOperator::ComputeY( ReconstructedParticle * p1,  ReconstructedParticle * p2, float Evis)
  {
    //float momentum1 = MathOperator::getModule(p1->getMomentum());
    //float momentum2 = MathOperator::getModule(p2->getMomentum());
    float E1 = p1->getEnergy();
    float E2 = p2->getEnergy();
    float Emin = (E1 < E2)? E1 : E2;
    float costheta = std::cos(MathOperator::getAngleBtw(p1->getMomentum(), p2->getMomentum()));
    float y = 2*Emin*Emin * (1 - costheta) / Evis / Evis;
    return costheta;
  }
  bool sortByP(EVENT::ReconstructedParticle * p1,  EVENT::ReconstructedParticle * p2) 
  {
    float momentum1 = MathOperator::getModule(p1->getMomentum());
    float momentum2 = MathOperator::getModule(p2->getMomentum());
    return momentum1 < momentum2; 
  }
} /* TTBarAnalysis */
