//---------------------------------------------------------------------------

#ifndef CubicTraceH
#define CubicTraceH
//---------------------------------------------------------------------------
class CCubicTrace
{
public:
   double a[4];    // ���ζ���ʽϵ��
   double MaxS;    // ��������ٶ�
   double MaxA;    // ���������ٶ�
   double DecayK;  // �ٶ�˥��ϵ��
private:
   double Max(double a, double b){return (a > b)? a : b;}
   void   Swap(float &a, float &b){float c = a; a = b; b = c;}
public:
   CCubicTrace(void);
public:
   bool   Refresh(float T, float x0, float v0, float x1, float v1);
   void   SetZero(void);
   void   Stop(void);
   void   Decay(void);
public:
   float  Position(float t);
   float  Speed(float t);
   float  MaxSpeed(float T);
   float  MaxAcc(float T);
};

class CMoveTrace
{
public:
   double       MoveTime;      // ��ɹ켣����ʱ��
   CCubicTrace  Trace[6];      // �������ɶȵĹ켣
public:
   void  Reset(void);
   void  Stop(void);
   void  Decay(void);
   bool  Schedule(float T, float Start[6], float VStart[6], float End[6], float VEnd[6]);
   void  Schedule(float Start[6], float VStart[6], float End[6], float VEnd[6]);
   void  Position(float t, float PosEuler[6]);
   void  Speed(float t, float Speed[6]);
};
#endif
