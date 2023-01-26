//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "CSPIN.h"
#include <ComCtrls.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "StuartWorkSpace.h"
#include "CubeSpace.h"
#include "SpaceFile.h"
#include <ToolWin.hpp>
#include "Space3DView.h"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel4;
        TSaveDialog *SaveDialog1;
        TOpenDialog *OpenDialog1;
        TGroupBox *GroupBox5;
        TLabel *Label13;
        TEdit *Edit1;
        TLabel *Label17;
        TEdit *Edit2;
        TLabel *Label18;
        TEdit *Edit3;
        TButton *Button4;
        TLabel *Label19;
        TEdit *Edit4;
        TEdit *Edit5;
        TLabel *Label20;
        TEdit *Edit6;
        TLabel *Label21;
        TLabel *Label22;
        TEdit *Edit7;
        TLabel *Label23;
        TEdit *Edit8;
        TSavePictureDialog *SavePictureDialog1;
        TImageList *ImageList1;
        TPanel *Panel2;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPaintBox *PaintBox1;
        TCoolBar *CoolBar2;
        TToolBar *ToolBar2;
        TPanel *Panel12;
        TToolButton *ToolButton18;
        TToolButton *ToolButton19;
        TPanel *Panel13;
        TToolButton *ToolButton20;
        TToolButton *ToolButton21;
        TPanel *Panel14;
        TToolButton *ToolButton22;
        TToolButton *ToolButton23;
        TTabSheet *TabSheet2;
        TChart *Chart1;
        TFastLineSeries *Series1;
        TCoolBar *CoolBar3;
        TToolBar *ToolBar3;
        TPanel *Panel7;
        TCSpinEdit *CSpinEdit22;
        TPanel *Panel8;
        TCSpinEdit *CSpinEdit23;
        TToolButton *ToolButton6;
        TToolButton *ToolButton7;
        TCoolBar *CoolBar1;
        TToolBar *ToolBar1;
        TPanel *Panel3;
        TCSpinEdit *CSpinEdit17;
        TCSpinEdit *CSpinEdit18;
        TToolButton *ToolButton3;
        TLabel *Label15;
        TEdit *Edit9;
        TBevel *Bevel4;
        TBevel *Bevel5;
        TPageControl *PageControl2;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
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
        TGroupBox *GroupBox2;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TCSpinEdit *CSpinEdit7;
        TCSpinEdit *CSpinEdit8;
        TCSpinEdit *CSpinEdit9;
        TCSpinEdit *CSpinEdit10;
        TCSpinEdit *CSpinEdit11;
        TCSpinEdit *CSpinEdit12;
        TGroupBox *GroupBox4;
        TButton *Button1;
        TButton *Button2;
        TButton *Button7;
        TBevel *Bevel3;
        TBevel *Bevel6;
        TBevel *Bevel7;
        TGroupBox *GroupBox3;
        TLabel *Label14;
        TButton *Button3;
        TButton *Button5;
        TButton *Button6;
        TCSpinEdit *CSpinEdit19;
        TBevel *Bevel1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton4;
        TColorBox *ColorBox1;
        TPanel *Panel1;
        TPanel *Panel5;
        TColorBox *ColorBox2;
        TCheckBox *CheckBox1;
        TButton *Button8;
        TButton *Button9;
        TButton *Button10;
        TToolButton *ToolButton5;
        TCheckBox *CheckBox2;
        TToolButton *ToolButton8;
        TCheckBox *CheckBox3;
        TBevel *Bevel2;
        TLabel *Label16;
        TEdit *Edit10;
        TLabel *Label24;
        TEdit *Edit11;
        TLabel *Label25;
        TEdit *Edit12;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TToolBar *ToolBar4;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox8;
        TCheckBox *CheckBox9;
        TCheckBox *CheckBox10;
        TTabSheet *TabSheet5;
        TGroupBox *GroupBox6;
        TLabel *Label26;
        TCSpinEdit *CSpinEdit13;
        TButton *Button11;
        TLabel *Label27;
        TCSpinEdit *CSpinEdit14;
        void __fastcall CSpinEdit1Change(TObject *Sender);
        void __fastcall CSpinEdit13Change(TObject *Sender);
        void __fastcall Chart1AfterDraw(TObject *Sender);
        void __fastcall CSpinEdit14Change(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ToolButton5Click(TObject *Sender);
        void __fastcall ToolButton6Click(TObject *Sender);
        void __fastcall ToolButton7Click(TObject *Sender);
        void __fastcall ToolButton8Click(TObject *Sender);
        void __fastcall ToolButton9Click(TObject *Sender);
        void __fastcall ToolButton10Click(TObject *Sender);
        void __fastcall PaintBox1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall PaintBox1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall PaintBox1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall PaintBox1Paint(TObject *Sender);
        void __fastcall CSpinEdit17Change(TObject *Sender);
        void __fastcall ToolButton1Click(TObject *Sender);
        void __fastcall ToolButton2Click(TObject *Sender);
        void __fastcall ColorBox1Change(TObject *Sender);
        void __fastcall ColorBox2Change(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall CheckBox7Click(TObject *Sender);
        void __fastcall CheckBox9Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
private:	// User declarations        
        bool               __IniLoading;
        CStuartWorkSpace   __RobotSpace;
        CJuneBugWorkSpace  __JuneBugSpace;
        CSpaceFile         __SpaceFile;
        CWorkSpace        *__WorkSpace;
        CSpace3DView       __Space3DView;
        CCubeSpace         __CubeSpace;
private:
        bool               __MouseDown;
        int                __MouseX;
        int                __MouseY;
private:
        void SaveRobotParams(void);
        void LoadRobotParams(void);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
// 修改记录
// 2021-06-10：修正了边界搜索和立方体空间优化。边界搜索仍然存在问题。
// 2021-06-11：解决了边界搜索问题。
#endif
 