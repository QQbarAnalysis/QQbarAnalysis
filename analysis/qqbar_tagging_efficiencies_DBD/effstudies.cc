#define effstudies_cxx
#include "effstudies.h"
#include "TPad.h"

void effstudies::eff_flavour(int n_entries=-1, TString pol="eL")
{

  double x[100], y[100], ex[100], ey[100], x2[100], ex2[100], y2[100], ey2[100], x3[100], ex3[100], y3[100], ey3[100];
  double btag_v[100];
  double ctag_v[100];
  double etag[100];
  
  for(int itag=0; itag<20; itag++) {
    
    TH1F* h_ctag= new TH1F("h_ctag","h_ctag",3,-0.5,2.5);
    TH1F* h_btag= new TH1F("h_btag","h_btag",3,-0.5,2.5);
    TH1F* h_btag2= new TH1F("h_btag2","h_btag2",3,-0.5,2.5);
  
    TH1F* h_quark= new TH1F("h_quark","h_quark",3,-0.5,2.5);
  
  
    btag_v[itag]=double(itag)/20.;
    ctag_v[itag]=double(itag)/20.;
    etag[itag]=0;
  
    Long64_t nentries;
    if(n_entries>0) nentries= n_entries;
    else nentries= fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;
      
      int quarkid=fabs(mc_quark_pdg[0]);

      if( mc_ISR_E[0]+mc_ISR_E[1]>35)  continue;
        
      if(PreSelection(5,35)==false) continue;
    
      if( quarkid==0 || quarkid>5) continue;
    
      for(int ijet=0; ijet<2; ijet++) {

	std::vector<float> p_jet;
	p_jet.push_back(jet_px[ijet]);
	p_jet.push_back(jet_py[ijet]);
	p_jet.push_back(jet_pz[ijet]);
	float costheta=GetCostheta(p_jet);

	if( fabs(costheta)>0.8 ) continue;
      
	if( quarkid<4) h_quark->Fill(0);
	if( quarkid==4) h_quark->Fill(1);
	if( quarkid==5) h_quark->Fill(2);
      
	if(jet_ctag[ijet]>ctag_v[itag] && quarkid<4) h_ctag->Fill(0);
	if(jet_ctag[ijet]>ctag_v[itag] && quarkid==4) h_ctag->Fill(1);
	if(jet_ctag[ijet]>ctag_v[itag] && quarkid==5) h_ctag->Fill(2);

	if(jet_btag[ijet]>btag_v[itag] && quarkid<4) h_btag->Fill(0);
	if(jet_btag[ijet]>btag_v[itag] && quarkid==4) h_btag->Fill(1);
	if(jet_btag[ijet]>btag_v[itag] && quarkid==5) h_btag->Fill(2);


	double momvertex=0;

	double mom_x=0, mom_y=0, mom_z=0;
	double e=0;
	double nt=0;
	for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
	  for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
	    nt++;
	    e+=jet_track_E[ijet][ivtx][itrack];
	    mom_x+=jet_track_px[ijet][ivtx][itrack];
	    mom_y+=jet_track_py[ijet][ivtx][itrack];
	    mom_z+=jet_track_pz[ijet][ivtx][itrack];
	  }
	}

	double mass = sqrt(pow(e,2) - pow(mom_x,2) -  pow(mom_y,2) - pow(mom_z,2) );
	momvertex= sqrt(pow(mom_x,2) +  pow(mom_y,2) + pow(mom_z,2) );

	if(momvertex>25 && jet_btag[ijet]>btag_v[itag] && quarkid<4) h_btag2->Fill(0);
	if(momvertex>25 && jet_btag[ijet]>btag_v[itag] && quarkid==4) h_btag2->Fill(1);
	if(momvertex>25 && jet_btag[ijet]>btag_v[itag] && quarkid==5) h_btag2->Fill(2);
      
      
      
      }
    }

    //ctag
    x[itag]=h_ctag->GetBinContent(2)/h_quark->GetBinContent(2);
    ex[itag]=sqrt(h_ctag->GetBinContent(2))/h_quark->GetBinContent(2);
  
    double norm=h_ctag->GetBinContent(1)*h_quark->GetBinContent(2)/h_quark->GetBinContent(1)+
      h_ctag->GetBinContent(2)*h_quark->GetBinContent(2)/h_quark->GetBinContent(2)+
      h_ctag->GetBinContent(3)*h_quark->GetBinContent(2)/h_quark->GetBinContent(3);

    y[itag]=h_ctag->GetBinContent(2)/norm;
    ey[itag]=sqrt(h_ctag->GetBinContent(2))/norm;

    //y[itag]=h_ctag->GetBinContent(2)/(h_ctag->Integral());
    //ey[itag]=sqrt(h_ctag->GetBinContent(2))/h_ctag->Integral();
  
    //btag
    x2[itag]=h_btag->GetBinContent(3)/h_quark->GetBinContent(3);
    ex2[itag]=sqrt(h_btag->GetBinContent(3))/h_quark->GetBinContent(3);

    norm=h_btag->GetBinContent(1)*h_quark->GetBinContent(3)/h_quark->GetBinContent(1)+
      h_btag->GetBinContent(2)*h_quark->GetBinContent(3)/h_quark->GetBinContent(2)+
      h_btag->GetBinContent(3)*h_quark->GetBinContent(3)/h_quark->GetBinContent(3);

    y2[itag]=h_btag->GetBinContent(3)/norm;
    ey2[itag]=sqrt(h_btag->GetBinContent(3))/norm;


    //btag + momvertex
    x3[itag]=h_btag2->GetBinContent(3)/h_quark->GetBinContent(3);
    ex3[itag]=sqrt(h_btag2->GetBinContent(3))/h_quark->GetBinContent(3);

    norm=h_btag2->GetBinContent(1)*h_quark->GetBinContent(3)/h_quark->GetBinContent(1)+
      h_btag2->GetBinContent(2)*h_quark->GetBinContent(3)/h_quark->GetBinContent(2)+
      h_btag2->GetBinContent(3)*h_quark->GetBinContent(3)/h_quark->GetBinContent(3);

    y3[itag]=h_btag2->GetBinContent(3)/norm;
    ey3[itag]=sqrt(h_btag2->GetBinContent(3))/norm;
  
  
 
  }
  
  TGraphErrors *g_ctag = new TGraphErrors(20,x,y,ex,ey);
  TGraphErrors *g_btag = new TGraphErrors(20,x2,y2,ex2,ey2);
  TGraphErrors *g_btag2 = new TGraphErrors(20,x3,y3,ex3,ey3);
  
  
  TGraphErrors *g_ctag_eff = new TGraphErrors(20,ctag_v,x,etag,ex);
  TGraphErrors *g_ctag_purity = new TGraphErrors(20,ctag_v,y,etag,ey);
  
  TGraphErrors *g_btag_eff = new TGraphErrors(20,btag_v,x2,etag,ex2);
  TGraphErrors *g_btag_purity = new TGraphErrors(20,btag_v,y2,etag,ey2);

  TGraphErrors *g_btag2_eff = new TGraphErrors(20,btag_v,x3,etag,ex3);
  TGraphErrors *g_btag2_purity = new TGraphErrors(20,btag_v,y3,etag,ey3);
  
  
  
  TFile *MyFile = new TFile(TString::Format("eff_purity_tag_%s.root",pol.Data()),"RECREATE");
  MyFile->cd();
  g_ctag->SetName("cquark");
  g_ctag->Write();
  g_btag->SetName("bquark");
  g_btag->Write();
  g_btag2->SetName("bquark_cut_mom");
  g_btag2->Write();
  

  g_ctag_eff->SetName("cquark_eff");
  g_ctag_eff->Write();
  g_ctag_purity->SetName("cquark_purity");
  g_ctag_purity->Write();
  
  g_btag_eff->SetName("bquark_eff");
  g_btag_eff->Write();
  g_btag_purity->SetName("bquark_purity");
  g_btag_purity->Write();

  g_btag2_eff->SetName("bquark_eff_cut_mom");
  g_btag2_eff->Write();
  g_btag2_purity->SetName("bquark_purity_cut_mom");
  g_btag2_purity->Write();
  
  MyFile->Close();
  
}


