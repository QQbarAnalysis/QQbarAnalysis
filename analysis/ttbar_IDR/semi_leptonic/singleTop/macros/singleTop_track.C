#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8

using namespace std;

// see math/mathcore/src/PdfFuncMathCore.cxx in ROOT 6.x
double crystalball_function(double x, double alpha, double n, double sigma, double mean) {
  // evaluate the crystal ball function
  if (sigma < 0.)     return 0.;
  double z = (x - mean)/sigma; 
  if (alpha < 0) z = -z; 
  double abs_alpha = std::abs(alpha);
  // double C = n/abs_alpha * 1./(n-1.) * std::exp(-alpha*alpha/2.);
  // double D = std::sqrt(M_PI/2.)*(1.+ROOT::Math::erf(abs_alpha/std::sqrt(2.)));
  // double N = 1./(sigma*(C+D));
  if (z  > - abs_alpha)
    return std::exp(- 0.5 * z * z);
  else {
    //double A = std::pow(n/abs_alpha,n) * std::exp(-0.5*abs_alpha*abs_alpha);
    double nDivAlpha = n/abs_alpha;
    double AA =  std::exp(-0.5*abs_alpha*abs_alpha);
    double B = nDivAlpha -abs_alpha;
    double arg = nDivAlpha/(B-z);
    return AA * std::pow(arg,n);
  }
}

double crystalball_function(const double *x, const double *p) {
  // if ((!x) || (!p)) return 0.; // just a precaution
  // [Constant] * ROOT::Math::crystalball_function(x, [Alpha], [N], [Sigma], [Mean])
  return (p[0] * crystalball_function(x[0], p[3], p[4], p[2], p[1]));
}

double GaussExp_function(double x, double k, double sigma, double mean) {
	if (sigma < 0.)     return 0.;
	double z = (x - mean)/sigma;
	if (k < 0) z = -z;
	double abs_k = std::abs(k);
	if (z  >= - abs_k)
		return std::exp(- 0.5 * z * z);
	else{
		double abs_k2 = abs_k * abs_k;
		return std::exp(0.5 * abs_k2 + abs_k * z);
	}

}

double GaussExp_function(const double *x, const double *p) {
  // if ((!x) || (!p)) return 0.; // just a precaution
  // [Constant] * ROOT::Math::crystalball_function(x, [Alpha], [N], [Sigma], [Mean])
  return (p[0] * GaussExp_function(x[0], p[3], p[2], p[1]));
}

