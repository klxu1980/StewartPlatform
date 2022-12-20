//---------------------------------------------------------------------------


#pragma hdrstop

#include "RobotServo.h"
#include <stdio.h>
#include "GlobalDef.h"

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
   __CtrlInterval(CTRL_INTERVAL)
{
   SetServoTransParams(SERVO_PULSE_ROUND, SERVO_ROUND_MM);
   SetServoSpeedLimit(SERVO_SPEED_MIN, SERVO_SPEED_MAX);
	
   for(int i = 0; i < 6; ++i)
   {
      __PulseCnt[i]    = 0;
      __CurPosition[i] = 0;   
   }

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
   __MinJackInc = MinSpeed * __CtrlInterval * __PulsePerRound / __MMPerRound;
   __MaxJackInc = MaxSpeed * __CtrlInterval * __PulsePerRound / __MMPerRound;
}
//---------------------------------------------------------------------------
void CRobotServo::SetJackLimit(float MinLength, float MaxLength)
{
   __MinServoLength = MinLength;
   __MaxServoLength = MaxLength;
}
//---------------------------------------------------------------------------
void CRobotServo::ServoMove(void)
{
   // 读取下部限位开关状态
   int LmtSwitchLower = ReadLmtSwitchLower();
   
   // 读取上一控制周期未能发出的脉冲数
   // 注意：由于FPGA程序的问题，必须首先读取每个通道的剩余脉冲数
   for(int i = 0; i < 6; ++i)
      __PulseLeft[i] = ReadPulseLeft(i); 

   // 计算下一控制周期的运动增量和方向
   for(int i = 0; i < 6; ++i)
   {
      if(LmtSwitchLower & (0x01 << i))   // 注意：这里需要实测下!!!!!!!!!!!!!!!!
      {
         __CurPosition[i] = 0;
         continue;
      }
      else
      {
         // 计算上一控制周期结束后，实际到达位置
         // 如果方向为正，则说明预期位置没有完全到达，因此应当减去剩余脉冲数
         // 如果方向为负，则与之相反
         if((__Direction >> i) & 0x01)
            __CurPosition[i] += __PulseCnt[i] - __PulseLeft[i];
         else
            __CurPosition[i] -= __PulseCnt[i] - __PulseLeft[i];
      }

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
   if(Form1->ListView3->Items->Count)
   {
      for(int i = 0; i < 6; ++i)
      {
         Form1->ListView3->Items->Item[i]->SubItems->Strings[0] = AnsiString().sprintf("%8.1f", JackLength(i) * 1000);
         Form1->ListView3->Items->Item[i]->SubItems->Strings[1] = IntToStr(__PulseCnt[i]);
         Form1->ListView3->Items->Item[i]->SubItems->Strings[2] = AnsiString().sprintf("%8.1f", __PulseCnt[i] * 60.0 / (__PulsePerRound * __CtrlInterval) );
      }
   }
   #endif
}
//---------------------------------------------------------------------------
void CRobotServo::RobotMove(CRobot &Robot, bool NoLimit)
{
   // 将目标位置换算为脉冲数
   double Length2Pulse = __PulsePerRound / __MMPerRound;
   for(int i = 0; i < 6; ++i)
   {
      double ServoLength = Robot.Jacks[i].ServoLength * 1000;

      if(!NoLimit)
      {
      if(ServoLength < __MinServoLength)
         ServoLength = __MinServoLength;
      else if(ServoLength > __MaxServoLength)
         ServoLength = __MaxServoLength;
      }

      __DstPosition[i] = ServoLength * Length2Pulse + 0.5;
   }
}
//---------------------------------------------------------------------------
bool Status = false;
void CRobotServo::GoZeroCtrl(void)
{
   int Pulse  = GO_ZERO_SPEED * __CtrlInterval * 1000.0 * __PulsePerRound / __MMPerRound;
   int DivCnt = CalcFreqDivBase(Pulse);

   #ifndef __BORLANDC__
   for(int i = 0; i < 6; ++i)
      fpga_read(i);

   for(int i = 0; i < 6; ++i)
   {
      WriteFreqDivBase(i, DivCnt);
      WritePulseCnt(i, Pulse);
   }
   WriteDirection(0);
   #else
   if(Form1->ListView3->Items->Count)
   {
      // 更新显示当前位置
      for(int i = 0; i < 6; ++i)
      {
         __CurPosition[i] -= Pulse;
         if(__CurPosition[i] < 0)
            __CurPosition[i] = 0;

         Form1->ListView3->Items->Item[i]->SubItems->Strings[0] = AnsiString().sprintf("%8.1f", JackLength(i) * 1000);
         Form1->ListView3->Items->Item[i]->SubItems->Strings[1] = IntToStr(Pulse);
         Form1->ListView3->Items->Item[i]->SubItems->Strings[2] = AnsiString().sprintf("%8.1f", Pulse * 60.0 / (__PulsePerRound * __CtrlInterval) );
      }
   }
   #endif
}
//---------------------------------------------------------------------------
void CRobotServo::SetJackLength(int JackID, int JackLength, int JackSpeed)
{
   // 将目标位置换算为脉冲数
   if(JackLength < __MinServoLength)
      JackLength = __MinServoLength;
   else if(JackLength > __MaxServoLength)
      JackLength = __MaxServoLength;
   __DstPosition[JackID] = JackLength * __PulsePerRound / __MMPerRound + 0.5;
}
//---------------------------------------------------------------------------
void CRobotServo::GoZero(void)
{
   __Zeroed = false;
}
//---------------------------------------------------------------------------
bool CRobotServo::Zeroed(void)
{
   #ifndef __BORLANDC__
   if((ReadLmtSwitchLower() & 0x03F) == 0x3F)
   {
      __Zeroed = true;
      for(int i = 0; i < 6; ++i)
         __CurPosition[i] = 0;
   }
   #else
   if(__CurPosition[0] <= 0 && __CurPosition[1] <= 0 && __CurPosition[2] <= 0 &&
      __CurPosition[3] <= 0 && __CurPosition[4] <= 0 && __CurPosition[5] <= 0)
   {
      __Zeroed = true;
   }
   #endif

   return __Zeroed;
}
