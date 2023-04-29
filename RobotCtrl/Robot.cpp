//---------------------------------------------------------------------------


#pragma hdrstop

#include "Robot.h"
#include <math.h>
#include "GlobalDef.h"
#include "NRCpp\nr.h"

#ifdef __BORLANDC__
//#include "Unit1.h"
#else
#include "usart.h"
#include "led.h"
#endif

#ifndef M_PI
#define M_PI  3.1415926
#endif
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CRobot::CRobot(void)
{
   for(int i = 0; i < 6; ++i)
   {
      // ������ʼ��Ϊ0
      CopyVector(ErrJointUpper[i], 0, 0, 0);
      CopyVector(ErrJointLower[i], 0, 0, 0);
      ErrJackFixedLen[i]  = 0;

      Jack[i].Owner = this;
   }
}
//---------------------------------------------------------------------------
void CRobot::RotateAroundZ(double Rst[3], double Src[3], double Angle)
{
   double Deg = Angle * M_PI / 180.0;
   double M[3][3] = {cos(Deg), -sin(Deg), 0,
                     sin(Deg),  cos(Deg), 0,
                     0,         0,        1
                    };

   MatrixMultiVector(Rst, M, Src);
}
//---------------------------------------------------------------------------
void CRobot::SetJackLength(int ID, double Length)
{
   Jack[ID].Length = Length;
   Jack[ID].Servo  = Length - JackFixedLength - ErrJackFixedLen[ID];
}
//---------------------------------------------------------------------------
void CRobot::SetJackServo(int ID, double Servo)
{
   Jack[ID].Servo  = Servo;
   Jack[ID].Length = Servo + JackFixedLength + ErrJackFixedLen[ID];
}
//---------------------------------------------------------------------------
void CRobot::InitStructureParams(void)
{
   // ���û����˵Ľ½ӵ�����
   RobotIKP.SetStructureParams(UpperArmLength,   UpperBaseLength,
                               LowerArmLength,   LowerBaseLength,
                               UpperJointHeight, LowerJointHeight);
   RobotFKP.SetStructureParams(UpperArmLength,   UpperBaseLength,
                               LowerArmLength,   LowerBaseLength,
                               UpperJointHeight, LowerJointHeight);
   RobotIKP.SetStructureErrors(ErrJointUpper, ErrJointLower);
   RobotFKP.SetStructureErrors(ErrJointUpper, ErrJointLower);

   // ��ʼ�����˳���
   for(int i = 0; i < 6; ++i)
      SetJackLength(i, JackFixedLength);

   // ��������˵�Ĭ������λ��
   RobotFKP.DefaultZ = CenterZ = CalcPlatformHeight(JackFixedLength + JackServoLength * 0.5) + DEFAULT_Z_OFFSET;
   //RobotFKP.DefaultZ = CenterZ = CalcPlatformHeight(JackFixedLength);
   //RobotFKP.DefaultZ = CenterZ = INIT_Z_POSITION;

   // ��������ʼλ��
   CopyVector(RobotFKP.UpperPos, 0, 0, CenterZ);
   CopyVector(RobotFKP.UpperEuler, 0, 0, 0);
}
//---------------------------------------------------------------------------
// CalcPlatformHeight()
//---------------------------------------------------------------------------
double CRobot::CalcPlatformHeight(double JackLength)
{
   double L  = sqrt(LowerArmLength * LowerArmLength + LowerBaseLength * LowerBaseLength) * sin(M_PI / 3.0 - atan(LowerBaseLength / LowerArmLength));
   double h  = sqrt(JackLength * JackLength - pow(L - UpperBaseLength, 2.0));
   double Lb = sqrt(LowerArmLength * LowerArmLength + LowerBaseLength * LowerBaseLength) * cos(M_PI / 3.0 - atan(LowerBaseLength / LowerArmLength));
   double H  = sqrt(h * h - pow(UpperArmLength - Lb, 2.0));

   return H;
}
//---------------------------------------------------------------------------
// PlatformMinHeight()
//---------------------------------------------------------------------------
double CRobot::PlatformMinHeight(void)
{
   return CalcPlatformHeight(JackFixedLength);
   //return CalcPlatformHeight(JACK_FIXED_LENGTH + JackServoMin);
}
//---------------------------------------------------------------------------
// PlatformMaxHeight()
//---------------------------------------------------------------------------
double CRobot::PlatformMaxHeight(void)
{
   //return CalcPlatformHeight(JackFixedLength + JackServoMax);
   return CalcPlatformHeight(JackFixedLength + JackServoLength);
}
//---------------------------------------------------------------------------
double CRobot::LimitServo(double Servo)
{
   if(JackServoBuffer > 0)
   {
      if(Servo < JackServoBuffer)
         return Sigmoid(Servo - JackServoBuffer) * JackServoBuffer + JackServoBuffer;
      else if(Servo > JackServoLength - JackServoBuffer)
      {
         double Upper = JackServoLength - JackServoBuffer;
         return Sigmoid(Servo - Upper) * JackServoBuffer + Upper;
      }
      else
         return Servo;
   }
   else
   {
      if(Servo < 0)
         return 0;
      else if(Servo > JackServoLength)
         return JackServoLength;
      else
         return Servo;
   }
}
//---------------------------------------------------------------------------
// PlatformMove()
//---------------------------------------------------------------------------
void CRobot::PlatformMove(double X, double Y, double Z, double Yaw, double Pitch, double Roll, bool ServoLimited)
{       
   // �������˶�ѧ�������˳���
   RobotIKP.Move(X, Y, Z, Yaw, Pitch, Roll);

   // �������˳���
   SetJackLength(0, RobotIKP.JackLength[0]);
   SetJackLength(1, RobotIKP.JackLength[1]);
   SetJackLength(2, RobotIKP.JackLength[2]);
   SetJackLength(3, RobotIKP.JackLength[3]);
   SetJackLength(4, RobotIKP.JackLength[4]);
   SetJackLength(5, RobotIKP.JackLength[5]);

   // ������˳����Ƿ񳬹�������
   // ��������£���Ҫ��鲢��ֵ�˶���Χ
   // �����ڹ����ָ��м�λ��ʱ����׻����λ�˶���JackServoMinλ�ã�
   //   ��˴�ʱ�����Լ�����λ
   Constrained = false;
   if(ServoLimited)
   {
      for(int i = 0; i < 6; ++i)
      {
         double Servo = LimitServo(Jack[i].Servo);
         if(Servo != Jack[i].Servo)
         {
            SetJackServo(i, Servo);
            Constrained = true;
         }
      }
   }
}
//---------------------------------------------------------------------------
// AfterServoMoved()
// ע�⣺RobotIKP��RobotFKP֮�䲻��ͬ��
//---------------------------------------------------------------------------
void CRobot::AfterServoMoved(double Servo1, double Servo2, double Servo3, double Servo4, double Servo5, double Servo6)
{
   // �����˶�ѧ��������Լ������ʹ�������˶�ѧ����ʵ��λ��
   RobotFKP.Move(Servo1 + JackFixedLength + ErrJackFixedLen[0],
                 Servo2 + JackFixedLength + ErrJackFixedLen[1],
                 Servo3 + JackFixedLength + ErrJackFixedLen[2],
                 Servo4 + JackFixedLength + ErrJackFixedLen[3],
                 Servo5 + JackFixedLength + ErrJackFixedLen[4],
                 Servo6 + JackFixedLength + ErrJackFixedLen[5]);

   // �������˶�ѧ�����������������˶�ѧ������
   RobotIKP.Copy(RobotFKP);
}
void CRobot::AfterServoMoved(void)
{
   // �����˶�ѧ��������Լ������ʹ�������˶�ѧ����ʵ��λ��
   RobotFKP.Move(Jack[0].Length, Jack[1].Length, Jack[2].Length,
                 Jack[3].Length, Jack[4].Length, Jack[5].Length);

   // �������˶�ѧ�����������������˶�ѧ������
   RobotIKP.Copy(RobotFKP);
}
//-------------------------------------------------------------------------------
// PlatformZeroed()
// �����˶�̨����󣬻����˵ĳ�ʼλ��
// ��Ҫ��һ������
//-------------------------------------------------------------------------------
void CRobot::PlatformZeroed(void)
{
   float Z = PlatformMinHeight();
   CopyVector(RobotIKP.UpperPos, 0, 0, Z);
   CopyVector(RobotIKP.UpperEuler, 0, 0, 0);
}
//---------------------------------------------------------------------------
bool gaussj(Mat_IO_DP &a, Mat_IO_DP &b);
bool CRobot::CalcForceOfJacks(double Force[3], double Torque[3])
{
   // ����ÿ�������������ķ���ʸ��������Ϊ��ƽָ̨����ƽ̨(����Ĭ����������˳���ѹ��)
   double FV[6][3];
   for(int i = 0; i < 6; ++i)
   {
      FV[i][0] = RobotIKP.UpperJointInLowerCoordinate[i][0] - RobotIKP.LowerJointInLowerCoordinate[i][0];
      FV[i][1] = RobotIKP.UpperJointInLowerCoordinate[i][1] - RobotIKP.LowerJointInLowerCoordinate[i][1];
      FV[i][2] = RobotIKP.UpperJointInLowerCoordinate[i][2] - RobotIKP.LowerJointInLowerCoordinate[i][2];

      Normalize(FV[i]);
   }

   // ��������λ������ƽ̨����ϵ�е�����
   // ����������ʡ��Ϊ��ƽ̨���ģ�����������������ƽ̨��������
   double MidPos[3] = {RobotIKP.UpperPos[0], RobotIKP.UpperPos[1], RobotIKP.UpperPos[2]};
   //MatrixMultiVector(MidPos, __RMatrix, __Middle);
   //VectorAddVector(MidPos, MidPos, __UpperPos);

   // ��������ʸ������ʸ��Ӧ���ɽ½ӵ�ָ������
   double Arm[6][3];
   for(int i = 0; i < 6; ++i)
      VectorSubVector(Arm[i], RobotIKP.UpperJointInLowerCoordinate[i], MidPos);

   // ��������ʸ��������������������ʸ��������ʸ��֮��Ĳ��
   double TV[6][3];
   for(int i = 0; i < 6; ++i)
      CalcCrossProduct(TV[i], FV[i], Arm[i]);

   // ͨ��������Է��̻��ÿ�����˵���
   // ���Է��������ʽ���£�
   // F[0]FV[0] + F[1]FV[1] + ... + F[5]FV[5] = Force     (�������ĺ���������ƽ̨������)
   // F[0]TV[0] + F[1]TV[1] + ... + F[5]TV[5] = Torque    (�������صĺ����ص�����ƽ̨��������)
   Mat_DP M(6, 6);
   for(int i = 0; i < 6; ++i)
   {
      M[0][i] = FV[i][0];
      M[1][i] = FV[i][1];
      M[2][i] = FV[i][2];

      M[3][i] = TV[i][0];
      M[4][i] = TV[i][1];
      M[5][i] = TV[i][2];
   }

   // �ⲿ��������
   Mat_DP F(6, 1);
   F[0][0] = Force[0];
   F[1][0] = Force[1];
   F[2][0] = Force[2];

   F[3][0] = Torque[0];
   F[4][0] = Torque[1];
   F[5][0] = Torque[2];

   // ͨ����˹��Ԫ�����������
   bool rst = gaussj(M, F);
   if(rst)
   {
      for(int i = 0; i < 6; ++i)
         Jack[i].Force = F[i][0];
   }
   return rst;
}

