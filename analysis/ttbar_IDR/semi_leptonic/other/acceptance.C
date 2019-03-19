void makePretty(TH1F * missed,  int color);

void acceptance()
{
	int nbins = 100;
	float maxcos = 1;
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,500,500);
	string recofilepath = "/home/ilc/yokugawa/run_preset/root_merge/TrashRecoProcessor_out/";
	string recofilename = "RecoTest.root";
	string recofile			= recofilepath + recofilename;
	TFile *file = TFile::Open(recofile.c_str());
	TTree * TaggedVertices = (TTree*) file->Get( "TaggedVertices" ) ;
	
	TH1F * kcos = new TH1F("kcos","",nbins,0,maxcos);
	TH1F * kgencos = new TH1F("kgencos",";|cos#theta|",nbins,0,maxcos);
	
	makePretty(kcos,kBlue);
	makePretty(kgencos,kGreen);

	int ngenkaons = TaggedVertices->Draw("abs(costhetaOfParticles) >> kgencos","abs(trueTypeOfParticles) == 321 && tpcHitsOfParticles > 60 && abs(costhetaOfParticles) < 0.95 && generation ","");
	int nkaons = TaggedVertices->Draw("abs(costhetaOfParticles) >> kcos","abs(pidTypeOfParticles) == 321 && generation ","same");
	kgencos->Draw();
	kcos->Draw("same");
	cout << "Ratio: " << (float)nkaons / ngenkaons * 100 <<"%\n";
	TLegend *legendMean = new TLegend(0.15,0.25,0.7,0.15,NULL,"brNDC");
        legendMean->SetFillColor(kWhite);
        legendMean->SetBorderSize(0);
        legendMean->AddEntry(kgencos,"Generated kaons","l");
        legendMean->AddEntry(kcos,"Reconstructed kaons","l");
	legendMean->Draw();
}
void makePretty(TH1F * missed,  int color)
{
	missed->SetMinimum(0);
	missed->SetStats(0);
	missed->SetLineColor(color);
	missed->SetLineWidth(2);
}
