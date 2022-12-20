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

   // ��ʼ��fpga�е��˶�ͨ��
   // ��ÿ��ͨ�����˶���������Ϊ0
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
   // ��Ŀ��λ�û���Ϊ������
   double Length2Pulse = 1000.0 * __PulsePerRound / __MMPerRound;
   for(int i = 0; i < 6; ++i)
      __DstPosition[i] = Robot.Jacks[i].ServoLength * Length2Pulse + 0.5;

   // ��ȡ��һ��������δ�ܷ�����������
   #ifndef __BORLANDC__
   for(int i = 0; i < 6; ++i)
      __PulseLeft[i] = fpga_read(i);
   #else
   for(int i = 0; i < 6; ++i)
      __PulseLeft[i] = 0;
   #endif
	 
   // ������һ�������ڵ��˶������ͷ���
   for(int i = 0; i < 6; ++i)
   {
      // ������һ�������ڽ�����ʵ�ʵ���λ��
      // �������Ϊ������˵��Ԥ��λ��û����ȫ������Ӧ����ȥʣ��������
      // �������Ϊ��������֮�෴
      if((__Direction >> i) & 0x01)
         __CurPosition[i] += __PulseCnt[i] - __PulseLeft[i];
      else
         __CurPosition[i] -= __PulseCnt[i] - __PulseLeft[i];

      // ���������������
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

      // ��ֹ��������������
      if(Delta > __MaxJackInc)
         __PulseCnt[i] = __MaxJackInc;
      else
         __PulseCnt[i] = Delta;

      // �����Ƶֵ
      // �����Ƶ�ʹ���ʱ�����������
      // ע�⣺Ŀǰ���õ�����ʱ��Ƶ��Ϊ1MHz
      if(__PulseCnt[i] > __MinJackInc)
         __DivCnt[i] = CalcFreqDivBase(__PulseCnt[i]);
      else
         __PulseCnt[i] = 0;
   }
	
   // �������������Ƶֵ�ͷ���fpga
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

   // �����������ȡ��λ����״̬������ѵ�����λ�㣬���ǹ������
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

   // ���δ����㣬�������˳�����λ�����˶���ֱ��������λ����
   // ע�⣺����������Ѿ�ȷ�����˵�����λ����ʱ������������壬���������ֱ����ÿ������д�̶������������������
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
