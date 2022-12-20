#include "RobotCtrl\CtrlSystem.h"
#include "RobotCtrl\CtrlBoard.h"
//-------------------------------------------------
//CCtrlSystem CtrlSystem;
//-------------------------------------------------
extern "C" void RobotCtrl(void)
{
	CtrlSystem.Control();
}
//-------------------------------------------------
extern "C" int RcvByteFromUART3(unsigned char Byte)
{	
	return CtrlBoard.RcvByteFromUART3(Byte);
}
//-------------------------------------------------
extern "C" int RcvByteFromUART2(unsigned char Byte)
{
	return CtrlBoard.RcvByteFromUART2(Byte);
}
//-------------------------------------------------
extern "C" int FdkForUART2(unsigned char **Fdk, int *FdkLength)
{
	CtrlBoard.FdkForUART2(Fdk, FdkLength);
}
//-------------------------------------------------
extern "C" int FdkForUART3(unsigned char **Fdk, int *FdkLength)
{
	CtrlBoard.FdkForUART3(Fdk, FdkLength);
}