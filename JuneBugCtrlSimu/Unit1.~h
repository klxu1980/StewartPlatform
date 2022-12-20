//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include "CSPIN.h"
#include "CtrlSystem.h"
#include "RobotImage.h"
#include "RobotComm.h"
#include "PlaneData.h"
#include "AccSensor.h"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImageList *ImageList1;
        TCoolBar *CoolBar1;
        TToolBar *ToolBar2;
        TPanel *Panel4;
        TToolButton *ToolButton8;
        TPanel *Panel5;
        TToolButton *ToolButton6;
        TToolButton *ToolButton7;
        TPanel *Panel6;
        TToolButton *ToolButton9;
        TToolButton *ToolButton10;
        TPanel *Panel8;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TPanel *Panel2;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
        TToolButton *ToolButton11;
        TToolButton *ToolButton12;
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
        TTabSheet *TabSheetServo;
        TGroupBox *GroupBox4;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TCSpinEdit *CSpinEditL1;
        TCSpinEdit *CSpinEditL2;
        TCSpinEdit *CSpinEditL3;
        TCSpinEdit *CSpinEditL4;
        TCSpinEdit *CSpinEditL5;
        TCSpinEdit *CSpinEditL6;
        TTabSheet *TabSheet2;
        TPaintBox *PaintBox1;
        TTimer *TimerCtrlSimu;
        TTimer *TimerComm;
        TStatusBar *StatusBar1;
        TGroupBox *GroupBox1;
        TLabeledEdit *EditMinZ;
        TLabeledEdit *EditMaxZ;
        TBevel *Bevel1;
        TPageControl *PageControl2;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet3;
        TGroupBox *GroupBox6;
        TListView *ListViewPostures;
        TPanel *Panel3;
        TGroupBox *GroupBox10;
        TListView *ListViewJacks;
        TGroupBox *GroupBox3;
        TShape *Shape1;
        TShape *Shape2;
        TShape *Shape3;
        TShape *Shape4;
        TShape *Shape5;
        TShape *Shape6;
        TShape *Shape7;
        TShape *Shape8;
        TShape *Shape9;
        TShape *Shape10;
        TShape *Shape11;
        TShape *Shape12;
        TShape *Shape13;
        TShape *Shape14;
        TShape *Shape15;
        TShape *Shape16;
        TShape *Shape17;
        TShape *Shape18;
        TShape *Shape19;
        TShape *Shape20;
        TShape *Shape21;
        TShape *Shape22;
        TShape *Shape23;
        TShape *Shape24;
        TGroupBox *GroupBox5;
        TListView *ListView2;
        TGroupBox *GroupBox8;
        TComboBox *ComboBox1;
        TCheckBox *CheckBox1;
        TTabSheet *TabSheet4;
        TRadioButton *RadioButton4;
        TCheckBox *CheckBox2;
        TLabeledEdit *LabeledEdit1;
        TLabeledEdit *LabeledEdit2;
        TLabeledEdit *LabeledEdit3;
        TTimer *AccSensorTimer;
        TLabeledEdit *LabeledEdit4;
        TCSpinEdit *CSpinEdit7;
        TPageControl *PageControl3;
        TTabSheet *TabSheet5;
        TTabSheet *TabSheet6;
        TPanel *Panel49;
        TCheckBox *CheckBoxFSXCtrl;
        TGroupBox *GroupBox7;
        TListView *ListView1;
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
        TTabSheet *TabSheet7;
        TTabSheet *TabSheet8;
        TTabSheet *TabSheet9;
        TLabeledEdit *LabeledEdit5;
        TLabeledEdit *LabeledEdit6;
        TLabeledEdit *LabeledEdit7;
        TLabeledEdit *LabeledEdit8;
        TLabeledEdit *LabeledEdit9;
        TLabeledEdit *LabeledEdit10;
        TLabeledEdit *LabeledEdit11;
        TLabeledEdit *LabeledEdit12;
        TLabeledEdit *LabeledEdit13;
        TLabeledEdit *LabeledEdit14;
        TLabeledEdit *LabeledEdit15;
        TLabeledEdit *LabeledEdit16;
        TLabeledEdit *LabeledEdit17;
        TLabeledEdit *LabeledEdit18;
        TLabeledEdit *LabeledEdit19;
        TLabeledEdit *LabeledEdit20;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox8;
        TLabeledEdit *LabeledEdit21;
        TLabeledEdit *LabeledEdit22;
        TLabeledEdit *LabeledEdit23;
        TLabeledEdit *LabeledEdit24;
        TLabeledEdit *LabeledEdit25;
        TLabeledEdit *LabeledEdit26;
        TLabeledEdit *LabeledEdit27;
        TLabeledEdit *LabeledEdit28;
        TLabeledEdit *LabeledEdit29;
        TButton *Button1;
        TTabSheet *TabSheet10;
        TRadioButton *RadioButton5;
        TTimer *TimerJoyStick;
        TIdUDPClient *IdUDPClient1;
        TTimer *Timer1;
        TGroupBox *GroupBox13;
        TLabeledEdit *LabeledEdit30;
        TLabeledEdit *LabeledEdit31;
        TCheckBox *CheckBox10;
        TPageControl *PageControl4;
        TTabSheet *TabSheet11;
        TTabSheet *TabSheet12;
        TPanel *Panel7;
        TPaintBox *PaintBox2;
        TCheckBox *CheckBox9;
        TLabel *Label7;
        TCSpinEdit *CSpinEdit8;
        TLabel *Label20;
        TCSpinEdit *CSpinEdit9;
        TLabel *Label21;
        TCSpinEdit *CSpinEdit10;
        TLabel *Label22;
        TCSpinEdit *CSpinEdit11;
        TLabel *Label23;
        TCSpinEdit *CSpinEdit12;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TEdit *Edit4;
        TLabel *Label24;
        TCSpinEdit *CSpinEdit13;
        void __fastcall PaintBox1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall PaintBox1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall PaintBox1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall ToolButton3Click(TObject *Sender);
        void __fastcall ToolButton4Click(TObject *Sender);
        void __fastcall ToolButton6Click(TObject *Sender);
        void __fastcall ToolButton7Click(TObject *Sender);
        void __fastcall ToolButton9Click(TObject *Sender);
        void __fastcall ToolButton10Click(TObject *Sender);
        void __fastcall ToolButton1Click(TObject *Sender);
        void __fastcall ToolButton2Click(TObject *Sender);
        void __fastcall TimerCtrlSimuTimer(TObject *Sender);
        void __fastcall TimerCommTimer(TObject *Sender);
        void __fastcall BtnRobotResetClick(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall AccSensorTimerTimer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall TimerJoyStickTimer(TObject *Sender);
        void __fastcall CheckBox9Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
        CCtrlSystem        __CtrlSystem;
        CRobotImage        __RobotImage;
        CRobotCommPkg      __RobotCommPkg;
        CAccSensor         __AccSensor;
        TDateTime          __AccLstTime;
private:
        HANDLE             __hFSXDll;
        HANDLE             __hComm;
        HANDLE             __hAccComm;
private:
        bool               __Initialized;
        bool               __MouseDown;
        int                __MouseX;
        int                __MouseY;
        float              __LstDx;
        float              __LstDy;
private:
        Graphics::TBitmap *__BmpJoyStick;
private:
        typedef bool      (*INIT_FSX_CONNECTION)(void);
        typedef CPlaneAcc (*GET_PLANE_ACC)(void);
        INIT_FSX_CONNECTION InitFSXConnection;
        GET_PLANE_ACC       GetPlaneAcceleration;
private:
        void    InitFSX(void);
        HANDLE  InitComm(AnsiString Comm, int BaudRate);
        bool    SendOrder(CRobotCommPkg &CommPkg);
        void    SendPosEurlarOrder(int ID, int Value);
        void    ShowRobotStatus(CRobotCommPkg &CommPkg);
        double  Rad2Degree(double Rad){return 180.0 * Rad / M_PI;}
private:
        void  SendPosEurlarOrder(void);
        void  SendMotionSimuOrder(void);
        void  SendJackLengthOrder(void);
        void  SendStableCtrlOrder(void);
        void  SendJuneBugCtrlOrder(void);
private:
        void  InitJoyStick(void);
        void  RefreshJoyStickIndicate(float Dx, float Dy, float Step);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
// 2020.07.22：修正了坐标系，增加了伺服电缸到达端点时的弹性减速控制。仿真模拟通过。 