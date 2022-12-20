//---------------------------------------------------------------------------

#ifndef PositionPredH
#define PositionPredH
#ifdef __BORLANDC__
#include <Classes.hpp>
#endif

#define   MOTION_RESUMED     true
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
// CMotionSimulator
//---------------------------------------------------------------------------
class CMotionSimulator
{
private:
   int    __SampleCnt;
   int    __MaxSampleCnt;
   double __X[64];
   double __Y[6][64];
   bool   __Resetting;
   bool   __Resetted;
private:
   CFilter2ndHighPass __FilterHighPass[6];
private:
#ifdef __BORLANDC__
   TDateTime    __StartTime;
#endif
private:
   double GetCurTime(void);
   double CalcSampleAcc(double Y2, double Y1, double Y0, double DT21, double DT10){return (Y2 - Y1) / (DT21 * DT21) - (Y1 - Y0) / (DT10 * DT21);}
   void   PopOldSample(double *Array);
   void   Fit(double *X, double *Y, double &A, double &B);
public:
   double A[6];       // 拟合后的直线方程，y = Ax + B
   double B[6];
public:
   CMotionSimulator(int SampleCnt);
public:
   void Reset(void);
   void FeedTargetPosition(double X, double Y, double Z, double Yaw, double Pitch, double Roll);
   void GetPlatformPosition(double &X, double &Y, double &Z, double &Yaw, double &Pitch, double &Roll);
};
#endif
 