//---------------------------------------------------------------------------


#pragma hdrstop

#include "CtrlSystem.h"

#ifndef __BORLANDC__
#include "led.h"
#include "fsmc.h"
#else
#include "Unit1.h"
#endif
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CCtrlSystem::CCtrlSystem(void)
 : __RcvedCnt(0),
   __OffsetZ(0.86),
   __CtrlInterval(0.02)
{
   __Robot.SetPlatformSize(0.404, 0.035, 0.455, 0.035);
   __Robot.SetMinMaxJackLength(0.844, 1.044);

   __Simulator.FilterX().SetParams(__CtrlInterval, 0.5, 0.25, 0.08);
   __Simulator.FilterY().SetParams(__CtrlInterval, 0.5, 0.25, 0.05);
   __Simulator.FilterZ().SetParams(__CtrlInterval, 0.5, 0.25, 0.03);

   __Servo.SetServoTransParams(10000, 5.0);
   __Servo.SetServoSpeedLimit(0.001, 0.1);

   Reset();
}
//---------------------------------------------------------------------------
// 通信报文格式：
// 0xAA CMD D1H D1 D1 D1L D2H D2M D2L D3H D3M D3L D4H D4M D4L D5H D5M D5L D6H D6M D6L
// CMD：报文指令类型：0 = 空指令；1 = 系统复位；2 = 直接控制电缸长度；
//                    3 = 直接控制上平台位姿；4 = 模拟器跟随
// D1L D1M D1H：实际控制数据。传输电缸长度：单位mm，精度0.1mm
//                            传输上平台位姿：对于X、Y、Z，单位mm，精度0.1mm；对于Yaw、Pitch、Roll，单位°，精度0.1°
//                            传输模拟器跟随：对于X、Y、Z，单位m/s^2，精度0.001；
//---------------------------------------------------------------------------
void CCtrlSystem::RcvCommByte(char Byte)
{
   __RcvedBytes[__RcvedCnt++] = Byte;
   if(__RcvedCnt == 15)
   {
      short CRC = CalcCRC(__RcvedBytes, 13);
      if(CRC == (__RcvedBytes[13] | (__RcvedBytes[14] << 8)))
      {
         for(int i = 0; i < 6; ++i)
            __RcvedData[i] = __RcvedBytes[i * 2 + 1] | (__RcvedBytes[i * 2 + 2] << 8);
         __RcvedCnt = 0;

         RcvCtrlOrder(__RcvedBytes[0], __RcvedData);
      }
      else
      {
         for(int i = 0; i < 14; ++i)
            __RcvedBytes[i] = __RcvedBytes[i + 1];
         __RcvedCnt = 14;
      }
   }

   /*
   if(__RcvedCnt == 0 && Byte == ':' || __RcvedCnt > 0)
   {
      __RcvedBytes[__RcvedCnt++] = Byte;

      if(__RcvedCnt == 27)
      {
         // 接收数据
         for(int i = 0; i < 6; ++i)
            __RcvedData[i] = ExtractData(__RcvedBytes + 2 + (i << 2));

         switch(__RcvedBytes[1])
         {
         case '1' :   // 运动台复位
            Reset();
            break;
         case '3' :   // 收到上平台位姿
            __Robot.Move(__RcvedData[0] * 0.001, __RcvedData[1] * 0.001, __RcvedData[2] * 0.001,
                         __RcvedData[3] * 0.01, __RcvedData[4] * 0.01, __RcvedData[5] * 0.01);
            break;
         case '4' :   // 收到飞机加速度
            __Simulator.FeedTargetAcc(__RcvedData[0] * 0.001, __RcvedData[1] * 0.001, __RcvedData[2] * 0.001, 0, 0, 0);
            break;
         }

         if(__RcvedData[1])
            __CtrlMode = __RcvedData[1];

         SendCommFdk(__RcvedData[1]);
         __RcvedCnt = 0;
      }
   }
   */
}
//---------------------------------------------------------------------------
void CCtrlSystem::RcvCtrlOrder(char Order, short Datas[6])
{
   switch(Order)
   {
   case 1 :   // 运动台复位
      Reset();
      break;
   case 3 :   // 收到上平台位姿
      __Robot.Move(Datas[0] * 0.001, Datas[1] * 0.001, Datas[2] * 0.001,
                   Datas[3] * 0.01, Datas[4] * 0.01, Datas[5] * 0.01);
      break;
   case 4 :   // 收到飞机加速度
      __Simulator.FeedTargetAcc(Datas[0] * 0.001, Datas[1] * 0.001, Datas[2] * 0.001, 0, 0, 0);
      break;
   }
}
//---------------------------------------------------------------------------
void CCtrlSystem::SendCommFdk(char CMD)
{
   //
}
//---------------------------------------------------------------------------
short CCtrlSystem::ASC2Hex(char ASC)
{
   if(ASC >= '0' && ASC <= '9')
      return ASC - '0';
   else if(ASC >= 'A' && ASC <= 'F')
      return ASC - 'A' + 10;
   else if(ASC >= 'a' && ASC <= 'f')
      return ASC - 'a' + 10;
   else
      return 0;
}
//---------------------------------------------------------------------------
short CCtrlSystem::ExtractData(char *Bytes)
{
   return (ASC2Hex(*Bytes) << 12) | (ASC2Hex(*++Bytes) << 8) | (ASC2Hex(*++Bytes) << 4) | ASC2Hex(*++Bytes);
}
//---------------------------------------------------------------------------
short CCtrlSystem::CalcCRC(char *Buffer, int Count)
{
   short CRC = 0xFFFF;

   for(int i = 0; i < Count; ++i)
   {
      CRC ^= Buffer[i];

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
//---------------------------------------------------------------------------
void CCtrlSystem::Reset(void)
{
   __Resetted = false;
   __Servo.GoZero();
   __Robot.Zeroed();
}
//---------------------------------------------------------------------------
float Pos = 0.76;
void CCtrlSystem::Control(void)
{
	/*
	int LmtSwitchLower = fpga_read(7);
	 if(LmtSwitchLower & 0x03F == 0)
		 LED_GREEN_OFF;
	 else
		 LED_GREEN_ON;
	*/

   __CtrlMode = 4;
   if(!__Resetted)
   {
      // 各个电缸应当首先归零
      if(!__Servo.Zeroed())
         __Servo.GoZeroCtrl();
      else
      {
         if(__OffsetZ - __Robot.PosZ() < 0.001)
            __Resetted = true;

         __Robot.Move(0, 0, __Robot.PosZ() + 0.01 * __CtrlInterval, 0, 0, 0);
         __Servo.RobotMove(__Robot);
      }
   }
   else
   {
      if(__CtrlMode == 4)
      {
         double X, Y, Z, Yaw, Pitch, Roll;
         __Simulator.GetPlatformPosition(X, Y, Z, Yaw, Pitch, Roll);
         Form1->Shape2->Brush->Color = __Robot.Move(X, Y, Z + __OffsetZ, Yaw, Pitch, Roll) == msOk? clLime : clRed;
      }
      __Servo.RobotMove(__Robot);
   }
}
