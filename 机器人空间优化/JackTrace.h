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
   CMoveTrace    __Trace;               // ���ζ���ʽ�켣������
   double        __InitJackLength[6];   // ��׳�ʼ����
   double        __LstJackLength[6];    // ǰ�ε�׳���
   double        __NewJackLength[6];    // �¸��µĵ�׳���
   double        __LstJackTime;         // ǰ�ε�׸���ʱ��
   double        __NewJackTime;         // �µ�׸���ʱ��
   bool          __NewJack;             // ��׳��ȱ�����
   unsigned int  __TimeCounter;         // ��ʱ������


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
   float PosEuler[6];   // ��������ÿ��ʱ�̵�λ����̬�����ײ��˶����Ƴ���ʹ��
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
