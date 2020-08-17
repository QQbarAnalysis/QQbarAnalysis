#define observable_cxx
#include "observable.h"
#include "TPad.h"

void observable::InitializeHistos(int n){

  nbins=n;
  bbbar_gen=0;
  preselection=0;
  bkg=0;
   
  bbbar_KcKc_reco=0;
  bbbar_BcBc_reco=0;
  bbbar_BcKc_reco=0;
  bbbar_KcBc_reco=0;
  bbbar_BcKc_same1_reco=0;
  bbbar_BcKc_same2_reco=0;
   
  h_bbbar = new TH1F("h_bbbar","h_bbbar",nbins,-1.0,1.0);
  h_bbbar_recocuts = new TH1F("h_bbbar_recocuts","h_bbbar_recocuts",nbins,-1.0,1.0);

  h_bbbar_BcBc_reco = new TH1F("h_bbbar_BcBc_reco","h_bbbar_BcBc_reco",nbins,-1.0,1.0);
  h_bbbar_BcBc_rejected = new TH1F("h_bbbar_BcBc_rejected","h_bbbar_BcBc_rejected",nbins,-1.0,1.0);

  h_bbbar_KcKc_reco = new TH1F("h_bbbar_KcKc_reco","h_bbbar_KcKc_reco",nbins,-1.0,1.0);
  h_bbbar_KcKc_rejected = new TH1F("h_bbbar_KcKc_rejected","h_bbbar_KcKc_rejected",nbins,-1.0,1.0);
   
  h_bbbar_BcKc_reco = new TH1F("h_bbbar_BcKc_reco","h_bbbar_BcKc_reco",nbins,-1.0,1.0);
  h_bbbar_BcKc_rejected = new TH1F("h_bbbar_BcKc_rejected","h_bbbar_BcKc_rejected",nbins,-1.0,1.0);
   
  h_bbbar_KcBc_reco = new TH1F("h_bbbar_KcBc_reco","h_bbbar_KcBc_reco",nbins,-1.0,1.0);
  h_bbbar_KcBc_rejected = new TH1F("h_bbbar_KcBc_rejected","h_bbbar_KcBc_rejected",nbins,-1.0,1.0);
   
  h_bbbar_BcKc_same1_reco = new TH1F("h_bbbar_BcKc_same1_reco","h_bbbar_BcKc_same1_reco",nbins,-1.0,1.0);
  h_bbbar_BcKc_same1_rejected = new TH1F("h_bbbar_BcKc_same1_rejected","h_bbbar_BcKc_same1_rejected",nbins,-1.0,1.0);
   
  h_bbbar_BcKc_same2_reco = new TH1F("h_bbbar_BcKc_same2_reco","h_bbbar_BcKc_same2_reco",nbins,-1.0,1.0);
  h_bbbar_BcKc_same2_rejected = new TH1F("h_bbbar_BcKc_same2_rejected","h_bbbar_BcKc_same2_rejected",nbins,-1.0,1.0);

  h_bbbar->Sumw2();
  h_bbbar_BcBc_reco->Sumw2();
  h_bbbar_BcBc_rejected->Sumw2();
  h_bbbar_KcKc_reco->Sumw2();
  h_bbbar_KcKc_rejected->Sumw2();
  h_bbbar_BcKc_reco->Sumw2();
  h_bbbar_BcKc_rejected->Sumw2();
  h_bbbar_KcBc_reco->Sumw2();
  h_bbbar_KcBc_rejected->Sumw2();
  h_bbbar_BcKc_same1_reco->Sumw2();
  h_bbbar_BcKc_same1_rejected->Sumw2();
  h_bbbar_BcKc_same2_reco->Sumw2();
  h_bbbar_BcKc_same2_rejected->Sumw2();
  
  for(int i=0; i<6; i++) {
    asymm_BcBc[i]= new TH1F(TString::Format("Asymm_BcBc_%i",i),TString::Format("Asymm_BcBc_%i",i),nbins,-1.0,1.0);
    asymm_BcBc[i]->Sumw2();
  }
   
  for(int i=0; i<6; i++) {
    asymm_KcKc[i]= new TH1F(TString::Format("Asymm_KcKc_%i",i),TString::Format("Asymm_KcKc_%i",i),nbins,-1.0,1.0);
    asymm_KcKc[i]->Sumw2();
  }
   
  for(int i=0; i<6; i++) {
    asymm_BcKc[i]= new TH1F(TString::Format("Asymm_BcKc_%i",i),TString::Format("Asymm_BcKc_%i",i),nbins,-1.0,1.0);
    asymm_BcKc[i]->Sumw2();
  }
   
  for(int i=0; i<6; i++) {
    asymm_KcBc[i]= new TH1F(TString::Format("Asymm_KcBc_%i",i),TString::Format("Asymm_KcBc_%i",i),nbins,-1.0,1.0);
    asymm_KcBc[i]->Sumw2();
  }
   
  for(int i=0; i<6; i++) {
    asymm_BcKc_same1[i]= new TH1F(TString::Format("Asymm_BcKc_same1_%i",i),TString::Format("Asymm_BcKc_same1_%i",i),nbins,-1.0,1.0);
    asymm_BcKc_same1[i]->Sumw2();
  }
   
  for(int i=0; i<6; i++) {
    asymm_BcKc_same2[i]= new TH1F(TString::Format("Asymm_BcKc_same2_%i",i),TString::Format("Asymm_BcKc_same2_%i",i),nbins,-1.0,1.0);
    asymm_BcKc_same2[i]->Sumw2();
  }


  //Efficiency histograms
  h_cos_parton = new TH1F("h_cos_parton","h_cos_parton",nbins,-1,1);
  h_cos_preselection = new TH1F("h_cos_preselection","h_cos_preselection",nbins,-1,1);
  h_cos_parton->Sumw2();
  h_cos_preselection->Sumw2();
  h_cos_charge_BcBc = new TH1F("h_cos_charge_BcBc","h_cos_charge_BcBc",nbins,-1,1);
  h_cos_charge_KcKc = new TH1F("h_cos_charge_KcKc","h_cos_charge_KcKc",nbins,-1,1);
  h_cos_charge_BcKc = new TH1F("h_cos_charge_BcKc","h_cos_charge_BcKc",nbins,-1,1);
  h_cos_charge_KcBc = new TH1F("h_cos_charge_KcBc","h_cos_charge_KcBc",nbins,-1,1);
  h_cos_charge_BcKc_same1 = new TH1F("h_cos_charge_BcKc_same1","h_cos_charge_BcKc_same1",nbins,-1,1);
  h_cos_charge_BcKc_same2 = new TH1F("h_cos_charge_BcKc_same2","h_cos_charge_BcKc_same2",nbins,-1,1);
  h_cos_charge_BcBc->Sumw2();
  h_cos_charge_KcKc->Sumw2();
  h_cos_charge_BcKc->Sumw2();
  h_cos_charge_KcBc->Sumw2();
  h_cos_charge_BcKc_same1->Sumw2();
  h_cos_charge_BcKc_same2->Sumw2();

  //resolution
  h_resolution_BcBc = new TH2F("h_resolution_BcBc","h_resolution_BcBc",nbins,-1,1,nbins,-1,1);
  h_resolution_KcKc = new TH2F("h_resolution_KcKc","h_resolution_KcKc",nbins,-1,1,nbins,-1,1);
  h_resolution_BcKc = new TH2F("h_resolution_BcKc","h_resolution_BcKc",nbins,-1,1,nbins,-1,1);
  h_resolution_KcBc = new TH2F("h_resolution_KcBc","h_resolution_KcBc",nbins,-1,1,nbins,-1,1);
  h_resolution_BcKc_same1 = new TH2F("h_resolution_BcKc_same1","h_resolution_BcKc_same1",nbins,-1,1,nbins,-1,1);
  h_resolution_BcKc_same2 = new TH2F("h_resolution_BcKc_same2","h_resolution_BcKc_same2",nbins,-1,1,nbins,-1,1);
  h_resolution_BcBc->Sumw2();
  h_resolution_KcKc->Sumw2();
  h_resolution_BcKc->Sumw2();
  h_resolution_KcBc->Sumw2();
  h_resolution_BcKc_same1->Sumw2();
  h_resolution_BcKc_same2->Sumw2();

  //resolution_jettrack
  h_resolution_jettrack_BcBc = new TH2F("h_resolution_jettrack_BcBc","h_resolution_jettrack_BcBc",nbins,-1,1,nbins,-1,1);
  h_resolution_jettrack_KcKc = new TH2F("h_resolution_jettrack_KcKc","h_resolution_jettrack_KcKc",nbins,-1,1,nbins,-1,1);
  h_resolution_jettrack_BcKc = new TH2F("h_resolution_jettrack_BcKc","h_resolution_jettrack_BcKc",nbins,-1,1,nbins,-1,1);
  h_resolution_jettrack_KcBc = new TH2F("h_resolution_jettrack_KcBc","h_resolution_jettrack_KcBc",nbins,-1,1,nbins,-1,1);
  h_resolution_jettrack_BcKc_same1 = new TH2F("h_resolution_jettrack_BcKc_same1","h_resolution_jettrack_BcKc_same1",nbins,-1,1,nbins,-1,1);
  h_resolution_jettrack_BcKc_same2 = new TH2F("h_resolution_jettrack_BcKc_same2","h_resolution_jettrack_BcKc_same2",nbins,-1,1,nbins,-1,1);
  h_resolution_jettrack_BcBc->Sumw2();
  h_resolution_jettrack_KcKc->Sumw2();
  h_resolution_jettrack_BcKc->Sumw2();
  h_resolution_jettrack_KcBc->Sumw2();
  h_resolution_jettrack_BcKc_same1->Sumw2();
  h_resolution_jettrack_BcKc_same2->Sumw2();

 
}

void observable::HistoEfficiencies() {

  h_cos_charge_BcBc->Divide(h_cos_parton);
  h_cos_charge_KcKc->Divide(h_cos_parton);
  h_cos_charge_BcKc->Divide(h_cos_parton);
  h_cos_charge_KcBc->Divide(h_cos_parton);
  h_cos_charge_BcKc_same1->Divide(h_cos_parton);
  h_cos_charge_BcKc_same2->Divide(h_cos_parton);

  h_cos_preselection->Divide(h_cos_parton);

}

void observable::CoutEfficiencies() {

  cout<<" Efficiencies: "<<endl;
  cout<<" Preselection: "<<100.*float(preselection)/float(bbbar_gen)<<" %     bkg: "<<100.*float(bkg)/float(preselection)<<" %"<<endl;
  cout<<" BcBc: "<<100.*float(bbbar_BcBc_reco)/float(bbbar_gen)<<" %     bkg: "<<100.*float(asymm_BcBc[2]->GetEntries())/float(asymm_BcBc[0]->GetEntries())<<" %"<<endl;
  cout<<" KcKc: "<<100.*float(bbbar_KcKc_reco)/float(bbbar_gen)<<" %     bkg: "<<100.*float(asymm_KcKc[2]->GetEntries())/float(asymm_KcKc[0]->GetEntries())<<" %"<<endl;
  cout<<" BcKc(jet1): "<<100.*float(bbbar_BcKc_same1_reco)/float(bbbar_gen)<<" %     bkg: "<<100.*float(asymm_BcKc_same1[2]->GetEntries())/float(asymm_BcKc_same1[0]->GetEntries())<<" %"<<endl;
  cout<<" BcKc(jet2): "<<100.*float(bbbar_BcKc_same2_reco)/float(bbbar_gen)<<" %     bkg: "<<100.*float(asymm_BcKc_same2[2]->GetEntries())/float(asymm_BcKc_same2[0]->GetEntries())<<" %"<<endl;
  cout<<" BcKc: "<<100.*float(bbbar_BcKc_reco)/float(bbbar_gen)<<" %     bkg: "<<100.*float(asymm_BcKc[2]->GetEntries())/float(asymm_BcKc[0]->GetEntries())<<" %"<<endl;
  cout<<" KcBc: "<<100.*float(bbbar_KcBc_reco)/float(bbbar_gen)<<" %     bkg: "<<100.*float(asymm_KcBc[2]->GetEntries())/float(asymm_KcBc[0]->GetEntries())<<" %"<<endl;

}

 

void observable::SaveRootFile(std::vector<TH1F*> asymm_all, std::vector<TH2F*> resolution, TString polarization="eL"){

  TFile *MyFile = new TFile(TString::Format("%s_250GeV_%s_btag1_%0.1f_btag2_%0.1f_nbins%i.root",process.Data(),polarization.Data(),btag1,btag2,nbins),"RECREATE");
  MyFile->cd();
  
  //partonlevel
  asymm_all[42]->SetName("parton");
  asymm_all[42]->Write();

  for(int i=0; i<6; i++) {
    TString cat="BcBc";
    if(i==1) cat="KcKc";
    if(i==2) cat="BcKc";
    if(i==3) cat="KcBc";
    if(i==4) cat="BcKc_same1";
    if(i==5) cat="BcKc_same2";

    asymm_all[7*i+0]->SetName("reco_"+cat);
    asymm_all[7*i+1]->SetName("cheatedcharge_"+cat);
    asymm_all[7*i+2]->SetName("corrected_"+cat);
    asymm_all[7*i+3]->SetName("bkg_qq_"+cat);
    asymm_all[7*i+4]->SetName("bkg_cc_"+cat);
    asymm_all[7*i+5]->SetName("bkg_radreturn_"+cat);
    asymm_all[7*i+0]->Write();
    asymm_all[7*i+1]->Write();
    asymm_all[7*i+2]->Write();
    asymm_all[7*i+3]->Write();
    asymm_all[7*i+4]->Write();
    asymm_all[7*i+5]->Write();

  }
   
  //calculated efficiencies (truth), categories + preseletion
  asymm_all[43]->SetName("event_reconstruction_eff_preselection");
  asymm_all[44]->SetName("event_reconstruction_eff_BcBc");
  asymm_all[45]->SetName("event_reconstruction_eff_KcKc");
  asymm_all[46]->SetName("event_reconstruction_eff_BcKc");
  asymm_all[47]->SetName("event_reconstruction_eff_KcBc");
  asymm_all[48]->SetName("event_reconstruction_eff_BcKc_same1");
  asymm_all[49]->SetName("event_reconstruction_eff_BcKc_same2");
  
  for(int i=43; i<50; i++) {
    asymm_all[i]->Write();
  }

  for(int i=1; i<6; i++) {
    //reco
    asymm_all[0]->Add(asymm_all[7*i+0]);
    //truth
    asymm_all[1]->Add(asymm_all[7*i+1]);//
    //corrected  
    asymm_all[2]->Add(asymm_all[7*i+2]);//
    //bkg-qq
    asymm_all[3]->Add(asymm_all[7*i+3]);//
    //bkg-cc
    asymm_all[4]->Add(asymm_all[7*i+4]);//
    //bkg-radreturn
    asymm_all[5]->Add(asymm_all[7*i+5]);//
  }

  asymm_all[0]->SetName("reco");
  asymm_all[1]->SetName("truth");
  asymm_all[2]->SetName("corrected");
  asymm_all[3]->SetName("bkg_qq");
  asymm_all[4]->SetName("bkg_cc");
  asymm_all[5]->SetName("bkg_radreturn");

  for(int i=0; i<6; i++) asymm_all[i]->Write();

  asymm_all[6]->SetName("p_value_BcBc");
  asymm_all[13]->SetName("p_value_KcKc");
  asymm_all[20]->SetName("p_value_BcKc");
  asymm_all[27]->SetName("p_value_KcBc");
  asymm_all[34]->SetName("p_value_BcKc_same1");
  asymm_all[41]->SetName("p_value_BcKc_same2");
  asymm_all[6]->Write();
  asymm_all[13]->Write();
  asymm_all[20]->Write();
  asymm_all[27]->Write();
  asymm_all[34]->Write();
  asymm_all[41]->Write();


  // write parton level distribution for reconstructed events
  asymm_all[50]->SetName("parton_recocuts");
  asymm_all[50]->Write();

  // Name rejected events per category (for the p-value calculation offline)
  asymm_all[51]->SetName("rejected_BcBc");
  asymm_all[52]->SetName("rejected_KcKc");
  asymm_all[53]->SetName("rejected_BcKc");
  asymm_all[54]->SetName("rejected_KcBc");
  asymm_all[55]->SetName("rejected_BcKc_same1");
  asymm_all[56]->SetName("rejected_BcKc_same2"); 

  asymm_all[57]->SetName("bkg_qq_rejected_BcBc");
  asymm_all[58]->SetName("bkg_qq_rejected_KcKc");
  asymm_all[59]->SetName("bkg_qq_rejected_BcKc");
  asymm_all[60]->SetName("bkg_qq_rejected_KcBc");
  asymm_all[61]->SetName("bkg_qq_rejected_BcKc_same1");
  asymm_all[62]->SetName("bkg_qq_rejected_BcKc_same2");

  asymm_all[63]->SetName("bkg_radreturn_rejected_BcBc");
  asymm_all[64]->SetName("bkg_radreturn_rejected_KcKc");
  asymm_all[65]->SetName("bkg_radreturn_rejected_BcKc");
  asymm_all[66]->SetName("bkg_radreturn_rejected_KcBc");
  asymm_all[67]->SetName("bkg_radreturn_rejected_BcKc_same1");
  asymm_all[68]->SetName("bkg_radreturn_rejected_BcKc_same2");
  
  for( int i=50; i<69; i++) asymm_all[i]->Write();
  
  
  for(unsigned i=0; i<resolution.size(); i++) resolution[i]->Write();
  
  MyFile->Close();
  

}



void observable::SaveRootFile(std::vector<TH1F*> asymm_all, TString polarization="eL"){


  TFile *MyFile = new TFile(TString::Format("%s_250GeV_%s_btag1_%0.1f_btag2_%0.1f_nbins%i.root",process.Data(),polarization.Data(),btag1,btag2,nbins),"RECREATE");
  MyFile->cd();
  
  //partonlevel
  //reco level, categories
  asymm_all[0]->SetName("reco_BcBc");
  asymm_all[1]->SetName("reco_KcKc");
  asymm_all[2]->SetName("reco_BcKc");
  asymm_all[3]->SetName("reco_KcBc");
  asymm_all[4]->SetName("reco_BcKc_same1");
  asymm_all[5]->SetName("reco_BcKc_same2");
  asymm_all[0]->Write();
  asymm_all[1]->Write();
  asymm_all[2]->Write();
  asymm_all[3]->Write();
  asymm_all[4]->Write();
  asymm_all[5]->Write();
 
  // Global histograms
  //-------------------------------------
  //reco
  asymm_all[0]->Add(asymm_all[1]);//kckc
  asymm_all[0]->Add(asymm_all[2]);//bckc
  asymm_all[0]->Add(asymm_all[3]);//kcbc
  asymm_all[0]->Add(asymm_all[4]);//bckc_same
  asymm_all[0]->Add(asymm_all[5]);//kcbc_same

  asymm_all[0]->SetName("reco");
  asymm_all[0]->Write();

  // write rejected events per category (for the p-value calculation offline)
  asymm_all[6]->SetName("rejected_BcBc");
  asymm_all[7]->SetName("rejected_KcKc");
  asymm_all[8]->SetName("rejected_BcKc");
  asymm_all[9]->SetName("rejected_KcBc");
  asymm_all[10]->SetName("rejected_BcKc_same1");
  asymm_all[11]->SetName("rejected_BcKc_same2");
  for( int i=6; i<12; i++) asymm_all[i]->Write();


  MyFile->Close();
  
}
void observable::AFBb_parton(int n_entries=-1, TString polarization="eL")
{


  TH1F* h_costheta_parton[25];
  TH1F* h_costheta_parton_cc[25];
  TH1F* h_costheta_parton_qq[25];
  TH1F* h_costheta_parton_rad[25];
  TH1F* h_costheta_parton_cc_rad[25];
  TH1F* h_costheta_parton_qq_rad[25];
  
  for(int i=0; i<25; i++) {
    h_costheta_parton[i]= new TH1F(TString::Format("h_costheta_parton_%i",i*5),TString::Format("h_costheta_parton_%i",i*5),40,-1.0,1.0);
    h_costheta_parton_qq[i]= new TH1F(TString::Format("h_costheta_parton_qq_%i",i*5),TString::Format("h_costheta_parton_qq_%i",i*5),40,-1.0,1.0);
    h_costheta_parton_cc[i]= new TH1F(TString::Format("h_costheta_parton_cc_%i",i*5),TString::Format("h_costheta_parton_cc_%i",i*5),40,-1.0,1.0);
    h_costheta_parton_rad[i]= new TH1F(TString::Format("h_costheta_parton_rad_%i",i*5),TString::Format("h_costheta_parton_rad_%i",i*5),40,-1.0,1.0);
    h_costheta_parton_qq_rad[i]= new TH1F(TString::Format("h_costheta_parton_qq_rad_%i",i*5),TString::Format("h_costheta_parton_qq_rad_%i",i*5),40,-1.0,1.0);
    h_costheta_parton_cc_rad[i]= new TH1F(TString::Format("h_costheta_parton_cc_rad_%i",i*5),TString::Format("h_costheta_parton_cc_rad_%i",i*5),40,-1.0,1.0);
  }

  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //   if(fabs(mc_quark_pdg[0])!=5) continue;

    float costheta_bbbar;
    std::vector<float> p_bbar;
    p_bbar.push_back(mc_quark_px[0]-mc_quark_px[1]);
    p_bbar.push_back(mc_quark_py[0]-mc_quark_py[1]);
    p_bbar.push_back(mc_quark_pz[0]-mc_quark_pz[1]);
    costheta_bbbar=GetCostheta(p_bbar);
        
    costheta_bbbar=  (mc_quark_charge[0] < 0) ? costheta_bbbar: -costheta_bbbar;
      
    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e+gamma1_e;//sqrt(pow(mc_ISR_px[0]+mc_ISR_px[1],2)+pow(mc_ISR_py[0]+mc_ISR_py[1],2)+pow(mc_ISR_pz[0]+mc_ISR_pz[1],2));// gamma0_e+gamma1_e;
          
    for(int i=0; i<25; i++) {
      float Kvcut=i*5.;
      if(gamma_e<Kvcut){
	if(fabs(mc_quark_pdg[0])==5) h_costheta_parton[i]->Fill(costheta_bbbar);
	if(fabs(mc_quark_pdg[0])==4) h_costheta_parton_cc[i]->Fill(costheta_bbbar);
	if(fabs(mc_quark_pdg[0])<3) h_costheta_parton_qq[i]->Fill(costheta_bbbar);
      }
      if(gamma_e>Kvcut){
	if(fabs(mc_quark_pdg[0])==5) h_costheta_parton_rad[i]->Fill(costheta_bbbar);
	if(fabs(mc_quark_pdg[0])==4) h_costheta_parton_cc_rad[i]->Fill(costheta_bbbar);
	if(fabs(mc_quark_pdg[0])<3) h_costheta_parton_qq_rad[i]->Fill(costheta_bbbar);
      }
      
    }
       
  }

  TFile *MyFile = new TFile(TString::Format("AFBb_%s_250GeV_%s_nbins40.root",process.Data(),polarization.Data()),"RECREATE");
  MyFile->cd();
  
  //partonlevel
  for(int i=0; i<25; i++) h_costheta_parton[i]->Write();
  for(int i=0; i<25; i++) h_costheta_parton_cc[i]->Write();
  for(int i=0; i<25; i++) h_costheta_parton_qq[i]->Write();
  
  for(int i=0; i<25; i++) h_costheta_parton_rad[i]->Write();
  for(int i=0; i<25; i++) h_costheta_parton_cc_rad[i]->Write();
  for(int i=0; i<25; i++) h_costheta_parton_qq_rad[i]->Write();
			    
  MyFile->Close();

}
    
