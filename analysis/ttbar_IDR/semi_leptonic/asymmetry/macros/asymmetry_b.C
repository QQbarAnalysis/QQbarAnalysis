#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)
void asymmetry_b()
{
	int token=0;

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

	FileSelector fs;
	std::vector<FileSelector> rootfiles;
	std::ifstream in( "/home/ilc/yokugawa/macros/semi_leptonic/input/record.txt" );

	while( fs.input(in) ){
		rootfiles.push_back(fs);
	}

	int nrootfiles = 0;
	nrootfiles = rootfiles.size();

	std::cout << "Choose a file from below:" << std::endl;
	for( int i=0; i < nrootfiles; i++){
		std::cout << i << ": " << rootfiles[i].info() << endl;
	}

	std::cout << "Enter code: ";
	std::cin >> token;
	std::cout << std::endl;

	std::string filename = rootfiles[token].filename();
	cout << "Processing : " << filename << " ..." << endl;

	TFile * file = TFile::Open(filename.c_str());

	int bin_e = 30;
	int max_e = 1;

	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);

	TH1F * cosReco = new TH1F("cosReco", "E(Ntracks)", bin_e,-1.0,max_e);
	cosReco->Sumw2();
	TH1F * cosGen = new TH1F("cosGen", ";cos#theta_{b};Entries", bin_e,-1.0,max_e);
	cosGen->Sumw2();

	TH1F * cosGen_wsingleTop = new TH1F("cosGen_wsingleTop", ";cos#theta_{t};Entries", bin_e,-1.0,max_e);
	cosGen_wsingleTop->Sumw2();

	TGaxis::SetMaxDigits(3);

	TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
	TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;

	cosReco->SetLineWidth(3);
	cosGen->SetLineWidth(3);
	cosGen_wsingleTop->SetLineWidth(3);

	cosGen->SetLineStyle(2);
	cosGen_wsingleTop->SetLineStyle(2);

	cosGen->SetLineColor(kGreen+1);
	cosGen->SetFillColor(kGreen+1);
	cosGen->SetFillStyle(3004);

	cosGen_wsingleTop->SetLineColor(kBlue+1);
	cosGen_wsingleTop->SetFillColor(kBlue+1);
	cosGen_wsingleTop->SetFillStyle(3004);

	int forward = GenTree->Draw("qMCBcostheta >> cosGen","qMCBcostheta > 0 && qMCBcostheta > -2 && singletopFlag == 0");
	int backward = GenTree->Draw("qMCBcostheta >> +cosGen","qMCBcostheta < 0 && qMCBcostheta > -2 && singletopFlag == 0");

	int forward2 = GenTree->Draw("qMCcostheta >> cosGen_wsingleTop","qMCBcostheta > 0 && qMCBcostheta > -2");
	int backward2 = GenTree->Draw("qMCcostheta >> +cosGen_wsingleTop","qMCBcostheta < 0 && qMCBcostheta > -2");

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

	// ntracks selections (correct)
	TCut diag1 = " (Top1bntracks - Top1Genbntracks) == 0 " ;
	TCut diag2 = " (Top2bntracks - Top2Genbntracks) == 0 " ;
	TCut diag  = diag1 || diag2;

	// ntracks selections (not correct)	
	//TCut diag1 = " (Top1bntracks - Top1Genbntracks) != 0 " ;
	//TCut diag2 = " (Top2bntracks - Top2Genbntracks) != 0 " ;
	//TCut diag  = diag1 && diag2;
	
	// Total cut applied
	TCut cuts = rcTW + hadM + pcut + gcut + methodAll;
	//TCut cuts = rcTW + hadM + pcut + gcut + methodAll + diag;

	TCut fcuts = "qBCostheta > 0" + cuts;
	TCut bcuts = "qBCostheta < 0 && qBCostheta > -1.0 " + cuts;

	int recoforward = normaltree->Draw("qBCostheta >> cosReco", fcuts);
	int recobackward = normaltree->Draw("qBCostheta >> +cosReco", bcuts);

	cosGen->SetStats(0);
	TF1 * fgen = new TF1("fgen","pol2",-1,1);
	TF1 * freco = new TF1("freco","pol2",-0.9,0.9);
	fgen->SetLineColor(kGreen);
	fgen->SetLineStyle(3);
	freco->SetLineStyle(3);

	//cosGen->Scale(cosReco->GetEntries()/ cosGen->GetEntries());
	double intCosReco = cosReco->Integral(2,29);
	double intCosGen  = cosGen->Integral(2,29);
	cosGen->Scale(intCosReco / intCosGen);


	cosGen->Fit("fgen","Q");
	cosReco->Fit("freco", "QR");
	cosGen->SetMinimum(0);
	cosGen->Draw("he");
	fgen->Draw("same");
	cosGen->SetMinimum(0);
	cosReco->Draw("samee");

/*
	TLegend *legendMean2 = new TLegend(0.20,0.75,0.6,0.85,NULL,"brNDC");
	legendMean2->SetFillColor(kWhite);
	legendMean2->SetBorderSize(0);
	legendMean2->AddEntry(cosGen,"Generated","f");
	legendMean2->AddEntry(cosReco,"Reconstructed","f");
	legendMean2->Draw();

	TLatex latex;
	latex.SetTextFont(72);
	latex.DrawLatexNDC(0.21,0.7,"ILD #bf{Preliminary}");
*/

	TLegend *leg = new TLegend(0.2,0.75,0.6,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(cosGen,"Generated","l");
	leg->AddEntry(cosReco,"Reconstructed","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	QQBARLabel(0.8,0.2,"",1);
	c1->Update();

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
	cosGen->GetYaxis()->SetTitleOffset(1);

	cout << "Afb gen functional: " << afbgenf << endl;
	cout << "Afb reco functional: " << afbrecof << "(" << afbrecof / afbgenf *100 << "%)"   << endl;
	float nominal = 30.8;
	float efficiency = (float)(recoforward + recobackward)/(forward + backward) * 2 * 100;
	cout << "Final efficiency: " << efficiency << "% (+" << efficiency / nominal *100 -100 << "%)\n" ;
	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";
	//file->Close();
}

