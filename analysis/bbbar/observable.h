/////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Sep 12 18:21:58 2018 by ROOT version 6.11/01
// from TTree Stats/tree
// found on file: ../../ntuples/BBbar_20180911_7637.root
//////////////////////////////////////////////////////////

#ifndef observable_h
#define observable_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <TH1.h>
#include <vector>
#include <TString.h>
#include <TLegend.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include "../style/Style.C"
#include "../style/Labels.C"

//#include "fastjet/ClusterSequence.hh"
//using namespace fastjet;
using namespace std;

// Header file for the classes stored in the TTree if any.

class observable {
public :

  float btag1=0.8;
  float btag2=0.3;
  
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   Float_t         mc_quark_E[2];
   Float_t         mc_quark_px[2];
   Float_t         mc_quark_py[2];
   Float_t         mc_quark_pz[2];
   Float_t         mc_quark_pt[2];
   Float_t         mc_quark_m[2];
   Float_t         mc_quark_pdg[2];
   Float_t         mc_quark_charge[2];
   Float_t         mc_qqbar_m;
   Float_t         mc_qqbar_pt;
   Float_t         mc_quark_ps_E[300];
   Float_t         mc_quark_ps_px[300];
   Float_t         mc_quark_ps_py[300];
   Float_t         mc_quark_ps_pz[300];
   Float_t         mc_quark_ps_pt[300];
   Float_t         mc_quark_ps_m[300];
   Float_t         mc_quark_ps_pdg[300];
   Float_t         mc_quark_ps_charge[300];
   Int_t           mc_quark_ps_n;
   Int_t           mc_matching;
   Float_t         maxenergy_photon_E;
   Float_t         maxenergy_photon_costheta;
   Float_t         y23;
   Float_t         y12;
   Float_t         jet_E[2];
   Float_t         jet_px[2];
   Float_t         jet_py[2];
   Float_t         jet_pz[2];
   Float_t         jet_m[2];
   Float_t         jet_btag[2];
   Int_t           jet_nvtx[2];
   Int_t           jet_vtx_isprimary[2][10];
   Int_t           jet_ntrack[2];
   Int_t           jet_vtx_ntrack[2][10];
   Float_t         jet_vtx_charge[2][10];
   Float_t         jet_track_E[2][10][20];
   Float_t         jet_track_px[2][10][20];
   Float_t         jet_track_py[2][10][20];
   Float_t         jet_track_pz[2][10][20];
   Float_t         jet_track_p[2][10][20];
   Float_t         jet_track_charge[2][10][20];
   Int_t           jet_track_iskaon[2][10][20];
   Float_t         jet_track_kaoncharge[2][10][20];
   Float_t         jet_track_z0[2][10][20];
   Float_t         jet_track_d0[2][10][20];
   Float_t         jet_track_phi[2][10][20];
   Float_t         qMCcostheta[2];
   Float_t         MCMass;
   Float_t         MCPDG;
   Float_t         B1momentum;
   Float_t         B2momentum;
   Float_t         B1Jetmomentum;
   Float_t         B2Jetmomentum;
   Float_t         B1mass;
   Float_t         B2mass;
   Float_t         B1btag;
   Float_t         B2btag;
   Float_t         B1chargeBalance;
   Float_t         B2chargeBalance;
   Int_t           B1charge;
   Int_t           B2charge;
   Int_t           B1VtxTag;
   Int_t           B2VtxTag;
   Int_t           B1KaonTag;
   Int_t           B2KaonTag;
   Float_t         B1costheta;
   Float_t         B2costheta;
   Float_t         B1truthAngle;
   Float_t         bbbarAngle;
   Float_t         bbbarPt;
   Float_t         bbbarP;
   Float_t         bbbar4JetMass;
   Float_t         InvMass;
   Float_t         Sphericity;
   Float_t         Thrust;
   Float_t         B1Y;
   Float_t         B2Y;
   Float_t         ZZMass1;
   Float_t         ZZMass2;
   Float_t         maxPhotonEnergy;
   Float_t         kaonMomentum;
   Float_t         maxPhotonCostheta;
   Float_t         qCostheta[2];
   Float_t         qCostheta1;
   Float_t         qCostheta2;
   Int_t           methodUsed;
   Int_t           methodRefused;
   Int_t           methodZero;
   Int_t           methodCorrect;
   Int_t           methodSameCharge[3];   //[methodRefused]
   Int_t           methodZeroCharge[3];   //[methodZero]
   Int_t           methodTaken[3];   //[methodUsed]
   Int_t           method[6];

