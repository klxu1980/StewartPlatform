//---------------------------------------------------------------------------
// 2022.01.23：完成计算机上的仿真测试

#pragma hdrstop

#include "MotionTrack.h"
#include "GlobalDef.h"
//#include <values.h>

//#include "Unit1.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CMotionTracker::CMotionTracker(void)
 : __LstDstTime(-1)
{
   __Trace.Trace[0].MaxS = 0.5;
   __Trace.Trace[1].MaxS = 0.5;
   __Trace.Trace[2].MaxS = 0.5;
   __Trace.Trace[3].MaxS = 10;
   __Trace.Trace[4].MaxS = 10;
   __Trace.Trace[5].MaxS = 10;

   __Trace.Trace[0].MaxA = 1;
   __Trace.Trace[1].MaxA = 1;
   __Trace.Trace[2].MaxA = 1;
   __Trace.Trace[3].MaxA = 5;
   __Trace.Trace[4].MaxA = 5;
   __Trace.Trace[5].MaxA = 5;
}
//----------------------------------------------------------------------------
// GetCurTime()
//----------------------------------------------------------------------------
double CMotionTracker::GetCurTime(void)
{
#ifdef __BORLANDC__
   return SecondSpan(__BeginTime, TDateTime::CurrentDateTime());
#else
#endif
}
//---------------------------------------------------------------------------
void CMotionTracker::Initialize(double Pos[3], double Euler[3])
{
#ifdef __BORLANDC__
   __BeginTime = TDateTime::CurrentDateTime();
#endif
   __End[0] = Pos[0];
   __End[1] = Pos[1];
   __End[2] = Pos[2];
   __End[3] = Euler[0];
   __End[4] = Euler[1];
   __End[5] = Euler[2];

   __VEnd[0] = __VEnd[1] = __VEnd[2] = __VEnd[3] = __VEnd[4] = __VEnd[5] = 0;

   __NewDst = false;
   __LstDstTime = GetCurTime();
}
//---------------------------------------------------------------------------
// NewDestination()
//---------------------------------------------------------------------------
void CMotionTracker::NewDestination(float PosEuler[6])
{
   double CurTime = GetCurTime();
   double DelTime = CurTime - __LstDstTime;

   if(DelTime > 0.01)
   {
      for(int i = 0; i < 6; ++i)
      {
         __VEnd[i] = (PosEuler[i] - __End[i]) / DelTime;
         __End[i]  = PosEuler[i];
      }
      __NewDst = true;
      __LstDstTime = CurTime;
   }
}
//---------------------------------------------------------------------------
// Move()
//---------------------------------------------------------------------------
void CMotionTracker::Move(double Pos[3], double Euler[3])
{
   if(__NewDst)
   {
      // 起始速度由当前位置和前次位置的差分计算
      __VStart[0] = (Pos[0] - __Start[0]) / CTRL_INTERVAL;
      __VStart[1] = (Pos[1] - __Start[1]) / CTRL_INTERVAL;
      __VStart[2] = (Pos[2] - __Start[2]) / CTRL_INTERVAL;
      __VStart[3] = (Euler[0] - __Start[3]) / CTRL_INTERVAL;
      __VStart[4] = (Euler[1] - __Start[4]) / CTRL_INTERVAL;
      __VStart[5] = (Euler[2] - __Start[5]) / CTRL_INTERVAL;

      // 规划路径
      __Trace.Schedule(__Start, __VStart, __End, __VEnd);

      // 如果跟踪目标在运动中，机器人总是滞后于目标，则轨迹具有相对较大的时间
      // 如果轨迹时间非常小，则说明目标已经停止
      if(__Trace.MoveTime < 0.05)
         __Trace.Stop();

      MoveTime = 0;
      MaxMoveTime = __Trace.MoveTime;
      __NewDst = false;
   }
   __Start[0] = Pos[0];
   __Start[1] = Pos[1];
   __Start[2] = Pos[2];
   __Start[3] = Euler[0];
   __Start[4] = Euler[1];
   __Start[5] = Euler[2];

   // 如果已经超过轨迹终止时间，则说明有可能上位机停止发送目标位姿
   // 则缓慢停止机器人运动，回退轨迹起始位姿
   MoveTime += CTRL_INTERVAL;
   if(MoveTime > MaxMoveTime)
      __Trace.Decay();

   // 计算机器人位姿
   __Trace.Position(MoveTime, PosEuler);
}
