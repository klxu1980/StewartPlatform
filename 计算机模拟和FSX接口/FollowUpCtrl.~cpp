//---------------------------------------------------------------------------


#pragma hdrstop

#include "FollowUpCtrl.h"
#include <DateUtils.hpp>
//---------------------------------------------------------------------------
#define  GAMMA_FACTOR           0.8
#define  MIN_INC_ERROR          0.001      // 单位m
#define  MAX_RECALC_POS_TIMES   32
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CFollowupCtrl::CFollowupCtrl(CRobot &Robot)
 : __Robot(Robot),
   __PosPredict(3),
   __Gamma(0),
   __NoSampleTimes(0),
   __MaxNoSampleTimes(3)
{
   #ifdef __BORLANDC__
   __StartTime = TDateTime::CurrentDateTime();
   #endif
}
//---------------------------------------------------------------------------
double CFollowupCtrl::GetCurTime(void)
{
   #ifdef __BORLANDC__
   return SecondSpan(__StartTime, TDateTime::CurrentDateTime());
   #endif
}
//---------------------------------------------------------------------------
void CFollowupCtrl::NewPosition(double X, double Y, double Z, double Yaw, double Pitch, double Roll)
{
   double Time = GetCurTime();
   __PosPredict.NewSample(Time, X, Y, Z, Yaw, Pitch, Roll);

   __NoSampleTimes = 0;
   __Gamma = 1.0;
}
//---------------------------------------------------------------------------
bool CFollowupCtrl::CalcLinkIncrement(double X, double Y, double Z, double Yaw, double Pitch, double Roll, double Factor)
{
   X     = __LstPosition[0] + (X     - __LstPosition[0]) * Factor;
   Y     = __LstPosition[1] + (Y     - __LstPosition[1]) * Factor;
   Z     = __LstPosition[2] + (Z     - __LstPosition[2]) * Factor;
   Yaw   = __LstPosition[3] + (Yaw   - __LstPosition[3]) * Factor;
   Pitch = __LstPosition[4] + (Pitch - __LstPosition[4]) * Factor;
   Roll  = __LstPosition[5] + (Roll  - __LstPosition[5]) * Factor;

   if(__Robot.Move(X, Y, Z, Yaw, Pitch, Roll) == msOk)
   {
      __LinkInc[0] = __Robot.Links[0].Length - __LstLinkLength[0];
      __LinkInc[1] = __Robot.Links[1].Length - __LstLinkLength[1];
      __LinkInc[2] = __Robot.Links[2].Length - __LstLinkLength[2];
      __LinkInc[3] = __Robot.Links[3].Length - __LstLinkLength[3];
      __LinkInc[4] = __Robot.Links[4].Length - __LstLinkLength[4];
      __LinkInc[5] = __Robot.Links[5].Length - __LstLinkLength[5];

      return true;
   }
   else
      return false;
}
//---------------------------------------------------------------------------
int CFollowupCtrl::MaxIncIndex(double Inc[6])
{
   int    MaxIdx  = 0;
   double MaxLinkInc = fabs(__LinkInc[0]);

   for(int i = 1; i < 6; ++i)
      if(fabs(__LinkInc[i]) > MaxLinkInc)
      {
         MaxIdx = i;
         MaxLinkInc = __LinkInc[i];
      }
   return MaxIdx;
}
//---------------------------------------------------------------------------
double CFollowupCtrl::MaxLinkInc(double Inc[6])
{
   double MaxLinkInc = fabs(__LinkInc[0]);
   for(int i = 1; i < 6; ++i)
      if(fabs(__LinkInc[i]) > MaxLinkInc)
         MaxLinkInc = fabs(__LinkInc[i]);
   return MaxLinkInc;
}
//---------------------------------------------------------------------------
/*
void CFollowupCtrl::GetCtrlIncrement(double LinkInc[6], double MaxAllowedInc)
{
   // 如果多次控制周期中都未收到新的位置，则位置增量开始衰减，从而使机器人停机
   if(++__NoSampleTimes - __MaxNoSampleTimes > 0)
      __Gamma *= GAMMA_FACTOR;

   // 计算本次控制周期应当到达的位置
   double X, Y, Z, Roll, Yaw, Pitch;
   double Time = GetCurTime();
   __PosPredict.CalcPosition(Time, X, Y, Z, Roll, Yaw, Pitch);

   // 计算连杆运动增量
   double Beta = 1.0;
   CalcLinkIncrement(X, Y, Z, Roll, Yaw, Pitch, __Gamma);

   // 如果运动增量大于伺服机构所允许的最大增量，则重新计算运动位置
   //int MaxIncIdx = MaxIncIndex(__LinkInc);
   //if(fabs(__LinkInc[MaxIncIdx]) > MaxAllowedInc)

   double MaxInc = MaxLinkInc(__LinkInc);
   if(MaxInc > MaxAllowedInc)
   {
      double UpperBound = 1.0;
      double LowerBound = 0.0;

      //while(fabs(fabs(__LinkInc[MaxIncIdx]) - MaxInc) < MIN_INC_ERROR)
      while(fabs(MaxInc - MaxAllowedInc) < MIN_INC_ERROR)
      {
         Beta = (UpperBound + LowerBound) * 0.5;
         CalcLinkIncrement(X, Y, Z, Roll, Yaw, Pitch, __Gamma * Beta);

         MaxInc = MaxLinkInc(__LinkInc);
         if(MaxInc > MaxAllowedInc)
            UpperBound = Beta;
         else
            LowerBound = Beta;
      }
   }
} */

