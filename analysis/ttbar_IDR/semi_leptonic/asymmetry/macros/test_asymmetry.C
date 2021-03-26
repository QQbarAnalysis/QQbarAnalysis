
#include <unistd.h>
#include <iostream>
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void test_asymmetry()
{
	int token=0;
	string filename0 = "/home/ilc/yokugawa/run/root_merge/";
	//string filename0 = "rootfile/"; 
	string filename1;

	cout << "0 = New/Small" << endl;
	cout << "1 = New/Large" << endl;
	cout << "2 = New/Large/QQbar" << endl;
	cout << "3 = Old      " 	  << endl;
	cout << "4 = Old/yyxylv      "       << endl;
	cout << "Choose from 0-4: ";
	cin  >> token;
	cout << endl;

	switch(token){
		case 0 : filename1 = "new/small/leptonic_yyxyev_eLeR_new_small.root";
						 break;
		case 1 : filename1 = "new/large/leptonic_yyxyev_eLeR_new_large.root";
						 break;
		case 2 : filename1 = "new/large/leptonic_yyxyev_eLeR_new_large_QQbar.root";
						 break;
		case 3 : filename1 = "old/leptonic_yyxyev_eLeR_old_lcut.root" ;
						 break;
		case 4 : filename1 = "old/leptonic_yyxylv_eLeR_iso_lep_lcut.root" ;
						 break;
	}

	string filename = filename0 + filename1;
	cout << "Processing : " << filename << " ..." << endl;

	TFile * file = TFile::Open(filename.c_str());

	int bin_e = 30;
	int max_e = 1;

	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TCanvas * c2 = new TCanvas("c2", "Data-MC",0,0,500,500);

	TH1F * cosGen = new TH1F("cosGen", ";cos#theta_{b};Entries", bin_e,-1.0,max_e);
	TH1F * EneGenNoTrk = new TH1F("EneGenNoTrk", ";Energy (GeV);Entries", 100, 0, 500);
	TH1F * EneGenTrk = new TH1F("EneGenTrk", ";Energy (GeV);Entries", 100, 0, 500);

	TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
	TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;

	cosGen->SetLineWidth(3);
	cosGen->SetLineStyle(2);
	cosGen->SetLineColor(kGreen+1);
	cosGen->SetFillColor(kGreen+1);
	cosGen->SetFillStyle(3004);


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

	// ntracks selections
	TCut diag1 = " (Top1bntracks - Top1Genbntracks) == 0 " ;
	TCut diag2 = " (Top2bntracks - Top2Genbntracks) == 0 " ;
	TCut diag  = diag1 || diag2;
	
	TCut noTrk = " (Top1bntracks == 0) || (Top2bntracks == 0)" ;
	//TCut noTrk = " (Top1bntracks == 0)" ;

	// Total cut applied
	TCut cuts = rcTW + hadM + pcut + gcut + methodAll;
	//TCut cuts = rcTW + hadM + pcut + gcut + methodAll + diag;
	
	TCut cutGen1 = "qMCBcostheta > 0 && qMCBcostheta > -2" + noTrk;
	TCut cutGen2 = "qMCBcostheta < 0 && qMCBcostheta > -2" + noTrk;

	c1->cd();
	int forward = normaltree->Draw("qMCBcostheta >> cosGen",cutGen1);
	int backward = normaltree->Draw("qMCBcostheta >> +cosGen",cutGen2);

	cosGen->SetStats(0);
	TF1 * fgen = new TF1("fgen","pol2",-1,1);
	TF1 * freco = new TF1("freco","pol2",-0.9,0.9);
	fgen->SetLineColor(kGreen);
	fgen->SetLineStyle(3);
	freco->SetLineStyle(3);

	cosGen->SetMinimum(0);
	cosGen->Draw("he");
	fgen->Draw("same");
	cosGen->SetMinimum(0);
	TLegend *legendMean2 = new TLegend(0.20,0.75,0.6,0.85,NULL,"brNDC");
	legendMean2->SetFillColor(kWhite);
	legendMean2->SetBorderSize(0);
	legendMean2->AddEntry(cosGen,"Generated","f");
	legendMean2->Draw();

	TLatex latex;
	latex.SetTextFont(72);
	latex.DrawLatexNDC(0.21,0.7,"ILD #bf{Preliminary}");

	gPad->SetLeftMargin(0.14);
	cosGen->GetYaxis()->SetTitleOffset(1.7);

	c2->cd();
	normaltree->Draw("totalEnergy >> EneGenTrk");
	normaltree->Draw("totalEnergy >> EneGenNoTrk",noTrk);
	
	EneGenTrk->SetLineColor(kRed);
	EneGenTrk->SetLineWidth(3);
	EneGenNoTrk->SetLineColor(kBlue);
	EneGenNoTrk->SetLineWidth(3);
	
	
	EneGenTrk->Draw();
	EneGenNoTrk->Draw("same");

}

