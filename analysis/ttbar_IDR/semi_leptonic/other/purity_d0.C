#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"


void purity_d0()
//250GeV_eL_before/VertexRestorer_bbbar_eL.root" )
//  void purity(string filename = "VertexRestorer_ttbar_test.root")

{

	string filename = "";
	int token;

	cout << "0 = yyxylv/small" 	  << endl;
	cout << "1 = yyxylv/large" 	  << endl;
	cout << "2 = yyxyev/small" << endl;
	cout << "3 = yyxyev/large" << endl;
	cout << "Choose from 0-3: ";
	cin  >> token;
	cout << endl;

	switch(token){
		case 0 : filename = "/home/ilc/yokugawa/run_preset_small/root_merge/VertexRestore_out/VR_s5_yyxylv.root";
						 break;
		case 1 : filename = "/home/ilc/yokugawa/run_preset/root_merge/VertexRestore_out/VR_l5_yyxylv.root";
						 break;
		case 2 : filename = "/home/ilc/yokugawa/run_preset_small/root_merge/VertexRestore_out/VR_s5_yyxyev.root";
						 break;
		case 3 : filename = "/home/ilc/yokugawa/run_preset/root_merge/VertexRestore_out/VR_l5_yyxyev.root";
						 break;
	}

	//string file		 = "VertexRestore_NewIsoLep_020619.root";
	//string filename = filepath + file ;
	TFile * file2 = TFile::Open(filename.c_str());
	gStyle->SetPalette(1);
	int nbin = 30;

	TTree *Stats = (TTree*)file2->Get("Stats");
	
	float maxangle = 0.1;
	float maxdev = 20;
	TH2F * rec = new TH2F("rec", ";#alpha;d_{0}/#sigma_{D_{0}}", nbin,0,maxangle,nbin,0,maxdev );
	TH2F * fake = new TH2F("fake", ";#alpha;d_{0}/#sigma_{D_{0}}", nbin,0,maxangle,nbin,0,maxdev );
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,1500,500);
	c1->Divide(3,1);
	c1->cd(1);
	Stats->Project("rec","(std::abs(missedD0)/sqrt(missedD0Error)):missedAngle","missedMomentum > 1. && missedObs > 0");
	//Stats->Project("rec","(missedD0Deviation+missedZ0Deviation):missedAngle","missedMomentum > 1. && missedObs > 0");
	//Stats->Project("rec","missedZ:missedObs","missedMomentum > 0. ");
	rec->SetStats(0);
	gPad->SetLeftMargin(0.1);
	gPad->SetRightMargin(0.15);
	rec->Draw("colz");
	rec->GetXaxis()->SetTitleOffset(0.75);
	rec->GetXaxis()->SetTitleSize(.07);
	rec->GetYaxis()->SetTitleOffset(0.75);
	rec->GetYaxis()->SetTitleSize(.06);
	c1->cd(2);
	//TF1 * f1 = new TF1("func", "2.2*atan(x*120)",0,maxangle);
	//TF1 * f1 = new TF1("func", "50.0*x + 2.0",0,maxangle);
	TF1 * f1 = new TF1("func", "func(x)",0,maxangle);
	//	TF1 * f2 = new TF1("func_default", "func_default(x)",0,maxangle);
	f1->SetLineWidth(4);
	//	f2->SetLineWidth(4);

	//Stats->Project("fake","fakeDeviation:fakeAngle","fakeMomentum > 1.  && fakeObs > 0");
	Stats->Project("fake","(std::abs(fakeD0)/sqrt(fakeD0Error)):fakeAngle","fakeMomentum > 1. && fakeObs > 0");
	//Stats->Project("fake","fakeZ:fakeObs","fakeMomentum > 0.");
	fake->SetStats(0);
	fake->Draw("colz");
	gPad->SetLeftMargin(0.1);
	gPad->SetRightMargin(0.15);
	fake->GetXaxis()->SetTitleOffset(0.75);
	fake->GetXaxis()->SetTitleSize(.07);
	fake->GetYaxis()->SetTitleOffset(0.75);
	fake->GetYaxis()->SetTitleSize(.06);
	TH2F * purity = new TH2F("purity", ";#alpha;d_{0}/#sigma_{D_{0}}", nbin,0,maxangle,nbin,0,maxdev );
	TH2F * efficiency = new TH2F("efficiency", "efficiency map;#alpha;d_{0}/#sigma_{D_{0}}", nbin,0,maxangle,nbin,0,maxdev );
	int fakesum = 0;
	int recsum = 0;
	
	/*for (int i = 0; i < nbin; i++) 
	{
		for (int j = nbin-1; j > -1; j--) 
		{
			int nfake = fake->GetBinContent(i+1,j+1);
			int nrec = rec->GetBinContent(i+1,j+1);
			fakesum += nfake;
			recsum += nrec;
			std::cout << "fake: " << nfake 
				  << " fakesum: " << fakesum 
				  << " rec: " << nrec
				  << " recsum: " << recsum 
				  <<  '\n';
			float content = (nfake+nrec > 0)? (float)recsum/(float)(fakesum+recsum)*100.0 : 0;
			purity->SetBinContent(i+1,j+1, (int)content);
		}
	}
	int recsume = 0;
	for (int i = 0; i < nbin; i++) 
	{
		for (int j = nbin-1; j > -1; j--) 
		{
			int nrec = rec->GetBinContent(i+1,j+1);
			recsume += nrec; 
			float content = (recsum > 0)? (float)recsume/(float)(recsum)*100.0 : 0;
			efficiency->SetBinContent(i+1,j+1, (int)content);
		}
	}*/
	string option = "colz";
	c1->cd(3);
	//efficiency->Draw(option.c_str());
	//TF1 * f1 = new TF1("f","sqrt(x-0.0075)+0.2",0,0.1);
	//TF1 * f1 = new TF1("f",".2+100*x",0,10);
	//c1->cd(4);
	TH2F * sum = new TH2F("sum", "missed;#alpha;d_{0}/#sigma_{D_{0}}", nbin,0,maxangle,nbin,0,maxdev );
	sum->Add(rec, fake);
	purity->Divide(rec,sum);
	purity->SetStats(0);
	purity->SetStats(0);
	purity->Draw(option.c_str());
	cout  << "N missed: " << rec->GetEntries() << "\n";
	cout  << "Purity: " << rec->GetEntries() / (rec->GetEntries() + fake->GetEntries()) << endl;
	fake->SetMarkerColor(kRed);
	fake->SetMarkerStyle(20);
	fake->SetMarkerSize(0.5);
	rec->SetMarkerColor(kBlue);
	rec->SetMarkerStyle(20);
	rec->SetMarkerSize(0.5);
	//fake->Draw();
	//rec->Draw("same");
	f1->Draw("same");
	//f2->SetLineColor(1);
	//	f2->Draw("same");
	gPad->SetLeftMargin(0.1);
	gPad->SetRightMargin(0.15);
	purity->GetXaxis()->SetTitleOffset(0.75);
	purity->GetXaxis()->SetTitleSize(.07);
	purity->GetYaxis()->SetTitleOffset(0.75);
	purity->GetYaxis()->SetTitleSize(0.06);
	//	purity->GetYaxis()->SetTitleSize(.07);

}
float func(float x)
{
	if (x < 0.08)
	{
	  //return 20*x+3.8;
	  //return 25*sqrt(x)+1.0;
	  //default bbbar 250  return atan(40*x)+4;
	  return 10*sqrt(x)+1.5;

	  //return 0.3/x+3;//atan(40*x)+4;

	}
	else
	{
		return 25;
	}
}

float func_default(float x)
{
	if (x < 0.08)
	{
	  //return 20*x+3.8;
	  return 25*sqrt(x)+1.0;
	  // return atan(40*x)+4;
	  //return 0.3/x+3;//atan(40*x)+4;

	}
	else
	{
		return 25;
	}
}
