#ifndef CtrlInterfaceH
#define CtrlInterfaceH

extern void  RobotCtrl(void);                                    // 每次FPGA硬件中断时调用该函数，实现机器人控制
extern int   RcvByteFromUART2(unsigned char Byte);
extern int   RcvByteFromUART3(unsigned char Byte);
extern int   FdkForUART2(unsigned char **Fdk, int *FdkLength);
extern int   FdkForUART3(unsigned char **Fdk, int *FdkLength);

#endif