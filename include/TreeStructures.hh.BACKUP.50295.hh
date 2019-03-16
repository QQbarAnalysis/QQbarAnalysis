#ifndef _SummaryData_hh
#define _SummaryData_hh
namespace QQbarProcessor 
{
<<<<<<< HEAD
	struct SummaryData 
	{
		public: 
		int _nEvt ;
		int _nGenUsed;
		int _nBkgUsed;
		int _nAfterBtagCuts;
		int _nAfterKinematicCuts;
		int _nAfterLeptonCuts;
		int _nAfterMassCuts;
		int _nAfterGenMassCuts;
		int _nChargedB;
		int _nKaons;
		void Clear()
		{
			_nEvt  = 0;
			_nBkgUsed = 0;
			_nGenUsed = 0;
			_nAfterBtagCuts = 0;
			_nAfterKinematicCuts = 0;
			_nAfterLeptonCuts = 0;
			_nAfterMassCuts = 0;
			_nAfterGenMassCuts = 0;
			_nChargedB = 0;
			_nKaons = 0;

		}
	};
	struct StatsData 
	{
		float _B1momentum;
		float _B2momentum;
		float _B1Jetmomentum;
		float _B2Jetmomentum;
		float _B2btag;
		float _B1btag;
		float _B1mass;
		float _B2mass;
		float _B1chargeBalance;
		float _B2chargeBalance;
		float _B1costheta;
		float _B2costheta;
		float _B1truthAngle;
		float _bbbarAngle;
		float _bbbarPt;
		float _bbbarP;
		float _InvMass;
		int _B1charge;
		int _B1KaonTag;
		int _B1VtxTag;
		int _B2KaonTag;
		int _B2VtxTag;
		int _B2charge;
		float _maxPhotonEnergy;
		float _maxPhotonCostheta;
		float _maxPhotonAngle;
		float _Sphericity;
		float _Thrust;
		float _B1Y;
		float _B2Y;
		float _bbbar4JetMass;
		float _kaonMomentum;
		float _ZZMass1;
		float _ZZMass2;
		float _SumCos;
		float _ThrustCos;

		int _mctag;
		int _recotag;
		float _hadMass;
		float _bProduct;
		float _W1mass;
		float _W1gamma;
		float _W1momentum;
		float _W1costheta;
		float _W2mass;
		float _W2momentum;
		float _W2costheta;
		int _Top1bcharge;
		int _Top1Genbcharge;
		float _Top1btag;
		float _Top1gamma;
		float _Top1bmomentum;
		int _Top1bntracks;
		int _Top1Genbntracks;
		float _Top1mass;
		float _Top1momentum;
		float _Top1energy;
		float _Top1bdistance;
		float _Top1costheta;
		float _Top1bcostheta;
		float _Top1cosWb;
		float _Top1pstarb;
		float _Top1truthAngle;
		int _Top1Vtx;
		int _Top1Kaon;
		int _Top1KaonNumber;
		int _Top1KaonCharges[10];
		float _Top1KaonMomentum[10];
		int _Top1bTVCM;
		int _Top2bntracks;
		int _Top2Genbntracks;
		int _Top2bTVCM;
		int _UsedBTVCM;
		float _Top2bmomentum;
		float _Top2bdistance;
		float _Top2btag;
		float _Top2mass;
		float _Top2energy;
		float _Top2gamma;
		int _Top2bcharge;
		int _Top2Genbcharge;
		float _Top2momentum;
		float _Top2costheta;
		float _Top2bcostheta;
		int _Top2Vtx;
		int _Top2Kaon;
		int _Top2KaonNumber;
		int _Top2KaonCharges[10];
		float _Top2KaonMomentum[10];
		int _Top2leptonCharge;
		float _Top2leptonE;
		float _Top2leptonCos;
		int _Top2leptonCorrect;
		float _qBCostheta[2];
		float _qCostheta[2];
		float _qCostheta1;
		float _qCostheta2;
		int _methodUsed;
		int _methodRefused;
		int _methodZero;
		int _methodCorrect;
		int _methodTaken[12];
		int _methodSameCharge[12];
		int _methodZeroCharge[12];
		float _chiHad;
		float _chiTopMass;
		float _chiTopE;
		float _chiPbstar;
		float _chiCosWb;
		float _chiGammaT;
		float _chiGammaT2;
		float _chiTop2Mass;
		float _chiTop2E;

