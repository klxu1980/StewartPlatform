//---------------------------------------------------------------------------

#ifndef RobotH
#define RobotH
#include "RobotIKP.h"
#include "RobotFKP.h"
//---------------------------------------------------------------------------
class CRobot
{
//---------------------------------------------------------------------------
// �����˵Ļ�е���������ࣺ
// 1. �½ӵ�λ�ò���(���ۡ��̱۳ߴ磬�½ӵ�������ƽ̨ƽ��߶�)
// 2. ���(����Ͳ)���Ȳ���
// 3. ������
// ǰ��������������ȷ����������ֵ�̻���GlobalDef.h�ļ��У���������CCtrlSystem�ำֵ;
//     Ҳ���������������ⲿ�趨������ռ��Ż������߶�̬��������ʱ��
// �������ɱ궨����ȷ����
// ע�⣺�Խṹ������ֵ�󣬱������InitStructureParams()����
public:
   // ��е�ߴ����
   // ͨ�����̱۳����û����˵Ļ�е�ߴ�
   //                            X (�½ӵ�)
   //                            |  BaseLength
   //              ArmLength     |  (ע�⣺�̱۳���ָ�����ܻ����ߴ��1/2)
   //  --------------------------|
   //                            |
   //                            |
   //                            X
   double  UpperArmLength;         // ��ƽ̨���۳���
   double  UpperBaseLength;        // ��ƽ̨�̱۳���
   double  LowerArmLength;         // ��ƽ̨���۳���
   double  LowerBaseLength;        // ��ƽ̨�̱۳���
   double  UpperJointHeight;       // ��ƽ̨�½ӵ��ƽ̨��ĸ߶�
   double  LowerJointHeight;       // ��ƽ̨�½ӵ��ƽ̨��ĸ߶�
public:
   // ���(����Ͳ)����
   //      -------------------------------------------------------------|
   //      |                            ------------------------------------------
   //   X--|                            |                                        |------X
   //   |  |                            ------------------------------------------      |
   //   |  -------------------------------------------------------------|               |
   //   |                   |        |                     |          |                 |
   // ����½½ӵ�       ����λ ��С�˶��г�         ����˶��г�   ����λ         ����Ͻ½ӵ�
   // ������ĸ��ṹ�������䳤�Ⱦ����½½ӵ�Ϊԭ��
   // 1. ��׹̶�����(JackFixedLength)������׵�������λʱ���½½ӵ����Ͻ½ӵ�֮��ĳ��ȡ�
   //             ����ܳ��� = ��׹̶����� + ����ŷ�����
   //        ����ŷ�����������λΪ���
   // 2. �ŷ����˶��г�(JackServoLength)���ŷ���׽�������������λ����֮���˶�������֮��ļ�༴Ϊ�ŷ����˶��г�
   // 3. �ŷ������г�(JackServoBuffer)��Ϊ�����ŷ���׵���������λʱͻȻֹͣ��ɳ��������λ����֮ǰ���û����г̡�
   //        ��������ʱ�������㷨Ӧȷ���ŷ��������С������г̴�ֹͣ����������÷�Χ�������S����ʹ�������λ����ǰ��ֹͣ��
   double  JackFixedLength;        // �ŷ���׹̶����ֳ��ȣ����������ȫ���ص�����λ����ʱ�����½½ӵ�֮��ļ�೤��
   double  JackServoLength;        // �ŷ�����˶����ֳ���
   double  JackServoBuffer;        // �ŷ���׻��岿�ֳ���
public:
   // ��е���
   double  ErrJointUpper[6][3];    // ��ƽ̨ÿ���½ӵ�İ�װ���
   double  ErrJointLower[6][3];    // ��ƽ̨ÿ���½ӵ�İ�װ���
   double  ErrJackFixedLen[6];     // ���˹̶����ֳ������
public:
   CRobotIKP   RobotIKP;           // ������㣬���ڸ���λ�˸����������˳���
   CRobotFKP   RobotFKP;           // ������㣬���ڸ���ʵ�����˳��ȼ���ʵ��λ��
public:
   CMoveStatus MoveStatus;         // �˶�״̬
   double      CenterZ;            // ����λ��Z����
   bool        Constrained;        // �˶��ܵ�Լ����������
   double      ForceDet;           // �����������ʱϵ���������ʽ����������������
public:
   // ֱ������
   struct  CJack
   {
   public:
      int     ID;
      CRobot *Owner;
   public:
      double Length;           // ���˳���(m)
      double Servo;            // ˿���������(m)
      double Force;            // ����������
   };
   CJack Jack[6];
private:
   void   RotateAroundZ(double Rst[3], double Src[3], double Angle);
   double Sigmoid(double Xi){return 2.0 / (exp(-2.0 * Xi / JackServoBuffer) + 1.0) - 1.0;}
   double LimitServo(double Servo);
   double CalcDeterminant(double FV[6][3], double TV[6][3]);
public:
   CRobot(void);
   void InitStructureParams(void);   // ��ʼ���ṹ����
public:
   // ����ƽ̨�߶Ƚ��й��㣬�����ǰ�װ��
   // ��Ҫ����Ϊ�����˶�ѧ�����ṩ��ʼλ��
   double CalcPlatformHeight(double JackLenght);   // ��6���˳���һ��ʱ��������ƽ̨�߶�
   double PlatformMinHeight(void);                 // ��ƽ̨��͸߶�
   double PlatformMaxHeight(void);                 // ��ƽ̨���߶�
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
   // ��ƽ̨λ�˿��ƣ�����������ƽ̨λ�ˣ��������˶�ѧ�������˳���
   // �������˶�ѧ����õ������˳����п��ܳ�������Լ����Χ�����ߵ�����ƽ̨��������㣬�������ʵ�ʳ�����Ҫ�ܵ�Լ����
   // ��ˣ���ƽ̨λ�˿��ư������¼��㲽�裺
   // 1. �ɸ���λ�˼������˳���
   // 2. ������˳����Ƿ񳬹������ޡ��������������ֵ���˳��ȡ�
   // 3. ����Ƿ���ܴ������졢���е����(Ŀǰ��û����)
   // 4. ���ڴ�����λ���ء��ٶ����޵�Լ�������˲�û����������ָ��λ�á���ˣ�ͨ�������˶�ѧ��������ƽ̨��ʵ��λ�ˡ�
   // ���������˶�ѧ������Ҫ�϶����ʱ�䣬��˽����ϲ����ֵ�PlatformMove()��AfterServoMoved()�����С�
   // PlatformMove()����ǰ3�����裬AfterServoMoved()������4.
   // ��ÿһ�ֿ����У����ò���Ӧ��Ϊ
   // 1. ����PlatformMove()�������˳���
   // 2. �����˳���������ŷ�������
   // 3. ����AfterServoMoved()���ڿ��Ƽ�϶��������˶�ѧ���㡣
   void PlatformMove(double X, double Y, double Z, double Yaw, double Pitch, double Roll, bool ServoLimited = true);
   void AfterServoMoved(double Servo1, double Servo2, double Servo3, double Servo4, double Servo5, double Servo6);
   void AfterServoMoved(void);
   void PlatformZeroed(void);
public:
   bool CalcForceOfJacks(double Force[3], double Torque[3]);
};
#endif
