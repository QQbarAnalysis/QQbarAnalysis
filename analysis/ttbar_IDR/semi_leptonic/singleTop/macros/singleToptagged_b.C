#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8

using namespace std;

void singleToptagged_b()
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

	TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
	TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;
	TTree * Summary = (TTree*) file->Get( "Summary" );

	// Histograms
	
	TCanvas * c1     			= new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * genCos   			= new TH1F("genCos",";cos#theta_{B}; Events / 0.07",30,-1,1);
	genCos->Sumw2();
	TH1F * genCos_noSingle		= new TH1F("genCos_noSingle",";cos#theta_{B}; Events / 0.07",30,-1,1);
	genCos_noSingle->Sumw2();

	TGaxis::SetMaxDigits(3);

	genCos->SetLineWidth(3);
	genCos->SetLineStyle(1);

	genCos_noSingle->SetLineWidth(3);
	genCos_noSingle->SetLineStyle(2);
	genCos_noSingle->SetLineColor(kGray+1);

	int gen_cos = GenTree->Draw("qMCBcostheta[0] >> genCos","qMCcostheta > -2");
	int gen_cos_nosingle = GenTree->Draw("qMCBcostheta[0] >> genCos_noSingle","qMCcostheta > -2 && singletopFlag == 0");

	genCos->Scale( 1 / genCos->GetEntries() );
	genCos_noSingle->Scale( 1 / genCos_noSingle->GetEntries() );

	genCos->SetMinimum(0);
	genCos_noSingle->SetMinimum(0);

	genCos->Draw("he");
	genCos_noSingle->Draw("hsame");

	TLegend *leg = new TLegend(0.2,0.75,0.5,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(genCos,"All Parton Level","l");
	leg->AddEntry(genCos_noSingle,"Single Top Rejected","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	QQBARLabel(0.8,0.2,"",1);

	c1->Update();








}

