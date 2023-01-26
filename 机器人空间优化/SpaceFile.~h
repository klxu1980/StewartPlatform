//---------------------------------------------------------------------------

#ifndef SpaceFileH
#define SpaceFileH
#include "WorkSpace.h"
#include <set>
using namespace std;
//---------------------------------------------------------------------------
// CSpaceFile is used to generate workspace from file saved data.
//---------------------------------------------------------------------------
class CSpaceFile : public CWorkSpace
{
private:
   int     __MinZ;
   int     __MaxZ;
   CXYZSet __Reachable;
   CXYSet  __XYLayer;
private:
   bool IsFeasible(int X, int Y, int Z){return __Reachable.count(CXYZ(X, Y, Z) );}
   void BeginEnumInitXY(int Z);
   bool FindNextInitXY(CXY &InitPoint);
   void GetXYLayer(CXYSet &Space, int Z);
   void VisitXYInFloodFill(int X, int Y);
public:
   CSpaceFile(int Step);
public:
   void LoadRobotFile(AnsiString FileName);
public:
   void SaveToFile(AnsiString FileName);
   void LoadFromFile(AnsiString FileName);
public:
   void GetXYSpace(vector<CXY> &Space, int Z);
};
#endif
