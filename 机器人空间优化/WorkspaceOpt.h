//---------------------------------------------------------------------------

#ifndef WorkspaceOptH
#define WorkspaceOptH
#include "Contour.h"
#include "SimplexOptimizer.h"
//---------------------------------------------------------------------------
class CWorkspaceOpt : public CSimplexOptimizer
{
public:
   CContour *WorkSpace;
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
   bool  SymmetryByX;                   // True: 沿X轴对称，False：沿Y轴对称
   float InitX, InitY, InitZ;           // 初始中心位置
private:
   float MaximizeL(double X, double Y, double Z);
   bool  CubeFeasible(double OX, double OY, double OZ, double WX, double WY, double WZ);
   bool  CubeFeasible(double OX, double OY, double OZ, double L);
   DP    CostFunction(const double *YZ);
public:
   bool  Optimize(void);
   void  DrawSpace(float Z, Graphics::TBitmap *SpaceMap);
};



#endif
