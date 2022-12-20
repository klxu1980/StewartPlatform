//---------------------------------------------------------------------------


#pragma hdrstop

#include "RobotComm.h"
#include "CtrlSystem.h"
#include <string.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CRobotCommPkg::CRobotCommPkg(void)
{
   //CtrlOrder = new unsigned char[140];
   //FdkStatus = new unsigned char[140];
}
//---------------------------------------------------------------------------
// CalcCRC()
//---------------------------------------------------------------------------
unsigned short CRobotCommPkg::CalcCRC(unsigned char *Buffer, int Count)
{
   unsigned short crc = 0xFFFF;

   for(int i = 0; i < Count; ++i)
   {
      crc ^= Buffer[i];

      for(int j = 0; j < 8; ++j)
      {
         if(crc & 1)
         {
            crc >>= 1;
            crc  ^= 0xA001;
         }
         else
         {
            crc >>= 1;
         }
      }
   }
   return crc;
}
//---------------------------------------------------------------------------
void CRobotCommPkg::AddCRC(unsigned char *Buffer, int DataSize)
{
   unsigned short crc = CalcCRC(Buffer, DataSize + 3);
   Buffer[DataSize + 3] = crc;
   Buffer[DataSize + 4] = crc >> 8;
}
//---------------------------------------------------------------------------
bool CRobotCommPkg::CheckCRC(unsigned char *Buffer, int DataSize)
{
   unsigned short crc = CalcCRC(Buffer, DataSize + 3);
   return crc == (Buffer[DataSize + 3] | (Buffer[DataSize + 4] << 8));
}
//--------------------------------------------------------------------------
bool CRobotCommPkg::CheckReceivedComm(unsigned char Byte, unsigned char *Buffer, int &RcvSize)
{
   // 检测收到的第一个字节是否报头
   if(RcvSize == 0 && Byte != 0x55)
      return false;

   // 将收到的字节存入缓冲区
   Buffer[RcvSize++] = Byte;

   // 还未收到数据长度字节
   if(RcvSize < 3)
      return false;

   // 收到的数据长度超过128字节，说明接收错误，删除整个报文
   if(Buffer[1] > 128)
   {
      RcvSize = 0;
      return false;
   }

   // 检查收到字节数量
   // 如果收到数量小于报文数据长度(接收到的第1个字节)+报头+CRC，则不检查CRC
   if(RcvSize < Buffer[1] + 5)
      return false;

   // 检查CRC
   RcvSize = 0;
   if(!CheckCRC(Buffer, Buffer[1]))
      return false;
   else
      return true;
}
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
void CRobotCommPkg::BuildNullOrder(void)
{
   CtrlOrder[0] = 0x55;
   CtrlOrder[1] = 0;
   CtrlOrder[2] = 0;
   AddCRC(CtrlOrder, CtrlOrder[1]);
}
//---------------------------------------------------------------------------
void CRobotCommPkg::BuildResetOrder(void)
{
   CtrlOrder[0] = 0x55;
   CtrlOrder[1] = 0;
   CtrlOrder[2] = 1;
   AddCRC(CtrlOrder, CtrlOrder[1]);
}
//---------------------------------------------------------------------------
void CRobotCommPkg::BuildJackCtrlOrder(int JackID, float JackLength, float Speed)
{
   CtrlOrder[0] = 0x55;
   CtrlOrder[1] = 5;
   CtrlOrder[2] = 2;
   CtrlOrder[3] = JackID;

   short Value[2] = {JackLength * 10000.0 + 0.5, Speed * 1000.0 + 0.5};

   Short2Buffer(Value[0], CtrlOrder + 4);
   Short2Buffer(Value[1], CtrlOrder + 6);

   AddCRC(CtrlOrder, CtrlOrder[1]);
}
//---------------------------------------------------------------------------
void CRobotCommPkg::BuildPosCtrlOrder(float X, float Y, float Z, float Yaw, float Pitch, float Roll)
{
   CtrlOrder[0] = 0x55;
   CtrlOrder[1] = 12;
   CtrlOrder[2] = 3;

   Short2Buffer(X * 10000.0, CtrlOrder + 3);
   Short2Buffer(Y * 10000.0, CtrlOrder + 5);
   Short2Buffer(Z * 10000.0, CtrlOrder + 7);

   Short2Buffer(Yaw   * 10.0, CtrlOrder + 9);
   Short2Buffer(Pitch * 10.0, CtrlOrder + 11);
   Short2Buffer(Roll  * 10.0, CtrlOrder + 13);
   
   AddCRC(CtrlOrder, CtrlOrder[1]);
}
//---------------------------------------------------------------------------
void CRobotCommPkg::BuildAccCtrlOrder(float AccX, float AccY, float AccZ, float SpdYaw, float SpdPitch, float SpdRoll)
{
   CtrlOrder[0] = 0x55;
   CtrlOrder[1] = 12;
   CtrlOrder[2] = 4;

   Short2Buffer(AccX * 1000.0, CtrlOrder + 3);
   Short2Buffer(AccY * 1000.0, CtrlOrder + 5);
   Short2Buffer(AccZ * 1000.0, CtrlOrder + 7);

   Short2Buffer(SpdYaw   * 10.0, CtrlOrder + 9);
   Short2Buffer(SpdPitch * 10.0, CtrlOrder + 11);
   Short2Buffer(SpdRoll  * 10.0, CtrlOrder + 13);

   AddCRC(CtrlOrder, CtrlOrder[1]);
}
//---------------------------------------------------------------------------
void CRobotCommPkg::BuildStableCtrlOrder(void)
{
   memset(CtrlOrder, 0, CtrlOrderSize());

   CtrlOrder[0] = 5;
   AddCRC(CtrlOrder, CtrlOrderSize());
}
//---------------------------------------------------------------------------
void CRobotCommPkg::BuildJuneBugCtrlOrder(float Dx, float Dy, float Yaw, float XYHeight, float Speed)
{
   CtrlOrder[0] = 0x55;
   CtrlOrder[1] = 10;
   CtrlOrder[2] = JUNEBUG_CTRL;

   Short2Buffer(Dx       * 1000.0, CtrlOrder + 3);
   Short2Buffer(Dy       * 1000.0, CtrlOrder + 5);
   Short2Buffer(Yaw      * 1000.0, CtrlOrder + 7);
   Short2Buffer(XYHeight * 1000.0, CtrlOrder + 9);
   Short2Buffer(Speed    * 1000.0, CtrlOrder + 11);

   AddCRC(CtrlOrder, CtrlOrder[1]);
}
#endif
//---------------------------------------------------------------------------
bool CRobotCommPkg::ReceiveCtrlOrder(unsigned char Byte)
{
   return CheckReceivedComm(Byte, CtrlOrder, CtrlLength);
}
//---------------------------------------------------------------------------
bool CRobotCommPkg::ReceiveFdkStatus(unsigned char Byte)
{
   return CheckReceivedComm(Byte, FdkStatus, FdkLength);
}
//---------------------------------------------------------------------------
void CRobotCommPkg::GetJackCtrlOrder(int &JackID, float &Length, float &Speed)
{
   JackID = CtrlOrder[3];
   Length = Buffer2Short(CtrlOrder + 4) * 0.0001;
   Speed  = Buffer2Short(CtrlOrder + 6) * 0.001;
}
//---------------------------------------------------------------------------
void CRobotCommPkg::GetPosCtrlOrder(float &X, float &Y, float &Z, float &Yaw, float &Pitch, float &Roll)
{
   X = Buffer2Short(CtrlOrder + 3) * 0.0001;
   Y = Buffer2Short(CtrlOrder + 5) * 0.0001;
   Z = Buffer2Short(CtrlOrder + 7) * 0.0001;
   Yaw   = Buffer2Short(CtrlOrder + 9)  * 0.1;
   Pitch = Buffer2Short(CtrlOrder + 11)  * 0.1;
   Roll  = Buffer2Short(CtrlOrder + 13) * 0.1;
}
//---------------------------------------------------------------------------
void CRobotCommPkg::GetAccCtrlOrder(float &AccX, float &AccY, float &AccZ, float &SpdYaw, float &SpdPitch, float &SpdRoll)
{
   AccX = Buffer2Short(CtrlOrder + 3) * 0.001;
   AccY = Buffer2Short(CtrlOrder + 5) * 0.001;
   AccZ = Buffer2Short(CtrlOrder + 7) * 0.001;
   SpdYaw   = Buffer2Short(CtrlOrder + 9)  * 0.1;
   SpdPitch = Buffer2Short(CtrlOrder + 11)  * 0.1;
   SpdRoll  = Buffer2Short(CtrlOrder + 13) * 0.1;
}
//---------------------------------------------------------------------------
void CRobotCommPkg::GetJuneBugOrder(float &Dx, float &Dy, float &Yaw, float &XYHeight, float &Speed)
{
   Dx       = Buffer2Short(CtrlOrder + 3)  * 0.001;
   Dy       = Buffer2Short(CtrlOrder + 5)  * 0.001;
   Yaw      = Buffer2Short(CtrlOrder + 7)  * 0.001;
   XYHeight = Buffer2Short(CtrlOrder + 9)  * 0.001;
   Speed    = Buffer2Short(CtrlOrder + 11) * 0.001;
}
//---------------------------------------------------------------------------
void CRobotCommPkg::FdkRobotStatus(CCtrlSystem *CtrlSystem)
{
   // 反馈控制模式
   FdkStatus[0] = 0x55;
   FdkStatus[1] = 16;
   FdkStatus[2] = CtrlSystem->__CtrlMode;

   // 反馈限位开关和运动限位
   FdkStatus[3] = 0;
   FdkStatus[4] = 0;
   FdkStatus[5] = 0;
   FdkStatus[6] = 0;
   for(int i = 0; i < 6; ++i)
   {
      FdkStatus[3] |= (CtrlBoard.DILower[i]? 1 : 0) << i;        // 下限位开关
      FdkStatus[4] |= (CtrlBoard.DIUpper[i]? 1 : 0) << i;        // 上限位开关
      FdkStatus[5] |= ((CtrlSystem->__Robot.Jack[i].Servo < CtrlSystem->__Robot.JackServoBuffer)? 1 : 0) << i;
      FdkStatus[6] |= ((CtrlSystem->__Robot.Jack[i].Servo > CtrlSystem->__Robot.JackServoLength - CtrlSystem->__Robot.JackServoBuffer)? 1 : 0) << i;
   }

   // 反馈连杆长度
   for(int i = 0; i < 6; ++i)
      Short2Buffer(CtrlSystem->__Robot.Jack[i].Servo * 10000 + 0.5, FdkStatus + 7 + i * 2);

  // CRC校验
  AddCRC(FdkStatus, FdkStatus[1]);
}
//---------------------------------------------------------------------------
void CRobotCommPkg::GetLmtSwitchStatus(char &SwitchLower, char &SwitchUpper, char &JackMin, char &JackMax)
{
   SwitchLower = FdkStatus[3];
   SwitchUpper = FdkStatus[4];
   JackMin     = FdkStatus[5];
   JackMax     = FdkStatus[6];
}
//---------------------------------------------------------------------------
void CRobotCommPkg::GetJackLength(float Length[6])
{
   for(int i = 0; i < 6; ++i)
      Length[i] = Buffer2Short(FdkStatus + 7 + i * 2) * 0.0001;
}
//---------------------------------------------------------------------------
void CRobotCommPkg::BuildAccCtrlParams(CMotionSimuParams Params)
{
   CtrlOrder[0] = 0x55;
   CtrlOrder[1] = sizeof(Params);
   CtrlOrder[2] = 6;

   memcpy(CtrlOrder + 3, &Params, sizeof(CMotionSimuParams));

   AddCRC(CtrlOrder, CtrlOrder[1]);
}
//---------------------------------------------------------------------------
void CRobotCommPkg::GetAccCtrlParams(CMotionSimuParams &Params)
{
   memcpy(&Params, CtrlOrder + 3, sizeof(CMotionSimuParams));
}
