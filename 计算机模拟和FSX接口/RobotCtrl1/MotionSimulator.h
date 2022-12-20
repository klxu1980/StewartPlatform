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
// 二阶高通滤波器
//---------------------------------------------------------------------------
class CFilter2ndHighPass
{
private:
   int    __XiCnt;    // 输入数量
   double __Xi[3];    // 输入
   double __Xh[3];    // 输出
   double __K1;
   double __K2;
   double __T;
public:
   CFilter2ndHighPass(void);
public:
   void   SetParams(double amax, double vmax, double xmax);
   void   Initialize(double Xi);      // 初始化滤波器。将__Xi均初始化为Xi，将__Xh初始化为0，从而避免0时刻出现大幅输出。
   double Output(double Xi);
};
//---------------------------------------------------------------------------
// 加速度到运动滤波器
// 二阶低通滤波器
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
   double RealAcc(void){return __RealAcc;}
   double InputAcc(void){return __InputAcc;}
};
//---------------------------------------------------------------------------
// CMotionSimulator
//---------------------------------------------------------------------------
class CMotionSimulator
{
private:
   double            __Acc[6];
   CFilterAcc2Motion __AccFilter[6];    // 加速度滤波器
#ifdef __BORLANDC__
   TDateTime         __LstSampleTime;
#endif
private:
   bool SampleOutputTime(void);
public:
   CMotionSimulator(void);
public:
   CFilterAcc2Motion& Filter(int ID)   {return __AccFilter[ID];}
   CFilterAcc2Motion& FilterX(void)    {return __AccFilter[0];}
   CFilterAcc2Motion& FilterY(void)    {return __AccFilter[1];}
   CFilterAcc2Motion& FilterZ(void)    {return __AccFilter[2];}
   CFilterAcc2Motion& FilterYaw(void)  {return __AccFilter[3];}
   CFilterAcc2Motion& FilterPitch(void){return __AccFilter[4];}
   CFilterAcc2Motion& FilterRoll(void) {return __AccFilter[5];}
public:
   void FeedTargetAcc(double AccX, double AccY, double AccZ, double AccYaw, double AccPitch, double AccRoll);
   void GetPlatformPosition(double &X, double &Y, double &Z, double &Yaw, double &Pitch, double &Roll);
};
#endif
 