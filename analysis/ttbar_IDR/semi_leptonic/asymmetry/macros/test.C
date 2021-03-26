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
void test()
{

	// initialize variables
	int styl = 0;
	int cx   = 500;
	double Legx1 = 0.20;
	double Legx2 = 0.6;

	int token=0;

	int bin_e = 30;
	int max_e = 1;

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
	//std::ifstream in( "/home/ilc/yokugawa/macros/semi_leptonic/input/test.txt" );

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

  std::string filename2 = "/hsm/ilc/users/vlohezic/preset_N_run/l5/electron+muon/QQbarProcessor_out/root_merge/IsoLepTagged.eR.pL_electron+muon_QQbar.root";

  TFile * file2 = TFile::Open(filename2.c_str());

	TGaxis::SetMaxDigits(3);

	TTree * normaltree = (TTree*) file->Get( "Stats" ) ;
	TTree * normaltree2 = (TTree*) file2->Get( "Stats" ) ;
	TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;

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

	TCanvas * c2 = new TCanvas("c2", "Data-MC",0,0,cx,500);
	TH1F * bmom  = new TH1F("bmomhist", "eLpR;bmom (GeV); Entries", 100, 0,200);

  int bmomentum = normaltree->Draw("Top1bmomentum >> bmomhist",fcuts||bcuts);
  int bmomentum2= normaltree->Draw("Top2bmomentum >> +bmomhist",fcuts||bcuts);

	bmom->Draw();

	TCanvas * c3 = new TCanvas("c3", "Data-MC",0,0,cx,500);
	TH1F * bmom2  = new TH1F("bmomhist2", "eRpL;bmom (GeV); Entries", 100, 0,200);

  bmomentum = normaltree2->Draw("Top1bmomentum >> bmomhist2",fcuts||bcuts);
  bmomentum2= normaltree2->Draw("Top2bmomentum >> +bmomhist2",fcuts||bcuts);

	bmom2->Draw();

	
}

