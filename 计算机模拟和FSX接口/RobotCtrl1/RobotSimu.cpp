//---------------------------------------------------------------------------


#pragma hdrstop

#include "RobotSimu.h"
#include <values.h>
#include "Unit1.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CRobotSimu::CRobotSimu(void)
{
   double X = -0.2;
   double Pos[6][3] = { 0.553 + X,  0.200, -0.100,
                        0 + X,    0.328, -0.100,
                       -0.347 + X,  0.200, -0.100,
                       -0.347 + X, -0.200, -0.100,
                        0 + X,   -0.328, -0.100,
                        0.553 + X, -0.200, -0.100
                      };
   for(int i = 0; i < 6; ++i)
      CopyVector(ChairBase[i], Pos[i]);
}
//--------------------------------------------------------------------------
CMoveStatus CRobotSimu::Move(double X, double Y, double Z,
                             double Yaw, double Pitch, double Roll)
{
   CMoveStatus Rst = CRobot::Move(X, Y, Z, Yaw, Pitch, Roll);
   CalcGlobalCoordination(X, Y, Z, Yaw, Pitch, Roll, ChairBase, ChairBasePos, 6);

   return Rst;
}
//---------------------------------------------------------------------------
bool CRobotSimu::CalcUpperPlatform(double JackLength[6])
{
   double X, Y, Z, Yaw, Pitch, Roll;
   CalcUpperPlatformPosEurlar(JackLength, X, Y, Z, Yaw, Pitch, Roll);

   CalcPosition[0] = X;
   CalcPosition[1] = Y;
   CalcPosition[2] = Z;
   CalcEurlar[0]   = Yaw;
   CalcEurlar[1]   = Pitch;
   CalcEurlar[2]   = Roll;

   // 计算上平台铰接点坐标
   CalcGlobalCoordination(CalcPosition[0], CalcPosition[1], CalcPosition[2],
                          CalcEurlar[0],   CalcEurlar[1],   CalcEurlar[2],
                          __UpperOrig, UpperJoints, 6);

   Form1->ListView2->Items->Item[0]->SubItems->Strings[1] = AnsiString().sprintf("%1.1f", CalcPosition[0] * 1000);
   Form1->ListView2->Items->Item[1]->SubItems->Strings[1] = AnsiString().sprintf("%1.1f", CalcPosition[1] * 1000);
   Form1->ListView2->Items->Item[2]->SubItems->Strings[1] = AnsiString().sprintf("%1.1f", CalcPosition[2] * 1000);

   Form1->ListView2->Items->Item[3]->SubItems->Strings[1] = AnsiString().sprintf("%1.1f", CalcEurlar[0]);
   Form1->ListView2->Items->Item[4]->SubItems->Strings[1] = AnsiString().sprintf("%1.1f", CalcEurlar[1]);
   Form1->ListView2->Items->Item[5]->SubItems->Strings[1] = AnsiString().sprintf("%1.1f", CalcEurlar[2]);
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
