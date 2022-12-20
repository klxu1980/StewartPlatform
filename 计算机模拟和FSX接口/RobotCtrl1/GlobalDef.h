//---------------------------------------------------------------------------

#ifndef GlobalDefH
#define GlobalDefH
#include <math.h>
//---------------------------------------------------------------------------
// 机器人结构尺寸
//         UpperArmLength     |  UpperBaseLength
//                            |  (注意：短臂长度指的是总基座尺寸的1/2)
//     -----------------------|
//                            |
//                            |
#define ROBOT_UPPER_ARM_LENGTH     0.65           // 机器人上平台长臂长度
#define ROBOT_UPPER_BASE_LENGTH    0.035          // 机器人上平台短臂长度
#define ROBOT_LOWER_ARM_LENGTH     0.65           // 机器人下平台长臂长度
#define ROBOT_LOWER_BASE_LENGTH    0.035          // 机器人下平台短臂长度
#define ROBOT_JACK_LENGTH_MIN      0.984          // 连杆最短长度
#define ROBOT_JACK_LENGTH_MAX      1.284          // 连杆最大长度

// 伺服电缸参数
#define SERVO_PULSE_ROUND  10000        // 伺服转动一周对应脉冲数
#define SERVO_ROUND_MM     5.0          // 伺服转动一周电缸直线运动距离，单位 mm
#define SERVO_SPEED_MIN    1            // 伺服最小于最大速度，单位 mm/s
#define SERVO_SPEED_MAX    100

#define SERVO_JACK_MIN     50           // 伺服电缸最小和最大运动行程，单位 mm
#define SERVO_JACK_MAX     250

// 控制器刷新周期
#ifdef __BORLANDC__
   #define  CTRL_INTERVAL  0.02
#else
   #define  CTRL_INTERVAL  0.01
#endif

#define GO_ZERO_SPEED   0.02

// 运动模拟参数
#define MAX_LINEAR_ACC  1
#define MAX_ROTARY_ACC  10


//----------------------------------------------------------------------------
double Clip(double Value, double Range)
{
   if(Value > Range)
      return Range;
   else if(Value < -Range)
      return -Range;
   else
      return Value;
}

double Rad2Degree(double Rad){return Rad * 180.0 / M_PI;}  // 弧度换算为角度

#endif
