//---------------------------------------------------------------------------

#ifndef ContourH
#define ContourH
#include <Graphics.hpp>
#include <set>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
class CXYZ
{
public:
   int X, Y, Z;
public:
   CXYZ(int X, int Y, int Z) : X(X), Y(Y), Z(Z) {}
};

class CXY
{
public:
   int X, Y;
public:
   CXY(void) : X(0), Y(0) {}
   CXY(int X, int Y) : X(X), Y(Y) {}
};
//---------------------------------------------------------------------------
class CWorkSpace
{
friend class CCubeSpace;
private:
   char     *__SpaceMap;     // 记录标记运动空间中，每个离散点的可达性
   const int __SpaceXMax;
   const int __SpaceYMax;
public:
   float     XStep;          // 搜索步长，即每个像素点代表的长度(mm)
   float     YStep;
   float     ZStep;
public:
   class CXYLess
   {
   public:
      bool operator () (const CXY &P1, const CXY &P2)
      {
         return P1.X < P2.X || (P1.X == P2.X && P1.Y < P2.Y);
      }
   };
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
   vector<CBorderXY> BorderXYZ;
protected:
   char& SpaceXY(int X, int Y){return __SpaceMap[(__SpaceYMax - Y) * (__SpaceXMax * 2 + 1) + __SpaceXMax + X];}
   void  InitWorkSpace(void){memset(__SpaceMap, 0, (__SpaceXMax * 2 + 1) * (__SpaceYMax * 2 + 1));}
protected:   
   virtual bool IsFeasible(int X, int Y, int Z) = 0;             // 检查某个点是否处在可达空间中
   virtual bool FindInitPoint(CXY &InitPoint, int Z) = 0;     // 找到第一个初始可达点
protected:
   void GetWorkSpaceBorderXY(int Z);                     // 找出Z所对应XY平面上的边界线
   void FloodFillXYSpace(int Z, CXY InitPoint, set<CXY, CXYLess> &BorderSet);
   void SortBorderXY(int Z, set<CXY, CXYLess> &BorderSet);
protected:
   void SaveContour(TStream *Stream);        // 将工作空间存储到文件中
   void LoadContour(TStream *Stream);      // 从文件中读取工作空间
public:
   CWorkSpace(void);
public:
   void DrawSpaceBorderXY(vector<CXY> &BorderXY, Graphics::TBitmap *SpaceImg);
   void DrawSpaceBorderXY(int Z, Graphics::TBitmap *SpaceImg, bool BorderOnly);
public:
   void virtual SaveToFile(AnsiString FileName) = 0;
   void virtual LoadFromFile(AnsiString FileName) = 0;
};
//----------------------------------------------------------------------------
#endif
