//---------------------------------------------------------------------------


#pragma hdrstop

#include "StableCtrl.h"
#include "GlobalDef.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CStableCtrl::CStableCtrl(void)
{
   FwdCtrlAmp[0] = 1.0;
   FwdCtrlAmp[1] = 1.0;
   FwdCtrlAmp[2] = 1.0;
   FwdCtrlAmp[3] = 1.0;
   FwdCtrlAmp[4] = 1.0;
   FwdCtrlAmp[5] = 1.0;

   Acc2Motion[0].SetParams(CTRL_INTERVAL, MAX_LINEAR_ACC, MAX_SPEED_X, MAX_RANGE_X);
   Acc2Motion[1].SetParams(CTRL_INTERVAL, MAX_LINEAR_ACC, MAX_SPEED_Y, MAX_RANGE_Z);
   Acc2Motion[2].SetParams(CTRL_INTERVAL, MAX_LINEAR_ACC, MAX_SPEED_Y, MAX_RANGE_Z);
}
//---------------------------------------------------------------------------
double CStableCtrl::SingleChannelFwdBwdCtrl(int Chan, double AccFwd, double AccBwd)
{
   double Acc = 0;

   // 前馈控制
   Acc -= AccFwd * FwdCtrlAmp[Chan];

   // 反馈控制

   return Acc;
}
//---------------------------------------------------------------------------
double CStableCtrl::SingleMotionChannelCtrl(int Chan, double AccFwd, double AccBwd)
{
   double Acc = SingleChannelFwdBwdCtrl(Chan, AccFwd, AccBwd);

   // 控制输出限幅
   return Acc2Motion[Chan].Output(Acc);
}
//---------------------------------------------------------------------------
void CStableCtrl::GetPlatformPosition(double &X, double &Y, double &Z, double &Yaw, double &Pitch, double &Roll)
{
   X = SingleMotionChannelCtrl(0, AccFdkFwd.AccX, 0);
   Y = SingleMotionChannelCtrl(1, AccFdkFwd.AccY, 0);
   Z = SingleMotionChannelCtrl(2, AccFdkFwd.AccZ, 0);

   Yaw = 0;
   Pitch = 0;
   Roll = 0;
}
