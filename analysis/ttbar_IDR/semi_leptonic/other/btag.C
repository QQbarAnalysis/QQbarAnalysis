#define MAXN  1000
#include <iostream>
using std::cout;

void btag(){
	int _jetnumber = 0;
	float _btag[MAXN];
	int _nvtx[MAXN];
	int _mcpdg[MAXN];
	int _tag;

	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1000,500);
	c1->Divide(2,1);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadColor(kWhite);
	TH1F * btagWith = new TH1F("with_vertices","Btag with",30,0,1.01 );
	TH1F * btagWithout = new TH1F("without_vertices","Btag without",30,0,1.01 );
	TChain* T = new TChain("Jets");
	T->Add("/home/ilc/yokugawa/run_preset/root_merge/TrashRecoProcessor_out/RecoTest.root");
	TChain* T1 = new TChain("Stats");
	T1->Add("/home/ilc/yokugawa/run_preset/root_merge/TruthVertexFinder_out/MCTest.root");
	T1->SetBranchAddress("tag", &_tag);

	int mTotalNumberOfEvents = T->GetEntries();
	T->SetBranchAddress("numberOfJets", &_jetnumber);
	T->SetBranchAddress("btags", _btag);
	T->SetBranchAddress("mcpdg", _mcpdg);
	T->SetBranchAddress("numberOfVertices", _nvtx);
	cout << "mTotalNumberOfEvents: " << mTotalNumberOfEvents << '\n';
	int counter = 0;
	int num = 0;
	int jetcounter = 0;
	for (unsigned int i = 0; i < mTotalNumberOfEvents; i += 1)
	{
		T->GetEntry(i);
		T1->GetEntry(i);
		if (_tag == 0) 
		{
			continue;
		}
		vector< int > bjets ;
		for (int j = 0; j < _jetnumber; j++) 
		{
			if (abs(_mcpdg[j]) < 1) 
			{
				continue;
			}
			/*
			cout << "PDG: " << _mcpdg[j]
			     << " btag: " << _btag[j]
			     << " vertex#: " << _nvtx[j]
			     << '\n';
			*/
			bjets.push_back(j);
			if (_nvtx[j] > 0) 
			{
				btagWith->Fill(_btag[j]);
			}
			else 
			{
				btagWithout->Fill(_btag[j]);
			}
		}
		if (bjets.size() < 2) 
		{
			//cout << "ERROR! " << i << " event! " << bjets.size() << " size\n ";
			num++;
		}
		if (bjets.size() == 2) 
		{
			if (_btag[bjets[0]] > 0.8 || _btag[bjets[1]] > 0.3) 
			{
				jetcounter++;
			}
			counter++;
		}
	}
	cout << "Total events: " << counter 
	     << " after b-tag cuts: " << jetcounter << '(' << (float)jetcounter/(float)counter*100.0 << "%)"
	     << " errors: " << num
	     << '\n';
	c1->cd(1);
	btagWithout->SetFillColor(kYellow);
	btagWithout->GetXaxis()->SetTitle("tag");
	btagWith->GetXaxis()->SetTitle("tag");
	btagWith->SetFillColor(kBlue);
	btagWith->Draw();
	c1->cd(2);
	btagWithout->Draw();
}
