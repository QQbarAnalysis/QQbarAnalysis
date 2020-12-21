//######################
//# 2020.9.28~         #
//# Seidai Tairafune   #
//######################

#include <TFile.h>
#include "TH1.h"
#include "TF1.h"
//#include "../style/Style.C"
//#include "../style/Labels.C"

void Correction() {
  TFile* f = new TFile("output_files_neut065_K50_eL/output_cambridge_merged_restorer_v02-01-02.root");
  TFile* f2 = new TFile("output_files_neut065_K50_eL/output_cambridge_merged_restorer_contami_v02-01-02.root");

  TGraphErrors* R3bl_PS[4];
    
  TGraphErrors* R3bl_Hadron[4];
  TGraphErrors* R3b_Hadron[4];
  TGraphErrors* R3l_Hadron[4];
    
  TGraphErrors* R3bl_Reco[4];
  TGraphErrors* R3b_Reco[4];
  TGraphErrors* R3l_Reco[4];

  TGraphErrors* R3bl_Reco_con[4];
  TGraphErrors* R3b_Reco_con[4];
  TGraphErrors* R3l_Reco_con[4];

  TGraphErrors* R3bl_Reco_con2[4];
  TGraphErrors* R3b_Reco_con2[4];
  TGraphErrors* R3l_Reco_con2[4];

  double r3bl_PS[4][50];

  double r3bl_Had[4][50];
  double r3b_Had[4][50];
  double r3l_Had[4][50];

  double r3bl_Rec[4][50];
  double r3b_Rec[4][50];
  double r3l_Rec[4][50];

  double r3bl_Rec_con[4][50];
  double r3b_Rec_con[4][50];
  double r3l_Rec_con[4][50];

  double r3bl_Rec_con2[4][50];
  double r3b_Rec_con2[4][50];
  double r3l_Rec_con2[4][50];

  double er3bl_PS[4][50];

  double er3bl_Had[4][50];
  double er3b_Had[4][50];
  double er3l_Had[4][50];

  double er3bl_Rec[4][50];
  double er3b_Rec[4][50];
  double er3l_Rec[4][50];

  double er3bl_Rec_con[4][50];
  double er3b_Rec_con[4][50];
  double er3l_Rec_con[4][50];

  double er3bl_Rec_con2[4][50];
  double er3b_Rec_con2[4][50];
  double er3l_Rec_con2[4][50];

  for(int i=0; i<4; i++) {
    R3bl_PS[i] = (TGraphErrors*)f->Get(TString::Format("R3bl_PS_STEP%i",i));

    R3bl_Hadron[i] = (TGraphErrors*)f->Get(TString::Format("R3bl_Hadron_STEP%i",i));
    R3b_Hadron[i] = (TGraphErrors*)f->Get(TString::Format("R3b_Hadron_STEP%i",i));
    R3l_Hadron[i] = (TGraphErrors*)f->Get(TString::Format("R3l_Hadron_STEP%i",i));

    R3bl_Reco[i] = (TGraphErrors*)f->Get(TString::Format("R3bl_Reco_STEP%i",i));
    R3b_Reco[i] = (TGraphErrors*)f->Get(TString::Format("R3b_Reco_STEP%i",i));
    R3l_Reco[i] = (TGraphErrors*)f->Get(TString::Format("R3l_Reco_STEP%i",i));

    R3bl_Reco_con[i] = (TGraphErrors*)f2->Get(TString::Format("R3bl_Reco2_STEP%i",i));
    R3b_Reco_con[i] = (TGraphErrors*)f2->Get(TString::Format("R3b_Reco2_STEP%i",i));
    R3l_Reco_con[i] = (TGraphErrors*)f2->Get(TString::Format("R3l_Reco2_STEP%i",i));

    R3bl_Reco_con2[i] = (TGraphErrors*)f2->Get(TString::Format("R3bl_Reco_STEP%i",i));
    R3b_Reco_con2[i] = (TGraphErrors*)f2->Get(TString::Format("R3b_Reco_STEP%i",i));
    R3l_Reco_con2[i] = (TGraphErrors*)f2->Get(TString::Format("R3l_Reco_STEP%i",i));


    Double_t* obs_list_PS = R3bl_PS[i]->GetY();

    Double_t* obs_list_Had = R3bl_Hadron[i]->GetY();
    Double_t* obs_listb_Had = R3b_Hadron[i]->GetY();
    Double_t* obs_listl_Had = R3l_Hadron[i]->GetY();

    Double_t* obs_list_Rec = R3bl_Reco[i]->GetY();
    Double_t* obs_listb_Rec = R3b_Reco[i]->GetY();
    Double_t* obs_listl_Rec = R3l_Reco[i]->GetY();

    Double_t* obs_list_Rec_con = R3bl_Reco_con[i]->GetY();
    Double_t* obs_listb_Rec_con = R3b_Reco_con[i]->GetY();
    Double_t* obs_listl_Rec_con = R3l_Reco_con[i]->GetY();

    Double_t* obs_list_Rec_con2 = R3bl_Reco_con2[i]->GetY();
    Double_t* obs_listb_Rec_con2 = R3b_Reco_con2[i]->GetY();
    Double_t* obs_listl_Rec_con2 = R3l_Reco_con2[i]->GetY();


    Double_t* obs_elist_PS = R3bl_PS[i]->GetEY();

    Double_t* obs_elist_Had = R3bl_Hadron[i]->GetEY();
    Double_t* obs_elistb_Had = R3b_Hadron[i]->GetEY();
    Double_t* obs_elistl_Had = R3l_Hadron[i]->GetEY();

    Double_t* obs_elist_Rec = R3bl_Reco[i]->GetEY();
    Double_t* obs_elistb_Rec = R3b_Reco[i]->GetEY();
    Double_t* obs_elistl_Rec = R3l_Reco[i]->GetEY();

    Double_t* obs_elist_Rec_con = R3bl_Reco_con[i]->GetEY();
    Double_t* obs_elistb_Rec_con = R3b_Reco_con[i]->GetEY();
    Double_t* obs_elistl_Rec_con = R3l_Reco_con[i]->GetEY();

    Double_t* obs_elist_Rec_con2 = R3bl_Reco_con2[i]->GetEY();
    Double_t* obs_elistb_Rec_con2 = R3b_Reco_con2[i]->GetEY();
    Double_t* obs_elistl_Rec_con2 = R3l_Reco_con2[i]->GetEY();


    //std::cout << "STEP :" << i << std::endl;
    for(int j=0; j<50; j++) {
      r3bl_PS[i][j] = obs_list_PS[j];

      r3bl_Had[i][j] = obs_list_Had[j];
      r3b_Had[i][j] = obs_listb_Had[j];
      r3l_Had[i][j] = obs_listl_Had[j];

      r3bl_Rec[i][j] = obs_list_Rec[j];
      r3b_Rec[i][j] = obs_listb_Rec[j];
      r3l_Rec[i][j] = obs_listl_Rec[j];

      r3bl_Rec_con[i][j] = obs_list_Rec_con[j];
      r3b_Rec_con[i][j] = obs_listb_Rec_con[j];
      r3l_Rec_con[i][j] = obs_listl_Rec_con[j];

      r3bl_Rec_con2[i][j] = obs_list_Rec_con2[j];
      r3b_Rec_con2[i][j] = obs_listb_Rec_con2[j];
      r3l_Rec_con2[i][j] = obs_listl_Rec_con2[j];


      er3bl_PS[i][j] = obs_elist_PS[j];

      er3bl_Had[i][j] = obs_elist_Had[j];
      er3b_Had[i][j] = obs_elistb_Had[j];
      er3l_Had[i][j] = obs_elistl_Had[j];

      er3bl_Rec[i][j] = obs_elist_Rec[j];
      er3b_Rec[i][j] = obs_elistb_Rec[j];
      er3l_Rec[i][j] = obs_elistl_Rec[j];

      er3bl_Rec_con[i][j] = obs_elist_Rec_con[j];
      er3b_Rec_con[i][j] = obs_elistb_Rec_con[j];
      er3l_Rec_con[i][j] = obs_elistl_Rec_con[j];

      er3bl_Rec_con2[i][j] = obs_elist_Rec_con2[j];
      er3b_Rec_con2[i][j] = obs_elistb_Rec_con2[j];
      er3l_Rec_con2[i][j] = obs_elistl_Rec_con2[j];
    }
  }


  double C_had[50];
  double C_det[50];
  double C_det_con[50];
  double C_det_bl[50];
  double C_det_con_bl[50];
  double C_det_con2[50];
  double C_det_con2_bl[50];
  
  double C_det_b[50];
  double C_det_l[50];

  double C_det_con_b[50];
  double C_det_con_l[50];
  double C_det_con2_b[50];
  double C_det_con2_l[50];
  
  double eC_had[50];
  double eC_det[50];
  double eC_det_con[50];
  double eC_det_bl[50];
  double eC_det_con_bl[50];
  double eC_det_con2[50];
  double eC_det_con2_bl[50];
  
  double eC_det_b[50];
  double eC_det_l[50];

  double eC_det_con_b[50];
  double eC_det_con_l[50];
  double eC_det_con2_b[50];
  double eC_det_con2_l[50];
  
  double ratio[50];
  double ratio_bl[50];
  double eratio[50];
  double eratio_bl[50];

  double ycuts[50];
  double eycuts[50];

  for(int jycuts=0; jycuts<50; jycuts++) {
    //C_had = (R3bl @PS STEP0)/(R3bl @Hadron STEP0)
    C_had[jycuts] = (r3bl_PS[0][jycuts]/r3bl_Had[0][jycuts]);
    eC_had[jycuts] = (r3bl_PS[0][jycuts]/r3bl_Had[0][jycuts])*sqrt(pow((er3bl_PS[0][jycuts]/r3bl_PS[0][jycuts]),2)+pow((er3bl_Had[0][jycuts]/r3bl_Had[0][jycuts]),2));
		

    //C_det_b = (R3b @Hadron STEP0)/(R3b @Reco STEP2&3+costheta<0.8 No MC cheating)
    C_det_b[jycuts] = (r3b_Had[0][jycuts]/r3b_Rec[3][jycuts]);
    eC_det_b[jycuts] = (r3b_Had[0][jycuts]/r3b_Rec[3][jycuts])*sqrt(pow((er3b_Had[0][jycuts]/r3b_Had[0][jycuts]),2)+pow((er3b_Rec[0][jycuts]/r3b_Rec[0][jycuts]),2));

    //C_det_l = (R3l @Hadron STEP0)/(R3l @Reco STEP2&3+costheta<0.8 No MC cheating)
    C_det_l[jycuts] = (r3l_Had[0][jycuts]/r3l_Rec[3][jycuts]);
    eC_det_l[jycuts] = (r3l_Had[0][jycuts]/r3l_Rec[3][jycuts])*sqrt(pow((er3l_Had[0][jycuts]/r3l_Had[0][jycuts]),2)+pow((er3l_Rec[0][jycuts]/r3l_Rec[0][jycuts]),2));

    //C_det = (R3bl @Hadron STEP0)/(R3bl @Reco STEP2&3+costheta<0.8 No MC cheating)
    C_det[jycuts] = (r3bl_Had[0][jycuts]/r3bl_Rec[3][jycuts]);
    eC_det[jycuts] = (r3bl_Had[0][jycuts]/r3bl_Rec[3][jycuts])*sqrt(pow((er3bl_Had[0][jycuts]/r3bl_Had[0][jycuts]),2)+pow((er3bl_Rec[3][jycuts]/r3bl_Rec[3][jycuts]),2));
      
    //C_det_bl = (C_det_b)/(C_det_l) (Equivalent with C_det)
    C_det_bl[jycuts] = (C_det_b[jycuts]/C_det_l[jycuts]);
    eC_det_bl[jycuts] = (C_det_b[jycuts]/C_det_l[jycuts])*sqrt(pow((eC_det_b[jycuts]/C_det_b[jycuts]),2)+pow((eC_det_l[jycuts]/C_det_l[jycuts]),2));

    /*
    //C_det_b = (R3b @Hadron STEP0)/(R3b @Reco STEP2&3+costheta<0.8)
    C_det_b[jycuts] = (r3b_Had[0][jycuts]/r3b_Rec[3][jycuts]);
    eC_det_b[jycuts] = (r3b_Had[0][jycuts]/r3b_Rec[3][jycuts])*sqrt(pow((er3b_Had[0][jycuts]/r3b_Had[0][jycuts]),2)+pow((er3b_Rec[3][jycuts]/r3b_Rec[3][jycuts]),2));

    //C_det_l = (R3l @Hadron STEP0)/(R3l @Reco STEP2&3+costheta<0.8)
    C_det_l[jycuts] = (r3l_Had[0][jycuts]/r3l_Rec[3][jycuts]);
    eC_det_l[jycuts] = (r3l_Had[0][jycuts]/r3l_Rec[3][jycuts])*sqrt(pow((er3l_Had[0][jycuts]/r3l_Had[0][jycuts]),2)+pow((er3l_Rec[3][jycuts]/r3l_Rec[3][jycuts]),2));
    //std::cout << C_det_b[jycuts] << "+-" << eC_det_b[jycuts] << ", " << C_det_l[jycuts] << "+-" << eC_det_l[jycuts] << std::endl;

    //C_det = (R3bl @Hadron STEP0)/(R3bl @Reco STEP2&3+costheta<0.8)
    C_det[jycuts] = (r3bl_Had[0][jycuts]/r3bl_Rec[3][jycuts]);
    eC_det[jycuts] = (r3bl_Had[0][jycuts]/r3bl_Rec[3][jycuts])*sqrt(pow((er3bl_Had[0][jycuts]/r3bl_Had[0][jycuts]),2)+pow((er3bl_Rec[3][jycuts]/r3bl_Rec[3][jycuts]),2));
		
    //C_det_bl = (C_det_b)/(C_det_l) (Equivalent with C_det)
    C_det_bl[jycuts] = (C_det_b[jycuts]/C_det_l[jycuts]);
    eC_det_bl[jycuts] = (C_det_b[jycuts]/C_det_l[jycuts])*sqrt(pow((eC_det_b[jycuts]/C_det_b[jycuts]),2)+pow((eC_det_l[jycuts]/C_det_l[jycuts]),2));
    */

    //C_det_con_b = (R3b @Hadron STEP0)/(R3b @Reco STEP2&3+costheta<0.8 No MC cheating)
    C_det_con_b[jycuts] = (r3b_Had[0][jycuts]/r3b_Rec_con[3][jycuts]);
    eC_det_con_b[jycuts] = (r3b_Had[0][jycuts]/r3b_Rec_con[3][jycuts])*sqrt(pow((er3b_Had[0][jycuts]/r3b_Had[0][jycuts]),2)+pow((er3b_Rec_con[0][jycuts]/r3b_Rec_con[0][jycuts]),2));

    //C_det_con_l = (R3l @Hadron STEP0)/(R3l @Reco STEP2&3+costheta<0.8 No MC cheating)
    C_det_con_l[jycuts] = (r3l_Had[0][jycuts]/r3l_Rec_con[3][jycuts]);
    eC_det_con_l[jycuts] = (r3l_Had[0][jycuts]/r3l_Rec_con[3][jycuts])*sqrt(pow((er3l_Had[0][jycuts]/r3l_Had[0][jycuts]),2)+pow((er3l_Rec_con[0][jycuts]/r3l_Rec_con[0][jycuts]),2));

    //C_det_con = (R3bl @Hadron STEP0)/(R3bl @Reco STEP2&3+costheta<0.8 No MC cheating)
    C_det_con[jycuts] = (r3bl_Had[0][jycuts]/r3bl_Rec_con[3][jycuts]);
    eC_det_con[jycuts] = (r3bl_Had[0][jycuts]/r3bl_Rec_con[3][jycuts])*sqrt(pow((er3bl_Had[0][jycuts]/r3bl_Had[0][jycuts]),2)+pow((er3bl_Rec_con[3][jycuts]/r3bl_Rec_con[3][jycuts]),2));
      
    //C_det_con_bl = (C_det_con_b)/(C_det_con_l) (Equivalent with C_det_con)
    C_det_con_bl[jycuts] = (C_det_con_b[jycuts]/C_det_con_l[jycuts]);
    eC_det_con_bl[jycuts] = (C_det_con_b[jycuts]/C_det_con_l[jycuts])*sqrt(pow((eC_det_con_b[jycuts]/C_det_con_b[jycuts]),2)+pow((eC_det_con_l[jycuts]/C_det_con_l[jycuts]),2));


    //C_det_con2_b = (R3b @Hadron STEP0)/(R3b @Reco STEP2&3+costheta<0.8 No MC cheating)
    C_det_con2_b[jycuts] = (r3b_Had[0][jycuts]/r3b_Rec_con2[3][jycuts]);
    eC_det_con2_b[jycuts] = (r3b_Had[0][jycuts]/r3b_Rec_con2[3][jycuts])*sqrt(pow((er3b_Had[0][jycuts]/r3b_Had[0][jycuts]),2)+pow((er3b_Rec_con2[0][jycuts]/r3b_Rec_con2[0][jycuts]),2));

    //C_det_con2_l = (R3l @Hadron STEP0)/(R3l @Reco STEP2&3+costheta<0.8 No MC cheating)
    C_det_con2_l[jycuts] = (r3l_Had[0][jycuts]/r3l_Rec_con2[3][jycuts]);
    eC_det_con2_l[jycuts] = (r3l_Had[0][jycuts]/r3l_Rec_con2[3][jycuts])*sqrt(pow((er3l_Had[0][jycuts]/r3l_Had[0][jycuts]),2)+pow((er3l_Rec_con2[0][jycuts]/r3l_Rec_con2[0][jycuts]),2));

    //C_det_con2 = (R3bl @Hadron STEP0)/(R3bl @Reco STEP2&3+costheta<0.8 No MC cheating)
    C_det_con2[jycuts] = (r3bl_Had[0][jycuts]/r3bl_Rec_con2[3][jycuts]);
    eC_det_con2[jycuts] = (r3bl_Had[0][jycuts]/r3bl_Rec_con2[3][jycuts])*sqrt(pow((er3bl_Had[0][jycuts]/r3bl_Had[0][jycuts]),2)+pow((er3bl_Rec_con2[3][jycuts]/r3bl_Rec_con2[3][jycuts]),2));
      
    //C_det_con2_bl = (C_det_con2_b)/(C_det_con2_l) (Equivalent with C_det_con2)
    C_det_con2_bl[jycuts] = (C_det_con2_b[jycuts]/C_det_con2_l[jycuts]);
    eC_det_con2_bl[jycuts] = (C_det_con2_b[jycuts]/C_det_con2_l[jycuts])*sqrt(pow((eC_det_con2_b[jycuts]/C_det_con2_b[jycuts]),2)+pow((eC_det_con2_l[jycuts]/C_det_con2_l[jycuts]),2));


    ratio[jycuts] = (C_det[jycuts]/C_det_con[jycuts]);
    eratio[jycuts] = (C_det[jycuts]/C_det_con[jycuts])*sqrt(pow(eC_det[jycuts]/C_det[jycuts],2)+pow(eC_det_con[jycuts]/C_det_con[jycuts],2));
    //std::cout << "ratio : " << ratio[jycuts] << " +- " << eratio[jycuts] << std::endl;
    ratio_bl[jycuts] = (C_det_bl[jycuts]/C_det_con_bl[jycuts]);
    eratio_bl[jycuts] = (C_det_bl[jycuts]/C_det_con_bl[jycuts])*sqrt(pow((eC_det_bl[jycuts]/C_det_bl[jycuts]),2)+pow((eC_det_con_bl[jycuts]/C_det_con_bl[jycuts]),2));

    ycuts[jycuts] = 0.001*jycuts;
    eycuts[jycuts] = 0.;
  }


  //y=1 line
  double base[60];
  double ebase[60];
  double ybase[60];
  double eybase[60];
  for (int j=0; j<60; j++) {
    base[j] = 1.;
    ebase[j] = 0.;
    ybase[j] = 0.001*j;
    eybase[j] = 0.;
  }


  //TCanvas* canvas = new TCanvas("Correction", "Correction", 800, 800);
  //canvas->cd();

  TGraphErrors* g_chad = new TGraphErrors(50, ycuts, C_had, eycuts, eC_had);

  TGraphErrors* g_cdet = new TGraphErrors(50, ycuts, C_det, eycuts, eC_det);
  TGraphErrors* g_cdet_b = new TGraphErrors(50, ycuts, C_det_b, eycuts, eC_det_b);
  TGraphErrors* g_cdet_l = new TGraphErrors(50, ycuts, C_det_l, eycuts, eC_det_l);
  TGraphErrors* g_cdet_bl = new TGraphErrors(50, ycuts, C_det_bl, eycuts, eC_det_bl);

  TGraphErrors* g_cdet_con = new TGraphErrors(50, ycuts, C_det_con, eycuts, eC_det_con);
  TGraphErrors* g_cdet_con_b = new TGraphErrors(50, ycuts, C_det_con_b, eycuts, eC_det_con_b);
  TGraphErrors* g_cdet_con_l = new TGraphErrors(50, ycuts, C_det_con_l, eycuts, eC_det_con_l);
  TGraphErrors* g_cdet_con_bl = new TGraphErrors(50, ycuts, C_det_con_bl, eycuts, eC_det_con_bl);

  TGraphErrors* g_cdet_con2 = new TGraphErrors(50, ycuts, C_det_con2, eycuts, eC_det_con2);
  TGraphErrors* g_cdet_con2_b = new TGraphErrors(50, ycuts, C_det_con2_b, eycuts, eC_det_con2_b);
  TGraphErrors* g_cdet_con2_l = new TGraphErrors(50, ycuts, C_det_con2_l, eycuts, eC_det_con2_l);
  TGraphErrors* g_cdet_con2_bl = new TGraphErrors(50, ycuts, C_det_con2_bl, eycuts, eC_det_con2_bl);

  TGraphErrors* g_base = new TGraphErrors(60, ybase, base, eybase, ebase);

  g_chad -> SetLineWidth(2);
  g_chad -> SetMarkerStyle(20);
  g_chad -> SetMarkerSize(1.5);
  g_chad -> SetMarkerColor(kAzure+2);

  g_cdet -> SetLineWidth(2);
  g_cdet -> SetMarkerStyle(21);
  g_cdet -> SetMarkerSize(1.5);
  g_cdet -> SetMarkerColor(kPink-8);

  g_cdet_b -> SetLineWidth(2);
  g_cdet_b -> SetMarkerStyle(21);
  g_cdet_b -> SetMarkerSize(1.5);
  g_cdet_b -> SetMarkerColor(kViolet-3);

  g_cdet_l -> SetLineWidth(2);
  g_cdet_l -> SetMarkerStyle(21);
  g_cdet_l -> SetMarkerSize(1.5);
  g_cdet_l -> SetMarkerColor(kRed-9);

  g_cdet_bl -> SetLineWidth(2);
  g_cdet_bl -> SetMarkerStyle(21);
  g_cdet_bl -> SetMarkerSize(1.5);
  g_cdet_bl -> SetMarkerColor(kPink-8);

  g_cdet_con -> SetLineWidth(2);
  g_cdet_con -> SetLineColor(kGray+2);
  g_cdet_con -> SetMarkerStyle(22);
  g_cdet_con -> SetMarkerSize(1.5);
  g_cdet_con -> SetMarkerColor(kViolet+4);

  g_cdet_con_b -> SetLineWidth(2);
  g_cdet_con_b -> SetLineColor(kGray+2);
  g_cdet_con_b -> SetMarkerStyle(22);
  g_cdet_con_b -> SetMarkerSize(1.8);
  g_cdet_con_b -> SetMarkerColor(kViolet-3);

  g_cdet_con_l -> SetLineWidth(2);
  g_cdet_con_l -> SetLineColor(kGray+2);
  g_cdet_con_l -> SetMarkerStyle(22);
  g_cdet_con_l -> SetMarkerSize(1.8);
  g_cdet_con_l -> SetMarkerColor(kRed-9);

  g_cdet_con_bl -> SetLineWidth(2);
  g_cdet_con_bl -> SetLineColor(kGray+2);
  g_cdet_con_bl -> SetMarkerStyle(22);
  g_cdet_con_bl -> SetMarkerSize(1.5);
  g_cdet_con_bl -> SetMarkerColor(kViolet+4);

  g_cdet_con2 -> SetLineWidth(2);
  g_cdet_con2 -> SetLineColor(kGray+2);
  g_cdet_con2 -> SetMarkerStyle(23);
  g_cdet_con2 -> SetMarkerSize(1.5);
  g_cdet_con2 -> SetMarkerColor(kOrange+4);

  g_cdet_con2_b -> SetLineWidth(2);
  g_cdet_con2_b -> SetLineColor(kGray+2);
  g_cdet_con2_b -> SetMarkerStyle(23);
  g_cdet_con2_b -> SetMarkerSize(1.8);
  g_cdet_con2_b -> SetMarkerColor(kViolet-3);

  g_cdet_con2_l -> SetLineWidth(2);
  g_cdet_con2_l -> SetLineColor(kGray+2);
  g_cdet_con2_l -> SetMarkerStyle(23);
  g_cdet_con2_l -> SetMarkerSize(1.8);
  g_cdet_con2_l -> SetMarkerColor(kRed-9);

  g_cdet_con2_bl -> SetLineWidth(2);
  g_cdet_con2_bl -> SetLineColor(kGray+2);
  g_cdet_con2_bl -> SetMarkerStyle(23);
  g_cdet_con2_bl -> SetMarkerSize(1.5);
  g_cdet_con2_bl -> SetMarkerColor(kOrange+4);

  g_base -> SetMarkerStyle(0);


  //Correction factors
  /*TCanvas* canvas = new TCanvas("C", "C", 800, 800);
    canvas->cd();
    TLegend* legend = new TLegend(0.15,0.75,0.4,0.88);
    legend->SetTextSize(0.045);
    TH1F* frame = gPad->DrawFrame(0, 0.9, 0.05, 1.2);
    frame -> SetYTitle("Correction factors");
    frame -> SetXTitle("y_{c}");
    frame -> SetTitleOffset(1.5, "Y");

    g_base -> Draw("C");
    g_chad -> Draw("SAMEP");
    g_cdet -> Draw("SAMEP");
    g_cdet_con -> Draw("SAMEP");

    legend -> AddEntry(g_chad, "C^{had}(PYTHIA)", "p");
    legend -> AddEntry(g_cdet, "C^{det}", "p");
    legend -> AddEntry(g_cdet_con, "C^{'det}", "p");
    legend -> SetLineColor(0);
    legend -> SetFillColor(0);
    legend -> SetFillStyle(0);
    legend -> SetLineStyle(0);
    legend -> SetShadowColor(0);
    legend -> Draw();*/

  //Correction factors (Be consisted part by part)
  TCanvas* canvas1 = new TCanvas("C_bl", "C_bl", 800, 800);
  canvas1->cd();
  TLegend* legend1 = new TLegend(0.15,0.7,0.3,0.88);
  legend1->SetTextSize(0.03);
  TH1F* frame1 = gPad->DrawFrame(0, 0.9, 0.05, 1.2);
  frame1 -> SetYTitle("Correction factors");
  frame1 -> SetXTitle("y_{c}");
  frame1 -> SetTitleOffset(1.5, "Y");

  g_base -> Draw("C");
  g_chad -> Draw("SAMEP");
  g_cdet_bl -> Draw("SAMEP");
  g_cdet_con_bl -> Draw("SAMEP");
  g_cdet_con2_bl -> Draw("SAMEP");

  legend1 -> AddEntry(g_chad, "C^{had}(PYTHIA)", "p");
  legend1 -> AddEntry(g_cdet_bl, "C^{det}_{ideal} (only signal)", "p");
  legend1 -> AddEntry(g_cdet_con2_bl, "C^{'' det} (+ mistag)", "p");
  legend1 -> AddEntry(g_cdet_con_bl, "C^{' det} (+mistag + Z/#gamma bkg)", "p");

  legend1 -> SetLineColor(0);
  legend1 -> SetFillColor(0);
  legend1 -> SetFillStyle(0);
  legend1 -> SetLineStyle(0);
  legend1 -> SetShadowColor(0);
  legend1 -> Draw();

  TText* t = new TText(0.2,0.6,"Cambridge");
  t -> SetNDC(1);
  t -> SetTextSize(0.05);
  t -> Draw();


  //ratio
  /*TCanvas* canvas2 = new TCanvas("ratio", "ratio", 800, 800);
    canvas2->cd();

    TGraphErrors* g_ratio = new TGraphErrors(50, ycuts, ratio, eycuts, eratio);
    TH1F* frame2 = gPad->DrawFrame(0, 0.9, 0.05, 1.1);
    frame2 -> SetYTitle("C^{det}/C^{'det}");
    frame2 -> SetXTitle("y_{c}");
    frame2 -> SetTitleOffset(1.5, "Y");

    g_ratio -> SetMarkerStyle(20);
    g_ratio -> SetMarkerSize(1.5);
    g_ratio -> SetMarkerColor(kAzure-6);
    g_ratio -> SetLineWidth(2);

    g_base -> Draw("C");
    g_ratio -> Draw("SAMEP");
    t -> Draw();*/


  //ratio (Be consisted part by part)
  TCanvas* canvas3 = new TCanvas("ratio_bl", "ratio_bl", 800, 800);
  canvas3->cd();

  TGraphErrors* g_ratio_bl = new TGraphErrors(50, ycuts, ratio_bl, eycuts, eratio_bl);
  TH1F* frame3 = gPad->DrawFrame(0, 0.9, 0.05, 1.1);
  frame3 -> SetYTitle("C^{det}/C^{'det}");
  frame3 -> SetXTitle("y_{c}");
  frame3 -> SetTitleOffset(1.5, "Y");

  g_ratio_bl -> SetMarkerStyle(20);
  g_ratio_bl -> SetMarkerSize(1.5);
  g_ratio_bl -> SetMarkerColor(kAzure-6);
  g_ratio_bl -> SetLineWidth(2);

  g_base -> Draw("C");
  g_ratio_bl -> Draw("SAMEP");
  t -> Draw();


  //Correction factor C_det part by part
  TCanvas* canvas4 = new TCanvas("PartCorrections", "PartCorrections", 800, 800);
  canvas4->cd();

  TLegend* legend4 = new TLegend(0.15,0.6,0.4,0.88);
  legend4->SetTextSize(0.045);
  TH1F* frame4 = gPad->DrawFrame(0, 0.9, 0.05, 1.5);
  frame4 -> SetYTitle("Correction factors");
  frame4 -> SetXTitle("y_{c}");
  frame4 -> SetTitleOffset(1.5, "Y");

  g_base -> Draw("C");
  g_cdet_b -> Draw("SAMEP");
  g_cdet_l -> Draw("SAMEP");
  g_cdet_con_b -> Draw("SAMEP");
  g_cdet_con_l -> Draw("SAMEP");
  g_cdet_con2_b -> Draw("SAMEP");
  g_cdet_con2_l -> Draw("SAMEP");
  //g_cdet_bl -> Draw("SAMEP");
	
  Double_t* cb_list = g_cdet_b -> GetY();
  Double_t* cl_list = g_cdet_l -> GetY();
  Double_t* cb_con_list = g_cdet_con_b -> GetY();
  Double_t* cl_con_list = g_cdet_con_l -> GetY();
  Double_t* cb_con2_list = g_cdet_con2_b -> GetY();
  Double_t* cl_con2_list = g_cdet_con2_l -> GetY();
  Double_t* cb_elist = g_cdet_b -> GetEY();
  Double_t* cl_elist = g_cdet_l -> GetEY();
  Double_t* cb_con_elist = g_cdet_con_b -> GetEY();
  Double_t* cl_con_elist = g_cdet_con_l -> GetEY();
  Double_t* cb_con2_elist = g_cdet_con2_b -> GetEY();
  Double_t* cl_con2_elist = g_cdet_con2_l -> GetEY();
  double cb_001 = cb_list[10];
  double cl_001 = cl_list[10];
  double cb_con_001 = cb_con_list[10];
  double cl_con_001 = cl_con_list[10];
  double cb_con2_001 = cb_con2_list[10];
  double cl_con2_001 = cl_con2_list[10];
  double ecb_001 = cb_elist[10];
  double ecl_001 = cl_elist[10];
  double ecb_con_001 = cb_con_elist[10];
  double ecl_con_001 = cl_con_elist[10];
  double ecb_con2_001 = cb_con2_elist[10];
  double ecl_con2_001 = cl_con2_elist[10];
  std::cout << "Cb @ yc=0.01 : " << cb_001 << "+-" << ecb_001 << " ,  Cl @ yc=0.01 : " << cl_001 << "+-" << ecl_001 << " -->  Cdet = " << cb_001/cl_001 << "+-" << eC_det_bl[10] << std::endl;
  std::cout << "C'b @ yc=0.01 : " << cb_con_001 << "+-" << ecb_con_001 << " ,  C'l @ yc=0.01 : " << cl_con_001 << "+-" << ecl_con_001 << " -->  C'det = " << cb_con_001/cl_con_001 << "+-" << eC_det_con_bl[10] << std::endl;
  std::cout << "C''b @ yc=0.01 : " << cb_con2_001 << "+-" << ecb_con2_001 << " ,  C'l @ yc=0.01 : " << cl_con2_001 << "+-" << ecl_con2_001 << " -->  C'det = " << cb_con2_001/cl_con2_001 << "+-" << eC_det_con2_bl[10] << std::endl;

  std::cout << "Cdet/C'det = " << (cb_001/cl_001)/(cb_con_001/cl_con_001) << "+-" << eratio_bl[10] << std::endl;
  std::cout << "Cdet/C''det = " << (cb_001/cl_001)/(cb_con2_001/cl_con2_001) << "+-" << eratio_bl[10] << std::endl;


  legend4 -> AddEntry(g_cdet_b, "C^{det}_{b}", "p");
  legend4 -> AddEntry(g_cdet_l, "C^{det}_{l}", "p");
  legend4 -> AddEntry(g_cdet_con_b, "C^{'det}_{b}", "p");
  legend4 -> AddEntry(g_cdet_con_l, "C^{'det}_{l}", "p");
  legend4 -> AddEntry(g_cdet_con2_b, "C^{'' det}_{b}", "p");
  legend4 -> AddEntry(g_cdet_con2_l, "C^{'' det}_{l}", "p");
  //legend4 -> AddEntry(g_cdet_bl, "C^{det}", "p");
  legend4 -> SetLineColor(0);
  legend4 -> SetFillColor(0);
  legend4 -> SetFillStyle(0);
  legend4 -> SetLineStyle(0);
  legend4 -> SetShadowColor(0);
  legend4 -> Draw();

  TText* t1 = new TText(0.15,0.55,"Cambridge");
  t1 -> SetNDC(1);
  t1 -> SetTextSize(0.05);
  t1 -> Draw();


  /*//Correction factor C_det part by part
    TCanvas* canvas5 = new TCanvas("PartCorrections_contami", "PartCorrections_contami", 800, 800);
    canvas5->cd();

    TLegend* legend5 = new TLegend(0.15,0.75,0.4,0.88);
    legend5->SetTextSize(0.045);
    TH1F* frame5 = gPad->DrawFrame(0, 0.9, 0.05, 16.0);
    frame5 -> SetYTitle("Correction factors (Contamination remained)");
    frame5 -> SetXTitle("y_{c}");
    frame5 -> SetTitleOffset(1.5, "Y");

    g_base -> Draw("C");
    g_cdet_con_b -> Draw("SAMEP");
    g_cdet_con_l -> Draw("SAMEP");
    //g_cdet_con_bl -> Draw("SAMEP");


    legend5 -> AddEntry(g_cdet_con_b, "C^{det}_b", "p");
    legend5 -> AddEntry(g_cdet_con_l, "C^{det}_l", "p");
    //legend5 -> AddEntry(g_cdet_con_bl, "C^{det}", "p");
    legend5 -> SetLineColor(0);
    legend5 -> SetFillColor(0);
    legend5 -> SetFillStyle(0);
    legend5 -> SetLineStyle(0);
    legend5 -> SetShadowColor(0);
    legend5 -> Draw();
    t -> Draw();*/
}
