//---------------------------------------------------------------------------

#ifndef AccSensorH
#define AccSensorH
//---------------------------------------------------------------------------
class CAccSensor
{
private:
   unsigned char __Buffer[32];
   int  __BufSize;
   int  __CommCnt;
public:
   float MinAccX;
   float MinAccY;
   float MinAccZ;
public:
   float GravityX;
   float GravityY;
   float GravityZ;
public:
   float AccX;
   float AccY;
   float AccZ;
private:
	 short Buffer2Short(unsigned char *Buffer){return *((short*)Buffer);}
   float GetValue(unsigned char *Buffer, float Scale){return Buffer2Short(Buffer) * Scale / 0x1000;}
public:
   CAccSensor(void);
public:
   bool ReceiveValueByte(unsigned char Byte);
   float CommRate(float Time);
};
#endif
