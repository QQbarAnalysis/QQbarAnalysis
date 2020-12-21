#include <unistd.h>
#include <cmath>
#include <iostream>
#define MAXV 8

void getEfficiency(TH1 * good, TH1 * total, bool same, int color, string title)
{
	if (TEfficiency::CheckConsistency(*good, *total)) 
	{
		TEfficiency * eff2 = new TEfficiency(*good, *total);

		eff2->SetTitle(title.c_str());
		eff2->SetLineColor(color);
		eff2->SetLineWidth(2);
		eff2->SetMarkerSize(1);
		eff2->SetMarkerStyle(20);
		if (color == kBlue) 
		{
			eff2->SetMarkerStyle(21);
		}
		eff2->SetMarkerColor(color);
		string draw = (same)? "Psame": "AP";
		eff2->Draw(draw.c_str());
		gPad->Update();
		eff2->GetPaintedGraph()->SetMaximum(1);
		eff2->GetPaintedGraph()->GetYaxis()->SetTitleOffset(1.5);
	}
}
bool IsConsistent(TH1 * good, TH1 * total)
{
	if (TEfficiency::CheckConsistency(*good, *total))
	{
		return true;
	}else{
		return false;
	}
}

void drawLegend()
{
	TH1F *eff1  = new TH1F("cosCCbar", "E(Ntracks)", 5,-1.0,1);
	eff1->SetLineColor(kBlack);
	eff1->SetLineWidth(2);
	eff1->SetMarkerSize(1);
	eff1->SetMarkerStyle(20);
	eff1->SetMarkerColor(kBlack);
	TH1F *eff21  = new TH1F("cosCCbar2", "E(Ntracks)", 5,-1.0,1);
	eff21->SetLineColor(kBlue);
	eff21->SetLineWidth(2);
	eff21->SetMarkerSize(1);
	eff21->SetMarkerStyle(21);
	eff21->SetMarkerColor(kBlue);

	TLegend *legendMean2 = new TLegend(0.2,0.7,0.6,0.85,NULL,"brNDC");
	//legendMean2->SetFillColor(kWhite);
	legendMean2->SetFillStyle(0);
	legendMean2->SetBorderSize(0);
	legendMean2->AddEntry(eff21,"After recovery","pl");
	legendMean2->AddEntry(eff1,"Before recovery","pl");
	legendMean2->Draw();

  //delete eff1;
	//delete eff21;
	//delete legendMean2;
}

