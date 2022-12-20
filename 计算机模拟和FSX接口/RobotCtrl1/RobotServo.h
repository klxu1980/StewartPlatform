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
   double  __CtrlInterval;           // 控制周期，单位s
   double  __MinServoLength;         // 连杆最小行程位置
   double  __MaxServoLength;         // 连杆最大行程位置
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
   unsigned short int ReadPulseLeft(int Idx)  {return fpga_read(i);}
   unsigned short int ReadLmtSwitchLower(void){return ~fpga_read(6);}
   void WriteFreqDivBase(int Idx, int Base) {fpga_write(Idx, Base);}
   void WritePulseCnt(int Idx, int PulseCnt){fpga_write(Idx + 6, PulseCnt);}
   void WriteDirection(int Direction)       {fpga_write(12, Direction);}
#else
   unsigned short int ReadPulseLeft(int Idx){return 0;}
   unsigned short int ReadLmtSwitchLower(void){return 0;}
   void WriteFreqDivBase(int Idx, int Base) {}
   void WritePulseCnt(int Idx, int PulseCnt){}
   void WriteDirection(int Direction)       {}
#endif
public:
   CRobotServo(void);
public:
   void SetServoCtrlInterval(float Interval);                      // 设置伺服控制周期(该周期应当与FPGA中的控制周期一致，单位s)
   void SetServoTransParams(int PulsePerRound, float MMPerRound);  // 设置伺服传动参数(电机转动一圈脉冲数，丝杠导程(单位mm))
   void SetServoSpeedLimit(float MinSpeed, float MaxSpeed);        // 设置连杆速度范围(最小速度和最大速度，单位mm/s)
   void SetJackLimit(float MinLength, float MaxLength);            // 设置连杆的最小和最大行程，单位mm
public:
   void RobotMove(CRobot &Robot, bool NoLimit = false);            // 机器人运动。在每个控制周期中，都应当调用该函数
   void ServoMove(void);
public:
   void GoZero(void);
   void GoZeroCtrl(void);                                          // 控制电缸向零点运动(由CtrlSystem调用)
   bool Zeroed(void);
public:
   void SetJackLength(int JackID, int JackLength, int JackSpeed);
   double JackLength(int JackID){return __CurPosition[JackID] * __MMPerRound * 0.001 / __PulsePerRound;} // 单位m
};
#endif
