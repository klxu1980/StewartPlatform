//---------------------------------------------------------------------------


#pragma hdrstop

#include "RobotSimu.h"
#include <math.h>
#include <Math.hpp>
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
void CRobotSimu::JackMove(int JackID, double Servo)
{
   Robot.SetJackServo(JackID, Servo);
   Robot.AfterServoMoved();
}
//---------------------------------------------------------------------------
void CRobotSimu::JackMove(double Servo[6])
{
   Robot.AfterServoMoved(Servo[0], Servo[1], Servo[2], Servo[3], Servo[4], Servo[5]);
}
//---------------------------------------------------------------------------
void CRobotSimu::PlatformMove(double Pos[3], double Euler[3])
{
   Robot.PlatformMove(Pos[0], Pos[1], Pos[2], Euler[0], Euler[1], Euler[2], false);
}
//---------------------------------------------------------------------------
void CRobotSimu::GetMeasurement(double M1[3], double M2[3], double M3[3])
{
   // 上平台等边三角形测点
   double V[3][3] = {0, 1, 0,
                     cos(M_PI / 3), -0.5, 0,
                     -cos(M_PI / 3), -0.5, 0};

   // 测点在全局坐标系中的坐标
   double P[3][3];
   Robot.RobotIKP.CalcGlobalCoordination(V, P, 3);

   // 测点在观测器中的坐标
   double M[3][3];
   Observer.PointFromRobotToObserver(M, P, 3);

   // 拷贝坐标
   CopyVector(M1, M[0]);
   CopyVector(M2, M[1]);
   CopyVector(M3, M[2]);
}
//---------------------------------------------------------------------------
void CRobotSimu::GetJackServo(double Servo[6])
{
   for(int i = 0; i < 6; ++i)
      Servo[i] = Robot.Jack[i].Servo;
}
//---------------------------------------------------------------------------
void CRobotSimu::GetPosEuler(double Pos[3], double Euler[3])
{
   CopyVector(Pos, Robot.RobotFKP.UpperPos);
   CopyVector(Euler, Robot.RobotFKP.UpperEuler);
}
//---------------------------------------------------------------------------
void CRobotSimu::GenerateSamples(CCalibrator &Calibrator, int SampleCnt)
{
   if(GenerateSampleByRandom)
   {
      Randomize();
      for(int i = 0; i < SampleCnt; ++i)
      {
         // 随机设置机器人伺服电缸长度，通过正向运动学计算机器人位姿
         int   JackID = RandomRange(0, 6);
         float Servo  = RandomRange(0, ServoRange) * 0.001;

         // 虚拟机器人运动
         JackMove(JackID, Servo);

         // 获得虚拟机器人测量点坐标
         double M1[3], M2[3], M3[3];
         GetMeasurement(M1, M2, M3);

         // 虚拟机器人电缸伸出量
         double Servos[6];
         GetJackServo(Servos);

         // 将标定数据加入标定器
         Calibrator.AddCaliData(M1, M2, M3, Servos);

         // 虚拟机器人位姿，仅供测试用
         /*
         double Pos[3], Euler[3];
         GetPosEuler(Pos, Euler);
         Calibrator.AddCaliData(Pos, Euler, Servos);
         */
   }
   }
   else
   {
      double Step = ServoRange * 0.001 / (SampleCnt - 1);
      for(int L1 = 0; L1 < SampleCnt; ++L1)
         for(int L2 = 0; L2 < SampleCnt; ++L2)
            for(int L3 = 0; L3 < SampleCnt; ++L3)
               for(int L4 = 0; L4 < SampleCnt; ++L4)
                  for(int L5 = 0; L5 < SampleCnt; ++L5)
                     for(int L6 = 0; L6 < SampleCnt; ++L6)
                     {
                        double Servos[6] = {L1 * Step, L2 * Step, L3 * Step, L4 * Step, L5 * Step, L6 * Step};

                        // 虚拟机器人运动
                        JackMove(Servos);

                        // 获得虚拟机器人测量点坐标
                        double M1[3], M2[3], M3[3];
                        GetMeasurement(M1, M2, M3);

                        // 将标定数据加入标定器
                        Calibrator.AddCaliData(M1, M2, M3, Servos);
                     }
   }
}
//---------------------------------------------------------------------------
void CRobotSimu::GenerateRobotErrors(int LinearRange)
{
   // 机器人误差
   for(int i = 0; i < 6; ++i)
      for(int m = 0; m < 3; ++m)
         Robot.ErrJointUpper[i][m] = RandomRange(-LinearRange, LinearRange) * 0.001;

   for(int i = 0; i < 6; ++i)
      for(int m = 0; m < 3; ++m)
         Robot.ErrJointLower[i][m] = IgnoreLowerJointErr? 0 : (RandomRange(-LinearRange, LinearRange) * 0.001);


   for(int i = 0; i < 6; ++i)
      Robot.ErrJackFixedLen[i] = IgnoreJackErr? 0 : (RandomRange(-LinearRange, LinearRange) * 0.001);

   Robot.InitStructureParams();
}
//---------------------------------------------------------------------------
void CRobotSimu::GenerateObserverErrors(int LinearRange, int RotatoryRange)
{
   if(!IgnoreObserveErr)
   {
      Observer.ErrPos[0] = RandomRange(-LinearRange, LinearRange) * 0.001;
      Observer.ErrPos[1] = RandomRange(-LinearRange, LinearRange) * 0.001;
      Observer.ErrPos[2] = RandomRange(-LinearRange, LinearRange) * 0.001;

      Observer.ErrEuler[0] = RandomRange(-RotatoryRange, RotatoryRange);
      Observer.ErrEuler[1] = RandomRange(-RotatoryRange, RotatoryRange);
      Observer.ErrEuler[2] = RandomRange(-RotatoryRange, RotatoryRange);
   }
   else
   {
      Observer.ErrPos[0] = 0;
      Observer.ErrPos[1] = 0;
      Observer.ErrPos[2] = 0;

      Observer.ErrEuler[0] = 0;
      Observer.ErrEuler[1] = 0;
      Observer.ErrEuler[2] = 0;
   }
}
//---------------------------------------------------------------------------
void CRobotSimu::GetRobotErrors(double Errors[42])
{
   for(int i = 0; i < 6; ++i)
   {
      Errors[i * 3]     = Robot.ErrJointUpper[i][0];
      Errors[i * 3 + 1] = Robot.ErrJointUpper[i][1];
      Errors[i * 3 + 2] = Robot.ErrJointUpper[i][2];
   }

   // 下平台铰接点误差，共18个
   for(int i = 0; i < 6; ++i)
   {
      Errors[i * 3 + 18] = Robot.ErrJointLower[i][0];
      Errors[i * 3 + 19] = Robot.ErrJointLower[i][1];
      Errors[i * 3 + 20] = Robot.ErrJointLower[i][2];
   }

   // 电缸零点误差，共6个
   for(int i = 0; i < 6; ++i)
      Errors[i + 36] = Robot.ErrJackFixedLen[i];
}
//---------------------------------------------------------------------------
void CRobotSimu::SetRobotErrors(double Errors[42])
{
   for(int i = 0; i < 6; ++i)
   {
      Robot.ErrJointUpper[i][0] = Errors[i * 3];
      Robot.ErrJointUpper[i][1] = Errors[i * 3 + 1];
      Robot.ErrJointUpper[i][2] = Errors[i * 3 + 2];
   }

   // 下平台铰接点误差，共18个
   for(int i = 0; i < 6; ++i)
   {
      Robot.ErrJointLower[i][0] = Errors[i * 3 + 18];
      Robot.ErrJointLower[i][1] = Errors[i * 3 + 1 + 18];
      Robot.ErrJointLower[i][2] = Errors[i * 3 + 2 + 18];
   }

   // 电缸零点误差，共6个
   for(int i = 0; i < 6; ++i)
      Robot.ErrJackFixedLen[i] = Errors[i + 36];

   Robot.InitStructureParams();
}
