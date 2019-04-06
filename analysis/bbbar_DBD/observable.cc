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
  
  for(int i=0; i<5; i++) {
    asymm_BcBc[i]= new TH1F(TString::Format("Asymm_BcBc_%i",i),TString::Format("Asymm_BcBc_%i",i),nbins,-1.0,1.0);
    asymm_BcBc[i]->Sumw2();
  }
   
  for(int i=0; i<5; i++) {
    asymm_KcKc[i]= new TH1F(TString::Format("Asymm_KcKc_%i",i),TString::Format("Asymm_KcKc_%i",i),nbins,-1.0,1.0);
    asymm_KcKc[i]->Sumw2();
  }
   
  for(int i=0; i<5; i++) {
    asymm_BcKc[i]= new TH1F(TString::Format("Asymm_BcKc_%i",i),TString::Format("Asymm_BcKc_%i",i),nbins,-1.0,1.0);
    asymm_BcKc[i]->Sumw2();
  }
   
  for(int i=0; i<5; i++) {
    asymm_KcBc[i]= new TH1F(TString::Format("Asymm_KcBc_%i",i),TString::Format("Asymm_KcBc_%i",i),nbins,-1.0,1.0);
    asymm_KcBc[i]->Sumw2();
  }
   
  for(int i=0; i<5; i++) {
    asymm_BcKc_same1[i]= new TH1F(TString::Format("Asymm_BcKc_same1_%i",i),TString::Format("Asymm_BcKc_same1_%i",i),nbins,-1.0,1.0);
    asymm_BcKc_same1[i]->Sumw2();
  }
   
  for(int i=0; i<5; i++) {
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

  /*
    float max=0;
    for(int i=0; i<20; i++) {
    if(h_cos_preselection->GetBinContent(i+1)>max) max=h_cos_preselection->GetBinContent(i+1);
    }
    h_cos_preselection->Scale(1./max);

    float max_BcBc=0, max_KcKc=0, max_BcKc=0, max_KcBc=0, max_BcKc_same1=0, max_BcKc_same2=0;
    for(int i=0; i<20; i++) {
    if(h_cos_charge_BcBc->GetBinContent(i+1)>max_BcBc) max_BcBc=h_cos_charge_BcBc->GetBinContent(i+1);
    if(h_cos_charge_KcKc->GetBinContent(i+1)>max_KcKc) max_KcKc=h_cos_charge_KcKc->GetBinContent(i+1);
    if(h_cos_charge_BcKc->GetBinContent(i+1)>max_BcKc) max_BcKc=h_cos_charge_BcKc->GetBinContent(i+1);
    if(h_cos_charge_KcBc->GetBinContent(i+1)>max_KcBc) max_KcBc=h_cos_charge_KcBc->GetBinContent(i+1);
    if(h_cos_charge_BcKc_same1->GetBinContent(i+1)>max_BcKc_same1) max_BcKc_same1=h_cos_charge_BcKc_same1->GetBinContent(i+1);
    if(h_cos_charge_BcKc_same2->GetBinContent(i+1)>max_BcKc_same2) max_BcKc_same2=h_cos_charge_BcKc_same2->GetBinContent(i+1);
    }
  
    h_cos_charge_BcBc->Scale(1./max_BcBc);
    h_cos_charge_KcKc->Scale(1./max_KcKc);
    h_cos_charge_BcKc->Scale(1./max_BcKc);
    h_cos_charge_KcBc->Scale(1./max_KcBc);
    h_cos_charge_BcKc_same1->Scale(1./max_BcKc_same1);
    h_cos_charge_BcKc_same2->Scale(1./max_BcKc_same2);*/

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
  asymm_all[36]->SetName("parton");
  asymm_all[36]->Write();
  //reco level, categories
  asymm_all[0]->SetName("reco_BcBc");
  asymm_all[6]->SetName("reco_KcKc");
  asymm_all[12]->SetName("reco_BcKc");
  asymm_all[18]->SetName("reco_KcBc");
  asymm_all[24]->SetName("reco_BcKc_same1");
  asymm_all[30]->SetName("reco_BcKc_same2");
  asymm_all[0]->Write();
  asymm_all[6]->Write();
  asymm_all[12]->Write();
  asymm_all[18]->Write();
  asymm_all[24]->Write();
  asymm_all[30]->Write();
  //truth level, categories
  asymm_all[1]->SetName("cheatedcharge_BcBc");
  asymm_all[7]->SetName("cheatedcharge_KcKc");
  asymm_all[13]->SetName("cheatedcharge_BcKc");
  asymm_all[19]->SetName("cheatedcharge_KcBc");
  asymm_all[25]->SetName("cheatedcharge_BcKc_same1");
  asymm_all[31]->SetName("cheatedcharge_BcKc_same2");
  asymm_all[1]->Write();
  asymm_all[7]->Write();
  asymm_all[13]->Write();
  asymm_all[19]->Write();
  asymm_all[25]->Write();
  asymm_all[31]->Write();
  //corrected level, categories
  asymm_all[2]->SetName("corrected_BcBc");
  asymm_all[8]->SetName("corrected_KcKc");
  asymm_all[14]->SetName("corrected_BcKc");
  asymm_all[20]->SetName("corrected_KcBc");
  asymm_all[26]->SetName("corrected_BcKc_same1");
  asymm_all[32]->SetName("corrected_BcKc_same2");
  asymm_all[2]->Write();
  asymm_all[8]->Write();
  asymm_all[14]->Write();
  asymm_all[20]->Write();
  asymm_all[26]->Write();
  asymm_all[32]->Write();
  //bkg qq level, categories
  asymm_all[3]->SetName("bkg_qq_BcBc");
  asymm_all[9]->SetName("bkg_qq_KcKc");
  asymm_all[15]->SetName("bkg_qq_BcKc");
  asymm_all[21]->SetName("bkg_qq_KcBc");
  asymm_all[27]->SetName("bkg_qq_BcKc_same1");
  asymm_all[33]->SetName("bkg_qq_BcKc_same2");
  asymm_all[3]->Write();
  asymm_all[9]->Write();
  asymm_all[15]->Write();
  asymm_all[21]->Write();
  asymm_all[27]->Write();
  asymm_all[33]->Write();
  //bkg Z-radreturn level, categories
  asymm_all[4]->SetName("bkg_radreturn_BcBc");
  asymm_all[10]->SetName("bkg_radreturn_KcKc");
  asymm_all[16]->SetName("bkg_radreturn_BcKc");
  asymm_all[22]->SetName("bkg_radreturn_KcBc");
  asymm_all[28]->SetName("bkg_radreturn_BcKc_same1");
  asymm_all[34]->SetName("bkg_radreturn_BcKc_same2");
  asymm_all[4]->Write();
  asymm_all[10]->Write();
  asymm_all[16]->Write();
  asymm_all[22]->Write();
  asymm_all[28]->Write();
  asymm_all[34]->Write();
  //calculated efficiencies (truth), categories + preseletion
  asymm_all[37]->SetName("event_reconstruction_eff_preselection");
  asymm_all[38]->SetName("event_reconstruction_eff_BcBc");
  asymm_all[39]->SetName("event_reconstruction_eff_KcKc");
  asymm_all[40]->SetName("event_reconstruction_eff_BcKc");
  asymm_all[41]->SetName("event_reconstruction_eff_KcBc");
  asymm_all[42]->SetName("event_reconstruction_eff_BcKc_same1");
  asymm_all[43]->SetName("event_reconstruction_eff_BcKc_same2");
  for(int i=37; i<44; i++) {
    asymm_all[i]->Write();
  }

  // Global histograms
  //-------------------------------------
  //reco
  asymm_all[0]->Add(asymm_all[6]);//kckc
  asymm_all[0]->Add(asymm_all[12]);//bckc
  asymm_all[0]->Add(asymm_all[18]);//kcbc
  asymm_all[0]->Add(asymm_all[24]);//bckc_same
  asymm_all[0]->Add(asymm_all[30]);//kcbc_same
 
  //truth
  asymm_all[1]->Add(asymm_all[7]);//kckc
  asymm_all[1]->Add(asymm_all[13]);//bckc
  asymm_all[1]->Add(asymm_all[19]);//kcbc
  asymm_all[1]->Add(asymm_all[25]);//bckc_same
  asymm_all[1]->Add(asymm_all[31]);//kcbc_same

  //corrected  
  asymm_all[2]->Add(asymm_all[8]);//kckc
  asymm_all[2]->Add(asymm_all[14]);//bckc
  asymm_all[2]->Add(asymm_all[20]);//kcbc
  asymm_all[2]->Add(asymm_all[26]);//bckc_same
  asymm_all[2]->Add(asymm_all[32]);//kcbc_same
  
  //bkg-qq
  asymm_all[3]->Add(asymm_all[9]);//kckc
  asymm_all[3]->Add(asymm_all[15]);//bckc
  asymm_all[3]->Add(asymm_all[21]);//kcbc
  asymm_all[3]->Add(asymm_all[27]);//bckc_same
  asymm_all[3]->Add(asymm_all[33]);//kcbc_same

  //bkg-radreturn
  asymm_all[4]->Add(asymm_all[10]);//kckc
  asymm_all[4]->Add(asymm_all[16]);//bckc
  asymm_all[4]->Add(asymm_all[22]);//kcbc
  asymm_all[4]->Add(asymm_all[28]);//bckc_same
  asymm_all[4]->Add(asymm_all[34]);//kcbc_same

  asymm_all[0]->SetName("reco");
  asymm_all[1]->SetName("truth");
  asymm_all[2]->SetName("corrected");
  asymm_all[3]->SetName("bkg_qq");
  asymm_all[4]->SetName("bkg_radreturn");

  for(int i=0; i<5; i++) asymm_all[i]->Write();

  asymm_all[5]->SetName("p_value_BcBc");
  asymm_all[11]->SetName("p_value_KcKc");
  asymm_all[17]->SetName("p_value_BcKc");
  asymm_all[23]->SetName("p_value_KcBc");
  asymm_all[29]->SetName("p_value_BcKc_same1");
  asymm_all[35]->SetName("p_value_BcKc_same2");
  asymm_all[5]->Write();
  asymm_all[11]->Write();
  asymm_all[17]->Write();
  asymm_all[23]->Write();
  asymm_all[29]->Write();
  asymm_all[35]->Write();


  // write parton level distribution for reconstructed events
  asymm_all[44]->SetName("parton_recocuts");
  asymm_all[44]->Write();

  // Name rejected events per category (for the p-value calculation offline)
  asymm_all[45]->SetName("rejected_BcBc");
  asymm_all[46]->SetName("rejected_KcKc");
  asymm_all[47]->SetName("rejected_BcKc");
  asymm_all[48]->SetName("rejected_KcBc");
  asymm_all[49]->SetName("rejected_BcKc_same1");
  asymm_all[50]->SetName("rejected_BcKc_same2"); 

  asymm_all[51]->SetName("bkg_qq_rejected_BcBc");
  asymm_all[52]->SetName("bkg_qq_rejected_KcKc");
  asymm_all[53]->SetName("bkg_qq_rejected_BcKc");
  asymm_all[54]->SetName("bkg_qq_rejected_KcBc");
  asymm_all[55]->SetName("bkg_qq_rejected_BcKc_same1");
  asymm_all[56]->SetName("bkg_qq_rejected_BcKc_same2");

  asymm_all[57]->SetName("bkg_radreturn_rejected_BcBc");
  asymm_all[58]->SetName("bkg_radreturn_rejected_KcKc");
  asymm_all[59]->SetName("bkg_radreturn_rejected_BcKc");
  asymm_all[60]->SetName("bkg_radreturn_rejected_KcBc");
  asymm_all[61]->SetName("bkg_radreturn_rejected_BcKc_same1");
  asymm_all[62]->SetName("bkg_radreturn_rejected_BcKc_same2");
  
  for( int i=45; i<63; i++) asymm_all[i]->Write();
  
  
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


void observable::Analysis(int n_entries=-1, TString polarization="eL", int n=20, int cuts=3)
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
    
    
    if(fabs(mc_quark_pdg[0])==5 && bbmass>180) {
      bbbar_gen++;
      h_cos_parton->Fill(costheta_bbbar);
      h_cos_parton->Fill(-costheta_bbbar);
      
      costheta_bbbar=  (mc_quark_charge[0] < 0) ? costheta_bbbar: -costheta_bbbar;

      h_bbbar->Fill( costheta_bbbar );
    }

    
    if(PreSelectionTest(cuts)==false) continue; 
    preselection++;

    if(fabs(mc_quark_pdg[0])!=5) bkg++;
    
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
    
    /* costheta_BcBc=GetCostheta(p);
       costheta_KcKc=GetCostheta(p);
       costheta_BcKc=GetCostheta(p);
       costheta_KcBc=GetCostheta(p);
       costheta_BcKc_same1=GetCostheta(p);
       costheta_BcKc_same2=GetCostheta(p);*/

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

	if( fabs(mc_quark_pdg[0]==5) && bbmass>180)	{
	  h_resolution_BcBc->Fill(cos_truth,cos_reco_truth);
	  h_resolution_jettrack_BcBc->Fill(cos_truth,cos_trackreco_truth);

	  asymm_BcBc[0]->Fill(cos_reco);
	  asymm_BcBc[1]->Fill(cos_reco_truth);
	}

	if(fabs(mc_quark_pdg[0])!=5) {
	  asymm_BcBc[3]->Fill(cos_reco);
	  h_qq_BcBc_rejected->Fill(cos_reco);   
	}
	if(fabs(mc_quark_pdg[0])==5 && bbmass<180) {
	  asymm_BcBc[4]->Fill(cos_reco);
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

	if( fabs(mc_quark_pdg[0]==5) && bbmass>180)	{
	  h_resolution_KcKc->Fill(cos_truth,cos_reco_truth);
	  h_resolution_jettrack_KcKc->Fill(cos_truth,cos_trackreco_truth);
	  
	  asymm_KcKc[0]->Fill(cos_reco);
	  asymm_KcKc[1]->Fill(cos_reco_truth);
	}
	  
	if(fabs(mc_quark_pdg[0])!=5) {
	  asymm_KcKc[3]->Fill(cos_reco);
	  h_qq_KcKc_rejected->Fill(cos_reco);   
	}
	if(fabs(mc_quark_pdg[0])==5 && bbmass<180) {
	  asymm_KcKc[4]->Fill(cos_reco);
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
	
	if( fabs(mc_quark_pdg[0]==5) && bbmass>180)	{
	  h_resolution_BcKc->Fill(cos_truth,cos_reco_truth);
	  h_resolution_jettrack_BcKc->Fill(cos_truth,cos_trackreco_truth);

	  asymm_BcKc[0]->Fill(cos_reco);
	  asymm_BcKc[1]->Fill(cos_reco_truth);
	}
	  
	if(fabs(mc_quark_pdg[0])!=5) {
	  asymm_BcKc[3]->Fill(cos_reco);
	  h_qq_BcKc_rejected->Fill(cos_reco);   
	}
	if(fabs(mc_quark_pdg[0])==5 && bbmass<180) {
	  asymm_BcKc[4]->Fill(cos_reco);
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
	
	if( fabs(mc_quark_pdg[0]==5) && bbmass>180) {
	  h_resolution_KcBc->Fill(cos_truth,cos_reco_truth);
	  h_resolution_jettrack_KcBc->Fill(cos_truth,cos_trackreco_truth);

	  asymm_KcBc[0]->Fill(cos_reco);
	  asymm_KcBc[1]->Fill(cos_reco_truth);
	}
	
	if(fabs(mc_quark_pdg[0])!=5) {
	  asymm_KcBc[3]->Fill(cos_reco);
	  h_qq_KcBc_rejected->Fill(cos_reco);   
	}
	if(fabs(mc_quark_pdg[0])==5 && bbmass<180) {
	  asymm_KcBc[4]->Fill(cos_reco);
	  h_radreturn_KcBc_rejected->Fill(cos_reco);   
	}
	taken = true;
      }
    }
    
    // --------------------------------------------------------------------------
    // Same side 1
    //Information to calculate p, for BcKc category

    if(taken == false ) {
      
      if(Bc[0]*Kc[0]<0  ){
	h_bbbar_BcKc_same1_rejected->Fill( costheta_BcKc_same1);
	h_bbbar_BcKc_same1_rejected->Fill( -costheta_BcKc_same1);
      }
      
      if( Bc[0]*Kc[0]>0 && (Bc[1]==0 && Kc[1]==0) ) {
	
	if(Bc[0] < 0) h_bbbar_BcKc_same1_reco->Fill( costheta_BcKc_same1);
	else h_bbbar_BcKc_same1_reco->Fill( -costheta_BcKc_same1);
 	
	float cos_reco=  (Bc[0] < 0) ? costheta_BcKc_same1: -costheta_BcKc_same1;
	
	h_cos_charge_BcKc_same1->Fill(costheta_BcKc_same1);
	h_cos_charge_BcKc_same1->Fill(-costheta_BcKc_same1);
	bbbar_BcKc_same1_reco++;
	
	if( fabs(mc_quark_pdg[0]==5) && bbmass>180) {
	  h_resolution_BcKc_same1->Fill(cos_truth,cos_reco_truth);
	  h_resolution_jettrack_BcKc_same1->Fill(cos_truth,cos_trackreco_truth);
	  
	  asymm_BcKc_same1[0]->Fill(cos_reco);
	  asymm_BcKc_same1[1]->Fill(cos_reco_truth);
	}
	
	if(fabs(mc_quark_pdg[0])!=5) {
	  asymm_BcKc_same1[3]->Fill(cos_reco);
	  h_qq_BcKc_same1_rejected->Fill(cos_reco);   
	}
	if(fabs(mc_quark_pdg[0])==5 && bbmass<180) {
	  asymm_BcKc_same1[4]->Fill(cos_reco);
	  h_radreturn_BcKc_same1_rejected->Fill(cos_reco);   
	}
	
	taken = true;
      }
    }
    
    // --------------------------------------------------------------------------
    // Same side 2
    //Information to calculate p, for BcKc category
    
    if(taken == false) {      
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

	if( fabs(mc_quark_pdg[0]==5) && bbmass>180) {
	  h_resolution_BcKc_same2->Fill(cos_truth,cos_reco_truth);
	  h_resolution_jettrack_BcKc_same2->Fill(cos_truth,cos_trackreco_truth);

	  asymm_BcKc_same2[0]->Fill(cos_reco);
	  asymm_BcKc_same2[1]->Fill(cos_reco_truth);
	}
	  
	if(fabs(mc_quark_pdg[0])!=5) {
	  asymm_BcKc_same2[3]->Fill(cos_reco);
	  h_qq_BcKc_same2_rejected->Fill(cos_reco);   
	}
	if(fabs(mc_quark_pdg[0])==5 && bbmass<180) {
	  asymm_BcKc_same2[4]->Fill(cos_reco);
	  h_radreturn_BcKc_same2_rejected->Fill(cos_reco);   
	}
	
	taken = true;
      }
    }
    if(taken==true &&	fabs(mc_quark_pdg[0])==5 && bbmass>180 ) h_bbbar_recocuts->Fill(costheta_bbbar);
          
  }//end loop


  // ***************************************************************  

  CoutEfficiencies();
  HistoEfficiencies();
  TH1F * p_b_histo = MakeCorrection("BcBc",h_bbbar_BcBc_reco,h_bbbar_BcBc_rejected);
  TH1F * p_k_histo = MakeCorrection("KcKc",h_bbbar_KcKc_reco,h_bbbar_KcKc_rejected);
  TH1F * p_bk_histo = MakeCorrection("BcKc",h_bbbar_BcKc_reco,h_bbbar_BcKc_rejected);
  TH1F * p_kb_histo = MakeCorrection("KcBc",h_bbbar_KcBc_reco,h_bbbar_KcBc_rejected);
  TH1F * p_bk_same1_histo = MakeCorrection("BcKc_same1",h_bbbar_BcKc_same1_reco,h_bbbar_BcKc_same1_rejected);
  TH1F * p_bk_same2_histo = MakeCorrection("BcKc_same2",h_bbbar_BcKc_same2_reco,h_bbbar_BcKc_same2_rejected);

  // ***************************************************************  

  std::vector<TH1F*> result;
  result.push_back(asymm_BcBc[0]);//reco
  result.push_back(asymm_BcBc[1]);//truth
  result.push_back(asymm_BcBc[2]);//corrected
  result.push_back(asymm_BcBc[3]);//bkg_qq
  result.push_back(asymm_BcBc[4]);//bkg_radreturn
  result.push_back(p_b_histo);

  result.push_back(asymm_KcKc[0]);//reco
  result.push_back(asymm_KcKc[1]);//truth
  result.push_back(asymm_KcKc[2]);//corrected
  result.push_back(asymm_KcKc[3]);//bkg_qq
  result.push_back(asymm_KcKc[4]);//bkg_radreturn
  result.push_back(p_k_histo);

  result.push_back(asymm_BcKc[0]);//reco
  result.push_back(asymm_BcKc[1]);//truth
  result.push_back(asymm_BcKc[2]);//corrected
  result.push_back(asymm_BcKc[3]);//bkg_qq
  result.push_back(asymm_BcKc[4]);//bkg_radreturn
  result.push_back(p_bk_histo);

  result.push_back(asymm_KcBc[0]);//reco
  result.push_back(asymm_KcBc[1]);//truth
  result.push_back(asymm_KcBc[2]);//corrected
  result.push_back(asymm_KcBc[3]);//bkg_qq
  result.push_back(asymm_KcBc[4]);//bkg_radreturn
  result.push_back(p_kb_histo);

  result.push_back(asymm_BcKc_same1[0]);//reco
  result.push_back(asymm_BcKc_same1[1]);//truth
  result.push_back(asymm_BcKc_same1[2]);//corrected
  result.push_back(asymm_BcKc_same1[3]);//bkg_qq
  result.push_back(asymm_BcKc_same1[4]);//bkg_radreturn
  result.push_back(p_bk_same1_histo);

  result.push_back(asymm_BcKc_same2[0]);//reco
  result.push_back(asymm_BcKc_same2[1]);//truth
  result.push_back(asymm_BcKc_same2[2]);//corrected
  result.push_back(asymm_BcKc_same2[3]);//bkg_qq
  result.push_back(asymm_BcKc_same2[4]);//bkg_radreturn
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



