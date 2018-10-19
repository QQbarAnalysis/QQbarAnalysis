//
//  Style, based on a style file from BaBar
//

#include <iostream>
#include "Style.h"
#include "TROOT.h"

void SetIrlesStyle ()
{
  static TStyle* irlesStyle = 0;
  std::cout << "\nApplying IRLES style settings...\n" << std::endl ;
  if ( irlesStyle==0 ) irlesStyle = IrlesStyle();
  gROOT->SetStyle("IRLES");
  gROOT->ForceStyle();
}

TStyle* IrlesStyle() 
{
  TStyle *irlesStyle = new TStyle("IRLES","Irles style");

  // use plain black on white colors
  Int_t icol=0; // WHITE
  irlesStyle->SetFrameBorderMode(icol);
  irlesStyle->SetFrameFillColor(icol);
  irlesStyle->SetCanvasBorderMode(icol);
  irlesStyle->SetCanvasColor(icol);
  irlesStyle->SetPadBorderMode(icol);
  irlesStyle->SetPadColor(icol);
  irlesStyle->SetStatColor(icol);
  //irlesStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

  // set the paper & margin sizes
  irlesStyle->SetPaperSize(20,26);

  // set margin sizes
  irlesStyle->SetPadTopMargin(0.05);
  irlesStyle->SetPadRightMargin(0.05);
  irlesStyle->SetPadBottomMargin(0.16);
  irlesStyle->SetPadLeftMargin(0.16);

  // set title offsets (for axis label)
  irlesStyle->SetTitleXOffset(1.4);
  irlesStyle->SetTitleYOffset(1.4);

  // use large fonts
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.04;
  irlesStyle->SetTextFont(font);

  irlesStyle->SetTextSize(tsize);
  irlesStyle->SetLabelFont(font,"x");
  irlesStyle->SetTitleFont(font,"x");
  irlesStyle->SetLabelFont(font,"y");
  irlesStyle->SetTitleFont(font,"y");
  irlesStyle->SetLabelFont(font,"z");
  irlesStyle->SetTitleFont(font,"z");
  
  irlesStyle->SetLabelSize(tsize,"x");
  irlesStyle->SetTitleSize(tsize,"x");
  irlesStyle->SetLabelSize(tsize,"y");
  irlesStyle->SetTitleSize(tsize,"y");
  irlesStyle->SetLabelSize(tsize,"z");
  irlesStyle->SetTitleSize(tsize,"z");

  // use bold lines and markers
  irlesStyle->SetMarkerStyle(20);
  irlesStyle->SetMarkerSize(0.8);
  irlesStyle->SetHistLineWidth(2.);
  irlesStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars 
  //irlesStyle->SetErrorX(0.001);
  // get rid of error bar caps
  irlesStyle->SetEndErrorSize(0.);

  // do not display any of the standard histogram decorations
  irlesStyle->SetOptTitle(0);
  //irlesStyle->SetOptStat(1111);
  irlesStyle->SetOptStat(0);
  //irlesStyle->SetOptFit(1111);
  irlesStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  irlesStyle->SetPadTickX(1);
  irlesStyle->SetPadTickY(1);

  return irlesStyle;

}