void observable::Analysis(int n_entries=-1, TString polarization="eL", int n=20, int cuts=4, float Kvcut=35)
{

  InitializeHistos(n);

  TH1F* h_radreturn_BcBc_rejected = new TH1F("h_radreturn_BcBc_rejected","h_radreturn_BcBc_rejected",nbins,-1.0,1.0);
  TH1F* h_radreturn_KcKc_rejected = new TH1F("h_radreturn_KcKc_rejected","h_radreturn_KcKc_rejected",nbins,-1.0,1.0);
  TH1F* h_radreturn_BcKc_rejected = new TH1F("h_radreturn_BcKc_rejected","h_radreturn_BcKc_rejected",nbins,-1.0,1.0);
  TH1F* h_radreturn_KcBc_rejected = new TH1F("h_radreturn_KcBc_rejected","h_radreturn_KcBc_rejected",nbins,-1.0,1.0);
  TH1F* h_radreturn_BcKc_same1_rejected = new TH1F("h_radreturn_BcKc_same1_rejected","h_radreturn_BcKc_same1_rejected",nbins,-1.0,1.0);
  TH1F* h_radreturn_BcKc_same2_rejected = new TH1F("h_radreturn_BcKc_same2_rejected","h_radreturn_BcKc_same2_rejected",nbins,-1.0,1.0);
  
  TH1F* h_qq_BcBc_rejected = new TH1F("h_qq_BcBc_rejected","h_qq_BcBc_rejected",nbins,-1.0,1.0);
  TH1F* h_qq_KcKc_rejected = new TH1F("h_qq_KcKc_rejected","h_qq_KcKc_rejected",nbins,-1.0,1.0);
  TH1F* h_qq_BcKc_rejected = new TH1F("h_qq_BcKc_rejected","h_qq_BcKc_rejected",nbins,-1.0,1.0);
  TH1F* h_qq_KcBc_rejected = new TH1F("h_qq_KcBc_rejected","h_qq_KcBc_rejected",nbins,-1.0,1.0);
  TH1F* h_qq_BcKc_same1_rejected = new TH1F("h_qq_BcKc_same1_rejected","h_qq_BcKc_same1_rejected",nbins,-1.0,1.0);
  TH1F* h_qq_BcKc_same2_rejected = new TH1F("h_qq_BcKc_same2_rejected","h_qq_BcKc_same2_rejected",nbins,-1.0,1.0);

  TH1F* h_cc_BcBc_rejected = new TH1F("h_cc_BcBc_rejected","h_cc_BcBc_rejected",nbins,-1.0,1.0);
  TH1F* h_cc_KcKc_rejected = new TH1F("h_cc_KcKc_rejected","h_cc_KcKc_rejected",nbins,-1.0,1.0);
  TH1F* h_cc_BcKc_rejected = new TH1F("h_cc_BcKc_rejected","h_cc_BcKc_rejected",nbins,-1.0,1.0);
  TH1F* h_cc_KcBc_rejected = new TH1F("h_cc_KcBc_rejected","h_cc_KcBc_rejected",nbins,-1.0,1.0);
  TH1F* h_cc_BcKc_same1_rejected = new TH1F("h_cc_BcKc_same1_rejected","h_cc_BcKc_same1_rejected",nbins,-1.0,1.0);
  TH1F* h_cc_BcKc_same2_rejected = new TH1F("h_cc_BcKc_same2_rejected","h_cc_BcKc_same2_rejected",nbins,-1.0,1.0);
  
    
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

    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e + gamma1_e;//_ISR_px[0]+mc_ISR_px[1],2)+pow(mc_ISR_py[0]+mc_ISR_py[1],2)+pow(mc_ISR_pz[0]+mc_ISR_pz[1],2));// gamma0_e+gamma1_e;
    float Kv_p=gamma_e;
          
    //costheta parton
    float costheta_bbbar;
    std::vector<float> p_bbar;
    p_bbar.push_back(mc_quark_px[0]-mc_quark_px[1]);
    p_bbar.push_back(mc_quark_py[0]-mc_quark_py[1]);
    p_bbar.push_back(mc_quark_pz[0]-mc_quark_pz[1]);
    costheta_bbbar=GetCostheta(p_bbar);
    
    
    if(fabs(mc_quark_pdg[0])==5 && Kv_p<Kvcut) {
      bbbar_gen++;
      h_cos_parton->Fill(costheta_bbbar);
      h_cos_parton->Fill(-costheta_bbbar);
      
      costheta_bbbar=  (mc_quark_charge[0] < 0) ? costheta_bbbar: -costheta_bbbar;
      h_bbbar->Fill( costheta_bbbar );
    }

        
    // angle for jets reconstructed only with secondary vertex tracks
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
    
    if(PreSelection(5,Kvcut)==false) continue;
    
    preselection++;


    // charge + angles
    int Kc[2];
    Kc[0]=0; Kc[1]=0;

    int Bc[2];
    Bc[0]=0; Bc[1]=0;
      
    float costheta_KcKc;
    float costheta_BcBc;
    float costheta_BcKc;
    float costheta_KcBc;
    float costheta_BcKc_same1;
    float costheta_BcKc_same2;

    std::vector<float> p;
    p.push_back(jet_px[0]-jet_px[1]);
    p.push_back(jet_py[0]-jet_py[1]);
    p.push_back(jet_pz[0]-jet_pz[1]);
    
    costheta_BcBc=costheta_tracks;
    costheta_KcKc=costheta_tracks;
    costheta_BcKc=costheta_tracks;
    costheta_KcBc=costheta_tracks;
    costheta_BcKc_same1=costheta_tracks;
    costheta_BcKc_same2=costheta_tracks;
    
    for(int ijet=0; ijet<2; ijet++) {
      Bc[ijet]=ChargeBcJet(ijet);
      Kc[ijet]=ChargeKcJet(ijet);
    }


    float cos_truth=-2;
    h_cos_preselection->Fill(costheta_BcBc);
    h_cos_preselection->Fill(-costheta_BcBc);

    float cos_reco_truth=-2;
    float cos_trackreco_truth=-2;

    if(fabs(mc_quark_pdg[0])==5) {

      cos_truth = costheta_bbbar;
      
      if(mc_matching==1 && mc_quark_charge[0]<0 ) {
        cos_reco_truth =costheta_BcBc;
	cos_trackreco_truth=costheta_tracks;
      }
      if(mc_matching==1 && mc_quark_charge[0]>0 ) {
        cos_reco_truth =-costheta_BcBc;
	cos_trackreco_truth=-costheta_tracks;
      }
      if(mc_matching==2 && mc_quark_charge[1]<0 ){
        cos_reco_truth =costheta_BcBc;
	cos_trackreco_truth=costheta_tracks;
      }
      if(mc_matching==2 && mc_quark_charge[1]>0 ){
        cos_reco_truth =-costheta_BcBc;
      	cos_trackreco_truth=-costheta_tracks;
      }
    }
    cos_reco_truth= cos_trackreco_truth;
    //  h_bbbar_preselected->Fill(cos_reco_truth);

    bool taken = false;
    bool rejected = false;

    if(cuts==11) {

      // ------------------------------------------------------------------------
      // Bc Bc case
      // calculate asymmetry for the different categories
      //Information to calculate p, for BcBc category
      if(taken ==false) {    
	if(Bc[0]*Bc[1]>0) {
	  h_bbbar_BcBc_rejected->Fill( costheta_BcBc);
	  h_bbbar_BcBc_rejected->Fill( -costheta_BcBc);
	}
	if(Bc[0]*Bc[1]<0) {
	  if(Bc[0] < 0) h_bbbar_BcBc_reco->Fill(costheta_BcBc);
	  else h_bbbar_BcBc_reco->Fill( -costheta_BcBc);
	  
	  h_cos_charge_BcBc->Fill(costheta_BcBc);
	  h_cos_charge_BcBc->Fill(-costheta_BcBc);
	  
	  float cos_reco=  (Bc[0] < 0) ? costheta_BcBc: -costheta_BcBc;
	  bbbar_BcBc_reco++;
	  
	  if( fabs(mc_quark_pdg[0]==5) && Kv_p<Kvcut)	{
	    h_resolution_BcBc->Fill(cos_truth,cos_reco_truth);
	    h_resolution_jettrack_BcBc->Fill(cos_truth,cos_trackreco_truth);
	    
	    asymm_BcBc[0]->Fill(cos_reco);
	    asymm_BcBc[1]->Fill(cos_reco_truth);
	  }
	  
	  if(fabs(mc_quark_pdg[0])<4 && Kv_p<Kvcut) {
	    asymm_BcBc[3]->Fill(cos_reco);
	  }
	  if(fabs(mc_quark_pdg[0])==4 && Kv_p<Kvcut) {
	    asymm_BcBc[5]->Fill(cos_reco);
	  }
	  if(Kv_p>Kvcut) {
	    asymm_BcBc[5]->Fill(cos_reco);
	  }
	  
	  //taken = true;
	  
	}
      }
  
      /// SINGLE CHARGE MEASUREMENT
      taken=false;
      
      // -------------------------------------------------------------------------
      // Bc
      if(taken == false) {      
	if( Bc[0]!=0 || Bc[1]!=0) {
	  
	  float cos_reco =-2;
	  if(Bc[0]!=0 && Bc[0] < 0) cos_reco=costheta_BcKc;
	  if(Bc[0]!=0 && Bc[0] > 0) cos_reco=-costheta_BcKc;
	  if(Bc[0]==0 && Bc[1] > 0) cos_reco=costheta_BcKc;
	  if(Bc[0]==0 && Bc[1] < 0) cos_reco=-costheta_BcKc;
	  
	  h_bbbar_BcKc_reco->Fill( costheta_BcKc);
	  
	  h_cos_charge_BcKc->Fill(costheta_BcKc);
	  h_cos_charge_BcKc->Fill(-costheta_BcKc);
	  bbbar_BcKc_reco++;
	  
	  if( fabs(mc_quark_pdg[0]==5) && Kv_p<Kvcut) {
	    h_resolution_BcKc->Fill(cos_truth,cos_reco_truth);
	    h_resolution_jettrack_BcKc->Fill(cos_truth,cos_trackreco_truth);
	    
	    asymm_BcKc[0]->Fill(cos_reco);
	    asymm_BcKc[1]->Fill(cos_reco_truth);
	  }
	  
	  if(fabs(mc_quark_pdg[0])<4 && Kv_p<Kvcut) {
	    asymm_BcKc[3]->Fill(cos_reco);
	  }
	  if(fabs(mc_quark_pdg[0])==4 && Kv_p<Kvcut) {
	    asymm_BcKc[4]->Fill(cos_reco);
	  }
	  if(Kv_p>Kvcut) {
	    asymm_BcKc[5]->Fill(cos_reco);
	  }
	  
	  taken = true;
	}
      }

      
      // -------------------------------------------------------------------------
      //Information to calculate p, for KcKc category      
      //  if(taken == false ) {
	if(Kc[0]*Kc[1]>0) {
	  h_bbbar_KcKc_rejected->Fill( costheta_KcKc);
	  h_bbbar_KcKc_rejected->Fill( -costheta_KcKc);
	}
	
	if(Kc[0]*Kc[1]<0) {
	  if(Kc[0] < 0) h_bbbar_KcKc_reco->Fill(costheta_KcKc);
	  else h_bbbar_KcKc_reco->Fill( -costheta_KcKc);
	  h_cos_charge_KcKc->Fill(costheta_KcKc);
	  h_cos_charge_KcKc->Fill(-costheta_KcKc);
	  
	  float cos_reco=  (Kc[0] < 0) ? costheta_KcKc: -costheta_KcKc;
	  bbbar_KcKc_reco++;
	  
	  if( fabs(mc_quark_pdg[0]==5) && Kv_p<Kvcut)	{
	    h_resolution_KcKc->Fill(cos_truth,cos_reco_truth);
	    h_resolution_jettrack_KcKc->Fill(cos_truth,cos_trackreco_truth);
	    
	    asymm_KcKc[0]->Fill(cos_reco);
	    asymm_KcKc[1]->Fill(cos_reco_truth);
	  }
	  
	  if(fabs(mc_quark_pdg[0])<4 && Kv_p<Kvcut) {
	    asymm_KcKc[3]->Fill(cos_reco);
	  }
	  if(fabs(mc_quark_pdg[0])==4 && Kv_p<Kvcut) {
	    asymm_KcKc[4]->Fill(cos_reco);
	  }
	  if(Kv_p>Kvcut) {
	    asymm_KcKc[5]->Fill(cos_reco);
	  }		
	  //	taken = true;	  
	}
	//  }
    
      if(taken == false) {      
	if( Kc[0]!=0 || Kc[1]!=0) {
	  
	  float cos_reco =-2;
	  if(Kc[0]!=0 && Kc[0] < 0) cos_reco=costheta_KcBc;
	  if(Kc[0]!=0 && Kc[0] > 0) cos_reco=-costheta_KcBc;
	  if(Kc[0]==0 && Kc[1] > 0) cos_reco=costheta_KcBc;
	  if(Kc[0]==0 && Kc[1] < 0) cos_reco=-costheta_KcBc;
	  
	  h_bbbar_KcBc_reco->Fill( costheta_KcBc);
	  
	  h_cos_charge_KcBc->Fill(costheta_KcBc);
	  h_cos_charge_KcBc->Fill(-costheta_KcBc);
	  bbbar_KcBc_reco++;
	  
	  if( fabs(mc_quark_pdg[0]==5) && Kv_p<Kvcut) {
	    h_resolution_KcBc->Fill(cos_truth,cos_reco_truth);
	    h_resolution_jettrack_KcBc->Fill(cos_truth,cos_trackreco_truth);
	    
	    asymm_KcBc[0]->Fill(cos_reco);
	    asymm_KcBc[1]->Fill(cos_reco_truth);
	  }
	  
	  if(fabs(mc_quark_pdg[0])<4 && Kv_p<Kvcut) {
	    asymm_KcBc[3]->Fill(cos_reco);
	  }
	  if(fabs(mc_quark_pdg[0])==4 && Kv_p<Kvcut) {
	    asymm_KcBc[4]->Fill(cos_reco);
	  }
	  if(Kv_p>Kvcut) {
	    asymm_KcBc[5]->Fill(cos_reco);
	  }
	  
	  taken = true;
	}
      }
      
      if(taken==true &&	fabs(mc_quark_pdg[0])==5 && Kv_p<Kvcut ) h_bbbar_recocuts->Fill(costheta_bbbar);
    }


    if(cuts==12) {

   
      // ------------------------------------------------------------------------
      // Bc Bc case
      // calculate asymmetry for the different categories
      //Information to calculate p, for BcBc category
      if(taken ==false) {    
	if(Bc[0]*Bc[1]>0) {
	  h_bbbar_BcBc_rejected->Fill( costheta_BcBc);
	  h_bbbar_BcBc_rejected->Fill( -costheta_BcBc);
	}
	if(Bc[0]*Bc[1]<0) {
	  if(Bc[0] < 0) h_bbbar_BcBc_reco->Fill(costheta_BcBc);
	  else h_bbbar_BcBc_reco->Fill( -costheta_BcBc);
	
	  h_cos_charge_BcBc->Fill(costheta_BcBc);
	  h_cos_charge_BcBc->Fill(-costheta_BcBc);
	
	  float cos_reco=  (Bc[0] < 0) ? costheta_BcBc: -costheta_BcBc;
	  bbbar_BcBc_reco++;

	  if( fabs(mc_quark_pdg[0]==5) && Kv_p<Kvcut)	{
	    h_resolution_BcBc->Fill(cos_truth,cos_reco_truth);
	    h_resolution_jettrack_BcBc->Fill(cos_truth,cos_trackreco_truth);

	    asymm_BcBc[0]->Fill(cos_reco);
	    asymm_BcBc[1]->Fill(cos_reco_truth);
	  }

	  if(fabs(mc_quark_pdg[0])<4 && Kv_p<Kvcut) {
	    asymm_BcBc[3]->Fill(cos_reco);
	    h_qq_BcBc_rejected->Fill(cos_reco);   
	  }

	  if(fabs(mc_quark_pdg[0])==4 && Kv_p<Kvcut) {
	    asymm_BcBc[4]->Fill(cos_reco);
	    h_cc_BcBc_rejected->Fill(cos_reco);   
	  }
	
	  if(Kv_p>Kvcut) {
	    asymm_BcBc[5]->Fill(cos_reco);
	    h_radreturn_KcKc_rejected->Fill(cos_reco);   
	  }
	
	  taken = true;

	}
      }
        // -------------------------------------------------------------------------
      //Information to calculate p, for KcKc category      
      if(taken == false ) {
	if(Kc[0]*Kc[1]>0) {
	  h_bbbar_KcKc_rejected->Fill( costheta_KcKc);
	  h_bbbar_KcKc_rejected->Fill( -costheta_KcKc);
	}
	
	if(Kc[0]*Kc[1]<0) {
	  if(Kc[0] < 0) h_bbbar_KcKc_reco->Fill(costheta_KcKc);
	  else h_bbbar_KcKc_reco->Fill( -costheta_KcKc);
	  h_cos_charge_KcKc->Fill(costheta_KcKc);
	  h_cos_charge_KcKc->Fill(-costheta_KcKc);
	
	  float cos_reco=  (Kc[0] < 0) ? costheta_KcKc: -costheta_KcKc;
	  bbbar_KcKc_reco++;

	  if( fabs(mc_quark_pdg[0]==5) && Kv_p<Kvcut)	{
	    h_resolution_KcKc->Fill(cos_truth,cos_reco_truth);
	    h_resolution_jettrack_KcKc->Fill(cos_truth,cos_trackreco_truth);
	  
	    asymm_KcKc[0]->Fill(cos_reco);
	    asymm_KcKc[1]->Fill(cos_reco_truth);
	  }
	  
	  if(fabs(mc_quark_pdg[0])<4 && Kv_p<Kvcut) {
	    asymm_KcKc[3]->Fill(cos_reco);
	    h_qq_KcKc_rejected->Fill(cos_reco);   
	  }

	  if(fabs(mc_quark_pdg[0])==4 && Kv_p<Kvcut) {
	    asymm_KcKc[4]->Fill(cos_reco);
	    h_cc_KcKc_rejected->Fill(cos_reco);   
	  }

	
	  if(Kv_p>Kvcut) {
	    asymm_KcKc[5]->Fill(cos_reco);
	    h_radreturn_KcKc_rejected->Fill(cos_reco);   
	  }		
	  taken = true;	  
	}
      }
      // ------------------------------------------------------------------------
      //Information to calculate p, for BcKc category
      if(Bc[0]*Kc[1]>0 && Bc[1]==0 && Kc[0]==0 ){
	h_bbbar_BcKc_rejected->Fill(costheta_BcKc);
	h_bbbar_BcKc_rejected->Fill(-costheta_BcKc);
      }
      if( Bc[0]*Kc[1]<0 && Bc[1]==0 && Kc[0]==0) {
	if(Bc[0] < 0) h_bbbar_BcKc_reco->Fill( costheta_BcKc);
	else h_bbbar_BcKc_reco->Fill( -costheta_BcKc);
      }
    
      if(taken == false) {
	if( Bc[0]*Kc[1]<0 && Bc[1]==0 && Kc[0]==0) {
	
	  h_cos_charge_BcKc->Fill(costheta_BcKc);
	  h_cos_charge_BcKc->Fill(-costheta_BcKc);
	
	  float cos_reco=  (Bc[0] < 0) ? costheta_BcKc: -costheta_BcKc;
	  bbbar_BcKc_reco++;
	
	  if( fabs(mc_quark_pdg[0]==5) && Kv_p<Kvcut)	{
	    h_resolution_BcKc->Fill(cos_truth,cos_reco_truth);
	    h_resolution_jettrack_BcKc->Fill(cos_truth,cos_trackreco_truth);

	    asymm_BcKc[0]->Fill(cos_reco);
	    asymm_BcKc[1]->Fill(cos_reco_truth);
	  }
	  
	  if(fabs(mc_quark_pdg[0])<4 && Kv_p<Kvcut) {
	    asymm_BcKc[3]->Fill(cos_reco);
	    h_qq_BcKc_rejected->Fill(cos_reco);   
	  }

	  if(fabs(mc_quark_pdg[0])==4 && Kv_p<Kvcut) {
	    asymm_BcKc[4]->Fill(cos_reco);
	    h_cc_BcKc_rejected->Fill(cos_reco);   
	  }
		
	  if(Kv_p>Kvcut) {
	    asymm_BcKc[5]->Fill(cos_reco);
	    h_radreturn_BcKc_rejected->Fill(cos_reco);   
	  }
	  taken = true;
	}
      }
    
      // ------------------------------------------------------------------------
      //Information to calculate p, for KcBc category
      if(Kc[0]*Bc[1]>0 && Bc[0]==0 && Kc[1]==0) {
	h_bbbar_KcBc_rejected->Fill( costheta_KcBc);
	h_bbbar_KcBc_rejected->Fill( -costheta_KcBc);
      }
      if( Kc[0]*Bc[1]<0 && Bc[0]==0 && Kc[1]==0)  {
      
	if(Kc[0] < 0) h_bbbar_KcBc_reco->Fill( costheta_KcBc);
	else h_bbbar_KcBc_reco->Fill( -costheta_KcBc);
      }
      if(taken == false) {
	if( Kc[0]*Bc[1]<0 && Bc[0]==0 && Kc[1]==0)  {
	
	  h_cos_charge_KcBc->Fill(costheta_KcBc);
	  h_cos_charge_KcBc->Fill(-costheta_KcBc);
	
	  float cos_reco=  (Kc[0] < 0) ? costheta_KcBc: -costheta_KcBc;
	  bbbar_KcBc_reco++;
	
	  if( fabs(mc_quark_pdg[0]==5) && Kv_p<Kvcut) {
	    h_resolution_KcBc->Fill(cos_truth,cos_reco_truth);
	    h_resolution_jettrack_KcBc->Fill(cos_truth,cos_trackreco_truth);

	    asymm_KcBc[0]->Fill(cos_reco);
	    asymm_KcBc[1]->Fill(cos_reco_truth);
	  }
	
	  if(fabs(mc_quark_pdg[0])<4 && Kv_p<Kvcut) {
	    asymm_KcBc[3]->Fill(cos_reco);
	    h_qq_KcBc_rejected->Fill(cos_reco);   
	  }

	  if(fabs(mc_quark_pdg[0])==4 && Kv_p<Kvcut) {
	    asymm_KcBc[4]->Fill(cos_reco);
	    h_cc_KcBc_rejected->Fill(cos_reco);   
	  }
	  if(Kv_p>Kvcut) {
	    asymm_KcBc[5]->Fill(cos_reco);
	    h_radreturn_KcBc_rejected->Fill(cos_reco);   
	  }
	  taken = true;
	}
      }
    
      // --------------------------------------------------------------------------
      // Same side 1
      //Information to calculate p, for BcKc category

      if(taken == false && jet_btag[1]>btag2) {
      
	if(Bc[0]*Kc[0]<0 ){
	  h_bbbar_BcKc_same1_rejected->Fill( costheta_BcKc_same1);
	  h_bbbar_BcKc_same1_rejected->Fill( -costheta_BcKc_same1);
	}
      
	if( Bc[0]*Kc[0]>0 && Bc[1]==0 && Kc[1]==0 ) {
	
	  if(Bc[0] < 0) h_bbbar_BcKc_same1_reco->Fill( costheta_BcKc_same1);
	  else h_bbbar_BcKc_same1_reco->Fill( -costheta_BcKc_same1);
 	
	  float cos_reco=  (Bc[0] < 0) ? costheta_BcKc_same1: -costheta_BcKc_same1;
	
	  h_cos_charge_BcKc_same1->Fill(costheta_BcKc_same1);
	  h_cos_charge_BcKc_same1->Fill(-costheta_BcKc_same1);
	  bbbar_BcKc_same1_reco++;
	
	  if( fabs(mc_quark_pdg[0]==5) && Kv_p<Kvcut) {
	    h_resolution_BcKc_same1->Fill(cos_truth,cos_reco_truth);
	    h_resolution_jettrack_BcKc_same1->Fill(cos_truth,cos_trackreco_truth);
	  
	    asymm_BcKc_same1[0]->Fill(cos_reco);
	    asymm_BcKc_same1[1]->Fill(cos_reco_truth);
	  }
	
	  if(fabs(mc_quark_pdg[0])<4 && Kv_p<Kvcut) {
	    asymm_BcKc_same1[3]->Fill(cos_reco);
	    h_qq_BcKc_same1_rejected->Fill(cos_reco);   
	  }
	  if(fabs(mc_quark_pdg[0])==4 && Kv_p<Kvcut) {
	    asymm_BcKc_same1[4]->Fill(cos_reco);
	    h_cc_BcKc_same1_rejected->Fill(cos_reco);   
	  }
	  if(Kv_p>Kvcut) {
	    asymm_BcKc_same1[5]->Fill(cos_reco);
	    h_radreturn_BcKc_same1_rejected->Fill(cos_reco);   
	  }
	
	  taken = true;
	}
      }
    
      // --------------------------------------------------------------------------
      // Same side 2
      //Information to calculate p, for BcKc category

      if(taken == false && jet_btag[0]>btag1) {      

	if(Bc[1]*Kc[1]<0){
	  h_bbbar_BcKc_same2_rejected->Fill( costheta_BcKc_same2);
	  h_bbbar_BcKc_same2_rejected->Fill( -costheta_BcKc_same2);
	}
	if( Bc[1]*Kc[1]>0 && Bc[0]==0 && Kc[0]==0 ) {
	  if(Bc[1] > 0) h_bbbar_BcKc_same2_reco->Fill( costheta_BcKc_same2);
	  else h_bbbar_BcKc_same2_reco->Fill( -costheta_BcKc_same2);

	  float cos_reco=  (Bc[1] > 0) ? costheta_BcKc_same2: -costheta_BcKc_same2;
	  h_cos_charge_BcKc_same2->Fill(costheta_BcKc_same2);
	  h_cos_charge_BcKc_same2->Fill(-costheta_BcKc_same2);
	  bbbar_BcKc_same2_reco++;

	  if( fabs(mc_quark_pdg[0]==5) && Kv_p<Kvcut) {
	    h_resolution_BcKc_same2->Fill(cos_truth,cos_reco_truth);
	    h_resolution_jettrack_BcKc_same2->Fill(cos_truth,cos_trackreco_truth);

	    asymm_BcKc_same2[0]->Fill(cos_reco);
	    asymm_BcKc_same2[1]->Fill(cos_reco_truth);
	  }
	  
	  if(fabs(mc_quark_pdg[0])<4 && Kv_p<Kvcut) {
	    asymm_BcKc_same2[3]->Fill(cos_reco);
	    h_qq_BcKc_same2_rejected->Fill(cos_reco);   
	  }

	  if(fabs(mc_quark_pdg[0])==4 && Kv_p<Kvcut) {
	    asymm_BcKc_same2[4]->Fill(cos_reco);
	    h_cc_BcKc_same2_rejected->Fill(cos_reco);   
	  }
	  if(Kv_p>Kvcut) {
	    asymm_BcKc_same2[5]->Fill(cos_reco);
	    h_radreturn_BcKc_same2_rejected->Fill(cos_reco);   
	  }
	
	  taken = true;
	}
      }
      if(taken==true &&	fabs(mc_quark_pdg[0])==5 && Kv_p<Kvcut ) h_bbbar_recocuts->Fill(costheta_bbbar);
    }
    
  }//end loop


  // ***************************************************************  

  CoutEfficiencies();
  HistoEfficiencies();
  TH1F * p_b_histo;
  TH1F * p_k_histo;
  TH1F * p_bk_histo;
  TH1F * p_kb_histo;
  TH1F * p_bk_same1_histo;
  TH1F * p_bk_same2_histo;
  if(cuts==12) {
    p_b_histo = MakeCorrection("BcBc",h_bbbar_BcBc_reco,h_bbbar_BcBc_rejected);
    p_k_histo = MakeCorrection("KcKc",h_bbbar_KcKc_reco,h_bbbar_KcKc_rejected);
    p_bk_histo = MakeCorrection("BcKc",h_bbbar_BcKc_reco,h_bbbar_BcKc_rejected);
    p_kb_histo = MakeCorrection("KcBc",h_bbbar_KcBc_reco,h_bbbar_KcBc_rejected);
    p_bk_same1_histo = MakeCorrection("BcKc_same1",h_bbbar_BcKc_same1_reco,h_bbbar_BcKc_same1_rejected);
    p_bk_same2_histo = MakeCorrection("BcKc_same2",h_bbbar_BcKc_same2_reco,h_bbbar_BcKc_same2_rejected);
  }
  if(cuts==11) {
    p_b_histo = MakeCorrection("BcBc",h_bbbar_BcBc_reco,h_bbbar_BcBc_rejected);
    p_k_histo = MakeCorrection("KcKc",h_bbbar_KcKc_reco,h_bbbar_KcKc_rejected);
    p_bk_histo = MakeCorrectionSingle("BcKc",h_bbbar_BcBc_reco,h_bbbar_BcBc_rejected);
    p_kb_histo = MakeCorrectionSingle("KcBc",h_bbbar_KcKc_reco,h_bbbar_KcKc_rejected);
    p_bk_same1_histo = MakeCorrection("BcKc_same1",h_bbbar_BcKc_same1_reco,h_bbbar_BcKc_same1_rejected);
    p_bk_same2_histo = MakeCorrection("BcKc_same2",h_bbbar_BcKc_same2_reco,h_bbbar_BcKc_same2_rejected);
  }

  // ***************************************************************  

  std::vector<TH1F*> result;
  result.push_back(asymm_BcBc[0]);//reco
  result.push_back(asymm_BcBc[1]);//truth
  result.push_back(asymm_BcBc[2]);//corrected
  result.push_back(asymm_BcBc[3]);//bkg_qq
  result.push_back(asymm_BcBc[4]);//bkg_cc
  result.push_back(asymm_BcBc[5]);//bkg_radreturn
  result.push_back(p_b_histo);

  result.push_back(asymm_KcKc[0]);//reco
  result.push_back(asymm_KcKc[1]);//truth
  result.push_back(asymm_KcKc[2]);//corrected
  result.push_back(asymm_KcKc[3]);//bkg_qq
  result.push_back(asymm_KcKc[4]);//bkg_cc
  result.push_back(asymm_KcKc[5]);//bkg_radreturn
  result.push_back(p_k_histo);

  result.push_back(asymm_BcKc[0]);//reco
  result.push_back(asymm_BcKc[1]);//truth
  result.push_back(asymm_BcKc[2]);//corrected
  result.push_back(asymm_BcKc[3]);//bkg_qq
  result.push_back(asymm_BcKc[4]);//bkg_cc
  result.push_back(asymm_BcKc[5]);//bkg_radreturn
  result.push_back(p_bk_histo);

  result.push_back(asymm_KcBc[0]);//reco
  result.push_back(asymm_KcBc[1]);//truth
  result.push_back(asymm_KcBc[2]);//corrected
  result.push_back(asymm_KcBc[3]);//bkg_qq
  result.push_back(asymm_KcBc[4]);//bkg_cc
  result.push_back(asymm_KcBc[5]);//bkg_radreturn
  result.push_back(p_kb_histo);

  result.push_back(asymm_BcKc_same1[0]);//reco
  result.push_back(asymm_BcKc_same1[1]);//truth
  result.push_back(asymm_BcKc_same1[2]);//corrected
  result.push_back(asymm_BcKc_same1[3]);//bkg_qq
  result.push_back(asymm_BcKc_same1[4]);//bkg_cc
  result.push_back(asymm_BcKc_same1[5]);//bkg_radreturn
  result.push_back(p_bk_same1_histo);

  result.push_back(asymm_BcKc_same2[0]);//reco
  result.push_back(asymm_BcKc_same2[1]);//truth
  result.push_back(asymm_BcKc_same2[2]);//corrected
  result.push_back(asymm_BcKc_same2[3]);//bkg_qq
  result.push_back(asymm_BcKc_same2[4]);//bkg_cc
  result.push_back(asymm_BcKc_same2[5]);//bkg_radreturn
  result.push_back(p_bk_same2_histo); 


  //efficiencies
  result.push_back(h_bbbar);
  result.push_back(h_cos_preselection);
  result.push_back(h_cos_charge_BcBc);
  result.push_back(h_cos_charge_KcKc);
  result.push_back(h_cos_charge_BcKc);
  result.push_back(h_cos_charge_KcBc);
  result.push_back(h_cos_charge_BcKc_same1);
  result.push_back(h_cos_charge_BcKc_same2);

  result.push_back(h_bbbar_recocuts);

  //Rejected
  result.push_back(h_bbbar_BcBc_rejected);
  result.push_back(h_bbbar_KcKc_rejected);
  result.push_back(h_bbbar_BcKc_rejected);
  result.push_back(h_bbbar_KcBc_rejected);
  result.push_back(h_bbbar_BcKc_same1_rejected);
  result.push_back(h_bbbar_BcKc_same2_rejected);

  //Rejected qq
  result.push_back(h_qq_BcBc_rejected);
  result.push_back(h_qq_KcKc_rejected);
  result.push_back(h_qq_BcKc_rejected);
  result.push_back(h_qq_KcBc_rejected);
  result.push_back(h_qq_BcKc_same1_rejected);
  result.push_back(h_qq_BcKc_same2_rejected);
  //Rejected cc
  result.push_back(h_cc_BcBc_rejected);
  result.push_back(h_cc_KcKc_rejected);
  result.push_back(h_cc_BcKc_rejected);
  result.push_back(h_cc_KcBc_rejected);
  result.push_back(h_cc_BcKc_same1_rejected);
  result.push_back(h_cc_BcKc_same2_rejected);
  
  //Rejected radreturn
  result.push_back(h_radreturn_BcBc_rejected);
  result.push_back(h_radreturn_KcKc_rejected);
  result.push_back(h_radreturn_BcKc_rejected);
  result.push_back(h_radreturn_KcBc_rejected);
  result.push_back(h_radreturn_BcKc_same1_rejected);
  result.push_back(h_radreturn_BcKc_same2_rejected);

  
  std::vector<TH2F*> result2;
  result2.push_back(h_resolution_BcBc);
  result2.push_back(h_resolution_KcKc);
  result2.push_back(h_resolution_BcKc);
  result2.push_back(h_resolution_KcBc);
  result2.push_back(h_resolution_BcKc_same1);
  result2.push_back(h_resolution_BcKc_same2);
  result2.push_back(h_resolution_jettrack_BcBc);
  result2.push_back(h_resolution_jettrack_KcKc);
  result2.push_back(h_resolution_jettrack_BcKc);
  result2.push_back(h_resolution_jettrack_KcBc);
  result2.push_back(h_resolution_jettrack_BcKc_same1);
  result2.push_back(h_resolution_jettrack_BcKc_same2);
  
  SaveRootFile(result,result2,polarization);
  

}