void observable::AnalysisBKG(int n_entries=-1, TString polarization="eL", int n=20, int cuts=3)
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

    
    if(PreSelectionTest(cuts)==false) continue; 
    preselection++;

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
   


    bool taken = false;
    bool rejected = false;

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
    if(taken == false) {
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
    if(taken == false) {
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


/*
  void observable::Selection(int n_entries=-1)
  {

  //  gROOT->Reset();
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleX(0.2);
  //gStyle->SetTitleY(0.92);
  gStyle->SetTitleStyle(0);
  //gStyle->SetTitleFontSize(0.03);
  gStyle->SetMarkerSize(0.3);
       
  bbbar_gen=0;
  bbbar_gen_radreturn=0;
  qqbar_gen=0;

  TH1F * h_mjj_bb = new TH1F("h_mjj_bb","h_mjj_bb",100,0,500);
  TH1F * h_egamma_bb = new TH1F("h_egamma_bb","h_egamma_bb",100,0,500);
  TH2F * h_btag1_btag2_bb = new TH2F("h_btag1_btag2_bb","h_btag1_btag2_bb",100,0,1,100,0,1);
  TH2F * h_mj1_mj2_bb = new TH2F("h_mj1_mj2_bb","h_mj1_mj2_bb",100,0,500,100,0,500);
  TH2F * h_pj1_pj2_bb = new TH2F("h_pj1_pj2_bb","h_pj1_pj2_bb",100,0,500,100,0,500);

  TH1F * h_mjj_radreturn = new TH1F("h_mjj_radreturn","h_mjj_radreturn",100,0,500);
  TH1F * h_egamma_radreturn = new TH1F("h_egamma_radreturn","h_egamma_radreturn",100,0,500);
  TH2F * h_btag1_btag2_radreturn = new TH2F("h_btag1_btag2_radreturn","h_btag1_btag2_radreturn",100,0,1,100,0,1);
  TH2F * h_mj1_mj2_radreturn = new TH2F("h_mj1_mj2_radreturn","h_mj1_mj2_radreturn",100,0,500,100,0,500);
  TH2F * h_pj1_pj2_radreturn = new TH2F("h_pj1_pj2_radreturn","h_pj1_pj2_radreturn",100,0,500,100,0,500);

  TH1F * h_mjj_qq = new TH1F("h_mjj_qq","h_mjj_qq",100,0,500);
  TH1F * h_egamma_qq = new TH1F("h_egamma_qq","h_egamma_qq",100,0,500);
  TH2F * h_btag1_btag2_qq = new TH2F("h_btag1_btag2_qq","h_btag1_btag2_qq",100,0,1,100,0,1);
  TH2F * h_mj1_mj2_qq = new TH2F("h_mj1_mj2_qq","h_mj1_mj2_qq",100,0,500,100,0,500);
  TH2F * h_pj1_pj2_qq = new TH2F("h_pj1_pj2_qq","h_pj1_pj2_qq",100,0,500,100,0,500);

  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;

  if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;
  if(PreSelection()==false) continue; 

  double reco_b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
  double reco_b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
  double reco_bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));
  double bbmass= sqrt(pow(mc_quark_E[0]+mc_quark_E[1],2)-pow(mc_quark_px[0]+mc_quark_px[1],2)-pow(mc_quark_py[0]+mc_quark_py[1],2)-pow(mc_quark_pz[0]+mc_quark_pz[1],2));

  double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
  double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

  double jj_pT= sqrt(pow(jet_px[0]+jet_px[1],2)+pow(jet_py[0]+jet_py[1],2));
    
  if(abs(mc_quark_pdg[0])==5 && bbmass>180) {
  h_mjj_bb->Fill(reco_bbmass);
  h_egamma_bb->Fill(maxenergy_photon_E);
  h_btag1_btag2_bb->Fill(jet_btag[0],jet_btag[1]);
  h_mj1_mj2_bb->Fill(reco_b1mass,reco_b2mass);
  h_pj1_pj2_bb->Fill(jet0_p,jet1_p);
  }
  if(abs(mc_quark_pdg[0])==5 && bbmass<180) {
  h_mjj_radreturn->Fill(reco_bbmass);
  h_egamma_radreturn->Fill(maxenergy_photon_E);
  h_btag1_btag2_radreturn->Fill(jet_btag[0],jet_btag[1]);
  h_mj1_mj2_radreturn->Fill(reco_b1mass,reco_b2mass);
  h_pj1_pj2_radreturn->Fill(jet0_p,jet1_p);
  }
  if(abs(mc_quark_pdg[0])!=5) {
  h_mjj_qq->Fill(reco_bbmass);
  h_egamma_qq->Fill(maxenergy_photon_E);
  h_btag1_btag2_qq->Fill(jet_btag[0],jet_btag[1]);
  h_mj1_mj2_qq->Fill(reco_b1mass,reco_b2mass);
  h_pj1_pj2_qq->Fill(jet0_p,jet1_p);
  }
    
  }

  TCanvas *canvas = new TCanvas("selection","selection",1000,1600);
  canvas->Divide(2,3);
  canvas->cd(1);
  h_mjj_qq->SetLineColor(1);
  h_mjj_qq->DrawNormalized("histo");
  h_mjj_bb->SetLineColor(2);
  h_mjj_bb->DrawNormalized("histosame");
  h_mjj_radreturn->SetLineColor(4);
  h_mjj_radreturn->DrawNormalized("histosame");

  canvas->cd(2);
  h_egamma_qq->SetLineColor(1);
  h_egamma_qq->DrawNormalized("histo");
  h_egamma_bb->SetLineColor(2);
  h_egamma_bb->DrawNormalized("histosame");
  h_egamma_radreturn->SetLineColor(4);
  h_egamma_radreturn->DrawNormalized("histosame");


  canvas->cd(3);
  h_mj1_mj2_qq->SetMarkerColor(1);
  h_mj1_mj2_qq->Draw("p");
  h_mj1_mj2_bb->SetMarkerColor(2);
  h_mj1_mj2_bb->Draw("psame");
  h_mj1_mj2_radreturn->SetMarkerColor(4);
  h_mj1_mj2_radreturn->Draw("psame");


  canvas->cd(4);
  h_btag1_btag2_qq->SetMarkerColor(1);
  h_btag1_btag2_qq->Draw("p");
  h_btag1_btag2_radreturn->SetMarkerColor(4);
  h_btag1_btag2_radreturn->Draw("psame");
  h_btag1_btag2_bb->SetMarkerColor(2);
  h_btag1_btag2_bb->Draw("psame");


  canvas->cd(5);
  h_pj1_pj2_qq->SetMarkerColor(1);
  h_pj1_pj2_qq->Draw("p");
  h_pj1_pj2_bb->SetMarkerColor(2);
  h_pj1_pj2_bb->Draw("psame");
  h_pj1_pj2_radreturn->SetMarkerColor(4);
  h_pj1_pj2_radreturn->Draw("psame");

   
  }*/


void observable::Selection(int n_entries=-1, int selection_type=0, TString polarization="eL")
{
  
  TFile *MyFile = new TFile(TString::Format("selection_%s_250GeV_%s_btag1_%0.1f_btag2_%0.1f.root",process.Data(),polarization.Data(),btag1,btag2),"RECREATE");
  MyFile->cd();
  
  //  gROOT->Reset();
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleX(0.2);
  //gStyle->SetTitleY(0.92);
  gStyle->SetTitleStyle(0);
  //gStyle->SetTitleFontSize(0.03);
  gStyle->SetMarkerSize(0.3);
       
  bbbar_gen=0;
  bbbar_gen_radreturn=0;
  qqbar_gen=0;

  TH1F * h_mjj_bb = new TH1F("h_mjj_bb","h_mjj_bb",100,0,500);
  TH1F * h_mjj_radreturn = new TH1F("h_mjj_radreturn","h_mjj_radreturn",100,0,500);
  TH1F * h_mjj_qq = new TH1F("h_mjj_qq","h_mjj_qq",100,0,500);
  
  TH1F * h_egamma_bb = new TH1F("h_egamma_bb","h_egamma_bb",100,0,500);
  TH1F * h_egamma_radreturn = new TH1F("h_egamma_radreturn","h_egamma_radreturn",100,0,500);
  TH1F * h_egamma_qq = new TH1F("h_egamma_qq","h_egamma_qq",100,0,500);

  TH1F * h_mj1_mj2_bb = new TH1F("h_mj1_mj2_bb","h_mj1_mj2_bb",100,0,500);
  TH1F * h_mj1_mj2_radreturn = new TH1F("h_mj1_mj2_radreturn","h_mj1_mj2_radreturn",100,0,500);
  TH1F * h_mj1_mj2_qq = new TH1F("h_mj1_mj2_qq","h_mj1_mj2_qq",100,0,500);

  TH1F * h_pj1_pj2_bb = new TH1F("h_pj1_pj2_bb","h_pj1_pj2_bb",100,0,500);
  TH1F * h_pj1_pj2_radreturn = new TH1F("h_pj1_pj2_radreturn","h_pj1_pj2_radreturn",100,0,500);
  TH1F * h_pj1_pj2_qq = new TH1F("h_pj1_pj2_qq","h_pj1_pj2_qq",100,0,500);

  //jet variables
  TH1F * h_d23_bb = new TH1F("h_d23_bb","h_d23_bb",100,0,500);
  TH1F * h_d23_radreturn = new TH1F("h_d23_radreturn","h_d23_radreturn",100,0,500);
  TH1F * h_d23_qq = new TH1F("h_d23_qq","h_d23_qq",100,0,500);

  TH1F * h_d12_bb = new TH1F("h_d12_bb","h_d12_bb",100,0,100000);
  TH1F * h_d12_radreturn = new TH1F("h_d12_radreturn","h_d12_radreturn",100,0,100000);
  TH1F * h_d12_qq = new TH1F("h_d12_qq","h_d12_qq",100,0,100000);

  TH1F * h_y23_bb = new TH1F("h_y23_bb","h_y23_bb",100,0,0.35);
  TH1F * h_y23_radreturn = new TH1F("h_y23_radreturn","h_y23_radreturn",100,0,0.35);
  TH1F * h_y23_qq = new TH1F("h_y23_qq","h_y23_qq",100,0,0.35);

  TH1F * h_y12_bb = new TH1F("h_y12_bb","h_y12_bb",100,0,1);
  TH1F * h_y12_radreturn = new TH1F("h_y12_radreturn","h_y12_radreturn",100,0,1);
  TH1F * h_y12_qq = new TH1F("h_y12_qq","h_y12_qq",100,0,1);

  //EVENT SHAPE variables
  TH1F * h_oblateness_bb = new TH1F("h_oblateness_bb","h_oblateness_bb",100,0,0.8);
  TH1F * h_oblateness_radreturn = new TH1F("h_oblateness_radreturn","h_oblateness_radreturn",100,0,0.8);
  TH1F * h_oblateness_qq = new TH1F("h_oblateness_qq","h_oblateness_qq",100,0,0.8);

  TH1F * h_aplanarity_bb = new TH1F("h_aplanarity_bb","h_aplanarity_bb",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_radreturn = new TH1F("h_aplanarity_radreturn","h_aplanarity_radreturn",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_qq = new TH1F("h_aplanarity_qq","h_aplanarity_qq",100,-0.4e-6,0.4e-6);

  TH1F * h_sphericity_bb = new TH1F("h_sphericity_bb","h_sphericity_bb",100,0,0.8);
  TH1F * h_sphericity_radreturn = new TH1F("h_sphericity_radreturn","h_sphericity_radreturn",100,0,0.8);
  TH1F * h_sphericity_qq = new TH1F("h_sphericity_qq","h_sphericity_qq",100,0,0.8);
  
  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  int bb_counter=0, radreturn_counter=0, qq_counter=0;
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    double bbmass= sqrt(pow(mc_quark_E[0]+mc_quark_E[1],2)-pow(mc_quark_px[0]+mc_quark_px[1],2)-pow(mc_quark_py[0]+mc_quark_py[1],2)-pow(mc_quark_pz[0]+mc_quark_pz[1],2));
    if(abs(mc_quark_pdg[0])==5 && bbmass>180) bb_counter++;
    if(abs(mc_quark_pdg[0])==5 && bbmass<180) radreturn_counter++;
    if(abs(mc_quark_pdg[0])!=5) qq_counter++;


    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;
    bool selection=PreSelectionTest(selection_type);
    if(selection==false) continue; 

    double reco_b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
    double reco_b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
    double reco_bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

    double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
    double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

    double jj_pT= sqrt(pow(jet_px[0]+jet_px[1],2)+pow(jet_py[0]+jet_py[1],2));
    
    if(abs(mc_quark_pdg[0])==5 && bbmass>180) {
      h_mjj_bb->Fill(reco_bbmass);
      h_egamma_bb->Fill(maxenergy_photon_E);
      h_mj1_mj2_bb->Fill(reco_b1mass+reco_b2mass);
      h_pj1_pj2_bb->Fill(jet0_p+jet1_p);
      h_d23_bb->Fill(d23);
      h_d12_bb->Fill(d12);
      h_y23_bb->Fill(y23);
      h_y12_bb->Fill(y12);
      h_oblateness_bb->Fill(oblateness);
      h_aplanarity_bb->Fill(aplanarity);
      h_sphericity_bb->Fill(sphericity);
    }
    
    if(abs(mc_quark_pdg[0])==5 && bbmass<180) {
      h_mjj_radreturn->Fill(reco_bbmass);
      h_egamma_radreturn->Fill(maxenergy_photon_E);
      h_mj1_mj2_radreturn->Fill(reco_b1mass+reco_b2mass);
      h_pj1_pj2_radreturn->Fill(jet0_p+jet1_p);
      h_d23_radreturn->Fill(d23);
      h_d12_radreturn->Fill(d12);
      h_y23_radreturn->Fill(y23);
      h_y12_radreturn->Fill(y12);
      h_oblateness_radreturn->Fill(oblateness);
      h_aplanarity_radreturn->Fill(aplanarity);
      h_sphericity_radreturn->Fill(sphericity);
    }
    if(abs(mc_quark_pdg[0])!=5) {
      h_mjj_qq->Fill(reco_bbmass);
      h_egamma_qq->Fill(maxenergy_photon_E);
      h_mj1_mj2_qq->Fill(reco_b1mass+reco_b2mass);
      h_pj1_pj2_qq->Fill(jet0_p+jet1_p);
      h_d23_qq->Fill(d23);
      h_d12_qq->Fill(d12);
      h_y23_qq->Fill(y23);
      h_y12_qq->Fill(y12);
      h_oblateness_qq->Fill(oblateness);
      h_aplanarity_qq->Fill(aplanarity);
      h_sphericity_qq->Fill(sphericity);
    }
    
  }
  cout<<TString::Format("selection_%s_250GeV_%s_btag1_%0.1f_btag2_%0.1f.root",process.Data(),polarization.Data(),btag1,btag2)<<endl;
  cout<<" Total generated bbbar events: " << bb_counter<<endl;
  cout<<" Total generated Z-radreturn events: " <<radreturn_counter<<endl;
  cout<<" Total generated qqbar events: " << qq_counter<<endl;

  // save histograms
  h_mjj_bb->Write();
  h_mjj_qq->Write();
  h_mjj_radreturn->Write();

  h_egamma_bb->Write();
  h_egamma_qq->Write();
  h_egamma_radreturn->Write();

  h_mj1_mj2_bb->Write();
  h_mj1_mj2_qq->Write();
  h_mj1_mj2_radreturn->Write();

  h_pj1_pj2_bb->Write();
  h_pj1_pj2_qq->Write();
  h_pj1_pj2_radreturn->Write();

  h_d23_bb->Write();
  h_d23_qq->Write();
  h_d23_radreturn->Write();

  h_d12_bb->Write();
  h_d12_qq->Write();
  h_d12_radreturn->Write();

  h_y23_bb->Write();
  h_y23_qq->Write();
  h_y23_radreturn->Write();

  h_y12_bb->Write();
  h_y12_qq->Write();
  h_y12_radreturn->Write();

  h_oblateness_bb->Write();
  h_oblateness_qq->Write();
  h_oblateness_radreturn->Write();

  h_aplanarity_bb->Write();
  h_aplanarity_qq->Write();
  h_aplanarity_radreturn->Write();

  h_sphericity_bb->Write();
  h_sphericity_qq->Write();
  h_sphericity_radreturn->Write();

  // plot histograms
  
  TCanvas *canvas = new TCanvas("selection","selection",1600,800);
  canvas->Divide(4,2);
  canvas->cd(1);
  h_mjj_bb->SetLineColor(2);
  h_mjj_bb->Draw("histo");
  h_mjj_qq->SetLineColor(1);
  h_mjj_qq->Draw("histosame");
  h_mjj_radreturn->SetLineColor(4);
  h_mjj_radreturn->Draw("histosame");

  canvas->cd(2);
  h_egamma_bb->SetLineColor(2);
  h_egamma_bb->Draw("histo");
  h_egamma_qq->SetLineColor(1);
  h_egamma_qq->Draw("histosame");
  h_egamma_radreturn->SetLineColor(4);
  h_egamma_radreturn->Draw("histosame");

  canvas->cd(3);
  h_mj1_mj2_bb->SetLineColor(2);
  h_mj1_mj2_bb->Draw("histo");
  h_mj1_mj2_qq->SetLineColor(1);
  h_mj1_mj2_qq->Draw("histosame");
  h_mj1_mj2_radreturn->SetLineColor(4);
  h_mj1_mj2_radreturn->Draw("histosame");

  canvas->cd(4);
  h_pj1_pj2_bb->SetLineColor(2);
  h_pj1_pj2_bb->Draw("histo");
  h_pj1_pj2_qq->SetLineColor(1);
  h_pj1_pj2_qq->Draw("histosame");
  h_pj1_pj2_radreturn->SetLineColor(4);
  h_pj1_pj2_radreturn->Draw("histosame");

  canvas->cd(5);
  h_mjj_bb->SetLineColor(2);
  h_mjj_bb->DrawNormalized("histo");
  h_mjj_qq->SetLineColor(1);
  h_mjj_qq->DrawNormalized("histosame");
  h_mjj_radreturn->SetLineColor(4);
  h_mjj_radreturn->DrawNormalized("histosame");

  canvas->cd(6);
  h_egamma_bb->SetLineColor(2);
  h_egamma_bb->DrawNormalized("histo");
  h_egamma_qq->SetLineColor(1);
  h_egamma_qq->DrawNormalized("histosame");
  h_egamma_radreturn->SetLineColor(4);
  h_egamma_radreturn->DrawNormalized("histosame");

  canvas->cd(7);
  h_mj1_mj2_bb->SetLineColor(2);
  h_mj1_mj2_bb->DrawNormalized("histo");
  h_mj1_mj2_qq->SetLineColor(1);
  h_mj1_mj2_qq->DrawNormalized("histosame");
  h_mj1_mj2_radreturn->SetLineColor(4);
  h_mj1_mj2_radreturn->DrawNormalized("histosame");

  canvas->cd(8);
  h_pj1_pj2_bb->SetLineColor(2);
  h_pj1_pj2_bb->DrawNormalized("histo");
  h_pj1_pj2_qq->SetLineColor(1);
  h_pj1_pj2_qq->DrawNormalized("histosame");
  h_pj1_pj2_radreturn->SetLineColor(4);
  h_pj1_pj2_radreturn->DrawNormalized("histosame");


  TCanvas *canvas_2 = new TCanvas("selection_jetvariables","selection_jetvariables",1600,800);
  canvas_2->Divide(4,2);
  canvas_2->cd(1);
  h_d23_bb->SetLineColor(2);
  h_d23_bb->Draw("histo");
  h_d23_qq->SetLineColor(1);
  h_d23_qq->Draw("histosame");
  h_d23_radreturn->SetLineColor(4);
  h_d23_radreturn->Draw("histosame");

  canvas_2->cd(2);
  h_d12_bb->SetLineColor(2);
  h_d12_bb->Draw("histo");
  h_d12_qq->SetLineColor(1);
  h_d12_qq->Draw("histosame");
  h_d12_radreturn->SetLineColor(4);
  h_d12_radreturn->Draw("histosame");

  canvas_2->cd(3);
  h_y23_bb->SetLineColor(2);
  h_y23_bb->Draw("histo");
  h_y23_qq->SetLineColor(1);
  h_y23_qq->Draw("histosame");
  h_y23_radreturn->SetLineColor(4);
  h_y23_radreturn->Draw("histosame");

  canvas_2->cd(4);
  h_y12_bb->SetLineColor(2);
  h_y12_bb->Draw("histo");
  h_y12_qq->SetLineColor(1);
  h_y12_qq->Draw("histosame");
  h_y12_radreturn->SetLineColor(4);
  h_y12_radreturn->Draw("histosame");

  canvas_2->cd(5);
  h_d23_bb->SetLineColor(2);
  h_d23_bb->DrawNormalized("histo");
  h_d23_qq->SetLineColor(1);
  h_d23_qq->DrawNormalized("histosame");
  h_d23_radreturn->SetLineColor(4);
  h_d23_radreturn->DrawNormalized("histosame");

  canvas_2->cd(6);
  h_d12_bb->SetLineColor(2);
  h_d12_bb->DrawNormalized("histo");
  h_d12_qq->SetLineColor(1);
  h_d12_qq->DrawNormalized("histosame");
  h_d12_radreturn->SetLineColor(4);
  h_d12_radreturn->DrawNormalized("histosame");

  canvas_2->cd(7);
  h_y23_bb->SetLineColor(2);
  h_y23_bb->DrawNormalized("histo");
  h_y23_qq->SetLineColor(1);
  h_y23_qq->DrawNormalized("histosame");
  h_y23_radreturn->SetLineColor(4);
  h_y23_radreturn->DrawNormalized("histosame");

  canvas_2->cd(8);
  h_y12_bb->SetLineColor(2);
  h_y12_bb->DrawNormalized("histo");
  h_y12_qq->SetLineColor(1);
  h_y12_qq->DrawNormalized("histosame");
  h_y12_radreturn->SetLineColor(4);
  h_y12_radreturn->DrawNormalized("histosame");

  TCanvas *canvas_3 = new TCanvas("selection_eventshapes_variables","selection_eventshapes_variables",1600,800);
  canvas_3->Divide(3,2);
  canvas_3->cd(1);
  h_oblateness_bb->SetLineColor(2);
  h_oblateness_bb->Draw("histo");
  h_oblateness_qq->SetLineColor(1);
  h_oblateness_qq->Draw("histosame");
  h_oblateness_radreturn->SetLineColor(4);
  h_oblateness_radreturn->Draw("histosame");

  canvas_3->cd(2);
  h_aplanarity_bb->SetLineColor(2);
  h_aplanarity_bb->Draw("histo");
  h_aplanarity_qq->SetLineColor(1);
  h_aplanarity_qq->Draw("histosame");
  h_aplanarity_radreturn->SetLineColor(4);
  h_aplanarity_radreturn->Draw("histosame");

  canvas_3->cd(3);
  h_sphericity_bb->SetLineColor(2);
  h_sphericity_bb->Draw("histo");
  h_sphericity_qq->SetLineColor(1);
  h_sphericity_qq->Draw("histosame");
  h_sphericity_radreturn->SetLineColor(4);
  h_sphericity_radreturn->Draw("histosame");

  canvas_3->cd(4);
  h_oblateness_bb->SetLineColor(2);
  h_oblateness_bb->DrawNormalized("histo");
  h_oblateness_qq->SetLineColor(1);
  h_oblateness_qq->DrawNormalized("histosame");
  h_oblateness_radreturn->SetLineColor(4);
  h_oblateness_radreturn->DrawNormalized("histosame");

  canvas_3->cd(5);
  h_aplanarity_bb->SetLineColor(2);
  h_aplanarity_bb->DrawNormalized("histo");
  h_aplanarity_qq->SetLineColor(1);
  h_aplanarity_qq->DrawNormalized("histosame");
  h_aplanarity_radreturn->SetLineColor(4);
  h_aplanarity_radreturn->DrawNormalized("histosame");

  canvas_3->cd(6);
  h_sphericity_bb->SetLineColor(2);
  h_sphericity_bb->DrawNormalized("histo");
  h_sphericity_qq->SetLineColor(1);
  h_sphericity_qq->DrawNormalized("histosame");
  h_sphericity_radreturn->SetLineColor(4);
  h_sphericity_radreturn->DrawNormalized("histosame");
 

   
}


void observable::SelectionBKG(int n_entries=-1, int selection_type=0, TString polarization="eL")
{
  TFile *MyFile = new TFile(TString::Format("selection_%s_250GeV_%s_btag1_%0.1f_btag2_%0.1f.root",process.Data(),polarization.Data(),btag1,btag2),"RECREATE");
  MyFile->cd();

  //  gROOT->Reset();
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleX(0.2);
  //gStyle->SetTitleY(0.92);
  gStyle->SetTitleStyle(0);
  //gStyle->SetTitleFontSize(0.03);
  gStyle->SetMarkerSize(0.3);
       
  bbbar_gen=0;
  bbbar_gen_radreturn=0;
  qqbar_gen=0;

  TH1F * h_mjj_bb = new TH1F("h_mjj_bb","h_mjj_bb",100,0,500);
  TH1F * h_egamma_bb = new TH1F("h_egamma_bb","h_egamma_bb",100,0,500);
  TH1F * h_mj1_mj2_bb = new TH1F("h_mj1_mj2_bb","h_mj1_mj2_bb",100,0,500);
  TH1F * h_pj1_pj2_bb = new TH1F("h_pj1_pj2_bb","h_pj1_pj2_bb",100,0,500);

  //jet variables
  TH1F * h_d23_bb = new TH1F("h_d23_bb","h_d23_bb",100,0,50000);
  TH1F * h_d12_bb = new TH1F("h_d12_bb","h_d12_bb",100,0,100000);
  TH1F * h_y23_bb = new TH1F("h_y23_bb","h_y23_bb",100,0,0.35);
  TH1F * h_y12_bb = new TH1F("h_y12_bb","h_y12_bb",100,0,1);

  //EVENT SHAPE variables
  TH1F * h_oblateness_bb = new TH1F("h_oblateness_bb","h_oblateness_bb",100,0,0.8);
  TH1F * h_aplanarity_bb = new TH1F("h_aplanarity_bb","h_aplanarity_bb",100,-0.4e-6,0.4e-6);
  TH1F * h_sphericity_bb = new TH1F("h_sphericity_bb","h_sphericity_bb",100,0,0.8);
  
  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  int counter=0;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    counter++;
    bool selection=PreSelectionTest(selection_type);
    if(selection==false) continue; 

    double reco_b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
    double reco_b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
    double reco_bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));
    double bbmass= sqrt(pow(mc_quark_E[0]+mc_quark_E[1],2)-pow(mc_quark_px[0]+mc_quark_px[1],2)-pow(mc_quark_py[0]+mc_quark_py[1],2)-pow(mc_quark_pz[0]+mc_quark_pz[1],2));

    double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
    double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

    double jj_pT= sqrt(pow(jet_px[0]+jet_px[1],2)+pow(jet_py[0]+jet_py[1],2));
    
    h_mjj_bb->Fill(reco_bbmass);
    h_egamma_bb->Fill(maxenergy_photon_E);
    h_mj1_mj2_bb->Fill(reco_b1mass+reco_b2mass);
    h_pj1_pj2_bb->Fill(jet0_p+jet1_p);
    h_d23_bb->Fill(d23);
    h_d12_bb->Fill(d12);
    h_y23_bb->Fill(y23);
    h_y12_bb->Fill(y12);
    h_oblateness_bb->Fill(oblateness);
    h_aplanarity_bb->Fill(aplanarity);
    h_sphericity_bb->Fill(sphericity);

     
  }

  cout<<  TString::Format("selection_%s_250GeV_%s_btag1_%0.1f_btag2_%0.1f.root",process.Data(),polarization.Data(),btag1,btag2)<<endl;
  cout<<" Total generated events: " << counter<<endl;

  // save histograms
  h_mjj_bb->Write();
  h_egamma_bb->Write();
  h_mj1_mj2_bb->Write();
  h_pj1_pj2_bb->Write();

  h_d23_bb->Write();
  h_d12_bb->Write();
  h_y23_bb->Write();
  h_y12_bb->Write();

  h_oblateness_bb->Write();
  h_aplanarity_bb->Write();
  h_sphericity_bb->Write();

  
  TCanvas *canvas = new TCanvas("selection_bkg","selection_bkg",1600,800);
  canvas->Divide(4,2);
  canvas->cd(1);
  h_mjj_bb->SetLineColor(2);
  h_mjj_bb->Draw("histo");

  canvas->cd(2);
  h_egamma_bb->SetLineColor(2);
  h_egamma_bb->Draw("histo");
 
  canvas->cd(3);
  h_mj1_mj2_bb->SetLineColor(2);
  h_mj1_mj2_bb->Draw("histo");

  canvas->cd(4);
  h_pj1_pj2_bb->SetLineColor(2);
  h_pj1_pj2_bb->Draw("histo");
 
  canvas->cd(5);
  h_mjj_bb->SetLineColor(2);
  h_mjj_bb->DrawNormalized("histo");

  canvas->cd(6);
  h_egamma_bb->SetLineColor(2);
  h_egamma_bb->DrawNormalized("histo");
 
  canvas->cd(7);
  h_mj1_mj2_bb->SetLineColor(2);
  h_mj1_mj2_bb->DrawNormalized("histo");

  canvas->cd(8);
  h_pj1_pj2_bb->SetLineColor(2);
  h_pj1_pj2_bb->DrawNormalized("histo");


  TCanvas *canvas_2 = new TCanvas("selection_bkg_jetvariables","selection_bkg_jetvariables",1600,800);
  canvas_2->Divide(4,2);
  canvas_2->cd(1);
  h_d23_bb->SetLineColor(2);
  h_d23_bb->Draw("histo");

  canvas_2->cd(2);
  h_d12_bb->SetLineColor(2);
  h_d12_bb->Draw("histo");

  canvas_2->cd(3);
  h_y23_bb->SetLineColor(2);
  h_y23_bb->Draw("histo");

  canvas_2->cd(4);
  h_y12_bb->SetLineColor(2);
  h_y12_bb->Draw("histo");

  canvas_2->cd(5);
  h_d23_bb->SetLineColor(2);
  h_d23_bb->DrawNormalized("histo");

  canvas_2->cd(6);
  h_d12_bb->SetLineColor(2);
  h_d12_bb->DrawNormalized("histo");

  canvas_2->cd(7);
  h_y23_bb->SetLineColor(2);
  h_y23_bb->DrawNormalized("histo");

  canvas_2->cd(8);
  h_y12_bb->SetLineColor(2);
  h_y12_bb->DrawNormalized("histo");

  TCanvas *canvas_3 = new TCanvas("selection_bkg_eventshapes_variables","selection_bkg_eventshapes_variables",1600,800);
  canvas_3->Divide(3,2);
  canvas_3->cd(1);
  h_oblateness_bb->SetLineColor(2);
  h_oblateness_bb->Draw("histo");

  canvas_3->cd(2);
  h_aplanarity_bb->SetLineColor(2);
  h_aplanarity_bb->Draw("histo");

  canvas_3->cd(3);
  h_sphericity_bb->SetLineColor(2);
  h_sphericity_bb->Draw("histo");

  canvas_3->cd(4);
  h_oblateness_bb->SetLineColor(2);
  h_oblateness_bb->DrawNormalized("histo");

  canvas_3->cd(5);
  h_aplanarity_bb->SetLineColor(2);
  h_aplanarity_bb->DrawNormalized("histo");

  canvas_3->cd(6);
  h_sphericity_bb->SetLineColor(2);
  h_sphericity_bb->DrawNormalized("histo");
 

   
}


