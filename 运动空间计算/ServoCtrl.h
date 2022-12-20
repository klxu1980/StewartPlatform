//---------------------------------------------------------------------------

#ifndef ServoCtrlH
#define ServoCtrlH
#include <Classes.hpp>
//---------------------------------------------------------------------------
class CServoCtrl
{
private:
   HANDLE  __hComm;                 // 通信串口
   int     __ServoAddr;             // 伺服地址
   int     __NxtSegment;            // 下一个要写入的分段号
   int     __PulseCnt;              // 脉冲总量
private:
   BYTE    __FdkBuffer[48];         // 伺服应答缓冲
   int     __FdkCnt;                // 应答字节数
private:
   WORD  CalcCRC(BYTE *Order, int Size);                           // 计算CRC
   bool  CheckCRC(BYTE *Buffer, int RxCnt);
   void  AppendCRC(BYTE *Buffer, int TxCnt);
private:
   bool WriteMultiWords(int Addr, WORD *Values, int WordCnt);     // 写多个数值寄存器
   bool ReadMultiWords(int Addr, WORD *Values, int WordCnt);      // 读多个数值寄存器
   void ReadServoFdk(BYTE *FdkBuffer, int &FdkCnt);               // 读伺服应答
private:
   void SendIncToSegment(int Segment, float Step, float Speed);   // 发送位置增量指令，步长单位m，速度单位m/s
   void SendSegmentID(int Segment);                               // 设置控制段编号
   bool WaitForServoFdk(void);                                    // 等待伺服控制器应答
public:
   CServoCtrl(int ServoAddr, AnsiString Comm);
public:
   // SendIncrement()用于将运动增量(即步长及速度)写入伺服控制器中(步长单位为m，速度单位为m/s)
   // 但是，运动增量只是写入了由__NxtSegment指定的控制段寄存器中，
   // 通过调用Move()函数，将__NxtSegment写入伺服控制器中，伺服才会真正运动
   void SendIncrement(float Step, float Speed);
   void Move(void);
public:
   bool ReadServo(void);
   void Zero(void);
public:
   float CurLength(void);     // 电缸当前伸展长度(单位m)
};
#endif
