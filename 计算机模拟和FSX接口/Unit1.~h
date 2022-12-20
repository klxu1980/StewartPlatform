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
#include "RobotSimu.h"
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
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TPanel *Panel8;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TTimer *Timer1;
        TTimer *Timer2;
        TToolButton *ToolButton5;
        TToolButton *ToolButton11;
        TToolButton *ToolButton12;
        TTimer *Timer3;
        TToolBar *ToolBar1;
        TPanel *Panel9;
        TToolButton *ToolButton13;
        TToolButton *BtnRobotReset;
        TToolButton *ToolButton14;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TPanel *Panel1;
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
        TBevel *Bevel1;
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
        TLabeledEdit *LabeledEdit8;
        TLabeledEdit *LabeledEdit9;
        TMemo *Memo1;
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
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox7;
        TListView *ListView1;
        TButton *Button1;
        TPanel *Panel49;
        TCheckBox *CheckBox1;
        TButton *Button2;
        TGroupBox *GroupBox9;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
        TLabel *Label19;
        TCSpinEdit *CSpinEdit1;
        TCSpinEdit *CSpinEdit2;
        TCSpinEdit *CSpinEdit3;
        TCSpinEdit *CSpinEdit4;
        TCSpinEdit *CSpinEdit5;
        TCSpinEdit *CSpinEdit6;
        TButton *Button3;
        TEdit *Edit1;
        TGroupBox *GroupBox6;
        TListView *ListView2;
        TGroupBox *GroupBox10;
        TListView *ListView3;
        TListView *ListView4;
        TPaintBox *PaintBox1;
        TPanel *Panel3;
        TChart *Chart1;
        TFastLineSeries *Series1;
        TFastLineSeries *Series2;
        TPanel *Panel7;
        TLabel *Label20;
        TComboBox *ComboBox1;
        TStatusBar *StatusBar1;
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
        void __fastcall ToolButton11Click(TObject *Sender);
        void __fastcall ToolButton12Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall Timer3Timer(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall BtnRobotResetClick(TObject *Sender);
private:
        bool               __Initialized;
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
        void  ShowRobotStatus(CRobot &Robot);
private:
        bool  SendOrder(char *Buffer);
        void  SendResetOrder(void);
        void  SendJackLengthOrder(int JackID, int Length, int Speed);   // Length单位：mm
        void  SendPosEurlarOrder(int ID, int Value);
        void  SendMotionSimuOrder(float AccX, float AccY, float AccZ, float AccYaw, float AccPitch, float AccRoll);
        unsigned short CalcCRC(unsigned char *Buffer, int Count);
        double Clip(double Value, double Range);
        double Rad2Degree(double Rad){return Rad * 180.0 / M_PI;}  // 弧度换算为角度
private:
        void  SendMotionSimuOrder(void);
        void  SendJackLengthOrder(void);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
// 2018-01-25: 加入机器人电缸伺服控制
// 2019-03-23: 重新修改上下平台尺寸
// 2019-05-05: 重新修改机器人控制程序，将正向运动学部分分离出来，由CRobotDKP处理
// 2019-05-06：修正了串口数据解析错误
// 2019-05-07：减少了串口数据长度，每个加速度使用一个字节发送
#endif
 