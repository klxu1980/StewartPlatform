//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "BasicCalc.h"
#include <IniFiles.hpp>
#include <Math.hpp>
#include "GlobalDef.h"
#include <values.h>
#include <algorithm>
#include <numeric>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner),
          __CaliStatus(-1)
{
   LoadRobotParams();
   Button7->Click();

   InitComm("COM8");
   ValueList->Strings->Add("电缸1=");
   ValueList->Strings->Add("电缸2=");
   ValueList->Strings->Add("电缸3=");
   ValueList->Strings->Add("电缸4=");
   ValueList->Strings->Add("电缸5=");
   ValueList->Strings->Add("电缸6=");
}
//---------------------------------------------------------------------------
void TForm1::InitComm(AnsiString Comm)
{
   // 初始化串口
   __hComm = CreateFile(Comm.c_str(),                   //打开串口
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
         CommDCB.BaudRate = UART3_BAUD_RATE;
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
}
//---------------------------------------------------------------------------
// SaveRobotParams()
//---------------------------------------------------------------------------
void TForm1::SaveRobotParams(void)
{      
   TIniFile *IniFile = new TIniFile(ExtractFileDir(Application->ExeName) + "\\机器人标定.ini");

   IniFile->WriteInteger("机械参数", "上平台长轴",     CSpinEdit1->Value);
   IniFile->WriteInteger("机械参数", "上平台短轴",     CSpinEdit2->Value);
   IniFile->WriteInteger("机械参数", "上平台铰点高度", CSpinEdit7->Value);

   IniFile->WriteInteger("机械参数", "下平台长轴",     CSpinEdit3->Value);
   IniFile->WriteInteger("机械参数", "下平台短轴",     CSpinEdit4->Value);
   IniFile->WriteInteger("机械参数", "下平台铰点高度", CSpinEdit8->Value);

   IniFile->WriteInteger("机械参数", "电缸最短行程", CSpinEdit5->Value);
   IniFile->WriteInteger("机械参数", "电缸最大行程", CSpinEdit6->Value);

   IniFile->WriteInteger("仪器位姿", "X", CSpinEdit9->Value);
   IniFile->WriteInteger("仪器位姿", "Y", CSpinEdit10->Value);
   IniFile->WriteInteger("仪器位姿", "Z", CSpinEdit15->Value);

   IniFile->WriteInteger("仪器位姿", "Yaw",   CSpinEdit11->Value);
   IniFile->WriteInteger("仪器位姿", "Pitch", CSpinEdit12->Value);
   IniFile->WriteInteger("仪器位姿", "Roll",  CSpinEdit16->Value);

   delete IniFile;
}
//---------------------------------------------------------------------------
// LoadRobotParams()
//---------------------------------------------------------------------------
void TForm1::LoadRobotParams(void)
{
   TIniFile *IniFile = new TIniFile(ExtractFileDir(Application->ExeName) + "\\机器人标定.ini");

   CSpinEdit1->Value = IniFile->ReadInteger("机械参数", "上平台长轴",     0);
   CSpinEdit2->Value = IniFile->ReadInteger("机械参数", "上平台短轴",     0);
   CSpinEdit7->Value = IniFile->ReadInteger("机械参数", "上平台铰点高度", 0);

   CSpinEdit3->Value = IniFile->ReadInteger("机械参数", "上平台长轴",     0);
   CSpinEdit4->Value = IniFile->ReadInteger("机械参数", "下平台短轴",     0);
   CSpinEdit8->Value = IniFile->ReadInteger("机械参数", "下平台铰点高度", 0);

   CSpinEdit5->Value = IniFile->ReadInteger("机械参数", "电缸最短行程", 0);
   CSpinEdit6->Value = IniFile->ReadInteger("机械参数", "电缸最大行程", 0);

   CSpinEdit9->Value = IniFile->ReadInteger("仪器位姿", "X",    0);
   CSpinEdit10->Value = IniFile->ReadInteger("仪器位姿", "Y",   0);
   CSpinEdit15->Value = IniFile->ReadInteger("仪器位姿", "Z",   0);

   CSpinEdit11->Value = IniFile->ReadInteger("仪器位姿", "Yaw",   0);
   CSpinEdit12->Value = IniFile->ReadInteger("仪器位姿", "Pitch", 0);
   CSpinEdit16->Value = IniFile->ReadInteger("仪器位姿", "Roll",  0);

   delete IniFile;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button7Click(TObject *Sender)
{
   SaveRobotParams();

   // 模拟机器人机械参数
   __RobotSimu.Robot.UpperArmLength   = CSpinEdit1->Value * 0.001;
   __RobotSimu.Robot.UpperBaseLength  = CSpinEdit2->Value * 0.001;
   __RobotSimu.Robot.LowerArmLength   = CSpinEdit3->Value * 0.001;

   __RobotSimu.Robot.LowerBaseLength  = CSpinEdit4->Value * 0.001;
   __RobotSimu.Robot.UpperJointHeight = CSpinEdit7->Value * 0.001;
   __RobotSimu.Robot.LowerJointHeight = CSpinEdit8->Value * 0.001;
   
   __RobotSimu.Robot.JackFixedLength  = CSpinEdit5->Value * 0.001;

   // 模拟机器人观测器参数
   __RobotSimu.Observer.MeterPos[0] = CSpinEdit9->Value * 0.001;
   __RobotSimu.Observer.MeterPos[1] = CSpinEdit10->Value * 0.001;
   __RobotSimu.Observer.MeterPos[2] = CSpinEdit15->Value * 0.001;

   __RobotSimu.Observer.MeterEuler[0] = CSpinEdit11->Value;
   __RobotSimu.Observer.MeterEuler[1] = CSpinEdit12->Value;
   __RobotSimu.Observer.MeterEuler[2] = CSpinEdit16->Value;

   // 标定机器人机械参数
   __Calibrator.Robot.UpperArmLength   = CSpinEdit1->Value * 0.001;
   __Calibrator.Robot.UpperBaseLength  = CSpinEdit2->Value * 0.001;
   __Calibrator.Robot.LowerArmLength   = CSpinEdit3->Value * 0.001;

   __Calibrator.Robot.LowerBaseLength  = CSpinEdit4->Value * 0.001;
   __Calibrator.Robot.UpperJointHeight = CSpinEdit7->Value * 0.001;
   __Calibrator.Robot.LowerJointHeight = CSpinEdit8->Value * 0.001;

   __Calibrator.Robot.JackFixedLength  = CSpinEdit5->Value * 0.001;

   __Calibrator.Robot.InitStructureParams();

   // 标定观察器参数
   __Calibrator.Observer.MeterPos[0] = CSpinEdit9->Value * 0.001;
   __Calibrator.Observer.MeterPos[1] = CSpinEdit10->Value * 0.001;
   __Calibrator.Observer.MeterPos[2] = CSpinEdit15->Value * 0.001;

   __Calibrator.Observer.MeterEuler[0] = CSpinEdit11->Value;
   __Calibrator.Observer.MeterEuler[1] = CSpinEdit12->Value;
   __Calibrator.Observer.MeterEuler[2] = CSpinEdit16->Value;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
   __RobotSimu.GenerateSampleByRandom = CheckBox4->Checked;
   __RobotSimu.ServoRange = CSpinEdit6->Value;
   __RobotSimu.GenerateSamples(__Calibrator, CSpinEdit22->Value);

   Memo2->Lines->Add("当前样本数 = " + IntToStr(__Calibrator.CaliDatas.size()));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
   // 试验条件
   __RobotSimu.IgnoreLowerJointErr = CheckBox1->Checked;
   __RobotSimu.IgnoreJackErr       = CheckBox2->Checked;
   __RobotSimu.IgnoreObserveErr    = CheckBox3->Checked;

   // 设定虚拟机器人误差
   __RobotSimu.GenerateRobotErrors(CSpinEdit29->Value);

   // 设定观测器误差
   __RobotSimu.GenerateObserverErrors(CSpinEdit20->Value, CSpinEdit30->Value);

   // 清除标定数据
   __Calibrator.Clear();

   // 显示误差设定
   ListView1->Items->Clear();
   ListView1->Columns->Clear();
   ListView1->Columns->Add()->Caption = "序号";
   for(int i = 0; i < 48; ++i)
      ListView1->Items->Add()->Caption = IntToStr(i + 1);

   ShowCaliResult(__RobotSimu.Robot, __RobotSimu.Observer, ListView1);
   ListView1->Column[1]->Caption = "给定误差";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button9Click(TObject *Sender)
{
   __Calibrator.ResetErrors();

   __Calibrator.IgnoreLowerErr = CheckBox1->Checked;
   __Calibrator.IgnoreJackErr  = CheckBox2->Checked;
   __Calibrator.IgnoreObserver = CheckBox3->Checked;

   bool Ok = __Calibrator.Calibrate(CSpinEdit18->Value);
   ShowCaliResult(__Calibrator.Robot, __Calibrator.Observer, ListView1);

   Memo2->Lines->Add("标定计算结束");
   Memo2->Lines->Add(AnsiString().sprintf("迭代次数 = %d, 最小误差 = %1.5f", __Calibrator.IterCnt, __Calibrator.MinError));
}
//---------------------------------------------------------------------------
void TForm1::ShowCaliResult(CRobot &Robot, CObserver &Observer, TListView *ListView)
{
   TListColumn *Column = ListView->Columns->Add();
   Column->Width = 100;
   Column->Caption = "检测误差";

   // 显示上平台铰接点误差
   for(int i = 0; i < 6; ++i)
      for(int m = 0; m < 3; ++m)
         ListView->Items->Item[i * 3 + m]->SubItems->Add(AnsiString().sprintf("%1.5f", Robot.ErrJointUpper[i][m] * 1000));

   // 显示下平台铰接点误差
   for(int i = 0; i < 6; ++i)
      for(int m = 0; m < 3; ++m)
         ListView->Items->Item[i * 3 + m + 18]->SubItems->Add(AnsiString().sprintf("%1.5f", Robot.ErrJointLower[i][m] * 1000));

   // 显示零点误差
   for(int i = 0; i < 6; ++i)
      ListView->Items->Item[i + 36]->SubItems->Add(AnsiString().sprintf("%1.5f", Robot.ErrJackFixedLen[i] * 1000));

   // 显示观测器误差
   ListView->Items->Item[42]->SubItems->Add(AnsiString().sprintf("%1.5f", Observer.ErrPos[0] * 1000));
   ListView->Items->Item[43]->SubItems->Add(AnsiString().sprintf("%1.5f", Observer.ErrPos[1] * 1000));
   ListView->Items->Item[44]->SubItems->Add(AnsiString().sprintf("%1.5f", Observer.ErrPos[2] * 1000));

   ListView->Items->Item[45]->SubItems->Add(AnsiString().sprintf("%1.5f", Observer.ErrEuler[0]));
   ListView->Items->Item[46]->SubItems->Add(AnsiString().sprintf("%1.5f", Observer.ErrEuler[1]));
   ListView->Items->Item[47]->SubItems->Add(AnsiString().sprintf("%1.5f", Observer.ErrEuler[2]));

   // 计算参数辨识误差
   double AvgErr = 0;
   double MaxErr = -MAXFLOAT;
   if(ListView->Columns->Count > 2)
   {
      int CurCol = ListView->Columns->Count - 2;
      for(int i = 0; i < ListView->Items->Count; ++i)
      {
         double P1 = ListView->Items->Item[i]->SubItems->Strings[0].ToDouble();
         double P2 = ListView->Items->Item[i]->SubItems->Strings[CurCol].ToDouble();
         double E  = (P1 - P2) * (P1 - P2);
         AvgErr += E;
         MaxErr  = max(MaxErr, E);
      }

      int ErrCnt = 48;
      if(CheckBox1->Checked)
         ErrCnt -= 18;
      if(CheckBox2->Checked)
         ErrCnt -= 6;
      if(CheckBox3->Checked)
         ErrCnt -= 6;
      AvgErr = sqrt(AvgErr / ErrCnt);
      MaxErr = sqrt(MaxErr);

      Memo2->Lines->Add(AnsiString().sprintf("最大误差 = %1.5f, 平均误差 = %1.5f", MaxErr, AvgErr));
   }

   /*
   // 对标定计算结果做平均
   // 计算标定误差
   double CaliErr = 0;
   for(int i = 0; i < ListView->Items->Count; ++i)
   {
      AverageCaliResult(ListView->Items->Item[i]);

      double e = EvalCaliError(ListView->Items->Item[i]);
      CaliErr += e * e;
   }
   CaliErr = sqrt(CaliErr);
   Chart1->Series[0]->AddXY(ListView->Columns->Count - 2, CaliErr);
   */
}
//---------------------------------------------------------------------------
void TForm1::AverageCaliResult(TListItem *Item)
{
   if(Item->SubItems->Count < 2)
      return;

   int Count = Item->SubItems->Count - 1;
   double Sum = Item->SubItems->Strings[Count - 1].ToDouble() * (Count - 1) +
                Item->SubItems->Strings[Count].ToDouble();
   Item->SubItems->Strings[Count] = AnsiString().sprintf("%1.5f", Sum / Count);
}
//---------------------------------------------------------------------------
double TForm1::EvalCaliError(TListItem *Item)
{
   if(Item->SubItems->Count < 2)
      return 0;

   return Item->SubItems->Strings[0].ToDouble() - Item->SubItems->Strings[Item->SubItems->Count - 1].ToDouble();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button10Click(TObject *Sender)
{
   EvaluatePosEulerError(CSpinEdit19->Value);
}
//---------------------------------------------------------------------------
void TForm1::EvaluatePosEulerError(int Count)
{
   double Errors[42];
   __RobotSimu.GetRobotErrors(Errors);

   vector<double> PosErrList;
   vector<double> EulerErrList;
   for(int i = 0; i < Count; ++i)
   {
      int   JackID = RandomRange(0, 6);
      float Servo  = RandomRange(0, CSpinEdit6->Value) * 0.001;

      // 真实误差条件下(即真实机器人)，机器人上平台的位姿
      double Pos1[3], Euler1[3];
      __RobotSimu.SetRobotErrors(Errors);
      __RobotSimu.JackMove(JackID, Servo);
      __RobotSimu.GetPosEuler(Pos1, Euler1);

      // 采用修正误差时，机器人的电缸长度
      double Jack[6];
      __RobotSimu.SetRobotErrors(__Calibrator.Error);
      __RobotSimu.PlatformMove(Pos1, Euler1);
      __RobotSimu.GetJackServo(Jack);

      // 真实机器人的实际位姿
      double Pos2[3], Euler2[3];
      __RobotSimu.SetRobotErrors(Errors);
      __RobotSimu.JackMove(Jack);
      __RobotSimu.GetPosEuler(Pos2, Euler2);

      // 位姿差异
      double PosErr[3], EulerErr[3];
      VectorSubVector(PosErr, Pos1, Pos2);
      VectorSubVector(EulerErr, Euler1, Euler2);

      // 记录误差
      double PosErrLen = VectorLength(PosErr);
      double EulerErrLen = VectorLength(EulerErr);

      PosErrList.push_back(PosErrLen);
      EulerErrList.push_back(EulerErrLen);
   }
   __RobotSimu.SetRobotErrors(Errors);

   // 显示误差分布
   ShowDistribution(PosErrList, Chart2->Series[0]);
   ShowDistribution(EulerErrList, Chart2->Series[1]);
   //Chart2->BottomAxis->Title = AnsiString().sprintf(""

   // 显示最大误差和平均误差
   double MaxPosErr = *max_element(PosErrList.begin(), PosErrList.end());
   double AvgPosErr = accumulate(PosErrList.begin(), PosErrList.end(), 0.0) / PosErrList.size();

   double MaxEulerErr = *max_element(EulerErrList.begin(), EulerErrList.end());
   double AvgEulerErr = accumulate(EulerErrList.begin(), EulerErrList.end(), 0.0) / EulerErrList.size();

   Edit1->Text = AnsiString().sprintf("AvgPosError = %1.3fmm, MaxPosError = %1.3fmm, AvgEulerError = %1.3f°, MaxEulerError = %1.3f°",
                                      AvgPosErr * 1000, MaxPosErr * 1000, AvgEulerErr, MaxEulerErr);
}
//---------------------------------------------------------------------------
void TForm1::ShowDistribution(vector<double> &Values, TChartSeries *Series)
{
   const int SIZE = 100;
   
   int Distribution[SIZE];
   fill(Distribution, Distribution + SIZE, 0);

   double Step = *max_element(Values.begin(), Values.end()) / SIZE;
   for(unsigned int i = 0; i < Values.size(); ++i)
   {
      int Idx = Values[i] / Step + 0.5;
      if(Idx <= 0)
         ++Distribution[0];
      else if(Idx > SIZE)
         ++Distribution[SIZE - 1];
      else
         ++Distribution[Idx];
   }

   Series->Clear();
   for(int i = 0; i < SIZE; ++i)
      Series->AddXY(i, Distribution[i] * 100.0 / Values.size());
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button11Click(TObject *Sender)
{
   int ErrRange[4] = {1, 2, 5, 10};
   for(int i = 0; i < 4; ++i)
   {
      // 设置本体误差范围
      CSpinEdit29->Value = ErrRange[i];

      // 测试统计100次随机误差条件下的位姿误差
      double AvgPosError = 0, AvgEulerError = 0, MaxPosError = 0, MaxEulerError = 0;
      for(int m = 0; m < 100; ++m)
      {
         // 产生一组随机误差
         Button8->Click();

         // 测试统计机器人位姿精度误差
         double AvgPos, AvgEuler, MaxPos, MaxEuler;
         //EvaluatePosEulerError(10000, AvgPos, MaxPos, AvgEuler, MaxEuler);
         AvgPosError   += AvgPos;
         AvgEulerError += AvgEuler;
         MaxPosError    = max(MaxPosError, MaxPos);
         MaxEulerError  = max(MaxEulerError, MaxEuler);
      }
      AvgPosError   /= 100;
      AvgEulerError /= 100;

      Memo2->Lines->Add("机械本体误差范围：" + IntToStr(ErrRange[i]) + "mm");
      Memo2->Lines->Add(AnsiString().sprintf("AvgPosError = %1.3fmm, MaxPosError = %1.3fmm, AvgEulerError = %1.3f°, MaxEulerError = %1.3f°",
                                      AvgPosError * 1000, MaxPosError * 1000, AvgEulerError, MaxEulerError));
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
   __RobotPkg.BuildJackCtrlOrder(CSpinEdit13->Value, CSpinEdit14->Value * 0.001, 0.02);
   SendOrder(__RobotPkg);
}
//---------------------------------------------------------------------------
// SendOrder()
//---------------------------------------------------------------------------
bool TForm1::SendOrder(CRobotCommPkg &CommPkg)
{
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
         Sleep(10);

         unsigned char Fdk[48];
         DWORD RcvLen;
         ReadFile(__hComm, Fdk, 48, &RcvLen, NULL);

         for(int m = 0; m < RcvLen; ++m)
            if(__RobotPkg.ReceiveFdkStatus(Fdk[m]))
            {
               float JackLength[6];
               __RobotPkg.GetJackLength(JackLength);

               ValueList->Strings->Strings[0] = AnsiString().sprintf("电缸1=%1.2f", JackLength[0] * 1000);
               ValueList->Strings->Strings[1] = AnsiString().sprintf("电缸2=%1.2f", JackLength[1] * 1000);
               ValueList->Strings->Strings[2] = AnsiString().sprintf("电缸3=%1.2f", JackLength[2] * 1000);
               ValueList->Strings->Strings[3] = AnsiString().sprintf("电缸4=%1.2f", JackLength[3] * 1000);
               ValueList->Strings->Strings[4] = AnsiString().sprintf("电缸5=%1.2f", JackLength[4] * 1000);
               ValueList->Strings->Strings[5] = AnsiString().sprintf("电缸6=%1.2f", JackLength[5] * 1000);

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
// 增加随机标定位姿
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
   __CaliStatus = 0;
   __SampleCnt  = CSpinEdit21->Value;


   for(int i = 0; i < CSpinEdit21->Value; ++i)
   {
      int JackID = RandomRange(0, 5);
      int JackLength = RandomRange(0, CSpinEdit6->Value);

      __RobotPkg.BuildJackCtrlOrder(JackID, JackLength * 0.001, 0.02);
      SendOrder(__RobotPkg);
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   __CaliStatus = -1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
   __RobotPkg.BuildJackCtrlOrder(0, 0, 0);

   if(__CaliStatus == 0)
   {
      int JackID = RandomRange(1, 6);
      int JackLength = RandomRange(50, CSpinEdit6->Value);

      __RobotPkg.BuildJackCtrlOrder(JackID, JackLength * 0.001, 0.02);
      
      //if(SendOrder(__RobotPkg))
      {
         __CaliStatus = 1;
         __CaliSteadyTime = 10000;
      }
   }
   else if(__CaliStatus == 1)
   {
      __CaliSteadyTime -= Timer1->Interval;
      if(__CaliSteadyTime <= 0)
         __CaliStatus = 2;
   }
   else if(__CaliStatus == 2)
   {
      // 测量标定点坐标

      --__SampleCnt;
      if(__SampleCnt)
         __CaliStatus = 0;
      else
         __CaliStatus = -1;
   }

   SendOrder(__RobotPkg);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
   if(SavePictureDialog1->Execute())
      Chart2->SaveToMetafileEnh(SavePictureDialog1->FileName + ".wmf");
}
//---------------------------------------------------------------------------