void effstudies::Analysis_rho_charge(int n_entries=-1, TString pol="eL", int quark=5, int rad=0)
{

  TH1F* fH= new TH1F("NH","NH",nbins/2,0,1.0);
  TH1F* fE= new TH1F("NE","NE",nbins/2,0,1.0);
  TH1F* Nq= new TH1F("Nq","Nq",nbins/2,0,1.0);
  TH1F* Nqj= new TH1F("Nqj","Nqj",nbins/2,0,1.0); 
  fH->Sumw2();
  fE->Sumw2();
  Nqj->Sumw2();
  Nq->Sumw2();

  TH1F* fH_Bc= new TH1F("NH_Bc","NH_Bc",nbins/2,0,1.0);
  TH1F* fE_Bc= new TH1F("NE_Bc","NE_Bc",nbins/2,0,1.0);
  fH_Bc->Sumw2();
  fE_Bc->Sumw2();

  TH1F* fH_Kc= new TH1F("NH_Kc","NH_Kc",nbins/2,0,1.0);
  TH1F* fE_Kc= new TH1F("NE_Kc","NE_Kc",nbins/2,0,1.0);
  fH_Kc->Sumw2();
  fE_Kc->Sumw2();

  TH1F* fH_onlybtag= new TH1F("NH_onlybtag","NH_onlybtag",nbins/2,0,1.0);
  TH1F* fE_onlybtag= new TH1F("NE_onlybtag","NE_onlybtag",nbins/2,0,1.0);
  fH_onlybtag->Sumw2();
  fE_onlybtag->Sumw2();
    
  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;


    float costheta_bbbar;
    std::vector<float> p_bbar;
    p_bbar.push_back(mc_quark_px[0]-mc_quark_px[1]);
    p_bbar.push_back(mc_quark_py[0]-mc_quark_py[1]);
    p_bbar.push_back(mc_quark_pz[0]-mc_quark_pz[1]);
    costheta_bbbar=GetCostheta(p_bbar);

    float gamma_e=mc_ISR_E[0]+mc_ISR_E[1];

    //    if(bbmass>200 && fabs(costheta_bbbar)<0.8) Rt++;
    if(rad==0) {
      if(quark<4) {
	if( (fabs(mc_quark_pdg[0])!=1 && fabs(mc_quark_pdg[0])!=2  && fabs(mc_quark_pdg[0])!=3) || gamma_e>35) continue;
      } else {
	if( fabs(mc_quark_pdg[0])!=quark || gamma_e>35) continue;
      }
    } else {
      if(quark<4) {
	if( (fabs(mc_quark_pdg[0])!=1 && fabs(mc_quark_pdg[0])!=2  && fabs(mc_quark_pdg[0])!=3) || gamma_e<35) continue;
      } else {
	if( fabs(fabs(mc_quark_pdg[0]))!=quark || gamma_e<35) continue;
      }
    }
    
    std::vector<float> pq;
    pq.push_back(jet_px[0]-jet_px[1]);
    pq.push_back(jet_py[0]-jet_py[1]);
    pq.push_back(jet_pz[0]-jet_pz[1]);

    double costhetaq=fabs(GetCostheta(pq));
    Nq->Fill(costhetaq);
    Nq->Fill(costhetaq);
    
    if(rad==0 && PreSelection(5,35)==false) continue;
    if(rad==1 && PreSelection(-5,35)==false) continue; // NOT IMPLEMENTED!!
    
    std::vector<float> p;
    p.push_back(jet_px[0]-jet_px[1]);
    p.push_back(jet_py[0]-jet_py[1]);
    p.push_back(jet_pz[0]-jet_pz[1]);

    double costheta=fabs(GetCostheta(p));
    Nqj->Fill(costheta);
    Nqj->Fill(costheta);
    
    // charge + angles
    int Kc[2];
    Kc[0]=0; Kc[1]=0;

    int Bc[2];
    Bc[0]=0; Bc[1]=0;
      
    for(int ijet=0; ijet<2; ijet++) {
      Bc[ijet]=ChargeBcJet(ijet);
      Kc[ijet]=ChargeKcJet(ijet);
    }

    //Bc or Kc
    bool singletag1=false;
    bool singletag2=false;
    bool Bcbool=false;

    double momvertex[2];
    for(int ijet=0; ijet<2; ijet++) {

      momvertex[ijet]=0;
      double mom_x=0, mom_y=0, mom_z=0;
      double e=0;
      double nt=0;
      for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
	for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
	  nt++;
	  e+=jet_track_E[ijet][ivtx][itrack];
	  mom_x+=jet_track_px[ijet][ivtx][itrack];
	  mom_y+=jet_track_py[ijet][ivtx][itrack];
	  mom_z+=jet_track_pz[ijet][ivtx][itrack];
	}    
      }

      double mass = sqrt(pow(e,2) - pow(mom_x,2) -  pow(mom_y,2) - pow(mom_z,2) );
      double mom= sqrt(pow(mom_x,2) +  pow(mom_y,2) + pow(mom_z,2) );
      momvertex[ijet]=mom;///double(nt);
    }

    //btag
    if(jet_btag[0]>btag1 ) singletag1=true;
    if(jet_btag[1]>btag2 ) singletag2=true;
    
    if(singletag1==true && singletag2==true )  {
      fE_onlybtag->Fill(costheta);
      fE_onlybtag->Fill(costheta);
    }
    if( singletag1==true ) fH_onlybtag->Fill(costheta);
    if( singletag2==true ) fH_onlybtag->Fill(costheta);

    
    //btag + mom vertex
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && momvertex[0]>25 ) singletag1=true;
    if(jet_btag[1]>btag2 && momvertex[1]>25 ) singletag2=true;
    
    if(singletag1==true && singletag2==true )  {
      fE->Fill(costheta);
      fE->Fill(costheta);
    }
    if( singletag1==true ) fH->Fill(costheta);
    if( singletag2==true ) fH->Fill(costheta);

    //Bc
    singletag1=false;
    singletag2=false;

    if(jet_btag[0]>btag1 && momvertex[0]>25 && Bc[0]!=0 ) singletag1=true;
    if(jet_btag[1]>btag2 && momvertex[1]>25 && Bc[1]!=0 ) singletag2=true;
    
    if(singletag1==true && singletag2==true)  {
      fE_Bc->Fill(costheta);
      fE_Bc->Fill(costheta);
    }
    if( singletag1==true ) fH_Bc->Fill(costheta);
    if( singletag2==true ) fH_Bc->Fill(costheta);
    //  if(singletag1==true || singletag2==true)  Bcbool=true;

    //Kc    
    singletag1=false;
    singletag2=false;
    
    if(jet_btag[0]>btag1 && momvertex[0]>25 && Kc[0]!=0 ) singletag1=true;
    if(jet_btag[1]>btag2 && momvertex[1]>25 && Kc[1]!=0 ) singletag2=true;
    
    if(singletag1==true && singletag2==true)  {
      fE_Kc->Fill(costheta);
      fE_Kc->Fill(costheta);
    }
    if( singletag1==true ) fH_Kc->Fill(costheta);
    if( singletag2==true ) fH_Kc->Fill(costheta);

    /*
    // *********************************8888
    //realistic categories
    singletag1=false;
    singletag2=false;
    bool taken=false;
    
    // BcBc
    if(jet_btag[0]>btag1 && Bc[0]!=0 )singletag1=true;
    if(jet_btag[1]>btag2 && Bc[1]!=0 )singletag2=true;
    
    if(singletag1==true && singletag2==true)  {
    //   fE_real->Fill(costheta);
    // fE_real->Fill(costheta);
    taken = true;
    }
    //   if( singletag1==true ) fH_real->Fill(costheta);
    //	 if( singletag2==true ) fH_real->Fill(costheta);
    
    //KcKc
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Kc[0]!=0 )singletag1=true;
    if(jet_btag[1]>btag2 && Kc[1]!=0 )singletag2=true;
    
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    */
    
    /*
    //BcKc
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Kc[0]==0 && Bc[0]!=0 )singletag1=true;
    if(jet_btag[1]>btag2 && Bc[1]==0 && Kc[1]!=0 )singletag2=true;
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    //KcBc
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Bc[0]==0 && Kc[0]!=0 )singletag1=true;
    if(jet_btag[1]>btag2 && Kc[1]==0 && Bc[1]!=0 )singletag2=true;
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }*/
    /*
    //BcKc_same1
    if(taken==false){
    singletag1=false;
    singletag2=false;
    //   if(jet_btag[0]>btag1 && Bc[1]==0 && Kc[1]==0 && Bc[0]!=0 )singletag1=true;
    if(jet_btag[0]>btag1 && Bc[1]==0 && Kc[1]==0 && Bc[0]!=0 && Kc[0]!=0 )singletag2=true;
    if(singletag2==true)  {
    fE_real->Fill(costheta);
    //	fE_real->Fill(costheta);
    }
    //  if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    //BcKc_same2
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[1]>btag2 && Bc[0]==0 && Kc[0]==0 && Bc[1]!=0 && Kc[1]!=0)singletag1=true;
    //  if(jet_btag[1]>0.2 && Bc[0]==0 && Kc[0]==0 && Kc[1]!=0 )singletag2=true;
    if(singletag1==true )  {
    fE_real->Fill(costheta);
    //	fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    //  if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    */
    
    /*    
    // *********************************8888
    //realistic categories
    singletag1=false;
    singletag2=false;
    bool taken;
    
    // BcBc
    if(jet_btag[0]>btag1 && Bc[0]!=0 )singletag1=true;
    if(jet_btag[1]>btag2 && Bc[1]!=0 )singletag2=true;
    
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;

    //KcKc
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Kc[0]!=0 )singletag1=true;
    if(jet_btag[1]>0.2 && Kc[1]!=0 )singletag2=true;
    
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    //BcKc
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Bc[1]==0 && Kc[0]==0 && Bc[0]!=0 )singletag1=true;
    if(jet_btag[1]>0.2 && Bc[1]==0 && Kc[0]==0 && Kc[1]!=0 )singletag2=true;
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    //KcBc
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Bc[0]==0 && Kc[1]==0 && Kc[0]!=0 )singletag1=true;
    if(jet_btag[1]>btag2 && Bc[0]==0 && Kc[1]==0 && Bc[1]!=0 )singletag2=true;
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    //BcKc_same1
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Bc[1]==0 && Kc[1]==0 && Bc[0]!=0 )singletag1=true;
    if(jet_btag[0]>btag1 && Bc[1]==0 && Kc[1]==0 && Kc[0]!=0 )singletag2=true;
    if(singletag1==true && singletag2==true && Bc[0]*Kc[0]>0)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    //BcKc_same2
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[1]>btag2 && Bc[0]==0 && Kc[0]==0 && Bc[1]!=0 )singletag1=true;
    if(jet_btag[1]>0.2 && Bc[0]==0 && Kc[0]==0 && Kc[1]!=0 )singletag2=true;
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    */
 
    
    
  }

  // *****************************************************************************************88
  //Bc or Kc
  double fH_total=0;
  double fE_total=0;
  double Nqj_total=0;

  double fH_08=0;
  double fE_08=0;
  double Nqj_08=0;
  
  double cos[100];
  double rho[100];
  double rhoLEP[100];
  double ecos[100];
  double erho[100];
  double erhoLEP[100];
  double effb[100];
  double effbd[100];
  double error_effb[100];
  double error_effbd[100];

  double eff2j[100];
  double error_eff2j[100];

  for(int i=0; i<nbins/2; i++) {
    cos[i]=0;
    rho[i]=0;
    ecos[i]=0;
    erho[i]=0;
    rhoLEP[i]=0;
    erhoLEP[i]=0;
    eff2j[i]=0;
    error_eff2j[i]=0;
    
    cos[i]=fH->GetBinCenter(i+1);
    ecos[i]=0;
    
    fH_total+=fH->GetBinContent(i+1);
    fE_total+=fE->GetBinContent(i+1);
    Nqj_total+=Nqj->GetBinContent(i+1);

    if(nbins==40 && i<16) {
      fH_08+=fH->GetBinContent(i+1);
      fE_08+=fE->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    if(nbins==20 && i<8) {
      fH_08+=fH->GetBinContent(i+1);
      fE_08+=fE->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    effb[i]=fH->GetBinContent(i+1)/Nqj->GetBinContent(i+1);
    effbd[i]=fE->GetBinContent(i+1)/Nqj->GetBinContent(i+1);

    error_effb[i]=sqrt(pow(sqrt(fH->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fH->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    error_effbd[i]=sqrt(pow(sqrt(fE->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fE->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    double der_effbd=1./(effb[i]-effb[i]*effb[i]);
    double der_effb=(effbd[i]-2.*effbd[i]*effb[i]+effb[i]*effb[i])/((effb[i]-1.)*(effb[i]-1.)*effb[i]*effb[i]);

    rho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    rhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );
 
    effb[i]*=100.;
    effbd[i]*=100.;
    error_effb[i]*=100.;
    error_effbd[i]*=100.;

    eff2j[i]=Nqj->GetBinContent(i+1)/Nq->GetBinContent(i+1);
    error_eff2j[i]=sqrt(pow(sqrt(Nqj->GetBinContent(i+1))/Nq->GetBinContent(i+1),2) + pow(Nqj->GetBinContent(i+1)*sqrt(Nq->GetBinContent(i+1))/(Nq->GetBinContent(i+1)*Nq->GetBinContent(i+1)),2));

    eff2j[i]*=100.;
    error_eff2j[i]*=100.;
  }

  TGraphErrors* grho= new TGraphErrors(nbins/2,cos,rho,ecos,erho);
  TGraphErrors* grhoLEP= new TGraphErrors(nbins/2,cos,rhoLEP,ecos,erhoLEP);
  TGraphErrors* geffb= new TGraphErrors(nbins/2,cos,effb,ecos,error_effb); 
  TGraphErrors* geffbd= new TGraphErrors(nbins/2,cos,effbd,ecos,error_effbd);
  TGraphErrors* geff2j= new TGraphErrors(nbins/2,cos,eff2j,ecos,error_eff2j); 

  double effb_=fH_total/Nqj_total;
  double effbd_=fE_total/Nqj_total;
  double error_effb_=sqrt(pow(sqrt(fH_total)/Nqj_total,2) + pow(fH_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  double error_effbd_=sqrt(pow(sqrt(fE_total)/Nqj_total,2) + pow(fE_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  double der_effbd=1./(effb_-effb_*effb_);
  double der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);

  double rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  double erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );

  double rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  double erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
 
  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  std::cout<<" ----------------------------------------------------------------------  "<< std::endl;
  std::cout<<" case btag + mom cut"<< std::endl;
  std::cout<<"  "<< std::endl;

  std::cout<<" fH="<<fH_total<<"   Nqj=" <<Nqj_total<< "   effb=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE="<<fE_total<<"   Nqj=" <<Nqj_total<< "   effbd=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;
  
  std::cout<<"cos(theta)<0.8  "<< std::endl;
  effb_=fH_08/Nqj_08;
  effbd_=fE_08/Nqj_08;
  error_effb_=sqrt(pow(sqrt(fH_08)/Nqj_08,2) + pow(fH_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  error_effbd_=sqrt(pow(sqrt(fE_08)/Nqj_08,2) + pow(fE_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);
  
  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
   
  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  std::cout<<" fH="<<fH_08<<"   Nqj=" <<Nqj_08<< "   effb=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE="<<fE_08<<"   Nqj=" <<Nqj_08<< "   effbd=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;

  // *****************************************************************************************88
  //onlybtag 
  fH_total=0;
  fE_total=0;
  Nqj_total=0;
   
  fH_08=0;
  fE_08=0;
  Nqj_08=0;
   
  for(int i=0; i<nbins/2; i++) {
    cos[i]=0;
    rho[i]=0;
    ecos[i]=0;
    erho[i]=0;
    rhoLEP[i]=0;
    erhoLEP[i]=0;
    
    cos[i]=fH_onlybtag->GetBinCenter(i+1);
    ecos[i]=0;
    
    fH_total+=fH_onlybtag->GetBinContent(i+1);
    fE_total+=fE_onlybtag->GetBinContent(i+1);
    Nqj_total+=Nqj->GetBinContent(i+1);

    if(nbins==40 && i<16) {
      fH_08+=fH_onlybtag->GetBinContent(i+1);
      fE_08+=fE_onlybtag->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    if(nbins==20 && i<8) {
      fH_08+=fH_onlybtag->GetBinContent(i+1);
      fE_08+=fE_onlybtag->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    effb[i]=fH_onlybtag->GetBinContent(i+1)/Nqj->GetBinContent(i+1);
    effbd[i]=fE_onlybtag->GetBinContent(i+1)/Nqj->GetBinContent(i+1);

    error_effb[i]=sqrt(pow(sqrt(fH_onlybtag->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fH_onlybtag->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    error_effbd[i]=sqrt(pow(sqrt(fE_onlybtag->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fE_onlybtag->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    double der_effbd=1./(effb[i]-effb[i]*effb[i]);
    double der_effb=(effbd[i]-2.*effbd[i]*effb[i]+effb[i]*effb[i])/((effb[i]-1.)*(effb[i]-1.)*effb[i]*effb[i]);

    rho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    rhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    
    effb[i]*=100.;
    effbd[i]*=100.;
    error_effb[i]*=100.;
    error_effbd[i]*=100.;   
  }

  TGraphErrors* grho_onlybtag= new TGraphErrors(nbins/2,cos,rho,ecos,erho);
  TGraphErrors* grhoLEP_onlybtag= new TGraphErrors(nbins/2,cos,rhoLEP,ecos,erhoLEP);
  TGraphErrors* geffb_onlybtag= new TGraphErrors(nbins/2,cos,effb,ecos,error_effb); 
  TGraphErrors* geffbd_onlybtag= new TGraphErrors(nbins/2,cos,effbd,ecos,error_effbd);

  effb_=fH_total/Nqj_total;
  effbd_=fE_total/Nqj_total;
  error_effb_=sqrt(pow(sqrt(fH_total)/Nqj_total,2) + pow(fH_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  error_effbd_=sqrt(pow(sqrt(fE_total)/Nqj_total,2) + pow(fE_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);

  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );

  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  
  std::cout<<" ----------------------------------------------------------------------  "<< std::endl;
  std::cout<<" case onlybtag "<< std::endl;
  std::cout<<"  "<< std::endl;

  std::cout<<" fH_onlybtag="<<fH_total<<"   Nqj=" <<Nqj_total<< "   effb=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_onlybtag="<<fE_total<<"   Nqj=" <<Nqj_total<< "   effbd=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_onlybtag="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_onlybtag="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;
  
  std::cout<<"cos(theta)<0.8  "<< std::endl;
  effb_=fH_08/Nqj_08;
  effbd_=fE_08/Nqj_08;
  error_effb_=sqrt(pow(sqrt(fH_08)/Nqj_08,2) + pow(fH_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  error_effbd_=sqrt(pow(sqrt(fE_08)/Nqj_08,2) + pow(fE_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);
  
  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
   
  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  std::cout<<" fH_onlybtag="<<fH_08<<"   Nqj=" <<Nqj_08<< "   effb_onlybtag=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_onlybtag="<<fE_08<<"   Nqj=" <<Nqj_08<< "   effbd_onlybtag=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_onlybtag="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_onlybtag="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;


  // *****************************************************************************************88
  //Bc 
  fH_total=0;
  fE_total=0;
  Nqj_total=0;
   
  fH_08=0;
  fE_08=0;
  Nqj_08=0;
   
  for(int i=0; i<nbins/2; i++) {
    cos[i]=0;
    rho[i]=0;
    ecos[i]=0;
    erho[i]=0;
    rhoLEP[i]=0;
    erhoLEP[i]=0;
    
    cos[i]=fH_Bc->GetBinCenter(i+1);
    ecos[i]=0;
    
    fH_total+=fH_Bc->GetBinContent(i+1);
    fE_total+=fE_Bc->GetBinContent(i+1);
    Nqj_total+=Nqj->GetBinContent(i+1);

    if(nbins==40 && i<16) {
      fH_08+=fH_Bc->GetBinContent(i+1);
      fE_08+=fE_Bc->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    if(nbins==20 && i<8) {
      fH_08+=fH_Bc->GetBinContent(i+1);
      fE_08+=fE_Bc->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    effb[i]=fH_Bc->GetBinContent(i+1)/Nqj->GetBinContent(i+1);
    effbd[i]=fE_Bc->GetBinContent(i+1)/Nqj->GetBinContent(i+1);

    error_effb[i]=sqrt(pow(sqrt(fH_Bc->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fH_Bc->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    error_effbd[i]=sqrt(pow(sqrt(fE_Bc->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fE_Bc->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    double der_effbd=1./(effb[i]-effb[i]*effb[i]);
    double der_effb=(effbd[i]-2.*effbd[i]*effb[i]+effb[i]*effb[i])/((effb[i]-1.)*(effb[i]-1.)*effb[i]*effb[i]);

    rho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    rhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    
    effb[i]*=100.;
    effbd[i]*=100.;
    error_effb[i]*=100.;
    error_effbd[i]*=100.;   
  }

  TGraphErrors* grho_Bc= new TGraphErrors(nbins/2,cos,rho,ecos,erho);
  TGraphErrors* grhoLEP_Bc= new TGraphErrors(nbins/2,cos,rhoLEP,ecos,erhoLEP);
  TGraphErrors* geffb_Bc= new TGraphErrors(nbins/2,cos,effb,ecos,error_effb); 
  TGraphErrors* geffbd_Bc= new TGraphErrors(nbins/2,cos,effbd,ecos,error_effbd);

  effb_=fH_total/Nqj_total;
  effbd_=fE_total/Nqj_total;
  error_effb_=sqrt(pow(sqrt(fH_total)/Nqj_total,2) + pow(fH_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  error_effbd_=sqrt(pow(sqrt(fE_total)/Nqj_total,2) + pow(fE_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);

  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );

  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  
  std::cout<<" ----------------------------------------------------------------------  "<< std::endl;
  std::cout<<" case Bc "<< std::endl;
  std::cout<<"  "<< std::endl;

  std::cout<<" fH_Bc="<<fH_total<<"   Nqj=" <<Nqj_total<< "   effb=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_Bc="<<fE_total<<"   Nqj=" <<Nqj_total<< "   effbd=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_Bc="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_Bc="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;
  
  std::cout<<"cos(theta)<0.8  "<< std::endl;
  effb_=fH_08/Nqj_08;
  effbd_=fE_08/Nqj_08;
  error_effb_=sqrt(pow(sqrt(fH_08)/Nqj_08,2) + pow(fH_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  error_effbd_=sqrt(pow(sqrt(fE_08)/Nqj_08,2) + pow(fE_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);
  
  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
   
  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  std::cout<<" fH_Bc="<<fH_08<<"   Nqj=" <<Nqj_08<< "   effb_Bc=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_Bc="<<fE_08<<"   Nqj=" <<Nqj_08<< "   effbd_Bc=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_Bc="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_Bc="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;


  // *****************************************************************************************88
  //Kc 
  fH_total=0;
  fE_total=0;
  Nqj_total=0;
   
  fH_08=0;
  fE_08=0;
  Nqj_08=0;
   
  for(int i=0; i<nbins/2; i++) {
    cos[i]=0;
    rho[i]=0;
    ecos[i]=0;
    erho[i]=0;
    rhoLEP[i]=0;
    erhoLEP[i]=0;
    
    cos[i]=fH_Kc->GetBinCenter(i+1);
    ecos[i]=0;
    
    fH_total+=fH_Kc->GetBinContent(i+1);
    fE_total+=fE_Kc->GetBinContent(i+1);
    Nqj_total+=Nqj->GetBinContent(i+1);

    if(nbins==40 && i<16) {
      fH_08+=fH_Kc->GetBinContent(i+1);
      fE_08+=fE_Kc->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    if(nbins==20 && i<8) {
      fH_08+=fH_Kc->GetBinContent(i+1);
      fE_08+=fE_Kc->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    effb[i]=fH_Kc->GetBinContent(i+1)/Nqj->GetBinContent(i+1);
    effbd[i]=fE_Kc->GetBinContent(i+1)/Nqj->GetBinContent(i+1);

    error_effb[i]=sqrt(pow(sqrt(fH_Kc->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fH_Kc->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    error_effbd[i]=sqrt(pow(sqrt(fE_Kc->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fE_Kc->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    double der_effbd=1./(effb[i]-effb[i]*effb[i]);
    double der_effb=(effbd[i]-2.*effbd[i]*effb[i]+effb[i]*effb[i])/((effb[i]-1.)*(effb[i]-1.)*effb[i]*effb[i]);

    rho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    rhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    
    effb[i]*=100.;
    effbd[i]*=100.;
    error_effb[i]*=100.;
    error_effbd[i]*=100.;   
  }

  TGraphErrors* grho_Kc= new TGraphErrors(nbins/2,cos,rho,ecos,erho);
  TGraphErrors* grhoLEP_Kc= new TGraphErrors(nbins/2,cos,rhoLEP,ecos,erhoLEP);
  TGraphErrors* geffb_Kc= new TGraphErrors(nbins/2,cos,effb,ecos,error_effb); 
  TGraphErrors* geffbd_Kc= new TGraphErrors(nbins/2,cos,effbd,ecos,error_effbd);

  effb_=fH_total/Nqj_total;
  effbd_=fE_total/Nqj_total;
  error_effb_=sqrt(pow(sqrt(fH_total)/Nqj_total,2) + pow(fH_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  error_effbd_=sqrt(pow(sqrt(fE_total)/Nqj_total,2) + pow(fE_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);

  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );

  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  
  std::cout<<" ----------------------------------------------------------------------  "<< std::endl;
  std::cout<<" case Kc "<< std::endl;
  std::cout<<"  "<< std::endl;

  std::cout<<" fH_Kc="<<fH_total<<"   Nqj=" <<Nqj_total<< "   effb=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_Kc="<<fE_total<<"   Nqj=" <<Nqj_total<< "   effbd=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_Kc="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_Kc="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;
  
  std::cout<<"cos(theta)<0.8  "<< std::endl;
  effb_=fH_08/Nqj_08;
  effbd_=fE_08/Nqj_08;
  error_effb_=sqrt(pow(sqrt(fH_08)/Nqj_08,2) + pow(fH_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  error_effbd_=sqrt(pow(sqrt(fE_08)/Nqj_08,2) + pow(fE_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);
  
  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
   
  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  std::cout<<" fH_Kc="<<fH_08<<"   Nqj=" <<Nqj_08<< "   effb_Kc=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_Kc="<<fE_08<<"   Nqj=" <<Nqj_08<< "   effbd_Kc=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_Kc="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_Kc="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;

  /*
  // *****************************************************************************************88
  //real 
  fH_total=0;
  fE_total=0;
  Nqj_total=0;
   
  fH_08=0;
  fE_08=0;
  Nqj_08=0;
   
  for(int i=0; i<nbins/2; i++) {
  cos[i]=0;
  rho[i]=0;
  ecos[i]=0;
  erho[i]=0;
  rhoLEP[i]=0;
  erhoLEP[i]=0;
    
  cos[i]=fH_real->GetBinCenter(i+1);
  ecos[i]=0;
    
  fH_total+=fH_real->GetBinContent(i+1);
  fE_total+=fE_real->GetBinContent(i+1);
  Nqj_total+=Nqj->GetBinContent(i+1);

  if(nbins==40 && i<16) {
  fH_08+=fH_real->GetBinContent(i+1);
  fE_08+=fE_real->GetBinContent(i+1);
  Nqj_08+=Nqj->GetBinContent(i+1);
  }
  if(nbins==20 && i<8) {
  fH_08+=fH_real->GetBinContent(i+1);
  fE_08+=fE_real->GetBinContent(i+1);
  Nqj_08+=Nqj->GetBinContent(i+1);
  }
  effb[i]=fH_real->GetBinContent(i+1)/Nqj->GetBinContent(i+1);
  effbd[i]=fE_real->GetBinContent(i+1)/Nqj->GetBinContent(i+1);

  error_effb[i]=sqrt(pow(sqrt(fH_real->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fH_real->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
  error_effbd[i]=sqrt(pow(sqrt(fE_real->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fE_real->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
  double der_effbd=1./(effb[i]-effb[i]*effb[i]);
  double der_effb=(effbd[i]-2.*effbd[i]*effb[i]+effb[i]*effb[i])/((effb[i]-1.)*(effb[i]-1.)*effb[i]*effb[i]);

  rho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
  erho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

  rhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
  erhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    
  effb[i]*=100.;
  effbd[i]*=100.;
  error_effb[i]*=100.;
  error_effbd[i]*=100.;   
  }

  TGraphErrors* grho_real= new TGraphErrors(nbins/2,cos,rho,ecos,erho);
  TGraphErrors* grhoLEP_real= new TGraphErrors(nbins/2,cos,rhoLEP,ecos,erhoLEP);
  TGraphErrors* geffb_real= new TGraphErrors(nbins/2,cos,effb,ecos,error_effb); 
  TGraphErrors* geffbd_real= new TGraphErrors(nbins/2,cos,effbd,ecos,error_effbd);

  effb_=fH_total/Nqj_total;
  effbd_=fE_total/Nqj_total;
  error_effb_=sqrt(pow(sqrt(fH_total)/Nqj_total,2) + pow(fH_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  error_effbd_=sqrt(pow(sqrt(fE_total)/Nqj_total,2) + pow(fE_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);

  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );

  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  
  std::cout<<" ----------------------------------------------------------------------  "<< std::endl;
  std::cout<<" case real "<< std::endl;
  std::cout<<"  "<< std::endl;

  std::cout<<" fH_real="<<fH_total<<"   Nqj=" <<Nqj_total<< "   effb=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_real="<<fE_total<<"   Nqj=" <<Nqj_total<< "   effbd=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_real="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_real="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;
  
  std::cout<<"cos(theta)<0.8  "<< std::endl;
  effb_=fH_08/Nqj_08;
  effbd_=fE_08/Nqj_08;
  error_effb_=sqrt(pow(sqrt(fH_08)/Nqj_08,2) + pow(fH_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  error_effbd_=sqrt(pow(sqrt(fE_08)/Nqj_08,2) + pow(fE_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);
  
  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
   
  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  std::cout<<" fH_real="<<fH_08<<"   Nqj=" <<Nqj_08<< "   effb_real=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_real="<<fE_08<<"   Nqj=" <<Nqj_08<< "   effbd_real=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_real="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_real="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;

  */

  TString title = TString::Format("correlations_quark%i_250GeV_%s_btag1_%0.1f_btag2_%0.1f_nbins%i.root",quark,pol.Data(),btag1,btag2,nbins);
  if(rad==1) title = TString::Format("correlations_quark%i_250GeV_radiative_%s_btag1_%0.1f_btag2_%0.1f_nbins%i.root",quark,pol.Data(),btag1,btag2,nbins);
  
  TFile *MyFile = new TFile(title,"RECREATE");
  MyFile->cd();
  /*  fH->Divide(Nqj);
      fE->Divide(Nqj);*/
  fH->Write();
  fE->Write();
  Nqj->Write();
  Nq->Write();

  grho->SetName("rho");
  grho->SetTitle("Correlation Factor");
  grho->GetXaxis()->SetTitle("|cos(#theta)|");
  grho->GetYaxis()->SetTitle("%");
  grho->Write();

  grhoLEP->SetName("rhoLEP");
  grhoLEP->SetTitle("Correlation Factor");
  grhoLEP->GetXaxis()->SetTitle("|cos(#theta)|");
  grhoLEP->GetYaxis()->SetTitle("%");
  grhoLEP->Write();

  geffb->SetName("effb");
  geffb->SetTitle("Single b-tagging");
  geffb->GetXaxis()->SetTitle("|cos(#theta)|");
  geffb->GetYaxis()->SetTitle("%");
  geffb->Write();

  geffbd->SetName("effbd");
  geffbd->SetTitle("Double b-tagging");
  geffbd->GetXaxis()->SetTitle("|cos(#theta)|");
  geffbd->GetYaxis()->SetTitle("%");
  geffbd->Write();

  geff2j->SetName("eff2j");
  if(quark>3)  geff2j->SetTitle(TString::Format("Two jet selection eff (for quark_id=%i)",quark));
  else geff2j->SetTitle("Two jet selection eff (for quark_id=1,2,3)");
  geff2j->GetXaxis()->SetTitle("|cos(#theta)|");
  geff2j->GetYaxis()->SetTitle("%");
  geff2j->Write();

  // onlybtag
  fH_onlybtag->Write();
  fE_onlybtag->Write();
  
  grho_onlybtag->SetName("rho_onlybtag");
  grho_onlybtag->SetTitle("Correlation Factor");
  grho_onlybtag->GetXaxis()->SetTitle("|cos(#theta)|");
  grho_onlybtag->GetYaxis()->SetTitle("%");
  grho_onlybtag->Write();

  grhoLEP_onlybtag->SetName("rhoLEP_onlybtag");
  grhoLEP_onlybtag->SetTitle("Correlation Factor");
  grhoLEP_onlybtag->GetXaxis()->SetTitle("|cos(#theta)|");
  grhoLEP_onlybtag->GetYaxis()->SetTitle("%");
  grhoLEP_onlybtag->Write();
  
  geffb_onlybtag->SetName("effb_onlybtag");
  geffb_onlybtag->SetTitle("Single b-tagging");
  geffb_onlybtag->GetXaxis()->SetTitle("|cos(#theta)|");
  geffb_onlybtag->GetYaxis()->SetTitle("%");
  geffb_onlybtag->Write();

  geffbd_onlybtag->SetName("effbd_onlybtag");
  geffbd_onlybtag->SetTitle("Double b-tagging");
  geffbd_onlybtag->GetXaxis()->SetTitle("|cos(#theta)|");
  geffbd_onlybtag->GetYaxis()->SetTitle("%");
  geffbd_onlybtag->Write();

  // Bc
  fH_Bc->Write();
  fE_Bc->Write();
  
  grho_Bc->SetName("rho_Bc");
  grho_Bc->SetTitle("Correlation Factor");
  grho_Bc->GetXaxis()->SetTitle("|cos(#theta)|");
  grho_Bc->GetYaxis()->SetTitle("%");
  grho_Bc->Write();

  grhoLEP_Bc->SetName("rhoLEP_Bc");
  grhoLEP_Bc->SetTitle("Correlation Factor");
  grhoLEP_Bc->GetXaxis()->SetTitle("|cos(#theta)|");
  grhoLEP_Bc->GetYaxis()->SetTitle("%");
  grhoLEP_Bc->Write();
  
  geffb_Bc->SetName("effb_Bc");
  geffb_Bc->SetTitle("Single b-tagging");
  geffb_Bc->GetXaxis()->SetTitle("|cos(#theta)|");
  geffb_Bc->GetYaxis()->SetTitle("%");
  geffb_Bc->Write();

  geffbd_Bc->SetName("effbd_Bc");
  geffbd_Bc->SetTitle("Double b-tagging");
  geffbd_Bc->GetXaxis()->SetTitle("|cos(#theta)|");
  geffbd_Bc->GetYaxis()->SetTitle("%");
  geffbd_Bc->Write();

  fH_Kc->Write();
  fE_Kc->Write();
  
  grho_Kc->SetName("rho_Kc");
  grho_Kc->SetTitle("Correlation Factor");
  grho_Kc->GetXaxis()->SetTitle("|cos(#theta)|");
  grho_Kc->GetYaxis()->SetTitle("%");
  grho_Kc->Write();

  grhoLEP_Kc->SetName("rhoLEP_Kc");
  grhoLEP_Kc->SetTitle("Correlation Factor");
  grhoLEP_Kc->GetXaxis()->SetTitle("|cos(#theta)|");
  grhoLEP_Kc->GetYaxis()->SetTitle("%");
  grhoLEP_Kc->Write();
  
  geffb_Kc->SetName("effb_Kc");
  geffb_Kc->SetTitle("Single b-tagging");
  geffb_Kc->GetXaxis()->SetTitle("|cos(#theta)|");
  geffb_Kc->GetYaxis()->SetTitle("%");
  geffb_Kc->Write();

  geffbd_Kc->SetName("effbd_Kc");
  geffbd_Kc->SetTitle("Double b-tagging");
  geffbd_Kc->GetXaxis()->SetTitle("|cos(#theta)|");
  geffbd_Kc->GetYaxis()->SetTitle("%");
  geffbd_Kc->Write();
  /*
    fH_real->Write();
    fE_real->Write();
  
    grho_real->SetName("rho_real");
    grho_real->SetTitle("Correlation Factor");
    grho_real->GetXaxis()->SetTitle("|cos(#theta)|");
    grho_real->GetYaxis()->SetTitle("%");
    grho_real->Write();

    grhoLEP_real->SetName("rhoLEP_real");
    grhoLEP_real->SetTitle("Correlation Factor");
    grhoLEP_real->GetXaxis()->SetTitle("|cos(#theta)|");
    grhoLEP_real->GetYaxis()->SetTitle("%");
    grhoLEP_real->Write();
  
    geffb_real->SetName("effb_real");
    geffb_real->SetTitle("Single b-tagging");
    geffb_real->GetXaxis()->SetTitle("|cos(#theta)|");
    geffb_real->GetYaxis()->SetTitle("%");
    geffb_real->Write();

    geffbd_real->SetName("effbd_real");
    geffbd_real->SetTitle("Double b-tagging");
    geffbd_real->GetXaxis()->SetTitle("|cos(#theta)|");
    geffbd_real->GetYaxis()->SetTitle("%");
    geffbd_real->Write();

  */
  

}



void effstudies::Analysis_rho_ccharge(int n_entries=-1, TString pol="eL", int quark=5, int rad=0)
{

  TH1F* fH= new TH1F("NH","NH",nbins/2,0,1.0);
  TH1F* fE= new TH1F("NE","NE",nbins/2,0,1.0);
  TH1F* Nq= new TH1F("Nq","Nq",nbins/2,0,1.0);
  TH1F* Nqj= new TH1F("Nqj","Nqj",nbins/2,0,1.0); 
  fH->Sumw2();
  fE->Sumw2();
  Nqj->Sumw2();
  Nq->Sumw2();

  TH1F* fH_Bc= new TH1F("NH_Bc","NH_Bc",nbins/2,0,1.0);
  TH1F* fE_Bc= new TH1F("NE_Bc","NE_Bc",nbins/2,0,1.0);
  fH_Bc->Sumw2();
  fE_Bc->Sumw2();

  TH1F* fH_Kc= new TH1F("NH_Kc","NH_Kc",nbins/2,0,1.0);
  TH1F* fE_Kc= new TH1F("NE_Kc","NE_Kc",nbins/2,0,1.0);
  fH_Kc->Sumw2();
  fE_Kc->Sumw2();

  TH1F* fH_real= new TH1F("NH_real","NH_real",nbins/2,0,1.0);
  TH1F* fE_real= new TH1F("NE_real","NE_real",nbins/2,0,1.0);
  fH_real->Sumw2();
  fE_real->Sumw2();
    
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

    float costheta_bbbar;
    std::vector<float> p_bbar;
    p_bbar.push_back(mc_quark_px[0]-mc_quark_px[1]);
    p_bbar.push_back(mc_quark_py[0]-mc_quark_py[1]);
    p_bbar.push_back(mc_quark_pz[0]-mc_quark_pz[1]);
    costheta_bbbar=GetCostheta(p_bbar);


    //    if(bbmass>200 && fabs(costheta_bbbar)<0.8) Rt++;
    if(rad==0) {
      if(quark<4) {
	if( (fabs(mc_quark_pdg[0])!=1 && fabs(mc_quark_pdg[0])!=2  && fabs(mc_quark_pdg[0])!=3) || bbmass<200) continue;
      } else {
	if( fabs(mc_quark_pdg[0])!=quark || bbmass<200) continue;
      }
    } else {
      if(quark<4) {
	if( (fabs(mc_quark_pdg[0])!=1 && fabs(mc_quark_pdg[0])!=2  && fabs(mc_quark_pdg[0])!=3) || bbmass>200) continue;
      } else {
	if( fabs(fabs(mc_quark_pdg[0]))!=quark || bbmass>200) continue;
      }
    }
    
    std::vector<float> pq;
    pq.push_back(jet_px[0]-jet_px[1]);
    pq.push_back(jet_py[0]-jet_py[1]);
    pq.push_back(jet_pz[0]-jet_pz[1]);

    double costhetaq=fabs(GetCostheta(pq));
    Nq->Fill(costhetaq);
    Nq->Fill(costhetaq);
    
    if(rad==0 && PreSelection(5,35)==false) continue;
    if(rad==1 && PreSelection(-5,35)==false) continue;
    
    std::vector<float> p;
    p.push_back(jet_px[0]-jet_px[1]);
    p.push_back(jet_py[0]-jet_py[1]);
    p.push_back(jet_pz[0]-jet_pz[1]);

    double costheta=fabs(GetCostheta(p));
    Nqj->Fill(costheta);
    Nqj->Fill(costheta);
    
    // charge + angles
    int Kc[2];
    Kc[0]=0; Kc[1]=0;

    int Bc[2];
    Bc[0]=0; Bc[1]=0;
      
    for(int ijet=0; ijet<2; ijet++) {
      Bc[ijet]=ChargeBcJet(ijet);
      Kc[ijet]=ChargeKcJet(ijet);
    }

    //Bc or Kc
    bool singletag1=false;
    bool singletag2=false;
    bool Bcbool=false;

    double momvertex[2];
    for(int ijet=0; ijet<2; ijet++) {

      momvertex[ijet]=0;
      double mom_x=0, mom_y=0, mom_z=0;
      double e=0;
      double nt=0;
      for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
	for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
	  nt++;
	  e+=jet_track_E[ijet][ivtx][itrack];
	  mom_x+=jet_track_px[ijet][ivtx][itrack];
	  mom_y+=jet_track_py[ijet][ivtx][itrack];
	  mom_z+=jet_track_pz[ijet][ivtx][itrack];
	}    
      }

      double mass = sqrt(pow(e,2) - pow(mom_x,2) -  pow(mom_y,2) - pow(mom_z,2) );
      double mom= sqrt(pow(mom_x,2) +  pow(mom_y,2) + pow(mom_z,2) );
      momvertex[ijet]=mom;///double(nt);
      //      if(mom/nt<5) continue;
    }
    
    //    if(jet_ctag[0]>ctag1 && (Bc[0]!=0 || Kc[0]!=0) && momvertex[0]>25)singletag1=true;
    //if(jet_ctag[1]>ctag2 && (Bc[1]!=0 || Kc[1]!=0) && momvertex[1]>25)singletag2=true;
    
    if(jet_ctag[0]>ctag1 && (Bc[0]!=0 || Kc[0]!=0) ) singletag1=true;
    if(jet_ctag[1]>ctag2 && (Bc[1]!=0 || Kc[1]!=0) ) singletag2=true;
    
    //    if(jet_btag[0]>btag1 && (Bc[0]!=0 || Kc[0]!=0) ) singletag1=true;
    //if(jet_btag[1]>btag2 && (Bc[1]!=0 || Kc[1]!=0) ) singletag2=true;  
    
    if(singletag1==true && singletag2==true )  {
      fE->Fill(costheta);
      fE->Fill(costheta);
    }
    if( singletag1==true ) fH->Fill(costheta);
    if( singletag2==true ) fH->Fill(costheta);

    //Bc
    singletag1=false;
    singletag2=false;

    if(jet_btag[0]>btag1 && Bc[0]!=0 ) singletag1=true;
    if(jet_btag[1]>btag2 && Bc[1]!=0 ) singletag2=true;
    
    if(singletag1==true && singletag2==true)  {
      fE_Bc->Fill(costheta);
      fE_Bc->Fill(costheta);
    }
    if( singletag1==true ) fH_Bc->Fill(costheta);
    if( singletag2==true ) fH_Bc->Fill(costheta);
    //  if(singletag1==true || singletag2==true)  Bcbool=true;

    //Kc    
    singletag1=false;
    singletag2=false;
    
    if(jet_btag[0]>btag1 && Kc[0]!=0 ) singletag1=true;
    if(jet_btag[1]>btag2 && Kc[1]!=0 ) singletag2=true;
    
    if(singletag1==true && singletag2==true)  {
      fE_Kc->Fill(costheta);
      fE_Kc->Fill(costheta);
    }
    if( singletag1==true ) fH_Kc->Fill(costheta);
    if( singletag2==true ) fH_Kc->Fill(costheta);

    /*
    // *********************************8888
    //realistic categories
    singletag1=false;
    singletag2=false;
    bool taken=false;
    
    // BcBc
    if(jet_btag[0]>btag1 && Bc[0]!=0 )singletag1=true;
    if(jet_btag[1]>btag2 && Bc[1]!=0 )singletag2=true;
    
    if(singletag1==true && singletag2==true)  {
    //   fE_real->Fill(costheta);
    // fE_real->Fill(costheta);
    taken = true;
    }
    //   if( singletag1==true ) fH_real->Fill(costheta);
    //	 if( singletag2==true ) fH_real->Fill(costheta);
    
    //KcKc
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Kc[0]!=0 )singletag1=true;
    if(jet_btag[1]>btag2 && Kc[1]!=0 )singletag2=true;
    
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    */
    
    /*
    //BcKc
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Kc[0]==0 && Bc[0]!=0 )singletag1=true;
    if(jet_btag[1]>btag2 && Bc[1]==0 && Kc[1]!=0 )singletag2=true;
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    //KcBc
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Bc[0]==0 && Kc[0]!=0 )singletag1=true;
    if(jet_btag[1]>btag2 && Kc[1]==0 && Bc[1]!=0 )singletag2=true;
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }*/
    /*
    //BcKc_same1
    if(taken==false){
    singletag1=false;
    singletag2=false;
    //   if(jet_btag[0]>btag1 && Bc[1]==0 && Kc[1]==0 && Bc[0]!=0 )singletag1=true;
    if(jet_btag[0]>btag1 && Bc[1]==0 && Kc[1]==0 && Bc[0]!=0 && Kc[0]!=0 )singletag2=true;
    if(singletag2==true)  {
    fE_real->Fill(costheta);
    //	fE_real->Fill(costheta);
    }
    //  if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    //BcKc_same2
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[1]>btag2 && Bc[0]==0 && Kc[0]==0 && Bc[1]!=0 && Kc[1]!=0)singletag1=true;
    //  if(jet_btag[1]>0.2 && Bc[0]==0 && Kc[0]==0 && Kc[1]!=0 )singletag2=true;
    if(singletag1==true )  {
    fE_real->Fill(costheta);
    //	fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    //  if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    */
    
    /*    
    // *********************************8888
    //realistic categories
    singletag1=false;
    singletag2=false;
    bool taken;
    
    // BcBc
    if(jet_btag[0]>btag1 && Bc[0]!=0 )singletag1=true;
    if(jet_btag[1]>btag2 && Bc[1]!=0 )singletag2=true;
    
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;

    //KcKc
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Kc[0]!=0 )singletag1=true;
    if(jet_btag[1]>0.2 && Kc[1]!=0 )singletag2=true;
    
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    //BcKc
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Bc[1]==0 && Kc[0]==0 && Bc[0]!=0 )singletag1=true;
    if(jet_btag[1]>0.2 && Bc[1]==0 && Kc[0]==0 && Kc[1]!=0 )singletag2=true;
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    //KcBc
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Bc[0]==0 && Kc[1]==0 && Kc[0]!=0 )singletag1=true;
    if(jet_btag[1]>btag2 && Bc[0]==0 && Kc[1]==0 && Bc[1]!=0 )singletag2=true;
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    //BcKc_same1
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[0]>btag1 && Bc[1]==0 && Kc[1]==0 && Bc[0]!=0 )singletag1=true;
    if(jet_btag[0]>btag1 && Bc[1]==0 && Kc[1]==0 && Kc[0]!=0 )singletag2=true;
    if(singletag1==true && singletag2==true && Bc[0]*Kc[0]>0)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    //BcKc_same2
    if(taken==false){
    singletag1=false;
    singletag2=false;
    if(jet_btag[1]>btag2 && Bc[0]==0 && Kc[0]==0 && Bc[1]!=0 )singletag1=true;
    if(jet_btag[1]>0.2 && Bc[0]==0 && Kc[0]==0 && Kc[1]!=0 )singletag2=true;
    if(singletag1==true && singletag2==true)  {
    fE_real->Fill(costheta);
    fE_real->Fill(costheta);
    }
    if( singletag1==true ) fH_real->Fill(costheta);
    if( singletag2==true ) fH_real->Fill(costheta);
    taken = true;
    }
    */
 
    
    
  }

  // *****************************************************************************************88
  //Bc or Kc
  double fH_total=0;
  double fE_total=0;
  double Nqj_total=0;

  double fH_08=0;
  double fE_08=0;
  double Nqj_08=0;
  
  double cos[100];
  double rho[100];
  double rhoLEP[100];
  double ecos[100];
  double erho[100];
  double erhoLEP[100];
  double effb[100];
  double effbd[100];
  double error_effb[100];
  double error_effbd[100];

  double eff2j[100];
  double error_eff2j[100];

  for(int i=0; i<nbins/2; i++) {
    cos[i]=0;
    rho[i]=0;
    ecos[i]=0;
    erho[i]=0;
    rhoLEP[i]=0;
    erhoLEP[i]=0;
    eff2j[i]=0;
    error_eff2j[i]=0;
    
    cos[i]=fH->GetBinCenter(i+1);
    ecos[i]=0;
    
    fH_total+=fH->GetBinContent(i+1);
    fE_total+=fE->GetBinContent(i+1);
    Nqj_total+=Nqj->GetBinContent(i+1);

    if(nbins==40 && i<16) {
      fH_08+=fH->GetBinContent(i+1);
      fE_08+=fE->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    if(nbins==20 && i<8) {
      fH_08+=fH->GetBinContent(i+1);
      fE_08+=fE->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    effb[i]=fH->GetBinContent(i+1)/Nqj->GetBinContent(i+1);
    effbd[i]=fE->GetBinContent(i+1)/Nqj->GetBinContent(i+1);

    error_effb[i]=sqrt(pow(sqrt(fH->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fH->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    error_effbd[i]=sqrt(pow(sqrt(fE->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fE->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    double der_effbd=1./(effb[i]-effb[i]*effb[i]);
    double der_effb=(effbd[i]-2.*effbd[i]*effb[i]+effb[i]*effb[i])/((effb[i]-1.)*(effb[i]-1.)*effb[i]*effb[i]);

    rho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    rhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );
 
    effb[i]*=100.;
    effbd[i]*=100.;
    error_effb[i]*=100.;
    error_effbd[i]*=100.;

    eff2j[i]=Nqj->GetBinContent(i+1)/Nq->GetBinContent(i+1);
    error_eff2j[i]=sqrt(pow(sqrt(Nqj->GetBinContent(i+1))/Nq->GetBinContent(i+1),2) + pow(Nqj->GetBinContent(i+1)*sqrt(Nq->GetBinContent(i+1))/(Nq->GetBinContent(i+1)*Nq->GetBinContent(i+1)),2));

    eff2j[i]*=100.;
    error_eff2j[i]*=100.;
  }

  TGraphErrors* grho= new TGraphErrors(nbins/2,cos,rho,ecos,erho);
  TGraphErrors* grhoLEP= new TGraphErrors(nbins/2,cos,rhoLEP,ecos,erhoLEP);
  TGraphErrors* geffb= new TGraphErrors(nbins/2,cos,effb,ecos,error_effb); 
  TGraphErrors* geffbd= new TGraphErrors(nbins/2,cos,effbd,ecos,error_effbd);
  TGraphErrors* geff2j= new TGraphErrors(nbins/2,cos,eff2j,ecos,error_eff2j); 

  double effb_=fH_total/Nqj_total;
  double effbd_=fE_total/Nqj_total;
  double error_effb_=sqrt(pow(sqrt(fH_total)/Nqj_total,2) + pow(fH_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  double error_effbd_=sqrt(pow(sqrt(fE_total)/Nqj_total,2) + pow(fE_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  double der_effbd=1./(effb_-effb_*effb_);
  double der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);

  double rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  double erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );

  double rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  double erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
 
  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  std::cout<<" ----------------------------------------------------------------------  "<< std::endl;
  std::cout<<" case Bc and/or Kc "<< std::endl;
  std::cout<<"  "<< std::endl;

  std::cout<<" fH="<<fH_total<<"   Nqj=" <<Nqj_total<< "   effb=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE="<<fE_total<<"   Nqj=" <<Nqj_total<< "   effbd=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;
  
  std::cout<<"cos(theta)<0.8  "<< std::endl;
  effb_=fH_08/Nqj_08;
  effbd_=fE_08/Nqj_08;
  error_effb_=sqrt(pow(sqrt(fH_08)/Nqj_08,2) + pow(fH_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  error_effbd_=sqrt(pow(sqrt(fE_08)/Nqj_08,2) + pow(fE_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);
  
  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
   
  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  std::cout<<" fH="<<fH_08<<"   Nqj=" <<Nqj_08<< "   effb=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE="<<fE_08<<"   Nqj=" <<Nqj_08<< "   effbd=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;

  // *****************************************************************************************88
  //Bc 
  fH_total=0;
  fE_total=0;
  Nqj_total=0;
   
  fH_08=0;
  fE_08=0;
  Nqj_08=0;
   
  for(int i=0; i<nbins/2; i++) {
    cos[i]=0;
    rho[i]=0;
    ecos[i]=0;
    erho[i]=0;
    rhoLEP[i]=0;
    erhoLEP[i]=0;
    
    cos[i]=fH_Bc->GetBinCenter(i+1);
    ecos[i]=0;
    
    fH_total+=fH_Bc->GetBinContent(i+1);
    fE_total+=fE_Bc->GetBinContent(i+1);
    Nqj_total+=Nqj->GetBinContent(i+1);

    if(nbins==40 && i<16) {
      fH_08+=fH_Bc->GetBinContent(i+1);
      fE_08+=fE_Bc->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    if(nbins==20 && i<8) {
      fH_08+=fH_Bc->GetBinContent(i+1);
      fE_08+=fE_Bc->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    effb[i]=fH_Bc->GetBinContent(i+1)/Nqj->GetBinContent(i+1);
    effbd[i]=fE_Bc->GetBinContent(i+1)/Nqj->GetBinContent(i+1);

    error_effb[i]=sqrt(pow(sqrt(fH_Bc->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fH_Bc->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    error_effbd[i]=sqrt(pow(sqrt(fE_Bc->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fE_Bc->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    double der_effbd=1./(effb[i]-effb[i]*effb[i]);
    double der_effb=(effbd[i]-2.*effbd[i]*effb[i]+effb[i]*effb[i])/((effb[i]-1.)*(effb[i]-1.)*effb[i]*effb[i]);

    rho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    rhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    
    effb[i]*=100.;
    effbd[i]*=100.;
    error_effb[i]*=100.;
    error_effbd[i]*=100.;   
  }

  TGraphErrors* grho_Bc= new TGraphErrors(nbins/2,cos,rho,ecos,erho);
  TGraphErrors* grhoLEP_Bc= new TGraphErrors(nbins/2,cos,rhoLEP,ecos,erhoLEP);
  TGraphErrors* geffb_Bc= new TGraphErrors(nbins/2,cos,effb,ecos,error_effb); 
  TGraphErrors* geffbd_Bc= new TGraphErrors(nbins/2,cos,effbd,ecos,error_effbd);

  effb_=fH_total/Nqj_total;
  effbd_=fE_total/Nqj_total;
  error_effb_=sqrt(pow(sqrt(fH_total)/Nqj_total,2) + pow(fH_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  error_effbd_=sqrt(pow(sqrt(fE_total)/Nqj_total,2) + pow(fE_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);

  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );

  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  
  std::cout<<" ----------------------------------------------------------------------  "<< std::endl;
  std::cout<<" case Bc "<< std::endl;
  std::cout<<"  "<< std::endl;

  std::cout<<" fH_Bc="<<fH_total<<"   Nqj=" <<Nqj_total<< "   effb=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_Bc="<<fE_total<<"   Nqj=" <<Nqj_total<< "   effbd=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_Bc="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_Bc="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;
  
  std::cout<<"cos(theta)<0.8  "<< std::endl;
  effb_=fH_08/Nqj_08;
  effbd_=fE_08/Nqj_08;
  error_effb_=sqrt(pow(sqrt(fH_08)/Nqj_08,2) + pow(fH_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  error_effbd_=sqrt(pow(sqrt(fE_08)/Nqj_08,2) + pow(fE_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);
  
  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
   
  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  std::cout<<" fH_Bc="<<fH_08<<"   Nqj=" <<Nqj_08<< "   effb_Bc=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_Bc="<<fE_08<<"   Nqj=" <<Nqj_08<< "   effbd_Bc=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_Bc="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_Bc="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;


  // *****************************************************************************************88
  //Kc 
  fH_total=0;
  fE_total=0;
  Nqj_total=0;
   
  fH_08=0;
  fE_08=0;
  Nqj_08=0;
   
  for(int i=0; i<nbins/2; i++) {
    cos[i]=0;
    rho[i]=0;
    ecos[i]=0;
    erho[i]=0;
    rhoLEP[i]=0;
    erhoLEP[i]=0;
    
    cos[i]=fH_Kc->GetBinCenter(i+1);
    ecos[i]=0;
    
    fH_total+=fH_Kc->GetBinContent(i+1);
    fE_total+=fE_Kc->GetBinContent(i+1);
    Nqj_total+=Nqj->GetBinContent(i+1);

    if(nbins==40 && i<16) {
      fH_08+=fH_Kc->GetBinContent(i+1);
      fE_08+=fE_Kc->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    if(nbins==20 && i<8) {
      fH_08+=fH_Kc->GetBinContent(i+1);
      fE_08+=fE_Kc->GetBinContent(i+1);
      Nqj_08+=Nqj->GetBinContent(i+1);
    }
    effb[i]=fH_Kc->GetBinContent(i+1)/Nqj->GetBinContent(i+1);
    effbd[i]=fE_Kc->GetBinContent(i+1)/Nqj->GetBinContent(i+1);

    error_effb[i]=sqrt(pow(sqrt(fH_Kc->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fH_Kc->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    error_effbd[i]=sqrt(pow(sqrt(fE_Kc->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fE_Kc->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
    double der_effbd=1./(effb[i]-effb[i]*effb[i]);
    double der_effb=(effbd[i]-2.*effbd[i]*effb[i]+effb[i]*effb[i])/((effb[i]-1.)*(effb[i]-1.)*effb[i]*effb[i]);

    rho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    rhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
    erhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    
    effb[i]*=100.;
    effbd[i]*=100.;
    error_effb[i]*=100.;
    error_effbd[i]*=100.;   
  }

  TGraphErrors* grho_Kc= new TGraphErrors(nbins/2,cos,rho,ecos,erho);
  TGraphErrors* grhoLEP_Kc= new TGraphErrors(nbins/2,cos,rhoLEP,ecos,erhoLEP);
  TGraphErrors* geffb_Kc= new TGraphErrors(nbins/2,cos,effb,ecos,error_effb); 
  TGraphErrors* geffbd_Kc= new TGraphErrors(nbins/2,cos,effbd,ecos,error_effbd);

  effb_=fH_total/Nqj_total;
  effbd_=fE_total/Nqj_total;
  error_effb_=sqrt(pow(sqrt(fH_total)/Nqj_total,2) + pow(fH_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  error_effbd_=sqrt(pow(sqrt(fE_total)/Nqj_total,2) + pow(fE_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);

  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );

  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  
  std::cout<<" ----------------------------------------------------------------------  "<< std::endl;
  std::cout<<" case Kc "<< std::endl;
  std::cout<<"  "<< std::endl;

  std::cout<<" fH_Kc="<<fH_total<<"   Nqj=" <<Nqj_total<< "   effb=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_Kc="<<fE_total<<"   Nqj=" <<Nqj_total<< "   effbd=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_Kc="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_Kc="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;
  
  std::cout<<"cos(theta)<0.8  "<< std::endl;
  effb_=fH_08/Nqj_08;
  effbd_=fE_08/Nqj_08;
  error_effb_=sqrt(pow(sqrt(fH_08)/Nqj_08,2) + pow(fH_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  error_effbd_=sqrt(pow(sqrt(fE_08)/Nqj_08,2) + pow(fE_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);
  
  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
   
  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  std::cout<<" fH_Kc="<<fH_08<<"   Nqj=" <<Nqj_08<< "   effb_Kc=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_Kc="<<fE_08<<"   Nqj=" <<Nqj_08<< "   effbd_Kc=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_Kc="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_Kc="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;

  /*
  // *****************************************************************************************88
  //real 
  fH_total=0;
  fE_total=0;
  Nqj_total=0;
   
  fH_08=0;
  fE_08=0;
  Nqj_08=0;
   
  for(int i=0; i<nbins/2; i++) {
  cos[i]=0;
  rho[i]=0;
  ecos[i]=0;
  erho[i]=0;
  rhoLEP[i]=0;
  erhoLEP[i]=0;
    
  cos[i]=fH_real->GetBinCenter(i+1);
  ecos[i]=0;
    
  fH_total+=fH_real->GetBinContent(i+1);
  fE_total+=fE_real->GetBinContent(i+1);
  Nqj_total+=Nqj->GetBinContent(i+1);

  if(nbins==40 && i<16) {
  fH_08+=fH_real->GetBinContent(i+1);
  fE_08+=fE_real->GetBinContent(i+1);
  Nqj_08+=Nqj->GetBinContent(i+1);
  }
  if(nbins==20 && i<8) {
  fH_08+=fH_real->GetBinContent(i+1);
  fE_08+=fE_real->GetBinContent(i+1);
  Nqj_08+=Nqj->GetBinContent(i+1);
  }
  effb[i]=fH_real->GetBinContent(i+1)/Nqj->GetBinContent(i+1);
  effbd[i]=fE_real->GetBinContent(i+1)/Nqj->GetBinContent(i+1);

  error_effb[i]=sqrt(pow(sqrt(fH_real->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fH_real->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
  error_effbd[i]=sqrt(pow(sqrt(fE_real->GetBinContent(i+1))/Nqj->GetBinContent(i+1),2) + pow(fE_real->GetBinContent(i+1)*sqrt(Nqj->GetBinContent(i+1))/(Nqj->GetBinContent(i+1)*Nqj->GetBinContent(i+1)),2));
  double der_effbd=1./(effb[i]-effb[i]*effb[i]);
  double der_effb=(effbd[i]-2.*effbd[i]*effb[i]+effb[i]*effb[i])/((effb[i]-1.)*(effb[i]-1.)*effb[i]*effb[i]);

  rho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
  erho[i]=100.*Error(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

  rhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(0);//(effbd[i]-effb[i]*effb[i])/(effb[i]-effb[i]*effb[i]);
  erhoLEP[i]=100.*ErrorLEP(effb[i],error_effb[i],effbd[i],error_effbd[i]).at(1);//sqrt( pow(error_effbd[i]*der_effbd,2) + pow(error_effb[i]*der_effb,2) );

    
  effb[i]*=100.;
  effbd[i]*=100.;
  error_effb[i]*=100.;
  error_effbd[i]*=100.;   
  }

  TGraphErrors* grho_real= new TGraphErrors(nbins/2,cos,rho,ecos,erho);
  TGraphErrors* grhoLEP_real= new TGraphErrors(nbins/2,cos,rhoLEP,ecos,erhoLEP);
  TGraphErrors* geffb_real= new TGraphErrors(nbins/2,cos,effb,ecos,error_effb); 
  TGraphErrors* geffbd_real= new TGraphErrors(nbins/2,cos,effbd,ecos,error_effbd);

  effb_=fH_total/Nqj_total;
  effbd_=fE_total/Nqj_total;
  error_effb_=sqrt(pow(sqrt(fH_total)/Nqj_total,2) + pow(fH_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  error_effbd_=sqrt(pow(sqrt(fE_total)/Nqj_total,2) + pow(fE_total*sqrt(Nqj_total)/(Nqj_total*Nqj_total),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);

  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );

  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  
  std::cout<<" ----------------------------------------------------------------------  "<< std::endl;
  std::cout<<" case real "<< std::endl;
  std::cout<<"  "<< std::endl;

  std::cout<<" fH_real="<<fH_total<<"   Nqj=" <<Nqj_total<< "   effb=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_real="<<fE_total<<"   Nqj=" <<Nqj_total<< "   effbd=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_real="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_real="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;
  
  std::cout<<"cos(theta)<0.8  "<< std::endl;
  effb_=fH_08/Nqj_08;
  effbd_=fE_08/Nqj_08;
  error_effb_=sqrt(pow(sqrt(fH_08)/Nqj_08,2) + pow(fH_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  error_effbd_=sqrt(pow(sqrt(fE_08)/Nqj_08,2) + pow(fE_08*sqrt(Nqj_08)/(Nqj_08*Nqj_08),2));
  der_effbd=1./(effb_-effb_*effb_);
  der_effb=(effbd_-2.*effbd_*effb_+effb_*effb_)/((effb_-1.)*(effb_-1.)*effb_*effb_);
  
  rho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erho_=100.*Error(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
  rhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(0);//(effbd_-effb_*effb_)/(effb_-effb_*effb_);//
  erhoLEP_=100.*ErrorLEP(effb_,error_effb_,effbd_,error_effbd_).at(1);//sqrt( pow(error_effbd_*der_effbd,2) + pow(error_effb_*der_effb,2) );
   
  effb_*=100.;
  effbd_*=100.;
  error_effb_*=100.;
  error_effbd_*=100.;
  std::cout<<" fH_real="<<fH_08<<"   Nqj=" <<Nqj_08<< "   effb_real=" <<effb_ << "+-"<<error_effb_<<" %"<<std::endl;
  std::cout<<" fE_real="<<fE_08<<"   Nqj=" <<Nqj_08<< "   effbd_real=" <<effbd_<< "+-"<<error_effbd_<<" %"<< std::endl;
  std::cout<<" rho_real="<< rho_ <<"+-"<< erho_<<" %"<<std::endl;
  std::cout<<" rhoLEP_real="<< rhoLEP_ <<"+-"<< erhoLEP_<<" %"<<std::endl;
  std::cout<<" "<< std::endl;

  */

  TString title = TString::Format("cc_correlations_quark%i_250GeV_%s_ctag1_%0.1f_ctag2_%0.1f_nbins%i.root",quark,pol.Data(),ctag1,ctag2,nbins);
  if(rad==1) title = TString::Format("cc_correlations_quark%i_250GeV_radiative_%s_ctag1_%0.1f_ctag2_%0.1f_nbins%i.root",quark,pol.Data(),ctag1,ctag2,nbins);
  
  TFile *MyFile = new TFile(title,"RECREATE");
  MyFile->cd();
  /*  fH->Divide(Nqj);
      fE->Divide(Nqj);*/
  fH->Write();
  fE->Write();
  Nqj->Write();
  Nq->Write();

  grho->SetName("rho");
  grho->SetTitle("Correlation Factor");
  grho->GetXaxis()->SetTitle("|cos(#theta)|");
  grho->GetYaxis()->SetTitle("%");
  grho->Write();

  grhoLEP->SetName("rhoLEP");
  grhoLEP->SetTitle("Correlation Factor");
  grhoLEP->GetXaxis()->SetTitle("|cos(#theta)|");
  grhoLEP->GetYaxis()->SetTitle("%");
  grhoLEP->Write();

  geffb->SetName("effb");
  geffb->SetTitle("Single b-tagging");
  geffb->GetXaxis()->SetTitle("|cos(#theta)|");
  geffb->GetYaxis()->SetTitle("%");
  geffb->Write();

  geffbd->SetName("effbd");
  geffbd->SetTitle("Double b-tagging");
  geffbd->GetXaxis()->SetTitle("|cos(#theta)|");
  geffbd->GetYaxis()->SetTitle("%");
  geffbd->Write();

  geff2j->SetName("eff2j");
  if(quark>3)  geff2j->SetTitle(TString::Format("Two jet selection eff (for quark_id=%i)",quark));
  else geff2j->SetTitle("Two jet selection eff (for quark_id=1,2,3)");
  geff2j->GetXaxis()->SetTitle("|cos(#theta)|");
  geff2j->GetYaxis()->SetTitle("%");
  geff2j->Write();

  fH_Bc->Write();
  fE_Bc->Write();
  
  grho_Bc->SetName("rho_Bc");
  grho_Bc->SetTitle("Correlation Factor");
  grho_Bc->GetXaxis()->SetTitle("|cos(#theta)|");
  grho_Bc->GetYaxis()->SetTitle("%");
  grho_Bc->Write();

  grhoLEP_Bc->SetName("rhoLEP_Bc");
  grhoLEP_Bc->SetTitle("Correlation Factor");
  grhoLEP_Bc->GetXaxis()->SetTitle("|cos(#theta)|");
  grhoLEP_Bc->GetYaxis()->SetTitle("%");
  grhoLEP_Bc->Write();
  
  geffb_Bc->SetName("effb_Bc");
  geffb_Bc->SetTitle("Single b-tagging");
  geffb_Bc->GetXaxis()->SetTitle("|cos(#theta)|");
  geffb_Bc->GetYaxis()->SetTitle("%");
  geffb_Bc->Write();

  geffbd_Bc->SetName("effbd_Bc");
  geffbd_Bc->SetTitle("Double b-tagging");
  geffbd_Bc->GetXaxis()->SetTitle("|cos(#theta)|");
  geffbd_Bc->GetYaxis()->SetTitle("%");
  geffbd_Bc->Write();

  fH_Kc->Write();
  fE_Kc->Write();
  
  grho_Kc->SetName("rho_Kc");
  grho_Kc->SetTitle("Correlation Factor");
  grho_Kc->GetXaxis()->SetTitle("|cos(#theta)|");
  grho_Kc->GetYaxis()->SetTitle("%");
  grho_Kc->Write();

  grhoLEP_Kc->SetName("rhoLEP_Kc");
  grhoLEP_Kc->SetTitle("Correlation Factor");
  grhoLEP_Kc->GetXaxis()->SetTitle("|cos(#theta)|");
  grhoLEP_Kc->GetYaxis()->SetTitle("%");
  grhoLEP_Kc->Write();
  
  geffb_Kc->SetName("effb_Kc");
  geffb_Kc->SetTitle("Single b-tagging");
  geffb_Kc->GetXaxis()->SetTitle("|cos(#theta)|");
  geffb_Kc->GetYaxis()->SetTitle("%");
  geffb_Kc->Write();

  geffbd_Kc->SetName("effbd_Kc");
  geffbd_Kc->SetTitle("Double b-tagging");
  geffbd_Kc->GetXaxis()->SetTitle("|cos(#theta)|");
  geffbd_Kc->GetYaxis()->SetTitle("%");
  geffbd_Kc->Write();
  /*
    fH_real->Write();
    fE_real->Write();
  
    grho_real->SetName("rho_real");
    grho_real->SetTitle("Correlation Factor");
    grho_real->GetXaxis()->SetTitle("|cos(#theta)|");
    grho_real->GetYaxis()->SetTitle("%");
    grho_real->Write();

    grhoLEP_real->SetName("rhoLEP_real");
    grhoLEP_real->SetTitle("Correlation Factor");
    grhoLEP_real->GetXaxis()->SetTitle("|cos(#theta)|");
    grhoLEP_real->GetYaxis()->SetTitle("%");
    grhoLEP_real->Write();
  
    geffb_real->SetName("effb_real");
    geffb_real->SetTitle("Single b-tagging");
    geffb_real->GetXaxis()->SetTitle("|cos(#theta)|");
    geffb_real->GetYaxis()->SetTitle("%");
    geffb_real->Write();

    geffbd_real->SetName("effbd_real");
    geffbd_real->SetTitle("Double b-tagging");
    geffbd_real->GetXaxis()->SetTitle("|cos(#theta)|");
    geffbd_real->GetYaxis()->SetTitle("%");
    geffbd_real->Write();

  */
  

}


void effstudies::QuarkTaggingTests(int n_entries=-1, TString polarization="eL")
{


  // ----------------------
  TH1F* h_multiplicity_vtx_b = new TH1F("multiplicity_vtx_b","multiplicity_vtx_b",8,-0.5,7.5);
  TH1F* h_multiplicity_vtx_c = new TH1F("multiplicity_vtx_c","multiplicity_vtx_c",8,-0.5,7.5);
  TH1F* h_multiplicity_vtx_q = new TH1F("multiplicity_vtx_q","multiplicity_vtx_q",8,-0.5,7.5);

  TH1F* h_multiplicity_tracks_b = new TH1F("multiplicity_tracks_b","multiplicity_tracks_b",30,-0.5,29.5);
  TH1F* h_multiplicity_tracks_c = new TH1F("multiplicity_tracks_c","multiplicity_tracks_c",30,-0.5,29.5);
  TH1F* h_multiplicity_tracks_q = new TH1F("multiplicity_tracks_q","multiplicity_tracks_q",30,-0.5,29.5);

  TH1F* h_p_tracks_b = new TH1F("p_tracks_b","p_tracks_b",80,-0.5,79.5);
  TH1F* h_p_tracks_c = new TH1F("p_tracks_c","p_tracks_c",80,-0.5,79.5);
  TH1F* h_p_tracks_q = new TH1F("p_tracks_q","p_tracks_q",80,-0.5,79.5);

  
  TH1F* h_norm_multiplicity_vtx_b = new TH1F("norm_multiplicity_vtx_b","norm_multiplicity_vtx_b",8,-0.5,7.5);
  TH1F* h_norm_multiplicity_vtx_c = new TH1F("norm_multiplicity_vtx_c","norm_multiplicity_vtx_c",8,-0.5,7.5);
  TH1F* h_norm_multiplicity_vtx_q = new TH1F("norm_multiplicity_vtx_q","norm_multiplicity_vtx_q",8,-0.5,7.5);

  TH1F* h_norm_multiplicity_tracks_b = new TH1F("norm_multiplicity_tracks_b","norm_multiplicity_tracks_b",30,-0.5,29.5);
  TH1F* h_norm_multiplicity_tracks_c = new TH1F("norm_multiplicity_tracks_c","norm_multiplicity_tracks_c",30,-0.5,29.5);
  TH1F* h_norm_multiplicity_tracks_q = new TH1F("norm_multiplicity_tracks_q","norm_multiplicity_tracks_q",30,-0.5,29.5);

  // ----------------------
  TH1F* h_mass_vtx_b = new TH1F("mass_vtx_b","mass_vtx_b",100,0.15,10.15);
  TH1F* h_mass_vtx_c = new TH1F("mass_vtx_c","mass_vtx_c",100,0.15,10.15);
  TH1F* h_mass_vtx_q = new TH1F("mass_vtx_q","mass_vtx_q",100,0.15,10.15);

  TH1F* h_norm_mass_vtx_b = new TH1F("norm_mass_vtx_b","norm_mass_vtx_b",100,0.15,10.15);
  TH1F* h_norm_mass_vtx_c = new TH1F("norm_mass_vtx_c","norm_mass_vtx_c",100,0.15,10.15);
  TH1F* h_norm_mass_vtx_q = new TH1F("norm_mass_vtx_q","norm_mass_vtx_q",100,0.15,10.15);

  // ----------------------
  TH1F* h_p_vtx_b = new TH1F("p_vtx_b","p_vtx_b",100,0.5,100.5);
  TH1F* h_p_vtx_c = new TH1F("p_vtx_c","p_vtx_c",100,0.5,100.5);
  TH1F* h_p_vtx_q = new TH1F("p_vtx_q","p_vtx_q",100,0.5,100.5);

  TH1F* h_norm_p_vtx_b = new TH1F("norm_p_vtx_b","norm_p_vtx_b",100,0.5,100.5);
  TH1F* h_norm_p_vtx_c = new TH1F("norm_p_vtx_c","norm_p_vtx_c",100,0.5,100.5);
  TH1F* h_norm_p_vtx_q = new TH1F("norm_p_vtx_q","norm_p_vtx_q",100,0.5,100.5);

  // ----------------------
  TH1F* h_p_leading_b = new TH1F("p_leading_b","p_leading_b",100,0.5,100.5);
  TH1F* h_p_leading_c = new TH1F("p_leading_c","p_leading_c",100,0.5,100.5);
  TH1F* h_p_leading_q = new TH1F("p_leading_q","p_leading_q",100,0.5,100.5);

  TH1F* h_p_track_average_b = new TH1F("p_track_average_b","p_track_average_b",200,0.5,100.5);
  TH1F* h_p_track_average_c = new TH1F("p_track_average_c","p_track_average_c",200,0.5,100.5);
  TH1F* h_p_track_average_q = new TH1F("p_track_average_q","p_track_average_q",200,0.5,100.5);


  // ----------------------
  TH2F* h_mass_p_vtx_b = new TH2F("mass_p_vtx_b","mass_p_vtx_b",250,0,250,100,0.5,100.5);
  TH2F* h_mass_p_vtx_c = new TH2F("mass_p_vtx_c","mass_p_vtx_c",250,0,250,100,0.5,100.5);
  TH2F* h_mass_p_vtx_q = new TH2F("mass_p_vtx_q","mass_p_vtx_q",250,0,250,100,0.5,100.5);

  TH2F* h_average_p_vtx_b = new TH2F("average_p_vtx_b","norm_p_vtx_b",100,0.5,100.5,100,0.5,100.5);
  TH2F* h_average_p_vtx_c = new TH2F("average_p_vtx_c","norm_p_vtx_c",100,0.5,100.5,100,0.5,100.5);
  TH2F* h_average_p_vtx_q = new TH2F("average_p_vtx_q","average_p_vtx_q",100,0.5,100.5,100,0.5,100.5);

  // ----------------------
  TH1F* h_btag_b = new TH1F("btag_b","btag_b",100,0,1);
  TH1F* h_btag_c = new TH1F("btag_c","btag_c",100,0,1);
  TH1F* h_btag_q = new TH1F("btag_q","btag_q",100,0,1);

  TH1F* h_norm_btag_b = new TH1F("norm_btag_b","norm_btag_b",100,0,1);
  TH1F* h_norm_btag_c = new TH1F("norm_btag_c","norm_btag_c",100,0,1);
  TH1F* h_norm_btag_q = new TH1F("norm_btag_q","norm_btag_q",100,0,1);

  // ----------------------
  TH1F* h_ctag_b = new TH1F("ctag_b","ctag_b",100,0,1);
  TH1F* h_ctag_c = new TH1F("ctag_c","ctag_c",100,0,1);
  TH1F* h_ctag_q = new TH1F("ctag_q","ctag_q",100,0,1);

  TH1F* h_norm_ctag_b = new TH1F("norm_ctag_b","norm_ctag_b",100,0,1);
  TH1F* h_norm_ctag_c = new TH1F("norm_ctag_c","norm_ctag_c",100,0,1);
  TH1F* h_norm_ctag_q = new TH1F("norm_ctag_q","norm_ctag_q",100,0,1);

  // ----------------------
  TH2F* h_btag_ctag_b = new TH2F("btag_ctag_b","btag_ctag_b",20,0,1,20,0,1);
  TH2F* h_btag_ctag_c = new TH2F("btag_ctag_c","btag_ctag_c",20,0,1,20,0,1);
  TH2F* h_btag_ctag_q = new TH2F("btag_ctag_q","btag_ctag_q",20,0,1,20,0,1);

  TH2F* h_norm_btag_ctag_b = new TH2F("norm_btag_ctag_b","norm_btag_ctag_b",20,0,1,20,0,1);
  TH2F* h_norm_btag_ctag_c = new TH2F("norm_btag_ctag_c","norm_btag_ctag_c",20,0,1,20,0,1);
  TH2F* h_norm_btag_ctag_q = new TH2F("norm_btag_ctag_q","norm_btag_ctag_q",20,0,1,20,0,1);


  //------------------------------------------------------
  // mass
  TH1F* h_mass_b= new TH1F("mass_b","mass_b",250,0,250);
  TH1F* h_mass_c= new TH1F("mass_c","mass_c",250,0,250);
  TH1F* h_mass_q= new TH1F("mass_q","mass_q",250,0,250);

  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();


  TString title="antibtag0.2_antctag0.2_"+polarization+".root";//_pvex20_mass1.5.root";
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //    if(PreSelection(0)==false) continue;
    if(mc_ISR_E[0]+mc_ISR_E[1]>35) continue;

    bool singletag[2];
    singletag[0]=false;
    singletag[1]=false;

    /*
      for(int ijet=0; ijet<2; ijet++) {
      if (jet_btag[ijet]<0.8) singletag[ijet]=true;
      //       continue;
      //       if (jet_btag[ijet]>0.5)
      //singletag[ijet]=true;
      }
      if(singletag[0]==false && singletag[1]==false) continue;
    */
    for(int ijet=0; ijet<2; ijet++) {
       
      if(jet_btag[ijet]>0.2 || jet_ctag[ijet]>0.2) continue;
       
      double mass=0, mom=0;
      for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
	 
	double mom_x=0, mom_y=0, mom_z=0;
	double e=0;
	double nt=0;
	for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
	  for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
	    nt++;
	    e+=jet_track_E[ijet][ivtx][itrack];
	    mom_x+=jet_track_px[ijet][ivtx][itrack];
	    mom_y+=jet_track_py[ijet][ivtx][itrack];
	    mom_z+=jet_track_pz[ijet][ivtx][itrack];
	  }    
	}

       
	mass = sqrt(pow(e,2) - pow(mom_x,2) -  pow(mom_y,2) - pow(mom_z,2) );
	mom= sqrt(pow(mom_x,2) +  pow(mom_y,2) + pow(mom_z,2) )/nt;
      }
      //if(mom<17) continue;
      // if(mass<0.6) continue;
       
      //      if(mass<1.5) continue;

      //      */
      
      //      if (Ctag_2(ijet) == false) continue;
      //  if (Ctag_4(ijet) == false) continue;
      /*      if (Ctag_5(ijet) == false) continue;*/

      int nvtx_total_b=0;
      int nvtx_total_c=0;
      int nvtx_total_q=0;
      int ntracks_total_b=0;
      int ntracks_total_c=0;
      int ntracks_total_q=0;

      double massvtx_total_b=0;
      double massvtx_total_c=0;
      double massvtx_total_q=0;

      double pvtx_total_b=0;
      double pvtx_total_c=0;
      double pvtx_total_q=0;
      
      double e_c=0, px_c=0, py_c=0, pz_c=0;
      double e_b=0, px_b=0, py_b=0, pz_b=0;
      double e_q=0, px_q=0, py_q=0, pz_q=0;

      double massjet=sqrt(pow(jet_E[ijet],2)-pow(jet_px[ijet],2)-pow(jet_py[ijet],2)-pow(jet_pz[ijet],2));
      
      // if(ijet==1) {
      if(fabs(mc_quark_pdg[ijet])==5) {
	h_mass_b->Fill(massjet);
	h_btag_b->Fill(jet_btag[ijet]);
	h_norm_btag_b->Fill(jet_btag[ijet]);
	
	h_ctag_b->Fill(jet_ctag[ijet]);
	h_norm_ctag_b->Fill(jet_ctag[ijet]);

	h_btag_ctag_b->Fill(jet_btag[ijet],jet_ctag[ijet]);
	h_norm_btag_ctag_b->Fill(jet_btag[ijet],jet_ctag[ijet]);
	
      } else 	if(fabs(mc_quark_pdg[ijet])==4) {
	h_mass_c->Fill(massjet);
	h_btag_c->Fill(jet_btag[ijet]);
	h_norm_btag_c->Fill(jet_btag[ijet]);
	
	h_ctag_c->Fill(jet_ctag[ijet]);
	h_norm_ctag_c->Fill(jet_ctag[ijet]);

	h_btag_ctag_c->Fill(jet_btag[ijet],jet_ctag[ijet]);
	h_norm_btag_ctag_c->Fill(jet_btag[ijet],jet_ctag[ijet]);
	
      } else if(fabs(mc_quark_pdg[ijet])<4){
	h_mass_q->Fill(massjet);
	h_btag_q->Fill(jet_btag[ijet]);
	h_norm_btag_q->Fill(jet_btag[ijet]);
	
	h_ctag_q->Fill(jet_ctag[ijet]);
	h_norm_ctag_q->Fill(jet_ctag[ijet]);

	h_btag_ctag_q->Fill(jet_btag[ijet],jet_ctag[ijet]);
	h_norm_btag_ctag_q->Fill(jet_btag[ijet],jet_ctag[ijet]);
	
      } //else continue;

      
	//  }
      // int ntracks_mass2GeV=0;

      double leadingP=0, leadingE=0, leadingPy=0,  leadingPz=0,  leadingPx=0;
      
      for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {

	
	if(fabs(mc_quark_pdg[0])==5)  nvtx_total_b++; 
	else if(fabs(mc_quark_pdg[0])==4) nvtx_total_c++;
	else if(fabs(mc_quark_pdg[0])<4) nvtx_total_q++;
	else continue;
	
	for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
	  if(fabs(mc_quark_pdg[0])==5) {
	    ntracks_total_b++;
	    e_b+=jet_track_E[ijet][ivtx][itrack];
  	    px_b+=jet_track_px[ijet][ivtx][itrack];
	    py_b+=jet_track_py[ijet][ivtx][itrack];
	    pz_b+=jet_track_pz[ijet][ivtx][itrack];

  	    leadingPx=jet_track_px[ijet][ivtx][itrack];
	    leadingPy=jet_track_py[ijet][ivtx][itrack];
	    leadingPz=jet_track_pz[ijet][ivtx][itrack];
	    double temp_leadingP= sqrt(pow(leadingPx,2) +  pow(leadingPy,2) + pow(leadingPz,2) );
	    if(temp_leadingP> leadingP) leadingP=temp_leadingP;

	    double temp_p= sqrt(pow(jet_track_px[ijet][ivtx][itrack],2)+pow(jet_track_py[ijet][ivtx][itrack],2)+pow(jet_track_pz[ijet][ivtx][itrack],2));
	    h_p_tracks_b->Fill(temp_p);
	    
	  } else  if(fabs(mc_quark_pdg[0])==4) {
	    ntracks_total_c++;
	    e_c+=jet_track_E[ijet][ivtx][itrack];
  	    px_c+=jet_track_px[ijet][ivtx][itrack];
	    py_c+=jet_track_py[ijet][ivtx][itrack];
	    pz_c+=jet_track_pz[ijet][ivtx][itrack];

	    leadingPx=jet_track_px[ijet][ivtx][itrack];
	    leadingPy=jet_track_py[ijet][ivtx][itrack];
	    leadingPz=jet_track_pz[ijet][ivtx][itrack];
	    double temp_leadingP= sqrt(pow(leadingPx,2) +  pow(leadingPy,2) + pow(leadingPz,2) );
	    if(temp_leadingP> leadingP) leadingP=temp_leadingP;
	    double temp_p= sqrt(pow(jet_track_px[ijet][ivtx][itrack],2)+pow(jet_track_py[ijet][ivtx][itrack],2)+pow(jet_track_pz[ijet][ivtx][itrack],2));
	    h_p_tracks_c->Fill(temp_p);
	  } else if(fabs(mc_quark_pdg[0])<4){
	    ntracks_total_q++;
	    e_q+=jet_track_E[ijet][ivtx][itrack];
  	    px_q+=jet_track_px[ijet][ivtx][itrack];
	    py_q+=jet_track_py[ijet][ivtx][itrack];
	    pz_q+=jet_track_pz[ijet][ivtx][itrack];

	    leadingPx=jet_track_px[ijet][ivtx][itrack];
	    leadingPy=jet_track_py[ijet][ivtx][itrack];
	    leadingPz=jet_track_pz[ijet][ivtx][itrack];
	    double temp_leadingP= sqrt(pow(leadingPx,2) +  pow(leadingPy,2) + pow(leadingPz,2) );
	    if(temp_leadingP> leadingP) leadingP=temp_leadingP;
	    double temp_p= sqrt(pow(jet_track_px[ijet][ivtx][itrack],2)+pow(jet_track_py[ijet][ivtx][itrack],2)+pow(jet_track_pz[ijet][ivtx][itrack],2));
	    h_p_tracks_q->Fill(temp_p);
	  }
	}
      
      }

      
      massvtx_total_b= sqrt(pow(e_b,2) - pow(px_b,2) -  pow(py_b,2) - pow(pz_b,2) );
      massvtx_total_c= sqrt(pow(e_c,2) - pow(px_c,2) -  pow(py_c,2) - pow(pz_c,2) );
      massvtx_total_q= sqrt(pow(e_q,2) - pow(px_q,2) -  pow(py_q,2) - pow(pz_q,2) );

      pvtx_total_b= sqrt(pow(px_b,2) +  pow(py_b,2) + pow(pz_b,2) );
      pvtx_total_c= sqrt(pow(px_c,2) +  pow(py_c,2) + pow(pz_c,2) );
      pvtx_total_q= sqrt(pow(px_q,2) +  pow(py_q,2) + pow(pz_q,2) );
      

      if(ntracks_total_b> 0 ) {
	h_mass_vtx_b->Fill(massjet);//vtx_total_b);
	h_norm_mass_vtx_b->Fill(massjet);//massvtx_total_b);
	h_p_vtx_b->Fill(pvtx_total_b);
	h_norm_p_vtx_b->Fill(pvtx_total_b);
	h_mass_p_vtx_b->Fill(massjet,pvtx_total_b);//massvtx_total_b,pvtx_total_b);
	h_average_p_vtx_b->Fill(pvtx_total_b,pvtx_total_b/double(ntracks_total_b));
	h_p_leading_b->Fill(leadingP);
	h_p_track_average_b->Fill(pvtx_total_b/double(ntracks_total_b));

      }
      if(ntracks_total_c> 0 ) {
	h_mass_vtx_c->Fill(massvtx_total_c);
	h_norm_mass_vtx_c->Fill(massvtx_total_c);
	h_p_vtx_c->Fill(pvtx_total_c);
	h_norm_p_vtx_c->Fill(pvtx_total_c);
	h_mass_p_vtx_c->Fill(massjet,pvtx_total_c);//massvtx_total_c,pvtx_total_c);
	//	h_norm_mass_p_vtx_c->Fill(massvtx_total_c,pvtx_total_c);
	h_average_p_vtx_c->Fill(pvtx_total_c,pvtx_total_c/double(ntracks_total_c));
	h_p_leading_c->Fill(leadingP);
	h_p_track_average_c->Fill(pvtx_total_c/double(ntracks_total_c));

      }
      if(ntracks_total_q> 0 ) {
	h_mass_vtx_q->Fill(massvtx_total_q);
	h_norm_mass_vtx_q->Fill(massvtx_total_q);
	h_p_vtx_q->Fill(pvtx_total_q);
	h_norm_p_vtx_q->Fill(pvtx_total_q);
	h_mass_p_vtx_q->Fill(massjet,pvtx_total_q);//massvtx_total_q,pvtx_total_q);
	//	h_norm_mass_p_vtx_q->Fill(massvtx_total_q,pvtx_total_q);
	h_average_p_vtx_q->Fill(pvtx_total_q,pvtx_total_q/double(ntracks_total_q));
	h_p_leading_q->Fill(leadingP);
	h_p_track_average_q->Fill(pvtx_total_q/double(ntracks_total_q));
      } 
    
	
      if(ntracks_total_b> 0 ){
	h_multiplicity_tracks_b->Fill(ntracks_total_b);
	h_norm_multiplicity_tracks_b->Fill(ntracks_total_b);
      }
      if(ntracks_total_c> 0  ) {
	h_multiplicity_tracks_c->Fill(ntracks_total_c);
	h_norm_multiplicity_tracks_c->Fill(ntracks_total_c);
      }
      if(ntracks_total_q> 0  ) {
	h_multiplicity_tracks_q->Fill(ntracks_total_q);
	h_norm_multiplicity_tracks_q->Fill(ntracks_total_q);
      }
     
      if(nvtx_total_b>-1) {
	h_multiplicity_vtx_b->Fill(nvtx_total_b);
	h_norm_multiplicity_vtx_b->Fill(nvtx_total_b);
      }

      if(nvtx_total_c>-1) {
	h_multiplicity_vtx_c->Fill(nvtx_total_c);
	h_norm_multiplicity_vtx_c->Fill(nvtx_total_c);
      }
  
      if(nvtx_total_q>-1) {
	h_multiplicity_vtx_q->Fill(nvtx_total_q);
	h_norm_multiplicity_vtx_q->Fill(nvtx_total_q);
      }  
    }
  }

  
  TFile *MyFile = new TFile(title,"RECREATE");
  MyFile->cd();
  h_p_tracks_b->Write();
  h_p_tracks_c->Write();
  h_p_tracks_q->Write();
  h_multiplicity_tracks_b->Write();
  h_multiplicity_tracks_c->Write();
  h_multiplicity_tracks_q->Write();

  TCanvas *c0 = new TCanvas ("c0","c0",800,800);
  c0->cd(1);

  h_mass_q->SetLineColor(4);
  h_mass_c->SetLineWidth(2);
  h_mass_c->GetYaxis()->SetTitle("[a.u]");
  h_mass_c->GetXaxis()->SetTitle("jet mass [GeV]");
  h_mass_c->DrawNormalized("histo");

  h_mass_b->SetLineWidth(2);
  h_mass_b->SetLineColor(2);
  h_mass_b->DrawNormalized("histosame");

  h_mass_q->SetLineWidth(2);
  h_mass_q->SetLineColor(1);
  h_mass_q->DrawNormalized("histosame");
  
  TLegend * leg0 = new TLegend(0.6,0.6,0.85,0.85);
  leg0->AddEntry(h_mass_c,"c-quark","l");
  leg0->AddEntry(h_mass_b,"b-quark","l");
  leg0->AddEntry(h_mass_q,"uds-quark","l");
  leg0->Draw();
  c0->Write();//"lcfiplustags.root.root");

  TCanvas *c1 = new TCanvas ("c1","c1",1800,1800);
  c1->Divide(2,2);
  c1->cd(1);

  h_multiplicity_vtx_q->SetLineColor(4);
  h_multiplicity_vtx_c->SetLineWidth(2);
  h_multiplicity_vtx_c->GetYaxis()->SetTitle("[a.u]");
  h_multiplicity_vtx_c->GetXaxis()->SetTitle("N sec. vertex per jet (>0)");
  h_multiplicity_vtx_c->Draw("histo");

  h_multiplicity_vtx_b->SetLineWidth(2);
  h_multiplicity_vtx_b->SetLineColor(2);
  h_multiplicity_vtx_b->Draw("histosame");

  h_multiplicity_vtx_q->SetLineWidth(2);
  h_multiplicity_vtx_q->SetLineColor(1);
  h_multiplicity_vtx_q->Draw("histosame");
  
  TLegend * leg = new TLegend(0.6,0.6,0.85,0.85);
  leg->AddEntry(h_multiplicity_vtx_c,"c-quark","l");
  leg->AddEntry(h_multiplicity_vtx_b,"b-quark","l");
  leg->AddEntry(h_multiplicity_vtx_q,"uds-quark","l");
  leg->Draw();

  c1->cd(2);
  h_multiplicity_tracks_c->SetLineColor(4);
  h_multiplicity_tracks_c->SetLineWidth(2);
  h_multiplicity_tracks_c->GetYaxis()->SetTitle("[a.u]");
  h_multiplicity_tracks_c->GetXaxis()->SetTitle("N sec. tracks per jet (N-vtx>0)");
  h_multiplicity_tracks_c->Draw("histo");

  h_multiplicity_tracks_b->SetLineWidth(2);
  h_multiplicity_tracks_b->SetLineColor(2);
  h_multiplicity_tracks_b->Draw("histosame");

  h_multiplicity_tracks_q->SetLineWidth(2);
  h_multiplicity_tracks_q->SetLineColor(1);
  h_multiplicity_tracks_q->Draw("histosame");
  
  leg->Draw();
  
  c1->cd(3);
  h_norm_multiplicity_vtx_c->Scale(1.0/h_norm_multiplicity_vtx_c->GetEntries());
  
  h_norm_multiplicity_vtx_c->SetLineColor(4);
  h_norm_multiplicity_vtx_c->SetLineWidth(2);
  h_norm_multiplicity_vtx_c->GetYaxis()->SetTitle("fraction of events");
  h_norm_multiplicity_vtx_c->GetXaxis()->SetTitle("N sec. vertex per jet (>0)");
  h_norm_multiplicity_vtx_c->Draw("histo");

  h_norm_multiplicity_vtx_b->Scale(1.0/h_norm_multiplicity_vtx_b->GetEntries());
  h_norm_multiplicity_vtx_b->SetLineWidth(2);
  h_norm_multiplicity_vtx_b->SetLineColor(2);
  h_norm_multiplicity_vtx_b->Draw("histosame");
  
  h_norm_multiplicity_vtx_q->Scale(1.0/h_norm_multiplicity_vtx_q->GetEntries());
  h_norm_multiplicity_vtx_q->SetLineWidth(2);
  h_norm_multiplicity_vtx_q->SetLineColor(1);
  h_norm_multiplicity_vtx_q->Draw("histosame");
  
  leg->Draw();

  c1->cd(4);
  
  h_norm_multiplicity_tracks_c->Scale(1.0/h_norm_multiplicity_tracks_c->GetEntries());
  h_norm_multiplicity_tracks_c->SetLineColor(4);
  h_norm_multiplicity_tracks_c->SetLineWidth(2);
  h_norm_multiplicity_tracks_c->GetYaxis()->SetTitle("fraction of events");
  h_norm_multiplicity_tracks_c->GetXaxis()->SetTitle("N sec. tracks per jet (N-vtx>0)");
  h_norm_multiplicity_tracks_c->Draw("histo");

  h_norm_multiplicity_tracks_b->Scale(1.0/h_norm_multiplicity_tracks_b->GetEntries());
  h_norm_multiplicity_tracks_b->SetLineWidth(2);
  h_norm_multiplicity_tracks_b->SetLineColor(2);
  h_norm_multiplicity_tracks_b->Draw("histosame");

  h_norm_multiplicity_tracks_q->Scale(1.0/h_norm_multiplicity_tracks_q->GetEntries());
  h_norm_multiplicity_tracks_q->SetLineWidth(2);
  h_norm_multiplicity_tracks_q->SetLineColor(1);
  h_norm_multiplicity_tracks_q->Draw("histosame");
  
  leg->Draw();

  c1->Write();//"multiplicity.root");
  

  TCanvas *c2 = new TCanvas ("c2","c2",1800,1800);
  c2->Divide(2,2);
  c2->cd(1);
  
  h_mass_vtx_c->SetLineColor(4);
  h_mass_vtx_c->SetLineWidth(2);
  h_mass_vtx_c->GetYaxis()->SetTitle("[a.u]");
  h_mass_vtx_c->GetXaxis()->SetTitle("Mass of the sec. vertex [GeV]");
  h_mass_vtx_c->Draw("histo");

  h_mass_vtx_b->SetLineWidth(2);
  h_mass_vtx_b->SetLineColor(2);
  h_mass_vtx_b->Draw("histosame");

  h_mass_vtx_q->SetLineWidth(2);
  h_mass_vtx_q->SetLineColor(1);
  h_mass_vtx_q->Draw("histosame");
  
  leg->Draw();
 
  c2->cd(2);
  h_norm_mass_vtx_c->Scale(1.0/h_norm_mass_vtx_c->GetEntries());
  h_norm_mass_vtx_c->SetLineColor(4);
  h_norm_mass_vtx_c->SetLineWidth(2);
  h_norm_mass_vtx_c->GetYaxis()->SetTitle("fraction of events");
  h_norm_mass_vtx_c->GetXaxis()->SetTitle("Mass of the sec. vertex [GeV]");
  h_norm_mass_vtx_c->Draw("histo");

  h_norm_mass_vtx_b->Scale(1.0/h_norm_mass_vtx_b->GetEntries());
  h_norm_mass_vtx_b->SetLineWidth(2);
  h_norm_mass_vtx_b->SetLineColor(2);
  h_norm_mass_vtx_b->Draw("histosame");
  
  h_norm_mass_vtx_q->Scale(1.0/h_norm_mass_vtx_q->GetEntries());
  h_norm_mass_vtx_q->SetLineWidth(2);
  h_norm_mass_vtx_q->SetLineColor(1);
  h_norm_mass_vtx_q->Draw("histosame");

  c2->cd(3);
  
  h_p_vtx_c->SetLineColor(4);
  h_p_vtx_c->SetLineWidth(2);
  h_p_vtx_c->GetYaxis()->SetTitle("[a.u]");
  h_p_vtx_c->GetXaxis()->SetTitle("momentum of the sec. vertex [GeV]");
  h_p_vtx_c->Draw("histo");

  h_p_vtx_b->SetLineWidth(2);
  h_p_vtx_b->SetLineColor(2);
  h_p_vtx_b->Draw("histosame");

  h_p_vtx_q->SetLineWidth(2);
  h_p_vtx_q->SetLineColor(1);
  h_p_vtx_q->Draw("histosame");
  
  leg->Draw();
 
  c2->cd(4);
  h_norm_p_vtx_c->Scale(1.0/h_norm_p_vtx_c->GetEntries());
  h_norm_p_vtx_c->SetLineColor(4);
  h_norm_p_vtx_c->SetLineWidth(2);
  h_norm_p_vtx_c->GetYaxis()->SetTitle("fraction of events");
  h_norm_p_vtx_c->GetXaxis()->SetTitle("momentum of the sec. vertex [GeV]");
  h_norm_p_vtx_c->Draw("histo");

  h_norm_p_vtx_b->Scale(1.0/h_norm_p_vtx_b->GetEntries());
  h_norm_p_vtx_b->SetLineWidth(2);
  h_norm_p_vtx_b->SetLineColor(2);
  h_norm_p_vtx_b->Draw("histosame");
  
  h_norm_p_vtx_q->Scale(1.0/h_norm_p_vtx_q->GetEntries());
  h_norm_p_vtx_q->SetLineWidth(2);
  h_norm_p_vtx_q->SetLineColor(1);
  h_norm_p_vtx_q->Draw("histosame");

  leg->Draw();
  
  c2->Write();//"mass_p_vtx.root");

  h_norm_p_vtx_b->Write();
  h_norm_p_vtx_c->Write();
  h_norm_p_vtx_q->Write();

  h_p_vtx_b->Write();
  h_p_vtx_c->Write();
  h_p_vtx_q->Write();
  
 
  
  TCanvas *c2_bis = new TCanvas ("c2_bis","c2_bis",1800,1800);
  c2_bis->Divide(2,2);
  c2_bis->cd(1);
  h_p_leading_c->SetLineColor(4);
  h_p_leading_c->SetLineWidth(2);
  h_p_leading_c->GetYaxis()->SetTitle("entries");
  h_p_leading_c->GetXaxis()->SetTitle("momentum of the leading sec. track [GeV]");
  h_p_leading_c->Draw("histo");

  h_p_leading_b->SetLineWidth(2);
  h_p_leading_b->SetLineColor(2);
  h_p_leading_b->Draw("histosame");

  h_p_leading_q->SetLineWidth(2);
  h_p_leading_q->SetLineColor(1);
  h_p_leading_q->Draw("histosame");

  c2_bis->cd(2);
  
  h_p_leading_c->SetLineColor(4);
  h_p_leading_c->SetLineWidth(2);
  h_p_leading_c->GetYaxis()->SetTitle("[a.u.]");
  h_p_leading_c->GetXaxis()->SetTitle("momentum of the leading sec. track [GeV]");
  h_p_leading_c->DrawNormalized("histo");

  h_p_leading_b->SetLineWidth(2);
  h_p_leading_b->SetLineColor(2);
  h_p_leading_b->DrawNormalized("histosame");

  h_p_leading_q->SetLineWidth(2);
  h_p_leading_q->SetLineColor(1);
  h_p_leading_q->DrawNormalized("histosame");
  
  leg->Draw();

  c2_bis->cd(3);
  h_p_track_average_c->SetLineColor(4);
  h_p_track_average_c->SetLineWidth(2);
  h_p_track_average_c->GetYaxis()->SetTitle("entries");
  h_p_track_average_c->GetXaxis()->SetTitle("average sec. track momentum [GeV]");
  h_p_track_average_c->Draw("histo");

  h_p_track_average_b->SetLineWidth(2);
  h_p_track_average_b->SetLineColor(2);
  h_p_track_average_b->Draw("histosame");

  h_p_track_average_q->SetLineWidth(2);
  h_p_track_average_q->SetLineColor(1);
  h_p_track_average_q->Draw("histosame");

  c2_bis->cd(4);
  
  h_p_track_average_c->SetLineColor(4);
  h_p_track_average_c->SetLineWidth(2);
  h_p_track_average_c->GetYaxis()->SetTitle("[a.u.]");
  h_p_track_average_c->GetXaxis()->SetTitle("average sec. track momentum [GeV]");
  h_p_track_average_c->DrawNormalized("histo");

  h_p_track_average_b->SetLineWidth(2);
  h_p_track_average_b->SetLineColor(2);
  h_p_track_average_b->DrawNormalized("histosame");

  h_p_track_average_q->SetLineWidth(2);
  h_p_track_average_q->SetLineColor(1);
  h_p_track_average_q->DrawNormalized("histosame");
  
  leg->Draw();
 
  
  c2_bis->Write();//"mass_p_vtx.root");

  TCanvas *c3 = new TCanvas ("c3","c3",2000,600);
  c3->Divide(4,1);
  c3->cd(1);
  
  h_mass_p_vtx_q->SetMarkerColor(1);
  h_mass_p_vtx_q->SetLineColor(1);
  h_mass_p_vtx_q->SetLineWidth(2);
  h_mass_p_vtx_q->SetTitle("uds-quark");

  h_mass_p_vtx_q->GetYaxis()->SetTitle("momentum of the sec. vertex [GeV]");
  h_mass_p_vtx_q->GetXaxis()->SetTitle("Mass of the sec. vertex [GeV]");
  h_mass_p_vtx_q->Draw("colz");

  c3->cd(2);
  
  h_mass_p_vtx_c->SetMarkerColor(4);
  h_mass_p_vtx_c->SetLineColor(4);
  h_mass_p_vtx_c->SetLineWidth(2);
  h_mass_p_vtx_c->SetTitle("c-quark");

  h_mass_p_vtx_c->GetYaxis()->SetTitle("momentum of the sec. vertex [GeV]");
  h_mass_p_vtx_c->GetXaxis()->SetTitle("Mass of the sec. vertex [GeV]");
  h_mass_p_vtx_c->Draw("colz");

  c3->cd(3);
  
  h_mass_p_vtx_b->SetMarkerColor(2);
  h_mass_p_vtx_b->SetLineColor(2);
  h_mass_p_vtx_b->SetLineWidth(2);
  h_mass_p_vtx_b->SetTitle("b-quark");

  h_mass_p_vtx_b->GetYaxis()->SetTitle("momentum of the sec. vertex [GeV]");
  h_mass_p_vtx_b->GetXaxis()->SetTitle("Mass of the sec. vertex [GeV]");
  h_mass_p_vtx_b->Draw("colz");

  c3->cd(4);
  
  h_mass_p_vtx_b->Draw("p");
  h_mass_p_vtx_q->Draw("psame");
  h_mass_p_vtx_c->Draw("psame");


    
  c3->Write();//"mass_p_vtx_2d.root");

  TCanvas *c3bis = new TCanvas ("c3bis","c3bis",2000,600);
  c3bis->Divide(4,1);
  c3bis->cd(1);
  
  h_average_p_vtx_q->SetMarkerColor(1);
  h_average_p_vtx_q->SetLineColor(1);
  h_average_p_vtx_q->SetLineWidth(2);
  h_average_p_vtx_q->SetTitle("uds-quark");

  h_average_p_vtx_q->GetYaxis()->SetTitle("momentum per track (average) [GeV]");
  h_average_p_vtx_q->GetXaxis()->SetTitle("momentum of the sec. vertex [GeV]");
  h_average_p_vtx_q->Draw("colz");

  c3bis->cd(2);
  
  h_average_p_vtx_c->SetMarkerColor(4);
  h_average_p_vtx_c->SetLineColor(4);
  h_average_p_vtx_c->SetLineWidth(2);
  h_average_p_vtx_c->SetTitle("c-quark");

  h_average_p_vtx_c->GetYaxis()->SetTitle("momentum per track (average) [GeV]");
  h_average_p_vtx_c->GetXaxis()->SetTitle("momentum of the sec. vertex [GeV]");  
  h_average_p_vtx_c->Draw("colz");

  c3bis->cd(3);
  
  h_average_p_vtx_b->SetMarkerColor(2);
  h_average_p_vtx_b->SetLineColor(2);
  h_average_p_vtx_b->SetLineWidth(2);
  h_average_p_vtx_b->SetTitle("b-quark");

  h_average_p_vtx_b->GetYaxis()->SetTitle("momentum per track (average) [GeV]");
  h_average_p_vtx_b->GetXaxis()->SetTitle("momentum of the sec. vertex [GeV]");  
  
  h_average_p_vtx_b->Draw("colz");


    
  c3bis->Write();//"mass_p_vtx_2d.root");

  TCanvas *c4 = new TCanvas ("c4","c4",1200,1200);
  c4->Divide(2,2);
  c4->cd(1);

  h_btag_c->SetLineColor(4);
  h_btag_c->SetLineWidth(2);
  h_btag_c->GetYaxis()->SetTitle("[a.u]");
  h_btag_c->GetXaxis()->SetTitle("btag");
  h_btag_c->Draw("histo");

  h_btag_b->SetLineWidth(2);
  h_btag_b->SetLineColor(2);
  h_btag_b->Draw("histosame");

  h_btag_q->SetLineWidth(2);
  h_btag_q->SetLineColor(1);
  h_btag_q->Draw("histosame");
  
  leg->Draw();

  c4->cd(2);
  
  h_ctag_c->SetLineColor(4);
  h_ctag_c->SetLineWidth(2);
  h_ctag_c->GetYaxis()->SetTitle("[a.u]");
  h_ctag_c->GetXaxis()->SetTitle("ctag");
  h_ctag_c->Draw("histo");

  h_ctag_b->SetLineWidth(2);
  h_ctag_b->SetLineColor(2);
  h_ctag_b->Draw("histosame");

  h_ctag_q->SetLineWidth(2);
  h_ctag_q->SetLineColor(1);
  h_ctag_q->Draw("histosame");
  
  leg->Draw();

 
  c4->cd(3);
  h_norm_btag_c->Scale(1.0/h_norm_btag_c->GetEntries());
  
  h_norm_btag_c->SetLineColor(4);
  h_norm_btag_c->SetLineWidth(2);
  h_norm_btag_c->GetYaxis()->SetTitle("fraction of events");
  h_norm_btag_c->GetXaxis()->SetTitle("btag");
  h_norm_btag_c->Draw("histo");

  h_norm_btag_b->Scale(1.0/h_norm_btag_b->GetEntries());
  h_norm_btag_b->SetLineWidth(2);
  h_norm_btag_b->SetLineColor(2);
  h_norm_btag_b->Draw("histosame");
  
  h_norm_btag_q->Scale(1.0/h_norm_btag_q->GetEntries());
  h_norm_btag_q->SetLineWidth(1);
  h_norm_btag_q->SetLineColor(1);
  h_norm_btag_q->Draw("histosame");
  
  leg->Draw();

  c4->cd(4);
  h_norm_ctag_c->Scale(1.0/h_norm_ctag_c->GetEntries());
  
  h_norm_ctag_c->SetLineColor(4);
  h_norm_ctag_c->SetLineWidth(2);
  h_norm_ctag_c->GetYaxis()->SetTitle("fraction of events");
  h_norm_ctag_c->GetXaxis()->SetTitle("ctag");
  h_norm_ctag_c->Draw("histo");

  h_norm_ctag_b->Scale(1.0/h_norm_ctag_b->GetEntries());
  h_norm_ctag_b->SetLineWidth(2);
  h_norm_ctag_b->SetLineColor(2);
  h_norm_ctag_b->Draw("histosame");
  
  h_norm_ctag_q->Scale(1.0/h_norm_ctag_q->GetEntries());
  h_norm_ctag_q->SetLineWidth(1);
  h_norm_ctag_q->SetLineColor(1);
  h_norm_ctag_q->Draw("histosame");
  
  leg->Draw();
  
  c4->Write();//"lcfiplustags.root.root");

  TCanvas *c3_bis = new TCanvas ("c3_bis","c3_bis",1200,1200);
  c3_bis->Divide(2,2);
  c3_bis->cd(1);

  h_btag_ctag_q->Scale(1./h_btag_ctag_q->GetEntries());
  h_btag_ctag_q->SetMarkerColor(1);
  h_btag_ctag_q->SetLineColor(1);
  h_btag_ctag_q->SetLineWidth(2);
  h_btag_ctag_q->SetTitle("uds-quark");

  h_btag_ctag_q->GetYaxis()->SetTitle("ctag");
  h_btag_ctag_q->GetXaxis()->SetTitle("btag");
  h_btag_ctag_q->Draw("colz");

  c3_bis->cd(2);
  h_btag_ctag_c->Scale(1./h_btag_ctag_c->GetEntries());
  h_btag_ctag_c->SetMarkerColor(4);
  h_btag_ctag_c->SetLineColor(4);
  h_btag_ctag_c->SetLineWidth(2);
  h_btag_ctag_c->SetTitle("c-quark");

  h_btag_ctag_c->GetYaxis()->SetTitle("ctag");
  h_btag_ctag_c->GetXaxis()->SetTitle("btag");
  h_btag_ctag_c->Draw("colz");

  c3_bis->cd(3);
  h_btag_ctag_b->Scale(1./h_btag_ctag_b->GetEntries());
  h_btag_ctag_b->SetMarkerColor(2);
  h_btag_ctag_b->SetLineColor(2);
  h_btag_ctag_b->SetLineWidth(2);
  h_btag_ctag_b->SetTitle("b-quark");

  h_btag_ctag_b->GetYaxis()->SetTitle("ctag");
  h_btag_ctag_b->GetXaxis()->SetTitle("btag");
  h_btag_ctag_b->Draw("colz");

  c3_bis->cd(4);
  

    
  c3_bis->Write();//"lcfiplustags_2d.root");

}

bool effstudies::PreSelection(int type=0,float Kvcut=35) {
  
  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
  double b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
  double b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
  double bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

  // float sph_eq=0;
  // float m= -0.04;//(0.012-0.04)/(0.8-0.1);
  // sph_eq=m*(fabs(costheta)) + 0.042;
  // float sintheta=sqrt(1-costheta*costheta);
  // sph_eq=0.001 + 0.035 * sintheta*sintheta;

  TVector3 v1(jet_px[0],jet_py[0],jet_pz[0]);
  TVector3 v2(jet_px[1],jet_py[1],jet_pz[1]);
  float acol=GetSinacol(v1,v2);
  
  double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
  double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

  float costheta_j0;
  std::vector<float> p_j0;
  p_j0.push_back(jet_px[0]);
  p_j0.push_back(jet_py[0]);
  p_j0.push_back(jet_pz[0]);
  costheta_j0=fabs(GetCostheta(p_j0));

  float costheta_j1;
  std::vector<float> p_j1;
  p_j1.push_back(jet_px[1]);
  p_j1.push_back(jet_py[1]);
  p_j1.push_back(jet_pz[1]);
  costheta_j1=fabs(GetCostheta(p_j1));
  
  float Kv=250.*acol/(acol+sqrt(1-costheta_j0*costheta_j0)+sqrt(1-costheta_j1*costheta_j1));
  float K1=jet0_p*acol/sqrt(1-costheta_j1*costheta_j1);
  float K2=jet1_p*acol/sqrt(1-costheta_j0*costheta_j0);

  //    float thrust=principle_thrust_value;
     
  double  neutralPFO_max[2];
  double  neutralPFO_total[2];
  double  neutralPFO_ratio[2];

  double  neutraljet_E[2];
  double  neutraljet_costheta[2];

  float costheta_neutral0;
  float costheta_neutral1;

    
  float neut[2][3];

  double npfo[2];
  for(int ijet=0; ijet<2; ijet++) {
    neutralPFO_max[ijet]=0;
    neutralPFO_total[ijet]=0;
    neutralPFO_ratio[ijet]=0;
    npfo[ijet]=0;
    double jetenergy=0;

    neut[ijet][0]=0;
    neut[ijet][1]=0;
    neut[ijet][2]=0;

    for(int ipfo=0; ipfo<100; ipfo++) {//jet_pfo_n[ijet]; ipfo++) {
      if(jet_pfo_E[ijet][ipfo]<0.1) continue;
	
      npfo[ijet]++;
      jetenergy+=jet_pfo_E[ijet][ipfo];
      if( (jet_pfo_type[ijet][ipfo]==22 || jet_pfo_charge[ijet][ipfo]==0) && jet_pfo_E[ijet][ipfo]> neutralPFO_max[ijet]) {
	neutralPFO_max[ijet]=jet_pfo_E[ijet][ipfo]; 
      }
      if( jet_pfo_type[ijet][ipfo]==22 ||  jet_pfo_charge[ijet][ipfo]==0 ) {

	neut[ijet][0]+=jet_pfo_px[ijet][ipfo];
	neut[ijet][1]+=jet_pfo_py[ijet][ipfo];
	neut[ijet][2]+=jet_pfo_pz[ijet][ipfo];

	neutralPFO_total[ijet]+=jet_pfo_E[ijet][ipfo]; 
	neutralPFO_ratio[ijet]+=jet_pfo_E[ijet][ipfo]; 
      }
    }
    neutralPFO_ratio[ijet]/=jetenergy;
  }

  for(int ijet=0; ijet<2; ijet++) {
    neutraljet_E[ijet]=-1;
    neutraljet_costheta[ijet]=-1; 
    if(neutralPFO_ratio[ijet]>0.85) {
      neutraljet_E[ijet]=jet_E[ijet];
      if(ijet==0) neutraljet_costheta[ijet]=costheta_j0;
      if(ijet==1) neutraljet_costheta[ijet]=costheta_j1;
    }
  }

        
  std::vector<float> neutral0;
  neutral0.push_back(neut[0][0]);
  neutral0.push_back(neut[0][1]);
  neutral0.push_back(neut[0][2]);

  std::vector<float> neutral1;
  neutral1.push_back(neut[1][0]);
  neutral1.push_back(neut[1][1]);
  neutral1.push_back(neut[1][2]);
    
  costheta_neutral0=GetCostheta(neutral0);
  costheta_neutral1=GetCostheta(neutral1);


  bool ISR_1=true;
  if(neutralPFO_ratio[0]<0.85 && neutralPFO_ratio[1]<0.85) ISR_1=false;

  bool ISR_2=true;
  if(npfo[0]>5 && npfo[1]>5) ISR_2=false;

  bool ISR_3=false;
  if( (fabs(costheta_neutral0)>0.99 && neutralPFO_total[0]>Kvcut) || (fabs(costheta_neutral1)>0.99 && neutralPFO_total[1]>Kvcut) ) ISR_3=true;

  if(type == 0 ) return true;

  if(type == -1 )  if( bbmass>130 && Kv < Kvcut && ISR_1==false ) return true;
  if(type == -2 )  if( bbmass>130 && Kv < Kvcut && ISR_1==false && ISR_2==false ) return true;
    
  if(type == 1 )  if( ISR_1==false && ISR_2==false && ISR_3==false) return true;
  if(type == 2 )  if( ISR_1==false && ISR_2==false && ISR_3==false && Kv < Kvcut)  return true;
  if(type == 3 )  if( ISR_1==false && ISR_2==false && ISR_3==false && bbmass>130 && Kv < Kvcut)  return true;
    
  if(type == 4 )  if( bbmass>130 && Kv < Kvcut && ISR_1==false && ISR_2==false && ISR_3==false && y23<0.015 )  return true;
  if(type == 5 )  if( bbmass>130 && Kv < Kvcut && ISR_1==false && ISR_2==false && ISR_3==false && y23<0.015 && (b1mass+b2mass)<100)  return true;
    
  return false;
}





float effstudies::ChargeBcJet(int ijet) {
  double charge=0;

  //  if(jet_btag[ijet] <0.8) return charge;

  double momvertex=0;

  double mom_x=0, mom_y=0, mom_z=0;
  double e=0;
  double nt=0;
  for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
    for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
      nt++;
      e+=jet_track_E[ijet][ivtx][itrack];
      mom_x+=jet_track_px[ijet][ivtx][itrack];
      mom_y+=jet_track_py[ijet][ivtx][itrack];
      mom_z+=jet_track_pz[ijet][ivtx][itrack];
    }
  }

  double mass = sqrt(pow(e,2) - pow(mom_x,2) -  pow(mom_y,2) - pow(mom_z,2) );
  momvertex= sqrt(pow(mom_x,2) +  pow(mom_y,2) + pow(mom_z,2) );

  //  if(momvertex<25) return 0;
  
  for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
    for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
      double mom = sqrt(pow(jet_track_px[ijet][ivtx][itrack],2)+pow(jet_track_py[ijet][ivtx][itrack],2)+pow(jet_track_pz[ijet][ivtx][itrack],2));
      //if(mom>1)
      charge+=jet_track_charge[ijet][ivtx][itrack];
    }
  }

  return charge;
}

float effstudies::ChargeKcJet(int ijet){//, int eff=0.88) {
  float eff=0.88;
  float purity=0.95;
  
  double charge=0;

  double momvertex=0;

  double mom_x=0, mom_y=0, mom_z=0;
  double e=0;
  double nt=0;
  for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
    for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
      nt++;
      e+=jet_track_E[ijet][ivtx][itrack];
      mom_x+=jet_track_px[ijet][ivtx][itrack];
      mom_y+=jet_track_py[ijet][ivtx][itrack];
      mom_z+=jet_track_pz[ijet][ivtx][itrack];
    }
  }

  double mass = sqrt(pow(e,2) - pow(mom_x,2) -  pow(mom_y,2) - pow(mom_z,2) );
  momvertex= sqrt(pow(mom_x,2) +  pow(mom_y,2) + pow(mom_z,2) );

  // if(momvertex<25) return 0;
  
  // if(jet_btag[ijet] <0.3) return charge;

  for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
    for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
      
      double mom = sqrt(pow(jet_track_px[ijet][ivtx][itrack],2)+pow(jet_track_py[ijet][ivtx][itrack],2)+pow(jet_track_pz[ijet][ivtx][itrack],2));

      std::vector<float> ptracks;
      ptracks.push_back(jet_track_px[ijet][ivtx][itrack]);
      ptracks.push_back(jet_track_py[ijet][ivtx][itrack]);
      ptracks.push_back(jet_track_pz[ijet][ivtx][itrack]);
      float costheta_tracks=GetCostheta(ptracks);
            
      TRandom1 *r1 = new TRandom1();
      double gen_eff=r1->Rndm();
      bool iskaon=false;
      if(mom>2 && fabs(costheta_tracks)<0.95 && jet_track_iskaoncheat[ijet][ivtx][itrack]==1 && gen_eff<eff) iskaon=true;

      TRandom1 *r2 = new TRandom1();
      double gen_purity=r2->Rndm();
      if( iskaon==true) {
	if(gen_purity<purity) charge+=jet_track_charge[ijet][ivtx][itrack];
	else charge-=jet_track_charge[ijet][ivtx][itrack];
      }
    }
   
  }
    
  return charge;
}

std::vector<float> effstudies::Error(double effb,double error_effb,double effbd,double error_effbd) {

  TRandom *r0= new TRandom2();
  TRandom *r1 = new TRandom2();

  TH1F *h1=new TH1F("h1","h1",6000,-0.3,0.3);

  
  for(int i=0; i<50000; i++) {

    double effb_new=r0->Gaus(effb,error_effb);
    double effbd_new=r1->Gaus(effbd,error_effbd);

    double rho=(effbd_new-effb_new*effb_new)/(effb_new-effb_new*effb_new);
    h1->Fill(rho);

  }

  std::vector<float> value;
  value.push_back(h1->GetMean());
  value.push_back(h1->GetRMS());
  return value;
}


std::vector<float> effstudies::ErrorLEP(double effb,double error_effb,double effbd,double error_effbd) {

  TRandom *r0= new TRandom2();
  TRandom *r1 = new TRandom2();

  TH1F *h1=new TH1F("h1","h1",12000,-0.6,0.6);

  
  for(int i=0; i<50000; i++) {

    double effb_new=r0->Gaus(effb,error_effb);
    double effbd_new=r1->Gaus(effbd,error_effbd);

    double rho=effbd_new/(effb_new*effb_new)-1.0;
    h1->Fill(rho);

  }

  std::vector<float> value;
  value.push_back(h1->GetMean());
  value.push_back(h1->GetRMS());
  return value;
}

