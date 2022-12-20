//---------------------------------------------------------------------------


#pragma hdrstop

#include "Observer.h"
#include "BasicCalc.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CObserver::CObserver(void)
{
   for(int i = 0; i < 3; ++i)
   {
      MeterPos[i]   = 0;
      MeterEuler[i] = 0;
      ErrPos[i]     = 0;
      ErrEuler[i]   = 0;
   }
}
//---------------------------------------------------------------------------
void CObserver::CalcPosEuler(double M1[3], double M2[3], double M3[3], double Pos[3], double Euler[3])
{
   // 将观测点坐标转换到机器人坐标系中
   double M[3][3] = {M1[0], M1[1], M1[2],
                     M2[0], M2[1], M2[2],
                     M3[0], M3[1], M3[2]
                    };

   double P[3][3];
   PointFromObserverToRobot(P, M, 3);

   // 计算中心点坐标和欧拉角
   PosEulerByTriangle(Pos, Euler, P[0], P[1], P[2]);
}
//---------------------------------------------------------------------------
void CObserver::PointFromRobotToObserver(double Rst[][3], double Src[][3], int Count)
{
   double Pos[3], Euler[3];
   VectorAddVector(Pos, MeterPos, ErrPos);
   VectorAddVector(Euler, MeterEuler, ErrEuler);

   double RM[3][3], RMT[3][3];
   RotateMatrixByEuler(RM, Euler);
   TransMatrix(RMT, RM);

   for(int i = 0; i < Count; ++i)
   {
      double Tmp[3];
      VectorSubVector(Tmp, Src[i], Pos);
      MatrixMultiVector(Rst[i], RMT, Tmp);
   }
}
//---------------------------------------------------------------------------
void CObserver::PointFromObserverToRobot(double Rst[][3], double Src[][3], int Count)
{
   double Pos[3], Euler[3];
   VectorAddVector(Pos, MeterPos, ErrPos);
   VectorAddVector(Euler, MeterEuler, ErrEuler);

   double RM[3][3];
   RotateMatrixByEuler(RM, Euler);

   for(int i = 0; i < Count; ++i)
   {
      MatrixMultiVector(Rst[i], RM, Src[i]);
      VectorAddVector(Rst[i], Rst[i], Pos);
   }
}