#include <unistd.h>
#include <iostream>
#include <string>
#define MAXV 8

using namespace std;
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void bcharge()
{
/*
		string filename0 = "/home/ilc/yokugawa/run/root_merge/";
		//string filename0 = "rootfile/"; 
		string filename1;

		filename1 = "new/large/leptonic_yyxyev_eLeR_new_large_QQbar.root";
*/
	
		string filename = "/hsm/ilc/users/yokugawa/preset_N_run/l5/semiLep/eLpR/electron_muon/QQbarProcessor_out/IsoLepTagged.eLpR_electron_muon_QQbar_MethodAll_temp.root";
	
		cout << "Processing : " << filename << " ..." << endl;

		TFile * file = TFile::Open(filename.c_str());

		int bin_e = 30;
		int max_e = 1;

		//TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
		TCanvas * c2 = new TCanvas("c2", "Data-MC",0,0,500,500);
		
		TH1F * GenChg = new TH1F("GenChg", ";B hadron charge;Events", 10, -5, 5);
		TH1F * RecoChg = new TH1F("RecoChg", ";B hadron charge;Events", 10, -5, 5);

		TTree * normaltree = (TTree*) file->Get( "Stats" ) ;

		// Selection lists
		TCut thru = "Thrust < 0.9";
		TCut hadM = "hadMass > 180 && hadMass < 420";
		TCut rcTW = "Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50";
		TCut pcut = "Top1bmomentum > 15 && Top2bmomentum > 15";
		TCut gcut = "(Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2";

		// Methods selection
		TCut methodAll = "methodTaken > 0";
		TCut method1 = "methodTaken == 1";
		TCut method2 = "methodTaken == 2";
		TCut method3 = "methodTaken == 3";
		TCut method4 = "methodTaken == 4";
		TCut method5 = "methodTaken == 5";
		TCut method6 = "methodTaken == 6";
		TCut method7 = "methodTaken == 7";

		// Total cut applied
		TCut cuts = rcTW + hadM + pcut + gcut + methodAll;

		//TCut fcuts = "qCostheta > 0" + cuts;
		//TCut bcuts = "qCostheta < 0 && qCostheta > -1.0 " + cuts;
		
		// Fill histograms from tree
		normaltree->Draw("MCBHadCharge >> GenChg", "singletopFlag == 0");
		normaltree->Draw("Top1bcharge >> RecoChg", cuts);
		normaltree->Draw("Top2bcharge >> +RecoChg", cuts);
		
		RecoChg->Scale(1 / RecoChg->GetEntries() );
		GenChg->Scale(1 / GenChg->GetEntries() );

		RecoChg->SetLineWidth(3);	
		GenChg->SetLineWidth(3);	
		GenChg->SetLineStyle(2);	
		GenChg->SetLineColor(kGreen+1);
		

		TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);

		GenChg->SetMinimum(0);
		GenChg->Draw("he");
		RecoChg->Draw("same");


}

