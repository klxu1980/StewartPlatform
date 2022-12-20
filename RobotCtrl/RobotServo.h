//---------------------------------------------------------------------------

#ifndef RobotServoH
#define RobotServoH
#include "Robot.h"
#include "CtrlBoard.h"

#ifndef __BORLANDC__
#include "fsmc.h"
#endif
//---------------------------------------------------------------------------
// ע�⣺1. Ϊ�˷��㣬�ŷ����Ƴ����ڲ������ȵ�λͳһΪmm������ӿڣ���ͳһΪm��
//       2. �ŷ������в����˶�������Լ�����˶�����Լ�����ϲ�������ŷ�������λ���ر����˶������ޡ�
//       Ŀǰ��û�����ŷ�����ĩ��ʱ�ļ��ٿ��ƣ�����Ҫ����
//---------------------------------------------------------------------------
class CRobotServo
{
private:
   int     __MinPulse;               // һ�������������������˿����С�˶�����(������)�����ڸ���ֵ�����������Ϊ��
   int     __MaxPulse;               // һ�������������������˿������˶�����(������)
   bool    __Zeroing;                // ���ڹ���
private: public:
   int     __CurPosition[6];         // ÿ��ͨ���ĵ�ǰλ��
   int     __DstPosition[6];         // ÿ��ͨ����һ��������Ӧ���ﵽ��λ��
   int     __CalcPosition[6];        // ��������ÿ��ͨ����Ӧ���ﵽ��λ��
   bool    __Direction[6];           // �˶�����, true=������(��������)
   unsigned short __PulseCnt[6];     // ÿͨ���˶�����
private:
   int     __MaxAccByPulse;          // �����ٶ�(��������Ϊ��λ)
   double  __ServoRange[6];          // ʵ�����г�(��λm)
   int     __Positions[6][3];        // �ŷ���������������ڵ�λ�ã����ڼ��ٶ��޷�
private:
   int  FilterDestination(int Idx, int DstPosition);
private:
   void NormalCtrl(void);            // �����˶�����
   void GoZeroCtrl(void);            // ���Ƶ��������˶�(��CtrlSystem����)
public:
   CRobotServo(void);
public:
   void RobotMove(CRobot &Robot);            // ��ɻ����˵��˶�ѧ����󣬵��øú����������˳���
   void ServoCtrl(void);                                           // �����ŷ������ʵ�����������ÿ���������ڶ���Ҫ����
public:
   void GoZero(void){__Zeroing = true;}                            // Ҫ�������ŷ�����
   bool IsAllZeroed(void);                                         // ����Ƿ����е�׾��ѵ������(����λ����)
public:
   // �ŷ���׵�ʵ�ʳ���
   double ServoLength(int JackID){return __CurPosition[JackID] * SERVO_ROUND_MM * 0.001 / SERVO_PULSE_ROUND;}
};
#endif
