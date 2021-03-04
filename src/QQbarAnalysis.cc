
#include "QQbarAnalysis.hh"

using namespace lcio ;
using namespace marlin ;
using std::vector;
using std::string;
using std::abs;
using EVENT::Track;
using EVENT::ReconstructedParticle;
using IMPL::ReconstructedParticleImpl;
using EVENT::ParticleID;
using IMPL::ParticleIDImpl;


namespace QQbarProcessor
{
  QQbarAnalysis:: QQbarAnalysis() {}

  void QQbarAnalysis::Init(std::string _hfilename) 
  { 


    TreeWriter writer;
    _hfile = new TFile( _hfilename.c_str(), "RECREATE", _hfilename.c_str() ) ;
    _hTree = new TTree( "Stats", "tree" );
    writer.InitializeStatsQQbarTree(_hTree, _stats);
    
  }

  vector< MCParticle * > QQbarAnalysis::AnalyseGeneratorQQbar(QQbarMCOperator & opera) {
  
    vector <MCParticle *> genfinalstate;
    for (unsigned int i = 5; i > 0; i--) {
      genfinalstate = opera.GetPairParticles(i);
      if (genfinalstate.size() == 2) break;
    }

    if (genfinalstate.size() == 2) {
      
      for (unsigned int i = 0; i < genfinalstate.size(); i++)  {
	MCParticle * mcb = genfinalstate[i];
	_stats._mc_quark_E[i]=mcb->getEnergy();
	_stats._mc_quark_px[i]=mcb->getMomentum()[0];
	_stats._mc_quark_py[i]=mcb->getMomentum()[1];
	_stats._mc_quark_pz[i]=mcb->getMomentum()[2];
	_stats._mc_quark_pdg[i]=mcb->getPDG();
	_stats._mc_quark_charge[i]=mcb->getCharge();
	_stats._mc_quark_m[i]=mcb->getMass();
      }
    }

    for (unsigned int i = 0; i < genfinalstate.size(); i++) 
      {
	streamlog_out(DEBUG) << "Hard Process Parton Level \n";
 	QQbarTools::PrintParticle(genfinalstate[i]);
      }

    return genfinalstate;
  }

  void QQbarAnalysis::AnalyseGeneratorISR(QQbarMCOperator & opera) {
  
    streamlog_out(DEBUG) << "Extract ISR \n";                                                                                                  

    vector <MCParticle *> genfinalstate;
    genfinalstate = opera.GetPairParticles(22);
    
    if (genfinalstate.size() == 2) {
      
      for (unsigned int i = 0; i < genfinalstate.size(); i++)  {
	MCParticle * mcb = genfinalstate[i];
	_stats._mc_ISR_E[i]=mcb->getEnergy();
	_stats._mc_ISR_px[i]=mcb->getMomentum()[0];
	_stats._mc_ISR_py[i]=mcb->getMomentum()[1];
	_stats._mc_ISR_pz[i]=mcb->getMomentum()[2];
	_stats._mc_ISR_pdg[i]=mcb->getPDG();
	_stats._mc_ISR_charge[i]=mcb->getCharge();
	_stats._mc_ISR_m[i]=mcb->getMass();
      }
    }

    for (unsigned int i = 0; i < genfinalstate.size(); i++) 
      {
	streamlog_out(DEBUG) << "ISR Parton Level \n";
 	QQbarTools::PrintParticle(genfinalstate[i]);
      }

    //    return genfinalstate;
  }

  
  void QQbarAnalysis::AnalyseGeneratorQQbar_PS(QQbarMCOperator & opera, float _Rparam_jet_ps, float _pparam_jet_ps)
  {
    
    vector<PseudoJet> particles;
    JetDefinition jet_def(ee_genkt_algorithm,_Rparam_jet_ps, _pparam_jet_ps);
    
    vector <MCParticle *> bbbar_ps = opera.GetQQbarQuarksPS();
    streamlog_out(DEBUG) << "Hard Process + PS Level \n";

  
    for(int i=0; i<bbbar_ps.size(); i++) {
      if(bbbar_ps.at(i)!=NULL) {
	_stats._mc_quark_ps_n++;
	_stats._mc_quark_ps_E[i]=bbbar_ps.at(i)->getEnergy();
	_stats._mc_quark_ps_px[i]=bbbar_ps.at(i)->getMomentum()[0];
	_stats._mc_quark_ps_py[i]=bbbar_ps.at(i)->getMomentum()[1];
	_stats._mc_quark_ps_pz[i]=bbbar_ps.at(i)->getMomentum()[2];
	_stats._mc_quark_ps_pdg[i]=bbbar_ps.at(i)->getPDG();
	_stats._mc_quark_ps_charge[i]=bbbar_ps.at(i)->getCharge();
	_stats._mc_quark_ps_m[i]=bbbar_ps.at(i)->getMass();

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
      }
    }

    if(particles.size()>1) {
      ClusterSequence cs(particles,jet_def);
      const int njets=2;
      
      vector<PseudoJet> jets = sorted_by_E(cs.exclusive_jets(njets));

      double ymerge_23= cs.exclusive_ymerge(njets);
      double ymerge_12= cs.exclusive_ymerge(njets-1);
      double dmerge_23= cs.exclusive_dmerge(njets);
      double dmerge_12= cs.exclusive_dmerge(njets-1);

      streamlog_out(DEBUG) << "y12 (parton + PS)= "<<ymerge_12 <<std::endl;
      streamlog_out(DEBUG) << "y23 (parton + PS)= "<<ymerge_23 <<std::endl;
      streamlog_out(DEBUG) << "d12 (parton + PS)= "<<dmerge_12 <<std::endl;
      streamlog_out(DEBUG) << "d23 (parton + PS)= "<<dmerge_23 <<std::endl;

      _stats._mc_quark_ps_y12=ymerge_12;
      _stats._mc_quark_ps_y23=ymerge_23;
      _stats._mc_quark_ps_d12=dmerge_12;
      _stats._mc_quark_ps_d23=dmerge_23;

      for(unsigned i=0; i< jets.size(); i++) {
	_stats._mc_quark_ps_jet_E[i]=jets[i].E();
	_stats._mc_quark_ps_jet_px[i]=jets[i].px();
	_stats._mc_quark_ps_jet_py[i]=jets[i].py();
	_stats._mc_quark_ps_jet_pz[i]=jets[i].pz();
      }

    }
  }

