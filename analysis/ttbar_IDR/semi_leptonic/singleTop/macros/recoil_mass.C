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

// Gaussian background function
Double_t background(Double_t *x, Double_t *p) {

	double z = (x[0] - p[4]) / p[5];
	return p[3] * std::exp( -0.5 * z * z );
}

void recoil_mass()
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
	
	TH1F * histMCTopHadMass	= new TH1F("histMCTopHadMass",";Gen Top_{Had} Mass (GeV); Entries",200,100,300);
	histMCTopHadMass->Sumw2();
	TH1F * histMCTopLepMass	= new TH1F("histMCTopLepMass",";Gen Top_{Lep} Mass (GeV); Entries",200,100,300);
	histMCTopLepMass->Sumw2();

	TH1F * histRecoTopHadMass	= new TH1F("histRecoTopHadMass",";Reco Top_{Had} Mass (GeV); Entries",200,100,300);
	histRecoTopHadMass->Sumw2();
	TH1F * histRecoTopLepMass	= new TH1F("histRecoTopLepMass",";Reco Top_{Lep} Mass (GeV); Entries",200,100,300);
	histRecoTopLepMass->Sumw2();

	TH1F * histRecoMCHadMassDiff	= new TH1F("histRecoMCHadMassDiff",";Reco-Gen Top_{Had} Mass (GeV); Entries",200,-100,100);
	TH1F * histRecoMCLepMassDiff	= new TH1F("histRecoMCLepMassDiff",";Reco-Gen Top_{Lep} Mass (GeV); Entries",200,-100,100);


	float recMmin=150.0, recMmax=250.0;
