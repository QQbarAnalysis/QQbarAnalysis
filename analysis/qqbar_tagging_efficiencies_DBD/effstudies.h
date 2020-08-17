/////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Sep 12 18:21:58 2018 by ROOT version 6.11/01
// from TTree Stats/tree
// found on file: ../../ntuples/BBbar_20180911_7637.root
//////////////////////////////////////////////////////////

#ifndef effstudies_h
#define effstudies_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <TH1.h>
#include <vector>
#include <TString.h>
#include <TRandom.h>
#include <TLegend.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include "../style/Style.C"
#include "../style/Labels.C"
#include "TSystemFile.h"

using namespace std;

// Header file for the classes stored in the TTree if any.

class effstudies {
public :

  float btag1=0.8;
  float btag2=0.8;
  float ctag1=0.875;
  float ctag2=0.875;
  
  Int_t nbins=40;
  TString process="bbbar";
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain


  Float_t         mc_quark_E[2];
   Float_t         mc_quark_px[2];
   Float_t         mc_quark_py[2];
   Float_t         mc_quark_pz[2];
   Float_t         mc_quark_pt[2];
   Float_t         mc_quark_m[2];
   Float_t         mc_quark_pdg[2];
   Float_t         mc_quark_charge[2];
   Float_t         mc_ISR_E[2];
   Float_t         mc_ISR_px[2];
   Float_t         mc_ISR_py[2];
   Float_t         mc_ISR_pz[2];
   Float_t         mc_ISR_pt[2];
   Float_t         mc_ISR_m[2];
   Float_t         mc_ISR_pdg[2];
   Float_t         mc_ISR_charge[2];
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
   Float_t         mc_quark_ps_y23;
   Float_t         mc_quark_ps_jet_E[2];
   Float_t         mc_quark_ps_jet_px[2];
   Float_t         mc_quark_ps_jet_py[2];
   Float_t         mc_quark_ps_jet_pz[2];
   Int_t           mc_quark_ps_jet_nparticles[2];
   Int_t           MCBOscillation;
   Int_t           MCBBarOscillation;
   Int_t           mc_matching;
   Float_t         maxenergy_photon_E;
   Float_t         maxenergy_photon_costheta;
   Float_t         jet_E[2];
   Float_t         jet_px[2];
   Float_t         jet_py[2];
   Float_t         jet_pz[2];
   Float_t         jet_m[2];
   Float_t         jet_btag[2];
   Float_t         jet_ctag[2];
   Float_t         y23;
   Float_t         y12;
   Float_t         d23;
   Float_t         d12;
   Float_t         oblateness;
   Float_t         aplanarity;
   Float_t         major_thrust_value;
   Float_t         major_thrust_axis[3];
   Float_t         minor_thrust_value;
   Float_t         minor_thrust_axis[3];
   Float_t         principle_thrust_value;
   Float_t         principle_thrust_axis[3];
   Float_t         sphericity;
   Float_t         sphericity_tensor[3];
   Float_t         jet_pfo_E[2][100];
   Float_t         jet_pfo_px[2][100];
   Float_t         jet_pfo_py[2][100];
   Float_t         jet_pfo_pz[2][100];
   Float_t         jet_pfo_m[2][100];
   Int_t           jet_pfo_type[2][100];
   Int_t           jet_pfo_charge[2][100];
   Int_t           jet_pfo_n[2];
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
   Float_t         jet_track_dedx[2][10][20];
   Int_t           jet_track_iskaon[2][10][20];
   Int_t           jet_track_iskaoncheat[2][10][20];
   Int_t           jet_track_pdg[2][10][20];
   Float_t         jet_track_z0[2][10][20];
   Float_t         jet_track_d0[2][10][20];
   Float_t         jet_track_phi[2][10][20];

