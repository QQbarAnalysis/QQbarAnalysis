#include "BBbarAnalysis.hh"

using namespace lcio ;
using namespace marlin ;
using std::vector;
using std::string;
using std::abs;
using EVENT::Track;
using IMPL::ReconstructedParticleImpl;
using EVENT::ParticleID;
using IMPL::ParticleIDImpl;


namespace QQbarProcessor
{
  BBbarAnalysis:: BBbarAnalysis() {}

  void BBbarAnalysis::Init(std::string _hfilename) 
  { 


    TreeWriter writer;
    _hfile = new TFile( _hfilename.c_str(), "RECREATE", _hfilename.c_str() ) ;
    _hTree = new TTree( "Stats", "tree" );
    writer.InitializeStatsBBbarTree(_hTree, _stats);
    
  }


  vector< MCParticle * > BBbarAnalysis::AnalyseGeneratorBBbar(QQbarMCOperator & opera)
  {
    vector <MCParticle *> genfinalstate;// = opera.GetPairParticles(5);
    for (unsigned int i = 5; i > 0; i--) {
      genfinalstate = opera.GetPairParticles(i);
      if (genfinalstate.size() == 2) break;
    }

    if (genfinalstate.size() == 2) {
      
      MCParticle * mcqqbar = opera.CombineParticles(genfinalstate[0],genfinalstate[1]);

      for (unsigned int i = 0; i < genfinalstate.size(); i++)  {
	MCParticle * mcb = genfinalstate[i];
	_stats._mc_quark_E[i]=mcb->getEnergy();
	_stats._mc_quark_px[i]=mcb->getMomentum()[0];
	_stats._mc_quark_py[i]=mcb->getMomentum()[1];
	_stats._mc_quark_pz[i]=mcb->getMomentum()[2];
	_stats._mc_quark_pdg[i]=mcb->getPDG();
	_stats._mc_quark_charge[i]=mcb->getCharge();
	_stats._mc_quark_m[i]=mcb->getMass();
	_stats._mc_quark_pt[i]=std::sqrt( std::pow(mcb->getMomentum()[0],2) + std::pow(mcb->getMomentum()[1],2) );
      }
      _stats._mc_qqbar_m=mcqqbar->getMass();
      _stats._mc_qqbar_pt=std::sqrt( std::pow(mcqqbar->getMomentum()[0],2) + std::pow(mcqqbar->getMomentum()[1],2) );
    }

    for (unsigned int i = 0; i < genfinalstate.size(); i++) 
      {
	streamlog_out(DEBUG) << "Hard Process Parton Level \n";
 	QQbarTools::PrintParticle(genfinalstate[i]);
      }

    return genfinalstate;
  }

  
  void BBbarAnalysis::AnalyseGeneratorBBbar_PS(QQbarMCOperator & opera)
  {

    vector<PseudoJet> particles;
    JetDefinition jet_def(ee_genkt_algorithm,1.5,1);

    vector <MCParticle *> bbbar_ps = opera.GetBBbarQuarksPS();
    streamlog_out(DEBUG) << "Hard Process + PS Level \n";

    int quark_idx[2];
    quark_idx[0]=-1; //b-quark
    quark_idx[1]=-1; //anti b-quark
    for(int i=0; i<bbbar_ps.size(); i++) {
      if(bbbar_ps.at(i)!=NULL) {
	_stats._mc_quark_ps_n++;
	_stats._mc_quark_ps_E[i]=bbbar_ps.at(i)->getEnergy();
	_stats._mc_quark_ps_px[i]=bbbar_ps.at(i)->getMomentum()[0];
	_stats._mc_quark_ps_py[i]=bbbar_ps.at(i)->getMomentum()[1];
	_stats._mc_quark_ps_pz[i]=bbbar_ps.at(i)->getMomentum()[2];
	_stats._mc_quark_ps_pdg[i]=bbbar_ps.at(i)->getPDG();
	if(bbbar_ps.at(i)->getPDG()==5) quark_idx[0]=i;
        if(bbbar_ps.at(i)->getPDG()==-5) quark_idx[1]=i;    
	_stats._mc_quark_ps_charge[i]=bbbar_ps.at(i)->getCharge();
	_stats._mc_quark_ps_m[i]=bbbar_ps.at(i)->getMass();
	_stats._mc_quark_ps_pt[i]=std::sqrt( std::pow(bbbar_ps.at(i)->getMomentum()[0],2) + std::pow(bbbar_ps.at(i)->getMomentum()[1],2) );

	particles.push_back(PseudoJet(bbbar_ps.at(i)->getMomentum()[0],bbbar_ps.at(i)->getMomentum()[1],bbbar_ps.at(i)->getMomentum()[2],bbbar_ps.at(i)->getEnergy()));

	QQbarTools::PrintParticle(bbbar_ps.at(i));
      } else {
        _stats._mc_quark_ps_n=0;                                                                                                                                                                        
	_stats._mc_quark_ps_E[i]=0;
	_stats._mc_quark_ps_px[i]=0;
	_stats._mc_quark_ps_py[i]=0;
	_stats._mc_quark_ps_pz[i]=0;
	_stats._mc_quark_ps_pdg[i]=0;
	_stats._mc_quark_ps_charge[i]=0;
	_stats._mc_quark_ps_m[i]=0;
	_stats._mc_quark_ps_pt[i]=0;
      }
    }

    if(particles.size()>1) {
      ClusterSequence cs(particles,jet_def);
      const int njets=2;
      
      vector<PseudoJet> jets = sorted_by_E(cs.exclusive_jets(njets));
      double ymerge= cs.exclusive_ymerge(njets);
      double ymerge_max= cs.exclusive_ymerge_max(njets);
      streamlog_out(DEBUG) << "y23 (parton + PS)= "<<ymerge <<std::endl;
      _stats._mc_quark_ps_y23=ymerge;
    

      for(unsigned i=0; i< jets.size(); i++) {
	_stats._mc_quark_ps_jet_E[i]=jets[i].E();
	_stats._mc_quark_ps_jet_px[i]=jets[i].px();
	_stats._mc_quark_ps_jet_py[i]=jets[i].py();
	_stats._mc_quark_ps_jet_pz[i]=jets[i].pz();
	//vector<PseudoJet> constituents = jets[i].constituents();
	//_stats._mc_quark_ps_jet_nparticles[i]=constituents.size();
      }
    }


  }

