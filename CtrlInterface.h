#ifndef CtrlInterfaceH
#define CtrlInterfaceH

extern void  RobotCtrl(void);                                    // ÿ��FPGAӲ���ж�ʱ���øú�����ʵ�ֻ����˿���
extern int   RcvByteFromUART2(unsigned char Byte);
extern int   RcvByteFromUART3(unsigned char Byte);
extern int   FdkForUART2(unsigned char **Fdk, int *FdkLength);
extern int   FdkForUART3(unsigned char **Fdk, int *FdkLength);

#endif