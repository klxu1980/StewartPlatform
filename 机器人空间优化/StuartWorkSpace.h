//---------------------------------------------------------------------------

#ifndef StuartWorkSpaceH
#define StuartWorkSpaceH
#include "WorkSpace.h"
#include "Robot.h"
#include <map>
#include <set>
using namespace std;
//---------------------------------------------------------------------------
// 6-DOF�����������˶��ռ�
//---------------------------------------------------------------------------
class CStuartWorkSpace : public CWorkSpace
{
private:
   int __InitX;
   int __InitY;
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
private:
   bool IsFeasible(int X, int Y, int Z);         // ����ض�λ���ܷ񵽴�
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
#endif
