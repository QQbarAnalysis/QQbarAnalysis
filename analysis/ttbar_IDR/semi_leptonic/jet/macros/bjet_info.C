#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)

using namespace std;
void bjet_info()
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

	// File Selector

	FileSelector fs;
	std::vector<FileSelector> rootfiles;
	std::ifstream in( "/home/ilc/yokugawa/macros/semi_leptonic/input/record.txt" );

	while( fs.input(in) ){
		rootfiles.push_back(fs);
	}

	int nrootfiles = 0;
	nrootfiles = rootfiles.size();
  
	cout << "nfiles = " << nrootfiles << endl;

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

	TTree * Stats      = (TTree*) file->Get( "Stats" ) ;
	TTree * GenTree    = (TTree*) file->Get( "GenTree" ) ;
	TTree * Summary    = (TTree*) file->Get( "Summary" );


	// Histograms
	
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * cosbjets_all = new TH1F("cosbjets_all", ";cos#theta_{t};Entries", 30,-1.0,1.0);
	TH1F * cosbjets_acc = new TH1F("cosbjets_acc", ";cos#theta_{t};Entries", 30,-1.0,1.0);
	TH1F * cosbjets_rej = new TH1F("cosbjets_rej", ";cos#theta_{t};Entries", 30,-1.0,1.0);

	// Histogram style

	TGaxis::SetMaxDigits(3);

	cosbjets_all->SetLineWidth(3);
	cosbjets_all->SetLineStyle(1);
	cosbjets_all->SetLineColor(kGray+1);
	cosbjets_all->SetFillColor(kGray+1);
	cosbjets_all->SetFillStyle(3004);

	cosbjets_acc->SetLineWidth(3);
	cosbjets_acc->SetLineStyle(2);
	cosbjets_acc->SetLineColor(kGreen+1);
	cosbjets_acc->SetFillColor(kGreen+1);
	cosbjets_acc->SetFillStyle(3004);

	cosbjets_rej->SetLineWidth(3);
	cosbjets_rej->SetLineStyle(2);
	cosbjets_rej->SetLineColor(kRed+1);
	cosbjets_rej->SetFillColor(kRed+1);
	cosbjets_rej->SetFillStyle(3004);

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
	TCut all  = methodAll;
	TCut cuts = rcTW + hadM + pcut + gcut + method1;
  TCut test = (!rcTW || !hadM || !pcut || !gcut);
	
	int jet_all = Stats->Draw("cosbjets >> cosbjets_all", all);
	int jet_acc = Stats->Draw("cosbjets >> cosbjets_acc", cuts);
	int jet_rej = Stats->Draw("cosbjets >> cosbjets_rej", !cuts);

	std::cout << "jet_all = " << jet_all << "\n";
	std::cout << "jet_acc = " << jet_acc << "\n";
	std::cout << "jet_rej = " << jet_rej << "\n";

	cosbjets_all->SetMinimum(0);
	cosbjets_all->Draw("");
	cosbjets_acc->SetMinimum(0);
	cosbjets_acc->Draw("same");
	cosbjets_rej->SetMinimum(0);
	cosbjets_rej->Draw("same");	


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
	
}

