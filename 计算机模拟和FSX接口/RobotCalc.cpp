//---------------------------------------------------------------------------


#pragma hdrstop

#include "RobotCalc.h"
#include <math.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
// 机器人机械参数
double  __Lt;                     // 上平台长臂长度
double  __lt;                     // 上平台短臂长度
double  __Lb;                     // 下平台长臂长度
double  __lb;                     // 下平台短臂长度
double  __MinLinkL;               // 连杆最小长度
double  __MaxLinkL;               // 连杆最大长度
double  __LinkDiameter;           // 连杆直径

double  __RMatrix[3][3];          // 上平台旋转矩阵
double  __UpperOrig[6][3];        // 上平台6个铰点在上平台坐标系下的坐标
double  __UpperEurlar[3];         // 上平台欧拉角(Yaw-Pitch-Roll, 即ψ-θ-φ)
double  UpperPlatform[6][3];      // 上平台各个铰接点的坐标(6行，3列)
double  LowerPlatform[6][3];      // 下平台各个铰接点的坐标

// 直线连杆
struct  CLink
{
   double UpperJoint[3];          // 上虎克铰全局坐标系坐标
   double LowerJoint[3];          // 下虎克铰全局坐标系坐标
   double Length;                 // 连杆长度
   double ServoLength;            // 丝杠伸出长度
   double Force;
};
CLink Links[6];

// 向量和矩阵计算
double Degree2Rad(double Degree){return Degree * M_PI / 180.0;}
void   MatrixMultiVector(double Rst[3], double M[3][3], double V[3]);
void   VectorAddVector(double Rst[3], double V1[3], double V2[3]);
void   VectorSubVector(double Rst[3], double V1[3], double V2[3]);
void   CalcCrossProduct(double Rst[3], double V1[3], double V2[3]);
void   Normalize(double Vector[3]);
void   CopyVector(double Dst[3], double Src[3]);
void   CopyVector(double Dst[3], double x, double y, double z);
void   CalcRotateMatrix(double Pys, double Theta, double Rho);    // 计算旋转阵

//---------------------------------------------------------------------------
// InitRobotCalculation()
//---------------------------------------------------------------------------
void InitRobotCalculation(void)
{  
   // 计算上下平台中每个铰接点在上下平台坐标系中的坐标
   double SinA = sin(2 * M_PI / 3);
   double CosA = cos(2 * M_PI / 3);

   // 上平台坐标
   CopyVector(__UpperOrig[0], __Lt,                       __lt,                      0);
   CopyVector(__UpperOrig[1], __Lt * CosA + __lt * SinA,  __Lt * SinA - __lt * CosA, 0);
   CopyVector(__UpperOrig[2], __Lt * CosA - __lt * SinA,  __Lt * SinA + __lt * CosA, 0);
   CopyVector(__UpperOrig[3], __Lt * CosA - __lt * SinA, -__Lt * SinA - __lt * CosA, 0);
   CopyVector(__UpperOrig[4], __Lt * CosA + __lt * SinA, -__Lt * SinA + __lt * CosA, 0);
   CopyVector(__UpperOrig[5], __Lt,                      -__lt,                      0);


   // 下平台坐标
   CopyVector(LowerPlatform[0], -__Lb,                      -__lb,                      0);
   CopyVector(LowerPlatform[1], -__Lb * CosA - __lb * SinA, -__Lb * SinA + __lb * CosA, 0);
   CopyVector(LowerPlatform[2], -__Lb * CosA + __lb * SinA, -__Lb * SinA - __lb * CosA, 0);
   CopyVector(LowerPlatform[3], -__Lb * CosA + __lb * SinA,  __Lb * SinA + __lb * CosA, 0);
   CopyVector(LowerPlatform[4], -__Lb * CosA - __lb * SinA,  __Lb * SinA - __lb * CosA, 0);
   CopyVector(LowerPlatform[5], -__Lb,                       __lb,                      0);
}
//---------------------------------------------------------------------------
// CalcRobot()
// 根据上平台位姿，计算连杆长度
//---------------------------------------------------------------------------
void CalcRobot(double Pos[3], double Eurlar[3])
{
   // 更新计算旋转矩阵，旋转矩阵为__RMatrix
   CalcRotateMatrix(Eurlar[0], Eurlar[1], Eurlar[2]);

   // 旋转矩阵左乘铰点初始坐标，得到上平台旋转后铰接点的坐标
   MatrixMultiVector(UpperPlatform[0], __RMatrix, __UpperOrig[0]);
   MatrixMultiVector(UpperPlatform[1], __RMatrix, __UpperOrig[1]);
   MatrixMultiVector(UpperPlatform[2], __RMatrix, __UpperOrig[2]);
   MatrixMultiVector(UpperPlatform[3], __RMatrix, __UpperOrig[3]);
   MatrixMultiVector(UpperPlatform[4], __RMatrix, __UpperOrig[4]);
   MatrixMultiVector(UpperPlatform[5], __RMatrix, __UpperOrig[5]);

   // 上平台平移后铰接点的坐标
   VectorAddVector(UpperPlatform[0], UpperPlatform[0], Pos);
   VectorAddVector(UpperPlatform[1], UpperPlatform[1], Pos);
   VectorAddVector(UpperPlatform[2], UpperPlatform[2], Pos);
   VectorAddVector(UpperPlatform[3], UpperPlatform[3], Pos);
   VectorAddVector(UpperPlatform[4], UpperPlatform[4], Pos);
   VectorAddVector(UpperPlatform[5], UpperPlatform[5], Pos);

   // 连杆坐标
   CopyVector(Links[0].UpperJoint, UpperPlatform[0]);
   CopyVector(Links[1].UpperJoint, UpperPlatform[1]);
   CopyVector(Links[2].UpperJoint, UpperPlatform[2]);
   CopyVector(Links[3].UpperJoint, UpperPlatform[3]);
   CopyVector(Links[4].UpperJoint, UpperPlatform[4]);
   CopyVector(Links[5].UpperJoint, UpperPlatform[5]);

   CopyVector(Links[0].LowerJoint, LowerPlatform[3]);
   CopyVector(Links[1].LowerJoint, LowerPlatform[4]);
   CopyVector(Links[2].LowerJoint, LowerPlatform[5]);
   CopyVector(Links[3].LowerJoint, LowerPlatform[0]);
   CopyVector(Links[4].LowerJoint, LowerPlatform[1]);
   CopyVector(Links[5].LowerJoint, LowerPlatform[2]);

   // 计算连杆长度
   for(int i = 0; i < 6; ++i)
   {
      Links[i].Length = (Links[i].UpperJoint[0] - Links[i].LowerJoint[0]) * (Links[i].UpperJoint[0] - Links[i].LowerJoint[0]) +
                        (Links[i].UpperJoint[1] - Links[i].LowerJoint[1]) * (Links[i].UpperJoint[1] - Links[i].LowerJoint[1]) +
                        (Links[i].UpperJoint[2] - Links[i].LowerJoint[2]) * (Links[i].UpperJoint[2] - Links[i].LowerJoint[2]);
      Links[i].Length = sqrt(Links[i].Length);
      Links[i].ServoLength = Links[i].Length - __MinLinkL;
   }
}

