#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)

using namespace std;
void efficiency()
{
	int token=0;

	FileSelector fs;
	std::vector<FileSelector> rootfiles;
	std::ifstream in( "/home/ilc/yokugawa/macros/semi_leptonic/input/record.txt" );

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

	int forward  = GenTree->Draw("qMCcostheta","qMCcostheta > 0 && qMCcostheta > -2 ");
	int backward = GenTree->Draw("qMCcostheta","qMCcostheta < 0 && qMCcostheta > -2");

	///////////////
	// BASE CUTS //
	///////////////

	//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && (Top1btag > 0.8 || Top2btag > 0.3)  && (Top1bmomentum > 15 && Top2bmomentum > 15) && methodTaken > 0";

	// **** Full cuts ****
	//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && ((methodTaken == 1 && Top1btag > 0.8 && Top2btag > 0.8 && Top1bmomentum > 35 && Top2bmomentum > 35) || methodTaken > 1 )";

	// **** Test ****
	//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((methodTaken == 1 && Top1bmomentum > 35 && Top2bmomentum > 35) || methodTaken > 2 )";

	//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4)";

	//string cuts = "&& hadMass > 180 && hadMass < 420 && Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50 && ((Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2 ) && ( methodTaken >= 1 )";


	// Begin efficiency calculation

	int entrySum = Summary->GetEntries();
	int nGenUsed, nAfterLeptonCuts, nAfterBtagCuts;
	int nevt=0, nlcut=0, nbcut=0;

	Summary->SetBranchAddress( "nGenUsed", &nGenUsed ) ;
	Summary->SetBranchAddress( "nAfterLeptonCuts", &nAfterLeptonCuts ) ;
	Summary->SetBranchAddress( "nAfterBtagCuts", &nAfterBtagCuts ) ;

	for(int i=0; i<entrySum; i++){

		Summary->GetEntry(i);

		nevt  += nGenUsed;
		nlcut += nAfterLeptonCuts;
		nbcut += nAfterBtagCuts;

	}

	cout << endl;

	cout << "============================ Baseline Cuts ============================" << endl;
	cout << "nEvents                      = " << nevt << " (100%)" << endl;
	cout << "after lepton cuts            = " << nlcut << " (" << (float)(nlcut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after btag cuts (0.8 & 0.3)  = " << nbcut << " (" << (float)(nbcut)/(float)(nevt) *100 << "%)" << endl;


	TCut thru = "Thrust < 0.9";
	TCut hadM = "hadMass > 180 && hadMass < 420";
	TCut rcTW = "Top1mass < 270 && W1mass < 250 && Top1mass > 120 && W1mass > 50";

	TCut pcut = "Top1bmomentum > 15 && Top2bmomentum > 15";
	TCut gcut = "(Top1gamma + Top2gamma) > 2.4  && Top2gamma < 2";

	TCut method = "methodTaken > 0";

	TCut cuts = thru && hadM && rcTW && pcut && gcut && method;

	int afterbcut    = normaltree->GetEntries();
	int afterthrucut = normaltree->GetEntries( thru );
	int afterhadMcut = normaltree->GetEntries( thru && hadM );
	int afterrcTWcut = normaltree->GetEntries( thru && hadM && rcTW );

	cout << "after thrust cut             = " << afterthrucut << " (" << (float)(afterthrucut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after hadronic mass cut      = " << afterhadMcut << " (" << (float)(afterhadMcut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after reco T & W mass cut    = " << afterrcTWcut << " (" << (float)(afterrcTWcut)/(float)(nevt) *100 << "%)" << endl;

	int afterpcut = normaltree->GetEntries( thru && hadM && rcTW && pcut );
	int aftergcut = normaltree->GetEntries( thru && hadM && rcTW && gcut );

	cout << "============================ Non-baseline Cuts ============================" << endl;
	cout << "after gcut                   = " << aftergcut << " (" << (float)(aftergcut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after pcut                   = " << afterpcut << " (" << (float)(afterpcut)/(float)(nevt) *100 << "%)" << endl;
	cout << endl;

	TCut fcoscut = "qCostheta > 0";
	TCut bcoscut = "qCostheta < 0 && qCostheta > -1.0";

	TCut fcuts = fcoscut && cuts;
	TCut bcuts = bcoscut && cuts;

	int recoforward = normaltree->GetEntries(fcuts);
	int recobackward = normaltree->GetEntries(bcuts);

	float afbgen = (float)(forward - backward) / (float) (forward + backward);
	float afbreco = (float)(recoforward - recobackward) / (float) (recoforward + recobackward);

	cout << "recoforward  = " << recoforward  << endl;
	cout << "recobackward = " << recobackward << endl;

	TCut noneCut = "qCostheta[1] == 2";
	int recoNONE = normaltree->GetEntries(noneCut);

	cout << "none = " << recoNONE << endl;

	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";
	std::cout << "Afb gen: " << afbgen << " N: " << forward + backward <<  "\n";
	std::cout << "Afb reco: " << afbreco << " N: " << recoforward + recobackward << "(" << afbreco / afbgen *100 << "%)"  << "\n";
	cout << "--------------------------------------------------------------\n";
	float efficiency = (float)(recoforward + recobackward)/(forward + backward) * 2 * 100;
	cout << "Final efficiency: " << efficiency << "%\n" ;
	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";
	//file->Close();
}