bool gaussj(Mat_IO_DP &a, Mat_IO_DP &b)
{
	int i,icol,irow,j,k,l,ll;
	DP big,dum,pivinv;

	int n=a.nrows();
	int m=b.ncols();
	Vec_INT indxc(n),indxr(n),ipiv(n);
	for (j=0;j<n;j++) ipiv[j]=0;
	for (i=0;i<n;i++) {
		big=0.0;
		for (j=0;j<n;j++)
			if (ipiv[j] != 1)
				for (k=0;k<n;k++) {
					if (ipiv[k] == 0) {
						if (fabs(a[j][k]) >= big) {
							big=fabs(a[j][k]);
							irow=j;
							icol=k;
						}
					}
				}
		++(ipiv[icol]);
		if (irow != icol) {
			for (l=0;l<n;l++) SWAP(a[irow][l],a[icol][l]);
			for (l=0;l<m;l++) SWAP(b[irow][l],b[icol][l]);
		}
		indxr[i]=irow;
		indxc[i]=icol;
		if (a[icol][icol] == 0.0)   // ��������ֵ
                   return false;
		pivinv=1.0/a[icol][icol];
		a[icol][icol]=1.0;
		for (l=0;l<n;l++) a[icol][l] *= pivinv;
		for (l=0;l<m;l++) b[icol][l] *= pivinv;
		for (ll=0;ll<n;ll++)
			if (ll != icol) {
				dum=a[ll][icol];
				a[ll][icol]=0.0;
				for (l=0;l<n;l++) a[ll][l] -= a[icol][l]*dum;
				for (l=0;l<m;l++) b[ll][l] -= b[icol][l]*dum;
			}
	}
	for (l=n-1;l>=0;l--) {
		if (indxr[l] != indxc[l])
			for (k=0;k<n;k++)
				SWAP(a[k][indxr[l]],a[k][indxc[l]]);
	}
        return true;
}
