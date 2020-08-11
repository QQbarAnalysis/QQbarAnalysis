#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

#define MAXV 8

using namespace std;
void asymmetry()
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
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);  
	gStyle->SetOptTitle(1);
	gStyle->SetTitleBorderSize(0);
	gStyle->SetTitleStyle(0);
	gStyle->SetMarkerSize(0);
	gStyle->SetTitleX(0.2); 
	gStyle->SetTitleY(0.9); 

	std::string filename = "../TTbarAnalysis_out.root";

	TFile * file = TFile::Open(filename.c_str());

	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,cx,500);
	TH1F * cosReco = new TH1F("cosReco", "E(Ntracks)", bin_e,-1.0,max_e);
	cosReco->Sumw2();
	TH1F * cosGen = new TH1F("cosGen", ";cos#theta_{t};Entries / 0.07", bin_e,-1.0,max_e);
	cosGen->Sumw2();

	TH1F * cosGen_wsingleTop = new TH1F("cosGen_wsingleTop", ";cos#theta_{t};Entries / 0.07", bin_e,-1.0,max_e);
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

	int forward = GenTree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && qMCcostheta > -2 && singletopFlag == 0");
	int backward = GenTree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && qMCcostheta > -2 && singletopFlag == 0");

	int forward2 = GenTree->Draw("qMCcostheta >> cosGen_wsingleTop","qMCcostheta > 0 && qMCcostheta > -2");
	int backward2 = GenTree->Draw("qMCcostheta >> +cosGen_wsingleTop","qMCcostheta < 0 && qMCcostheta > -2");

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
	int recoforward = normaltree->Draw("qCostheta >> cosReco", fcuts);
	int recobackward = normaltree->Draw("qCostheta >> +cosReco", bcuts);

	cout << recoforward <<endl;


	cosGen->SetStats(0);
	TF1 * fgen = new TF1("fgen","pol2",-1,1);
	TF1 * freco = new TF1("freco","pol2",-0.9,0.9);
	fgen->SetLineColor(kGreen);
	fgen->SetLineStyle(3);
	freco->SetLineStyle(3);

	//cosGen->Scale(cosReco->GetEntries()/ cosGen->GetEntries());
	double intCosReco = cosReco->Integral(2,29);
	double intCosGen  = cosGen->Integral(2,29);
	double intCosGen_wsingleTop  = cosGen_wsingleTop->Integral(2,29);
	//cosGen->Scale(intCosReco / intCosGen);
	cosReco->Scale(1/intCosReco);
	cosGen->Scale(1/intCosGen);
	cosGen_wsingleTop->Scale(1/intCosGen_wsingleTop);
	
	cosGen->Fit("fgen","Q");
	cosReco->Fit("freco", "QR");
	cosGen_wsingleTop->SetMinimum(0);
	cosGen_wsingleTop->Draw("he");
	cosGen->Draw("hsame");
	fgen->Draw("same");
	cosGen->SetMinimum(0);
	cosReco->Draw("samee");


	TLegend *leg = new TLegend(0.20,0.70,0.70,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(cosGen_wsingleTop,"Parton level","l");
	leg->AddEntry(cosGen,"Parton level (after single top removal)","l");
	leg->AddEntry(cosReco,"Reconstructed","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

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
	//

	
}

