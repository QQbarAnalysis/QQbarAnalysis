#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8

using namespace std;

void efficiency()
{
	int token=0;

	bool twoDmode = 1;

	// set plot style

	if(!twoDmode) SetQQbarStyle();

	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);  
	gStyle->SetOptTitle(1);
	gStyle->SetTitleBorderSize(0);
	gStyle->SetTitleStyle(0);
	gStyle->SetMarkerSize(0);
	gStyle->SetTitleX(0.2); 
	gStyle->SetTitleY(0.9); 

		// set margin sizes
	if (twoDmode){
		gStyle->SetPadTopMargin(0.1);
		gStyle->SetPadRightMargin(0.13);
		gStyle->SetPadBottomMargin(0.15);
		gStyle->SetPadLeftMargin(0.15);
	}


	// File Selector

	FileSelector fs;
	std::vector<FileSelector> rootfiles;
	std::ifstream in( "/home/ilc/yokugawa/macros/semi_leptonic/input/record2.txt" );

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

	TTree * Stats = (TTree*) file->Get( "Stats" ) ;
	TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;
	TTree * Summary = (TTree*) file->Get( "Summary" );




//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	%%%%%%%%%%%%  Histogram  %%%%%%%%%%%%%%%%%
//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	float cosMIN = -0.9;
	float cosMAX = -0.6;

	TCanvas * c1			= new TCanvas("c1", "cosTheta",0,0,500,500);

	TH1F * hallCos			= new TH1F("hallCos",";cos#theta_{t}; Entries",20.,cosMIN,cosMAX);
	hallCos->Sumw2();

	TH1F * hpassCos			= new TH1F("hpassCos",";cos#theta_{t}; Entries",20.,cosMIN,cosMAX);
	hpassCos->Sumw2();

	TH1F * hallBjetE		= new TH1F("hallBjetE",";bjet_{E} (GeV); Entries",50.,20.,200.0);
	hallBjetE->Sumw2();

	TH1F * hpassBjetE		= new TH1F("hpassBjetE",";bjet_{E} (GeV); Entries",50.,20.,200.0);
	hpassBjetE->Sumw2();

	TH1F * hallMCBCos		= new TH1F("hallMCBCos",";MC cos#theta_{b}; Entries",20.,-1.0,1.0);
	hallMCBCos->Sumw2();

	TH1F * hpassMCBCos		= new TH1F("hpassMCBCos",";MC cos#theta_{b}; Entries",20.,-1.0,1.0);
	hpassMCBCos->Sumw2();

	TH1F * hallMCTopCos		= new TH1F("hallMCTopCos",";MC cos#theta_{t}; Entries",20.,cosMIN,cosMAX);
	hallMCTopCos->Sumw2();

	TH1F * hpassMCTopCos		= new TH1F("hpassMCTopCos",";MC cos#theta_{t}; Entries",20.,cosMIN,cosMAX);
	hpassMCTopCos->Sumw2();

	TH2F * histMCTopCos_BjetE	= new TH2F("histMCTopCos_BjetE",";MC cos#theta_{t};b-jet Energy (GeV)",20,-1.0,1.0,50,0.,200);

	TH2F * histMCBCos_BjetE	= new TH2F("histMCBCos_BjetE",";MC cos#theta_{b};b-jet Energy (GeV)",20,-1.0,1.0,50,0.,200);


	TGaxis::SetMaxDigits(3);

	hallCos->SetLineWidth(3);
	hallCos->SetLineStyle(1);
	hallCos->SetLineColor(kGray+1);

	hpassCos->SetLineWidth(3);
	hpassCos->SetLineStyle(1);

	hallMCBCos->SetLineWidth(3);
	hallMCBCos->SetLineStyle(1);
	hallMCBCos->SetLineColor(kGray+1);

	hpassMCBCos->SetLineWidth(3);
	hpassMCBCos->SetLineStyle(1);

	hallMCTopCos->SetLineWidth(3);
	hallMCTopCos->SetLineStyle(1);
	hallMCTopCos->SetLineColor(kGray+1);

	hpassMCTopCos->SetLineWidth(3);
	hpassMCTopCos->SetLineStyle(1);



	////////////// Cuts //////////////

	TCut thru = "Thrust < 0.9";
	TCut hadM = "hadMass > 180 && hadMass < 420";
	TCut rcTW = "Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50";
	TCut pcut = "Top1bmomentum > 15 && Top2bmomentum > 15";
	TCut gcut = "(Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2";

	TCut cuts = rcTW + hadM + pcut + gcut;

	// Methods selection
	TCut methodAll = "methodTaken > 0";
	TCut method1 = "methodTaken == 1";
	TCut method2 = "methodTaken == 2";
	TCut method3 = "methodTaken == 3";
	TCut method4 = "methodTaken == 4";
	TCut method5 = "methodTaken == 5";
	TCut method6 = "methodTaken == 6";
	TCut method7 = "methodTaken == 7";

	TCut MCcos2  = "qMCcostheta > -2";
	TCut MCcos09 = "qMCcostheta < -0.9";

	TCut MCcosAbove09 = "qMCcostheta > -0.9";
	TCut MCcosBelow06 = "qMCcostheta < -0.6"; 
	TCut MC0906 = MCcosAbove09 + MCcosBelow06;

	TCut bmom1	 = "Top1bmomentum > 0";
	TCut bmom2	 = "Top2bmomentum > 0";
	TCut singleTopFlagON = "singletopFlag == 1";


