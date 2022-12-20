 #ifndef __robot_inv_h__
 #define __robot_inv_h__
 
 #include <stdio.h>
 #include <math.h>
 #include <string.h>
 #include <stdlib.h>
 
 #define   PI 3.14159265
 
	extern float PL1, Pl1, PL2, Pl2;                                               //����ƽ̨���ۺͶ̱۳���
	extern float UpPlatformAngle;                                                  //��ƽ̨�Ƕ�
	extern float DownPlatformAngle;                                                //��ƽ̨�Ƕ�
	extern float MinLinkLength;
	extern float MaxLinkLength;
	
	
	extern float OriginX, OriginY, OriginZ, Yaw, Pitch, Roll;                      //�������ɶ�
	                                                                       
	extern float Origin[3];                                                        //��ƽ̨���ĵ�����
	extern float RotateMatrix[3][3];                                               //��ת����
	extern float UpGemelMatrix[3][6];                                              //��ƽ̨����������ƽ̨����ϵ�е��������
	extern float UpGemelMatrixInAll[3][6];                                         //��ƽ̨��������ȫ������ϵ�е��������
	extern float DownGemelMatrix[3][6];                                            //��ƽ̨����������ƽ̨����ϵ�е��������
	                                                                       
	extern float L[6];                                                //�����˳�
	extern int Pulse[6];
	extern int PulsePerRound;
	extern float MMPerRound;
	
	extern float Pointa[3], Pointb[3], Pointc[3], Pointd[3], Pointe[3], Pointf[3]; //��ƽ̨��������ȫ������ϵ�е��������ת���������
	extern float PointA[3], PointB[3], PointC[3], PointD[3], PointE[3], PointF[3]; //��ƽ̨��������ȫ������ϵ�е��������ת���������
	
	extern int x[1000],y[1000],z[1000];
  extern int alfa[1000],beta[1000],gama[1000];
  //extern double L1_[50],L2_[50],L3_[50],L4_[50],L5_[50],L6_[50];

  void SetBasicParameter(void);
	void SetControlParameter(float OriginX_, float OriginY_, float OriginZ_, float Yaw_, float Pitch_, float Roll_);
	void CaculateMatrix(void);                                                  //�������
	void MatrixToPoint(void);                                                   //����ת���������
	void CaculateRodLength(void);                                               //����˳�
	void LengthToPulseCnt(void);                                                    //���˳���ת��Ϊ�������
	void Inverse_Kinematics(float _X_, float _Y_, float _Z_, float _Yaw_, float _Pitch_, float _Roll_);
  void LinesControl(int *beginposition, int *endposition, int Point_Count);
  void CurveControl(
      double t1,double t2,
      double alfa1, double beta1, double gama1,
      double alfa2, double beta2, double gama2,
      int Point_Count, int BeginDot
      );

 #endif //__robot_inv_h__

