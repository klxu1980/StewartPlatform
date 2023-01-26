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
   float Kx;       // X, Y, Z����ϵ��
   float Ky;
   float Kz;
public:
   float X;        // �Ż������������������ͳ���
   float Y;
   float Z;
   float L;
public:
   bool  CheckFeasibleByEnum;           // �Ƿ����ö�ټ�⹤���ռ�
   float InitX, InitY, InitZ;           // ��ʼ����λ��
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
