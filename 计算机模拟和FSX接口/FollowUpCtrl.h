//---------------------------------------------------------------------------

#ifndef FollowUpCtrlH
#define FollowUpCtrlH
#include "Robot.h"
#include "PositionPred.h"
//---------------------------------------------------------------------------
class CFollowupCtrl
{
private:
   CRobot           &__Robot;
   CPosPredict       __PosPredict;
private:
#ifdef __BORLANDC__
   TDateTime    __StartTime;
#endif
private:
   int          __NoSampleTimes;     // 没有收到采样数据次数
   int          __MaxNoSampleTimes;
   double       __Gamma;             // 位置衰减因子
private:
   double       __LstPosition[6];    // 前次位置
   double       __LstLinkLength[6];  // 前次连杆长度
   double       __LinkInc[6];        // 连杆控制增量
private:
   double GetCurTime(void);          // 获得当前时间(单位s)
   bool   CalcLinkIncrement(double X, double Y, double Z, double Yaw, double Pitch, double Roll, double Factor);
   int    MaxIncIndex(double Inc[6]);
   double MaxLinkInc(double Inc[6]);
public:
   CFollowupCtrl(CRobot &Robot);
public:
   void    NewPosition(double X, double Y, double Z,                     // 接收跟踪对象的最新位姿
                       double Yaw, double Pitch, double Roll);
   bool    CalcLinkIncrement(double MaxAllowedInc);   // 计算连杆控制增量
   CRobot &Robot(void){return __Robot;}
   double  LinkIncrement(int Idx){return __LinkInc[Idx];}
public:
   void    SynchronizeRobot(void);
};
#endif