  //Added by Seidai in 2020.Sep.17
  //MC stable particle information provider
  void QQbarAnalysis::AnalyseGeneratorQQbar_Stable(QQbarMCOperator& opera, float _Rparam_jet_ps, float _pparam_jet_ps) {
    vector<PseudoJet> particles;
    JetDefinition jet_def(ee_genkt_algorithm, _Rparam_jet_ps, _pparam_jet_ps);
    
    //Obtain particles which are appeared after intermediate particle
    vector<vector<MCParticle*> > all_stable = opera.GetQQbarStables();
    vector<MCParticle*> qqbar_stable = all_stable.at(0);
    vector<MCParticle*> isr_stable = all_stable.at(1);
    vector<MCParticle*> overlay_stable = all_stable.at(2);

    streamlog_out(DEBUG) << "Stable level \n";
    
    int nstables=qqbar_stable.size();
    for(int i=0; i<nstables; i++) {
      if(qqbar_stable.at(i)!=NULL) {
        //They are filled at line:587
	_stats._mc_stable_E[_stats._mc_stable_n]=qqbar_stable.at(i)->getEnergy();
	_stats._mc_stable_px[_stats._mc_stable_n]=qqbar_stable.at(i)->getMomentum()[0];
	_stats._mc_stable_py[_stats._mc_stable_n]=qqbar_stable.at(i)->getMomentum()[1];
	_stats._mc_stable_pz[_stats._mc_stable_n]=qqbar_stable.at(i)->getMomentum()[2];
	_stats._mc_stable_pdg[_stats._mc_stable_n]=qqbar_stable.at(i)->getPDG();
	_stats._mc_stable_charge[_stats._mc_stable_n]=qqbar_stable.at(i)->getCharge();
	_stats._mc_stable_m[_stats._mc_stable_n]=qqbar_stable.at(i)->getMass();
        _stats._mc_stable_isisr[_stats._mc_stable_n]=0;
        _stats._mc_stable_isoverlay[_stats._mc_stable_n]=0;	
	_stats._mc_stable_n++;
        //Consists particle object which has 4-momentum
	particles.push_back(PseudoJet(qqbar_stable.at(i)->getMomentum()[0], qqbar_stable.at(i)->getMomentum()[1], qqbar_stable.at(i)->getMomentum()[2], qqbar_stable.at(i)->getEnergy()));
	
	QQbarTools::PrintParticle(qqbar_stable.at(i));
      } else { //If qqbar_stable is empty(stables nothing), entry just zero
	_stats._mc_stable_n=0;
      }
    }

    int nisr=isr_stable.size();
    for(int i=0; i<nisr; i++) {
      if(isr_stable.at(i)!=NULL) {
        //They are filled at line:587                                                                                                                                                                 
        _stats._mc_stable_E[_stats._mc_stable_n]=isr_stable.at(i)->getEnergy();
        _stats._mc_stable_px[_stats._mc_stable_n]=isr_stable.at(i)->getMomentum()[0];
        _stats._mc_stable_py[_stats._mc_stable_n]=isr_stable.at(i)->getMomentum()[1];
        _stats._mc_stable_pz[_stats._mc_stable_n]=isr_stable.at(i)->getMomentum()[2];
        _stats._mc_stable_pdg[_stats._mc_stable_n]=isr_stable.at(i)->getPDG();
        _stats._mc_stable_charge[_stats._mc_stable_n]=isr_stable.at(i)->getCharge();
        _stats._mc_stable_m[_stats._mc_stable_n]=isr_stable.at(i)->getMass();
        _stats._mc_stable_isisr[_stats._mc_stable_n]=1;
        _stats._mc_stable_isoverlay[_stats._mc_stable_n]=0;
        _stats._mc_stable_n++;
	QQbarTools::PrintParticle(isr_stable.at(i));
      } 
    }
    int noverlay=overlay_stable.size();
    for(int i=0; i<noverlay; i++) {
      if(overlay_stable.at(i)!=NULL) {
        _stats._mc_stable_E[_stats._mc_stable_n]=overlay_stable.at(i)->getEnergy();
        _stats._mc_stable_px[_stats._mc_stable_n]=overlay_stable.at(i)->getMomentum()[0];
        _stats._mc_stable_py[_stats._mc_stable_n]=overlay_stable.at(i)->getMomentum()[1];
        _stats._mc_stable_pz[_stats._mc_stable_n]=overlay_stable.at(i)->getMomentum()[2];
        _stats._mc_stable_pdg[_stats._mc_stable_n]=overlay_stable.at(i)->getPDG();
        _stats._mc_stable_charge[_stats._mc_stable_n]=overlay_stable.at(i)->getCharge();
        _stats._mc_stable_m[_stats._mc_stable_n]=overlay_stable.at(i)->getMass();
        _stats._mc_stable_isisr[_stats._mc_stable_n]=0;
        _stats._mc_stable_isoverlay[_stats._mc_stable_n]=1;
        _stats._mc_stable_n++;
	QQbarTools::PrintParticle(overlay_stable.at(i)); 
      }
    }

    //stables loop
    if(particles.size()>1) {
      ClusterSequence cs(particles, jet_def);
      const int njets=2;

      vector<PseudoJet> jets = sorted_by_E(cs.exclusive_jets(njets));
      double ymerge_23 = cs.exclusive_ymerge(njets);
      double ymerge_12 = cs.exclusive_ymerge(njets-1);
      double dmerge_12 = cs.exclusive_dmerge(njets);
      double dmerge_23 = cs.exclusive_dmerge(njets-1);
      
      streamlog_out(DEBUG) << "y12 (Stable)= " << ymerge_12 << std::endl;
      streamlog_out(DEBUG) << "y23 (Stable)= " << ymerge_23 << std::endl;
      streamlog_out(DEBUG) << "d12 (Stable)= " << dmerge_12 << std::endl;
      streamlog_out(DEBUG) << "d23 (Stable)= " << dmerge_23 << std::endl;
      
      _stats._mc_stable_y12 = ymerge_12;
      _stats._mc_stable_y23 = ymerge_23;
      _stats._mc_stable_d12 = dmerge_12;
      _stats._mc_stable_d23 = dmerge_23;
      for(int i=0; i<jets.size(); i++) {
	_stats._mc_stable_n++;
	_stats._mc_stable_jet_E[i]=jets[i].E();
	_stats._mc_stable_jet_px[i]=jets[i].px();
	_stats._mc_stable_jet_py[i]=jets[i].py();
	_stats._mc_stable_jet_pz[i]=jets[i].pz();
      }
      
    }
  }//AnalyseGeneratorQQbar_Stable()


  
  void QQbarAnalysis::AnalyseQQbar(LCEvent * evt,
				   bool _boolDBDanalysis,
				   bool _newPandoraPFO,
				   std::string _colName ,
				   std::string _newcolName ,
				   std::string _colRelName,
				   std::string _initialJetsColName,
				   std::string _JetsColName ,
				   std::string _JetsRelColName ,
				   std::string _MCColName,
				   std::string _Old2NewPandoraPFOsLink,
				   float _Rparam_jet_ps, 
				   float _pparam_jet_ps
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

        streamlog_out(DEBUG) <<"   ---------------------------------------------------------- Analysis EVENT: " <<evt->getEventNumber() <<"\n";
	//MonteCarlo & parton level Information
	LCCollection * mccol = evt->getCollection(_MCColName);
	
	//reconstruction
	LCCollection * jetcol = evt->getCollection(_JetsColName);
	LCCollection * jetrelcol = evt->getCollection(_JetsRelColName);

        //LCCollection * mcvtxcol = evt->getCollection(_MCVtxColName); 
        LCCollection * pfocol = evt->getCollection(_colName);  
	//        VertexChargeOperator vtxOperator(evt->getCollection(_colName),evt->getCollection(_colRelName)); 
	vector< RecoJet * > * jets = QQbarTools::getJets(jetcol, jetrelcol);

	ClearVariables();

	std::sort(jets->begin(), jets->end(), QQbarTools::sortByBtag);
        if (jets->size() != 2 ) {
	  streamlog_out(DEBUG) << "ERROR jets size = "<< jets->size() <<"\n";
          _hTree->Fill();
          ClearVariables();
          return;          
        }  

	//MC bbbar Analysis
	QQbarMCOperator operaMC(mccol,evt->getCollection(_colRelName));    
	//if(opera.IsEvent()==true) {
	vector < MCParticle * > mcbs = AnalyseGeneratorQQbar(operaMC);//Hard Process
	AnalyseGeneratorISR(operaMC); 
	AnalyseGeneratorQQbar_PS(operaMC,_Rparam_jet_ps,_pparam_jet_ps);
	AnalyseGeneratorQQbar_Stable(operaMC,_Rparam_jet_ps,_pparam_jet_ps);

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
	    _stats._d23 = params[pidh.getParameterIndex(alid,"y23")];
	    _stats._d12 = params[pidh.getParameterIndex(alid,"y12")];
	    streamlog_out(DEBUG) << "not DBD d23 (reco)= "<<_stats._d23<<"\n";

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
	
        _stats._aplanarity = jetcol->getParameters().getFloatVal("aplanarity");
	_stats._sphericity = jetcol->getParameters().getFloatVal("sphericity");
	std::vector<float> sphericitytensor;
	jetcol->getParameters().getFloatVals( "sphericity_tensor_eigenvalues" , sphericitytensor) ;
	_stats._sphericity_tensor[0]=sphericitytensor[0];
	_stats._sphericity_tensor[1]=sphericitytensor[1];
	_stats._sphericity_tensor[2]=sphericitytensor[2];


	//Obtain particles which are appeared after intermediate particle                                                                                                                                      
	vector<vector<MCParticle*> > all_stable = operaMC.GetQQbarStables();
	vector<MCParticle*> isr_stable = all_stable.at(1);

	//get the pfO object identified as photon with the maximum energy
	// get pFo + type per jet
	int pfo_recorded=0;
	for(int ijet=0;ijet<2; ijet++) {

	  streamlog_out(DEBUG)<<" IJET "<<ijet<<"\n";
	  streamlog_out(DEBUG)<<" _stats._jet_E="<<jets->at(ijet)->getEnergy();
	  streamlog_out(DEBUG)<<" _stats._jet_px="<<jets->at(ijet)->getMomentum()[0];
	  streamlog_out(DEBUG)<<" _stats._jet_py="<<jets->at(ijet)->getMomentum()[1];
	  streamlog_out(DEBUG)<<" _stats._jet_pz="<<jets->at(ijet)->getMomentum()[2];
	  streamlog_out(DEBUG)<<" _stats._jet_m="<<jets->at(ijet)->getMass();
	  streamlog_out(DEBUG)<<" _stats._jet_type="<<jets->at(ijet)->getType();
	  streamlog_out(DEBUG)<<" _stats._jet_charge="<<jets->at(ijet)->getCharge()<<"\n";

	  _stats._jet_E[ijet]=jets->at(ijet)->getEnergy();
	  _stats._jet_px[ijet]=jets->at(ijet)->getMomentum()[0];
	  _stats._jet_py[ijet]=jets->at(ijet)->getMomentum()[1];
	  _stats._jet_pz[ijet]=jets->at(ijet)->getMomentum()[2];
	  _stats._jet_btag[ijet]=jets->at(ijet)->GetBTag();
          _stats._jet_ctag[ijet]=jets->at(ijet)->GetCTag();

	  //	  ReconstructedParticle * jet_reco = dynamic_cast< ReconstructedParticle * >(jetcol->getElementAt(ijet));
  
	  std::string pfocollection=_colName;
	  //	  if(_newPandoraPFO==true) pfocollection=_newcolName;

	  PIDHandler pidh_1(evt->getCollection(pfocollection));
	  int pid_1 = pidh_1.getAlgorithmID("LikelihoodPID");

	  PIDHandler pidh_2(evt->getCollection(pfocollection));
          int pid_2 = pidh_2.getAlgorithmID("dEdxPID");


	  vector<ReconstructedParticle*> components_originalPFO = jets->at(ijet)->getParticles();
	  if(components_originalPFO.size()>150) {
	    std::cout<<"ERROR: nPFOs> 150: "<<components_originalPFO.size()<<std::endl;
	  }
	  for(int i=0; i<components_originalPFO.size(); i++) { 

	    ReconstructedParticle * component = components_originalPFO.at(i);

	    /*if(_newPandoraPFO==true) {
              streamlog_out(DEBUG)<<"newpandora=true\n";
	      vector< LCObject * > obj = navigator.getRelatedToObjects(components_originalPFO.at(i));
	      streamlog_out(DEBUG)<<"  oldPandoraPFOID:"<<components_originalPFO.at(i)->getEnergy();
              streamlog_out(DEBUG)<<" size:"<<obj.size()<<" ";
	      streamlog_out(DEBUG)<<obj.at(0)->id()<<"\n";
	      component = dynamic_cast< ReconstructedParticle * >(obj[0]);
	      streamlog_out(DEBUG)<<" newID:" << component->getEnergy()<<"\n";

	      }*/
	      
            streamlog_out(DEBUG)<<"pfo number: "<<i<<"\n";
	    streamlog_out(DEBUG)<<" _stats._pfo_E="<<component->getEnergy();
	    streamlog_out(DEBUG)<<" _stats._pfo_px="<<component->getMomentum()[0];
	    streamlog_out(DEBUG)<<" _stats._pfo_py="<<component->getMomentum()[1];
	    streamlog_out(DEBUG)<<" _stats._pfo_pz="<<component->getMomentum()[2];
	    streamlog_out(DEBUG)<<" _stats._pfo_m="<<component->getMass();
	    streamlog_out(DEBUG)<<" _stats._pfo_type="<<component->getType();
	    streamlog_out(DEBUG)<<" _stats._pfo_charge="<<component->getCharge()<<"\n";

            if(component->getStartVertex()!=NULL) {
	      //we collect the info of the tracks associated to the primary vtx
	      if(component->getStartVertex()->isPrimary()) {
		streamlog_out(DEBUG)<<" IS PRIMARY TRACK: ssave info " <<std::endl;

		_stats._pfo_jet_match[pfo_recorded]=ijet;

		MCParticle * mctrack=operaMC.getMCParticle(component);

		_stats._pfo_E[pfo_recorded]=component->getEnergy();
		_stats._pfo_px[pfo_recorded]=component->getMomentum()[0];
		_stats._pfo_py[pfo_recorded]=component->getMomentum()[1];
		_stats._pfo_pz[pfo_recorded]=component->getMomentum()[2];
		_stats._pfo_m[pfo_recorded]=component->getMass();
		_stats._pfo_type[pfo_recorded]=component->getType();
		_stats._pfo_charge[pfo_recorded]=component->getCharge();
		//cheat info                                                                                                                                                                                   
		_stats._pfo_pdgcheat[pfo_recorded]=operaMC.getPDG(mctrack);
                streamlog_out(DEBUG)<<" PDG CHEAT " <<_stats._pfo_pdgcheat[pfo_recorded]<<std::endl;

		_stats._pfo_vtx[pfo_recorded]=0;
		_stats._pfo_istrack[pfo_recorded]=1;
		_stats._pfo_isisr[pfo_recorded]=0;
		for(int iisr=0; iisr<isr_stable.size();iisr++) {
		  if(mctrack==isr_stable.at(iisr)) {
		    _stats._pfo_isisr[pfo_recorded]=1;
		    streamlog_out(DEBUG)<<" Primary track is associated to ISR "<<std::endl;
		    continue;
		  }
		}
		Track * trk =component->getTracks()[0];
		_stats._pfo_chi2[pfo_recorded]=trk->getChi2();
                _stats._pfo_ndf[pfo_recorded]=float(trk->getNdf());
                _stats._pfo_isoverlay[pfo_recorded]=operaMC.isOverlay(mctrack);
		_stats._pfo_tpc_hits[pfo_recorded]=trk->getSubdetectorHitNumbers()[6];
		_stats._pfo_dedx[pfo_recorded]=trk->getdEdx()*1e6;
		_stats._pfo_dedxerror[pfo_recorded]=trk->getdEdxError()*1e6;
		_stats._pfo_d0[pfo_recorded]=trk->getD0();
                _stats._pfo_z0[pfo_recorded]=trk->getZ0();
                _stats._pfo_phi[pfo_recorded]=trk->getPhi();
                _stats._pfo_omega[pfo_recorded]=trk->getOmega();
                _stats._pfo_tanlambda[pfo_recorded]=trk->getTanLambda();
		const FloatVec cov = trk->getCovMatrix();
		//indexes extracted from LCFIPlus code enum cov { d0d0=0, d0ph, phph, d0om, phom, omom, d0z0,                  
		//                 z0ph, z0om, z0z0, d0td, phtd, omtd, z0td, tdtd, covN  
		//};  
		_stats._pfo_d0error[pfo_recorded]=cov[0];
		_stats._pfo_z0error[pfo_recorded]=cov[9];
		_stats._pfo_phierror[pfo_recorded]=cov[2];
		_stats._pfo_omegaerror[pfo_recorded]=cov[5];
		_stats._pfo_tanlambdaerror[pfo_recorded]=cov[14];

		if(_newPandoraPFO==true) {
		  LCRelationNavigator navigator(evt->getCollection(_Old2NewPandoraPFOsLink));
		  vector< LCObject * > obj = navigator.getRelatedToObjects(component);
		  streamlog_out(DEBUG)<<" objSize:"<<obj.size()<<"\n";
		  ReconstructedParticle * component_pid = dynamic_cast< ReconstructedParticle* >(obj[0]);
		  _stats._pfo_pid[pfo_recorded] = pidh_1.getParticleID(component_pid, pid_1).getPDG();
		  streamlog_out(DEBUG)<<" PDG with LikelihoodPID " <<pid_1<<" "<<pidh_1.getParticleID(component_pid, pid_1).getPDG()<<std::endl;
		  _stats._pfo_pid_likelihood[pfo_recorded]=pidh_1.getParticleID(component_pid, pid_1).getLikelihood();

		  _stats._pfo_piddedx[pfo_recorded] = pidh_2.getParticleID(component_pid, pid_2).getPDG();
		  _stats._pfo_piddedx_likelihood[pfo_recorded]=pidh_2.getParticleID(component_pid, pid_2).getLikelihood();
		  streamlog_out(DEBUG)<<" PDG with LikelihoodPID-dEdx1 " <<pid_2<<" "<<pidh_2.getParticleID(component_pid, pid_2).getPDG()<<std::endl;
		} else {
		  _stats._pfo_pid[pfo_recorded] = pidh_1.getParticleID(component, pid_1).getPDG();
                  streamlog_out(DEBUG)<<" PDG with LikelihoodPID " <<pid_1<<" "<<pidh_1.getParticleID(component, pid_1).getPDG()<<std::endl;
                  _stats._pfo_pid_likelihood[pfo_recorded]=pidh_1.getParticleID(component, pid_1).getLikelihood();

                  _stats._pfo_piddedx[pfo_recorded] = pidh_2.getParticleID(component, pid_2).getPDG();
                  _stats._pfo_piddedx_likelihood[pfo_recorded]=pidh_2.getParticleID(component, pid_2).getLikelihood();
                  streamlog_out(DEBUG)<<" PDG with LikelihoodPID-dEdx1 " <<pid_2<<" "<<pidh_2.getParticleID(component, pid_2).getPDG()<<std::endl;
		}


		pfo_recorded++;
		if(ijet==0) _stats._pfo_n_j1++;
		if(ijet==1) _stats._pfo_n_j2++;
		if(pfo_recorded>999) {
		  streamlog_out(DEBUG)<<"ERROR - pfo_recorded > 150 "<<std::endl;
		  break;
		}
	      } else {
                streamlog_out(DEBUG)<<" IS A SECONDARY TRACK: ignore info because we prefer the LCFIPlus + VertexRecovery Information " <<std::endl;
	      }
	    } else {
	      streamlog_out(DEBUG)<<" THIS PFO is not a track associated to any vtx" <<std::endl;

	      _stats._pfo_jet_match[pfo_recorded]=ijet;

	      _stats._pfo_E[pfo_recorded]=component->getEnergy();
	      _stats._pfo_px[pfo_recorded]=component->getMomentum()[0];
	      _stats._pfo_py[pfo_recorded]=component->getMomentum()[1];
	      _stats._pfo_pz[pfo_recorded]=component->getMomentum()[2];
	      _stats._pfo_m[pfo_recorded]=component->getMass();
	      _stats._pfo_type[pfo_recorded]=component->getType();
	      _stats._pfo_charge[pfo_recorded]=component->getCharge();
	      //cheat info      
	      MCParticle * mcpfo=operaMC.getMCParticle(component);
	      /*
	      MCParticle * mcpfo;
	      if(_newPandoraPFO==true) {
		LCRelationNavigator navigator(evt->getCollection(_Old2NewPandoraPFOsLink));
		vector< LCObject * > obj = navigator.getRelatedToObjects(component);
		//		mcpfo= operaMC.getMCParticle(dynamic_cast< ReconstructedParticle* >(obj[0]));
		ReconstructedParticle * jetpart = dynamic_cast< ReconstructedParticle * >(obj[0]);
		mcpfo= operaMC.getMCParticle(jetpart);

	      } else {
		mcpfo= operaMC.getMCParticle(component);
		}*/

	      _stats._pfo_pdgcheat[pfo_recorded]=operaMC.getPDG(mcpfo);
	      streamlog_out(DEBUG)<<" PDG CHEAT " <<_stats._pfo_pdgcheat[pfo_recorded]<<std::endl;
	      _stats._pfo_istrack[pfo_recorded]=0;
	      _stats._pfo_vtx[pfo_recorded]=-1;
              _stats._pfo_isoverlay[pfo_recorded]=operaMC.isOverlay(mcpfo);
	      _stats._pfo_isisr[pfo_recorded]=0;
	      for(int iisr=0; iisr<isr_stable.size();iisr++) {
		if(mcpfo==isr_stable.at(iisr)) {
		  _stats._pfo_isisr[pfo_recorded]=1;
		  streamlog_out(DEBUG)<<" PFO is related to ISR particle "<<std::endl;
		  continue;
		}
	      }

	      if(_newPandoraPFO==true) {
		  LCRelationNavigator navigator(evt->getCollection(_Old2NewPandoraPFOsLink));
		  vector< LCObject * > obj = navigator.getRelatedToObjects(component);
		  streamlog_out(DEBUG)<<" objSize:"<<obj.size()<<"\n";
		  ReconstructedParticle * component_pid = dynamic_cast< ReconstructedParticle* >(obj[0]);
		  _stats._pfo_pid[pfo_recorded] = pidh_1.getParticleID(component_pid, pid_1).getPDG();
		  streamlog_out(DEBUG)<<" PDG with LikelihoodPID " <<pid_1<<" "<<pidh_1.getParticleID(component_pid, pid_1).getPDG()<<std::endl;
		  _stats._pfo_pid_likelihood[pfo_recorded]=pidh_1.getParticleID(component_pid, pid_1).getLikelihood();

		} else {
		  _stats._pfo_pid[pfo_recorded] = pidh_1.getParticleID(component, pid_1).getPDG();
                  streamlog_out(DEBUG)<<" PDG with LikelihoodPID " <<pid_1<<" "<<pidh_1.getParticleID(component, pid_1).getPDG()<<std::endl;
                  _stats._pfo_pid_likelihood[pfo_recorded]=pidh_1.getParticleID(component, pid_1).getLikelihood();

	      }

	      _stats._pfo_piddedx[pfo_recorded] = 0;
	      _stats._pfo_piddedx_likelihood[pfo_recorded]=0;

	      pfo_recorded++;
	      if(ijet==0) _stats._pfo_n_j1++;
	      if(ijet==1) _stats._pfo_n_j2++;
		
	      if(pfo_recorded>999) {
		streamlog_out(DEBUG)<<"ERROR - pfo_recorded > 150 "<<std::endl;
		break;
	      }
	    }
	  }
	
	  //Get all secondary vertexes associated to secondary tracks in each jet
	  vector< Vertex * > * vertices = jets->at(ijet)->GetRecoVertices();
	  _stats._nvtx+=vertices->size();
	  if(ijet==0) _stats._nvtx_j1=vertices->size();
	  if(ijet==1) _stats._nvtx_j2=vertices->size();

	  streamlog_out(DEBUG)<<"nvertices = "<<vertices->size()<<std::endl;
	  if(vertices->size()==0) {
	    _stats._pfo_n=pfo_recorded;
	    continue;
	  }
	  
	  for( int ivtx=0; ivtx<vertices->size(); ivtx++) {


	    streamlog_out(DEBUG)<<"   ivtx = "<<ivtx<<std::endl;
	    int ntrack = vertices->at(ivtx)->getAssociatedParticle()->getParticles().size();
	    streamlog_out(DEBUG)<<"   ntracks = "<<ntrack<<std::endl;
	    for(int itr=0; itr< ntrack; itr++) {

	      _stats._pfo_jet_match[pfo_recorded]=ijet;

              ReconstructedParticle * found_track_particle = vertices->at(ivtx)->getAssociatedParticle()->getParticles().at(itr);
	      streamlog_out(DEBUG)<<"track number: "<<itr<<"\n";
	      streamlog_out(DEBUG)<<" _stats._pfo_E[pfo_recorded]="<<found_track_particle->getEnergy();
	      streamlog_out(DEBUG)<<" _stats._pfo_px[pfo_recorded]="<<found_track_particle->getMomentum()[0];
	      streamlog_out(DEBUG)<<" _stats._pfo_py[pfo_recorded]="<<found_track_particle->getMomentum()[1];
	      streamlog_out(DEBUG)<<" _stats._pfo_pz[pfo_recorded]="<<found_track_particle->getMomentum()[2];
	      streamlog_out(DEBUG)<<" _stats._pfo_m[pfo_recorded]="<<found_track_particle->getMass();
	      streamlog_out(DEBUG)<<" _stats._pfo_type[pfo_recorded]="<<found_track_particle->getType();
	      streamlog_out(DEBUG)<<" _stats._pfo_charge[pfo_recorded]="<<found_track_particle->getCharge()<<"\n";


	      _stats._pfo_E[pfo_recorded]=found_track_particle->getEnergy();
	      _stats._pfo_px[pfo_recorded]=found_track_particle->getMomentum()[0];
	      _stats._pfo_py[pfo_recorded]=found_track_particle->getMomentum()[1];
	      _stats._pfo_pz[pfo_recorded]=found_track_particle->getMomentum()[2];
	      _stats._pfo_m[pfo_recorded]=found_track_particle->getMass();
	      _stats._pfo_type[pfo_recorded]=found_track_particle->getType();
	      _stats._pfo_charge[pfo_recorded]=found_track_particle->getCharge();
	      //cheat info                                          
              MCParticle * mctrack= operaMC.getMCParticle(found_track_particle);

	      _stats._pfo_pdgcheat[pfo_recorded]=operaMC.getPDG(mctrack);
	      streamlog_out(DEBUG)<<" PDG CHEAT " <<_stats._pfo_pdgcheat[pfo_recorded]<<std::endl;
	      _stats._pfo_vtx[pfo_recorded]=ivtx+1;
	      _stats._pfo_istrack[pfo_recorded]=1;
	      _stats._pfo_isisr[pfo_recorded]=0;
              for(int iisr=0; iisr<isr_stable.size();iisr++) {
                if(mctrack==isr_stable.at(iisr)) {
                  _stats._pfo_isisr[pfo_recorded]=1;
                  streamlog_out(DEBUG)<<" Secondary track is related to ISR particle "<<std::endl;
                  continue;
                }
              }
	      Track * trk = found_track_particle->getTracks()[0];
	      _stats._pfo_isoverlay[pfo_recorded]=operaMC.isOverlay(mctrack);
	      _stats._pfo_tpc_hits[pfo_recorded]=trk->getSubdetectorHitNumbers()[6];
	      _stats._pfo_dedx[pfo_recorded]=trk->getdEdx()*1e6;
	      _stats._pfo_dedxerror[pfo_recorded]=trk->getdEdxError()*1e6;
	      _stats._pfo_d0[pfo_recorded]=trk->getD0();
	      _stats._pfo_z0[pfo_recorded]=trk->getZ0();
	      _stats._pfo_phi[pfo_recorded]=trk->getPhi();
	      _stats._pfo_omega[pfo_recorded]=trk->getOmega();
	      _stats._pfo_tanlambda[pfo_recorded]=trk->getTanLambda();
	      _stats._pfo_chi2[pfo_recorded]=trk->getChi2();
	      _stats._pfo_ndf[pfo_recorded]=float(trk->getNdf());
	      const FloatVec cov = trk->getCovMatrix();
	      //indexes extracted from LCFIPlus code enum cov { d0d0=0, d0ph, phph, d0om, phom, omom, d0z0,
	      //		 z0ph, z0om, z0z0, d0td, phtd, omtd, z0td, tdtd, covN
	      //};
	      _stats._pfo_d0error[pfo_recorded]=cov[0];
	      _stats._pfo_z0error[pfo_recorded]=cov[9];
	      _stats._pfo_phierror[pfo_recorded]=cov[2];
	      _stats._pfo_omegaerror[pfo_recorded]=cov[5];
	      _stats._pfo_tanlambdaerror[pfo_recorded]=cov[14];
	      
	      if(_newPandoraPFO==true) {
		LCRelationNavigator navigator(evt->getCollection(_Old2NewPandoraPFOsLink));
		vector< LCObject * > obj = navigator.getRelatedToObjects(found_track_particle);
		streamlog_out(DEBUG)<<" objSize:"<<obj.size()<<"\n";
		ReconstructedParticle * component_pid = dynamic_cast< ReconstructedParticle* >(obj[0]);
		_stats._pfo_pid[pfo_recorded] = pidh_1.getParticleID(component_pid, pid_1).getPDG();
		streamlog_out(DEBUG)<<" PDG with LikelihoodPID " <<pid_1<<" "<<pidh_1.getParticleID(component_pid, pid_1).getPDG()<<std::endl;
		_stats._pfo_pid_likelihood[pfo_recorded]=pidh_1.getParticleID(component_pid, pid_1).getLikelihood();
		
		_stats._pfo_piddedx[pfo_recorded] = pidh_2.getParticleID(component_pid, pid_2).getPDG();
		_stats._pfo_piddedx_likelihood[pfo_recorded]=pidh_2.getParticleID(component_pid, pid_2).getLikelihood();
		streamlog_out(DEBUG)<<" PDG with LikelihoodPID-dEdx1 " <<pid_2<<" "<<pidh_2.getParticleID(component_pid, pid_2).getPDG()<<std::endl;
		
	      } else {
		_stats._pfo_pid[pfo_recorded] = pidh_1.getParticleID(found_track_particle, pid_1).getPDG();
		streamlog_out(DEBUG)<<" PDG with default LikelihoodPID " <<pid_1<<" "<<pidh_1.getParticleID(found_track_particle, pid_1).getPDG()<<std::endl;
		_stats._pfo_pid_likelihood[pfo_recorded]=pidh_1.getParticleID(found_track_particle, pid_1).getLikelihood();
		
		_stats._pfo_piddedx[pfo_recorded] = pidh_2.getParticleID(found_track_particle, pid_2).getPDG();
		_stats._pfo_piddedx_likelihood[pfo_recorded]=pidh_2.getParticleID(found_track_particle, pid_2).getLikelihood();
		streamlog_out(DEBUG)<<" PDG with LikelihoodPID-dEdx1 " <<pid_2<<" "<<pidh_2.getParticleID(found_track_particle, pid_2).getPDG()<<std::endl;
	      }


	      streamlog_out(DEBUG)<<"      itr= "<<itr<<std::endl;
	      pfo_recorded++;
	      if(ijet==0) _stats._pfo_n_j1++;
	      if(ijet==1) _stats._pfo_n_j2++;

	      if(pfo_recorded>999) {
		streamlog_out(DEBUG)<<"ERROR - pfo_recorded > 150 "<<std::endl;
		break;
	      }
	    }//itr
	  }//vitx
	  
	  _stats._pfo_n=pfo_recorded;
	  if(pfo_recorded==0) 
	    streamlog_out(DEBUG)<<"ERROR - pfo_recorded =0 "<<std::endl;

	}//ijet
	_hTree->Fill();	

	delete jets;
	ClearVariables();
      }
    catch(DataNotAvailableException &e)
      {
	std::cout << e.what() <<"\n";
      }
    
  }


  void QQbarAnalysis::ClearVariables()
  {
    _stats.Clear();
  }

  void QQbarAnalysis::End()
  {   
    _hfile->Write();
    _hfile->Close();
  }

}
