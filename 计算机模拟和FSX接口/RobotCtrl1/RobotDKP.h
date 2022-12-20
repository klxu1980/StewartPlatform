//---------------------------------------------------------------------------

#ifndef RobotDKPH
#define RobotDKPH
#include "Robot.h"
#include "nr.h"
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
class CRobotDKP : public CRobot
{
private:
   class CVec6
   {
   public:
      double V[6];
   public:
      double& operator () (int Idx){return V[Idx];}
      double  Distance2(CVec6 &Vec)
      {
         return (V[0] - Vec.V[0]) * (V[0] - Vec.V[0]) +
                (V[1] - Vec.V[1]) * (V[1] - Vec.V[1]) +
                (V[2] - Vec.V[2]) * (V[2] - Vec.V[2]) +
                (V[3] - Vec.V[3]) * (V[3] - Vec.V[3]) +
                (V[4] - Vec.V[4]) * (V[4] - Vec.V[4]) +
                (V[5] - Vec.V[5]) * (V[5] - Vec.V[5]);
      }
   };
   class CPostureJacks
   {
   public:
      double X;
      double Y;
      double Z;
      double Yaw;
      double Roll;
      double Pitch;
      double JackLength[6];
   public:
      double JackDifference(double Jack[6])
      {
         return (JackLength[0] - Jack[0]) * (JackLength[0] - Jack[0]) +
                (JackLength[1] - Jack[1]) * (JackLength[1] - Jack[1]) +
                (JackLength[2] - Jack[2]) * (JackLength[2] - Jack[2]) +
                (JackLength[3] - Jack[3]) * (JackLength[3] - Jack[3]) +
                (JackLength[4] - Jack[4]) * (JackLength[4] - Jack[4]) +
                (JackLength[5] - Jack[5]) * (JackLength[5] - Jack[5]);
      }
   };
   vector<CPostureJacks>  __PostJacks;
   double                 __LinearStep;
   double                 __RotaryStep;
private:
   void   EnumPostures(pair<double, double> XRange, pair<double, double> YRange, pair<double, double> ZRange,
                       pair<double, double> YawRange, pair<double, double> RollRange, pair<double, double> PitchRange);     
private:
   double ErrorFunc(double Pos[3], double Eurlar[3]);                           // 总误差函数
   DP     ErrorFunc(Vec_I_DP &UpperPlatform);                                   // 总误差函数
   double ErrorFunc(double UpperPlatform[6]);                                   // 总误差函数
   void   get_psum(Mat_I_DP &p, Vec_O_DP &psum);                                // 单纯形法，用于连续多维优化
   bool   amoeba(Mat_IO_DP &p, Vec_IO_DP &y, const DP ftol, int &nfunk);
   DP     amotry(Mat_IO_DP &p, Vec_O_DP &y, Vec_IO_DP &psum, const int ihi, const DP fac);
public:
   bool   CalcUpperPlatform(double JackLength[6]);                              // 计算上平台位姿(连杆长度单位mm)
   //void   CalcForceOfJacks(double Force[3], double Torque[3]);                  // 计算连杆受力
public:
   

   double L1Length(void);                                                    // 基于解析式计算L1连杆长度，暂时不使用
public:
};
#endif