  void BBbarAnalysis::AnalyseBBbar(LCEvent * evt,
				   bool _boolDBDanalysis,
				   bool _boolkaoncheat,
				   std::string _colName ,
				   std::string _colRelName,
				   std::string _initialJetsColName,
				   std::string _JetsColName ,
				   std::string _JetsRelColName ,
				   std::string _MCColName,
				   std::string _KaonTaggerName
				   )
  {
    LCCollection * mcvtxcol = NULL;
    try
      {
	//mcvtxcol = evt->getCollection(_MCVtxColName);
      }
    catch(DataNotAvailableException &e)
      {
	streamlog_out(DEBUG) << e.what() <<"\n";
      }
    try
      {

        streamlog_out(DEBUG) <<"   ---------------------------------------------------------- Analysis \n";
	//MonteCarlo & parton level Information
	LCCollection * mccol = evt->getCollection(_MCColName);
	
	//reconstruction
	LCCollection * jetcol = evt->getCollection(_JetsColName);
	LCCollection * jetrelcol = evt->getCollection(_JetsRelColName);

        //LCCollection * mcvtxcol = evt->getCollection(_MCVtxColName); 
        LCCollection * pfocol = evt->getCollection(_colName);  
        VertexChargeOperator vtxOperator(evt->getCollection(_colName),evt->getCollection(_colRelName)); 
	vector< RecoJet * > * jets = QQbarTools::getJets(jetcol, jetrelcol);

	ClearVariables();
	//MC bbbar Analysis
	QQbarMCOperator opera(mccol);
	vector < MCParticle * > mcbs = AnalyseGeneratorBBbar(opera);//Hard Process
	//	vector < MCParticle * > mcbs_ps =
	//	ClearVariables(); 

	AnalyseGeneratorBBbar_PS(opera);
	
	std::sort(jets->begin(), jets->end(), QQbarTools::sortByBtag);
	if (jets->size() != 2 ) {
	  _hTree->Fill();
	  ClearVariables();
	  return;
	}

	// get jet reconstruction variables (merging distances)
	if(_boolDBDanalysis==true) {
	  LCCollection * originaljets = evt->getCollection(_initialJetsColName); 
	  _stats._d23 = originaljets->getParameters().getFloatVal("d_{n,n+1}");
	  _stats._d12 = originaljets->getParameters().getFloatVal("d_{n-1,n}");
	  _stats._y23 = originaljets->getParameters().getFloatVal("y_{n,n+1}");
	  _stats._y12 = originaljets->getParameters().getFloatVal("y_{n-1,n}");
	  streamlog_out(DEBUG) << "y23 (reco)= "<<_stats._y23<<"\n";                                                                                  

	} else {
	  //for the IDR we use the jet reconstruction from LCFIPlus, that includes the yth variable calculation
	  PIDHandler pidh(jetcol);     
	  int alid = -1;
	  try { 
	    alid = pidh.getAlgorithmID("yth"); 
	    ReconstructedParticle * jetpart = dynamic_cast< ReconstructedParticle * >(jetcol->getElementAt(0));
	    const ParticleID& pid = pidh.getParticleID(jetpart,alid);
	    vector<float> params = pid.getParameters();
	    _stats._y23 = params[pidh.getParameterIndex(alid,"y23")];
	    _stats._y12 = params[pidh.getParameterIndex(alid,"y12")];
	    streamlog_out(DEBUG) << "y23 (reco)= "<<_stats._y23<<"\n";
	  } catch(UTIL::UnknownAlgorithm &e){ 
	    streamlog_out(DEBUG) << "No algorithm yth!\n"; 
	    streamlog_out(WARNING)<< e.what() << "\n";
	  }
	}

	//get the event shape variables. Needs that we run before the following processors
	//<!-- ========== EventShapes ========================== -->
	//  <processor name="MySphere"/>
	//<processor name="MyThrustReconstruction"/>
	_stats._oblateness = pfocol->getParameters().getFloatVal("Oblateness");
	_stats._aplanarity = pfocol->getParameters().getFloatVal("aplanarity");
	_stats._major_thrust_value = pfocol->getParameters().getFloatVal("majorThrustValue");
	_stats._minor_thrust_value = pfocol->getParameters().getFloatVal("minorThrustValue");
	_stats._principle_thrust_value = pfocol->getParameters().getFloatVal("principleThrustValue");
	std::vector<float> minoraxis;
	pfocol->getParameters().getFloatVals( "minorThrustAxis" , minoraxis) ;
	_stats._minor_thrust_axis[0]=minoraxis[0];
	_stats._minor_thrust_axis[1]=minoraxis[1];
	_stats._minor_thrust_axis[2]=minoraxis[2];
	std::vector<float> majoraxis;
	pfocol->getParameters().getFloatVals( "majorThrustAxis" , majoraxis) ;
	_stats._major_thrust_axis[0]=majoraxis[0];
	_stats._major_thrust_axis[1]=majoraxis[1];
	_stats._major_thrust_axis[2]=majoraxis[2];
	std::vector<float> principleaxis;
	pfocol->getParameters().getFloatVals( "principleThrustAxis" , principleaxis) ;
	_stats._principle_thrust_axis[0]=principleaxis[0];
	_stats._principle_thrust_axis[1]=principleaxis[1];
	_stats._principle_thrust_axis[2]=principleaxis[2];
	
	_stats._sphericity = jetcol->getParameters().getFloatVal("sphericity");
	std::vector<float> sphericitytensor;
	jetcol->getParameters().getFloatVals( "sphericity_tensor_eigenvalues" , sphericitytensor) ;
	_stats._sphericity_tensor[0]=sphericitytensor[0];
	_stats._sphericity_tensor[1]=sphericitytensor[1];
	_stats._sphericity_tensor[2]=sphericitytensor[2];


	//get the pfO object identified as photon with the maximum energy
	ReconstructedParticle * maxenergy_reco_photon=QQbarTools::findPhoton(pfocol);
	if(maxenergy_reco_photon) {
	  vector<float> gdirection = MathOperator::getDirection(maxenergy_reco_photon->getMomentum());
	  _stats._maxenergy_photon_costheta = (std::cos( MathOperator::getAngles(gdirection)[1] ));
	  _stats._maxenergy_photon_E = maxenergy_reco_photon->getEnergy();
	  if(maxenergy_reco_photon->getEnergy()>40)  streamlog_out(DEBUG)<<" Radiative return candidate with Egamma= = "<<maxenergy_reco_photon->getEnergy()<<std::endl;
	}

	//match reco jets with quarks BEFORE radiation
	MatchB(jets, mcbs, mcvtxcol);

	// get pFo + type
	// needs to be done per jet.
	// TODO
	/*
	  for(int ipfo=0; ipfo<pfocol->getNumberOfElements(); ipfo++) {
	  ReconstructedParticle * particle = dynamic_cast< ReconstructedParticle * >(pfocol->getElementAt(ipfo));
	  _stats._pfo_E[ipfo]=particle->getEnergy();
	  _stats._pfo_px[ipfo]=particle->getMomentum()[0];
	  _stats._pfo_py[ipfo]=particle->getMomentum()[1];
	  _stats._pfo_pz[ipfo]=particle->getMomentum()[2];
	  _stats._pfo_m[ipfo]=particle->getMass();
	  _stats._pfo_type[ipfo]=particle->getType();
	  _stats._pfo_n++;

	  }*/

	// Save trackjet, vtx, track, kaon info
	for(int ijet=0; ijet<2; ijet++) {
	  _stats._jet_E[ijet]=jets->at(ijet)->getEnergy();
	  _stats._jet_px[ijet]=jets->at(ijet)->getMomentum()[0];
	  _stats._jet_py[ijet]=jets->at(ijet)->getMomentum()[1];
	  _stats._jet_pz[ijet]=jets->at(ijet)->getMomentum()[2];
	  _stats._jet_m[ijet]=jets->at(ijet)->getMass();
	  _stats._jet_btag[ijet]=jets->at(ijet)->GetBTag();
          _stats._jet_ctag[ijet]=jets->at(ijet)->GetCTag();
	  
	  //Get all secondary vertexes associated to secondary tracks in each jet
	  vector< Vertex * > * vertices = jets->at(ijet)->GetRecoVertices();
	  _stats._jet_nvtx[ijet]=vertices->size();
	  streamlog_out(DEBUG)<<"nvertices = "<<vertices->size()<<std::endl;

	  for( int ivtx=0; ivtx<vertices->size(); ivtx++) {
	    streamlog_out(DEBUG)<<"   ivtx = "<<ivtx<<std::endl;
	    _stats._jet_ntrack[ijet]+=vertices->at(ivtx)->getAssociatedParticle()->getParticles().size();
	    _stats._jet_vtx_isprimary[ijet][ivtx]=vertices->at(ivtx)->isPrimary();
	    _stats._jet_vtx_ntrack[ijet][ivtx]=vertices->at(ivtx)->getAssociatedParticle()->getParticles().size();
	    _stats._jet_vtx_charge[ijet][ivtx]=vertices->at(ivtx)->getAssociatedParticle()->getCharge();


	    int ntrack = vertices->at(ivtx)->getAssociatedParticle()->getParticles().size();
	    streamlog_out(DEBUG)<<"   ntracks = "<<ntrack<<std::endl;

	    for(int itr=0; itr< ntrack; itr++) {
	      streamlog_out(DEBUG)<<"      itr= "<<itr<<std::endl;
	      if(vertices->at(ivtx)->getAssociatedParticle()->getParticles().at(itr)==NULL) continue;
      
	      ReconstructedParticle * found_track_particle = vertices->at(ivtx)->getAssociatedParticle()->getParticles().at(itr);

	      _stats._jet_track_charge[ijet][ivtx][itr]=found_track_particle->getCharge();
	      _stats._jet_track_E[ijet][ivtx][itr]=found_track_particle->getEnergy();
	      _stats._jet_track_px[ijet][ivtx][itr]=found_track_particle->getMomentum()[0];
	      _stats._jet_track_py[ijet][ivtx][itr]=found_track_particle->getMomentum()[1];
	      _stats._jet_track_pz[ijet][ivtx][itr]=found_track_particle->getMomentum()[2];
	      _stats._jet_track_p[ijet][ivtx][itr]=MathOperator::getModule(found_track_particle->getMomentum());
	      _stats._jet_track_charge[ijet][ivtx][itr]=found_track_particle->getCharge();

	      streamlog_out(DEBUG)<<"      Tracks Test  --  "<<ivtx<<" "<<itr<<" "<<found_track_particle->getTracks().size()<<" "<<found_track_particle->getEnergy()<< " " <<found_track_particle->getTracks()[0]->getZ0()<<" "<<found_track_particle->getCharge()<<"  dEdx: "<< found_track_particle->getTracks()[0]->getdEdx()*1e6<<" pdg: "<<vtxOperator.getPDGtrack(found_track_particle) <<std::endl;

	      _stats._jet_track_z0[ijet][ivtx][itr]=found_track_particle->getTracks()[0]->getZ0();
	      _stats._jet_track_d0[ijet][ivtx][itr]=found_track_particle->getTracks()[0]->getD0();
	      _stats._jet_track_phi[ijet][ivtx][itr]=found_track_particle->getTracks()[0]->getPhi();


	      _stats._jet_track_iskaon[ijet][ivtx][itr]=0;   
	      _stats._jet_track_iskaoncheat[ijet][ivtx][itr]=0; 

	      _stats._jet_track_dedx[ijet][ivtx][itr]=found_track_particle->getTracks()[0]->getdEdx()*1e6;
	      _stats._jet_track_pdg[ijet][ivtx][itr]=vtxOperator.getPDGtrack(found_track_particle);


	      // identified kaons
	      if( _boolkaoncheat==false && vtxOperator.isKaon(found_track_particle)==true) _stats._jet_track_iskaon[ijet][ivtx][itr]=1;   
	      if( vtxOperator.isKaonCheat(found_track_particle)==true)  _stats._jet_track_iskaoncheat[ijet][ivtx][itr]=1;   
	      
	    }//itr
	  }//vitx


	}//ijet
	_hTree->Fill();
	delete jets;
      }
    catch(DataNotAvailableException &e)
      {
	std::cout << e.what() <<"\n";
      }
    
  }