//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	%%%%%%%%%%%%  Selection  %%%%%%%%%%%%%%%%%
//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


// Entry

//	int bjet1all	= Stats->Draw("jet_E[0] >> jetE1all",MCcos2);

// Selection

//  SingleTop && Cos0.9 && Method1
//	int bjet1 		= Stats->Draw("jet_E[0] >> jetE1",   MCcos2 + MCcos09 + method1); //(crystalball)
//	int bjet1_2		= Stats->Draw("jet_E[0] >> jetE1_2", MCcos2 + MCcos09 + method1 + singleTopFlagON); //(crystalball)
//	int bjet1_3		= Stats->Draw("jet_E[0] >> jetE1_3", MCcos2 + MCcos09 + method1 + !singleTopFlagON); //(crystalball)


//  SingleTop && Cos0.9
//	int bjet1 		= Stats->Draw("jet_E[0] >> jetE1", MCcos2 + MCcos09 + singleTopFlagON); //(crystalball)
	
// SingleTop
//	int bjet1 		= Stats->Draw("jet_E[0] >> jetE1", MCcos2 + singleTopFlagON); //(dgaus)


// Cos0.9
//	int bjet1 		= Stats->Draw("jet_E[0] >> jetE1", MCcos2 + MCcos09); //(flognormal)
//	int bjet1_2		= Stats->Draw("jet_E[0] >> jetE1_2", MCcos2 + MCcos09 + singleTopFlagON); //(flognormal)
//	int bjet1_3		= Stats->Draw("jet_E[0] >> jetE1_3", MCcos2 + MCcos09 + !singleTopFlagON); //(flognormal)


// Method1
//	int bjet1 		= Stats->Draw("jet_E[0] >> jetE1", MCcos2 + method1); //(tgaus)

// All
//	int bjet1 		= Stats->Draw("jet_E[0] >> jetE1",   MCcos2);
//	int bjet1_2		= Stats->Draw("jet_E[0] >> jetE1_2", MCcos2 + method1); //(tgaus)
//	int bjet1_3		= Stats->Draw("jet_E[0] >> jetE1_3", MCcos2 + singleTopFlagON); //(tgaus)



	int allCos  = Stats->Draw("qCostheta >> hallCos",  MCcos2 + MC0906);
	int passCos = Stats->Draw("qCostheta >> hpassCos", MCcos2 + method1 + MC0906);

	int allBjetE  = Stats->Draw("jet_E[0] >> hallBjetE",  MCcos2);
	int passBjetE = Stats->Draw("jet_E[0] >> hpassBjetE", MCcos2 + method1);

	int allMCBCos  = Stats->Draw("qMCBcostheta >> hallMCBCos",  MCcos2);
	int passMCBCos = Stats->Draw("qMCBcostheta >> hpassMCBCos", MCcos2 + method1);

	int allMCTopCos  = Stats->Draw("qMCcostheta >> hallMCTopCos",  MCcos2 + MC0906);
	int passMCTopCos = Stats->Draw("qMCcostheta >> hpassMCTopCos", MCcos2 + method1 + MC0906);

	int MCTopCos_BjetE = Stats->Draw("jet_E[0]:qMCcostheta >> histMCTopCos_BjetE", MCcos2 + method1);

	int MCBCos_BjetE = Stats->Draw("jet_E[0]:qMCBcostheta >> histMCBCos_BjetE", MCcos2);


