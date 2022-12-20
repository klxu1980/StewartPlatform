//---------------------------------------------------------------------------


#pragma hdrstop

#include "RobotFKP.h"

#ifdef __BORLANDC__
#include "Unit1.h"
#endif
//---------------------------------------------------------------------------

#pragma package(smart_init)
//--------------------------------------------------------------------------
#ifdef __BORLANDC__
CRobotFKP::CRobotFKP(void)
	: __Optimizer(*this)
{
}
#else
CRobotFKP::CRobotFKP(void)
{
}
#endif
//--------------------------------------------------------------------------
double CRobotFKP::ErrorFunc(double Pos[3], double Eurlar[3])
{
   // ������ƽ̨�½ӵ�����
   CalcGlobalCoordination(Pos, Eurlar, UpperJointInUpperCoordinate, UpperJointInLowerCoordinate, 6);

   // �������˳���
   double Length[6];
   CalcJackLength(Length);

   // �������
   double Diff = 0.0;
   for(int i = 0; i < 6; ++i)
      Diff += (JackLength[i] - Length[i]) * (JackLength[i] - Length[i]);

   // ���ӵ�������
   ++IterCount;

   return Diff;
}
//--------------------------------------------------------------------------
double CRobotFKP::ErrorFunc(const double PosGesture[6])
{
   double Pos[3]    = {PosGesture[0], PosGesture[1], PosGesture[2]};
   double Eurlar[3] = {PosGesture[3], PosGesture[4], PosGesture[5]};

   return ErrorFunc(Pos, Eurlar);
}
//---------------------------------------------------------------------------
// CalcPosEurlar()
//---------------------------------------------------------------------------
bool CRobotFKP::CalcPosEurlar(bool DefaultInit)
{              
#ifdef __BORLANDC__	
   // ʹ�û������˶��ռ������λ����Ϊ�����ʼ��
   bool   Rst;
   double Opt[6];
   if(DefaultInit)
   {
      double InitPoly[7 * 6] = {0.0, 0.0, DefaultZ,        0,  0,  0,
                                0.1, 0.0, DefaultZ,        0,  0,  0,
                                0.0, 0.1, DefaultZ,        0,  0,  0,
                                0.0, 0.0, DefaultZ + 0.1,  0,  0,  0,
                                0.0, 0.0, DefaultZ,       10,  0,  0,
                                0.0, 0.0, DefaultZ,        0, 10,  0,
                                0.0, 0.0, DefaultZ,        0,  0, 10};
      Rst = __Optimizer.Calc(InitPoly, 6, Opt);
   }
   // ʹ�û�����ǰ��λ����Ϊ�����ʼ��
   else
   {
      // ʹ�ø���λ����Ϊ��ʼ��
      double InitPoly[7 * 6] = {UpperPos[0], UpperPos[1], UpperPos[2], UpperEuler[0], UpperEuler[1], UpperEuler[2],
                                UpperPos[0] + 0.001, UpperPos[1], UpperPos[2], UpperEuler[0], UpperEuler[1], UpperEuler[2],
                                UpperPos[0], UpperPos[1] + 0.001, UpperPos[2], UpperEuler[0], UpperEuler[1], UpperEuler[2],
                                UpperPos[0], UpperPos[1], UpperPos[2] + 0.001, UpperEuler[0], UpperEuler[1], UpperEuler[2],
                                UpperPos[0], UpperPos[1], UpperPos[2], UpperEuler[0] + 0.1, UpperEuler[1], UpperEuler[2],
                                UpperPos[0], UpperPos[1], UpperPos[2], UpperEuler[0], UpperEuler[1] + 0.1, UpperEuler[2],
                                UpperPos[0], UpperPos[1], UpperPos[2], UpperEuler[0], UpperEuler[1], UpperEuler[2] + 0.1};
      Rst = __Optimizer.Calc(InitPoly, 6, Opt);
   }
   IterCount = __Optimizer.IterCnt;

   // ��ʼʱ�������ĸ�������µ����η��޷�������ʵ�ⷢ��û���������
   // ����������
   UpperPos[0]   = Opt[0];
   UpperPos[1]   = Opt[1];
   UpperPos[2]   = Opt[2];
   UpperEuler[0] = Opt[3];
   UpperEuler[1] = Opt[4];
   UpperEuler[2] = Opt[5];

   // ������ƽ̨�½ӵ�����ƽ̨����ϵ�е�����
   CalcGlobalCoordination(UpperPos, UpperEuler, UpperJointInUpperCoordinate, UpperJointInLowerCoordinate, 6);

   return Rst;
#endif
}
//---------------------------------------------------------------------------
// Move()
//---------------------------------------------------------------------------
bool CRobotFKP::Move(double JackLength1, double JackLength2, double JackLength3,
                     double JackLength4, double JackLength5, double JackLength6,
                     bool DefaultInit)
{
   CRobotFKP::JackLength[0] = JackLength1;
   CRobotFKP::JackLength[1] = JackLength2;
   CRobotFKP::JackLength[2] = JackLength3;
   CRobotFKP::JackLength[3] = JackLength4;
   CRobotFKP::JackLength[4] = JackLength5;
   CRobotFKP::JackLength[5] = JackLength6;

   CalcPosEurlar(DefaultInit);
}
