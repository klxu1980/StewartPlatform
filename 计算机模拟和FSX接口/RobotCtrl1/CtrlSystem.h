//---------------------------------------------------------------------------

#ifndef CtrlSystemH
#define CtrlSystemH
#include "Robot.h"
#include "RobotSimu.h"
#include "MotionSimulator.h"
#include "RobotServo.h"
//---------------------------------------------------------------------------
// 三种控制指令：1. 机器人复位
//               2. 直接控制每个连杆长度
//               3. 直接控制机器人上平台位姿
//               4. 机器人跟随模拟器运动
//---------------------------------------------------------------------------
class CCtrlSystem
{
private:
   CRobot             __Robot;           // 机器人运动学计算(仅包含逆向)
   CMotionSimulator   __Simulator;       // 运动模拟器，将加速度信号转换为位置和角度
   CRobotServo        __Servo;           // 机器人伺服控制器
   #ifdef __BORLANDC__
   CRobotSimu         __RobotSimu;       // 虚拟机器人对象
   #endif
private:
   char               __RcvedBytes[64];  // 通信接收字节缓冲
   int                __RcvedCnt;
private:
   int                __CtrlMode;        // 控制模式
   int                __LstCtrlMode;     // 前次控制模式
   bool               __Resetted;        // 已复位标志(系统重启上电后=false)
   float              __CentralZ;        // 中心位置Z轴坐标
   float              __CtrlInterval;    // 控制周期，单位s
private:    // 直接位姿控制相关参数变量
   double             __DstPosEurlar[6]; // 目标位姿
   int                __MoveSpeed;       // 直接位姿控制平移速度(单位mm/s)
   int                __RotateSpeed;     // 直接位姿控制转动速度(单位°/s)
private:    // 直接电缸控制相关参数变量
   double             __JackSpeed[6];    // 设定电缸运动速度，单位 mm/s
   double             __DstJackLength[6];// 电缸目标长度(mm)
private:
   short  CalcCRC(char *Buffer, int Count);
   short  Bytes2Word(char *Buffer){return (unsigned char)Buffer[0] + ((unsigned char)Buffer[1] << 8);}
   short  ExtractData(char *Bytes);
   void   SendCommFdk(char CMD);
   void   RcvJackCtrlOrder(short Datas[6]);
   void   RcvCtrlOrder(char Order, short Datas[6]);
   double Rad2Angle(double Rad){return Rad * 180.0 / M_PI;}
private:
   void  Reset(void);                     // 机器人复位
   void  ResettingCtrl(void);             // 机器人复位控制
   void  DirectJackCtrl(void);            // 机器人直接电缸控制
   void  DirectPosEurlarCtrl(void);       // 机器人直接位姿控制
   void  MotionSimuCtrl(void);            // 运动模拟控制
   void  OnCtrlModeChanged(void);         // 控制模式改变
private:
   void  CalcDestination(double SrcX, double SrcY, double SrcZ,
                         double DstX, double DstY, double DstZ,
                         double &X,   double &Y,   double &Z,
                         double Speed, double Interval);
public:
   CCtrlSystem(void);
public:
   CRobot&           Robot(void)    {return __Robot;}
   CMotionSimulator& Simulator(void){return __Simulator;}
   CRobotServo&      Servo(void)    {return __Servo;}
   #ifdef __BORLANDC__
   CRobotSimu&       RobotSimu(void){return __RobotSimu;}
   #endif
public:
   void Control(void);
   void RcvCommByte(char Byte);
public:
   float RobotRangeFromCenter(double Dir[6]);
};
#endif