		int _MCBOscillation;
		int _MCBWcorrect;
		int _MCBBarOscillation;
		float _MCTopBangle;
		//float _MCTopBarBangle;
		int _MCLeptonPDG;
		float _MCLeptonMomentum;
		float _MCLeptonCostheta;
		float _MCTopmomentum;
		float _MCTopmass;
		float _MCquarkAngle;
		float _MCTopcostheta;
		float _MCTopBarmomentum;
		float _MCTopBarmass;
		float _MCTopBarcostheta;
		float _MCTopcosWb;
		float _MCTopcosWt;
		float _qMCcostheta[2];
		float _MCMass;
		float _MCPDG;
		float _MCPt;
		float _qMCBcostheta[2];
		float _MCNeutrinoEnergy;
		float _totalEnergy;
		float _missedEnergy;
		float _gammaT;
		
		//hadronic
		float _chiHad1;
		float _chiTopMass1;
		float _chiTopE1;
		float _chiPbstar1;
		float _chiCosWb1;
		float _chiGammaT1;
		float _chiHad2;
		float _chiTopMass2;
		float _chiTopE2;
		float _chiPbstar2;
		float _chiCosWb2;

		void Clear()
		{
			_MCPDG = 0;
			_B1momentum = -1.0;
			_B2momentum = -1.0;
			_B1mass = -1.0;
			_B2mass = -1.0;
			_B2btag = -1.;
			_B1btag = -1.0;
			_B1costheta = -2.0;
			_B2costheta = -2.0;
			_B1charge = -5.0;
			_B2charge = -5.0;
			_B1truthAngle = -1.0;
			_MCPt = 0.0;
			_bbbarPt = 0.0;
			_bbbarP = 0.0;
			_MCLeptonMomentum = -1.0;
			_MCLeptonCostheta = -2.0;
			_MCLeptonPDG = 0;
			_MCTopmass = -1.0;
			_MCMass = -1.0;
			_MCTopBarmass = -1.0;
			_MCTopmomentum = -1.0;
			_MCTopBarmomentum = -1.0;
			_MCTopcostheta = -2.0;
			_MCTopBarcostheta = -2.0;
			_qMCcostheta[0] = -2.0;
			_qMCcostheta[1] = -2.0;
			_qMCBcostheta[0] = -2.0;
			_qMCBcostheta[1] = -2.0;
			_MCTopBangle = -1.0;
			_MCTopcosWb = -2.0;
			_Top1mass = -1.0;
			_W1mass = -1.0;
			_W2costheta = -2.0;
			_chiHad = -1.0;
			_methodUsed = 0;
			_methodRefused = 0;
			_methodZero = 0;
			_methodCorrect = -1;
			_qBCostheta[0] = -2.0;
			_qBCostheta[1] = -2.0;
			_qCostheta[0] = -2.0;
			_qCostheta[1] = -2.0;
			_ZZMass1 = -1;
			_ZZMass2 = -1;
			for (unsigned int i = 0; i < 6; i++) 
			{
				_methodTaken[i] = -1;
				_methodSameCharge[i] = -1;
				_methodZeroCharge[i] = -1;
			}
		}
	};
=======
  struct SummaryData  {
  public: 
    int _nEvt ;
    int _nGenUsed;
    int _nBkgUsed;
    int _nAfterBtagCuts;
    int _nAfterKinematicCuts;
    int _nAfterLeptonCuts;
    int _nAfterMassCuts;
    int _nAfterGenMassCuts;
    int _nChargedB;
    int _nKaons;

    void Clear()  {
      _nEvt  = 0;
      _nBkgUsed = 0;
      _nGenUsed = 0;
      _nAfterBtagCuts = 0;
      _nAfterKinematicCuts = 0;
      _nAfterLeptonCuts = 0;
      _nAfterMassCuts = 0;
      _nAfterGenMassCuts = 0;
      _nChargedB = 0;
      _nKaons = 0;

    }
  };


  struct StatsData  {
  public:
	  
    float _B1momentum;
    float _B2momentum;
    float _B1Jetmomentum;
    float _B2Jetmomentum;
    float _B2btag;
    float _B1btag;
    float _B1mass;
    float _B2mass;
    float _B1chargeBalance;
    float _B2chargeBalance;
    float _B1costheta;
    float _B2costheta;
    float _B1truthAngle;
    float _bbbarAngle;
    float _bbbarPt;
    float _bbbarP;
    float _InvMass;
    int _B1charge;
    int _B1KaonTag;
    int _B1VtxTag;
    int _B2KaonTag;
    int _B2VtxTag;
    int _B2charge;
    float _maxPhotonEnergy;
    float _maxPhotonCostheta;
    float _Sphericity;
    float _Thrust;
    float _B1Y;
    float _B2Y;
    float _bbbar4JetMass;
    float _kaonMomentum;
    float _ZZMass1;
    float _ZZMass2;

