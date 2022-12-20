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
//---------------------------------------------------------------------------
CFilterAcc2Motion::CFilterAcc2Motion(void)
 : __T(0.02),
   __Amax(9.8),
   __K1(__Amax / 0.4),
   __K2(__Amax / 0.1)
{
   __Xh[0] = __Xh[1] = __Xh[2] = 0;
}
//---------------------------------------------------------------------------
void CFilterAcc2Motion::SetParams(double T, double amax, double vmax, double xmax)
{
   __T    = T;
   __Tsqr = T * T;
   __Amax = amax;
   __K1   = amax / xmax;
   __K2   = amax / vmax;
}
//---------------------------------------------------------------------------
double CFilterAcc2Motion::Output(double Acc)
{
   __InputAcc = Acc;

   // 加速度限幅
   if(Acc > __Amax)
      Acc = __Amax;
   else if(Acc < -__Amax)
      Acc = -__Amax;

   // 注意：__Xh[0] = Xh[k], __Xh[1] = Xh[k-1], __Xh[2] = Xh[k-2]
   __Xh[2] = __Xh[1];
   __Xh[1] = __Xh[0];
   __Xh[0] = ((2.0 + __K2 * __T) * __Xh[1] - __Xh[2] + __T * __T * Acc) / (1.0 + __K2 * __T + __K1 * __T * __T);

   // 计算实际输出加速度
   __RealAcc = (__Xh[0] - 2.0 * __Xh[1] + __Xh[2]) / (__T * __T); 

   return __Xh[0];
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   CFilterAcc2Motion Motion;
   Motion.SetParams(0.01,
                    LabeledEdit3->Text.ToDouble(),
                    LabeledEdit2->Text.ToDouble(),
                    LabeledEdit1->Text.ToDouble());

   Chart1->Series[0]->Clear();
   for(float t = 0; t < 10; t += 0.01)
   {
      double y = Motion.Output(LabeledEdit3->Text.ToDouble());
      Chart1->Series[0]->AddXY(t, y);
   }
}
//---------------------------------------------------------------------------
