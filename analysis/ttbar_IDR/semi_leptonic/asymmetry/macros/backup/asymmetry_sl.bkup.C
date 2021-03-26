#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"

//#include "rootlogon.C"
//#include "bilo_sty.C"
#define MAXV 8

using namespace std;
void asymmetry_sl()
{

	// initialize variables
	int styl = 0;
	int cx   = 500;
	double Legx1 = 0.20;
	double Legx2 = 0.6;

	int token_l5=0;
	int token_s5=0;

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

	std::cout << "Enter code for l5: ";
	std::cin >> token_l5;
	std::cout << "Enter code for s5: ";
	std::cin >> token_s5;

	std::cout << std::endl;

	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,cx,500);

  ////////////// Detector Model LARGE //////////////

	std::string filename_l5 = rootfiles[token_l5].filename();
	cout << "Processing (l5) : " << filename_l5 << " ..." << endl;

	TFile * file_l5 = TFile::Open(filename_l5.c_str());

	int bin_e = 30;
	int max_e = 1;

	TH1F * cosReco_l5 = new TH1F("cosReco_l5", "E(Ntracks)", bin_e,-1.0,max_e);
	cosReco_l5->Sumw2();
	TH1F * cosGen = new TH1F("cosGen", ";cos#theta_{t};Entries", bin_e,-1.0,max_e);
	cosGen->Sumw2();

	TGaxis::SetMaxDigits(3);

	TTree * normaltree_l5 = (TTree*) file_l5->Get( "Stats" ) ;
	TTree * GenTree = (TTree*) file_l5->Get( "GenTree" ) ;

	cosReco_l5->SetLineWidth(3);
	cosGen->SetLineWidth(3);
	cosGen->SetLineStyle(2);
	cosGen->SetLineColor(kGreen+1);
	cosGen->SetFillColor(kGreen+1);
	cosGen->SetFillStyle(3004);


  ////////////// Detector Model SMALL //////////////

	std::string filename_s5 = rootfiles[token_s5].filename();
	cout << "Processing (s5) : " << filename_s5 << " ..." << endl;

	TFile * file_s5 = TFile::Open(filename_s5.c_str());

	TH1F * cosReco_s5 = new TH1F("cosReco_s5", "E(Ntracks)", bin_e,-1.0,max_e);
	cosReco_s5->Sumw2();

	TTree * normaltree_s5 = (TTree*) file_s5->Get( "Stats" ) ;

	cosReco_s5->SetLineWidth(3);

  ////////////// Analysis //////////////

	int forward = GenTree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && qMCcostheta > -2 ");
	int backward = GenTree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && qMCcostheta > -2");

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
	//TCut cuts = rcTW + hadM + pcut + gcut + (method1|| method2|| method3|| method4);

	TCut fcuts = "qCostheta > 0" + cuts;
	TCut bcuts = "qCostheta < 0 && qCostheta > -1.0 " + cuts;

  // l5
	int recoforward_l5 = normaltree_l5->Draw("qCostheta >> cosReco_l5", fcuts);
	int recobackward_l5 = normaltree_l5->Draw("qCostheta >> +cosReco_l5", bcuts);
  // s5
	int recoforward_s5 = normaltree_s5->Draw("qCostheta >> cosReco_s5", fcuts);
	int recobackward_s5 = normaltree_s5->Draw("qCostheta >> +cosReco_s5", bcuts);
	

	cosGen->SetStats(0);
	TF1 * fgen = new TF1("fgen","pol2",-1,1);
	TF1 * freco_l5 = new TF1("freco_l5","pol2",-0.9,0.9);
	TF1 * freco_s5 = new TF1("freco_s5","pol2",-0.9,0.9);
	fgen->SetLineColor(kGreen);
	fgen->SetLineStyle(3);
	freco_l5->SetLineStyle(3);
	freco_s5->SetLineStyle(3);

	//cosGen->Scale(cosReco_l5->GetEntries()/ cosGen->GetEntries());
	double intCosReco_l5 = cosReco_l5->Integral(2,29);
	double intCosReco_s5 = cosReco_s5->Integral(2,29);
	double intCosGen  = cosGen->Integral(2,29);
	cosGen->Scale(intCosReco_l5 / intCosGen);
	
	cosGen->Fit("fgen","Q");
	cosReco_l5->Fit("freco_l5", "QR");
	cosGen->SetMinimum(0);
	cosGen->Draw("he");
	fgen->Draw("same");
	cosGen->SetMinimum(0);
	cosReco_l5->Draw("samee");

	TLegend *leg = new TLegend(0.2,0.75,0.6,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(cosGen,"Parton level","l");
	leg->AddEntry(cosReco_l5,"Reconstructed","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	QQBARLabel(0.8,0.2,"",1);
	c1->Update();

	float afbgen = (float)(forward - backward) / (float) (forward + backward);
	float afbreco = (float)(recoforward_l5 - recobackward_l5) / (float) (recoforward_l5 + recobackward_l5);


	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";
	std::cout << "Afb gen: " << afbgen << " N: " << forward + backward <<  "\n";
	std::cout << "Afb reco: " << afbreco << " N: " << recoforward_l5 + recobackward_l5 << "(" << afbreco / afbgen *100 << "%)"  << "\n";
	std::cout << "Chi2: " << cosReco_l5->Chi2Test(cosGen,"UUNORMCHI2/NDF") << "\n";
	cout << "--------------------------------------------------------------\n";
	float afbgenf = (fgen->Integral(0,1) - fgen->Integral(-1,0)) / (fgen->Integral(0,1) + fgen->Integral(-1,0));
	float afbrecof = (freco_l5->Integral(0,1) - freco_l5->Integral(-1,0)) / (freco_l5->Integral(0,1) + freco_l5->Integral(-1,0));

	gPad->SetLeftMargin(0.14);
	cosGen->GetYaxis()->SetTitleOffset(1);

	cout << "Afb gen functional: " << afbgenf << endl;
	cout << "Afb reco functional: " << afbrecof << "(" << afbrecof / afbgenf *100 << "%)"   << endl;
	float nominal = 30.8;

	float efficiency = (float)(recoforward_l5 + recobackward_l5)/(forward + backward) * 2 * 100;
	cout << "Final efficiency: " << efficiency << "% (+" << efficiency / nominal *100 -100 << "%)\n" ;
	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";
	//file->Close();
	
}

