#ifndef  PlaneDataH
#define  PlaneDataH
//-----------------------------------------------------------------------------------
class CPlaneAcc
{
public:
	float AccX;  
	float AccY;
	float AccZ;
	float SpdYaw;
	float SpdPitch;
	float SpdRoll;
public:
	CPlaneAcc(void)
	 : AccX(0),
	   AccY(0),
	   AccZ(0),
	   SpdYaw(0),
	   SpdPitch(0),
	   SpdRoll(0)
	{}
};
#endif