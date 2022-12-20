//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TRangeDlg.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TRangeDlg *RangeDlg;
//--------------------------------------------------------------------- 
__fastcall TRangeDlg::TRangeDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void TRangeDlg::ShowRange(vector<pair<double, double> > &Values)
{
   for(unsigned int i = 0; i < Values.size(); ++i)
      Chart1->Series[0]->AddXY(Values[i].first, Values[i].second);

   ShowModal();
}
