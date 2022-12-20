//---------------------------------------------------------------------------


#pragma hdrstop

#include "MotionSimu.h"

#ifdef __BORLANDC__
#include <DateUtils.hpp>
#endif
//---------------------------------------------------------------------------
#define  GAMMA_FACTOR           0.8
#define  MIN_INC_ERROR          0.001      // 单位m
#define  MAX_RECALC_POS_TIMES   32
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CFilter2ndHighpass::CFilter2ndHighpass(void)
 : __T(0.02),
   __K1(20),
   __K2(100)
{
   __Xi[0] = __Xi[1] = __Xi[2] = 0;
   __Xh[0] = __Xh[1] = __Xh[2] = 0;
}
//---------------------------------------------------------------------------
void CFilter2ndHighpass::SetParams(double amax, double vmax, double xmax)
{
   __K1 = amax / xmax;
   __K2 = amax / vmax;
}
//---------------------------------------------------------------------------
void CFilter2ndHighpass::Initialize(double Xi)
{
   __Xi[0] = __Xi[1] = __Xi[2] = Xi;
   __Xh[0] = __Xh[1] = __Xh[2] = 0;
}
//---------------------------------------------------------------------------
double CFilter2ndHighpass::Output(double Xi)
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
void CMotionSimulator::NewPosition(double X, double Y, double Z, double Yaw, double Pitch, double Roll)
{
   __PosPredict.NewSample(X, Y, Z, Yaw, Pitch, Roll);
}
//---------------------------------------------------------------------------
bool CMotionSimulator::CalcMotion(double &X, double &Y, double &Z,                 
                                  double &Yaw, double &Pitch, double &Roll)
{
   if(__PosPredict.CurPosition(X, Y, Z, Yaw, Pitch, Roll))
   {
      // 对姿态进行高通滤波
      X     = __FilterHighpass[0].Output(X);
      Y     = __FilterHighpass[1].Output(Y);
      Z     = __FilterHighpass[2].Output(Z);
      Yaw   = __FilterHighpass[3].Output(Yaw);
      Pitch = __FilterHighpass[4].Output(Pitch);
      Roll  = __FilterHighpass[5].Output(Roll);

      return true;
   }
   else
   {
      
      return false;
   }
}
