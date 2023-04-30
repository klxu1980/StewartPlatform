//---------------------------------------------------------------------------


#pragma hdrstop

#include "CtrlSystem.h"
#include "GlobalDef.h"
#include <string.h>

#ifndef __BORLANDC__
#include "led.h"
#include "fsmc.h"
#include "usart.h"
#else
#include "Unit1.h"
#endif

CCtrlSystem CtrlSystem;
//---------------------------------------------------------------------------

#ifdef __BORLANDC__
#pragma package(smart_init)
#endif
//---------------------------------------------------------------------------
CCtrlSystem::CCtrlSystem(void)
 : __CtrlInterval(CTRL_INTERVAL),
   __CtrlMode(ORDER_IDLE)
{
   // 设置机器人几何参数
   __Robot.UpperArmLength   = ROBOT_UPPER_ARM_LENGTH;
   __Robot.UpperBaseLength  = ROBOT_UPPER_BASE_LENGTH;
   __Robot.LowerArmLength   = ROBOT_LOWER_ARM_LENGTH;
   __Robot.LowerBaseLength  = ROBOT_LOWER_BASE_LENGTH;
   __Robot.UpperJointHeight = 0;
   __Robot.LowerJointHeight = 0;

   __Robot.JackFixedLength = JACK_FIXED_LENGTH;
   __Robot.JackServoLength = JACK_SERVO_LENGTH;
   __Robot.JackServoBuffer = JACK_SERVO_DEC;

   __Robot.InitStructureParams();

   // 设置每个直线运动的加速度->位置系数(T, amax, vmax, xmax)
   __Simulator.Acc2Motion[0].SetParams(__CtrlInterval, MAX_LINEAR_ACC, MAX_SPEED_X, MAX_RANGE_X);
   __Simulator.Acc2Motion[1].SetParams(__CtrlInterval, MAX_LINEAR_ACC, MAX_SPEED_Y, MAX_RANGE_Y);
   __Simulator.Acc2Motion[2].SetParams(__CtrlInterval, MAX_LINEAR_ACC, MAX_SPEED_Z, MAX_RANGE_Z);

   // 设置每个角运动的角速度->姿态系数(T, vmax, angle_max)
   __Simulator.RSpd2Rotate[0].SetParams(__CtrlInterval,   MAX_ROTARY_SPD, MAX_YAW);       // 12
   __Simulator.RSpd2Rotate[1].SetParams(__CtrlInterval,   MAX_ROTARY_SPD, MAX_PITCH);     // 12
   __Simulator.RSpd2Rotate[2].SetParams(__CtrlInterval,  MAX_ROTARY_SPD,  MAX_ROLL);      // 12

   // 设置通过重力模拟加速度的系数
   __Simulator.Acc2Angle[0].SetParams(__CtrlInterval, 1, 5);
   __Simulator.Acc2Angle[1].SetParams(__CtrlInterval, 1, 5);

   // 运动台复位
   Reset();
}
//---------------------------------------------------------------------------
// 通信指令报文格式：
// CMD D1L D1H D2L D2H D3L D3H D4L D4H D5L D5H D6L D6H CRCL CRCH
// CMD：报文指令类型：0 = 空指令；
//                    1 = 系统复位；
//                    2 = 直接控制电缸长度，单位0.1mm
//                    3 = 直接控制上平台位姿，位置单位0.1mm，姿态单位0.1°
//                    4 = 模拟器跟随，加速度单位0.001m/s^2，角速度单位0.1°/s
// CRCL CRCH：CRC校验
//---------------------------------------------------------------------------
bool CCtrlSystem::RcvCommandByte(char Byte)
{
   if(__CommPkg.ReceiveCtrlOrder(Byte))
   {
      // 检查控制模式是否发生变化
      // 如果发生变化，则调用OnCtrlModeChanged()加以处理
      if(__CtrlMode != __CommPkg.GetOrderType())
            OnCtrlModeChanged(__CommPkg.GetOrderType());
      __CtrlMode = __CommPkg.GetOrderType();

      // 解析指令报文
      ExtractCtrlOrder();

      // 反馈状态
      __CommPkg.FdkRobotStatus(this);

      return true;
   }

   return false;
}
//---------------------------------------------------------------------------
void CCtrlSystem::ExtractCtrlOrder(void)
{
  // 根据控制模式，解析指令报文
  if(__CtrlMode == ORDER_IDLE)
  {
     // 空闲指令，机器人返回状态信息
  }
  else if(__CtrlMode == RESET_ROBOT)
  {
     // 运动台复位
     Reset();    
  }
  else if(__CtrlMode == DIRECT_JACK_CTRL)
  {
     // 直接控制电缸长度
     // 字节1：电缸编号，字节2、3：电缸伸出长度(mm)，字节4、5：电缸运动速度(mm)
     int   Idx;
     float Length, Speed;
     __CommPkg.GetJackCtrlOrder(Idx, Length, Speed);

     if(Idx >= 1 && Idx <= 6)
     {
        __DstJackServoLen[Idx - 1] = Limit(Length, 0, JACK_SERVO_LENGTH);
        __DstJackSpeed[Idx - 1]    = Speed;
     }
  }
  else if(__CtrlMode ==  DIRECT_POS_EURLAR_CTRL)
  {
     // 控制上平台位姿
     // 直接上平台位姿控制缺少合理的路径规划，目前先暂时让程序可以跑起来
     // 字节1：位姿编号，字节2、3：给定位姿(位置mm，姿态°)
     float PosEuler[6];
     __CommPkg.GetPosCtrlOrder(PosEuler[0], PosEuler[1], PosEuler[2],
                               PosEuler[3], PosEuler[4], PosEuler[5]);
     __MotionTrack.NewDestination(PosEuler);
  }
  else if(__CtrlMode == MOTION_SIMU_CTRL)
  {
     // 运动模拟
     float AccX, AccY, AccZ, SpdYaw, SpdPitch, SpdRoll;
     __CommPkg.GetAccCtrlOrder(AccX, AccY, AccZ, SpdYaw, SpdPitch, SpdRoll);

     __Simulator.FeedTargetAccAndSpd(AccX, AccY, AccZ, SpdYaw, SpdPitch, SpdRoll);
  }
  else if(__CtrlMode == MOTION_SIMU_PARAM)
  {
     CMotionSimuParams Params;
     __CommPkg.GetAccCtrlParams(Params);
     __Simulator.SetParams(Params);
  }
  else if(__CtrlMode == JUNEBUG_CTRL)
  {
     float Dir, Step, Yaw, XYHeight, Speed;
     __CommPkg.GetJuneBugOrder(Dir, Step, Yaw, XYHeight, Speed);
     __JuneBugCtrl.Dir      = Dir;
     __JuneBugCtrl.Step     = Step;
     __JuneBugCtrl.Yaw      = Yaw;
     __JuneBugCtrl.XYHeight = XYHeight;
     __JuneBugCtrl.Speed    = Speed;
  }
}
//---------------------------------------------------------------------------
bool CCtrlSystem::FdkBuffer(unsigned char **Fdk, int *FdkLength)
{
   *Fdk = __CommPkg.FdkStatus;
   *FdkLength = __CommPkg.FdkStatusSize();
	 return true;
}
//---------------------------------------------------------------------------
void CCtrlSystem::OnCtrlModeChanged(int CtrlMode)
{
   if(CtrlMode == DIRECT_POS_EURLAR_CTRL)
   {
      double Pos[3] = {__Robot.RobotIKP.UpperPos[0],
                       __Robot.RobotIKP.UpperPos[1],
                       __Robot.RobotIKP.UpperPos[2] - __Robot.CenterZ};
      __MotionTrack.Initialize(Pos, __Robot.RobotIKP.UpperEuler);
   }
   else if(CtrlMode == DIRECT_JACK_CTRL)
   {
      for(int i = 0; i < 6; ++i)
         __DstJackServoLen[i] = __Robot.Jack[i].Servo;
   }
}
//---------------------------------------------------------------------------
void CCtrlSystem::Reset(void)
{
   __AllJackZeroed = __Resetted = false;
   __Servo.GoZero();
}
//---------------------------------------------------------------------------
// ResetCtrl()
// 复位控制
//---------------------------------------------------------------------------
void CCtrlSystem::ResetCtrl(void)
{
   // 机器人复位
   // 机器人上电时，或者发送复位按钮后，则执行复位操作，此时不接受其他任何指令
   // 复位时，首先控制所有电缸收缩，直至均到达下限位开关(零位开关)
   // 之后，沿Z轴缓慢上升，直至到达中心点。
   if(!__AllJackZeroed)
   {
      __AllJackZeroed = __Servo.IsAllZeroed(); 
      if(__AllJackZeroed)
         __Robot.PlatformZeroed();
   }
   else
   {
      // 归零结束后，返回中间位置
      double Step = ZERO_2_CENTER_SPD * __CtrlInterval;
      if(__Robot.PosZ() - __Robot.CenterZ >= 0)
      {
         __Resetted = true;

         double Pos[3] = {0, 0, 0};
         double Euler[3] = {0, 0, 0};
         __JuneBugCtrl.Initialize();
         __MotionTrack.Initialize(Pos, Euler);
      }
      else
      {
         // 注意：复位时，伺服不受最小行程约束
         __Robot.PlatformMove(0, 0, __Robot.PosZ() + Step, 0, 0, 0, false);
         __Servo.RobotMove(__Robot);
      }
   }
}
//---------------------------------------------------------------------------
// DirectJackCtrl()
// 直接控制机器人的电缸
//---------------------------------------------------------------------------
void CCtrlSystem::DirectJackCtrl(void)
{
   // 计算每个电缸的长度
   for(int i = 0; i < 6; ++i)
   {
      // 计算运动增量，和剩余运动量
      double Delta    = __DstJackSpeed[i] * __CtrlInterval;
      double Distance = __DstJackServoLen[i] - __Robot.Jack[i].Servo;

      // 如果运动增量小于运动量，则增加连杆的长度
      // 否则，令连杆长度等于目标长度
      if(Delta < fabs(Distance))
         __Robot.SetJackServo(i, __Robot.Jack[i].Servo + ((Distance > 0)? Delta : -Delta));
      else
         __Robot.SetJackServo(i, __DstJackServoLen[i]);
   }
}
//---------------------------------------------------------------------------
// MotionSimuCtrl()
// 运动模拟控制
// 根据给定加速度，控制上平台运动
//---------------------------------------------------------------------------
void CCtrlSystem::MotionSimuCtrl(void)
{
   // 运动模拟控制
   // 首先令运动模拟模块计算出当前应到达的位姿
   // 然后再令机器人向该位姿运动
   // 注意：在运动模拟时，为了便于安装座椅、显示器等，将机器人的尾方向，改为头方向，
   //       因此控制机器人时，需要对坐标方向取反
   double X, Y, Z, Yaw, Pitch, Roll;
   __Simulator.GetPlatformPosition(X, Y, Z, Yaw, Pitch, Roll);

   // 机器人运动
   //__Robot.PlatformMove(-X, -Y, -Z - __Robot.CenterZ, -Yaw, -Pitch, -Roll);
   __Robot.PlatformMove(X, Y, Z + __Robot.CenterZ, Yaw, Pitch, Roll);
}
//---------------------------------------------------------------------------
// DirectPosEurlarCtrl()
// 根据设定目标位姿，插值计算每个控制周期的位姿
//---------------------------------------------------------------------------
void CCtrlSystem::DirectPosEurlarCtrl(void)
{
   double Pos[3] = {__Robot.RobotFKP.UpperPos[0],
                    __Robot.RobotFKP.UpperPos[1],
                    __Robot.RobotFKP.UpperPos[2] - __Robot.CenterZ};
   __MotionTrack.Move(Pos, __Robot.RobotFKP.UpperEuler);

   // 机器人运动
   __Robot.PlatformMove(__MotionTrack.PosEuler[0],
                        __MotionTrack.PosEuler[1],
                        __MotionTrack.PosEuler[2] + __Robot.CenterZ,
                        __MotionTrack.PosEuler[3],
                        __MotionTrack.PosEuler[4],
                        __MotionTrack.PosEuler[5]);
}
//---------------------------------------------------------------------------
void CCtrlSystem::StableCtrl(void)
{
   // 减摆控制
   double X, Y, Z, Yaw, Pitch, Roll;
   __StableCtrl.GetPlatformPosition(X, Y, Z, Yaw, Pitch, Roll);

   // 机器人运动
   __Robot.PlatformMove(X, Y, Z + __Robot.CenterZ, Yaw, Pitch, Roll);
}
//---------------------------------------------------------------------------
void CCtrlSystem::JuneBugCtrl(void)
{
   __JuneBugCtrl.Move();
   __Robot.PlatformMove(__JuneBugCtrl.PosEuler[0],
                        __JuneBugCtrl.PosEuler[1],
                        __JuneBugCtrl.PosEuler[2] + __Robot.CenterZ,
                        __JuneBugCtrl.PosEuler[3],
                        __JuneBugCtrl.PosEuler[4],
                        __JuneBugCtrl.PosEuler[5]);
}
//---------------------------------------------------------------------------
void CCtrlSystem::Control(void)
{	
   // 绿色LED指示灯闪烁，表明控制器在工作
   LedFlick();

   if(!__Resetted)
   {
      // 复位控制
      ResetCtrl();
   }
   else
   {
      // 正常控制
      // 在正常控制程序中，调用Robot.PlatformMove()函数
      #ifndef SYS_STABLE_CTRL
      switch(__CtrlMode)
      {
        case ORDER_IDLE             :   break;
        case DIRECT_JACK_CTRL       :   DirectJackCtrl();        break;
        case DIRECT_POS_EURLAR_CTRL :   DirectPosEurlarCtrl();   break;
        case MOTION_SIMU_CTRL       :   MotionSimuCtrl();        break;
        case STABLE_CTRL            :   StableCtrl();            break;
        case JUNEBUG_CTRL           :   JuneBugCtrl();           break;
      }
      #else
      StableCtrl();
      #endif

      __Servo.RobotMove(__Robot);
   }

   // 伺服控制
   __Servo.ServoCtrl();

   // 根据电缸伸出量，计算实际位姿
   // 伺服归零期间不做计算
#ifdef CALC_FDKP
   if(__AllJackZeroed)
   {
      __Robot.AfterServoMoved(__Servo.ServoLength(0), __Servo.ServoLength(1), __Servo.ServoLength(2),
                              __Servo.ServoLength(3), __Servo.ServoLength(4), __Servo.ServoLength(5));
   }
#endif
}
//---------------------------------------------------------------------------
void CCtrlSystem::CalcDestination(double SrcX, double SrcY, double SrcZ,
                                  double DstX, double DstY, double DstZ,
                                  double &X,   double &Y,   double &Z,
                                  double Step)
{
   // 计算运动分量和运动行程
   double Vx = DstX - SrcX;
   double Vy = DstY - SrcY;
   double Vz = DstZ - SrcZ;
   double V  = sqrt(Vx * Vx + Vy * Vy + Vz * Vz);

   if(V <= Step)
   {
      X = DstX;
      Y = DstY;
      Z = DstZ;
   }
   else
   {
      Vx /= V;
      Vy /= V;
      Vz /= V;

      X = SrcX + Vx * Step;
      Y = SrcY + Vy * Step;
      Z = SrcZ + Vz * Step;
   }
}
//---------------------------------------------------------------------------
void CCtrlSystem::LedFlick(void)
{
#ifndef __BORLANDC__
   ++__LedFlickCnt;
   if((__LedFlickCnt / 20) % 2)
      LED_GREEN_ON;
   else
      LED_GREEN_OFF;
#endif
}