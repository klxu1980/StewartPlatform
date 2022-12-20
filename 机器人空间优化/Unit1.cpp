//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <IniFiles.hpp>
#include <Jpeg.hpp>

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner),
          __WorkSpace(NULL),
          __SpaceFile(40)
{
   __IniLoading = true;
   LoadRobotParams();
   __IniLoading = false;

   CSpinEdit22->Value = 500;
   CSpinEdit23->Value = 500;

   __Space3DView.SetSpaceCubeColor(ColorBox2->Selected);
}
//---------------------------------------------------------------------------
// SaveRobotParams()
//---------------------------------------------------------------------------
void TForm1::SaveRobotParams(void)
{
   if(__IniLoading)
      return;
      
   TIniFile *IniFile = new TIniFile(ExtractFileDir(Application->ExeName) + "\\机器人运动空间.ini");

   IniFile->WriteInteger("机械参数", "上平台长轴",   CSpinEdit1->Value);
   IniFile->WriteInteger("机械参数", "上平台短轴",   CSpinEdit2->Value);
   IniFile->WriteInteger("机械参数", "下平台长轴",   CSpinEdit3->Value);
   IniFile->WriteInteger("机械参数", "下平台短轴",   CSpinEdit4->Value);
   IniFile->WriteInteger("机械参数", "电缸最短行程", CSpinEdit5->Value);
   IniFile->WriteInteger("机械参数", "电缸最大行程", CSpinEdit6->Value);

   IniFile->WriteInteger("运动范围", "最大偏航角", CSpinEdit7->Value);
   IniFile->WriteInteger("运动范围", "最小偏航角", CSpinEdit8->Value);
   IniFile->WriteInteger("运动范围", "最大俯仰角", CSpinEdit9->Value);
   IniFile->WriteInteger("运动范围", "最小俯仰角", CSpinEdit10->Value);
   IniFile->WriteInteger("运动范围", "最大滚转角", CSpinEdit11->Value);
   IniFile->WriteInteger("运动范围", "最小滚转角", CSpinEdit12->Value);

   IniFile->WriteInteger("显示范围", "X轴", CSpinEdit22->Value);
   IniFile->WriteInteger("显示范围", "Y轴", CSpinEdit23->Value);

   delete IniFile;
}
//---------------------------------------------------------------------------
// LoadRobotParams()
//---------------------------------------------------------------------------
void TForm1::LoadRobotParams(void)
{
   TIniFile *IniFile = new TIniFile(ExtractFileDir(Application->ExeName) + "\\机器人运动空间.ini");

   CSpinEdit1->Value = IniFile->ReadInteger("机械参数", "上平台长轴",   0);
   CSpinEdit2->Value = IniFile->ReadInteger("机械参数", "上平台短轴",   0);
   CSpinEdit3->Value = IniFile->ReadInteger("机械参数", "下平台长轴",   0);
   CSpinEdit4->Value = IniFile->ReadInteger("机械参数", "下平台短轴",   0);
   CSpinEdit5->Value = IniFile->ReadInteger("机械参数", "电缸最短行程", 0);
   CSpinEdit6->Value = IniFile->ReadInteger("机械参数", "电缸最大行程", 0);

   CSpinEdit7->Value = IniFile->ReadInteger("运动范围", "最大偏航角",   0);
   CSpinEdit8->Value = IniFile->ReadInteger("运动范围", "最小偏航角",   0);
   CSpinEdit9->Value = IniFile->ReadInteger("运动范围", "最大俯仰角",   0);
   CSpinEdit10->Value = IniFile->ReadInteger("运动范围", "最小俯仰角",  0);
   CSpinEdit11->Value = IniFile->ReadInteger("运动范围", "最大滚转角",  0);
   CSpinEdit12->Value = IniFile->ReadInteger("运动范围", "最小滚转角",  0);

   CSpinEdit22->Value = IniFile->ReadInteger("显示范围", "X轴", 0);
   CSpinEdit23->Value = IniFile->ReadInteger("显示范围", "Y轴", 0);

   delete IniFile;
}
//---------------------------------------------------------------------------
// CSpinEdit1Change()
//---------------------------------------------------------------------------
void __fastcall TForm1::CSpinEdit1Change(TObject *Sender)
{
   SaveRobotParams();
}
//---------------------------------------------------------------------------
// CSpinEdit13Change()
// 改变Z轴位置，重新计算机器人运动空间
//---------------------------------------------------------------------------
void __fastcall TForm1::CSpinEdit13Change(TObject *Sender)
{  
   if(!__WorkSpace)
      return;

   // 更新边界图
   //Chart1->Refresh();

   // 更新3D显示
   __Space3DView.SetZRange(CSpinEdit17->Value, CSpinEdit18->Value);
}
//---------------------------------------------------------------------------
// Chart1AfterDraw()
// 绘制机器人运动空间边界
//---------------------------------------------------------------------------
void __fastcall TForm1::Chart1AfterDraw(TObject *Sender)
{
   if(!__WorkSpace)
      return;

   for(unsigned int i = 0; i < __WorkSpace->BorderXYZ.size(); ++i)
   {
      vector<CXY> &XY = __WorkSpace->BorderXYZ[i].Border;
      if(__WorkSpace->BorderXYZ[i].Z < CSpinEdit17->Value || __WorkSpace->BorderXYZ[i].Z > CSpinEdit18->Value)
         continue;

      // 颜色渐变
      TColor Color1 = clBlue;
      TColor Color2 = clRed;

      int B = (Color1 & 0x0FF0000) + ((Color2 & 0x0FF0000) - (Color1 & 0x0FF0000)) * float(i) / __WorkSpace->BorderXYZ.size();
      int G = (Color1 & 0x0FF00) + ((Color2 & 0x0FF00) - (Color1 & 0x0FF00)) * float(i) / __WorkSpace->BorderXYZ.size();
      int R = (Color1 & 0x0FF) + ((Color2 & 0x0FF) - (Color1 & 0x0FF)) * float(i) / __WorkSpace->BorderXYZ.size();
      Chart1->Canvas->Pen->Color = (B & 0x0FF0000) | (G & 0x0FF00) | (R & 0x0FF);

      // 起始点
      int X0 = Chart1->BottomAxis->CalcXPosValue(XY.front().X);
      int Y0 = Chart1->LeftAxis->CalcYPosValue(XY.front().Y);
      Chart1->Canvas->MoveTo(X0, Y0);

      // 绘制边界线
      for(unsigned int i = 1; i < XY.size(); ++i)
      {
         int X = Chart1->BottomAxis->CalcXPosValue(XY[i].X);
         int Y = Chart1->LeftAxis->CalcYPosValue(XY[i].Y);

         Chart1->Canvas->LineTo(X, Y);
      }
      Chart1->Canvas->LineTo(X0, Y0);
   }

   // 绘制机器人立方体空间
   float OX = __CubeSpace.X;
   float OY = __CubeSpace.Y;
   float WX = __CubeSpace.Kx * __CubeSpace.L;
   float WY = __CubeSpace.Ky * __CubeSpace.L;

   Chart1->Canvas->Pen->Color = clBlack;
   Chart1->Canvas->Pen->Width = 2;
   Chart1->Canvas->MoveTo(Chart1->BottomAxis->CalcXPosValue(OX - WX), Chart1->LeftAxis->CalcYPosValue(OY - WY));
   Chart1->Canvas->LineTo(Chart1->BottomAxis->CalcXPosValue(OX - WX), Chart1->LeftAxis->CalcYPosValue(OY + WY));
   Chart1->Canvas->LineTo(Chart1->BottomAxis->CalcXPosValue(OX + WX), Chart1->LeftAxis->CalcYPosValue(OY + WY));
   Chart1->Canvas->LineTo(Chart1->BottomAxis->CalcXPosValue(OX + WX), Chart1->LeftAxis->CalcYPosValue(OY - WY));
   Chart1->Canvas->LineTo(Chart1->BottomAxis->CalcXPosValue(OX - WX), Chart1->LeftAxis->CalcYPosValue(OY - WY));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CSpinEdit14Change(TObject *Sender)
{
   Chart1->BottomAxis->SetMinMax(-CSpinEdit22->Value, CSpinEdit22->Value);
   Chart1->LeftAxis->SetMinMax(-CSpinEdit23->Value, CSpinEdit23->Value);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
   // 机器人机械参数
   __RobotSpace.Robot.UpperArmLength   = CSpinEdit1->Value * 0.001;
   __RobotSpace.Robot.UpperBaseLength  = CSpinEdit2->Value * 0.001;
   __RobotSpace.Robot.LowerArmLength   = CSpinEdit3->Value * 0.001;
   __RobotSpace.Robot.LowerBaseLength  = CSpinEdit4->Value * 0.001;
   __RobotSpace.Robot.UpperJointHeight = 0;
   __RobotSpace.Robot.LowerJointHeight = 0;
   __RobotSpace.Robot.JackFixedLength  = CSpinEdit5->Value * 0.001;
   __RobotSpace.Robot.JackServoLength  = CSpinEdit6->Value * 0.001;
   __RobotSpace.Robot.JackServoBuffer  = 0;

   // 机器人姿态运动范围
   __RobotSpace.YawMax   = CSpinEdit7->Value;
   __RobotSpace.YawMin   = CSpinEdit8->Value;
   __RobotSpace.PitchMax = CSpinEdit9->Value;
   __RobotSpace.PitchMin = CSpinEdit10->Value;
   __RobotSpace.RollMax  = CSpinEdit11->Value;
   __RobotSpace.RollMin  = CSpinEdit12->Value;

   // 计算机器人运动范围
   __RobotSpace.SetSearchStep(CSpinEdit19->Value);

   // 搜索运动空间
   __RobotSpace.GetWorkSpaceBorder();
   if(!__RobotSpace.BorderXYZ.empty())
   {
      __WorkSpace = &__RobotSpace;
      __Space3DView.DrawSpace(&__RobotSpace, -__RobotSpace.BorderXYZ.front().Z);

      CSpinEdit17->MinValue = __RobotSpace.BorderXYZ.front().Z;
      CSpinEdit17->MaxValue = __RobotSpace.BorderXYZ.back().Z;
      CSpinEdit17->Value    = __RobotSpace.BorderXYZ.front().Z;

      CSpinEdit18->MinValue = CSpinEdit17->MinValue;
      CSpinEdit18->MaxValue = CSpinEdit17->MaxValue;
      CSpinEdit18->Value    = CSpinEdit17->MaxValue;

      Application->MessageBox("机器人运动空间计算结束", "", MB_OK | MB_ICONINFORMATION);
   }
   else
      Application->MessageBox("该约束条件下无可用空间", "", MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
   if(SaveDialog1->Execute() && __WorkSpace)
      __WorkSpace->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
   if(OpenDialog1->Execute())
   {
      __RobotSpace.LoadFromFile(OpenDialog1->FileName);

      CSpinEdit1->Value = __RobotSpace.Robot.UpperArmLength   * 1000;
      CSpinEdit2->Value = __RobotSpace.Robot.UpperBaseLength  * 1000;
      CSpinEdit3->Value = __RobotSpace.Robot.LowerArmLength   * 1000;
      CSpinEdit4->Value = __RobotSpace.Robot.LowerBaseLength  * 1000;
      CSpinEdit5->Value = __RobotSpace.Robot.JackFixedLength  * 1000;
      CSpinEdit6->Value = __RobotSpace.Robot.JackServoLength  * 1000;

      CSpinEdit7->Value  = __RobotSpace.YawMax;
      CSpinEdit8->Value  = __RobotSpace.YawMin;
      CSpinEdit9->Value  = __RobotSpace.PitchMax;
      CSpinEdit10->Value = __RobotSpace.PitchMin;
      CSpinEdit11->Value = __RobotSpace.RollMax;
      CSpinEdit12->Value = __RobotSpace.RollMin;

      if(!__RobotSpace.BorderXYZ.empty())
      {
         CSpinEdit17->MinValue = __RobotSpace.BorderXYZ.front().Z;
         CSpinEdit17->MaxValue = __RobotSpace.BorderXYZ.back().Z;
         CSpinEdit17->Value    = __RobotSpace.BorderXYZ.front().Z;

         CSpinEdit18->MinValue = CSpinEdit17->MinValue;
         CSpinEdit18->MaxValue = CSpinEdit17->MaxValue;
         CSpinEdit18->Value    = CSpinEdit17->MaxValue;

         __WorkSpace = &__RobotSpace;
         __Space3DView.DrawSpace(&__RobotSpace, -__RobotSpace.BorderXYZ.front().Z);
      }
      else
         Application->MessageBox("该运动空间为空", "", MB_OK | MB_ICONINFORMATION);
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
   // 运动空间初始中心点
   // 注意：计算均以mm为单位
   if(CheckBox1->Checked)
   {
      __CubeSpace.InitX = Edit9->Text.ToDouble();
      __CubeSpace.InitY = Edit4->Text.ToDouble();
      __CubeSpace.InitZ = Edit5->Text.ToDouble();
   }
   else
   {
      __CubeSpace.InitX = 0;
      __CubeSpace.InitY = 0;
      __CubeSpace.InitZ = (__RobotSpace.BorderXYZ.front().Z + __RobotSpace.BorderXYZ.back().Z) * 0.5;
   }

   // 运动空间缩放比例
   __CubeSpace.Kx = Edit1->Text.ToDouble();
   __CubeSpace.Ky = Edit2->Text.ToDouble();
   __CubeSpace.Kz = Edit3->Text.ToDouble();

   // 并联机器人和串联机器人的对称轴不一样
   // 并联机器人以Y轴为对称轴，串联机器人以X轴为对称轴
   //__CubeSpace.SymmetryByX = RadioButton2->Checked;

   // 将当前机器人运动空间信息复制给空间优化程序
   __CubeSpace.WorkSpace = __WorkSpace;

   // 空间优化
   if(__CubeSpace.Optimize() )
   {
      Edit9->Text = AnsiString().sprintf("%1.1f", __CubeSpace.X);
      Edit4->Text = AnsiString().sprintf("%1.1f", __CubeSpace.Y);
      Edit5->Text = AnsiString().sprintf("%1.1f", __CubeSpace.Z);

      Edit6->Text = AnsiString().sprintf("%1.1f", (__CubeSpace.L * __CubeSpace.Kx));
      Edit7->Text = AnsiString().sprintf("%1.1f", (__CubeSpace.L * __CubeSpace.Ky));
      Edit8->Text = AnsiString().sprintf("%1.1f", (__CubeSpace.L * __CubeSpace.Kz));

      __Space3DView.DrawCube(&__CubeSpace);
   }
   else
      Application->MessageBox("运动空间优化失败", "错误", MB_OK | MB_ICONERROR);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   if(OpenDialog1->Execute())
   {
      __SpaceFile.LoadRobotFile(OpenDialog1->FileName);
      __Space3DView.DrawSpace(&__SpaceFile);

      if(!__SpaceFile.BorderXYZ.empty())
      {
         CSpinEdit17->MinValue = __SpaceFile.BorderXYZ.front().Z;
         CSpinEdit17->MaxValue = __SpaceFile.BorderXYZ.back().Z;
         CSpinEdit17->Value    = __SpaceFile.BorderXYZ.front().Z;

         CSpinEdit18->MinValue = CSpinEdit17->MinValue;
         CSpinEdit18->MaxValue = CSpinEdit17->MaxValue;
         CSpinEdit18->Value    = CSpinEdit17->MaxValue;
      }
      __WorkSpace = &__SpaceFile;

      Application->MessageBox("机器人运动空间计算结束", "", MB_OK | MB_ICONINFORMATION);
      Caption = "串联机器人运动空间-" + OpenDialog1->FileName;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
   if(SaveDialog1->Execute() && __WorkSpace)
      __WorkSpace->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button7Click(TObject *Sender)
{
   if(OpenDialog1->Execute())
   {
      __SpaceFile.LoadFromFile(OpenDialog1->FileName);

      __Space3DView.DrawSpace(&__SpaceFile);

      if(!__SpaceFile.BorderXYZ.empty())
      {
         CSpinEdit17->MinValue = __SpaceFile.BorderXYZ.front().Z;
         CSpinEdit17->MaxValue = __SpaceFile.BorderXYZ.back().Z;
         CSpinEdit17->Value    = __SpaceFile.BorderXYZ.front().Z;

         CSpinEdit18->MinValue = CSpinEdit17->MinValue;
         CSpinEdit18->MaxValue = CSpinEdit17->MaxValue;
         CSpinEdit18->Value    = CSpinEdit17->MaxValue;

         __WorkSpace = &__SpaceFile;
      }
   }        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   __Space3DView.Initialize(GetDC(TabSheet1->Handle));        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton5Click(TObject *Sender)
{
   __Space3DView.RotateAroundX(10);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton6Click(TObject *Sender)
{
   __Space3DView.RotateAroundX(-10);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton7Click(TObject *Sender)
{
   __Space3DView.RotateAroundY(10);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton8Click(TObject *Sender)
{
   __Space3DView.RotateAroundY(-10);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton9Click(TObject *Sender)
{
   __Space3DView.RotateAroundZ(10);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton10Click(TObject *Sender)
{
   __Space3DView.RotateAroundZ(-10);        
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

void __fastcall TForm1::PaintBox1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
   if(!__MouseDown)
      return;

   int    ViewWidth = min(PaintBox1->Width, PaintBox1->Height);
   double DeltaX = double(X - __MouseX) / ViewWidth;
   double DeltaY = double(Y - __MouseY) / ViewWidth;
   __Space3DView.MoveScreen(DeltaX, DeltaY);

   __MouseX = X;
   __MouseY = Y;              
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   __MouseDown = false;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1Paint(TObject *Sender)
{
   int ViewWidth  = min(PaintBox1->Width, PaintBox1->Height);
   TPoint LeftTop = PaintBox1->ClientToParent(TPoint(0, 0), this);

   __Space3DView.Resize(PaintBox1->Left + (PaintBox1->Width  - ViewWidth) / 2,
                        PaintBox1->Top  + (PaintBox1->Height - ViewWidth) / 2,
                        ViewWidth,
                        ViewWidth);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CSpinEdit17Change(TObject *Sender)
{
   if(!__WorkSpace)
      return;

   // 更新边界图
   Chart1->Refresh();

   // 显示优化后的矩形空间
   //__CubeSpace.DrawSpace(CSpinEdit13->Value * 0.001, SpaceMap);

   if(CheckBox3->Checked)
      __Space3DView.SetZRange(CSpinEdit17->Value, CSpinEdit17->Value + __WorkSpace->Step);
   else
      __Space3DView.SetZRange(CSpinEdit17->Value, CSpinEdit18->Value);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ToolButton1Click(TObject *Sender)
{
   __Space3DView.Zoom(1.1);
   CSpinEdit22->Value = CSpinEdit22->Value * 0.9;
   CSpinEdit23->Value = CSpinEdit23->Value * 0.9;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton2Click(TObject *Sender)
{
   __Space3DView.Zoom(0.9);
   CSpinEdit22->Value = CSpinEdit22->Value * 1.1;
   CSpinEdit23->Value = CSpinEdit23->Value * 1.1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ColorBox1Change(TObject *Sender)
{
   __Space3DView.SetBKColor(ColorBox1->Selected);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ColorBox2Change(TObject *Sender)
{
   __Space3DView.SetSpaceCubeColor(ColorBox2->Selected);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
   vector<CXY> Space;
   __SpaceFile.GetXYSpace(Space, CSpinEdit17->Value);

   Form2->DrawWorkspace(Space);
   Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
   Graphics::TBitmap *Bitmap = new Graphics::TBitmap();
   Bitmap->Width  = 1000;
   Bitmap->Height = 800;
   __SpaceFile.DrawSpaceBorderXY(Bitmap, CSpinEdit17->Value);

   Form2->Image1->Canvas->Draw(0, 0, Bitmap);
   Form2->Show();       
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{  
   // 运动空间缩放比例
   __CubeSpace.Kx = Edit1->Text.ToDouble();
   __CubeSpace.Ky = Edit2->Text.ToDouble();
   __CubeSpace.Kz = Edit3->Text.ToDouble();

   // 将当前机器人运动空间信息复制给空间优化程序
   __CubeSpace.WorkSpace = __WorkSpace;

   // 空间优化
   int Xmin = 1000;
   int Xmax = 4500;
   int Zmin = -1000;
   int Zmax = 3500;

   if(CheckBox4->Checked)
      Xmin = Xmax = Edit9->Text.ToDouble();
   if(CheckBox6->Checked)
      Zmin = Zmax = Edit5->Text.ToDouble();

   __CubeSpace.OptimizeNaive(Xmin, Xmax, 0, 0, Zmin, Zmax);

      Edit9->Text = AnsiString().sprintf("%1.1f", __CubeSpace.X);
      Edit4->Text = AnsiString().sprintf("%1.1f", __CubeSpace.Y);
      Edit5->Text = AnsiString().sprintf("%1.1f", __CubeSpace.Z);

      Edit6->Text = AnsiString().sprintf("%1.1f", (__CubeSpace.L * __CubeSpace.Kx));
      Edit7->Text = AnsiString().sprintf("%1.1f", (__CubeSpace.L * __CubeSpace.Ky));
      Edit8->Text = AnsiString().sprintf("%1.1f", (__CubeSpace.L * __CubeSpace.Kz));

      __Space3DView.DrawCube(&__CubeSpace);
           
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
   __Space3DView.ShowCube(CheckBox2->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox7Click(TObject *Sender)
{
   if(CheckBox7->Checked && CheckBox8->Checked)
      __Space3DView.ShowHalfX(SHOW_WHOLE_DIR);
   else if(CheckBox7->Checked)
      __Space3DView.ShowHalfX(SHOW_POS_DIR);
   else
      __Space3DView.ShowHalfX(SHOW_NEG_DIR);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox9Click(TObject *Sender)
{
   if(CheckBox9->Checked && CheckBox10->Checked)
      __Space3DView.ShowHalfY(SHOW_WHOLE_DIR);
   else if(CheckBox9->Checked)
      __Space3DView.ShowHalfY(SHOW_POS_DIR);
   else
      __Space3DView.ShowHalfY(SHOW_NEG_DIR);
}
//---------------------------------------------------------------------------

