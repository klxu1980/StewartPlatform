//---------------------------------------------------------------------------


#pragma hdrstop

#include "MotionSimulator.h"
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
CFilter2ndHighPass::CFilter2ndHighPass(void)
 : __T(0.02),
   __K1(20),
   __K2(100),
   __XiCnt(0)
{
   __Xi[0] = __Xi[1] = __Xi[2] = 0;
   __Xh[0] = __Xh[1] = __Xh[2] = 0;
}
//---------------------------------------------------------------------------
void CFilter2ndHighPass::SetParams(double amax, double vmax, double xmax)
{
   __K1 = amax / xmax;
   __K2 = amax / vmax;
}
//---------------------------------------------------------------------------
void CFilter2ndHighPass::Initialize(double Xi)
{
   __Xi[0] = __Xi[1] = __Xi[2] = Xi;
}
//---------------------------------------------------------------------------
double CFilter2ndHighPass::Output(double Xi)
{
   __Xi[2] = __Xi[1];
   __Xi[1] = __Xi[0];
   __Xi[0] = Xi;

   __Xh[2] = __Xh[1];
   __Xh[1] = __Xh[0];
   __Xh[0] = ((2.0 + __K2 * __T) * __Xh[1] - __Xh[2] + __Xi[0] - 2.0 * __Xi[1] + __Xi[2]) / (1.0 + __K2 * __T + __K1 * __T * __T);

   return __Xh[0];
}
//---------------------------------------------------------------------------
CFilter2ndLowPass::CFilter2ndLowPass(void)
 : __T(0.02),
   __Tsqr(__T * __T),
   __Amax(9.8),
   __K1(__Amax / 0.4),
   __K2(__Amax / 0.1)
{
   __Xh[0] = __Xh[1] = __Xh[2] = 0;
}
//---------------------------------------------------------------------------
void CFilter2ndLowPass::SetParams(double T, double amax, double vmax, double xmax)
{
   __T    = T;
   __Tsqr = T * T;
   __Amax = amax;
   __K1   = amax / xmax;
   __K2   = amax / vmax;
}
//---------------------------------------------------------------------------
double CFilter2ndLowPass::Output(double Acc)
{
   // 加速度限幅
   if(Acc > __Amax)
      Acc = __Amax;
   else if(Acc < -__Amax)
      Acc = -__Amax;

   __Xh[2] = __Xh[1];
   __Xh[1] = __Xh[0];
   __Xh[0] = ((2.0 + __K2 * __T) * __Xh[1] - __Xh[2] + __Tsqr * Acc) / (1.0 + __K2 * __T + __K1 * __Tsqr);

   return __Xh[0];
}
//---------------------------------------------------------------------------
CMotionSimulator::CMotionSimulator(void)
{
}
//---------------------------------------------------------------------------
bool CMotionSimulator::SampleOutputTime(void)
{
   #ifdef __BORLANDC__
   return SecondSpan(__LstSampleTime, TDateTime::CurrentDateTime()) > 3.0;
   #endif
}
//---------------------------------------------------------------------------
void CMotionSimulator::FeedTargetAcc(double AccX, double AccY, double AccZ, double AccYaw, double AccPitch, double AccRoll)
{
   __Acc[0] = AccX;
   __Acc[1] = AccY;
   __Acc[2] = AccZ;
   __Acc[3] = AccYaw;
   __Acc[4] = AccPitch;
   __Acc[5] = AccRoll;

   #ifdef __BORLANDC__
   __LstSampleTime = TDateTime::CurrentDateTime();
   #endif
}
//---------------------------------------------------------------------------
// GetPlatformPosition()
//---------------------------------------------------------------------------
void CMotionSimulator::GetPlatformPosition(double &X, double &Y, double &Z, double &Yaw, double &Pitch, double &Roll)
{
   if(!SampleOutputTime())
   {
      X     = __AccFilter[0].Output(__Acc[0]);
      Y     = __AccFilter[1].Output(__Acc[1]);
      Z     = __AccFilter[2].Output(__Acc[2]);
      Yaw   = __AccFilter[3].Output(__Acc[3]);
      Pitch = __AccFilter[4].Output(__Acc[4]);
      Roll  = __AccFilter[5].Output(__Acc[5]);
   }
   else
   {
      X     = __AccFilter[0].Output(0);
      Y     = __AccFilter[1].Output(0);
      Z     = __AccFilter[2].Output(0);
      Yaw   = __AccFilter[3].Output(0);
      Pitch = __AccFilter[4].Output(0);
      Roll  = __AccFilter[5].Output(0);
   }
}
