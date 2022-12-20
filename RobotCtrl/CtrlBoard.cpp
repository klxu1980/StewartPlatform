//---------------------------------------------------------------------------


#pragma hdrstop

#include "CtrlBoard.h"
#ifndef __BORLANDC__
#include "usart.h"
#endif

#include "CtrlSystem.h"
#include "GlobalDef.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CCtrlBoard CtrlBoard;
//---------------------------------------------------------------------------
CCtrlBoard::CCtrlBoard(void)
{
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
// RefreshDIStatus()
//---------------------------------------------------------------------------
void CCtrlBoard::RefreshDIStatus(void)
{
#ifndef __BORLANDC__
   unsigned short Upper = ~fpga_read(7);
	 unsigned short Lower = ~fpga_read(6);
#else
   unsigned short Lower = 0;
   unsigned short Upper = 0;
#endif
   for(int i = 0; i < 6; ++i)
   {
      DILower[i] = Lower & (0x01 << i);
      DIUpper[i] = Upper & (0x01 << i);
   }
}
//---------------------------------------------------------------------------
// RefreshPulseLeft()
//---------------------------------------------------------------------------
void CCtrlBoard::RefreshPulseLeft(void)
{
   // 读取上一控制周期未能发出的脉冲数
   // 注意：由于FPGA程序的问题，必须首先读取每个通道的剩余脉冲数
#ifndef __BORLANDC__
   for(int i = 0; i < 6; ++i)
      PulseLeft[i] = fpga_read(i);
#else
   for(int i = 0; i < 6; ++i)
      PulseLeft[i] = 0;
#endif
}
//---------------------------------------------------------------------------
// OutputPulse()
//---------------------------------------------------------------------------
void CCtrlBoard::OutputPulse(int Chan, int Pulse)
{
   if(Pulse > 0)
   { 
      // 根据控制周期内需要发出的脉冲数，计算脉冲频率，并转换为分频数
      // 将分频数写入FPGA，控制脉冲输出频率
      // 将脉冲数量写入FPGA
      unsigned short DivCnt = PULSE_SRC_FREQUENCY * CTRL_INTERVAL / Pulse + 0.5; 
      WriteFreqDivBase(Chan, DivCnt);
      WritePulseCnt(Chan, Pulse);
   }
   else
      WritePulseCnt(Chan, 0);
}
//---------------------------------------------------------------------------
// OutputDirection()
//---------------------------------------------------------------------------
void CCtrlBoard::OutputDirection(bool Direction[6])
{	
   unsigned short DirWORD = 0;

   DirWORD |= Direction[0]? 0x01 : 0x0;
   DirWORD |= Direction[1]? 0x02 : 0x0;
   DirWORD |= Direction[2]? 0x04 : 0x0;
   DirWORD |= Direction[3]? 0x08 : 0x0;
   DirWORD |= Direction[4]? 0x10 : 0x0;
   DirWORD |= Direction[5]? 0x20 : 0x0;

   WriteDirection(DirWORD);
}
//---------------------------------------------------------------------------
// OutputDirection()
//---------------------------------------------------------------------------
void CCtrlBoard::OutputDirection(bool Direction)
{
	 // Direction = true;     // 需要让电缸伸出来时，设置为true
   WriteDirection(Direction? 0x3F : 0x0);
}
//--------------------------------------------------------------------------
// RcvByteFromUART2()
//--------------------------------------------------------------------------
bool CCtrlBoard::RcvByteFromUART2(unsigned char Byte)
{
#ifdef SYS_STABLE_CTRL
   return CtrlSystem.StableController().AccFdkBwd.ReceiveValueByte(Byte);	
#endif
}
//--------------------------------------------------------------------------
// RcvByteFromUART3()
//--------------------------------------------------------------------------
bool CCtrlBoard::RcvByteFromUART3(unsigned char Byte)
{
#ifndef SYS_STABLE_CTRL
	return CtrlSystem.RcvCommandByte(Byte);
#else
   return CtrlSystem.StableController().AccFdkFwd.ReceiveValueByte(Byte);	
#endif
}
//--------------------------------------------------------------------------
// FdkForUART2()
//--------------------------------------------------------------------------
bool CCtrlBoard::FdkForUART2(unsigned char **pBuffer, int *size)
{
	return false;
}
//--------------------------------------------------------------------------
// FdkForUART3()
//--------------------------------------------------------------------------
bool CCtrlBoard::FdkForUART3(unsigned char **pBuffer, int *size)
{
#ifndef SYS_STABLE_CTRL
	return CtrlSystem.FdkBuffer(pBuffer, size);
#else
	return false;
#endif
}
