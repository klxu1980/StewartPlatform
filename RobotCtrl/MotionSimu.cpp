//---------------------------------------------------------------------------


#pragma hdrstop

#include "MotionSimu.h"
#include "RobotComm.h"
#include "GlobalDef.h"
#include <math.h>

#ifdef __BORLANDC__
#include <DateUtils.hpp>
#endif
//---------------------------------------------------------------------------
#define  GAMMA_FACTOR           0.8
#define  MIN_INC_ERROR          0.001      // 单位m
#define  MAX_RECALC_POS_TIMES   32

#define  MAX_TIME_INTERVAL      3.0
#define  MAX_LINEAR_ACC         9.8      // m/s^2
#define  MAX_ROTATARY_ACC       10       // deg/s^2
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CFilterAcc2Motion::CFilterAcc2Motion(void)
 : __T(0.02),
   __Amax(9.8),
   __K1(__Amax / 0.4),
   __K2(__Amax / 0.1)
{
   __Xh[0] = __Xh[1] = __Xh[2] = 0;
}
//---------------------------------------------------------------------------
void CFilterAcc2Motion::SetParams(double T, double amax, double vmax, double xmax)
{
   __T    = T;
   __Tsqr = T * T;
   __Amax = amax;
   __K1   = amax / xmax;
   __K2   = amax / vmax;
}
//---------------------------------------------------------------------------
double CFilterAcc2Motion::Output(double Acc)
{
   __InputAcc = Acc;

   // 加速度限幅
   if(Acc > __Amax)
      Acc = __Amax;
   else if(Acc < -__Amax)
      Acc = -__Amax;

   // 注意：__Xh[0] = Xh[k], __Xh[1] = Xh[k-1], __Xh[2] = Xh[k-2]
   __Xh[2] = __Xh[1];
   __Xh[1] = __Xh[0];
   __Xh[0] = ((2.0 + __K2 * __T) * __Xh[1] - __Xh[2] + __T * __T * Acc) / (1.0 + __K2 * __T + __K1 * __T * __T);

   // 计算实际输出加速度
   __RealAcc = (__Xh[0] - 2.0 * __Xh[1] + __Xh[2]) / (__T * __T); 

   return __Xh[0];
}
//---------------------------------------------------------------------------
void CFilterAcc2Angle::SetParams(double T, double amax, double omega_max)
{
   if(amax > 9.8)
      __Amax = 9.8;
   else
      __Amax = amax;
      
   __Filter.SetParams(T, asin(amax / 9.8), omega_max * M_PI / 180.0, asin(amax / 9.8));
}
//---------------------------------------------------------------------------
double CFilterAcc2Angle::Output(double Acc)
{
   if(Acc > __Amax)
      Acc = __Amax;
   else if(Acc < -__Amax)
      Acc = -__Amax;
      
   __Angle = __Filter.Output(asin(Acc / 9.8));
   return __Angle * 180.0 / M_PI;
}
//---------------------------------------------------------------------------
double CFilterAcc2Angle::RealAcc(void)
{
   return sin(__Filter.XValue()) * 9.8;
}
//---------------------------------------------------------------------------
double CFilterAcc2Angle::InputAcc(void)
{
   return sin(__Filter.InputAcc());
}
//---------------------------------------------------------------------------
CFilterRSpd2Angle::CFilterRSpd2Angle(void)
 : __T(0.02)
{
   __Xh[0] = __Xh[1] = 0;
}
//---------------------------------------------------------------------------
void CFilterRSpd2Angle::SetParams(double T, double vmax, double xmax)
{
   __T = T;
   __K = vmax / xmax;
   __Vmax = vmax;
}
//---------------------------------------------------------------------------
double CFilterRSpd2Angle::Output(double V)
{
   if(V > __Vmax)
      V = __Vmax;
   else if(V < -__Vmax)
      V = -__Vmax;

   __Xh[1] = __Xh[0];
   __Xh[0] = (__Xh[1] - __T * V) / (1.0 + __T * __K);

   __InputV = V;
   __RealV  = (__Xh[0] - __Xh[1]) / __T;

   return __Xh[0];
}
//---------------------------------------------------------------------------
/*
CLowPassFilter::CLowPassFilter(void)
{
   __X[0] = __X[1] = 0;
   __Y[0] = __Y[1] = 0;
}
//--------------------------------------------------------------------------
void CLowPassFilter::SetParams(double T, double FreqThresh, double Damping)
{
   __b  = pow(FreqThresh, 2.0) * pow(T, 2.0);
   __a0 = pow(FreqThresh, 2.0) * pow(T, 2.0) + 4.0 * FreqThresh * Damping * T + 4.0;
   __a1 = 2.0 * pow(FreqThresh, 2.0) * pow(T, 2.0) - 8.0;
   __a2 = pow(FreqThresh, 2.0) * pow(T, 2.0) - 4.0 * FreqThresh * Damping * T + 4.0;
   __T  = T;
}
//--------------------------------------------------------------------------
double CLowPassFilter::Filter(double x)
{
   double y = (__b * (x + 2.0 * __X[0] + __X[1]) - __a1 * __Y[0] - __a2 * __Y[1]) / __a0;

   __X[1] = __X[0];
   __X[0] = x;

   __Y[1] = __Y[0];
   __Y[0] = y;

   return y;
}
*/
CLowPassFilter::CLowPassFilter(void)
{
   __Y = 0;
   __Alpha = 0;
}
//--------------------------------------------------------------------------
void CLowPassFilter::SetParams(double Alpha)
{
   __Alpha = Alpha;
}
//--------------------------------------------------------------------------
double CLowPassFilter::Filter(double x)
{
   __Y = __Alpha * __Y + (1.0 - __Alpha) * x;
   return __Y;
}
//--------------------------------------------------------------------------
double CHighPassFilter::Filter(double x)
{
   double y = CLowPassFilter::Filter(x);
   return x - y;
}
//---------------------------------------------------------------------------
CMotionSimulator::CMotionSimulator(void)
{
   for(int i = 0; i < 6; ++i)
      HighPassFilter[i].SetParams(-1);
}
//---------------------------------------------------------------------------
bool CMotionSimulator::SampleOutputTime(void)
{
   #ifdef __BORLANDC__
   return SecondSpan(__LstSampleTime, TDateTime::CurrentDateTime()) > 3.0;
   #else
   return false;
   #endif
}
//---------------------------------------------------------------------------
void CMotionSimulator::FeedTargetAccAndSpd(double AccX, double AccY, double AccZ, double SpdYaw, double SpdPitch, double SpdRoll)
{
   __Input[0] = AccX;
   __Input[1] = AccY;
   __Input[2] = AccZ;
   __Input[3] = SpdYaw;
   __Input[4] = SpdPitch;
   __Input[5] = SpdRoll;

   #ifdef __BORLANDC__
   __LstSampleTime = TDateTime::CurrentDateTime();
   #endif
}
//---------------------------------------------------------------------------
// GetPlatformPosition()
//---------------------------------------------------------------------------
void CMotionSimulator::GetPlatformPosition(double &X, double &Y, double &Z, double &Yaw, double &Pitch, double &Roll)
{  
   // 如果超时没有输入，则将所有输入变为0
   // 直接这样做容易引起冲击，后面要修改
   if(SampleOutputTime())
      for(int i = 0; i < 6; ++i)
         __Input[i] = 0;

   // 令输入通过高通滤波器
   double FilteredInput[6];
   for(int i = 0; i < 6; ++i)
      if(HighPassFilter[i].Enabled())
         FilteredInput[i] = HighPassFilter[i].Filter(__Input[i]);
      else
         FilteredInput[i] = __Input[i];


   // 由加速度计算X、Y、Z方向上的运动量
   // 注意：该运动量以机体坐标系为参考
   X = Acc2Motion[0].Output(FilteredInput[0]);
   Y = Acc2Motion[1].Output(FilteredInput[1]);
   Z = Acc2Motion[2].Output(FilteredInput[2]);

   // 将直线运动量变换到机器人全局坐标系
   // 还未完成

   // 由角速度计算姿态角
   Yaw   = RSpd2Rotate[0].Output(FilteredInput[3]);
   Pitch = RSpd2Rotate[1].Output(FilteredInput[4]);
   Roll  = RSpd2Rotate[2].Output(FilteredInput[5]);

   // 由Y、X方向上的加速度计算俯仰角和滚转角，通过重力模拟持续加速度
   Pitch -= Acc2Angle[0].Output(__Input[1]);   // 俯仰角产生Y方向加速度
   Roll  -= Acc2Angle[1].Output(__Input[0]);   // 俯仰角产生X方向加速度

   // 实际模拟结果
   __Simulated[0] = Acc2Motion[0].RealAcc() + Acc2Angle[0].RealAcc();
   __Simulated[1] = Acc2Motion[1].RealAcc() + Acc2Angle[1].RealAcc();
   __Simulated[2] = Acc2Motion[2].RealAcc();
   __Simulated[3] = RSpd2Rotate[0].RealSpd();
   __Simulated[4] = RSpd2Rotate[1].RealSpd();
   __Simulated[5] = RSpd2Rotate[2].RealSpd();
}
//--------------------------------------------------------------------------
void CMotionSimulator::GetSimulatedAccAndSpd(double &AccX, double &AccY, double &AccZ, double &SpdYaw, double &SpdPitch, double &SpdRoll)
{
   AccX = __Simulated[0];
   AccY = __Simulated[1];
   AccZ = __Simulated[2];
   SpdYaw   = __Simulated[3];
   SpdPitch = __Simulated[4];
   SpdRoll  = __Simulated[5];
}
//---------------------------------------------------------------------------
void CMotionSimulator::SetParams(CMotionSimuParams Params)
{
   Acc2Motion[0].SetParams(CTRL_INTERVAL, Params.AccXMax, Params.SpdXMax, Params.XMax);
   Acc2Motion[1].SetParams(CTRL_INTERVAL, Params.AccYMax, Params.SpdYMax, Params.YMax);
   Acc2Motion[2].SetParams(CTRL_INTERVAL, Params.AccZMax, Params.SpdZMax, Params.ZMax);

   Acc2Angle[0].SetParams(CTRL_INTERVAL, Params.AccPitchMax, Params.AccPitchSpdMax);
   Acc2Angle[1].SetParams(CTRL_INTERVAL, Params.AccRollMax,  Params.AccRollSpdMax);

   RSpd2Rotate[0].SetParams(CTRL_INTERVAL, Params.YawSpdMax,   Params.YawMax);
   RSpd2Rotate[1].SetParams(CTRL_INTERVAL, Params.PitchSpdMax, Params.PitchMax);
   RSpd2Rotate[2].SetParams(CTRL_INTERVAL, Params.RollSpdMax,  Params.RollMax);

   HighPassFilter[0].SetParams(Params.HighPassX);
   HighPassFilter[1].SetParams(Params.HighPassY);
   HighPassFilter[2].SetParams(Params.HighPassZ);
   HighPassFilter[3].SetParams(Params.HighPassYaw);
   HighPassFilter[4].SetParams(Params.HighPassPitch);
   HighPassFilter[5].SetParams(Params.HighPassRoll);
}