void observable::AnalysisBKG(int n_entries=-1, TString polarization="eL", int n=20, int cuts=3,float Kvcut=35)
{

  InitializeHistos(n);
  
  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    
    /// charge calculation
    int Kc[2];
    Kc[0]=0; Kc[1]=0;

    int Bc[2];
    Bc[0]=0; Bc[1]=0;
      
    for(int ijet=0; ijet<2; ijet++) {
      Bc[ijet]=ChargeBcJet(ijet);
      Kc[ijet]=ChargeKcJet(ijet);
    }

    //angle calculation
    float costheta_KcKc;
    float costheta_BcBc;
    float costheta_BcKc;
    float costheta_KcBc;
    float costheta_BcKc_same1;
    float costheta_BcKc_same2;

    /*std::vector<float> p;
      p.push_back(jet_px[0]-jet_px[1]);
      p.push_back(jet_py[0]-jet_py[1]);
      p.push_back(jet_pz[0]-jet_pz[1]);

    
      costheta_BcBc=GetCostheta(p);
      costheta_KcKc=GetCostheta(p);
      costheta_BcKc=GetCostheta(p);
      costheta_KcBc=GetCostheta(p);
      costheta_BcKc_same1=GetCostheta(p);
      costheta_BcKc_same2=GetCostheta(p);*/

    // angle for jets reconstructed only with secondary vertex tracks
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
   
    costheta_BcBc=costheta_tracks;
    costheta_KcKc=costheta_tracks;
    costheta_BcKc=costheta_tracks;
    costheta_KcBc=costheta_tracks;
    costheta_BcKc_same1=costheta_tracks;
    costheta_BcKc_same2=costheta_tracks;
   

    if(PreSelection(5,Kvcut)==false) continue; 
    preselection++;
    
    bool taken = false;
    bool rejected = false;

    if(cuts==11) {

      	if( Bc[0]!=0 || Bc[1]!=0) {

	  float cos_reco =-2;
	  if(Bc[0]!=0 && Bc[0] < 0) cos_reco=costheta_BcKc;
	  if(Bc[0]!=0 && Bc[0] > 0) cos_reco=-costheta_BcKc;
	  if(Bc[0]==0 && Bc[1] > 0) cos_reco=costheta_BcKc;
	  if(Bc[0]==0 && Bc[1] < 0) cos_reco=-costheta_BcKc;
	  
	  asymm_BcKc[0]->Fill(cos_reco);
	  taken = true;
	  
	}

	if( Kc[0]!=0 || Kc[1]!=0) {

	  float cos_reco =-2;
	  if(Kc[0]!=0 && Kc[0] < 0) cos_reco=costheta_KcBc;
	  if(Kc[0]!=0 && Kc[0] > 0) cos_reco=-costheta_KcBc;
	  if(Kc[0]==0 && Kc[1] > 0) cos_reco=costheta_KcBc;
	  if(Kc[0]==0 && Kc[1] < 0) cos_reco=-costheta_KcBc;
	  
	  asymm_KcBc[0]->Fill(cos_reco);
	  taken = true;
	  
	}

    }

    if(cuts==12) {
      // ------------------------------------------------------------------------
      // Bc Bc case
      // calculate asymmetry for the different categories
      //Information to calculate p, for BcBc category
      if(taken ==false) {
	if(Bc[0]*Bc[1]>0) {
	  h_bbbar_BcBc_rejected->Fill( costheta_BcBc);
	  h_bbbar_BcBc_rejected->Fill( -costheta_BcBc);
	}
	if(Bc[0]*Bc[1]<0) {
	  float cos_reco=  (Bc[0] < 0) ? costheta_BcBc: -costheta_BcBc;
	  asymm_BcBc[0]->Fill(cos_reco);
	  taken = true;
	}
      }
      
      // -------------------------------------------------------------------------
      //Information to calculate p, for KcKc category      
      if(taken == false ) {	
	if(Kc[0]*Kc[1]>0) {
	  h_bbbar_KcKc_rejected->Fill( costheta_KcKc);
	  h_bbbar_KcKc_rejected->Fill( -costheta_KcKc);
	}
	if(Kc[0]*Kc[1]<0) {
	  float cos_reco=  (Kc[0] < 0) ? costheta_KcKc: -costheta_KcKc;
	  asymm_KcKc[0]->Fill(cos_reco);
	  taken = true;
	}
      }
      // ------------------------------------------------------------------------
      //Information to calculate p, for BcKc category
      if(Bc[0]*Kc[1]>0 && Bc[1]==0 && Kc[0]==0 ){
	h_bbbar_BcKc_rejected->Fill(costheta_BcKc);
	h_bbbar_BcKc_rejected->Fill(-costheta_BcKc);
      }
      if(taken == false) {
	if( Bc[0]*Kc[1]<0 && Bc[1]==0 && Kc[0]==0) {
	  float cos_reco=  (Bc[0] < 0) ? costheta_BcKc: -costheta_BcKc;
	  asymm_BcKc[0]->Fill(cos_reco);
	  taken = true;
	}
      }
      
      // ------------------------------------------------------------------------
      //Information to calculate p, for KcBc category
      if(Kc[0]*Bc[1]>0 && Bc[0]==0 && Kc[1]==0) {
	h_bbbar_KcBc_rejected->Fill( costheta_KcBc);
	h_bbbar_KcBc_rejected->Fill( -costheta_KcBc);
      }
      if(taken == false) {
	if( Kc[0]*Bc[1]<0 && Bc[0]==0 && Kc[1]==0)  {
	  float cos_reco=  (Kc[0] < 0) ? costheta_KcBc: -costheta_KcBc;
	  asymm_KcBc[0]->Fill(cos_reco);
	  taken = true;
	}
      }
      
      
      // --------------------------------------------------------------------------
      // Same side 1
      //Information to calculate p, for BcKc category
      if(taken == false && jet_btag[1]>btag2) {
	if(Bc[0]*Kc[0]<0  ){
	  h_bbbar_BcKc_same1_rejected->Fill( costheta_BcKc_same1);
	  h_bbbar_BcKc_same1_rejected->Fill( -costheta_BcKc_same1);
	}
	if( Bc[0]*Kc[0]>0 && (Bc[1]==0 && Kc[1]==0) ) {	
	  float cos_reco=  (Bc[0] < 0) ? costheta_BcKc_same1: -costheta_BcKc_same1;
	  asymm_BcKc_same1[0]->Fill(cos_reco);
	  
	  taken = true;
	}
      }
      
      // --------------------------------------------------------------------------
      // Same side 2
      //Information to calculate p, for BcKc category
      if(taken == false && jet_btag[0]>btag1) {
	if(Bc[1]*Kc[1]<0){
	  h_bbbar_BcKc_same2_rejected->Fill( costheta_BcKc_same2);
	  h_bbbar_BcKc_same2_rejected->Fill( -costheta_BcKc_same2);
	}
	if( Bc[1]*Kc[1]>0 && Bc[0]==0 && Kc[0]==0 ) {
	  float cos_reco=  (Bc[1] > 0) ? costheta_BcKc_same2: -costheta_BcKc_same2;
	  asymm_BcKc_same2[0]->Fill(cos_reco);
	  taken = true;
	}
      }
    }
    
  }//end loop

  // ***************************************************************  
  std::vector<TH1F*> result;
  result.push_back(asymm_BcBc[0]);//reco
  result.push_back(asymm_KcKc[0]);
  result.push_back(asymm_BcKc[0]);
  result.push_back(asymm_KcBc[0]);
  result.push_back(asymm_BcKc_same1[0]);
  result.push_back(asymm_BcKc_same2[0]);
  
  //Rejected
  result.push_back(h_bbbar_BcBc_rejected);
  result.push_back(h_bbbar_KcKc_rejected);
  result.push_back(h_bbbar_BcKc_rejected);
  result.push_back(h_bbbar_KcBc_rejected);
  result.push_back(h_bbbar_BcKc_same1_rejected);
  result.push_back(h_bbbar_BcKc_same2_rejected);
  
  SaveRootFile(result,polarization);
  

}


