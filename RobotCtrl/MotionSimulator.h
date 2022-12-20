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
// ���ٶȵ�ֱ���˶��˲���
//---------------------------------------------------------------------------
class CFilterAcc2Motion
{
private:
   double __Xh[3];    // ���
   double __Amax;     // �����ٶ�
   double __K1;       // λ�û�����ϵ����K1 = amax / xmax������xmax������г�(��λm)
   double __K2;       // �ٶȻ�����ϵ����K2 = amax / vmax������vmax������ٶ�(��λm/s)
   double __T;        // ����ʱ��
   double __Tsqr;     // ����ʱ��ƽ��
   double __InputAcc; // ������ٶ�
   double __RealAcc;  // ʵ��������ٶ�
public:
   CFilterAcc2Motion(void);
public:
   void   SetParams(double T, double amax, double vmax, double xmax);
   double Output(double Acc);
   double XValue(void){return __Xh[0];}
   double RealAcc(void){return __RealAcc;}
   double InputAcc(void){return __InputAcc;}
};
//---------------------------------------------------------------------------
// ���ٶȵ������˲���
//---------------------------------------------------------------------------
class CFilterAcc2Angle
{
private:
   CFilterAcc2Motion __Filter;
   double __Angle;
public:
   void   SetParams(double T, double amax, double omega_max);
   double Output(double Acc);
   double RealAcc(void);
   double InputAcc(void);
};
//---------------------------------------------------------------------------
// ���ٶȵ��Ƕ��˲���
//---------------------------------------------------------------------------
class CFilterRSpd2Angle
{
private:
   double __Xh[2];    // ����г�
   double __Vmax;     // ����ٶ�
   double __K;        // λ�û�����ϵ����K = vmax / xmax������xmax������г�(��λm)
   double __T;        // ����ʱ��
   double __InputV;   // �����ٶ�
   double __RealV;    // ʵ������ٶ�
public:
   CFilterRSpd2Angle(void);
public:
   void   SetParams(double T, double vmax, double xmax);
   double Output(double V);
   double XValue(void){return __Xh[0];}
   double RealSpd(void){return __RealV;}
   double InputSpd(void){return __InputV;}
};
//---------------------------------------------------------------------------
class CLowPassFilter
{
private:
   double __X[2];
   double __Y[2];
   double __b;
   double __a0;
   double __a1;
   double __a2;
   double __T;
public:
   CLowPassFilter(void);
public:
   void   SetParams(double T, double FreqThresh, double Damping);
   double Filter(double x);
};
//---------------------------------------------------------------------------
class CHighPassFilter
{
private:
   CLowPassFilter __LowPass;
public:
   void   SetParams(double T, double FreqThresh, double Damping);
   double Filter(double x);
};
//---------------------------------------------------------------------------
// CMotionSimulator
//---------------------------------------------------------------------------
class CMotionSimulator
{
private:
   double            __Input[6];        // ������ٶȺͽ��ٶ�
#ifdef __BORLANDC__
   TDateTime         __LstSampleTime;
#endif
public:
   CFilterAcc2Motion Acc2Motion[3];         // �ɼ��ٶȵ�λ��
   CFilterRSpd2Angle RSpd2Rotate[3];        // �ɽ��ٶȵ��Ƕ�
   CFilterAcc2Angle  Acc2Angle[2];          // �ɼ��ٶȵ��Ƕ�(Y������ٶȡ�X������ٶ�)
   CHighPassFilter   HighPassFilter[6];     // ���ٶȡ����ٶȸ�ͨ�˲���
   bool              HighPassEnabled[6];    // ʹ�ܸ�ͨ�˲���
private:
   bool SampleOutputTime(void);
public:
   CMotionSimulator(void);
public:
   void FeedTargetAcc(double AccX, double AccY, double AccZ, double SpdYaw, double SpdPitch, double SpdRoll);
   void GetPlatformPosition(double &X, double &Y, double &Z, double &Yaw, double &Pitch, double &Roll);
};
#endif
 