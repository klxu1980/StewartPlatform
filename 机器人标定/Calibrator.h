//---------------------------------------------------------------------------

#ifndef CalibratorH
#define CalibratorH
#include "SimplexOptimizer.h"
#include "Robot.h"
#include "Observer.h"
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
class CCalibrator : public CSimplexOptimizer
{
public:
   CRobot    Robot;             // ������
   CObserver Observer;          // �۲���
   double    Error[48];         // ���еı궨���(ÿ�����˽�3����װ��
                                // ÿ����׵�����λ����1������˱�����3*12 + 6 = 42����
                                // �ټӹ۲����6����)
   bool      IgnoreJackErr;     // �����������
   bool      IgnoreLowerErr;    // ������ƽ̨�½ӵ����
   bool      IgnoreObserver;    // ���Թ۲������
public:
   double    MinError;          // ��С���(���ƽ���������)
public:
   double    DefaultRobotErr;       // ���������ȱʡֵ(�����ʼ��ʹ��)
   double    DefaultObserverTErr;   // �۲���ƽ�����ȱʡֵ
   double    DefaultObserverRErr;   // �۲���ת�����ȱʡֵ
public:
   double    MaxRobotErr;           // �������˱������(����궨����õ���ĳЩ�����̫��)
   double    MaxObserverTErr;
   double    MaxObserverRErr;
   double    NormRate;
private:
   DP   CostFunction(const double *x);
   int  CopySolutionToRobot(const double *x, CRobot &Robot);
   int  CopySolutionToObserver(const double *x, CObserver &Observer);
public:
   // ʵ�ʹ۲���
   struct CCaliData
   {
   public:
      // ��ƽ̨�۲�����ꡣ�۲����3�����㣬���ɵȱ������Ρ�
      double M1[3];
      double M2[3];
      double M3[3];
   public:
      // ��׸������ȡ�������������Ϊ������������������λ���ش��������
      // ��׵�ʵ�ʳ������������֮�������
      double Jack[6];
   public:
      double Pos[3];       // ע�⣺�����궨ʱ��ʹ�õ�λ����Ϣ��λ�˽����ڲ�����
      double Euler[3];
   };
   vector<CCaliData>  CaliDatas;
public:
   CCalibrator(void);
public:
   void   Clear(void);
   void   ResetErrors(void);                                                       // ������б궨���ݺͽ��
   void   AddCaliData(double M1[3], double M2[3], double M3[3], double Jack[6]);   // ��ӱ궨����(��ƽ̨�������͵�������)
   void   AddCaliData(double Pos[3], double Euler[3], double Jack[6]);             // ��ӱ궨����(��ƽ̨λ�˺͵�������)
   bool   Calibrate(int MaxIterCnt);                                               // �궨
   void   CopyToRobot(CRobot &Robot);                                              // ���궨���������������
   void   CopyToObserver(CObserver &Observer);                                     // ���궨����������۲���
};
#endif