void observable::KStudy(int n_entries=-1, int selection_type=0, TString polarization="eL", float Kcut=2500)
{
  
  TFile *MyFile = new TFile(TString::Format("kstudy_%s_250GeV_%s.root",process.Data(),polarization.Data()),"RECREATE");
  MyFile->cd();
  
  //  gROOT->Reset();
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(0.3);

  //0=signal, 1=rad ret (1 ISR), 2=rad ret (2 ISR)
  TH1F * h_KISR_1[3];
  TH1F * h_KISR_2[3];
  TH1F * h_KISR[3];
  for(int i=0; i<3; i++) {
    h_KISR_1[i] = new TH1F(TString::Format("h_KISR_1_%i",i),TString::Format("h_KISR_1_%i",i),2000,0,200);
    h_KISR_2[i] = new TH1F(TString::Format("h_KISR_2_%i",i),TString::Format("h_KISR_2_%i",i),2000,0,200);
    h_KISR[i] = new TH1F(TString::Format("h_KISR_%i",i),TString::Format("h_KISR_%i",i),2000,0,200);
  }

  TH1F * h_KReco_1[3];
  TH1F * h_KReco_2[3];
  TH1F * h_KReco_geom[3];
  TH1F * h_KReco_1plus2[3];
  TH1F * h_KReco_1minus2[3];
  TH1F * h_KReco_1plus2divgeom[3];
  TH1F * h_KReco_1divgeom[3];
  TH1F * h_KReco_2divgeom[3];
  TH1F * h_KReco_1divgeom_plus_2divgeom[3];
  TH1F * h_KReco_1plus2minusgeom[3];

  TH2F * h_K2D[3];

  
  TH1F * h_KReco_1minus2divgeom[3];
  TH2F * h_KReco_1vsgeom[3];
  TH2F * h_KReco_1ratiovsgeom[3];
  TH2F * h_KReco_2vsgeom[3];
  TH2F * h_KReco_2ratiovsgeom[3];

  for(int i=0; i<3; i++) {
    h_KReco_1[i] = new TH1F(TString::Format("h_KReco_1_%i",i),TString::Format("h_KReco_1_%i",i),2000,0,200);
    h_KReco_2[i] = new TH1F(TString::Format("h_KReco_2_%i",i),TString::Format("h_KReco_2_%i",i),2000,0,200);
    h_KReco_geom[i] = new TH1F(TString::Format("h_KReco_geom_%i",i),TString::Format("h_KReco_geom_%i",i),2000,0,200);
    h_KReco_1plus2[i] = new TH1F(TString::Format("h_KReco_1plus2_%i",i),TString::Format("h_KReco_1plus2_%i",i),2000,0,200);
    h_KReco_1plus2minusgeom[i] = new TH1F(TString::Format("h_KReco_1plus2minusgeom_%i",i),TString::Format("h_KReco_1plus2minusgeom_%i",i),2000,-100,100);
    h_K2D[i] = new TH2F(TString::Format("h_K2D_%i",i),TString::Format("h_K2D_%i",i),2000,-100,100,2000,0,10);

    h_KReco_1minus2[i] = new TH1F(TString::Format("h_KReco_1minus2_%i",i),TString::Format("h_KReco_1minus2_%i",i),2000,0,200);
    h_KReco_1plus2divgeom[i] = new TH1F(TString::Format("h_KReco_1plus2divgeom_%i",i),TString::Format("h_KReco_1plus2divgeom_%i",i),20000,0,200);
    h_KReco_1divgeom[i] = new TH1F(TString::Format("h_KReco_1divgeom_%i",i),TString::Format("h_KReco_1divgeom_%i",i),20000,0,200);
    h_KReco_2divgeom[i] = new TH1F(TString::Format("h_KReco_2divgeom_%i",i),TString::Format("h_KReco_2divgeom_%i",i),20000,0,200);

    h_KReco_1divgeom_plus_2divgeom[i] = new TH1F(TString::Format("h_KReco_1divgeom_plus_2divgeom_%i",i),TString::Format("h_KReco_1divgeom_plus_2divgeom_%i",i),20000,0,200);

    h_KReco_1minus2divgeom[i] = new TH1F(TString::Format("h_KReco_1minus2divgeom_%i",i),TString::Format("h_KReco_1minus2divgeom_%i",i),20000,-100,100);
    h_KReco_1vsgeom[i] = new TH2F(TString::Format("h_KReco_1vsgeom_%i",i),TString::Format("h_KReco_1vsgeom_%i",i),2000,0,200,2000,0,200);
    h_KReco_1ratiovsgeom[i] = new TH2F(TString::Format("h_KReco_1ratiovsgeom_%i",i),TString::Format("h_KReco_1ratiovsgeom_%i",i),2000,0,10,2000,0,200);
    h_KReco_2vsgeom[i] = new TH2F(TString::Format("h_KReco_2vsgeom_%i",i),TString::Format("h_KReco_2vsgeom_%i",i),2000,0,200,2000,0,200);
    h_KReco_2ratiovsgeom[i] = new TH2F(TString::Format("h_KReco_2ratiovsgeom_%i",i),TString::Format("h_KReco_2ratiovsgeom_%i",i),2000,0,10,2000,0,200);
  
  }
  
  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  int bb_counter=0, radreturn_counter=0, qq_counter=0, cc_counter=0;
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e + gamma1_e;//_ISR_px[0]+mc_ISR_px[1],2)+pow(mc_ISR_py[0]+mc_ISR_py[1],2)+pow(mc_ISR_pz[0]+mc_ISR_pz[1],2));//gamma0_e+gamma1_e;

    float max_gamma_e=gamma0_e;
    if(gamma1_e>max_gamma_e) max_gamma_e=gamma1_e;

    bool singleISR=true;
    if(gamma0_e>Kcut && gamma1_e>Kcut) singleISR=false;
    
    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;


    //reco stuff
    float jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
    float jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

    float costheta_j0;
    std::vector<float> p_j0;
    p_j0.push_back(jet_px[0]);
    p_j0.push_back(jet_py[0]);
    p_j0.push_back(jet_pz[0]);
    costheta_j0=GetCostheta(p_j0);

    float costheta_j1;
    std::vector<float> p_j1;
    p_j1.push_back(jet_px[1]);
    p_j1.push_back(jet_py[1]);
    p_j1.push_back(jet_pz[1]);
    costheta_j1=GetCostheta(p_j1);

    TVector3 v0(jet_px[0],jet_py[0],jet_pz[0]);
    TVector3 v1(jet_px[1],jet_py[1],jet_pz[1]);
    float acol=GetSinacol(v0,v1);
    float Kreco0=acol*jet1_p/sqrt(1-costheta_j0*costheta_j0);
    float Kreco1=acol*jet0_p/sqrt(1-costheta_j1*costheta_j1);
    float K1plusK2=0.5*(Kreco0+Kreco1);
    float K1minusK2=0.5*(Kreco0-Kreco1);

    float Kreco_geom=250.*acol/(acol+sqrt(1-costheta_j0*costheta_j0)+sqrt(1-costheta_j1*costheta_j1));
					
    bool selection=PreSelection(selection_type,Kcut);
    if(selection==false) continue;

    if(gamma_e<Kcut) {
      
      h_KISR_1[0]->Fill(gamma0_e);
      h_KISR_2[0]->Fill(gamma1_e);
      h_KISR[0]->Fill(gamma_e);


      h_KReco_1[0]->Fill(Kreco0);
      h_KReco_2[0]->Fill(Kreco1);
      h_KReco_geom[0]->Fill(Kreco_geom);
      h_KReco_1plus2[0]->Fill(K1plusK2);
      h_KReco_1minus2[0]->Fill(K1minusK2);
      h_KReco_1plus2divgeom[0]->Fill(K1plusK2/Kreco_geom);

      h_KReco_1divgeom[0]->Fill(Kreco0/Kreco_geom);
      h_KReco_2divgeom[0]->Fill(Kreco1/Kreco_geom);
      h_KReco_1divgeom_plus_2divgeom[0]->Fill(Kreco0/Kreco_geom+Kreco1/Kreco_geom);

      h_KReco_1minus2divgeom[0]->Fill(K1minusK2/Kreco_geom);

      h_KReco_1plus2minusgeom[0]->Fill(Kreco0+Kreco1-2.*Kreco_geom);

      h_K2D[0]->Fill(Kreco0+Kreco1-2.*Kreco_geom,K1plusK2/Kreco_geom);

      h_KReco_1vsgeom[0]->Fill(Kreco0,Kreco_geom);
      h_KReco_2vsgeom[0]->Fill(Kreco1,Kreco_geom);
      h_KReco_1ratiovsgeom[0]->Fill(Kreco0/Kreco_geom,Kreco_geom);
      h_KReco_2ratiovsgeom[0]->Fill(Kreco1/Kreco_geom,Kreco_geom);
    }

    if(gamma_e>Kcut && singleISR==true) {
      
      h_KISR_1[1]->Fill(gamma0_e);
      h_KISR_2[1]->Fill(gamma1_e);
      h_KISR[1]->Fill(gamma_e);


      h_KReco_1[1]->Fill(Kreco0);
      h_KReco_2[1]->Fill(Kreco1);
      h_KReco_geom[1]->Fill(Kreco_geom);
      h_KReco_1plus2[1]->Fill(K1plusK2);
      h_KReco_1minus2[1]->Fill(K1minusK2);
      h_KReco_1plus2divgeom[1]->Fill(K1plusK2/Kreco_geom);

      h_KReco_1divgeom[1]->Fill(Kreco0/Kreco_geom);
      h_KReco_2divgeom[1]->Fill(Kreco1/Kreco_geom);
      h_KReco_1divgeom_plus_2divgeom[1]->Fill(Kreco0/Kreco_geom+Kreco1/Kreco_geom);

      h_KReco_1minus2divgeom[1]->Fill(K1minusK2/Kreco_geom);
      h_K2D[1]->Fill(Kreco0+Kreco1-2.*Kreco_geom,K1plusK2/Kreco_geom);

      h_KReco_1plus2minusgeom[1]->Fill(Kreco0+Kreco1-2.*Kreco_geom);
	      
      h_KReco_1vsgeom[1]->Fill(Kreco0,Kreco_geom);
      h_KReco_2vsgeom[1]->Fill(Kreco1,Kreco_geom);
      h_KReco_1ratiovsgeom[1]->Fill(Kreco0/Kreco_geom,Kreco_geom);
      h_KReco_2ratiovsgeom[1]->Fill(Kreco1/Kreco_geom,Kreco_geom);
    }

    if(gamma_e>Kcut && singleISR==false) {
      
      h_KISR_1[2]->Fill(gamma0_e);
      h_KISR_2[2]->Fill(gamma1_e);
      h_KISR[2]->Fill(gamma_e);

      h_KReco_1[2]->Fill(Kreco0);
      h_KReco_2[2]->Fill(Kreco1);
      h_KReco_geom[2]->Fill(Kreco_geom);
      h_KReco_1plus2[2]->Fill(K1plusK2);
      h_KReco_1minus2[2]->Fill(K1minusK2);
      h_KReco_1plus2divgeom[2]->Fill(K1plusK2/Kreco_geom);

      h_KReco_1divgeom[2]->Fill(Kreco0/Kreco_geom);
      h_KReco_2divgeom[2]->Fill(Kreco1/Kreco_geom);
      h_KReco_1divgeom_plus_2divgeom[2]->Fill(Kreco0/Kreco_geom+Kreco1/Kreco_geom);
      h_KReco_1minus2divgeom[2]->Fill(K1minusK2/Kreco_geom);

      h_KReco_1plus2minusgeom[2]->Fill(Kreco0+Kreco1-2.*Kreco_geom);
      h_K2D[2]->Fill(Kreco0+Kreco1-2.*Kreco_geom,K1plusK2/Kreco_geom);
     
      h_KReco_1vsgeom[2]->Fill(Kreco0,Kreco_geom);
      h_KReco_2vsgeom[2]->Fill(Kreco1,Kreco_geom);
      h_KReco_1ratiovsgeom[2]->Fill(Kreco0/Kreco_geom,Kreco_geom);
      h_KReco_2ratiovsgeom[2]->Fill(Kreco1/Kreco_geom,Kreco_geom);
    }
    
    
  }
  cout<<TString::Format("kstudy_%s_250GeV_%s.root",process.Data(),polarization.Data())<<endl;

  for(int i=0; i<3; i++) {
    h_KISR_1[i]->Write();
    h_KISR_2[i]->Write();
    h_KISR[i]->Write();
    h_K2D[i]->Write();
    h_KReco_1[i]->Write();
    h_KReco_2[i]->Write();
    h_KReco_geom[i]->Write();
    h_KReco_1plus2[i]->Write();
    h_KReco_1minus2[i]->Write();
    h_KReco_1plus2divgeom[i]->Write();
    h_KReco_1divgeom[i]->Write();
    h_KReco_2divgeom[i]->Write();
    h_KReco_1divgeom_plus_2divgeom[i]->Write();
    h_KReco_1plus2minusgeom[i]->Write();
    h_KReco_1minus2divgeom[i]->Write();
    h_KReco_1vsgeom[i]->Write();
    h_KReco_2vsgeom[i]->Write();
    h_KReco_1ratiovsgeom[i]->Write();
    h_KReco_2ratiovsgeom[i]->Write();
  }
  
   
}



void observable::IdentifyRR(int n_entries=-1, int selection_type=0, TString polarization="eL", float Kvcut=2500)
{

  TFile *MyFile = new TFile(TString::Format("IdentifyRR_onlyNeutron_%s_250GeV_%s.root",process.Data(),polarization.Data()),"RECREATE");
  MyFile->cd();

  TH1F * h_gamma_K_parton = new TH1F("h_gamma_K_parton","h_gamma_K_parton",250,-0.5,249.5);
  TH1F * h_gamma_costhetaparton = new TH1F("h_gamma_costhetaparton","h_gamma_costhetaparton",10000,-1,1);
  TH2F * h_gamma_K_coshteta_parton = new TH2F("h_gamma_K_coshteta_parton","h_gamma_K_coshteta_parton",100,-1,1,250,-0.5,249.5);

  TH1F * h_gamma_K_parton_b = new TH1F("h_gamma_K_parton_b","h_gamma_K_parton_b",250,-0.5,249.5);
  TH1F * h_gamma_costhetaparton_b = new TH1F("h_gamma_costhetaparton_b","h_gamma_costhetaparton_b",100,-1,1);
  TH2F * h_gamma_K_coshteta_parton_b = new TH2F("h_gamma_K_coshteta_parton_b","h_gamma_K_coshteta_parton_b",100,-1,1,250,-0.5,249.5);


  // parton level plots
  TH2F * h_costheta_parton[5];
  TH1F * h_ISR_E[5];
  TH1F * h_ISR_Ediff[5];
  TH2F * h_ISR_E2d[5];
  
  TH1F * h_FSR_E[5]; 
  TH1F * h_FSR_Ediff[5];
  TH2F * h_FSR_E2d[5]; 
  
  TH1F * h_FSR22_E[5]; 
  TH1F * h_FSR22_Ediff[5];
  TH2F * h_FSR22_E2d[5];
  
  TH1F * h_FSR21_E[5]; 
  TH1F * h_FSR21_Ediff[5];
  TH2F * h_FSR21_E2d[5];

  TH1F * h_y23_parton[5];

  for(int i=0; i<5; i++) {
    h_costheta_parton[i] = new TH2F(TString::Format("h_costheta_parton_%i",i),"h_costheta_parton",200,-1,1,200,-1,1);
    h_ISR_E[i]= new TH1F(TString::Format("h_ISR_E_%i",i),"h_ISR_E",250,0.5,250.5);
    h_ISR_Ediff[i]= new TH1F(TString::Format("h_ISR_Ediff_%i",i),"h_ISR_Ediff",5000,-250,250);
    h_ISR_E2d[i]= new TH2F(TString::Format("h_ISR_E2d_%i",i),"h_ISR_E2d",250,0.5,250.52,50,0.5,250.5);
    
    h_FSR_E[i]= new TH1F(TString::Format("h_FSR_E_%i",i),"h_FSR_E",250,0.5,250.5);
    h_FSR_Ediff[i]= new TH1F(TString::Format("h_FSR_Ediff_%i",i),"h_FSR_Ediff",5000,-250,250);
    h_FSR_E2d[i]= new TH2F(TString::Format("h_FSR_E2d_%i",i),"h_FSR_E2d",250,0.5,250.5,250,0.5,250.5);
    
    h_FSR22_E[i]= new TH1F(TString::Format("h_FSR22_E_%i",i),"h_FSR22_E",250,0.5,250.5);
    h_FSR22_Ediff[i]= new TH1F(TString::Format("h_FSR22_Ediff_%i",i),"h_FSR22_Ediff",5000,-250,250);
    h_FSR22_E2d[i]= new TH2F(TString::Format("h_FSR22_E2d_%i",i),"h_FSR22_E2d",250,0.5,250.5,250,0.5,250.5);
    
    h_FSR21_E[i]= new TH1F(TString::Format("h_FSR21_E_%i",i),"h_FSR21_E",250,0.5,250.5);
    h_FSR21_Ediff[i]= new TH1F(TString::Format("h_FSR21_Ediff_%i",i),"h_FSR21_Ediff",5000,-250,250);
    h_FSR21_E2d[i]= new TH2F(TString::Format("h_FSR21_E2d_%i",i),"h_FSR21_E2d",250,0.5,250.5,250,0.5,250.5);

    h_y23_parton[i] =  new TH1F(TString::Format("h_y23_parton_%i",i),"h_y23_parton",400,0,0.25);

  }
  
  //reco level
  
  TH2F * h_costheta_reco[5];

  TH2F * h_PFOphoton_max_2d[5];
  TH2F * h_PFOphoton_all_2d[5];
  TH2F * h_PFOphoton_ratio_2d[5];
  TH2F * h_PFOphoton_ratio_E_2d[5];

  TH1F * h_PFOphoton_all_costheta[5];
  TH1F * h_PFOphoton_all2_costheta[5];
  TH2F * h_PFOphoton_all_costheta_cosjet[5];
  TH2F * h_PFOphoton_all_E_costheta[5];
  
  TH2F * h_PFOphoton_npfo_ratio_2d[5];

  TH1F * h_y23[5];
  TH1F * h_thrust[5];
  TH2F * h_mjmj_2d[5];
  TH1F * h_mjmj[5];

  for(int i=0; i<5; i++) {
    h_costheta_reco[i] = new TH2F(TString::Format("h_costheta_reco_%i",i),"h_costheta_reco",200,-1,1,200,-1,1);
    h_PFOphoton_max_2d[i] =  new TH2F(TString::Format("h_PFOphoton_max_2d_%i",i),"h_PFOphoton_max_2d",250,0.5,250.5,250,0.5,250.5);
    h_PFOphoton_all_2d[i] =  new TH2F(TString::Format("h_PFOphoton_all_2d_%i",i),"h_PFOphoton_all_2d",250,0.5,250.5,250,0.5,250.5);
    h_PFOphoton_ratio_2d[i] =  new TH2F(TString::Format("h_PFOphoton_ratio_2d_%i",i),"h_PFOphoton_ratio_2d",500,-1,2,500,-1,2);
    h_PFOphoton_ratio_E_2d[i] =  new TH2F(TString::Format("h_PFOphoton_ratio_E_2d_%i",i),"h_PFOphoton_ratio_E_2d",500,-1,2,500,0.5,250.5);

    h_PFOphoton_all_costheta[i] =new TH1F(TString::Format("h_PFOphoton_all_costheta_%i",i),"h_PFOphoton_all_costheta",200,-1,1);
    h_PFOphoton_all2_costheta[i] =new TH1F(TString::Format("h_PFOphoton_all2_costheta_%i",i),"h_PFOphoton_all2_costheta",200,-1,1);
    h_PFOphoton_all_costheta_cosjet[i] = new TH2F(TString::Format("h_PFOphoton_costheta_cosjet_%i",i),"h_PFOphoton_costheta_cosjet",200,-1,1,200,-1,1);
    h_PFOphoton_all_E_costheta[i] = new TH2F(TString::Format("h_PFOphoton_E_costheta_%i",i),"h_PFOphoton_E_costheta",200,-1,1,200,0.5,200.5);

    
    h_PFOphoton_npfo_ratio_2d[i] =  new TH2F(TString::Format("h_PFOphoton_npfo_ratio_2d_%i",i),"h_PFOphoton_npfo_ratio_2d",500,-1,2,100,-0.5,99.5);

    h_y23[i] =  new TH1F(TString::Format("h_y23_%i",i),"h_y23",400,0,0.25);
    h_thrust[i]= new TH1F(TString::Format("h_thrust_%i",i),"h_thrust",1000,0,1);
    h_mjmj_2d[i] = new TH2F(TString::Format("h_mjmj_2d_%i",i),"h_mjmj",2000,0,200,2000,0,200);
    h_mjmj[i] = new TH1F(TString::Format("h_mjmj_%i",i),"h_mjmj",2000,0,200);
  }
  
  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  int bb_counter=0, radreturn_counter=0, qq_counter=0, cc_counter=0;
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    //-------------------
    //Photon ISR parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e + gamma1_e;//_ISR_px[0]+mc_ISR_px[1],2)+pow(mc_ISR_py[0]+mc_ISR_py[1],2)+pow(mc_ISR_pz[0]+mc_ISR_pz[1],2));//gamma0_e+gamma1_e;

    std::vector<float> p_gamma1;
    p_gamma1.push_back(mc_ISR_px[0]);
    p_gamma1.push_back(mc_ISR_py[0]);
    p_gamma1.push_back(mc_ISR_pz[0]);
    float gamma1_costheta=GetCostheta(p_gamma1);

    std::vector<float> p_gamma2;
    p_gamma2.push_back(mc_ISR_px[1]);
    p_gamma2.push_back(mc_ISR_py[1]);
    p_gamma2.push_back(mc_ISR_pz[1]);
    float gamma2_costheta=GetCostheta(p_gamma2);
    
    h_gamma_K_parton ->Fill(gamma0_e);
    h_gamma_K_parton ->Fill(gamma1_e);
    h_gamma_costhetaparton->Fill(gamma1_costheta);
    h_gamma_costhetaparton->Fill(gamma2_costheta);
    h_gamma_K_coshteta_parton->Fill(gamma1_costheta,gamma0_e);
    h_gamma_K_coshteta_parton->Fill(gamma2_costheta,gamma1_e);

    if(fabs(mc_quark_pdg[0])==5) {
      h_gamma_K_parton_b ->Fill(gamma0_e);
      h_gamma_K_parton_b ->Fill(gamma1_e);
      h_gamma_costhetaparton_b->Fill(gamma1_costheta);
      h_gamma_costhetaparton_b->Fill(gamma2_costheta);
      h_gamma_K_coshteta_parton_b->Fill(gamma1_costheta,gamma0_e);
      h_gamma_K_coshteta_parton_b->Fill(gamma2_costheta,gamma1_e);
    }
    //FSR
    float fsr_21=0;
    float fsr_22=0;
    float fsr=0;

    for(int j=0; j<300; j++) {
      if(mc_quark_ps_E[j]<0) continue;
      if(mc_quark_ps_pdg[j]==22 && mc_quark_ps_E[j]>0) fsr_22+=mc_quark_ps_E[j];
      if(mc_quark_ps_pdg[j]==21 && mc_quark_ps_E[j]>0) fsr_21+=mc_quark_ps_E[j];
      if( (mc_quark_ps_pdg[j]==22 || mc_quark_ps_pdg[j]==21) && mc_quark_ps_E[j]>0) fsr+=mc_quark_ps_E[j];
    }
							    
    
    //-------------------
    //Kv parton
    float costheta_b0;
    std::vector<float> p_b0;
    p_b0.push_back(mc_quark_px[0]);
    p_b0.push_back(mc_quark_py[0]);
    p_b0.push_back(mc_quark_pz[0]);
    costheta_b0=GetCostheta(p_b0);
    float costheta_b1;
    std::vector<float> p_b1;
    p_b1.push_back(mc_quark_px[1]);
    p_b1.push_back(mc_quark_py[1]);
    p_b1.push_back(mc_quark_pz[1]);
    costheta_b1=GetCostheta(p_b1);
    
    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;


    	
    bool selection=PreSelection(selection_type,Kvcut);
    if(selection==false) continue;
    
    // RECO STUFF
    float costheta_j0;
    std::vector<float> p_j0;
    p_j0.push_back(jet_px[0]);
    p_j0.push_back(jet_py[0]);
    p_j0.push_back(jet_pz[0]);
    costheta_j0=GetCostheta(p_j0);

    float costheta_j1;
    std::vector<float> p_j1;
    p_j1.push_back(jet_px[1]);
    p_j1.push_back(jet_py[1]);
    p_j1.push_back(jet_pz[1]);
    costheta_j1=GetCostheta(p_j1);

    double reco_b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
    double reco_b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2)); 

    double reco_mass_max=reco_b1mass;
    double reco_mass_min=reco_b2mass;

    if(reco_b2mass>reco_b1mass) {
      reco_mass_max=reco_b2mass;
      reco_mass_min=reco_b1mass;
    }
    
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
	if( (jet_pfo_type[ijet][ipfo]==2112 && jet_pfo_E[ijet][ipfo]> neutralPFO_max[ijet])) { 
	     //|| jet_pfo_charge[ijet][ipfo]==0) && jet_pfo_E[ijet][ipfo]> neutralPFO_max[ijet]) { 
	     //|| jet_pfo_type[ijet][ipfo]==2112) && jet_pfo_E[ijet][ipfo]> neutralPFO_max[ijet]) {
	    //	      || jet_pfo_charge[ijet][ipfo]==0) && jet_pfo_E[ijet][ipfo]> neutralPFO_max[ijet]) {
	  neutralPFO_max[ijet]=jet_pfo_E[ijet][ipfo]; 
	}
	if( jet_pfo_type[ijet][ipfo]==2112 ){
	  //|| jet_pfo_type[ijet][ipfo]==2112){
	    //||  jet_pfo_charge[ijet][ipfo]==0 ) { 
	    //|| jet_pfo_type[ijet][ipfo]==2112){//||  jet_pfo_charge[ijet][ipfo]==0 ) {

	  std::vector<float> temp;
	  temp.push_back(jet_pfo_px[ijet][ipfo]);
	  temp.push_back(jet_pfo_py[ijet][ipfo]);
	  temp.push_back(jet_pfo_pz[ijet][ipfo]);
	  
	  if(gamma_e>Kvcut)  h_PFOphoton_all2_costheta[0]->Fill(GetCostheta(temp));
	  if(gamma_e<Kvcut)  h_PFOphoton_all2_costheta[1]->Fill(GetCostheta(temp));
	  if(gamma_e<Kvcut && fabs(mc_quark_pdg[0])==5 )  h_PFOphoton_all2_costheta[2]->Fill(GetCostheta(temp));
	  if(gamma_e<Kvcut && fabs(mc_quark_pdg[0])==4 )  h_PFOphoton_all2_costheta[3]->Fill(GetCostheta(temp));
	  if(gamma_e<Kvcut && fabs(mc_quark_pdg[0])<4 )  h_PFOphoton_all2_costheta[4]->Fill(GetCostheta(temp));

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


    
    //radiative return events !
    if(gamma_e>Kvcut) {

      h_PFOphoton_all_costheta[0]->Fill(costheta_neutral0);
      h_PFOphoton_all_costheta[0]->Fill(costheta_neutral1);

      h_PFOphoton_all_costheta_cosjet[0]->Fill(costheta_neutral0,costheta_j0);
      h_PFOphoton_all_costheta_cosjet[0]->Fill(costheta_neutral0,costheta_j0);

      h_PFOphoton_all_E_costheta[0]->Fill(costheta_neutral0,neutralPFO_total[0]);
      h_PFOphoton_all_E_costheta[0]->Fill(costheta_neutral1,neutralPFO_total[1]);
           
      h_costheta_parton[0]->Fill(costheta_b0,costheta_b1);
      h_ISR_E[0]->Fill(gamma0_e+gamma1_e);
      h_ISR_Ediff[0]->Fill(gamma0_e-gamma1_e);
      h_ISR_E2d[0]->Fill(gamma0_e,gamma1_e);

      
      h_FSR_E[0]->Fill( fsr);
      //      h_FSR_Ediff[0]->Fill(0);
      // h_FSR_E2d[0]->Fill(0,0);
      
      h_FSR22_E[0]->Fill(fsr_22); 
      //h_FSR22_Ediff[0]->Fill(0,0);
      //h_FSR22_E2d[0]->Fill(0,0);
  
      h_FSR21_E[0]->Fill(fsr_21);
      //h_FSR21_Ediff[0]->Fill(0,0);
      //h_FSR21_E2d[0]->Fill(0,0);

      
      h_costheta_reco[0]->Fill(costheta_j0,costheta_j1);

      
      h_PFOphoton_max_2d[0]->Fill(neutralPFO_max[0],neutralPFO_max[1]);
      h_PFOphoton_all_2d[0]->Fill(neutralPFO_total[0],neutralPFO_total[1]);
      h_PFOphoton_ratio_2d[0]->Fill(neutralPFO_ratio[0],neutralPFO_ratio[1]);
      h_PFOphoton_ratio_E_2d[0]->Fill(neutralPFO_ratio[0],jet_E[0]);
      h_PFOphoton_ratio_E_2d[0]->Fill(neutralPFO_ratio[1],jet_E[1]);

      h_PFOphoton_npfo_ratio_2d[0]->Fill(neutralPFO_ratio[0],npfo[0]);
      h_PFOphoton_npfo_ratio_2d[0]->Fill(neutralPFO_ratio[1],npfo[1]);

      h_y23[0]->Fill(y23);
      h_y23_parton[0]->Fill(mc_quark_ps_y23);
      h_thrust[0]->Fill(principle_thrust_value);
      h_mjmj_2d[0]->Fill(reco_mass_max,reco_mass_min);
      h_mjmj[0]->Fill(reco_mass_max+reco_mass_min);

    }

    //Signal Events, all flavours
    if(gamma_e<Kvcut) {

      h_PFOphoton_all_costheta[1]->Fill(costheta_neutral0);
      h_PFOphoton_all_costheta[1]->Fill(costheta_neutral1);

      h_PFOphoton_all_costheta_cosjet[1]->Fill(costheta_neutral0,costheta_j0);
      h_PFOphoton_all_costheta_cosjet[1]->Fill(costheta_neutral0,costheta_j0);

      h_PFOphoton_all_E_costheta[1]->Fill(costheta_neutral0,neutralPFO_total[0]);
      h_PFOphoton_all_E_costheta[1]->Fill(costheta_neutral1,neutralPFO_total[1]);
      
      h_costheta_parton[1]->Fill(costheta_b0,costheta_b1);
      h_ISR_E[1]->Fill(gamma0_e+gamma1_e);;
      h_ISR_Ediff[1]->Fill(gamma0_e-gamma1_e);
      h_ISR_E2d[1]->Fill(gamma0_e,gamma1_e);
  
      h_FSR_E[1]->Fill( fsr);
      //h_FSR_Ediff[1]->Fill(0);
      //h_FSR_E2d[1]->Fill(0,0);
      
      h_FSR22_E[1]->Fill(fsr_22); 
      //h_FSR22_Ediff[1]->Fill(0,0);
      //h_FSR22_E2d[1]->Fill(0,0);
  
      h_FSR21_E[1]->Fill(fsr_21);
      //h_FSR21_Ediff[1]->Fill(0,0);
      //h_FSR21_E2d[1]->Fill(0,0);

      h_costheta_reco[1]->Fill(costheta_j0,costheta_j1);

      h_PFOphoton_max_2d[1]->Fill(neutralPFO_max[0],neutralPFO_max[1]);
      h_PFOphoton_all_2d[1]->Fill(neutralPFO_total[0],neutralPFO_total[1]);
      h_PFOphoton_ratio_2d[1]->Fill(neutralPFO_ratio[0],neutralPFO_ratio[1]);
      h_PFOphoton_ratio_E_2d[1]->Fill(neutralPFO_ratio[0],jet_E[0]);
      h_PFOphoton_ratio_E_2d[1]->Fill(neutralPFO_ratio[1],jet_E[1]);

      h_PFOphoton_npfo_ratio_2d[1]->Fill(neutralPFO_ratio[0],npfo[0]);
      h_PFOphoton_npfo_ratio_2d[1]->Fill(neutralPFO_ratio[1],npfo[1]);
      
      h_y23[1]->Fill(y23);
      h_y23_parton[1]->Fill(mc_quark_ps_y23);
      h_thrust[1]->Fill(principle_thrust_value);
      h_mjmj_2d[1]->Fill(reco_mass_max,reco_mass_min);
      h_mjmj[1]->Fill(reco_mass_max+reco_mass_min);
         
    }

     //Signal Events, b-quark
    if(gamma_e<Kvcut && fabs(mc_quark_pdg[0])==5 ) {

      h_PFOphoton_all_costheta[2]->Fill(costheta_neutral0);
      h_PFOphoton_all_costheta[2]->Fill(costheta_neutral1);

      h_PFOphoton_all_costheta_cosjet[2]->Fill(costheta_neutral0,costheta_j0);
      h_PFOphoton_all_costheta_cosjet[2]->Fill(costheta_neutral0,costheta_j0);

      h_PFOphoton_all_E_costheta[2]->Fill(costheta_neutral0,neutralPFO_total[0]);
      h_PFOphoton_all_E_costheta[2]->Fill(costheta_neutral1,neutralPFO_total[1]);
      
      h_costheta_parton[2]->Fill(costheta_b0,costheta_b1);
      h_ISR_E[2]->Fill(gamma0_e+gamma1_e);;
      h_ISR_Ediff[2]->Fill(gamma0_e-gamma1_e);
      h_ISR_E2d[2]->Fill(gamma0_e,gamma1_e);
  
      h_FSR_E[2]->Fill( fsr);
      //h_FSR_Ediff[2]->Fill(0);
      //h_FSR_E2d[2]->Fill(0,0);
      
      h_FSR22_E[2]->Fill(fsr_22); 
      // h_FSR22_Ediff[2]->Fill(0,0);
      //h_FSR22_E2d[2]->Fill(0,0);
  
      h_FSR21_E[2]->Fill(fsr_21);
      //h_FSR21_Ediff[2]->Fill(0,0);
      //h_FSR21_E2d[2]->Fill(0,0);

      h_costheta_reco[2]->Fill(costheta_j0,costheta_j1);

      h_PFOphoton_max_2d[2]->Fill(neutralPFO_max[0],neutralPFO_max[1]);
      h_PFOphoton_all_2d[2]->Fill(neutralPFO_total[0],neutralPFO_total[1]);
      h_PFOphoton_ratio_2d[2]->Fill(neutralPFO_ratio[0],neutralPFO_ratio[1]);
      h_PFOphoton_ratio_E_2d[2]->Fill(neutralPFO_ratio[0],jet_E[0]);
      h_PFOphoton_ratio_E_2d[2]->Fill(neutralPFO_ratio[1],jet_E[1]);

      h_PFOphoton_npfo_ratio_2d[2]->Fill(neutralPFO_ratio[0],npfo[0]);
      h_PFOphoton_npfo_ratio_2d[2]->Fill(neutralPFO_ratio[1],npfo[1]);
      
      h_y23[2]->Fill(y23);
      h_y23_parton[2]->Fill(mc_quark_ps_y23);
      h_thrust[2]->Fill(principle_thrust_value);
      h_mjmj_2d[2]->Fill(reco_mass_max,reco_mass_min);
      h_mjmj[2]->Fill(reco_mass_max+reco_mass_min);
   
    }

     //Signal Events, c-quark
    if(gamma_e<Kvcut && fabs(mc_quark_pdg[0])==4 ) {

      h_PFOphoton_all_costheta[3]->Fill(costheta_neutral0);
      h_PFOphoton_all_costheta[3]->Fill(costheta_neutral1);

      h_PFOphoton_all_costheta_cosjet[3]->Fill(costheta_neutral0,costheta_j0);
      h_PFOphoton_all_costheta_cosjet[3]->Fill(costheta_neutral0,costheta_j0);

      h_PFOphoton_all_E_costheta[3]->Fill(costheta_neutral0,neutralPFO_total[0]);
      h_PFOphoton_all_E_costheta[3]->Fill(costheta_neutral1,neutralPFO_total[1]);

      h_costheta_parton[3]->Fill(costheta_b0,costheta_b1);
      h_ISR_E[3]->Fill(gamma0_e+gamma1_e);;
      h_ISR_Ediff[3]->Fill(gamma0_e-gamma1_e);
      h_ISR_E2d[3]->Fill(gamma0_e,gamma1_e);
  
      h_FSR_E[3]->Fill( fsr);
      //h_FSR_Ediff[3]->Fill(0);
      //h_FSR_E2d[3]->Fill(0,0);
      
      h_FSR22_E[3]->Fill(fsr_22); 
      //h_FSR22_Ediff[3]->Fill(0,0);
      //h_FSR22_E2d[3]->Fill(0,0);
  
      h_FSR21_E[3]->Fill(fsr_21);
      //h_FSR21_Ediff[3]->Fill(0,0);
      //h_FSR21_E2d[3]->Fill(0,0);

      h_costheta_reco[3]->Fill(costheta_j0,costheta_j1);

      h_PFOphoton_max_2d[3]->Fill(neutralPFO_max[0],neutralPFO_max[1]);
      h_PFOphoton_all_2d[3]->Fill(neutralPFO_total[0],neutralPFO_total[1]);
      h_PFOphoton_ratio_2d[3]->Fill(neutralPFO_ratio[0],neutralPFO_ratio[1]);
      h_PFOphoton_ratio_E_2d[3]->Fill(neutralPFO_ratio[0],jet_E[0]);
      h_PFOphoton_ratio_E_2d[3]->Fill(neutralPFO_ratio[1],jet_E[1]);

      h_PFOphoton_npfo_ratio_2d[3]->Fill(neutralPFO_ratio[0],npfo[0]);
      h_PFOphoton_npfo_ratio_2d[3]->Fill(neutralPFO_ratio[1],npfo[1]);
      
      h_y23[3]->Fill(y23);
      h_y23_parton[3]->Fill(mc_quark_ps_y23);
      h_thrust[3]->Fill(principle_thrust_value);
      h_mjmj_2d[3]->Fill(reco_mass_max,reco_mass_min);
      h_mjmj[3]->Fill(reco_mass_max+reco_mass_min);

    }

     //Signal Events,  uds-quark
    if(gamma_e<Kvcut && fabs(mc_quark_pdg[0])<4 ) {

      h_PFOphoton_all_costheta[4]->Fill(costheta_neutral0);
      h_PFOphoton_all_costheta[4]->Fill(costheta_neutral1);

      h_PFOphoton_all_costheta_cosjet[4]->Fill(costheta_neutral0,costheta_j0);
      h_PFOphoton_all_costheta_cosjet[4]->Fill(costheta_neutral0,costheta_j0);

      h_PFOphoton_all_E_costheta[4]->Fill(costheta_neutral0,neutralPFO_total[0]);
      h_PFOphoton_all_E_costheta[4]->Fill(costheta_neutral1,neutralPFO_total[1]);

      h_costheta_parton[4]->Fill(costheta_b0,costheta_b1);
      h_ISR_E[4]->Fill(gamma0_e+gamma1_e);;
      h_ISR_Ediff[4]->Fill(gamma0_e-gamma1_e);
      h_ISR_E2d[4]->Fill(gamma0_e,gamma1_e);
  
      h_FSR_E[4]->Fill( fsr);
      //h_FSR_Ediff[4]->Fill(0);
      //h_FSR_E2d[4]->Fill(0,0);
      
      h_FSR22_E[4]->Fill(fsr_22); 
      //h_FSR22_Ediff[4]->Fill(0,0);
      //h_FSR22_E2d[4]->Fill(0,0);
  
      h_FSR21_E[4]->Fill(fsr_21);
      //h_FSR21_Ediff[4]->Fill(0,0);
      //h_FSR21_E2d[4]->Fill(0,0);

      h_costheta_reco[4]->Fill(costheta_j0,costheta_j1);

      h_PFOphoton_max_2d[4]->Fill(neutralPFO_max[0],neutralPFO_max[1]);
      h_PFOphoton_all_2d[4]->Fill(neutralPFO_total[0],neutralPFO_total[1]);
      h_PFOphoton_ratio_2d[4]->Fill(neutralPFO_ratio[0],neutralPFO_ratio[1]);
      h_PFOphoton_ratio_E_2d[4]->Fill(neutralPFO_ratio[0],jet_E[0]);
      h_PFOphoton_ratio_E_2d[4]->Fill(neutralPFO_ratio[1],jet_E[1]);

      h_PFOphoton_npfo_ratio_2d[4]->Fill(neutralPFO_ratio[0],npfo[0]);
      h_PFOphoton_npfo_ratio_2d[4]->Fill(neutralPFO_ratio[1],npfo[1]);
      
      h_y23[4]->Fill(y23);
      h_y23_parton[4]->Fill(mc_quark_ps_y23);
      h_thrust[4]->Fill(principle_thrust_value);
      h_mjmj_2d[4]->Fill(reco_mass_max,reco_mass_min);
      h_mjmj[4]->Fill(reco_mass_max+reco_mass_min);

       
    }
    
  }

  h_gamma_K_parton ->Write();
  h_gamma_costhetaparton->Write();
  h_gamma_K_coshteta_parton->Write();

  h_gamma_K_parton_b ->Write();
  h_gamma_costhetaparton_b->Write();
  h_gamma_K_coshteta_parton_b->Write();
  
  for(int i=0; i<5; i++) {
    
    h_costheta_parton[i]->Write();
    h_ISR_E[i]->Write();
    h_ISR_Ediff[i]->Write();
    h_ISR_E2d[i]->Write();

    h_y23_parton[i]->Write();
    h_FSR_E[i]->Write(); 
    h_FSR_Ediff[i]->Write();
    h_FSR_E2d[i]->Write(); 
    
    h_FSR22_E[i]->Write(); 
    h_FSR22_Ediff[i]->Write();
    h_FSR22_E2d[i]->Write();
    
    h_FSR21_E[i]->Write(); 
    h_FSR21_Ediff[i]->Write();
    h_FSR21_E2d[i]->Write();
    
    
    //reco level
    h_PFOphoton_all_costheta[i]->Write();
    h_PFOphoton_all2_costheta[i]->Write();
    h_PFOphoton_all_costheta_cosjet[i]->Write();
    h_PFOphoton_all_E_costheta[i]->Write();

    h_costheta_reco[i]->Write();
    
    h_PFOphoton_max_2d[i]->Write();
    h_PFOphoton_all_2d[i]->Write();
    h_PFOphoton_ratio_2d[i]->Write();
    h_PFOphoton_ratio_E_2d[i]->Write();

    h_PFOphoton_npfo_ratio_2d[i]->Write();

    h_y23[i]->Write();
    h_thrust[i]->Write();
    h_mjmj[i]->Write();
    h_mjmj_2d[i]->Write();
  }
   
}


