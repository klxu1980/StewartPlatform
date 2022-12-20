//---------------------------------------------------------------------------

#ifndef RobotServoH
#define RobotServoH
#include "Robot.h"

#ifndef __BORLANDC__
#include "fsmc.h"
#endif

#define  PULSE_FREQUENCY      1000000.0    // 脉冲源频率
//---------------------------------------------------------------------------
class CRobotServo
{
private:
   int     __PulsePerRound;          // 伺服电机转动一圈所需脉冲数
   double  __MMPerRound;             // 伺服电机转动一圈丝杠运动距离(单位mm)
   double  __CtrlInterval;           // 控制周期
   int     __MinJackInc;             // 一个控制周期中所允许的丝杠最大运动增量(已换算为输出到驱动器的脉冲数量)
   int     __MaxJackInc;             // 一个控制周期中所允许的丝杠最小运动增量。低于该值时，不输出脉冲到驱动器，以避免电机转速过低。
   bool    __Zeroed;                 // 已归零。归零要求所有连杆收缩直至遇到下端限位开关。
private:
   int __CurPosition[6];                // 每个通道的当前位置
   int __DstPosition[6];                // 每个通道下一控制周期应当达到的位置
   unsigned short int __PulseCnt[6];    // 每通道运动增量
   unsigned short int __Direction;      // 运动方向
   unsigned short int __DivCnt[6];      // 每通道脉冲分频值
   unsigned short int __PulseLeft[6];   // 每个通道上一控制周期未完成的脉冲数量
private:
   int MM2Pulse(float MM){return MM * __PulsePerRound / __MMPerRound;}
   int CalcFreqDivBase(int Pulse){return PULSE_FREQUENCY * __CtrlInterval / Pulse + 0.5;}
private:
#ifndef __BORLANDC__
   void WriteFreqDivBase(int Idx, int Base) {fpga_write(Idx, Base);}
   void WritePulseCnt(int Idx, int PulseCnt){fpga_write(Idx + 6, PulseCnt);}
   void WriteDirection(int Direction)       {fpga_write(12, Direction);}
#else
   void WriteFreqDivBase(int Idx, int Base) {}
   void WritePulseCnt(int Idx, int PulseCnt){}
   void WriteDirection(int Direction)       {}
#endif
public:
   CRobotServo(void);
public:
   void SetServoCtrlInterval(float Interval);
   void SetServoTransParams(int PulsePerRound, float MMPerRound);  // 设置伺服传动参数(电机转动一圈脉冲数，丝杠导程(单位mm))
   void SetServoSpeedLimit(float MinSpeed, float MaxSpeed);        // 设置连杆速度范围(最小速度和最大速度，单位mm/s)
public:
   void RobotMove(CRobot &Robot);                  // 机器人运动。在每个控制周期中，都应当调用该函数
   void GoZeroCtrl(void);
   void GoZero(void){__Zeroed = false;}
   bool Zeroed(void){return __Zeroed;}
};
#endif