void observable::AngularDistributions(int n_entries=-1,  TString polarization="eL")
{
  
  TFile *MyFile = new TFile(TString::Format("angular_%s_250GeV_%s_btag1_%0.1f_btag2_%0.1f.root",process.Data(),polarization.Data(),btag1,btag2),"RECREATE");
  MyFile->cd();
  
  //  gROOT->Reset();
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  //gStyle->SetTitleX(0.2);
  //gStyle->SetTitleY(0.92);
  gStyle->SetTitleStyle(0);
  //gStyle->SetTitleFontSize(0.03);
  gStyle->SetMarkerSize(0.3);
       
  bbbar_gen=0;
  bbbar_gen_radreturn=0;
  qqbar_gen=0;

  TH1F * h_cos_b = new TH1F("h_cos_b","h_cos_b",160,-1,1);
  TH1F * h_cos_q = new TH1F("h_cos_q","h_cos_q",160,-1,1);
  
  //--------------------------------------------------------------------------------------------------------
  TH1F * h_cos_track_0 = new TH1F("h_cos_track_0","h_cos_track_0",160,-1,1);
  TH2F * h_cos_track_jet_0 = new TH2F("h_cos_track_jet_0","h_cos_track_jet_0",160,-1,1,40,-0.2,0.2);
  TH1F * h_cos_track_2 = new TH1F("h_cos_track_2","h_cos_track_2",160,-1,1);
  TH2F * h_cos_track_jet_2 = new TH2F("h_cos_track_jet_2","h_cos_track_jet_2",160,-1,1,40,-0.2,0.2);
  TH1F * h_cos_track_4 = new TH1F("h_cos_track_4","h_cos_track_4",160,-1,1);
  TH2F * h_cos_track_jet_4 = new TH2F("h_cos_track_jet_4","h_cos_track_jet_4",160,-1,1,40,-0.2,0.2);

  //--------------------------------------------------------------------------------------------------------
  TH1F * h_btag_cos_track_0 = new TH1F("h_btag_cos_track_0","h_btag_cos_track_0",160,-1,1);
  TH2F * h_btag_cos_track_jet_0 = new TH2F("h_btag_cos_track_jet_0","h_btag_cos_track_jet_0",160,-1,1,40,-0.2,0.2);
  TH1F * h_btag_cos_track_2 = new TH1F("h_btag_cos_track_2","h_btag_cos_track_2",160,-1,1);
  TH2F * h_btag_cos_track_jet_2 = new TH2F("h_btag_cos_track_jet_2","h_btag_cos_track_jet_2",160,-1,1,40,-0.2,0.2);
  TH1F * h_btag_cos_track_4 = new TH1F("h_btag_cos_track_4","h_btag_cos_track_4",160,-1,1);
  TH2F * h_btag_cos_track_jet_4 = new TH2F("h_btag_cos_track_jet_4","h_btag_cos_track_jet_4",160,-1,1,40,-0.2,0.2);
  
  
  TH1F * h_cos_jet_test[18];
  for(int itest =0; itest<18; itest++) h_cos_jet_test[itest]= new TH1F(TString::Format("h_cos_jet_test%i",itest),TString::Format("h_cos_jet_test%i",itest),160,-1,1);

  TH2F * h_cos_quark_jet_test[18];
  for(int itest =0; itest<18; itest++) h_cos_quark_jet_test[itest]= new TH2F(TString::Format("h_cos_quark_jet_test%i",itest),TString::Format("h_cos_quark_jet_test%i",itest),10,-1,1,10,-1,1);

  TH2F * h2_cos_quark_jet_test[18];
  for(int itest =0; itest<18; itest++) h2_cos_quark_jet_test[itest]= new TH2F(TString::Format("h2_cos_quark_jet_test%i",itest),TString::Format("h2_cos_quark_jet_test%i",itest),40,-1,1,40,-1,1);

  TH2F * h_cos_quark_jettracks_test[18];
  for(int itest =0; itest<18; itest++) h_cos_quark_jettracks_test[itest]= new TH2F(TString::Format("h_cos_quark_jettracks_test%i",itest),TString::Format("h_cos_quark_jettracks_test%i",itest),10,-1,1,10,-1,1);

  TH2F * h2_cos_quark_jettracks_test[18];
  for(int itest =0; itest<18; itest++) h2_cos_quark_jettracks_test[itest]= new TH2F(TString::Format("h2_cos_quark_jettracks_test%i",itest),TString::Format("h2_cos_quark_jettracks_test%i",itest),40,-1,1,40,-1,1);

  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  int selected_parton_level=0;
  int selected_jet_level=0;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

   
    double bbmass= sqrt(pow(mc_quark_E[0]+mc_quark_E[1],2)-pow(mc_quark_px[0]+mc_quark_px[1],2)-pow(mc_quark_py[0]+mc_quark_py[1],2)-pow(mc_quark_pz[0]+mc_quark_pz[1],2));

    for(int i=0; i<2; i++) {
      selected_parton_level++;
      std::vector<float> p;
      p.push_back(mc_quark_px[i]);
      p.push_back(mc_quark_py[i]);
      p.push_back(mc_quark_pz[i]);
      float costheta=GetCostheta(p);
      if(fabs(mc_quark_pdg[i])==5 ) {
	h_cos_b->Fill(costheta);
      }
      h_cos_q->Fill(costheta);
    }

    for(int itest =0; itest<18; itest++) {
      if(PreSelectionTest(itest)==true) {
	for(int ijet=0; ijet<2; ijet++) {
	  if(itest==0) selected_jet_level++;
	  std::vector<float> pq1;
	  pq1.push_back(mc_quark_px[0]);
	  pq1.push_back(mc_quark_py[0]);
	  pq1.push_back(mc_quark_pz[0]);
	  float costhetaq1=GetCostheta(pq1);
      	  std::vector<float> pq2;
	  pq2.push_back(mc_quark_px[1]);
	  pq2.push_back(mc_quark_py[1]);
	  pq2.push_back(mc_quark_pz[1]);
	  float costhetaq2=GetCostheta(pq2);
	  
	  std::vector<float> p;
	  p.push_back(jet_px[ijet]);
	  p.push_back(jet_py[ijet]);
	  p.push_back(jet_pz[ijet]);
	  float costheta=GetCostheta(p);

	  float costheta0=-2;
	  if(mc_matching==1 && ijet ==0 ) costheta0=costhetaq1;
	  if(mc_matching==1 && ijet ==1 ) costheta0=costhetaq2;
	  if(mc_matching==2 && ijet ==0 ) costheta0=costhetaq2;
	  if(mc_matching==2 && ijet ==1 ) costheta0=costhetaq1;
	  	  
	  h_cos_jet_test[itest]->Fill(costheta);
	  h_cos_quark_jet_test[itest]->Fill(costheta0,costheta);
	  h2_cos_quark_jet_test[itest]->Fill(costheta0,costheta);


	  float ptrack_x=0;
	  float ptrack_y=0;
	  float ptrack_z=0;
	  for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
	    for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
	      ptrack_x+=jet_track_px[ijet][ivtx][itrack];
	      ptrack_y+=jet_track_py[ijet][ivtx][itrack];
	      ptrack_z+=jet_track_pz[ijet][ivtx][itrack];
	    }
	  }
	  std::vector<float> ptracks;
	  ptracks.push_back(ptrack_x);
	  ptracks.push_back(ptrack_y);
	  ptracks.push_back(ptrack_z);
	  float costheta_tracks=GetCostheta(ptracks);
	  h_cos_quark_jettracks_test[itest]->Fill(costheta0,costheta_tracks);
	  h2_cos_quark_jettracks_test[itest]->Fill(costheta0,costheta_tracks);

	}
      }
    }
      
 

    if(PreSelectionTest(0)==true) {

      for(int ijet=0; ijet<2; ijet++) {
	std::vector<float> p0;
	p0.push_back(jet_px[ijet]);
	p0.push_back(jet_py[ijet]);
	p0.push_back(jet_pz[ijet]);
	
	float costheta0=GetCostheta(p0);
		
	for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
	  for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
	    double mom = sqrt(pow(jet_track_px[ijet][ivtx][itrack],2)+pow(jet_track_py[ijet][ivtx][itrack],2)+pow(jet_track_pz[ijet][ivtx][itrack],2));
	    std::vector<float> p;
	    p.push_back(jet_track_px[ijet][ivtx][itrack]);
	    p.push_back(jet_track_py[ijet][ivtx][itrack]);
	    p.push_back(jet_track_pz[ijet][ivtx][itrack]);
	    float costheta =GetCostheta(p);
	    if(mom>0) {
	      h_cos_track_0->Fill(costheta);
	      h_cos_track_jet_0->Fill(costheta0,costheta0-costheta);
	    }
	    if(mom>2) {
	      h_cos_track_2->Fill(costheta);
	      h_cos_track_jet_2->Fill(costheta0,costheta0-costheta);
	    }
	    if(mom>4) {
	      h_cos_track_4->Fill(costheta);
	      h_cos_track_jet_4->Fill(costheta0,costheta0-costheta);
	    }
	    
	  }
	}
      }
    }

    if(PreSelectionTest(1)==true) {

      for(int ijet=0; ijet<2; ijet++) {
	std::vector<float> p0;
	p0.push_back(jet_px[ijet]);
	p0.push_back(jet_py[ijet]);
	p0.push_back(jet_pz[ijet]);
	
	float costheta0=GetCostheta(p0);
		
	for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
	  for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
	    double mom = sqrt(pow(jet_track_px[ijet][ivtx][itrack],2)+pow(jet_track_py[ijet][ivtx][itrack],2)+pow(jet_track_pz[ijet][ivtx][itrack],2));
	    std::vector<float> p;
	    p.push_back(jet_track_px[ijet][ivtx][itrack]);
	    p.push_back(jet_track_py[ijet][ivtx][itrack]);
	    p.push_back(jet_track_pz[ijet][ivtx][itrack]);
	    float costheta =GetCostheta(p);
	    if(mom>0) {
	      h_btag_cos_track_0->Fill(costheta);
	      h_btag_cos_track_jet_0->Fill(costheta0,costheta0-costheta);
	    }
	    if(mom>2) {
	      h_btag_cos_track_2->Fill(costheta);
	      h_btag_cos_track_jet_2->Fill(costheta0,costheta0-costheta);
	    }
	    if(mom>4) {
	      h_btag_cos_track_4->Fill(costheta);
	      h_btag_cos_track_jet_4->Fill(costheta0,costheta0-costheta);
	    }
	  }
	}
      }
    }
      
  }

  cout<<selected_parton_level<<" "<<selected_jet_level<<endl;
  h_cos_b->Write();
  h_cos_q->Write();
  
  //--------------------------------------------------------------------------------------------------------
  h_cos_track_0->Write();
  h_cos_track_jet_0->Write();
  h_cos_track_2->Write();
  h_cos_track_jet_2->Write();
  h_cos_track_4->Write();
  h_cos_track_jet_4->Write();

  //--------------------------------------------------------------------------------------------------------
  h_btag_cos_track_0->Write();
  h_btag_cos_track_jet_0->Write();
  h_btag_cos_track_2->Write();
  h_btag_cos_track_jet_2->Write();
  h_btag_cos_track_4->Write();
  h_btag_cos_track_jet_4->Write();

  
  
  for(int itest =0; itest<18; itest++) {
    h_cos_jet_test[itest]->Write();
    h_cos_quark_jet_test[itest]->Write();
    h2_cos_quark_jet_test[itest]->Write();

    h_cos_quark_jettracks_test[itest]->Write();
    h2_cos_quark_jettracks_test[itest]->Write();
  }

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