void observable::Selection(int n_entries=-1, int selection_type=0, TString polarization="eL", float Kvcut=2500)
{
  
  TFile *MyFile = new TFile(TString::Format("selection_%s_250GeV_%s.root",process.Data(),polarization.Data()),"RECREATE");
  MyFile->cd();
  
  //  gROOT->Reset();
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(0.3);
       
  bbbar_gen=0;
  bbbar_gen_radreturn=0;
  qqbar_gen=0;
  qqbar_gen_radreturn=0;
  ccbar_gen=0;
  ccbar_gen_radreturn=0;
  
  
  

  TH1F * h_cross_costheta = new TH1F("h_cross_costheta","h_cross_costheta",20,0,1);
  TH1F * h_cross_costheta_bb = new TH1F("h_cross_costheta_bb","h_cross_costheta_bb",20,0,1);
  TH1F * h_cross_costheta_qq = new TH1F("h_cross_costheta_qq","h_cross_costheta_qq",20,0,1);
  TH1F * h_cross_costheta_cc = new TH1F("h_cross_costheta_cc","h_cross_costheta_cc",20,0,1);
  TH1F * h_cross_costheta_radreturn = new TH1F("h_cross_costheta_radreturn","h_cross_costheta_radreturn",20,0,1);
  TH1F * h_cross_costheta_radreturn_bb = new TH1F("h_cross_costheta_radreturn_bb","h_cross_costheta_radreturn_bb",20,0,1);
  TH1F * h_cross_costheta_radreturn_qq = new TH1F("h_cross_costheta_radreturn_qq","h_cross_costheta_radreturn_qq",20,0,1);
  TH1F * h_cross_costheta_radreturn_cc = new TH1F("h_cross_costheta_radreturn_cc","h_cross_costheta_radreturn_cc",20,0,1);
  
  //costheta
  TH1F * h_costheta_bb = new TH1F("h_costheta_bb","h_costheta_bb",20,0,1);
  TH1F * h_costheta_qq = new TH1F("h_costheta_qq","h_costheta_qq",20,0,1);
  TH1F * h_costheta_cc = new TH1F("h_costheta_cc","h_costheta_cc",20,0,1);
  TH1F * h_costheta_radreturn = new TH1F("h_costheta_radreturn","h_costheta_radreturn",20,0,1);
  TH1F * h_costheta_radreturn_bb = new TH1F("h_costheta_radreturn_bb","h_costheta_radreturn_bb",20,0,1);
  TH1F * h_costheta_radreturn_qq = new TH1F("h_costheta_radreturn_qq","h_costheta_radreturn_qq",20,0,1);
  TH1F * h_costheta_radreturn_cc = new TH1F("h_costheta_radreturn_cc","h_costheta_radreturn_cc",20,0,1);

  TH1F * h_f0_bb = new TH1F("h_f0_bb","h_f0_bb",20,0,1);
  TH1F * h_f0_radreturn = new TH1F("h_f0_radreturn","h_f0_radreturn",20,0,1);
  TH1F * h_f0_qq = new TH1F("h_f0_qq","h_f0_qq",20,0,1);
  TH1F * h_f0_cc = new TH1F("h_f0_cc","h_f0_cc",20,0,1);

  TH1F * h_f1_bb = new TH1F("h_f1_bb","h_f1_bb",20,0,1);
  TH1F * h_f1_radreturn = new TH1F("h_f1_radreturn","h_f1_radreturn",20,0,1);
  TH1F * h_f1_qq = new TH1F("h_f1_qq","h_f1_qq",20,0,1);
  TH1F * h_f1_cc = new TH1F("h_f1_cc","h_f1_cc",20,0,1);

  TH1F * h_f2_bb = new TH1F("h_f2_bb","h_f2_bb",20,0,1);
  TH1F * h_f2_radreturn = new TH1F("h_f2_radreturn","h_f2_radreturn",20,0,1);
  TH1F * h_f2_qq = new TH1F("h_f2_qq","h_f2_qq",20,0,1);
  TH1F * h_f2_cc = new TH1F("h_f2_cc","h_f2_cc",20,0,1);
  
  TH1F * h_sintheta_bb = new TH1F("h_sintheta_bb","h_sintheta_bb",20,0,1);
  TH1F * h_sintheta_radreturn = new TH1F("h_sintheta_radreturn","h_sintheta_radreturn",20,0,1);
  TH1F * h_sintheta_qq = new TH1F("h_sintheta_qq","h_sintheta_qq",20,0,1);
  TH1F * h_sintheta_cc = new TH1F("h_sintheta_cc","h_sintheta_cc",20,0,1);
  
  //mass & momentum & angle
  TH1F * h_mjj_bb = new TH1F("h_mjj_bb","h_mjj_bb",100,0,500);
  TH1F * h_mjj_radreturn = new TH1F("h_mjj_radreturn","h_mjj_radreturn",100,0,500);
  TH1F * h_mjj_qq = new TH1F("h_mjj_qq","h_mjj_qq",100,0,500);
  TH1F * h_mjj_cc = new TH1F("h_mjj_cc","h_mjj_cc",100,0,500);

  TH1F * h_egamma_bb = new TH1F("h_egamma_bb","h_egamma_bb",100,0,500);
  TH1F * h_egamma_radreturn = new TH1F("h_egamma_radreturn","h_egamma_radreturn",100,0,500);
  TH1F * h_egamma_qq = new TH1F("h_egamma_qq","h_egamma_qq",100,0,500);
  TH1F * h_egamma_cc = new TH1F("h_egamma_cc","h_egamma_cc",100,0,500);
  
  TH1F * h_costhetagamma_bb = new TH1F("h_costhetagamma_bb","h_costhetagamma_bb",100,-1,1);
  TH1F * h_costhetagamma_radreturn = new TH1F("h_costhetagamma_radreturn","h_costhetagamma_radreturn",100,-1,1);
  TH1F * h_costhetagamma_qq = new TH1F("h_costhetagamma_qq","h_costhetagamma_qq",100,-1,1);
  TH1F * h_costhetagamma_cc = new TH1F("h_costhetagamma_cc","h_costhetagamma_cc",100,-1,1);

  TH2F * h_e_costheta_gamma_bb = new TH2F("h_e_costheta_gamma_bb","h_e_costheta_gamma_bb",400,-1,1,500,0,500);
  TH2F * h_e_costheta_gamma_radreturn = new TH2F("h_e_costheta_gamma_radreturn","h_e_costheta_gamma_radreturn",400,-1,1,500,0,500);
  TH2F * h_e_costheta_gamma_qq = new TH2F("h_e_costheta_gamma_qq","h_e_costheta_gamma_qq",400,-1,1,500,0,500);
  TH2F * h_e_costheta_gamma_cc = new TH2F("h_e_costheta_gamma_cc","h_e_costheta_gamma_cc",400,-1,1,500,0,500);
  
  TH2F * h_cos_costheta_gamma_bb = new TH2F("h_cos_costheta_gamma_bb","h_cos_costheta_gamma_bb",200,-1,1,200,-1,1);
  TH2F * h_cos_costheta_gamma_radreturn = new TH2F("h_cos_costheta_gamma_radreturn","h_cos_costheta_gamma_radreturn",200,-1,1,200,-1,1);
  TH2F * h_cos_costheta_gamma_qq = new TH2F("h_cos_costheta_gamma_qq","h_cos_costheta_gamma_qq",200,-1,1,200,-1,1);
  TH2F * h_cos_costheta_gamma_cc = new TH2F("h_cos_costheta_gamma_cc","h_cos_costheta_gamma_cc",200,-1,1,200,-1,1);

  TH1F * h_mj1_mj2_bb = new TH1F("h_mj1_mj2_bb","h_mj1_mj2_bb",100,0,500);
  TH1F * h_mj1_mj2_radreturn = new TH1F("h_mj1_mj2_radreturn","h_mj1_mj2_radreturn",100,0,500);
  TH1F * h_mj1_mj2_qq = new TH1F("h_mj1_mj2_qq","h_mj1_mj2_qq",100,0,500);
  TH1F * h_mj1_mj2_cc = new TH1F("h_mj1_mj2_cc","h_mj1_mj2_cc",100,0,500);

  TH1F * h_mjFat_bb = new TH1F("h_mjFat_bb","h_mjFat_bb",100,0,500);
  TH1F * h_mjFat_radreturn = new TH1F("h_mjFat_radreturn","h_mjFat_radreturn",100,0,500);
  TH1F * h_mjFat_qq = new TH1F("h_mjFat_qq","h_mjFat_qq",100,0,500);
  TH1F * h_mjFat_cc = new TH1F("h_mjFat_cc","h_mjFat_cc",100,0,500);

  TH1F * h_mjThin_bb = new TH1F("h_mjThin_bb","h_mjThin_bb",100,0,500);
  TH1F * h_mjThin_radreturn = new TH1F("h_mjThin_radreturn","h_mjThin_radreturn",100,0,500);
  TH1F * h_mjThin_qq = new TH1F("h_mjThin_qq","h_mjThin_qq",100,0,500);
  TH1F * h_mjThin_cc = new TH1F("h_mjThin_cc","h_mjThin_cc",100,0,500);

  TH1F * h_angle_bb = new TH1F("h_angle_bb","h_angle_bb",1000,-7,7);
  TH1F * h_angle_radreturn = new TH1F("h_angle_radreturn","h_angle_radreturn",1000,-7,7);
  TH1F * h_angle_qq = new TH1F("h_angle_qq","h_angle_qq",1000,-7,7);
  TH1F * h_angle_cc = new TH1F("h_angle_cc","h_angle_cc",1000,-7,7);

  TH1F * h_pj1_pj2_bb = new TH1F("h_pj1_pj2_bb","h_pj1_pj2_bb",100,0,500);
  TH1F * h_pj1_pj2_radreturn = new TH1F("h_pj1_pj2_radreturn","h_pj1_pj2_radreturn",100,0,500);
  TH1F * h_pj1_pj2_qq = new TH1F("h_pj1_pj2_qq","h_pj1_pj2_qq",100,0,500);
  TH1F * h_pj1_pj2_cc = new TH1F("h_pj1_pj2_cc","h_pj1_pj2_cc",100,0,500);

  //jet algorithm variables
  TH1F * h_d23_bb = new TH1F("h_d23_bb","h_d23_bb",100,0,500);
  TH1F * h_d23_radreturn = new TH1F("h_d23_radreturn","h_d23_radreturn",100,0,500);
  TH1F * h_d23_qq = new TH1F("h_d23_qq","h_d23_qq",100,0,500);
  TH1F * h_d23_cc = new TH1F("h_d23_cc","h_d23_cc",100,0,500);

  TH1F * h_d12_bb = new TH1F("h_d12_bb","h_d12_bb",100,0,100000);
  TH1F * h_d12_radreturn = new TH1F("h_d12_radreturn","h_d12_radreturn",100,0,100000);
  TH1F * h_d12_qq = new TH1F("h_d12_qq","h_d12_qq",100,0,100000);
  TH1F * h_d12_cc = new TH1F("h_d12_cc","h_d12_cc",100,0,100000);

  TH1F * h_y23_bb = new TH1F("h_y23_bb","h_y23_bb",400,0,0.25);
  TH1F * h_y23_radreturn = new TH1F("h_y23_radreturn","h_y23_radreturn",400,0,0.25);
  TH1F * h_y23_qq = new TH1F("h_y23_qq","h_y23_qq",400,0,0.25);
  TH1F * h_y23_cc = new TH1F("h_y23_cc","h_y23_cc",400,0,0.25);

  TH1F * h_y12_bb = new TH1F("h_y12_bb","h_y12_bb",100,0,1);
  TH1F * h_y12_radreturn = new TH1F("h_y12_radreturn","h_y12_radreturn",100,0,1);
  TH1F * h_y12_qq = new TH1F("h_y12_qq","h_y12_qq",100,0,1);
  TH1F * h_y12_cc = new TH1F("h_y12_cc","h_y12_cc",100,0,1);

  //EVENT SHAPE variables
  TH1F * h_oblateness_bb = new TH1F("h_oblateness_bb","h_oblateness_bb",100,0,0.8);
  TH1F * h_oblateness_radreturn = new TH1F("h_oblateness_radreturn","h_oblateness_radreturn",100,0,0.8);
  TH1F * h_oblateness_qq = new TH1F("h_oblateness_qq","h_oblateness_qq",100,0,0.8);
  TH1F * h_oblateness_cc = new TH1F("h_oblateness_cc","h_oblateness_cc",100,0,0.8);

  TH1F * h_aplanarity_bb = new TH1F("h_aplanarity_bb","h_aplanarity_bb",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_radreturn = new TH1F("h_aplanarity_radreturn","h_aplanarity_radreturn",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_qq = new TH1F("h_aplanarity_qq","h_aplanarity_qq",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_cc = new TH1F("h_aplanarity_cc","h_aplanarity_cc",100,-0.4e-6,0.4e-6);

  TH1F * h_sphericity_bb = new TH1F("h_sphericity_bb","h_sphericity_bb",2000,0,2);
  TH1F * h_sphericity_radreturn = new TH1F("h_sphericity_radreturn","h_sphericity_radreturn",2000,0,2);
  TH1F * h_sphericity_qq = new TH1F("h_sphericity_qq","h_sphericity_qq",2000,0,2);
  TH1F * h_sphericity_cc = new TH1F("h_sphericity_cc","h_sphericity_cc",2000,0,2);

  TH1F * h_acol_bb = new TH1F("h_acol_bb","h_acol_bb",1000,-4,4);
  TH1F * h_acol_radreturn = new TH1F("h_acol_radreturn","h_acol_radreturn",1000,-4,4);
  TH1F * h_acol_qq = new TH1F("h_acol_qq","h_acol_qq",1000,-4,4);
  TH1F * h_acol_cc = new TH1F("h_acol_cc","h_acol_cc",1000,-4,4);

  TH1F * h_sinacol_bb = new TH1F("h_sinacol_bb","h_sinacol_bb",200,0,2);
  TH1F * h_sinacol_radreturn = new TH1F("h_sinacol_radreturn","h_sinacol_radreturn",200,0,2);
  TH1F * h_sinacol_qq = new TH1F("h_sinacol_qq","h_sinacol_qq",200,0,2);
  TH1F * h_sinacol_cc = new TH1F("h_sinacol_cc","h_sinacol_cc",200,0,2);
  
  TH1F * h_K = new TH1F("h_K","h_K",2000,0,200);
  TH1F * h_K_bb = new TH1F("h_K_bb","h_K_bb",2000,0,200);
  TH1F * h_K_radreturn = new TH1F("h_K_radreturn","h_K_radreturn",2000,0,200);
  TH1F * h_K_qq = new TH1F("h_K_qq","h_K_qq",2000,0,200);
  TH1F * h_K_cc = new TH1F("h_K_cc","h_K_cc",2000,0,200);

  TH1F * h_K_parton_bb = new TH1F("h_K_parton_bb","h_K_parton_bb",2000,0,200);
  TH1F * h_K_parton_radreturn = new TH1F("h_K_parton_radreturn","h_K_parton_radreturn",2000,0,200);
  TH1F * h_K_parton_qq = new TH1F("h_K_parton_qq","h_K_parton_qq",2000,0,200);
  TH1F * h_K_parton_cc = new TH1F("h_K_parton_cc","h_K_parton_cc",2000,0,200);

  TH2F * h_K_parton_K_bb = new TH2F("h_K_parton_K_bb","h_K_parton_K_bb",200,0,200,200,0,200);
  TH2F * h_K_parton_K_radreturn = new TH2F("h_K_parton_K_radreturn","h_K_parton_K_radreturn",200,0,200,200,0,200);
  TH2F * h_K_parton_K_qq = new TH2F("h_K_parton_K_qq","h_K_parton_K_qq",200,0,200,200,0,200);
  TH2F * h_K_parton_K_cc = new TH2F("h_K_parton_K_cc","h_K_parton_K_cc",200,0,200,200,0,200);

  TH1F * h_K_res = new TH1F("h_K_res","h_K_res",4000,-200,200);
  TH2F * h_sphericity_cos_bb = new TH2F("h_sphericity_cos_bb","h_sphericity_cos_bb",40,-1,1,2000,0,2);
  TH2F * h_sphericity_cos_radreturn = new TH2F("h_sphericity_cos_radreturn","h_sphericity_cos_radreturn",40,-1,1,2000,0,2);
  TH2F * h_sphericity_cos_qq = new TH2F("h_sphericity_cos_qq","h_sphericity_cos_qq",40,-1,1,2000,0,2);
  TH2F * h_sphericity_cos_cc = new TH2F("h_sphericity_cos_cc","h_sphericity_cos_cc",40,-1,1,2000,0,2);

  TH2F * h_acol_cos_bb = new TH2F("h_acol_cos_bb","h_acol_cos_bb",40,-1,1,2000,0,2);
  TH2F * h_acol_cos_radreturn = new TH2F("h_acol_cos_radreturn","h_acol_cos_radreturn",40,-1,1,2000,0,2);
  TH2F * h_acol_cos_qq = new TH2F("h_acol_cos_qq","h_acol_cos_qq",40,-1,1,2000,0,2);
  TH2F * h_acol_cos_cc = new TH2F("h_acol_cos_cc","h_acol_cos_cc",40,-1,1,2000,0,2);

  TH2F * h_sphericity_sin_bb = new TH2F("h_sphericity_sin_bb","h_sphericity_sin_bb",40,-1,1,2000,0,2);
  TH2F * h_sphericity_sin_radreturn = new TH2F("h_sphericity_sin_radreturn","h_sphericity_sin_radreturn",40,-1,1,2000,0,2);
  TH2F * h_sphericity_sin_qq = new TH2F("h_sphericity_sin_qq","h_sphericity_sin_qq",40,-1,1,2000,0,2);
  TH2F * h_sphericity_sin_cc = new TH2F("h_sphericity_sin_cc","h_sphericity_sin_cc",40,-1,1,2000,0,2);

  TH2F * h_acol_sin_bb = new TH2F("h_acol_sin_bb","h_acol_sin_bb",40,-1,1,2000,0,2);
  TH2F * h_acol_sin_radreturn = new TH2F("h_acol_sin_radreturn","h_acol_sin_radreturn",40,-1,1,2000,0,2);
  TH2F * h_acol_sin_qq = new TH2F("h_acol_sin_qq","h_acol_sin_qq",40,-1,1,2000,0,2);
  TH2F * h_acol_sin_cc = new TH2F("h_acol_sin_cc","h_acol_sin_cc",40,-1,1,2000,0,2);

  TH2F * h_acol_sphericity_bb = new TH2F("h_acol_sphericity_bb","h_acol_sphericity_bb",2000,0,2,2000,0,2);
  TH2F * h_acol_sphericity_radreturn = new TH2F("h_acol_sphericity_radreturn","h_acol_sphericity_radreturn",2000,0,2,2000,0,2);
  TH2F * h_acol_sphericity_qq = new TH2F("h_acol_sphericity_qq","h_acol_sphericity_qq",2000,0,2,2000,0,2);
  TH2F * h_acol_sphericity_cc = new TH2F("h_acol_sphericity_cc","h_acol_sphericity_cc",2000,0,2,2000,0,2);
      
    
  TH1F * h_thrust_bb = new TH1F("h_thrust_bb","h_thrust_bb",1000,0,1);
  TH1F * h_thrust_radreturn = new TH1F("h_thrust_radreturn","h_thrust_radreturn",1000,0,1);
  TH1F * h_thrust_qq = new TH1F("h_thrust_qq","h_thrust_qq",1000,0,1);
  TH1F * h_thrust_cc = new TH1F("h_thrust_cc","h_thrust_cc",1000,0,1);


  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  int bb_counter=0, radreturn_counter=0, qq_counter=0, cc_counter=0;
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

   
    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e+gamma1_e;//sqrt(pow(mc_ISR_px[0]+mc_ISR_px[1],2)+pow(mc_ISR_py[0]+mc_ISR_py[1],2)+pow(mc_ISR_pz[0]+mc_ISR_pz[1],2));//gamma0_e+gamma1_e;
    
    //-------------------
    //Kv parton
    double b0_p= sqrt(pow(mc_quark_px[0],2)+pow(mc_quark_py[0],2)+pow(mc_quark_pz[0],2));
    double b1_p= sqrt(pow(mc_quark_px[1],2)+pow(mc_quark_py[1],2)+pow(mc_quark_pz[1],2));
    float costheta_b0;
    std::vector<float> p_b0;
    p_b0.push_back(mc_quark_px[0]);
    p_b0.push_back(mc_quark_py[0]);
    p_b0.push_back(mc_quark_pz[0]);
    costheta_b0=fabs(GetCostheta(p_b0));
    float costheta_b1;
    std::vector<float> p_b1;
    p_b1.push_back(mc_quark_px[1]);
    p_b1.push_back(mc_quark_py[1]);
    p_b1.push_back(mc_quark_pz[1]);
    costheta_b1=fabs(GetCostheta(p_b1));
    TVector3 v0_p(mc_quark_px[0],mc_quark_py[0],mc_quark_pz[0]);
    TVector3 v1_p(mc_quark_px[1],mc_quark_py[1],mc_quark_pz[1]);
    float acol_p=GetSinacol(v0_p,v1_p);
    float Kv_p=250.*acol_p/(acol_p+sqrt(1-costheta_b0*costheta_b0)+sqrt(1-costheta_b1*costheta_b1));

    if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) {
      bbbar_gen++;
      bb_counter++;
    }
    if(gamma_e>Kvcut ) {
      radreturn_counter++;
      if(fabs(mc_quark_pdg[0])==5) bbbar_gen_radreturn++;
      if(fabs(mc_quark_pdg[0])==4) ccbar_gen_radreturn++;
      if(fabs(mc_quark_pdg[0])<4) qqbar_gen_radreturn++;
    }
    if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut){
      cc_counter++;
      ccbar_gen++;
    }
    if(fabs(mc_quark_pdg[0])<5 && gamma_e<Kvcut) {
      qq_counter++;
      qqbar_gen++;
    }


    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //reco stuff
    double reco_b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
    double reco_b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
    double reco_bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

    double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
    double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

    double jj_pT= sqrt(pow(jet_px[0]+jet_px[1],2)+pow(jet_py[0]+jet_py[1],2));

    float costheta_bbbar;
    std::vector<float> p_bbar;
    p_bbar.push_back(jet_px[0]-jet_px[1]);
    p_bbar.push_back(jet_py[0]-jet_py[1]);
    p_bbar.push_back(jet_pz[0]-jet_pz[1]);
    costheta_bbbar=fabs(GetCostheta(p_bbar));

    float costheta_j0;
    std::vector<float> p_j0;
    p_j0.push_back(jet_px[0]);
    p_j0.push_back(jet_py[0]);
    p_j0.push_back(jet_pz[0]);
    costheta_j0=GetCostheta(p_j0);

    float costheta_j1;
    std::vector<float> p_j1;
    p_j1.push_back(jet_px[1]);
    p_j1.push_back(jet_py[1]);
    p_j1.push_back(jet_pz[1]);
    costheta_j1=GetCostheta(p_j1);

    TVector3 v0(jet_px[0],jet_py[0],jet_pz[0]);
    TVector3 v1(jet_px[1],jet_py[1],jet_pz[1]);
    float acol=GetSinacol(v0,v1);
    float Kv=250.*acol/(acol+sqrt(1-costheta_j0*costheta_j0)+sqrt(1-costheta_j1*costheta_j1));

    float thrust=principle_thrust_value;//GetThrust(v0,v1);
 
    double  neutralPFO_max[2];
    double  neutralPFO_total[2];
    double  neutralPFO_ratio[2];

    double  neutraljet_E[2];
    double  neutraljet_costheta[2];

    double npfo[2];
    for(int ijet=0; ijet<2; ijet++) {
      neutralPFO_max[ijet]=0;
      neutralPFO_total[ijet]=0;
      neutralPFO_ratio[ijet]=0;
      npfo[ijet]=0;
      double jetenergy=0;

      for(int ipfo=0; ipfo<100; ipfo++) {//jet_pfo_n[ijet]; ipfo++) {
	if(jet_pfo_E[ijet][ipfo]<0.1) continue;
	
	npfo[ijet]++;
	jetenergy+=jet_pfo_E[ijet][ipfo];
	if( (jet_pfo_type[ijet][ipfo]==22 || jet_pfo_charge[ijet][ipfo]==0) && jet_pfo_E[ijet][ipfo]> neutralPFO_max[ijet]) {
	  neutralPFO_max[ijet]=jet_pfo_E[ijet][ipfo]; 
	}
	if( jet_pfo_type[ijet][ipfo]==22 ||  jet_pfo_charge[ijet][ipfo]==0 ) {
	  neutralPFO_total[ijet]+=jet_pfo_E[ijet][ipfo]; 
	  neutralPFO_ratio[ijet]+=jet_pfo_E[ijet][ipfo]; 
	}
      }
      neutralPFO_ratio[ijet]/=jetenergy;
    }

    for(int ijet=0; ijet<2; ijet++) {
      neutraljet_E[ijet]=-1;
      neutraljet_costheta[ijet]=-2; 
      if(neutralPFO_ratio[ijet]>0.85) {
	neutraljet_E[ijet]=jet_E[ijet];
	if(ijet==0) neutraljet_costheta[ijet]=costheta_j0;
	if(ijet==1) neutraljet_costheta[ijet]=costheta_j1;
      }
    }
    
     
    // parton level definitions
    if(gamma_e<Kvcut) h_cross_costheta->Fill(costheta_bbbar);
    if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) h_cross_costheta_bb->Fill(costheta_bbbar);
    if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut) h_cross_costheta_cc->Fill(costheta_bbbar);
    if(fabs(mc_quark_pdg[0])<4 && gamma_e<Kvcut) h_cross_costheta_qq->Fill(costheta_bbbar);
    if(fabs(mc_quark_pdg[0])==5 && gamma_e>Kvcut) h_cross_costheta_radreturn_bb->Fill(costheta_bbbar);
    if(fabs(mc_quark_pdg[0])==4 && gamma_e>Kvcut) h_cross_costheta_radreturn_cc->Fill(costheta_bbbar);
    if(fabs(mc_quark_pdg[0])<4 && gamma_e>Kvcut) h_cross_costheta_radreturn_qq->Fill(costheta_bbbar);
    if(gamma_e>Kvcut) h_cross_costheta_radreturn->Fill(costheta_bbbar);

    if(PreSelection(5,Kvcut)==true) {
      if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) {
	h_f0_bb->Fill(costheta_bbbar);
	h_f0_bb->Fill(costheta_bbbar);
      }
     if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut) {
	h_f0_cc->Fill(costheta_bbbar);
	h_f0_cc->Fill(costheta_bbbar);
      }
     if(fabs(mc_quark_pdg[0])<4 && gamma_e<Kvcut) {
	h_f0_qq->Fill(costheta_bbbar);
	h_f0_qq->Fill(costheta_bbbar);
      }
     if(gamma_e>Kvcut) {
	h_f0_radreturn->Fill(costheta_bbbar);
	h_f0_radreturn->Fill(costheta_bbbar);
     }
    }
    
    bool selection=PreSelection(selection_type,Kvcut);
    if(selection==false) continue;
	  
    if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) {

      h_K_res->Fill(gamma_e-Kv);
      
      h_costheta_bb->Fill(costheta_bbbar);

      if(selection_type == 11 && jet_btag[0]>btag1) h_f1_bb->Fill(costheta_bbbar);
      if(selection_type == 11 && jet_btag[1]>btag2) h_f1_bb->Fill(costheta_bbbar);
      if(selection_type == 12) {
	h_f1_bb->Fill(costheta_bbbar);
	h_f1_bb->Fill(costheta_bbbar);
	h_f2_bb->Fill(costheta_bbbar);
	h_f2_bb->Fill(costheta_bbbar);
      }
      if(selection_type == 13 && JetBtag(0)==true) h_f1_bb->Fill(costheta_bbbar);
      if(selection_type == 13 && JetBtag(1)==true) h_f1_bb->Fill(costheta_bbbar);
      if(selection_type == 14) {
	h_f1_bb->Fill(costheta_bbbar);
	h_f1_bb->Fill(costheta_bbbar);
	h_f2_bb->Fill(costheta_bbbar);
	h_f2_bb->Fill(costheta_bbbar);
      }
      if(selection_type == 15 && jet_ctag[0]>ctag1) h_f1_bb->Fill(costheta_bbbar);
      if(selection_type == 15 && jet_ctag[1]>ctag2) h_f1_bb->Fill(costheta_bbbar);
      if(selection_type == 16) {
	h_f1_bb->Fill(costheta_bbbar);
	h_f1_bb->Fill(costheta_bbbar);
	h_f2_bb->Fill(costheta_bbbar);
	h_f2_bb->Fill(costheta_bbbar);
      }
      if(selection_type == 17 && JetCtag(0)==true) h_f1_bb->Fill(costheta_bbbar);
      if(selection_type == 17 && JetCtag(1)==true) h_f1_bb->Fill(costheta_bbbar);
      if(selection_type == 18) {
	h_f1_bb->Fill(costheta_bbbar);
	h_f1_bb->Fill(costheta_bbbar);
	h_f2_bb->Fill(costheta_bbbar);
	h_f2_bb->Fill(costheta_bbbar);
      }
      
      h_sintheta_bb->Fill(sqrt(1-costheta_bbbar*costheta_bbbar));
      h_mjj_bb->Fill(reco_bbmass);

      h_egamma_bb->Fill(neutraljet_E[0]);
      h_egamma_bb->Fill(neutraljet_E[1]);

      h_costhetagamma_bb->Fill(neutraljet_costheta[0]);
      h_costhetagamma_bb->Fill(neutraljet_costheta[1]);

      h_e_costheta_gamma_bb->Fill(neutraljet_E[0],neutraljet_costheta[0]);
      h_e_costheta_gamma_bb->Fill(neutraljet_E[1],neutraljet_costheta[1]);

      h_cos_costheta_gamma_bb->Fill(costheta_j0,neutraljet_costheta[1]);
      h_cos_costheta_gamma_bb->Fill(costheta_j1,neutraljet_costheta[1]);

      h_mj1_mj2_bb->Fill(reco_b1mass+reco_b2mass);
      if(reco_b1mass>reco_b2mass) {
	h_mjFat_bb->Fill(reco_b1mass);
	h_mjThin_bb->Fill(reco_b2mass);
      } else {
	h_mjFat_bb->Fill(reco_b2mass);
	h_mjThin_bb->Fill(reco_b1mass);
      }
      h_pj1_pj2_bb->Fill(jet0_p+jet1_p);
      h_d23_bb->Fill(d23);
      h_d12_bb->Fill(d12);
      h_y23_bb->Fill(y23);
      h_y12_bb->Fill(y12);
      h_oblateness_bb->Fill(oblateness);
      h_aplanarity_bb->Fill(aplanarity);

      h_sphericity_bb->Fill(sphericity);
      h_sinacol_bb->Fill(acol);
      h_acol_bb->Fill(TMath::ASin(acol));
      h_K_bb->Fill(Kv);
      h_K_parton_bb->Fill(gamma_e);
      h_K_parton_K_bb->Fill(gamma_e,Kv);
      h_sphericity_cos_bb->Fill(costheta_bbbar,sphericity);
      h_acol_cos_bb->Fill(costheta_bbbar,acol);
      h_sphericity_sin_bb->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),sphericity);
      h_acol_sin_bb->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),acol);
      h_acol_sphericity_bb->Fill(sphericity,acol);
      h_thrust_bb->Fill(thrust);
      
      float angle=getAngle2Vec(jet_px[0],jet_py[0],jet_pz[0],jet_E[0],jet_px[1],jet_py[1],jet_pz[1],jet_E[1]);
      h_angle_bb->Fill(angle);
    }
    
    if( gamma_e>Kvcut ) {
      h_mjj_radreturn->Fill(reco_bbmass);

      h_egamma_radreturn->Fill(neutraljet_E[0]);
      h_egamma_radreturn->Fill(neutraljet_E[1]);

      h_costhetagamma_radreturn->Fill(neutraljet_costheta[0]);
      h_costhetagamma_radreturn->Fill(neutraljet_costheta[1]);

      h_e_costheta_gamma_radreturn->Fill(neutraljet_E[0],neutraljet_costheta[0]);
      h_e_costheta_gamma_radreturn->Fill(neutraljet_E[1],neutraljet_costheta[1]);

      h_cos_costheta_gamma_radreturn->Fill(costheta_j0,neutraljet_costheta[1]);
      h_cos_costheta_gamma_radreturn->Fill(costheta_j1,neutraljet_costheta[1]);
      h_mj1_mj2_radreturn->Fill(reco_b1mass+reco_b2mass);
      
      h_costheta_radreturn->Fill(costheta_bbbar);
      if( fabs(mc_quark_pdg[0])==5 ) h_costheta_radreturn_bb->Fill(costheta_bbbar);
      if( fabs(mc_quark_pdg[0])==4 ) h_costheta_radreturn_cc->Fill(costheta_bbbar);
      if( fabs(mc_quark_pdg[0])<4 ) h_costheta_radreturn_qq->Fill(costheta_bbbar);

      //Rb/Rc calc.
 
      if(selection_type == 11 && jet_btag[0]>btag1) h_f1_radreturn->Fill(costheta_bbbar);
      if(selection_type == 11 && jet_btag[1]>btag2) h_f1_radreturn->Fill(costheta_bbbar);
      if(selection_type == 12) {
	h_f1_radreturn->Fill(costheta_bbbar);
	h_f1_radreturn->Fill(costheta_bbbar);
	h_f2_radreturn->Fill(costheta_bbbar);
	h_f2_radreturn->Fill(costheta_bbbar);
      }
      if(selection_type == 13 && JetBtag(0)==true) h_f1_radreturn->Fill(costheta_bbbar);
      if(selection_type == 13 && JetBtag(1)==true) h_f1_radreturn->Fill(costheta_bbbar);
      if(selection_type == 14) {
	h_f1_radreturn->Fill(costheta_bbbar);
	h_f1_radreturn->Fill(costheta_bbbar);
	h_f2_radreturn->Fill(costheta_bbbar);
	h_f2_radreturn->Fill(costheta_bbbar);
      }
      if(selection_type == 15 && jet_ctag[0]>ctag1) h_f1_radreturn->Fill(costheta_bbbar);
      if(selection_type == 15 && jet_ctag[1]>ctag2) h_f1_radreturn->Fill(costheta_bbbar);
      if(selection_type == 16) {
	h_f1_radreturn->Fill(costheta_bbbar);
	h_f1_radreturn->Fill(costheta_bbbar);
	h_f2_radreturn->Fill(costheta_bbbar);
	h_f2_radreturn->Fill(costheta_bbbar);
      }
      if(selection_type == 17 && JetCtag(0)==true) h_f1_radreturn->Fill(costheta_bbbar);
      if(selection_type == 17 && JetCtag(1)==true) h_f1_radreturn->Fill(costheta_bbbar);
      if(selection_type == 18) {
	h_f1_radreturn->Fill(costheta_bbbar);
	h_f1_radreturn->Fill(costheta_bbbar);
	h_f2_radreturn->Fill(costheta_bbbar);
	h_f2_radreturn->Fill(costheta_bbbar);
      }
      
      h_sintheta_radreturn->Fill(sqrt(1-costheta_bbbar*costheta_bbbar));
      if(reco_b1mass>reco_b2mass) {
	h_mjFat_radreturn->Fill(reco_b1mass);
	h_mjThin_radreturn->Fill(reco_b2mass);
      } else {
	h_mjFat_radreturn->Fill(reco_b2mass);
	h_mjThin_radreturn->Fill(reco_b1mass);
      }

      h_pj1_pj2_radreturn->Fill(jet0_p+jet1_p);
      h_d23_radreturn->Fill(d23);
      h_d12_radreturn->Fill(d12);
      h_y23_radreturn->Fill(y23);
      h_y12_radreturn->Fill(y12);
      h_oblateness_radreturn->Fill(oblateness);
      h_aplanarity_radreturn->Fill(aplanarity);

      h_sphericity_radreturn->Fill(sphericity);
      h_sinacol_radreturn->Fill(acol);
      h_acol_radreturn->Fill(TMath::ASin(acol));
      h_K_radreturn->Fill(Kv);
      h_K_parton_radreturn->Fill(gamma_e);
      h_K_parton_K_radreturn->Fill(gamma_e,Kv);
      h_sphericity_cos_radreturn->Fill(costheta_bbbar,sphericity);
      h_acol_cos_radreturn->Fill(costheta_bbbar,acol);
      h_sphericity_sin_radreturn->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),sphericity);
      h_acol_sin_radreturn->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),acol);
      h_acol_sphericity_radreturn->Fill(sphericity,acol);
      h_thrust_radreturn->Fill(thrust);

      float angle=getAngle2Vec(jet_px[0],jet_py[0],jet_pz[0],jet_E[0],jet_px[1],jet_py[1],jet_pz[1],jet_E[1]);
      h_angle_radreturn->Fill(angle);
    }
    if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut) {
      h_mjj_cc->Fill(reco_bbmass);

      h_egamma_cc->Fill(neutraljet_E[0]);
      h_egamma_cc->Fill(neutraljet_E[1]);

      h_costhetagamma_cc->Fill(neutraljet_costheta[0]);
      h_costhetagamma_cc->Fill(neutraljet_costheta[1]);

      h_e_costheta_gamma_cc->Fill(neutraljet_E[0],neutraljet_costheta[0]);
      h_e_costheta_gamma_cc->Fill(neutraljet_E[1],neutraljet_costheta[1]);

      h_cos_costheta_gamma_cc->Fill(costheta_j0,neutraljet_costheta[1]);
      h_cos_costheta_gamma_cc->Fill(costheta_j1,neutraljet_costheta[1]);
    
      h_mj1_mj2_cc->Fill(reco_b1mass+reco_b2mass);
      h_costheta_cc->Fill(costheta_bbbar);
      //Rb/Rc calc.

      if(selection_type == 11 && jet_btag[0]>btag1) h_f1_cc->Fill(costheta_bbbar);
      if(selection_type == 11 && jet_btag[1]>btag2) h_f1_cc->Fill(costheta_bbbar);
      if(selection_type == 12) {
	h_f1_cc->Fill(costheta_bbbar);
	h_f1_cc->Fill(costheta_bbbar);
	h_f2_cc->Fill(costheta_bbbar);
	h_f2_cc->Fill(costheta_bbbar);
      }
      if(selection_type == 13 && JetBtag(0)==true) h_f1_cc->Fill(costheta_bbbar);
      if(selection_type == 13 && JetBtag(1)==true) h_f1_cc->Fill(costheta_bbbar);
      if(selection_type == 14) {
	h_f1_cc->Fill(costheta_bbbar);
	h_f1_cc->Fill(costheta_bbbar);
	h_f2_cc->Fill(costheta_bbbar);
	h_f2_cc->Fill(costheta_bbbar);
      }
      if(selection_type == 15 && jet_ctag[0]>ctag1) h_f1_cc->Fill(costheta_bbbar);
      if(selection_type == 15 && jet_ctag[1]>ctag2) h_f1_cc->Fill(costheta_bbbar);
      if(selection_type == 16) {
	h_f1_cc->Fill(costheta_bbbar);
	h_f1_cc->Fill(costheta_bbbar);
	h_f2_cc->Fill(costheta_bbbar);
	h_f2_cc->Fill(costheta_bbbar);
      }
      if(selection_type == 17 && JetCtag(0)==true) h_f1_cc->Fill(costheta_bbbar);
      if(selection_type == 17 && JetCtag(1)==true) h_f1_cc->Fill(costheta_bbbar);
      if(selection_type == 18) {
	h_f1_cc->Fill(costheta_bbbar);
	h_f1_cc->Fill(costheta_bbbar);
	h_f2_cc->Fill(costheta_bbbar);
	h_f2_cc->Fill(costheta_bbbar);
      }
      h_sintheta_cc->Fill(sqrt(1-costheta_bbbar*costheta_bbbar));
      if(reco_b1mass>reco_b2mass) {
	h_mjFat_cc->Fill(reco_b1mass);
	h_mjThin_cc->Fill(reco_b2mass);
      } else {
	h_mjFat_cc->Fill(reco_b2mass);
	h_mjThin_cc->Fill(reco_b1mass);
      }
      h_pj1_pj2_cc->Fill(jet0_p+jet1_p);
      h_d23_cc->Fill(d23);
      h_d12_cc->Fill(d12);
      h_y23_cc->Fill(y23);
      h_y12_cc->Fill(y12);
      h_oblateness_cc->Fill(oblateness);
      h_aplanarity_cc->Fill(aplanarity);
      
      h_sphericity_cc->Fill(sphericity);
      h_sinacol_cc->Fill(acol);
      h_acol_cc->Fill(TMath::ASin(acol));
      h_K_cc->Fill(Kv);
      h_K_parton_cc->Fill(gamma_e);
      h_K_parton_K_cc->Fill(gamma_e,Kv);
      h_sphericity_cos_cc->Fill(costheta_bbbar,sphericity);
      h_acol_cos_cc->Fill(costheta_bbbar,acol);
      h_sphericity_sin_cc->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),sphericity);
      h_acol_sin_cc->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),acol);
      h_acol_sphericity_cc->Fill(sphericity,acol);
      h_thrust_cc->Fill(thrust);
  
      float angle=getAngle2Vec(jet_px[0],jet_py[0],jet_pz[0],jet_E[0],jet_px[1],jet_py[1],jet_pz[1],jet_E[1]);
      h_angle_cc->Fill(angle);      
    }
    if(fabs(mc_quark_pdg[0])<4 && gamma_e<Kvcut) {
      h_mjj_qq->Fill(reco_bbmass);

      h_egamma_qq->Fill(neutraljet_E[0]);
      h_egamma_qq->Fill(neutraljet_E[1]);

      h_costhetagamma_qq->Fill(neutraljet_costheta[0]);
      h_costhetagamma_qq->Fill(neutraljet_costheta[1]);

      h_e_costheta_gamma_qq->Fill(neutraljet_E[0],neutraljet_costheta[0]);
      h_e_costheta_gamma_qq->Fill(neutraljet_E[1],neutraljet_costheta[1]);

      h_cos_costheta_gamma_qq->Fill(costheta_j0,neutraljet_costheta[1]);
      h_cos_costheta_gamma_qq->Fill(costheta_j1,neutraljet_costheta[1]);
     
      h_mj1_mj2_qq->Fill(reco_b1mass+reco_b2mass);
      h_costheta_qq->Fill(costheta_bbbar);
      //Rb/Rc calc.
      if(selection_type == 11 && jet_btag[0]>btag1) h_f1_qq->Fill(costheta_bbbar);
      if(selection_type == 11 && jet_btag[1]>btag2) h_f1_qq->Fill(costheta_bbbar);
      if(selection_type == 12) {
	h_f1_qq->Fill(costheta_bbbar);
	h_f1_qq->Fill(costheta_bbbar);
	h_f2_qq->Fill(costheta_bbbar);
	h_f2_qq->Fill(costheta_bbbar);
      }
      if(selection_type == 13 && JetBtag(0)==true) h_f1_qq->Fill(costheta_bbbar);
      if(selection_type == 13 && JetBtag(1)==true) h_f1_qq->Fill(costheta_bbbar);
      if(selection_type == 14) {
	h_f1_qq->Fill(costheta_bbbar);
	h_f1_qq->Fill(costheta_bbbar);
	h_f2_qq->Fill(costheta_bbbar);
	h_f2_qq->Fill(costheta_bbbar);
      }
      if(selection_type == 15 && jet_ctag[0]>ctag1) h_f1_qq->Fill(costheta_bbbar);
      if(selection_type == 15 && jet_ctag[1]>ctag2) h_f1_qq->Fill(costheta_bbbar);
      if(selection_type == 16) {
	h_f1_qq->Fill(costheta_bbbar);
	h_f1_qq->Fill(costheta_bbbar);
	h_f2_qq->Fill(costheta_bbbar);
	h_f2_qq->Fill(costheta_bbbar);
      }
      if(selection_type == 17 && JetCtag(0)==true) h_f1_qq->Fill(costheta_bbbar);
      if(selection_type == 17 && JetCtag(1)==true) h_f1_qq->Fill(costheta_bbbar);
      if(selection_type == 18) {
	h_f1_qq->Fill(costheta_bbbar);
	h_f1_qq->Fill(costheta_bbbar);
	h_f2_qq->Fill(costheta_bbbar);
	h_f2_qq->Fill(costheta_bbbar);
      }
      h_sintheta_qq->Fill(sqrt(1-costheta_bbbar*costheta_bbbar));

      if(reco_b1mass>reco_b2mass) {
	h_mjFat_qq->Fill(reco_b1mass);
	h_mjThin_qq->Fill(reco_b2mass);
      } else {
	h_mjFat_qq->Fill(reco_b2mass);
	h_mjThin_qq->Fill(reco_b1mass);
      }
      h_pj1_pj2_qq->Fill(jet0_p+jet1_p);
      h_d23_qq->Fill(d23);
      h_d12_qq->Fill(d12);
      h_y23_qq->Fill(y23);
      h_y12_qq->Fill(y12);
      h_oblateness_qq->Fill(oblateness);
      h_aplanarity_qq->Fill(aplanarity);

      h_sphericity_qq->Fill(sphericity);
      h_sinacol_qq->Fill(acol);
      h_acol_qq->Fill(TMath::ASin(acol));
      h_K_qq->Fill(Kv);
      h_K_parton_qq->Fill(gamma_e);
      h_K_parton_K_qq->Fill(gamma_e,Kv);
      h_sphericity_cos_qq->Fill(costheta_bbbar,sphericity);
      h_acol_cos_qq->Fill(costheta_bbbar,acol);
      h_sphericity_sin_qq->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),sphericity);
      h_acol_sin_qq->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),acol);
      h_acol_sphericity_qq->Fill(sphericity,acol);
      h_thrust_qq->Fill(thrust);
         

      float angle=getAngle2Vec(jet_px[0],jet_py[0],jet_pz[0],jet_E[0],jet_px[1],jet_py[1],jet_pz[1],jet_E[1]);
      h_angle_qq->Fill(angle);      
    }
    
  }
  cout<<TString::Format("selection_%s_250GeV_%s.root",process.Data(),polarization.Data())<<endl;
  cout<<" Total generated events: bb cc qq bb(rad) cc(rad) qq(rad)" <<endl;
  cout<<"                     "<<bbbar_gen<<" "<<ccbar_gen<<" "<<qqbar_gen<<" "<<bbbar_gen_radreturn<<" "<<ccbar_gen_radreturn<<" "<<qqbar_gen_radreturn<<endl;
    //  cout<<" Total generated Z-radreturn events: " <<radreturn_counter<<endl;
    //cout<<" Total generated qqbar events: " << qq_counter<<endl;
    //cout<<" Total generated ccbar events: " << cc_counter<<endl;

  // save histograms
  h_mjj_bb->Write();
  h_mjj_qq->Write();
  h_mjj_cc->Write();
  h_mjj_radreturn->Write();

  h_costheta_bb->Write();
  h_costheta_qq->Write();
  h_costheta_cc->Write();
  h_costheta_radreturn->Write();
  h_costheta_radreturn_bb->Write();
  h_costheta_radreturn_cc->Write();
  h_costheta_radreturn_qq->Write();

  h_cross_costheta->Write();
  h_cross_costheta_bb->Write();
  h_cross_costheta_qq->Write();
  h_cross_costheta_cc->Write();
  h_cross_costheta_radreturn->Write();
  h_cross_costheta_radreturn_bb->Write();
  h_cross_costheta_radreturn_cc->Write();
  h_cross_costheta_radreturn_qq->Write();

  h_f0_bb->Write();
  h_f0_qq->Write();
  h_f0_cc->Write();
  h_f0_radreturn->Write();

  h_f1_bb->Write();
  h_f1_qq->Write();
  h_f1_cc->Write();
  h_f1_radreturn->Write();

  h_f2_bb->Write();
  h_f2_qq->Write();
  h_f2_cc->Write();
  h_f2_radreturn->Write();

  h_sintheta_bb->Write();
  h_sintheta_qq->Write();
  h_sintheta_cc->Write();
  h_sintheta_radreturn->Write();
  
  h_egamma_bb->Write();
  h_egamma_qq->Write();
  h_egamma_cc->Write();
  h_egamma_radreturn->Write();


  h_costhetagamma_bb->Write();
  h_costhetagamma_qq->Write();
  h_costhetagamma_cc->Write();
  h_costhetagamma_radreturn->Write();

 
  h_e_costheta_gamma_bb->Write();
  h_e_costheta_gamma_qq->Write();
  h_e_costheta_gamma_cc->Write();
  h_e_costheta_gamma_radreturn->Write();

  h_cos_costheta_gamma_bb->Write();
  h_cos_costheta_gamma_qq->Write();
  h_cos_costheta_gamma_cc->Write();
  h_cos_costheta_gamma_radreturn->Write();
  
  h_mj1_mj2_bb->Write();
  h_mj1_mj2_qq->Write();
  h_mj1_mj2_cc->Write();
  h_mj1_mj2_radreturn->Write();

  h_mjFat_bb->Write();
  h_mjFat_qq->Write();
  h_mjFat_cc->Write();
  h_mjFat_radreturn->Write();

  h_mjThin_bb->Write();
  h_mjThin_qq->Write();
  h_mjThin_cc->Write();
  h_mjThin_radreturn->Write();

  h_angle_bb->Write();
  h_angle_qq->Write();
  h_angle_cc->Write();
  h_angle_radreturn->Write();

  h_pj1_pj2_bb->Write();
  h_pj1_pj2_qq->Write();
  h_pj1_pj2_cc->Write();
  h_pj1_pj2_radreturn->Write();

  h_d23_bb->Write();
  h_d23_qq->Write();
  h_d23_cc->Write();
  h_d23_radreturn->Write();

  h_d12_bb->Write();
  h_d12_qq->Write();
  h_d12_cc->Write();
  h_d12_radreturn->Write();

  h_y23_bb->Write();
  h_y23_qq->Write();
  h_y23_cc->Write();
  h_y23_radreturn->Write();

  h_y12_bb->Write();
  h_y12_qq->Write();
  h_y12_cc->Write();
  h_y12_radreturn->Write();

  h_oblateness_bb->Write();
  h_oblateness_qq->Write();
  h_oblateness_cc->Write();
  h_oblateness_radreturn->Write();

  h_aplanarity_bb->Write();
  h_aplanarity_qq->Write();
  h_aplanarity_cc->Write();
  h_aplanarity_radreturn->Write();

  h_sphericity_bb->Write();
  h_sphericity_qq->Write();
  h_sphericity_cc->Write();
  h_sphericity_radreturn->Write();

  h_sphericity_cos_bb->Write();
  h_sphericity_cos_qq->Write();
  h_sphericity_cos_cc->Write();
  h_sphericity_cos_radreturn->Write();

  h_sphericity_sin_bb->Write();
  h_sphericity_sin_qq->Write();
  h_sphericity_sin_cc->Write();
  h_sphericity_sin_radreturn->Write();
  
  h_acol_bb->Write();
  h_acol_qq->Write();
  h_acol_cc->Write();
  h_acol_radreturn->Write();

  h_sinacol_bb->Write();
  h_sinacol_qq->Write();
  h_sinacol_cc->Write();
  h_sinacol_radreturn->Write();

  h_K->Write();
  h_K_bb->Write();
  h_K_qq->Write();
  h_K_cc->Write();
  h_K_radreturn->Write();
  h_K_res->Write();
  
  h_K_parton_bb->Write();
  h_K_parton_qq->Write();
  h_K_parton_cc->Write();
  h_K_parton_radreturn->Write();

  h_K_parton_K_bb->Write();
  h_K_parton_K_qq->Write();
  h_K_parton_K_cc->Write();
  h_K_parton_K_radreturn->Write();

  h_acol_cos_bb->Write();
  h_acol_cos_qq->Write();
  h_acol_cos_cc->Write();
  h_acol_cos_radreturn->Write();

  h_acol_sin_bb->Write();
  h_acol_sin_qq->Write();
  h_acol_sin_cc->Write();
  h_acol_sin_radreturn->Write();
  
  h_acol_sphericity_bb->Write();
  h_acol_sphericity_qq->Write();
  h_acol_sphericity_cc->Write();
  h_acol_sphericity_radreturn->Write();

  h_thrust_bb->Write();
  h_thrust_qq->Write();
  h_thrust_cc->Write();
  h_thrust_radreturn->Write();

   
}



