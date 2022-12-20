//---------------------------------------------------------------------------


#pragma hdrstop

#include "CRobotSpace.h"
#include <stack>
#include <set>
#include <values.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CStuartWorkSpace::CStuartWorkSpace(void)
 : Step(0.001)
{
   XStep = YStep = ZStep = 1;
}
//---------------------------------------------------------------------------
void CStuartWorkSpace::SetSearchStep(float Step)
{
   this->Step = Step * 0.001;
   XStep = YStep = ZStep = Step;
}
//---------------------------------------------------------------------------
// IsFeasible()
// 检查机器人是否可以到到给定位置点
//---------------------------------------------------------------------------
bool CStuartWorkSpace::IsFeasible(int X, int Y, int Z)
{
   for(int i = 0; i < 8; ++i)
   {
      Robot.PlatformMove(X * Step, Y * Step, Z * Step,
                        (i & 0x01)? YawMin   : YawMax,
                        (i & 0x02)? PitchMin : PitchMax,
                        (i & 0x04)? RollMin  : RollMax);

      if(Robot.Constrained)
         return false;
   }

   return true;
}
//---------------------------------------------------------------------------
void CStuartWorkSpace::BeginEnumInitXY(int Z)
{
   __InitZ = Z;
}
//---------------------------------------------------------------------------
bool CStuartWorkSpace::FindNextInitXY(CXY &InitPoint, int Z)
{
   InitPoint.X = 0;
   InitPoint.Y = 0;

   if(__InitZ != MAXINT && IsFeasible(0, 0, Z))
   {
      __InitZ = MAXINT;
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

   SaveContour(Stream);

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

   LoadContour(Stream);

   delete Stream;
}