   // List of branches
   TBranch        *b_mc_quark_E;   //!
   TBranch        *b_mc_quark_px;   //!
   TBranch        *b_mc_quark_py;   //!
   TBranch        *b_mc_quark_pz;   //!
   TBranch        *b_mc_quark_pt;   //!
   TBranch        *b_mc_quark_m;   //!
   TBranch        *b_mc_quark_pdg;   //!
   TBranch        *b_mc_quark_charge;   //!
   TBranch        *b_mc_ISR_E;   //!
   TBranch        *b_mc_ISR_px;   //!
   TBranch        *b_mc_ISR_py;   //!
   TBranch        *b_mc_ISR_pz;   //!
   TBranch        *b_mc_ISR_pt;   //!
   TBranch        *b_mc_ISR_m;   //!
   TBranch        *b_mc_ISR_pdg;   //!
   TBranch        *b_mc_ISR_charge;   //!
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
   TBranch        *b_mc_quark_ps_y23;   //!
   TBranch        *b_mc_quark_ps_jet_E;
   TBranch        *b_mc_quark_ps_jet_px;
   TBranch        *b_mc_quark_ps_jet_py;
   TBranch        *b_mc_quark_ps_jet_pz;
   TBranch        *b_mc_quark_ps_nparticles;
   TBranch        *b_MCBOscillation;   //!
   TBranch        *b_MCBBarOscillation;   //!
   TBranch        *b_mc_matching;   //!
   TBranch        *b_maxenergy_photon_E;   //!
   TBranch        *b_maxenergy_photon_costheta;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_px;   //!
   TBranch        *b_jet_py;   //!
   TBranch        *b_jet_pz;   //!
   TBranch        *b_jet_m;   //!
   TBranch        *b_jet_btag;   //!
   TBranch        *b_jet_ctag;   //!
   TBranch        *b_y23;   //!
   TBranch        *b_y12;   //!
   TBranch        *b_d23;   //!
   TBranch        *b_d12;   //!
   TBranch        *b_oblateness;   //!
   TBranch        *b_aplanarity;   //!
   TBranch        *b_major_thrust_value;   //!
   TBranch        *b_major_thrust_axis;   //!
   TBranch        *b_minor_thrust_value;   //!
   TBranch        *b_minor_thrust_axis;   //!
   TBranch        *b_principle_thrust_value;   //!
   TBranch        *b_principle_thrust_axis;   //!
   TBranch        *b_sphericity;   //!
   TBranch        *b_sphericity_tensor;   //!
   TBranch        *b_jet_pfo_E;   //!
   TBranch        *b_jet_pfo_px;   //!
   TBranch        *b_jet_pfo_py;   //!
   TBranch        *b_jet_pfo_pz;   //!
   TBranch        *b_jet_pfo_m;   //!
   TBranch        *b_jet_pfo_type;   //!
   TBranch        *b_jet_pfo_charge;   //!
   TBranch        *b_jet_pfo_n;   //!
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
   TBranch        *b_jet_track_dedx;   //!
   TBranch        *b_jet_track_iskaon;   //!
   TBranch        *b_jet_track_iskaoncheat;   //!
   TBranch        *b_jet_track_pdg;   //!
   TBranch        *b_jet_track_z0;   //!
   TBranch        *b_jet_track_d0;   //!
   TBranch        *b_jet_track_phi;   //!


   effstudies(TString tree_s);
   effstudies(TList *f=0);
   virtual ~effstudies();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   //initialize
   virtual void     Init(TTree *tree);

   //analysis
   virtual void     eff_flavour(int n, TString polarization);
   //   virtual void     Analysis_rho_btag(int n, TString polarization, int quark, int rad);
   //virtual void     Analysis_rho_ctag(int n, TString polarization, int quark, int rad);
   virtual void     Analysis_rho_charge(int n, TString polarization, int quark, int rad);
   virtual void     Analysis_rho_ccharge(int n, TString polarization, int quark, int rad);
   // virtual void     Analysis_efficiency(int n, TString polarization, int zpole);
   virtual void     QuarkTaggingTests(int, TString);
   //tools
   virtual bool     PreSelection(int, float);
   virtual float    ChargeBcJet(int ijet);
   virtual float    ChargeKcJet(int ijet);
   virtual std::vector<float>    Error(double,double,double,double);
   virtual std::vector<float>    ErrorLEP(double,double,double,double);

   
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   
   float getModule(vector< float > & v)   {
     float module = 0.0;
     for (unsigned int i = 0; i < v.size(); i++) module += v[i]*v[i];
     module = sqrt(module);
     return module;
   }
   
   std::vector< float > getDirection(vector<float> & vectorPoint) {
     vector< float > vector1;
     float module = getModule(vectorPoint);
     for (int i = 0; i < 3; i++) vector1.push_back( vectorPoint[i]/module);
     return vector1;
   }
   
