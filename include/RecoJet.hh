#include "MathOperator.hh"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <EVENT/ReconstructedParticle.h>
#include <IMPL/ReconstructedParticleImpl.h>
#include <EVENT/Vertex.h>

#ifndef _RecoJet_hh
#define _RecoJet_hh
namespace QQbarProcessor 
{
	struct JetCharge
	{
		JetCharge()
		{
			ByTVCM = NULL;
			ByTrackCount = NULL;
			ByLepton = NULL;
		}
		~JetCharge()
		{
			delete ByTVCM;
			delete ByTrackCount;
			delete ByLepton;
		}

		int * ByTVCM;
		int * ByTrackCount;
		int * ByLepton;
	};
	class RecoJet : public IMPL::ReconstructedParticleImpl
	{
		public:
			//
			//	Constants
			//

			//
			//	Constructors
			//
			RecoJet (EVENT::ReconstructedParticle * rawjet, float btag, float ctag, int number);// : IMPL::ReconstructedParticleImpl(rawjet);
			RecoJet ();
			virtual ~RecoJet () {};
			//
			//	Methods
			//
			JetCharge & GetComputedCharge();
			const float GetBTag() const;
			const float GetCTag() const;
			void SetBTag(float value);
			void SetCTag(float value);
			void SetRecoVertices(std::vector<  EVENT::Vertex * > * vertices);
			std::vector<  EVENT::Vertex * > * GetRecoVertices();
			int GetNumberOfVertices();
			int GetNumberOfVertexParticles();
			float GetHadronCharge(bool weight = false);
			float GetHadronMomentum();
			float GetHadronMass();
			EVENT::ReconstructedParticle * GetRawRecoJet();
			float GetCostheta();
			float GetMinHadronDistance();
			float GetMaxHadronDistance();
			const double * GetMomentum();
			int GetMCPDG();
			void SetMCPDG(int pdg);


			const float __GetMCCharge() const;
			void __SetMCCharge(float charge);
			const int __GetMCNtracks() const;
			void __SetMCNtracks(int n);
			const int __GetMCOscillation() const;
			void __SetMCOscillation(int n);

		protected:
			//
			//	Data
			//
			float myBTag;
			float myCTag;
			int myNumber;
			int myMCPDG;
			float myMCCharge;
			int myMCNtracks;
			int myMCOscillation;
			JetCharge myComputedCharge;
			EVENT::ReconstructedParticle * myRawRecoJet;
			std::vector<  EVENT::Vertex * > * myRecoVertices;
			//
			//	Private methods
			//
	};
}
#endif
