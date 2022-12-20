//---------------------------------------------------------------------------

#ifndef CRobotSpaceH
#define CRobotSpaceH
#include "WorkSpace.h"
#include "Robot.h"
#include <map>
#include <set>
using namespace std;
//---------------------------------------------------------------------------
class CStuartWorkSpace : public CWorkSpace
{
private:
   int __InitZ;
public:
   CRobot Robot;
public:
   float YawMin;
   float YawMax;
   float PitchMin;
   float PitchMax;
   float RollMin;
   float RollMax;
   float Z;
public:
   float Step;      // 搜索步长
private:
   bool IsFeasible(int X, int Y, int Z);     // 检测特定位置能否到达
   void BeginEnumInitXY(int Z);
   bool FindNextInitXY(CXY &InitPoint, int Z);
public:
   CStuartWorkSpace(void);
public:
   void GetWorkSpaceBorder(void);
   void SetSearchStep(float Step);
public:
   void SaveToFile(AnsiString FileName);
   void LoadFromFile(AnsiString FileName);  
};
#endif
