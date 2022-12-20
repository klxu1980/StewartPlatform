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
class CWorkSpace
{
friend class CCubeSpace;
private:
   // ��¼����˶��ռ��У�ÿ����ɢ��Ŀɴ���
   char     *__XYVisited;
   const int __XMax;
   const int __YMax;
public:
   // ������������ÿ�����ص����ĳ���(mm)
   float     Step;
   int       SymAxis;    // �Գ���
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
   vector<CBorderXY> BorderXYZ;   // BorderXYZ�Ǿ��������ı߽��
private:
   char& XYVisited(int X, int Y){return __XYVisited[(__YMax - Y) * (__XMax * 2 + 1) + __XMax + X];}
   void  InitVisitMark(void){memset(__XYVisited, 0, (__XMax * 2 + 1) * (__YMax * 2 + 1));}
protected:
   virtual bool IsFeasible(int X, int Y, int Z) = 0;    // ���ĳ�����Ƿ��ڿɴ�ռ��У�ע�⣺X, Y, ZΪ�ɲ�����ɢ���������
   virtual void BeginEnumInitXY(int Z) = 0;             // ��ʼö�ٳ�ʼ��
   virtual bool FindNextInitXY(CXY &InitPoint) = 0;     // �ҵ���һ����ʼ�ɴ�㣬�����ö���꣬�򷵻�false
   virtual void VisitXYInFloodFill(int X, int Y) = 0;
protected:
   void GetWorkSpaceBorderXY(int Z);                     // �ҳ�Z����ӦXYƽ���ϵı߽���
   void FloodFillXYSpace(int Z, CXY InitPoint, set<CXY, XYLess> &BorderSet);
   void SortBorderXY(int Z, set<CXY, XYLess> &BorderSet);
protected:
   void SaveBorder(TStream *Stream);        // �洢�����ռ�߽��
   void LoadBorder(TStream *Stream);        // ���ع����ռ�߽��
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
