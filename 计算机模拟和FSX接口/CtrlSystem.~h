//---------------------------------------------------------------------------

#ifndef CtrlSystemH
#define CtrlSystemH
#include "Robot.h"
#include "MotionSimulator.h"
#include "RobotServo.h"
//---------------------------------------------------------------------------
// 三种控制模式：1. 直接控制每个连杆长度
//               2. 直接控制机器人上平台位姿
//               3. 机器人跟随模拟器运动
//---------------------------------------------------------------------------
class CCtrlSystem
{
private:
   CRobot             __Robot;
   CMotionSimulator   __Simulator;
   CRobotServo        __Servo;
private:
#ifdef __BORLANDC__
   HANDLE             __hComm;
#endif
private:
   char               __RcvedBytes[64];
   short              __RcvedData[6];
   int                __RcvedCnt;
private:
   int                __CtrlMode;
   bool               __Resetted;
   const float        __OffsetZ;
   float              __CtrlInterval;
private:
   short ASC2Hex(char ASC);
   short ExtractData(char *Bytes);
   short CalcCRC(char *Buffer, int Count);
   void  SendCommFdk(char CMD);
   void  RcvCtrlOrder(char Order, short Datas[6]);
private:
   void  Reset(void);
   void  ResettingCtrl(void);
public:
   CCtrlSystem(void);
public:
   CRobot&           Robot(void)    {return __Robot;}
   CMotionSimulator& Simulator(void){return __Simulator;}
   CRobotServo&      Servo(void)    {return __Servo;}
public:
   void Control(void);
   void RcvCommByte(char Byte);
};
#endif
