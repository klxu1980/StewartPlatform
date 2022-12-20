//---------------------------------------------------------------------------


#pragma hdrstop

#include "RobotAnalysis.h"
#include <math.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
double CalcMaxOrthogonalSpace(CRobot &Robot, double AxisRatio[6], double Z0)
{
   double L1 = 0;
   double L2 = 1;

   // 先找出L1，L2的初始值，令L1
   while(true)
   {
      double PosEurlar[6];
      for(int i = 0; i < 6; ++i)
         PosEurlar[i] = L2 * AxisRatio[i];

      Robot.PlatformMove(PosEurlar[0], PosEurlar[1], PosEurlar[2] + Z0,
                         PosEurlar[3], PosEurlar[4], PosEurlar[5]);
      if(Robot.MoveStatus == msOk)
      {
         L1  = L2;
         L2 *= 2;
      }
      else
         break;
   }
   
   // 找出最大值
   double L;
   while(fabs(L1 - L2) > 1E-6)
   {
      L = (L1 + L2) * 0.5;

      double PosEurlar[6];
      for(int i = 0; i < 6; ++i)
         PosEurlar[i] = L * AxisRatio[i];

      Robot.PlatformMove(PosEurlar[0], PosEurlar[1], PosEurlar[2] + Z0,
                         PosEurlar[3], PosEurlar[4], PosEurlar[5]);
      if(Robot.MoveStatus == msOk)
         L1 = L;
      else
         L2 = L;
   }

   return L;
}
