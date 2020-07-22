#include "QQbarTools.hh"
using std::vector;
using std::string;

namespace QQbarProcessor 
{

  ReconstructedParticle * QQbarTools::findPhoton(LCCollection * pfocol){

    int pfonumber = pfocol->getNumberOfElements();
    ReconstructedParticle * winner = NULL;
    float maxenergy = 0.0;
    for (int i = 0; i < pfonumber; i++) 
      {
	ReconstructedParticle * particle = dynamic_cast< ReconstructedParticle * >(pfocol->getElementAt(i));
	if ((particle->getType() == 22 || particle->getType() ==2112) && particle->getEnergy() > maxenergy) 
	  {
	    winner = particle;
	    maxenergy = particle->getEnergy();
	  }
      }
    // if (winner) 
    //  {
    //	vector<float> gdirection = MathOperator::getDirection(winner->getMomentum());
    //	_stats._maxPhotonCostheta = (std::cos( MathOperator::getAngles(gdirection)[1] ));
    //	_stats._maxPhotonEnergy = winner->getEnergy();
    //  }
    return winner;
  }

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


  string QQbarTools::intToStr(int * number)
  {
    std::stringstream ss;
    if (number) 
      {
	ss << *number;
      }
    else 
      {
	ss << "NAN";
      }
    string str = ss.str();
    return str;
  }

  float QQbarTools::getMass(std::vector< EVENT::ReconstructedParticle * > & hemisphere)
  {
    float mass = 0.0;
    float energy  = 0.0;
    float momentum[3] = { 0., 0., 0.};
    for (unsigned int i = 0; i < hemisphere.size(); i++) 
      {
	energy += hemisphere[i]->getEnergy();
	momentum[0] += hemisphere[i]->getMomentum()[0];
	momentum[1] += hemisphere[i]->getMomentum()[1];
	momentum[2] += hemisphere[i]->getMomentum()[2];
      }
    mass = std::sqrt(energy * energy - momentum[0] * momentum[0] - momentum[1]*momentum[1] - momentum[2] * momentum[2] );
		
    return mass;
  }

