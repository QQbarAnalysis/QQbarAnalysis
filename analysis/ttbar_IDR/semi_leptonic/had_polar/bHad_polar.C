
#include <unistd.h>
#include <iostream>
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void bHad_polar()
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
				case 0 : filename1 = "leptonic_yyxyev_eLeR_new_small.root";
						 break;
				case 1 : filename1 = "leptonic_yyxyev_eLeR_new_large.root";
						 break;
				case 2 : filename1 = "leptonic_yyxyev_eLeR_new_large_QQbar.root";
						 break;
				case 3 : filename1 = "leptonic_yyxyev_eLeR_old_lcut.root" ;
						 break;
				case 4 : filename1 = "leptonic_yyxylv_eLeR_iso_lep_lcut.root" ;
						 break;
		}

		string filename = filename0 + filename1;
		cout << "Processing : " << filename << " ..." << endl;

		TFile * file = TFile::Open(filename.c_str());

		int bin_e = 30;
		int max_e = 1;
		
		TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
		
		TH1F * cosReco = new TH1F("cosReco", "E(Ntracks)", bin_e,-1.0,max_e);
		cosReco->Sumw2();
		TH1F * cosGen = new TH1F("cosGen", ";cos#theta_{topHad};Entries", bin_e,-1.0,max_e);
		cosGen->Sumw2();

		//TTree * normaltree = Stats;
		TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
		TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;
		//cosReco->SetLineColor(kBlue);
		cosReco->SetLineWidth(3);
		cosGen->SetLineWidth(3);
		cosGen->SetLineStyle(2);
		cosGen->SetLineColor(kGreen+1);
		cosGen->SetFillColor(kGreen+1);
		cosGen->SetFillStyle(3004);

		//int forward = GenTree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && qMCcostheta > -2 ");
		//int backward = GenTree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && qMCcostheta > -2");
		int forward = GenTree->Draw("qMCBcostheta >> cosGen","qMCBcostheta > 0 && qMCBcostheta > -2 ");
		int backward = GenTree->Draw("qMCBcostheta >> +cosGen","qMCBcostheta < 0 && qMCBcostheta > -2");
		
		
		///////////////
		// BASE CUTS //
		///////////////

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
		TCut cuts = rcTW + hadM + method7;

		TCut fcuts = "Top1bcostheta > 0" + cuts;
		TCut bcuts = "Top1bcostheta < 0" + cuts;

		// Top hadronic angle
		int recoforward = normaltree->Draw("-Top1bcostheta*Top2leptonCharge >> cosReco", fcuts);
		int recobackward = normaltree->Draw("-Top1bcostheta*Top2leptonCharge >> +cosReco", bcuts);

		///////// NOTE //////////
		// Top1bcostheta exists while Top2bcostheta don't


		cosGen->SetStats(0);
		TF1 * fgen = new TF1("fgen","pol2",-1,1);
		TF1 * freco = new TF1("freco","pol2",-0.9,0.9);
		fgen->SetLineColor(kGreen);
		fgen->SetLineStyle(3);
		freco->SetLineStyle(3);
		cosGen->Scale(cosReco->GetEntries()/ cosGen->GetEntries());
		cosGen->Fit("fgen","Q");
		cosReco->Fit("freco", "QR");
		cosGen->SetMinimum(0);
		cosGen->Draw("he");
		fgen->Draw("same");
		cosGen->SetMinimum(0);
		cosReco->Draw("samee");
		TLegend *legendMean2 = new TLegend(0.20,0.75,0.6,0.85,NULL,"brNDC");
		legendMean2->SetFillColor(kWhite);
		legendMean2->SetBorderSize(0);
		legendMean2->AddEntry(cosGen,"Generated","f");
		legendMean2->AddEntry(cosReco,"Reconstructed","f");
		legendMean2->Draw();
		float afbgen = (float)(forward - backward) / (float) (forward + backward);
		float afbreco = (float)(recoforward - recobackward) / (float) (recoforward + recobackward);

		
		cout << "--------------------------------------------------------------\n";
		cout << "--------------------------------------------------------------\n";
		std::cout << "Afb gen: " << afbgen << " N: " << forward + backward <<  "\n";
		std::cout << "Afb reco: " << afbreco << " N: " << recoforward + recobackward << "(" << afbreco / afbgen *100 << "%)"  << "\n";
		std::cout << "Chi2: " << cosReco->Chi2Test(cosGen,"UUNORMCHI2/NDF") << "\n";
		cout << "--------------------------------------------------------------\n";
		float afbgenf = (fgen->Integral(0,1) - fgen->Integral(-1,0)) / (fgen->Integral(0,1) + fgen->Integral(-1,0));
		float afbrecof = (freco->Integral(0,1) - freco->Integral(-1,0)) / (freco->Integral(0,1) + freco->Integral(-1,0));
		gPad->SetLeftMargin(0.14);
		cosGen->GetYaxis()->SetTitleOffset(1.7);
		cout << "Afb gen functional: " << afbgenf << endl;
		cout << "Afb reco functional: " << afbrecof << "(" << afbrecof / afbgenf *100 << "%)"   << endl;
		float nominal = 30.8;
		float efficiency = (float)(recoforward + recobackward)/(forward + backward) * 2 * 100;
		cout << "Final efficiency: " << efficiency << "% (+" << efficiency / nominal *100 -100 << "%)\n" ;
		cout << "--------------------------------------------------------------\n";
		cout << "--------------------------------------------------------------\n";
		//file->Close();
}

