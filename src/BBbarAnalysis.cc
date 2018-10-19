#include "BBbarAnalysis.hh"

using namespace lcio ;
//using namespace marlin ;
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

    vector <MCParticle *> bbbar_ps = opera.GetBBbarQuarksPS();


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


    for(int i=0; i<bbbar_ps.size(); i++) {
      _stats._mc_quark_ps_n++;
      if(bbbar_ps.at(i) != NULL)  {
	_stats._mc_quark_ps_E[i]=bbbar_ps.at(i)->getEnergy();
	_stats._mc_quark_ps_px[i]=bbbar_ps.at(i)->getMomentum()[i];
	_stats._mc_quark_ps_py[i]=bbbar_ps.at(i)->getMomentum()[1];
	_stats._mc_quark_ps_pz[i]=bbbar_ps.at(i)->getMomentum()[2];
	_stats._mc_quark_ps_pdg[i]=bbbar_ps.at(i)->getPDG();
	_stats._mc_quark_ps_charge[i]=bbbar_ps.at(i)->getCharge();
	_stats._mc_quark_ps_m[i]=bbbar_ps.at(i)->getMass();
	_stats._mc_quark_ps_pt[i]=std::sqrt( std::pow(bbbar_ps.at(i)->getMomentum()[i],2) + std::pow(bbbar_ps.at(i)->getMomentum()[1],2) );
      } else {
	_stats._mc_quark_ps_E[i]=0.;
	_stats._mc_quark_ps_px[i]=0.;
	_stats._mc_quark_ps_py[i]=0.;
	_stats._mc_quark_ps_pz[i]=0.;
	_stats._mc_quark_ps_pdg[i]=0.;
	_stats._mc_quark_ps_charge[i]=0.;
	_stats._mc_quark_ps_m[i]=0.;
	_stats._mc_quark_ps_pt[i]=0.;
      }
    }
        
    for (unsigned int i = 0; i < genfinalstate.size(); i++) 
      {
 	QQbarTools::PrintParticle(genfinalstate[i]);
      }

    return genfinalstate;
  }

  void BBbarAnalysis::AnalyseBBbar(LCEvent * evt, 
				    std::string _colName ,
				    std::string _JetsColName ,
				    std::string _JetsRelColName ,
				    std::string _MCColName ,
				    std::string _colRelName  ) 
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
	LCCollection * jetcol = evt->getCollection(_JetsColName);
	LCCollection * jetrelcol = evt->getCollection(_JetsRelColName);
	LCCollection * mccol = evt->getCollection(_MCColName);
	//LCCollection * mcvtxcol = evt->getCollection(_MCVtxColName);
	LCCollection * pfocol = evt->getCollection(_colName);
	QQbarMCOperator opera(mccol);
	vector < MCParticle * > mcbs = AnalyseGeneratorBBbar(opera);
	VertexChargeOperator vtxOperator(evt->getCollection(_colName),evt->getCollection(_colRelName));
	vector< RecoJet * > * jets = QQbarTools::getJets(jetcol, jetrelcol);

	std::sort(jets->begin(), jets->end(), QQbarTools::sortByBtag);

	if (jets->size() != 2 ) {
	  _hTree->Fill();
	  ClearVariables();
	  return;
	}

	LCCollection * satorujets = evt->getCollection("RefinedJets");
	_stats._y23 = satorujets->getParameters().getFloatVal("YPlus");
	_stats._y12 = satorujets->getParameters().getFloatVal("YMinus");

	ReconstructedParticle * maxenergy_reco_photon=QQbarTools::findPhoton(pfocol);
	if(maxenergy_reco_photon) {
	  vector<float> gdirection = MathOperator::getDirection(maxenergy_reco_photon->getMomentum());
	  _stats._maxenergy_photon_costheta = (std::cos( MathOperator::getAngles(gdirection)[1] ));
	  _stats._maxenergy_photon_E = maxenergy_reco_photon->getEnergy();
	}

	MatchB(jets, mcbs, mcvtxcol);

	for(int ijet=0; ijet<2; ijet++) {
	  _stats._jet_E[ijet]=jets->at(ijet)->getEnergy();
	  _stats._jet_px[ijet]=jets->at(ijet)->getMomentum()[0];
	  _stats._jet_py[ijet]=jets->at(ijet)->getMomentum()[1];
	  _stats._jet_pz[ijet]=jets->at(ijet)->getMomentum()[2];
	  _stats._jet_m[ijet]=jets->at(ijet)->getMass();
	  _stats._jet_btag[ijet]=jets->at(ijet)->GetBTag();
	
	  vector< Vertex * > * vertices = jets->at(ijet)->GetRecoVertices();
	  _stats._jet_nvtx[ijet]=vertices->size();
	  streamlog_out(DEBUG)<<"nvertices = "<<vertices->size()<<std::endl;

	  for( int ivtx=0; ivtx<vertices->size(); ivtx++) {
	    streamlog_out(DEBUG)<<"nvertices = "<<vertices->size()<<" "<<ivtx<<std::endl;
	    _stats._jet_ntrack[ijet]+=vertices->at(ivtx)->getAssociatedParticle()->getParticles().size();
	    _stats._jet_vtx_isprimary[ijet][ivtx]=vertices->at(ivtx)->isPrimary();
	    _stats._jet_vtx_ntrack[ijet][ivtx]=vertices->at(ivtx)->getAssociatedParticle()->getParticles().size();
	    _stats._jet_vtx_charge[ijet][ivtx]=vertices->at(ivtx)->getAssociatedParticle()->getCharge();

	    streamlog_out(DEBUG)<<"ntracks-- = "<<std::endl;

	    int ntrack = vertices->at(ivtx)->getAssociatedParticle()->getParticles().size();
	    streamlog_out(DEBUG)<<"ntracks = "<<ntrack<<std::endl;
	    streamlog_out(DEBUG)<<" Tracks Test  -  "<<ivtx<<" "<<vertices->at(ivtx)->isPrimary()<<" "<<vertices->at(ivtx)->getAssociatedParticle()->getCharge()<<std::endl;

	    for(int itr=0; itr< ntrack; itr++) {
	      streamlog_out(DEBUG)<<"ntracks = "<<ntrack<<" "<<itr<<std::endl;
	      if(vertices->at(ivtx)->getAssociatedParticle()->getParticles().at(itr)==NULL) continue;
      
	      ReconstructedParticle * found_track_particle = vertices->at(ivtx)->getAssociatedParticle()->getParticles().at(itr);

	      _stats._jet_track_charge[ijet][ivtx][itr]=found_track_particle->getCharge();
	      _stats._jet_track_E[ijet][ivtx][itr]=found_track_particle->getEnergy();
	      _stats._jet_track_px[ijet][ivtx][itr]=found_track_particle->getMomentum()[0];
	      _stats._jet_track_py[ijet][ivtx][itr]=found_track_particle->getMomentum()[1];
	      _stats._jet_track_pz[ijet][ivtx][itr]=found_track_particle->getMomentum()[2];
	      _stats._jet_track_p[ijet][ivtx][itr]=MathOperator::getModule(found_track_particle->getMomentum());
	      _stats._jet_track_charge[ijet][ivtx][itr]=found_track_particle->getCharge();

	      streamlog_out(DEBUG)<<" Tracks Test  --  "<<ivtx<<" "<<itr<<" "<<found_track_particle->getTracks().size()<<" "<<found_track_particle->getEnergy()<< " " <<found_track_particle->getTracks()[0]->getZ0()<<" "<<found_track_particle->getCharge()<<std::endl;

	      _stats._jet_track_z0[ijet][ivtx][itr]=found_track_particle->getTracks()[0]->getZ0();
	      _stats._jet_track_d0[ijet][ivtx][itr]=found_track_particle->getTracks()[0]->getD0();
	      _stats._jet_track_phi[ijet][ivtx][itr]=found_track_particle->getTracks()[0]->getPhi();


	      // get kaons cheating !!
	      ReconstructedParticle * kaon_candidate = vtxOperator.__getKaonsCheat(found_track_particle);
	      if(kaon_candidate!=NULL) {
		//kaon_charge=-kaon_candidate->getCharge();
		
		float purity = 0.95;
		float efficiency = 0.88;
		bool reconstructed_kaon=vtxOperator.__magicBall(efficiency, kaon_candidate->getMomentum()[0]);
		float kaon_charge=-1000;
		
		
		if ( reconstructed_kaon==true) {
		  bool correct_charge_kaon=vtxOperator.__magicBall(purity, kaon_candidate->getMomentum()[1]);
		  if (correct_charge_kaon==true)  
		    kaon_charge=kaon_candidate->getCharge();
		  else
		    kaon_charge=-kaon_candidate->getCharge();
		}
		
		if(reconstructed_kaon==true) {
		  _stats._jet_track_iskaon[ijet][ivtx][itr]=1;
		  _stats._jet_track_kaoncharge[ijet][ivtx][itr]=kaon_charge;
		}
	      } else _stats._jet_track_iskaon[ijet][ivtx][itr]=0; // kaon candidate
    
	    }//itr

	  }//itx
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
