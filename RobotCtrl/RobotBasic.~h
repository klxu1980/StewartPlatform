//---------------------------------------------------------------------------

#ifndef RobotBasicH
#define RobotBasicH
#include <math.h>
#include "BasicCalc.h"
//---------------------------------------------------------------------------
// 注意：在计算中，长度单位均为m，角度单位均为°
//---------------------------------------------------------------------------
// 注意：在计算过程中使用到了两个坐标系：下平台坐标系和上平台坐标系
// 下平台坐标系也称为全局坐标系或大地坐标系
// 下平台坐标系采用右手系，
// 定义X轴沿屏幕由左向右，Y轴垂直屏幕由内向外，Z轴沿屏幕由上向下
//
//    |-------------------------- X
//    | \
//    |  \
//    |   \
//    |    \
//    |     \
//    |Z     \ Y
//
// 上平台坐标系与下平台坐标系方向相同
//
//---------------------------------------------------------------------------
// 上下平台连杆铰接点编号定义：
//      连杆            1    2   3   4   5    6
//  上平台铰接点        1    2   3   4   5    6
//  下平台铰接点        4    5   6   1   2    3
//---------------------------------------------------------------------------
// 通过长短臂长设置机器人的机械尺寸
//                            X (铰接点)
//              ArmLength     |  BaseLength
//                            |  (注意：短臂长度指的是总基座尺寸的1/2)
//     -----------------------|
//                            |
//                            |
//                            X
class CRobotBasic
{
public:
   double  UpperJointInUpperCoordinate[6][3];  // 上平台铰接点在上平台坐标系中的坐标
   double  UpperJointInLowerCoordinate[6][3];  // 上平台铰接点在下平台坐标系中的坐标
   double  LowerJointInLowerCoordinate[6][3];  // 下平台铰接点在下平台坐标系中的坐标
public:
   double  UpperPos[3];                        // 上平台位置坐标(X, Y, Z)，单位m
   double  UpperEuler[3];                      // 上平台姿态欧拉角(Yaw-Pitch-Roll, 即ψ-θ-φ)，单位°
   double  JackLength[6];                      // 上下铰接点之间的连杆长度
private:
   static bool    __SinInited;          // 正弦、余弦函数表(快速计算用)
   static double  __SinValue[1801];
   static double  __CosValue[1801];
protected:    
   double  Sin(double Deg);
   double  Cos(double Deg);
protected:
   void CalcJackLength(double Length[6]);   // 计算连杆长度
   void RotateAroundZ(double Rst[3], double Src[3], double Angle);
public:
   CRobotBasic(void);
public:
   void SetStructureParams(double UpperArmLength,
                           double UpperBaseLength,
                           double LowerArmLength,
                           double LowerBaseLength,
                           double UpperJointHeight,
                           double LowerJointHeight);
   void SetStructureErrors(double  ErrJointUpper[6][3],      // 上平台每个铰接点的安装误差
                           double  ErrJointLower[6][3]);     // 下平台每个铰接点的安装误差
   void SetJointCoordinates(double UpperJonts[6][3], double LowerJonts[6][3]);
   void Copy(CRobotBasic &Robot);    // 拷贝上平台位姿、上铰接点坐标、连杆长度
};
#endif
