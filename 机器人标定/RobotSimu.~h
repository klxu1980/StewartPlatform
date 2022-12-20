//---------------------------------------------------------------------------

#ifndef RobotSimuH
#define RobotSimuH
#include "Robot.h"
#include "Observer.h"
#include "Calibrator.h"
//---------------------------------------------------------------------------
class CRobotSimu
{
public:
   CRobot    Robot;
   CObserver Observer;
public:
   int  ServoRange;        // 伺服运动范围，单位mm
   int  JackSampleCnt;     // 每个电缸的采样数量
public:
   bool IgnoreLowerJointErr;
   bool IgnoreJackErr;
   bool IgnoreObserveErr;
   bool GenerateSampleByRandom;
public:
   void JackMove(int JackID, double Servo);
   void JackMove(double Servo[6]);
   void PlatformMove(double Pos[3], double Euler[3]);
public:
   void GetMeasurement(double M1[3], double M2[3], double M3[3]);
   void GetJackServo(double Servo[6]);
   void GetPosEuler(double Pos[3], double Euler[3]);
public:
   void GenerateRobotErrors(int ErrorRange);
   void GenerateObserverErrors(int LinearRange, int RotatoryRange);
   void GenerateSamples(CCalibrator &Calibrator, int SampleCnt);
public:
   void GetRobotErrors(double Errors[42]);
   void SetRobotErrors(double Errors[42]);
};
#endif
