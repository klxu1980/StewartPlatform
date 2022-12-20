//---------------------------------------------------------------------------


#pragma hdrstop

#include "Robot.h"
using namespace std;
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CRobot::CRobot(void)
{
}
//---------------------------------------------------------------------------
// SetPlatformSize()
//---------------------------------------------------------------------------
void CRobot::SetPlatformSize(double UpperArmLength, double UpperBaseLength, double LowerArmLength, double LowerBaseLength)
{
   __UpperArmLength  = UpperArmLength;
   __UpperBaseLength = UpperBaseLength;
   __LowerArmLength  = LowerArmLength;
   __LowerBaseLength = LowerBaseLength;

   // 计算上下平台中每个铰接点在上下平台坐标系中的坐标
   double SinA = sin(2 * M_PI / 3);
   double CosA = cos(2 * M_PI / 3);

   // 上平台坐标
   CopyVector(__UpperOrig[0],
              __UpperArmLength,
              __UpperBaseLength,
              0);
   CopyVector(__UpperOrig[1],
              __UpperArmLength * CosA + __UpperBaseLength * SinA,
              __UpperArmLength * SinA - __UpperBaseLength * CosA,
              0);
   CopyVector(__UpperOrig[2],
              __UpperArmLength * CosA - __UpperBaseLength * SinA,
              __UpperArmLength * SinA + __UpperBaseLength * CosA,
              0);
   CopyVector(__UpperOrig[3],
              __UpperArmLength * CosA - __UpperBaseLength * SinA,
              -__UpperArmLength * SinA - __UpperBaseLength * CosA,
              0);
   CopyVector(__UpperOrig[4],
              __UpperArmLength * CosA + __UpperBaseLength * SinA,
              -__UpperArmLength * SinA + __UpperBaseLength * CosA,
              0);
   CopyVector(__UpperOrig[5],
              __UpperArmLength,
              -__UpperBaseLength,
              0);


   // 下平台坐标
   CopyVector(LowerPlatform[0],
              -__LowerArmLength,
              -__LowerBaseLength,
              0);
   CopyVector(LowerPlatform[1],
              -__LowerArmLength * CosA - __LowerBaseLength * SinA,
              -__LowerArmLength * SinA + __LowerBaseLength * CosA,
              0);
   CopyVector(LowerPlatform[2],
              -__LowerArmLength * CosA + __LowerBaseLength * SinA,
              -__LowerArmLength * SinA - __LowerBaseLength * CosA,
              0);
   CopyVector(LowerPlatform[3],
              -__LowerArmLength * CosA + __LowerBaseLength * SinA,
              __LowerArmLength * SinA + __LowerBaseLength * CosA,
              0);
   CopyVector(LowerPlatform[4],
              -__LowerArmLength * CosA - __LowerBaseLength * SinA,
              __LowerArmLength * SinA - __LowerBaseLength * CosA,
              0);
   CopyVector(LowerPlatform[5],
              -__LowerArmLength,
              __LowerBaseLength,
              0);
}
//---------------------------------------------------------------------------
// SetMinMaxJackLength()
//---------------------------------------------------------------------------
void CRobot::SetMinMaxJackLength(double MinL, double MaxL)
{
   __MinJackL = MinL;
   __MaxJackL = MaxL;
}
//---------------------------------------------------------------------------
// SetJackDiameter()
//---------------------------------------------------------------------------
void CRobot::SetJackDiameter(double V)
{
   __JackDiameter = V;
}
//---------------------------------------------------------------------------
// CalcRotateMatrix()
//---------------------------------------------------------------------------
void CRobot::CalcRotateMatrix(double Pys, double Theta, double Rho)
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

   __RMatrix[0][0] =  CosTheta * CosPys;
   __RMatrix[1][0] = -CosTheta * SinPys;
   __RMatrix[2][0] =  SinTheta;

   __RMatrix[0][1] =  SinTheta * SinRho * CosPys + CosRho * SinPys;
   __RMatrix[1][1] = -SinTheta * SinRho * SinPys + CosRho * CosPys;
   __RMatrix[2][1] = -SinRho * CosTheta;

   __RMatrix[0][2] = -SinTheta * CosRho * CosPys + SinRho * SinPys;
   __RMatrix[1][2] =  SinTheta * CosRho * SinPys + SinRho * CosPys;
   __RMatrix[2][2] =  CosTheta * CosRho;
}
//---------------------------------------------------------------------------
// MatrixMultiVector()
//---------------------------------------------------------------------------
void CRobot::MatrixMultiVector(double Rst[3], double M[3][3], double V[3])
{
   Rst[0] = __RMatrix[0][0] * V[0] + __RMatrix[1][0] * V[1] + __RMatrix[2][0] * V[2];
   Rst[1] = __RMatrix[0][1] * V[0] + __RMatrix[1][1] * V[1] + __RMatrix[2][1] * V[2];
   Rst[2] = __RMatrix[0][2] * V[0] + __RMatrix[1][2] * V[1] + __RMatrix[2][2] * V[2];
}
//---------------------------------------------------------------------------
// VectorAddVector()
//---------------------------------------------------------------------------
void CRobot::VectorAddVector(double Rst[3], double V1[3], double V2[3])
{
   Rst[0] = V1[0] + V2[0];
   Rst[1] = V1[1] + V2[1];
   Rst[2] = V1[2] + V2[2];
}
//---------------------------------------------------------------------------
// VectorSubVector()
//---------------------------------------------------------------------------
void CRobot::VectorSubVector(double Rst[3], double V1[3], double V2[3])
{
   Rst[0] = V1[0] - V2[0];
   Rst[1] = V1[1] - V2[1];
   Rst[2] = V1[2] - V2[2];
}
//---------------------------------------------------------------------------
// CalcJackLength()
//---------------------------------------------------------------------------
void CRobot::CalcJackLength(double Pos[3], double Eurlar[3])
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
   CopyVector(Jacks[0].UpperJoint, UpperPlatform[0]);
   CopyVector(Jacks[1].UpperJoint, UpperPlatform[1]);
   CopyVector(Jacks[2].UpperJoint, UpperPlatform[2]);
   CopyVector(Jacks[3].UpperJoint, UpperPlatform[3]);
   CopyVector(Jacks[4].UpperJoint, UpperPlatform[4]);
   CopyVector(Jacks[5].UpperJoint, UpperPlatform[5]);

   CopyVector(Jacks[0].LowerJoint, LowerPlatform[3]);
   CopyVector(Jacks[1].LowerJoint, LowerPlatform[4]);
   CopyVector(Jacks[2].LowerJoint, LowerPlatform[5]);
   CopyVector(Jacks[3].LowerJoint, LowerPlatform[0]);
   CopyVector(Jacks[4].LowerJoint, LowerPlatform[1]);
   CopyVector(Jacks[5].LowerJoint, LowerPlatform[2]);

   // 计算连杆长度
   for(int i = 0; i < 6; ++i)
   {
      Jacks[i].Length = (Jacks[i].UpperJoint[0] - Jacks[i].LowerJoint[0]) * (Jacks[i].UpperJoint[0] - Jacks[i].LowerJoint[0]) +
                        (Jacks[i].UpperJoint[1] - Jacks[i].LowerJoint[1]) * (Jacks[i].UpperJoint[1] - Jacks[i].LowerJoint[1]) +
                        (Jacks[i].UpperJoint[2] - Jacks[i].LowerJoint[2]) * (Jacks[i].UpperJoint[2] - Jacks[i].LowerJoint[2]);
      Jacks[i].Length = sqrt(Jacks[i].Length);
      Jacks[i].ServoLength = Jacks[i].Length - __MinJackL;
   }
}
//---------------------------------------------------------------------------
// IsJackLengthFeasibility()
//---------------------------------------------------------------------------
bool CRobot::IsJackLengthFeasibility(void)
{
   // 检查连杆长度是否正确，即连杆长度应当在最小和最大范围之间
   for(int i = 0; i < 6; ++i)
      if(Jacks[i].Length < __MinJackL - 0.1 || Jacks[i].Length > __MaxJackL + 0.001)
         return false; 
   return true;
}
//---------------------------------------------------------------------------
// NoSingularityExists()
//---------------------------------------------------------------------------
bool CRobot::NoSingularityExists(void)
{
   // 计算上平面法向量
   double ZVector[3] = {0, 0, 1};
   double NVector[3] = {
                           __RMatrix[0][0] * ZVector[0] + __RMatrix[1][0] * ZVector[1] + __RMatrix[2][0] * ZVector[2],
                           __RMatrix[0][1] * ZVector[0] + __RMatrix[1][1] * ZVector[1] + __RMatrix[2][1] * ZVector[2],
                           __RMatrix[0][2] * ZVector[0] + __RMatrix[1][2] * ZVector[1] + __RMatrix[2][2] * ZVector[2]
                       };

   // 计算法向量与每个连杆之间夹角余弦值
   // 如果余弦值小于一定阈值，则认为进入奇异点
   for(int i = 0; i < 6; ++i)
   {
      /*
      double lx = Jacks[i * 2][0] - Jacks[i * 2 + 1][0];
      double ly = Jacks[i * 2][1] - Jacks[i * 2 + 1][1];
      double lz = Jacks[i * 2][2] - Jacks[i * 2 + 1][2];
      */

      double lx = Jacks[i].UpperJoint[0] - Jacks[i].LowerJoint[0];
      double ly = Jacks[i].UpperJoint[1] - Jacks[i].LowerJoint[1];
      double lz = Jacks[i].UpperJoint[2] - Jacks[i].LowerJoint[2];

      double V    = NVector[0] * (lx) + NVector[1] * (ly) + NVector[2] * (lz);
      double CosA = V * V / (lx * lx + ly * ly + lz * lz);

      if(CosA < 0.01)
         return false;
   }

   return true;
}
//---------------------------------------------------------------------------
// CalcCrossProduct()
//---------------------------------------------------------------------------
void CRobot::CalcCrossProduct(double Rst[3], double V1[3], double V2[3])
{
   Rst[0] = V1[1] * V2[2] - V1[2] * V2[1];
   Rst[1] = V1[2] * V2[0] - V1[0] * V2[2];
   Rst[2] = V1[0] * V2[1] - V1[1] * V2[0];
}
//---------------------------------------------------------------------------
// CalcJackBetweenLines()
//---------------------------------------------------------------------------
bool CRobot::CalcJackBetweenLines(double A1[3], double A2[3], double B1[3], double B2[3], double A[3], double B[3])
{
   double VA[3] = {A1[0] - A2[0], A1[1] - A2[1], A1[2] - A2[2]};
   double VB[3] = {B1[0] - B2[0], B1[1] - B2[1], B1[2] - B2[2]};

   // 计算直线A与B向量之间的叉积
   double ABProd[3];
   CalcCrossProduct(ABProd, VA, VB);

   // 判断两直线是否平行
   if(ABProd[0] * ABProd[0] + ABProd[1] * ABProd[1] + ABProd[2] * ABProd[2] < 0.0001)
      return false;

   // 计算经过直线A的垂面法向量
   double SurfaceA[3];
   CalcCrossProduct(SurfaceA, ABProd, VA);

   // 计算直线B与该平面的交点
   double T;
   T  = (A1[0] - B1[0]) * SurfaceA[0] + (A1[1] - B1[1]) * SurfaceA[1] + (A1[2] - B1[2]) * SurfaceA[2];
   T /= SurfaceA[0] * VB[0] + SurfaceA[1] * VB[1] + SurfaceA[2] * VB[2];

   B[0] = VB[0] * T + B1[0];
   B[1] = VB[1] * T + B1[1];
   B[2] = VB[2] * T + B1[2];

   // 计算经过直线B的垂面法向量
   double SurfaceB[3];
   CalcCrossProduct(SurfaceB, ABProd, VB);

   // 计算直线A与该平面的交点
   T  = (B1[0] - A1[0]) * SurfaceB[0] + (B1[1] - A1[1]) * SurfaceB[1] + (B1[2] - A1[2]) * SurfaceB[2];
   T /= SurfaceB[0] * VA[0] + SurfaceB[1] * VA[1] + SurfaceB[2] * VA[2];

   A[0] = VA[0] * T + A1[0];
   A[1] = VA[1] * T + A1[1];
   A[2] = VA[2] * T + A1[2];

   return true;
}
//---------------------------------------------------------------------------
// JackKnocked()
//---------------------------------------------------------------------------
bool CRobot::JackKnocked(double A1[3], double A2[3], double B1[3], double B2[3])
{
   double A[3], B[3];
   CalcJackBetweenLines(A1, A2, B1, B2, A, B);

   double Gap = sqrt( (A[0] - B[0]) * (A[0] - B[0]) + (A[1] - B[1]) * (A[1] - B[1]) + (A[2] - B[2]) * (A[2] - B[2]) );
   if(Gap < __JackDiameter && IsPointInSegment(A1, A2, A) && IsPointInSegment(B1, B2, B) )
      return true;

   return false;
}
//---------------------------------------------------------------------------
bool CRobot::IsPointInSegment(double A1[3], double B1[3], double A[3])
{
   double L1 = sqrt( (A1[0] - A[0]) * (A1[0] - A[0]) + (A1[1] - A[1]) * (A1[1] - A[1]) + (A1[2] - A[2]) * (A1[2] - A[2]) );
   double L2 = sqrt( (B1[0] - A[0]) * (B1[0] - A[0]) + (B1[1] - A[1]) * (B1[1] - A[1]) + (B1[2] - A[2]) * (B1[2] - A[2]) );
   double L  = sqrt( (A1[0] - B1[0]) * (A1[0] - B1[0]) + (A1[1] - B1[1]) * (A1[1] - B1[1]) + (A1[2] - B1[2]) * (A1[2] - B1[2]) );

   return L1 + L2 < L * 1.02;
}
//---------------------------------------------------------------------------
bool CRobot::IsJackKnocked(void)
{
   for(int i = 0; i < 6; ++i)
      for(int m = i + 1; m < 6; ++m)
         if(JackKnocked(Jacks[i].UpperJoint, Jacks[i].LowerJoint, Jacks[m].UpperJoint, Jacks[m].LowerJoint) )
            return true;
            
   return false;
}
//---------------------------------------------------------------------------
void CRobot::CopyVector(double Dst[3], double Src[3])
{
   Dst[0] = Src[0];
   Dst[1] = Src[1];
   Dst[2] = Src[2];
}
//---------------------------------------------------------------------------
void CRobot::CopyVector(double Dst[3], double x, double y, double z)
{
   Dst[0] = x;
   Dst[1] = y;
   Dst[2] = z;
}
//---------------------------------------------------------------------------
/*
void CRobot::CalcForceOfJacks(double Force[3], double Torque[3])
{
   // 计算每个连杆作用力的方向矢量，方向为下平台指向上平台(即，默认情况下连杆承受压力)
   double FV[6][3];
   for(int i = 0; i < 6; ++i)
   {
      FV[i][0] = Jacks[i].UpperJoint[0] - Jacks[i].LowerJoint[0];
      FV[i][1] = Jacks[i].UpperJoint[1] - Jacks[i].LowerJoint[1];
      FV[i][2] = Jacks[i].UpperJoint[2] - Jacks[i].LowerJoint[2];

      Normalize(FV[i]);
   }

   // 计算质心位置
   double MidPos[3];
   MatrixMultiVector(MidPos, __RMatrix, __Middle);
   VectorAddVector(MidPos, MidPos, __UpperPos);

   // 计算力臂矢量，该矢量应当由铰接点指向质心
   double Arm[6][3];
   for(int i = 0; i < 6; ++i)
      VectorSubVector(Arm[i], UpperPlatform[i], MidPos);

   // 计算力矩矢量，即连杆作用力方向矢量与力臂矢量之间的叉积
   double TV[6][3];
   for(int i = 0; i < 6; ++i)
      CalcCrossProduct(TV[i], FV[i], Arm[i]);

   // 通过求解线性方程获得每个连杆的力
   // 线性方程组的形式如下：
   // F[0]FV[0] + F[1]FV[1] + ... + F[5]FV[5] = Force     (连杆力的合力等于上平台所受力)
   // F[0]TV[0] + F[1]TV[1] + ... + F[5]TV[5] = Torque    (连杆力矩的合力矩等于上平台所受力矩)
   Mat_DP M(6, 6);
   for(int i = 0; i < 6; ++i)
   {
      M[0][i] = FV[i][0];
      M[1][i] = FV[i][1];
      M[2][i] = FV[i][2];

      M[3][i] = TV[i][0];
      M[4][i] = TV[i][1];
      M[5][i] = TV[i][2];
   }

   // 外部力和力矩
   Mat_DP F(6, 1);
   F[0][0] = Force[0];
   F[1][0] = Force[1];
   F[2][0] = Force[2];

   F[3][0] = Torque[0];
   F[4][0] = Torque[1];
   F[5][0] = Torque[2];

   // 通过高斯消元法求解连杆力
   NR::gaussj(M, F);
   for(int i = 0; i < 6; ++i)
      Jacks[i].Force = F[i][0];
}
*/
//---------------------------------------------------------------------------
void CRobot::Normalize(double V[3])
{
   double L = sqrt(V[0] * V[0] + V[1] * V[1] + V[2] * V[2]);

   V[0] /= L;
   V[1] /= L;
   V[2] /= L;
}
//---------------------------------------------------------------------------
// Move()
//---------------------------------------------------------------------------
CMoveStatus CRobot::Move(double Pos[3], double Eurlar[3])
{
   CopyVector(__UpperPos,    Pos);
   CopyVector(__UpperEurlar, Eurlar);

   // 计算上平台位姿
   CalcJackLength(Pos, Eurlar);

   // 检查运动是否可行
   if(!IsJackLengthFeasibility())
      return msJackOutofRange;
   else if(!NoSingularityExists() )
      return msSingular;
   else if(IsJackKnocked() )
      return msJackCollision;
   else
      return msOk;
} 
CMoveStatus CRobot::Move(double X, double Y, double Z, double Yaw, double Pitch, double Roll)
{
   CopyVector(__UpperPos,    X, Y, Z);
   CopyVector(__UpperEurlar, Yaw, Pitch, Roll);

   // 计算上平台位姿
   CalcJackLength(__UpperPos, __UpperEurlar);

   // 检查运动是否可行
   if(!IsJackLengthFeasibility())
      return msJackOutofRange;
   else if(!NoSingularityExists() )
      return msSingular;
   else if(IsJackKnocked() )
      return msJackCollision;
   else
      return msOk;
}
//---------------------------------------------------------------------------
// CalcPlatformHeight()
//---------------------------------------------------------------------------
double CRobot::CalcPlatformHeight(double JackLength)
{
   double L  = sqrt(__LowerArmLength * __LowerArmLength + __LowerBaseLength * __LowerBaseLength) * sin(M_PI / 3.0 - atan(__LowerBaseLength / __LowerArmLength));
   double h  = sqrt(JackLength * JackLength - pow(L - __UpperBaseLength, 2.0));
   double Lb = sqrt(__LowerArmLength * __LowerArmLength + __LowerBaseLength * __LowerBaseLength) * cos(M_PI / 3.0 - atan(__LowerBaseLength / __LowerArmLength));
   double H  = sqrt(h * h - pow(__UpperArmLength - Lb, 2.0));

   return H;
}
//---------------------------------------------------------------------------
// PlatformMinHeight()
//---------------------------------------------------------------------------
double CRobot::PlatformMinHeight(void)
{
   return CalcPlatformHeight(__MinJackL);
}
//---------------------------------------------------------------------------
// PlatformMaxHeight()
//---------------------------------------------------------------------------
double CRobot::PlatformMaxHeight(void)
{
   return CalcPlatformHeight(__MaxJackL);
}
//---------------------------------------------------------------------------
// L1Length()
//---------------------------------------------------------------------------
double CRobot::L1Length(void)
{
   double xi    = __UpperEurlar[0];
   double theta = __UpperEurlar[1];
   double phi   = __UpperEurlar[2];
   double x0    = __UpperPos[0];
   double y0    = __UpperPos[1];
   double z0    = __UpperPos[2];

   double Lt = __UpperArmLength;
   double lt = __UpperBaseLength;
   double Lb = __LowerArmLength;
   double lb = __LowerBaseLength;

   double Length = pow(cos(theta) * cos(xi) * Lt - cos(theta) * sin(xi) * lt + x0 - 0.5 * Lb - 0.5 * lb * sqrt(3.0), 2.0) +
                   pow((sin(theta) * sin(phi) * cos(xi) + cos(phi) * sin(xi)) * Lt + (-sin(theta) * sin(phi) * sin(xi) + cos(phi) * cos(xi)) * lt + y0 - 0.5 * Lb * sqrt(3.0) + 0.5 * lb, 2.0) +
                   pow((-sin(theta) * cos(phi) * cos(xi) + sin(phi) * sin(xi)) * Lt + (sin(theta) * cos(phi) * sin(xi) + sin(phi) * cos(xi)) * lt + z0, 2.0);

   return sqrt(Length);


   //,    (cos(theta)*cos(xi)*(-1/2*Lt+1/2*lt*3^(1/2))-cos(theta)*sin(xi)*(1/2*Lt*3^(1/2)+1/2*lt)+x0-1/2*Lb+1/2*lb*3^(1/2))^2+((sin(theta)*sin(phi)*cos(xi)+cos(phi)*sin(xi))*(-1/2*Lt+1/2*lt*3^(1/2))+(-sin(theta)*sin(phi)*sin(xi)+cos(phi)*cos(xi))*(1/2*Lt*3^(1/2)+1/2*lt)+y0-1/2*Lb*3^(1/2)-1/2*lb)^2+((-sin(theta)*cos(phi)*cos(xi)+sin(phi)*sin(xi))*(-1/2*Lt+1/2*lt*3^(1/2))+(sin(theta)*cos(phi)*sin(xi)+sin(phi)*cos(xi))*(1/2*Lt*3^(1/2)+1/2*lt)+z0)^2,
}
//--------------------------------------------------------------------------
/*
DP CRobot::ErrorFunc(Vec_I_DP &x)
{
   double Pos[3]    = {x[0], x[1], x[2]};
   double Eurlar[3] = {x[3], x[4], x[5]};

   Move(Pos, Eurlar);

   double Diff = 0;
   for(int i = 0; i < 6; ++i)
      Diff += pow(__JackLength[i] - Jacks[i].Length, 2.0);

   return Diff;
}
double CRobot::ErrorFunc(double PosGesture[6])
{
   double Pos[3]    = {PosGesture[0], PosGesture[1], PosGesture[2]};
   double Eurlar[3] = {PosGesture[3], PosGesture[4], PosGesture[5]};

   Move(Pos, Eurlar);

   double Diff = 0;
   for(int i = 0; i < 6; ++i)
      Diff += pow(__JackLength[i] - Jacks[i].Length, 2.0);

   return Diff;
}
//---------------------------------------------------------------------------
// get_psum()
//---------------------------------------------------------------------------
void CRobot::get_psum(Mat_I_DP &p, Vec_O_DP &psum)
{
    int i,j;
    DP sum;

    int mpts=p.nrows();
    int ndim=p.ncols();
    for (j=0;j<ndim;j++)
    {
        for (sum=0.0,i=0;i<mpts;i++)
            sum += p[i][j];
        psum[j]=sum;
    }
}
//---------------------------------------------------------------------------
// amoeba()
//---------------------------------------------------------------------------
bool CRobot::amoeba(Mat_IO_DP &p, Vec_IO_DP &y, const DP ftol, int &nfunk)
{
	const int NMAX=5000;
	const DP TINY=1.0e-10;
	int i,ihi,ilo,inhi,j;
	DP rtol,ysave,ytry;

	int mpts=p.nrows();
	int ndim=p.ncols();
	Vec_DP psum(ndim);
	nfunk=0;
	get_psum(p,psum);
	for (;;) {
		ilo=0;
		ihi = y[0]>y[1] ? (inhi=1,0) : (inhi=0,1);
		for (i=0;i<mpts;i++) {
			if (y[i] <= y[ilo]) ilo=i;
			if (y[i] > y[ihi]) {
				inhi=ihi;
				ihi=i;
			} else if (y[i] > y[inhi] && i != ihi) inhi=i;
		}
		rtol=2.0*fabs(y[ihi]-y[ilo])/(fabs(y[ihi])+fabs(y[ilo])+TINY);
		if (rtol < ftol) {
			SWAP(y[0],y[ilo]);
			for (i=0;i<ndim;i++) SWAP(p[0][i],p[ilo][i]);
			break;
		}
		if (nfunk >= NMAX)
                   return false;
                   
		nfunk += 2;
		ytry=amotry(p,y,psum, ihi,-1.0);
		if (ytry <= y[ilo])
			ytry=amotry(p,y,psum,ihi,2.0);
		else if (ytry >= y[inhi]) {
			ysave=y[ihi];
			ytry=amotry(p,y,psum,ihi,0.5);
			if (ytry >= ysave) {
				for (i=0;i<mpts;i++) {
					if (i != ilo) {
						for (j=0;j<ndim;j++)
							p[i][j]=psum[j]=0.5*(p[i][j]+p[ilo][j]);
						y[i]=ErrorFunc(psum);
					}
				}
				nfunk += ndim;
				get_psum(p,psum);
			}
		} else --nfunk;
	}

        return true;
}
//---------------------------------------------------------------------------
// amotry()
//---------------------------------------------------------------------------
DP CRobot::amotry(Mat_IO_DP &p, Vec_O_DP &y, Vec_IO_DP &psum, const int ihi, const DP fac)
{
	int j;
	DP fac1,fac2,ytry;

	int ndim=p.ncols();
	Vec_DP ptry(ndim);
	fac1=(1.0-fac)/ndim;
	fac2=fac1-fac;
	for (j=0;j<ndim;j++)
		ptry[j]=psum[j]*fac1-p[ihi][j]*fac2;
	ytry=ErrorFunc(ptry);
	if (ytry < y[ihi]) {
		y[ihi]=ytry;
		for (j=0;j<ndim;j++) {
			psum[j] += ptry[j]-p[ihi][j];
			p[ihi][j]=ptry[j];
		}
	}
	return ytry;
}
*/
//---------------------------------------------------------------------------
// CalcUpperPlatform()
//---------------------------------------------------------------------------
/*
bool CRobot::CalcUpperPlatform(double JackLength[6])
{
   // 连杆给定长度
   for(int i = 0; i < 6; ++i)
      __JackLength[i] = JackLength[i] * 0.001;

   // 计算初始位置
   // 初始位置设置为机器人运动空间的中心位置
   double MidZ = (PlatformMinHeight() + PlatformMaxHeight()) * 0.5;
   double InitPoly[7][6] = {{0, 0, MidZ, 0, 0, 0},
                            {1, 0, MidZ, 0, 0, 0},
                            {0, 1, MidZ, 0, 0, 0},
                            {0, 0, MidZ + 1, 0, 0, 0},
                            {0, 0, MidZ, 0.5, 0, 0},
                            {0, 0, MidZ, 0, 0.5, 0},
                            {0, 0, MidZ, 0, 0, 0.5}};

   Mat_DP p(7, 6);    // 定义单纯型多面体，由7个端点构成，其中一行表示一个端子
   Vec_DP y(7);       // 单纯型多面体每个端子的cost

   // 初始化单纯型多面体，计算每个端点的初始值
   for (int Row = 0; Row < 7; ++Row)
   {
      for(int Col = 0; Col < 6; ++Col)
         p[Row][Col] = InitPoly[Row][Col];
      y[Row] = ErrorFunc(InitPoly[Row]);
   }

   // 调用阿米巴函数计算上平台位姿
   int FuncCnt;
   bool Rst = amoeba(p, y, 1.0e-10, FuncCnt);   // 注意：amoeba()中已经包含了ErrorFunc()

   // 拷贝计算结果
   for(int Col = 0; Col < 3; ++Col)
   {
      CalcPosition[Col] = p[0][Col];
      CalcEurlar[Col]   = p[0][Col + 3];
   }

   return Rst;
}
*/
//---------------------------------------------------------------------------
void CRobot::Zeroed(void)
{
   //Move(0, 0, PlatformMinHeight(), 0, 0, 0);
	 Move(0, 0, 0.76, 0, 0, 0);
}
