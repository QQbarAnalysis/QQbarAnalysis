#define observable_cxx
#include "observable.h"
#include "TPad.h"
float getModule(vector< float > & v)
{
  float module = 0.0;
  for (unsigned int i = 0; i < v.size(); i++)
    {
      module += v[i]*v[i];
    }
  module = sqrt(module);
  return module;
}

std::vector< float > getDirection(vector<float> & vectorPoint)
{
  vector< float > vector1;
  float module = getModule(vectorPoint);
  for (int i = 0; i < 3; i++)
    {
      vector1.push_back( vectorPoint[i]/module);
    }
  return vector1;
}

std::vector< float > getAngles(std::vector< float > & direction)
{
  vector< float > result;
  float epsilon = 0.00001;
  float semi = 1.5708;
  float pi = 2*semi;
  float phi = 0.0;
  if (direction[0] > 0.0 && direction[1] > 0.0 - epsilon) 
    {
      phi = atan(direction[1] / direction[0]); //(direction[0] < epsilon && direction[0] > 0.0 - epsilon)?
    }
  if (direction[0] < 0.0 && direction[1] > 0.0) 
    {
      phi = semi - atan(direction[1] / direction[0]) ;
    }
  if (direction[0] < 0.0 && direction[1] < 0.0 + epsilon) 
    {
      phi =  atan(direction[1] / direction[0]) + pi;
    }
  if (direction[0] > 0.0 && direction[1] < 0.0 - epsilon) 
    {
      phi = semi - atan(direction[1] / direction[0]) + pi;
    }
  if (direction[1] > 0.0 && direction[0] < 0.0 + epsilon && direction[0] > 0.0 -  epsilon) 
    {
      phi = semi;
    }
  if (direction[1] < 0.0 && direction[0] < 0.0 + epsilon && direction[0] > 0.0 -  epsilon) 
    {
      phi = pi + semi;
    }
  float teta = acos(direction[2]);
  result.push_back(phi);
  result.push_back(teta);
  return result;
}

float GetCostheta(std::vector<float> & vectorPoint)
{
  float costheta1 =  -2.0;
  std::vector< float > d1= getDirection(vectorPoint);
  costheta1 =  std::cos( getAngles(d1).at(1) );
  return costheta1;
}

void observable::Plot(bool reco_truth=true, int method=0, int n=-1){

  std::vector<TH1F*> asymm_Bc;
  std::vector<TH1F*> asymm_Kc;

  if(method==0 ){    
     asymm_Bc = Asymm_Bc(n,reco_truth);
    asymm_Bc[0]->Add(asymm_Bc[4]);//reco
    asymm_Bc[1]->Add(asymm_Bc[5]);//corrected
    asymm_Bc[2]->Add(asymm_Bc[6]);//bkg
    asymm_Bc[3]->Add(asymm_Bc[7]);//truth
  }
  if(method==1 ){    
    asymm_Bc = Asymm_Kc(n,reco_truth);
    asymm_Bc[0]->Add(asymm_Bc[4]);//reco
    asymm_Bc[1]->Add(asymm_Bc[5]);//corrected
    asymm_Bc[2]->Add(asymm_Bc[6]);//bkg
    asymm_Bc[3]->Add(asymm_Bc[7]);//truth
  }
  if(method==2 ){    
    asymm_Bc = Asymm_Bc(n,reco_truth);
    asymm_Bc[0]->Add(asymm_Bc[4]);//reco
    asymm_Bc[1]->Add(asymm_Bc[5]);//corrected
    asymm_Bc[2]->Add(asymm_Bc[6]);//bkg
    asymm_Bc[3]->Add(asymm_Bc[7]);//truth
    
    asymm_Kc = Asymm_Kc(n,reco_truth);
    asymm_Bc[0]->Add(asymm_Kc[1]);//reco
    asymm_Bc[1]->Add(asymm_Kc[1]);//corrected
    asymm_Bc[2]->Add(asymm_Kc[2]);//bkg
    asymm_Bc[3]->Add(asymm_Kc[3]);//truth

    asymm_Bc[0]->Add(asymm_Kc[4]);//reco
    asymm_Bc[1]->Add(asymm_Kc[5]);//corrected
    asymm_Bc[2]->Add(asymm_Kc[6]);//bkg
    asymm_Bc[3]->Add(asymm_Kc[7]);//truth
  }   

  asymm_Bc[0]->Scale(1./asymm_Bc[4]->Integral());//reco
  asymm_Bc[1]->Scale(1./asymm_Bc[5]->Integral());//corrected
  asymm_Bc[2]->Scale(1./asymm_Bc[6]->Integral());//bkg
  asymm_Bc[3]->Scale(1./asymm_Bc[7]->Integral());//truth
  
  TString s_method="vertex";
  if(method==1)s_method="kaons";
  if(method==1)s_method="all";

  
  TCanvas *canvasBc = new TCanvas("canvasBc","canvasBc",1000,800);
  asymm_Bc[0]->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
  if(method==0 ) asymm_Bc[0]->SetTitle("Vertex, eL");
  if(method==1 ) asymm_Bc[0]->SetTitle("Kaons, eL");
  if(method==2 ) asymm_Bc[0]->SetTitle("eL");

  asymm_Bc[0]->GetYaxis()->SetTitle("Entries/0.05rad");
  asymm_Bc[0]->GetYaxis()->SetRangeUser(0,asymm_Bc[0]->GetMaximum()*1.5);
  asymm_Bc[0]->GetYaxis()->SetTitleOffset(1.5);
  asymm_Bc[0]->SetMarkerStyle(1);
  asymm_Bc[0]->SetMarkerSize(1.5);
  asymm_Bc[0]->SetLineColor(1);
  asymm_Bc[0]->Draw("p");

  asymm_Bc[3]->SetLineColor(3);
  asymm_Bc[3]->SetLineStyle(2);
  asymm_Bc[3]->SetLineWidth(2);
  asymm_Bc[3]->SetFillColor(3);
  asymm_Bc[3]->SetFillStyle(3002);
  asymm_Bc[3]->Draw("histofsame");
  
  /*  asymm_Bc[2]->SetLineColor(2);
  asymm_Bc[2]->SetLineStyle(1);
  asymm_Bc[2]->SetLineWidth(1);
  asymm_Bc[2]->SetFillColor(2);
  asymm_Bc[2]->SetFillStyle(3001);
  asymm_Bc[2]->Draw("histofsame");*/
  
  asymm_Bc[1]->SetMarkerStyle(1);
  asymm_Bc[1]->SetMarkerSize(1.5);
  asymm_Bc[1]->SetMarkerColor(4);
  asymm_Bc[1]->SetLineColor(4);
  asymm_Bc[1]->Draw("psame");

  
  TLegend *legBc = new TLegend(0.22,0.66,0.40,0.85);
  legBc->AddEntry(asymm_Bc[0],"Reco","pl");
  legBc->AddEntry(asymm_Bc[1],"Reco corrected","pl");
  if(reco_truth==true) legBc->AddEntry(asymm_Bc[3],"Reco, truth charge","lf");
  else legBc->AddEntry(asymm_Bc[3],"parton level","lf");
  // legBc->AddEntry(asymm_Bc[2],"Reco, not b#bar{b}","lf");
  legBc->SetFillColor(0);
  legBc->SetLineColor(0);
  legBc->SetShadowColor(0);
  legBc->Draw();

  if(reco_truth==true)  canvasBc->Print(TString::Format("%s_btag1_%0.1f_btag2_%0.1f_truth.eps",s_method.Data(),btag1,btag2));
  else canvasBc->Print(TString::Format("%s_btag1_%0.1f_btag2_%0.1f.eps",s_method.Data(),btag1,btag2));
  
  TCanvas *canvasBc_ratio = new TCanvas("canvasBc_ratio","canvasBc_ratio",800,400);
  TGraphErrors *asymm_Bc_ratio_corrected=Ratio(asymm_Bc[1],asymm_Bc[3]);
  asymm_Bc_ratio_corrected->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
  if(method==0 ) asymm_Bc_ratio_corrected->SetTitle("Vertex, eL");
  if(method==1 ) asymm_Bc_ratio_corrected->SetTitle("Kaons, eL");
  if(method==2 ) asymm_Bc_ratio_corrected->SetTitle("eL");
  asymm_Bc_ratio_corrected->GetYaxis()->SetTitle("ratio_corrected");
  asymm_Bc_ratio_corrected->GetYaxis()->SetRangeUser(0.4,1.4);
  asymm_Bc_ratio_corrected->GetXaxis()->SetRangeUser(-1,1);
  asymm_Bc_ratio_corrected->GetYaxis()->SetTitleOffset(1.5);
  asymm_Bc_ratio_corrected->SetMarkerStyle(1);
  asymm_Bc_ratio_corrected->SetMarkerSize(1.5);
  asymm_Bc_ratio_corrected->SetMarkerColor(4);
  asymm_Bc_ratio_corrected->SetLineColor(4);
  asymm_Bc_ratio_corrected->Draw("alp");
  if(reco_truth==true) canvasBc_ratio->Print(TString::Format("ratio_%s_btag1_%0.1f_btag2_%0.1f_truth.eps",s_method.Data(),btag1,btag2));
  else canvasBc_ratio->Print(TString::Format("ratio_%s_btag1_%0.1f_btag2_%0.1f.eps",s_method.Data(),btag1,btag2));



  TCanvas *canvasKc_p = new TCanvas("canvasKc_p","canvasKc_p",800,400);
  asymm_Kc[8]->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
  asymm_Kc[8]->SetTitle("Vertex, p_value");
  if(method==0 ) asymm_Kc[8]->SetTitle("Vertex, eL");
  if(method==1 ) asymm_Kc[8]->SetTitle("Kaons, eL");
  if(method==2 ) asymm_Kc[8]->SetTitle("eL");
  asymm_Kc[8]->GetYaxis()->SetTitle("ratio_corrected");
  asymm_Kc[8]->GetYaxis()->SetRangeUser(0.6,1.0);
  asymm_Kc[8]->GetXaxis()->SetRangeUser(-1,1);
  asymm_Kc[8]->GetYaxis()->SetTitleOffset(1.5);
  asymm_Kc[8]->SetMarkerStyle(1);
  asymm_Kc[8]->SetMarkerSize(1.5);
  asymm_Kc[8]->SetMarkerColor(4);
  asymm_Kc[8]->SetLineColor(4);
  asymm_Kc[8]->Draw("lp");
  canvasKc_p->Print(TString::Format("p_Kc_%s_btag1_%0.1f_btag2_%0.1f.eps",s_method.Data(),btag1,btag2));


}

