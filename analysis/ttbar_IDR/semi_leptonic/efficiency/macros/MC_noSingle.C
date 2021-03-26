#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "../../style/Style.C"
#include "../../style/Labels.C"
#define MAXV 8
//void asymmetry(string filename = "TTBarProcessorLeft.root", TCanvas * c1 = NULL)

using namespace std;

void fill_hist(TH1F * cosReco, int& recoforward, int &recobackward, float qCostheta[2])
{
	if(qCostheta[0] > 0){
		recoforward++;
		cosReco->Fill(qCostheta[0]);
	}else if(qCostheta[0] < 0 && qCostheta[0] >= -1.0){
		recobackward++;
		cosReco->Fill(qCostheta[0]);
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

void MC_noSingle()
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

	// Begin efficiency calculation

	int entrySum = Summary->GetEntries();
	int nGenUsed, nAfterLeptonCuts, nAfterBtagCuts;
	int nevt=0, nlcut=0, nbcut=0;

	if(token==4||token==5){
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
	THStack * cosRecoStack = new THStack("cosRecoStack",";cos#theta_{t};Entries / 0.07");
	TH1F * cosRecoAll = new TH1F("cosRecoAll", "E(Ntracks)", 30,-1.0,1.0);
	cosRecoAll->Sumw2();
	TH1F * cosRecoOK = new TH1F("cosRecoOK", "E(Ntracks)", 30,-1.0,1.0);
	cosRecoOK->Sumw2();
	TH1F * cosRecoNG = new TH1F("cosRecoNG", "E(Ntracks)", 30,-1.0,1.0);
	cosRecoNG->Sumw2();
	TH1F * cosGen = new TH1F("cosGen", ";cos#theta_{t};Entries / 0.07", 30,-1.0,1.0);
	cosGen->Sumw2();

	TH2F * cosMCRC = new TH2F("cosMCRC",";Reco cos#theta_{t};Gen cos#theta_{t}", 30, -1.0, 1.0, 30, -1.0, 1.0);

	TGaxis::SetMaxDigits(3);
	cosRecoOK->SetLineWidth(3);
	cosRecoNG->SetLineWidth(3);
	cosRecoAll->SetLineWidth(3);

	//cosRecoAll->SetLineColor(kGray+1);
	cosRecoOK->SetLineColor(kBlue+1);
	cosRecoNG->SetLineColor(kRed+1);

	//cosRecoOK->SetFillColorAlpha(kBlue+1,0.35);
	cosRecoNG->SetFillColor(kRed+1);

	//cosRecoOK->SetFillStyle(3004);
	cosRecoNG->SetFillStyle(3004);

	cosGen->SetLineWidth(3);
	cosGen->SetLineStyle(2);
	cosGen->SetLineColor(kGreen+1);
	cosGen->SetFillColor(kGreen+1);
	cosGen->SetFillStyle(3004);

	// Gen Info
	//int forward = GenTree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && qMCcostheta > -2 ");
	//int backward = GenTree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && qMCcostheta > -2");

	int forward = 0;
	int backward = 0;

	if(token==4||token==5){
		forward = GenTree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && qMCcostheta > -2 ");
		backward = GenTree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && qMCcostheta > -2");
	}else{
		forward = GenTree->Draw("qMCcostheta >> cosGen","qMCcostheta > 0 && qMCcostheta > -2 && singletopFlag == 0");
		backward = GenTree->Draw("qMCcostheta >> +cosGen","qMCcostheta < 0 && qMCcostheta > -2 && singletopFlag == 0");
	}



	//int forward = 0;
	//int backward = 0;

	int entryStat = normaltree->GetEntries();

	float Thrust=0,
				hadMass=0,
				Top1mass=0,
				W1mass=0,
				Top1bmomentum=0,
				Top2bmomentum=0,
				Top1gamma=0,
				Top2gamma=0,
				cosbjets=0,
				Top1costheta=0;

	float qMCcostheta[2],
				qCostheta[2],
				jet_E[2];
	
	float MCTop1charge=0,
				MCTop2charge=0;

	int recoforward=0,
			recobackward=0,
			methodUsed=0;

	int methodTaken[100],
			methodCheck[100],
			chgValue[100];
				
  int afterthrucut=0,
			afterhadMcut=0,
			afterrcTWcut=0,
			afterpcut=0,
			aftergcut=0,
			afterchgconfig=0;
	
	int	aftermethod7=0,
			aftermethod75=0,
			aftermethod756=0,
			aftermethod7561=0,
			aftermethod75612=0,
			aftermethod756123=0,
			aftermethod7561234=0,
			aftermethod1234=0,
			aftermethod1=0;
	
	int temp1=0,
			temp2=0;

	int aftermethod[8] = {0};
	int methodcorrect[8] = {0};

	int method1correct=0,
			method7correct=0,
			methodAllcorrect=0;

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
	normaltree->SetBranchAddress("methodCheck", methodCheck);
	normaltree->SetBranchAddress("chgValue", chgValue);
	normaltree->SetBranchAddress("qMCcostheta", qMCcostheta);
	normaltree->SetBranchAddress("qCostheta", qCostheta);
	normaltree->SetBranchAddress("cosbjets", &cosbjets);
	normaltree->SetBranchAddress("jet_E", jet_E);
	normaltree->SetBranchAddress("Top1costheta", &Top1costheta);
	normaltree->SetBranchAddress("MCTop1charge", &MCTop1charge);
	normaltree->SetBranchAddress("MCTop2charge", &MCTop2charge);

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

							bool methodUsedFlag[8] = {0};
							bool methodOK[8] = {0};
							bool sumCorrect = false;

							int sum = 0;
							//int sumCorrect = 0;
							int sumHad=0;
							int sumLep=0;

							for(int imethod = 0; imethod < methodUsed; imethod++){

								int Nmethod = methodTaken[imethod];
								int charge  = chgValue[imethod];
								int check		= methodCheck[imethod];


								sum += charge;

/*
								if(charge>0){
									if(Nmethod==1) sum += 6;
									if(Nmethod==2) sum += 3;
									if(Nmethod==3) sum += 4;
									if(Nmethod==4) sum += 5;
									//if(Nmethod==5) sum += 2;
									//if(Nmethod==6) sum += 1;
									if(Nmethod==7) sum += 7;
								}else{
									if(Nmethod==1) sum -= 6;
									if(Nmethod==2) sum -= 3;
									if(Nmethod==3) sum -= 4;
									if(Nmethod==4) sum -= 5;
									//if(Nmethod==5) sum -= 2;
									//if(Nmethod==6) sum -= 1;
									if(Nmethod==7) sum -= 7;
								}

								if(charge>0){
									sum++;
								}else if(charge<0){
									sum--;
								}
*/

								//sumCorrect += check;

								if(Nmethod<=4){
									sumHad += charge;
								}else if(Nmethod==7){
									sumLep += charge;
								}

								for(int n=1; n<8; n++){
									if(n == Nmethod) methodUsedFlag[n]=true;
									if(n == Nmethod && check) methodOK[n]=true;
								}

							}


							if(sum == 0){
								temp++;
								continue;
							}else{

								afterchgconfig++;
								if(sum * MCTop1charge < 0) sumCorrect = true;

								if(sumHad*sumLep > 0){
									HadLepMatch++;
								}else{
									HadLepMissMatch++;
								}

								for(int jmethod = 1; jmethod < 8; jmethod++){

									if(methodUsedFlag[jmethod]){
										aftermethod[jmethod]++;
										if(methodOK[jmethod]){
											methodcorrect[jmethod]++;
										}
									}

								} // end jmethod


								if(methodUsedFlag[7]){

									aftermethod7++;

/*
									if(sumLep<0){
										fill_hist2(cosRecoAll, recoforward, recobackward, Top1costheta, 1);
									}else if(sumLep>0){
										fill_hist2(cosRecoAll, recoforward, recobackward, Top1costheta, -1);
									}

									int recof0=0;
									int recob0=0;
									if(methodOK[7]){
										if(sumLep<0){
											fill_hist2(cosRecoOK, recof0, recob0, Top1costheta, 1);
										}else if(sumLep>0){
											fill_hist2(cosRecoOK, recof0, recob0, Top1costheta, -1);
										}
									}else{
										if(sumLep<0){
											fill_hist2(cosRecoNG, recof0, recob0, Top1costheta, 1);
										}else if(sumLep>0){
											fill_hist2(cosRecoNG, recof0, recob0, Top1costheta, -1);
										}
									}
*/
									if(methodOK[7]) method7correct++;

								}// method check 7

								if(methodUsedFlag[7] || methodUsedFlag[5]){
									aftermethod75++;

									//fill_hist(cosRecoOK, recoforward, recobackward, qCostheta);
								
								}// method check 75

								if(methodUsedFlag[7] || methodUsedFlag[6]){

									//fill_hist(cosRecoOK, recoforward, recobackward, qCostheta);
								
								}// method check 76

								if(methodUsedFlag[5] || methodUsedFlag[6]){

									//fill_hist(cosRecoOK, recoforward, recobackward, qCostheta);
								
								}// method check 56

								if(methodUsedFlag[7] || methodUsedFlag[5] || methodUsedFlag[6]){
									aftermethod756++;

									//fill_hist(cosRecoOK, recoforward, recobackward, qCostheta);
								
								}// method check 756

								if(methodUsedFlag[7] || methodUsedFlag[5] || methodUsedFlag[6] || methodUsedFlag[1]) aftermethod7561++;
								if(methodUsedFlag[7] || methodUsedFlag[5] || methodUsedFlag[6] || methodUsedFlag[1] || methodUsedFlag[2]) aftermethod75612++;
								if(methodUsedFlag[7] || methodUsedFlag[5] || methodUsedFlag[6] || methodUsedFlag[1] || methodUsedFlag[2] || methodUsedFlag[3]) aftermethod756123++;
								if(methodUsedFlag[7] || methodUsedFlag[5] || methodUsedFlag[6] || methodUsedFlag[1] || methodUsedFlag[2] || methodUsedFlag[3] || methodUsedFlag[4]){
									aftermethod7561234++;

/*
									if(sum<0){
										fill_hist2(cosRecoAll, recoforward, recobackward, Top1costheta, 1);
									}else if(sum>0){
										fill_hist2(cosRecoAll, recoforward, recobackward, Top1costheta, -1);
									}

									int recof0=0;
									int recob0=0;
									if(sumCorrect){
										if(sum<0){
											fill_hist2(cosRecoOK, recof0, recob0, Top1costheta, 1);
										}else if(sum>0){
											fill_hist2(cosRecoOK, recof0, recob0, Top1costheta, -1);
										}
									}else{
										if(sum<0){
											fill_hist2(cosRecoNG, recof0, recob0, Top1costheta, 1);
										}else if(sum>0){
											fill_hist2(cosRecoNG, recof0, recob0, Top1costheta, -1);
										}
									}
*/
									if(sumCorrect) methodAllcorrect++;

								}// method check 1234567

								if(methodUsedFlag[1] || methodUsedFlag[2] || methodUsedFlag[3] || methodUsedFlag[4]){
									aftermethod1234++;


									if(sumHad<0){
										fill_hist2(cosRecoAll, recoforward, recobackward, Top1costheta, 1);
									}else if(sumHad>0){
										fill_hist2(cosRecoAll, recoforward, recobackward, Top1costheta, -1);
									}

									int recof0=0;
									int recob0=0;
									if(sumHad * MCTop1charge < 0){
										if(sumHad<0){
											fill_hist2(cosRecoOK, recof0, recob0, Top1costheta, 1);
										}else if(sumHad>0){
											fill_hist2(cosRecoOK, recof0, recob0, Top1costheta, -1);
										}
									}else{
										if(sumHad<0){
											fill_hist2(cosRecoNG, recof0, recob0, Top1costheta, 1);
										}else if(sumHad>0){
											fill_hist2(cosRecoNG, recof0, recob0, Top1costheta, -1);
										}
									}

									//fill_hist(cosRecoOK, recoforward, recobackward, qCostheta);

								}// method check 1234

								if(methodUsedFlag[1] || methodUsedFlag[2] || methodUsedFlag[3] || methodUsedFlag[4] || methodUsedFlag[7]){

									//fill_hist(cosRecoOK, recoforward, recobackward, qCostheta);

								}// method check 12347

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
	cout << "after method75               = " << aftermethod75 			<< " (" << (float)(aftermethod75)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method756              = " << aftermethod756 		<< " (" << (float)(aftermethod756)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method7561             = " << aftermethod7561 		<< " (" << (float)(aftermethod7561)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method75612            = " << aftermethod75612 	<< " (" << (float)(aftermethod75612)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method756123           = " << aftermethod756123 	<< " (" << (float)(aftermethod756123)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method7561234          = " << aftermethod7561234 << " (" << (float)(aftermethod7561234)/(float)(nevt) *100 << "%)" << endl;
	cout << "after method1234             = " << aftermethod1234 		<< " (" << (float)(aftermethod1234)/(float)(nevt) *100 << "%)" << endl;
	cout << endl;
	cout << "skipped (sum = 0)            = " << temp << " (" << (float)(temp)/(float)(nevt) *100 << "%)" << endl;
  cout << "beforecut (cos = -2)         = " << beforecut << endl;
  cout << "aftercut (cos = -2)          = " << aftercut << endl;
	cout << "after gcut                   = " << aftergcut << " (" << (float)(aftergcut)/(float)(nevt) *100 << "%)" << endl;
	cout << "after pcut                   = " << afterpcut << " (" << (float)(afterpcut)/(float)(nevt) *100 << "%)" << endl;
	cout << endl;
	cout << "HadLepMatch = " << HadLepMatch << ", HadLepMissMatch = " << HadLepMissMatch << endl;

	cout << "============================ Method Correct Ratio ============================" << endl;
	cout << "after charge config = " << (float)(afterchgconfig)/(float)(nevt) *100 << "%" << endl;
	for(int kmethod = 1; kmethod < 8; kmethod++){
		cout << "Method" << kmethod << "\t number used = " << aftermethod[kmethod] << "\t (" << (float)(aftermethod[kmethod])/(float)(afterchgconfig) *100 << "%)\t correct ratio = " << (float)(methodcorrect[kmethod])/(float)(aftermethod[kmethod]) * 100 << "%" << endl;
	}
	cout << "MethodAll = " << (float)(methodAllcorrect)/(float)(aftermethod7561234) * 100 << "%" << endl;


	// Plot and Fit

	cosGen->SetStats(0);
	TF1 * fgen = new TF1("fgen","pol2",-1,1);
	TF1 * freco = new TF1("freco","pol2",-0.9,0.9);
	fgen->SetLineColor(kGreen);
	fgen->SetLineStyle(3);
	freco->SetLineStyle(3);


	//cosGen->Scale(cosRecoOK->GetEntries()/ cosGen->GetEntries());
	
	double intCosRecoAll = cosRecoAll->Integral(2,29);
	double intCosRecoOK = cosRecoOK->Integral(2,29);
	double intCosRecoNG = cosRecoNG->Integral(2,29);
	double intCosGen  = cosGen->Integral(2,29);
	//double intCosReco = cosRecoOK->Integral(10,21);
	//double intCosGen  = cosGen->Integral(10,21);
	
	//cosGen->Scale(intCosRecoAll / intCosGen);
	
	cosRecoAll->Scale(1 / intCosRecoAll);
	//cosRecoOK->Scale(intCosRecoAll / intCosGen);
	//cosRecoNG->Scale(intCosRecoAll / intCosGen);
	
	cosRecoOK->Scale(1 / intCosRecoAll);
	cosRecoNG->Scale(1 / intCosRecoAll);
	
	cosGen->Scale( 1 / intCosGen);


	
	cosGen->Fit("fgen","Q");
	cosRecoAll->Fit("freco", "QR");
	//cosRecoOK->Fit("freco", "QR");	
	//cosRecoNG->Fit("freco", "QR");
	

	cosRecoStack->Add(cosRecoNG);
	cosRecoStack->Add(cosRecoOK);

	cosGen->SetMinimum(0);
	cosGen->Draw("he");
	cosRecoNG->Draw("hsame");
	//cosRecoStack->Draw("");
	//cosGen->SetMinimum(0);
	//fgen->Draw("same");
	//cosGen->SetMinimum(0);
	cosRecoAll->Draw("same");
	//cosRecoOK->Draw("samee");
	//cosRecoNG->Draw("samee");

	TLegend *leg = new TLegend(0.2,0.75,0.6,0.85); //set here your x_0,y_0, x_1,y_1 options
	leg->SetTextFont(42);
	leg->AddEntry(cosGen,"Parton level","l");

	leg->AddEntry(cosRecoAll,"Reco. All","l");

	//leg->AddEntry(cosRecoOK,"Reco. Correct","l");
	leg->AddEntry(cosRecoNG,"Reco. Wrong","l");

	leg->SetFillColor(0);
	leg->SetLineColor(0);
	leg->SetShadowColor(0);
	leg->Draw();

	QQBARLabel(0.8,0.2,"",1);

	c1->Update();


	//TCanvas * c2 = new TCanvas("c2", "Data-MC",0,0,500,500);
	//cosMCRC->Draw("COLZ");

	float afbgen = (float)(forward - backward) / (float) (forward + backward);
	float afbreco = (float)(recoforward - recobackward) / (float) (recoforward + recobackward);

	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";
	std::cout << "Afb gen: " << afbgen << " N: " << forward + backward <<  "\n";
	std::cout << "Afb reco: " << afbreco << " N: " << recoforward + recobackward << "(" << afbreco / afbgen *100 << "%)"  << "\n";
	std::cout << "Chi2: " << cosRecoOK->Chi2Test(cosGen,"UUNORMCHI2/NDF") << "\n";
	cout << "--------------------------------------------------------------\n";
	float efficiency = (float)(recoforward + recobackward)/(forward + backward) * 2 * 100;
	cout << "Final efficiency: " << efficiency << "%\n" ;
	cout << "--------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------\n";


	// some garbage I might use later

/*
									// mc loop
									for(int imc=0; imc < 2; imc++){

										float qMCcos = qMCcostheta[imc];

										if(qMCcos > 0 && qMCcos > -2){
											forward++;
											cosGen->Fill(qMCcos);
										}else if(qMCcos < 0 && qMCcos > -2){
											backward++;
											cosGen->Fill(qMCcos);
										}

									}// end for mc loop
*/
	
}

