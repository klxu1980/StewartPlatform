//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "TRangeDlg.h"
#include "GlobalDef.h"
#include <math.h>
#include <vector>
#include <IniFiles.hpp>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner),
          __RobotImage(__CtrlSystem.RobotSimu()),
          __Initialized(false)
{
   TIniFile *IniFile = new TIniFile("并联机器人设计.ini");
   LabeledEdit1->Text = IniFile->ReadString("结构参数", "上平台长臂长度", "2.25");
   LabeledEdit2->Text = IniFile->ReadString("结构参数", "上平台短臂长度", "0.1");
   LabeledEdit5->Text = IniFile->ReadString("结构参数", "下平台长臂长度", "3.5");
   LabeledEdit6->Text = IniFile->ReadString("结构参数", "下平台短臂长度", "0.1");
   LabeledEdit3->Text = IniFile->ReadString("结构参数", "最小杆长",       "6");
   LabeledEdit4->Text = IniFile->ReadString("结构参数", "最大杆长",       "11");
   LabeledEdit7->Text = IniFile->ReadString("结构参数", "连杆直径",       "0.1");
   delete IniFile;

   BtnSettings->Click();

   //__hFSXDll = LoadLibrary("C:\\Program Files (x86)\\Microsoft Games\\Microsoft Flight Simulator X SDK\\SDK\\Core Utilities Kit\\SimConnect SDK\\Samples\\飞行模拟器接口\\FSXDll\\debug\\FSXDll.dll");
   __hFSXDll = LoadLibrary("FSXDll.dll");

   InitFSXConnection    = (INIT_FSX_CONNECTION)GetProcAddress(__hFSXDll, "InitFSXConnection");
   GetPlaneAcceleration = (GET_PLANE_ACC)      GetProcAddress(__hFSXDll, "GetPlaneAcc");

   InitFSXConnection();

   FormResize(NULL);

   Timer1->Enabled = true;
   Timer2->Enabled = true;
   Timer3->Enabled = true;

   ListView3->Items->Clear();
   for(int Row = 0; Row < 6; ++Row)
   {
      TListItem *Item = ListView3->Items->Add();
      Item->Caption = IntToStr(Row + 1);
      for(int Col = 1; Col < ListView3->Columns->Count; ++Col)
         Item->SubItems->Add("");
   }


   // 初始化串口
   __hComm = CreateFile("COM8",                   //打开串口
                        GENERIC_READ | GENERIC_WRITE,   //读写方式
                        0,                              //不能共享
                        NULL,                           //不用安全结构
                        OPEN_EXISTING,                  //打开已存在的设备
                        FILE_FLAG_WRITE_THROUGH,        //同步方式
                        0);                             //无模板

   if((unsigned long)__hComm != 0xFFFFFFFF)
   {
      //设置串口属性
      DCB CommDCB;
      if(GetCommState(__hComm, &CommDCB))
      {
         CommDCB.BaudRate = 9600;
         CommDCB.ByteSize = 8;
         CommDCB.Parity   = 0;
         CommDCB.StopBits = 0;

         if(!SetCommState(__hComm, &CommDCB))
            throw Exception("设置串口属性错误!");
      }
      else
         throw Exception("读取串口属性错误!");

      //设置超时
      COMMTIMEOUTS CommTimeouts;
      GetCommTimeouts(__hComm, &CommTimeouts);
      CommTimeouts.ReadIntervalTimeout        = MAXDWORD;
      CommTimeouts.ReadTotalTimeoutMultiplier = 0;
      CommTimeouts.ReadTotalTimeoutConstant   = 0;
      SetCommTimeouts(__hComm, &CommTimeouts);
   }
   else
      Application->MessageBox("无法打开串口", "错误", MB_OK | MB_ICONERROR);

   __Initialized = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   __RobotImage.Initialize(GetDC(Handle));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
   //if(__CtrlSystem.Initialized())
   if(__Initialized)
      __RobotImage.Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
   int ViewWidth = min(PaintBox1->Width, PaintBox1->Height);

   __RobotImage.Resize(PaintBox1->Left + (PaintBox1->Width  - ViewWidth) / 2,
                       PaintBox1->Top  + (PaintBox1->Height - ViewWidth) / 2,
                       ViewWidth,
                       ViewWidth);
}
//---------------------------------------------------------------------------
// CSpinEdit1Change()
// 设置上平台位姿
//---------------------------------------------------------------------------
void __fastcall TForm1::CSpinEditXChange(TObject *Sender)
{
   if(CSpinEditX->Focused())
      SendPosEurlarOrder(0, CSpinEditX->Value);
   else if(CSpinEditY->Focused())
      SendPosEurlarOrder(1, CSpinEdidY->Value);
   else if(CSpinEditZ->Focused())
      SendPosEurlarOrder(2, CSpinEditZ->Value);
   else if(CSpinEditYaw->Focused())
      SendPosEurlarOrder(3, CSpinEditYaw->Value);
   else if(CSpinEditPitch->Focused())
      SendPosEurlarOrder(4, CSpinEditPitch->Value);
   else if(CSpinEditRoll->Focused())
      SendPosEurlarOrder(5, CSpinEditRoll->Value);



/*
   // 计算上平台运动
   Memo1->Lines->Clear();
   switch(__CtrlSystem.Robot().Move(CSpinEditX->Value * 0.001, CSpinEditY->Value * 0.001, CSpinEditZ->Value * 0.001,
                       CSpinEditYaw->Value, CSpinEditPitch->Value, CSpinEditRoll->Value))
   {
   case msOk :
      Memo1->Lines->Add("工作正常");
      break;
   case msJackOutofRange :
      Memo1->Lines->Add("连杆长度超出范围");
      break;
   case msSingular :
      Memo1->Lines->Add("遇到奇异点");
      break;
   case msJackCollision :
      Memo1->Lines->Add("连杆相碰");
      break;
   }

   // 上平台受力计算
   double Force[3]  = {0, 0, -CSpinEdit7->Value};
   double Torque[3] = {0, 0, 0};
   __Robot.CalcForceOfJacks(Force, Torque);

   // 绘制机器人，显示机器人状态
   __RobotImage.Repaint();
   ShowRobotStatus(__Robot);

   // 将连杆长度输出到正向运动学控制页面
   CSpinEdit8->OnChange  = NULL;
   CSpinEdit9->OnChange  = NULL;
   CSpinEdit10->OnChange = NULL;
   CSpinEdit11->OnChange = NULL;
   CSpinEdit12->OnChange = NULL;
   CSpinEdit13->OnChange = NULL;

   CSpinEdit8->Value  = __Robot.Jacks[0].Length * 1000.0 + 0.5;
   CSpinEdit9->Value  = __Robot.Jacks[1].Length * 1000.0 + 0.5;
   CSpinEdit10->Value = __Robot.Jacks[2].Length * 1000.0 + 0.5;
   CSpinEdit11->Value = __Robot.Jacks[3].Length * 1000.0 + 0.5;
   CSpinEdit12->Value = __Robot.Jacks[4].Length * 1000.0 + 0.5;
   CSpinEdit13->Value = __Robot.Jacks[5].Length * 1000.0 + 0.5;

   CSpinEdit8->OnChange   = CSpinEdit8Change;
   CSpinEdit9->OnChange   = CSpinEdit8Change;
   CSpinEdit10->OnChange  = CSpinEdit8Change;
   CSpinEdit11->OnChange  = CSpinEdit8Change;
   CSpinEdit12->OnChange  = CSpinEdit8Change;
   CSpinEdit13->OnChange  = CSpinEdit8Change;
*/
}
//---------------------------------------------------------------------------
// ShowRobotStatus()
//---------------------------------------------------------------------------
void TForm1::ShowRobotStatus(CRobot &Robot)
{
   AnsiString Str;
   /*
   PnlJackLen1->Caption = Str.sprintf("%8.2f, %5.3f", __Robot.Jacks[0].Length * 1000.0, __FollowupCtrl.JackIncrement(0) * 1000.0);
   PnlJackLen2->Caption = Str.sprintf("%8.2f, %5.3f", __Robot.Jacks[1].Length * 1000.0, __FollowupCtrl.JackIncrement(1) * 1000.0);
   PnlJackLen3->Caption = Str.sprintf("%8.2f, %5.3f", __Robot.Jacks[2].Length * 1000.0, __FollowupCtrl.JackIncrement(2) * 1000.0);
   PnlJackLen4->Caption = Str.sprintf("%8.2f, %5.3f", __Robot.Jacks[3].Length * 1000.0, __FollowupCtrl.JackIncrement(3) * 1000.0);
   PnlJackLen5->Caption = Str.sprintf("%8.2f, %5.3f", __Robot.Jacks[4].Length * 1000.0, __FollowupCtrl.JackIncrement(4) * 1000.0);
   PnlJackLen6->Caption = Str.sprintf("%8.2f, %5.3f", __Robot.Jacks[5].Length * 1000.0, __FollowupCtrl.JackIncrement(5) * 1000.0);
   */
   return;

   // 显示上平台铰接点坐标
   Memo1->Lines->Add("");
   Memo1->Lines->Add("连杆坐标及长度");
   for(int i = 0; i < 6; ++i)
   {
      Memo1->Lines->Add("连杆" + IntToStr(i + 1));
      /*
      Memo1->Lines->Add(AnsiString().sprintf("上铰接点坐标：(%5.1f, %5.1f, %5.1f)", __Robot.Jacks[i].UpperJoint[0] * 1000.0,
                                                                                    __Robot.Jacks[i].UpperJoint[1] * 1000.0,
                                                                                    __Robot.Jacks[i].UpperJoint[2] * 1000.0));
      Memo1->Lines->Add(AnsiString().sprintf("下铰接点坐标：(%5.1f, %5.1f, %5.1f)", __Robot.Jacks[i].LowerJoint[0] * 1000.0,
                                                                                    __Robot.Jacks[i].LowerJoint[1] * 1000.0,
                                                                                    __Robot.Jacks[i].LowerJoint[2] * 1000.0));
      */
      Memo1->Lines->Add(AnsiString().sprintf("连杆长度：%8.1f, 丝杠伸出量：%8.1f",
                        __CtrlSystem.Robot().Jacks[i].Length * 1000.0, __CtrlSystem.Robot().Jacks[i].ServoLength * 1000.0) );
   }

   // 计算胡克铰角度
   /*
   double V[3] = {__Robot.Jacks[0].UpperJoint[0] - __Robot.Jacks[0].LowerJoint[0], __Robot.Jacks[0].UpperJoint[1] - __Robot.Jacks[0].LowerJoint[1], __Robot.Jacks[0].UpperJoint[2] - __Robot.Jacks[0].LowerJoint[2]};
   double SinYZ = V[2] / sqrt(V[1] * V[1] + V[2] * V[2]);
   double AngleYZ = asin(SinYZ) * 180.0 / M_PI;
   Memo1->Lines->Add(AnsiString().sprintf("YZ平面上投影角：%5.2f", AngleYZ));
   */

   /*
      Memo1->Lines->Add("");
      Memo1->Lines->Add("受力分析：");
      for(int i = 0; i < 6; ++i)
         Memo1->Lines->Add(AnsiString().sprintf("连杆%d: %8.5f", i + 1, -JackForce[i]) );
   */

   // 显示连杆受力
   Memo1->Lines->Add("");
   Memo1->Lines->Add("受力分析：");
   for(int i = 0; i < 6; ++i)
      Memo1->Lines->Add(AnsiString().sprintf("连杆%d: %8.5f", i + 1, -__CtrlSystem.Robot().Jacks[i].Force) );
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToolButton6Click(TObject *Sender)
{
   __RobotImage.RotateAroundX(10);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToolButton7Click(TObject *Sender)
{
   __RobotImage.RotateAroundX(-10);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToolButton9Click(TObject *Sender)
{
   __RobotImage.RotateAroundY(10);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToolButton10Click(TObject *Sender)
{
   __RobotImage.RotateAroundY(-10);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToolButton1Click(TObject *Sender)
{
   __RobotImage.RotateAroundZ(10);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToolButton2Click(TObject *Sender)
{
   __RobotImage.RotateAroundZ(-10);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnSettingsClick(TObject *Sender)
{
/*
   TIniFile *IniFile = new TIniFile("并联机器人设计.ini");
   IniFile->WriteInteger("结构参数", "上平台长臂长度", LabeledEdit1->Text.ToInt());
   IniFile->WriteInteger("结构参数", "上平台短臂长度", LabeledEdit2->Text.ToInt());
   IniFile->WriteInteger("结构参数", "下平台长臂长度", LabeledEdit5->Text.ToInt());
   IniFile->WriteInteger("结构参数", "下平台短臂长度", LabeledEdit6->Text.ToInt());
   IniFile->WriteInteger("结构参数", "最小杆长",       LabeledEdit3->Text.ToInt());
   IniFile->WriteInteger("结构参数", "最大杆长",       LabeledEdit4->Text.ToInt());
   IniFile->WriteInteger("结构参数", "连杆直径",       LabeledEdit7->Text.ToInt());
   delete IniFile;

   __CtrlSystem.Robot().SetPlatformSize(LabeledEdit1->Text.ToInt() * 0.001,
                           LabeledEdit2->Text.ToInt() * 0.001,
                           LabeledEdit5->Text.ToInt() * 0.001,
                           LabeledEdit6->Text.ToInt() * 0.001);
   __CtrlSystem.Robot().SetMinMaxJackLength(LabeledEdit3->Text.ToInt() * 0.001,
                               LabeledEdit4->Text.ToInt() * 0.001);
   __CtrlSystem.Robot().SetJackDiameter(LabeledEdit7->Text.ToInt() * 0.001);

   __CtrlSystem.Robot().Zeroed();

   //__CtrlSystem.Robot().Move(

   //__FollowupCtrl.SynchronizeRobot();

   LabeledEdit8->Text = AnsiString().sprintf("%1.1f", __CtrlSystem.Robot().PlatformMinHeight() * 1000.0);
   LabeledEdit9->Text = AnsiString().sprintf("%1.1f", __CtrlSystem.Robot().PlatformMaxHeight() * 1000.0);

   CSpinEditZ->Value = __CtrlSystem.Robot().PlatformMinHeight() * 1000.0 + 0.5;

   CSpinEdit8->Value = LabeledEdit3->Text.ToInt();
   CSpinEdit9->Value = LabeledEdit3->Text.ToInt();
   CSpinEdit10->Value = LabeledEdit3->Text.ToInt();
   CSpinEdit11->Value = LabeledEdit3->Text.ToInt();
   CSpinEdit12->Value = LabeledEdit3->Text.ToInt();
   CSpinEdit13->Value = LabeledEdit3->Text.ToInt();
   */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   __MouseDown = true;
   __MouseX    = X;
   __MouseY    = Y;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   __MouseDown = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
   if(!__MouseDown)
      return;

   int    ViewWidth = min(PaintBox1->Width, PaintBox1->Height);
   double DeltaX = double(X - __MouseX) / ViewWidth;
   double DeltaY = double(Y - __MouseY) / ViewWidth;
   __RobotImage.MoveScreen(DeltaX, DeltaY);

   __MouseX = X;
   __MouseY = Y;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToolButton3Click(TObject *Sender)
{
   __RobotImage.Zoom(1.1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToolButton4Click(TObject *Sender)
{
   __RobotImage.Zoom(0.9);        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CSpinEdit8Change(TObject *Sender)
{
   if(CSpinEdit8->Focused())
      SendJackLengthOrder(0, CSpinEdit8->Value, 20);
   else if(CSpinEdit9->Focused())
      SendJackLengthOrder(1, CSpinEdit9->Value, 20);
   else if(CSpinEdit10->Focused())
      SendJackLengthOrder(2, CSpinEdit10->Value, 20);
   else if(CSpinEdit11->Focused())
      SendJackLengthOrder(3, CSpinEdit11->Value, 20);
   else if(CSpinEdit12->Focused())
      SendJackLengthOrder(4, CSpinEdit12->Value, 20);
   else if(CSpinEdit13->Focused())
      SendJackLengthOrder(5, CSpinEdit13->Value, 20);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToolButton11Click(TObject *Sender)
{
/*
   vector<pair<double, double> > Values;

   for(double Z = 0.0; Z < 20.0; Z += 0.01)
   {
      double Pos[3]    = {0, 0, Z};
      double Eurlar[3] = {0, 0, 0};

      if(__CtrlSystem.Robot().Move(Pos, Eurlar) != msOk)
         continue;

      Values.push_back(pair<double, double>(Z, 0) );
      for(double Pys = 0.0; Pys < 180.0; Pys += 0.1)
      {
         Eurlar[1] = Pys;
         if(__CtrlSystem.Robot().Move(Pos, Eurlar) != msOk)
            break;

         Values.back().second = Pys;
      }
   }

   TRangeDlg *Dlg = new TRangeDlg(NULL);
   Dlg->ShowRange(Values);
   delete Dlg;
*/
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton12Click(TObject *Sender)
{
/*
   vector<pair<double, double> > Values;

   for(double Z = 0.0; Z < 20.0; Z += 0.01)
   {
      double Pos[3]    = {0, 0, Z};
      double Eurlar[3] = {0, 0, 0};

      if(__CtrlSystem.Robot().Move(Pos, Eurlar) != msOk)
         continue;

      Values.push_back(pair<double, double>(Z, 0) );
      for(double Pys = 0.0; Pys < 180.0; Pys += 0.1)
      {
         Eurlar[0] = Pys;
         if(__CtrlSystem.Robot().Move(Pos, Eurlar) != msOk)
            break;

         Values.back().second = Pys* 2;
      }
   }

   TRangeDlg *Dlg = new TRangeDlg(NULL);
   Dlg->ShowRange(Values);
   delete Dlg;
*/
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
   //double X, Y, Z, Yaw, Pitch, Roll;
   //__MotionSimu.GetPlatformPosition(X, Y, Z, Yaw, Pitch, Roll);

   //if(!__CtrlSystem.Initialized())
   if(!__Initialized)
      return;

   __CtrlSystem.Control();
   __RobotImage.Repaint();

   if(ListView2->Items->Count)
   {
      ListView2->Items->Item[0]->SubItems->Strings[0] = AnsiString().sprintf("%8.1f", __CtrlSystem.Robot().PosX() * 1000);
      ListView2->Items->Item[1]->SubItems->Strings[0] = AnsiString().sprintf("%8.1f", __CtrlSystem.Robot().PosY() * 1000);
      ListView2->Items->Item[2]->SubItems->Strings[0] = AnsiString().sprintf("%8.1f", __CtrlSystem.Robot().PosZ() * 1000);
      ListView2->Items->Item[3]->SubItems->Strings[0] = AnsiString().sprintf("%8.1f", __CtrlSystem.Robot().PosYaw());
      ListView2->Items->Item[4]->SubItems->Strings[0] = AnsiString().sprintf("%8.1f", __CtrlSystem.Robot().PosPitch());
      ListView2->Items->Item[5]->SubItems->Strings[0] = AnsiString().sprintf("%8.1f", __CtrlSystem.Robot().PosRoll());
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
   if(RadioButton1->Checked)
      SendMotionSimuOrder();
   else if(RadioButton2->Checked)
   {
   }
   else if(RadioButton3->Checked)
   {
   }
}
//---------------------------------------------------------------------------
// SendOrder()
//---------------------------------------------------------------------------
bool TForm1::SendOrder(char *Order)
{
   short CRC = CalcCRC(Order, 7);
   Order[7] = CRC;
   Order[8] = CRC >> 8;

   for(int i = 0; i < 9; ++i)
      __CtrlSystem.RcvCommByte(Order[i]);

   if(__hComm)
   {
      DWORD Size;
      WriteFile(__hComm, Order, 9, &Size, NULL);

      for(int i = 0; i < 10; ++i)
      {
         Sleep(10);

         char  Fdk[4] = {0, 0, 0, 0};
         DWORD FdkLen;
         if(ReadFile(__hComm, Fdk, 4, &FdkLen, NULL) && Fdk[0] == 0x55)
         {
            StatusBar1->Panels->Items[0]->Text = "通信成功";
            return true;
         }
      }
   }
   StatusBar1->Panels->Items[0]->Text = "通信失败";
   return false;
}
//---------------------------------------------------------------------------
// SendResetOrder()
//---------------------------------------------------------------------------
void TForm1::SendResetOrder(void)
{
   char Order[9] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
   SendOrder(Order);
}
//---------------------------------------------------------------------------
// SendJackLengthOrder()
//---------------------------------------------------------------------------
void TForm1::SendJackLengthOrder(int JackID, int Length, int Speed)
{
   char Order[9] = {2, JackID, Length, Length >> 8, Speed, Speed >> 8, 0, 0, 0};
   SendOrder(Order);
}
//---------------------------------------------------------------------------
// SendPosEurlarOrder()
//---------------------------------------------------------------------------
void TForm1::SendPosEurlarOrder(int ID, int Value)
{
   char Order[9] = {3, ID, Value, Value >> 8, 0, 0, 0, 0, 0};
   SendOrder(Order);
}
//---------------------------------------------------------------------------
// SendMotionSimuOrder()
//---------------------------------------------------------------------------
void TForm1::SendMotionSimuOrder(float AccX, float AccY, float AccZ, float AccYaw, float AccPitch, float AccRoll)
{
   char Order[9] = {4};
   Order[1]  = char(Clip(AccX,     MAX_LINEAR_ACC) * 100 / MAX_LINEAR_ACC);
   Order[2]  = char(Clip(AccY,     MAX_LINEAR_ACC) * 100 / MAX_LINEAR_ACC);
   Order[3]  = char(Clip(AccZ,     MAX_LINEAR_ACC) * 100 / MAX_LINEAR_ACC);
   Order[4]  = char(Clip(AccYaw,   MAX_ROTARY_ACC) * 100 / MAX_ROTARY_ACC);
   Order[5]  = char(Clip(AccPitch, MAX_ROTARY_ACC) * 100 / MAX_ROTARY_ACC);
   Order[6]  = char(Clip(AccRoll,  MAX_ROTARY_ACC) * 100 / MAX_ROTARY_ACC);

   SendOrder(Order);
}
//---------------------------------------------------------------------------
// CalcCRC()
//---------------------------------------------------------------------------
unsigned short TForm1::CalcCRC(unsigned char *Buffer, int Count)
{
   unsigned short CRC = 0xFFFF;

   for(int i = 0; i < Count; ++i)
   {
      CRC ^= Buffer[i];

      for(int j = 0; j < 8; ++j)
      {
         if(CRC & 1)
         {
            CRC >>= 1;
            CRC  ^= 0xA001;
         }
         else
         {
            CRC >>= 1;
         }
      }
   }
   return CRC;
}
//---------------------------------------------------------------------------
void TForm1::SendMotionSimuOrder(void)
{
   CPlaneAcc Acc;
   if(CheckBox1->Checked)
   {
      Acc = GetPlaneAcceleration();
      Acc.AccYaw   = Rad2Degree(Acc.AccYaw);
      Acc.AccPitch = Rad2Degree(Acc.AccPitch);
      Acc.AccRoll  = Rad2Degree(Acc.AccRoll);
   }
   else
   {
      // 注意：FSX中，Z轴是航向，X轴是机翼方向，Y轴是高度方向
      Acc.AccZ = CSpinEdit1->Value * 0.1;
      Acc.AccX = CSpinEdit2->Value * 0.1;
      Acc.AccY = CSpinEdit3->Value * 0.1;
      Acc.AccYaw   = CSpinEdit4->Value * 0.1;
      Acc.AccPitch = CSpinEdit5->Value * 0.1;
      Acc.AccRoll  = CSpinEdit6->Value * 0.1;
   }

   if(ListView1->Items->Count)
   {
      ListView1->Items->Item[0]->SubItems->Strings[0] = AnsiString().sprintf("%8.4f", Acc.AccZ);
      ListView1->Items->Item[1]->SubItems->Strings[0] = AnsiString().sprintf("%8.4f", Acc.AccX);
      ListView1->Items->Item[2]->SubItems->Strings[0] = AnsiString().sprintf("%8.4f", Acc.AccY);
      ListView1->Items->Item[3]->SubItems->Strings[0] = AnsiString().sprintf("%8.4f", Acc.AccYaw);
      ListView1->Items->Item[4]->SubItems->Strings[0] = AnsiString().sprintf("%8.4f", Acc.AccPitch);
      ListView1->Items->Item[5]->SubItems->Strings[0] = AnsiString().sprintf("%8.4f", Acc.AccRoll);
   }

   SendMotionSimuOrder(Acc.AccZ, Acc.AccX, Acc.AccY, Acc.AccYaw, Acc.AccPitch, Acc.AccRoll);
}
//---------------------------------------------------------------------------
void TForm1::SendJackLengthOrder(void)
{
   if(CSpinEdit8->Focused())
      SendJackLengthOrder(0, CSpinEdit8->Value, 20);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
   float Z = __CtrlSystem.Robot().CalcPlatformHeight(0.844);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
   double Dir[6] = {0, 0, 0, 0, 0, -1};
   double L = __CtrlSystem.RobotRangeFromCenter(Dir);
   Edit1->Text = FloatToStr(L);        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnRobotResetClick(TObject *Sender)
{
   SendResetOrder();
}
//----------------------------------------------------------------------------
double TForm1::Clip(double Value, double Range)
{
   if(Value > Range)
      return Range;
   else if(Value < -Range)
      return -Range;
   else
      return Value;
}
