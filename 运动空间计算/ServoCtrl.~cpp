//---------------------------------------------------------------------------


#pragma hdrstop

#include "ServoCtrl.h"
#include <Forms.hpp>
//---------------------------------------------------------------------------
#define  MM_TO_PULSE   2500.0
#define  MM_TO_ROUND   0.25     // 伺服转动一周需要10000脉冲，电缸运动1mm需要2500脉冲，因此伺服转动一周电缸运动4mm
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
// CServoCtrl()
//---------------------------------------------------------------------------
CServoCtrl::CServoCtrl(int ServoAddr, AnsiString Comm)
        : __hComm(NULL),
          __ServoAddr(ServoAddr),
          __NxtSegment(1)
{
   // 初始化串口
   __hComm = CreateFile(Comm.c_str(),                   //打开串口
                        GENERIC_READ | GENERIC_WRITE,   //读写方式
                        0,                              //不能共享
                        NULL,                           //不用安全结构
                        OPEN_EXISTING,                  //打开已存在的设备
                        FILE_FLAG_WRITE_THROUGH,        //同步方式
                        0);                             //无模板

   if((unsigned long)__hComm == 0xFFFFFFFF)
   {
      Application->MessageBox(("无法打开串口" + Comm).c_str(), "错误", MB_OK | MB_ICONERROR);
      return;
   }

   //设置串口属性
   DCB CommDCB;
   if(GetCommState(__hComm, &CommDCB))
   {
      CommDCB.BaudRate = 115200;
      CommDCB.ByteSize = 8;
      CommDCB.Parity   = 2;
      CommDCB.StopBits = 0;
      
      if(!SetCommState(__hComm, &CommDCB))
         throw Exception("设置串口属性错误!");
   }
   else
      throw Exception("读取串口属性错误!");

   //设置超时
   COMMTIMEOUTS CommTimeouts;
   GetCommTimeouts(__hComm, &CommTimeouts);
   CommTimeouts.ReadIntervalTimeout        = MAXDWORD;
   CommTimeouts.ReadTotalTimeoutMultiplier = 0;
   CommTimeouts.ReadTotalTimeoutConstant   = 0;
   SetCommTimeouts(__hComm, &CommTimeouts);
}
//--------------------------------------------------------------------------
// CalcCRC()
//--------------------------------------------------------------------------
WORD CServoCtrl::CalcCRC(BYTE *Buffer, int Count)
{
   WORD CRC = 0xFFFF;

   for(int i = 0; i < Count; ++i)
   {
      CRC ^= WORD(BYTE(Buffer[i]));

      for(int j = 0; j < 8; ++j)
      {
         if(CRC & 1)
         {
            CRC >>= 1;
            CRC  ^= 0xA001;
         }
         else
         {
            CRC >>= 1;
         }
      }
   }
   return CRC;
}
//--------------------------------------------------------------------------
// CheckCRC()
//--------------------------------------------------------------------------
bool CServoCtrl::CheckCRC(BYTE *Buffer, int RxCnt)
{
   WORD CRC = (Buffer[RxCnt - 1] << 8) | Buffer[RxCnt - 2];
   return CalcCRC(Buffer, RxCnt - 2) == CRC;
}
//--------------------------------------------------------------------------
// AppendCRC()
//--------------------------------------------------------------------------
void CServoCtrl::AppendCRC(BYTE *Buffer, int TxCnt)
{
   // 注意：CRC是低字节在前，高字节在后
   WORD CRC = CalcCRC(Buffer, TxCnt);
   Buffer[TxCnt]     = CRC;
   Buffer[TxCnt + 1] = CRC >> 8;
}
//---------------------------------------------------------------------------
// ReadServoFdk()
//---------------------------------------------------------------------------
void CServoCtrl::ReadServoFdk(BYTE *FdkBuffer, int &FdkCnt)
{
   BYTE Buffer[16];
   DWORD RecCount;
   if(ReadFile(__hComm,          // 用 CreateFile 获得的文件句柄
               Buffer,           // 输入缓冲区首址
               16,               // 设定读入字节数
               &RecCount,        // 实际读入字节数
               NULL))            // 重叠操作方式数据结构地址
   {
      memcpy(FdkBuffer + FdkCnt, Buffer, RecCount);
      FdkCnt += RecCount;
   }
}
//---------------------------------------------------------------------------
// WriteMultiWords()
//---------------------------------------------------------------------------
bool CServoCtrl::WriteMultiWords(int Addr, WORD *Values, int WordCnt)
{
   // ModbusRTU指令
   BYTE Order[280] = {__ServoAddr, 0x10, Addr >> 8, Addr, WordCnt >> 8, WordCnt, WordCnt * 2};

   // 待写入的值
   for(int i = 0; i < WordCnt; ++i)
   {
      Order[7 + i * 2] = Values[i] >> 8;
      Order[8 + i * 2] = Values[i];
   }

   // CRC校验
   AppendCRC(Order, 7 + WordCnt * 2);

   // 下传指令
   DWORD Size;
   WriteFile(__hComm, Order, 15, &Size, NULL);

   // 等待应答
   int  FdkCnt = 0;
   BYTE FdkBuffer[16];
   for(int i = 0; i < 10; ++i)
   {
      // 读串应答
      Sleep(10);
      ReadServoFdk(FdkBuffer, FdkCnt);

      // 如果收到应答字节数为8以上，则检查应答是否正确
      if(FdkCnt >= 8)
         return CheckCRC(FdkBuffer, FdkCnt) && memcmp(Order, FdkBuffer, 6) == 0;
   }
   return false;
}
//---------------------------------------------------------------------------
// ReadMultiWords()
//---------------------------------------------------------------------------
bool CServoCtrl::ReadMultiWords(int Addr, WORD *Values, int WordCnt)
{
   // 构造指令
   BYTE Order[8] = {__ServoAddr, 0x04, Addr >> 8, Addr, WordCnt >> 8, WordCnt};
   AppendCRC(Order, 6);

   // 下传指令
   DWORD Size;
   WriteFile(__hComm, Order, 15, &Size, NULL);

   // 等待应答
   int  FdkCnt = 0;
   BYTE FdkBuffer[280];
   for(int i = 0; i < 10; ++i)
   {
      // 读串口应答
      Sleep(10);
      ReadServoFdk(FdkBuffer, FdkCnt);

      // 如果收到应答字节数为3以上，则检查应答地址
      if(FdkCnt >= 3 && (FdkBuffer[0] != __ServoAddr || FdkBuffer[1] != 0x04 || FdkBuffer[2] != WordCnt * 2) )
         return false;

      // 收到完整应答，且CRC校验正确，则解析数据
      if(FdkCnt >= WordCnt * 2 + 5 && CheckCRC(FdkBuffer, WordCnt * 2 + 5) )
      {
         for(int i = 0; i < WordCnt; ++i)
            Values[i] = (FdkBuffer[3 + i * 2] << 8) | FdkBuffer[4 + i * 2];

         return true;
      }
   }
   return false;
}
//---------------------------------------------------------------------------
// SendIncToSegment()
// 将运动步长写入伺服控制器指定segment中
// 步长单位为m
// 速度单位为m/s
//---------------------------------------------------------------------------
void CServoCtrl::SendIncToSegment(int Segment, float Step, float Speed)
{
   // 计算运动步长和速度
   int ServoPulse = Step  * 1000.0 * MM_TO_PULSE + 0.5;        // 步长脉冲
   int ServoSpeed = Speed * 1000.0 * MM_TO_ROUND * 10 + 0.5;   // 速度单位为0.1rpm

   // 累计脉冲数不能小于0
   if(__PulseCnt + ServoPulse < 0)
      ServoPulse = -__PulseCnt;
   __PulseCnt += ServoPulse;

   // 伺服方向，正脉冲电感缩进，负脉冲电缸伸出
   ServoPulse = -ServoPulse;

   // 速度不能小于0.1rpm
   if(ServoSpeed < 1)
      ServoSpeed = 1;

   int PulseHigh = ServoPulse / 10000;
   int PulseLow  = ServoPulse % 10000;
   WORD Values[3] = {PulseLow, PulseHigh, ServoSpeed};

   // 下传指令    寄存器首地址需要确认
   WriteMultiWords(0, Values, 3);
}
//---------------------------------------------------------------------------
// SendSegmentID()
//---------------------------------------------------------------------------
void CServoCtrl::SendSegmentID(int Segment)
{
   WORD Value = Segment;
   WriteMultiWords(0x2209, &Value, 1);
}
//---------------------------------------------------------------------------
// SendIncrement()
// 步长单位为mm
// 速度单位为mm/s
//---------------------------------------------------------------------------
void CServoCtrl::SendIncrement(float Step, float Speed)
{
   SendIncToSegment(__NxtSegment, Step, Speed);
}
//--------------------------------------------------------------------------
// ReadServo()
//--------------------------------------------------------------------------
bool CServoCtrl::ReadServo(void)
{   
}
//----------------------------------------------------------------------------
// Move()
//----------------------------------------------------------------------------
void CServoCtrl::Move(void)
{
   SendSegmentID(__NxtSegment);
   //__NxtSegment = __NxtSegment % 2 + 1;
   __NxtSegment = 1;
}
//---------------------------------------------------------------------------
// Zero()
//---------------------------------------------------------------------------
void CServoCtrl::Zero(void)
{
   __PulseCnt = 0;
}
//---------------------------------------------------------------------------
// CurLength()
//---------------------------------------------------------------------------
float CServoCtrl::CurLength(void)
{
   return __PulseCnt * 0.001 / MM_TO_PULSE;
}

