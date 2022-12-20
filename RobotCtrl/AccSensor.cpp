//---------------------------------------------------------------------------


#pragma hdrstop

#include "AccSensor.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CAccSensor::CAccSensor(void)
 : __BufSize(0),
   __CommCnt(0),
   GravityX(0),
   GravityY(0),
   GravityZ(0),
   AccX(0),
   AccY(0),
   AccZ(0),
   MinAccX(0.1),
   MinAccY(0.1),
   MinAccZ(0.1)
{
}
//---------------------------------------------------------------------------
bool CAccSensor::ReceiveValueByte(unsigned char Byte)
{
   if(!__BufSize && Byte != 0x55)
      return false;

   __Buffer[__BufSize++] = Byte;
   if(__BufSize < 11)
      return false;

   __BufSize = 0;

   // check sum
   int Sum = 0;
   for(int i = 0; i < 10; ++i)
      Sum += __Buffer[i];
   if((Sum & 0x0FF) != (__Buffer[10] & 0x0FF))
      return false;

   const double Alpha = 0.8;
   switch(__Buffer[1])
   {
   case 0x51:
   {
      float X = GetValue(__Buffer + 2, 16);// * 9.8;
      float Y = GetValue(__Buffer + 4, 16);// * 9.8;
      float Z = GetValue(__Buffer + 6, 16);// * 9.8;

      GravityX = GravityX * Alpha + X * (1.0 - Alpha);
      GravityY = GravityY * Alpha + Y * (1.0 - Alpha);
      GravityZ = GravityZ * Alpha + Z * (1.0 - Alpha);

      AccX = AccX * Alpha + (X - GravityX) * (1.0 - Alpha);
      AccY = AccY * Alpha + (Y - GravityY) * (1.0 - Alpha);
      AccZ = AccZ * Alpha + (Z - GravityZ) * (1.0 - Alpha);

      if(AccX < MinAccX)
         AccX = 0;
      if(AccY < MinAccY)
         AccY = 0;
      if(AccZ < MinAccZ)
         AccZ = 0;

      break;
   }
   case 0x52:
      break;
   }
   ++__CommCnt;
   return true;
}
//---------------------------------------------------------------------------
float CAccSensor::CommRate(float Time)
{
   float Rate = __CommCnt / Time;
   __CommCnt = 0;
   return Rate;
}
