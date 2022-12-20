//---------------------------------------------------------------------------


#pragma hdrstop

#include "CubicTrace.h"
#include "GlobalDef.h"
#include <math.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CCubicTrace::CCubicTrace(void)
 : DecayK(0.8)
{
   SetZero();
}
//---------------------------------------------------------------------------
bool CCubicTrace::Refresh(float T, float x0, float v0, float x1, float v1)
{
   a[0] = (fabs(x0) < 0.00001)? 0 : x0;
   a[1] = (fabs(v0) < 0.00001)? 0 : v0;

   a[2] = (3 * (x1 - x0) - (2 * v0 + v1) * T) / (T * T);
   a[3] = (2 * (x0 - x1) + (v0 + v1) * T) / (T * T * T);

   if(fabs(a[2]) < 0.00001)
      a[2] = 0;
   if(fabs(a[3]) < 0.00001)
      a[3] = 0;

   return MaxSpeed(T) <= MaxS && MaxAcc(T) <= MaxA;
}
//---------------------------------------------------------------------------
// MaxSpeedByCubic()
// 找出三次多项式轨迹中的最大速度
//---------------------------------------------------------------------------
float CCubicTrace::MaxSpeed(float T)
{
   // 比较0时刻和T时刻的速度，找出最大值
   float MaxSpd = Max(fabs(a[1]), fabs(a[1] + 2 * a[2] * T + 3 * a[3] * T * T));

   // 计算加速度为0时的速度
   // a[3]有可能接近或等于0，此时加速度恒定，速度最大值一定出现在0时刻或T时刻
   if(fabs(a[3]) > 0.001)
   {
      float Ta = -a[2] / (3 * a[3]);
      if(Ta > 0 && Ta < T)
         MaxSpd = Max(fabs(a[1] + a[2] * Ta), MaxSpd);
   }

   return MaxSpd;
}
//---------------------------------------------------------------------------
void CMoveTrace::Reset(void)
{
   for(int i = 0; i < 6; ++i)
      Trace[i].SetZero();
}
//---------------------------------------------------------------------------
void CMoveTrace::Stop(void)
{
   for(int i = 0; i < 6; ++i)
      Trace[i].Stop();
}
//---------------------------------------------------------------------------
void CMoveTrace::Decay(void)
{
   for(int i = 0; i < 6; ++i)
      Trace[i].Decay();
}
//---------------------------------------------------------------------------
// MaxAccByCubic()
// 找出三次多项式轨迹中的最大加速度
//---------------------------------------------------------------------------
float CCubicTrace::MaxAcc(float T)
{
   return Max(fabs(2 * a[2]), fabs(2 * a[2] + 6 * a[3] * T));
}
//---------------------------------------------------------------------------
// ScheduleMovement()
// 基于三次多项式规划时间T内的运动轨迹，并检查轨迹是否超出最大速度和加速度上限
//---------------------------------------------------------------------------
bool CMoveTrace::Schedule(float T, float Start[6], float VStart[6], float End[6], float VEnd[6])
{
   // 计算三次多项式轨迹
   for(int i = 0; i < 6; ++i)
      if(!Trace[i].Refresh(T, Start[i], VStart[i], End[i], VEnd[i]) )
         return false;
   return true;
}
//---------------------------------------------------------------------------
// ScheduleMovement()
// 基于二分搜索规划轨迹，找出满足速度、加速度约束的最快路径
//---------------------------------------------------------------------------
void CMoveTrace::Schedule(float Start[6], float VStart[6], float End[6], float VEnd[6])
{
   float T1 = 0.01;
   float T2 = 20;

   while(T2 - T1 > 0.01)
   {
      float T = (T1 + T2) * 0.5;
      if(Schedule(T, Start, VStart, End, VEnd) )
         T2 = T;
      else
         T1 = T;
   }
   Schedule(T2, Start, VStart, End, VEnd);

   MoveTime = T2;
}
//---------------------------------------------------------------------------
void CMoveTrace::Position(float t, float PosEuler[6])
{
   for(int i = 0; i < 6; ++i)
      PosEuler[i] = Trace[i].Position(t);
}
//---------------------------------------------------------------------------
void CMoveTrace::Speed(float t, float Speed[6])
{
   for(int i = 0; i < 6; ++i)
      Speed[i] = Trace[i].Speed(t);
}
