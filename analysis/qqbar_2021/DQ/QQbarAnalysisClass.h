//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun  9 18:55:11 2021 by ROOT version 6.18/04
// from TTree Stats/tree
// found on file: ../../../scripts/2021_LCFIandQQbar_dEdxCorrection/15161_000.root
//////////////////////////////////////////////////////////

#ifndef QQbarAnalysisClass_h
#define QQbarAnalysisClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <TH1.h>
#include <vector>
#include <TString.h>
#include <TLegend.h>
#include <TH2.h>
#include <TGraphErrors.h>
#include "TSystemFile.h"
#include "TLorentzVector.h"
#include "DQTools.h"
#include "../common/methods.h"
#include "../common/PreSelection.h"
// Header file for the classes stored in the TTree if any.

class QQbarAnalysisClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain



  QQbarAnalysisClass(TString tree_s);
  QQbarAnalysisClass(TList *f=0);
   virtual ~QQbarAnalysisClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);

  //analysis
  virtual void     DQChecks(int , float , TString );
  
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);

 private: 


};

#endif

#ifdef QQbarAnalysisClass_cxx

QQbarAnalysisClass::QQbarAnalysisClass(TString tree_s) : fChain(0) 
{
  
  TFile *f = new TFile(tree_s);
  TTree *tree = (TTree*)f->Get("Stats");
  //  tree->Print();
  Init(tree);
  
}

QQbarAnalysisClass::QQbarAnalysisClass(TList *f) : fChain(0) 
{
  // if parameter tree is not specified (or zero), use a list of of files provided as input

  TIter next(f);
  TSystemFile *file;
  TString fname;
  while((file = (TSystemFile*)next())){
    fname = file->GetName();
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(fname);
    TTree *tree=0;
    f->GetObject("Stats",tree);
    Init(tree);
  }
}


QQbarAnalysisClass::~QQbarAnalysisClass()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}


Int_t QQbarAnalysisClass::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t QQbarAnalysisClass::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}



void QQbarAnalysisClass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);
   SetBranchAddressFunction(fChain);
   
   Notify();
}

Bool_t QQbarAnalysisClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void QQbarAnalysisClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t QQbarAnalysisClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef QQbarAnalysisClass_cxx