  vector<float> QQbarTools::getThrust(vector<float> & thrust, LCCollection * pfos)
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
  }

  vector<float> QQbarTools::getZZ(LCCollection * fourjetcol)
  {
    if (!fourjetcol || fourjetcol->getNumberOfElements() < 4) 
      {
	vector<float> result;
	result.push_back(0);
	result.push_back(0);
	return result;
      }

    int njets = fourjetcol->getNumberOfElements();

    vector<ReconstructedParticle * > jets;
    vector<float> masses;
    float average = 0.0;
    for (unsigned int i = 0; i < njets; i++) 
      {
	ReconstructedParticle * jetpart = dynamic_cast< ReconstructedParticle * >(fourjetcol->getElementAt(i));
	jets.push_back(jetpart);
	masses.push_back(jetpart->getMass());
	//average += std::sqrt(std::pow(jetpart->getEnergy(),2) -std::pow( MathOperator::getModule(jetpart->getMomentum()),2));
	//streamlog_out(DEBUG) << "m_" << i << ": " << std::sqrt(std::pow(jetpart->getEnergy(),2) -std::pow( MathOperator::getModule(jetpart->getMomentum()),2)) << "\n";
      }
    //    std::sort(jets.begin(), jets.end(), sortByEnergy);

    int n = 0;
    vector< vector<float> > differences;
    /*vector<ReconstructedParticle * > jetsZ1;
      jetsZ1.push_back(jets[0]);
      jetsZ1.push_back(jets[1]);
      vector<ReconstructedParticle * > jetsZ2;
      jetsZ2.push_back(jets[2]);
      jetsZ2.push_back(jets[3]);
      float mass1 = getMass(jetsZ1);
      float mass2 = getMass(jetsZ2);
      vector<float> pair1;
      pair1.push_back(mass1);
      pair1.push_back(mass2);
      differences.push_back(pair1);*/

    vector<ReconstructedParticle * > jetsZ3;
    jetsZ3.push_back(jets[0]);
    jetsZ3.push_back(jets[2]);
    vector<ReconstructedParticle * > jetsZ4;
    jetsZ4.push_back(jets[1]);
    jetsZ4.push_back(jets[3]);
    float mass3 = getMass(jetsZ3);
    float mass4 = getMass(jetsZ4);
    vector<float> pair2;
    pair2.push_back(mass3);
    pair2.push_back(mass4);
    differences.push_back(pair2);
		
    vector<ReconstructedParticle * > jetsZ5;
    jetsZ5.push_back(jets[0]);
    jetsZ5.push_back(jets[3]);
    vector<ReconstructedParticle * > jetsZ6;
    jetsZ6.push_back(jets[1]);
    jetsZ6.push_back(jets[2]);
    float mass5 = getMass(jetsZ5);
    float mass6 = getMass(jetsZ6);
    vector<float> pair3;
    pair3.push_back(mass5);
    pair3.push_back(mass6);
    differences.push_back(pair3);
		
    streamlog_out(DEBUG) << "Masses: " //<< mass1 << " & " << mass2 << "; "
			 << mass3 << " & " << mass4 << "; "
			 << mass5 << " & " << mass6 << ";\n";
    float mindiff = 1000.;
    int chosen = -1;
    for (unsigned int i = 0; i < differences.size(); i++) 
      {
	float diff = abs(differences[i][0] - differences[i][1]);
	if (diff < mindiff) 
	  {
	    mindiff = diff;
	    chosen = i;
	  }
      }
    //    _stats._ZZMass1 = differences[chosen][0];
    //_stats._ZZMass2 = differences[chosen][1];

    vector<float> result;
    result.push_back(differences[chosen][0]);
    result.push_back(differences[chosen][1]);
    return result;

    /*for (unsigned int i = 1; i < njets; i++) 
      {
      for (unsigned int j = 0; j < i; j++) 
      {
      float ei = jets[i]->getEnergy();
      float ej = jets[j]->getEnergy();
      float momentum = 0.;
      for (unsigned int k = 0; k < 3; k++) 
      {
      momentum+= jets[i]->getMomentum()[k]*jets[j]->getMomentum()[k];
      }
      float mass = std::sqrt(ei*ej - momentum);
      average += mass;
      massesZ.push_back(mass);
      n++;
      streamlog_out(DEBUG) << "Z_" << i << "|" << j << ": " << mass << "\n";
      }
      }
      float deviation = 0.0;
      for (unsigned int i = 0; i < masses.size(); i++) 
      {
      deviation += std::pow(average / n - massesZ[i],2);
      }
      _stats._bbbar4JetMass = average / n;//average / n;*/

  }

  float QQbarTools::getChargeBalance(RecoJet * jet)
  {
    int nparticles = jet->getParticles().size();
    float e_c = 0.0;
    float e = 0.0;
    for (unsigned int i = 0; i < nparticles; i++) 
      {
	ReconstructedParticle * particle = jet->getParticles()[i];
	if (std::abs(particle->getCharge()) > 0.0) 
	  {
	    e_c += particle->getEnergy();
	  }
	e += particle->getEnergy();
      }
    return e_c / e;
  }

  std::vector< RecoJet * > * QQbarTools::getBTagJets(std::vector< RecoJet * > * alljets, std::vector< RecoJet * > * wjets)
  {
    vector< RecoJet * > * result = new vector< RecoJet * >();
    if (!wjets) 
      {
        streamlog_out(DEBUG) << "Wjets are NULL!\n";
        return result;
      }
    if (alljets->size() < 4) 
      {
        return result;
      }
    //vector<RecoJet>
    streamlog_out(DEBUG) << "Before sorting:\n";
    for (unsigned int i = 0; i < alljets->size(); i++) 
      {
        RecoJet * jet = alljets->at(i);
        streamlog_out(DEBUG) << "\tB tag: " << jet->GetBTag()  << "\n";
        /*if (jet->GetBTag() > _lowBTagCutparameter) 
          {
          result->push_back(jet);
          }
          else 
          {
          wjets->push_back(jet);
          }*/
      }
    std::sort(alljets->begin(), alljets->end(), sortByBtag);
    streamlog_out(DEBUG) << "After sorting:\n";
    for (unsigned int i = 0; i < alljets->size(); i++) 
      {
        RecoJet * jet = alljets->at(i);
        streamlog_out(DEBUG) << "\tB tag: " << jet->GetBTag()  << "\n";

      }
    result->push_back(alljets->at(0));
    result->push_back(alljets->at(1));
    for (unsigned int i = 2; i < alljets->size(); i++) 
      {
        wjets->push_back(alljets->at(i));
      }
    return result;
  }

    

}


