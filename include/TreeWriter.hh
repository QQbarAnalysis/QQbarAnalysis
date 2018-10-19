#include <iostream>
#include <vector>
#include <string>
#include <TFile.h>
#include <TTree.h>
#include "TreeStructures.hh"
#ifndef _TreeWriter_hh
#define _TreeWriter_hh

namespace QQbarProcessor 
{
  class TreeWriter 
  {
  public:
    //
    //	Constants
    //
    
    //
    //	Constructors
    //
    TreeWriter ();
    virtual ~TreeWriter () {};
    //
    //	Methods
    //
    
    void InitializeSummaryTree(TTree * tree, SummaryData & data);
    void InitializeStatsTree(TTree * tree, StatsData & data);
    void InitializeStatsBBbarTree(TTree * tree, StatsData_BBbar & data);
    
    void InitializeStatsHadronicTree(TTree * tree, StatsData & data);
  private:
    //
    //	Data
    //
    
    //
    //	Private methods
    //
  };
} /* TTBarAnalysis */
#endif
