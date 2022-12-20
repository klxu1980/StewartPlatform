//---------------------------------------------------------------------------
// 2021.12.30�������������ٶȸı�������Ŀ��ƴ���

#pragma hdrstop

#include "JuneBugCtrl.h"
#include "GlobalDef.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// CJuneBugCtrl()
//---------------------------------------------------------------------------
CJuneBugCtrl::CJuneBugCtrl(void)
 : XYHeight(0.05)
{
   // ���û����˼��β���
   __Robot.UpperArmLength   = ROBOT_UPPER_ARM_LENGTH;
   __Robot.UpperBaseLength  = ROBOT_UPPER_BASE_LENGTH;
   __Robot.LowerArmLength   = ROBOT_LOWER_ARM_LENGTH;
   __Robot.LowerBaseLength  = ROBOT_LOWER_BASE_LENGTH;
   __Robot.UpperJointHeight = 0;
   __Robot.LowerJointHeight = 0;

   __Robot.JackFixedLength = JACK_FIXED_LENGTH;
   __Robot.JackServoLength = JACK_SERVO_LENGTH;
   __Robot.JackServoBuffer = JACK_SERVO_DEC;

   __Robot.InitStructureParams();

   MaxSpd[0] = 0.1;
   MaxSpd[1] = 0.1;
   MaxSpd[2] = 0.1;
   MaxSpd[3] = 10;
   MaxSpd[4] = 10;
   MaxSpd[5] = 10;

   MaxAcc[0] = 0.05;
   MaxAcc[1] = 0.05;
   MaxAcc[2] = 0.05;
   MaxAcc[3] = 5;
   MaxAcc[4] = 5;
   MaxAcc[5] = 5;

   Initialize();
}
//---------------------------------------------------------------------------
// Initialize()
//---------------------------------------------------------------------------
void CJuneBugCtrl::Initialize(void)
{
   __BugState = bsIdle;
   ScheduleIdleMovement();
}
//---------------------------------------------------------------------------
// Move()
//---------------------------------------------------------------------------
void CJuneBugCtrl::Move(void)
{
   switch(__BugState)
   {
   case bsIdle:
      StateIdle();
      break;
   case bsMoveUp:
   case bsMoveDown:
      StateMoveUpDown();
      break;
   case bsMoveUpDownIdle:
      StateMoveUpDownIdle();
      break;
   case bsMoveXYUpper:
   case bsMoveXYLower:
      StateMoveXY();
      break;
   case bsMoveXYIdleUpper:
   case bsMoveXYIdleLower:
      StateMoveXYIdle();
      break;
   }

   // ���չ켣�˶�
   MoveByTrace();
}
//---------------------------------------------------------------------------
// MoveRequired()
//---------------------------------------------------------------------------
bool CJuneBugCtrl::MoveRequired(void)
{
   return (Length(Dx, Dy) > 0.1 || fabs(Yaw) > 2.0) && Speed > 0.1;
}
//---------------------------------------------------------------------------
// CalcCubicParams()
//---------------------------------------------------------------------------
void CJuneBugCtrl::CalcCubicParams(float T, float x0, float v0, float x1, float v1, float a[4])
{
   a[0] = x0;
   a[1] = v0;
   a[2] = (3 * (x1 - x0) - (2 * v0 + v1) * T) / (T * T);
   a[3] = (2 * (x0 - x1) + (v0 + v1) * T) / (T * T * T);
}
//---------------------------------------------------------------------------
// MaxSpeedByCubic()
// �ҳ����ζ���ʽ�켣�е�����ٶ�
//---------------------------------------------------------------------------
float CJuneBugCtrl::MaxSpeedByCubic(float T, float a[4])
{
   // �Ƚ�0ʱ�̺�Tʱ�̵��ٶȣ��ҳ����ֵ
   float MaxSpd = Max(fabs(a[1]), fabs(a[1] + 2 * a[2] * T + 3 * a[3] * T * T));

   // ������ٶ�Ϊ0ʱ���ٶ�
   // a[3]�п��ܽӽ������0����ʱ���ٶȺ㶨���ٶ����ֵһ��������0ʱ�̻�Tʱ��
   if(fabs(a[3]) > 0.001)
   {
      float Ta = -a[2] / (3 * a[3]);
      if(Ta > 0 && Ta < T)
         MaxSpd = Max(fabs(a[1] + a[2] * Ta), MaxSpd);
   }

   return MaxSpd;
}
//---------------------------------------------------------------------------
// MaxAccByCubic()
// �ҳ����ζ���ʽ�켣�е������ٶ�
//---------------------------------------------------------------------------
float CJuneBugCtrl::MaxAccByCubic(float T, float a[4])
{
   return Max(fabs(2 * a[2]), fabs(2 * a[2] + 6 * a[3] * T));
}
//---------------------------------------------------------------------------
// MoveByTrace()
//---------------------------------------------------------------------------
void CJuneBugCtrl::MoveByTrace(void)
{
   for(int i = 0; i < 6; ++i)
      PosEuler[i] = PositionByCubic(__MoveTime, __TraceCubic[i]);
   PosEuler[2] += __Robot.CenterZ;

   __MoveTime += CTRL_INTERVAL;
}
//---------------------------------------------------------------------------
// ScheduleMovement()
// �������ζ���ʽ�滮ʱ��T�ڵ��˶��켣�������켣�Ƿ񳬳�����ٶȺͼ��ٶ�����
//---------------------------------------------------------------------------
bool CJuneBugCtrl::ScheduleMovement(float T, float Start[6], float VStart[6], float End[6], float VEnd[6])
{
   for(int i = 0; i < 6; ++i)
   {
      // �������ζ���ʽ�켣
      CalcCubicParams(T, Start[i], VStart[i], End[i], VEnd[i], __TraceCubic[i]);

      // �������ٶȺͼ��ٶ�
      float MaxSpd = MaxSpeedByCubic(T, __TraceCubic[i]);
      float MaxAcc = MaxAccByCubic(T, __TraceCubic[i]);

      float S = (__SpdInUse > 0.1)? __SpdInUse : 0.1;
      if(MaxSpd > this->MaxSpd[i] * S || MaxAcc > this->MaxAcc[i] * S)
         return false;
   }
   return true;
}
//---------------------------------------------------------------------------
// ScheduleMovement()
// ���ڶ��������滮�켣���ҳ������ٶȡ����ٶ�Լ�������·��
//---------------------------------------------------------------------------
void CJuneBugCtrl::ScheduleMovement(float Start[6], float VStart[6], float End[6], float VEnd[6])
{
   float T1 = 0.01;
   float T2 = 20;

   while(T2 - T1 > 0.05)
   {
      float T = (T1 + T2) * 0.5;
      if(ScheduleMovement(T, Start, VStart, End, VEnd) )
         T2 = T;
      else
         T1 = T;
   }
   ScheduleMovement(T2, Start, VStart, End, VEnd);

   __MoveTime = 0;
   __MaxMoveTime = T2;
}
//---------------------------------------------------------------------------
// ScheduleMovement()
// �����������˶�ʱ���µ��˶��켣����ʼλ�ú��ٶ�Ӧ����
// ǰһ�׶��˶��켣����ֹλ���ٶ�һ�£��Ӷ������ٶȼ��ٶ�ͻ��
//---------------------------------------------------------------------------
void CJuneBugCtrl::ScheduleMovement(float End[6], float VEnd[6])
{
   float Start[6] = {PositionByCubic(__MoveTime, __TraceCubic[0]),
                     PositionByCubic(__MoveTime, __TraceCubic[1]),
                     PositionByCubic(__MoveTime, __TraceCubic[2]),
                     PositionByCubic(__MoveTime, __TraceCubic[3]),
                     PositionByCubic(__MoveTime, __TraceCubic[4]),
                     PositionByCubic(__MoveTime, __TraceCubic[5])
                    };
   float VStart[6] = {SpeedByCubic(__MoveTime, __TraceCubic[0]),
                      SpeedByCubic(__MoveTime, __TraceCubic[1]),
                      SpeedByCubic(__MoveTime, __TraceCubic[2]),
                      SpeedByCubic(__MoveTime, __TraceCubic[3]),
                      SpeedByCubic(__MoveTime, __TraceCubic[4]),
                      SpeedByCubic(__MoveTime, __TraceCubic[5])
                     };
   ScheduleMovement(Start, VStart, End, VEnd);
}
//---------------------------------------------------------------------------
// ScheduleIdleMovement()
// ����������λ��ʱ���˶��켣Ϊ0�������˱��־�ֹ����
//---------------------------------------------------------------------------
void CJuneBugCtrl::ScheduleIdleMovement(void)
{
   for(int i = 0; i < 6; ++i)
   {
      __TraceCubic[i][0] = __TraceCubic[i][1] = __TraceCubic[i][2]
         = __TraceCubic[i][3] = 0;
   }
   __MoveTime = 0;
}
//---------------------------------------------------------------------------
// ScheduleXYMovement()
// �滮��������XYƽ���ϵ��˶��켣
//---------------------------------------------------------------------------
void CJuneBugCtrl::ScheduleXYMovement(float XYHeight, float Dx, float Dy, float Yaw)
{
   // Dx, DyΪ[-1, 1]֮��Ķ�������������ת��Ϊ(Dx, Dy, Step)��
   // ʹ(Dx, Dy)��ʾ����(Length(Dx, Dy) == 0)��Step \in [0, 1]��ʾ��Բ���
   float Step;
   float XYLen = Length(Dx, Dy);
   if(XYLen < 0.1)
      Step = Dx = Dy = 0;
   else
   {
      Dx  /= XYLen;
      Dy  /= XYLen;
      Step = Max(fabs(Dx), fabs(Dy));
   }
   
   if(XYHeight >= 0)
   {
      // ʵ���˶�����(m)����(Dx, Dy, Yaw)�����ϵ����ֱ���˶�����������Բ���
      float Dist = SearchForTheLargestXYStep(XYHeight, Dx, Dy, Yaw) * Step;

      // �켣ĩ��λ�˺��ٶ�(�ٶȾ�Ϊ0)
      float End[6]  = {Dist * Dx, Dist * Dy, XYHeight, Yaw, 0, 0};
      float VEnd[6] = {0, 0, 0, 0, 0, 0};

      // �滮ÿ������˶��켣
      ScheduleMovement(End, VEnd);
   }
   else
   {
      float Dist    = SearchForTheLargestXYStep(-XYHeight, -Dx, -Dy, -Yaw) * Step;
      float End[6]  = {-Dist * Dx, -Dist * Dy, XYHeight, -Yaw, 0, 0};
      float VEnd[6] = {0, 0, 0, 0, 0, 0};

      ScheduleMovement(End, VEnd);
   }
}
//---------------------------------------------------------------------------
// SearchForTheLargestStep()
// ���ö��ַ��������������ϵ���󲽳�
//---------------------------------------------------------------------------
float CJuneBugCtrl::SearchForTheLargestXYStep(float Z, float Dx, float Dy, float Yaw)
{
   if(Dx == 0 && Dy == 0)
      return 0;

   float L1 = 0;
   float L2 = 1;     // ��λ��m

   while(L2 - L1 > 0.001)
   {
      float L = (L1 + L2) * 0.5;
      float X = L * Dx;
      float Y = L * Dy;
      __Robot.PlatformMove(X, Y, Z + __Robot.CenterZ, Yaw, 0, 0);

      if(__Robot.Constrained)
         L2 = L;
      else
         L1 = L;
   }
   
   return L1;
}
//---------------------------------------------------------------------------
// StateIdle()
// �����˾�ֹ״̬
//---------------------------------------------------------------------------
void CJuneBugCtrl::StateIdle(void)
{
   if(MoveRequired())
   {
      // ��IDLE״̬ת���˶�ʱ�����������������˶���ʹ�������뿪����
      __BugState = bsMoveUp;

      // �滮�˶�·����������λ����XY��ƽ���˶�
      float End[6]  = {0, 0, XYHeight, 0, 0, 0};
      float VEnd[6] = {0, 0, 0, 0, 0, 0};

      __SpdInUse = Speed;
      ScheduleMovement(End, VEnd);
   }
   else
   {
      // û��Ҫ���˶����������ͣ��������λ��
      ScheduleIdleMovement();
   }
}
//---------------------------------------------------------------------------
// StateMoveUpDown()
// ��������Z�����ϻ������˶����Ӷ�ʹ��������������뿪����
//---------------------------------------------------------------------------
void CJuneBugCtrl::StateMoveUpDown(void)
{
   if(!MoveRequired())
   {
      // �˶������ͽǶ�Ϊ0����ع�����λ��
      __BugState = bsMoveUpDownIdle;

      // �滮�ع�����λ�õ��˶��켣
      float End[6]  = {0, 0, 0, 0, 0, 0};
      float VEnd[6] = {0, 0, 0, 0, 0, 0};

      ScheduleMovement(End, VEnd);
   }
   else if(__MoveTime >= __MaxMoveTime)
   {
      // ��ɹ켣������ǰһ״̬�жϵ�ǰ������ƽ�����ƽ��
      __SpdInUse = Speed;
      if(__BugState == bsMoveUp)
      {
         __BugState = bsMoveXYUpper;
         ScheduleXYMovement(XYHeight, Dx, Dy, Yaw);
      }
      else
      {
         __BugState = bsMoveXYLower;
         ScheduleXYMovement(-XYHeight, Dx, Dy, Yaw);
      }
   }
}
//----------------------------------------------------------------------------
// StateMoveUpDownIdle()
//----------------------------------------------------------------------------
void CJuneBugCtrl::StateMoveUpDownIdle(void)
{
   if(__MoveTime >= __MaxMoveTime)
   {
      __BugState = bsIdle;
      ScheduleIdleMovement();
   }
}
//----------------------------------------------------------------------------
// StateMoveXY()
//----------------------------------------------------------------------------
void CJuneBugCtrl::StateMoveXY(void)
{
   if(!MoveRequired())
   {
      // ����Ҫ���˶����ع�����λ��
      if(__BugState == bsMoveXYUpper)
      {
         __BugState = bsMoveXYIdleUpper;

         float End[6]  = {0, 0, XYHeight, 0, 0, 0};
         float VEnd[6] = {0, 0, 0, 0, 0, 0};
         ScheduleMovement(End, VEnd);
      }
      else
      {
         __BugState = bsMoveXYIdleLower;

         float End[6]  = {0, 0, -XYHeight, 0, 0, 0};
         float VEnd[6] = {0, 0, 0, 0, 0, 0};
         ScheduleMovement(End, VEnd);
      }
   }
   else if(__MoveTime >= __MaxMoveTime)
   {
      // �˶������п��ܷ����ı䣬�����Ҫ�ж��������㻹���������˶�������
      float Step1 = SearchForTheLargestXYStep(XYHeight, Dx, Dy, Yaw);
      float Step2 = SearchForTheLargestXYStep(-XYHeight, -Dx, -Dy, -Yaw);

      float CurX   = PositionByCubic(__MoveTime, __TraceCubic[0]);
      float CurY   = PositionByCubic(__MoveTime, __TraceCubic[1]);
      float CurYaw = PositionByCubic(__MoveTime, __TraceCubic[3]);

      CBugState NxtState;
      if(Length(CurX - Step1 * Dx, CurY - Step1 * Dy, (CurYaw - Yaw) * 0.1) >
         Length(CurX + Step2 * Dx, CurY + Step2 * Dy, (CurYaw + Yaw) * 0.1) )
      {
         NxtState = bsMoveXYUpper;
      }
      else
      {
         NxtState = bsMoveXYLower;
      }

      __SpdInUse = Speed;
      if(__BugState != NxtState)
      {
         float CurX   = PositionByCubic(__MoveTime, __TraceCubic[0]);
         float CurY   = PositionByCubic(__MoveTime, __TraceCubic[1]);
         float CurYaw = PositionByCubic(__MoveTime, __TraceCubic[3]);

         float DstHeight;
         if(NxtState == bsMoveXYLower)
         {
            __BugState = bsMoveDown;
            DstHeight  = -XYHeight;
         }
         else
         {
            __BugState = bsMoveUp;
            DstHeight  = XYHeight;
         }

         float End[6]  = {CurX, CurY, DstHeight, CurYaw, 0, 0};
         float VEnd[6] = {0, 0, 0, 0, 0, 0};
         ScheduleMovement(End, VEnd);
      }
      else
      {
         __BugState = NxtState;
         if(NxtState == bsMoveXYLower)
            ScheduleXYMovement(-XYHeight, Dx, Dy, Yaw);
         else
            ScheduleXYMovement(XYHeight, Dx, Dy, Yaw);
      }
   }
}
//----------------------------------------------------------------------------
// StateMoveXYIdle()
//----------------------------------------------------------------------------
void CJuneBugCtrl::StateMoveXYIdle(void)
{
   if(__MoveTime >= __MaxMoveTime)
   {
      if(MoveRequired())
      {
         __SpdInUse = Speed;
         if(__BugState == bsMoveXYIdleUpper)
         {
            __BugState = bsMoveXYUpper;
            ScheduleXYMovement(XYHeight, Dx, Dy, Yaw);
         }
         else
         {
            __BugState = bsMoveXYLower;
            ScheduleXYMovement(-XYHeight, Dx, Dy, Yaw);
         }
      }
      else
      {
         // �Ѿ��˶�������λ�ã���ֱ�˶�������λ��
         __BugState = bsMoveUpDownIdle;

         float End[6]  = {0, 0, 0, 0, 0, 0};
         float VEnd[6] = {0, 0, 0, 0, 0, 0};
         ScheduleMovement(End, VEnd);
      }
   }
}
