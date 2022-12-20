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
   char     *__SpaceMap;     // ��¼����˶��ռ��У�ÿ����ɢ��Ŀɴ���
   const int __SpaceXMax;
   const int __SpaceYMax;
public:
   float     XStep;          // ������������ÿ�����ص����ĳ���(mm)
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
   // ����XYƽ���ϵı߽���
   // ע�⣺�߽����ϵ�������Ϊ��ʵ���꣬��λmm
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
   virtual bool IsFeasible(int X, int Y, int Z) = 0;             // ���ĳ�����Ƿ��ڿɴ�ռ���
   virtual bool FindInitPoint(CXY &InitPoint, int Z) = 0;     // �ҵ���һ����ʼ�ɴ��
protected:
   void GetWorkSpaceBorderXY(int Z);                     // �ҳ�Z����ӦXYƽ���ϵı߽���
   void FloodFillXYSpace(int Z, CXY InitPoint, set<CXY, CXYLess> &BorderSet);
   void SortBorderXY(int Z, set<CXY, CXYLess> &BorderSet);
protected:
   void SaveContour(TStream *Stream);        // �������ռ�洢���ļ���
   void LoadContour(TStream *Stream);      // ���ļ��ж�ȡ�����ռ�
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
