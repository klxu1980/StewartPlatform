//---------------------------------------------------------------------------

#ifndef WorkSpaceH
#define WorkSpaceH
#include <Graphics.hpp>
#include <set>
#include <vector>
using namespace std;

#define SYM_NONE     0
#define SYM_BY_X     1
#define SYM_BY_Y     2
#define SYM_BY_Z     3
//---------------------------------------------------------------------------
// 定义三维点及其偏序关系，从而进一步定义三维点集合
//---------------------------------------------------------------------------
class CXYZ
{
public:
   int X, Y, Z;
public:
   CXYZ(int X, int Y, int Z) : X(X), Y(Y), Z(Z) {}
};

class XYZLess
{
public:
   bool operator () (const CXYZ xyz1, const CXYZ &xyz2)
   {
      return xyz1.Z < xyz2.Z ||
             (xyz1.Z == xyz2.Z && xyz1.X < xyz2.X) ||
             (xyz1.Z == xyz2.Z && xyz1.X == xyz2.X && xyz1.Y < xyz2.Y);
   }
};

typedef set<CXYZ, XYZLess> CXYZSet;
//---------------------------------------------------------------------------
// 定义二维点及其偏序关系，从而进一步定义二维点集合
//---------------------------------------------------------------------------
class CXY
{
public:
   int X, Y;
public:
   CXY(void) : X(0), Y(0) {}
   CXY(int X, int Y) : X(X), Y(Y) {}
};

class XYLess
{
public:
   bool operator () (const CXY &P1, const CXY &P2)
   {
      return P1.X < P2.X || (P1.X == P2.X && P1.Y < P2.Y);
   }
};

typedef set<CXY, XYLess> CXYSet;
//---------------------------------------------------------------------------
// CWorkSpace用于搜索机器人的运动空间
// 空间搜索沿着Z轴执行。对每个Z轴坐标，以Step为步长，对XY平面离散化，检查每个离散点
// 是否可达。之后，绘制出运动空间边界
//---------------------------------------------------------------------------
class CWorkSpace
{
friend class CCubeSpace;
private:
   bool     *__XYVisited;    // 二维数组，用于在搜索运动空间边界时，记录已被访问的点
   const int __XMax;         // __XYVisited的维度为(__XMax * 2 + 1) * (__YMax * 2 + 1)
   const int __YMax;
public:
   float     Step;           // 搜索步长，即每个像素点代表的长度(mm)。
   int       SymAxis;        // 对称轴
public:
   // 定义XY平面上的边界线
   // 注意：边界线上点的坐标均为真实坐标，单位mm
   class CBorderXY
   {
   public:
      int Z;
      vector<CXY> Border;
   public:
      CBorderXY(int Z) : Z(Z) {}
      CBorderXY(int Z, vector<CXY> &Border)
       : Z(Z), Border(Border) {}
   };
   vector<CBorderXY> BorderXYZ;   // BorderXYZ是经过排序后的边界点
private:
   bool& XYVisited(int X, int Y){return __XYVisited[(__YMax - Y) * (__XMax * 2 + 1) + __XMax + X];}
   void  InitVisitMark(void){memset(__XYVisited, 0, (__XMax * 2 + 1) * (__YMax * 2 + 1));}
protected:
   virtual bool IsFeasible(int X, int Y, int Z) = 0;    // 检查某个点是否处在可达空间中，注意：X, Y, Z为由步长离散化后的坐标
   virtual void BeginEnumInitXY(int Z) = 0;             // 开始枚举初始点
   virtual bool FindNextInitXY(CXY &InitPoint) = 0;     // 找到下一个初始可达点，如果已枚举完，则返回false
   virtual void VisitXYInFloodFill(int X, int Y) = 0;
protected:
   void GetWorkSpaceBorderXY(int Z);                     // 找出Z所对应XY平面上的边界线
   void FloodFillXYSpace(int Z, CXY InitPoint, set<CXY, XYLess> &BorderSet);
   void SortBorderXY(int Z, set<CXY, XYLess> &BorderSet);
protected:
   void SaveBorder(TStream *Stream);        // 存储工作空间边界点
   void LoadBorder(TStream *Stream);        // 加载工作空间边界点
public:
   CWorkSpace(void);
public:
   void DrawSpaceBorderXY(Graphics::TBitmap *SpaceImg, int Z);
   void DrawSpaceBorderXY(int Z, Graphics::TBitmap *SpaceImg, bool BorderOnly);
public:
   void virtual SaveToFile(AnsiString FileName) = 0;
   void virtual LoadFromFile(AnsiString FileName) = 0;
};
//----------------------------------------------------------------------------
#endif
