//---------------------------------------------------------------------------

#ifndef RobotH
#define RobotH
#include <math.h>
#include "nr.h"
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
// 上下平台连杆铰接点编号定义：
//      连杆            1    2   3   4   5    6
//  上平台铰接点        1    2   3   4   5    6
//  下平台铰接点        4    5   6   1   2    3
//---------------------------------------------------------------------------
enum CMoveStatus
{
   msOk,
   msJackOutofRange,       // 连杆超出长度
   msSingular,             // 奇异点
   msJackCollision         // 连杆相碰
};

//==========================================================================
// CRobotIKP
// 机器人逆向运动学求解
//==========================================================================
class CRobot
{
protected:   // 机械尺寸参数
   double  __UpperArmLength;         // 上平台长臂长度
   double  __UpperBaseLength;        // 上平台短臂长度
   double  __LowerArmLength;         // 下平台长臂长度
   double  __LowerBaseLength;        // 下平台短臂长度
protected:
   double  __MinJackL;               // 连杆最小长度
   double  __MaxJackL;               // 连杆最大长度
   double  __JackDiameter;           // 连杆直径
protected:
   // 上平台位姿
   double  __UpperPos[3];            // 上平台原点坐标(X, Y, Z)，单位m
   double  __UpperEurlar[3];         // 上平台欧拉角(Yaw-Pitch-Roll, 即ψ-θ-φ)，单位°
   double  __UpperOrig[6][3];        // 上平台6个铰点在上平台坐标系下的坐标
protected:
   double  __JackLength[6];          // 给定连杆长度(正向运动学计算用)
public:
   // 直线连杆
   struct  CJack
   {
   public:
      double UpperJoint[3];          // 上虎克铰全局坐标系坐标
      double LowerJoint[3];          // 下虎克铰全局坐标系坐标
      double Length;                 // 连杆长度
      double ServoLength;            // 丝杠伸出长度
      double Force;                  // 连杆作用力
   };
   CJack Jacks[6];
protected:  // 向量和矩阵计算
   double Degree2Rad(double Degree){return Degree * M_PI / 180.0;}           // 角度换算为弧度
   void   MatrixMultiVector(double Rst[3], double M[3][3], double V[3]);     // 矩阵左乘向量
   void   VectorAddVector(double Rst[3], double V1[3], double V2[3]);        // 向量加
   void   VectorSubVector(double Rst[3], double V1[3], double V2[3]);        // 向量减
   void   CalcCrossProduct(double Rst[3], double V1[3], double V2[3]);       // 向量叉积
   void   Normalize(double Vector[3]);                                       // 向量归一化
   void   CopyVector(double Dst[3], double Src[3]);                          // 拷贝向量
   void   CopyVector(double Dst[3], double x, double y, double z);
protected:   // 逆向运动学计算
   void   UpperPlatformJointsCoordition(double Joints[6][3]);                       // 上平台铰接点在上平台坐标系中的坐标
   void   LowerPlatformJointsCoordition(double Joints[6][3]);                       // 下平台铰接点在下平台坐标系中的坐标
   void   CalcRotateMatrix(double Pys, double Theta, double Rho, double M[3][3]);   // 计算旋转阵
   void   CalcJackLength(double Pos[3], double Eurlar[3]);                          // 计算连杆长度(输入上平台位置和姿态)
   CMoveStatus Move(void);
private:
   bool   IsJackLengthFeasibility(void);          // 连杆长度是否在允许范围内
   bool   NoSingularityExists(void);              // 是否存在奇异点
private:
   bool   CalcJackBetweenLines(double A1[3], double A2[3],      // 计算两条直线(A1, A2定义第一条，B1, B2定义第二条)之间的法线(结果为A, B)
                               double B1[3], double B2[3],
                               double A[3],  double B[3]);
   bool   IsPointInSegment(double A1[3], double B1[3], double A[3]);            // 判断点是否在线段中
   bool   JackKnocked(double A1[3], double A2[3], double B1[3], double B2[3]);  // 判断两个连杆是否相碰
   bool   IsJackKnocked(void);                                                  // 判断是否有连杆相碰
protected:   // 正向运动学计算
   double ErrorFunc(double Pos[3], double Eurlar[3]);                           // 总误差函数
   DP     ErrorFunc(Vec_I_DP &UpperPlatform);                                   // 总误差函数
   double ErrorFunc(double UpperPlatform[6]);                                   // 总误差函数
   void   get_psum(Mat_I_DP &p, Vec_O_DP &psum);                                // 单纯形法，用于连续多维优化
   bool   amoeba(Mat_IO_DP &p, Fec_IO_DP &y, const DP ftol, int &nfunk);
   DP     amotry(Mat_IO_DP &p, Vec_O_DP &y, Vec_IO_DP &psum, const int ihi, const DP fac);
public:
   CRobot(void);
public:
   void   SetPlatformSize(double UpperArmLength,                   // 设置上下平台尺寸
                          double UpperBaseLength,
                          double LowerArmLength,
                          double LowerBaseLength);
   void   SetMinMaxJackLength(double MinL, double MaxL);           // 设置连杆长度上下限
   void   SetJackDiameter(double V);                               // 设置连杆半径
public:
   CMoveStatus Move(double Pos[3], double Eurlar[3]);              // 机器人运动
   CMoveStatus Move(double X, double Y, double Z,
                    double Yaw, double Pitch, double Roll);
   void Zeroed(void);                                              // 机器人归零
   void SetJackLength(int JackID, double ServoLength);          
public:
   double MinJackLength(void){return __MinJackL;}
   double MaxJackLength(void){return __MaxJackL;}
public:
   double PosX(void){return __UpperPos[0];}
   double PosY(void){return __UpperPos[1];}
   double PosZ(void){return __UpperPos[2];}
   double PosYaw(void)  {return __UpperEurlar[0];}
   double PosPitch(void){return __UpperEurlar[1];}
   double PosRoll(void) {return __UpperEurlar[2];}
public:
   // 计算上平台坐标系中点在下平台坐标系中的坐标
   void CalcGlobalCoordination(double X, double Y, double Z, double Yaw, double Pitch, double Roll,
                               double PosLocal[][3], double PosGlobal [][3], int Count);
   bool CalcUpperPlatformPosEurlar(double JackLength[6], double &X, double &Y, double &Z, double &Yaw, double &Pitch, double &Roll);
   bool UpdateUpperPlatformPosEurlar(void);
public:
   double CalcPlatformHeight(double JackLenght);   // 当6连杆长度一致时，计算上平台高度
   double PlatformMinHeight(void);                 // 上平台最低高度
   double PlatformMaxHeight(void);                 // 上平台最大高度
};
#endif
