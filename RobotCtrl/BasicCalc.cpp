//---------------------------------------------------------------------------


#pragma hdrstop

#include "BasicCalc.h"
#include <math.h>
#ifndef M_PI
#define M_PI  3.1415926
#endif
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
void MatrixMultiMatrix(double Rst[3][3], double M1[3][3], double M2[3][3])
{
   Rst[0][0] = M1[0][0] * M2[0][0] + M1[0][1] * M2[1][0] + M1[0][2] * M2[2][0];
   Rst[0][1] = M1[0][0] * M2[0][1] + M1[0][1] * M2[1][1] + M1[0][2] * M2[2][1];
   Rst[0][2] = M1[0][0] * M2[0][2] + M1[0][1] * M2[1][2] + M1[0][2] * M2[2][2];

   Rst[1][0] = M1[1][0] * M2[0][0] + M1[1][1] * M2[1][0] + M1[1][2] * M2[2][0];
   Rst[1][1] = M1[1][0] * M2[0][1] + M1[1][1] * M2[1][1] + M1[1][2] * M2[2][1];
   Rst[1][2] = M1[1][0] * M2[0][2] + M1[1][1] * M2[1][2] + M1[1][2] * M2[2][2];

   Rst[2][0] = M1[2][0] * M2[0][0] + M1[2][1] * M2[1][0] + M1[2][2] * M2[2][0];
   Rst[2][1] = M1[2][0] * M2[0][1] + M1[2][1] * M2[1][1] + M1[2][2] * M2[2][1];
   Rst[2][2] = M1[2][0] * M2[0][2] + M1[2][1] * M2[1][2] + M1[2][2] * M2[2][2];
}
//---------------------------------------------------------------------------
void TransMatrix(double Rst[3][3], double Src[3][3])
{
   Rst[0][0] = Src[0][0];
   Rst[0][1] = Src[1][0];
   Rst[0][2] = Src[2][0];

   Rst[1][0] = Src[0][1];
   Rst[1][1] = Src[1][1];
   Rst[1][2] = Src[2][1];

   Rst[2][0] = Src[0][2];
   Rst[2][1] = Src[1][2];
   Rst[2][2] = Src[2][2];
}
//---------------------------------------------------------------------------
// MatrixMultiVector()
//---------------------------------------------------------------------------
void MatrixMultiVector(double Rst[3], double M[3][3], double V[3])
{
   Rst[0] = M[0][0] * V[0] + M[0][1] * V[1] + M[0][2] * V[2];
   Rst[1] = M[1][0] * V[0] + M[1][1] * V[1] + M[1][2] * V[2];
   Rst[2] = M[2][0] * V[0] + M[2][1] * V[1] + M[2][2] * V[2];
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
//---------------------------------------------------------------------------
// CalcCrossProduct()
//---------------------------------------------------------------------------
void CalcCrossProduct(double Rst[3], double V1[3], double V2[3])
{
   Rst[0] = V1[1] * V2[2] - V1[2] * V2[1];
   Rst[1] = V1[2] * V2[0] - V1[0] * V2[2];
   Rst[2] = V1[0] * V2[1] - V1[1] * V2[0];
}
//---------------------------------------------------------------------------
void VectorMultiScale(double Rst[3], double V[3], double Scale)
{
   Rst[0] = V[0] * Scale;
   Rst[1] = V[1] * Scale;
   Rst[2] = V[2] * Scale;
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
// CopyVector()
//---------------------------------------------------------------------------
void CopyVector(double Dst[3], double x, double y, double z)
{
   Dst[0] = x;
   Dst[1] = y;
   Dst[2] = z;
}
//---------------------------------------------------------------------------
// Normalize()
//---------------------------------------------------------------------------
void Normalize(double V[3])
{
   double L = sqrt(V[0] * V[0] + V[1] * V[1] + V[2] * V[2]);

   V[0] /= L;
   V[1] /= L;
   V[2] /= L;
}
//---------------------------------------------------------------------------
double VectorLength(double V[3])
{
   return sqrt(V[0] * V[0] + V[1] * V[1] + V[2] * V[2]);
}
//---------------------------------------------------------------------------
double Distance(double P1[3], double P2[3])
{
   double D1 = P1[0] - P2[0];
   double D2 = P1[1] - P2[1];
   double D3 = P1[2] - P2[2];

   return sqrt(D1 * D1 + D2 * D2 + D3 * D3);
}
//---------------------------------------------------------------------------
double Limit(double Value, double Range)
{
   if(Value > Range)
      return Range;
   else if(Value < -Range)
      return -Range;
   else
      return Value;
}
//---------------------------------------------------------------------------
double Limit(double Value, double Min, double Max)
{
   if(Value > Max)
      return Max;
   else if(Value < Min)
      return Min;
   else
      return Value;
}
//---------------------------------------------------------------------------
void RotateMatrixX(double M[3][3], double Angle)
{
   Angle *= M_PI / 180.0;

   double Sin = sin(Angle);
   double Cos = cos(Angle);

   M[0][0] = 1;
   M[0][1] = 0;
   M[0][2] = 0;

   M[1][0] = 0;
   M[1][1] = Cos;
   M[1][2] = -Sin;
   M[2][0] = 0;
   
   M[2][1] = Sin;
   M[2][2] = Cos;
}
//---------------------------------------------------------------------------
void RotateMatrixY(double M[3][3], double Angle)
{
   Angle *= M_PI / 180.0;

   double Sin = sin(Angle);
   double Cos = cos(Angle);

   M[0][0] = Cos;
   M[0][1] = 0;
   M[0][2] = Sin;

   M[1][0] = 0;
   M[1][1] = 1;
   M[1][2] = 0;

   M[2][0] = -Sin;
   M[2][1] = 0;
   M[2][2] = Cos;
}
//---------------------------------------------------------------------------
void RotateMatrixZ(double M[3][3], double Angle)
{
   Angle *= M_PI / 180.0;

   double Sin = sin(Angle);
   double Cos = cos(Angle);

   M[0][0] = Cos;
   M[0][1] = -Sin;
   M[0][2] = 0;

   M[1][0] = Sin;
   M[1][1] = Cos;
   M[1][2] = 0;
   
   M[2][0] = 0;
   M[2][1] = 0;
   M[2][2] = 1;
}
//---------------------------------------------------------------------------
void RotateMatrixByEuler(double M[3][3], double Euler[3])
{
   // 由度变换到弧度
   double Yaw   = Euler[0] * M_PI / 180.0;
   double Pitch = Euler[1] * M_PI / 180.0;
   double Roll  = Euler[2] * M_PI / 180.0;

   // 计算获得旋转阵
   double SinYaw   = sin(Yaw);
   double CosYaw   = cos(Yaw);
   double SinPitch = sin(Pitch);
   double CosPitch = cos(Pitch);
   double SinRoll  = sin(Roll);
   double CosRoll  = cos(Roll);

   M[0][0] =  CosYaw * CosRoll - SinYaw * SinPitch * SinRoll;
   M[0][1] = -SinYaw * CosPitch;
   M[0][2] =  CosYaw * SinRoll + SinYaw * SinPitch * CosRoll;

   M[1][0] =  SinYaw * CosRoll + CosYaw * SinPitch * SinRoll;
   M[1][1] =  CosYaw * CosPitch;
   M[1][2] =  SinYaw * SinRoll - CosYaw * SinPitch * CosRoll;

   M[2][0] =  -CosPitch * SinRoll;
   M[2][1] =  SinPitch;
   M[2][2] =  CosPitch * CosRoll;

   double MM[3][3];
   RotateMatrixY(MM, Euler[2]);
}
//---------------------------------------------------------------------------
void EulerByTriangle(double Euler[3], double Vx[3], double Vy[3])
{
   // 计算偏航角和俯仰角
   Euler[0] = -atan(Vy[0] / Vy[1]) * 180.0 / M_PI;
   Euler[1] = atan(Vy[2] / sqrt(Vy[0] * Vy[0] + Vy[1] * Vy[1])) * 180.0 / M_PI;

   // 计算滚转角
   double Vxx[3] = {Vy[1], -Vy[0], 0};   
   Euler[2] = acos((Vxx[0] * Vx[0] + Vxx[1] * Vx[1]) / (VectorLength(Vxx) * VectorLength(Vx)) ) * 180.0 / M_PI;

   if(Vx[2] > 0)
      Euler[2] = -Euler[2];
}
//----------------------------------------------------------------------------
void PosEulerByTriangle(double Pos[3], double Euler[3], double P1[3], double P2[3], double P3[3])
{
   // 计算中心点
   VectorAddVector(Pos,  P1,  P2);
   VectorAddVector(Pos,  Pos, P3);
   VectorMultiScale(Pos, Pos, 1.0 / 3.0);

   // 计算Y轴、X轴向量
   double Vx[3], Vy[3];
   VectorSubVector(Vx, P2, P3);
   VectorSubVector(Vy, P1, Pos);

   // 计算欧拉角
   EulerByTriangle(Euler, Vx, Vy);
}
