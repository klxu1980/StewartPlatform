//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <math.h>
#include <ExtCtrls.hpp>
#include "RobotImage.h"
#include "CSPIN.h"
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <Mmsystem.h>
#include "Robot.h"
#include "MotionSimulator.h"
#include "RobotServo.h"
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "PlaneData.h"
#include "CtrlSystem.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImageList *ImageList1;
        TCoolBar *CoolBar1;
        TToolBar *ToolBar2;
        TPanel *Panel2;
        TToolButton *ToolButton6;
        TToolButton *ToolButton7;
        TToolButton *ToolButton9;
        TToolButton *ToolButton10;
        TToolButton *ToolButton8;
        TShape *Shape1;
        TPaintBox *PaintBox1;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TPanel *Panel8;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TGroupBox *GroupBox1;
        TLabeledEdit *LabeledEdit1;
        TLabeledEdit *LabeledEdit2;
        TLabeledEdit *LabeledEdit3;
        TLabeledEdit *LabeledEdit4;
        TLabeledEdit *LabeledEdit5;
        TLabeledEdit *LabeledEdit6;
        TLabeledEdit *LabeledEdit7;
        TButton *BtnSettings;
        TGroupBox *GroupBox3;
        TLabel *Label7;
        TCSpinEdit *CSpinEdit7;
        TTabSheet *TabSheetRobot;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TCSpinEdit *CSpinEditX;
        TCSpinEdit *CSpinEditY;
        TCSpinEdit *CSpinEditZ;
        TCSpinEdit *CSpinEditYaw;
        TCSpinEdit *CSpinEditPitch;
        TCSpinEdit *CSpinEditRoll;
        TMemo *Memo1;
        TLabeledEdit *LabeledEdit8;
        TLabeledEdit *LabeledEdit9;
        TTabSheet *TabSheetServo;
        TGroupBox *GroupBox4;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TCSpinEdit *CSpinEdit8;
        TCSpinEdit *CSpinEdit9;
        TCSpinEdit *CSpinEdit10;
        TCSpinEdit *CSpinEdit11;
        TCSpinEdit *CSpinEdit12;
        TCSpinEdit *CSpinEdit13;
        TLabeledEdit *LabeledEdit10;
        TLabeledEdit *LabeledEdit11;
        TMemo *Memo2;
        TPanel *Panel3;
        TButton *Button7;
        TButton *Button8;
        TButton *Button5;
        TTimer *Timer1;
        TTimer *Timer2;
        TToolButton *ToolButton5;
        TToolButton *ToolButton11;
        TToolButton *ToolButton12;
        TBevel *Bevel1;
        TTimer *Timer3;
        TBevel *Bevel2;
        TGroupBox *GroupBox5;
        TPanel *Panel1;
        TPanel *PnlLinkLen1;
        TPanel *Panel7;
        TPanel *PnlLinkLen2;
        TPanel *Panel10;
        TPanel *PnlLinkLen3;
        TPanel *Panel12;
        TPanel *PnlLinkLen4;
        TPanel *Panel14;
        TPanel *PnlLinkLen5;
        TPanel *Panel16;
        TPanel *PnlLinkLen6;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox6;
        TPanel *Panel9;
        TPanel *Panel11;
        TPanel *Panel13;
        TPanel *Panel15;
        TPanel *Panel17;
        TPanel *Panel18;
        TPanel *Panel19;
        TPanel *Panel20;
        TPanel *Panel21;
        TPanel *Panel22;
        TPanel *Panel23;
        TPanel *Panel24;
        TGroupBox *GroupBox7;
        TPanel *Panel25;
        TPanel *Panel26;
        TPanel *Panel27;
        TPanel *Panel28;
        TPanel *Panel29;
        TPanel *Panel30;
        TPanel *Panel31;
        TPanel *Panel32;
        TPanel *Panel33;
        TPanel *Panel34;
        TPanel *Panel35;
        TPanel *Panel36;
        TShape *Shape2;
        TCSpinEdit *CSpinEdit1;
        TTabSheet *TabSheet3;
        TGroupBox *GroupBox8;
        TPanel *Panel37;
        TPanel *Panel38;
        TPanel *Panel39;
        TPanel *Panel40;
        TPanel *Panel41;
        TPanel *Panel42;
        TPanel *Panel43;
        TPanel *Panel44;
        TPanel *Panel45;
        TPanel *Panel46;
        TPanel *Panel47;
        TPanel *Panel48;
        TCheckBox *CheckBox1;
        TCSpinEdid *CSpinEdit2;
        TCSpinEdit *CSpinEdit3;
        TButton *Button1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall CSpinEditXChange(TObject *Sender);
        void __fastcall ToolButton6Click(TObject *Sender);
        void __fastcall ToolButton7Click(TObject *Sender);
        void __fastcall ToolButton9Click(TObject *Sender);
        void __fastcall ToolButton10Click(TObject *Sender);
        void __fastcall ToolButton1Click(TObject *Sender);
        void __fastcall ToolButton2Click(TObject *Sender);
        void __fastcall BtnSettingsClick(TObject *Sender);
        void __fastcall PaintBox1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall PaintBox1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall PaintBox1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall ToolButton3Click(TObject *Sender);
        void __fastcall ToolButton4Click(TObject *Sender);
        void __fastcall CSpinEdit8Change(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall ToolButton11Click(TObject *Sender);
        void __fastcall ToolButton12Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall Timer3Timer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:
        CCtrlSystem        __CtrlSystem;
        CRobotImage        __RobotImage;
        bool               __MouseDown;
        int                __MouseX;
        int                __MouseY;
        HANDLE             __hFSXDll;
        HANDLE             __hComm;
private:
        typedef bool      (*INIT_FSX_CONNECTION)(void);
        typedef CPlaneAcc (*GET_PLANE_ACC)(void);
private:
        INIT_FSX_CONNECTION InitFSXConnection;
        GET_PLANE_ACC       GetPlaneAcceleration;
private:
        void ShowRobotStatus(CRobot &Robot);
        short CalcCRC(char *Buffer, int Count);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
// 2018-1-25: 加入机器人电缸伺服控制
#endif
 