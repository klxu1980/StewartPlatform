//---------------------------------------------------------------------------

#ifndef RobotH
#define RobotH
#include "RobotIKP.h"
#include "RobotFKP.h"
//---------------------------------------------------------------------------
class CRobot
{
//---------------------------------------------------------------------------
// 机器人的机械参数有三类：
// 1. 铰接点位置参数(长臂、短臂尺寸，铰接点与上下平台平面高度)
// 2. 电缸(作动筒)长度参数
// 3. 误差参数
// 前两类参数由设计期确定，具体数值固化在GlobalDef.h文件中，程序中由CCtrlSystem类赋值;
//     也可能由其他程序外部设定，比如空间优化、或者动态负载评估时。
// 误差参数由标定计算确定。
// 注意：对结构参数赋值后，必须调用InitStructureParams()函数
public:
   // 机械尺寸参数
   // 通过长短臂长设置机器人的机械尺寸
   //                            X (铰接点)
   //                            |  BaseLength
   //              ArmLength     |  (注意：短臂长度指的是总基座尺寸的1/2)
   //  --------------------------|
   //                            |
   //                            |
   //                            X
   double  UpperArmLength;         // 上平台长臂长度
   double  UpperBaseLength;        // 上平台短臂长度
   double  LowerArmLength;         // 下平台长臂长度
   double  LowerBaseLength;        // 下平台短臂长度
   double  UpperJointHeight;       // 上平台铰接点和平台间的高度
   double  LowerJointHeight;       // 下平台铰接点和平台间的高度
public:
   // 电缸(作动筒)参数
   //      -------------------------------------------------------------|
   //      |                            ------------------------------------------
   //   X--|                            |                                        |------X
   //   |  |                            ------------------------------------------      |
   //   |  -------------------------------------------------------------|               |
   //   |                   |        |                     |          |                 |
   // 电缸下铰接点       下限位 最小运动行程         最大运动行程   上限位         电缸上铰接点
   // 电缸有四个结构参数，其长度均以下铰接点为原点
   // 1. 电缸固定长度(JackFixedLength)：当电缸到达下限位时，下铰接点与上铰接点之间的长度。
   //             电缸总长度 = 电缸固定长度 + 电缸伺服长度
   //        电缸伺服长度以下限位为零点
   // 2. 伺服总运动行程(JackServoLength)：伺服电缸仅允许在上下限位开关之间运动，二者之间的间距即为伺服总运动行程
   // 3. 伺服缓冲行程(JackServoBuffer)：为避免伺服电缸到达上下限位时突然停止造成冲击，在限位开关之前设置缓冲行程。
   //        正常工作时，控制算法应确保伺服电缸在最小、最大行程处停止。如果超出该范围，则基于S函数使电缸在限位开关前逐渐停止。
   double  JackFixedLength;        // 伺服电缸固定部分长度，即当电缸完全缩回到下限位开关时，上下铰接点之间的间距长度
   double  JackServoLength;        // 伺服电缸运动部分长度
   double  JackServoBuffer;        // 伺服电缸缓冲部分长度
public:
   // 机械误差
   double  ErrJointUpper[6][3];    // 上平台每个铰接点的安装误差
   double  ErrJointLower[6][3];    // 下平台每个铰接点的安装误差
   double  ErrJackFixedLen[6];     // 连杆固定部分长度误差
public:
   CRobotIKP   RobotIKP;           // 逆向计算，用于根据位姿给定计算连杆长度
   CRobotFKP   RobotFKP;           // 正向计算，用于根据实际连杆长度计算实际位姿
public:
   CMoveStatus MoveStatus;         // 运动状态
   double      CenterZ;            // 中心位置Z坐标
   bool        Constrained;        // 运动受到约束条件限制
   double      ForceDet;           // 电缸受力计算时系数阵的行列式，用于评估奇异性
public:
   // 直线连杆
   struct  CJack
   {
   public:
      int     ID;
      CRobot *Owner;
   public:
      double Length;           // 连杆长度(m)
      double Servo;            // 丝杠伸出长度(m)
      double Force;            // 连杆作用力
   };
   CJack Jack[6];
private:
   void   RotateAroundZ(double Rst[3], double Src[3], double Angle);
   double Sigmoid(double Xi){return 2.0 / (exp(-2.0 * Xi / JackServoBuffer) + 1.0) - 1.0;}
   double LimitServo(double Servo);
   double CalcDeterminant(double FV[6][3], double TV[6][3]);
public:
   CRobot(void);
   void InitStructureParams(void);   // 初始化结构参数
public:
   // 对上平台高度进行估算，不考虑安装误差，
   // 主要用于为正向运动学计算提供初始位姿
   double CalcPlatformHeight(double JackLenght);   // 当6连杆长度一致时，计算上平台高度
   double PlatformMinHeight(void);                 // 上平台最低高度
   double PlatformMaxHeight(void);                 // 上平台最大高度
public:
   double PosX(void)    {return RobotIKP.UpperPos[0];}
   double PosY(void)    {return RobotIKP.UpperPos[1];}
   double PosZ(void)    {return RobotIKP.UpperPos[2];}
   double PosYaw(void)  {return RobotIKP.UpperEuler[0];}
   double PosPitch(void){return RobotIKP.UpperEuler[1];}
   double PosRoll(void) {return RobotIKP.UpperEuler[2];}
public:
   void  SetJackLength(int ID, double Length);
   void  SetJackServo(int ID, double Servo);
public:
   // 上平台位姿控制，即，给定上平台位姿，由逆向运动学计算连杆长度
   // 由逆向运动学计算得到的连杆长度有可能超出物理约束范围，或者导致上平台进入奇异点，因此连杆实际长度需要受到约束。
   // 因此，上平台位姿控制包含以下计算步骤：
   // 1. 由给定位姿计算连杆长度
   // 2. 检查连杆长度是否超过上下限。如果超过，则限值连杆长度。
   // 3. 检查是否可能存在奇异、或机械干涉(目前还没有做)
   // 4. 由于存在限位开关、速度上限等约束，连杆并没有真正到达指定位置。因此，通过正向运动学，计算上平台的实际位姿。
   // 由于正向运动学计算需要较多计算时间，因此将以上步骤拆分到PlatformMove()和AfterServoMoved()函数中。
   // PlatformMove()负责前3个步骤，AfterServoMoved()负责步骤4.
   // 在每一轮控制中，调用步骤应当为
   // 1. 调用PlatformMove()计算连杆长度
   // 2. 将连杆长度输出到伺服控制器
   // 3. 调用AfterServoMoved()，在控制间隙完成正向运动学计算。
   void PlatformMove(double X, double Y, double Z, double Yaw, double Pitch, double Roll, bool ServoLimited = true);
   void AfterServoMoved(double Servo1, double Servo2, double Servo3, double Servo4, double Servo5, double Servo6);
   void AfterServoMoved(void);
   void PlatformZeroed(void);
public:
   bool CalcForceOfJacks(double Force[3], double Torque[3]);
};
#endif
