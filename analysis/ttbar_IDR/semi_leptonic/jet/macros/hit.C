const int NMAXPFOS = 2;
float jet_px[NMAXPFOS], jet_py[NMAXPFOS], jet_pz[NMAXPFOS];

void DrawSlice(float zstart = -3000., float zend = 3000., TTree* T = 0, TH2D* h = 0, TCanvas* c=0)
{
  h->Reset();
  int nevents = T->GetEntries();

  for (int ev = 0; ev < nevents; ev++) {
    
    T->GetEntry(ev);
    for ( int ip = 0; ip < 2; ip++ ) {
      float x = jet_px[ip];
      float y = jet_py[ip];
      float z = jet_pz[ip];
      if (z >= zstart && z<zend) {
        h->Fill(x,y);
      }
    }
  }
  c->cd();
  h->Draw("COL");
  stringstream fname;
  fname << "$HOME/macros/semi_leptonic/jet_p/hit_" << zstart << "_" << zend << ".pdf" << ends;
  c->Print(fname.str().data());
}

void hit ()
{
  TFile* file = new TFile("$HOME/run/root_merge/new/large/leptonic_yyxyev_eLeR_new_large_QQbar_VR.root");
	TTree * normaltree = (TTree*) file->Get( "Stats" ) ;

  TH2D* h = new TH2D("h","",100,-1000,1000,100,-1000,1000);
  TCanvas* c = new TCanvas("c","",600,400);

  normaltree->SetBranchAddress("jet_px",jet_px);
  normaltree->SetBranchAddress("jet_py",jet_py);
  normaltree->SetBranchAddress("jet_pz",jet_pz);

#if 0
  float zstart = 2350.; 
  float dz = 50.;
#else
  float zstart = -2850.; 
  float dz = 50.;
#endif
  for (int i = 0; i < 10; i++) {
    DrawSlice(zstart+i*dz,zstart+(i+1)*dz,normaltree,h,c);
  }

}
