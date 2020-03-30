// A. Irles
// irles @ lal.in2p3.fr
// 30 March 2020

#define observable_cxx
#include "observable.h"
#include "TPad.h"

void observable::AnalysisY23(int n_entries=-1)
{

  TH1F * h1_y23_ps = new TH1F("h1_y23_ps","h1_y23_ps",100,0,0.05);
  TH1F * h1_y23_reco = new TH1F("h1_y23_reco","h1_y23_reco",100,0,0.05);
  TH2F * h2_y23 = new TH2F("h2_y23","h2_y23",100,0,0.05,100,0,0.05);

  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    double bbmass= sqrt(pow(mc_quark_E[0]+mc_quark_E[1],2)-pow(mc_quark_px[0]+mc_quark_px[1],2)-pow(mc_quark_py[0]+mc_quark_py[1],2)-pow(mc_quark_pz[0]+mc_quark_pz[1],2));

    
    //for the moment, we restrict the analysis to the bb events without radaitive return
    if(fabs(mc_quark_pdg[0])==5 && bbmass>200) {

      //as the angle direction is wrong using the neutral PFOs (issue seen for the DBD)
      // we use the angle defined by the secondary tracks
      // we use this to have the same selection as the Rb/Afb analysis
      float ptrack_x=0;
      float ptrack_y=0;
      float ptrack_z=0;
      
      for(int ivtx=0; ivtx<jet_nvtx[0]; ivtx++) {
	for(int itrack=0; itrack<jet_vtx_ntrack[0][ivtx]; itrack++) {
	  ptrack_x+=jet_track_px[0][ivtx][itrack];
	  ptrack_y+=jet_track_py[0][ivtx][itrack];
	  ptrack_z+=jet_track_pz[0][ivtx][itrack];
	}
      }
      
      for(int ivtx=0; ivtx<jet_nvtx[1]; ivtx++) {
	for(int itrack=0; itrack<jet_vtx_ntrack[1][ivtx]; itrack++) {
	  ptrack_x-=jet_track_px[1][ivtx][itrack];
	  ptrack_y-=jet_track_py[1][ivtx][itrack];
	  ptrack_z-=jet_track_pz[1][ivtx][itrack];
	}
      }
      std::vector<float> ptracks;
      ptracks.push_back(ptrack_x);
      ptracks.push_back(ptrack_y);
      ptracks.push_back(ptrack_z);
      float costheta_tracks=GetCostheta(ptracks);
      
      if(PreSelection(costheta_tracks)==false) continue;

      
      h1_y23_ps->Fill(mc_quark_ps_y23);
      h1_y23_reco->Fill(y23);
      h2_y23->Fill(y23,mc_quark_ps_y23);
    }
    
  }//end loop
  
  TFile *MyFile = new TFile("output.root","RECREATE");
  MyFile->cd();
  h1_y23_ps->Write();
  h1_y23_reco->Write();
  h2_y23->GetXaxis()->SetTitle("reco y23");
  h2_y23->GetYaxis()->SetTitle("parton shower y23");
  h2_y23->Write();
  
  
  
}
  
   


bool observable::PreSelection(float costheta=0.8) {
  
  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
  double b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
  double b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
  double bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

  float sph_eq=0;
  float m= -0.04;//(0.012-0.04)/(0.8-0.1);
  sph_eq=m*(fabs(costheta)) + 0.042;

  float sintheta=sqrt(1-costheta*costheta);
  
  sph_eq=0.001 + 0.035 * sintheta*sintheta;


  if( y23<0.02 && sphericity<0.012 && (b1mass+b2mass) <100 && jet_btag[0]>btag1 && jet_btag[1]>btag2) return true;
  
  return false;
}
