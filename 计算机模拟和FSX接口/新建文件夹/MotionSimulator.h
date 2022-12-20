//---------------------------------------------------------------------------

#ifndef MotionSimulatorH
#define MotionSimulatorH
#ifdef __BORLANDC__
#include <Classes.hpp>
#include <DateUtils.hpp>
#endif

#define   MOTION_RESUMED     true
//---------------------------------------------------------------------------
// Motion simulator���ڽ��ɻ�6����̬�����ļ��ٶ�ת��Ϊ������������ƽ̨λ��
//---------------------------------------------------------------------------
// ���׸�ͨ�˲���
//---------------------------------------------------------------------------
class CFilter2ndHighPass
{
private:
   int    __XiCnt;    // ��������
   double __Xi[3];    // ����
   double __Xh[3];    // ���
   double __K1;
   double __K2;
   double __T;
public:
   CFilter2ndHighPass(void);
public:
   void   SetParams(double amax, double vmax, double xmax);
   void   Initialize(double Xi);      // ��ʼ���˲�������__Xi����ʼ��ΪXi����__Xh��ʼ��Ϊ0���Ӷ�����0ʱ�̳��ִ�������
   double Output(double Xi);
};
//---------------------------------------------------------------------------
// ���׵�ͨ�˲���
//---------------------------------------------------------------------------
class CFilter2ndLowPass
{
private:
   double __Xh[3];    // ���
   double __Amax;     // �����ٶ�
   double __K1;       // λ�û�����ϵ����K1 = amax / xmax������xmax������г�(��λm)
   double __K2;       // �ٶȻ�����ϵ����K2 = amax / vmax������vmax������ٶ�(��λm/s)
   double __T;        // ����ʱ��
   double __Tsqr;     // ����ʱ��ƽ��
public:
   CFilter2ndLowPass(void);
public:
   void   SetParams(double T, double amax, double vmax, double xmax);
   double Output(double Acc);
};
//---------------------------------------------------------------------------
// CMotionSimulator
//---------------------------------------------------------------------------
class CMotionSimulator
{
private:
   double            __Acc[6];
   CFilter2ndLowPass __AccFilter[6];    // ���ٶ��˲���
#ifdef __BORLANDC__
   TDateTime         __LstSampleTime;
#endif
private:
   bool SampleOutputTime(void);
public:
   CMotionSimulator(void);
public:
   CFilter2ndLowPass& FilterX(void)    {return __AccFilter[0];}
   CFilter2ndLowPass& FilterY(void)    {return __AccFilter[1];}
   CFilter2ndLowPass& FilterZ(void)    {return __AccFilter[2];}
   CFilter2ndLowPass& FilterYaw(void)  {return __AccFilter[3];}
   CFilter2ndLowPass& FilterPitch(void){return __AccFilter[4];}
   CFilter2ndLowPass& FilterRoll(void) {return __AccFilter[5];}
public:
   void FeedTargetAcc(double AccX, double AccY, double AccZ, double AccYaw, double AccPitch, double AccRoll);
   void GetPlatformPosition(double &X, double &Y, double &Z, double &Yaw, double &Pitch, double &Roll);
};
#endif
 