void observable::SelectionBKG(int n_entries=-1, int selection_type=0, TString polarization="eL", float Kvcut=2500)
{
  
  TFile *MyFile = new TFile(TString::Format("selection_%s_250GeV_%s.root",process.Data(),polarization.Data()),"RECREATE");
  MyFile->cd();
  
  //  gROOT->Reset();
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(0.3);
      
    
  TH1F * h_cross_costheta = new TH1F("h_cross_costheta","h_cross_costheta",20,0,1);
  TH1F * h_cross_costheta_bb = new TH1F("h_cross_costheta_bb","h_cross_costheta_bb",20,0,1);
 
  
  //costheta
  TH1F * h_costheta_bb = new TH1F("h_costheta_bb","h_costheta_bb",20,0,1);
  TH1F * h_f0_bb = new TH1F("h_f0_bb","h_f0_bb",20,0,1);
  TH1F * h_f1_bb = new TH1F("h_f1_bb","h_f1_bb",20,0,1);
  TH1F * h_f2_bb = new TH1F("h_f2_bb","h_f2_bb",20,0,1);
  TH1F * h_sintheta_bb = new TH1F("h_sintheta_bb","h_sintheta_bb",20,0,1);

  
  //mass & momentum & angle
  TH1F * h_mjj_bb = new TH1F("h_mjj_bb","h_mjj_bb",100,0,500);
  TH1F * h_egamma_bb = new TH1F("h_egamma_bb","h_egamma_bb",100,0,500);
  TH1F * h_costhetagamma_bb = new TH1F("h_costhetagamma_bb","h_costhetagamma_bb",100,-1,1);
  TH2F * h_e_costheta_gamma_bb = new TH2F("h_e_costheta_gamma_bb","h_e_costheta_gamma_bb",400,-1,1,500,0,500);  
  TH2F * h_cos_costheta_gamma_bb = new TH2F("h_cos_costheta_gamma_bb","h_cos_costheta_gamma_bb",200,-1,1,200,-1,1);
  TH2F * h_cos_costheta_gamma_radreturn = new TH2F("h_cos_costheta_gamma_radreturn","h_cos_costheta_gamma_radreturn",200,-1,1,200,-1,1);

  TH1F * h_mj1_mj2_bb = new TH1F("h_mj1_mj2_bb","h_mj1_mj2_bb",100,0,500);
  TH1F * h_mjFat_bb = new TH1F("h_mjFat_bb","h_mjFat_bb",100,0,500);
  TH1F * h_mjThin_bb = new TH1F("h_mjThin_bb","h_mjThin_bb",100,0,500);
  TH1F * h_angle_bb = new TH1F("h_angle_bb","h_angle_bb",1000,-7,7);
  TH1F * h_pj1_pj2_bb = new TH1F("h_pj1_pj2_bb","h_pj1_pj2_bb",100,0,500);

  //jet algorithm variables
  TH1F * h_d23_bb = new TH1F("h_d23_bb","h_d23_bb",100,0,500);
  TH1F * h_d12_bb = new TH1F("h_d12_bb","h_d12_bb",100,0,100000);
  TH1F * h_y23_bb = new TH1F("h_y23_bb","h_y23_bb",400,0,0.25);
  TH1F * h_y12_bb = new TH1F("h_y12_bb","h_y12_bb",100,0,1);

  //EVENT SHAPE variables
  TH1F * h_oblateness_bb = new TH1F("h_oblateness_bb","h_oblateness_bb",100,0,0.8);
  TH1F * h_aplanarity_bb = new TH1F("h_aplanarity_bb","h_aplanarity_bb",100,-0.4e-6,0.4e-6);
  TH1F * h_sphericity_bb = new TH1F("h_sphericity_bb","h_sphericity_bb",2000,0,2);

  TH1F * h_acol_bb = new TH1F("h_acol_bb","h_acol_bb",1000,-4,4);
  TH1F * h_sinacol_bb = new TH1F("h_sinacol_bb","h_sinacol_bb",200,0,2);
  
  TH1F * h_K = new TH1F("h_K","h_K",2000,0,200);
  TH1F * h_K_bb = new TH1F("h_K_bb","h_K_bb",2000,0,200);
  
  TH1F * h_K_parton_bb = new TH1F("h_K_parton_bb","h_K_parton_bb",2000,0,200);
  TH2F * h_K_parton_K_bb = new TH2F("h_K_parton_K_bb","h_K_parton_K_bb",200,0,200,200,0,200);
  TH1F * h_K_res = new TH1F("h_K_res","h_K_res",4000,-200,200);
  TH2F * h_sphericity_cos_bb = new TH2F("h_sphericity_cos_bb","h_sphericity_cos_bb",40,-1,1,2000,0,2);
  
  TH2F * h_acol_cos_bb = new TH2F("h_acol_cos_bb","h_acol_cos_bb",40,-1,1,2000,0,2);
  TH2F * h_sphericity_sin_bb = new TH2F("h_sphericity_sin_bb","h_sphericity_sin_bb",40,-1,1,2000,0,2);
  TH2F * h_acol_sin_bb = new TH2F("h_acol_sin_bb","h_acol_sin_bb",40,-1,1,2000,0,2);
  TH2F * h_acol_sphericity_bb = new TH2F("h_acol_sphericity_bb","h_acol_sphericity_bb",2000,0,2,2000,0,2);
    
  TH1F * h_thrust_bb = new TH1F("h_thrust_bb","h_thrust_bb",1000,0,1);


  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  int bb_counter=0, radreturn_counter=0, qq_counter=0, cc_counter=0;
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

   
    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e+gamma1_e;//sqrt(pow(mc_ISR_px[0]+mc_ISR_px[1],2)+pow(mc_ISR_py[0]+mc_ISR_py[1],2)+pow(mc_ISR_pz[0]+mc_ISR_pz[1],2));//gamma0_e+gamma1_e;

    //-------------------
    //Kv parton
    double b0_p= sqrt(pow(mc_quark_px[0],2)+pow(mc_quark_py[0],2)+pow(mc_quark_pz[0],2));
    double b1_p= sqrt(pow(mc_quark_px[1],2)+pow(mc_quark_py[1],2)+pow(mc_quark_pz[1],2));
    float costheta_b0;
    std::vector<float> p_b0;
    p_b0.push_back(mc_quark_px[0]);
    p_b0.push_back(mc_quark_py[0]);
    p_b0.push_back(mc_quark_pz[0]);
    costheta_b0=fabs(GetCostheta(p_b0));
    float costheta_b1;
    std::vector<float> p_b1;
    p_b1.push_back(mc_quark_px[1]);
    p_b1.push_back(mc_quark_py[1]);
    p_b1.push_back(mc_quark_pz[1]);
    costheta_b1=fabs(GetCostheta(p_b1));
    TVector3 v0_p(mc_quark_px[0],mc_quark_py[0],mc_quark_pz[0]);
    TVector3 v1_p(mc_quark_px[1],mc_quark_py[1],mc_quark_pz[1]);
    float acol_p=GetSinacol(v0_p,v1_p);
    float Kv_p=250.*acol_p/(acol_p+sqrt(1-costheta_b0*costheta_b0)+sqrt(1-costheta_b1*costheta_b1));

    if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) {
      bbbar_gen++;
      bb_counter++;
    }
    if(gamma_e>Kvcut ) {
      radreturn_counter++;
      if(fabs(mc_quark_pdg[0])==5) bbbar_gen_radreturn++;
      if(fabs(mc_quark_pdg[0])==4) ccbar_gen_radreturn++;
      if(fabs(mc_quark_pdg[0])<4) qqbar_gen_radreturn++;
    }
    if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut){
      cc_counter++;
      ccbar_gen++;
    }
    if(fabs(mc_quark_pdg[0])<5 && gamma_e<Kvcut) {
      qq_counter++;
      qqbar_gen++;
    }


    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //reco stuff
    double reco_b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
    double reco_b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
    double reco_bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

    double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
    double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

    double jj_pT= sqrt(pow(jet_px[0]+jet_px[1],2)+pow(jet_py[0]+jet_py[1],2));

    float costheta_bbbar;
    std::vector<float> p_bbar;
    p_bbar.push_back(jet_px[0]-jet_px[1]);
    p_bbar.push_back(jet_py[0]-jet_py[1]);
    p_bbar.push_back(jet_pz[0]-jet_pz[1]);
    costheta_bbbar=fabs(GetCostheta(p_bbar));

    float costheta_j0;
    std::vector<float> p_j0;
    p_j0.push_back(jet_px[0]);
    p_j0.push_back(jet_py[0]);
    p_j0.push_back(jet_pz[0]);
    costheta_j0=GetCostheta(p_j0);

    float costheta_j1;
    std::vector<float> p_j1;
    p_j1.push_back(jet_px[1]);
    p_j1.push_back(jet_py[1]);
    p_j1.push_back(jet_pz[1]);
    costheta_j1=GetCostheta(p_j1);

    TVector3 v0(jet_px[0],jet_py[0],jet_pz[0]);
    TVector3 v1(jet_px[1],jet_py[1],jet_pz[1]);
    float acol=GetSinacol(v0,v1);
    float Kv=250.*acol/(acol+sqrt(1-costheta_j0*costheta_j0)+sqrt(1-costheta_j1*costheta_j1));

    float thrust=principle_thrust_value;//GetThrust(v0,v1);
 
    double  neutralPFO_max[2];
    double  neutralPFO_total[2];
    double  neutralPFO_ratio[2];

    double  neutraljet_E[2];
    double  neutraljet_costheta[2];

    double npfo[2];
    for(int ijet=0; ijet<2; ijet++) {
      neutralPFO_max[ijet]=0;
      neutralPFO_total[ijet]=0;
      neutralPFO_ratio[ijet]=0;
      npfo[ijet]=0;
      double jetenergy=0;

      for(int ipfo=0; ipfo<100; ipfo++) {//jet_pfo_n[ijet]; ipfo++) {
	if(jet_pfo_E[ijet][ipfo]<0.1) continue;
	
	npfo[ijet]++;
	jetenergy+=jet_pfo_E[ijet][ipfo];
	if( (jet_pfo_type[ijet][ipfo]==22 || jet_pfo_charge[ijet][ipfo]==0) && jet_pfo_E[ijet][ipfo]> neutralPFO_max[ijet]) {
	  neutralPFO_max[ijet]=jet_pfo_E[ijet][ipfo]; 
	}
	if( jet_pfo_type[ijet][ipfo]==22 ||  jet_pfo_charge[ijet][ipfo]==0 ) {
	  neutralPFO_total[ijet]+=jet_pfo_E[ijet][ipfo]; 
	  neutralPFO_ratio[ijet]+=jet_pfo_E[ijet][ipfo]; 
	}
      }
      neutralPFO_ratio[ijet]/=jetenergy;
    }

    for(int ijet=0; ijet<2; ijet++) {
      neutraljet_E[ijet]=-1;
      neutraljet_costheta[ijet]=-2; 
      if(neutralPFO_ratio[ijet]>0.85) {
	neutraljet_E[ijet]=jet_E[ijet];
	if(ijet==0) neutraljet_costheta[ijet]=costheta_j0;
	if(ijet==1) neutraljet_costheta[ijet]=costheta_j1;
      }
    }
    
     
    // parton level definitions
    h_cross_costheta->Fill(costheta_bbbar);
    h_cross_costheta_bb->Fill(costheta_bbbar);

    if(PreSelection(5,Kvcut)==true) {
      h_f0_bb->Fill(costheta_bbbar);
      h_f0_bb->Fill(costheta_bbbar);
    }
    
						
    bool selection=PreSelection(selection_type,Kvcut);
    if(selection==false) continue;
	  
    h_K_res->Fill(gamma_e-Kv);
    
    h_costheta_bb->Fill(costheta_bbbar);
    
    //Rb/Rc calc.

    if(selection_type == 11 && jet_btag[0]>btag1) h_f1_bb->Fill(costheta_bbbar);
    if(selection_type == 11 && jet_btag[1]>btag2) h_f1_bb->Fill(costheta_bbbar);
    if(selection_type == 12) {
      h_f1_bb->Fill(costheta_bbbar);
      h_f1_bb->Fill(costheta_bbbar);
      h_f2_bb->Fill(costheta_bbbar);
      h_f2_bb->Fill(costheta_bbbar);
    }
    if(selection_type == 13 && JetBtag(0)==true) h_f1_bb->Fill(costheta_bbbar);
    if(selection_type == 13 && JetBtag(1)==true) h_f1_bb->Fill(costheta_bbbar);
    if(selection_type == 14) {
      h_f1_bb->Fill(costheta_bbbar);
      h_f1_bb->Fill(costheta_bbbar);
      h_f2_bb->Fill(costheta_bbbar);
      h_f2_bb->Fill(costheta_bbbar);
    }
    if(selection_type == 15 && jet_ctag[0]>ctag1) h_f1_bb->Fill(costheta_bbbar);
    if(selection_type == 15 && jet_ctag[1]>ctag2) h_f1_bb->Fill(costheta_bbbar);
    if(selection_type == 16) {
      h_f1_bb->Fill(costheta_bbbar);
      h_f1_bb->Fill(costheta_bbbar);
      h_f2_bb->Fill(costheta_bbbar);
      h_f2_bb->Fill(costheta_bbbar);
    }
    if(selection_type == 17 && JetCtag(0)==true) h_f1_bb->Fill(costheta_bbbar);
    if(selection_type == 17 && JetCtag(1)==true) h_f1_bb->Fill(costheta_bbbar);
    if(selection_type == 18) {
      h_f1_bb->Fill(costheta_bbbar);
      h_f1_bb->Fill(costheta_bbbar);
      h_f2_bb->Fill(costheta_bbbar);
      h_f2_bb->Fill(costheta_bbbar);
    }
    
    h_sintheta_bb->Fill(sqrt(1-costheta_bbbar*costheta_bbbar));
    h_mjj_bb->Fill(reco_bbmass);
    
    h_egamma_bb->Fill(neutraljet_E[0]);
    h_egamma_bb->Fill(neutraljet_E[1]);
    
    h_costhetagamma_bb->Fill(neutraljet_costheta[0]);
    h_costhetagamma_bb->Fill(neutraljet_costheta[1]);
    
    h_e_costheta_gamma_bb->Fill(neutraljet_E[0],neutraljet_costheta[0]);
    h_e_costheta_gamma_bb->Fill(neutraljet_E[1],neutraljet_costheta[1]);
    
    h_cos_costheta_gamma_bb->Fill(costheta_j0,neutraljet_costheta[1]);
    h_cos_costheta_gamma_bb->Fill(costheta_j1,neutraljet_costheta[1]);
    
    h_mj1_mj2_bb->Fill(reco_b1mass+reco_b2mass);
    if(reco_b1mass>reco_b2mass) {
      h_mjFat_bb->Fill(reco_b1mass);
      h_mjThin_bb->Fill(reco_b2mass);
    } else {
      h_mjFat_bb->Fill(reco_b2mass);
      h_mjThin_bb->Fill(reco_b1mass);
    }
    h_pj1_pj2_bb->Fill(jet0_p+jet1_p);
    h_d23_bb->Fill(d23);
    h_d12_bb->Fill(d12);
    h_y23_bb->Fill(y23);
    h_y12_bb->Fill(y12);
    h_oblateness_bb->Fill(oblateness);
    h_aplanarity_bb->Fill(aplanarity);
    
    h_sphericity_bb->Fill(sphericity);
    h_sinacol_bb->Fill(acol);
    h_acol_bb->Fill(TMath::ASin(acol));
    h_K_bb->Fill(Kv);
    h_K_parton_bb->Fill(gamma_e);
    h_K_parton_K_bb->Fill(gamma_e,Kv);
    h_sphericity_cos_bb->Fill(costheta_bbbar,sphericity);
    h_acol_cos_bb->Fill(costheta_bbbar,acol);
    h_sphericity_sin_bb->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),sphericity);
    h_acol_sin_bb->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),acol);
    h_acol_sphericity_bb->Fill(sphericity,acol);
    h_thrust_bb->Fill(thrust);
    
    float angle=getAngle2Vec(jet_px[0],jet_py[0],jet_pz[0],jet_E[0],jet_px[1],jet_py[1],jet_pz[1],jet_E[1]);
    h_angle_bb->Fill(angle);
    
  }
  cout<<TString::Format("selection_%s_250GeV_%s.root",process.Data(),polarization.Data())<<endl;
  cout<<" Total generated events: bb cc qq bb(rad) cc(rad) qq(rad)" <<endl;
  cout<<"                     "<<bbbar_gen<<" "<<ccbar_gen<<" "<<qqbar_gen<<" "<<bbbar_gen_radreturn<<" "<<ccbar_gen_radreturn<<" "<<qqbar_gen_radreturn<<endl;
    //  cout<<" Total generated Z-radreturn events: " <<radreturn_counter<<endl;
    //cout<<" Total generated qqbar events: " << qq_counter<<endl;
    //cout<<" Total generated ccbar events: " << cc_counter<<endl;

  // save histograms
  h_mjj_bb->Write();
  h_costheta_bb->Write();

  h_cross_costheta->Write();
  h_cross_costheta_bb->Write();


  h_f0_bb->Write();
  h_f1_bb->Write();
  h_f2_bb->Write();

  h_sintheta_bb->Write(); 
  h_egamma_bb->Write();
  h_costhetagamma_bb->Write();
 
  h_e_costheta_gamma_bb->Write();
  h_cos_costheta_gamma_bb->Write();
  
  h_mj1_mj2_bb->Write();
  h_mjFat_bb->Write();
  h_mjThin_bb->Write();

  h_angle_bb->Write();
  h_pj1_pj2_bb->Write();
  h_d23_bb->Write();
  h_d12_bb->Write();
  h_y23_bb->Write();

  h_y12_bb->Write();

  h_oblateness_bb->Write();
  h_aplanarity_bb->Write();
  h_sphericity_bb->Write();
  h_sphericity_cos_bb->Write();

  h_sphericity_sin_bb->Write();
  
  h_acol_bb->Write();
  h_sinacol_bb->Write();

  h_K->Write();
  h_K_bb->Write();
  
  h_K_parton_bb->Write();
  h_K_parton_K_bb->Write();
  h_acol_cos_bb->Write();
  h_acol_sin_bb->Write();
  h_acol_sphericity_bb->Write();
  h_thrust_bb->Write();


   
}