//	float recMmin=100.0, recMmax=300.0;
	TH2F * histTopHadMass	= new TH2F("histTopHadMass",";MC Top_{Had} Mass (GeV);Reco Top_{Had} Mass (GeV)",200,recMmin,recMmax,200,recMmin,recMmax);
	TH2F * histTopLepMass	= new TH2F("histTopLepMass",";MC Top_{Lep} Mass (GeV);Reco Top_{Lep} Mass (GeV)",200,recMmin,recMmax,200,recMmin,recMmax);

	TH2F * histTopLepHadMass	= new TH2F("histTopLepHadMass",";Gen Top_{Lep} Mass (GeV);Gen Top_{Had} Mass (GeV)",200,recMmin,recMmax,200,recMmin,recMmax);

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


	// Event Loop

	int entryStat = Stats->GetEntries();

	for(int iStatEntry=0; iStatEntry<entryStat; iStatEntry++){

		Stats->GetEntry(iStatEntry);



		bool qMCCheck1 = false;
		bool qMCCheck2 = false;

		if(qMCcostheta[0] > -2 && qMCcostheta[0] < -0.9) qMCCheck1=true;
		if(qMCcostheta[1] > -2 && qMCcostheta[1] < -0.9) qMCCheck2=true;

//		if(qMCCheck1 && qMCCheck2){

//			for (int i = 0; i < methodUsed; ++i)
//			{

//				if(methodTaken[i]==1){

					// Generated Level

					float MCTopHadMass = -1;
					float MCTopLepMass = -1;

					if(MCLeptonPDG < 0){
						MCTopHadMass = MCTopmass;
						MCTopLepMass = MCTopBarmass;
					}
					if(MCLeptonPDG > 0){
						MCTopHadMass = MCTopBarmass;
						MCTopLepMass = MCTopmass;
					}

					if(MCTopHadMass != -1) histMCTopHadMass->Fill(MCTopHadMass);
					if(MCTopLepMass != -1) histMCTopLepMass->Fill(MCTopLepMass);


					// Reconstructed Level

//					if(singletopFlag==0){
						histRecoTopHadMass->Fill(Top1mass);
						histRecoTopLepMass->Fill(Top2mass);
//					}

					histTopHadMass->Fill(MCTopHadMass,Top1mass);
					histTopLepMass->Fill(MCTopLepMass,Top2mass);


//					histTopLepHadMass->Fill(MCTopLepMass,MCTopHadMass);


					if(singletopFlag==1){
						histTopLepHadMass->Fill(MCTopLepMass,MCTopHadMass);
//						histTopLepHadMass->Fill(Top2mass,Top1mass);
					}


					// Reco MC Difference

					float HadDiff = Top1mass - MCTopHadMass;
					float LepDiff = Top2mass - MCTopLepMass;

					histRecoMCHadMassDiff->Fill(HadDiff);
					histRecoMCLepMassDiff->Fill(LepDiff);

//				} // method = 1

//			} // for loop

//		} // cos 0.9


/*

		if(Thrust<0.9){

			if(hadMass > 180 && hadMass < 420){

				if(Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50){

					if( (Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ){

						if(Top1bmomentum > 15 && Top2bmomentum > 15){

							for (int i = 0; i < methodUsed; ++i)
							{

								if(methodTaken[i]==1){

									bool qMCCheck1 = false;
									bool qMCCheck2 = false;

									if(qMCcostheta[0] > -2 && qMCcostheta[0] < -0.9) qMCCheck1=true;
									if(qMCcostheta[1] > -2 && qMCcostheta[1] < -0.9) qMCCheck2=true;

									//if(qMCCheck1 && qMCCheck2){

										// Generated Level

										float MCTopHadMass = -1;
										float MCTopLepMass = -1;

										if(MCLeptonPDG < 0){
											MCTopHadMass = MCTopmass;
											MCTopLepMass = MCTopBarmass;
										}
										if(MCLeptonPDG > 0){
											MCTopHadMass = MCTopBarmass;
											MCTopLepMass = MCTopmass;
										}

										if(MCTopHadMass != -1) histMCTopHadMass->Fill(MCTopHadMass);
										if(MCTopLepMass != -1) histMCTopLepMass->Fill(MCTopLepMass);


										// Reconstructed Level

										histRecoTopHadMass->Fill(Top1mass);
										histRecoTopLepMass->Fill(Top2mass);

										histTopHadMass->Fill(MCTopHadMass,Top1mass);
										histTopLepMass->Fill(MCTopLepMass,Top2mass);

										// Reco MC Difference

										float HadDiff = Top1mass - MCTopHadMass;
										float LepDiff = Top2mass - MCTopLepMass;

										histRecoMCHadMassDiff->Fill(HadDiff);
										histRecoMCLepMassDiff->Fill(LepDiff);

									//}

								}

							}


						}//pcut
					}//gcut
				}//rcTW cut
			}//hadM cut
		}//thrust cut

*/


	}// End of Event Loop

	
	// set margin sizes
	if (twoDmode){
		gStyle->SetPadTopMargin(0.1);
		gStyle->SetPadRightMargin(0.13);
		gStyle->SetPadBottomMargin(0.15);
		gStyle->SetPadLeftMargin(0.15);
	}


	// hist normalization

	histMCTopHadMass->Scale( 1 / histMCTopHadMass->GetEntries() );
	histMCTopLepMass->Scale( 1 / histMCTopLepMass->GetEntries() );
	histRecoTopHadMass->Scale( 1 / histRecoTopHadMass->GetEntries() );
	histRecoTopLepMass->Scale( 1 / histRecoTopLepMass->GetEntries() );


	// hist setting

	histMCTopHadMass->GetYaxis()->SetRangeUser(0,0.28);
	histMCTopLepMass->GetYaxis()->SetRangeUser(0,0.28);
	histRecoTopHadMass->GetYaxis()->SetRangeUser(0,35E-3);
	histRecoTopLepMass->GetYaxis()->SetRangeUser(0,25E-3);


	histMCTopHadMass->SetLineWidth(3);
	histMCTopHadMass->SetLineStyle(1);
	histMCTopHadMass->SetLineColor(kGray+1);

	histRecoTopHadMass->SetLineWidth(3);
	histRecoTopHadMass->SetLineStyle(1);

	histMCTopLepMass->SetLineWidth(3);
	histMCTopLepMass->SetLineStyle(1);
	histMCTopLepMass->SetLineColor(kGray+1);

	histRecoTopLepMass->SetLineWidth(3);
	histRecoTopLepMass->SetLineStyle(1);



	// Fit Functions

	float xmin = 140., xmax = 200.;
	TF1 *crystalball = new TF1("crystalball", crystalball_function, xmin, xmax, 5);
	TF1 *fgaus       = new TF1("fgaus","gaus",xmin, xmax);
	TF1 *dgaus1		 = new TF1("dgaus1","gaus(0) + gaus(3)",xmin,xmax);
	TF1 *dgaus2		 = new TF1("dgaus2","gaus(0) + gaus(3)",xmin,xmax);

	TF1 *fbg		 = new TF1("fbg",background,100,300,6);
	TF1 *fbg2		 = new TF1("fbg2",background,100,300,6);
	double par[6];
	double par2[6];


	crystalball->SetParNames("Constant", "Mean", "Sigma", "Alpha", "N");
	crystalball->SetTitle("crystalball"); // not strictly necessary

	float p0 = 30.0E-3;
	float p1 = 175.;
	float p2 = 20.;
	float p3 = 1.0;
	float p4 = 1.0;

	float constant = 20E-3;
	float mean = 175.0;
	float wid = 5.0;

	float bgconstant = 6.5e-3;
	float bgmean = 187.5;
	float bgwid = 32.0;

	crystalball->SetParameters(p0,p1,p2,p3,p4);
	fgaus->SetParameters(constant, mean, wid);
	dgaus1->SetParameters(constant, mean, wid, bgconstant, bgmean, bgwid);
	dgaus2->SetParameters(constant, mean, wid, bgconstant, bgmean, bgwid);

	crystalball->SetLineColor(kRed);
	fgaus->SetLineColor(kRed);
	dgaus1->SetLineColor(kRed);
	dgaus2->SetLineColor(kRed);
	fbg->SetLineColor(kGray);
	fbg2->SetLineColor(kGray);


