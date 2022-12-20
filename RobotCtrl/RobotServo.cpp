//---------------------------------------------------------------------------


#pragma hdrstop

#include "RobotServo.h"
#include <stdio.h>

#ifdef __BORLANDC__
#include <Forms.hpp>
#include "Unit1.h"
#else
#include "led.h"
#include "usart.h"
#endif
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CRobotServo::CRobotServo(void)
 : __Zeroing(false)
{
   // 设置伺服传动参数(转动一周脉冲数、导程)
   // 设置伺服速度上下限
   __MinPulse      = (SERVO_RPM_MIN / 60.0) * CTRL_INTERVAL * SERVO_PULSE_ROUND;
   __MaxPulse      = (SERVO_RPM_MAX / 60.0) * CTRL_INTERVAL * SERVO_PULSE_ROUND;
   __MaxAccByPulse = (SERVO_RPM_MAX / 60.0) * SERVO_PULSE_ROUND / SERVO_FULL_SPD_ACC_TIME;

   // 初始化脉冲计数器和当前位置
   for(int i = 0; i < 6; ++i)
   {
      __PulseCnt[i]    = 0;
      __CurPosition[i] = 0;
      __Direction[i]   = false;
   }
}
//---------------------------------------------------------------------------
// ServoCtrl()
//---------------------------------------------------------------------------
void CRobotServo::ServoCtrl(void)
{
   if(__Zeroing)
      GoZeroCtrl();
   else
      NormalCtrl();
}
//---------------------------------------------------------------------------
// NormalCtrl()
//---------------------------------------------------------------------------
void CRobotServo::NormalCtrl(void)
{
   // 读取下部限位开关状态
   CtrlBoard.RefreshDIStatus();
   
   // 读取上一控制周期未能发出的脉冲数
   // 注意：由于FPGA程序的问题，必须首先读取每个通道的剩余脉冲数
   CtrlBoard.RefreshPulseLeft();

   // 计算下一控制周期的运动增量和方向
   for(int i = 0; i < ACTIVE_SERVO_CNT; ++i)
   {
      if(CtrlBoard.DILower[i])   // 如果遇到下限位开关，则当前位置清零
         __CurPosition[i] = 0;
      else
      {
         // 计算上一控制周期结束后，实际到达位置
         // 如果方向为正，则说明预期位置没有完全到达，因此应当减去剩余脉冲数
         // 如果方向为负，则与之相反
         if(__Direction[i])
            __CurPosition[i] -= CtrlBoard.PulseLeft[i];
         else
            __CurPosition[i] += CtrlBoard.PulseLeft[i];
      }

      // 对输出进行限幅，避免加速度过大出现机械震动
      int DstPosition = FilterDestination(i, __DstPosition[i]);

      // 计算脉冲输出数量
      unsigned int Delta;
      if(DstPosition >= __CurPosition[i])
      {
         Delta = DstPosition - __CurPosition[i];
         __Direction[i] = true;
      }
      else
      {
         Delta = __CurPosition[i] - DstPosition;
         __Direction[i] = false;
      }
      __PulseCnt[i] = Delta;

      // 防止脉冲数超过上限
      if(Delta > __MaxPulse)
         __PulseCnt[i] = __MaxPulse;

      // 防止脉冲数超过下限
      if(Delta < __MinPulse)
         __PulseCnt[i] = 0;

      // 本次控制周期结束时，预期到达的位置
      if(__Direction[i])
         __CurPosition[i] += __PulseCnt[i];
      else
         __CurPosition[i] -= __PulseCnt[i];
   }
	
   // 输出脉冲数、分频值和方向到fpga
#ifndef __BORLANDC__
   for(int i = 0; i < ACTIVE_SERVO_CNT; ++i)
      CtrlBoard.OutputPulse(i, __PulseCnt[i]);
   CtrlBoard.OutputDirection(__Direction);
#else
   if(Form1->ListViewJacks->Items->Count)
   {
      for(int i = 0; i < 6; ++i)
      {
         Form1->ListViewJacks->Items->Item[i]->SubItems->Strings[0] = AnsiString().sprintf("%8.1f", __CurPosition[i] * SERVO_ROUND_MM / SERVO_PULSE_ROUND);
         Form1->ListViewJacks->Items->Item[i]->SubItems->Strings[1] = IntToStr(__PulseCnt[i]);
         Form1->ListViewJacks->Items->Item[i]->SubItems->Strings[2] = AnsiString().sprintf("%8.1f", __PulseCnt[i] * 60.0 / (SERVO_PULSE_ROUND * CTRL_INTERVAL) );
      }
   }
#endif
}
//---------------------------------------------------------------------------
void CRobotServo::GoZeroCtrl(void)
{
   // 计算每个控制周期中，归零脉冲数和频率
   int Pulse = GO_ZERO_RPM * SERVO_PULSE_ROUND * CTRL_INTERVAL / 60.0;

#ifndef __BORLANDC__
   CtrlBoard.RefreshPulseLeft();
   CtrlBoard.RefreshDIStatus();

   for(int i = 0; i < ACTIVE_SERVO_CNT; ++i)
   {
      if(CtrlBoard.DILower[i])
         __CurPosition[i] = 0;
      CtrlBoard.OutputPulse(i, Pulse);

      __Positions[i][0] = __Positions[i][1] = __Positions[i][2] = 0;
   }
   CtrlBoard.OutputDirection(false);
#else
   for(int i = 0; i < ACTIVE_SERVO_CNT; ++i)
   {
      __CurPosition[i] -= Pulse;
      if(__CurPosition[i] < 0)
         __CurPosition[i] = 0;

      __Positions[i][0] = __Positions[i][1] = __Positions[i][2] = 0;
   }
#endif
}
//---------------------------------------------------------------------------
void CRobotServo::RobotMove(CRobot &Robot)
{
   // 将目标位置换算为脉冲数
   double Length2Pulse = SERVO_PULSE_ROUND / SERVO_ROUND_MM;
   
   __DstPosition[0] = Robot.Jack[0].Servo * (SERVO_PULSE_ROUND / SERVO_ROUND_MM) * 1000.0 + 0.5;
   __DstPosition[1] = Robot.Jack[1].Servo * (SERVO_PULSE_ROUND / SERVO_ROUND_MM) * 1000.0 + 0.5;
   __DstPosition[2] = Robot.Jack[2].Servo * (SERVO_PULSE_ROUND / SERVO_ROUND_MM) * 1000.0 + 0.5;
   __DstPosition[3] = Robot.Jack[3].Servo * (SERVO_PULSE_ROUND / SERVO_ROUND_MM) * 1000.0 + 0.5;
   __DstPosition[4] = Robot.Jack[4].Servo * (SERVO_PULSE_ROUND / SERVO_ROUND_MM) * 1000.0 + 0.5;
   __DstPosition[5] = Robot.Jack[5].Servo * (SERVO_PULSE_ROUND / SERVO_ROUND_MM) * 1000.0 + 0.5;
}
//---------------------------------------------------------------------------
bool CRobotServo::IsAllZeroed(void)
{
   __Zeroing = false;
#ifndef __BORLANDC__
   for(int i = 0; i < ACTIVE_SERVO_CNT; ++i)
      if(!CtrlBoard.DILower[i])
      {
         __Zeroing = true;
         return false;
      }
#else			
   for(int i = 0; i < ACTIVE_SERVO_CNT; ++i)
      if(__CurPosition[0] > 0)
      {
         __Zeroing = true;
         return false;
      }
#endif

   // 归零后的一些状态初始化操作
   for(int i = 0; i < ACTIVE_SERVO_CNT; ++i)
	 {
      __Positions[i][0] = 0;
		  __Positions[i][1] = 0;
		  __Positions[i][2] = 0;
		  __CurPosition[i]  = 0;
	 }

   return true;
}
//---------------------------------------------------------------------------
int CRobotServo::FilterDestination(int Idx, int DstPosition)
{
   // 计算给定跟踪位置所产生的加速度，对该加速度限幅
   __Positions[Idx][2] = __Positions[Idx][1];
   __Positions[Idx][1] = __CurPosition[Idx];
   __Positions[Idx][0] = DstPosition;

   int a = (__Positions[Idx][0] - 2 * __Positions[Idx][1] + __Positions[Idx][2]) / (CTRL_INTERVAL * CTRL_INTERVAL);
   if(a > __MaxAccByPulse)
      a = __MaxAccByPulse;
   else if(a < -__MaxAccByPulse)
      a = -__MaxAccByPulse;

   __Positions[Idx][0] = 2 * __Positions[Idx][1] - __Positions[Idx][2] + a * (CTRL_INTERVAL * CTRL_INTERVAL);

   return __Positions[Idx][0];
}