   std::vector< float > getAngles(std::vector< float > & direction) {
       vector< float > result;
       float epsilon = 0.00001;
       float semi = 1.5708;
       float pi = 2*semi;
       float phi = 0.0;
       if (direction[0] > 0.0 && direction[1] > 0.0 - epsilon) 
	   phi = atan(direction[1] / direction[0]); //(direction[0] < epsilon && direction[0] > 0.0 - epsilon)?
       if (direction[0] < 0.0 && direction[1] > 0.0) 
	   phi = semi - atan(direction[1] / direction[0]) ;
       if (direction[0] < 0.0 && direction[1] < 0.0 + epsilon) 
	   phi =  atan(direction[1] / direction[0]) + pi;
       if (direction[0] > 0.0 && direction[1] < 0.0 - epsilon) 
	   phi = semi - atan(direction[1] / direction[0]) + pi;
       if (direction[1] > 0.0 && direction[0] < 0.0 + epsilon && direction[0] > 0.0 -  epsilon) 
	   phi = semi;
       if (direction[1] < 0.0 && direction[0] < 0.0 + epsilon && direction[0] > 0.0 -  epsilon) 
	   phi = pi + semi;

       float teta = acos(direction[2]);
       result.push_back(phi);
       result.push_back(teta);
       return result;
   }
   
   float GetCostheta(std::vector<float> & vectorPoint){
     float costheta1 =  -2.0;
     std::vector< float > d1= getDirection(vectorPoint);
     costheta1 =  std::cos( getAngles(d1).at(1) );
     return costheta1;
   }
   float GetSinacol(TVector3 v1, TVector3 v2){
     float sinacol =  -2.0;
     TVector3 v= v1.Cross(v2);
     sinacol = (v.Mag()/(v1.Mag()*v2.Mag()));// * v2.Mag()/(v1+v2).Mag();
     return sinacol;
   }
   
   
 private:   


};

#endif
#ifdef effstudies_cxx
effstudies::effstudies(TString tree_s) : fChain(0) 
{
  
  TFile *f = new TFile(tree_s);
  TTree *tree = (TTree*)f->Get("Stats");
  //  tree->Print();
  Init(tree);
  
}

effstudies::effstudies(TList *f) : fChain(0) 
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


effstudies::~effstudies()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}


Int_t effstudies::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t effstudies::LoadTree(Long64_t entry)
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

