#ifndef  PlaneDataH
#define  PlaneDataH
//-----------------------------------------------------------------------------------
class CPlaneAcc
{
public:
	float AccX;  
	float AccY;
	float AccZ;
	float AccYaw;  
	float AccPitch;
	float AccRoll;
public:
	CPlaneAcc(void)
	 : AccX(0),
	   AccY(0),
	   AccZ(0),
	   AccYaw(0),
	   AccPitch(0),
	   AccRoll(0)
	{}
};
#endif