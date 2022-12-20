//---------------------------------------------------------------------------

#ifndef CalibratorH
#define CalibratorH
#include "SimplexOptimizer.h"
#include "Robot.h"
#include "Observer.h"
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
class CCalibrator : public CSimplexOptimizer
{
public:
   CRobot    Robot;             // 机器人
   CObserver Observer;          // 观测器
   double    Error[48];         // 所有的标定误差(每个胡克铰3个安装误差，
                                // 每个电缸的下限位开关1个误差，因此本体误差共3*12 + 6 = 42个。
                                // 再加观测误差6个。)
   bool      IgnoreJackErr;     // 忽略连杆误差
   bool      IgnoreLowerErr;    // 忽略下平台铰接点误差
   bool      IgnoreObserver;    // 忽略观察器误差
public:
   double    MinError;          // 最小误差(电缸平均长度误差)
public:
   double    DefaultRobotErr;       // 机器人误差缺省值(构造初始解使用)
   double    DefaultObserverTErr;   // 观测器平移误差缺省值
   double    DefaultObserverRErr;   // 观测器转动误差缺省值
public:
   double    MaxRobotErr;           // 最大机器人本体误差(避免标定计算得到的某些误差项太大)
   double    MaxObserverTErr;
   double    MaxObserverRErr;
   double    NormRate;
private:
   DP   CostFunction(const double *x);
   int  CopySolutionToRobot(const double *x, CRobot &Robot);
   int  CopySolutionToObserver(const double *x, CObserver &Observer);
public:
   // 实际观测结果
   struct CCaliData
   {
   public:
      // 上平台观测点坐标。观测点是3个顶点，构成等边三角形。
      double M1[3];
      double M2[3];
      double M3[3];
   public:
      // 电缸给定长度。电缸伸出量被认为不包含误差，但由于下限位开关存在误差，因此
      // 电缸的实际长度与给定长度之间存在误差。
      double Jack[6];
   public:
      double Pos[3];       // 注意：正常标定时不使用到位姿信息，位姿仅用于测试用
      double Euler[3];
   };
   vector<CCaliData>  CaliDatas;
public:
   CCalibrator(void);
public:
   void   Clear(void);
   void   ResetErrors(void);                                                       // 清除已有标定数据和结果
   void   AddCaliData(double M1[3], double M2[3], double M3[3], double Jack[6]);   // 添加标定数据(上平台测点坐标和电缸伸出量)
   void   AddCaliData(double Pos[3], double Euler[3], double Jack[6]);             // 添加标定数据(上平台位姿和电缸伸出量)
   bool   Calibrate(int MaxIterCnt);                                               // 标定
   void   CopyToRobot(CRobot &Robot);                                              // 将标定结果拷贝给机器人
   void   CopyToObserver(CObserver &Observer);                                     // 将标定结果拷贝给观测器
};
#endif
