//---------------------------------------------------------------------------


#pragma hdrstop

#include "RobotBasic.h"
#include "GlobalDef.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
bool    CRobotBasic::__SinInited(false);
double  CRobotBasic::__SinValue[1801];
double  CRobotBasic::__CosValue[1801];
//---------------------------------------------------------------------------
// Initialize()
//---------------------------------------------------------------------------
CRobotBasic::CRobotBasic(void)
{
   // 预先计算正弦、余弦数值
   if(!__SinInited)
   {
      for(int i = 0; i < 1801; ++i)
      {
         __SinValue[i] = sin((i - 900) * 0.1 * M_PI / 180.0);
         __CosValue[i] = cos(i * 0.1 * M_PI / 180.0);
      }
      __SinInited = true;
   }
}
//---------------------------------------------------------------------------
// Sin()
// 快速计算正弦近似值，以保证在嵌入式系统中进行迭代计算时的高效性
//---------------------------------------------------------------------------
double CRobotBasic::Sin(double Deg)
{
#ifdef CALC_SIN_FAST
   // 将角度转变为两位定点数，归一化到0~360°之间
   // 由于正弦在-90°~90°之间单调，因此给输入角度加90°
   int DegI = (int(Deg * 100.0 + 0.5) + 9000) % 36000;

   // 预存的正弦值只包括0~180°(即-90°~90°)
   // 因此，当Deg超过180°时，需要用360°- Deg
   if(DegI >= 18000)
      DegI = 36000 - DegI;

   // 找出Deg的上下界，近似计算正弦值
   int L = DegI / 10;
   int H = L + 1;

   return (__SinValue[H] - __SinValue[L]) * (DegI - L * 10) * 0.1 + __SinValue[L];
#else
   return sin(Deg * M_PI / 180.0);
#endif
}
//---------------------------------------------------------------------------
// Cos()
// 快速计算余弦近似值，以保证在嵌入式系统中进行迭代计算时的高效性
//---------------------------------------------------------------------------
double CRobotBasic::Cos(double Deg)
{
#ifdef CALC_SIN_FAST
   // 将角度转变为两位定点数，归一化到0~360°之间
   int DegI = int(Deg * 100.0 + 0.5) % 36000;

   // 预存的余弦值只包括0~180°
   // 因此，当Deg超过180°时，需要用360°- Deg
   if(DegI >= 18000)
      DegI = 36000 - DegI;

   // 找出Deg的上下界，近似计算正弦值
   int L = DegI / 10;
   int H = L + 1;

   return (__CosValue[H] - __CosValue[L]) * (DegI - L * 10) * 0.1 + __CosValue[L];
#else
   return cos(Deg * M_PI / 180.0);
#endif
}
//--------------------------------------------------------------------------
// SetJointPositions()
//--------------------------------------------------------------------------
void CRobotBasic::SetJointCoordinates(double UpperJonts[6][3], double LowerJonts[6][3])
{
   for(int i = 0; i < 6; ++i)
   {
      CopyVector(UpperJointInUpperCoordinate[i], UpperJonts[i]);
      CopyVector(LowerJointInLowerCoordinate[i], LowerJonts[i]);
   }
}
//--------------------------------------------------------------------------
void CRobotBasic::CalcJackLength(double Length[6])
{
   // 计算连杆长度
   // 上下平台连杆铰接点编号定义：
   //      连杆            1    2   3   4   5    6
   //  上平台铰接点        1    2   3   4   5    6
   //  下平台铰接点        4    5   6   1   2    3
   Length[0] = Distance(UpperJointInLowerCoordinate[0], LowerJointInLowerCoordinate[3]);
   Length[1] = Distance(UpperJointInLowerCoordinate[1], LowerJointInLowerCoordinate[4]);
   Length[2] = Distance(UpperJointInLowerCoordinate[2], LowerJointInLowerCoordinate[5]);
   Length[3] = Distance(UpperJointInLowerCoordinate[3], LowerJointInLowerCoordinate[0]);
   Length[4] = Distance(UpperJointInLowerCoordinate[4], LowerJointInLowerCoordinate[1]);
   Length[5] = Distance(UpperJointInLowerCoordinate[5], LowerJointInLowerCoordinate[2]);
}
//--------------------------------------------------------------------------
// Copy()
//--------------------------------------------------------------------------
void CRobotBasic::Copy(CRobotBasic &Robot)
{
   CopyVector(UpperPos, Robot.UpperPos);
   CopyVector(UpperEuler, Robot.UpperEuler);

   for(int i = 0; i < 6; ++i)
   {
      CopyVector(UpperJointInLowerCoordinate[i], Robot.UpperJointInLowerCoordinate[i]);
      JackLength[i] = Robot.JackLength[i];
   }
}
//----------------------------------------------------------------------------
void CRobotBasic::SetStructureParams(double UpperArmLength,
                                     double UpperBaseLength,
                                     double LowerArmLength,
                                     double LowerBaseLength,
                                     double UpperJointHeight,
                                     double LowerJointHeight)
{
   // 上平台坐标
   double UpperJoints[6][3];

   CopyVector(UpperJoints[0],
              UpperBaseLength,
              UpperArmLength,
              -UpperJointHeight);
   RotateAroundZ(UpperJoints[2], UpperJoints[0],  120);
   RotateAroundZ(UpperJoints[4], UpperJoints[0], -120);

   CopyVector(UpperJoints[1],
              -UpperBaseLength,
              UpperArmLength,
              -UpperJointHeight);
   RotateAroundZ(UpperJoints[3], UpperJoints[1],  120);
   RotateAroundZ(UpperJoints[5], UpperJoints[1], -120);

   // 下平台坐标系
   double LowerJoints[6][3];

   CopyVector(LowerJoints[0],
              -LowerBaseLength,
              -LowerArmLength,
              LowerJointHeight);
   RotateAroundZ(LowerJoints[2], LowerJoints[0],  120);
   RotateAroundZ(LowerJoints[4], LowerJoints[0], -120);

   CopyVector(LowerJoints[1],
              LowerBaseLength,
              -LowerArmLength,
              LowerJointHeight);
   RotateAroundZ(LowerJoints[3], LowerJoints[1],  120);
   RotateAroundZ(LowerJoints[5], LowerJoints[1], -120);

   // 拷贝到逆向和正弦运动学计算中
   SetJointCoordinates(UpperJoints, LowerJoints);
}
//---------------------------------------------------------------------------
void CRobotBasic::RotateAroundZ(double Rst[3], double Src[3], double Angle)
{
   double Deg = Angle * M_PI / 180.0;
   double M[3][3] = {cos(Deg), -sin(Deg), 0,
                     sin(Deg),  cos(Deg), 0,
                     0,         0,        1
                    };

   MatrixMultiVector(Rst, M, Src);
}
//---------------------------------------------------------------------------
void CRobotBasic::SetStructureErrors(double  ErrJointUpper[6][3],
                                     double  ErrJointLower[6][3])
{
   for(int i = 0; i < 6; ++i)
   {
      VectorAddVector(UpperJointInUpperCoordinate[i], UpperJointInUpperCoordinate[i], ErrJointUpper[i]);
      VectorAddVector(LowerJointInLowerCoordinate[i], LowerJointInLowerCoordinate[i], ErrJointLower[i]);
   }
}
