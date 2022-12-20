//---------------------------------------------------------------------------


#pragma hdrstop

#include "CtrlSystem.h"
#include "GlobalDef.h"

#ifndef __BORLANDC__
#include "led.h"
#include "fsmc.h"
#else
#include "Unit1.h"
#endif

#define  DIRECT_JACK_CTRL         2
#define  DIRECT_POS_EURLAR_CTRL   3
#define  MOTION_SIMU_CTRL         4
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CCtrlSystem::CCtrlSystem(void)
 : __RcvedCnt(0),
   __CentralZ(0.86),
   __CtrlInterval(CTRL_INTERVAL)
{
   // 设置机器人几何参数
   //__Robot.SetPlatformSize(1.160, 1.160, 0.455, 0.035);
   //__Robot.SetPlatformSize(0.6697, 0.035, 0.6697, 0.035);
   //__Robot.SetPlatformSize(0.65, 0.035, 0.75, 0.035);
   //__Robot.SetMinMaxJackLength(0.844, 1.044);
   __Robot.SetPlatformSize(ROBOT_UPPER_ARM_LENGTH, ROBOT_UPPER_BASE_LENGTH,
                           ROBOT_LOWER_ARM_LENGTH, ROBOT_LOWER_BASE_LENGTH);
   __Robot.SetMinMaxJackLength(ROBOT_JACK_LENGTH_MIN, ROBOT_JACK_LENGTH_MAX);

   #ifdef __BORLANDC__
   __RobotSimu.SetPlatformSize(ROBOT_UPPER_ARM_LENGTH, ROBOT_UPPER_BASE_LENGTH,
                           ROBOT_LOWER_ARM_LENGTH, ROBOT_LOWER_BASE_LENGTH);
   __RobotSimu.SetMinMaxJackLength(ROBOT_JACK_LENGTH_MIN, ROBOT_JACK_LENGTH_MAX);
   #endif

   // 设置伺服参数
   __Servo.SetServoCtrlInterval(__CtrlInterval);
   __Servo.SetServoTransParams(SERVO_PULSE_ROUND, SERVO_ROUND_MM);
   __Servo.SetServoSpeedLimit(SERVO_SPEED_MIN, SERVO_SPEED_MAX);
   __Servo.SetJackLimit(SERVO_JACK_MIN, SERVO_JACK_MAX);

   // 机器人中心位置
   __CentralZ = __Robot.CalcPlatformHeight((__Robot.MinJackLength() + __Robot.MaxJackLength()) * 0.5);

   // 设置每个自由度上的加速度->位姿系数(T, amax, vmax, xmax)
   __Simulator.FilterX().SetParams(__CtrlInterval, MAX_LINEAR_ACC, 0.3, 0.11);     // 0.13
   __Simulator.FilterY().SetParams(__CtrlInterval, MAX_LINEAR_ACC, 0.3, 0.12);     // 0.14
   __Simulator.FilterZ().SetParams(__CtrlInterval, MAX_LINEAR_ACC, 0.3, 0.11);     // 0.13

   __Simulator.FilterYaw().SetParams(__CtrlInterval,   MAX_ROTARY_ACC, 30, 12);     // 13
   __Simulator.FilterPitch().SetParams(__CtrlInterval, MAX_ROTARY_ACC, 30, 11);     // 12
   __Simulator.FilterRoll().SetParams(__CtrlInterval,  MAX_ROTARY_ACC, 30, 11.5);   // 12.5

   Reset();
}
//---------------------------------------------------------------------------
float CCtrlSystem::RobotRangeFromCenter(double Dir[6])
{
   double Min = __Robot.CalcPlatformHeight(__Robot.MinJackLength());
   double Max = __Robot.CalcPlatformHeight(__Robot.MaxJackLength());

   double CenterZ = __Robot.CalcPlatformHeight((__Robot.MinJackLength() + __Robot.MaxJackLength()) * 0.5);
   double Pos[6] = {0, 0, CenterZ, 0, 0, 0};
   do
   {
      for(int i = 0; i < 6; ++i)
         Pos[i] += Dir[i] * 0.001;
   }while(__Robot.Move(Pos[0], Pos[1], Pos[2], Pos[3], Pos[4], Pos[5]) == msOk);

   for(int i = 0; i < 6; ++i)
      Pos[i] -= Dir[i] * 0.001;

   __Robot.Move(Pos[0], Pos[1], Pos[2], Pos[3], Pos[4], Pos[5]);

   return sqrt(Pos[0] * Pos[0] + Pos[1] * Pos[1] + (Pos[2] - CenterZ) * (Pos[2] - __CentralZ) +
               Pos[3] * Pos[3] + Pos[4] * Pos[4] + Pos[5] * Pos[5]);
}
//---------------------------------------------------------------------------
// 通信报文格式：
// CMD D1L D1H D2L D2H D3L D3H D4L D4H D5L D5H D6L D6H CRCL CRCH
// CMD：报文指令类型：0 = 空指令；1 = 系统复位；2 = 直接控制电缸长度；
//                    3 = 直接控制上平台位姿；4 = 模拟器跟随
// D1L D1H：实际控制数据。传输电缸长度：单位mm，精度0.1mm
//                        传输上平台位姿：对于X、Y、Z，单位mm，精度0.1mm；对于Yaw、Pitch、Roll，单位°，精度0.1°
//                        传输模拟器跟随：对于X、Y、Z，单位m/s^2，精度0.001；
// CRCL CRCH：CRC校验
//---------------------------------------------------------------------------
void CCtrlSystem::RcvCommByte(char Byte)
{
   __RcvedBytes[__RcvedCnt++] = Byte;
   if(__RcvedCnt == 9)
   {
      short CRC = CalcCRC(__RcvedBytes, 7);

      // CRC校验正确，则接收指令
      if(CRC == Bytes2Word(__RcvedBytes + 7) ) //(short)((unsigned char)__RcvedBytes[7] | ((unsigned char)__RcvedBytes[8] << 8)))
      {
         switch(__RcvedBytes[0])
         {
         case 1 :   // 运动台复位
            Reset();
            break;
         case DIRECT_JACK_CTRL :   // 设置电缸长度
            if(__LstCtrlMode != DIRECT_JACK_CTRL)
            {
               // 初始化目标电缸长度
               for(int i = 0; i < 6; ++i)
                  __DstJackLength[i] = __Robot.Jacks[i].ServoLength;
            }
            __JackSpeed[__RcvedBytes[1]]     = Bytes2Word(__RcvedBytes + 4) * 0.001;
            __DstJackLength[__RcvedBytes[1]] = Bytes2Word(__RcvedBytes + 2) * 0.001;
            break;
         case DIRECT_POS_EURLAR_CTRL :   // 收到上平台位姿
            if(__RcvedBytes[1] < 3)
               __DstPosEurlar[__RcvedBytes[1] ] = Bytes2Word(__RcvedBytes + 2) * 0.001;
            else if(__RcvedBytes[1] < 6)
               __DstPosEurlar[__RcvedBytes[1] ] = __RcvedBytes[2] | (__RcvedBytes[3] << 8);
            break;
         case MOTION_SIMU_CTRL :   // 收到运动加速度
            __Simulator.FeedTargetAcc(__RcvedBytes[1] * MAX_LINEAR_ACC * 0.01,
                                      __RcvedBytes[2] * MAX_LINEAR_ACC * 0.01,
                                      __RcvedBytes[3] * MAX_LINEAR_ACC * 0.01,
                                      __RcvedBytes[4] * MAX_ROTARY_ACC * 0.01,
                                      __RcvedBytes[5] * MAX_ROTARY_ACC * 0.01,
                                      __RcvedBytes[6] * MAX_ROTARY_ACC * 0.01);
            break;
         }
         __CtrlMode = __RcvedBytes[0];
         __RcvedCnt = 0;
      }
      // CRC校验失败，将最早收到的字节删除
      else
      {
         for(int i = 0; i < 8; ++i)
            __RcvedBytes[i] = __RcvedBytes[i + 1];
         __RcvedCnt = 8;
      }
   }
}
//---------------------------------------------------------------------------
void CCtrlSystem::RcvJackCtrlOrder(short Datas[6])
{
}
//---------------------------------------------------------------------------
void CCtrlSystem::SendCommFdk(char CMD)
{
   //
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
// ResettingCtrl()
// 复位控制
//---------------------------------------------------------------------------
void CCtrlSystem::ResettingCtrl(void)
{
   // 机器人复位
   // 机器人上电时，或者发送复位按钮后，则执行复位操作，此时不接受其他任何指令
   // 复位时，首先控制所有电缸收缩，直至均到达下限位开关(零位开关)
   // 之后，沿Z轴缓慢上升，直至到达中心点。
   if(!__Servo.Zeroed())
   {
      __Servo.GoZeroCtrl();
   }
   else
   {
      // 归零结束后，到达设定初始状态
      if(__CentralZ - __Robot.PosZ() < 0.001)
         __Resetted = true;

      __Robot.Move(0, 0, __Robot.PosZ() + GO_ZERO_SPEED * __CtrlInterval, 0, 0, 0);
      __Servo.RobotMove(__Robot, true);
   }
}
//---------------------------------------------------------------------------
// DirectJackCtrl()
// 机器人的正向运动学仅用于仿真试验
//---------------------------------------------------------------------------
void CCtrlSystem::DirectJackCtrl(void)
{
   for(int i = 0; i < 6; ++i)
   {
      double Delta    = __JackSpeed[i] * __CtrlInterval;
      double Distance = __DstJackLength[i] - __Robot.Jacks[i].ServoLength;
      
      if(__DstJackLength[i] > __Robot.Jacks[i].ServoLength)
      {
         if(Distance > Delta)
            __Robot.Jacks[i].ServoLength += Delta;
         else
            __Robot.Jacks[i].ServoLength = __DstJackLength[i];
      }
      else
      {
         if(-Distance > Delta)
            __Robot.Jacks[i].ServoLength -= Delta;
         else
            __Robot.Jacks[i].ServoLength = __DstJackLength[i];
      }

      __Robot.Jacks[i].Length = __Robot.Jacks[i].ServoLength + ROBOT_JACK_LENGTH_MIN;
   }
   __Servo.RobotMove(__Robot);
}
//---------------------------------------------------------------------------
// MotionSimuCtrl()
// 运动模拟控制
// 根据给定加速度，控制上平台运动
//---------------------------------------------------------------------------
void CCtrlSystem::MotionSimuCtrl(void)
{
   // 正常运动控制
   // 注意：正常运动控制时，为了避免求解连杆长度时间较长造成系统顿挫，控制器先输出连杆的脉冲输出量，
   //       然后再计算下一控制周期的连杆运动增量
   __Servo.RobotMove(__Robot);

   // 运动模拟控制
   // 首先令运动模拟模块计算出当前应到达的位姿
   // 然后再令机器人向该位姿运动
   // 注意：在运动模拟时，为了便于安装座椅、显示器等，将机器人的尾方向，改为头方向，
   //       因此控制机器人时，需要对坐标方向取反
   double X, Y, Z, Yaw, Pitch, Roll;
   __Simulator.GetPlatformPosition(X, Y, Z, Yaw, Pitch, Roll);

   // 机器人运动
   __Robot.Move(-X, -Y, Z + __CentralZ, -Yaw, -Pitch, -Roll);

   #ifdef __BORLANDC__
   static double Time = 0;
   Time += __CtrlInterval;
   Form1->Chart1->Series[0]->AddXY(Time, __Simulator.Filter(Form1->ComboBox1->ItemIndex).InputAcc());
   Form1->Chart1->Series[1]->AddXY(Time, __Simulator.Filter(Form1->ComboBox1->ItemIndex).RealAcc());

   Time += __CtrlInterval;
   if(Time > Form1->Chart1->BottomAxis->Maximum)
   {
      Time = 0;
      Form1->Chart1->Series[0]->Clear();
      Form1->Chart1->Series[1]->Clear();
   }
   #endif
}
//---------------------------------------------------------------------------
// DirectPosEurlarCtrl()
//---------------------------------------------------------------------------
void CCtrlSystem::DirectPosEurlarCtrl(void)
{
   double X, Y, Z, Yaw, Pitch, Roll;

   CalcDestination(__Robot.PosX(), __Robot.PosY(), __Robot.PosZ(),
                   __DstPosEurlar[0], __DstPosEurlar[1], __DstPosEurlar[2],
                   X, Y, Z,
                   0.02, __CtrlInterval);
   CalcDestination(__Robot.PosYaw(), __Robot.PosPitch(), __Robot.PosRoll(),
                   __DstPosEurlar[3], __DstPosEurlar[4], __DstPosEurlar[5],
                   Yaw, Pitch, Roll,
                   1, __CtrlInterval);

   __Robot.Move(X, Y, Z, Yaw, Pitch, Roll);
   __Servo.RobotMove(__Robot);
}
//---------------------------------------------------------------------------
void CCtrlSystem::Control(void)
{
   #ifndef __BORLANDC__
   // 绿色LED指示灯闪烁，表明控制器在工作
   ++LedFlickCnt;
   if(LedFlickCnt < 20)
      LED_GREEN_ON;
   else if(LedFlickCnt < 40)
      LED_GREEN_OFF;
   else
      LedFlickCnt = 0;
   #endif

   if(!__Resetted)
   {
      // 复位控制
      ResettingCtrl();
   }
   else
   {
      // 由电缸控制模式转换到其他模式时，需要更新当前机器人的姿态
      if(__CtrlMode != __LstCtrlMode)
         OnCtrlModeChanged();

      // 控制
      switch(__CtrlMode)
      {
      case DIRECT_JACK_CTRL       :   DirectJackCtrl();        break;
      case DIRECT_POS_EURLAR_CTRL :   DirectPosEurlarCtrl();   break;
      case MOTION_SIMU_CTRL       :   MotionSimuCtrl();        break;
      }
   }

   if(__Servo.Zeroed())
      __Servo.ServoMove();

   // 通过正向运动学计算出上平台的位姿，用于虚拟仿真测试
   #ifdef __BORLANDC__
   //if(__Resetted)
   {
      double JackLengths[6];
      for(int i = 0; i < 6; ++i)
         JackLengths[i] = __Servo.JackLength(i) + ROBOT_JACK_LENGTH_MIN;

      // 计算上平台位姿
      __RobotSimu.CalcUpperPlatform(JackLengths);
   }
   #endif
}
//---------------------------------------------------------------------------
void CCtrlSystem::OnCtrlModeChanged(void)
{
   // 切换到直接电缸控制，需要拷贝当前每个电缸的实际长度
   if(__CtrlMode == DIRECT_JACK_CTRL)
   {
   }

   // 之前的控制模式是直接电缸控制，则需要更新重新计算当前的位姿
   if(__LstCtrlMode == DIRECT_JACK_CTRL)
      __Robot.UpdateUpperPlatformPosEurlar();

   __LstCtrlMode = __CtrlMode;
}
//---------------------------------------------------------------------------
void CCtrlSystem::CalcDestination(double SrcX, double SrcY, double SrcZ,
                                  double DstX, double DstY, double DstZ,
                                  double &X,   double &Y,   double &Z,
                                  double Speed, double Interval)
{
   double Vx = DstX - SrcX;
   double Vy = DstY - SrcY;
   double Vz = DstZ - SrcZ;
   double V  = sqrt(Vx * Vx + Vy * Vy + Vz * Vz);

   double Inc = Speed * Interval;
   if(V < Inc)
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

      X = SrcX + Vx * Inc;
      Y = SrcY + Vy * Inc;
      Z = SrcZ + Vz * Inc;
   }
}
