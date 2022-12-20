//---------------------------------------------------------------------------

#ifndef CtrlSystemH
#define CtrlSystemH
#include "Robot.h"
#include "RobotSimu.h"
#include "MotionSimulator.h"
#include "RobotServo.h"
//---------------------------------------------------------------------------
// ���ֿ���ָ�1. �����˸�λ
//               2. ֱ�ӿ���ÿ�����˳���
//               3. ֱ�ӿ��ƻ�������ƽ̨λ��
//               4. �����˸���ģ�����˶�
//---------------------------------------------------------------------------
class CCtrlSystem
{
private:
   CRobot             __Robot;           // �������˶�ѧ����(����������)
   CMotionSimulator   __Simulator;       // �˶�ģ�����������ٶ��ź�ת��Ϊλ�úͽǶ�
   CRobotServo        __Servo;           // �������ŷ�������
   #ifdef __BORLANDC__
   CRobotSimu         __RobotSimu;       // ��������˶���
   #endif
private:
   char               __RcvedBytes[64];  // ͨ�Ž����ֽڻ���
   int                __RcvedCnt;
private:
   int                __CtrlMode;        // ����ģʽ
   int                __LstCtrlMode;     // ǰ�ο���ģʽ
   bool               __Resetted;        // �Ѹ�λ��־(ϵͳ�����ϵ��=false)
   float              __CentralZ;        // ����λ��Z������
   float              __CtrlInterval;    // �������ڣ���λs
private:    // ֱ��λ�˿�����ز�������
   double             __DstPosEurlar[6]; // Ŀ��λ��
   int                __MoveSpeed;       // ֱ��λ�˿���ƽ���ٶ�(��λmm/s)
   int                __RotateSpeed;     // ֱ��λ�˿���ת���ٶ�(��λ��/s)
private:    // ֱ�ӵ�׿�����ز�������
   double             __JackSpeed[6];    // �趨����˶��ٶȣ���λ mm/s
   double             __DstJackLength[6];// ���Ŀ�곤��(mm)
private:
   short  CalcCRC(char *Buffer, int Count);
   short  Bytes2Word(char *Buffer){return (unsigned char)Buffer[0] + ((unsigned char)Buffer[1] << 8);}
   short  ExtractData(char *Bytes);
   void   SendCommFdk(char CMD);
   void   RcvJackCtrlOrder(short Datas[6]);
   void   RcvCtrlOrder(char Order, short Datas[6]);
   double Rad2Angle(double Rad){return Rad * 180.0 / M_PI;}
private:
   void  Reset(void);                     // �����˸�λ
   void  ResettingCtrl(void);             // �����˸�λ����
   void  DirectJackCtrl(void);            // ������ֱ�ӵ�׿���
   void  DirectPosEurlarCtrl(void);       // ������ֱ��λ�˿���
   void  MotionSimuCtrl(void);            // �˶�ģ�����
   void  OnCtrlModeChanged(void);         // ����ģʽ�ı�
private:
   void  CalcDestination(double SrcX, double SrcY, double SrcZ,
                         double DstX, double DstY, double DstZ,
                         double &X,   double &Y,   double &Z,
                         double Speed, double Interval);
public:
   CCtrlSystem(void);
public:
   CRobot&           Robot(void)    {return __Robot;}
   CMotionSimulator& Simulator(void){return __Simulator;}
   CRobotServo&      Servo(void)    {return __Servo;}
   #ifdef __BORLANDC__
   CRobotSimu&       RobotSimu(void){return __RobotSimu;}
   #endif
public:
   void Control(void);
   void RcvCommByte(char Byte);
public:
   float RobotRangeFromCenter(double Dir[6]);
};
#endif
