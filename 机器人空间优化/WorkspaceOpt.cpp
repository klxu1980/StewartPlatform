//---------------------------------------------------------------------------


#pragma hdrstop

#include "WorkspaceOpt.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
// CubeFeasible()
// Check if the cube is feasible.
// Checking method: Check if any one of the work space border falls into the cube.
//---------------------------------------------------------------------------
bool CWorkspaceOpt::CubeFeasible(double OX, double OY, double OZ, double WX, double WY, double WZ)
{
   double X1 = OX - WX;
   double X2 = OX + WX;
   double Y1 = OY - WY;
   double Y2 = OY + WY;
   double Z1 = OZ - WZ;
   double Z2 = OZ + WZ;

   for(unsigned int i = 0; i < WorkSpace->BorderXYZ.size(); ++i)
   {
      double Z = WorkSpace->BorderXYZ[i].Z * 0.001;
      vector<CContour::CPoint> &Border = WorkSpace->BorderXYZ[i].Border;
      for(unsigned int m = 0; m < Border.size(); ++m)
      {
         double X = Border[m].X * 0.001;
         double Y = Border[m].Y * 0.001;

         if(X > X1 && X < X2 && Y > Y1 && Y < Y2 && Z > Z1 && Z < Z2)
            return false;
      }
   }
   return true;
}
bool CWorkspaceOpt::CubeFeasible(double OX, double OY, double OZ, double L)
{
   // 首先检测中心点是否在机器人工作空间中
   if(!WorkSpace->IsFeasible(OX / WorkSpace->XStep, OY / WorkSpace->YStep, OZ / WorkSpace->ZStep))
      return false;

   // 之后检测工作空间边界点是否在立方体内
   double X1 = OX - L * Kx;
   double X2 = OX + L * Kx;
   double Y1 = OY - L * Ky;
   double Y2 = OY + L * Ky;
   double Z1 = OZ - L * Kz;
   double Z2 = OZ + L * Kz;

   for(unsigned int i = 0; i < WorkSpace->BorderXYZ.size(); ++i)
   {
      double Z = WorkSpace->BorderXYZ[i].Z * WorkSpace->ZStep;
      vector<CContour::CPoint> &Border = WorkSpace->BorderXYZ[i].Border;
      for(unsigned int m = 0; m < Border.size(); ++m)
      {
         double X = Border[m].X * WorkSpace->XStep;
         double Y = Border[m].Y * WorkSpace->YStep;

         if(X > X1 && X < X2 && Y > Y1 && Y < Y2 && Z > Z1 && Z < Z2)
            return false;
      }
   }
   return true;
}
//---------------------------------------------------------------------------
float CWorkspaceOpt::MaximizeL(double X, double Y, double Z)
{       
   // 首先搜索两个初始点，L1满足约束，L2不满足约束
   double L = 0.1;
   double L1, L2;
   if(CubeFeasible(X, Y, Z, L))
   {
      do
      {
         L1 = L;
         L *= 2;
      }while(CubeFeasible(X, Y, Z, L));
      L2 = L;
   }
   else
   {
      do
      {
         L2 = L;
         L *= 0.5;
      }while(!CubeFeasible(X, Y, Z, L) && L > 0.01);
      L1 = L;
   }
   if(L1 <= 0.001)
      return 0;

   // 通过二分法找到最大的L
   while(L2 - L1 > 0.00001)
   {
      L = (L1 + L2) * 0.5;
      if(CubeFeasible(X, Y, Z, L))
         L1 = L;
      else
         L2 = L;
   }
   return L1;
}
//---------------------------------------------------------------------------
/*
DP CWorkspaceOpt::CostFunction(const double *YZ)
{
   float MaxL = MaximizeL(YZ[0], YZ[1]);
   return -MaxL;
}
*/