std::vector<TH1F*> observable::Asymm_Bc(int n_entries=-1, bool reco_truth=true)
{

  //  gROOT->Reset();
  SetIrlesStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleY(0.92);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleFontSize(0.03);
  gStyle->SetMarkerSize(1.5);
       
  int bbbar_gen=0;
  int bbbar_BcBc_reco=0;
  int bbbar_BcBc_reco_bkg=0;
  int bbbar_BcBc_rejected=0;

  int bbbar_KcKc_reco=0;
  int bbbar_KcKc_rejected=0;
  
  int bbbar_Bc_reco=0;
  int bbbar_Bc_reco_bkg=0;
  
  TH1F * h_bbbar_BcBc_reco = new TH1F("h_bbbar_BcBc_reco","h_bbbar_BcBc_reco",20,-1.0,1.0);
  TH1F * h_bbbar_BcBc_rejected = new TH1F("h_bbbar_BcBc_rejected","h_bbbar_BcBc_rejected",20,-1.0,1.0);
  
  TH1F * asymm_BcBc[4];
  for(int i=0; i<3; i++) {
    asymm_BcBc[i]= new TH1F(TString::Format("Asymm_BcBc_%i",i),TString::Format("Asymm_BcBc_%i",i),20,-1.0,1.0);
    asymm_BcBc[i]->Sumw2();
  }
  //0 == reco (bbbar), 1=truth (for reco selection), 2=bkg (no bbbar), 3= corrected

  TH1F * asymm_Bc[4];
  for(int i=0; i<3; i++) {
    asymm_Bc[i]= new TH1F(TString::Format("Asymm_Bc_%i",i),TString::Format("Asymm_Bc_%i",i),20,-1.0,1.0);
    asymm_Bc[i]->Sumw2();
  }

  TH2F * h_matrix = new TH2F("h_matrix","h_matrix",20,-1.0,1.0,20,-1.0,1.0);
  TH1F * h_eff = new TH1F("h_eff","h_eff",20,-1.0,1.0);


  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

      if(abs(mc_quark_pdg[0])==5) bbbar_gen++;

      if(PreSelection()==false) continue; 

      int Bc[2];
      int Kc[2];
      Bc[0]=0; Bc[1]=0;
      Kc[0]=0; Kc[1]=0;

      std::vector<float> costheta_Bc;
      std::vector<float> costheta_Bc_wrong;
      std::vector<float> costheta_BcBc;
      std::vector<float> costheta_BcBc_wrong;

      std::vector<float> costheta_bbbar;

      for(int ijet=0; ijet<2; ijet++) {
	
	std::vector<float> p;
	p.push_back(jet_px[ijet]);
	p.push_back(jet_py[ijet]);
	p.push_back(jet_pz[ijet]);

	costheta_BcBc.push_back(GetCostheta(p));
	costheta_Bc.push_back(GetCostheta(p));
	
	costheta_BcBc_wrong.push_back(GetCostheta(p));
	costheta_Bc_wrong.push_back(GetCostheta(p));
	
	std::vector<float> p_bbar;
	p_bbar.push_back(mc_quark_px[ijet]);
	p_bbar.push_back(mc_quark_py[ijet]);
	p_bbar.push_back(mc_quark_pz[ijet]);

	costheta_bbbar.push_back(GetCostheta(p_bbar));

	
	Bc[ijet]=ChargeBcJet(ijet);
	Kc[ijet]=ChargeKcJet(ijet);

      }//end ijet

      float cos_truth=-2;
      
      if(abs(mc_quark_pdg[0])==5) {
	costheta_bbbar[0]=  (mc_quark_charge[0] < 0) ? costheta_bbbar[0]: -costheta_bbbar[0];
	costheta_bbbar[1]=  (mc_quark_charge[1] < 0) ? costheta_bbbar[1]: -costheta_bbbar[1];
	
	
	//Information to calculate p, for BcBc category
	if(Bc[0]*Bc[1]>0 ) {
	  bbbar_BcBc_rejected++;
	  h_bbbar_BcBc_rejected->Fill( (costheta_BcBc[0]-costheta_BcBc[1])/2.);
	  h_bbbar_BcBc_rejected->Fill( -(costheta_BcBc[0]-costheta_BcBc[1])/2.);
	}
	
	if(Bc[0]*Bc[1]<0 ) {
	  bbbar_BcBc_reco++;
	  if(Bc[0] < 0) h_bbbar_BcBc_reco->Fill( (costheta_BcBc[0]-costheta_BcBc[1])/2.);
	  else h_bbbar_BcBc_reco->Fill( -(costheta_BcBc[0]-costheta_BcBc[1])/2.);
	}

	//  cos_truth =  (costheta_bbbar[0]+costheta_bbbar[1])/2.;

	if(mc_matching==1 && mc_quark_charge[0]<0 )
	  cos_truth =(costheta_BcBc[0]-costheta_BcBc[1])/2.;
	
	if(mc_matching==1 && mc_quark_charge[0]>0 )
	  cos_truth =-(costheta_BcBc[0]-costheta_BcBc[1])/2.;
	
	if(mc_matching==2 && mc_quark_charge[1]<0 )
	  cos_truth =(costheta_BcBc[0]-costheta_BcBc[1])/2.;
	
	if(mc_matching==2 && mc_quark_charge[1]>0 )
	  cos_truth =-(costheta_BcBc[0]-costheta_BcBc[1])/2.;
	
	if(reco_truth == true){
	  cos_truth = (costheta_bbbar[0] +costheta_bbbar[0])/2.;
	}

	
	h_eff->Fill(cos_truth);
      }
      
      // calculate asymmetry for the different categories
      //Bc Bc case
      if(Bc[0]*Bc[1]<0) {

	costheta_BcBc[0]=  (Bc[0] < 0) ? costheta_BcBc[0]: -costheta_BcBc[0];
	costheta_BcBc[1]=  (Bc[1] < 0) ? costheta_BcBc[1]: -costheta_BcBc[1];
	float cos_reco= (costheta_BcBc[0]+costheta_BcBc[1])/2.;

	
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_BcBc[0]->Fill(cos_reco);
	  asymm_BcBc[1]->Fill(cos_truth);
	  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}

	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_BcBc[2]->Fill(cos_reco);
	  bbbar_BcBc_reco_bkg++;
	}

      }//end BcBc
      
      
      // -------------------------------------------
      //Bc 0 or 0 Bc case
      //case a
      if(Bc[0]!=0 && Bc[1]==0) {
	costheta_Bc[0]=  (Bc[0] < 0) ? costheta_Bc[0]: -costheta_Bc[0];
	costheta_Bc[1]=  (Bc[0] > 0) ? costheta_Bc[1]: -costheta_Bc[1];

	bbbar_Bc_reco++;

	float cos_reco= (costheta_Bc[0]+costheta_Bc[1])/2.;
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_Bc[0]->Fill(cos_reco);
	  asymm_Bc[1]->Fill(cos_truth);
	  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}

	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_Bc[2]->Fill(cos_reco);
	  bbbar_Bc_reco_bkg++;
	}
      }//end Bc/0, case a
      
      if(Bc[1]!=0 && Bc[0]==0) {
	costheta_Bc[0]=  (Bc[1] > 0) ? costheta_Bc[0]: -costheta_Bc[0];
	costheta_Bc[1]=  (Bc[1] < 0) ? costheta_Bc[1]: -costheta_Bc[1];

	bbbar_Bc_reco++;

	float cos_reco= (costheta_Bc[0]+costheta_Bc[1])/2.;

	if(abs(mc_quark_pdg[0])==5) {
	  asymm_Bc[0]->Fill(cos_reco);
	  asymm_Bc[1]->Fill(cos_truth);
	  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}

	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_Bc[2]->Fill(cos_reco);
	  bbbar_Bc_reco_bkg++;
	}
	}//end Bc/0 case b
      
	  
     
   }//end loop

   /// ---****************************************************************************************
   // BcBc
   float p=CalculateP(bbbar_BcBc_reco,bbbar_BcBc_rejected);
   std::vector<float> p_vect=CalculateP(h_bbbar_BcBc_reco,h_bbbar_BcBc_rejected);

   TH1F * p_histo = new TH1F("p_histo_Bc","p_histo_Bc",10,-1,0);
   p_histo->Sumw2();
   for(unsigned i=0; i<p_vect.size()/2; i++) {
     p_histo->SetBinContent(i+1,p_vect.at(i));
     p_histo->SetBinError(i+1,p_vect.at(i+10));
   }

   asymm_BcBc[3]=CorrectHistoDoubleTag(asymm_BcBc[0],p_vect);
   asymm_BcBc[0]->Add(asymm_BcBc[2]);
   asymm_BcBc[1]->Add(asymm_BcBc[2]);
   asymm_BcBc[3]->Add(asymm_BcBc[2]);


   /// ---****************************************************************************************
   // Bc/0 || 0/Bc
   asymm_Bc[3]=CorrectHistoSingleTag(asymm_Bc[0],p_vect);
   asymm_Bc[0]->Add(asymm_Bc[2]);
   asymm_Bc[1]->Add(asymm_Bc[2]);
   asymm_Bc[3]->Add(asymm_Bc[2]);
     
   TCanvas *canvas_matrix = new TCanvas("canvas_matrix","canvas_matrix",1000,800);
   //  canvas_matrix->Divide(2,1);
   canvas_matrix->cd(1);
   float int_y[20];
   for(int i=1; i<21; i++) {
     int_y[i-1]=0;
     for(int j=1; j<21; j++) {
       int_y[i-1]+=h_matrix->GetBinContent(i,j);
     }
   }

   for(int i=1; i<21; i++) {
     for(int j=1; j<21; j++) {
       if(int_y[i-1]>0 && h_matrix->GetBinContent(i,j)) h_matrix->SetBinContent(i,j,h_matrix->GetBinContent(i,j)/int_y[i-1]);
     }
   }
   h_matrix->GetXaxis()->SetTitle("cos_theta_truth");
   h_matrix->GetYaxis()->SetTitle("cos_theta_reco");
   h_matrix->Draw("colz");
   
   if(reco_truth==true) canvas_matrix->Print("BcBc_migrations_truth.eps");
   else canvas_matrix->Print("BcBc_migrations.eps");

   /// ****************************************************************************************
   // Bc/Bc
   //correction

   TCanvas *canvas_BcBc = new TCanvas("canvas_BcBc","canvas_BcBc",1000,800);
   asymm_BcBc[0]->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
   asymm_BcBc[0]->SetTitle("Bc/Bc case, eL");
   asymm_BcBc[0]->GetYaxis()->SetTitle("Entries/0.05rad");
   asymm_BcBc[0]->GetYaxis()->SetRangeUser(0,asymm_BcBc[0]->GetMaximum()*1.5);
   asymm_BcBc[0]->GetYaxis()->SetTitleOffset(1.5);
   asymm_BcBc[0]->SetMarkerStyle(1);
   asymm_BcBc[0]->SetMarkerSize(1.5);
   asymm_BcBc[0]->SetLineColor(1);
   asymm_BcBc[0]->Draw("p");

   asymm_BcBc[1]->SetLineColor(3);
   asymm_BcBc[1]->SetLineStyle(2);
   asymm_BcBc[1]->SetLineWidth(2);
   asymm_BcBc[1]->SetFillColor(3);
   asymm_BcBc[1]->SetFillStyle(3002);
   asymm_BcBc[1]->Draw("histofsame");


   asymm_BcBc[2]->SetLineColor(2);
   asymm_BcBc[2]->SetLineStyle(1);
   asymm_BcBc[2]->SetLineWidth(1);
   asymm_BcBc[2]->SetFillColor(2);
   asymm_BcBc[2]->SetFillStyle(3001);
   asymm_BcBc[2]->Draw("histofsame");

   asymm_BcBc[3]->SetMarkerStyle(1);
   asymm_BcBc[3]->SetMarkerSize(1.5);
   asymm_BcBc[3]->SetMarkerColor(4);
   asymm_BcBc[3]->SetLineColor(4);
   asymm_BcBc[3]->Draw("psame");

   TLegend *leg_BcBc = new TLegend(0.22,0.66,0.61,0.85);
   leg_BcBc->AddEntry(asymm_BcBc[0],TString::Format("Reco, eff=%0.2f ",float(bbbar_BcBc_reco)/float(bbbar_gen)),"pl");
   leg_BcBc->AddEntry(asymm_BcBc[3],TString::Format("Reco corrected, <p=%0.2f>",p),"pl");
   if(reco_truth) leg_BcBc->AddEntry(asymm_BcBc[1],"Reco, truth charge","lf");
   else leg_BcBc->AddEntry(asymm_BcBc[1],"truth","lf");
   leg_BcBc->AddEntry(asymm_BcBc[2],"Reco, not b#bar{b}","lf");
   leg_BcBc->SetFillColor(0);
   leg_BcBc->SetLineColor(0);
   leg_BcBc->SetShadowColor(0);
   leg_BcBc->Draw();

   if(reco_truth==true) canvas_BcBc->Print(TString::Format("BcBc_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));
   else canvas_BcBc->Print(TString::Format("BcBc_btag1_%0.1f_btag2_%0.1f.eps",btag1,btag2));
   /// ---****************************************************************************************
   // Bc/0 || 0/Bc
   asymm_Bc[3]=CorrectHistoSingleTag(asymm_Bc[0],p_vect);

   asymm_Bc[0]->Add(asymm_Bc[2]);
   asymm_Bc[1]->Add(asymm_Bc[2]);
   asymm_Bc[3]->Add(asymm_Bc[2]);


   TCanvas *canvas_Bc = new TCanvas("canvas_Bc","canvas_Bc",1000,800);
   asymm_Bc[0]->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
   asymm_Bc[0]->SetTitle("Bc/0 || 0/Bc case, eL");
   asymm_Bc[0]->GetYaxis()->SetTitle("Entries/0.05rad");
   asymm_Bc[0]->GetYaxis()->SetRangeUser(0,asymm_Bc[0]->GetMaximum()*1.5);
   asymm_Bc[0]->GetYaxis()->SetTitleOffset(1.5);
   asymm_Bc[0]->SetMarkerStyle(1);
   asymm_Bc[0]->SetMarkerSize(1.5);
   asymm_Bc[0]->SetLineColor(1);
   asymm_Bc[0]->Draw("p");

   asymm_Bc[1]->SetLineColor(3);
   asymm_Bc[1]->SetLineStyle(2);
   asymm_Bc[1]->SetLineWidth(2);
   asymm_Bc[1]->SetFillColor(3);
   asymm_Bc[1]->SetFillStyle(3002);
   asymm_Bc[1]->Draw("histofsame");


   asymm_Bc[2]->SetLineColor(2);
   asymm_Bc[2]->SetLineStyle(1);
   asymm_Bc[2]->SetLineWidth(1);
   asymm_Bc[2]->SetFillColor(2);
   asymm_Bc[2]->SetFillStyle(3001);
   asymm_Bc[2]->Draw("histofsame");

   asymm_Bc[3]->SetMarkerStyle(1);
   asymm_Bc[3]->SetMarkerSize(1.5);
   asymm_Bc[3]->SetMarkerColor(4);
   asymm_Bc[3]->SetLineColor(4);
   asymm_Bc[3]->Draw("psame");

  
   TLegend *leg_Bc = new TLegend(0.22,0.66,0.61,0.85);
   leg_Bc->AddEntry(asymm_Bc[0],TString::Format("Reco, eff=%0.2f ",float(bbbar_Bc_reco)/float(bbbar_gen)),"pl");
   leg_Bc->AddEntry(asymm_Bc[3],TString::Format("Reco corrected, <p=%0.2f> ",p),"pl");
   if(reco_truth) leg_Bc->AddEntry(asymm_Bc[1],"Reco, truth charge","lf");
   else leg_Bc->AddEntry(asymm_Bc[1],"truth","lf");
   leg_Bc->AddEntry(asymm_Bc[2],"Reco, not b#bar{b}","lf");
   leg_Bc->SetFillColor(0);
   leg_Bc->SetLineColor(0);
   leg_Bc->SetShadowColor(0);
   leg_Bc->Draw();

   if(reco_truth==true) canvas_Bc->Print(TString::Format("Bc_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));
   else canvas_Bc->Print(TString::Format("Bc_btag1_%0.1f_btag2_%0.1f.eps",btag1,btag2));

   
   TCanvas *canvas_BcBc_ratio = new TCanvas("canvas_BcBc_ratio","canvas_BcBc_ratio",800,400);
   TH1F * asymm_total_corrected =new TH1F("asymm_total_corrected","asymm_total_corrected",20,-1.0,1.0);
   asymm_total_corrected->Add(asymm_BcBc[3]);
   asymm_total_corrected->Add(asymm_Bc[3]);

   TH1F * asymm_total_truth =new TH1F("asymm_total_truth","asymm_total_truth",20,-1.0,1.0);
   asymm_total_truth->Add(asymm_BcBc[1]);
   asymm_total_truth->Add(asymm_Bc[1]);
   
   TGraphErrors *asymm_BcBc_ratio_corrected=Ratio(asymm_total_corrected,asymm_total_truth);
   //   gPad->SetLogy();
   asymm_BcBc_ratio_corrected->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
   asymm_BcBc_ratio_corrected->SetTitle("Bc case, eL");
   asymm_BcBc_ratio_corrected->GetYaxis()->SetTitle("ratio_corrected");
   asymm_BcBc_ratio_corrected->GetYaxis()->SetRangeUser(0.4,1.4);
   asymm_BcBc_ratio_corrected->GetXaxis()->SetRangeUser(-1,1);
   asymm_BcBc_ratio_corrected->GetYaxis()->SetTitleOffset(1.5);
   asymm_BcBc_ratio_corrected->SetMarkerStyle(1);
   asymm_BcBc_ratio_corrected->SetMarkerSize(1.5);
   asymm_BcBc_ratio_corrected->SetMarkerColor(4);
   asymm_BcBc_ratio_corrected->SetLineColor(4);
   asymm_BcBc_ratio_corrected->Draw("alp");

   if(reco_truth==true)canvas_BcBc_ratio->Print(TString::Format("BcBc_Bc_ratio_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));
   else canvas_BcBc_ratio->Print(TString::Format("BcBc_Bc_ratio_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));

   std::vector<TH1F*> result;
   result.push_back(asymm_BcBc[0]);
   result.push_back(asymm_BcBc[3]);
   result.push_back(asymm_BcBc[2]);
   result.push_back(asymm_BcBc[1]);
   result.push_back(asymm_Bc[0]);
   result.push_back(asymm_Bc[3]);
   result.push_back(asymm_Bc[2]);
   result.push_back(asymm_Bc[1]);
   result.push_back(p_histo);

   return result;
}


std::vector<TH1F*> observable::Asymm_Kc(int n_entries=-1, bool reco_truth=true)
{

  //  gROOT->Reset();
  SetIrlesStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleY(0.92);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleFontSize(0.03);
  gStyle->SetMarkerSize(1.5);
       
  int bbbar_gen=0;
  int bbbar_KcKc_reco=0;
  int bbbar_KcKc_reco_bkg=0;
  int bbbar_KcKc_rejected=0;
  int bbbar_Kc_reco=0;
  int bbbar_Kc_reco_bkg=0;

  TH1F * h_bbbar_KcKc_reco = new TH1F("h_bbbar_KcKc_reco","h_bbbar_KcKc_reco",20,-1.0,1.0);
  TH1F * h_bbbar_KcKc_rejected = new TH1F("h_bbbar_KcKc_rejected","h_bbbar_KcKc_rejected",20,-1.0,1.0);
  
  TH1F * asymm_KcKc[4];
  for(int i=0; i<3; i++) {
    asymm_KcKc[i]= new TH1F(TString::Format("Asymm_KcKc_%i",i),TString::Format("Asymm_KcKc_%i",i),20,-1.0,1.0);
    asymm_KcKc[i]->Sumw2();
  }
  //0 == reco (bbbar), 1=truth (for reco selection), 2=bkg (no bbbar), 3= corrected

  TH1F * asymm_Kc[4];
  for(int i=0; i<3; i++) {
    asymm_Kc[i]= new TH1F(TString::Format("Asymm_Kc_%i",i),TString::Format("Asymm_Kc_%i",i),20,-1.0,1.0);
    asymm_Kc[i]->Sumw2();
  }

  TH2F * h_matrix = new TH2F("h_matrix","h_matrix",20,-1.0,1.0,20,-1.0,1.0);
  TH1F * h_eff = new TH1F("h_eff","h_eff",20,-1.0,1.0);


  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

      if(abs(mc_quark_pdg[0])==5) bbbar_gen++;

      if(PreSelection()==false) continue; 

      int Kc[2];
      Kc[0]=0; Kc[1]=0;

      int Bc[2];
      Bc[0]=0; Bc[1]=0;
      
      std::vector<float> costheta_Kc;
      std::vector<float> costheta_Kc_wrong;
      std::vector<float> costheta_KcKc;
      std::vector<float> costheta_KcKc_wrong;

      std::vector<float> costheta_bbbar;

      for(int ijet=0; ijet<2; ijet++) {
	
	std::vector<float> p;
	p.push_back(jet_px[ijet]);
	p.push_back(jet_py[ijet]);
	p.push_back(jet_pz[ijet]);

	costheta_KcKc.push_back(GetCostheta(p));
	costheta_Kc.push_back(GetCostheta(p));
	
	costheta_KcKc_wrong.push_back(GetCostheta(p));
	costheta_Kc_wrong.push_back(GetCostheta(p));
	
	std::vector<float> p_bbar;
	p_bbar.push_back(mc_quark_px[ijet]);
	p_bbar.push_back(mc_quark_py[ijet]);
	p_bbar.push_back(mc_quark_pz[ijet]);

	costheta_bbbar.push_back(GetCostheta(p_bbar));

	
	Bc[ijet]=ChargeBcJet(ijet);
	Kc[ijet]=ChargeKcJet(ijet);

      }//end ijet

      float cos_truth=-2;
      
      if(abs(mc_quark_pdg[0])==5) {
	costheta_bbbar[0]=  (mc_quark_charge[0] < 0) ? costheta_bbbar[0]: -costheta_bbbar[0];
	costheta_bbbar[1]=  (mc_quark_charge[1] < 0) ? costheta_bbbar[1]: -costheta_bbbar[1];
	
	
	//Information to calculate p, for KcKc category
	if(Kc[0]*Kc[1]>0 && Bc[0]==0 && Bc[1]==0) {
	  bbbar_KcKc_rejected++;
	  h_bbbar_KcKc_rejected->Fill( (costheta_KcKc[0]-costheta_KcKc[1])/2.);
	  h_bbbar_KcKc_rejected->Fill( -(costheta_KcKc[0]-costheta_KcKc[1])/2.);
	}
	
	if(Kc[0]*Kc[1]<0 && Bc[0]==0 && Bc[1]==0) {
	  bbbar_KcKc_reco++;
	  if(Kc[0] < 0) h_bbbar_KcKc_reco->Fill( (costheta_KcKc[0]-costheta_KcKc[1])/2.);
	  else h_bbbar_KcKc_reco->Fill( -(costheta_KcKc[0]-costheta_KcKc[1])/2.);
	}

	//  cos_truth =  (costheta_bbbar[0]+costheta_bbbar[1])/2.;

	if(mc_matching==1 && mc_quark_charge[0]<0 )
	  cos_truth =(costheta_KcKc[0]-costheta_KcKc[1])/2.;
	
	if(mc_matching==1 && mc_quark_charge[0]>0 )
	  cos_truth =-(costheta_KcKc[0]-costheta_KcKc[1])/2.;
	
	if(mc_matching==2 && mc_quark_charge[1]<0 )
	  cos_truth =(costheta_KcKc[0]-costheta_KcKc[1])/2.;
	
	if(mc_matching==2 && mc_quark_charge[1]>0 )
	  cos_truth =-(costheta_KcKc[0]-costheta_KcKc[1])/2.;
	
	if(reco_truth == true){
	  cos_truth = (costheta_bbbar[0] +costheta_bbbar[0])/2.;
	}

	
	h_eff->Fill(cos_truth);
      }
      
      // calculate asymmetry for the different categories
      //Kc Kc case
      if(Kc[0]*Kc[1]<0 && Bc[0]==0 && Bc[1]==0) {

	costheta_KcKc[0]=  (Kc[0] < 0) ? costheta_KcKc[0]: -costheta_KcKc[0];
	costheta_KcKc[1]=  (Kc[1] < 0) ? costheta_KcKc[1]: -costheta_KcKc[1];
	float cos_reco= (costheta_KcKc[0]+costheta_KcKc[1])/2.;

	
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_KcKc[0]->Fill(cos_reco);
	  asymm_KcKc[1]->Fill(cos_truth);
	  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}

	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_KcKc[2]->Fill(cos_reco);
	  bbbar_KcKc_reco_bkg++;
	}

      }//end KcKc
      
      
      // -------------------------------------------
      //Kc 0 or 0 Kc case
      //case a
      if(Kc[0]!=0 && Kc[1]==0 && Bc[0]==0 && Bc[1]==0) {
	costheta_Kc[0]=  (Kc[0] < 0) ? costheta_Kc[0]: -costheta_Kc[0];
	costheta_Kc[1]=  (Kc[0] > 0) ? costheta_Kc[1]: -costheta_Kc[1];

	bbbar_Kc_reco++;

	float cos_reco= (costheta_Kc[0]+costheta_Kc[1])/2.;
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_Kc[0]->Fill(cos_reco);
	  asymm_Kc[1]->Fill(cos_truth);
	  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}

	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_Kc[2]->Fill(cos_reco);
	  bbbar_Kc_reco_bkg++;
	}
      }//end Kc/0, case a
      
      if(Kc[1]!=0 && Kc[0]==0 && Bc[0]==0 && Bc[1]==0) {
	costheta_Kc[0]=  (Kc[1] > 0) ? costheta_Kc[0]: -costheta_Kc[0];
	costheta_Kc[1]=  (Kc[1] < 0) ? costheta_Kc[1]: -costheta_Kc[1];

	bbbar_Kc_reco++;

	float cos_reco= (costheta_Kc[0]+costheta_Kc[1])/2.;

	if(abs(mc_quark_pdg[0])==5) {
	  asymm_Kc[0]->Fill(cos_reco);
	  asymm_Kc[1]->Fill(cos_truth);
	  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}

	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_Kc[2]->Fill(cos_reco);
	  bbbar_Kc_reco_bkg++;
	}
	}//end Kc/0 case b
      
	  
     
   }//end loop

   /// ---****************************************************************************************
   // KcKc
   float p=CalculateP(bbbar_KcKc_reco,bbbar_KcKc_rejected);
   std::vector<float> p_vect=CalculateP(h_bbbar_KcKc_reco,h_bbbar_KcKc_rejected);

   TH1F * p_histo = new TH1F("p_histo_Kc","p_histo_Kc",10,-1,0);
     p_histo->Sumw2();
   for(unsigned i=0; i<p_vect.size()/2; i++) {
     p_histo->SetBinContent(i+1,p_vect.at(i));
     p_histo->SetBinError(i+1,p_vect.at(i+10));
   }

   asymm_KcKc[3]=CorrectHistoDoubleTag(asymm_KcKc[0],p_vect);
   asymm_KcKc[0]->Add(asymm_KcKc[2]);
   asymm_KcKc[1]->Add(asymm_KcKc[2]);
   asymm_KcKc[3]->Add(asymm_KcKc[2]);


   /// ---****************************************************************************************
   // Kc/0 || 0/Kc
   asymm_Kc[3]=CorrectHistoSingleTag(asymm_Kc[0],p_vect);
   asymm_Kc[0]->Add(asymm_Kc[2]);
   asymm_Kc[1]->Add(asymm_Kc[2]);
   asymm_Kc[3]->Add(asymm_Kc[2]);
     
   TCanvas *canvas_matrix = new TCanvas("canvas_matrix","canvas_matrix",1000,800);
   //  canvas_matrix->Divide(2,1);
   canvas_matrix->cd(1);
   float int_y[20];
   for(int i=1; i<21; i++) {
     int_y[i-1]=0;
     for(int j=1; j<21; j++) {
       int_y[i-1]+=h_matrix->GetBinContent(i,j);
     }
   }

   for(int i=1; i<21; i++) {
     for(int j=1; j<21; j++) {
       if(int_y[i-1]>0 && h_matrix->GetBinContent(i,j)) h_matrix->SetBinContent(i,j,h_matrix->GetBinContent(i,j)/int_y[i-1]);
     }
   }
   h_matrix->GetXaxis()->SetTitle("cos_theta_truth");
   h_matrix->GetYaxis()->SetTitle("cos_theta_reco");
   h_matrix->Draw("colz");
   
   if(reco_truth==true) canvas_matrix->Print("KcKc_migrations_truth.eps");
   else canvas_matrix->Print("KcKc_migrations.eps");

   /// ****************************************************************************************
   // Kc/Kc
   //correction

   TCanvas *canvas_KcKc = new TCanvas("canvas_KcKc","canvas_KcKc",1000,800);
   asymm_KcKc[0]->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
   asymm_KcKc[0]->SetTitle("Kc/Kc case, eL");
   asymm_KcKc[0]->GetYaxis()->SetTitle("Entries/0.05rad");
   asymm_KcKc[0]->GetYaxis()->SetRangeUser(0,asymm_KcKc[0]->GetMaximum()*1.5);
   asymm_KcKc[0]->GetYaxis()->SetTitleOffset(1.5);
   asymm_KcKc[0]->SetMarkerStyle(1);
   asymm_KcKc[0]->SetMarkerSize(1.5);
   asymm_KcKc[0]->SetLineColor(1);
   asymm_KcKc[0]->Draw("p");

   asymm_KcKc[1]->SetLineColor(3);
   asymm_KcKc[1]->SetLineStyle(2);
   asymm_KcKc[1]->SetLineWidth(2);
   asymm_KcKc[1]->SetFillColor(3);
   asymm_KcKc[1]->SetFillStyle(3002);
   asymm_KcKc[1]->Draw("histofsame");


   asymm_KcKc[2]->SetLineColor(2);
   asymm_KcKc[2]->SetLineStyle(1);
   asymm_KcKc[2]->SetLineWidth(1);
   asymm_KcKc[2]->SetFillColor(2);
   asymm_KcKc[2]->SetFillStyle(3001);
   asymm_KcKc[2]->Draw("histofsame");

   asymm_KcKc[3]->SetMarkerStyle(1);
   asymm_KcKc[3]->SetMarkerSize(1.5);
   asymm_KcKc[3]->SetMarkerColor(4);
   asymm_KcKc[3]->SetLineColor(4);
   asymm_KcKc[3]->Draw("psame");

   TLegend *leg_KcKc = new TLegend(0.22,0.66,0.61,0.85);
   leg_KcKc->AddEntry(asymm_KcKc[0],TString::Format("Reco, eff=%0.2f ",float(bbbar_KcKc_reco)/float(bbbar_gen)),"pl");
   leg_KcKc->AddEntry(asymm_KcKc[3],TString::Format("Reco corrected, <p=%0.2f>",p),"pl");
   if(reco_truth) leg_KcKc->AddEntry(asymm_KcKc[1],"Reco, truth charge","lf");
   else leg_KcKc->AddEntry(asymm_KcKc[1],"truth","lf");
   leg_KcKc->AddEntry(asymm_KcKc[2],"Reco, not b#bar{b}","lf");
   leg_KcKc->SetFillColor(0);
   leg_KcKc->SetLineColor(0);
   leg_KcKc->SetShadowColor(0);
   leg_KcKc->Draw();

   if(reco_truth==true) canvas_KcKc->Print(TString::Format("KcKc_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));
   else canvas_KcKc->Print(TString::Format("KcKc_btag1_%0.1f_btag2_%0.1f.eps",btag1,btag2));
   /// ---****************************************************************************************
   // Kc/0 || 0/Kc
   asymm_Kc[3]=CorrectHistoSingleTag(asymm_Kc[0],p_vect);

   asymm_Kc[0]->Add(asymm_Kc[2]);
   asymm_Kc[1]->Add(asymm_Kc[2]);
   asymm_Kc[3]->Add(asymm_Kc[2]);


   TCanvas *canvas_Kc = new TCanvas("canvas_Kc","canvas_Kc",1000,800);
   asymm_Kc[0]->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
   asymm_Kc[0]->SetTitle("Kc/0 || 0/Kc case, eL");
   asymm_Kc[0]->GetYaxis()->SetTitle("Entries/0.05rad");
   asymm_Kc[0]->GetYaxis()->SetRangeUser(0,asymm_Kc[0]->GetMaximum()*1.5);
   asymm_Kc[0]->GetYaxis()->SetTitleOffset(1.5);
   asymm_Kc[0]->SetMarkerStyle(1);
   asymm_Kc[0]->SetMarkerSize(1.5);
   asymm_Kc[0]->SetLineColor(1);
   asymm_Kc[0]->Draw("p");

   asymm_Kc[1]->SetLineColor(3);
   asymm_Kc[1]->SetLineStyle(2);
   asymm_Kc[1]->SetLineWidth(2);
   asymm_Kc[1]->SetFillColor(3);
   asymm_Kc[1]->SetFillStyle(3002);
   asymm_Kc[1]->Draw("histofsame");


   asymm_Kc[2]->SetLineColor(2);
   asymm_Kc[2]->SetLineStyle(1);
   asymm_Kc[2]->SetLineWidth(1);
   asymm_Kc[2]->SetFillColor(2);
   asymm_Kc[2]->SetFillStyle(3001);
   asymm_Kc[2]->Draw("histofsame");

   asymm_Kc[3]->SetMarkerStyle(1);
   asymm_Kc[3]->SetMarkerSize(1.5);
   asymm_Kc[3]->SetMarkerColor(4);
   asymm_Kc[3]->SetLineColor(4);
   asymm_Kc[3]->Draw("psame");

  
   TLegend *leg_Kc = new TLegend(0.22,0.66,0.61,0.85);
   leg_Kc->AddEntry(asymm_Kc[0],TString::Format("Reco, eff=%0.2f ",float(bbbar_Kc_reco)/float(bbbar_gen)),"pl");
   leg_Kc->AddEntry(asymm_Kc[3],TString::Format("Reco corrected, <p=%0.2f> ",p),"pl");
   if(reco_truth) leg_Kc->AddEntry(asymm_Kc[1],"Reco, truth charge","lf");
   else leg_Kc->AddEntry(asymm_Kc[1],"truth","lf");
   leg_Kc->AddEntry(asymm_Kc[2],"Reco, not b#bar{b}","lf");
   leg_Kc->SetFillColor(0);
   leg_Kc->SetLineColor(0);
   leg_Kc->SetShadowColor(0);
   leg_Kc->Draw();

   if(reco_truth==true) canvas_Kc->Print(TString::Format("Kc_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));
   else canvas_Kc->Print(TString::Format("Kc_btag1_%0.1f_btag2_%0.1f.eps",btag1,btag2));

   
   TCanvas *canvas_KcKc_ratio = new TCanvas("canvas_KcKc_ratio","canvas_KcKc_ratio",800,400);
   TH1F * asymm_total_corrected =new TH1F("asymm_total_corrected","asymm_total_corrected",20,-1.0,1.0);
   asymm_total_corrected->Add(asymm_KcKc[3]);
   asymm_total_corrected->Add(asymm_Kc[3]);

   TH1F * asymm_total_truth =new TH1F("asymm_total_truth","asymm_total_truth",20,-1.0,1.0);
   asymm_total_truth->Add(asymm_KcKc[1]);
   asymm_total_truth->Add(asymm_Kc[1]);
   
   TGraphErrors *asymm_KcKc_ratio_corrected=Ratio(asymm_total_corrected,asymm_total_truth);
   //   gPad->SetLogy();
   asymm_KcKc_ratio_corrected->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
   asymm_KcKc_ratio_corrected->SetTitle("Kc case, eL");
   asymm_KcKc_ratio_corrected->GetYaxis()->SetTitle("ratio_corrected");
   asymm_KcKc_ratio_corrected->GetYaxis()->SetRangeUser(0.4,1.4);
   asymm_KcKc_ratio_corrected->GetXaxis()->SetRangeUser(-1,1);
   asymm_KcKc_ratio_corrected->GetYaxis()->SetTitleOffset(1.5);
   asymm_KcKc_ratio_corrected->SetMarkerStyle(1);
   asymm_KcKc_ratio_corrected->SetMarkerSize(1.5);
   asymm_KcKc_ratio_corrected->SetMarkerColor(4);
   asymm_KcKc_ratio_corrected->SetLineColor(4);
   asymm_KcKc_ratio_corrected->Draw("alp");

   if(reco_truth==true)canvas_KcKc_ratio->Print(TString::Format("KcKc_Kc_ratio_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));
   else canvas_KcKc_ratio->Print(TString::Format("KcKc_Kc_ratio_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));

   std::vector<TH1F*> result;
   result.push_back(asymm_KcKc[0]);
   result.push_back(asymm_KcKc[3]);
   result.push_back(asymm_KcKc[2]);
   result.push_back(asymm_KcKc[1]);
   result.push_back(asymm_Kc[0]);
   result.push_back(asymm_Kc[3]);
   result.push_back(asymm_Kc[2]);
   result.push_back(asymm_Kc[1]);
   result.push_back(p_histo);

   return result;
}


std::vector<TH1F*> observable::Asymm_BcKc(int n_entries=-1, bool reco_truth=true)
{

  //  gROOT->Reset();
  SetIrlesStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleY(0.92);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleFontSize(0.03);
  gStyle->SetMarkerSize(1.5);
       
  int bbbar_gen=0;
  int bbbar_KcKc_reco=0;
  int bbbar_BcBc_reco=0;
  int bbbar_BcKc_reco=0;
  int bbbar_KcBc_reco=0;
  
  TH1F * h_bbbar_KcKc_reco = new TH1F("h_bbbar_KcKc_reco","h_bbbar_KcKc_reco",20,-1.0,1.0);
  TH1F * h_bbbar_KcKc_rejected = new TH1F("h_bbbar_KcKc_rejected","h_bbbar_KcKc_rejected",20,-1.0,1.0);

  TH1F * h_bbbar_BcBc_reco = new TH1F("h_bbbar_BcBc_reco","h_bbbar_BcBc_reco",20,-1.0,1.0);
  TH1F * h_bbbar_BcBc_rejected = new TH1F("h_bbbar_BcBc_rejected","h_bbbar_BcBc_rejected",20,-1.0,1.0);
  
  
  TH1F * asymm_BcBc[4];
  for(int i=0; i<3; i++) {
    asymm_BcBc[i]= new TH1F(TString::Format("Asymm_BcBc_%i",i),TString::Format("Asymm_BcBc_%i",i),20,-1.0,1.0);
    asymm_BcBc[i]->Sumw2();
  }

  TH1F * asymm_KcKc[4];
  for(int i=0; i<3; i++) {
    asymm_KcKc[i]= new TH1F(TString::Format("Asymm_KcKc_%i",i),TString::Format("Asymm_KcKc_%i",i),20,-1.0,1.0);
    asymm_KcKc[i]->Sumw2();
  }
  //0 == reco (bbbar), 1=truth (for reco selection), 2=bkg (no bbbar), 3= corrected

  TH1F * asymm_BcKc[4];
  for(int i=0; i<3; i++) {
    asymm_BcKc[i]= new TH1F(TString::Format("Asymm_BcKc_%i",i),TString::Format("Asymm_BcKc_%i",i),20,-1.0,1.0);
    asymm_BcKc[i]->Sumw2();
  }

  TH1F * asymm_KcBc[4];
  for(int i=0; i<3; i++) {
    asymm_KcBc[i]= new TH1F(TString::Format("Asymm_KcBc_%i",i),TString::Format("Asymm_KcBc_%i",i),20,-1.0,1.0);
    asymm_KcBc[i]->Sumw2();
  }


  // TH2F * h_matrix = new TH2F("h_matrix","h_matrix",20,-1.0,1.0,20,-1.0,1.0);
  //TH1F * h_eff = new TH1F("h_eff","h_eff",20,-1.0,1.0);


  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

      if(abs(mc_quark_pdg[0])==5) bbbar_gen++;

      if(PreSelection()==false) continue; 

      int Kc[2];
      Kc[0]=0; Kc[1]=0;

      int Bc[2];
      Bc[0]=0; Bc[1]=0;
      
      std::vector<float> costheta_KcKc;
      std::vector<float> costheta_BcBc;
      std::vector<float> costheta_BcKc;
      std::vector<float> costheta_KcBc;

      std::vector<float> costheta_bbbar;

      for(int ijet=0; ijet<2; ijet++) {
	
	std::vector<float> p;
	p.push_back(jet_px[ijet]);
	p.push_back(jet_py[ijet]);
	p.push_back(jet_pz[ijet]);

	costheta_BcBc.push_back(GetCostheta(p));
	costheta_KcKc.push_back(GetCostheta(p));
	costheta_BcKc.push_back(GetCostheta(p));
	costheta_KcBc.push_back(GetCostheta(p));

	std::vector<float> p_bbar;
	p_bbar.push_back(mc_quark_px[ijet]);
	p_bbar.push_back(mc_quark_py[ijet]);
	p_bbar.push_back(mc_quark_pz[ijet]);

	costheta_bbbar.push_back(GetCostheta(p_bbar));

	
	Bc[ijet]=ChargeBcJet(ijet);
	Kc[ijet]=ChargeKcJet(ijet);

      }//end ijet

      float cos_truth=-2;
      
      if(abs(mc_quark_pdg[0])==5) {
	costheta_bbbar[0]=  (mc_quark_charge[0] < 0) ? costheta_bbbar[0]: -costheta_bbbar[0];
	costheta_bbbar[1]=  (mc_quark_charge[1] < 0) ? costheta_bbbar[1]: -costheta_bbbar[1];
	
	//Information to calculate p, for KcKc category
	if(Kc[0]*Kc[1]>0 && Bc[0]==0 && Bc[1]==0) {
	  //bbbar_KcKc_rejected++;
	  h_bbbar_KcKc_rejected->Fill( (costheta_KcKc[0]-costheta_KcKc[1])/2.);
	  h_bbbar_KcKc_rejected->Fill( -(costheta_KcKc[0]-costheta_KcKc[1])/2.);
	}
	
	if(Kc[0]*Kc[1]<0 && Bc[0]==0 && Bc[1]==0) {
	  if(Kc[0] < 0) h_bbbar_KcKc_reco->Fill( (costheta_KcKc[0]-costheta_KcKc[1])/2.);
	  else h_bbbar_KcKc_reco->Fill( -(costheta_KcKc[0]-costheta_KcKc[1])/2.);
	}

	//Information to calculate p, for BcBc category
	if(Bc[0]*Bc[1]>0 && Kc[0]==0 && Kc[1]==0) {
	  //bbbar_BcBc_rejected++;
	  h_bbbar_BcBc_rejected->Fill( (costheta_BcBc[0]-costheta_BcBc[1])/2.);
	  h_bbbar_BcBc_rejected->Fill( -(costheta_BcBc[0]-costheta_BcBc[1])/2.);
	}
	
	if(Bc[0]*Bc[1]<0 && Kc[0]==0 && Kc[1]==0) {
	  if(Bc[0] < 0) h_bbbar_BcBc_reco->Fill( (costheta_BcBc[0]-costheta_BcBc[1])/2.);
	  else h_bbbar_BcBc_reco->Fill( -(costheta_BcBc[0]-costheta_BcBc[1])/2.);
	}
	

	//  cos_truth =  (costheta_bbbar[0]+costheta_bbbar[1])/2.;

	if(mc_matching==1 && mc_quark_charge[0]<0 )
	  cos_truth =(costheta_KcKc[0]-costheta_KcKc[1])/2.;
	
	if(mc_matching==1 && mc_quark_charge[0]>0 )
	  cos_truth =-(costheta_KcKc[0]-costheta_KcKc[1])/2.;
	
	if(mc_matching==2 && mc_quark_charge[1]<0 )
	  cos_truth =(costheta_KcKc[0]-costheta_KcKc[1])/2.;
	
	if(mc_matching==2 && mc_quark_charge[1]>0 )
	  cos_truth =-(costheta_KcKc[0]-costheta_KcKc[1])/2.;
	
	if(reco_truth == false){
	  cos_truth = (costheta_bbbar[0] +costheta_bbbar[0])/2.;
	}

	
	//	h_eff->Fill(cos_truth);
      }

      bool disagreement = false;
      if ( Bc[0]*Bc[1]>0 || Bc[0]*Kc[1]>0 || Kc[0]*Kc[1]>0 || Kc[0]*Bc[1]>0) disagreement = true;
      
      if(Bc[0]*Bc[1]<0 && disagreement == false) {
	// ------------------------------------------------------------------------
	// Bc Bc case
	// calculate asymmetry for the different categories
	
	costheta_BcBc[0]=  (Bc[0] < 0) ? costheta_BcBc[0]: -costheta_BcBc[0];
	costheta_BcBc[1]=  (Bc[1] < 0) ? costheta_BcBc[1]: -costheta_BcBc[1];
	float cos_reco= (costheta_BcBc[0]+costheta_BcBc[1])/2.;
	bbbar_BcBc_reco++;

	
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_BcBc[0]->Fill(cos_reco);
	  asymm_BcBc[1]->Fill(cos_truth);
	  // h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}

	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_BcBc[2]->Fill(cos_reco);
	}

      } else if(Kc[0]*Kc[1]<0 && disagreement == false) {
	  // ------------------------------------------------------------------------
	  // Kc Kc case
	  // calculate asymmetry for the different categories

	costheta_KcKc[0]=  (Kc[0] < 0) ? costheta_KcKc[0]: -costheta_KcKc[0];
	costheta_KcKc[1]=  (Kc[1] < 0) ? costheta_KcKc[1]: -costheta_KcKc[1];
	float cos_reco= (costheta_KcKc[0]+costheta_KcKc[1])/2.;
	bbbar_KcKc_reco++;

	
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_KcKc[0]->Fill(cos_reco);
	  asymm_KcKc[1]->Fill(cos_truth);
	  //  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}

	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_KcKc[2]->Fill(cos_reco);
	}

      } else if( Bc[0]*Kc[1]<0 && disagreement == false) {
	// -------------------------------------------
	//BcKc 
	//case a
	costheta_BcKc[0]=  (Bc[0] < 0) ? costheta_BcKc[0]: -costheta_BcKc[0];
	costheta_BcKc[1]=  (Kc[1] < 0) ? costheta_BcKc[1]: -costheta_BcKc[1];

	bbbar_BcKc_reco++;

	float cos_reco= (costheta_BcKc[0]+costheta_BcKc[1])/2.;
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_BcKc[0]->Fill(cos_reco);
	  asymm_BcKc[1]->Fill(cos_truth);
	  //	  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}

	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_BcKc[2]->Fill(cos_reco);
	}
      } else if( Kc[0]*Bc[1]<0 && disagreement == false)  {
	// -------------------------------------------
	//KcBc 
	//case b
	costheta_KcBc[0]=  (Kc[0] < 0) ? costheta_KcBc[0]: -costheta_KcBc[0];
	costheta_KcBc[1]=  (Bc[1] < 0) ? costheta_KcBc[1]: -costheta_KcBc[1];

	bbbar_KcBc_reco++;

	float cos_reco= (costheta_KcBc[0]+costheta_KcBc[1])/2.;
	if(abs(mc_quark_pdg[0])==5) {
	  asymm_KcBc[0]->Fill(cos_reco);
	  asymm_KcBc[1]->Fill(cos_truth);
	  //	  h_matrix->Fill((costheta_bbbar[0]+costheta_bbbar[1])/2.,cos_truth);
	}

	if(abs(mc_quark_pdg[0])!=5) {
	  asymm_KcBc[2]->Fill(cos_reco);
	}
      }
      
	  
     
   }//end loop

   /// ---****************************************************************************************
   // KcKc
   std::vector<float> p_k_vect=CalculateP(h_bbbar_KcKc_reco,h_bbbar_KcKc_rejected);

   TH1F * p_k_histo = new TH1F("p_k_histo_Kc","p_k_histo_Kc",10,-1,0);
   p_k_histo->Sumw2();
   for(unsigned i=0; i<p_k_vect.size()/2; i++) {
     p_k_histo->SetBinContent(i+1,p_k_vect.at(i));
     p_k_histo->SetBinError(i+1,p_k_vect.at(i+10));
   }

   asymm_KcKc[3]=CorrectHistoDoubleTag(asymm_KcKc[0],p_k_vect);
   asymm_KcKc[0]->Add(asymm_KcKc[2]);
   asymm_KcKc[1]->Add(asymm_KcKc[2]);
   asymm_KcKc[3]->Add(asymm_KcKc[2]);


   /// ---****************************************************************************************
   // BcBc
   std::vector<float> p_b_vect=CalculateP(h_bbbar_BcBc_reco,h_bbbar_BcBc_rejected);

   TH1F * p_b_histo = new TH1F("p_b_histo_Kc","p_b_histo_Kc",10,-1,0);
   p_b_histo->Sumw2();
   for(unsigned i=0; i<p_b_vect.size()/2; i++) {
     p_b_histo->SetBinContent(i+1,p_b_vect.at(i));
     p_b_histo->SetBinError(i+1,p_b_vect.at(i+10));
   }
   asymm_BcBc[3]=CorrectHistoDoubleTag(asymm_BcBc[0],p_b_vect);
   asymm_BcBc[0]->Add(asymm_BcBc[2]);
   asymm_BcBc[1]->Add(asymm_BcBc[2]);
   asymm_BcBc[3]->Add(asymm_BcBc[2]);


   /// ---****************************************************************************************
   // BcKc
   asymm_BcKc[3]=CorrectHistoDoubleTag(asymm_BcKc[0],p_b_vect,p_k_vect);
   asymm_BcKc[0]->Add(asymm_BcKc[2]);
   asymm_BcKc[1]->Add(asymm_BcKc[2]);
   asymm_BcKc[3]->Add(asymm_BcKc[2]);

   asymm_KcBc[3]=CorrectHistoDoubleTag(asymm_KcBc[0],p_k_vect,p_b_vect);
   asymm_KcBc[0]->Add(asymm_KcBc[2]);
   asymm_KcBc[1]->Add(asymm_KcBc[2]);
   asymm_KcBc[3]->Add(asymm_KcBc[2]);
      

   /// ****************************************************************************************
   // Kc/Kc
   //correction

   TCanvas *canvas_KcKc = new TCanvas("canvas_KcKc","canvas_KcKc",1000,800);
   asymm_KcKc[0]->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
   asymm_KcKc[0]->SetTitle("Kc/Kc case, eL");
   asymm_KcKc[0]->GetYaxis()->SetTitle("Entries/0.05rad");
   asymm_KcKc[0]->GetYaxis()->SetRangeUser(0,asymm_KcKc[0]->GetMaximum()*1.5);
   asymm_KcKc[0]->GetYaxis()->SetTitleOffset(1.5);
   asymm_KcKc[0]->SetMarkerStyle(1);
   asymm_KcKc[0]->SetMarkerSize(1.5);
   asymm_KcKc[0]->SetLineColor(1);
   asymm_KcKc[0]->Draw("p");

   asymm_KcKc[1]->SetLineColor(3);
   asymm_KcKc[1]->SetLineStyle(2);
   asymm_KcKc[1]->SetLineWidth(2);
   asymm_KcKc[1]->SetFillColor(3);
   asymm_KcKc[1]->SetFillStyle(3002);
   asymm_KcKc[1]->Draw("histofsame");


   asymm_KcKc[2]->SetLineColor(2);
   asymm_KcKc[2]->SetLineStyle(1);
   asymm_KcKc[2]->SetLineWidth(1);
   asymm_KcKc[2]->SetFillColor(2);
   asymm_KcKc[2]->SetFillStyle(3001);
   asymm_KcKc[2]->Draw("histofsame");

   asymm_KcKc[3]->SetMarkerStyle(1);
   asymm_KcKc[3]->SetMarkerSize(1.5);
   asymm_KcKc[3]->SetMarkerColor(4);
   asymm_KcKc[3]->SetLineColor(4);
   asymm_KcKc[3]->Draw("psame");

   TLegend *leg_KcKc = new TLegend(0.22,0.66,0.61,0.85);
   leg_KcKc->AddEntry(asymm_KcKc[0],TString::Format("Reco, eff=%0.3f",float(bbbar_KcKc_reco)/float(bbbar_gen)),"pl");
   leg_KcKc->AddEntry(asymm_KcKc[3],"Reco corrected","pl");
   if(reco_truth) leg_KcKc->AddEntry(asymm_KcKc[1],"Reco, truth charge","lf");
   else leg_KcKc->AddEntry(asymm_KcKc[1],"truth","lf");
   leg_KcKc->AddEntry(asymm_KcKc[2],"Reco, not b#bar{b}","lf");
   leg_KcKc->SetFillColor(0);
   leg_KcKc->SetLineColor(0);
   leg_KcKc->SetShadowColor(0);
   leg_KcKc->Draw();

   if(reco_truth==true) canvas_KcKc->Print(TString::Format("KcKc_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));
   else canvas_KcKc->Print(TString::Format("KcKc_btag1_%0.1f_btag2_%0.1f.eps",btag1,btag2));

   //--------------------------------------------------------------------------
   
   TCanvas *canvas_BcBc = new TCanvas("canvas_BcBc","canvas_BcBc",1000,800);
   asymm_BcBc[0]->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
   asymm_BcBc[0]->SetTitle("BcBc case, eL");
   asymm_BcBc[0]->GetYaxis()->SetTitle("Entries/0.05rad");
   asymm_BcBc[0]->GetYaxis()->SetRangeUser(0,asymm_BcBc[0]->GetMaximum()*1.5);
   asymm_BcBc[0]->GetYaxis()->SetTitleOffset(1.5);
   asymm_BcBc[0]->SetMarkerStyle(1);
   asymm_BcBc[0]->SetMarkerSize(1.5);
   asymm_BcBc[0]->SetLineColor(1);
   asymm_BcBc[0]->Draw("p");

   asymm_BcBc[1]->SetLineColor(3);
   asymm_BcBc[1]->SetLineStyle(2);
   asymm_BcBc[1]->SetLineWidth(2);
   asymm_BcBc[1]->SetFillColor(3);
   asymm_BcBc[1]->SetFillStyle(3002);
   asymm_BcBc[1]->Draw("histofsame");


   asymm_BcBc[2]->SetLineColor(2);
   asymm_BcBc[2]->SetLineStyle(1);
   asymm_BcBc[2]->SetLineWidth(1);
   asymm_BcBc[2]->SetFillColor(2);
   asymm_BcBc[2]->SetFillStyle(3001);
   asymm_BcBc[2]->Draw("histofsame");

   asymm_BcBc[3]->SetMarkerStyle(1);
   asymm_BcBc[3]->SetMarkerSize(1.5);
   asymm_BcBc[3]->SetMarkerColor(4);
   asymm_BcBc[3]->SetLineColor(4);
   asymm_BcBc[3]->Draw("psame");

  
   TLegend *leg_BcBc = new TLegend(0.22,0.66,0.61,0.85);
   leg_BcBc->AddEntry(asymm_BcBc[0],TString::Format("Reco, eff=%0.3f",float(bbbar_BcBc_reco)/float(bbbar_gen)),"pl");
   leg_BcBc->AddEntry(asymm_BcBc[3],"Reco corrected","pl");
   if(reco_truth) leg_BcBc->AddEntry(asymm_BcBc[1],"Reco, truth charge","lf");
   else leg_BcBc->AddEntry(asymm_BcBc[1],"truth","lf");
   leg_BcBc->AddEntry(asymm_BcBc[2],"Reco, not b#bar{b}","lf");
   leg_BcBc->SetFillColor(0);
   leg_BcBc->SetLineColor(0);
   leg_BcBc->SetShadowColor(0);
   leg_BcBc->Draw();

   if(reco_truth==true) canvas_BcBc->Print(TString::Format("BcBc_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));
   else canvas_BcBc->Print(TString::Format("BcBc_btag1_%0.1f_btag2_%0.1f.eps",btag1,btag2));

   //--------------------------------------------------------------------------
   
   TCanvas *canvas_BcKc = new TCanvas("canvas_BcKc","canvas_BcKc",1000,800);
   asymm_BcKc[0]->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
   asymm_BcKc[0]->SetTitle("BcKc case, eL");
   asymm_BcKc[0]->GetYaxis()->SetTitle("Entries/0.05rad");
   asymm_BcKc[0]->GetYaxis()->SetRangeUser(0,asymm_BcKc[0]->GetMaximum()*1.5);
   asymm_BcKc[0]->GetYaxis()->SetTitleOffset(1.5);
   asymm_BcKc[0]->SetMarkerStyle(1);
   asymm_BcKc[0]->SetMarkerSize(1.5);
   asymm_BcKc[0]->SetLineColor(1);
   asymm_BcKc[0]->Draw("p");

   asymm_BcKc[1]->SetLineColor(3);
   asymm_BcKc[1]->SetLineStyle(2);
   asymm_BcKc[1]->SetLineWidth(2);
   asymm_BcKc[1]->SetFillColor(3);
   asymm_BcKc[1]->SetFillStyle(3002);
   asymm_BcKc[1]->Draw("histofsame");


   asymm_BcKc[2]->SetLineColor(2);
   asymm_BcKc[2]->SetLineStyle(1);
   asymm_BcKc[2]->SetLineWidth(1);
   asymm_BcKc[2]->SetFillColor(2);
   asymm_BcKc[2]->SetFillStyle(3001);
   asymm_BcKc[2]->Draw("histofsame");

   asymm_BcKc[3]->SetMarkerStyle(1);
   asymm_BcKc[3]->SetMarkerSize(1.5);
   asymm_BcKc[3]->SetMarkerColor(4);
   asymm_BcKc[3]->SetLineColor(4);
   asymm_BcKc[3]->Draw("psame");

  
   TLegend *leg_BcKc = new TLegend(0.22,0.66,0.61,0.85);
   leg_BcKc->AddEntry(asymm_BcKc[0],TString::Format("Reco, eff=%0.3f",float(bbbar_BcKc_reco)/float(bbbar_gen)),"pl");
   leg_BcKc->AddEntry(asymm_BcKc[3],"Reco corrected","pl");
   if(reco_truth) leg_BcKc->AddEntry(asymm_BcKc[1],"Reco, truth charge","lf");
   else leg_BcKc->AddEntry(asymm_BcKc[1],"truth","lf");
   leg_BcKc->AddEntry(asymm_BcKc[2],"Reco, not b#bar{b}","lf");
   leg_BcKc->SetFillColor(0);
   leg_BcKc->SetLineColor(0);
   leg_BcKc->SetShadowColor(0);
   leg_BcKc->Draw();

   if(reco_truth==true) canvas_BcKc->Print(TString::Format("BcKc_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));
   else canvas_BcKc->Print(TString::Format("BcKc_btag1_%0.1f_btag2_%0.1f.eps",btag1,btag2));

     //--------------------------------------------------------------------------
   
   TCanvas *canvas_KcBc = new TCanvas("canvas_KcBc","canvas_KcBc",1000,800);
   asymm_KcBc[0]->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
   asymm_KcBc[0]->SetTitle("KcBc case, eL");
   asymm_KcBc[0]->GetYaxis()->SetTitle("Entries/0.05rad");
   asymm_KcBc[0]->GetYaxis()->SetRangeUser(0,asymm_KcBc[0]->GetMaximum()*1.5);
   asymm_KcBc[0]->GetYaxis()->SetTitleOffset(1.5);
   asymm_KcBc[0]->SetMarkerStyle(1);
   asymm_KcBc[0]->SetMarkerSize(1.5);
   asymm_KcBc[0]->SetLineColor(1);
   asymm_KcBc[0]->Draw("p");

   asymm_KcBc[1]->SetLineColor(3);
   asymm_KcBc[1]->SetLineStyle(2);
   asymm_KcBc[1]->SetLineWidth(2);
   asymm_KcBc[1]->SetFillColor(3);
   asymm_KcBc[1]->SetFillStyle(3002);
   asymm_KcBc[1]->Draw("histofsame");


   asymm_KcBc[2]->SetLineColor(2);
   asymm_KcBc[2]->SetLineStyle(1);
   asymm_KcBc[2]->SetLineWidth(1);
   asymm_KcBc[2]->SetFillColor(2);
   asymm_KcBc[2]->SetFillStyle(3001);
   asymm_KcBc[2]->Draw("histofsame");

   asymm_KcBc[3]->SetMarkerStyle(1);
   asymm_KcBc[3]->SetMarkerSize(1.5);
   asymm_KcBc[3]->SetMarkerColor(4);
   asymm_KcBc[3]->SetLineColor(4);
   asymm_KcBc[3]->Draw("psame");

  
   TLegend *leg_KcBc = new TLegend(0.22,0.66,0.61,0.85);
   leg_KcBc->AddEntry(asymm_KcBc[0],TString::Format("Reco, eff=%0.3f",float(bbbar_KcBc_reco)/float(bbbar_gen)),"pl");
   leg_KcBc->AddEntry(asymm_KcBc[3],"Reco corrected","pl");
   if(reco_truth) leg_KcBc->AddEntry(asymm_KcBc[1],"Reco, truth charge","lf");
   else leg_KcBc->AddEntry(asymm_KcBc[1],"truth","lf");
   leg_KcBc->AddEntry(asymm_KcBc[2],"Reco, not b#bar{b}","lf");
   leg_KcBc->SetFillColor(0);
   leg_KcBc->SetLineColor(0);
   leg_KcBc->SetShadowColor(0);
   leg_KcBc->Draw();

   if(reco_truth==true) canvas_KcBc->Print(TString::Format("KcBc_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));
   else canvas_KcBc->Print(TString::Format("KcBc_btag1_%0.1f_btag2_%0.1f.eps",btag1,btag2));

   
   
   /* TCanvas *canvas_KcKc_ratio = new TCanvas("canvas_KcKc_ratio","canvas_KcKc_ratio",800,400);
   TH1F * asymm_total_corrected =new TH1F("asymm_total_corrected","asymm_total_corrected",20,-1.0,1.0);
   asymm_total_corrected->Add(asymm_KcKc[3]);
   asymm_total_corrected->Add(asymm_Kc[3]);

   TH1F * asymm_total_truth =new TH1F("asymm_total_truth","asymm_total_truth",20,-1.0,1.0);
   asymm_total_truth->Add(asymm_KcKc[1]);
   asymm_total_truth->Add(asymm_Kc[1]);
   
   TGraphErrors *asymm_KcKc_ratio_corrected=Ratio(asymm_total_corrected,asymm_total_truth);
   //   gPad->SetLogy();
   asymm_KcKc_ratio_corrected->GetXaxis()->SetTitle("<cos_{bjets}(#theta)>");
   asymm_KcKc_ratio_corrected->SetTitle("Kc case, eL");
   asymm_KcKc_ratio_corrected->GetYaxis()->SetTitle("ratio_corrected");
   asymm_KcKc_ratio_corrected->GetYaxis()->SetRangeUser(0.4,1.4);
   asymm_KcKc_ratio_corrected->GetXaxis()->SetRangeUser(-1,1);
   asymm_KcKc_ratio_corrected->GetYaxis()->SetTitleOffset(1.5);
   asymm_KcKc_ratio_corrected->SetMarkerStyle(1);
   asymm_KcKc_ratio_corrected->SetMarkerSize(1.5);
   asymm_KcKc_ratio_corrected->SetMarkerColor(4);
   asymm_KcKc_ratio_corrected->SetLineColor(4);
   asymm_KcKc_ratio_corrected->Draw("alp");

   if(reco_truth==true)canvas_KcKc_ratio->Print(TString::Format("KcKc_Kc_ratio_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));
   else canvas_KcKc_ratio->Print(TString::Format("KcKc_Kc_ratio_btag1_%0.1f_btag2_%0.1f_truth.eps",btag1,btag2));*/

   std::vector<TH1F*> result;
   result.push_back(asymm_BcBc[0]);
   result.push_back(asymm_BcBc[3]);
   result.push_back(asymm_BcBc[2]);
   result.push_back(asymm_BcBc[1]);
   result.push_back(p_b_histo);
   
   result.push_back(asymm_KcKc[0]);
   result.push_back(asymm_KcKc[3]);
   result.push_back(asymm_KcKc[2]);
   result.push_back(asymm_KcKc[1]);
   result.push_back(p_k_histo);

   result.push_back(asymm_BcKc[0]);
   result.push_back(asymm_BcKc[3]);
   result.push_back(asymm_BcKc[2]);
   result.push_back(asymm_BcKc[1]);

   result.push_back(asymm_KcBc[0]);
   result.push_back(asymm_KcBc[3]);
   result.push_back(asymm_KcBc[2]);
   result.push_back(asymm_KcBc[1]);
   

   return result;
}


void observable::y23Analysis()
{

  //  gROOT->Reset();
  /* SetIrlesStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleY(0.92);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleFontSize(0.03);
  gStyle->SetMarkerSize(1.5);*/
       
 
  TH2F * map_theta_max = new TH2F("map_theta_max","map_theta_max",200,0,1,100,-0.1,0.1);
  TH2F * map_phi_max = new TH2F("map_phi_max","map_phi_max",200,0,1,100,-0.1,0.1);

  TH2F * map_theta_max_2 = new TH2F("map_theta_max_2","map_theta_max_2",200,0,0.1,100,-0.1,0.1);
  TH2F * map_phi_max_2 = new TH2F("map_phi_max_2","map_phi_max_2",200,0,0.1,100,-0.1,0.1);

  
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if(PreSelection()==false || abs(mc_quark_pdg[0])!=5) continue; 
      if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

      std::vector<float> theta_bbbar;
      std::vector<float> phi_bbbar;

      for(int i=0; i<2; i++) {
	std::vector<float> p;
	p.push_back(mc_quark_px[i]);
	p.push_back(mc_quark_py[i]);
	p.push_back(mc_quark_pz[i]);
	std::vector< float > d1= getDirection(p);
	theta_bbbar.push_back(getAngles(d1).at(1));
	phi_bbbar.push_back(getAngles(d1).at(0));
      }

      std::vector<float> theta_jj;
      std::vector<float> phi_jj;
      for(int i=0; i<2; i++) {
	std::vector<float> p;
	p.push_back(jet_px[i]);
	p.push_back(jet_py[i]);
	p.push_back(jet_pz[i]);
	std::vector< float > d1= getDirection(p);
	theta_jj.push_back(getAngles(d1).at(1));
	phi_jj.push_back(getAngles(d1).at(0));
      }

      float dist[4];
      int imatch=0;

      for (int ib=0; ib<2; ib++) {
	for (int ij=0; ij<2; ij++) {
	   dist[imatch] = sqrt( pow(theta_bbbar.at(ib) - theta_jj.at(ij),2) +  pow(phi_bbbar.at(ib) - phi_jj.at(ij),2) );
	   imatch++;
	}
      }

      imatch=-1;
      float min_dist=1000000;
      for(int i=0; i<4; i++) {
	if(dist[i]<min_dist) {
	  min_dist = dist[i];
	  imatch = i;
	}
      }

      if(imatch ==0 || imatch==3) {
	float distance1 = sqrt( pow(theta_bbbar.at(0) - theta_jj.at(0),2) +  pow(phi_bbbar.at(0) - phi_jj.at(0),2) );
	float distance2 = sqrt( pow(theta_bbbar.at(1) - theta_jj.at(1),2) +  pow(phi_bbbar.at(1) - phi_jj.at(1),2) );

	if(distance1<distance2) {
	  map_theta_max->Fill(y12,theta_bbbar.at(1) - theta_jj.at(1));
	  map_phi_max->Fill(y12,phi_bbbar.at(1) - phi_jj.at(1));

	  map_theta_max_2->Fill(y23,theta_bbbar.at(1) - theta_jj.at(1));
	  map_phi_max_2->Fill(y23,phi_bbbar.at(1) - phi_jj.at(1));
	} else {
	  map_theta_max->Fill(y12,theta_bbbar.at(0) - theta_jj.at(0));
	  map_phi_max->Fill(y12,phi_bbbar.at(0) - phi_jj.at(0));
	  
	  map_theta_max_2->Fill(y23,theta_bbbar.at(0) - theta_jj.at(0));
	  map_phi_max_2->Fill(y23,phi_bbbar.at(0) - phi_jj.at(0));
	}
	  
      }

      if(imatch ==1 || imatch==2) {
	float distance1 = sqrt( pow(theta_bbbar.at(0) - theta_jj.at(1),2) +  pow(phi_bbbar.at(0) - phi_jj.at(1),2) );
	float distance2 = sqrt( pow(theta_bbbar.at(1) - theta_jj.at(0),2) +  pow(phi_bbbar.at(1) - phi_jj.at(0),2) );

	if(distance1<distance2) {
	  map_theta_max->Fill(y12,theta_bbbar.at(1) - theta_jj.at(0));
	  map_phi_max->Fill(y12,phi_bbbar.at(1) - phi_jj.at(0));

	  map_theta_max_2->Fill(y23,theta_bbbar.at(1) - theta_jj.at(0));
	  map_phi_max_2->Fill(y23,phi_bbbar.at(1) - phi_jj.at(0));
	} else {
	  map_theta_max->Fill(y12,theta_bbbar.at(0) - theta_jj.at(1));
	  map_phi_max->Fill(y12,phi_bbbar.at(0) - phi_jj.at(1));
	  
	  map_theta_max_2->Fill(y23,theta_bbbar.at(0) - theta_jj.at(1));
	  map_phi_max_2->Fill(y23,phi_bbbar.at(0) - phi_jj.at(1));
	}
      }

	
     
   }//end loop


 
   TCanvas *canvas_cos = new TCanvas("canvas_cos","canvas_cos",1200,600);
   canvas_cos->Divide(2,2);
   canvas_cos->cd(1);
   map_theta_max->Draw("colz");
   canvas_cos->cd(2);
   map_phi_max->Draw("colz");
   canvas_cos->cd(3);
   map_theta_max_2->Draw("colz");
   canvas_cos->cd(4);
   map_phi_max_2->Draw("colz");
      
      
}

/*
void observable::PSAnalysis()
{
 
  if (fChain == 0) return;


  TH1F * h_energy[3];
  TH1F * h_cos[3];
  
  for(int i=0; i<3; i++){
    h_energy[i]= new TH1F(TString::Format("energy_%i",i),TString::Format("energy_%i",i),350,0.5,350.5);
    h_cos[i]= new TH1F(TString::Format("cos_%i",i),TString::Format("cos_%i",i),10,-1,1);
  }

  TH1F *h_y12[2];
  TH1F *h_y23[2];
  TH1F *h_yratio[2];
  
  for(int i=0; i<2; i++){
    h_y12[i]= new TH1F(TString::Format("y12_%i",i),TString::Format("y12_%i",i),100,0,1);
    h_y23[i]= new TH1F(TString::Format("y23_%i",i),TString::Format("y23_%i",i),100,0,1);
    h_yratio[i]= new TH1F(TString::Format("yratio_%i",i),TString::Format("yratio_%i",i),10000,0,10000);
  }

  TH2F *h_cos_cos[2];
  for(int i=0; i<2; i++){
    h_cos_cos[i]= new TH2F(TString::Format("cos_cos_%i",i),TString::Format("cos_cos_%i",i),10,-1,1,10,-1,1);
  }

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if(PreSelection()==false || abs(mc_quark_pdg[0])!=5) continue; 

      cout << jentry << " ----------- "<< endl;

      //---------------------------------------------------------------
      //partons
      vector<float> costheta_bbbar;
      for(int ijet=0; ijet<2; ijet++) {
	std::vector<float> p_bbar;
	p_bbar.push_back(mc_quark_px[ijet]);
	p_bbar.push_back(mc_quark_py[ijet]);
	p_bbar.push_back(mc_quark_pz[ijet]);
	
	costheta_bbbar.push_back(GetCostheta(p_bbar));
      }
      costheta_bbbar[0]=  (mc_quark_charge[0] < 0) ? costheta_bbbar[0]: -costheta_bbbar[0];

      cout << "q1 " << mc_quark_E[0] << " q2 " << mc_quark_E[1] << " cos:"<<(costheta_bbbar[0]-costheta_bbbar[1])/2.<< endl;
      h_energy[0]->Fill(mc_quark_E[0]+mc_quark_E[1]);
      h_cos[0]->Fill(abs(costheta_bbbar[0]-costheta_bbbar[1])/2.);
  

      //---------------------------------------------------------------
      //PS
    
      vector<PseudoJet> particles;

      for(int i=0; i<mc_quark_ps_n; i++) {
	if( mc_quark_ps_E[i]>0 ) particles.push_back( PseudoJet(mc_quark_ps_px[i], mc_quark_ps_py[i], mc_quark_ps_pz[i],mc_quark_ps_E[i] ) );
      }

      JetDefinition jet_def(ee_kt_algorithm);
      ClusterSequence cs(particles, jet_def);
      vector<PseudoJet> jets = sorted_by_E(cs.exclusive_jets(2));

     
      vector<float> costheta_bbbar_ps;
      for(int ijet=0; ijet<2; ijet++) {
	std::vector<float> p_bbar;
	p_bbar.push_back(mc_quark_ps_px[ijet]);
	p_bbar.push_back(mc_quark_ps_py[ijet]);
	p_bbar.push_back(mc_quark_ps_pz[ijet]);
	
	costheta_bbbar_ps.push_back(GetCostheta(p_bbar));
      }
      cout << "q1_ps " << mc_quark_ps_E[0] << " q2_ps " << mc_quark_ps_E[1] << " cos:"<<(costheta_bbbar_ps[0]-costheta_bbbar_ps[1])/2.<< endl;

      vector<float> costheta_jets_ps;
      for(int ijet=0; ijet<2; ijet++) {
	std::vector<float> p_bbar;
	p_bbar.push_back(jets[ijet].px());
	p_bbar.push_back(jets[ijet].py());
	p_bbar.push_back(jets[ijet].pz());
	
	costheta_jets_ps.push_back(GetCostheta(p_bbar));
      }

      cout << "jet_ps " << jets[0].E() << " jet_ps " << jets[1].E() << " cos:"<<(costheta_jets_ps[0]-costheta_jets_ps[1])/2.<< endl;

      h_energy[1]->Fill(jets[0].E()+jets[1].E());
      h_cos[1]->Fill(abs(costheta_jets_ps[0]-costheta_jets_ps[1])/2.);
      
       cout<<  "jet_ps   y23:"<< cs.exclusive_ymerge(2)<< " y12:"<< cs.exclusive_ymerge(1)<<endl;
       float y12_=  cs.exclusive_ymerge(1);
       float y23_=  cs.exclusive_ymerge(2);
       h_y12[0]->Fill(y12_);
       h_y23[0]->Fill(y23_);
       h_yratio[0]->Fill(y23_/y12_);
       //---------------------------------------------------------------
       //RECO
       vector<float> costheta_jets;
       for(int ijet=0; ijet<2; ijet++) {
	 std::vector<float> p_bbar;
	 p_bbar.push_back(jet_px[ijet]);
	 p_bbar.push_back(jet_py[ijet]);
	 p_bbar.push_back(jet_pz[ijet]);
	 
	 costheta_jets.push_back(GetCostheta(p_bbar));
       }

       h_energy[2]->Fill(jet_E[0]+jet_E[1]);
       h_cos[2]->Fill(abs(costheta_jets[0]-costheta_jets[1])/2.);
      
       cout<<  "jet_ps   y23:"<< cs.exclusive_ymerge(2)<< " y12:"<< cs.exclusive_ymerge(1)<<endl;
       h_y12[0]->Fill(y12);
       h_y23[0]->Fill(y23);
       h_yratio[0]->Fill(y23/y12);
       
       cout << "jet " << jet_E[0] << " jet " << jet_E[1] << " cos:"<<(costheta_jets[0]-costheta_jets[1])/2.<< endl;
       
       cout << "jet_reco d23:"<< y23<< " y12:"<< y12<<endl;
       cout << "jet reco E:" << jet_E[0] << " E2 " << jet_E[1] << endl;

       h_cos_cos[0]->Fill(abs(costheta_jets[0]-costheta_jets[1])/2.,abs(costheta_bbbar[0]-costheta_bbbar[1])/2.);
       h_cos_cos[1]->Fill(abs(costheta_jets[0]-costheta_jets[1])/2.,abs(costheta_jets_ps[0]-costheta_jets_ps[1])/2.);
       
     
   }//end loop

   TCanvas * canv1 = new TCanvas("canv1","canv1",1200,600);
   canv1->Divide(2,1);
   canv1->cd(1);
   for(int i=0; i<3; i++) {
     h_energy[i]->SetLineColor(i+1);
     h_energy[i]->Draw("same");
   }
   canv1->cd(2);
   for(int i=0; i<3; i++) {
     h_cos[i]->SetLineColor(i+1);
     h_cos[i]->Draw("same");
   }
   TCanvas * canv2 = new TCanvas("canv2","canv2",1200,600);
   canv2->Divide(2,1);
   canv2->cd(1);
   h_cos_cos[0]->Draw("colz");
   
   canv2->cd(2);
   h_cos_cos[1]->Draw("colz");
   

   
   }*/
          
float observable::CalculateP_Bc()
{

  //  gROOT->Reset();
  SetIrlesStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleY(0.92);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleFontSize(0.03);
  gStyle->SetMarkerSize(1.5);
  
     
  int bbbar_BcBc_reco=0;
  int bbbar_BcBc_rejected=0;
  
  if (fChain == 0) return 0;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;
    
   
    if(PreSelection()==false ) continue;
     
    int Bc[2];
    int Kc[2];
    Bc[0]=0; Bc[1]=0;
    Kc[0]=0; Kc[1]=0;
    
    
    for(int ijet=0; ijet<2; ijet++) {
      Bc[ijet]=ChargeBcJet(ijet);
      
    }//end ijet

    //Information to calculate p, for BcBc category
    if(Bc[0]*Bc[1]>0) bbbar_BcBc_rejected++;
    if(Bc[0]*Bc[1]<0) bbbar_BcBc_reco++;
      
  }
  float p=CalculateP(bbbar_BcBc_reco,bbbar_BcBc_rejected);
  std::cout<<"Calculated p = "<<p<<endl;
  return p;
  
  
  }


std::vector<float> observable::CalculateP(TH1F* h_accepted, TH1F *h_rejected)
{


  for(int i=1; i<21; i++) {
    float accepted = h_accepted->GetBinContent(21-i);
    float rejected = h_rejected->GetBinContent(21-i);
    accepted += h_accepted->GetBinContent(i);
    // rejected += h_rejected->GetBinContent(i);
    float a=1;
    float b=-1;
    float c= rejected/ (2* (accepted+rejected));
    float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
    float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
  }

  std::vector<float> result_error;

  for(int i=1; i<11; i++) {
    std::vector<float> result_j;
    for(int i1=-1; i1<2; i1+=2) {
      for(int i2=-1; i2<2; i2+=2) {
	//	for(int i3=-1; i3<2; i3+=2) {
	  float accepted = h_accepted->GetBinContent(21-i)+i1*sqrt(h_accepted->GetBinContent(21-i));
	  float rejected = h_rejected->GetBinContent(21-i)+i2*sqrt(h_rejected->GetBinContent(21-i));
	  accepted += h_accepted->GetBinContent(i)+i1*sqrt(h_accepted->GetBinContent(i));
	  
	  float a=1;
	  float b=-1;
	  float c= rejected/ (2* (accepted+rejected));
	  float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
	  float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
	  if(p>0 || p2>0 ) result_j.push_back(max(p,p2));
	  //	}
      }
    }
    float average=0;
    for(unsigned j=0; j<result_j.size(); j++) average+=result_j.at(j)/result_j.size();
    if(average!=0) {
      float std_dev=0;
      for(unsigned j=0; j<result_j.size(); j++) std_dev=pow(result_j.at(j)-average,2);
      std_dev=sqrt(std_dev/(result_j.size()-1));
      result_error.push_back(std_dev);
    } else result_error.push_back(0);
  }
    
  std::vector<float> result;
  for(int i=1; i<11; i++) {
    float accepted = h_accepted->GetBinContent(21-i);
    float rejected = h_rejected->GetBinContent(21-i);
    accepted += h_accepted->GetBinContent(i);
    float a=1;
    float b=-1;
    float c= rejected/ (2* (accepted+rejected));
    float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
    float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
    if(p>0 || p2>0 ) result.push_back(max(p,p2));
    else result.push_back(-1);
  }

  

  float average=0;
  float n=0;
  for(unsigned i=0; i<result.size(); i++) {
    if(result.at(i)>0) { average+=result.at(i); n++;}
  }
  average/=n;
  for(unsigned i=0; i<result_error.size(); i++) {
    if(result.at(i)<0) result.at(i)=average;
    result.push_back(result_error.at(i));
  }

  for(unsigned i=0; i<10; i++) {
    cout<<"p =" <<result.at(i)<<" +-"<<result.at(10+i)<<endl;
  }
  return result;
  
}


float observable::CalculateP(int accepted, int rejected)
{

  float n= float(accepted)+float(rejected);
  float p = 0.5 + 0.5*sqrt(1-2*float(rejected)/n);
  
  return p;
  
}


TGraphErrors* observable::Ratio(TH1F* histo, TH1F* histo_ref) {

  double x[20], y[20], ey[20];
  
  for(int i=0; i<20; i++) {
    x[i]=histo_ref->GetBinCenter(i+1);
    y[i]= histo->GetBinContent(i+1)/histo_ref->GetBinContent(i+1);
    ey[i]=sqrt( pow(histo->GetBinError(i+1)/histo_ref->GetBinContent(i+1),2) + pow(histo->GetBinContent(i+1)*histo_ref->GetBinError(i+1)/(2*histo_ref->GetBinContent(i+1)*histo_ref->GetBinContent(i+1)),2));
  }

  TGraphErrors * result = new TGraphErrors(20,x,y,0,ey);
  return result;
}

TH1F* observable::CorrectHistoDoubleTag(TH1F* histo, float p) {
  
  TH1F * corrected = new TH1F("corrected","corrected",20,-1,1);
  corrected->Sumw2();
  float q=1-p;

  for(int i=1; i<11; i++) {
    float nm_reco=histo->GetBinContent(i);
    float np_reco=histo->GetBinContent(21-i);
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
    
    corrected->SetBinContent(i,(np_reco*q*q-nm_reco*p*p)*weight);
    corrected->SetBinContent(21-i,-(np_reco*p*p-nm_reco*q*q)*weight);

    corrected->SetBinError(i,sqrt(np_reco*pow(q*q,2)+nm_reco*pow(p*p,2))*weight);
    corrected->SetBinError(21-i,sqrt(np_reco*pow(p*p,2)+nm_reco*pow(q*q,2))*weight);
  }
  std::cout<<" end correction histogram " <<endl;
  return corrected;


}
TH1F* observable::CorrectHistoDoubleTag(TH1F* histo, std::vector<float> p_vect) {
  
  TH1F * corrected_up = new TH1F("corrected_up","corrected_up",20,-1,1);
  corrected_up->Sumw2(); 
  for(int i=1; i<11; i++) {
    float nm_reco=histo->GetBinContent(i);
    float np_reco=histo->GetBinContent(21-i);
    
    float p=p_vect.at(i-1)+p_vect.at(20-(11-i));
    float q=1-p;
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
    corrected_up->SetBinContent(i,(np_reco*q*q-nm_reco*p*p)*weight);
    corrected_up->SetBinContent(21-i,-(np_reco*p*p-nm_reco*q*q)*weight);
  }
  TH1F * corrected_down = new TH1F("corrected_down","corrected_down",20,-1,1);
  corrected_down->Sumw2(); 
  for(int i=1; i<11; i++) {
    float nm_reco=histo->GetBinContent(i);
    float np_reco=histo->GetBinContent(21-i);
    
    float p=p_vect.at(i-1)-p_vect.at(20-(11-i));
    float q=1-p;
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
    corrected_down->SetBinContent(i,(np_reco*q*q-nm_reco*p*p)*weight);
    corrected_down->SetBinContent(21-i,-(np_reco*p*p-nm_reco*q*q)*weight);
  }
  

  TH1F * corrected = new TH1F("corrected","corrected",20,-1,1);
  corrected->Sumw2();
  for(int i=1; i<11; i++) {
    float p=p_vect.at(i-1);
    float q=1-p;
    float nm_reco=histo->GetBinContent(i);
    float np_reco=histo->GetBinContent(21-i);
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
    
    corrected->SetBinContent(i,(np_reco*q*q-nm_reco*p*p)*weight);
    corrected->SetBinContent(21-i,-(np_reco*p*p-nm_reco*q*q)*weight);

    float error=abs(corrected_up->GetBinContent(i) - corrected_down->GetBinContent(i))/2.;
    corrected->SetBinError(i,sqrt(pow(error,2) + (np_reco*pow(q*q,2)+nm_reco*pow(p*p,2))*weight*weight ));
    error=abs(corrected_up->GetBinContent(21-i) - corrected_down->GetBinContent(21-i))/2.;
    corrected->SetBinError(21-i,sqrt(pow(error,2)+(np_reco*pow(p*p,2)+nm_reco*pow(q*q,2))*weight*weight));

  }
  std::cout<<" end correction histogram " <<endl;
  return corrected;


}

TH1F* observable::CorrectHistoDoubleTag(TH1F* histo, std::vector<float> p_vect, std::vector<float> p_vect2) {
  
  // TH1F * corrected_up = new TH1F("corrected_up","corrected_up",20,-1,1);
  // corrected_up->Sumw2(); 
  // for(int i=1; i<11; i++) {
  //   float nm_reco=histo->GetBinContent(i);
  //   float np_reco=histo->GetBinContent(21-i);
    
  //   float p=p_vect.at(i-1)+p_vect.at(20-(11-i));
  //   float q=1-p;
  //   float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
  //   corrected_up->SetBinContent(i,(np_reco*q*q-nm_reco*p*p)*weight);
  //   corrected_up->SetBinContent(21-i,-(np_reco*p*p-nm_reco*q*q)*weight);
  // }
  // TH1F * corrected_down = new TH1F("corrected_down","corrected_down",20,-1,1);
  // corrected_down->Sumw2(); 
  // for(int i=1; i<11; i++) {
  //   float nm_reco=histo->GetBinContent(i);
  //   float np_reco=histo->GetBinContent(21-i);
    
  //   float p=p_vect.at(i-1)-p_vect.at(20-(11-i));
  //   float q=1-p;
  //   float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
  //   corrected_down->SetBinContent(i,(np_reco*q*q-nm_reco*p*p)*weight);
  //   corrected_down->SetBinContent(21-i,-(np_reco*p*p-nm_reco*q*q)*weight);
  // }
  

  TH1F * corrected = new TH1F("corrected","corrected",20,-1,1);
  corrected->Sumw2();
  for(int i=1; i<11; i++) {
    float p=p_vect.at(i-1);
    float q=1-p;
    float p2=p_vect2.at(i-1);
    float q2=1-p2;
    
    float nm_reco=histo->GetBinContent(i);
    float np_reco=histo->GetBinContent(21-i);
    float weight = (p*p2+q*q2)/(q*q2*q*q2-p*p2*p*p2);
    
    corrected->SetBinContent(i,(np_reco*q*q2-nm_reco*p*p2)*weight);
    corrected->SetBinContent(21-i,-(np_reco*p*p2-nm_reco*q*q2)*weight);

    float error=0;//abs(corrected_up->GetBinContent(i) - corrected_down->GetBinContent(i))/2.;
    corrected->SetBinError(i,sqrt(pow(error,2) + (np_reco*pow(q*q2,2)+nm_reco*pow(p*p2,2))*weight*weight ));
    error=0;//abs(corrected_up->GetBinContent(21-i) - corrected_down->GetBinContent(21-i))/2.;
    corrected->SetBinError(21-i,sqrt(pow(error,2)+(np_reco*pow(p*p2,2)+nm_reco*pow(q*q2,2))*weight*weight));

  }
  std::cout<<" end correction histogram " <<endl;
  return corrected;


}

TH1F* observable::CorrectHistoSingleTag(TH1F* histo, std::vector<float> p_vect) {

    TH1F * corrected_up = new TH1F("corrected_up","corrected_up",20,-1,1);
  corrected_up->Sumw2(); 
  for(int i=1; i<11; i++) {
    float nm_reco=histo->GetBinContent(i);
    float np_reco=histo->GetBinContent(21-i);
    
    float p=p_vect.at(i-1)+p_vect.at(20-(11-i));
    float q=1-p;
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
    corrected_up->SetBinContent(i,(np_reco*q*q-nm_reco*p*p)*weight);
    corrected_up->SetBinContent(21-i,-(np_reco*p*p-nm_reco*q*q)*weight);
  }
  TH1F * corrected_down = new TH1F("corrected_down","corrected_down",20,-1,1);
  corrected_down->Sumw2(); 
  for(int i=1; i<11; i++) {
    float nm_reco=histo->GetBinContent(i);
    float np_reco=histo->GetBinContent(21-i);
    
    float p=p_vect.at(i-1)-p_vect.at(20-(11-i));
    float q=1-p;
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
    corrected_down->SetBinContent(i,(np_reco*q*q-nm_reco*p*p)*weight);
    corrected_down->SetBinContent(21-i,-(np_reco*p*p-nm_reco*q*q)*weight);
  }

   

  TH1F * corrected = new TH1F("corrected","corrected",20,-1,1);
  corrected->Sumw2();
  for(int i=1; i<11; i++) {
    float p=p_vect.at(i-1);
    float q=1-p;
    float nm_reco=histo->GetBinContent(i);
    float np_reco=histo->GetBinContent(21-i);
    float weight = (p+q)/(q*q-p*p);

    corrected->SetBinContent(i,(np_reco*q-nm_reco*p)*weight);
    corrected->SetBinContent(21-i,-(np_reco*p-nm_reco*q)*weight);

    float error=abs(corrected_up->GetBinContent(i) - corrected_down->GetBinContent(i))/2.;
    corrected->SetBinError(i,sqrt(error*error + (np_reco*pow(q,2)+nm_reco*pow(p,2))*weight*weight));
    error=abs(corrected_up->GetBinContent(21-i) - corrected_down->GetBinContent(21-i))/2.;
    corrected->SetBinError(21-i,sqrt(error*error + (np_reco*pow(q,2)+nm_reco*pow(p,2))*weight*weight));

  }
  std::cout<<" end correction histogram " <<endl;
  return corrected;

}


TH1F* observable::CorrectHistoSingleTag(TH1F* histo, float p) {
  
  TH1F * corrected = new TH1F("corrected","corrected",20,-1,1);
  corrected->Sumw2();
  float q=1-p;

  for(int i=0; i<11; i++) {
    float nm_reco=histo->GetBinContent(i);
    float np_reco=histo->GetBinContent(21-i);
    float weight = (p+q)/(q*q-p*p);
    
    corrected->SetBinContent(i,(np_reco*q-nm_reco*p)*weight);
    corrected->SetBinContent(21-i,-(np_reco*p-nm_reco*q)*weight);

    corrected->SetBinError(i,sqrt(np_reco*pow(q,2)+nm_reco*pow(p,2))*weight);
    corrected->SetBinError(21-i,sqrt(np_reco*pow(p,2)+nm_reco*pow(q,2))*weight);
  }
  std::cout<<" end correction histogram " <<endl;
  return corrected;


}


TH1F* observable::CorrectHistoSingleTag(TH1F* histo, float p, float p2) {
  
  TH1F * corrected = new TH1F("corrected","corrected",20,-1,1);
  corrected->Sumw2();
  float q=1-p;
  float q2=1-p2;

  for(int i=1; i<11; i++) {
    float nm_reco=histo->GetBinContent(i);
    float np_reco=histo->GetBinContent(21-i);
    float weight = (p*p2+q*q2)/(q*q*q2*q2-p*p*p2*p2);
    corrected->SetBinContent(i,(np_reco*q*q2-nm_reco*p*p2)*weight);
    corrected->SetBinContent(21-i,-(np_reco*p*p2-nm_reco*q*q2)*weight);

    corrected->SetBinError(i,sqrt(np_reco*pow(q*q2,2)+nm_reco*pow(p*p2,2))*weight);
    corrected->SetBinError(21-i,sqrt(np_reco*pow(p*p2,2)+nm_reco*pow(q*q2,2))*weight);
  }
  std::cout<<" end correction histogram " <<endl;
  return corrected;


}

/*TH1F* observable::CorrectHistoDoubleTag(TH1F* histo, float p) {
  
  TH1F * corrected = new TH1F("corrected","corrected",50,-1,1);
  corrected->Sumw2();
  float q=1-p;

  for(int i=0; i<26; i++) {
    float nm_reco=histo->GetBinContent(i);
  
    float np_reco=histo->GetBinContent(51-i);
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
    corrected->SetBinContent(i,(np_reco*q*q-nm_reco*p*p)*weight);
    corrected->SetBinContent(51-i,-(np_reco*p*p-nm_reco*q*q)*weight);

    corrected->SetBinError(i,sqrt(np_reco*pow(q*q,2)+nm_reco*pow(p*p,2))*weight);
    corrected->SetBinError(51-i,sqrt(np_reco*pow(p*p,2)+nm_reco*pow(q*q,2))*weight);
  }
  std::cout<<" end correction histogram " <<endl;
  return corrected;


}

TH1F* observable::CorrectHistoSingleTag(TH1F* histo, float p) {
  
  TH1F * corrected = new TH1F("corrected","corrected",50,-1,1);
  corrected->Sumw2();
  float q=1-p;

  for(int i=0; i<26; i++) {
    float nm_reco=histo->GetBinContent(i);
  
    float np_reco=histo->GetBinContent(51-i);
    float weight = (p+q)/(q*q-p*p);
    corrected->SetBinContent(i,(np_reco*q-nm_reco*p)*weight);
    corrected->SetBinContent(51-i,-(np_reco*p-nm_reco*q)*weight);

    corrected->SetBinError(i,sqrt(np_reco*pow(q,2)+nm_reco*pow(p,2))*weight);
    corrected->SetBinError(51-i,sqrt(np_reco*pow(p,2)+nm_reco*pow(q,2))*weight);
  }
  std::cout<<" end correction histogram " <<endl;
  return corrected;


  }*/


 bool observable::PreSelection() {

   if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;
   double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
   double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));
   
   double b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
   double b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
   double bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));
   
   
   if( bbmass < 180 || (b1mass+b2mass) >120 || maxenergy_photon_E>40 || jet_btag[0]<btag1 || jet_btag[1]<btag2 || jet0_p<40 || jet1_p<40) return false;

   return true;
 }

float observable::ChargeBcJet(int ijet) {
  double charge=0;

  if(jet_btag[ijet] <0.8) return charge;
  
  for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
    for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
      charge+=jet_track_charge[ijet][ivtx][itrack];
    }
  }

  return charge;
}

float observable::ChargeKcJet(int ijet) {
    double charge=0;
    
    for(int ivtx=0; ivtx<jet_nvtx[ijet]; ivtx++) {
      for(int itrack=0; itrack<jet_vtx_ntrack[ijet][ivtx]; itrack++) {
	if(jet_track_iskaon[ijet][ivtx][itrack]==1) charge+=jet_track_kaoncharge[ijet][ivtx][itrack];
      }
    }
    
    return charge;
}
