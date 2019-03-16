#ifndef _SummaryData_hh
#define _SummaryData_hh
namespace QQbarProcessor 
{
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
			for (unsigned int i = 0; i < 6; i++) 
			{
				_methodTaken[i] = -1;
				_methodSameCharge[i] = -1;
				_methodZeroCharge[i] = -1;
			}
		}
	};
}
#endif
