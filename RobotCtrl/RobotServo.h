//---------------------------------------------------------------------------

#ifndef RobotServoH
#define RobotServoH
#include "Robot.h"
#include "CtrlBoard.h"

#ifndef __BORLANDC__
#include "fsmc.h"
#endif

//---------------------------------------------------------------------------
// 在早期设计机器人时，使用的是脉冲控制的增量型伺服电机。控制系统需要向FPGA发送下一个控制周期中的脉冲数量和运动方向。
// 新的机器人设计中，采用绝对位置型伺服电机，并通过EtherCAT总线向电机驱动器发送绝对位置。
// 因此，重新设计了伺服驱动器的控制接口类：
// 1. CRobotServo：伺服驱动器接口基类
// 2. CIncServo：增量脉冲型伺服驱动控制。该控制接口通过FPGA输出脉冲控制伺服电机。
// 3. CAbsServo：绝对位置型。该控制接口通过EtherCAT总线输出控制指令。
// 需要注意的是，绝对位置型接口目前有3种EtherCAT总线通信方式：
// 1. 基于倍福机器人控制器的EtherCAT总线接口
// 2. 基于开源的SOEM接口库
// 3. 在ROS仿真环境下驱动虚拟机器人


//---------------------------------------------------------------------------
// 注意：1. 为了方便，伺服控制程序内部，长度单位统一为mm；对外接口，则统一为m。
//       2. 伺服程序中不对运动量加以约束。运动量的约束由上层程序处理，伺服依靠限位开关避免运动量超限。
//       目前还没有做伺服到达末端时的减速控制，后面要加上
//---------------------------------------------------------------------------
class CRobotServo
{
private: public:
   double  __CurPosition[6];         // 每个通道的当前位置，单位m
   double  __DstPosition[6];         // 每个通道下一控制周期应当达到的位置，单位m
private:
   double  __AccMax;                 // 最大加速度，单位m/s^2
   double  __ServoRange[6];          // 实测电缸行程，单位m
   double  __Positions[6][3];        // 伺服最近三个控制周期的位置，用于加速度限幅
private:
   double FilterDestination(int Idx, double DstPosition);
public:
   CRobotServo(void);
public:
   void virtual RobotMove(CRobot &Robot) = 0;   // 完成机器人的运动学解算后，调用该函数传递连杆长度
   void virtual ServoCtrl(void) = 0;            // 控制伺服电机的实际脉冲输出，每个控制周期都需要调用
public:
   //void GoZero(void){__Zeroing = true;}         // 要求所有伺服归零
   //bool IsAllZeroed(void);                      // 检查是否所有电缸均已到达零点(下限位开关)
public:
   // 伺服电缸的实际长度
   double ServoLength(int JackID) { return __CurPosition[JackID]; }
};
//----------------------------------------------------------------------------------
// CIncServo
//----------------------------------------------------------------------------------
class CIncServo : public CRobotServo
{
private:
	int     __MinPulse;               // 一个控制周期中所允许的丝杠最小运动增量(脉冲数)，低于该阈值，则脉冲输出为零
	int     __MaxPulse;               // 一个控制周期中所允许的丝杠最大运动增量(脉冲数)
	bool    __Zeroing;                // 正在归零
private: public:
	//int     __CurPosition[6];         // 每个通道的当前位置
	//int     __DstPosition[6];         // 每个通道下一控制周期应当达到的位置
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
	CIncServo(void);
public:
	void RobotMove(CRobot& Robot);            // 完成机器人的运动学解算后，调用该函数传递连杆长度
	void ServoCtrl(void);                                           // 控制伺服电机的实际脉冲输出，每个控制周期都需要调用
public:
	void GoZero(void) { __Zeroing = true; }                            // 要求所有伺服归零
	bool IsAllZeroed(void);                                         // 检查是否所有电缸均已到达零点(下限位开关)
public:
	// 伺服电缸的实际长度
	double ServoLength(int JackID) { return __CurPosition[JackID] * SERVO_ROUND_MM * 0.001 / SERVO_PULSE_ROUND; }
};
//----------------------------------------------------------------------------------
// CAbsServo
//----------------------------------------------------------------------------------
class CAbsServo : public CRobotServo
{

};
#endif