//---------------------------------------------------------------------------
// CalcRotateMatrix()
// 计算旋转矩阵，输入角度分别为：偏航角、俯仰角、滚转角
//---------------------------------------------------------------------------
void CalcRotateMatrix(double Pys, double Theta, double Rho)
{
   Pys   = Degree2Rad(Pys);
   Theta = Degree2Rad(Theta);
   Rho   = Degree2Rad(Rho);

   double SinTheta = sin(Theta);
   double CosTheta = cos(Theta);
   double SinPys   = sin(Pys);
   double CosPys   = cos(Pys);
   double SinRho   = sin(Rho);
   double CosRho   = cos(Rho);

   __RMatrix[0][0] =  CosTheta*CosPys;
   __RMatrix[1][0] = -CosTheta*SinPys;
   __RMatrix[2][0] =  SinTheta;

   __RMatrix[0][1] =  SinTheta*SinRho*CosPys+CosRho*SinPys;
   __RMatrix[1][1] = -SinTheta*SinRho*SinPys+CosRho*CosPys;
   __RMatrix[2][1] = -SinRho*CosTheta;

   __RMatrix[0][2] = -SinTheta*CosRho*CosPys+SinRho*SinPys;
   __RMatrix[1][2] =  SinTheta*CosRho*SinPys+SinRho*CosPys;
   __RMatrix[2][2] =  CosTheta*CosRho;
}
//---------------------------------------------------------------------------
// CopyVector()
//---------------------------------------------------------------------------
void CopyVector(double Dst[3], double Src[3])
{
   Dst[0] = Src[0];
   Dst[1] = Src[1];
   Dst[2] = Src[2];
}
//---------------------------------------------------------------------------
void CopyVector(double Dst[3], double x, double y, double z)
{
   Dst[0] = x;
   Dst[1] = y;
   Dst[2] = z;
}
//---------------------------------------------------------------------------
// MatrixMultiVector()
//---------------------------------------------------------------------------
void MatrixMultiVector(double Rst[3], double M[3][3], double V[3])
{
   Rst[0] = __RMatrix[0][0] * V[0] + __RMatrix[1][0] * V[1] + __RMatrix[2][0] * V[2];
   Rst[1] = __RMatrix[0][1] * V[0] + __RMatrix[1][1] * V[1] + __RMatrix[2][1] * V[2];
   Rst[2] = __RMatrix[0][2] * V[0] + __RMatrix[1][2] * V[1] + __RMatrix[2][2] * V[2];
}
//---------------------------------------------------------------------------
// VectorAddVector()
//---------------------------------------------------------------------------
void VectorAddVector(double Rst[3], double V1[3], double V2[3])
{
   Rst[0] = V1[0] + V2[0];
   Rst[1] = V1[1] + V2[1];
   Rst[2] = V1[2] + V2[2];
}
//---------------------------------------------------------------------------
// VectorSubVector()
//---------------------------------------------------------------------------
void VectorSubVector(double Rst[3], double V1[3], double V2[3])
{
   Rst[0] = V1[0] - V2[0];
   Rst[1] = V1[1] - V2[1];
   Rst[2] = V1[2] - V2[2];
}
