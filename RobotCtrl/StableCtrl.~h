//---------------------------------------------------------------------------

#ifndef StableCtrlH
#define StableCtrlH
#include "AccSensor.h"
#include "MotionSimu.h"
//---------------------------------------------------------------------------
class CStableCtrl
{
private:
   double SingleChannelFwdBwdCtrl(int Chan, double AccFwd, double AccBwd);
   double SingleMotionChannelCtrl(int Chan, double AccFwd, double AccBwd);
public:
   CAccSensor AccFdkFwd;     // 前馈控制加计
   CAccSensor AccFdkBwd;     // 反馈控制加计
public:
   CFilterAcc2Motion Acc2Motion[3];         // 由加速度计算位移量
public:
   double FwdCtrlAmp[6];     // 前馈控制增益
public:
   CStableCtrl(void);
public:
   void GetPlatformPosition(double &X, double &Y, double &Z, double &Yaw, double &Pitch, double &Roll);
};
#endif
