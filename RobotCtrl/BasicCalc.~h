//---------------------------------------------------------------------------

#ifndef BasicCalcH
#define BasicCalcH
#ifdef __BORLANDC__
#endif
//---------------------------------------------------------------------------
void   MatrixMultiMatrix(double Rst[3][3], double M1[3][3], double M2[3][3]);   // Rst = M1*M2
void   TransMatrix(double Rst[3][3], double Src[3][3]);
void   MatrixMultiVector(double Rst[3], double M[3][3], double V[3]);     // 矩阵左乘向量(注意：Rst和V不能是同一个变量)
void   VectorAddVector(double Rst[3], double V1[3], double V2[3]);        // 向量加
void   VectorSubVector(double Rst[3], double V1[3], double V2[3]);        // 向量减
void   CalcCrossProduct(double Rst[3], double V1[3], double V2[3]);       // 向量叉积
void   VectorMultiScale(double Rst[3], double V[3], double Scale);
void   Normalize(double Vector[3]);                                       // 向量归一化
void   CopyVector(double Dst[3], double Src[3]);                          // 拷贝向量
void   CopyVector(double Dst[3], double x, double y, double z);
double VectorLength(double V[3]);
double Distance(double P1[3], double P2[3]);
double Limit(double Value, double Range);
double Limit(double Value, double Min, double Max);
void   RotateMatrixX(double M[3][3], double Angle);
void   RotateMatrixY(double M[3][3], double Angle);
void   RotateMatrixZ(double M[3][3], double Angle);
void   RotateMatrixByEuler(double M[3][3], double Euler[3]);
void   EulerByTriangle(double Euler[3], double Vx[3], double Vy[3]);
void   PosEulerByTriangle(double Pos[3], double Euler[3], double M1[3], double M2[3], double M3[3]);
#endif
