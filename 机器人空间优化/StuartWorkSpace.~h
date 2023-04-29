//---------------------------------------------------------------------------

#ifndef StuartWorkSpaceH
#define StuartWorkSpaceH
#include "WorkSpace.h"
#include "Robot.h"
#include <map>
#include <set>
using namespace std;
//---------------------------------------------------------------------------
// 6-DOF并联机器人运动空间
//---------------------------------------------------------------------------
class CStuartWorkSpace : public CWorkSpace
{
private:
   int __InitX;
   int __InitY;
public:
   CRobot Robot;
public:
   // 姿态角度约束。搜索运动空间范围时，需要在这里定义姿态角的最大范围
   float YawMin;
   float YawMax;
   float PitchMin;
   float PitchMax;
   float RollMin;
   float RollMax;
   float Z;
   float MinJackForce;
   float MaxJackForce;
private:
   bool IsFeasible(int X, int Y, int Z);         // 检测特定位置能否到达
   void BeginEnumInitXY(int Z);
   bool FindNextInitXY(CXY &InitPoint);
   void VisitXYInFloodFill(int X, int Y){}
public:
   CStuartWorkSpace(void);
public:
   void GetWorkSpaceBorder(void);
   void SetSearchStep(float Step);
public:
   void SaveToFile(AnsiString FileName);
   void LoadFromFile(AnsiString FileName);
};
//---------------------------------------------------------------------------
class CJuneBugWorkSpace : public CStuartWorkSpace
{
public:
   int XYHeight;
   int YawRange;
public:
   CJuneBugWorkSpace(void);
public:
   void GetWorkSpaceBorder(void);
};
#endif
