//---------------------------------------------------------------------------


#pragma hdrstop

#include "PositionPred.h"
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
CMotionSimulator::CMotionSimulator(int SampleCnt)
 : __MaxSampleCnt(SampleCnt),
   __SampleCnt(0)
{
   for(int i = 0; i < 6; ++i)
      A[i] = B[i] = 0.0;

   Reset();
}
//---------------------------------------------------------------------------
void CMotionSimulator::PopOldSample(double *Array)
{
   for(int i = 1; i < __SampleCnt; ++i)
      Array[i - 1] = Array[i];
}
//---------------------------------------------------------------------------
// Reset()
//     当飞行模拟重新开始，或者因为重置导致跟随位置发生较大变化时，应当进行Reset操作。
// 进入Reset状态后，运动跟随器不再跟随新的位置变化，而是保持恒定速度的位置输出，使得高通滤波器输出之间变为0。
//     当滤波器输出接近0时，则Reset状态结束
//---------------------------------------------------------------------------
void CMotionSimulator::Reset(void)
{
   __Resetting = true;
   __Resetted  = false;
}
//---------------------------------------------------------------------------
void CMotionSimulator::FeedTargetPosition(double X, double Y, double Z, double Yaw, double Pitch, double Roll)
{
   // 从队列中弹出最早的采样
   if(__SampleCnt == __MaxSampleCnt)
   {
      PopOldSample(__X);
      for(int i = 0; i < 6; ++i)
         PopOldSample(__Y[i]);
      --__SampleCnt;
   }

   // 将最新采样压入队列
   __X[__SampleCnt]    = GetCurTime();
   __Y[0][__SampleCnt] = X;
   __Y[1][__SampleCnt] = Y;
   __Y[2][__SampleCnt] = Z;
   __Y[3][__SampleCnt] = Yaw;
   __Y[4][__SampleCnt] = Pitch;
   __Y[5][__SampleCnt] = Roll;

   if(++__SampleCnt < __MaxSampleCnt || __Resetting)
      return;

   if(!__Resetted)
   {
      __FilterHighPass[0].Initialize(X);
      __FilterHighPass[1].Initialize(X);
      __FilterHighPass[2].Initialize(X);
      __FilterHighPass[3].Initialize(Yaw);
      __FilterHighPass[4].Initialize(Pitch);
      __FilterHighPass[5].Initialize(Roll);

      __Resetted = true;
   }

   // 检查样本是否存在不连续，或加速度过大
   // 加速度计算采用以下方式：
   //   |   ---------------------
   //   |  /
   //   | /
   //   |/
   //  -----|-------|------|-------
   //      S0      S1     S2
   //
   //        y2 - y1      y1 - y0
   //       ---------  - ---------
   //        t2 - t1      t1 - t0
   //   a = ----------------------
   //              t2 - t1
   int ChkRange = __SampleCnt - 2;
   for(int i = 0; i < ChkRange; ++i)
   {
      double DT21 = __X[i + 2] - __X[i + 1];
      double DT10 = __X[i + 1] - __X[i];

      if(DT21 > MAX_TIME_INTERVAL || DT10 > MAX_TIME_INTERVAL ||
         fabs(CalcSampleAcc(__Y[0][i + 2], __Y[0][i + 1], __Y[0][i], DT21, DT10)) > MAX_LINEAR_ACC ||
         fabs(CalcSampleAcc(__Y[1][i + 2], __Y[1][i + 1], __Y[1][i], DT21, DT10)) > MAX_LINEAR_ACC ||
         fabs(CalcSampleAcc(__Y[2][i + 2], __Y[2][i + 1], __Y[2][i], DT21, DT10)) > MAX_LINEAR_ACC ||
         fabs(CalcSampleAcc(__Y[3][i + 2], __Y[3][i + 1], __Y[3][i], DT21, DT10)) > MAX_ROTATARY_ACC ||
         fabs(CalcSampleAcc(__Y[4][i + 2], __Y[4][i + 1], __Y[4][i], DT21, DT10)) > MAX_ROTATABY_ACC ||
         fabs(CalcSampleAcc(__Y[5][i + 2], __Y[5][i + 1], __Y[5][i], DT21, DT10)) > MAX_ROTATARY_ACC)
      {
         Reset();
         return;
      }

   }

   // 直线拟合
   for(int i = 0; i < 6; ++i)
      Fit(__X, __Y[i], A[i], B[i]);
}
//---------------------------------------------------------------------------
void CMotionSimulator::Fit(double *X, double *Y, double &A, double &B)
{
   double xmean = 0.0;
   double ymean = 0.0;
   for (int i = 0; i < __SampleCnt; ++i)
   {
      xmean += X[i];
      ymean += Y[i];
   }
   xmean /= __SampleCnt;
   ymean /= __SampleCnt;

   double sumx2 = 0.0;
   double sumy2 = 0.0;
   double sumxy = 0.0;
   for (int i = 0; i < __SampleCnt; ++i)
   {
      sumx2 += (X[i] - xmean) * (X[i] - xmean);
      sumy2 += (Y[i] - ymean) * (Y[i] - ymean);
      sumxy += (Y[i] - ymean) * (X[i] - xmean);
   }
   A = sumxy / sumx2;
   B = ymean - A * xmean;
}
//---------------------------------------------------------------------------
// GetPlatformPosition()
//---------------------------------------------------------------------------
void CMotionSimulator::GetPlatformPosition(double &X, double &Y, double &Z, double &Yaw, double &Pitch, double &Roll)
{
   // 计算出预测位置
   double Time = GetCurTime();
   X     = A[0] * Time + B[0];
   Y     = A[1] * Time + B[1];
   Z     = A[2] * Time + B[2];
   Yaw   = A[3] * Time + B[3];
   Pitch = A[4] * Time + B[4];
   Roll  = A[5] * Time + B[5];

   // 送入高通滤波器
   X = __FilterHighPass[0].Output(X);
   Y = __FilterHighPass[1].Output(Y);
   Z = __FilterHighPass[2].Output(Z);
   Yaw   = __FilterHighPass[3].Output(Yaw);
   Pitch = __FilterHighPass[4].Output(Pitch);
   Roll  = __FilterHighPass[5].Output(Roll);

   // 如果运动位置已经接近原点，则退出Reset状态(如果当前处于Reset状态的话)
   if(__Resetting && X * X + Y * Y + Z * Z + Yaw * Yaw + Pitch * Pitch + Roll * Roll < 0.001)
      __Resetting = false;
}
//---------------------------------------------------------------------------
double CMotionSimulator::GetCurTime(void)
{
   #ifdef __BORLANDC__
   return SecondSpan(__StartTime, TDateTime::CurrentDateTime());
   #endif
}