void singleTop_track()
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

	TTree * Stats = (TTree*) file->Get( "Stats" ) ;
	TTree * GenTree = (TTree*) file->Get( "GenTree" ) ;
	TTree * Summary = (TTree*) file->Get( "Summary" );

	// Histograms
	
	TCanvas * c1			= new TCanvas("c1", "jetTrack_E",0,0,500,500);
	TH1F * jetTrack_Eall	= new TH1F("jetTrack_Eall",";jetE_{track} (GeV); 1 / Entries",100,0,100);
	jetTrack_Eall->Sumw2();
	TH1F * jetTrack_E		= new TH1F("jetTrack_E",";jetE_{track} (GeV); 1 / Entries",100,0,100);
	jetTrack_E->Sumw2();

	TH1F * jet_Eall	= new TH1F("jet_Eall",";jetE (GeV); 1 / Entries",200,0,200);
	jet_Eall->Sumw2();
	TH1F * hjet_E		= new TH1F("hjet_E",";jetE (GeV); 1 / Entries",200,0,200);
	hjet_E->Sumw2();


	TH1F * jetTrack_pall	= new TH1F("jetTrack_pall",";jetP_{track} (GeV); 1 / Entries",30,0,30);
	jetTrack_pall->Sumw2();
	TH1F * jetTrack_p		= new TH1F("jetTrack_p",";jetP_{track} (GeV); 1 / Entries",30,0,30);
	jetTrack_p->Sumw2();

	TGaxis::SetMaxDigits(3);

	jetTrack_Eall->SetLineWidth(3);
	jetTrack_Eall->SetLineStyle(1);
	jetTrack_Eall->SetLineColor(kGray+1);

	jetTrack_E->SetLineWidth(3);
	jetTrack_E->SetLineStyle(1);	


	jet_Eall->SetLineWidth(3);
	jet_Eall->SetLineStyle(1);
	jet_Eall->SetLineColor(kGray+1);

	hjet_E->SetLineWidth(3);
	hjet_E->SetLineStyle(1);


	jetTrack_pall->SetLineWidth(3);
	jetTrack_pall->SetLineStyle(1);
	jetTrack_pall->SetLineColor(kGray+1);

	jetTrack_p->SetLineWidth(3);
	jetTrack_p->SetLineStyle(1);


	// Set variables

	int MCLeptonPDG=0;
	int singletopFlag=0;
	int methodUsed=0;
	int methodTaken[100];
	float MCTopmass=0, MCTopBarmass=0;
	float qMCcostheta[2];

	// jet information
	int   jet_nvtx[2];
	float jet_E[2];

    // jet track info
	int   jet_vtx_ntrack[2][10];
    float jet_track_E[2][10][20];
    float jet_track_p[2][10][20];

    // cut variables
	float 	Thrust=0,
			hadMass=0,
			Top1mass=0,
			Top2mass=0,
			W1mass=0,
			Top1bmomentum=0,
			Top2bmomentum=0,
			Top1gamma=0,
			Top2gamma=0;


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
	Stats->SetBranchAddress("W1mass", &W1mass);
	Stats->SetBranchAddress("Top1bmomentum", &Top1bmomentum);
	Stats->SetBranchAddress("Top2bmomentum", &Top2bmomentum);
	Stats->SetBranchAddress("Top1gamma", &Top1gamma);
	Stats->SetBranchAddress("Top2gamma", &Top2gamma);

	// jet info

	Stats->SetBranchAddress("jet_nvtx", jet_nvtx);
	Stats->SetBranchAddress("jet_vtx_ntrack", jet_vtx_ntrack);
	Stats->SetBranchAddress("jet_E", jet_E);
	Stats->SetBranchAddress("jet_track_E", jet_track_E);
	Stats->SetBranchAddress("jet_track_p", jet_track_p);


	// Event Loop

	int entryStat = Stats->GetEntries();
	cout << "Total number of events: " << entryStat << endl;

	int sel_evt = 0;

	bool method_mode = true;

	for(int iStatEntry=0; iStatEntry<entryStat; iStatEntry++){

		Stats->GetEntry(iStatEntry);

		bool qMCCheck1 = false;
		bool qMCCheck2 = false;
		bool qMCCheck  = false;

		if(qMCcostheta[0] > -2 && qMCcostheta[0] > -0.9 && qMCcostheta[0] < -0.6) qMCCheck1=true;
		if(qMCcostheta[1] > -2 && qMCcostheta[1] > -0.9 && qMCcostheta[1] < -0.6) qMCCheck2=true;
		if(qMCCheck1 && qMCCheck2) qMCCheck=true;

		bool single_qMC_check = false;
		bool single_check     = false;

		if(singletopFlag==1 && qMCCheck) single_qMC_check=true;
		if(singletopFlag==1) single_check=true;

		bool check = single_qMC_check;

		bool method_check = false;
		for (int i = 0; i < methodUsed; ++i){
			if(methodTaken[i]==1){
				method_check=true;
				break;
			}
		}

//		if(check && method_check) sel_evt++;
		if(check) sel_evt++;

		// Reconstructed Level

		for (int ijet = 0; ijet < 2; ++ijet)
		{
			jet_Eall->Fill( jet_E[ijet] );

			if(method_mode){	
				if(check && !method_check){
					hjet_E->Fill( jet_E[ijet] );
				}
			}else{
				if(check) hjet_E->Fill( jet_E[ijet] );
			}


			for (int ivtx = 0; ivtx < jet_nvtx[ijet]; ++ivtx)
			{
				for (int itr = 0; itr < jet_vtx_ntrack[ijet][ivtx]; ++itr)
				{
					jetTrack_Eall->Fill( jet_track_E[ijet][ivtx][itr] );
					jetTrack_pall->Fill( jet_track_p[ijet][ivtx][itr] );

					if(method_mode){	
						if(check && !method_check){
							jetTrack_E->Fill( jet_track_E[ijet][ivtx][itr] );
							jetTrack_p->Fill( jet_track_p[ijet][ivtx][itr] );
						}
					}else{
						if(check){
							jetTrack_E->Fill( jet_track_E[ijet][ivtx][itr] );
							jetTrack_p->Fill( jet_track_p[ijet][ivtx][itr] );
						}
					}

				} // end itr

			} // end ivtx

		} // end ijet


	}// End of Event Loop


	cout << "Selected number of events: " << sel_evt << endl;



	cout << jetTrack_Eall->GetEntries() << "\n";
	cout << jetTrack_E->GetEntries() << "\n";

	jetTrack_Eall->Scale( 1 / jetTrack_Eall->GetEntries() );
	jetTrack_E->Scale( 1 / jetTrack_E->GetEntries() );

	jet_Eall->Scale( 1 / jet_Eall->GetEntries() );
	hjet_E->Scale( 1 / hjet_E->GetEntries() );

	jetTrack_pall->Scale( 1 / jetTrack_pall->GetEntries() );
	jetTrack_p->Scale( 1 / jetTrack_p->GetEntries() );

	jetTrack_Eall->SetMinimum(0);
	jetTrack_E->SetMinimum(0);

	jet_Eall->SetMinimum(0);
	hjet_E->SetMinimum(0);

	jetTrack_pall->SetMinimum(0);
	jetTrack_p->SetMinimum(0);

//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

	jetTrack_E->Draw("he");
	jetTrack_Eall->Draw("hsame");


	TLegend *leg = new TLegend(0.7,0.85,0.9,0.95); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(jetTrack_Eall,"All Reconstructed","l");
	leg->AddEntry(jetTrack_E,"Single Top Tagged","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	c1->Update();

	TCanvas * c2			= new TCanvas("c2", "jetTrack_P",0,0,500,500);

	jetTrack_p->Draw("he");
	jetTrack_pall->Draw("hsame");


	TLegend *leg2 = new TLegend(0.7,0.85,0.9,0.95); //set here your x_0,y_0, x_1,y_1 options
	leg2->SetTextFont(42);
	leg2->AddEntry(jetTrack_pall,"All Reconstructed","l");
	leg2->AddEntry(jetTrack_p,"Single Top Tagged","l");
	leg2->SetFillColor(0);
	leg2->SetLineColor(0);
	leg2->SetShadowColor(0);
	leg2->Draw();	

	TCanvas * c3			= new TCanvas("c3", "cjet_E",0,0,500,500);

	hjet_E->Draw("he");
	jet_Eall->Draw("hsame");


	TLegend *leg3 = new TLegend(0.7,0.85,0.9,0.95); //set here your x_0,y_0, x_1,y_1 options
	leg3->SetTextFont(42);
	leg3->AddEntry(jet_Eall,"All Reconstructed","l");
	leg3->AddEntry(hjet_E,"Single Top Tagged","l");
	leg3->SetFillColor(0);
	leg3->SetLineColor(0);
	leg3->SetShadowColor(0);
	leg3->Draw();






}

