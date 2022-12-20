//---------------------------------------------------------------------------


#pragma hdrstop

#include "RobotIKP.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
// CalcGlobalCoordination()
//---------------------------------------------------------------------------
void CRobotIKP::CalcGlobalCoordination(double Pos[3], double Euler[3],
                                       double PosLocal[][3], double PosGlobal [][3], int Count)
{
   // 获得旋转矩阵
   double RMatrix[3][3];
   RotateMatrixByEuler(RMatrix, Euler);

   // 将每个点映射到全局坐标系
   for(int i = 0; i < Count; ++i)
   {
      MatrixMultiVector(PosGlobal[i], RMatrix, PosLocal[i]);
      VectorAddVector(PosGlobal[i], PosGlobal[i], Pos);
   }
}
//---------------------------------------------------------------------------
// CalcGlobalCoordination()
//---------------------------------------------------------------------------
void CRobotIKP::CalcGlobalCoordination(double X, double Y, double Z, double Yaw, double Pitch, double Roll,
                                       double PosLocal[][3], double PosGlobal [][3], int Count)
{
   double Pos[3] = {X, Y, Z};
   double Eurlar[3] = {Yaw, Pitch, Roll};

   CalcGlobalCoordination(Pos, Eurlar, PosLocal, PosGlobal, Count);
}
//---------------------------------------------------------------------------
// CalcGlobalCoordination()
//---------------------------------------------------------------------------
void CRobotIKP::CalcGlobalCoordination(double PosLocal[][3], double PosGlobal [][3], int Count)
{  
   CalcGlobalCoordination(UpperPos, UpperEuler, PosLocal, PosGlobal, Count);
}
//---------------------------------------------------------------------------
// Move()
//---------------------------------------------------------------------------
void CRobotIKP::Move(double X, double Y, double Z, double Yaw, double Pitch, double Roll)
{
   // 拷贝位姿
   CopyVector(UpperPos,   X, Y, Z);
   CopyVector(UpperEuler, Yaw, Pitch, Roll);

   // 计算上平台铰接点在下平台坐标系中的坐标
   CalcGlobalCoordination(UpperPos, UpperEuler, UpperJointInUpperCoordinate, UpperJointInLowerCoordinate, 6);

   // 计算连杆长度
   CalcJackLength(JackLength);
}
