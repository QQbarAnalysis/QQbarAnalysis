
#include "MathOperator.hh"
#include "RecoJet.hh"
#include <stdio.h>
#include <EVENT/ReconstructedParticle.h>
#include <IMPL/ReconstructedParticleImpl.h>
#ifndef Top_Quark_h
#define Top_Quark_h 1
namespace QQbarProcessor 
{
	class TopQuark : public RecoJet
	{
		public:
		//
		//	Constants
		//
	
		//
		//	Constructors
		//
			TopQuark (RecoJet * b, EVENT::ReconstructedParticle * w);
			TopQuark (RecoJet * b);
			virtual ~TopQuark () 
			{
				//delete myB;
			};
		//
		//	Methods
		//
			RecoJet * GetB();
			EVENT::ReconstructedParticle * GetW();
			float getMass();
			int GetResultTVCM();
			void SetResultTVCM(int used = 0);
			bool IsHadronic();
		private:
		//
		//	Data
		//
			RecoJet * myB;
			EVENT::ReconstructedParticle * myW;
			int myResultTVCM;
		//
		//	Private methods
		//
	};
} /* TTbarAnalisys */
#endif