    int _mctag;
    int _recotag;
    float _W1mass;
    float _W1momentum;
    float _W1costheta;
    float _W2mass;
    float _W2momentum;
    float _W2costheta;
    int _Top1bcharge;
    float _Top1btag;
    float _Top1bmomentum;
    int _Top1bntracks;
    float _Top1mass;
    float _Top1momentum;
    float _Top1energy;
    float _Top1bdistance;
    float _Top1costheta;
    float _Top1bcostheta;
    float _Top1cosWb;
    float _Top1truthAngle;
    int _Top1Vtx;
    int _Top1Kaon;
    int _Top1KaonNumber;
    int _Top1KaonCharges[10];
    float _Top1KaonMomentum[10];
    int _Top1bTVCM;
    int _Top2bntracks;
    int _Top2bTVCM;
    int _UsedBTVCM;
    float _Top2bmomentum;
    float _Top2bdistance;
    float _Top2btag;
    float _Top2mass;
    int _Top2bcharge;
    float _Top2momentum;
    float _Top2costheta;
    float _Top2bcostheta;
    int _Top2Vtx;
    int _Top2Kaon;
    int _Top2KaonNumber;
    int _Top2KaonCharges[10];
    float _Top2KaonMomentum[10];
    int _Top2leptonCharge;
    int _Top2leptonCorrect;
    float _qCostheta[2];
    float _qCostheta1;
    float _qCostheta2;
    int _methodUsed;
    int _methodRefused;
    int _methodZero;
    int _methodCorrect;
    int _methodTaken[6];
    int _methodSameCharge[6];
    int _methodZeroCharge[6];
    int _method[6];
    float _chiHad1;
    float _chiTopMass1;
    float _chiTopE1;
    float _chiPbstar1;
    float _chiCosWb1;
    float _chiGammaT1;
    float _chiHad2;
    float _chiTopMass2;
    float _chiTopE2;
    float _chiPbstar2;
    float _chiCosWb2;
    float _chiGammaT2;

    int _MCBOscillation;
    int _MCBBarOscillation;
    float _MCTopBangle;
    //float _MCTopBarBangle;
    int _MCLeptonPDG;
    float _MCLeptonMomentum;
    float _MCLeptonCostheta;
    float _MCTopmomentum;
    float _MCTopmass;
    float _MCquarkAngle;
    float _MCTopcostheta;
    float _MCTopBarmomentum;
    float _MCTopBarmass;
    float _MCTopBarcostheta;
    float _MCTopcosWb;
    float _MCTopcosWt;
    float _qMCcostheta[2];
    float _MCMass;
    float _MCPDG;
    float _MCPt;
    float _qMCBcostheta[2];
    float _MCNeutrinoEnergy;
    float _totalEnergy;
    float _missedEnergy;
    float _gammaT;
		
    void Clear()  {
      _MCPDG = 0;
      _B1momentum = -1.0;
      _B2momentum = -1.0;
      _B1mass = -1.0;
      _B2mass = -1.0;
      _B2btag = -1.;
      _B1btag = -1.0;
      _B1costheta = -2.0;
      _B2costheta = -2.0;
      _B1charge = -5.0;
      _B2charge = -5.0;
      _B1truthAngle = -1.0;
      _MCPt = 0.0;
      _bbbarPt = 0.0;
      _bbbarP = 0.0;
      _MCLeptonMomentum = -1.0;
      _MCLeptonCostheta = -2.0;
      _MCLeptonPDG = 0;
      _MCTopmass = -1.0;
      _MCMass = -1.0;
      _MCTopBarmass = -1.0;
      _MCTopmomentum = -1.0;
      _MCTopBarmomentum = -1.0;
      _MCTopcostheta = -2.0;
      _MCTopBarcostheta = -2.0;
      _qMCcostheta[0] = -2.0;
      _qMCcostheta[1] = -2.0;
      _qMCBcostheta[0] = -2.0;
      _qMCBcostheta[1] = -2.0;
      _MCTopBangle = -1.0;
      _MCTopcosWb = -2.0;
      _Top1mass = -1.0;
      _W1mass = -1.0;
      _W2costheta = -2.0;
      _chiHad1 = -1.0;
      _chiHad2 = -1.0;
      _methodUsed = 0;
      _methodRefused = 0;
      _methodZero = 0;
      _methodCorrect = -1;
      _qCostheta[0] = -2.0;
      _qCostheta[1] = -2.0;
      _ZZMass1 = -1;
      _ZZMass2 = -1;
      for (unsigned int i = 0; i < 6; i++) {
	_methodTaken[i] = -1;
	_methodSameCharge[i] = -1;
	_methodZeroCharge[i] = -1;
	_method[i]=0;
      }
    }
  };


