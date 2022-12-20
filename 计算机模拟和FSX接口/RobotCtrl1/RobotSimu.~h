//---------------------------------------------------------------------------

#ifndef RobotSimuH
#define RobotSimuH
#include "Robot.h"

#include <vector>
using namespace std;
//---------------------------------------------------------------------------
class CRobotSimu : public CRobot
{
public:
   double ChairBase[6][3];      // 座椅底座
   double ChairBasePos[6][3];
   double UpperJoints[6][3];
public:
   // 正向运动学计算，得到上平台位姿
   double  CalcPosition[3];          // 正向运动学解算得到的上平台质心位置
   double  CalcEurlar[3];            // 正向运动学解算得到的上平台姿态

public:
   CRobotSimu(void);
public:
   CMoveStatus Move(double X, double Y, double Z,
                    double Yaw, double Pitch, double Roll);
   bool  CalcUpperPlatform(double JackLength[6]);     // JackLength单位：m
};
#endif
