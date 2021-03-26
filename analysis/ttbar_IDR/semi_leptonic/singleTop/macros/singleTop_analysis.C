#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8

using namespace std;

void singleTop_analysis()
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
	
	TCanvas * c1     					= new TCanvas("c1", "Data-MC",0,0,500,500);
	//TH1F * genMass   					= new TH1F("genMass","; Top Mass (GeV); Events",100,150,200);
	//TH1F * genMass_noSingle   = new TH1F("genMass_noSingle","; Top Mass (GeV); Events",100,150,200);
	TH1F * genMass   					= new TH1F("genMass","; Top Mass (GeV); Events",400,0,400);
	TH1F * genMass_noSingle   = new TH1F("genMass_noSingle","; Top Mass (GeV); Events",400,0,400);
	TH1F * genCos   					= new TH1F("genCos",";cos#theta_{t}; Events / 0.07",30,-1,1);
	genCos->Sumw2();
	TH1F * genCos_noSingle		= new TH1F("genCos_noSingle",";cos#theta_{t}; Events / 0.07",30,-1,1);
	genCos_noSingle->Sumw2();


	TGaxis::SetMaxDigits(3);
	genMass->SetLineWidth(3);
	genMass->SetLineStyle(1);
	genMass->SetLineColor(kGray+1);

	genMass->GetYaxis()->SetTitleOffset(1.3);

	genMass_noSingle->SetLineWidth(3);
	genMass_noSingle->SetLineStyle(1);
	genMass_noSingle->SetLineColor(kRed+1);


	genCos->SetLineWidth(3);
	genCos->SetLineStyle(1);

	genCos_noSingle->SetLineWidth(3);
	genCos_noSingle->SetLineStyle(2);
	genCos_noSingle->SetLineColor(kGray+1);


	//int gen_mass  				 = normaltree->Draw("MCTopmass >> genMass","");
	//int gen_mass_nosingle  = normaltree->Draw("MCTopmass >> genMass_noSingle","singletopFlag == 0");

	//int gen_cos = GenTree->Draw("qMCcostheta >> genCos","qMCcostheta > -2");
	//int gen_cos_nosingle = GenTree->Draw("qMCcostheta >> genCos_noSingle","qMCcostheta > -2 && singletopFlag == 0");

	int gen_mass  				 = normaltree->Draw("MCTopmass >> genMass","qMCcostheta > -2 && qMCcostheta < -0.9");
	int gen_mass_nosingle  = normaltree->Draw("MCTopmass >> genMass_noSingle","qMCcostheta > -2 && qMCcostheta < -0.9 && singletopFlag == 0");

	// restrict to cos < -0.9
	int gen_cos = GenTree->Draw("qMCcostheta >> genCos","qMCcostheta > -2 && qMCcostheta < -0.9");
	int gen_cos_nosingle = GenTree->Draw("qMCcostheta >> genCos_noSingle","qMCcostheta > -2 && qMCcostheta < -0.9 && singletopFlag == 0");

	cout << "single top events = " << gen_mass - gen_mass_nosingle << endl;
	cout << "all gen events    = " << gen_mass << endl;


	float single_ratio = (float)(gen_mass - gen_mass_nosingle)/(float)(gen_mass) * 100;

	cout << "single top ratio = " << single_ratio << endl;

	genMass->SetAxisRange(0.,3E3,"Y");

	genMass->Draw();
	genMass_noSingle->Draw("same");

	TLegend *leg = new TLegend(0.2,0.75,0.5,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(genMass,"All Parton Level","l");
	leg->AddEntry(genMass_noSingle,"Single Top Rejected","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	QQBARLabel(0.8,0.2,"",1);

	c1->Update();



	TCanvas * c2     					= new TCanvas("c2", "Data-MC",0,0,500,500);
	genCos->Scale( 1 / genCos->GetEntries() );
	genCos_noSingle->Scale( 1 / genCos_noSingle->GetEntries() );

	genCos->SetMinimum(0);
	genCos_noSingle->SetMinimum(0);

	genCos->Draw("he");
	genCos_noSingle->Draw("hsame");

	TLegend *leg2 = new TLegend(0.2,0.75,0.5,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg2->SetTextFont(42);
	leg2->AddEntry(genCos,"All Parton Level","l");
	leg2->AddEntry(genCos_noSingle,"Single Top Rejected","l");
	leg2->SetFillColor(0);
	leg2->SetLineColor(0);
	leg2->SetShadowColor(0);
	leg2->Draw();

	QQBARLabel(0.8,0.2,"",1);

	c2->Update();









}

