//
//   @file    IrlesLabels.h         
//   
//   @author M.Sutton
// 

#ifndef __IRLESLABELS_H
#define __IRLESLABELS_H

#include "Rtypes.h"

void IRLESLabel(Double_t x,Double_t y,char* text=NULL,Color_t color=1); 

void IRLESLabel_ratio(Double_t x,Double_t y,char* text=NULL,Color_t color=1);

void IRLESLabelOld(Double_t x,Double_t y,bool Preliminary=false,Color_t color=1); 

void IRLESVersion(char* version=NULL,Double_t x=0.88,Double_t y=0.975,Color_t color=1); 

void myText(Double_t x,Double_t y,Color_t color,char *text); 

void myText_ratio(Double_t x,Double_t y,Color_t color,char *text);

void myBoxText(Double_t x, Double_t y,Double_t boxsize,Int_t mcolor,char *text); 

void myMarkerText(Double_t x,Double_t y,Int_t color,Int_t mstyle,char *text); 

#endif // __IRLESLABELS_H
