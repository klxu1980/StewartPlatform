//---------------------------------------------------------------------------


#pragma hdrstop

#include "JackTrace.h"
#include "GlobalDef.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CJackTrace::CJackTrace(void)
{
   // 设置轨迹规划器的速度和加速度约束
   for(int i = 0; i < 6; ++i)
   {
      __Trace.Trace[0].MaxS = JACK_MAX_SPEED;
      __Trace.Trace[0].MaxA = JACK_MAX_ACC;
   }
}
//---------------------------------------------------------------------------
// Initialize()
// 通常当机器人完成归零操作时进行初始化
//---------------------------------------------------------------------------
void CJackTrace::Initialize(double JackLength[6])
{
#ifdef __BORLANDC__
   __BeginTime = TDateTime::CurrentDateTime();
#endif

   for(int i = 0; i < 6; ++i)
   {
      __InitJackLength[i] = JackLength[i]; // 记录归零完成后电缸长度，以便电缸轨迹规划时从0开始
      __NewJackLength[i]  = 0.0;
   }
   __Trace.Reset();

   __NewJack     = false;
   __TimeCounter = 0;
   __LstJackTime = 0;
}
//----------------------------------------------------------------------------
// GetCurTime()
//----------------------------------------------------------------------------
double CJackTrace::GetCurTime(void)
{
   return __TimeCounter * CTRL_INTERVAL;
}
//---------------------------------------------------------------------------
// NewJackLength()
//---------------------------------------------------------------------------
void CJackTrace::NewJackLength(double JackLength[6])
{
   for(int i = 0; i < 6; ++i)
   {
      __LstJackLength[i] = __NewJackLength[i];
      __NewJackLength[i] = JackLength[i] - __InitJackLength[i];  // 减去初始长度，使规划齐次化
   }

   __LstJackTime = __NewJackTime;
   __NewJackTime = GetCurTime();
   __NewJack = true;
}
//---------------------------------------------------------------------------
// Move()
// 这里还有个问题：两次更新间隔很长时怎样处理?
//---------------------------------------------------------------------------
void CJackTrace::Move(float JackLength[6])
{
   if(__NewJack || MoveTime > MaxMoveTime)
   {
      // 起始速度由当前位置和前次位置的差分计算
      float L0[6];
      float V0[6];
      float L1[6];
      float V1[6];

      // 根据运动曲线获取当前电缸长度和速度
      __Trace.Position(MoveTime, L0);
      __Trace.Speed(MoveTime, V0);

      // 目标位置和速度
      // 如果上层算法更新了电缸的预期位置，则目标位置为预期位置，目标速度为新位置与旧位置的差分
      // 如果上层算法未更新电缸预期位置，则目标位置为当前位置，目标速度为0，从而令机器人停止下来
      if(__NewJack)
      {
         double DTime = __NewJackTime - __LstJackTime;
         for(int i = 0; i < 6; ++i)
         {
            L1[i] = __NewJackLength[i];
            V1[i] = (__NewJackLength[i] - __LstJackLength[i]) / DTime;
         }
      }
      else
      {
         for(int i = 0; i < 6; ++i)
         {
            L1[i] = L0[i];
            V1[i] = 0;
         }
      }

      // 规划电缸的运动曲线
      __Trace.Schedule(L0, V0, L1, V1);

      // 重置运动时间和标志位
      MoveTime = 0;
      MaxMoveTime = __Trace.MoveTime;
      __NewJack = false;
   }

   // 计算机器人位姿
   __Trace.Position(MoveTime, JackLength);
   for(int i = 0; i < 6; ++i)
      JackLength[i] += __InitJackLength[i];
}