   // List of branches
   TBranch        *b_mc_quark_E;   //!
   TBranch        *b_mc_quark_px;   //!
   TBranch        *b_mc_quark_py;   //!
   TBranch        *b_mc_quark_pz;   //!
   TBranch        *b_mc_quark_pt;   //!
   TBranch        *b_mc_quark_m;   //!
   TBranch        *b_mc_quark_pdg;   //!
   TBranch        *b_mc_quark_charge;   //!
   TBranch        *b_mc_qqbar_m;   //!
   TBranch        *b_mc_qqbar_pt;   //!
   TBranch        *b_mc_quark_ps_E;   //!
   TBranch        *b_mc_quark_ps_px;   //!
   TBranch        *b_mc_quark_ps_py;   //!
   TBranch        *b_mc_quark_ps_pz;   //!
   TBranch        *b_mc_quark_ps_pt;   //!
   TBranch        *b_mc_quark_ps_m;   //!
   TBranch        *b_mc_quark_ps_pdg;   //!
   TBranch        *b_mc_quark_ps_charge;   //!
   TBranch        *b_mc_quark_ps_n;   //!
   TBranch        *b_mc_matching;   //!
   TBranch        *b_maxenergy_photon_E;   //!
   TBranch        *b_maxenergy_photon_costheta;   //!
   TBranch        *b_y23;   //!
   TBranch        *b_y12;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_px;   //!
   TBranch        *b_jet_py;   //!
   TBranch        *b_jet_pz;   //!
   TBranch        *b_jet_m;   //!
   TBranch        *b_jet_btag;   //!
   TBranch        *b_jet_nvtx;   //!
   TBranch        *b_jet_vtx_isprimary;   //!
   TBranch        *b_jet_ntrack;   //!
   TBranch        *b_jet_vtx_ntrack;   //!
   TBranch        *b_jet_vtx_charge;   //!
   TBranch        *b_jet_track_E;   //!
   TBranch        *b_jet_track_px;   //!
   TBranch        *b_jet_track_py;   //!
   TBranch        *b_jet_track_pz;   //!
   TBranch        *b_jet_track_p;   //!
   TBranch        *b_jet_track_charge;   //!
   TBranch        *b_jet_track_iskaon;   //!
   TBranch        *b_jet_track_kaoncharge;   //!
   TBranch        *b_jet_track_z0;   //!
   TBranch        *b_jet_track_d0;   //!
   TBranch        *b_jet_track_phi;   //!
   TBranch        *b_qMCcostheta;   //!
   TBranch        *b_MCMass;   //!
   TBranch        *b_MCPDG;   //!
   TBranch        *b_B1momentum;   //!
   TBranch        *b_B2momentum;   //!
   TBranch        *b_B1Jetmomentum;   //!
   TBranch        *b_B2Jetmomentum;   //!
   TBranch        *b_B1mass;   //!
   TBranch        *b_B2mass;   //!
   TBranch        *b_B1btag;   //!
   TBranch        *b_B2btag;   //!
   TBranch        *b_B1chargeBalance;   //!
   TBranch        *b_B2chargeBalance;   //!
   TBranch        *b_B1charge;   //!
   TBranch        *b_B2charge;   //!
   TBranch        *b_B1VtxTag;   //!
   TBranch        *b_B2VtxTag;   //!
   TBranch        *b_B1KaonTag;   //!
   TBranch        *b_B2KaonTag;   //!
   TBranch        *b_B1costheta;   //!
   TBranch        *b_B2costheta;   //!
   TBranch        *b_B1truthAngle;   //!
   TBranch        *b_bbbarAngle;   //!
   TBranch        *b_bbbarPt;   //!
   TBranch        *b_bbbarP;   //!
   TBranch        *b_bbbar4JetMass;   //!
   TBranch        *b_InvMass;   //!
   TBranch        *b_Sphericity;   //!
   TBranch        *b_Thrust;   //!
   TBranch        *b_B1Y;   //!
   TBranch        *b_B2Y;   //!
   TBranch        *b_ZZMass1;   //!
   TBranch        *b_ZZMass2;   //!
   TBranch        *b_maxPhotonEnergy;   //!
   TBranch        *b_kaonMomentum;   //!
   TBranch        *b_maxPhotonCostheta;   //!
   TBranch        *b_qCostheta;   //!
   TBranch        *b_qCostheta1;   //!
   TBranch        *b_qCostheta2;   //!
   TBranch        *b_methodUsed;   //!
   TBranch        *b_methodRefused;   //!
   TBranch        *b_methodZero;   //!
   TBranch        *b_methodCorrect;   //!
   TBranch        *b_methodSameCharge;   //!
   TBranch        *b_methodZeroCharge;   //!
   TBranch        *b_methodTaken;   //!
   TBranch        *b_method;   //!

  
   observable(TTree *tree=0);
   virtual ~observable();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     y23Analysis();
   //   virtual void     PSAnalysis();
   virtual void     Plot(bool reco_truth, int mode, int n);
   std::vector<TH1F*> Asymm_Bc(int n, bool reco_truth);
   std::vector<TH1F*> Asymm_Kc(int n, bool reco_truth);
   std::vector<TH1F*> Asymm_BcKc(int n, bool reco_truth);
   virtual float    ChargeBcJet(int ijet);
   virtual float    ChargeKcJet(int ijet);
   virtual float    CalculateP(int a, int r);
   virtual std::vector<float>    CalculateP(TH1F* a, TH1F* r);
   TH1F*    CorrectHistoDoubleTag(TH1F* histo, float p);
   TH1F*    CorrectHistoSingleTag(TH1F* histo, float p);

