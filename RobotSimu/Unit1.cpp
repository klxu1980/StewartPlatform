//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "RobotBasic.h"
#include "PlaneData.h"
#include <IniFiles.hpp>
#include <Mmsystem.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner),
          __Initialized(false),
          __RobotImage(__CtrlSystem.Robot()),
          __hComm(0),
          __hAccComm(0)
{
   //InitFSX();

   FormResize(NULL);

   EditMinZ->Text = AnsiString().sprintf("%1.3f", __CtrlSystem.Robot().PlatformMinHeight());
   EditMaxZ->Text = AnsiString().sprintf("%1.3f", __CtrlSystem.Robot().PlatformMaxHeight());

   __Initialized = true;
   TimerCtrlSimu->Enabled = true;

   // 运动模拟参数
   if(FileExists("MotionCtrlParams.dat") )
   {
   CMotionSimuParams Params;
   TStream *Stream = new TFileStream("MotionCtrlParams.dat", fmOpenRead);
   Stream->ReadBuffer(&Params, sizeof(Params));
   delete Stream;

   LabeledEdit5->Text  = AnsiString().sprintf("%1.2f", Params.XMax);
   LabeledEdit6->Text  = AnsiString().sprintf("%1.2f", Params.SpdXMax);
   LabeledEdit27->Text = AnsiString().sprintf("%1.2f", Params.AccXMax);

   LabeledEdit7->Text  = AnsiString().sprintf("%1.2f", Params.YMax);
   LabeledEdit8->Text  = AnsiString().sprintf("%1.2f", Params.SpdYMax);
   LabeledEdit28->Text = AnsiString().sprintf("%1.2f", Params.AccYMax);

   LabeledEdit9->Text  = AnsiString().sprintf("%1.2f", Params.ZMax);
   LabeledEdit10->Text = AnsiString().sprintf("%1.2f", Params.SpdZMax);
   LabeledEdit29->Text = AnsiString().sprintf("%1.2f", Params.AccZMax);

   LabeledEdit11->Text = AnsiString().sprintf("%1.2f", Params.AccPitchMax);
   LabeledEdit12->Text = AnsiString().sprintf("%1.2f", Params.AccPitchSpdMax);

   LabeledEdit13->Text = AnsiString().sprintf("%1.2f", Params.AccRollMax);
   LabeledEdit14->Text = AnsiString().sprintf("%1.2f", Params.AccRollSpdMax);

   LabeledEdit19->Text = AnsiString().sprintf("%1.2f", Params.YawMax);
   LabeledEdit20->Text = AnsiString().sprintf("%1.2f", Params.YawSpdMax);

   LabeledEdit15->Text = AnsiString().sprintf("%1.2f", Params.PitchMax);
   LabeledEdit16->Text = AnsiString().sprintf("%1.2f", Params.PitchSpdMax);

   LabeledEdit17->Text = AnsiString().sprintf("%1.2f", Params.RollMax);
   LabeledEdit18->Text = AnsiString().sprintf("%1.2f", Params.RollSpdMax);

   LabeledEdit21->Text = AnsiString().sprintf("%1.2f", fabs(Params.HighPassX));
   LabeledEdit22->Text = AnsiString().sprintf("%1.2f", fabs(Params.HighPassY));
   LabeledEdit23->Text = AnsiString().sprintf("%1.2f", fabs(Params.HighPassZ));
   LabeledEdit24->Text = AnsiString().sprintf("%1.2f", fabs(Params.HighPassYaw));
   LabeledEdit25->Text = AnsiString().sprintf("%1.2f", fabs(Params.HighPassPitch));
   LabeledEdit26->Text = AnsiString().sprintf("%1.2f", fabs(Params.HighPassRoll));

   CheckBox3->Checked = Params.HighPassX > 0;
   CheckBox4->Checked = Params.HighPassY > 0;
   CheckBox5->Checked = Params.HighPassZ > 0;
   CheckBox6->Checked = Params.HighPassYaw > 0;
   CheckBox7->Checked = Params.HighPassPitch > 0;
   CheckBox8->Checked = Params.HighPassRoll > 0;

   // 发送控制参数
   __RobotCommPkg.BuildAccCtrlParams(Params);
   //SendOrder(__RobotCommPkg);
   }

   InitJoyStick();
}
//---------------------------------------------------------------------------
void TForm1::InitFSX(void)
{
   //__hFSXDll = LoadLibrary("C:\\Program Files (x86)\\Microsoft Games\\Microsoft Flight Simulator X SDK\\SDK\\Core Utilities Kit\\SimConnect SDK\\Samples\\飞行模拟器接口\\FSXDll\\debug\\FSXDll.dll");
   __hFSXDll = LoadLibrary("FSXDll.dll");

   InitFSXConnection    = (INIT_FSX_CONNECTION)GetProcAddress(__hFSXDll, "InitFSXConnection");
   GetPlaneAcceleration = (GET_PLANE_ACC)      GetProcAddress(__hFSXDll, "GetPlaneAcc");

   InitFSXConnection();
   
}
//---------------------------------------------------------------------------
HANDLE TForm1::InitComm(AnsiString Comm, int BaudRate)
{
   // 初始化串口
   HANDLE handle = CreateFile(Comm.c_str(),                   //打开串口
                        GENERIC_READ | GENERIC_WRITE,   //读写方式
                        0,                              //不能共享
                        NULL,                           //不用安全结构
                        OPEN_EXISTING,                  //打开已存在的设备
                        FILE_FLAG_WRITE_THROUGH,        //同步方式
                        0);                             //无模板

   if((unsigned long)handle != 0xFFFFFFFF)
   {
      //设置串口属性
      DCB CommDCB;
      if(GetCommState(handle, &CommDCB))
      {
         CommDCB.BaudRate = BaudRate;
         CommDCB.ByteSize = 8;
         CommDCB.Parity   = 0;
         CommDCB.StopBits = 0;

         if(!SetCommState(handle, &CommDCB))
         {
            Application->MessageBox("设置串口属性错误!", "错误", MB_OK | MB_ICONERROR);
            handle = 0;
         }
      }
      else
      {
         Application->MessageBox("读取串口属性错误!", "错误", MB_OK | MB_ICONERROR);
         handle = 0;
      }

      //设置超时
      COMMTIMEOUTS CommTimeouts;
      GetCommTimeouts(handle, &CommTimeouts);
      CommTimeouts.ReadIntervalTimeout        = MAXDWORD;
      CommTimeouts.ReadTotalTimeoutMultiplier = 0;
      CommTimeouts.ReadTotalTimeoutConstant   = 0;
      SetCommTimeouts(handle, &CommTimeouts);
   }
   else
   {
      Application->MessageBox("无法打开串口", "错误", MB_OK | MB_ICONERROR);
      handle = 0;
   }

   return handle;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   __RobotImage.Initialize(GetDC(Handle));
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
   if(RadioButton2->Checked)
   {
      CSpinEditX->Value = (X - PaintBox1->Width / 2) * 0.5;
      CSpinEditY->Value = -(Y - PaintBox1->Height / 2) * 0.5;
   }
   
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
void __fastcall TForm1::FormPaint(TObject *Sender)
{
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
void __fastcall TForm1::TimerCtrlSimuTimer(TObject *Sender)
{            
   if(!__Initialized)
      return;

   __CtrlSystem.Control();
   __RobotImage.Repaint();

   // 显示正向迭代次数
   Panel3->Caption = AnsiString().sprintf("  正向迭代次数: %d", __CtrlSystem.Robot().RobotFKP.IterCount);

   // 显示机器人计算结果
   if(ListViewPostures->Items->Count)
   {
      ListViewPostures->Items->Item[0]->SubItems->Strings[0] = AnsiString().sprintf("%8.3f", __CtrlSystem.Robot().PosX() * 1000);
      ListViewPostures->Items->Item[1]->SubItems->Strings[0] = AnsiString().sprintf("%8.3f", __CtrlSystem.Robot().PosY() * 1000);
      ListViewPostures->Items->Item[2]->SubItems->Strings[0] = AnsiString().sprintf("%8.3f", __CtrlSystem.Robot().PosZ() * 1000);
      ListViewPostures->Items->Item[3]->SubItems->Strings[0] = AnsiString().sprintf("%8.3f", __CtrlSystem.Robot().PosYaw());
      ListViewPostures->Items->Item[4]->SubItems->Strings[0] = AnsiString().sprintf("%8.3f", __CtrlSystem.Robot().PosPitch());
      ListViewPostures->Items->Item[5]->SubItems->Strings[0] = AnsiString().sprintf("%8.3f", __CtrlSystem.Robot().PosRoll());

      ListViewPostures->Items->Item[0]->SubItems->Strings[1] = AnsiString().sprintf("%8.3f", __RobotImage.Robot()->UpperPos[0] * 1000);
      ListViewPostures->Items->Item[1]->SubItems->Strings[1] = AnsiString().sprintf("%8.3f", __RobotImage.Robot()->UpperPos[1] * 1000);
      ListViewPostures->Items->Item[2]->SubItems->Strings[1] = AnsiString().sprintf("%8.3f", __RobotImage.Robot()->UpperPos[2] * 1000);
      ListViewPostures->Items->Item[3]->SubItems->Strings[1] = AnsiString().sprintf("%8.3f", __RobotImage.Robot()->UpperEuler[0]);
      ListViewPostures->Items->Item[4]->SubItems->Strings[1] = AnsiString().sprintf("%8.3f", __RobotImage.Robot()->UpperEuler[1]);
      ListViewPostures->Items->Item[5]->SubItems->Strings[1] = AnsiString().sprintf("%8.3f", __RobotImage.Robot()->UpperEuler[2]);
   }
}
//---------------------------------------------------------------------------
// SendOrder()
//---------------------------------------------------------------------------
bool TForm1::SendOrder(CRobotCommPkg &CommPkg)
{
   // 将指令发送到模拟试验对象中
   for(int i = 0; i < CommPkg.CtrlOrderSize(); ++i)
      __CtrlSystem.RcvCommandByte(CommPkg.CtrlOrder[i]);

   if(__hComm == 0)
      return false;

   // 向实际控制硬件发送指令
   if((unsigned long)__hComm != 0xFFFFFFFF)
   {
      // 发送指令
      DWORD Size;
      WriteFile(__hComm, CommPkg.CtrlOrder, CommPkg.CtrlOrderSize(), &Size, NULL);

      // 发送后等待应答
      unsigned char FdkBuffer[48];
      int  FdkCnt = 0;
      for(int i = 0; i < 10; ++i)
      {
         Sleep((unsigned int)10);

         unsigned char Fdk[48];
         DWORD RcvLen;
         ReadFile(__hComm, Fdk, 48, &RcvLen, NULL);

         for(int m = 0; m < RcvLen; ++m)
            if(__RobotCommPkg.ReceiveFdkStatus(Fdk[m]))
            {
               ShowRobotStatus(__RobotCommPkg);

               StatusBar1->Panels->Items[0]->Text = "通信成功";
               return true;
            }
      }
      StatusBar1->Panels->Items[0]->Text = "通信失败";
   }
   else
      StatusBar1->Panels->Items[0]->Text = "串口未打开";

   return false;
}
//---------------------------------------------------------------------------
void TForm1::ShowRobotStatus(CRobotCommPkg &CommPkg)
{
   // 显示限位状态
   char SwitchLower, SwitchUpper, JackMin, JackMax;
   CommPkg.GetLmtSwitchStatus(SwitchLower, SwitchUpper, JackMin, JackMax);

   TShape *Switches[4][6] = {Shape19, Shape20, Shape21, Shape22, Shape23, Shape24,
                             Shape13, Shape14, Shape15, Shape16, Shape17, Shape18,
                             Shape7,  Shape8,  Shape9,  Shape10, Shape11, Shape12,
                             Shape1,  Shape2,  Shape3,  Shape4,  Shape5,  Shape6
                                        };
   for(int i = 0; i < 6; ++i)
   {
      Switches[0][i]->Brush->Color = (SwitchLower & (0x01 << i))? clLime : clWhite;   // 下限位开关
      Switches[1][i]->Brush->Color = (JackMin & (0x01 << i))? clLime : clWhite;   // 下运动极限
      Switches[2][i]->Brush->Color = (JackMax & (0x01 << i))? clLime : clWhite;   // 上限位开关
      Switches[3][i]->Brush->Color = (SwitchUpper & (0x01 << i))? clLime : clWhite;   // 上运动极限
   }

   // 显示电缸长度
   if(ListView2->Items->Count)
   {
      float JackLength[6];
      CommPkg.GetJackLength(JackLength);

      for(int i = 0; i < 6; ++i)
         ListView2->Items->Item[i]->SubItems->Strings[0] = AnsiString().sprintf("%1.1f", JackLength[i] * 1000.0);

      /*
                  // 显示运动增量
                  for(int i = 0; i < 6; ++i)
                  {
                     int Length = FdkBuffer[17 + i * 2] | (FdkBuffer[18 + i * 2] << 8);
                     ListView2->Items->Item[i]->SubItems->Strings[1] = IntToStr(Length);
                  }
      */
   }
}
//---------------------------------------------------------------------------
// SendPosEurlarOrder()
//---------------------------------------------------------------------------
void TForm1::SendPosEurlarOrder(int ID, int Value)
{
   //char Order[9] = {3, ID, Value, Value >> 8, 0, 0, 0, 0, 0};
   //SendOrder(Order);
}
//---------------------------------------------------------------------------
void TForm1::SendPosEurlarOrder(void)
{
   __RobotCommPkg.BuildPosCtrlOrder(CSpinEditX->Value * 0.001,
                                    CSpinEditY->Value * 0.001,
                                    CSpinEditZ->Value * 0.001,
                                    CSpinEditYaw->Value * 0.1,
                                    CSpinEditPitch->Value * 0.1,
                                    CSpinEditRoll->Value * 0.1);
   SendOrder(__RobotCommPkg);
}
//---------------------------------------------------------------------------
void TForm1::SendMotionSimuOrder(void)
{
   CPlaneAcc Acc;
   if(CheckBoxFSXCtrl->Checked)
   {
      // 注意：FSX中，Z轴是航向，X轴是机翼方向，Y轴是高度方向
      CPlaneAcc A = GetPlaneAcceleration();
      Acc.AccX = A.AccX / 2;
      Acc.AccY = A.AccZ / 2;
      Acc.AccZ = A.AccY / 2;
      //Acc.AccYaw   = Rad2Degree(Acc.AccYaw);
      //Acc.AccPitch = Rad2Degree(Acc.AccPitch);
      //Acc.AccRoll  = Rad2Degree(Acc.AccRoll);
   }
   else
   {
      // 依照机器人的坐标系给出加速度
      Acc.AccX = CSpinEdit1->Value * 0.1;
      Acc.AccY = CSpinEdit2->Value * 0.1;
      Acc.AccZ = CSpinEdit3->Value * 0.1;
      Acc.AccYaw   = CSpinEdit4->Value;
      Acc.AccPitch = CSpinEdit5->Value;
      Acc.AccRoll  = CSpinEdit6->Value;
   }

   __RobotCommPkg.BuildAccCtrlOrder(Acc.AccX, Acc.AccY, Acc.AccZ, Acc.AccYaw, Acc.AccPitch, Acc.AccRoll);
   SendOrder(__RobotCommPkg);

   if(ListView1->Items->Count)
   {
      ListView1->Items->Item[0]->SubItems->Strings[0] = AnsiString().sprintf("%8.4f", Acc.AccX);
      ListView1->Items->Item[1]->SubItems->Strings[0] = AnsiString().sprintf("%8.4f", Acc.AccY);
      ListView1->Items->Item[2]->SubItems->Strings[0] = AnsiString().sprintf("%8.4f", Acc.AccZ);
      ListView1->Items->Item[3]->SubItems->Strings[0] = AnsiString().sprintf("%8.4f", Acc.AccYaw);
      ListView1->Items->Item[4]->SubItems->Strings[0] = AnsiString().sprintf("%8.4f", Acc.AccPitch);
      ListView1->Items->Item[5]->SubItems->Strings[0] = AnsiString().sprintf("%8.4f", Acc.AccRoll);
   }

   //SendMotionSimuOrder(Acc.AccZ, Acc.AccX, Acc.AccY, Acc.AccYaw, Acc.AccPitch, Acc.AccRoll);
}
//---------------------------------------------------------------------------
void TForm1::SendJackLengthOrder(void)
{
   TCSpinEdit *Edit[6] = {CSpinEditL1, CSpinEditL2, CSpinEditL3, CSpinEditL4, CSpinEditL5, CSpinEditL6};
   for(int i = 0; i < 6; ++i)
      if(Edit[i]->Focused())
      {
         __RobotCommPkg.BuildJackCtrlOrder(i, Edit[i]->Value * 0.001, 0.02);
         SendOrder(__RobotCommPkg);
      }
}
//---------------------------------------------------------------------------
void TForm1::SendStableCtrlOrder(void)
{
   __RobotCommPkg.BuildStableCtrlOrder();
   SendOrder(__RobotCommPkg);   
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerCommTimer(TObject *Sender)
{
   if(RadioButton1->Checked)
      SendMotionSimuOrder();
   else if(RadioButton2->Checked)
      SendPosEurlarOrder();
   else if(RadioButton3->Checked)
      SendJackLengthOrder();
   else if(RadioButton4->Checked)
      SendStableCtrlOrder();
   else if(RadioButton5->Checked)
      SendJuneBugCtrlOrder();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnRobotResetClick(TObject *Sender)
{
   __RobotCommPkg.BuildResetOrder();
   SendOrder(__RobotCommPkg);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
   if(CheckBox1->Checked)
      __hComm = InitComm(ComboBox1->Text, UART3_BAUD_RATE);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
   if(CheckBox2->Checked)
      __hAccComm = InitComm("COM4", 9600);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AccSensorTimerTimer(TObject *Sender)
{                 
   if(__hAccComm)
   {            
      // 发送后等待应答
      unsigned char Fdk[48];
      DWORD RcvLen;
      ReadFile(__hAccComm, Fdk, 48, &RcvLen, NULL);

      for(int i = 0; i < RcvLen; ++i)
      {
         if(__AccSensor.ReceiveValueByte(Fdk[i]) )
         {
            LabeledEdit1->Text = AnsiString().sprintf("%1.3f", __AccSensor.AccX);
            LabeledEdit2->Text = AnsiString().sprintf("%1.3f", __AccSensor.AccY);
            LabeledEdit3->Text = AnsiString().sprintf("%1.3f", __AccSensor.AccZ);
         }

         __CtrlSystem.StableController().AccFdkFwd.ReceiveValueByte(Fdk[i]);
      }
   }
   //__CtrlSystem.StableController().AccFdkFwd.AccY = CSpinEdit7->Value;

   float Second = SecondSpan(__AccLstTime, TDateTime::CurrentDateTime());
   if(Second > 2.0)
   {
      __AccLstTime = TDateTime::CurrentDateTime();
      LabeledEdit4->Text = AnsiString().sprintf("%1.3f", __AccSensor.CommRate(Second));
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   CMotionSimuParams Params;
   Params.XMax    = LabeledEdit5->Text.ToDouble();
   Params.SpdXMax = LabeledEdit6->Text.ToDouble();
   Params.AccXMax = LabeledEdit27->Text.ToDouble();

   Params.YMax    = LabeledEdit7->Text.ToDouble();
   Params.SpdYMax = LabeledEdit8->Text.ToDouble();
   Params.AccYMax = LabeledEdit28->Text.ToDouble();

   Params.ZMax    = LabeledEdit9->Text.ToDouble();
   Params.SpdZMax = LabeledEdit10->Text.ToDouble();
   Params.AccZMax = LabeledEdit29->Text.ToDouble();

   Params.AccPitchMax    = LabeledEdit11->Text.ToDouble();
   Params.AccPitchSpdMax = LabeledEdit12->Text.ToDouble();

   Params.AccRollMax    = LabeledEdit13->Text.ToDouble();
   Params.AccRollSpdMax = LabeledEdit14->Text.ToDouble();

   Params.YawMax    = LabeledEdit19->Text.ToDouble();
   Params.YawSpdMax = LabeledEdit20->Text.ToDouble();

   Params.PitchMax    = LabeledEdit15->Text.ToDouble();
   Params.PitchSpdMax = LabeledEdit16->Text.ToDouble();

   Params.RollMax    = LabeledEdit17->Text.ToDouble();
   Params.RollSpdMax = LabeledEdit18->Text.ToDouble();

   Params.HighPassX     = LabeledEdit21->Text.ToDouble();
   Params.HighPassY     = LabeledEdit22->Text.ToDouble();
   Params.HighPassZ     = LabeledEdit23->Text.ToDouble();
   Params.HighPassYaw   = LabeledEdit24->Text.ToDouble();
   Params.HighPassPitch = LabeledEdit25->Text.ToDouble();
   Params.HighPassRoll  = LabeledEdit26->Text.ToDouble();

   if(!CheckBox3->Enabled)
      Params.HighPassX *= -1;
   if(!CheckBox4->Enabled)
      Params.HighPassY *= -1;
   if(!CheckBox5->Enabled)
      Params.HighPassZ *= -1;
   if(!CheckBox6->Enabled)
      Params.HighPassYaw *= -1;
   if(!CheckBox7->Enabled)
      Params.HighPassPitch *= -1;
   if(!CheckBox8->Enabled)
      Params.HighPassRoll *= -1;

   // 发送控制参数
   __RobotCommPkg.BuildAccCtrlParams(Params);
   SendOrder(__RobotCommPkg);

   // 保存参数
   TStream *Stream = new TFileStream("MotionCtrlParams.dat", fmCreate);
   Stream->WriteBuffer(&Params, sizeof(Params));
   delete Stream;
}
//---------------------------------------------------------------------------
void TForm1::SendJuneBugCtrlOrder(void)
{
   float Dx  = CSpinEdit8->Value * 0.01;
   float Dy  = CSpinEdit9->Value * 0.01;
   float Yaw = CSpinEdit10->Value;
   float Spd = CSpinEdit11->Value * 0.01;
   float XYHeight = CSpinEdit12->Value * 0.001;

   RefreshJoyStickIndicate(Dx, Dy);
   __RobotCommPkg.BuildJuneBugCtrlOrder(Dx, Dy, Yaw, XYHeight, Spd);
   SendOrder(__RobotCommPkg);
}
//---------------------------------------------------------------------------
void TForm1::InitJoyStick(void)
{
   UINT JoyStickNum = joyGetNumDevs();
   if(JoyStickNum == 0)
   {
      GroupBox12->Caption = "摇杆控制(未插入摇杆)";
      CheckBox9->Enabled  = false;
   }

   __BmpJoyStick = new Graphics::TBitmap();
   __BmpJoyStick->Width  = PaintBox2->Width;
   __BmpJoyStick->Height = PaintBox2->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerJoyStickTimer(TObject *Sender)
{
   JOYINFOEX JoyInfo;
   if(joyGetPosEx(JOYSTICKID1, &JoyInfo) == JOYERR_NOERROR)
   {
      float Dx = (int(JoyInfo.dwXpos) - 32767) / 32768.0;
      float Dy = (int(JoyInfo.dwYpos) - 32767) / 32738.0;

      RefreshJoyStickIndicate(Dx, Dy);
      //__RobotCommPkg.BuildJuneBugCtrlOrder(Dx, Dy, 0, DD);
      //SendOrder(__RobotCommPkg);
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox9Click(TObject *Sender)
{
   TimerJoyStick->Enabled = CheckBox9->Checked;
}
//---------------------------------------------------------------------------
void TForm1::RefreshJoyStickIndicate(float Dx, float Dy)
{
   __BmpJoyStick->Canvas->Brush->Color = clBlack;
   __BmpJoyStick->Canvas->Pen->Color   = clLime;
   __BmpJoyStick->Canvas->Pen->Width   = 2;

   __BmpJoyStick->Canvas->FillRect(TRect(0, 0, __BmpJoyStick->Width, __BmpJoyStick->Height));
   __BmpJoyStick->Canvas->MoveTo(__BmpJoyStick->Width / 2, __BmpJoyStick->Height / 2);

   float Step  = max(fabs(Dx), fabs(Dy));
   float XYLen = sqrt(Dx * Dx + Dy * Dy);

   if(XYLen > 0.1)
   {
      int X = Dx * Step * __BmpJoyStick->Width / (2 * XYLen);
      int Y = Dy * Step * __BmpJoyStick->Width / (2 * XYLen);
      __BmpJoyStick->Canvas->LineTo(__BmpJoyStick->Width / 2 + X, __BmpJoyStick->Height / 2 + Y);
   }
   PaintBox2->Canvas->Draw(0, 0, __BmpJoyStick);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
   if(CheckBox10->Checked)
   {
      float DD = sqrt(CSpinEdit8->Value * CSpinEdit8->Value + CSpinEdit9->Value * CSpinEdit9->Value);

      float Dx = 0;
      float Dy = 0;
      if(DD > 0)
      {
         Dx = CSpinEdit8->Value / DD;
         Dy = CSpinEdit9->Value / DD;
      }
      float Yaw      = CSpinEdit10->Value;
      float Step     = CSpinEdit11->Value * 0.01;
      float XYHeight = CSpinEdit12->Value * 0.001;

      float Order[5] = {Dx, Dy, Yaw, Step, XYHeight};
      IdUDPClient1->Host = LabeledEdit30->Text;
      IdUDPClient1->Port = LabeledEdit31->Text.ToInt();
      IdUDPClient1->SendBuffer(Order, sizeof(float) * 5);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
   TimerCommTimer(NULL);        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToolButton12Click(TObject *Sender)
{
   TimerCtrlSimu->Interval = 200;
   TimerComm->Interval = 2000;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton11Click(TObject *Sender)
{
   if(TimerCtrlSimu->Enabled)
   {
      TimerCtrlSimu->Enabled = false;
      TimerComm->Enabled = false;
   }
   else
   {
      TimerCtrlSimu->Enabled = true;
      TimerComm->Enabled = true;
   }
}
//---------------------------------------------------------------------------

