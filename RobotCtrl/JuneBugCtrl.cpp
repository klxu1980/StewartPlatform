//---------------------------------------------------------------------------
// 2021.12.30：修正了由于速度改变而产生的控制错误
// 2022.03.05：测试发现了两个主要问题：
//             1. 

#pragma hdrstop

#include "JuneBugCtrl.h"
#include "GlobalDef.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// CJuneBugCtrl()
//---------------------------------------------------------------------------
CJuneBugCtrl::CJuneBugCtrl(void)
 : XYHeight(0.01)
{
   // 设置机器人几何参数
   __Robot.UpperArmLength   = ROBOT_UPPER_ARM_LENGTH;
   __Robot.UpperBaseLength  = ROBOT_UPPER_BASE_LENGTH;
   __Robot.LowerArmLength   = ROBOT_LOWER_ARM_LENGTH;
   __Robot.LowerBaseLength  = ROBOT_LOWER_BASE_LENGTH;
   __Robot.UpperJointHeight = 0;
   __Robot.LowerJointHeight = 0;

   __Robot.JackFixedLength = JACK_FIXED_LENGTH;
   __Robot.JackServoLength = JACK_SERVO_LENGTH;
   __Robot.JackServoBuffer = JACK_SERVO_DEC;

   __Robot.InitStructureParams();

   MaxSpd[0] = 0.1;
   MaxSpd[1] = 0.1;
   MaxSpd[2] = 0.1;
   MaxSpd[3] = 20;
   MaxSpd[4] = 20;
   MaxSpd[5] = 20;
   MaxJackSpd = SERVO_RPM_MAX * SERVO_ROUND_MM * 0.001 / 60.0;

   MaxAcc[0] = 0.5;
   MaxAcc[1] = 0.5;
   MaxAcc[2] = 0.5;
   MaxAcc[3] = 2;
   MaxAcc[4] = 2;
   MaxAcc[5] = 2;

   Initialize();
}
//---------------------------------------------------------------------------
// Initialize()
//---------------------------------------------------------------------------
void CJuneBugCtrl::Initialize(void)
{
   __BugState = bsIdle;
   ScheduleIdleMovement();
}
//---------------------------------------------------------------------------
// Move()
//---------------------------------------------------------------------------
void CJuneBugCtrl::Move(void)
{
   switch(__BugState)
   {
   case bsIdle:
      StateIdle();
      break;
   case bsMoveUp:
   case bsMoveDown:
      StateMoveUpDown();
      break;
   case bsMoveUpDownIdle:
      StateMoveUpDownIdle();
      break;
   case bsMoveXYUpper:
   case bsMoveXYLower:
      StateMoveXY();
      break;
   case bsMoveXYIdleUpper:
   case bsMoveXYIdleLower:
      StateMoveXYIdle();
      break;
   }

   // 按照轨迹运动
   MoveByTrace();
}
//---------------------------------------------------------------------------
// MoveRequired()
//---------------------------------------------------------------------------
bool CJuneBugCtrl::MoveRequired(void)
{
   return (Length(Dx, Dy) > 0.1 || fabs(Yaw) > 2.0) && Speed > 0.1;
}
//---------------------------------------------------------------------------
// CalcCubicParams()
//---------------------------------------------------------------------------
void CJuneBugCtrl::CalcCubicParams(float T, float x0, float v0, float x1, float v1, float a[4])
{
   a[0] = x0;
   a[1] = v0;
   a[2] = (3 * (x1 - x0) - (2 * v0 + v1) * T) / (T * T);
   a[3] = (2 * (x0 - x1) + (v0 + v1) * T) / (T * T * T);
}
//---------------------------------------------------------------------------
// MoveByTrace()
//---------------------------------------------------------------------------
void CJuneBugCtrl::MoveByTrace(void)
{
   __Trace.Position(__MoveTime, PosEuler);
   __MoveTime += CTRL_INTERVAL;
}
//---------------------------------------------------------------------------
float max = 0;
bool CJuneBugCtrl::CheckJackOverSpeed(CMoveTrace &Trace, float Interval)
{
   float LstJack[6];
   float PosEuler[6];
   Trace.Position(0, PosEuler);
   __Robot.PlatformMove(PosEuler[0],
                        PosEuler[1],
                        PosEuler[2] + __Robot.CenterZ,
                        PosEuler[3],
                        PosEuler[4],
                        PosEuler[5]);
   for(int i = 0; i < 6; ++i)
      LstJack[i] = __Robot.Jack[i].Length;

   float MaxStep = SERVO_RPM_MAX * SERVO_ROUND_MM * 0.001 * Interval / 60.0;
   for(float T = 0; T < Trace.MoveTime; T += Interval)
   {
      Trace.Position(T, PosEuler);
      __Robot.PlatformMove(PosEuler[0],
                           PosEuler[1],
                           PosEuler[2] + __Robot.CenterZ,
                           PosEuler[3],
                           PosEuler[4],
                           PosEuler[5]);
      for(int i = 0; i < 6; ++i)
      {
         float xx = fabs(__Robot.Jack[i].Length - LstJack[i]);
         if(max < xx)
            max = xx;


         if(fabs(__Robot.Jack[i].Length - LstJack[i]) > MaxStep * 0.9)
            return false;
         LstJack[i] = __Robot.Jack[i].Length;
      }
   }
   return true;  
}
//---------------------------------------------------------------------------
// ScheduleMovement()
// 基于二分搜索规划轨迹，找出满足速度、加速度约束的最快路径
//---------------------------------------------------------------------------
void CJuneBugCtrl::ScheduleMovement(float Start[6], float VStart[6], float End[6], float VEnd[6])
{
   float S = (__SpdInUse > 0.1)? __SpdInUse : 0.1;
   for(int i = 0; i < 6; ++i)
   {
      __Trace.Trace[i].MaxS = MaxSpd[i] * S;
      __Trace.Trace[i].MaxA = MaxAcc[i] * S;
   }
   __Trace.Schedule(Start, VStart, End, VEnd);

   // 进一步检查运动过程中是否电缸超过速度上限
   // 从仿真测试看目前没有必要
   /*
   if(!CheckJackOverSpeed(__Trace, 0.1))
   {
      float T1 = __Trace.MoveTime;
      float T2 = 5;

      while(T2 - T1 > 0.01)
      {
         float T = (T1 + T2) * 0.5;
         __Trace.Schedule(T, Start, VStart, End, VEnd);
         __Trace.MoveTime = T;

         if(CheckJackOverSpeed(__Trace, 0.1) )
            T2 = T;
         else
            T1 = T;
      }
      __Trace.Schedule(T2, Start, VStart, End, VEnd);
      __Trace.MoveTime = T2;
   }
   */

   __MoveTime = 0;
   __MaxMoveTime = __Trace.MoveTime;
}
//---------------------------------------------------------------------------
// ScheduleMovement()
// 机器人正常运动时，新的运动轨迹的起始位置和速度应当与
// 前一阶段运动轨迹的终止位置速度一致，从而避免速度加速度突变
//---------------------------------------------------------------------------
void CJuneBugCtrl::ScheduleMovement(float End[6], float VEnd[6])
{
   float Start[6], VStart[6];
   __Trace.Position(__MoveTime, Start);
   __Trace.Speed(__MoveTime, VStart);
   ScheduleMovement(Start, VStart, End, VEnd);
}
//---------------------------------------------------------------------------
// ScheduleIdleMovement()
// 机器人中立位置时，运动轨迹为0，机器人保持静止不动
//---------------------------------------------------------------------------
void CJuneBugCtrl::ScheduleIdleMovement(void)
{
   for(int i = 0; i < 6; ++i)
      __Trace.Trace[i].SetZero();
   __MoveTime = 0;
}
//---------------------------------------------------------------------------
// ScheduleXYMovement()
// 规划机器人在XY平面上的运动轨迹
//---------------------------------------------------------------------------
void CJuneBugCtrl::ScheduleXYMovement(float XYHeight, float Dx, float Dy, float Yaw)
{
   // Dx, Dy为[-1, 1]之间的独立变量，将其转换为(Dx, Dy, Step)，
   // 使(Dx, Dy)表示方向(Length(Dx, Dy) == 0)，Step \in [0, 1]表示相对步长
   float Step;
   float XYLen = Length(Dx, Dy);
   if(XYLen < 0.1)
      Step = Dx = Dy = 0;
   else
   {
      Dx  /= XYLen;
      Dy  /= XYLen;
      Step = Max(fabs(Dx), fabs(Dy));
   }
   
   if(XYHeight >= 0)
   {
      // 实际运动长度(m)等于(Dx, Dy, Yaw)方向上的最大直线运动量，乘以相对步长
      float Dist = SearchForTheLargestXYStep(XYHeight, Dx, Dy, Yaw) * Step;

      // 轨迹末端位姿和速度(速度均为0)
      float End[6]  = {Dist * Dx, Dist * Dy, XYHeight, Yaw, 0, 0};
      float VEnd[6] = {0, 0, 0, 0, 0, 0};

      // 规划每个轴的运动轨迹
      ScheduleMovement(End, VEnd);
   }
   else
   {
      float Dist    = SearchForTheLargestXYStep(-XYHeight, -Dx, -Dy, -Yaw) * Step;
      float End[6]  = {-Dist * Dx, -Dist * Dy, XYHeight, -Yaw, 0, 0};
      float VEnd[6] = {0, 0, 0, 0, 0, 0};

      ScheduleMovement(End, VEnd);
   }
}
//---------------------------------------------------------------------------
// SearchForTheLargestStep()
// 采用二分法搜索给定方向上的最大步长
//---------------------------------------------------------------------------
float CJuneBugCtrl::SearchForTheLargestXYStep(float Z, float Dx, float Dy, float Yaw)
{
   if(Dx == 0 && Dy == 0)
      return 0;

   float L1 = 0;
   float L2 = 1;     // 单位：m

   while(L2 - L1 > 0.001)
   {
      float L = (L1 + L2) * 0.5;
      float X = L * Dx;
      float Y = L * Dy;
      __Robot.PlatformMove(X, Y, Z + __Robot.CenterZ, Yaw, 0, 0);

      if(__Robot.Constrained)
         L2 = L;
      else
         L1 = L;
   }
   
   return L1;
}
//---------------------------------------------------------------------------
// StateIdle()
// 机器人静止状态
//---------------------------------------------------------------------------
void CJuneBugCtrl::StateIdle(void)
{
   if(MoveRequired())
   {
      // 从IDLE状态转入运动时，机器人首先向上运动，使上三足离开地面
      __BugState = bsMoveUp;

      // 规划运动路径，由中立位置向XY上平面运动
      float End[6]  = {0, 0, XYHeight, 0, 0, 0};
      float VEnd[6] = {0, 0, 0, 0, 0, 0};

      __SpdInUse = Speed;
      ScheduleMovement(End, VEnd);
   }
   else
   {
      // 没有要求运动，则机器人停留在中立位置
      ScheduleIdleMovement();
   }
}
//---------------------------------------------------------------------------
// StateMoveUpDown()
// 机器人沿Z轴向上或向下运动，从而使上三足或下三足离开地面
//---------------------------------------------------------------------------
void CJuneBugCtrl::StateMoveUpDown(void)
{
   if(!MoveRequired())
   {
      float PosEuler[6];
      __Trace.Position(__MoveTime, PosEuler);

      if(__MoveTime >= __MaxMoveTime)
      {
         __BugState = (PosEuler[2] > 0)? bsMoveXYIdleUpper : bsMoveXYIdleLower;


         // 规划回归中立位置的运动轨迹
         float End[6]  = {0, 0, (PosEuler[2] > 0)? XYHeight : -XYHeight,
                          0, 0, 0};
         float VEnd[6] = {0, 0, 0, 0, 0, 0};

         ScheduleMovement(End, VEnd);
      }
      else if(__BugState == bsMoveDown)
      {
         if(PosEuler[2] > 0)
         {
            __BugState = bsMoveUp;

            // 规划回归中立位置的运动轨迹
            float End[6]  = {PosEuler[0], PosEuler[1], XYHeight, 0, 0, 0};
            float VEnd[6] = {0, 0, 0, 0, 0, 0};

            ScheduleMovement(End, VEnd);
         }
      }
      else
      {
         if(PosEuler[2] < 0)
         {
            __BugState = bsMoveDown;

            // 规划回归中立位置的运动轨迹
            float End[6]  = {PosEuler[0], PosEuler[1], -XYHeight, 0, 0, 0};
            float VEnd[6] = {0, 0, 0, 0, 0, 0};

            ScheduleMovement(End, VEnd);
         }
      }
   }
   else if(__MoveTime >= __MaxMoveTime)
   {
      // 完成轨迹，根据前一状态判断当前处于上平面或下平面
      __SpdInUse = Speed;
      if(__BugState == bsMoveUp)
      {
         __BugState = bsMoveXYUpper;
         ScheduleXYMovement(XYHeight, Dx, Dy, Yaw);
      }
      else
      {
         __BugState = bsMoveXYLower;
         ScheduleXYMovement(-XYHeight, Dx, Dy, Yaw);
      }
   }
}
//----------------------------------------------------------------------------
// StateMoveUpDownIdle()
//----------------------------------------------------------------------------
void CJuneBugCtrl::StateMoveUpDownIdle(void)
{
   if(__MoveTime >= __MaxMoveTime)
   {
      __BugState = bsIdle;
      ScheduleIdleMovement();
   }
}
//----------------------------------------------------------------------------
// StateMoveXY()
//----------------------------------------------------------------------------
void CJuneBugCtrl::StateMoveXY(void)
{
   if(!MoveRequired())
   {
      // 不再要求运动，回归中立位置
      if(__BugState == bsMoveXYUpper)
      {
         __BugState = bsMoveXYIdleUpper;

         float End[6]  = {0, 0, XYHeight, 0, 0, 0};
         float VEnd[6] = {0, 0, 0, 0, 0, 0};
         ScheduleMovement(End, VEnd);
      }
      else
      {
         __BugState = bsMoveXYIdleLower;

         float End[6]  = {0, 0, -XYHeight, 0, 0, 0};
         float VEnd[6] = {0, 0, 0, 0, 0, 0};
         ScheduleMovement(End, VEnd);
      }
   }
   else if(__MoveTime >= __MaxMoveTime)
   {
      // 运动方向有可能发生改变，因此需要判断是上三足还是下三足运动最有利
      float Step1 = SearchForTheLargestXYStep(XYHeight, Dx, Dy, Yaw);
      float Step2 = SearchForTheLargestXYStep(-XYHeight, -Dx, -Dy, -Yaw);

      float CurX   = __Trace.Trace[0].Position(__MoveTime);
      float CurY   = __Trace.Trace[1].Position(__MoveTime);
      float CurYaw = __Trace.Trace[3].Position(__MoveTime);

      CBugState NxtState;
      if(Length(CurX - Step1 * Dx, CurY - Step1 * Dy, (CurYaw - Yaw) * 0.1) >
         Length(CurX + Step2 * Dx, CurY + Step2 * Dy, (CurYaw + Yaw) * 0.1) )
      {
         NxtState = bsMoveXYUpper;
      }
      else
      {
         NxtState = bsMoveXYLower;
      }

      __SpdInUse = Speed;
      if(__BugState != NxtState)
      {
         float DstHeight;
         if(NxtState == bsMoveXYLower)
         {
            __BugState = bsMoveDown;
            DstHeight  = -XYHeight;
         }
         else
         {
            __BugState = bsMoveUp;
            DstHeight  = XYHeight;
         }

         float End[6]  = {CurX, CurY, DstHeight, CurYaw, 0, 0};
         float VEnd[6] = {0, 0, 0, 0, 0, 0};
         ScheduleMovement(End, VEnd);
      }
      else
      {
         __BugState = NxtState;
         if(NxtState == bsMoveXYLower)
            ScheduleXYMovement(-XYHeight, Dx, Dy, Yaw);
         else
            ScheduleXYMovement(XYHeight, Dx, Dy, Yaw);
      }
   }
}
//----------------------------------------------------------------------------
// StateMoveXYIdle()
//----------------------------------------------------------------------------
void CJuneBugCtrl::StateMoveXYIdle(void)
{
   if(__MoveTime >= __MaxMoveTime)
   {
      if(MoveRequired())
      {
         __SpdInUse = Speed;
         if(__BugState == bsMoveXYIdleUpper)
         {
            __BugState = bsMoveXYUpper;
            ScheduleXYMovement(XYHeight, Dx, Dy, Yaw);
         }
         else
         {
            __BugState = bsMoveXYLower;
            ScheduleXYMovement(-XYHeight, Dx, Dy, Yaw);
         }
      }
      else
      {
         // 已经运动到中心位置，垂直运动到中立位置
         __BugState = bsMoveUpDownIdle;

         float End[6]  = {0, 0, 0, 0, 0, 0};
         float VEnd[6] = {0, 0, 0, 0, 0, 0};
         ScheduleMovement(End, VEnd);
      }
   }
}