   TH1F*    CorrectHistoDoubleTag(TH1F* histo, std::vector<float> p);
   TH1F*    CorrectHistoDoubleTag(TH1F* histo, std::vector<float> p, std::vector<float> p2);
   TH1F*    CorrectHistoSingleTag(TH1F* histo, std::vector<float> p);

   TH1F*    CorrectHistoSingleTag(TH1F* histo, float p, float p2);
   TGraphErrors*    Ratio(TH1F* histo, TH1F* histo_ref);
   // TH1F*    CorrectHistoSingleTag(TH1F* histo, float p);
   virtual float    CalculateP_Bc();
   virtual bool     PreSelection();

   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);


};

#endif

#ifdef observable_cxx
observable::observable(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../ntuples/BBbar_20180911_7637.root");
     if (!f || !f->IsOpen()) {
       f = new TFile("../../ntuples/BBbar_20180911_7637.root");
      }
     f->GetObject("Stats",tree);
   }
   Init(tree);
}

observable::~observable()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t observable::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t observable::LoadTree(Long64_t entry)
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

void observable::Init(TTree *tree)
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

   fChain->SetBranchAddress("mc_quark_E", mc_quark_E, &b_mc_quark_E);
   fChain->SetBranchAddress("mc_quark_px", mc_quark_px, &b_mc_quark_px);
   fChain->SetBranchAddress("mc_quark_py", mc_quark_py, &b_mc_quark_py);
   fChain->SetBranchAddress("mc_quark_pz", mc_quark_pz, &b_mc_quark_pz);
   fChain->SetBranchAddress("mc_quark_pt", mc_quark_pt, &b_mc_quark_pt);
   fChain->SetBranchAddress("mc_quark_m", mc_quark_m, &b_mc_quark_m);
   fChain->SetBranchAddress("mc_quark_pdg", mc_quark_pdg, &b_mc_quark_pdg);
   fChain->SetBranchAddress("mc_quark_charge", mc_quark_charge, &b_mc_quark_charge);
   fChain->SetBranchAddress("mc_qqbar_m", &mc_qqbar_m, &b_mc_qqbar_m);
   fChain->SetBranchAddress("mc_qqbar_pt", &mc_qqbar_pt, &b_mc_qqbar_pt);
   fChain->SetBranchAddress("mc_quark_ps_E", mc_quark_ps_E, &b_mc_quark_ps_E);
   fChain->SetBranchAddress("mc_quark_ps_px", mc_quark_ps_px, &b_mc_quark_ps_px);
   fChain->SetBranchAddress("mc_quark_ps_py", mc_quark_ps_py, &b_mc_quark_ps_py);
   fChain->SetBranchAddress("mc_quark_ps_pz", mc_quark_ps_pz, &b_mc_quark_ps_pz);
   fChain->SetBranchAddress("mc_quark_ps_pt", mc_quark_ps_pt, &b_mc_quark_ps_pt);
   fChain->SetBranchAddress("mc_quark_ps_m", mc_quark_ps_m, &b_mc_quark_ps_m);
   fChain->SetBranchAddress("mc_quark_ps_pdg", mc_quark_ps_pdg, &b_mc_quark_ps_pdg);
   fChain->SetBranchAddress("mc_quark_ps_charge", mc_quark_ps_charge, &b_mc_quark_ps_charge);
   fChain->SetBranchAddress("mc_quark_ps_n", &mc_quark_ps_n, &b_mc_quark_ps_n);
   fChain->SetBranchAddress("mc_matching", &mc_matching, &b_mc_matching);
   fChain->SetBranchAddress("maxenergy_photon_E", &maxenergy_photon_E, &b_maxenergy_photon_E);
   fChain->SetBranchAddress("maxenergy_photon_costheta", &maxenergy_photon_costheta, &b_maxenergy_photon_costheta);
   fChain->SetBranchAddress("y23", &y23, &b_y23);
   fChain->SetBranchAddress("y12", &y12, &b_y12);
   fChain->SetBranchAddress("jet_E", jet_E, &b_jet_E);
   fChain->SetBranchAddress("jet_px", jet_px, &b_jet_px);
   fChain->SetBranchAddress("jet_py", jet_py, &b_jet_py);
   fChain->SetBranchAddress("jet_pz", jet_pz, &b_jet_pz);
   fChain->SetBranchAddress("jet_m", jet_m, &b_jet_m);
   fChain->SetBranchAddress("jet_btag", jet_btag, &b_jet_btag);
   fChain->SetBranchAddress("jet_nvtx", jet_nvtx, &b_jet_nvtx);
   fChain->SetBranchAddress("jet_vtx_isprimary", jet_vtx_isprimary, &b_jet_vtx_isprimary);
   fChain->SetBranchAddress("jet_ntrack", jet_ntrack, &b_jet_ntrack);
   fChain->SetBranchAddress("jet_vtx_ntrack", jet_vtx_ntrack, &b_jet_vtx_ntrack);
   fChain->SetBranchAddress("jet_vtx_charge", jet_vtx_charge, &b_jet_vtx_charge);
   fChain->SetBranchAddress("jet_track_E", jet_track_E, &b_jet_track_E);
   fChain->SetBranchAddress("jet_track_px", jet_track_px, &b_jet_track_px);
   fChain->SetBranchAddress("jet_track_py", jet_track_py, &b_jet_track_py);
   fChain->SetBranchAddress("jet_track_pz", jet_track_pz, &b_jet_track_pz);
   fChain->SetBranchAddress("jet_track_p", jet_track_p, &b_jet_track_p);
   fChain->SetBranchAddress("jet_track_charge", jet_track_charge, &b_jet_track_charge);
   fChain->SetBranchAddress("jet_track_iskaon", jet_track_iskaon, &b_jet_track_iskaon);
   fChain->SetBranchAddress("jet_track_kaoncharge", jet_track_kaoncharge, &b_jet_track_kaoncharge);
   fChain->SetBranchAddress("jet_track_z0", jet_track_z0, &b_jet_track_z0);
   fChain->SetBranchAddress("jet_track_d0", jet_track_d0, &b_jet_track_d0);
   fChain->SetBranchAddress("jet_track_phi", jet_track_phi, &b_jet_track_phi);
   fChain->SetBranchAddress("qMCcostheta", qMCcostheta, &b_qMCcostheta);
   fChain->SetBranchAddress("MCMass", &MCMass, &b_MCMass);
   fChain->SetBranchAddress("MCPDG", &MCPDG, &b_MCPDG);
   fChain->SetBranchAddress("B1momentum", &B1momentum, &b_B1momentum);
   fChain->SetBranchAddress("B2momentum", &B2momentum, &b_B2momentum);
   fChain->SetBranchAddress("B1Jetmomentum", &B1Jetmomentum, &b_B1Jetmomentum);
   fChain->SetBranchAddress("B2Jetmomentum", &B2Jetmomentum, &b_B2Jetmomentum);
   fChain->SetBranchAddress("B1mass", &B1mass, &b_B1mass);
   fChain->SetBranchAddress("B2mass", &B2mass, &b_B2mass);
   fChain->SetBranchAddress("B1btag", &B1btag, &b_B1btag);
   fChain->SetBranchAddress("B2btag", &B2btag, &b_B2btag);
   fChain->SetBranchAddress("B1chargeBalance", &B1chargeBalance, &b_B1chargeBalance);
   fChain->SetBranchAddress("B2chargeBalance", &B2chargeBalance, &b_B2chargeBalance);
   fChain->SetBranchAddress("B1charge", &B1charge, &b_B1charge);
   fChain->SetBranchAddress("B2charge", &B2charge, &b_B2charge);
   fChain->SetBranchAddress("B1VtxTag", &B1VtxTag, &b_B1VtxTag);
   fChain->SetBranchAddress("B2VtxTag", &B2VtxTag, &b_B2VtxTag);
   fChain->SetBranchAddress("B1KaonTag", &B1KaonTag, &b_B1KaonTag);
   fChain->SetBranchAddress("B2KaonTag", &B2KaonTag, &b_B2KaonTag);
   fChain->SetBranchAddress("B1costheta", &B1costheta, &b_B1costheta);
   fChain->SetBranchAddress("B2costheta", &B2costheta, &b_B2costheta);
   fChain->SetBranchAddress("B1truthAngle", &B1truthAngle, &b_B1truthAngle);
   fChain->SetBranchAddress("bbbarAngle", &bbbarAngle, &b_bbbarAngle);
   fChain->SetBranchAddress("bbbarPt", &bbbarPt, &b_bbbarPt);
   fChain->SetBranchAddress("bbbarP", &bbbarP, &b_bbbarP);
   fChain->SetBranchAddress("bbbar4JetMass", &bbbar4JetMass, &b_bbbar4JetMass);
   fChain->SetBranchAddress("InvMass", &InvMass, &b_InvMass);
   fChain->SetBranchAddress("Sphericity", &Sphericity, &b_Sphericity);
   fChain->SetBranchAddress("Thrust", &Thrust, &b_Thrust);
   fChain->SetBranchAddress("B1Y", &B1Y, &b_B1Y);
   fChain->SetBranchAddress("B2Y", &B2Y, &b_B2Y);
   fChain->SetBranchAddress("ZZMass1", &ZZMass1, &b_ZZMass1);
   fChain->SetBranchAddress("ZZMass2", &ZZMass2, &b_ZZMass2);
   fChain->SetBranchAddress("maxPhotonEnergy", &maxPhotonEnergy, &b_maxPhotonEnergy);
   fChain->SetBranchAddress("kaonMomentum", &kaonMomentum, &b_kaonMomentum);
   fChain->SetBranchAddress("maxPhotonCostheta", &maxPhotonCostheta, &b_maxPhotonCostheta);
   fChain->SetBranchAddress("qCostheta", qCostheta, &b_qCostheta);
   fChain->SetBranchAddress("qCostheta1", &qCostheta1, &b_qCostheta1);
   fChain->SetBranchAddress("qCostheta2", &qCostheta2, &b_qCostheta2);
   fChain->SetBranchAddress("methodUsed", &methodUsed, &b_methodUsed);
   fChain->SetBranchAddress("methodRefused", &methodRefused, &b_methodRefused);
   fChain->SetBranchAddress("methodZero", &methodZero, &b_methodZero);
   fChain->SetBranchAddress("methodCorrect", &methodCorrect, &b_methodCorrect);
   fChain->SetBranchAddress("methodSameCharge", methodSameCharge, &b_methodSameCharge);
   fChain->SetBranchAddress("methodZeroCharge", methodZeroCharge, &b_methodZeroCharge);
   fChain->SetBranchAddress("methodTaken", methodTaken, &b_methodTaken);
   fChain->SetBranchAddress("method", method, &b_method);
   Notify();
}

Bool_t observable::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void observable::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t observable::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef observable_cxx
