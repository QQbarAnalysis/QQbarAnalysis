#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

void makePretty(TH1F * cosAll, int color, int reconumber)
{
	cosAll->Scale(1./reconumber);
	cosAll->SetLineColor(color);
	//cosAll->SetFillColor(color-1);
	cosAll->SetLineWidth(3);

}

void alpha()
	//250GeV_eL_before/VertexRestorer_bbbar_eL.root" )
	//  void purity(string filename = "VertexRestorer_ttbar_test.root")

{
	//large
	string filepath_large = "/home/ilc/yokugawa/run_preset/root_merge/VertexRestore_out/" ;
	//small
	string filepath_small = "/home/ilc/yokugawa/run_preset_small/root_merge/VertexRestore_out/" ;

	string file		 = "VertexRestore_NewIsoLep_020619.root";

	string filename_large = filepath_large + file ;
	string filename_small = filepath_small + file ;

	TFile * file2 = TFile::Open(filename_large.c_str());
	TFile * file3 = TFile::Open(filename_small.c_str());
	gStyle->SetPalette(1);
	int nbin = 100;

	TTree *Stats = (TTree*)file2->Get("Stats");
	TTree *Stats3 = (TTree*)file3->Get("Stats");


	float maxangle = 1;
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,500,500);
	TH1F * h_alpha_large = new TH1F("h_alpha_large", "alpha", nbin,0,maxangle);
	TH1F * h_alpha_small = new TH1F("h_alpha_small", "alpha", nbin,0,maxangle);

	int reconumber = Stats->Draw("fakeAngle >> h_alpha_large","");
	int reconumber3= Stats3->Draw("fakeAngle >> h_alpha_small","");

	h_alpha_large->SetStats(0);
	h_alpha_small->SetStats(0);
	gPad->SetLeftMargin(0.1);
	gPad->SetRightMargin(0.15);

	makePretty(h_alpha_large,kBlue,reconumber);
	makePretty(h_alpha_small,kRed,reconumber3);

	THStack * stack = new THStack("stack",";alpha; Entries (normalised to N_{rec})");
	stack->Add(h_alpha_large);
	stack->Add(h_alpha_small);

	stack->Draw("histo");
	TLegend *legendMean3 = new TLegend(0.25,0.3,0.45,0.42,NULL,"brNDC");
        legendMean3->SetFillColor(kWhite);
        legendMean3->SetBorderSize(0);
        legendMean3->AddEntry(h_alpha_large,"Large","f");
        legendMean3->AddEntry(h_alpha_small,"Small","f");
	legendMean3->Draw("same");

	c1->Update();









}
