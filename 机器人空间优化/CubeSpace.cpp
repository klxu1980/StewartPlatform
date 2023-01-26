//---------------------------------------------------------------------------


#pragma hdrstop

#include "CubeSpace.h"
#define MAX_L_INDEPENDENTLY
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
bool CCubeSpace::CubeFeasible(double OX, double OY, double OZ, double L)
{
   // 目前看，枚举方法的计算效率反而更高一些
   //return CheckFeasibleByEnum? CubeFeasibleByEnum(OX, OY, OZ, L) : CubeFeasibleByBorder(OX, OY, OZ, L);

   return CubeFeasibleByBorder(OX, OY, OZ, L);
}
//---------------------------------------------------------------------------
// CubeFeasibleByEnum()
// Checking method: Check by enumerating every point.
//---------------------------------------------------------------------------
bool CCubeSpace::CubeFeasibleByEnum(double OX, double OY, double OZ, double L)
{
   // 对工作空间离散化后，检查工作空间
   int XBegin = (OX - L * Kx) / WorkSpace->Step;
   int XEnd   = (OX + L * Kx) / WorkSpace->Step;

   int YBegin = (OY - L * Ky) / WorkSpace->Step;
   int YEnd   = (OY + L * Ky) / WorkSpace->Step;

   int ZBegin = (OZ - L * Kz) / WorkSpace->Step;
   int ZEnd   = (OZ + L * Kz) / WorkSpace->Step;

   // 如果空间存在对称性，则减少一半检测计算量
   switch(WorkSpace->SymAxis)
   {
   case SYM_BY_X : YBegin = 0; break;
   case SYM_BY_Y : XBegin = 0; break;
   }

   // 枚举检测每个离散化点
   for(int X = XBegin; X <= XEnd; ++X)
      for(int Y = YBegin; Y <= YEnd; ++Y)
         for(int Z = ZBegin; Z <= ZEnd; ++Z)
            if(!WorkSpace->IsFeasible(X, Y, Z))
               return false;

   return true; 

}
//---------------------------------------------------------------------------
bool CCubeSpace::CubeFeasibleByBorder(double OX, double OY, double OZ, double L)
{
   // 首先检测中心点是否在机器人工作空间中
   if(!WorkSpace->IsFeasible(OX / WorkSpace->Step, OY / WorkSpace->Step, OZ / WorkSpace->Step))
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
      double Z = WorkSpace->BorderXYZ[i].Z;
      vector<CXY> &Border = WorkSpace->BorderXYZ[i].Border;
      for(unsigned int m = 0; m < Border.size(); ++m)
      {
         double X = Border[m].X;
         double Y = Border[m].Y;

         if(X > X1 && X < X2 && Y > Y1 && Y < Y2 && Z > Z1 && Z < Z2)
            return false;
      }
   }
   return true;
}
//---------------------------------------------------------------------------
// MaximizeL()
//---------------------------------------------------------------------------
float CCubeSpace::MaximizeL(double X, double Y, double Z)
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
#ifdef MAX_L_INDEPENDENTLY
double CCubeSpace::CostFunction(const double *Solution)
{
   double X, Y, Z;
   if(WorkSpace->SymAxis == SYM_BY_X)
   {
      // 以X轴为对称，则解中仅包括立方体中心坐标为(X, 0, Z)
      X = Solution[0];
      Y = 0;
      Z = Solution[1];
   }
   else
   {
      // 以Y轴为对称，则解中仅包括立方体中心坐标为(0, Y, Z)
      X = 0;
      Y = Solution[0];
      Z = Solution[1];
   }

   float MaxL = MaximizeL(X, Y, Z);
   return -MaxL;
}
#else
DP CCubeSpace::CostFunction(const double *Solution)
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
#endif
//---------------------------------------------------------------------------
#ifdef MAX_L_INDEPENDENTLY
bool CCubeSpace::Optimize(void)
{
   int Offset = WorkSpace->Step * 2;
   if(WorkSpace->SymAxis == SYM_BY_X)
   {
      double InitPoly[3 * 2] = {InitX,          InitZ,
                                InitX + Offset, InitZ,
                                InitX,          InitZ + Offset
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
      double InitPoly[3 * 2] = {InitY,          InitZ,
                                InitY + Offset, InitZ,
                                InitY,          InitZ + Offset
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
#else
bool CCubeSpace::Optimize(void)
{
   if(SymmetryByX)
   {
      double InitPoly[4 * 3] = {InitX,     InitZ,     0.1,
                                InitX + 1, InitZ,     0.1,
                                InitX,     InitZ + 1, 0.1,
                                InitX,     InitZ,     0.2
                               };

      int    IterCnt;
      double Solution[3];
      if(Calc(InitPoly, 3, Solution, IterCnt))
      {
         X = Solution[0];
         Y = 0;
         Z = Solution[1];
         L = Solution[2];

         return true;
      }
      else
         return false;
   }
   else
   {
      double InitPoly[4 * 3] = {InitY,     InitZ,   0.1,
                                InitY + 1, InitZ,   0.1,
                                InitY,     InitZ + 1, 0.1,
                                InitY,     InitZ,    0.2
                               };

      int    IterCnt;
      double Solution[3];
      if(Calc(InitPoly, 3, Solution, IterCnt))
      {
         X = 0;
         Y = Solution[0];
         Z = Solution[1];
         L = Solution[2];

         return true;
      }
      else
         return false;
   }
}
#endif
//----------------------------------------------------------------------------
void CCubeSpace::DrawSpace(float Z, Graphics::TBitmap *SpaceMap)
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
//----------------------------------------------------------------------------
void CCubeSpace::OptimizeNaiveByXZ(int MinX, int MaxX, int MinZ, int MaxZ)
{
   int XBegin = MinX / WorkSpace->Step;
   int XEnd   = MaxX / WorkSpace->Step;
   int ZBegin = MinZ / WorkSpace->Step;
   int ZEnd   = MaxZ / WorkSpace->Step;

   float MaxL = 0;
   float Cx, Cz;
   for(int x = XBegin; x < XEnd; ++x)
      for(int z = ZBegin; z < ZEnd; ++z)
      {
         float L = MaximizeL(x * WorkSpace->Step, 0, z * WorkSpace->Step);
         if(L > MaxL)
         {
            MaxL = L;
            Cx = x;
            Cz = z;
         }
      }

   X = Cx * WorkSpace->Step;
   Y = 0;
   Z = Cz * WorkSpace->Step;
   L = MaxL;
}
//----------------------------------------------------------------------------
void CCubeSpace::OptimizeNaive(int MinX, int MaxX, int MinY, int MaxY, int MinZ, int MaxZ)
{
   int XBegin = MinX / WorkSpace->Step;
   int XEnd   = MaxX / WorkSpace->Step;
   int YBegin = MinY / WorkSpace->Step;
   int YEnd   = MaxY / WorkSpace->Step;
   int ZBegin = MinZ / WorkSpace->Step;
   int ZEnd   = MaxZ / WorkSpace->Step;

   float MaxL = 0;
   float Cx, Cy, Cz;
   for(int x = XBegin; x <= XEnd; ++x)
      for(int y = YBegin; y <= YEnd; ++y)
         for(int z = ZBegin; z <= ZEnd; ++z)
         {
            float L = MaximizeL(x * WorkSpace->Step, y * WorkSpace->Step, z * WorkSpace->Step);
            if(L > MaxL)
            {
               MaxL = L;
               Cx = x;
               Cy = y;
               Cz = z;
            }
         }

   X = Cx * WorkSpace->Step;
   Y = Cy * WorkSpace->Step;
   Z = Cz * WorkSpace->Step;
   L = MaxL;
}
