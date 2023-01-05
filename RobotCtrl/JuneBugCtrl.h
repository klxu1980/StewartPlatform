//---------------------------------------------------------------------------

#ifndef JuneBugCtrlH
#define JuneBugCtrlH
#include "Robot.h"
#include "MotionSimu.h"
#include "CubicTrace.h"
//---------------------------------------------------------------------------
enum CBugState
{
   bsIdle,
   bsMoveUp,
   bsMoveDown,
   bsMoveUpDownIdle,
   bsMoveXYUpper,
   bsMoveXYLower,
   bsMoveXYIdleUpper,
   bsMoveXYIdleLower
};

class CJuneBugCtrl
{
private:
   CRobot         __Robot;             // 机器人运动学计算(用于迭代计算步长等)
   CBugState      __BugState;          // 机器人状态
   CMoveTrace     __Trace;
   float          __MaxMoveTime;       // 当前轨迹最大运动时间(s)，通过轨迹规划获得，机器人应当在该时间内完成当前轨迹
   float          __MoveTime;          // 当前轨迹已运动时间(s)，当__MoveTime >= __MaxMoveTime时，说明当前轨迹已完成
   float          __SpdInUse;          // 目前正在使用的速度(只有当机器人停止时，才能改变速度)
public:
   // 轨迹规划时的速度、加速度约束
   float MaxSpd[6];                    // x, y, z, yaw, pitch, roll最大速度，单位m/s或°/s
   float MaxAcc[6];                    // 每个轴的最大加速度
   float MaxJackSpd;                   // 伺服电缸的最大允许速度，单位mm/s
public:
   // 机器人的运动指令
   // 机器人有两种平面运动：平移运动和旋转运动
   float Dir;                           // 直线运动角度(单位deg)
   float Step;                         // 直线运动步长
   float Yaw;                          // 运动偏航角(单位deg)
   float XYHeight;                     // 运动平面高度(m)
   float Speed;                        // 运动相对速度([0, 1]之间)
public:
   float PosEuler[6];                  // 机器人在每个时刻的位置姿态，供底层运动控制程序使用
private:
   // 机器人的状态函数，机器人处于某一状态时，调用相应的状态函数
   // 在状态函数中，根据事件转移状态
   void  StateIdle(void);
   void  StateMoveUpDown(void);
   void  StateMoveUpDownIdle(void);
   void  StateMoveXY(void);
   void  StateMoveXYIdle(void);
private:
   float Square(float x) {return x * x;}
   float Length(float a, float b){return sqrt(a * a + b * b);}
   float Length(float a, float b, float c){return sqrt(a * a + b * b + c * c);}
   float Max(float a, float b){return (a > b)? a : b;}
   float SearchForTheLargestXYStep(float Z, float Dir, float Step, float Yaw);
   void  ScheduleMovement(float Start[6], float VStart[6], float End[6], float VEnd[6]);
   void  ScheduleMovement(float End[6], float VEnd[6]);
   void  ScheduleIdleMovement(void);
   void  ScheduleXYMovement(float XYHeight, float Dir, float Step, float Yaw);
   bool  CheckJackOverSpeed(CMoveTrace &Trace, float Interval=0.1);
private:
   bool  MoveRequired(void);
   void  MoveByTrace(void);
public:
   CJuneBugCtrl(void);
public:
   void Initialize(void);       // 机器人初始化，一般用于机器人归零结束后
   void Move(void);             // 机器人运动控制，每个控制周期调用一次该函数，计算机器人的位姿
};
#endif
