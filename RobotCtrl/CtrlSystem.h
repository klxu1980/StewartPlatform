//---------------------------------------------------------------------------

#ifndef CtrlSystemH
#define CtrlSystemH
#include "Robot.h"
#include "MotionSimu.h"
#include "RobotServo.h"
#include "RobotComm.h"
#include "StableCtrl.h"
#include "JuneBugCtrl.h"
#include "MotionTrack.h"
//---------------------------------------------------------------------------
// 六种控制指令：1. 机器人复位，令上平台下降到下限位开关，然后再缓慢上升到中位点
//               2. 直接控制每个连杆长度
//               3. 直接控制机器人上平台位姿
//               4. 机器人跟随模拟器运动
//               5. 机器人减摆控制
//               6. 六足机器人控制
//---------------------------------------------------------------------------
class CCtrlSystem
{
friend class CRobotCommPkg;
private:
   CRobot             __Robot;           // 机器人运动学计算(仅包含逆向)
   CMotionSimulator   __Simulator;       // 运动模拟器，将加速度信号转换为位置和角度
   CStableCtrl        __StableCtrl;      // 减摆控制器
   CJuneBugCtrl       __JuneBugCtrl;     // 六足机器人控制器
   CMotionTracker     __MotionTrack;     // 实时运动跟踪
   CRobotCommPkg      __CommPkg;         // 机器人通信报文
   #ifdef INC_SERVO
   CIncServo          __Servo;           // 机器人伺服控制器
   #endif
   #ifdef ROS_SERVO
   CROSServo          __Servo;
   #endif
private:    // 通信
   unsigned char      __FdkBytes[64];
   int                __FdkCnt;
private:
   int                __CtrlMode;           // 控制模式
   bool               __Resetted;           // 已复位标志(系统重启上电后=false)
   bool               __AllJackZeroed;      // 所有连杆已经归零
   float              __CtrlInterval;       // 控制周期，单位s
private:    // 直接位姿控制相关参数变量
   //double             __CurPosEurlar[6];    // 初始姿态
   //double             __DstPosEurlar[6];    // 目标位姿
   //double             __TransSpeed;         // 直接位姿控制平移速度(单位mm/s)
   //double             __RotateSpeed;        // 直接位姿控制转动速度(单位°/s)
   //double             __TransStep;
   //double             __RotateStep;
private:    // 直接电缸控制相关参数变量
   double             __DstJackSpeed[6];    // 设定电缸运动速度，单位 mm/s
   double             __DstJackServoLen[6]; // 电缸目标长度(mm)
private:
   #ifndef __BORLANDC__
   unsigned int       __LedFlickCnt;
   #endif
private:
   void  Reset(void);                     // 机器人复位
   void  ResetCtrl(void);                 // 机器人复位控制
   void  DirectJackCtrl(void);            // 机器人直接电缸控制
   void  DirectPosEurlarCtrl(void);       // 机器人直接位姿控制
   void  MotionSimuCtrl(void);            // 运动模拟控制
   void  StableCtrl(void);                // 减摆控制
   void  JuneBugCtrl(void);               // 六足机器人控制
   void  OnCtrlModeChanged(int CtrlMode); // 控制模式发生改变
private:
   void  ExtractCtrlOrder(void);          // 根据控制模式解析指令
private:
   // 计算位姿渐变(以后要重新写)
   void  CalcDestination(double SrcX, double SrcY, double SrcZ,
                         double DstX, double DstY, double DstZ,
                         double &X,   double &Y,   double &Z,
                         double Step);
private:
   void LedFlick(void);
public:
   CCtrlSystem(void);
public:
   CRobot&           Robot(void)    {return __Robot;}
   CMotionSimulator& Simulator(void){return __Simulator;}
   CRobotServo&      Servo(void)    {return __Servo;}
public:
   void  Control(void);
   bool  RcvCommandByte(char Byte);
   bool  FdkBuffer(unsigned char **Fkd, int *FdkLength);
public:
   CStableCtrl& StableController(void){return __StableCtrl;}
};
extern CCtrlSystem CtrlSystem;
#endif
