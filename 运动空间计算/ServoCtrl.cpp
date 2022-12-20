//---------------------------------------------------------------------------


#pragma hdrstop

#include "ServoCtrl.h"
#include <Forms.hpp>
//---------------------------------------------------------------------------
#define  MM_TO_PULSE   2500.0
#define  MM_TO_ROUND   0.25     // �ŷ�ת��һ����Ҫ10000���壬����˶�1mm��Ҫ2500���壬����ŷ�ת��һ�ܵ���˶�4mm
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
// CServoCtrl()
//---------------------------------------------------------------------------
CServoCtrl::CServoCtrl(int ServoAddr, AnsiString Comm)
        : __hComm(NULL),
          __ServoAddr(ServoAddr),
          __NxtSegment(1)
{
   // ��ʼ������
   __hComm = CreateFile(Comm.c_str(),                   //�򿪴���
                        GENERIC_READ | GENERIC_WRITE,   //��д��ʽ
                        0,                              //���ܹ���
                        NULL,                           //���ð�ȫ�ṹ
                        OPEN_EXISTING,                  //���Ѵ��ڵ��豸
                        FILE_FLAG_WRITE_THROUGH,        //ͬ����ʽ
                        0);                             //��ģ��

   if((unsigned long)__hComm == 0xFFFFFFFF)
   {
      Application->MessageBox(("�޷��򿪴���" + Comm).c_str(), "����", MB_OK | MB_ICONERROR);
      return;
   }

   //���ô�������
   DCB CommDCB;
   if(GetCommState(__hComm, &CommDCB))
   {
      CommDCB.BaudRate = 115200;
      CommDCB.ByteSize = 8;
      CommDCB.Parity   = 2;
      CommDCB.StopBits = 0;
      
      if(!SetCommState(__hComm, &CommDCB))
         throw Exception("���ô������Դ���!");
   }
   else
      throw Exception("��ȡ�������Դ���!");

   //���ó�ʱ
   COMMTIMEOUTS CommTimeouts;
   GetCommTimeouts(__hComm, &CommTimeouts);
   CommTimeouts.ReadIntervalTimeout        = MAXDWORD;
   CommTimeouts.ReadTotalTimeoutMultiplier = 0;
   CommTimeouts.ReadTotalTimeoutConstant   = 0;
   SetCommTimeouts(__hComm, &CommTimeouts);
}
//--------------------------------------------------------------------------
// CalcCRC()
//--------------------------------------------------------------------------
WORD CServoCtrl::CalcCRC(BYTE *Buffer, int Count)
{
   WORD CRC = 0xFFFF;

   for(int i = 0; i < Count; ++i)
   {
      CRC ^= WORD(BYTE(Buffer[i]));

      for(int j = 0; j < 8; ++j)
      {
         if(CRC & 1)
         {
            CRC >>= 1;
            CRC  ^= 0xA001;
         }
         else
         {
            CRC >>= 1;
         }
      }
   }
   return CRC;
}
//--------------------------------------------------------------------------
// CheckCRC()
//--------------------------------------------------------------------------
bool CServoCtrl::CheckCRC(BYTE *Buffer, int RxCnt)
{
   WORD CRC = (Buffer[RxCnt - 1] << 8) | Buffer[RxCnt - 2];
   return CalcCRC(Buffer, RxCnt - 2) == CRC;
}
//--------------------------------------------------------------------------
// AppendCRC()
//--------------------------------------------------------------------------
void CServoCtrl::AppendCRC(BYTE *Buffer, int TxCnt)
{
   // ע�⣺CRC�ǵ��ֽ���ǰ�����ֽ��ں�
   WORD CRC = CalcCRC(Buffer, TxCnt);
   Buffer[TxCnt]     = CRC;
   Buffer[TxCnt + 1] = CRC >> 8;
}
//---------------------------------------------------------------------------
// ReadServoFdk()
//---------------------------------------------------------------------------
void CServoCtrl::ReadServoFdk(BYTE *FdkBuffer, int &FdkCnt)
{
   BYTE Buffer[16];
   DWORD RecCount;
   if(ReadFile(__hComm,          // �� CreateFile ��õ��ļ����
               Buffer,           // ���뻺������ַ
               16,               // �趨�����ֽ���
               &RecCount,        // ʵ�ʶ����ֽ���
               NULL))            // �ص�������ʽ���ݽṹ��ַ
   {
      memcpy(FdkBuffer + FdkCnt, Buffer, RecCount);
      FdkCnt += RecCount;
   }
}
//---------------------------------------------------------------------------
// WriteMultiWords()
//---------------------------------------------------------------------------
bool CServoCtrl::WriteMultiWords(int Addr, WORD *Values, int WordCnt)
{
   // ModbusRTUָ��
   BYTE Order[280] = {__ServoAddr, 0x10, Addr >> 8, Addr, WordCnt >> 8, WordCnt, WordCnt * 2};

   // ��д���ֵ
   for(int i = 0; i < WordCnt; ++i)
   {
      Order[7 + i * 2] = Values[i] >> 8;
      Order[8 + i * 2] = Values[i];
   }

   // CRCУ��
   AppendCRC(Order, 7 + WordCnt * 2);

   // �´�ָ��
   DWORD Size;
   WriteFile(__hComm, Order, 15, &Size, NULL);

   // �ȴ�Ӧ��
   int  FdkCnt = 0;
   BYTE FdkBuffer[16];
   for(int i = 0; i < 10; ++i)
   {
      // ������Ӧ��
      Sleep(10);
      ReadServoFdk(FdkBuffer, FdkCnt);

      // ����յ�Ӧ���ֽ���Ϊ8���ϣ�����Ӧ���Ƿ���ȷ
      if(FdkCnt >= 8)
         return CheckCRC(FdkBuffer, FdkCnt) && memcmp(Order, FdkBuffer, 6) == 0;
   }
   return false;
}
//---------------------------------------------------------------------------
// ReadMultiWords()
//---------------------------------------------------------------------------
bool CServoCtrl::ReadMultiWords(int Addr, WORD *Values, int WordCnt)
{
   // ����ָ��
   BYTE Order[8] = {__ServoAddr, 0x04, Addr >> 8, Addr, WordCnt >> 8, WordCnt};
   AppendCRC(Order, 6);

   // �´�ָ��
   DWORD Size;
   WriteFile(__hComm, Order, 15, &Size, NULL);

   // �ȴ�Ӧ��
   int  FdkCnt = 0;
   BYTE FdkBuffer[280];
   for(int i = 0; i < 10; ++i)
   {
      // ������Ӧ��
      Sleep(10);
      ReadServoFdk(FdkBuffer, FdkCnt);

      // ����յ�Ӧ���ֽ���Ϊ3���ϣ�����Ӧ���ַ
      if(FdkCnt >= 3 && (FdkBuffer[0] != __ServoAddr || FdkBuffer[1] != 0x04 || FdkBuffer[2] != WordCnt * 2) )
         return false;

      // �յ�����Ӧ����CRCУ����ȷ�����������
      if(FdkCnt >= WordCnt * 2 + 5 && CheckCRC(FdkBuffer, WordCnt * 2 + 5) )
      {
         for(int i = 0; i < WordCnt; ++i)
            Values[i] = (FdkBuffer[3 + i * 2] << 8) | FdkBuffer[4 + i * 2];

         return true;
      }
   }
   return false;
}
//---------------------------------------------------------------------------
// SendIncToSegment()
// ���˶�����д���ŷ�������ָ��segment��
// ������λΪm
// �ٶȵ�λΪm/s
//---------------------------------------------------------------------------
void CServoCtrl::SendIncToSegment(int Segment, float Step, float Speed)
{
   // �����˶��������ٶ�
   int ServoPulse = Step  * 1000.0 * MM_TO_PULSE + 0.5;        // ��������
   int ServoSpeed = Speed * 1000.0 * MM_TO_ROUND * 10 + 0.5;   // �ٶȵ�λΪ0.1rpm

   // �ۼ�����������С��0
   if(__PulseCnt + ServoPulse < 0)
      ServoPulse = -__PulseCnt;
   __PulseCnt += ServoPulse;

   // �ŷ������������������������������
   ServoPulse = -ServoPulse;

   // �ٶȲ���С��0.1rpm
   if(ServoSpeed < 1)
      ServoSpeed = 1;

   int PulseHigh = ServoPulse / 10000;
   int PulseLow  = ServoPulse % 10000;
   WORD Values[3] = {PulseLow, PulseHigh, ServoSpeed};

   // �´�ָ��    �Ĵ����׵�ַ��Ҫȷ��
   WriteMultiWords(0, Values, 3);
}
//---------------------------------------------------------------------------
// SendSegmentID()
//---------------------------------------------------------------------------
void CServoCtrl::SendSegmentID(int Segment)
{
   WORD Value = Segment;
   WriteMultiWords(0x2209, &Value, 1);
}
//---------------------------------------------------------------------------
// SendIncrement()
// ������λΪmm
// �ٶȵ�λΪmm/s
//---------------------------------------------------------------------------
void CServoCtrl::SendIncrement(float Step, float Speed)
{
   SendIncToSegment(__NxtSegment, Step, Speed);
}
//--------------------------------------------------------------------------
// ReadServo()
//--------------------------------------------------------------------------
bool CServoCtrl::ReadServo(void)
{   
}
//----------------------------------------------------------------------------
// Move()
//----------------------------------------------------------------------------
void CServoCtrl::Move(void)
{
   SendSegmentID(__NxtSegment);
   //__NxtSegment = __NxtSegment % 2 + 1;
   __NxtSegment = 1;
}
//---------------------------------------------------------------------------
// Zero()
//---------------------------------------------------------------------------
void CServoCtrl::Zero(void)
{
   __PulseCnt = 0;
}
//---------------------------------------------------------------------------
// CurLength()
//---------------------------------------------------------------------------
float CServoCtrl::CurLength(void)
{
   return __PulseCnt * 0.001 / MM_TO_PULSE;
}

