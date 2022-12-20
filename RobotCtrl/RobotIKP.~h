//---------------------------------------------------------------------------

#ifndef RobotIKPH
#define RobotIKPH
#include "RobotBasic.h"
//==========================================================================
// CRobotIKP
// 机器人逆向运动学求解
//==========================================================================
enum CMoveStatus
{
   msOk,
   msJackOutofRange,       // 连杆超出长度
   msSingular,             // 奇异点
   msJackCollision         // 连杆相碰
};

class CRobotIKP : public CRobotBasic
{
protected:   // 逆向运动学计算
   void CalcRotateMatrix(double Pys, double Theta, double Rho, double M[3][3]);   // 计算旋转阵
public:
   // 计算上平台坐标系中任意点在全局坐标系中的坐标
   void CalcGlobalCoordination(double Pos[3], double Euler[3],
                               double PosLocal[][3], double PosGlobal [][3], int Count);
   void CalcGlobalCoordination(double X, double Y, double Z, double Yaw, double Pitch, double Roll,
                               double PosLocal[][3], double PosGlobal [][3], int Count);
   void CalcGlobalCoordination(double PosLocal[][3], double PosGlobal [][3], int Count);
public:
   // 机器人运动
   // 由逆向运动学，计算出达到给定上平台位姿，每个连杆的实际长度
   void Move(double X, double Y, double Z, double Yaw, double Pitch, double Roll);
};
#endif
