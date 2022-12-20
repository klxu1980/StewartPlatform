//---------------------------------------------------------------------------

#ifndef CtrlBoardH
#define CtrlBoardH
#include "GlobalDef.h"

#ifndef __BORLANDC__
#include "led.h"
#include "fsmc.h"
#endif
//---------------------------------------------------------------------------
class CCtrlBoard
{     
public:
   bool           DIUpper[6];             // 上限位开关输入
   bool           DILower[6];             // 下限位开关输入
   unsigned short PulseLeft[6];           // 每个通道上一控制周期未完成的脉冲数量
private:
#ifndef __BORLANDC__
   void WriteFreqDivBase(int Idx, int Base) {fpga_write(Idx, Base);}
   void WritePulseCnt(int Idx, int PulseCnt){fpga_write(Idx + 6, PulseCnt);}
   void WriteDirection(int Direction)       {fpga_write(12, Direction);}
#else
   void WriteFreqDivBase(int Idx, int Base) {}
   void WritePulseCnt(int Idx, int PulseCnt){}
   void WriteDirection(int Direction)       {}
#endif
public:
   CCtrlBoard(void);
public:
   void RefreshDIStatus(void);                // 更新DI输入
   void RefreshPulseLeft(void);               // 更新前次脉冲输出剩余脉冲数
   void OutputPulse(int Chan, int Pulse);     // 输出脉冲
   void OutputDirection(bool Direction[6]);   // 输出运动方向
   void OutputDirection(bool Direction);      // 输出运动方向(6通道同方向)
public:
	 bool RcvByteFromUART2(unsigned char Byte);               // 从UART2接收到一个字节，如果接收到一个完整报文，则返回true。注意，硬件部分应当调用该函数传递接收到的字节。
   bool RcvByteFromUART3(unsigned char Byte);               // 同上
   bool FdkForUART2(unsigned char **pBuffer, int *size);    // 通过UART2返回应答报文，如果需要发送应答，则函数返回true。
   bool FdkForUART3(unsigned char **pBuffer, int *size);    // 同上
};
extern CCtrlBoard CtrlBoard;
#endif

// 串口通信部分需要改进
