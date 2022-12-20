//---------------------------------------------------------------------------

#ifndef RobotCommH
#define RobotCommH

#define  ORDER_IDLE               0
#define  RESET_ROBOT              1
#define  DIRECT_JACK_CTRL         2
#define  DIRECT_POS_EURLAR_CTRL   3
#define  MOTION_SIMU_CTRL         4
#define  STABLE_CTRL              5
#define  MOTION_SIMU_PARAM        6
#define  JUNEBUG_CTRL             7

//---------------------------------------------------------------------------
struct CMotionSimuParams
{
   float AccXMax;            // x轴加速度模拟上限
   float SpdXMax;            // x轴速度上限
   float XMax;
   float AccYMax;
   float SpdYMax;
   float YMax;
   float AccZMax;
   float SpdZMax;
   float ZMax;
   float AccPitchMax;
   float AccPitchSpdMax;
   float AccRollMax;
   float AccRollSpdMax;
   float YawMax;
   float YawSpdMax;
   float PitchMax;
   float PitchSpdMax;
   float RollMax;
   float RollSpdMax;
   float HighPassX;
   float HighPassY;
   float HighPassZ;
   float HighPassYaw;
   float HighPassPitch;
   float HighPassRoll;
};
//---------------------------------------------------------------------------
// 上位机和机器人之间的通信报文，主要通过RS-485，或者以太网传送
// 通信报文的基本格式：
// 报头：0x55
// 报文长度：1字节，最大不超过128字节
// 报文功能：1字节
// 数据报文：长度等于报文长度
// 校验字节：采用CRC校验，2字节
// CRobotCommPkg同时供上位机、下位机使用
//---------------------------------------------------------------------------
class CCtrlSystem;
class CRobotCommPkg
{
private:
   unsigned short CalcCRC(unsigned char *Buffer, int Count);
   void AddCRC(unsigned char *Buffer, int PkgSize);
   bool CheckCRC(unsigned char *Buffer, int PkgSize);
   bool CheckReceivedComm(unsigned char Byte, unsigned char *Buffer, int &RcvSize);
private:
   void  Short2Buffer(short Value, unsigned char *Buffer){Buffer[0] = Value; Buffer[1] = Value >> 8;}
   short Buffer2Short(unsigned char *Buffer){return *((short*)Buffer);}
public:
   unsigned char CtrlOrder[110];     // 向机器人下传的指令报文(注意：由于某些不清楚的原因，BC中不允许该缓冲太大)
   unsigned char FdkStatus[24];      // 机器人返回的应答报文
   int CtrlLength;                   // 收到的控制指令长度
   int FdkLength;                    // 收到的反馈应答长度
public:
   CRobotCommPkg(void);
public:
   int CtrlOrderSize(void){return CtrlOrder[1] + 5;}
   int FdkStatusSize(void){return FdkStatus[1] + 5;}
public:
   bool  ReceiveCtrlOrder(unsigned char Byte);
   bool  ReceiveFdkStatus(unsigned char Byte);
public:
   // 以下部分是上位机向机器人发送的控制指令报文
   // 报文指令类型：0 = 空指令；
   //               1 = 系统复位；
   //               2 = 直接控制电缸长度，长度单位m，分辨率0.1mm；速度单位m/s，分辨率1mm/s
   //               3 = 直接控制上平台位姿，位置单位m，分辨率0.1mm；姿态单位°，分辨率0.1°
   //               4 = 模拟器控制参数，加速度单位m/s^2，分辨率0.001m/s^2；角速度单位°/s，分辨率0.1°/s
   //               5 = 减摆控制指令
   void  BuildNullOrder(void);
   void  BuildResetOrder(void);
   void  BuildJackCtrlOrder(int JackID, float JackLength, float Speed);
   void  BuildPosCtrlOrder(float X, float Y, float Z, float Yaw, float Pitch, float Roll);
   void  BuildAccCtrlOrder(float AccX, float AccY, float AccZ, float SpdYaw, float SpdPitch, float SpdRoll);
   void  BuildAccCtrlParams(CMotionSimuParams Params);
   void  BuildStableCtrlOrder(void);
   void  BuildJuneBugCtrlOrder(float Dx, float Dy, float Yaw, float XYHeight, float Speed);
public:
   // 以下部分是机器人接受解析上位机指令
   int   GetOrderType(void){return CtrlOrder[2];}
   void  GetJackCtrlOrder(int &JackID, float &Length, float &Speed);
   void  GetPosCtrlOrder(float &X, float &Y, float &Z, float &Yaw, float &Pitch, float &Roll);
   void  GetAccCtrlOrder(float &AccX, float &AccY, float &AccZ, float &SpdYaw, float &SpdPitch, float &SpdRoll);
   void  GetAccCtrlParams(CMotionSimuParams &Params);
   void  GetJuneBugOrder(float &Dx, float &Dy, float &Yaw, float &XYHeight, float &Speed);
public:
   void  FdkRobotStatus(CCtrlSystem *CtrlSystem);
   void  GetLmtSwitchStatus(char &SwitchLower, char &SwitchUpper, char &JackMin, char &JackMax);
   void  GetJackLength(float Length[6]);
};
#endif
