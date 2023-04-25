//---------------------------------------------------------------------------

#ifndef GlobalDefH
#define GlobalDefH
#include <math.h>
#ifndef M_PI
#define M_PI   3.141592654
#endif
//---------------------------------------------------------------------------
// 机器人结构尺寸
//         UpperArmLength     |  UpperBaseLength
//                            |  (注意：短臂长度指的是总基座尺寸的1/2)
//     -----------------------|
//                            |
//                            |

// 伺服电缸参数
//#define ROBOT_2
//#define ROBOT_1
//#define JUNE_BUG1
#define ROBOT_3

#ifdef ROBOT_1       // 办公室的机器人
   #define ROBOT_UPPER_ARM_LENGTH     0.375           // 机器人上平台长臂长度
   #define ROBOT_UPPER_BASE_LENGTH    0.036           // 机器人上平台短臂长度
   #define ROBOT_LOWER_ARM_LENGTH     0.675           // 机器人下平台长臂长度
   #define ROBOT_LOWER_BASE_LENGTH    0.036           // 机器人下平台短臂长度

   #define ACTIVE_SERVO_CNT           6
   #define SERVO_PULSE_ROUND          10000          // 伺服转动一周对应脉冲数(每个控制周期脉冲数不超过65535，
                                                     //   每秒脉冲总数不超过6553500，每秒最多50转，因此每转一周脉冲数不超过131,070。
																										 //   设定为10,000，台达伺服B2编码器1转脉冲为160,000，将电子齿轮分子(P1-44)设为160，分母(P1-45)为10。
   #define SERVO_ROUND_MM             5.0            // 伺服转动一周电缸直线运动距离，单位 mm
   #define SERVO_RPM_MIN              5              // 伺服最小转速，单位RPM
   #define SERVO_RPM_MAX              3000           // 伺服最大转速，单位RPM

   #define JACK_FIXED_LENGTH          1.134          // 伺服电缸固定部分长度(该长度指的是由基座到限位开关的位置，需要准确测量)
   #define JACK_SERVO_LENGTH          0.2            // 伺服运动部分总行程(m)，通常指上下限位开关之间的长度
   #define JACK_SERVO_DEC             0.05           // 伺服两端减速区长度(m)

   #define INIT_Z_POSITION            1.140
#endif

#ifdef ROBOT_2
   #define ROBOT_UPPER_ARM_LENGTH     1.1           // 机器人上平台长臂长度
   #define ROBOT_UPPER_BASE_LENGTH    0.06          // 机器人上平台短臂长度
   #define ROBOT_LOWER_ARM_LENGTH     1.25           // 机器人下平台长臂长度
   #define ROBOT_LOWER_BASE_LENGTH    0.06          // 机器人下平台短臂长度
	 
   #define ACTIVE_SERVO_CNT           6
   #define SERVO_PULSE_ROUND          10000          // 伺服转动一周对应脉冲数(每个控制周期脉冲数不超过65535，
                                                     //   每秒脉冲总数不超过6553500，每秒最多50转，因此每转一周脉冲数不超过131,070。
																										 //   设定为10,000，台达伺服B2编码器1转脉冲为160,000，将电子齿轮分子(P1-44)设为160，分母(P1-45)为10。
   #define SERVO_ROUND_MM             5.0            // 伺服转动一周电缸直线运动距离，单位 mm
   #define SERVO_RPM_MIN              5              // 伺服最小转速，单位RPM
   #define SERVO_RPM_MAX              3000           // 伺服最大转速，单位RPM

   #define JACK_FIXED_LENGTH          1.15          // 伺服电缸固定部分长度(该长度指的是由基座到限位开关的位置，需要准确测量)
   #define JACK_SERVO_LENGTH          0.4           // 伺服电缸最小运动行程，单位m(正常运动中，伺服要与限位开关保持一定缓冲距离)
   #define JACK_SERVO_DEC             0.05           // 伺服电缸最大运动行程，单位m
