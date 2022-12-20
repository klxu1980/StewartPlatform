//---------------------------------------------------------------------------


#pragma hdrstop

#include "Calibrator.h"
#include <Classes.hpp>
#include <math.h>
#include <values.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CCalibrator::CCalibrator(void)
 : DefaultRobotErr(0.005),
   DefaultObserverTErr(0.01),
   DefaultObserverRErr(10),
   MaxRobotErr(0.005),
   NormRate(1)
{
   Clear();
}
//---------------------------------------------------------------------------
void CCalibrator::AddCaliData(double M1[3], double M2[3], double M3[3], double Jack[6])
{
   CCaliData Data;
   CopyVector(Data.M1, M1);
   CopyVector(Data.M2, M2);
   CopyVector(Data.M3, M3);

   for(int i = 0; i < 6; ++i)
      Data.Jack[i] = Jack[i];

   CaliDatas.push_back(Data);
}
//---------------------------------------------------------------------------
void CCalibrator::AddCaliData(double Pos[3], double Euler[3], double Jack[6])
{
   CCaliData Data;
   CopyVector(Data.Pos, Pos);
   CopyVector(Data.Euler, Euler);

   for(int i = 0; i < 6; ++i)
      Data.Jack[i] = Jack[i];

   CaliDatas.push_back(Data);
}
//---------------------------------------------------------------------------
int CCalibrator::CopySolutionToRobot(const double *x, CRobot &Robot)
{
   int ErrCnt = 0;

   // xΪ���궨�����
   // ��ƽ̨�½ӵ�����18��
   for(int i = 0; i < 6; ++i)
   {
      Robot.ErrJointUpper[i][0] = x[i * 3];
      Robot.ErrJointUpper[i][1] = x[i * 3 + 1];
      Robot.ErrJointUpper[i][2] = x[i * 3 + 2];
   }
   ErrCnt += 3 * 6;

   // ��ƽ̨�½ӵ�����18��
   if(!IgnoreLowerErr)
   {
      for(int i = 0; i < 6; ++i)
      {
         Robot.ErrJointLower[i][0] = x[i * 3 + ErrCnt];
         Robot.ErrJointLower[i][1] = x[i * 3 + 1 + ErrCnt];
         Robot.ErrJointLower[i][2] = x[i * 3 + 2 + ErrCnt];
      }
      ErrCnt += 3 * 6;
   }

   // ����������6��
   if(!IgnoreJackErr)
   {
      for(int i = 0; i < 6; ++i)
         Robot.ErrJackFixedLen[i] = x[i + ErrCnt];
      ErrCnt += 6;
   }
   
   Robot.InitStructureParams();

   return ErrCnt;
}
//---------------------------------------------------------------------------
int CCalibrator::CopySolutionToObserver(const double *x, CObserver &Observer)
{
   if(!IgnoreObserver)
   {
      Observer.ErrPos[0] = x[0];
      Observer.ErrPos[1] = x[1];
      Observer.ErrPos[2] = x[2];

      Observer.ErrEuler[0] = x[3];
      Observer.ErrEuler[1] = x[4];
      Observer.ErrEuler[2] = x[5];

      return 6;
   }
   else
      return 0;
}
//---------------------------------------------------------------------------
DP CCalibrator::CostFunction(const double *x)
{
   // ���û����˱������͹۲����
   int RobotErrCnt = CopySolutionToRobot(x, Robot);
   int ObsveErrCnt = CopySolutionToObserver(x + RobotErrCnt, Observer);

   // ���������ʵ�����
   double RobotError = 0;
   for(unsigned int i = 0; i < CaliDatas.size(); ++i)
   {
      // �ɹ۲����ݼ�����ƽ̨λ��
      double Pos[3], Euler[3];
      Observer.CalcPosEuler(CaliDatas[i].M1, CaliDatas[i].M2, CaliDatas[i].M3, Pos, Euler);

      // ��λ�˼�����
      Robot.PlatformMove(Pos[0], Pos[1], Pos[2], Euler[0], Euler[1], Euler[2], false);

      // ���㲢�ۻ�������
      for(int m = 0; m < 6; ++m)
      {
         double e = Robot.Jack[m].Servo - CaliDatas[i].Jack[m];
         //RobotError += e * e;
         RobotError += fabs(e);
      }
   }
   RobotError = sqrt(RobotError / CaliDatas.size());
   MinError = min(MinError, RobotError);

   // �������޳ͷ�
   double ParamError = 0;
   for(int i = 0; i < RobotErrCnt; ++i)
   {
      double Delta = max(0.0, fabs(x[i]) - MaxRobotErr);
      ParamError = max(ParamError, Delta); //Delta * Delta;
   }
   if(!IgnoreObserver)
   {
      for(int i = 0; i < 3; ++i)
      {
         double Delta = max(0, fabs(x[i + RobotErrCnt]) - MaxObserverTErr);
         ParamError += Delta * Delta;
      }
      for(int i = 0; i < 3; ++i)
      {
         double Delta = max(0, fabs(x[i + RobotErrCnt + 3]) - MaxObserverRErr);
         ParamError += Delta * Delta;
      }
   }
   //ParamError = sqrt(ParamError / (RobotErrCnt + ObsveErrCnt));

   // ����ƽ�����
   return RobotError + NormRate * ParamError;
}
//---------------------------------------------------------------------------
bool CCalibrator::Calibrate(int MaxIterCnt)
{
   int RobotErrCnt = 42;
   if(IgnoreLowerErr)
      RobotErrCnt -= 3 * 6;
   if(IgnoreJackErr)
      RobotErrCnt -= 6;

   int ObseErrCnt = IgnoreObserver? 0 : 6;
   int ErrorCnt = RobotErrCnt + ObseErrCnt;
   
   // ��ʼ������
   double InitPoly[48 * 49];
   fill(InitPoly, InitPoly + 48 * 49, 0.0);

   // ��ʼ��������
   // �����˱������
   for(int r = 0; r < RobotErrCnt; ++r)
      InitPoly[(r + 1) * ErrorCnt + r] = DefaultRobotErr * (random(2)? -1 : 1);

   if(!IgnoreObserver)
   {
      for(int r = 0; r < 3; ++r)
         InitPoly[(r + RobotErrCnt + 1) * ErrorCnt + r + RobotErrCnt] = DefaultObserverTErr * (random(2)? -1 : 1);

      for(int r = 0; r < 3; ++r)
         InitPoly[(r + RobotErrCnt + 4) * ErrorCnt + r + RobotErrCnt + 3] = DefaultObserverRErr * (random(2)? -1 : 1);
   }

   // �Ż�����
   MinError = MAXFLOAT;
   bool Ok = Calc(InitPoly, ErrorCnt, Error, MaxIterCnt);

   // ��������д������˺͹۲��������
   CopySolutionToRobot(Error, Robot);
   CopySolutionToObserver(Error + RobotErrCnt, Observer);

   return Ok;
}
//---------------------------------------------------------------------------
void CCalibrator::Clear(void)
{
   for(int i = 0; i < 48; ++i)
      Error[i] = 0;

   CaliDatas.clear();
}
//---------------------------------------------------------------------------
void CCalibrator::ResetErrors(void)
{
   for(int i = 0; i < 48; ++i)
      Error[i] = 0;
}