void effstudies::Init(TTree *tree)
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
   fChain->SetBranchAddress("mc_ISR_E", mc_ISR_E, &b_mc_ISR_E);
   fChain->SetBranchAddress("mc_ISR_px", mc_ISR_px, &b_mc_ISR_px);
   fChain->SetBranchAddress("mc_ISR_py", mc_ISR_py, &b_mc_ISR_py);
   fChain->SetBranchAddress("mc_ISR_pz", mc_ISR_pz, &b_mc_ISR_pz);
   fChain->SetBranchAddress("mc_ISR_pt", mc_ISR_pt, &b_mc_ISR_pt);
   fChain->SetBranchAddress("mc_ISR_m", mc_ISR_m, &b_mc_ISR_m);
   fChain->SetBranchAddress("mc_ISR_pdg", mc_ISR_pdg, &b_mc_ISR_pdg);
   fChain->SetBranchAddress("mc_ISR_charge", mc_ISR_charge, &b_mc_ISR_charge);
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
   fChain->SetBranchAddress("mc_quark_ps_y23", &mc_quark_ps_y23, &b_mc_quark_ps_y23);
   fChain->SetBranchAddress("mc_quark_ps_jet_E", mc_quark_ps_jet_E, &b_mc_quark_ps_jet_E);
   fChain->SetBranchAddress("mc_quark_ps_jet_px", mc_quark_ps_jet_px, &b_mc_quark_ps_jet_px);
   fChain->SetBranchAddress("mc_quark_ps_jet_py", mc_quark_ps_jet_py, &b_mc_quark_ps_jet_py);
   fChain->SetBranchAddress("mc_quark_ps_jet_pz", mc_quark_ps_jet_pz, &b_mc_quark_ps_jet_pz);
   fChain->SetBranchAddress("mc_quark_ps_jet_nparticles", mc_quark_ps_jet_nparticles, &b_mc_quark_ps_nparticles);
   fChain->SetBranchAddress("MCBOscillation", &MCBOscillation, &b_MCBOscillation);
   fChain->SetBranchAddress("MCBBarOscillation", &MCBBarOscillation, &b_MCBBarOscillation);
   fChain->SetBranchAddress("mc_matching", &mc_matching, &b_mc_matching);
   fChain->SetBranchAddress("maxenergy_photon_E", &maxenergy_photon_E, &b_maxenergy_photon_E);
   fChain->SetBranchAddress("maxenergy_photon_costheta", &maxenergy_photon_costheta, &b_maxenergy_photon_costheta);
   fChain->SetBranchAddress("jet_E", jet_E, &b_jet_E);
   fChain->SetBranchAddress("jet_px", jet_px, &b_jet_px);
   fChain->SetBranchAddress("jet_py", jet_py, &b_jet_py);
   fChain->SetBranchAddress("jet_pz", jet_pz, &b_jet_pz);
   fChain->SetBranchAddress("jet_m", jet_m, &b_jet_m);
   fChain->SetBranchAddress("jet_btag", jet_btag, &b_jet_btag);
   fChain->SetBranchAddress("jet_ctag", jet_ctag, &b_jet_ctag);
   fChain->SetBranchAddress("y23", &y23, &b_y23);
   fChain->SetBranchAddress("y12", &y12, &b_y12);
   fChain->SetBranchAddress("d23", &d23, &b_d23);
   fChain->SetBranchAddress("d12", &d12, &b_d12);
   fChain->SetBranchAddress("oblateness", &oblateness, &b_oblateness);
   fChain->SetBranchAddress("aplanarity", &aplanarity, &b_aplanarity);
   fChain->SetBranchAddress("major_thrust_value", &major_thrust_value, &b_major_thrust_value);
   fChain->SetBranchAddress("major_thrust_axis", major_thrust_axis, &b_major_thrust_axis);
   fChain->SetBranchAddress("minor_thrust_value", &minor_thrust_value, &b_minor_thrust_value);
   fChain->SetBranchAddress("minor_thrust_axis", minor_thrust_axis, &b_minor_thrust_axis);
   fChain->SetBranchAddress("principle_thrust_value", &principle_thrust_value, &b_principle_thrust_value);
   fChain->SetBranchAddress("principle_thrust_axis", principle_thrust_axis, &b_principle_thrust_axis);
   fChain->SetBranchAddress("sphericity", &sphericity, &b_sphericity);
   fChain->SetBranchAddress("sphericity_tensor", sphericity_tensor, &b_sphericity_tensor);
   fChain->SetBranchAddress("jet_pfo_E", jet_pfo_E, &b_jet_pfo_E);
   fChain->SetBranchAddress("jet_pfo_px", jet_pfo_px, &b_jet_pfo_px);
   fChain->SetBranchAddress("jet_pfo_py", jet_pfo_py, &b_jet_pfo_py);
   fChain->SetBranchAddress("jet_pfo_pz", jet_pfo_pz, &b_jet_pfo_pz);
   fChain->SetBranchAddress("jet_pfo_m", jet_pfo_m, &b_jet_pfo_m);
   fChain->SetBranchAddress("jet_pfo_type", jet_pfo_type, &b_jet_pfo_type);
   fChain->SetBranchAddress("jet_pfo_charge", jet_pfo_charge, &b_jet_pfo_charge);
   fChain->SetBranchAddress("jet_pfo_n", jet_pfo_n, &b_jet_pfo_n);
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
   fChain->SetBranchAddress("jet_track_dedx", jet_track_dedx, &b_jet_track_dedx);
   fChain->SetBranchAddress("jet_track_iskaon", jet_track_iskaon, &b_jet_track_iskaon);
   fChain->SetBranchAddress("jet_track_iskaoncheat", jet_track_iskaoncheat, &b_jet_track_iskaoncheat);
   fChain->SetBranchAddress("jet_track_pdg", jet_track_pdg, &b_jet_track_pdg);
   fChain->SetBranchAddress("jet_track_z0", jet_track_z0, &b_jet_track_z0);
   fChain->SetBranchAddress("jet_track_d0", jet_track_d0, &b_jet_track_d0);
   fChain->SetBranchAddress("jet_track_phi", jet_track_phi, &b_jet_track_phi);
   Notify();
   
   
}

Bool_t effstudies::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void effstudies::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t effstudies::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef effstudies_cxx