#endif

#ifdef ROBOT_3
   #define ROBOT_UPPER_ARM_LENGTH     1.5           // 机器人上平台长臂长度
   #define ROBOT_UPPER_BASE_LENGTH    0.2          // 机器人上平台短臂长度
   #define ROBOT_LOWER_ARM_LENGTH     3.0           // 机器人下平台长臂长度
   #define ROBOT_LOWER_BASE_LENGTH    0.2          // 机器人下平台短臂长度

   #define ACTIVE_SERVO_CNT           6
   #define SERVO_PULSE_ROUND          10000          // 伺服转动一周对应脉冲数(每个控制周期脉冲数不超过65535，
                                                     //   每秒脉冲总数不超过6553500，每秒最多50转，因此每转一周脉冲数不超过131,070。
																										 //   设定为10,000，台达伺服B2编码器1转脉冲为160,000，将电子齿轮分子(P1-44)设为160，分母(P1-45)为10。
   #define SERVO_ROUND_MM             5.0            // 伺服转动一周电缸直线运动距离，单位 mm
   #define SERVO_RPM_MIN              5              // 伺服最小转速，单位RPM
   #define SERVO_RPM_MAX              3000           // 伺服最大转速，单位RPM

   #define JACK_FIXED_LENGTH          3.0          // 伺服电缸固定部分长度(该长度指的是由基座到限位开关的位置，需要准确测量)
   #define JACK_SERVO_LENGTH          2.0           // 伺服电缸最小运动行程，单位m(正常运动中，伺服要与限位开关保持一定缓冲距离)
   #define JACK_SERVO_DEC             0.05           // 伺服电缸最大运动行程，单位m

   #define DEFAULT_Z_OFFSET           0.0
   #define XYPLANE_HEIGHT             0.01
#endif




#ifdef JUNE_BUG       // 六足爬行机器人
   #define ROBOT_UPPER_ARM_LENGTH     0.555          // 机器人上平台长臂长度
   #define ROBOT_UPPER_BASE_LENGTH    0.045          // 机器人上平台短臂长度
   #define ROBOT_LOWER_ARM_LENGTH     0.399          // 机器人下平台长臂长度
   #define ROBOT_LOWER_BASE_LENGTH    0.045          // 机器人下平台短臂长度

   #define ACTIVE_SERVO_CNT           6
   #define SERVO_PULSE_ROUND          10000          // 伺服转动一周对应脉冲数(每个控制周期脉冲数不超过65535，
                                                     //   每秒脉冲总数不超过6553500，每秒最多50转，因此每转一周脉冲数不超过131,070。
																										 //   设定为10,000，台达伺服B2编码器1转脉冲为160,000，将电子齿轮分子(P1-44)设为160，分母(P1-45)为10。
   #define SERVO_ROUND_MM             5.0            // 伺服转动一周电缸直线运动距离，单位 mm
   #define SERVO_RPM_MIN              5              // 伺服最小转速，单位RPM
   #define SERVO_RPM_MAX              3000           // 伺服最大转速，单位RPM

   #define JACK_FIXED_LENGTH          0.506          // 伺服电缸固定部分长度(该长度指的是由基座到限位开关的位置，需要准确测量)
   #define JACK_SERVO_LENGTH          0.300          // 伺服运动部分总行程(m)，通常指上下限位开关之间的长度
   #define JACK_SERVO_DEC             0.005          // 伺服两端减速区长度(m)

   #define INIT_Z_POSITION            1.140
#endif

