#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8

using namespace std;

void makepretty(TH1F* h1 = 0)
{
	h1->Scale( 1 / h1->GetEntries() );
	h1->SetLineWidth(3);
	h1->SetLineStyle(1);
}



void btag()
{
	int token=0;

	int nBINS=20;
	float MIN_BTAG=0.8;
	float MAX_BTAG=1.0;

	bool twoDmode = 0;

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

	//gStyle->SetOptLogy(1);


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

	// Histograms

	TH1F * histTop1btag	= new TH1F("histTop1btag",";Top_{Had} b-tag; Entries",nBINS,MIN_BTAG,MAX_BTAG);
	histTop1btag->Sumw2();
	TH1F * histTop2btag	= new TH1F("histTop2btag",";Top_{Lep} b-tag; Entries",nBINS,MIN_BTAG,MAX_BTAG);
	histTop2btag->Sumw2();
	
	TH1F * histTop1btag_single	= new TH1F("histTop1btag_single",";Top_{Had} b-tag; Entries",nBINS,MIN_BTAG,MAX_BTAG);
	histTop1btag_single->Sumw2();
	TH1F * histTop2btag_single	= new TH1F("histTop2btag_single",";Top_{Lep} b-tag; Entries",nBINS,MIN_BTAG,MAX_BTAG);
	histTop2btag_single->Sumw2();

	TH1F * histTop1btag_method1	= new TH1F("histTop1btag_method1",";Top_{Had} b-tag; Entries",nBINS,MIN_BTAG,MAX_BTAG);
	histTop1btag_method1->Sumw2();
	TH1F * histTop2btag_method1	= new TH1F("histTop2btag_method1",";Top_{Had} b-tag; Entries",nBINS,MIN_BTAG,MAX_BTAG);
	histTop2btag_method1->Sumw2();

	TGaxis::SetMaxDigits(3);

	// Set variables

	int MCLeptonPDG=0;
	int singletopFlag=0;
	int methodUsed=0;
	int methodTaken[100];
	float MCTopmass=0, MCTopBarmass=0;
	float qMCcostheta[2];

	float 	Thrust=0,
	hadMass=0,
	Top1mass=0,
	Top2mass=0,
	Top1btag=0,
	Top2btag=0,
	W1mass=0,
	Top1bmomentum=0,
	Top2bmomentum=0,
	Top1gamma=0,
	Top2gamma=0;

	int Top1Vtx=0;
	int Top2Vtx=0;


	// Set Branch Adress

	// Generator Info

	Stats->SetBranchAddress("MCLeptonPDG", &MCLeptonPDG);
	Stats->SetBranchAddress("qMCcostheta", qMCcostheta);
	Stats->SetBranchAddress("MCTopmass", &MCTopmass);
	Stats->SetBranchAddress("MCTopBarmass", &MCTopBarmass);
	Stats->SetBranchAddress("singletopFlag", &singletopFlag);
	Stats->SetBranchAddress("methodTaken", methodTaken);
	Stats->SetBranchAddress("methodUsed", &methodUsed);

	//　Reconstructed Info

	Stats->SetBranchAddress("Thrust", &Thrust);
	Stats->SetBranchAddress("hadMass", &hadMass);
	Stats->SetBranchAddress("Top1mass", &Top1mass);
	Stats->SetBranchAddress("Top2mass", &Top2mass);
	Stats->SetBranchAddress("Top1btag", &Top1btag);
	Stats->SetBranchAddress("Top2btag", &Top2btag);
	Stats->SetBranchAddress("W1mass", &W1mass);
	Stats->SetBranchAddress("Top1bmomentum", &Top1bmomentum);
	Stats->SetBranchAddress("Top2bmomentum", &Top2bmomentum);
	Stats->SetBranchAddress("Top1gamma", &Top1gamma);
	Stats->SetBranchAddress("Top2gamma", &Top2gamma);
	Stats->SetBranchAddress("Top1Vtx", &Top1Vtx);
	Stats->SetBranchAddress("Top2Vtx", &Top2Vtx);

	int ntop1vtx0 = 0;
	int ntop1vtx1 = 0;
	int ntop2vtx0 = 0;
	int ntop2vtx1 = 0;


	// Event Loop

	int entryStat = Stats->GetEntries();

	for(int iStatEntry=0; iStatEntry<entryStat; iStatEntry++){

		Stats->GetEntry(iStatEntry);

		bool qMCCheck1 = false;
		bool qMCCheck2 = false;

		if(qMCcostheta[0] > -2 && qMCcostheta[0] < -0.9) qMCCheck1=true;
		if(qMCcostheta[1] > -2 && qMCcostheta[1] < -0.9) qMCCheck2=true;

		//if(qMCCheck1 && qMCCheck2){

			histTop1btag->Fill(Top1btag);
			histTop2btag->Fill(Top2btag);

			if (singletopFlag)
			{
				histTop1btag_single->Fill(Top1btag);
				histTop2btag_single->Fill(Top2btag);

			}

			for (int i = 0; i < methodUsed; ++i)
			{

				if(methodTaken[i]==1){

					histTop1btag_method1->Fill(Top1btag);
					histTop2btag_method1->Fill(Top2btag);

					(Top1Vtx) ? ntop1vtx1++ : ntop1vtx0++;
					(Top2Vtx) ? ntop2vtx1++ : ntop2vtx0++;

				}// single top flag

			}// method used loop

		//}// qMCCheck

	}// End of Event Loop

	
	// set margin sizes
	if (twoDmode){
		gStyle->SetPadTopMargin(0.1);
		gStyle->SetPadRightMargin(0.13);
		gStyle->SetPadBottomMargin(0.15);
		gStyle->SetPadLeftMargin(0.15);
	}


	makepretty(histTop1btag);
	makepretty(histTop2btag);
	makepretty(histTop1btag_single);
	makepretty(histTop2btag_single);
	makepretty(histTop1btag_method1);
	makepretty(histTop2btag_method1);


	histTop1btag_method1->SetLineColor(kBlue+1);
	histTop2btag_method1->SetLineColor(kBlue+1);


	histTop1btag->SetLineColor(kGray+1);
	histTop2btag->SetLineColor(kGray+1);

	cout << "when single top found" << endl;
	cout << "ntop1vtx1 = " << ntop1vtx1 << ", ntop1vtx0 = " << ntop1vtx0 << endl;
	cout << "ntop2vtx1 = " << ntop2vtx1 << ", ntop2vtx0 = " << ntop1vtx0 << endl;


	TCanvas * c1	= new TCanvas("c1", "DataMC",0,0,1000,500);
	c1->Divide(2,1);

	c1->cd(1);
	histTop1btag->Draw("he");
	histTop1btag_single->Draw("hsame");
	histTop1btag_method1->Draw("hsame");

	TLegend *leg = new TLegend(0.2,0.75,0.5,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(histTop1btag,"All Reconstructed","l");
	leg->AddEntry(histTop1btag_single,"Single Top Events","l");
	leg->AddEntry(histTop1btag_method1,"Method1 only","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	c1->cd(2);
	histTop2btag->Draw("he");
	histTop2btag_single->Draw("hsame");
	histTop2btag_method1->Draw("hsame");

	TLegend *leg2 = new TLegend(0.2,0.75,0.5,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg2->SetTextFont(42);
	leg2->AddEntry(histTop2btag,"All Reconstructed","l");
	leg2->AddEntry(histTop2btag_single,"Single Top Events","l");
	leg2->AddEntry(histTop2btag_method1,"Method1 only","l");
	leg2->SetFillColor(0);
	leg2->SetLineColor(0);
	leg2->SetShadowColor(0);
	leg2->Draw();


}

