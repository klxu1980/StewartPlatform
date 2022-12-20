//---------------------------------------------------------------------------

#ifndef RobotServoH
#define RobotServoH
#include "Robot.h"
#include "CtrlBoard.h"

#ifndef __BORLANDC__
#include "fsmc.h"
#endif
//---------------------------------------------------------------------------
// 注意：1. 为了方便，伺服控制程序内部，长度单位统一为mm；对外接口，则统一为m。
//       2. 伺服程序中不对运动量加以约束。运动量的约束由上层程序处理，伺服依靠限位开关避免运动量超限。
//       目前还没有做伺服到达末端时的减速控制，后面要加上
//---------------------------------------------------------------------------
class CRobotServo
{
private:
   int     __MinPulse;               // 一个控制周期中所允许的丝杠最小运动增量(脉冲数)，低于该阈值，则脉冲输出为零
   int     __MaxPulse;               // 一个控制周期中所允许的丝杠最大运动增量(脉冲数)
   bool    __Zeroing;                // 正在归零
private: public:
   int     __CurPosition[6];         // 每个通道的当前位置
   int     __DstPosition[6];         // 每个通道下一控制周期应当达到的位置
   int     __CalcPosition[6];        // 计算所得每个通道所应当达到的位置
   bool    __Direction[6];           // 运动方向, true=正方向(即电缸伸出)
   unsigned short __PulseCnt[6];     // 每通道运动增量
private:
   int     __MaxAccByPulse;          // 最大加速度(以脉冲数为单位)
   double  __ServoRange[6];          // 实测电缸行程(单位m)
   int     __Positions[6][3];        // 伺服最近三个控制周期的位置，用于加速度限幅
private:
   int  FilterDestination(int Idx, int DstPosition);
private:
   void NormalCtrl(void);            // 正常运动控制
   void GoZeroCtrl(void);            // 控制电缸向零点运动(由CtrlSystem调用)
public:
   CRobotServo(void);
public:
   void RobotMove(CRobot &Robot);            // 完成机器人的运动学解算后，调用该函数传递连杆长度
   void ServoCtrl(void);                                           // 控制伺服电机的实际脉冲输出，每个控制周期都需要调用
public:
   void GoZero(void){__Zeroing = true;}                            // 要求所有伺服归零
   bool IsAllZeroed(void);                                         // 检查是否所有电缸均已到达零点(下限位开关)
public:
   // 伺服电缸的实际长度
   double ServoLength(int JackID){return __CurPosition[JackID] * SERVO_ROUND_MM * 0.001 / SERVO_PULSE_ROUND;}
};
#endif
