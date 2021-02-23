#include "Labels.h"
#include "TLatex.h"
#include "TLine.h"
#include "TPave.h"
#include "TMarker.h"

void QQBARLabel(Double_t x,Double_t y,TString text,Color_t color)
{
  TLatex l;
  //l.SetTextAlign(12);
  l.SetTextSize(0.065);
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextColor(color);

  double delx = 1200*gPad->GetWh()/(1000*gPad->GetWw());
  
  l.DrawLatex(x,y,"ILD");
  if (text) {
    TLatex p;
    p.SetNDC();
    p.SetTextSize(0.05);
    p.SetTextFont(42);
    p.SetTextColor(color);
    p.DrawLatex(x+0.1,y,text);
  }
}

void QQBARLabel2(Double_t x,Double_t y,TString text,Color_t color, Double_t textsize, Double_t angle)
{
  
  TLatex p;
  p.SetNDC();
  p.SetTextSize(textsize);
  p.SetTextFont(52);
  p.SetTextColor(color);
  p.SetTextAngle(angle);
  p.DrawLatex(x,y,text);
  
}





