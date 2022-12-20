//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "CSPIN.h"
#include <ComCtrls.hpp>
#include "Robot.h"
#include "Observer.h"
#include "Calibrator.h"
#include "RobotSimu.h"
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "RobotComm.h"
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TCSpinEdit *CSpinEdit1;
        TCSpinEdit *CSpinEdit2;
        TCSpinEdit *CSpinEdit3;
        TCSpinEdit *CSpinEdit4;
        TCSpinEdit *CSpinEdit5;
        TCSpinEdit *CSpinEdit6;
        TLabel *Label7;
        TCSpinEdit *CSpinEdit7;
        TLabel *Label8;
        TCSpinEdit *CSpinEdit8;
        TGroupBox *GroupBox2;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label15;
        TLabel *Label16;
        TCSpinEdit *CSpinEdit9;
        TCSpinEdit *CSpinEdit10;
        TCSpinEdit *CSpinEdit11;
        TCSpinEdit *CSpinEdit12;
        TCSpinEdit *CSpinEdit15;
        TCSpinEdit *CSpinEdit16;
        TPanel *Panel3;
        TGroupBox *GroupBox3;
        TLabel *Label20;
        TComboBox *ComboBox1;
        TLabel *Label13;
        TCSpinEdit *CSpinEdit13;
        TLabel *Label14;
        TCSpinEdit *CSpinEdit14;
        TButton *Button2;
        TBevel *Bevel1;
        TBevel *Bevel2;
        TGroupBox *GroupBox4;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TBevel *Bevel3;
        TButton *Button7;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TPaintBox *PaintBox1;
        TMemo *Memo1;
        TPanel *Panel2;
        TCSpinEdit *CSpinEdit21;
        TLabel *Label21;
        TGroupBox *GroupBox5;
        TValueListEditor *ValueList;
        TStatusBar *StatusBar1;
        TTimer *Timer1;
        TButton *Button1;
        TGroupBox *GroupBox6;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TPageControl *PageControl2;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
        TListView *ListView1;
        TMemo *Memo2;
        TChart *Chart1;
        TFastLineSeries *Series1;
        TTabSheet *TabSheet5;
        TChart *Chart2;
        TBarSeries *Series2;
        TBarSeries *Series3;
        TPanel *Panel4;
        TEdit *Edit1;
        TGroupBox *GroupBox7;
        TLabel *Label29;
        TCSpinEdit *CSpinEdit29;
        TLabel *Label18;
        TCSpinEdit *CSpinEdit20;
        TLabel *Label30;
        TCSpinEdit *CSpinEdit30;
        TLabel *Label17;
        TCSpinEdit *CSpinEdit17;
        TGroupBox *GroupBox8;
        TLabel *Label19;
        TCSpinEdit *CSpinEdit18;
        TLabel *Label23;
        TCSpinEdit *CSpinEdit19;
        TGroupBox *GroupBox9;
        TButton *Button8;
        TButton *Button6;
        TButton *Button9;
        TButton *Button10;
        TButton *Button11;
        TGroupBox *GroupBox10;
        TButton *Button12;
        TSavePictureDialog *SavePictureDialog1;
        TLabel *Label22;
        TCSpinEdit *CSpinEdit22;
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);
private:
        CRobotSimu     __RobotSimu;
        CCalibrator    __Calibrator;
        CRobotCommPkg  __RobotPkg;
        HANDLE         __hComm;
        int            __CaliStatus;
        int            __SampleCnt;
        int            __CaliSteadyTime;
private:
        void InitComm(AnsiString Comm);
        bool SendOrder(CRobotCommPkg &CommPkg);
private:	// User declarations
        void SaveRobotParams(void);
        void LoadRobotParams(void);
private:
        void EvaluatePosEulerError(int Count);
        void ShowDistribution(vector<double> &Values, TChartSeries *Series);
private:
        void   ShowCaliResult(CRobot &Robot, CObserver &Observe, TListView *View);
        void   AverageCaliResult(TListItem *Item);
        double EvalCaliError(TListItem *Item);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
