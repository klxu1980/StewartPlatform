//---------------------------------------------------------------------------

#ifndef MotionSimuH
#define MotionSimuH
#include "PositionPred.h"

#ifdef __BORLANDC__
#include <Classes.hpp>
#endif
//---------------------------------------------------------------------------
// 二阶高通滤波器
//---------------------------------------------------------------------------
class CFilter2ndHighpass
{
private:
   double __Xh[3];    // 输出
   double __Xi[3];    // 输入
   double __K1;
   double __K2;
   double __T;
public:
   CFilter2ndHighpass(void);
public:
   void   SetParams(double amax, double vmax, double xmax);
   void   Initialize(double Xi);      // 初始化滤波器。将__Xi均初始化为Xi，将__Xh初始化为0，从而避免0时刻出现大幅输出。
   double Output(double Xi);
};
//---------------------------------------------------------------------------
// 二阶低通滤波器
//---------------------------------------------------------------------------
class CFilter2ndLowpass
{
private:
   double __Xh[3];    // 输出
   double __Xi[3];    // 输入
   double __K1;
   double __K2;
   double __T;
public:
   double Output(double Xi){return 0;}
};
//---------------------------------------------------------------------------
class CMotionSimulator
{
private:
   CPosPredict  __PosPredict;
   bool         __MotionStopped;    
private:
   CFilter2ndHighpass   __FilterHighpass[6];    // 6个高通滤波器，分别是X、Y、Z、Yaw、Pitch、Roll
   CFilter2ndLowpass    __FilterLowpass[2];     // 2个低通滤波器，分别是X、Y
public:
   void   NewPosition(double X, double Y, double Z,                     // 接收跟踪对象的最新位姿
                      double Yaw, double Pitch, double Roll);
   bool   CalcMotion(double &X, double &Y, double &Z,                 
                     double &Yaw, double &Pitch, double &Roll);
};
#endif
