void purity()
{
	string filepath = "/home/ilc/yokugawa/run_preset/root_merge/VertexRestore_out/" ;
	string file		 = "VertexRestore_NewIsoLep_020619.root";
	string filename = filepath + file ;

	TFile * file2 = TFile::Open(filename.c_str());
	gStyle->SetPalette(1);
	int nbin = 30;

	float maxangle = 0.1;
	float maxdev = 20;
	TH2F * rec = new TH2F("rec", ";#alpha;#epsilon/#sigma", nbin,0,maxangle,nbin,0,maxdev );
	TH2F * fake = new TH2F("fake", ";#alpha;#epsilon/#sigma", nbin,0,maxangle,nbin,0,maxdev );
	TCanvas * c1 = new TCanvas("c1", "Data-MC",0,0,1500,500);
	c1->Divide(3,1);
	c1->cd(1);

	TTree * Stats = (TTree*) file2->Get( "Stats" ) ;
	Stats->Project("rec","missedDeviation:missedAngle","missedMomentum > 1. && missedObs > 0");
	//Stats->Project("rec","missedZ:missedObs","missedMomentum > 0. ");
	rec->SetStats(0);
	gPad->SetLeftMargin(0.1);
	gPad->SetRightMargin(0.15);
	rec->Draw("colz");
	rec->GetXaxis()->SetTitleOffset(0.75);
	rec->GetXaxis()->SetTitleSize(.07);
	rec->GetYaxis()->SetTitleOffset(0.75);
	rec->GetYaxis()->SetTitleSize(.07);
	c1->cd(2);
	//TF1 * f1 = new TF1("func", "2.2*atan(x*120)",0,maxangle);
	//TF1 * f1 = new TF1("func", "50.0*x + 2.0",0,maxangle);
	TF1 * f1 = new TF1("func", "func(x)",0,maxangle);
	f1->SetLineWidth(4);
	Stats->Project("fake","fakeDeviation:fakeAngle","fakeMomentum > 1.  && fakeObs > 0");
	//Stats->Project("fake","fakeZ:fakeObs","fakeMomentum > 0.");
	fake->SetStats(0);
	fake->Draw("colz");
	gPad->SetLeftMargin(0.1);
	gPad->SetRightMargin(0.15);
	fake->GetXaxis()->SetTitleOffset(0.75);
	fake->GetXaxis()->SetTitleSize(.07);
	fake->GetYaxis()->SetTitleOffset(0.75);
	fake->GetYaxis()->SetTitleSize(.07);
	TH2F * purity = new TH2F("purity", ";#alpha;#epsilon/#sigma", nbin,0,maxangle,nbin,0,maxdev );
	TH2F * efficiency = new TH2F("efficiency", "efficiency map;#alpha;#epsilon/#sigma", nbin,0,maxangle,nbin,0,maxdev );
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
	TH2F * sum = new TH2F("sum", "missed;#alpha;#epsilon/#sigma", nbin,0,maxangle,nbin,0,maxdev );
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
	gPad->SetLeftMargin(0.1);
	gPad->SetRightMargin(0.15);
	purity->GetXaxis()->SetTitleOffset(0.75);
	purity->GetXaxis()->SetTitleSize(.07);
	purity->GetYaxis()->SetTitleOffset(0.75);
	purity->GetYaxis()->SetTitleSize(.07);

}

float func(float x)
{
	if (x < 0.08)
	{
		return 25*sqrt(x)+1.0;
	}
	else
	{
		return 25;
	}
}
