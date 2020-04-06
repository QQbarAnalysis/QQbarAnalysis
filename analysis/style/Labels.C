#include "Labels.h"

#include "TLatex.h"
#include "TLine.h"
#include "TPave.h"
#include "TMarker.h"

void QQBARLabel(Double_t x,Double_t y,char* text,Color_t color)
{
  TLatex l;
  //l.SetTextAlign(12);
  l.SetTextSize(0.08);
  l.SetNDC();
  l.SetTextFont(62);
  l.SetTextColor(color);

  double delx = 800*gPad->GetWh()/(1000*gPad->GetWw());
  
  l.DrawLatex(x,y,"ILD");
  if (text) {
    TLatex p;
    p.SetNDC();
    p.SetTextSize(0.06);
    p.SetTextFont(42);
    p.SetTextColor(color);
    p.DrawLatex(x+0.105,y,text);
  }
}