  void BBbarAnalysis::MatchB(vector<RecoJet*> * bjets, vector< MCParticle * > & mcbs, LCCollection * mcvtxcol)
  {
    float charge = 0.0;
    float angle = 4.0;
    int bgenntracks = 0;
    int bbargenntracks = 0;
    _stats._MCBOscillation = 0;
    _stats._MCBBarOscillation = 0;
    if (mcvtxcol && mcvtxcol->getNumberOfElements() > 0) 
      {
	for (int i = 0; i < mcvtxcol->getNumberOfElements(); i++) 
	  {
	    Vertex * vertex = dynamic_cast< Vertex * >(mcvtxcol->getElementAt(i));
	    if (vertex->getParameters()[1] > 0) 
	      {
		bgenntracks += vertex->getAssociatedParticle()->getParticles().size();
	      }
	    if (vertex->getParameters()[1] < 0) 
	      {
		bbargenntracks += vertex->getAssociatedParticle()->getParticles().size();
	      }
	  }
	_stats._MCBBarOscillation = mcvtxcol->getParameters().getIntVal("BBarOscillation");
	_stats._MCBOscillation = mcvtxcol->getParameters().getIntVal("BOscillation");
      }
    for (unsigned int i = 0; i < mcbs.size(); i++) 
      {
	MCParticle * mcb = mcbs[i];
	float angleCurrent =  MathOperator::getAngle(mcb->getMomentum(), bjets->at(0)->getMomentum());
	if (angleCurrent < angle) 
	  { 
	    angle = angleCurrent;
	    charge = mcb->getCharge();
	    bjets->at(0)->__SetMCCharge(charge);
	  }
      }
    streamlog_out(DEBUG) << "Truth Angle: " << angle << " charge: " << charge << "\n";
    //    _stats._B1truthAngle = angle;
    bjets->at(1)->__SetMCCharge(-charge);

    if( _stats._mc_quark_charge[0]*charge > 0 ) _stats._mc_matching=1;
    if( _stats._mc_quark_charge[0]*charge < 0 ) _stats._mc_matching=2;

    if ( bjets->at(0)->__GetMCCharge() < 0) 
      {
	bjets->at(0)->__SetMCNtracks(bgenntracks);
	bjets->at(0)->__SetMCOscillation(_stats._MCBOscillation);
	bjets->at(1)->__SetMCNtracks(bbargenntracks);
	bjets->at(1)->__SetMCOscillation(_stats._MCBBarOscillation);
      }
    else 
      {
	bjets->at(0)->__SetMCNtracks(bbargenntracks);
	bjets->at(0)->__SetMCOscillation(_stats._MCBBarOscillation);
	bjets->at(1)->__SetMCNtracks(bgenntracks);
	bjets->at(1)->__SetMCOscillation(_stats._MCBOscillation);
      }
  }

  void BBbarAnalysis::ClearVariables()
  {
    _stats.Clear();
  }

  void BBbarAnalysis::End()
  {   
    _hfile->Write();
    _hfile->Close();
  }

}