bool CFollowupCtrl::CalcLinkIncrement(double MaxAllowedInc)
{
   // 如果多次控制周期中都未收到新的位置，则位置增量开始衰减，从而使机器人停机
   if(++__NoSampleTimes - __MaxNoSampleTimes > 0)
      __Gamma *= GAMMA_FACTOR;

   // 计算本次控制周期应当到达的位置
   // 如果已有跟随数据不足以计算目标位置，则退出控制
   double X, Y, Z, Yaw, Pitch, Roll;
   if(!__PosPredict.CalcPosition(GetCurTime(), X, Y, Z, Yaw, Pitch, Roll))
      return false;

   // 计算连杆运动增量
   double Beta = 1.0;
   bool   Rst  = CalcLinkIncrement(X, Y, Z, Yaw, Pitch, Roll, __Gamma);

   // 如果运动增量大于伺服机构所允许的最大增量，或者跟踪位置超出合理范围，
   // 则缩小运动范围
   double MaxInc;
   if(!Rst || (MaxInc = MaxLinkInc(__LinkInc)) > MaxAllowedInc)
   {
      double UpperBound = 1.0;
      double LowerBound = 0.0;
      int    IterTimes  = 0;

      while(++IterTimes <= MAX_RECALC_POS_TIMES && fabs(MaxInc - MaxAllowedInc) > MIN_INC_ERROR)
      {
         // 线性缩小运动范围
         Beta = (UpperBound + LowerBound) * 0.5;
         Rst  = CalcLinkIncrement(X, Y, Z, Yaw, Pitch, Roll, __Gamma * Beta);

         if(!Rst || (MaxInc = MaxLinkInc(__LinkInc)) > MaxAllowedInc)
            UpperBound = Beta;
         else
            LowerBound = Beta;
      }

      if(IterTimes >= MAX_RECALC_POS_TIMES)
         return false;
   }

   // 记录本次控制实际到达位置
   double Factor = __Gamma * Beta;
   __LstPosition[0] = __Robot.PosX();
   __LstPosition[1] = __Robot.PosY();
   __LstPosition[2] = __Robot.PosZ();
   __LstPosition[3] = __Robot.PosYaw();
   __LstPosition[4] = __Robot.PosPitch();
   __LstPosition[5] = __Robot.PosRoll();

   __LstLinkLength[0] = __Robot.Links[0].Length;
   __LstLinkLength[1] = __Robot.Links[1].Length;
   __LstLinkLength[2] = __Robot.Links[2].Length;
   __LstLinkLength[3] = __Robot.Links[3].Length;
   __LstLinkLength[4] = __Robot.Links[4].Length;
   __LstLinkLength[5] = __Robot.Links[5].Length;

   return true;
}
//---------------------------------------------------------------------------
void CFollowupCtrl::SynchronizeRobot(void)
{
   __LstPosition[0] = __Robot.PosX();
   __LstPosition[1] = __Robot.PosY();
   __LstPosition[2] = __Robot.PosZ();
   __LstPosition[3] = __Robot.PosYaw();
   __LstPosition[4] = __Robot.PosPitch();
   __LstPosition[5] = __Robot.PosRoll();

   __LstLinkLength[0] = __Robot.Links[0].Length;
   __LstLinkLength[1] = __Robot.Links[1].Length;
   __LstLinkLength[2] = __Robot.Links[2].Length;
   __LstLinkLength[3] = __Robot.Links[3].Length;
   __LstLinkLength[4] = __Robot.Links[4].Length;
   __LstLinkLength[5] = __Robot.Links[5].Length;
}
