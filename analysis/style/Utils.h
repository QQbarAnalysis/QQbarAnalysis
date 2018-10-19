//
//   @file    IrlesUtils.h         
//   
//

#ifndef __IRLESUTILS_H
#define __IRLESUTILS_H

#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"

void IRLES_LABEL(Double_t x,Double_t y,Color_t color=1); 

TGraphErrors* myTGraphErrorsDivide(TGraphErrors* g1,TGraphErrors* g2);

TGraphAsymmErrors* myTGraphErrorsDivide(TGraphAsymmErrors* g1,TGraphAsymmErrors* g2);

TGraphAsymmErrors* myMakeBand(TGraphErrors* g0, TGraphErrors* g1,TGraphErrors* g2);

void myAddtoBand(TGraphErrors* g1, TGraphAsymmErrors* g2);

TGraphErrors* TH1TOTGraph(TH1 *h1);

void myText(Double_t x,Double_t y,Color_t color,char *text);

void myBoxText(Double_t x, Double_t y,Double_t boxsize,Int_t mcolor,char *text);

void myMarkerText(Double_t x,Double_t y,Int_t color,Int_t mstyle,char *text,Float_t msize=2.); 

#endif // __IRLESUTILS_H
