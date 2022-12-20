//---------------------------------------------------------------------------


#pragma hdrstop

#include "MotionSimulator.h"
#include <math.h>

#ifdef __BORLANDC__
#include <DateUtils.hpp>
#endif
//---------------------------------------------------------------------------
#define  GAMMA_FACTOR           0.8
#define  MIN_INC_ERROR          0.001      // ��λm
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

   // ���ٶ��޷�
   if(Acc > __Amax)
      Acc = __Amax;
   else if(Acc < -__Amax)
      Acc = -__Amax;

   // ע�⣺__Xh[0] = Xh[k], __Xh[1] = Xh[k-1], __Xh[2] = Xh[k-2]
   __Xh[2] = __Xh[1];
   __Xh[1] = __Xh[0];
   __Xh[0] = ((2.0 + __K2 * __T) * __Xh[1] - __Xh[2] + __T * __T * Acc) / (1.0 + __K2 * __T + __K1 * __T * __T);

   // ����ʵ��������ٶ�
   __RealAcc = (__Xh[0] - 2.0 * __Xh[1] + __Xh[2]) / (__T * __T); 

   return __Xh[0];
}
//---------------------------------------------------------------------------
void CFilterAcc2Angle::SetParams(double T, double amax, double omega_max)
{
   __Filter.SetParams(T, asin(amax / 9.8), omega_max * M_PI / 180.0, asin(amax / 9.8));
}
//---------------------------------------------------------------------------
double CFilterAcc2Angle::Output(double Acc)
{
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
}
//---------------------------------------------------------------------------
double CFilterRSpd2Angle::Output(double V)
{
   __Xh[1] = __Xh[0];
   __Xh[0] = (__Xh[1] - __T * V) / (1.0 + __T * __K);

   __InputV = V;
   __RealV  = (__Xh[0] - __Xh[1]) / __T;

   return __Xh[0];
}
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
void CHighPassFilter::SetParams(double T, double FreqThresh, double Damping)
{
   __LowPass.SetParams(T, FreqThresh, Damping);
}
//--------------------------------------------------------------------------
double CHighPassFilter::Filter(double x)
{
   double y = __LowPass.Filter(x);
   return x - y;
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
   #else
   return false;
   #endif
}
//---------------------------------------------------------------------------
void CMotionSimulator::FeedTargetAcc(double AccX, double AccY, double AccZ, double SpdYaw, double SpdPitch, double SpdRoll)
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
   // �����ʱû�����룬�����������Ϊ0
   // ֱ������������������������Ҫ�޸�
   if(SampleOutputTime())
      for(int i = 0; i < 6; ++i)
         __Input[i] = 0;

   // ������ͨ����ͨ�˲���
   double FilteredInput[6];
   for(int i = 0; i < 6; ++i)
      if(HighPassEnabled[i])
         FilteredInput[i] = HighPassFilter[i].Filter(__Input[i]);

   // �ɼ��ٶȼ���X��Y��Z�����ϵ��˶���
   // ע�⣺���˶����Ի�������ϵΪ�ο�
   X = Acc2Motion[0].Output(FilteredInput[0]);
   Y = Acc2Motion[0].Output(FilteredInput[1]);
   Z = Acc2Motion[0].Output(FilteredInput[2]);

   // ��ֱ���˶����任��������ȫ������ϵ
   // ��δ���

   // �ɽ��ٶȼ�����̬��
   Yaw   = RSpd2Rotate[0].Output(FilteredInput[3]);
   Pitch = RSpd2Rotate[1].Output(FilteredInput[4]);
   Roll  = RSpd2Rotate[2].Output(FilteredInput[5]);

   // ��Y��X�����ϵļ��ٶȼ��㸩���Ǻ͹�ת�ǣ�ͨ������ģ��������ٶ�
   Pitch += Acc2Angle[0].Output(__Input[1]);   // �����ǲ���Y������ٶ�
   Roll  += Acc2Angle[1].Output(__Input[0]);   // �����ǲ���X������ٶ�
}