  struct StatsData_BBbar  {
  public:
	  
    float _mc_quark_E[2];
    float _mc_quark_px[2];
    float _mc_quark_py[2];
    float _mc_quark_pz[2];
    float _mc_quark_pt[2];
    float _mc_quark_m[2];
    float _mc_quark_pdg[2];
    float _mc_quark_charge[2];
    float _mc_qqbar_m;
    float _mc_qqbar_pt;
    int _mc_matching;

    float _mc_quark_ps_E[300];
    float _mc_quark_ps_px[300];
    float _mc_quark_ps_py[300];
    float _mc_quark_ps_pz[300];
    float _mc_quark_ps_pt[300];
    float _mc_quark_ps_m[300];
    float _mc_quark_ps_pdg[300];
    float _mc_quark_ps_charge[300];
    int _mc_quark_ps_n;

    int _MCBOscillation;
    int _MCBBarOscillation;

    float _maxenergy_photon_E;
    float _maxenergy_photon_costheta;

    float _y23;
    float _y12;

    float _jet_E[2];
    float _jet_px[2];
    float _jet_py[2];
    float _jet_pz[2];
    float _jet_m[2];
    float _jet_btag[2];

    int _jet_nvtx[2];
    int _jet_ntrack[2];
    int _jet_vtx_isprimary[2][10];
    int _jet_vtx_ntrack[2][10];
    float _jet_vtx_charge[2][10];

    float _jet_track_E[2][10][20];
    float _jet_track_px[2][10][20];
    float _jet_track_py[2][10][20];
    float _jet_track_pz[2][10][20];
    float _jet_track_p[2][10][20];
    float _jet_track_charge[2][10][20];
    int _jet_track_iskaon[2][10][20];
    float _jet_track_kaoncharge[2][10][20];
    float _jet_track_z0[2][10][20];
    float _jet_track_d0[2][10][20];
    float _jet_track_phi[2][10][20];
		
    void Clear()  {

      for (unsigned int i = 0; i < 300; i++) {
	_mc_quark_ps_E[i]=0;
	_mc_quark_ps_px[i]=0;
	_mc_quark_ps_py[i]=0;
	_mc_quark_ps_pz[i]=0;
	_mc_quark_ps_m[i]=0;
	_mc_quark_ps_pt[i]=0;
	_mc_quark_ps_pdg[i]=-1000;
	_mc_quark_ps_charge[i]=-1000;

      }

      _mc_quark_ps_n=0;

      for (unsigned int i = 0; i < 2; i++) {
	_mc_quark_E[i]=0;
	_mc_quark_px[i]=0;
	_mc_quark_py[i]=0;
	_mc_quark_pz[i]=0;
	_mc_quark_m[i]=0;
	_mc_quark_pt[i]=0;
	_mc_quark_pdg[i]=-1000;
	_mc_quark_charge[i]=-1000;

      }
      _mc_qqbar_m=0;
      _mc_qqbar_pt=0;
      _mc_matching=-1;

      _MCBOscillation=0;
      _MCBBarOscillation=0;


      _maxenergy_photon_E=0;
      _maxenergy_photon_costheta=0;
      _y12=0;
      _y23=0;

      for (unsigned int i = 0; i < 2; i++) {
	_jet_E[i]=0;
	_jet_px[i]=0;
	_jet_py[i]=0;
	_jet_pz[i]=0;
	_jet_m[i]=0;
	_jet_btag[i]=0;

	_jet_nvtx[i]=0;
	_jet_ntrack[i]=-1;

	for(int ivx=0; ivx<10; ivx++) {
	  _jet_vtx_isprimary[i][ivx]=-1;
	  _jet_vtx_ntrack[i][ivx]=-1;
	  _jet_vtx_charge[i][ivx]=-1000;

	  for(int itr=0; itr<20; itr++) {
	    _jet_track_E[i][ivx][itr]=0;
	    _jet_track_px[i][ivx][itr]=0;
	    _jet_track_py[i][ivx][itr]=0;
	    _jet_track_pz[i][ivx][itr]=0;
	    _jet_track_p[i][ivx][itr]=0;
	    _jet_track_charge[i][ivx][itr]=-1000;
	    _jet_track_iskaon[i][ivx][itr]=-1;
	    _jet_track_kaoncharge[i][ivx][itr]=-1000;
	    _jet_track_z0[i][ivx][itr]=-1000;
	    _jet_track_d0[i][ivx][itr]=-1000;
	    _jet_track_phi[i][ivx][itr]=-1000;
	  }
	  
	}
      }
      
    }//end clear
  };//end StatsData_BBbar

>>>>>>> QQbarAnalysisBranch2018
}
#endif
