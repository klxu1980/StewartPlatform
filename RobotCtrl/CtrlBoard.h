//---------------------------------------------------------------------------

#ifndef CtrlBoardH
#define CtrlBoardH
#include "GlobalDef.h"

#ifndef __BORLANDC__
#include "led.h"
#include "fsmc.h"
#endif
//---------------------------------------------------------------------------
class CCtrlBoard
{     
public:
   bool           DIUpper[6];             // ����λ��������
   bool           DILower[6];             // ����λ��������
   unsigned short PulseLeft[6];           // ÿ��ͨ����һ��������δ��ɵ���������
private:
#ifndef __BORLANDC__
   void WriteFreqDivBase(int Idx, int Base) {fpga_write(Idx, Base);}
   void WritePulseCnt(int Idx, int PulseCnt){fpga_write(Idx + 6, PulseCnt);}
   void WriteDirection(int Direction)       {fpga_write(12, Direction);}
#else
   void WriteFreqDivBase(int Idx, int Base) {}
   void WritePulseCnt(int Idx, int PulseCnt){}
   void WriteDirection(int Direction)       {}
#endif
public:
   CCtrlBoard(void);
public:
   void RefreshDIStatus(void);                // ����DI����
   void RefreshPulseLeft(void);               // ����ǰ���������ʣ��������
   void OutputPulse(int Chan, int Pulse);     // �������
   void OutputDirection(bool Direction[6]);   // ����˶�����
   void OutputDirection(bool Direction);      // ����˶�����(6ͨ��ͬ����)
public:
	 bool RcvByteFromUART2(unsigned char Byte);               // ��UART2���յ�һ���ֽڣ�������յ�һ���������ģ��򷵻�true��ע�⣬Ӳ������Ӧ�����øú������ݽ��յ����ֽڡ�
   bool RcvByteFromUART3(unsigned char Byte);               // ͬ��
   bool FdkForUART2(unsigned char **pBuffer, int *size);    // ͨ��UART2����Ӧ���ģ������Ҫ����Ӧ����������true��
   bool FdkForUART3(unsigned char **pBuffer, int *size);    // ͬ��
};
extern CCtrlBoard CtrlBoard;
#endif

// ����ͨ�Ų�����Ҫ�Ľ�
