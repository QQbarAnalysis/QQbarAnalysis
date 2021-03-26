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
void merge()
{

	// initialize variables
	int styl = 0;
	int cx   = 500;
	double Legx1 = 0.20;
	double Legx2 = 0.6;

	int tokenL=0;
	int tokenR=0;

	int chiral=0;

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


	//	eLpR
	std::string filenameL = "../rootfile/asymmetry1.root";
	cout << "Processing : " << filenameL << " ..." << endl;

	TFile * fileL = TFile::Open(filenameL.c_str());

	TH1F * cosRecoL = new TH1F("cosRecoL", ";cos#theta_{t};Entries", bin_e,-1.0,max_e);
	cosRecoL->Sumw2();
	TH1F * cosGenL = new TH1F("cosGenL", ";cos#theta_{t};Entries", bin_e,-1.0,max_e);
	cosGenL->Sumw2();

	TGaxis::SetMaxDigits(3);
	
	fileL->GetObject("cosReco",cosRecoL);
	fileL->GetObject("cosGen",cosGenL);

	cosRecoL->SetLineWidth(3);
	cosGenL->SetLineWidth(3);
	cosGenL->SetLineStyle(2);

	cosGenL->SetLineColor(kBlue+1);
	cosRecoL->SetLineColor(kBlue+1);

	//	eRpL
	std::string filenameR = "../rootfile/asymmetry2.root";
	cout << "Processing : " << filenameR << " ..." << endl;

	TFile * fileR = TFile::Open(filenameR.c_str());

	TH1F * cosRecoR = new TH1F("cosRecoR", ";cos#theta_{t};Entries", bin_e,-1.0,max_e);
	cosRecoR->Sumw2();
	TH1F * cosGenR = new TH1F("cosGenR", ";cos#theta_{t};Entries", bin_e,-1.0,max_e);
	cosGenR->Sumw2();

	fileR->GetObject("cosReco",cosRecoR);
	fileR->GetObject("cosGen",cosGenR);

	cosRecoR->SetLineWidth(3);
	cosGenR->SetLineWidth(3);
	cosGenR->SetLineStyle(2);

	cosGenR->SetLineColor(kRed+1);
	cosRecoR->SetLineColor(kRed+1);

	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,cx,500);

	cosGenL->Draw();
	cosRecoL->Draw("same");
	cosGenR->Draw("same");
	cosRecoR->Draw("same");













}

