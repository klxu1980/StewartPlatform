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
   // 计算上平台铰接点坐标
   CalcGlobalCoordination(Pos, Eurlar, UpperJointInUpperCoordinate, UpperJointInLowerCoordinate, 6);

   // 计算连杆长度
   double Length[6];
   CalcJackLength(Length);

   // 计算误差
   double Diff = 0.0;
   for(int i = 0; i < 6; ++i)
      Diff += (JackLength[i] - Length[i]) * (JackLength[i] - Length[i]);

   // 增加迭代次数
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
   // 使用机器人运动空间的中心位置作为计算初始解
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
   // 使用机器人前次位姿作为计算初始解
   else
   {
      // 使用给定位姿作为初始解
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

   // 开始时曾经担心个别情况下单纯形法无法收敛，实测发现没有这个问题
   // 拷贝计算结果
   UpperPos[0]   = Opt[0];
   UpperPos[1]   = Opt[1];
   UpperPos[2]   = Opt[2];
   UpperEuler[0] = Opt[3];
   UpperEuler[1] = Opt[4];
   UpperEuler[2] = Opt[5];

   // 计算上平台铰接点在下平台坐标系中的坐标
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
