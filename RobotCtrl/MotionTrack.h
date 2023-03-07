//---------------------------------------------------------------------------

#ifndef MotionTrackH
#define MotionTrackH
#include "CubicTrace.h"

#ifdef __BORLANDC__
#include <Classes.hpp>
#include <DateUtils.hpp>
#endif
//---------------------------------------------------------------------------
class CMotionTracker
{
private:
   CMoveTrace  __Trace;
   float       __LstDst[6];
   float       __Start[6];
   float       __VStart[6];
   float       __End[6];
   float       __VEnd[6];
   double      __LstDstTime;
   bool        __NewDst;
private:
#ifdef __BORLANDC__
   TDateTime   __BeginTime;
#endif
public:
   float MoveTime;
   float MaxMoveTime;
   float PosEuler[6];   // ��������ÿ��ʱ�̵�λ����̬�����ײ��˶����Ƴ���ʹ��
private:
   double GetCurTime(void);
   void   Schedule(float Start[6], float VStart[6], float End[6], float VEnd[6]);
public:
   CMotionTracker(void);
public:
   void Initialize(double Pos[3], double Euler[3]);       // �����˳�ʼ����һ�����ڻ����˹��������
   void NewDestination(float PosEuler[6]);
   void Move(double Pos[3], double Euler[3]);
};
#endif