#ifdef JUNE_BUG1       // 六足爬行机器人
   #define ROBOT_UPPER_ARM_LENGTH     0.448          // 机器人上平台长臂长度
   #define ROBOT_UPPER_BASE_LENGTH    0.050          // 机器人上平台短臂长度
   #define ROBOT_LOWER_ARM_LENGTH     0.448          // 机器人下平台长臂长度
   #define ROBOT_LOWER_BASE_LENGTH    0.050          // 机器人下平台短臂长度

   #define ACTIVE_SERVO_CNT           6
   #define SERVO_PULSE_ROUND          2000           // 伺服转动一周对应脉冲数(每个控制周期脉冲数不超过65535，
                                                     // 每秒脉冲总数不超过6553500，每秒最多50转，因此每转一周脉冲数不超过131,070。
																										 //   设定为10,000，台达伺服B2编码器1转脉冲为160,000，将电子齿轮分子(P1-44)设为160，分母(P1-45)为10。
   #define SERVO_ROUND_MM             5.0            // 伺服转动一周电缸直线运动距离，单位 mm
   #define SERVO_RPM_MIN              20             // 伺服最小转速，单位RPM
   #define SERVO_RPM_MAX              3000           // 伺服最大转速，单位RPM

   #define JACK_FIXED_LENGTH          0.54           // 伺服电缸固定部分长度(该长度指的是由基座到限位开关的位置，需要准确测量)
   #define JACK_SERVO_LENGTH          0.25           // 伺服运动部分总行程(m)，通常指上下限位开关之间的长度
   #define JACK_SERVO_DEC             0.005          // 伺服两端减速区长度(m)

   #define INIT_Z_POSITION            1.3
   #define DEFAULT_Z_OFFSET           0.0

   #define XYPLANE_HEIGHT             0.01
#endif

// 运动模拟参数
#define MAX_LINEAR_ACC  0.5      // 最大直线加速度(m/s^2)

#define MAX_SPEED_X     0.3    // x轴的最大线速度
#define MAX_RANGE_X     0.038   // x轴的最大运动距离(以中心点为原点)

#define MAX_SPEED_Y     0.3    // y轴的最大线速度
#define MAX_RANGE_Y     0.078   // y轴的最大运动距离(以中心点为原点)

#define MAX_SPEED_Z     0.3    // z轴的最大线速度
#define MAX_RANGE_Z     0.038   // z轴的最大运动距离(以中心点为原点)

#define MAX_ROTARY_SPD  20     // 最大角速度(deg/s)
#define MAX_YAW         5
#define MAX_PITCH       10
#define MAX_ROLL        10

// 减摆控制
// 由于减摆控制需要使用UART2和UART3，因此减摆控制时，无法进行正常的上位机通信控制
//#define SYS_STABLE_CTRL   


//---------------------------------------------------------------------------
// 以下参数基本固定
//---------------------------------------------------------------------------
// 控制器刷新周期
#ifdef __BORLANDC__
   #define  CTRL_INTERVAL  0.02
#else
   #define  CTRL_INTERVAL  0.01
#endif

// 电缸允许最大速度(m/s)和最大加速度(m/s^2)
#define JACK_MAX_SPEED  0.25
#define JACK_MAX_ACC    0.5

// 控制器归零速度
#define GO_ZERO_RPM          100     // 归零转速
#define ZERO_2_CENTER_SPD    0.01    // 由零点向中心点移动速度(m/s)

// 伺服最大转速变化(0RPM到SERVO_RPM_MAX)所需要的加速时间
// 通过该时间计算最大允许加速度，从而避免伺服出现猛烈振动
#define SERVO_FULL_SPD_ACC_TIME   0.4

#define JACK_SERVO_DEC_RANGE       0.05           // 伺服电缸减速行程(m)

// 控制器参数
#define  PULSE_SRC_FREQUENCY     1.0E6   // 脉冲源频率(1M)

// 计算正弦余弦时，使用快速算法
//#define  CALC_SIN_FAST

// 是否在每个控制周期间隔进行正向运动学计算
//#define CALC_FDKP

// 通信速率
#define UART3_BAUD_RATE 4800

// 控制器以字符方式显示控制信息，用于debug调试用
#define  SHOW_DEBUG_STRING
//----------------------------------------------------------------------------

#endif
