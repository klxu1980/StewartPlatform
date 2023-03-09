//---------------------------------------------------------------------------


#pragma hdrstop

#include "JackTrace.h"
#include "GlobalDef.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CJackTrace::CJackTrace(void)
{
   for(int i = 0; i < 6; ++i)
   {
      __Trace.Trace[0].MaxS = JACK_MAX_SPEED;
      __Trace.Trace[0].MaxA = JACK_MAX_ACC;
   }
}
//----------------------------------------------------------------------------
// GetCurTime()
//----------------------------------------------------------------------------
double CJackTrace::GetCurTime(void)
{
#ifdef __BORLANDC__
   return SecondSpan(__BeginTime, TDateTime::CurrentDateTime());
#else
#endif
}
//---------------------------------------------------------------------------
void CJackTrace::Initialize(double JackLength[6])
{
#ifdef __BORLANDC__
   __BeginTime = TDateTime::CurrentDateTime();
#endif

   for(int i = 0; i < 6; ++i)
   {
      __InitJackLength[i] = JackLength[i];
      __NewJackLength[i] = 0.0;
   }
   __Trace.Reset();

   __NewJack     = false;
   __NoLstJack   = false;
   __LstJackTime = GetCurTime();
}
//---------------------------------------------------------------------------
// NewJackLength()
//---------------------------------------------------------------------------
void CJackTrace::NewJackLength(double JackLength[6])
{
   for(int i = 0; i < 6; ++i)
   {
      __LstJackLength[i] = __NewJackLength[i];
      __NewJackLength[i] = JackLength[i];
   }

   __LstJackTime = __NewJackTime;
   __NewJackTime = GetCurTime();
   __NewJack = true;
}
//---------------------------------------------------------------------------
// Move()
// 这部分代码还没写完善
//---------------------------------------------------------------------------
void CJackTrace::Move(float JackLength[6])
{
   bool NewSchedule = false;

   if(__NewJack || MoveTime > MaxMoveTime)
   {
      // 起始速度由当前位置和前次位置的差分计算
      float L0[6];
      float V0[6];
      float L1[6];
      float V1[6];

      // 根据规划曲线获取当前电缸长度和速度
      __Trace.Position(MoveTime, L0);
      __Trace.Speed(MoveTime, V0);

      double DTime = __NewJackTime - __LstJackTime;
      for(int i = 0; i < 6; ++i)
      {
         L1[i] = __NewJackLength[i];
         V1[i] = (__NewJackLength[i] - __LstJackLength[i]) / DTime;
      }

      // 规划路径
      __Trace.Schedule(L0, V0, L1, V1);


      MoveTime = 0;
      MaxMoveTime = __Trace.MoveTime;
      __NewJack = false;
   }

   // 计算机器人位姿
   __Trace.Position(MoveTime, JackLength);
}