
void makePretty(TH2F * p, int color);
void makePretty(TH1F * missed,  int color);

void dEdx()
{
	TCanvas * c1 = new TCanvas("c1", "The 3d view",0,0,1200,600);
	c1->Divide(2,1);
	string recofilepath = "/home/ilc/yokugawa/run_preset/root_merge/TrashRecoProcessor_out/before_vtx_recovery/";
	string recofilename = "RecoTest_before_NewIsoLep_012819.root";
	string recofile			= recofilepath + recofilename;
	TFile * file = TFile::Open(recofile.c_str());
	TTree * TaggedVertices = (TTree*) file->Get( "TaggedVertices" ) ;
	TTree * Stats				 	 = (TTree*) file->Get( "Stats" ) ;

	int nbins = 1000;
	float maxp = 80;
	float maxcos = 1;
	float maxs = 3e-7;
	float maxes = 3e-9;
	float mins = 1e-7;
	
	c1->cd(1);
	TH2F * pip	 	= new TH2F("pip",";p [GeV];dE/dx [GeV/mm]",nbins,0,maxp ,nbins, mins, maxs);
	TH2F * prp 		= new TH2F("prp",";p [GeV];#frac{dE}{dx} [GeV/mm]",nbins,0,maxp ,nbins, mins, maxs);
	TH2F * ep 		= new TH2F("ep",";p [GeV];#frac{dE}{dx} [GeV/mm]",nbins,0,maxp ,nbins, mins, maxs);
	TH2F * mup 		= new TH2F("mup",";p [GeV];#frac{dE}{dx} [GeV/mm]",nbins,0,maxp ,nbins, mins, maxs);
	TH2F * kp 		= new TH2F("kp","",nbins,0,maxp ,nbins, mins, maxs);
	TH2F * picos 	= new TH2F("picos",";|cos#theta|;dE/dx [GeV/mm]",nbins,0,maxcos ,nbins, mins, maxs);
	TH2F * kcos 	= new TH2F("kcos","",nbins,0,maxcos ,nbins, mins, maxs);
	TH2F * pcos 	= new TH2F("pcos","",nbins,0,maxcos ,nbins, mins, maxs);
	TH1F * ko 		= new TH1F("ko",";offset [mm]",nbins, 0, 6);
	TH1F * po 		= new TH1F("po",";offset [mm]",nbins, 0, 6);
	int pcol = kGreen+1;
	makePretty(pip,kRed);
	makePretty(prp,pcol);
	makePretty(ep,kBlack);
	makePretty(mup,kBlack);
	makePretty(kp,kBlue);
	makePretty(picos,kRed);
	makePretty(kcos,kBlue);
	makePretty(pcos,pcol);
	pip->GetYaxis()->SetTitleOffset(1.7);

	int npions=0;
	int nprotons=0;
	int nkaons=0;

	if (recofilename == "RecoTest_before_NewIsoLep_012819.root") 
	{
		//npions = TaggedVertices->Draw("dEdxOfParticles*pow(acos(abs(costhetaOfParticles)),0.15):momentumOfParticles >> pip","dEdxOfParticles > 0 && abs(trueTypeOfParticles) == 211  && generation ","");
		//nprotons = TaggedVertices->Draw("dEdxOfParticles*pow(acos(abs(costhetaOfParticles)),0.15):momentumOfParticles >> prp","dEdxOfParticles > 0 && abs(trueTypeOfParticles) == 2212&& generation","");
		//nkaons = TaggedVertices->Draw("dEdxOfParticles*pow(acos(abs(costhetaOfParticles)),0.15):momentumOfParticles >> kp","dEdxOfParticles > 0 && abs(trueTypeOfParticles) == 321 && generation ","");

		npions = TaggedVertices->Draw("dEdxOfParticles:momentumOfParticles >> pip","dEdxOfParticles > 0 && abs(trueTypeOfParticles) == 211  && generation ","");
		nprotons = TaggedVertices->Draw("dEdxOfParticles:momentumOfParticles >> prp","dEdxOfParticles > 0 && abs(trueTypeOfParticles) == 2212&& generation","");
		nkaons = TaggedVertices->Draw("dEdxOfParticles:momentumOfParticles >> kp","dEdxOfParticles > 0 && abs(trueTypeOfParticles) == 321 && generation ","");


		//int npions = TaggedVertices->Draw("dEdxOfParticles:momentumOfParticles >> pip","dEdxOfParticles > 0 && abs(trueTypeOfParticles) == 211  && generation ","");
		//int nprotons = TaggedVertices->Draw("dEdxOfParticles:momentumOfParticles >> prp","dEdxOfParticles > 0 && abs(trueTypeOfParticles) == 2212&& generation","");
		//int nkaons = TaggedVertices->Draw("dEdxOfParticles:momentumOfParticles >> kp","dEdxOfParticles > 0 && abs(trueTypeOfParticles) == 321 && generation ","");
	}
	if (recofilename == "pid.root") 
	{
		npions = Stats->Draw("dEdx:momentum >> pip","dEdx > 0 && abs(trueType) == 211","");
		nprotons = Stats->Draw("dEdx:momentum >> prp","dEdx > 0 && abs(trueType) == 2212","");
		nkaons = Stats->Draw("dEdx:momentum >> kp","dEdx > 0 && abs(trueType) == 321","");
	}
	cout << "Nkaons: " << nkaons << " nprotons: "<< nprotons << " npions: " << npions << endl;
	gPad->SetLogx();
	TF1 * f1 = new TF1("f1","1.9e-08*log(x)+1.25e-07",0, maxp);
	TF1 * f2 = new TF1("f2","1.9e-08*log(x)+1.07e-07",0, maxp);
	f1->SetLineColor(kGray);
	f2->SetLineColor(kGray);
	gPad->SetLeftMargin(0.18);
	gPad->SetRightMargin(0.05);
	pip->Draw();
	kp->Draw("same");
	prp->Draw("same");
	f1->Draw("same");
	f2->Draw("same");
	TLegend *legendMean = new TLegend(0.2,0.85,0.35,0.7,NULL,"brNDC");
	legendMean->SetFillColor(kWhite);
	legendMean->SetBorderSize(0);
	legendMean->AddEntry(pip,"#pi","fp");
	legendMean->AddEntry(kp,"K","fp");
	legendMean->AddEntry(prp,"p","fp");
	legendMean->Draw();
	if (recofilename == "pid.root") 
	{
		return;
	}
	pip->GetYaxis()->SetTitleOffset(1.6);
	int font = 43;
	int size = 20;
	TLatex text;
	text.SetTextAlign(13);
	text.SetTextSize(size);
	text.SetTextFont(font);
	text.SetTextColor(kGray+2);
	text.SetNDC();
	text.DrawLatex(0.85, 0.86,"ILD");
	c1->cd(2);

	//TaggedVertices->Draw("dEdxOfParticles*pow(acos(abs(costhetaOfParticles)),0.15):costhetaOfParticles >> picos","errordEdxOfParticles > 0 && abs(trueTypeOfParticles) == 211","");
	//TaggedVertices->Draw("dEdxOfParticles*pow(acos(abs(costhetaOfParticles)),0.15):costhetaOfParticles >> kcos","errordEdxOfParticles > 0 && abs(trueTypeOfParticles) == 321","");
	//TaggedVertices->Draw("dEdxOfParticles*pow(acos(abs(costhetaOfParticles)),0.15):costhetaOfParticles >> pcos","errordEdxOfParticles > 0 && abs(trueTypeOfParticles) == 2212","");
	TaggedVertices->Draw("dEdxOfParticles:costhetaOfParticles >> picos","errordEdxOfParticles > 0 && abs(trueTypeOfParticles) == 211","");
	TaggedVertices->Draw("dEdxOfParticles:costhetaOfParticles >> kcos","errordEdxOfParticles > 0 && abs(trueTypeOfParticles) == 321","");
	TaggedVertices->Draw("dEdxOfParticles:costhetaOfParticles >> pcos","errordEdxOfParticles > 0 && abs(trueTypeOfParticles) == 2212","");
	gPad->Modified();
	TaggedVertices->Draw("offsetOfParticles >> ko" , "momentumOfParticles > 0 &&  abs(trueTypeOfParticles) == 321 && generation == 3 && isProngOfParticles == 1");
	TaggedVertices->Draw("offsetOfParticles >> po" , "momentumOfParticles > 0 &&  abs(trueTypeOfParticles) == 211 && generation == 3 && isProngOfParticles == 1");
	gPad->SetLeftMargin(0.18);
	gPad->SetRightMargin(0.05);
	picos->Draw();
	pcos->Draw("same");
	kcos->Draw("same");
	picos->GetYaxis()->SetTitleOffset(1.6);
	makePretty(ko, kBlue);
	makePretty(po,kRed);
	//ko->DrawNormalized();
	//po->DrawNormalized("same");
	TLegend *legendMean1 = new TLegend(0.2,0.85,0.35,0.7,NULL,"brNDC");
	legendMean1->SetFillColor(kWhite);
	legendMean1->SetBorderSize(0);
	legendMean1->AddEntry(picos,"#pi","f");
	legendMean1->AddEntry(kcos,"K","f");
	legendMean1->AddEntry(pcos,"p","f");
	//legendMean1->AddEntry(po,"#pi","l");
	//legendMean1->AddEntry(ko,"K","l");
	legendMean1->Draw();
}
void makePretty(TH2F * p, int color)
{
	p->SetStats(0);
	p->SetMarkerColor(color);	
	p->SetFillColor(color);	
	p->SetMarkerStyle(20);
	p->SetMarkerSize(0.2);
}
void makePretty(TH1F * missed,  int color)
{
	missed->SetMinimum(0);
	missed->SetStats(0);
	missed->SetLineColor(color);
	missed->SetLineWidth(2);
}
