#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)

using namespace std;

void fill_hist(TH1F * cosReco, int& recoforward, int &recobackward, float qCostheta[2], float q)
{
	float qCos = q * qCostheta[0];

	if(qCos > 0){
		recoforward++;
		cosReco->Fill(qCos);
	}else if(qCos < 0 && qCos >= -1.0){
		recobackward++;
		cosReco->Fill(qCos);
	}

}

void fill_hist2(TH1F * cosReco, int& recoforward, int &recobackward, float Top1costheta, float q)
{
	float qCos = q * Top1costheta;

	if(qCos > 0){
		recoforward++;
		cosReco->Fill(qCos);
	}else if(qCos < 0 && qCos >= -1.0){
		recobackward++;
		cosReco->Fill(qCos);
	}

}

void efficiency_methods()
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

	//int forward  = GenTree->Draw("qMCcostheta","qMCcostheta > 0 && qMCcostheta > -2 ");
	//int backward = GenTree->Draw("qMCcostheta","qMCcostheta < 0 && qMCcostheta > -2");

	// Begin efficiency calculation

	int entrySum = Summary->GetEntries();
	int nGenUsed, nAfterLeptonCuts, nAfterBtagCuts;
	int nevt=0, nlcut=0, nbcut=0;

	if(token==16||token==17){
		Summary->SetBranchAddress( "nEvents", &nGenUsed ) ;
	}else{
		Summary->SetBranchAddress( "nGenUsed", &nGenUsed ) ;
	}

	//Summary->SetBranchAddress( "nGenUsed", &nGenUsed ) ;
	Summary->SetBranchAddress( "nAfterLeptonCuts", &nAfterLeptonCuts ) ;
	Summary->SetBranchAddress( "nAfterBtagCuts", &nAfterBtagCuts ) ;

	for(int i=0; i<entrySum; i++){

		Summary->GetEntry(i);

		nevt  += nGenUsed;
		nlcut += nAfterLeptonCuts;
		nbcut += nAfterBtagCuts;

	}

	cout << "============================ Baseline Cuts ============================" << endl;
	cout << "nEvents                      = " << nevt << " (100%)" << endl;
	cout << "after lepton cuts            = " << nlcut << " (" << (float)(nlcut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after btag cuts (0.8 & 0.3)  = " << nbcut << " (" << (float)(nbcut)/(float)(nevt) *100 << "%)" << endl;



	// Histograms
	
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * cosReco = new TH1F("cosReco", "E(Ntracks)", 30,-1.0,1.0);
	cosReco->Sumw2();
	TH1F * cosGen = new TH1F("cosGen", ";cos#theta_{t};Entries", 30,-1.0,1.0);
	cosGen->Sumw2();
	TH1F * cosGen_wsingleTop = new TH1F("cosGen_wsingleTop", ";cos#theta_{t};Entries / 0.07", 30,-1.0,1.0);
	cosGen_wsingleTop->Sumw2();


	TGaxis::SetMaxDigits(3);
/*
	cosReco->SetLineWidth(3);
	cosGen->SetLineWidth(3);
	cosGen->SetLineStyle(2);
	cosGen->SetLineColor(kGreen+1);
	cosGen->SetFillColor(kGreen+1);
	cosGen->SetFillStyle(3004);
*/
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

	// Gen Info
	//int forward = GenTree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && qMCcostheta > -2 ");
	//int backward = GenTree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && qMCcostheta > -2");
	int forward2 = GenTree->Draw("qMCcostheta >> cosGen_wsingleTop","qMCcostheta > 0 && qMCcostheta > -2");
	int backward2 = GenTree->Draw("qMCcostheta >> +cosGen_wsingleTop","qMCcostheta < 0 && qMCcostheta > -2");

	int forward = GenTree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && qMCcostheta > -2 && singletopFlag == 0");
	int backward = GenTree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && qMCcostheta > -2 && singletopFlag == 0");

	int entryStat = normaltree->GetEntries();

	float Thrust=0,
				hadMass=0,
				Top1mass=0,
				W1mass=0,
				Top1bmomentum=0,
				Top2bmomentum=0,
				Top1gamma=0,
				Top2gamma=0,
				Top1costheta=0,
				cosbjets=0;

	float qMCcostheta[2],
				qCostheta[2],
				jet_E[2];
	
	int recoforward=0,
			recobackward=0,
			methodUsed=0;

	int methodTaken[100],
			chgValue[100];
				
  int afterthrucut=0,
			afterhadMcut=0,
			afterrcTWcut=0,
			afterpcut=0,
			aftergcut=0;
	
	int	aftermethod7=0,
			aftermethod75=0,
			aftermethod756=0,
			aftermethod7561=0,
			aftermethod75612=0,
			aftermethod756123=0,
			aftermethod7561234=0,
			aftermethod1234=0,
			aftermethod1=0;

	normaltree->SetBranchAddress("Thrust", &Thrust);
	normaltree->SetBranchAddress("hadMass", &hadMass);
	normaltree->SetBranchAddress("Top1mass", &Top1mass);
	normaltree->SetBranchAddress("W1mass", &W1mass);
	normaltree->SetBranchAddress("Top1bmomentum", &Top1bmomentum);
	normaltree->SetBranchAddress("Top2bmomentum", &Top2bmomentum);
	normaltree->SetBranchAddress("Top1gamma", &Top1gamma);
	normaltree->SetBranchAddress("Top2gamma", &Top2gamma);
	normaltree->SetBranchAddress("methodUsed", &methodUsed);
	normaltree->SetBranchAddress("methodTaken", methodTaken);
	normaltree->SetBranchAddress("chgValue", chgValue);
	//normaltree->SetBranchAddress("qMCcostheta", qMCcostheta);
	normaltree->SetBranchAddress("Top1costheta", &Top1costheta);
	normaltree->SetBranchAddress("qCostheta", qCostheta);
	normaltree->SetBranchAddress("cosbjets", &cosbjets);
	normaltree->SetBranchAddress("jet_E", &jet_E);

	int temp=0;
	int HadLepMatch=0;
	int HadLepMissMatch=0;

	int beforecut=0, aftercut=0;

  for(int iStatEntry=0; iStatEntry<entryStat; iStatEntry++){

		normaltree->GetEntry(iStatEntry);

		if(qCostheta[0]==-2) beforecut++;

		if(Thrust<0.9){

			afterthrucut++;

			if(hadMass > 180 && hadMass < 420){

				afterhadMcut++;

				if(Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50){

					afterrcTWcut++;

					if( (Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ){

						aftergcut++;

						if(Top1bmomentum > 15 && Top2bmomentum > 15){

							afterpcut++;

							if(qCostheta[0]==-2) aftercut++;

							bool methodCheck1=false,
									 methodCheck2=false,
									 methodCheck3=false,
									 methodCheck4=false,
									 methodCheck5=false,
									 methodCheck6=false,
									 methodCheck7=false;

							int sum = 0;
							int sumHad=0;
							int sumLep=0;

							for(int imethod = 0; imethod < methodUsed; imethod++){

								int Nmethod = methodTaken[imethod];
								int charge  = chgValue[imethod];

								sum += charge;

								if(imethod==1){
									//sum += 10*charge;
								}

								if(imethod<4){
									sumHad += charge;
									//sum += 100*charge;
								}else if(imethod==7){
									sumLep += charge;

									//test
									//sum += 20*charge;
								}

								if(Nmethod==1) methodCheck1=true;
								if(Nmethod==2) methodCheck2=true;
								if(Nmethod==3) methodCheck3=true;
								if(Nmethod==4) methodCheck4=true;
								if(Nmethod==5) methodCheck5=true;
								if(Nmethod==6) methodCheck6=true;
								if(Nmethod==7) methodCheck7=true;

							}


							if(sum == 0){
								temp++;
								continue;
							}else{

								if(sumHad*sumLep > 0){
									HadLepMatch++;
								}else{
									HadLepMissMatch++;
								}

								if(methodCheck7){
									aftermethod7++;

									fill_hist(cosReco, recoforward, recobackward, qCostheta, 1);

								}// method check 7

								if(methodCheck7 || methodCheck5){
									aftermethod75++;

									//fill_hist(cosReco, recoforward, recobackward, qCostheta, 1);
								
								}// method check 75

								if(methodCheck7 || methodCheck6){

									//fill_hist(cosReco, recoforward, recobackward, qCostheta, 1);
								
								}// method check 76

								if(methodCheck5 || methodCheck6){

									//fill_hist(cosReco, recoforward, recobackward, qCostheta, 1);
								
								}// method check 56

								if(methodCheck7 || methodCheck5 || methodCheck6){
									aftermethod756++;

									//fill_hist(cosReco, recoforward, recobackward, qCostheta, 1);
								
								}// method check 756

								if(methodCheck7 || methodCheck5 || methodCheck6 || methodCheck1) aftermethod7561++;
								if(methodCheck7 || methodCheck5 || methodCheck6 || methodCheck1 || methodCheck2) aftermethod75612++;
								if(methodCheck7 || methodCheck5 || methodCheck6 || methodCheck1 || methodCheck2 || methodCheck3) aftermethod756123++;
								if(methodCheck7 || methodCheck5 || methodCheck6 || methodCheck1 || methodCheck2 || methodCheck3 || methodCheck4){
									aftermethod7561234++;

/*
									if(sum > 0){
										fill_hist2(cosReco, recoforward, recobackward, Top1costheta, -1);
									}else{
										fill_hist2(cosReco, recoforward, recobackward, Top1costheta, 1);
									}
*/

									//fill_hist(cosReco, recoforward, recobackward, qCostheta, 1);

								}// method check 1234567

								if(methodCheck1 || methodCheck2 || methodCheck3 || methodCheck4){
									aftermethod1234++;

									//fill_hist(cosReco, recoforward, recobackward, qCostheta);

								}// method check 1234

								if(methodCheck1 || methodCheck2 || methodCheck3 || methodCheck4 || methodCheck7){

									//fill_hist(cosReco, recoforward, recobackward, qCostheta);

								}// method check 1234

								if(methodCheck1){
									aftermethod1++;

									//fill_hist(cosReco, recoforward, recobackward, qCostheta,1);

								}else{

									//cosbjets_rej->Fill(cosbjets);
									//jetE_rej->Fill(jet_E);

								}// method check 1

							}//consistency

						}//pcut
					}//gcut
				}//rcTW cut
			}//hadM cut
		}//thrust cut
	}

	cout << "after thrust cut             = " << afterthrucut << " (" << (float)(afterthrucut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after hadronic mass cut      = " << afterhadMcut << " (" << (float)(afterhadMcut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after reco T & W mass cut    = " << afterrcTWcut << " (" << (float)(afterrcTWcut)/(float)(nevt) *100 << "%)" << endl;

	cout << "============================ Non-baseline Cuts ============================" << endl;
	cout << "after method7                = " << aftermethod7 			<< " (" << (float)(aftermethod7)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method75               = " << aftermethod75 			<< " (" << (float)(aftermethod75)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method756              = " << aftermethod756 		<< " (" << (float)(aftermethod756)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method7561             = " << aftermethod7561 		<< " (" << (float)(aftermethod7561)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method75612            = " << aftermethod75612 	<< " (" << (float)(aftermethod75612)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method756123           = " << aftermethod756123 	<< " (" << (float)(aftermethod756123)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method7561234          = " << aftermethod7561234 << " (" << (float)(aftermethod7561234)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method1234             = " << aftermethod1234 		<< " (" << (float)(aftermethod1234)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method1                = " << aftermethod1				<< " (" << (float)(aftermethod1)/(float)(nevt) *100 << "%)" << endl;
	cout << endl;
	cout << "skipped (sum = 0)            = " << temp << " (" << (float)(temp)/(float)(nevt) *100 << "%)" << endl;
  cout << "beforecut (cos = -2)         = " << beforecut << endl;
  cout << "aftercut (cos = -2)          = " << aftercut << endl;
	cout << "after gcut                   = " << aftergcut << " (" << (float)(aftergcut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after pcut                   = " << afterpcut << " (" << (float)(afterpcut)/(float)(nevt) *100 << "%)" << endl;
	cout << endl;
	cout << "HadLepMatch = " << HadLepMatch << ", HadLepMissMatch = " << HadLepMissMatch << endl;

	// Plot and Fit

	cosGen->SetStats(0);
	TF1 * fgen = new TF1("fgen","pol2",-1,1);
	TF1 * freco = new TF1("freco","pol2",-0.9,0.9);
	fgen->SetLineColor(kGreen);
	fgen->SetLineStyle(3);
	freco->SetLineStyle(3);	//cosGen->Scale(cosReco->GetEntries()/ cosGen->GetEntries());
	
	double intCosReco = cosReco->Integral(2,29);
	double intCosGen  = cosGen->Integral(2,29);
	double intCosGen_wsingleTop  = cosGen_wsingleTop->Integral(2,29);
	//double intCosReco = cosReco->Integral(10,21);
	//double intCosGen  = cosGen->Integral(10,21);
	
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
/*
	cosReco->Fit("freco", "QR");
	cosGen->SetMinimum(0);
	cosGen->Draw("he");
	fgen->Draw("same");
	cosGen->SetMinimum(0);
	cosReco->Draw("samee");
*/

	TLegend *leg = new TLegend(0.20,0.70,0.70,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(cosGen_wsingleTop,"Parton level","l");
	leg->AddEntry(cosGen,"Parton level (after single top removal)","l");
	leg->AddEntry(cosReco,"Reconstructed","l");
	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	QQBARLabel(0.8,0.2,"",1);

	c1->Update();

	float afbgen = (float)(forward - backward) / (float) (forward + backward);
	float afbreco = (float)(recoforward - recobackward) / (float) (recoforward + recobackward);

	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";
	std::cout << "Afb gen: " << afbgen << " N: " << forward + backward <<  "\n";
	std::cout << "Afb reco: " << afbreco << " N: " << recoforward + recobackward << "(" << afbreco / afbgen *100 << "%)"  << "\n";
	std::cout << "Chi2: " << cosReco->Chi2Test(cosGen,"UUNORMCHI2/NDF") << "\n";
	cout << "--------------------------------------------------------------\n";
	float efficiency = (float)(recoforward + recobackward)/(forward + backward) * 2 * 100;
	cout << "Final efficiency: " << efficiency << "%\n" ;
	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";

	
}

