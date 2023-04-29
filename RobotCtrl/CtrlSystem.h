//---------------------------------------------------------------------------

#ifndef CtrlSystemH
#define CtrlSystemH
#include "Robot.h"
#include "MotionSimu.h"
#include "RobotServo.h"
#include "RobotComm.h"
#include "StableCtrl.h"
#include "JuneBugCtrl.h"
#include "MotionTrack.h"
//---------------------------------------------------------------------------
// ���ֿ���ָ�1. �����˸�λ������ƽ̨�½�������λ���أ�Ȼ���ٻ�����������λ��
//               2. ֱ�ӿ���ÿ�����˳���
//               3. ֱ�ӿ��ƻ�������ƽ̨λ��
//               4. �����˸���ģ�����˶�
//               5. �����˼��ڿ���
//               6. ��������˿���
//---------------------------------------------------------------------------
class CCtrlSystem
{
friend class CRobotCommPkg;
private:
   CRobot             __Robot;           // �������˶�ѧ����(����������)
   CMotionSimulator   __Simulator;       // �˶�ģ�����������ٶ��ź�ת��Ϊλ�úͽǶ�
   CStableCtrl        __StableCtrl;      // ���ڿ�����
   CJuneBugCtrl       __JuneBugCtrl;     // ��������˿�����
   CMotionTracker     __MotionTrack;     // ʵʱ�˶�����
   CRobotCommPkg      __CommPkg;         // ������ͨ�ű���
   #ifdef INC_SERVO
   CIncServo          __Servo;           // �������ŷ�������
   #endif
   #ifdef ROS_SERVO
   CROSServo          __Servo;
   #endif
private:    // ͨ��
   unsigned char      __FdkBytes[64];
   int                __FdkCnt;
private:
   int                __CtrlMode;           // ����ģʽ
   bool               __Resetted;           // �Ѹ�λ��־(ϵͳ�����ϵ��=false)
   bool               __AllJackZeroed;      // ���������Ѿ�����
   float              __CtrlInterval;       // �������ڣ���λs
private:    // ֱ��λ�˿�����ز�������
   //double             __CurPosEurlar[6];    // ��ʼ��̬
   //double             __DstPosEurlar[6];    // Ŀ��λ��
   //double             __TransSpeed;         // ֱ��λ�˿���ƽ���ٶ�(��λmm/s)
   //double             __RotateSpeed;        // ֱ��λ�˿���ת���ٶ�(��λ��/s)
   //double             __TransStep;
   //double             __RotateStep;
private:    // ֱ�ӵ�׿�����ز�������
   double             __DstJackSpeed[6];    // �趨����˶��ٶȣ���λ mm/s
   double             __DstJackServoLen[6]; // ���Ŀ�곤��(mm)
private:
   #ifndef __BORLANDC__
   unsigned int       __LedFlickCnt;
   #endif
private:
   void  Reset(void);                     // �����˸�λ
   void  ResetCtrl(void);                 // �����˸�λ����
   void  DirectJackCtrl(void);            // ������ֱ�ӵ�׿���
   void  DirectPosEurlarCtrl(void);       // ������ֱ��λ�˿���
   void  MotionSimuCtrl(void);            // �˶�ģ�����
   void  StableCtrl(void);                // ���ڿ���
   void  JuneBugCtrl(void);               // ��������˿���
   void  OnCtrlModeChanged(int CtrlMode); // ����ģʽ�����ı�
private:
   void  ExtractCtrlOrder(void);          // ���ݿ���ģʽ����ָ��
private:
   // ����λ�˽���(�Ժ�Ҫ����д)
   void  CalcDestination(double SrcX, double SrcY, double SrcZ,
                         double DstX, double DstY, double DstZ,
                         double &X,   double &Y,   double &Z,
                         double Step);
private:
   void LedFlick(void);
public:
   CCtrlSystem(void);
public:
   CRobot&           Robot(void)    {return __Robot;}
   CMotionSimulator& Simulator(void){return __Simulator;}
   CRobotServo&      Servo(void)    {return __Servo;}
public:
   void  Control(void);
   bool  RcvCommandByte(char Byte);
   bool  FdkBuffer(unsigned char **Fkd, int *FdkLength);
public:
   CStableCtrl& StableController(void){return __StableCtrl;}
};
extern CCtrlSystem CtrlSystem;
#endif
