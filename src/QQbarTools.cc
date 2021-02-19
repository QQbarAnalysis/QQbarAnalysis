#include "QQbarTools.hh"
using std::vector;
using std::string;

namespace QQbarProcessor 
{

  vector< RecoJet * > * QQbarTools::getJets(LCCollection * jetcol, LCCollection *jetrelcol)
  {
    int jetnumber = jetcol->getNumberOfElements();
    vector< RecoJet * > * result = new vector< RecoJet * >();
    LCRelationNavigator navigator(jetrelcol);
    PIDHandler pidh(jetcol);
    int alid = -1;
    try
      {
	alid = pidh.getAlgorithmID("vtxrec");
      }
    catch(UTIL::UnknownAlgorithm &e)
      {
	streamlog_out(DEBUG) << "No algorithm vtxrec!\n";
	alid = -1;
      }
    if (alid < 0) 
      {
	try
	  {
	    alid = pidh.getAlgorithmID("lcfiplus");
	  }
	catch(UTIL::UnknownAlgorithm &e)
	  {
	    streamlog_out(DEBUG) << "No algorithm lcfiplus!\n";
	    alid = -1;
	  }
			
      }
    streamlog_out(DEBUG) << "Algorithm id: " << jetnumber << "\n";
    for (int j = 0; j < jetnumber; j++) 
      {
	ReconstructedParticle * jetpart = dynamic_cast< ReconstructedParticle * >(jetcol->getElementAt(j));
	vector< Vertex * > * vertices = convert(navigator.getRelatedToObjects(jetpart));
	const vector< ReconstructedParticle * > components = jetpart->getParticles();
	int nvtx = vertices->size();
	float btag = 0.0;
	float ctag = 0.0;
	if (alid > -1) 
	  {
	    const ParticleID& pid = pidh.getParticleID(jetpart,alid);
	    vector<float> params = pid.getParameters();
	    btag = params[pidh.getParameterIndex(alid,"BTag")];
	    ctag = params[pidh.getParameterIndex(alid,"CTag")];
	  }
	RecoJet * jet = new RecoJet(jetpart, btag, ctag, nvtx);
	jet->SetRecoVertices(vertices);
	PrintJet(jet);
	result->push_back(jet);
      }
    return result;
		
  }

  vector< Vertex * > * QQbarTools::convert(const std::vector< LCObject * > & objs)
  {
    std::vector< Vertex * > * result = new std::vector< Vertex * >();
    for (unsigned int i = 0; i < objs.size(); i++) 
      {
	result->push_back(dynamic_cast< Vertex * >(objs[i]));
      }
    return result;
  }

  void QQbarTools::PrintJet(RecoJet * jet)
  {
    streamlog_out(DEBUG) << "Jet E: " << jet->getEnergy()
			 << " m: " << jet->getMass()
			 << " btag: " << jet->GetBTag()
			 << " costheta: " << jet->GetCostheta()
			 << " p_B: " << jet->GetHadronMomentum()
			 << " ntracks: " << jet->GetNumberOfVertexParticles()
			 << "\n";
  }

  void QQbarTools::PrintParticle(ReconstructedParticle * jet)
  {
    streamlog_out(DEBUG) << "E: " << jet->getEnergy()
			 <<" m: " << jet->getMass()
			 <<" PDG: " << jet->getType()
			 << "\n";
  }

  void QQbarTools::PrintParticle(MCParticle * jet)
  {
    streamlog_out(DEBUG) << "E: " << jet->getEnergy()
			 <<" m: " << jet->getMass()
			 <<" q: " << jet->getCharge()
			 <<" PDG: " << jet->getPDG()
			 << "\n";
  }

  void QQbarTools::PrintJets(std::vector< RecoJet * > *jets)
  {
    for (unsigned int i = 0; i < jets->size(); i++) 
      {
	PrintJet(jets->at(i));
      }
  }


  /*  vector<float> QQbarTools::getThrust(vector<float> & thrust, LCCollection * pfos)
  {
    streamlog_out(DEBUG) << "Size: " << thrust.size() << "\n";
    double taxis[3];
    taxis[0] = thrust[0]; taxis[1] = thrust[1]; taxis[2] = thrust[2];
    vector<float> direction = MathOperator::getDirection(thrust);
    float axisAngle = MathOperator::getAngles(direction)[1];
    streamlog_out(DEBUG) << "THRUST COS0: " << std::cos(axisAngle) << "\n";
    int nparticles = pfos->getNumberOfElements();
    int counter = 0;
    vector< ReconstructedParticle * > jetPositive;
    vector< ReconstructedParticle * > jetNegative;
    for (unsigned int i = 0; i < nparticles; i++) 
      {
	ReconstructedParticle * particle = dynamic_cast< ReconstructedParticle * >(pfos->getElementAt(i));
	float angle = MathOperator::getAngleBtw(taxis, particle->getMomentum());
	//streamlog_out(DEBUG) << "Angle: " << angle << "\n";
	if (angle > 3.1416/2) 
	  {
	    jetPositive.push_back(particle);
	    counter++;
	  }
	else 
	  {
	    jetNegative.push_back(particle);
	  }
      }
    streamlog_out(DEBUG) << "In positive direction " << counter << " particles, in negative - " << nparticles - counter << "\n";
    //_stats._ZZMass1 = getMass(jetPositive);
    //_stats._ZZMass2 = getMass(jetNegative);
    vector<float> masses;
    masses.push_back(getMass(jetPositive));
    masses.push_back(getMass(jetNegative));

    streamlog_out(DEBUG) << "Mass_+: " << masses.at(0) << " Mass_-: " << masses.at(1) << "\n";
    }*/


}