DP CWorkspaceOpt::CostFunction(const double *Solution)
{
   double X, Y, Z, L;
   if(SymmetryByX)
   {
      // 以X轴为对称，则解中仅包括立方体中心坐标为(X, 0, Z)
      X = Solution[0];
      Y = 0;
      Z = Solution[1];
      L = Solution[2];
   }
   else
   {
      // 以Y轴为对称，则解中仅包括立方体中心坐标为(0, Y, Z)
      X = 0;
      Y = Solution[0];
      Z = Solution[1];
      L = Solution[2];
   }

   float MaxL = MaximizeL(X, Y, Z);
   return -MaxL;
}

/*
DP CWorkspaceOpt::CostFunction(const double *Solution)
{
   double X, Y, Z, L;
   if(SymmetryByX)
   {
      // 以X轴为对称，则解中仅包括立方体中心坐标为(X, 0, Z)
      X = Solution[0];
      Y = 0;
      Z = Solution[1];
      L = Solution[2];
   }
   else
   {
      // 以Y轴为对称，则解中仅包括立方体中心坐标为(0, Y, Z)
      X = 0;
      Y = Solution[0];
      Z = Solution[1];
      L = Solution[2];
   }

   if(CubeFeasible(X, Y, Z, L))
      return -L;
   else
      return 0;
}
*/
//---------------------------------------------------------------------------
/*
bool CWorkspaceOpt::Optimize(void)
{
   float InitZ = (WorkSpace->BorderXYZ.front().Z + WorkSpace->BorderXYZ.back().Z) * 0.5 * 0.001;
   double InitPoly[3 * 2] = {0.0,  InitZ,
                             0.001, InitZ,
                             0.0,  InitZ + 0.001};

   int    IterCnt;
   double Solution[2];
   if(Calc(InitPoly, 2, Solution, IterCnt))
   {
      Y = Solution[0];
      Z = Solution[1];
      L = MaximizeL(Y, Z);

      return true;
   }
   else
      return false;
}
*/

bool CWorkspaceOpt::Optimize(void)
{
   if(SymmetryByX)
   {
      double InitPoly[3 * 2] = {InitX,     InitZ,
                                InitX + 1, InitZ,
                                InitX,     InitZ + 1
                               };

      int    IterCnt;
      double Solution[2];
      if(Calc(InitPoly, 2, Solution, IterCnt))
      {
         X = Solution[0];
         Y = 0;
         Z = Solution[1];

         L = MaximizeL(X, Y, Z);

         return true;
      }
      else
         return false;
   }
   else
   {
      double InitPoly[3 * 2] = {InitY,     InitZ,
                                InitY + 1, InitZ,
                                InitY,     InitZ + 1
                               };

      int    IterCnt;
      double Solution[2];
      if(Calc(InitPoly, 2, Solution, IterCnt))
      {
         X = 0;
         Y = Solution[0];
         Z = Solution[1];

         L = MaximizeL(X, Y, Z);

         return true;
      }
      else
         return false;
   }
}
//----------------------------------------------------------------------------
void CWorkspaceOpt::DrawSpace(float Z, Graphics::TBitmap *SpaceMap)
{
   if(Z < this->Z - L * Kz || Z > this->Z + L * Kz)
      return;
      
   int OY = Y * 1000 + 0.5;
   SpaceMap->Canvas->Pen->Color = clRed;
   SpaceMap->Canvas->MoveTo( L * Kx * 1000 + SpaceMap->Width / 2, -L * Ky * 1000 + SpaceMap->Height / 2);
   SpaceMap->Canvas->LineTo(-L * Kx * 1000 + SpaceMap->Width / 2, -L * Ky * 1000 + SpaceMap->Height / 2);
   SpaceMap->Canvas->LineTo(-L * Kx * 1000 + SpaceMap->Width / 2,  L * Ky * 1000 + SpaceMap->Height / 2);
   SpaceMap->Canvas->LineTo( L * Kx * 1000 + SpaceMap->Width / 2,  L * Ky * 1000 + SpaceMap->Height / 2);
   SpaceMap->Canvas->LineTo( L * Kx * 1000 + SpaceMap->Width / 2, -L * Ky * 1000 + SpaceMap->Height / 2);
}