void chargeEfficiency()
{
	int color = kBlack;
	TCanvas * c1 = NULL;

	// set plot style
//	SetQQbarStyle();
	gStyle->SetOptFit(0);
	gStyle->SetOptStat(0);  
	gStyle->SetOptTitle(1);
	gStyle->SetTitleBorderSize(0);
	gStyle->SetTitleStyle(0);
	gStyle->SetMarkerSize(0);
	gStyle->SetTitleX(0.2); 
	gStyle->SetTitleY(0.9); 

	std::string recofile_before = "../TrashReco_bfVR_out.root";
	std::string recofile_after = "../TrashReco_afVR_out.root";
	std::string genfile = "../TruthVertexFinder_out.root";

	//gStyle->SetCanvasPreferGL(kTRUE);
	int bin_e = 6;
	int max_e = 3;
	bool same = true;
	if (!c1) 
	{
		c1 = new TCanvas("c1", "Data-MC",0,0,800,800);
		c1->Divide(2,2);
		same = false;
	}
	TH1F * chargemc = new TH1F("distmc", "Generator charge", bin_e,-3,max_e);
	TH1F * chargereco = new TH1F("distreco", "Reconstructed charge", bin_e,-3,max_e);
	int nbins = 50;
	int maxp = 120;
	int maxd = 20;
	TH1F * momentumreco = new TH1F("numberreco2", "Reconstructed particles", nbins,0,maxp);
	TH1F * momentumrecototal = new TH1F("numbercreco", "Reconstructed particles", nbins,0,maxp);
	TH1F * distreco = new TH1F("disteco2", "Reconstructed particles", nbins,0,maxd);
	TH1F * distrecototal = new TH1F("distreco2", "Reconstructed particles", nbins,0,maxd);
	TH1F * btagreco = new TH1F("breco2", "Reconstructed particles", nbins,0,1);
	TH1F * btagrecototal = new TH1F("breco", "Reconstructed particles", nbins,0,1);
	TH1F * numberreco = new TH1F("bn2", "Reconstructed particles", 12,0,12);
	TH1F * numberrecototal = new TH1F("bn", "Reconstructed particles", 12,0,12);
	TH1F * numbergen = new TH1F("bgenn2", "Reconstructed particles", 12,0,12);
	TH1F * numbergentotal = new TH1F("bgenn", "Reconstructed particles", 12,0,12);
	TH1F * cosgen = new TH1F("cosgenn2", "Reconstructed particles", nbins,0,1);
	TH1F * cosgentotal = new TH1F("cosgenn", "Reconstructed particles", nbins,0,1);

	chargereco->Sumw2();
	chargemc->Sumw2();

	TChain* MC2 = new TChain("Stats");
	MC2->Add(genfile.c_str());
	//TChain* MC = new TChain("Vertices");
	//MC->Add("TrashMCTest.root");
	TChain* RECO = new TChain("Stats");
	RECO->Add(recofile_before.c_str());

	TChain* RECO2 = new TChain("Stats");
	RECO2->Add(recofile_after.c_str());

	int _numberOfVertexes = 0;
	int _tag = 0;
	float _coordinates[MAXV][3];
	int _PDG[MAXV];
	int _generation[MAXV];
	int _distance[MAXV];
	int _charge[MAXV];

	int _brecocharge = 0;
	int _bbarrecocharge = 0;
	int _boffsetnumber = 0;
	int _bbaroffsetnumber = 0;
	int _bcharge = 0;
	int _bbarcharge = 0;
	float _bcostheta = 0.0;
	float _bbarcostheta = 0.0;
	float _brecocostheta = 0.0;
	float _bbarrecocostheta = 0.0;
	float _bdistance = 0.0;
	float _bbardistance = 0.0;
	float _bmomentum = 0.0;
	float _bbarmomentum = 0.0;
	int _bnumber = 0;
	int _bbarnumber = 0;
	int _cnumber = 0;
	int _cbarnumber = 0;
	float _bIPdistance = 0.0;
	float _bbarIPdistance = 0.0;
	float _bptmiss = 0.0;
	float _bbarptmiss = 0.0;
	float _bteta = 0.0;
	float _bbarteta = 0.0;
	int _breconumber = 0;
	int _bbarreconumber = 0;
	float _btag = 0.0;
	float _bbartag = 0.0;

	float _zerotag = 0.0;
	float _plustag = 0.0;
	float _minustag = 0.0;
	float _btrusttag = 0.0;
	float _bbartrusttag = 0.0;

	//bool usemva = true;
	bool usemva = false;
	MC2->SetBranchAddress("bcharge", &_bcharge);
	MC2->SetBranchAddress("bbarcharge", &_bbarcharge);
	MC2->SetBranchAddress("btotalnumber", &_bnumber);
	MC2->SetBranchAddress("bbartotalnumber", &_bbarnumber);
	MC2->SetBranchAddress("cbarnumber", &_cbarnumber);
	MC2->SetBranchAddress("cnumber", &_cnumber);
	MC2->SetBranchAddress("bIPdistance", &_bdistance);
	MC2->SetBranchAddress("bbarIPdistance", &_bbardistance);

	int _numberOfTagged = 0;
	int _PDGreco[MAXV];
	int _generationreco[MAXV];
	int _chargereco[MAXV];
	int _numberOfParticles[MAXV];
	int _bnvtx = 0;
	int _bbarnvtx = 0;


	RECO->SetBranchAddress("bcostheta", &_brecocostheta);
	RECO->SetBranchAddress("bbarcostheta", &_bbarrecocostheta);
	RECO->SetBranchAddress("bbarptmiss", &_bbarptmiss);
	RECO->SetBranchAddress("bptmiss", &_bptmiss);

	RECO->SetBranchAddress("bnvtx", &_bnvtx);
	RECO->SetBranchAddress("bbarnvtx", &_bbarnvtx);

	RECO->SetBranchAddress("bbarmomentum", &_bbarmomentum);
	RECO->SetBranchAddress("bmomentum", &_bmomentum);
	RECO->SetBranchAddress("bIPdistance", &_bIPdistance);
	RECO->SetBranchAddress("bbarIPdistance", &_bbarIPdistance);
	RECO->SetBranchAddress("bcharge", &_brecocharge);
	RECO->SetBranchAddress("bbarcharge", &_bbarrecocharge);
	RECO->SetBranchAddress("bnumber", &_breconumber);
	RECO->SetBranchAddress("bbarnumber", &_bbarreconumber);
	RECO->SetBranchAddress("bnoffsettracks", &_boffsetnumber);
	RECO->SetBranchAddress("bbarnoffsettracks", &_bbaroffsetnumber);
	RECO->SetBranchAddress("btag", &_btag);
	RECO->SetBranchAddress("bbartag", &_bbartag);


	if (usemva) 
	{
		RECO->SetBranchAddress("zerotag", &_zerotag);
		RECO->SetBranchAddress("plustag", &_plustag);
		RECO->SetBranchAddress("minustag", &_minustag);
		RECO->SetBranchAddress("btrusttag", &_btrusttag);
		RECO->SetBranchAddress("bbartrusttag", &_bbartrusttag);
	}

	int mTotalNumberOfEvents1 = MC2->GetEntries();

cout << "this is test" << endl;


	int b0num=0;
	int bbar0num=0;
	int breco0num=0;
	int bbarreco0num=0;
	
	int counter = 0;
	int total = 0;
	int num = 1;
	float dist = 8.0;
	int totalcounter = 0;
	cout << "================================= Before Recovery =================================" << "\n";
	cout << "Total events: " << mTotalNumberOfEvents1 << "\n";
	cout << "Total events: " << RECO->GetEntries() << "\n";
	
	for (int k = 0; k < mTotalNumberOfEvents1; k++)
	{
		RECO->GetEntry(k);
		MC2->GetEntry(k);

		if (_bbarreconumber >  0 && _bbarnumber > 0) 
		{
			totalcounter++;
		}
		if (_breconumber >  0 && _bnumber > 0) 
		{
			totalcounter++;
		}
		bool bexist = false;
		bool bbarexist = false;
		float btagcut = 0.8;
		float ncut = 9;
		float pcut = 20.0;
		float distcut = .990;
		float distcutbar = .990;
		float btagcutbar = 0.8;
		float coscut = 10.9;
		float pcutbar = 20.0;
		int bnvtxcut = 0;
		int bbarnvtxcut = 0;

		float mvacut = 0.6;
		float mvacut0 = 0.4;
		
		if(_bbarnumber <= 0) bbar0num++ ;
		if(_bbarreconumber <= 0) bbarreco0num++ ;
		if(_bnumber <= 0) b0num++ ;
		if(_breconumber <= 0) breco0num++ ;

		if (_bbarreconumber %2 == 1 && _bbarreconumber != 3) 
		{
			//btagcutbar = .9;
			//pcutbar = 20.0;
			//distcutbar = 1.0;
			bbarnvtxcut = 1;
		}
		if (_breconumber %2 == 1 && _breconumber != 3) 
		{
			//btagcut = .9;
			//pcut = 20.0;
			//distcut = 1.0;
			bnvtxcut = 1;
		}
		if (_bbarnumber >  -1
				
				//&& _bbartrusttag > mvacut
				//&& _bbarreconumber != _bbarnumber
				//&&_bbarmomentum >pcutbar 
				//&& _bbardistance > distcut
				//&&_bbartag > btagcutbar
				//&& _bbarreconumber < ncut
				//&& _bbarnvtx > bbarnvtxcut
				//&& abs(_bbarrecocostheta) < coscut
				//&&_bbarrecocharge == 0
				//&& (_bbarreconumber %2 == 1)// || _bbarreconumber == 3)
				//&& _bbaroffsetnumber <= 0//_bbarreconumber 
			
			  && _bbarreconumber > 0
				
				//_bbarnumber==_bbarreconumber
				)
				{
					momentumrecototal->Fill(_bbarmomentum);
					distrecototal->Fill(_bbardistance);
					btagrecototal->Fill(_bbartag);
					numbergentotal->Fill(_bbarnumber);
					numberrecototal->Fill(_bbarreconumber);
					cosgentotal->Fill(abs(_bbarrecocostheta));
					total++;
					//std::cout << "Reco bbar charge: " << _bbarrecocharge << '\n';

					//if(_bbarrecocharge == _bbarcharge)
					if ((_bbarrecocharge * _bbarcharge > 0.0) || (_bbarrecocharge ==0 && _bbarcharge == 0)) 
					{
						momentumreco->Fill(_bbarmomentum);
						distreco->Fill(_bbardistance);
						btagreco->Fill(_bbartag);
						numbergen->Fill(_bbarnumber);
						numberreco->Fill(_bbarreconumber);
						cosgen->Fill(abs(_bbarrecocostheta));
						counter++;
					}
				}
		if (_bnumber > -1 
				
				//&& (_zerotag > mvacut0 || _plustag > mvacut || _minustag > mvacut )
				//&& _btrusttag > mvacut
				//&& _breconumber != _bnumber
				//&& _bmomentum > pcut 
				//&& _btag > btagcut
				//&& _bdistance > distcut
				//&& _breconumber < ncut
				//&& _bnvtx > bnvtxcut
				//&& abs(_brecocostheta) < coscut
				//&&_brecocharge == 0
				//&& (_breconumber %2 == 1)// || _breconumber == 3)
				//&& _boffsetnumber <= 0//_breconumber
			  
				&& _breconumber > 0
				
				//_bnumber==_breconumber
				) 
				{
					momentumrecototal->Fill(_bmomentum);
					distrecototal->Fill(_bdistance);
					btagrecototal->Fill(_btag);
					numbergentotal->Fill(_bnumber);
					numberrecototal->Fill(_breconumber);
					cosgentotal->Fill(abs(_brecocostheta));
					total++;
					//if(_brecocharge == _bcharge)
					if ((_brecocharge * _bcharge > 0.0) || (_brecocharge ==0 && _bcharge == 0)) 
					{
						momentumreco->Fill(_bmomentum);
						distreco->Fill(_bdistance);
						btagreco->Fill(_btag);
						numberreco->Fill(_breconumber);
						numbergen->Fill(_bnumber);
						cosgen->Fill(abs(_brecocostheta));
						counter++;

					}
				}
	}

	cout << "Correct charge: " << counter
		<< " of " << total
		<< " (" << (float)counter/(float)total*100. << "%)" << '\n';
	
	cout << "Efficiency: " << (float) total / (float) totalcounter * 100  << "%, out of " << totalcounter << " events." <<'\n';

	cout << "================================= After Recovery =================================" << "\n";

	RECO2->SetBranchAddress("bcostheta", &_brecocostheta);
	RECO2->SetBranchAddress("bbarcostheta", &_bbarrecocostheta);
	RECO2->SetBranchAddress("bbarptmiss", &_bbarptmiss);
	RECO2->SetBranchAddress("bptmiss", &_bptmiss);

	RECO2->SetBranchAddress("bnvtx", &_bnvtx);
	RECO2->SetBranchAddress("bbarnvtx", &_bbarnvtx);

	RECO2->SetBranchAddress("bbarmomentum", &_bbarmomentum);
	RECO2->SetBranchAddress("bmomentum", &_bmomentum);
	RECO2->SetBranchAddress("bIPdistance", &_bIPdistance);
	RECO2->SetBranchAddress("bbarIPdistance", &_bbarIPdistance);
	RECO2->SetBranchAddress("bcharge", &_brecocharge);
	RECO2->SetBranchAddress("bbarcharge", &_bbarrecocharge);
	RECO2->SetBranchAddress("bnumber", &_breconumber);
	RECO2->SetBranchAddress("bbarnumber", &_bbarreconumber);
	RECO2->SetBranchAddress("bnoffsettracks", &_boffsetnumber);
	RECO2->SetBranchAddress("bbarnoffsettracks", &_bbaroffsetnumber);
	RECO2->SetBranchAddress("btag", &_btag);
	RECO2->SetBranchAddress("bbartag", &_bbartag);

	TH1F * momentumreco_after = new TH1F("numberreco2_after", "Reconstructed particles", nbins,0,maxp);
	TH1F * momentumrecototal_after = new TH1F("numbercreco_after", "Reconstructed particles", nbins,0,maxp);
	TH1F * distreco_after = new TH1F("disteco2_after", "Reconstructed particles", nbins,0,maxd);
	TH1F * distrecototal_after = new TH1F("distreco2_after", "Reconstructed particles", nbins,0,maxd);
	TH1F * btagreco_after = new TH1F("breco2_after", "Reconstructed particles", nbins,0,1);
	TH1F * btagrecototal_after = new TH1F("breco_after", "Reconstructed particles", nbins,0,1);
	TH1F * numberreco_after = new TH1F("bn2_after", "Reconstructed particles", 12,0,12);
	TH1F * numberrecototal_after = new TH1F("bn_after", "Reconstructed particles", 12,0,12);
	TH1F * numbergen_after = new TH1F("bgenn2_after", "Reconstructed particles", 12,0,12);
	TH1F * numbergentotal_after = new TH1F("bgenn_after", "Reconstructed particles", 12,0,12);
	TH1F * cosgen_after = new TH1F("cosgenn2_after", "Reconstructed particles", nbins,0,1);
	TH1F * cosgentotal_after = new TH1F("cosgenn_after", "Reconstructed particles", nbins,0,1);

	counter = 0;
	total = 0;
	num = 1;
	dist = 8.0;
	totalcounter = 0;

	for (int k = 0; k < mTotalNumberOfEvents1; k++)
	{
		RECO2->GetEntry(k);
		MC2->GetEntry(k);

		if (_bbarreconumber >  0 && _bbarnumber > 0) 
		{
			totalcounter++;
		}
		if (_breconumber >  0 && _bnumber > 0) 
		{
			totalcounter++;
		}
		bool bexist = false;
		bool bbarexist = false;
		float btagcut = 0.8;
		float ncut = 9;
		float pcut = 20.0;
		float distcut = .990;
		float distcutbar = .990;
		float btagcutbar = 0.8;
		float coscut = 10.9;
		float pcutbar = 20.0;
		int bnvtxcut = 0;
		int bbarnvtxcut = 0;

		float mvacut = 0.6;
		float mvacut0 = 0.4;
		if (_bbarreconumber %2 == 1 && _bbarreconumber != 3) 
		{
			//btagcutbar = .9;
			//pcutbar = 20.0;
			//distcutbar = 1.0;
			bbarnvtxcut = 1;
		}
		if (_breconumber %2 == 1 && _breconumber != 3) 
		{
			//btagcut = .9;
			//pcut = 20.0;
			//distcut = 1.0;
			bnvtxcut = 1;
		}
		if (_bbarnumber >  -1
				
				//&& _bbartrusttag > mvacut
				//&& _bbarreconumber != _bbarnumber
				//&&_bbarmomentum >pcutbar 
				//&& _bbardistance > distcut
				//&&_bbartag > btagcutbar
				//&& _bbarreconumber < ncut
				//&& _bbarnvtx > bbarnvtxcut
				//&& abs(_bbarrecocostheta) < coscut
				//&&_bbarrecocharge == 0
				//&& (_bbarreconumber %2 == 1)// || _bbarreconumber == 3)
				//&& _bbaroffsetnumber <= 0//_bbarreconumber 
			  
				&& _bbarreconumber > 0
				
				//_bbarnumber==_bbarreconumber
				)
				{
					momentumrecototal_after->Fill(_bbarmomentum);
					distrecototal_after->Fill(_bbardistance);
					btagrecototal_after->Fill(_bbartag);
					numbergentotal_after->Fill(_bbarnumber);
					numberrecototal_after->Fill(_bbarreconumber);
					cosgentotal_after->Fill(abs(_bbarrecocostheta));
					total++;
					//std::cout << "Reco bbar charge: " << _bbarrecocharge << '\n';

					//if(_bbarrecocharge == _bbarcharge)
					if ((_bbarrecocharge * _bbarcharge > 0.0) || (_bbarrecocharge ==0 && _bbarcharge == 0)) 
					{
						momentumreco_after->Fill(_bbarmomentum);
						distreco_after->Fill(_bbardistance);
						btagreco_after->Fill(_bbartag);
						numbergen_after->Fill(_bbarnumber);
						numberreco_after->Fill(_bbarreconumber);
						cosgen_after->Fill(abs(_bbarrecocostheta));
						counter++;
					}
				}
		if (_bnumber > -1 

				//&& (_zerotag > mvacut0 || _plustag > mvacut || _minustag > mvacut )
				//&& _btrusttag > mvacut
				//&& _breconumber != _bnumber
				//&& _bmomentum > pcut 
				//&& _btag > btagcut
				//&& _bdistance > distcut
				//&& _breconumber < ncut
				//&& _bnvtx > bnvtxcut
				//&& abs(_brecocostheta) < coscut
				//&&_brecocharge == 0
				//&& (_breconumber %2 == 1)// || _breconumber == 3)
				//&& _boffsetnumber <= 0//_breconumber
			
			  && _breconumber > 0

				//_bnumber==_breconumber
				) 
				{
					momentumrecototal_after->Fill(_bmomentum);
					distrecototal_after->Fill(_bdistance);
					btagrecototal_after->Fill(_btag);
					numbergentotal_after->Fill(_bnumber);
					numberrecototal_after->Fill(_breconumber);
					cosgentotal_after->Fill(abs(_brecocostheta));
					total++;
					//if(_brecocharge == _bcharge)
					if ((_brecocharge * _bcharge > 0.0) || (_brecocharge ==0 && _bcharge == 0)) 
					{
						momentumreco_after->Fill(_bmomentum);
						distreco_after->Fill(_bdistance);
						btagreco_after->Fill(_btag);
						numberreco_after->Fill(_breconumber);
						numbergen_after->Fill(_bnumber);
						cosgen_after->Fill(abs(_brecocostheta));
						counter++;

					}
				}
	}

	gStyle->SetPalette(1);
	c1->cd(1);
	gPad->SetLeftMargin(0.15);
	gPad->SetRightMargin(0.03);
	getEfficiency(btagreco, btagrecototal, same, color, ";btag;Charge purity");
	getEfficiency(btagreco_after, btagrecototal_after, 1, kBlue, ";btag;Charge purity");
	drawLegend();
	
	c1->cd(2);
	gPad->SetLeftMargin(0.15);
	gPad->SetRightMargin(0.03);
	getEfficiency(momentumreco, momentumrecototal, same, color, ";|p_{B,had}|;Charge purity");
	getEfficiency(momentumreco_after, momentumrecototal_after, 1, kBlue, ";|p_{B,had}|;Charge purity");
	
	c1->cd(3);
	gPad->SetLeftMargin(0.15);
	gPad->SetRightMargin(0.03);
	getEfficiency(numberreco, numberrecototal, same, color, ";N_{rec};Charge purity");
	getEfficiency(numberreco_after, numberrecototal_after, 1, kBlue, ";N_{rec};Charge purity");

	c1->cd(4);
	gPad->SetLeftMargin(0.15);
	gPad->SetRightMargin(0.03);
	getEfficiency(cosgen, cosgentotal, same, color, ";|cos#theta_{B}|;Charge purity");
	getEfficiency(cosgen_after, cosgentotal_after, 1, kBlue, ";|cos#theta_{B}|;Charge purity");
	
	cout << "Correct charge: " << counter
		<< " of " << total
		<< " (" << (float)counter/(float)total*100. << "%)" << '\n';
	cout << "Efficiency: " << (float) total / (float) totalcounter * 100  << "%, out of " << totalcounter << " events." <<'\n';
	int font = 43;
	int size = 20;

}