bool observable::PreSelection(int type) {

  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
  double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
  double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));
   
  double b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
  double b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
  double bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

  double jj_pT= sqrt(pow(jet_px[0]+jet_px[1],2)+pow(jet_py[0]+jet_py[1],2));
   
  //if( bbmass < 180 || (b1mass+b2mass) >120 || maxenergy_photon_E>40 || jet_btag[0]<btag1 || jet_btag[1]<btag2 || jet0_p<40 || jet1_p<40) return false;
  //500GeV
  //  if(bbmass < 300 ||  maxenergy_photon_E>100 || jet_btag[0]<btag1 || jet_btag[1]<btag2) return false; 
  //250GeV
  //if( bbmass<180 || (b1mass+b2mass) >120 || maxenergy_photon_E>40) return false;//  || jet_btag[0]<btag1 || jet_btag[1]<btag2 ) return false;
  if(type ==0)  if(jet_btag[0]<btag1 || jet_btag[1]<btag2  ) return false;
  if(type ==1)  if(jet_btag[0]<btag1 || jet_btag[1]<btag2 || bbmass < 180 || maxenergy_photon_E>40  ) return false;
  if(type ==2)  if(jet_btag[0]<btag1 || jet_btag[1]<btag2 || bbmass < 180 || maxenergy_photon_E>40 ||  (b1mass+b2mass) >120) return false;
  if(type ==3)  if(jet_btag[0]<btag1 || jet_btag[1]<btag2 || bbmass < 180 || maxenergy_photon_E>40 ||  (b1mass+b2mass) >120 || oblateness>0.18) return false;
  if(type ==4)  if(jet_btag[0]<btag1 || jet_btag[1]<btag2 || bbmass < 180 || maxenergy_photon_E>40 ||  y23>0.075) return false;
  if(type ==5)  if(jet_btag[0]<btag1 || jet_btag[1]<btag2 || bbmass < 180 || maxenergy_photon_E>40 ||  y12<0.12) return false;
  if(type ==6)  if(jet_btag[0]<btag1 || jet_btag[1]<btag2 || bbmass < 180 || maxenergy_photon_E>40 ||  y23>0.975 || y12<0.12) return false;
  if(type ==7)  if(jet_btag[0]<btag1 || jet_btag[1]<btag2 || bbmass < 180 || maxenergy_photon_E>40 || (b1mass+b2mass) >120 || y23>0.075) return false;
  if(type ==8)  if(jet_btag[0]<btag1 || jet_btag[1]<btag2 || bbmass < 180 || maxenergy_photon_E>40 || (b1mass+b2mass) >120 || y12<0.12) return false;
  if(type ==9)  if(jet_btag[0]<btag1 || jet_btag[1]<btag2 || bbmass < 180 || maxenergy_photon_E>40 || (b1mass+b2mass) >120 || y23>0.975 || y12<0.12) return false;

  return true;
}

