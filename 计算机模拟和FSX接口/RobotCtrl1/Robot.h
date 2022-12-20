//---------------------------------------------------------------------------

#ifndef RobotH
#define RobotH
#include <math.h>
#include "nr.h"
//---------------------------------------------------------------------------
// ע�⣺�ڼ��������ʹ�õ�����������ϵ����ƽ̨����ϵ����ƽ̨����ϵ
// ��ƽ̨����ϵҲ��Ϊȫ������ϵ��������ϵ
// ��ƽ̨����ϵ��������ϵ��
// ����X������Ļ�������ң�Y�ᴹֱ��Ļ�������⣬Z������Ļ��������
//
//    |-------------------------- X
//    | \
//    |  \
//    |   \
//    |    \
//    |     \
//    |Z     \ Y
//
// ��ƽ̨����ϵ����ƽ̨����ϵ������ͬ
//
// ����ƽ̨���˽½ӵ��Ŷ��壺
//      ����            1    2   3   4   5    6
//  ��ƽ̨�½ӵ�        1    2   3   4   5    6
//  ��ƽ̨�½ӵ�        4    5   6   1   2    3
//---------------------------------------------------------------------------
enum CMoveStatus
{
   msOk,
   msJackOutofRange,       // ���˳�������
   msSingular,             // �����
   msJackCollision         // ��������
};

//==========================================================================
// CRobotIKP
// �����������˶�ѧ���
//==========================================================================
class CRobot
{
protected:   // ��е�ߴ����
   double  __UpperArmLength;         // ��ƽ̨���۳���
   double  __UpperBaseLength;        // ��ƽ̨�̱۳���
   double  __LowerArmLength;         // ��ƽ̨���۳���
   double  __LowerBaseLength;        // ��ƽ̨�̱۳���
protected:
   double  __MinJackL;               // ������С����
   double  __MaxJackL;               // ������󳤶�
   double  __JackDiameter;           // ����ֱ��
protected:
   // ��ƽ̨λ��
   double  __UpperPos[3];            // ��ƽ̨ԭ������(X, Y, Z)����λm
   double  __UpperEurlar[3];         // ��ƽ̨ŷ����(Yaw-Pitch-Roll, ����-��-��)����λ��
   double  __UpperOrig[6][3];        // ��ƽ̨6���µ�����ƽ̨����ϵ�µ�����
protected:
   double  __JackLength[6];          // �������˳���(�����˶�ѧ������)
public:
   // ֱ������
   struct  CJack
   {
   public:
      double UpperJoint[3];          // �ϻ��˽�ȫ������ϵ����
      double LowerJoint[3];          // �»��˽�ȫ������ϵ����
      double Length;                 // ���˳���
      double ServoLength;            // ˿���������
      double Force;                  // ����������
   };
   CJack Jacks[6];
protected:  // �����;������
   double Degree2Rad(double Degree){return Degree * M_PI / 180.0;}           // �ǶȻ���Ϊ����
   void   MatrixMultiVector(double Rst[3], double M[3][3], double V[3]);     // �����������
   void   VectorAddVector(double Rst[3], double V1[3], double V2[3]);        // ������
   void   VectorSubVector(double Rst[3], double V1[3], double V2[3]);        // ������
   void   CalcCrossProduct(double Rst[3], double V1[3], double V2[3]);       // �������
   void   Normalize(double Vector[3]);                                       // ������һ��
   void   CopyVector(double Dst[3], double Src[3]);                          // ��������
   void   CopyVector(double Dst[3], double x, double y, double z);
protected:   // �����˶�ѧ����
   void   UpperPlatformJointsCoordition(double Joints[6][3]);                       // ��ƽ̨�½ӵ�����ƽ̨����ϵ�е�����
   void   LowerPlatformJointsCoordition(double Joints[6][3]);                       // ��ƽ̨�½ӵ�����ƽ̨����ϵ�е�����
   void   CalcRotateMatrix(double Pys, double Theta, double Rho, double M[3][3]);   // ������ת��
   void   CalcJackLength(double Pos[3], double Eurlar[3]);                          // �������˳���(������ƽ̨λ�ú���̬)
   CMoveStatus Move(void);
private:
   bool   IsJackLengthFeasibility(void);          // ���˳����Ƿ�������Χ��
   bool   NoSingularityExists(void);              // �Ƿ���������
private:
   bool   CalcJackBetweenLines(double A1[3], double A2[3],      // ��������ֱ��(A1, A2�����һ����B1, B2����ڶ���)֮��ķ���(���ΪA, B)
                               double B1[3], double B2[3],
                               double A[3],  double B[3]);
   bool   IsPointInSegment(double A1[3], double B1[3], double A[3]);            // �жϵ��Ƿ����߶���
   bool   JackKnocked(double A1[3], double A2[3], double B1[3], double B2[3]);  // �ж����������Ƿ�����
   bool   IsJackKnocked(void);                                                  // �ж��Ƿ�����������
protected:   // �����˶�ѧ����
   double ErrorFunc(double Pos[3], double Eurlar[3]);                           // ������
   DP     ErrorFunc(Vec_I_DP &UpperPlatform);                                   // ������
   double ErrorFunc(double UpperPlatform[6]);                                   // ������
   void   get_psum(Mat_I_DP &p, Vec_O_DP &psum);                                // �����η�������������ά�Ż�
   bool   amoeba(Mat_IO_DP &p, Fec_IO_DP &y, const DP ftol, int &nfunk);
   DP     amotry(Mat_IO_DP &p, Vec_O_DP &y, Vec_IO_DP &psum, const int ihi, const DP fac);
public:
   CRobot(void);
public:
   void   SetPlatformSize(double UpperArmLength,                   // ��������ƽ̨�ߴ�
                          double UpperBaseLength,
                          double LowerArmLength,
                          double LowerBaseLength);
   void   SetMinMaxJackLength(double MinL, double MaxL);           // �������˳���������
   void   SetJackDiameter(double V);                               // �������˰뾶
public:
   CMoveStatus Move(double Pos[3], double Eurlar[3]);              // �������˶�
   CMoveStatus Move(double X, double Y, double Z,
                    double Yaw, double Pitch, double Roll);
   void Zeroed(void);                                              // �����˹���
   void SetJackLength(int JackID, double ServoLength);          
public:
   double MinJackLength(void){return __MinJackL;}
   double MaxJackLength(void){return __MaxJackL;}
public:
   double PosX(void){return __UpperPos[0];}
   double PosY(void){return __UpperPos[1];}
   double PosZ(void){return __UpperPos[2];}
   double PosYaw(void)  {return __UpperEurlar[0];}
   double PosPitch(void){return __UpperEurlar[1];}
   double PosRoll(void) {return __UpperEurlar[2];}
public:
   // ������ƽ̨����ϵ�е�����ƽ̨����ϵ�е�����
   void CalcGlobalCoordination(double X, double Y, double Z, double Yaw, double Pitch, double Roll,
                               double PosLocal[][3], double PosGlobal [][3], int Count);
   bool CalcUpperPlatformPosEurlar(double JackLength[6], double &X, double &Y, double &Z, double &Yaw, double &Pitch, double &Roll);
   bool UpdateUpperPlatformPosEurlar(void);
public:
   double CalcPlatformHeight(double JackLenght);   // ��6���˳���һ��ʱ��������ƽ̨�߶�
   double PlatformMinHeight(void);                 // ��ƽ̨��͸߶�
   double PlatformMaxHeight(void);                 // ��ƽ̨���߶�
};
#endif
