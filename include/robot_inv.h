 #ifndef __robot_inv_h__
 #define __robot_inv_h__
 
 #include <stdio.h>
 #include <math.h>
 #include <string.h>
 #include <stdlib.h>
 
 #define   PI 3.14159265
 
	extern float PL1, Pl1, PL2, Pl2;                                               //上下平台长臂和短臂长度
	extern float UpPlatformAngle;                                                  //上平台角度
	extern float DownPlatformAngle;                                                //下平台角度
	extern float MinLinkLength;
	extern float MaxLinkLength;
	
	
	extern float OriginX, OriginY, OriginZ, Yaw, Pitch, Roll;                      //六个自由度
	                                                                       
	extern float Origin[3];                                                        //上平台中心点坐标
	extern float RotateMatrix[3][3];                                               //旋转矩阵
	extern float UpGemelMatrix[3][6];                                              //上平台铰链点在上平台坐标系中的坐标矩阵
	extern float UpGemelMatrixInAll[3][6];                                         //上平台铰链点在全局坐标系中的坐标矩阵
	extern float DownGemelMatrix[3][6];                                            //下平台铰链点在下平台坐标系中的坐标矩阵
	                                                                       
	extern float L[6];                                                //六个杆长
	extern int Pulse[6];
	extern int PulsePerRound;
	extern float MMPerRound;
	
	extern float Pointa[3], Pointb[3], Pointc[3], Pointd[3], Pointe[3], Pointf[3]; //上平台铰链点在全局坐标系中的坐标矩阵转换后的坐标
	extern float PointA[3], PointB[3], PointC[3], PointD[3], PointE[3], PointF[3]; //下平台铰链点在全局坐标系中的坐标矩阵转换后的坐标
	
	extern int x[1000],y[1000],z[1000];
  extern int alfa[1000],beta[1000],gama[1000];
  //extern double L1_[50],L2_[50],L3_[50],L4_[50],L5_[50],L6_[50];

  void SetBasicParameter(void);
	void SetControlParameter(float OriginX_, float OriginY_, float OriginZ_, float Yaw_, float Pitch_, float Roll_);
	void CaculateMatrix(void);                                                  //计算矩阵
	void MatrixToPoint(void);                                                   //矩阵转换成坐标点
	void CaculateRodLength(void);                                               //计算杆长
	void LengthToPulseCnt(void);                                                    //连杆长度转换为脉冲个数
	void Inverse_Kinematics(float _X_, float _Y_, float _Z_, float _Yaw_, float _Pitch_, float _Roll_);
  void LinesControl(int *beginposition, int *endposition, int Point_Count);
  void CurveControl(
      double t1,double t2,
      double alfa1, double beta1, double gama1,
      double alfa2, double beta2, double gama2,
      int Point_Count, int BeginDot
      );

 #endif //__robot_inv_h__

