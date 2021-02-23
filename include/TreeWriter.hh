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
    
    void InitializeStatsQQbarTree(TTree * tree, StatsData_QQbar & data);
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
