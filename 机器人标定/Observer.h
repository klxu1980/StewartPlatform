//---------------------------------------------------------------------------

#ifndef ObserverH
#define ObserverH
//---------------------------------------------------------------------------
class CObserver
{
public:
   // 观测仪器以机器人坐标系为参考的中心点坐标和姿态欧拉角
   double MeterPos[3];
   double MeterEuler[3];
   double ErrPos[3];
   double ErrEuler[3];
public:
   CObserver(void);
public:
   void PointFromRobotToObserver(double Rst[][3], double Src[][3], int Count);
   void PointFromObserverToRobot(double Rst[][3], double Src[][3], int Count);
public:
   void CalcPosEuler(double M1[3], double M2[3], double M3[3], double Pos[3], double Euler[3]);
};
#endif
