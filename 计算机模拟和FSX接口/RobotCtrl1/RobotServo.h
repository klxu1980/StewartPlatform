//---------------------------------------------------------------------------

#ifndef RobotServoH
#define RobotServoH
#include "Robot.h"

#ifndef __BORLANDC__
#include "fsmc.h"
#endif

#define  PULSE_FREQUENCY      1000000.0    // ����ԴƵ��
//---------------------------------------------------------------------------
class CRobotServo
{
private:
   int     __PulsePerRound;          // �ŷ����ת��һȦ����������
   double  __MMPerRound;             // �ŷ����ת��һȦ˿���˶�����(��λmm)
   double  __CtrlInterval;           // �������ڣ���λs
   double  __MinServoLength;         // ������С�г�λ��
   double  __MaxServoLength;         // ��������г�λ��
   int     __MinJackInc;             // һ�������������������˿������˶�����(�ѻ���Ϊ���������������������)
   int     __MaxJackInc;             // һ�������������������˿����С�˶����������ڸ�ֵʱ����������嵽���������Ա�����ת�ٹ��͡�
   bool    __Zeroed;                 // �ѹ��㡣����Ҫ��������������ֱ�������¶���λ���ء�
private:
   int __CurPosition[6];                // ÿ��ͨ���ĵ�ǰλ��
   int __DstPosition[6];                // ÿ��ͨ����һ��������Ӧ���ﵽ��λ��
   unsigned short int __PulseCnt[6];    // ÿͨ���˶�����
   unsigned short int __Direction;      // �˶�����
   unsigned short int __DivCnt[6];      // ÿͨ�������Ƶֵ
   unsigned short int __PulseLeft[6];   // ÿ��ͨ����һ��������δ��ɵ���������
private:
   int MM2Pulse(float MM){return MM * __PulsePerRound / __MMPerRound;}
   int CalcFreqDivBase(int Pulse){return PULSE_FREQUENCY * __CtrlInterval / Pulse + 0.5;}
private:
#ifndef __BORLANDC__
   unsigned short int ReadPulseLeft(int Idx)  {return fpga_read(i);}
   unsigned short int ReadLmtSwitchLower(void){return ~fpga_read(6);}
   void WriteFreqDivBase(int Idx, int Base) {fpga_write(Idx, Base);}
   void WritePulseCnt(int Idx, int PulseCnt){fpga_write(Idx + 6, PulseCnt);}
   void WriteDirection(int Direction)       {fpga_write(12, Direction);}
#else
   unsigned short int ReadPulseLeft(int Idx){return 0;}
   unsigned short int ReadLmtSwitchLower(void){return 0;}
   void WriteFreqDivBase(int Idx, int Base) {}
   void WritePulseCnt(int Idx, int PulseCnt){}
   void WriteDirection(int Direction)       {}
#endif
public:
   CRobotServo(void);
public:
   void SetServoCtrlInterval(float Interval);                      // �����ŷ���������(������Ӧ����FPGA�еĿ�������һ�£���λs)
   void SetServoTransParams(int PulsePerRound, float MMPerRound);  // �����ŷ���������(���ת��һȦ��������˿�ܵ���(��λmm))
   void SetServoSpeedLimit(float MinSpeed, float MaxSpeed);        // ���������ٶȷ�Χ(��С�ٶȺ�����ٶȣ���λmm/s)
   void SetJackLimit(float MinLength, float MaxLength);            // �������˵���С������г̣���λmm
public:
   void RobotMove(CRobot &Robot, bool NoLimit = false);            // �������˶�����ÿ�����������У���Ӧ�����øú���
   void ServoMove(void);
public:
   void GoZero(void);
   void GoZeroCtrl(void);                                          // ���Ƶ��������˶�(��CtrlSystem����)
   bool Zeroed(void);
public:
   void SetJackLength(int JackID, int JackLength, int JackSpeed);
   double JackLength(int JackID){return __CurPosition[JackID] * __MMPerRound * 0.001 / __PulsePerRound;} // ��λm
};
#endif