std::vector<float> observable::CalculateP(TH1F* h_accepted, TH1F *h_rejected)
{

  for(int i=1; i<nbins/2+1; i++) {
    float accepted = h_accepted->GetBinContent(nbins+1-i);
    float rejected = h_rejected->GetBinContent(nbins+1-i);
    accepted += h_accepted->GetBinContent(i);
    float a=1;
    float b=-1;
    float c= rejected/ (2* (accepted+rejected));
    float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
    float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
  }

  std::vector<float> result_error;
  std::vector<float> result;

  for(int i=1; i<nbins/2+1; i++) {
    std::vector<float> result_j;
    for(int i1=-1; i1<2; i1+=2) {
      for(int i2=-1; i2<2; i2+=2) {
	for(int i3=-1; i3<2; i3+=2) {
	  float accepted = h_accepted->GetBinContent(nbins+1-i)+i1*sqrt(h_accepted->GetBinContent(nbins+1-i));
	  float rejected = h_rejected->GetBinContent(nbins+1-i)+i2*sqrt(h_rejected->GetBinContent(nbins+1-i));
	  accepted += h_accepted->GetBinContent(i)+i3*sqrt(h_accepted->GetBinContent(i));
	  
	  float a=1;
	  float b=-1;
	  float c= rejected/ (2* (accepted+rejected));
	  float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
	  float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
	  if(p>0.99) p=0;
	  if(p2>0.99) p2=0;
	  if(p>0 || p2>0 ) result_j.push_back(max(p,p2));
	}
      }
    }
    float average=0;
    float n=0;
    for(unsigned j=0; j<result_j.size(); j++) {
      if(result_j.at(j)>0) {
	average+=result_j.at(j);
	n++;
      }
    }
    average/=n;
 
    if(average!=0) {
      result.push_back(average);
      float std_dev=0;
      for(unsigned j=0; j<result_j.size(); j++) {
	if(result_j.at(j)>0) {
	  std_dev+=pow(result_j.at(j)-average,2);
	}
      }
      std_dev=sqrt(std_dev/(n-1));
      result_error.push_back(std_dev);
    } else {
      result_error.push_back(0);
      result.push_back(0);
    }
  }

  for(unsigned i=0; i<result_error.size(); i++) {
    if(result_error.at(i)>0) 
      result.push_back(result_error.at(i));
    else
      result.push_back(0);
  }


  return result;
   
}