/*
	TCanvas * c1	= new TCanvas("c1", "DataMC",0,0,700,700);

	c1->Divide(2,2);

	c1->cd(1);
	histMCTopHadMass->Draw("he");

	c1->cd(2);
	histMCTopLepMass->Draw("he");

	c1->cd(3);
	histRecoTopHadMass->Fit("dgaus1");
	dgaus1->GetParameters(par);
	fbg->SetParameters(par);
	histRecoTopHadMass->Draw("he");
	dgaus1->Draw("same");
//	fbg->Draw("same");


	c1->cd(4);
	histRecoTopLepMass->Fit("dgaus2");
	dgaus2->GetParameters(par);
	fbg2->SetParameters(par);
	histRecoTopLepMass->Draw("he");
	dgaus2->Draw("same");
//	fbg2->Draw("same");

	c1->Update();
*/

	TCanvas * c2	= new TCanvas("c2", "DataMC2",0,0,1000,500);
	c2->Divide(2,1);

	histTopHadMass->GetXaxis()->SetTitleOffset(1.7);
	histTopHadMass->GetYaxis()->SetTitleOffset(1.7);

	histTopLepMass->GetXaxis()->SetTitleOffset(1.7);
	histTopLepMass->GetYaxis()->SetTitleOffset(1.7);


	c2->cd(1);
	histTopHadMass->Draw("COLZ");

	c2->cd(2);
	histTopLepMass->Draw("COLZ");
	
/*
	TCanvas * c3	= new TCanvas("c3", "DataMC3",0,0,1000,500);
	c3->Divide(2,1);

	c3->cd(1);
	histRecoMCHadMassDiff->Draw("he");

	c3->cd(2);
	histRecoMCLepMassDiff->Draw("he");
*/

	TCanvas * c4	= new TCanvas("c4", "DataMC3",0,0,500,500);
	histTopLepHadMass->Draw("COLZ");

}

