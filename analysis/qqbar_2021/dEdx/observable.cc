// A. Irles
// irles @ lal.in2p3.fr
// 30 March 2020

#define observable_cxx
#include "observable.h"
#include "TPad.h"

void observable::dEdx(int n_entries=-1, TString process="",bool secondary=false, bool ignoreoverlay=true, bool angular_correction=true) {

  float momentum_min=0.95;
  //  1.,1.33,1.667
  Float_t bins_p[]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.5,3,4,5,6,7,8,9,10,12,14,16,18,20,24,28,32,36,40,44,48,52,56,60,64,68,72,80,90,100};
		    //13.33,16.667,20,30,40,50,60,70,80,90,100};
  Int_t nbinnum_p=sizeof(bins_p)/sizeof(Float_t) - 1;

  Float_t bins_cos[50]={};
  bins_cos[0]=0;
  for(int i=1;i<50;i++) bins_cos[i]=bins_cos[i-1]+1./50.;
		    //13.33,16.667,20,30,40,50,60,70,80,90,100};
  Int_t nbinnum_cos=sizeof(bins_p)/sizeof(Float_t) - 1;

  Float_t binsy[200];
  binsy[0]=0.1;
  for(int i=1;i<200;i++) binsy[i]=binsy[i-1]+0.1/100.;
  Int_t nbinnumy=199;

  TH2F* kaon_dEdx_truth = new TH2F("kaon_dEdx_truth","kaon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* proton_dEdx_truth = new TH2F("proton_dEdx_truth","proton_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* pion_dEdx_truth = new TH2F("pion_dEdx_truth","pion_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* electron_dEdx_truth = new TH2F("electron_dEdx_truth","electron_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* muon_dEdx_truth = new TH2F("muon_dEdx_truth","muon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);

  TH2F* kaon_dEdx_cos = new TH2F("kaon_dEdx_cos","kaon_dEdx_cos",nbinnum_cos,bins_cos,nbinnumy,binsy);
  TH2F* proton_dEdx_cos = new TH2F("proton_dEdx_cos","proton_dEdx_cos",nbinnum_cos,bins_cos,nbinnumy,binsy);
  TH2F* pion_dEdx_cos = new TH2F("pion_dEdx_cos","pion_dEdx_cos",nbinnum_cos,bins_cos,nbinnumy,binsy);
  TH2F* electron_dEdx_cos = new TH2F("electron_dEdx_cos","electron_dEdx_cos",nbinnum_cos,bins_cos,nbinnumy,binsy);
  TH2F* muon_dEdx_cos = new TH2F("muon_dEdx_cos","muon_dEdx_cos",nbinnum_cos,bins_cos,nbinnumy,binsy);

  TH2F* kaon_dEdx_pid = new TH2F("kaon_dEdx_pid","kaon_dEdx_pid",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* proton_dEdx_pid = new TH2F("proton_dEdx_pid","proton_dEdx_pid",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* pion_dEdx_pid = new TH2F("pion_dEdx_pid","pion_dEdx_pid",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* electron_dEdx_pid = new TH2F("electron_dEdx_pid","electron_dEdx_pid",nbinnum_p,bins_p,nbinnumy,binsy);
  TH2F* muon_dEdx_pid = new TH2F("muon_dEdx_pid","muon_dEdx_pid",nbinnum_p,bins_p,nbinnumy,binsy);

  TH1F* n_kaon_jet = new TH1F("n_kaon_jet","n_kaon_jet",15,-0.5,14.5);
  TH1F* n_kaon_vtx = new TH1F("n_kaon_vtx","n_kaon_vtx",15,-0.5,14.5);
  TH1F* p_kaon = new TH1F("p_kaon","p_kaon",125,-0.5,124.5);
  TH1F* p_proton = new TH1F("p_proton","p_proton",125,-0.5,124.5);
  TH1F* p_pion = new TH1F("p_pion","p_pion",125,-0.5,124.5);
  TH1F* p_electron = new TH1F("p_electron","p_electron",125,-0.5,124.5);
  TH1F* p_muon = new TH1F("p_muon","p_muon",125,-0.5,124.5);

  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();
  std::cout<<nentries<<std::endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //  double bbmass= sqrt(pow(mc_quark_E[0]+mc_quark_E[1],2)-pow(mc_quark_px[0]+mc_quark_px[1],2)-pow(mc_quark_py[0]+mc_quark_py[1],2)-pow(mc_quark_pz[0]+mc_quark_pz[1],2));
    double gamma_e=mc_ISR_E[0]+mc_ISR_E[1];

    //for the moment, we restrict the analysis to the bb events without radaitive return
    if(fabs(mc_quark_pdg[0])==5 && gamma_e<35) {
      for(int ijet=0; ijet<2; ijet++){
	int nkaonjet=0;
	double nt=0;
	if(jet_btag[ijet]>0.8) {
	  int nkaonvtx=0;
	  for(int ipfo=0; ipfo<pfo_n; ipfo++) {

	    float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
	    
	    if(secondary==true &&  pfo_vtx[ipfo]<1) continue;
	    // if(secondary==false &&  pfo_vtx[ipfo]>0) continue;
	    if(ignoreoverlay==false && pfo_isoverlay[ipfo]==1) continue;

	    float costheta;
	    std::vector<float> p_track;
	    p_track.push_back(pfo_px[ipfo]);
	    p_track.push_back(pfo_py[ipfo]);
	    p_track.push_back(pfo_pz[ipfo]);
	    costheta=GetCostheta(p_track);
	    float dedx=pfo_dedx[ipfo];
	    if(angular_correction==true) {
	      dedx=dedx*pow(TMath::ACos(fabs(costheta)),0.05);
	    }
	    if( pfo_ntracks[ipfo]==1 && fabs(pfo_ntracks[ipfo])!=0) {
	      
	      if( fabs(pfo_pdgcheat[ipfo])==321 ){
		nkaonjet++;
		nkaonvtx++;
		p_kaon->Fill(momentum);
	      }
	      if( fabs(pfo_pdgcheat[ipfo])==211 ) p_pion->Fill(momentum);
	      if( fabs(pfo_pdgcheat[ipfo])==2212 ) p_proton->Fill(momentum);
	      if( fabs(pfo_pdgcheat[ipfo])==11 ) p_electron->Fill(momentum);
	      if( fabs(pfo_pdgcheat[ipfo])==13 ) p_muon->Fill(momentum);
	      
	    //for(int ijet=0; ijet<2; ijet++) {
	      if(dedx>0) {
		if(fabs(pfo_pdgcheat[ipfo])==211) pion_dEdx_truth->Fill(momentum,dedx);
		if(fabs(pfo_pdgcheat[ipfo])==321) kaon_dEdx_truth->Fill(momentum,dedx);
		if(fabs(pfo_pdgcheat[ipfo])==2212) proton_dEdx_truth->Fill(momentum,dedx);
		if(fabs(pfo_pdgcheat[ipfo])==11) electron_dEdx_truth->Fill(momentum,dedx);
		if(fabs(pfo_pdgcheat[ipfo])==13) muon_dEdx_truth->Fill(momentum,dedx);
		
		if(fabs(pfo_pdgcheat[ipfo])==211) pion_dEdx_cos->Fill(fabs(costheta),dedx);
		if(fabs(pfo_pdgcheat[ipfo])==321) kaon_dEdx_cos->Fill(fabs(costheta),dedx);
		if(fabs(pfo_pdgcheat[ipfo])==2212) proton_dEdx_cos->Fill(fabs(costheta),dedx);
		if(fabs(pfo_pdgcheat[ipfo])==11) electron_dEdx_cos->Fill(fabs(costheta),dedx);
		if(fabs(pfo_pdgcheat[ipfo])==13) muon_dEdx_cos->Fill(fabs(costheta),dedx);
		
		
		if(fabs(pfo_piddedx[ipfo])==211) pion_dEdx_pid->Fill(momentum,dedx);
		if(fabs(pfo_piddedx[ipfo])==321) kaon_dEdx_pid->Fill(momentum,dedx);
		if(fabs(pfo_piddedx[ipfo])==2212) proton_dEdx_pid->Fill(momentum,dedx);
		if(fabs(pfo_piddedx[ipfo])==11) electron_dEdx_pid->Fill(momentum,dedx);
		if(fabs(pfo_piddedx[ipfo])==13) muon_dEdx_pid->Fill(momentum,dedx);
	      }
	    }
	  }
	  n_kaon_vtx->Fill(nkaonvtx);
	}//btag
      }//ijet
    }//bb
  }//for

   SetQQbarStyle();
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);

   gStyle->SetTitleBorderSize(0);
   gStyle->SetTitleStyle(0);
   gStyle->SetTitleX(0.3);
   gStyle->SetMarkerSize(0.2);
   gStyle->SetPadLeftMargin(0.2);

   TCanvas* c_dEdx_truth_0 = new TCanvas("c_dEdx","c_dEdx",800,800);
   c_dEdx_truth_0->cd(1);
   gPad->SetLogx();
   pion_dEdx_truth->GetXaxis()->SetTitle("p [GeV]");
   pion_dEdx_truth->GetYaxis()->SetTitle("#frac{dE}{dx} [MeV]");
   pion_dEdx_truth->GetYaxis()->SetTitleOffset(1.7);
  
   pion_dEdx_truth->SetMarkerColor(4);
   pion_dEdx_truth->SetMarkerStyle(1);
   pion_dEdx_truth->SetLineColor(4);
   pion_dEdx_truth->SetTitle("");
   pion_dEdx_truth->SetContour(5);
   pion_dEdx_truth->Draw("p");

   proton_dEdx_truth->SetMarkerColor(kGreen+1);
   proton_dEdx_truth->SetMarkerStyle(1);
   proton_dEdx_truth->SetLineColor(kGreen+1);
   proton_dEdx_truth->SetContour(5);
   proton_dEdx_truth->Draw("psame");

   kaon_dEdx_truth->SetMarkerColor(2);
   kaon_dEdx_truth->SetMarkerStyle(1);
   kaon_dEdx_truth->SetLineColor(2);
   kaon_dEdx_truth->SetContour(5);
   kaon_dEdx_truth->Draw("psame");

   
   electron_dEdx_truth->SetMarkerColor(kBlack);
   electron_dEdx_truth->SetMarkerStyle(1);
   electron_dEdx_truth->SetLineColor(kBlack);
   electron_dEdx_truth->SetContour(5);
   electron_dEdx_truth->Draw("psame");

   muon_dEdx_truth->SetMarkerColor(kGray);
   muon_dEdx_truth->SetMarkerStyle(1);
   muon_dEdx_truth->SetLineColor(kGray);
   muon_dEdx_truth->SetContour(5);
   muon_dEdx_truth->Draw("psame");

   TCanvas* c_dEdx_pid_0 = new TCanvas("c_dEdx_pid","c_dEdx_pid",800,800);
   c_dEdx_pid_0->cd(1);
   gPad->SetLogx();
   pion_dEdx_pid->GetXaxis()->SetTitle("p [GeV]");
   pion_dEdx_pid->GetYaxis()->SetTitle("#frac{dE}{dx} [MeV]");
   pion_dEdx_pid->GetYaxis()->SetTitleOffset(1.7);
  
   pion_dEdx_pid->SetMarkerColor(4);
   pion_dEdx_pid->SetMarkerStyle(1);
   pion_dEdx_pid->SetLineColor(4);
   pion_dEdx_pid->SetTitle("");
   pion_dEdx_pid->SetContour(5);
   pion_dEdx_pid->Draw("p");

   proton_dEdx_pid->SetMarkerColor(kGreen+1);
   proton_dEdx_pid->SetMarkerStyle(1);
   proton_dEdx_pid->SetLineColor(kGreen+1);
   proton_dEdx_pid->SetContour(5);
   proton_dEdx_pid->Draw("psame");

   kaon_dEdx_pid->SetMarkerColor(2);
   kaon_dEdx_pid->SetMarkerStyle(1);
   kaon_dEdx_pid->SetLineColor(2);
   kaon_dEdx_pid->SetContour(5);
   kaon_dEdx_pid->Draw("psame");

   
   electron_dEdx_pid->SetMarkerColor(kBlack);
   electron_dEdx_pid->SetMarkerStyle(1);
   electron_dEdx_pid->SetLineColor(kBlack);
   electron_dEdx_pid->SetContour(5);
   electron_dEdx_pid->Draw("psame");

   muon_dEdx_pid->SetMarkerColor(kGray);
   muon_dEdx_pid->SetMarkerStyle(1);
   muon_dEdx_pid->SetLineColor(kGray);
   muon_dEdx_pid->SetContour(5);
   muon_dEdx_pid->Draw("psame");

  

   QQBARLabel(0.25,0.85,"",1);
  
   TLegend *leg1 = new TLegend(0.7,0.8,0.8,0.9);
   leg1->AddEntry(pion_dEdx_pid,"PID-dEdx #pi","lp");
   leg1->AddEntry(kaon_dEdx_pid,"PID-dEdx K","lp");
   leg1->AddEntry(proton_dEdx_pid,"PID-dEdx p","lp");
   leg1->AddEntry(muon_dEdx_pid,"PID-dEdx #mu","lp");
   leg1->AddEntry(electron_dEdx_pid,"PID-dEdx e","lp");
   leg1->SetFillColor(0);
   leg1->SetLineColor(0);
   leg1->SetShadowColor(0);
   leg1->Draw();
  

   //kaon
   float x_kaon[200], y_kaon[200], ey_kaon[200], ey_kaon2[200];
   float ex[200];
   int n_kaon=0;
   for(int i=0; i<kaon_dEdx_truth->GetNbinsX(); i++) {
     if( kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1) >momentum_min  ) {
       TH1D * proj_kaon =kaon_dEdx_truth->ProjectionY("proj_kaon",i,i+1);
       
       x_kaon[n_kaon]=kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1);
       y_kaon[n_kaon]=proj_kaon->GetMean();
       ey_kaon[n_kaon]=proj_kaon->GetRMS();
       ey_kaon2[n_kaon]=proj_kaon->GetMean()/sqrt(proj_kaon->GetEntries());
       ex[n_kaon]=0;//kaon_dEdx_truth->GetXaxis()->GetBinWidth(i+1)/2.;
       n_kaon++;
     }
   }
   TGraphErrors *kaonproj= new TGraphErrors(n_kaon,x_kaon,y_kaon,ex,ey_kaon);
   TGraphErrors *kaonproj2= new TGraphErrors(n_kaon,x_kaon,y_kaon,ex,ey_kaon2);

   //pion
   float x_pion[200], y_pion[200], ey_pion[200], ey_pion2[200];
   int n_pion=0;
   for(int i=0; i<pion_dEdx_truth->GetNbinsX(); i++) {
     if( pion_dEdx_truth->GetXaxis()->GetBinCenter(i+1) >momentum_min  ) {
       TH1D * proj_pion =pion_dEdx_truth->ProjectionY("proj_pion",i,i+1);

       x_pion[n_pion]=pion_dEdx_truth->GetXaxis()->GetBinCenter(i+1);
       y_pion[n_pion]=proj_pion->GetMean();
       ey_pion[n_pion]=proj_pion->GetRMS();
       ey_pion2[n_pion]=proj_pion->GetMean()/sqrt(proj_pion->GetEntries());
       ex[n_pion]=pion_dEdx_truth->GetXaxis()->GetBinWidth(i+1)/2.;
       n_pion++;
     }
   }
   TGraphErrors *pionproj= new TGraphErrors(n_pion,x_pion,y_pion,ex,ey_pion);
   TGraphErrors *pionproj2= new TGraphErrors(n_pion,x_pion,y_pion,ex,ey_pion2);
   
   //proton
   float x_proton[200], y_proton[200], ey_proton[200], ey_proton2[200];
   int n_proton=0;
   for(int i=0; i<proton_dEdx_truth->GetNbinsX(); i++) {
     if( proton_dEdx_truth->GetXaxis()->GetBinCenter(i+1) >momentum_min  ) {
       TH1D * proj_proton =proton_dEdx_truth->ProjectionY("proj_proton",i,i+1);

       x_proton[n_proton]=proton_dEdx_truth->GetXaxis()->GetBinCenter(i+1);
       y_proton[n_proton]=proj_proton->GetMean();
       ey_proton[n_proton]=proj_proton->GetRMS();
       ey_proton2[n_proton]=proj_proton->GetMean()/sqrt(proj_proton->GetEntries());
       ex[n_proton]=proton_dEdx_truth->GetXaxis()->GetBinWidth(i+1)/2.;
       n_proton++;
     }
   }
   TGraphErrors *protonproj= new TGraphErrors(n_proton,x_proton,y_proton,ex,ey_proton);
   TGraphErrors *protonproj2= new TGraphErrors(n_proton,x_proton,y_proton,ex,ey_proton2);
   

  //----------------------------------------------------------------------------------------
  // TCanvas* c_calculateparam = new TCanvas("c_calculateparam","c_calculateparam",1000,800);
  // pionproj->SetMarkerColor(4);
  // pionproj->SetLineColor(4);
  // pionproj->SetTitle("dE/dx projection");
  // pionproj->GetYaxis()->SetTitle("dE/dx#times10^{-6}");
  // pionproj->GetXaxis()->SetTitle("p");
  // pionproj->Draw("ap");

  // kaonproj->SetMarkerColor(2);
  // kaonproj->SetLineColor(2);
  // kaonproj->Draw("p");

  // protonproj->SetMarkerColor(3);
  // protonproj->SetLineColor(3);
  // protonproj->Draw("p"); 

  TF1 *f1= new TF1("f1","[0]+[1]*std::log(x)",3,100);
  f1->SetLineColor(2);
  // f1->SetParameter(0,0.15);
  // f1->SetParameter(1,0.02);

  kaonproj->Fit(f1,"REM");

  double x[100], y[100];
  

  for(int ieff=0; ieff<11; ieff++) {
    float eff=0.45+0.05*ieff;
    
    double a=f1->GetParameter(0);
    double b=f1->GetParameter(1);
    
    double a_up=0;
    double a_down=0;
    float max_purity=0;
    float max_eff=0;
    
    for(int j=0; j<50; j++) {
      for(int k=0; k<50; k++) {
  	double ea=(0.1+0.1*j)*f1->GetParError(0);
  	double ea2=-(0.1+0.1*k)*f1->GetParError(0);
	
  	double int_pion=0;
  	double int_kaon=0;
  	double int_proton=0;
  	double int_kaon_total=0;
	
  	for(int i=0; i<kaon_dEdx_truth->GetNbinsX(); i++) {
  	  TH1D * proj_kaon =kaon_dEdx_truth->ProjectionY("proj_kaon",i,i+1);
  	  int_kaon_total+=proj_kaon->GetEntries();
  	  if( kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1) > momentum_min ) {
  	    TH1D * proj_pion =pion_dEdx_truth->ProjectionY("proj_pion",i,i+1);
  	    TH1D * proj_proton =proton_dEdx_truth->ProjectionY("proj_proton",i,i+1);
	    
  	    for(int j1=0; j1<proj_pion->GetNbinsX(); j1++) {
  	      double yplus = a+ea + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
  	      double yminus = a+ea2 + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
  	      if(proj_pion->GetXaxis()->GetBinCenter(j1)< yplus &&  proj_pion->GetXaxis()->GetBinCenter(j1)> yminus) int_pion+=proj_pion->GetBinContent(j1);
  	    }
	    
  	    for(int j1=0; j1<proj_kaon->GetNbinsX(); j1++) {
  	      double yplus = a+ea + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
  	      double yminus = a+ea2 + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
  	      if(proj_kaon->GetXaxis()->GetBinCenter(j1)< yplus &&  proj_kaon->GetXaxis()->GetBinCenter(j1)> yminus) int_kaon+=proj_kaon->GetBinContent(j1);
  	    }
	    
  	    for(int j1=0; j1<proj_proton->GetNbinsX(); j1++) {
  	      double yplus = a+ea + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
  	      double yminus = a+ea2 + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
	      
  	      if(proj_proton->GetXaxis()->GetBinCenter(j1)< yplus &&  proj_proton->GetXaxis()->GetBinCenter(j1)> yminus) int_proton+=proj_proton->GetBinContent(j1);
  	    }	
  	  }
  	}
	
  	if((int_proton+int_pion+int_kaon)/int_kaon_total>eff ) {
  	  // cout<<j<<" "<<k<< "  ->  eff: "<< int_kaon/int_kaon_total<<" purity: "<<1.-(int_proton+int_pion)/int_kaon<<" (pion:"<<1.-(int_pion)/int_kaon<<") (proton:"<<1.-(int_proton)/int_kaon<<")"<<endl;
  	  if( int_kaon/(int_proton+int_pion+int_kaon)  > max_purity) {
  	    max_purity = int_kaon/(int_proton+int_pion+int_kaon);
  	    max_eff= (int_proton+int_pion+int_kaon)/int_kaon_total;
  	    a_up=a+ea;
  	    a_down=a+ea2;
  	    //	cout<<" purity="<<max_purity<<" eff="<<(int_proton+int_pion+int_kaon)/int_kaon_total<<";    slope="<<b<<" upper="<<a+ea<<" lower="<<a+ea2<<endl;
  	  }
  	}
      }
    }
    cout<<"eff_input>"<<eff<<":     purity="<<max_purity<<" eff="<<max_eff<<";    slope="<<b<<" upper="<<a_up<<" lower="<<a_down<<endl;
    x[ieff]=eff;
    y[ieff]=max_purity;
    a_up=0;
    a_down=0;
    max_purity=0;
    max_eff= 0;
  }
  
  TGraph *eff_purity = new TGraph(11,x,y);
  TString fname="all_tracks";
  if(secondary==true) fname = "secondary_tracks";
  if(ignoreoverlay==true) fname += "_ignoreoverlay";
  if(angular_correction==true) fname += "_angularcorrection";
  fname = TString::Format("output_250_%s_%s.root",fname.Data(),process.Data());
  
  TFile *MyFile = new TFile(fname,"RECREATE");
  MyFile->cd();
  pion_dEdx_truth->SetName("pion");
  kaon_dEdx_truth->SetName("kaon");
  proton_dEdx_truth->SetName("proton");
  electron_dEdx_truth->SetName("electron");
  muon_dEdx_truth->SetName("muon");
  pion_dEdx_truth->Write();
  kaon_dEdx_truth->Write();
  proton_dEdx_truth->Write();
  electron_dEdx_truth->Write();
  muon_dEdx_truth->Write();
  c_dEdx_truth_0->Write();
  n_kaon_jet->Write();

  pion_dEdx_cos->SetName("pion_cos");
  kaon_dEdx_cos->SetName("kaon_cos");
  proton_dEdx_cos->SetName("proton_cos");
  electron_dEdx_cos->SetName("electron_cos");
  muon_dEdx_cos->SetName("muon_cos");
  pion_dEdx_cos->Write();
  kaon_dEdx_cos->Write();
  proton_dEdx_cos->Write();
  electron_dEdx_cos->Write();
  muon_dEdx_cos->Write();
  
  pion_dEdx_pid->SetName("pid_pion");
  kaon_dEdx_pid->SetName("pid_kaon");
  proton_dEdx_pid->SetName("pid_proton");
  electron_dEdx_pid->SetName("pid_electron");
  muon_dEdx_pid->SetName("pid_muon");
  pion_dEdx_pid->Write();
  kaon_dEdx_pid->Write();
  proton_dEdx_pid->Write();
  electron_dEdx_pid->Write();
  muon_dEdx_pid->Write();
  c_dEdx_pid_0->Write();
  
  n_kaon_vtx->Write();
  p_kaon->Write();
  p_proton->Write();
  p_pion->Write();
  p_electron->Write();
  p_muon->Write();

  protonproj->SetName("proton_proj");
  protonproj->Write();
  pionproj->SetName("pion_proj");
  pionproj->Write();
  kaonproj->SetName("kaon_proj");
  kaonproj->Write();

  protonproj2->SetName("proton_proj2");
  protonproj2->Write();
  pionproj2->SetName("pion_proj2");
  pionproj2->Write();
  kaonproj2->SetName("kaon_proj2");
  kaonproj2->Write();
  
  
  eff_purity->SetName("eff_purity");
  eff_purity->Write();
  
  
  MyFile->Close();
  
  
}

  
   


bool observable::PreSelection(int type=0,float Kvcut=25) {
  
  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
  if(type == 0 ) return true;


  return false;
}

