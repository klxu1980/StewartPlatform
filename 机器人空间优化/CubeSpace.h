//---------------------------------------------------------------------------

#ifndef CubeSpaceH
#define CubeSpaceH
#include "WorkSpace.h"
#include "SimplexOptimizer.h"
//---------------------------------------------------------------------------
class CCubeSpace : public CSimplexOptimizer
{
public:
   CWorkSpace *WorkSpace;
public:
   float Kx;       // X, Y, Z比例系数
   float Ky;
   float Kz;
public:
   float X;        // 优化后的立方体中心坐标和长度
   float Y;
   float Z;
   float L;
public:
   bool  CheckFeasibleByEnum;           // 是否基于枚举检测工作空间
   float InitX, InitY, InitZ;           // 初始中心位置
private:
   float  MaximizeL(double X, double Y, double Z);
   bool   CubeFeasible(double OX, double OY, double OZ, double L);
   bool   CubeFeasibleByEnum(double OX, double OY, double OZ, double L);
   bool   CubeFeasibleByBorder(double OX, double OY, double OZ, double L);
   double CostFunction(const double *YZ);
public:
   CCubeSpace(void) : CheckFeasibleByEnum(true) {}
public:
   bool  Optimize(void);
   void  OptimizeNaiveByXZ(int MinX, int MaxX, int MinZ, int MaxZ);
   void  OptimizeNaive(int MinX, int MaxX, int MinY, int MaxY, int MinZ, int MaxZ);
public:
   void  DrawSpace(float Z, Graphics::TBitmap *SpaceMap);
};



#endif