//--------------------------------------------------------------------
// pq correction
// *******************************************************************
TH1F* observable::CorrectHistoSingleTag(TH1F* histo, std::vector<float> p_vect) {
  

  TH1F * corrected = new TH1F("corrected","corrected",nbins,-1,1);
  corrected->Sumw2();
  for(int i=1; i<nbins/2+1; i++) {
    float p=p_vect.at(i-1);
    float q=1-p;
    float weight = 1./(p*p-q*q);

    //calcualte average
    float av_i=0;
    float av_41i=0;
    float n=0;
    //   for(int i1=-1; i1<2; i1+=1) {
    //  for(int i2=-1; i2<2; i2+=1) {
    float nm_reco_error = histo->GetBinContent(i);//+i1*histo->GetBinError(i);
    float np_reco_error= histo->GetBinContent(nbins+1-i);//+i2*histo->GetBinError(nbins+1-i);
    av_i+= -(np_reco_error*q-nm_reco_error*p)*weight ;
    av_41i+= (np_reco_error*p-nm_reco_error*q)*weight ;
	n++;
	// }
	//  }
    av_i/=n;
    av_41i/=n;
    corrected->SetBinContent(i,av_i);
    corrected->SetBinContent(nbins+1-i,av_41i);

    //calculate error
    float error_i_min=1000000000;
    float error_41i_min=100000000;
    float error_i_max=0;
    float error_41i_max=0;
    float error_i=0;
    float error_41i=0;
    n=0;
    for(int i1=-1; i1<2; i1+=1) {
      for(int i2=-1; i2<2; i2+=1) {
	float nm_reco_error = histo->GetBinContent(i)+i1*histo->GetBinError(i);
	float np_reco_error= histo->GetBinContent(nbins+1-i)+i2*histo->GetBinError(nbins+1-i);
	double a=-(np_reco_error*q-nm_reco_error*p)*weight;
	double b=(np_reco_error*p-nm_reco_error*q)*weight ;
	if(a<error_i_min) error_i_min=a;
	if(a>error_i_max) error_i_max=a;

	if(b<error_41i_min) error_41i_min=b;
	if(b>error_41i_max) error_41i_max=b;
	
	error_i+=pow( -(np_reco_error*q-nm_reco_error*p)*weight -av_i ,2);
	error_41i+=pow( (np_reco_error*p-nm_reco_error*q)*weight  - av_41i, 2);
	
	n++;
      }
    }

    //    error_i=fabs(error_i_max-error_i_min)/2.;
    //error_41i=fabs(error_41i_max-error_41i_min)/2.;
    
    error_i=sqrt(error_i/(n-1.));
    error_41i=sqrt(error_41i/(n-1.));
    corrected->SetBinError(i,error_i );
    corrected->SetBinError(nbins+1-i,error_41i );
  }
  
  return corrected;

}

TH1F* observable::CorrectHistoDoubleTag(TH1F* histo, std::vector<float> p_vect) {
  

  TH1F * corrected = new TH1F("corrected","corrected",nbins,-1,1);
  corrected->Sumw2();
  for(int i=1; i<nbins/2+1; i++) {
    float p=p_vect.at(i-1);
    float q=1-p;
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);

    //calcualte average
    float av_i=0;
    float av_41i=0;
    float n=0;
    for(int i1=-1; i1<2; i1+=1) {
      for(int i2=-1; i2<2; i2+=1) {
	float nm_reco_error = histo->GetBinContent(i)+i1*histo->GetBinError(i);
	float np_reco_error= histo->GetBinContent(nbins+1-i)+i2*histo->GetBinError(nbins+1-i);
	av_i+= (np_reco_error*q*q-nm_reco_error*p*p)*weight ;
	av_41i+= -(np_reco_error*p*p-nm_reco_error*q*q)*weight ;
	n++;
      }
    }
    av_i/=n;
    av_41i/=n;
    corrected->SetBinContent(i,av_i);
    corrected->SetBinContent(nbins+1-i,av_41i);

    //calculate error
    float error_i=0;
    float error_41i=0;
    n=0;
    for(int i1=-1; i1<2; i1+=1) {
      for(int i2=-1; i2<2; i2+=1) {
	float nm_reco_error = histo->GetBinContent(i)+i1*histo->GetBinError(i);
	float np_reco_error= histo->GetBinContent(nbins+1-i)+i2*histo->GetBinError(nbins+1-i);
	error_i+=pow( (np_reco_error*q*q-nm_reco_error*p*p)*weight -av_i ,2);
	error_41i+=pow( -(np_reco_error*p*p-nm_reco_error*q*q)*weight  - av_41i, 2);
	n++;
      }
    }
    error_i=sqrt(error_i/(n-1.));
    error_41i=sqrt(error_41i/(n-1.));
    corrected->SetBinError(i,error_i );
    corrected->SetBinError(nbins+1-i,error_41i );
  }
  
  return corrected;

}


TH1F* observable::MakeCorrection(TString type, TH1F* h_reco, TH1F* h_rejected) {
  
  std::vector<float> p_b_vect=CalculateP(h_reco,h_rejected);
  TH1F * p_b = new TH1F("p_"+type,"p_"+type,nbins/2,0,1);
  p_b->Sumw2();
  for(unsigned i=0; i<p_b_vect.size()/2; i++) {
    p_b->SetBinContent(nbins/2-i,p_b_vect.at(i));
    p_b->SetBinError(nbins/2-i,p_b_vect.at(i+nbins/2));
  }
  //0=reco, 1=truth, 2=corrected,  3=bkg_q, 4=bkg_radreturn
  if(type=="BcBc") asymm_BcBc[2]=CorrectHistoDoubleTag(asymm_BcBc[0],p_b_vect);
  if(type=="KcKc") asymm_KcKc[2]=CorrectHistoDoubleTag(asymm_KcKc[0],p_b_vect);
  if(type=="BcKc") asymm_BcKc[2]=CorrectHistoDoubleTag(asymm_BcKc[0],p_b_vect);
  if(type=="KcBc") asymm_KcBc[2]=CorrectHistoDoubleTag(asymm_KcBc[0],p_b_vect);
  if(type=="BcKc_same1") asymm_BcKc_same1[2]=CorrectHistoDoubleTag(asymm_BcKc_same1[0],p_b_vect);
  if(type=="BcKc_same2") asymm_BcKc_same2[2]=CorrectHistoDoubleTag(asymm_BcKc_same2[0],p_b_vect);

  return p_b;
  
}

TH1F* observable::MakeCorrectionSingle(TString type, TH1F* h_reco, TH1F* h_rejected) {

  std::vector<float> p_b_vect=CalculateP(h_reco,h_rejected);
  TH1F * p_b = new TH1F("p_"+type,"p_"+type,nbins/2,0,1);
  p_b->Sumw2();
  for(unsigned i=0; i<p_b_vect.size()/2; i++) {
    p_b->SetBinContent(nbins/2-i,p_b_vect.at(i));
    p_b->SetBinError(nbins/2-i,p_b_vect.at(i+nbins/2));
  }
  //0=reco, 1=truth, 2=corrected,  3=bkg_q, 4=bkg_radreturn
  if(type=="BcBc") asymm_BcBc[2]=CorrectHistoSingleTag(asymm_BcBc[0],p_b_vect);
  if(type=="KcKc") asymm_KcKc[2]=CorrectHistoSingleTag(asymm_KcKc[0],p_b_vect);
  if(type=="BcKc") asymm_BcKc[2]=CorrectHistoSingleTag(asymm_BcKc[0],p_b_vect);
  if(type=="KcBc") asymm_KcBc[2]=CorrectHistoSingleTag(asymm_KcBc[0],p_b_vect);
  if(type=="BcKc_same1") asymm_BcKc_same1[2]=CorrectHistoSingleTag(asymm_BcKc_same1[0],p_b_vect);
  if(type=="BcKc_same2") asymm_BcKc_same2[2]=CorrectHistoSingleTag(asymm_BcKc_same2[0],p_b_vect);

  return p_b;

}

bool observable::PreSelection(int type=0,float Kvcut=25) {
  
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

    if(type == -1 )  if( Kv < Kvcut && bbmass>130 && ISR_1==false ) return true;
    if(type == -2 )  if( Kv < Kvcut && bbmass>130 && ISR_1==false && ISR_2==false ) return true;
    
    if(type == 1 )  if( Kv < Kvcut ) return true;
    if(type == 2 )  if( Kv < Kvcut && bbmass>130 )  return true;
    if(type == 3 )  if( ISR_1==false && ISR_2==false && ISR_3==false && bbmass>130 && Kv < Kvcut)  return true;
    
    if(type == 4 )  if( bbmass>130 && Kv < Kvcut && ISR_1==false && ISR_2==false && ISR_3==false && y23<0.015 )  return true;
    if(type == 5 )  if( bbmass>130 && Kv < Kvcut && ISR_1==false && ISR_2==false && ISR_3==false && y23<0.015 && (b1mass+b2mass)<100)  return true;
    
  
    if(type > 10) {
      if( bbmass>130 && Kv < Kvcut && ISR_1==false && ISR_2==false && ISR_3==false && y23<0.015 && (b1mass+b2mass)<100  ) {
	//btagging
	if(type == 11 )  if( jet_btag[0]>btag1) return true;
	if(type == 12 )  if( jet_btag[0]>btag1 && jet_btag[1]>btag2) return true;
	if(type == 13 )  if( JetBtag(0)==true || JetBtag(1)==true ) return true;
	if(type == 14 )  if( JetBtag(0)==true && JetBtag(1)==true ) return true;
	
	//ctagging
	if(type == 15 )  if( jet_ctag[0]>ctag1 || jet_ctag[1]>ctag2 ) return true;
	if(type == 16 )  if( jet_ctag[0]>ctag1 && jet_ctag[1]>ctag2 ) return true;
      }
    }

  return false;
}


bool observable::JetCtag(int ijet) {

  double ctagv=0;
  if(ijet==0) ctagv=ctag1;
  if(ijet==1) ctagv=ctag2;

  if(jet_ctag[ijet]<ctagv) return false;

  if(ChargeKcJet(ijet)!=0) return true;
  if(ChargeBcJet(ijet)!=0) return true;

  return false;

}


bool observable::JetBtag(int ijet) {

  double btagv=0;
  if(ijet==0) btagv=btag1;
  if(ijet==1) btagv=btag2;
  
  if(jet_btag[ijet]<btagv) return false;


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

  if(momvertex<25) return false;  

  
  //  if(ChargeKcJet(ijet)!=0) return true;
  //if(ChargeBcJet(ijet)!=0) return true;

  return true;

}
  

float observable::ChargeBcJet(int ijet) {

  double btagv=0;
  if(ijet==0) btagv=btag1;
  if(ijet==1) btagv=btag2;

  if(jet_btag[ijet]<btagv) return 0;
  
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

  if(momvertex<25) return 0;
  
  for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
    for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
      double mom = sqrt(pow(jet_track_px[ijet][ivtx][itrack],2)+pow(jet_track_py[ijet][ivtx][itrack],2)+pow(jet_track_pz[ijet][ivtx][itrack],2));
      //if(mom>1)
      charge+=jet_track_charge[ijet][ivtx][itrack];
    }
  }

  return charge;
}

float observable::ChargeKcJet(int ijet){//, int eff=0.88) {

  double btagv=0;
  if(ijet==0) btagv=btag1;
  if(ijet==1) btagv=btag2;

  if(jet_btag[ijet]<btagv) return 0;
  
  float eff=0.90;//88;
  float purity=0.975;//95;


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

  if(momvertex<25) return 0;
  
  double charge=0;

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

      TRandom1 *r3 = new TRandom1();
      double gen_05=r3->Rndm();
      
      if( iskaon==true) {
	if(gen_purity<purity) charge+=jet_track_charge[ijet][ivtx][itrack];
	else {
	  if(gen_05<0.5) charge-=jet_track_charge[ijet][ivtx][itrack];
	  else charge+=jet_track_charge[ijet][ivtx][itrack];
	}
      }
    }
    
  }
    
  return charge;
}

std::vector<float> observable::Error(double effb,double error_effb,double effbd,double error_effbd) {

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


std::vector<float> observable::ErrorLEP(double effb,double error_effb,double effbd,double error_effbd) {

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

