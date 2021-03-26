#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)

using namespace std;

void sethist(Color_t clr, TH1F* h = 0);

void bjet_EvE()
{
	// set plot style
	SetQQbarStyle();
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);  
	gStyle->SetOptTitle(1);
	gStyle->SetTitleBorderSize(0);
	gStyle->SetTitleStyle(0);
	gStyle->SetMarkerSize(0);
	gStyle->SetTitleX(0.2); 
	gStyle->SetTitleY(0.9); 

	// set file path
	std::string filename = "/hsm/ilc/users/yokugawa/preset_N_run/l5/electron_muon/QQbarProcessor_out/IsoLepTagged.eL.pR_electron_muon_QQbar_MethodAll_110119.root";

	TFile * file = TFile::Open(filename.c_str());

	TTree * normaltree = (TTree*) file->Get( "Stats" ) ;

	// Histograms
	
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * cosbjets_all = new TH1F("cosbjets_all", ";cos#theta_{bjets};Entries", 200,-1.0,1.0);
	TH1F * cosbjets_acc = new TH1F("cosbjets_acc", ";cos#theta_{bjets};Entries", 200,-1.0,1.0);
	TH1F * cosbjets_rej = new TH1F("cosbjets_rej", ";cos#theta_{bjets};Entries", 200,-1.0,1.0);

	TH1F * bjetE_all = new TH1F("bjetE_all", ";E_{bjet} (GeV);Entries", 200,0.,200.);
	TH1F * bjetE_acc = new TH1F("bjetE_acc", ";E_{bjet} (GeV);Entries", 200,0.,200.);
	TH1F * bjetE_rej = new TH1F("bjetE_rej", ";E_{bjet} (GeV);Entries", 200,0.,200.);

	TGaxis::SetMaxDigits(3);

	sethist(kGray+1, cosbjets_all);
	cosbjets_all->SetLineStyle(1);
	sethist(kGreen+1, cosbjets_acc);
	sethist(kRed+1, cosbjets_rej);

	sethist(kGray+1, bjetE_all);
	bjetE_all->SetLineStyle(1);
	sethist(kGreen+1, bjetE_acc);
	sethist(kRed+1, bjetE_rej);


	float Thrust=0,
				hadMass=0,
				Top1mass=0,
				W1mass=0,
				Top1bmomentum=0,
				Top2bmomentum=0,
				Top1gamma=0,
				Top2gamma=0,
				cosbjets=0;

	float qMCcostheta[2],
				qCostheta[2],
				jet_E[2];
	
	int recoforward=0,
			recobackward=0,
			methodUsed=0;

	int methodTaken[100],
			chgValue[100];
				
	int entryStat = normaltree->GetEntries();	


	normaltree->SetBranchAddress("Thrust", &Thrust);
	normaltree->SetBranchAddress("hadMass", &hadMass);
	normaltree->SetBranchAddress("Top1mass", &Top1mass);
	normaltree->SetBranchAddress("W1mass", &W1mass);
	normaltree->SetBranchAddress("Top1bmomentum", &Top1bmomentum);
	normaltree->SetBranchAddress("Top2bmomentum", &Top2bmomentum);
	normaltree->SetBranchAddress("Top1gamma", &Top1gamma);
	normaltree->SetBranchAddress("Top2gamma", &Top2gamma);
	normaltree->SetBranchAddress("methodUsed", &methodUsed);
	normaltree->SetBranchAddress("methodTaken", methodTaken);
	normaltree->SetBranchAddress("chgValue", chgValue);
	//normaltree->SetBranchAddress("qMCcostheta", qMCcostheta);
	normaltree->SetBranchAddress("qCostheta", qCostheta);
	
	normaltree->SetBranchAddress("cosbjets", &cosbjets);
	normaltree->SetBranchAddress("jet_E", jet_E);

	int temp=0;
	int total=0, afBaseLine=0, mth1=0;

  for(int iStatEntry=0; iStatEntry<entryStat; iStatEntry++){

		normaltree->GetEntry(iStatEntry);

		//cosbjets_all->Fill(cosbjets);
		//bjetE_all->Fill(jet_E[0]);
		//bjetE_all->Fill(jet_E[1]);

		total++;

		if(Thrust<0.9){

			if(hadMass > 180 && hadMass < 420){

				if(Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50){

					if( (Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ){

						if(Top1bmomentum > 15 && Top2bmomentum > 15){

							afBaseLine++;

							bool methodCheck1=false,
									 methodCheck2=false,
									 methodCheck3=false,
									 methodCheck4=false,
									 methodCheck5=false,
									 methodCheck6=false,
									 methodCheck7=false;

							int sum = 0;

							for(int imethod = 0; imethod < methodUsed; imethod++){

								int Nmethod = methodTaken[imethod];
								int charge  = chgValue[imethod];

								sum += charge;

								if(Nmethod==1) methodCheck1=true;
								if(Nmethod==2) methodCheck2=true;
								if(Nmethod==3) methodCheck3=true;
								if(Nmethod==4) methodCheck4=true;
								if(Nmethod==5) methodCheck5=true;
								if(Nmethod==6) methodCheck6=true;
								if(Nmethod==7) methodCheck7=true;

							}

							if( (qCostheta[0] > -1.0 && qCostheta[0] < -0.9) || (qCostheta[1] > -1.0 && qCostheta[1] < -0.9) ){

								cosbjets_all->Fill(cosbjets);
								bjetE_all->Fill(jet_E[0]);
								bjetE_all->Fill(jet_E[1]);

								if(sum == 0){
									continue;
								}else{

									if(methodCheck1){

										mth1++;

										cosbjets_acc->Fill(cosbjets);
										bjetE_acc->Fill(jet_E[0]);
										bjetE_acc->Fill(jet_E[1]);

									}else{

										cosbjets_rej->Fill(cosbjets);
										bjetE_rej->Fill(jet_E[0]);
										bjetE_rej->Fill(jet_E[1]);

									}// method check

								}//consistency

							}// qCos > 0.9

						}//pcut
					}//gcut
				}//rcTW cut
			}//hadM cut
		}//thrust cut

	}// End Entries

	std::cout << "total = " << total << "\t" << "afBaseLine = " << afBaseLine << "\t" << "mth1 = " << mth1 << std::endl;

	// Plot
	cosbjets_all->SetMinimum(0);
	cosbjets_all->Draw("");
	cosbjets_rej->SetMinimum(0);
	cosbjets_rej->Draw("same");	
	cosbjets_acc->SetMinimum(0);
	cosbjets_acc->Draw("same");

	// Legends
	TLegend *leg = new TLegend(0.2,0.75,0.6,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(cosbjets_all,"All","l");
	leg->AddEntry(cosbjets_acc,"Accepted","l");
	leg->AddEntry(cosbjets_rej,"Rejected","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	QQBARLabel(0.8,0.2,"",1);

	c1->Update();


	TCanvas * c2 = new TCanvas("c2", "Data-MC",0,0,500,500);

	// Plot
	bjetE_all->SetMinimum(0);
	bjetE_all->Draw("");
	bjetE_rej->SetMinimum(0);
	bjetE_rej->Draw("same");	
	bjetE_acc->SetMinimum(0);
	bjetE_acc->Draw("same");

	// Legends
	TLegend *leg2 = new TLegend(0.2,0.75,0.6,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg2->SetTextFont(42);
	leg2->AddEntry(bjetE_all,"All","l");
	leg2->AddEntry(bjetE_acc,"Accepted","l");
	leg2->AddEntry(bjetE_rej,"Rejected","l");
	leg2->SetFillColor(0);
	leg2->SetLineColor(0);
	leg2->SetShadowColor(0);
	leg2->Draw();

	QQBARLabel(0.8,0.2,"",1);

	c2->Update();

}

void sethist(Color_t clr, TH1F* h = 0){

	h->SetLineWidth(3);
	h->SetLineStyle(2);
	h->SetLineColor(clr);
	h->SetFillColor(clr);
	h->SetFillStyle(3004);

}