bool observable::PreSelectionTest(int type=0) {

  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
  double b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
  double b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
  double bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));
  if(type ==0 ) return true;
  if(type ==1 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2  ) return true;
  if(type ==2 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 && oblateness<0.18 ) return true;
  if(type ==3 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 && oblateness<0.18 &&  bbmass >180 && maxenergy_photon_E<40 ) return true;
  if(type ==4 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 && oblateness<0.18 &&  bbmass >180 && maxenergy_photon_E<40 &&  (b1mass+b2mass) <120) return true;
  if(type ==5 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 &&  bbmass >180 && maxenergy_photon_E<40 ) return true;
  if(type ==6 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 &&  bbmass >180 && maxenergy_photon_E<40 &&  (b1mass+b2mass) <120) return true;
  if(type ==7 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 && sphericity<0.05 ) return true;
  if(type ==8 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 &&sphericity<0.05 &&  bbmass >180 && maxenergy_photon_E<40 ) return true;
  if(type ==9 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 &&sphericity<0.05 &&  bbmass >180 && maxenergy_photon_E<40 &&  (b1mass+b2mass) <120) return true;
  if(type ==10 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 && y23<0.075) return true;
  if(type ==11 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 && y12>0.12) return true;
  if(type ==12 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 && y12>0.12 &&  bbmass >180 && maxenergy_photon_E<40 &&  (b1mass+b2mass) <120) return true;
  if(type ==13 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 && y23<0.075 && bbmass >180 && maxenergy_photon_E<40 &&  (b1mass+b2mass) <120) return true;
  if(type ==14 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 && y12>0.12 &&  y23<0.075 && bbmass >180 && maxenergy_photon_E<40 &&  (b1mass+b2mass) <120) return true;
  if(type ==15 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 && bbmass >180 ) return true;
  if(type ==16 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 && maxenergy_photon_E<40 ) return true;
  if(type ==17 )  if(  jet_btag[0]>btag1 && jet_btag[1]>btag2 && (b1mass+b2mass) <120 ) return true;
  
  return false;
}


float observable::ChargeBcJet(int ijet) {
  double charge=0;

  //  if(jet_btag[ijet] <0.8) return charge;
  
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
  float eff=0.88;
  float purity=0.95;
  
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
      if( iskaon==true) {
	if(gen_purity<purity) charge+=jet_track_charge[ijet][ivtx][itrack];
	else charge-=jet_track_charge[ijet][ivtx][itrack];
      }
    }
   
  }
    
  return charge;
}

