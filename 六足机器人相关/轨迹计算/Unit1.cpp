//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
   float ax[4];
   float ay[4];

   CalcParams(LabeledEdit9->Text.ToDouble(),
              LabeledEdit1->Text.ToDouble(), LabeledEdit5->Text.ToDouble(),
              LabeledEdit3->Text.ToDouble(), LabeledEdit7->Text.ToDouble(),
              ax);

   CalcParams(LabeledEdit9->Text.ToDouble(),
              LabeledEdit2->Text.ToDouble(), LabeledEdit6->Text.ToDouble(),
              LabeledEdit4->Text.ToDouble(), LabeledEdit8->Text.ToDouble(),
              ay);

   float MinX = 100000;
   float MinY = 100000;
   float MaxX = -100000;
   float MaxY = -100000;
   __Trace.clear();
   for(float t = 0; t < LabeledEdit9->Text.ToDouble(); t += 0.01)
   {
      float x = ax[0] + ax[1] * t + ax[2] * t * t + ax[3] * t * t * t;
      float y = ay[0] + ay[1] * t + ay[2] * t * t + ay[3] * t * t * t;

      MinX = min(MinX, x);
      MaxX = max(MaxX, x);
      MinY = min(MinY, y);
      MaxY = max(MaxY, y);
      __Trace.push_back(pair<float, float>(x, y));
   }
   Chart1->BottomAxis->SetMinMax(MinX, MaxX);
   Chart1->LeftAxis->SetMinMax(MinY, MaxY);
}
//---------------------------------------------------------------------------
void TForm1::CalcParams(float T, float L0, float L1, float V0, float V1, float *a)
{
   a[0] = L0;
   a[1] = V0;
   a[2] = (3 * (L1 - L0) - (2 * V0 + V1) * T) / (T * T);
   a[3] = (2 * (L0 - L1) + (V0 + V1) * T) / (T * T * T);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Chart1AfterDraw(TObject *Sender)
{
   if(__Trace.empty())
      return;

   Chart1->Canvas->MoveTo(Chart1->BottomAxis->CalcPosValue(__Trace[0].first),
                          Chart1->LeftAxis->CalcPosValue(__Trace[0].second));
   for(unsigned int i = 0; i < __Trace.size(); ++i)
      Chart1->Canvas->LineTo(Chart1->BottomAxis->CalcPosValue(__Trace[i].first),
                          Chart1->LeftAxis->CalcPosValue(__Trace[i].second));
}
//---------------------------------------------------------------------------

