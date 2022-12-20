//---------------------------------------------------------------------------


#pragma hdrstop

#include "RobotServo.h"
#include <stdio.h>

#ifdef __BORLANDC__
#include <Forms.hpp>
#include "Unit1.h"
#else
#include "led.h"
#endif
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CRobotServo::CRobotServo(void)
 : __Zeroed(false),
	 __Direction(0),
   __CtrlInterval(0.1)
{
   SetServoTransParams(10000, 5.0);
   SetServoSpeedLimit(0.001, 0.1);
	
   for(int i = 0; i < 6; ++i)
      __PulseCnt[i] = 0;

   // 初始化fpga中的运动通道
   // 将每个通道的运动增量设置为0
   #ifndef __BORLANDC__
   FPGA_Timer_OFF;

   for(int i = 0; i < 6; ++i)
   {
      WriteFreqDivBase(i, 65535);
      WritePulseCnt(i, 0);
   }
   WriteDirection(0);
	
   FPGA_Timer_ON;
   #endif
}
//---------------------------------------------------------------------------
void CRobotServo::SetServoCtrlInterval(float Interval)
{
   __CtrlInterval = Interval;
}
//---------------------------------------------------------------------------
void CRobotServo::SetServoTransParams(int PulsePerRound, float MMPerRound)
{
   __PulsePerRound = PulsePerRound;
   __MMPerRound    = MMPerRound;
}
//---------------------------------------------------------------------------
void CRobotServo::SetServoSpeedLimit(float MinSpeed, float MaxSpeed)
{
   __MinJackInc = MinSpeed * 1000.0 * __CtrlInterval * __PulsePerRound / __MMPerRound;
   __MaxJackInc = MaxSpeed * 1000.0 * __CtrlInterval * __PulsePerRound / __MMPerRound;
}
//---------------------------------------------------------------------------
void CRobotServo::RobotMove(CRobot &Robot)
{
   // 将目标位置换算为脉冲数
   double Length2Pulse = 1000.0 * __PulsePerRound / __MMPerRound;
   for(int i = 0; i < 6; ++i)
      __DstPosition[i] = Robot.Jacks[i].ServoLength * Length2Pulse + 0.5;

   // 读取上一控制周期未能发出的脉冲数
   #ifndef __BORLANDC__
   for(int i = 0; i < 6; ++i)
      __PulseLeft[i] = fpga_read(i);
   #else
   for(int i = 0; i < 6; ++i)
      __PulseLeft[i] = 0;
   #endif
	 
   // 计算下一控制周期的运动增量和方向
   for(int i = 0; i < 6; ++i)
   {
      // 计算上一控制周期结束后，实际到达位置
      // 如果方向为正，则说明预期位置没有完全到达，因此应当减去剩余脉冲数
      // 如果方向为负，则与之相反
      if((__Direction >> i) & 0x01)
         __CurPosition[i] += __PulseCnt[i] - __PulseLeft[i];
      else
         __CurPosition[i] -= __PulseCnt[i] - __PulseLeft[i];

      // 计算脉冲输出数量
      unsigned int Delta;
      if(__DstPosition[i] >= __CurPosition[i])
      {
         Delta = __DstPosition[i] - __CurPosition[i];
         __Direction |= 0x01 << i;
      }
      else
      {
         Delta = __CurPosition[i] - __DstPosition[i];
         __Direction &= ~(0x01 << i);
      }

      // 防止脉冲数超过上限
      if(Delta > __MaxJackInc)
         __PulseCnt[i] = __MaxJackInc;
      else
         __PulseCnt[i] = Delta;

      // 计算分频值
      // 当输出频率过低时，不输出脉冲
      // 注意：目前采用的脉冲时钟频率为1MHz
      if(__PulseCnt[i] > __MinJackInc)
         __DivCnt[i] = CalcFreqDivBase(__PulseCnt[i]);
      else
         __PulseCnt[i] = 0;
   }
	
   // 输出脉冲数、分频值和方向到fpga
   #ifndef __BORLANDC__
   for(int i = 0; i < 6; ++i)
   {
      WriteFreqDivBase(i, __DivCnt[i]);
      WritePulseCnt(i, __PulseCnt[i]);
   }
   WriteDirection(__Direction);
   #else
   Form1->Panel38->Caption = IntToStr(__PulseCnt[0]);
   Form1->Panel40->Caption = IntToStr(__PulseCnt[1]);
   Form1->Panel42->Caption = IntToStr(__PulseCnt[2]);
   Form1->Panel44->Caption = IntToStr(__PulseCnt[3]);
   Form1->Panel46->Caption = IntToStr(__PulseCnt[4]);
   Form1->Panel48->Caption = IntToStr(__PulseCnt[5]);
   #endif
}
//---------------------------------------------------------------------------
bool Status = false;
void CRobotServo::GoZeroCtrl(void)
{
   /*
   if(Status)
      LED_GREEN_OFF;
   else
      LED_GREEN_ON;
   Status = !Status;
   */

   // 首先在这里读取限位开关状态，如果已到达限位点，则标记归零结束
   #ifndef __BORLANDC__
   int LmtSwitchLower = fpga_read(6);
   if(LmtSwitchLower & 0x03F == 0)
      __Zeroed = true;
   #else
   for(int i = 0; i < 6; ++i)
      __CurPosition[i] = 0;
   __Zeroed = true;
   #endif
	 
   //__Zeroed = true;

   // 如果未到零点，则令连杆朝向限位开关运动，直至到达限位开关
   // 注意：脉冲输出器已经确保连杆到达限位开关时，不再输出脉冲，因此在这里直接向每个连杆写固定脉冲数不会造成问题
   if(!__Zeroed)
   {
      int Pulse  = 0.01 * __CtrlInterval * 1000.0 * __PulsePerRound / __MMPerRound;
      int DivCnt = CalcFreqDivBase(Pulse);

      #ifndef __BORLANDC__
      for(int i = 0; i < 6; ++i)
         fpga_read(i);
      #endif
		 
      for(int i = 0; i < 6; ++i)
      {
         WriteFreqDivBase(i, DivCnt);
         WritePulseCnt(i, Pulse);
      }
      WriteDirection(0);
   }
}
