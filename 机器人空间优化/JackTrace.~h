//---------------------------------------------------------------------------

#ifndef JackTraceH
#define JackTraceH
#include "CubicTrace.h"

#ifdef __BORLANDC__
#include <Classes.hpp>
#include <DateUtils.hpp>
#endif
//---------------------------------------------------------------------------
class CJackTrace
{
private:
   CMoveTrace    __Trace;               // 三次多项式轨迹计算器
   double        __InitJackLength[6];   // 电缸初始长度
   double        __LstJackLength[6];    // 前次电缸长度
   double        __NewJackLength[6];    // 新更新的电缸长度
   double        __LstJackTime;         // 前次电缸更新时间
   double        __NewJackTime;         // 新电缸更新时间
   bool          __NewJack;             // 电缸长度被更新
   unsigned int  __TimeCounter;         // 计时计数器


   float       __LstDst[6];
   float       __Start[6];
   float       __VStart[6];
   float       __End[6];
   float       __VEnd[6];


private:
#ifdef __BORLANDC__
   TDateTime   __BeginTime;
#endif
public:
   float MoveTime;
   float MaxMoveTime;
   float PosEuler[6];   // 机器人在每个时刻的位置姿态，供底层运动控制程序使用
private:
   double GetCurTime(void);
   void   Schedule(float Start[6], float VStart[6], float End[6], float VEnd[6]);
public:
   CJackTrace(void);
public:
   void Initialize(double JackLength[6]);    
   void NewJackLength(double Length[6]);
   void Move(float JackLength[6]);
};
#endif
