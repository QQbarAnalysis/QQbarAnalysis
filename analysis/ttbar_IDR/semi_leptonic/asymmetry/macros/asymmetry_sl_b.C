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
void asymmetry_sl_b()
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
	gStyle->SetMarkerSize(1);
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


  ////////////// Cuts //////////////

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

	TCut fcuts = "qBCostheta > 0" + cuts;
	TCut bcuts = "qBCostheta < 0 && qBCostheta > -1.0 " + cuts;



  ////////////// Detector Model LARGE //////////////

	std::string filename_l5 = rootfiles[token_l5].filename();
	cout << "Processing (l5) : " << filename_l5 << " ..." << endl;

	TFile * file_l5 = TFile::Open(filename_l5.c_str());

	int bin_e = 20;
	int max_e = 1;

	TH1F * cosReco_l5 = new TH1F("cosReco_l5", "E(Ntracks)", bin_e,-1.0,max_e);
	cosReco_l5->Sumw2();
	TH1F * cosGen_l5 = new TH1F("cosGen_l5", ";cos#theta_{b};Entries", bin_e,-1.0,max_e);
	cosGen_l5->Sumw2();

	TGaxis::SetMaxDigits(3);

	TTree * normaltree_l5 = (TTree*) file_l5->Get( "Stats" ) ;
	TTree * GenTree_l5 = (TTree*) file_l5->Get( "GenTree" ) ;

	cout << "l5Reco Entry = " << normaltree_l5->GetEntries() << endl;
	cout << "l5Gen Entry = " << GenTree_l5->GetEntries() << endl;

	int forward_l5  = GenTree_l5->Draw("qMCBcostheta >> cosGen_l5","qMCBcostheta > 0 && qMCBcostheta > -2 ");
	int backward_l5 = GenTree_l5->Draw("qMCBcostheta >> +cosGen_l5","qMCBcostheta < 0 && qMCBcostheta > -2");

	int recoforward_l5  = normaltree_l5->Draw("qBCostheta >> cosReco_l5", fcuts);
	int recobackward_l5 = normaltree_l5->Draw("qBCostheta >> +cosReco_l5", bcuts);

	double intCosReco = cosReco_l5->Integral(2,19);
	double intCosGen  = cosGen_l5->Integral(2,19);
	cosGen_l5->Scale(intCosReco / intCosGen);


  ////////////// Detector Model SMALL //////////////

	std::string filename_s5 = rootfiles[token_s5].filename();
	cout << "Processing (s5) : " << filename_s5 << " ..." << endl;

	TFile * file_s5 = TFile::Open(filename_s5.c_str());

	TH1F * cosReco_s5 = new TH1F("cosReco_s5", "E(Ntracks)", bin_e,-1.0,max_e);
	cosReco_s5->Sumw2();
	TH1F * cosGen_s5 = new TH1F("cosGen_s5", ";cos#theta_{b};Entries", bin_e,-1.0,max_e);
	cosGen_s5->Sumw2();

	TTree * normaltree_s5 = (TTree*) file_s5->Get( "Stats" ) ;
	TTree * GenTree_s5 = (TTree*) file_s5->Get( "GenTree" ) ;

	cout << "s5Reco Entry = " << normaltree_s5->GetEntries() << endl;
	cout << "s5Gen Entry = " << GenTree_s5->GetEntries() << endl;

	int forward_s5  = GenTree_s5->Draw("qMCcostheta >> cosGen_s5","qMCcostheta > 0 && qMCcostheta > -2 ");
	int backward_s5 = GenTree_s5->Draw("qMCcostheta >> +cosGen_s5","qMCcostheta < 0 && qMCcostheta > -2");

	int recoforward_s5  = normaltree_s5->Draw("qBCostheta >> cosReco_s5", fcuts);
	int recobackward_s5 = normaltree_s5->Draw("qBCostheta >> +cosReco_s5", bcuts);

	double intCosReco2 = cosReco_s5->Integral(2,19);
	double intCosGen2  = cosGen_s5->Integral(2,19);
	cosGen_s5->Scale(intCosReco2 / intCosGen2);

	// test
	cosReco_s5->Scale(intCosReco / intCosReco2);


  ////////////// Style Setting //////////////

	cosReco_l5->SetLineWidth(3);
  cosReco_l5->SetLineColor(kBlue);
  cosReco_l5->SetMarkerColor(kBlue);
  cosReco_l5->SetMarkerStyle(21);

	cosReco_s5->SetLineWidth(3);
  cosReco_s5->SetLineColor(kRed);
  cosReco_s5->SetMarkerColor(kRed);
  cosReco_s5->SetMarkerStyle(22);
	cosReco_s5->SetLineStyle(2);

	cosGen_l5->SetLineWidth(3);
	//cosGen_l5->SetLineStyle(2);
	cosGen_l5->SetLineColor(kGreen+1);
	cosGen_l5->SetFillColor(kGreen+1);
	
	//cosGen_l5->SetLineColor(kGray+1);
	//cosGen_l5->SetFillColor(kGray+1);

	cosGen_l5->SetFillStyle(3004);
	cosGen_l5->SetStats(0);
	cosGen_l5->SetMinimum(0);

  //cosGen_l5->SetTitle("e_{L}^{-}e_{R}^{+}#rightarrow t#bar{t} @ 500GeV, 2.1 ab^{-1}");
  cosGen_l5->SetTitle("e_{L}^{-}e_{R}^{+}#rightarrow t#bar{t} @ 500GeV");
	cosGen_l5->GetXaxis()->SetTitleOffset(1.1);
  cosGen_l5->GetXaxis()->SetTitleFont(42);
  cosGen_l5->GetXaxis()->SetTitleSize(0.05);
  cosGen_l5->GetXaxis()->SetLabelSize(0.05);
  cosGen_l5->GetXaxis()->SetLabelOffset(0.015);

  cosGen_l5->GetYaxis()->SetTitle("Entries / 0.1");
	cosGen_l5->GetYaxis()->SetTitleOffset(1.4);
  cosGen_l5->GetYaxis()->SetTitleFont(42);
  cosGen_l5->GetYaxis()->SetTitleSize(0.05);
  cosGen_l5->GetYaxis()->SetLabelSize(0.05);
  cosGen_l5->GetYaxis()->SetLabelOffset(0.015);


  ////////////// Fitting //////////////

	TF1 * fgen = new TF1("fgen","pol2",-1,1);
	TF1 * freco_l5 = new TF1("freco_l5","pol2",-0.9,0.9);
	TF1 * freco_s5 = new TF1("freco_s5","pol2",-0.9,0.9);
	fgen->SetLineColor(kGreen);
	
	//fgen->SetLineColor(kGray);
	fgen->SetLineStyle(3);
	freco_l5->SetLineStyle(3);
	freco_l5->SetLineColor(kBlue+1);
	freco_s5->SetLineStyle(3);
	freco_s5->SetLineColor(kRed+1);
	
	cosGen_l5->Fit("fgen","Q");
	cosReco_l5->Fit("freco_l5", "QR");
	cosReco_s5->Fit("freco_s5", "QR");

  ////////////// Drawing //////////////

	cosGen_l5->Draw("he");
	fgen->Draw("same");
	cosReco_l5->Draw("samee");
	cosReco_s5->Draw("samee");

	//TLegend *leg = new TLegend(0.2,0.65,0.6,0.75); //set here your x_0,y_0, x_1,y_1 options
  TLegend *leg = new TLegend(0.2,0.65,0.55,0.8);
	leg->SetTextFont(42);
	leg->AddEntry(cosGen_l5,"Parton level","l");
	leg->AddEntry(cosReco_l5,"IDR-L","lep");
	leg->AddEntry(cosReco_s5,"IDR-S","lep");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	QQBARLabel(0.8,0.2,"",1);

	c1->Update();

  ////////////// Calculation //////////////

	float afbgen = (float)(forward_l5 - backward_l5) / (float) (forward_l5 + backward_l5);
	float afbreco = (float)(recoforward_l5 - recobackward_l5) / (float) (recoforward_l5 + recobackward_l5);

	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";
	std::cout << "Afb gen: " << afbgen << " N: " << forward_l5 + backward_l5 <<  "\n";
	std::cout << "Afb reco: " << afbreco << " N: " << recoforward_l5 + recobackward_l5 << "(" << afbreco / afbgen *100 << "%)"  << "\n";
	std::cout << "Chi2: " << cosReco_l5->Chi2Test(cosGen_l5,"UUNORMCHI2/NDF") << "\n";
	cout << "--------------------------------------------------------------\n";
	float afbgenf = (fgen->Integral(0,1) - fgen->Integral(-1,0)) / (fgen->Integral(0,1) + fgen->Integral(-1,0));
	float afbrecof = (freco_l5->Integral(0,1) - freco_l5->Integral(-1,0)) / (freco_l5->Integral(0,1) + freco_l5->Integral(-1,0));

	//gPad->SetLeftMargin(0.14);
	//cosGen_l5->GetYaxis()->SetTitleOffset(1);

	cout << "Afb gen functional: " << afbgenf << endl;
	cout << "Afb reco functional: " << afbrecof << "(" << afbrecof / afbgenf *100 << "%)"   << endl;
	float nominal = 30.8;

	float efficiency = (float)(recoforward_l5 + recobackward_l5)/(forward_l5 + backward_l5) * 2 * 100;
	cout << "Final efficiency: " << efficiency << "% (+" << efficiency / nominal *100 -100 << "%)\n" ;
	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";
	//file->Close();
/*
*/
	
}

