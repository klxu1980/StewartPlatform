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
   // ���û����˼��β���
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

   // �����ŷ�����
   __Servo.SetServoCtrlInterval(__CtrlInterval);
   __Servo.SetServoTransParams(SERVO_PULSE_ROUND, SERVO_ROUND_MM);
   __Servo.SetServoSpeedLimit(SERVO_SPEED_MIN, SERVO_SPEED_MAX);
   __Servo.SetJackLimit(SERVO_JACK_MIN, SERVO_JACK_MAX);

   // ����������λ��
   __CentralZ = __Robot.CalcPlatformHeight((__Robot.MinJackLength() + __Robot.MaxJackLength()) * 0.5);

   // ����ÿ�����ɶ��ϵļ��ٶ�->λ��ϵ��(T, amax, vmax, xmax)
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
// ͨ�ű��ĸ�ʽ��
// CMD D1L D1H D2L D2H D3L D3H D4L D4H D5L D5H D6L D6H CRCL CRCH
// CMD������ָ�����ͣ�0 = ��ָ�1 = ϵͳ��λ��2 = ֱ�ӿ��Ƶ�׳��ȣ�
//                    3 = ֱ�ӿ�����ƽ̨λ�ˣ�4 = ģ��������
// D1L D1H��ʵ�ʿ������ݡ������׳��ȣ���λmm������0.1mm
//                        ������ƽ̨λ�ˣ�����X��Y��Z����λmm������0.1mm������Yaw��Pitch��Roll����λ�㣬����0.1��
//                        ����ģ�������棺����X��Y��Z����λm/s^2������0.001��
// CRCL CRCH��CRCУ��
//---------------------------------------------------------------------------
void CCtrlSystem::RcvCommByte(char Byte)
{
   __RcvedBytes[__RcvedCnt++] = Byte;
   if(__RcvedCnt == 9)
   {
      short CRC = CalcCRC(__RcvedBytes, 7);

      // CRCУ����ȷ�������ָ��
      if(CRC == Bytes2Word(__RcvedBytes + 7) ) //(short)((unsigned char)__RcvedBytes[7] | ((unsigned char)__RcvedBytes[8] << 8)))
      {
         switch(__RcvedBytes[0])
         {
         case 1 :   // �˶�̨��λ
            Reset();
            break;
         case DIRECT_JACK_CTRL :   // ���õ�׳���
            if(__LstCtrlMode != DIRECT_JACK_CTRL)
            {
               // ��ʼ��Ŀ���׳���
               for(int i = 0; i < 6; ++i)
                  __DstJackLength[i] = __Robot.Jacks[i].ServoLength;
            }
            __JackSpeed[__RcvedBytes[1]]     = Bytes2Word(__RcvedBytes + 4) * 0.001;
            __DstJackLength[__RcvedBytes[1]] = Bytes2Word(__RcvedBytes + 2) * 0.001;
            break;
         case DIRECT_POS_EURLAR_CTRL :   // �յ���ƽ̨λ��
            if(__RcvedBytes[1] < 3)
               __DstPosEurlar[__RcvedBytes[1] ] = Bytes2Word(__RcvedBytes + 2) * 0.001;
            else if(__RcvedBytes[1] < 6)
               __DstPosEurlar[__RcvedBytes[1] ] = __RcvedBytes[2] | (__RcvedBytes[3] << 8);
            break;
         case MOTION_SIMU_CTRL :   // �յ��˶����ٶ�
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
      // CRCУ��ʧ�ܣ��������յ����ֽ�ɾ��
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
// ��λ����
//---------------------------------------------------------------------------
void CCtrlSystem::ResettingCtrl(void)
{
   // �����˸�λ
   // �������ϵ�ʱ�����߷��͸�λ��ť����ִ�и�λ��������ʱ�����������κ�ָ��
   // ��λʱ�����ȿ������е��������ֱ������������λ����(��λ����)
   // ֮����Z�Ỻ��������ֱ���������ĵ㡣
   if(!__Servo.Zeroed())
   {
      __Servo.GoZeroCtrl();
   }
   else
   {
      // ��������󣬵����趨��ʼ״̬
      if(__CentralZ - __Robot.PosZ() < 0.001)
         __Resetted = true;

      __Robot.Move(0, 0, __Robot.PosZ() + GO_ZERO_SPEED * __CtrlInterval, 0, 0, 0);
      __Servo.RobotMove(__Robot, true);
   }
}
//---------------------------------------------------------------------------
// DirectJackCtrl()
// �����˵������˶�ѧ�����ڷ�������
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
// �˶�ģ�����
// ���ݸ������ٶȣ�������ƽ̨�˶�
//---------------------------------------------------------------------------
void CCtrlSystem::MotionSimuCtrl(void)
{
   // �����˶�����
   // ע�⣺�����˶�����ʱ��Ϊ�˱���������˳���ʱ��ϳ����ϵͳ�ٴ죬��������������˵������������
   //       Ȼ���ټ�����һ�������ڵ������˶�����
   __Servo.RobotMove(__Robot);

   // �˶�ģ�����
   // �������˶�ģ��ģ��������ǰӦ�����λ��
   // Ȼ��������������λ���˶�
   // ע�⣺���˶�ģ��ʱ��Ϊ�˱��ڰ�װ���Ρ���ʾ���ȣ��������˵�β���򣬸�Ϊͷ����
   //       ��˿��ƻ�����ʱ����Ҫ�����귽��ȡ��
   double X, Y, Z, Yaw, Pitch, Roll;
   __Simulator.GetPlatformPosition(X, Y, Z, Yaw, Pitch, Roll);

   // �������˶�
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
   // ��ɫLEDָʾ����˸�������������ڹ���
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
      // ��λ����
      ResettingCtrl();
   }
   else
   {
      // �ɵ�׿���ģʽת��������ģʽʱ����Ҫ���µ�ǰ�����˵���̬
      if(__CtrlMode != __LstCtrlMode)
         OnCtrlModeChanged();

      // ����
      switch(__CtrlMode)
      {
      case DIRECT_JACK_CTRL       :   DirectJackCtrl();        break;
      case DIRECT_POS_EURLAR_CTRL :   DirectPosEurlarCtrl();   break;
      case MOTION_SIMU_CTRL       :   MotionSimuCtrl();        break;
      }
   }

   if(__Servo.Zeroed())
      __Servo.ServoMove();

   // ͨ�������˶�ѧ�������ƽ̨��λ�ˣ���������������
   #ifdef __BORLANDC__
   //if(__Resetted)
   {
      double JackLengths[6];
      for(int i = 0; i < 6; ++i)
         JackLengths[i] = __Servo.JackLength(i) + ROBOT_JACK_LENGTH_MIN;

      // ������ƽ̨λ��
      __RobotSimu.CalcUpperPlatform(JackLengths);
   }
   #endif
}
//---------------------------------------------------------------------------
void CCtrlSystem::OnCtrlModeChanged(void)
{
   // �л���ֱ�ӵ�׿��ƣ���Ҫ������ǰÿ����׵�ʵ�ʳ���
   if(__CtrlMode == DIRECT_JACK_CTRL)
   {
   }

   // ֮ǰ�Ŀ���ģʽ��ֱ�ӵ�׿��ƣ�����Ҫ�������¼��㵱ǰ��λ��
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
