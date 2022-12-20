//---------------------------------------------------------------------------

#ifndef MotionSimulatorH
#define MotionSimulatorH
#ifdef __BORLANDC__
#include <Classes.hpp>
#include <DateUtils.hpp>
#endif

#define   MOTION_RESUMED     true
//---------------------------------------------------------------------------
// Motion simulator用于将飞机6个姿态变量的加速度转换为并联机器人上平台位姿
//---------------------------------------------------------------------------
// 加速度到直线运动滤波器
//---------------------------------------------------------------------------
class CFilterAcc2Motion
{
private:
   double __Xh[3];    // 输出
   double __Amax;     // 最大加速度
   double __K1;       // 位置环反馈系数，K1 = amax / xmax，其中xmax是最大行程(单位m)
   double __K2;       // 速度环反馈系数，K2 = amax / vmax，其中vmax是最大速度(单位m/s)
   double __T;        // 采样时间
   double __Tsqr;     // 采样时间平方
   double __InputAcc; // 输入加速度
   double __RealAcc;  // 实际输出加速度
public:
   CFilterAcc2Motion(void);
public:
   void   SetParams(double T, double amax, double vmax, double xmax);
   double Output(double Acc);
   double XValue(void){return __Xh[0];}
   double RealAcc(void){return __RealAcc;}
   double InputAcc(void){return __InputAcc;}
};
//---------------------------------------------------------------------------
// 加速度到仰角滤波器
//---------------------------------------------------------------------------
class CFilterAcc2Angle
{
private:
   CFilterAcc2Motion __Filter;
   double __Angle;
public:
   void   SetParams(double T, double amax, double omega_max);
   double Output(double Acc);
   double RealAcc(void);
   double InputAcc(void);
};
//---------------------------------------------------------------------------
// 角速度到角度滤波器
//---------------------------------------------------------------------------
class CFilterRSpd2Angle
{
private:
   double __Xh[2];    // 输出行程
   double __Vmax;     // 最大速度
   double __K;        // 位置环反馈系数，K = vmax / xmax，其中xmax是最大行程(单位m)
   double __T;        // 采样时间
   double __InputV;   // 输入速度
   double __RealV;    // 实际输出速度
public:
   CFilterRSpd2Angle(void);
public:
   void   SetParams(double T, double vmax, double xmax);
   double Output(double V);
   double XValue(void){return __Xh[0];}
   double RealSpd(void){return __RealV;}
   double InputSpd(void){return __InputV;}
};
//---------------------------------------------------------------------------
class CLowPassFilter
{
private:
   double __X[2];
   double __Y[2];
   double __b;
   double __a0;
   double __a1;
   double __a2;
   double __T;
public:
   CLowPassFilter(void);
public:
   void   SetParams(double T, double FreqThresh, double Damping);
   double Filter(double x);
};
//---------------------------------------------------------------------------
class CHighPassFilter
{
private:
   CLowPassFilter __LowPass;
public:
   void   SetParams(double T, double FreqThresh, double Damping);
   double Filter(double x);
};
//---------------------------------------------------------------------------
// CMotionSimulator
//---------------------------------------------------------------------------
class CMotionSimulator
{
private:
   double            __Input[6];        // 输入加速度和角速度
#ifdef __BORLANDC__
   TDateTime         __LstSampleTime;
#endif
public:
   CFilterAcc2Motion Acc2Motion[3];         // 由加速度到位移
   CFilterRSpd2Angle RSpd2Rotate[3];        // 由角速度到角度
   CFilterAcc2Angle  Acc2Angle[2];          // 由加速度到角度(Y方向加速度、X方向加速度)
   CHighPassFilter   HighPassFilter[6];     // 加速度、角速度高通滤波器
   bool              HighPassEnabled[6];    // 使能高通滤波器
private:
   bool SampleOutputTime(void);
public:
   CMotionSimulator(void);
public:
   void FeedTargetAcc(double AccX, double AccY, double AccZ, double SpdYaw, double SpdPitch, double SpdRoll);
   void GetPlatformPosition(double &X, double &Y, double &Z, double &Yaw, double &Pitch, double &Roll);
};
#endif
 