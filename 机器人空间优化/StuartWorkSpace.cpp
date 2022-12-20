//---------------------------------------------------------------------------


#pragma hdrstop

#include "StuartWorkSpace.h"
#include <stack>
#include <set>
#include <values.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CStuartWorkSpace::CStuartWorkSpace(void)
{
   Step = 1;
   SymAxis = SYM_BY_Y;
}
//---------------------------------------------------------------------------
void CStuartWorkSpace::SetSearchStep(float Step)
{
   this->Step = Step;
}
//---------------------------------------------------------------------------
// IsFeasible()
// 检查机器人是否可以到到给定位置点
//---------------------------------------------------------------------------
bool CStuartWorkSpace::IsFeasible(int X, int Y, int Z)
{
   // 改变搜索步长，从而加快搜索
   X *= Step;
   Y *= Step;
   Z *= Step;

   // 检测是否可以满足角度约束
   for(int i = 0; i < 8; ++i)
   {
      Robot.PlatformMove(X * 0.001, Y * 0.001, Z * 0.001,
                        (i & 0x01)? YawMin   : YawMax,
                        (i & 0x02)? PitchMin : PitchMax,
                        (i & 0x04)? RollMin  : RollMax);

      if(Robot.Constrained)
         return false;
   }

   return true;
}
//---------------------------------------------------------------------------
// BeginEnumInitXY()
//---------------------------------------------------------------------------
void CStuartWorkSpace::BeginEnumInitXY(int Z)
{
   if(IsFeasible(0, 0, Z) )
      __InitX = __InitY = 0;
   else
      __InitX = __InitY = MAXINT;
}
//---------------------------------------------------------------------------
// FindNextInitXY()
// 并联机器人仅仅从(0, 0, Z)点出发搜索运动空间
//---------------------------------------------------------------------------
bool CStuartWorkSpace::FindNextInitXY(CXY &InitPoint)
{
   if(__InitX != MAXINT)
   {
      InitPoint.X = __InitX;
      InitPoint.Y = __InitY;
      __InitX = __InitY = MAXINT;
      return true;
   }
   else
      return false;
}
//---------------------------------------------------------------------------
void CStuartWorkSpace::GetWorkSpaceBorder(void)
{
   Robot.InitStructureParams();

   BorderXYZ.clear();
   for(int Z = 0; Z <= 5000; ++Z)
      GetWorkSpaceBorderXY(Z);
}
//---------------------------------------------------------------------------
void CStuartWorkSpace::SaveToFile(AnsiString FileName)
{
   TStream *Stream = new TFileStream(FileName, fmCreate);

   Stream->Write(&Robot.UpperArmLength,   sizeof(Robot.UpperArmLength));
   Stream->Write(&Robot.UpperBaseLength,  sizeof(Robot.UpperBaseLength));
   Stream->Write(&Robot.LowerArmLength,   sizeof(Robot.LowerArmLength));
   Stream->Write(&Robot.LowerBaseLength,  sizeof(Robot.LowerBaseLength));
   Stream->Write(&Robot.UpperJointHeight, sizeof(Robot.UpperJointHeight));
   Stream->Write(&Robot.LowerJointHeight, sizeof(Robot.LowerJointHeight));
   Stream->Write(&Robot.JackFixedLength,  sizeof(Robot.JackFixedLength));
   Stream->Write(&Robot.JackServoLength,  sizeof(Robot.JackServoLength));
   Stream->Write(&YawMin,    sizeof(YawMin));
   Stream->Write(&YawMax,    sizeof(YawMax));
   Stream->Write(&PitchMin,  sizeof(PitchMin));
   Stream->Write(&PitchMax,  sizeof(PitchMax));
   Stream->Write(&RollMin,   sizeof(RollMin));
   Stream->Write(&RollMax,   sizeof(RollMax));

   SaveBorder(Stream);

   delete Stream;
}
//---------------------------------------------------------------------------
void CStuartWorkSpace::LoadFromFile(AnsiString FileName)
{
   TStream *Stream = new TFileStream(FileName, fmOpenRead);

   Stream->Read(&Robot.UpperArmLength,   sizeof(Robot.UpperArmLength));
   Stream->Read(&Robot.UpperBaseLength,  sizeof(Robot.UpperBaseLength));
   Stream->Read(&Robot.LowerArmLength,   sizeof(Robot.LowerArmLength));
   Stream->Read(&Robot.LowerBaseLength,  sizeof(Robot.LowerBaseLength));
   Stream->Read(&Robot.UpperJointHeight, sizeof(Robot.UpperJointHeight));
   Stream->Read(&Robot.LowerJointHeight, sizeof(Robot.LowerJointHeight));
   Stream->Read(&Robot.JackFixedLength,  sizeof(Robot.JackFixedLength));
   Stream->Read(&Robot.JackServoLength,  sizeof(Robot.JackServoLength));
   Stream->Read(&YawMin,    sizeof(YawMin));
   Stream->Read(&YawMax,    sizeof(YawMax));
   Stream->Read(&PitchMin,  sizeof(PitchMin));
   Stream->Read(&PitchMax,  sizeof(PitchMax));
   Stream->Read(&RollMin,   sizeof(RollMin));
   Stream->Read(&RollMax,   sizeof(RollMax));

   Robot.InitStructureParams();

   LoadBorder(Stream);

   delete Stream;
}