//	cout << "Number of Events\n";
//	cout << "Events ALL: " << hallCos->GetEntries() << "\n";
//	cout << "Events PASS: " << hpassCos->GetEntries() << "\n";

	cout << "GenTree Number = " << GenTree->GetEntries() << "\n";

	cout << "Stats Number = " << Stats->GetEntries() << "\n";

	cout << "Number of Events (qMCcostheta)\n";
	cout << "Events ALL: " << hallMCTopCos->GetEntries() << "\n";

	cout << "Number of Events (hallBjetE)\n";
	cout << "Events ALL: " << hallBjetE->GetEntries() << "\n";

	cout << "Number of Events (hallMCBCos)\n";
	cout << "Events ALL: " << hallMCBCos->GetEntries() << "\n";



//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	%%%%%%%%%%  Normalization  %%%%%%%%%%%%%%%
//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	double intALLCos   = hallCos->Integral(2,19);
	double intPASSCos  = hpassCos->Integral(2,19);


//	hall->Scale( 1 / intALL, "width" );
//	hpass->Scale( 1 / intPASS, "width" );

	hallCos->SetMinimum(0);
	hpassCos->SetMinimum(0);

	hallBjetE->SetMinimum(0);
	hpassBjetE->SetMinimum(0);

	hallMCBCos->SetMinimum(0);
	hpassMCBCos->SetMinimum(0);

	hallMCTopCos->SetMinimum(0);
	hpassMCTopCos->SetMinimum(0);


//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	%%%%%%%%%%%%%%%  Draw  %%%%%%%%%%%%%%%%%%%
//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	hallCos->Draw("he");
	hpassCos->Draw("hsame");

	c1->Update();

	TCanvas * c2			= new TCanvas("c2", "cBjetE",0,0,500,500);

	hallBjetE->Draw("he");
	hpassBjetE->Draw("hsame");

	c2->Update();


	TCanvas * c3			= new TCanvas("c3", "CosEfficiency",0,0,500,500);

	TEfficiency* pEffCos = 0;

	if(TEfficiency::CheckConsistency(*hpassCos,*hallCos)){

		pEffCos = new TEfficiency(*hpassCos,*hallCos);
		pEffCos->Draw("ap");
		pEffCos->SetTitle(";cos#theta_{t};Fraction");

	}

	TCanvas * c4			= new TCanvas("c4", "bjetEEfficiency",0,0,500,500);

	TEfficiency* pEffBjetE = 0;

	if(TEfficiency::CheckConsistency(*hpassBjetE,*hallBjetE)){

		pEffBjetE = new TEfficiency(*hpassBjetE,*hallBjetE);
		pEffBjetE->Draw("ap");
		pEffBjetE->SetTitle(";bjet_{E} (GeV);Fraction");

	}


	TCanvas * c5			= new TCanvas("c5", "cMCBCos",0,0,500,500);

	hallMCBCos->Draw("he");
	hpassMCBCos->Draw("hsame");

	c5->Update();


	TCanvas * c6			= new TCanvas("c6", "MCBCosEfficiency",0,0,500,500);

	TEfficiency* pEffMCBCos = 0;

	if(TEfficiency::CheckConsistency(*hpassMCBCos,*hallMCBCos)){

		pEffMCBCos = new TEfficiency(*hpassMCBCos,*hallMCBCos);
		pEffMCBCos->Draw("ap");
		pEffMCBCos->SetTitle(";MC cos#theta_{b};Fraction");

	}

	TCanvas * c7			= new TCanvas("c7", "cMCCos",0,0,500,500);

	hallMCTopCos->Draw("he");
	hpassMCTopCos->Draw("hsame");

	c7->Update();


	TCanvas * c8			= new TCanvas("c8", "MCCosEfficiency",0,0,500,500);

	TEfficiency* pEffMCTopCos = 0;

	if(TEfficiency::CheckConsistency(*hpassMCTopCos,*hallMCTopCos)){

		pEffMCTopCos = new TEfficiency(*hpassMCTopCos,*hallMCTopCos);
		pEffMCTopCos->Draw("ap");
		pEffMCTopCos->SetTitle(";MC cos#theta_{t};Fraction");

	}

	TCanvas * c9			= new TCanvas("c9", "cMCTopCos_BjetE",0,0,500,500);

	histMCTopCos_BjetE->Draw("COLZ");
	c9->Update();

	TCanvas * c10			= new TCanvas("c10", "cMCBCos_BjetE",0,0,500,500);

	histMCBCos_BjetE->Draw("COLZ");
	c10->Update();





}

