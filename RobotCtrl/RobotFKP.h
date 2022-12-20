//---------------------------------------------------------------------------

#ifndef RobotFKPH
#define RobotFKPH
#include "RobotIKP.h"

#ifdef __BORLANDC__
#include "SimplexOptimizer.h"
#endif
//---------------------------------------------------------------------------
class CRobotFKP : public CRobotIKP
{
public:
   double DefaultZ;         // 缺省的位置中心点
   int    IterCount;        // 迭代计算步数
protected:
   double ErrorFunc(double Pos[3], double Eurlar[3]);       // 总误差函数
   double ErrorFunc(const double UpperPlatform[6]);
protected:
#ifdef __BORLANDC__
   class CMyOptimizer : public CSimplexOptimizer
   {
   private:
      CRobotFKP &__Owner;
   private:
      double CostFunction(const double *x){return __Owner.ErrorFunc(x);}
   public:
      CMyOptimizer(CRobotFKP &Owner) : __Owner(Owner) {}
   };
   friend class CMyOptimizer;
   CMyOptimizer __Optimizer;
#endif
protected:
   bool CalcPosEurlar(bool DefaultInit = false);
public:
   CRobotFKP(void);
public:
   // 正向计算上平台位姿
   // DefaultInit = true： 使用运动中心点(即连杆均为一半行程时的位姿)作为初始解
   // DefaultInit = false：使用给定位姿(即UpperPos和UpperEurlar)作为初始解
   bool Move(double JackLength1, double JackLength2, double JackLength3,
             double JackLength4, double JackLength5, double JackLength6,
             bool DefaultInit = false);
};
#endif
