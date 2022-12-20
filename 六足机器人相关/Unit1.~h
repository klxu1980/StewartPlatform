//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
class CFilterAcc2Motion
{
private:
   double __Xh[3];    // 输出
   double __Amax;     // 最大加速度
   double __K1;       // 位置环反馈系数，K1 = amax / xmax，其中xmax是最大行程(单位m)
   double __K2;       // 速度环反馈系数，K2 = amax / vmax，其中vmax是最大速度(单位m/s)
   double __T;        // 采样时间
   double __Tsqr;     // 采样时间平方
   double __InputAcc; // 输入加速度
   double __RealAcc;  // 实际输出加速度
public:
   CFilterAcc2Motion(void);
public:
   void   SetParams(double T, double amax, double vmax, double xmax);
   double Output(double Acc);
   double XValue(void){return __Xh[0];}
   double RealAcc(void){return __RealAcc;}
   double InputAcc(void){return __InputAcc;}
};

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TChart *Chart1;
        TLineSeries *Series1;
        TLineSeries *Series2;
        TLabeledEdit *LabeledEdit1;
        TLabeledEdit *LabeledEdit2;
        TLabeledEdit *LabeledEdit3;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 