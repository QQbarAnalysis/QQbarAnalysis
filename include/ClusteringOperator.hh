#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <EVENT/ReconstructedParticle.h>
#include "MathOperator.hh"
#include "TopQuark.hh"
#include "RecoJet.hh"
#ifndef _ClusteringOperator_hh
#define _ClusteringOperator_hh
namespace QQbarProcessor 
{
	class ClusteringOperator 
	{
		public:
		//
		//	Constants
		//
	
		//
		//	Constructors
		//
			ClusteringOperator ();
			virtual ~ClusteringOperator () {};
		//
		//	Methods
		//
			float ClusterizeJet(RecoJet * jet);
			float ComputeY( EVENT::ReconstructedParticle * p1,  EVENT::ReconstructedParticle * p2, float Evis);
		private:
		//
		//	Data
		//
			std::vector< EVENT::ReconstructedParticle * > toDelete;
			float myLastYvalue;
		//
		//	Private methods
		//
	};
	bool sortByP(EVENT::ReconstructedParticle * p1,  EVENT::ReconstructedParticle * p2);
} /* TTBarAnalysis */
#endif
