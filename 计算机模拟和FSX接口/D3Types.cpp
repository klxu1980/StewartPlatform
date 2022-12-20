//---------------------------------------------------------------------------


#pragma hdrstop

#include "D3Types.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
void CVector::Normalize(void)
{
   double Normal = Length();
   if(Normal != 0.0)
   {
      X /= Normal;
      Y /= Normal;
      Z /= Normal;
   }
   else
   {
      X = 0.0;
      Y = 0.0;
      Z = 1.0;
   }
}
//---------------------------------------------------------------------------
// VectorMulMatrix()
// 向量乘变换矩阵
//---------------------------------------------------------------------------
CVector MatrixMulVector(double M[3][3], CVector Vi)
{
   return CVector(M[0][0] * Vi.X + M[0][1] * Vi.Y + M[0][2] * Vi.Z,
                  M[1][0] * Vi.X + M[1][1] * Vi.Y + M[1][2] * Vi.Z,
                  M[2][0] * Vi.X + M[2][1] * Vi.Y + M[2][2] * Vi.Z);
}
//---------------------------------------------------------------------------
// CMatrix3()
//---------------------------------------------------------------------------
CMatrix3::CMatrix3(double M[3][3])
{
   for(int Row = 0; Row < 3; ++Row)
      for(int Col = 0; Col < 3; ++Col)
         CMatrix3::M[Row][Col] = M[Row][Col];
}
//---------------------------------------------------------------------------
// CMatrix3::operator * ()
//---------------------------------------------------------------------------
CMatrix3 CMatrix3::operator * (CMatrix3 &Matrix)
{
   CMatrix3 NM;

   NM.M[0][0] = M[0][0] * Matrix.M[0][0] + M[0][1] * Matrix.M[1][0] + M[0][2] * Matrix.M[2][0];
   NM.M[0][1] = M[0][0] * Matrix.M[0][1] + M[0][1] * Matrix.M[1][1] + M[0][2] * Matrix.M[2][1];
   NM.M[0][2] = M[0][0] * Matrix.M[0][2] + M[0][1] * Matrix.M[1][2] + M[0][2] * Matrix.M[2][2];

   NM.M[1][0] = M[1][0] * Matrix.M[0][0] + M[1][1] * Matrix.M[1][0] + M[1][2] * Matrix.M[2][0];
   NM.M[1][1] = M[1][0] * Matrix.M[0][1] + M[1][1] * Matrix.M[1][1] + M[1][2] * Matrix.M[2][1];
   NM.M[1][2] = M[1][0] * Matrix.M[0][2] + M[1][1] * Matrix.M[1][2] + M[1][2] * Matrix.M[2][2];

   NM.M[2][0] = M[2][0] * Matrix.M[0][0] + M[2][1] * Matrix.M[1][0] + M[2][2] * Matrix.M[2][0];
   NM.M[2][1] = M[2][0] * Matrix.M[0][1] + M[2][1] * Matrix.M[1][1] + M[2][2] * Matrix.M[2][1];
   NM.M[2][2] = M[2][0] * Matrix.M[0][2] + M[2][1] * Matrix.M[1][2] + M[2][2] * Matrix.M[2][2];

   return NM;
}
CMatrix3 CMatrix3::operator * (double Matrix[3][3])
{
   CMatrix3 NM;

   NM.M[0][0] = M[0][0] * Matrix[0][0] + M[0][1] * Matrix[1][0] + M[0][2] * Matrix[2][0];
   NM.M[0][1] = M[0][0] * Matrix[0][1] + M[0][1] * Matrix[1][1] + M[0][2] * Matrix[2][1];
   NM.M[0][2] = M[0][0] * Matrix[0][2] + M[0][1] * Matrix[1][2] + M[0][2] * Matrix[2][2];

   NM.M[1][0] = M[1][0] * Matrix[0][0] + M[1][1] * Matrix[1][0] + M[1][2] * Matrix[2][0];
   NM.M[1][1] = M[1][0] * Matrix[0][1] + M[1][1] * Matrix[1][1] + M[1][2] * Matrix[2][1];
   NM.M[1][2] = M[1][0] * Matrix[0][2] + M[1][1] * Matrix[1][2] + M[1][2] * Matrix[2][2];

   NM.M[2][0] = M[2][0] * Matrix[0][0] + M[2][1] * Matrix[1][0] + M[2][2] * Matrix[2][0];
   NM.M[2][1] = M[2][0] * Matrix[0][1] + M[2][1] * Matrix[1][1] + M[2][2] * Matrix[2][1];
   NM.M[2][2] = M[2][0] * Matrix[0][2] + M[2][1] * Matrix[1][2] + M[2][2] * Matrix[2][2];

   return NM;
}
//---------------------------------------------------------------------------
// 矩阵乘以矩阵
//---------------------------------------------------------------------------
void MatrixMulMatrix(double M1[3][3], double M2[3][3], double M[3][3])
{
   M[0][0] = M1[0][0] * M2[0][0] + M1[0][1] * M2[1][0] + M1[0][2] * M2[2][0];
   M[0][1] = M1[0][0] * M2[0][1] + M1[0][1] * M2[1][1] + M1[0][2] * M2[2][1];
   M[0][2] = M1[0][0] * M2[0][2] + M1[0][1] * M2[1][2] + M1[0][2] * M2[2][2];

   M[1][0] = M1[1][0] * M2[0][0] + M1[1][1] * M2[1][0] + M1[1][2] * M2[2][0];
   M[1][1] = M1[1][0] * M2[0][1] + M1[1][1] * M2[1][1] + M1[1][2] * M2[2][1];
   M[1][2] = M1[1][0] * M2[0][2] + M1[1][1] * M2[1][2] + M1[1][2] * M2[2][2];

   M[2][0] = M1[2][0] * M2[0][0] + M1[2][1] * M2[1][0] + M1[2][2] * M2[2][0];
   M[2][1] = M1[2][0] * M2[0][1] + M1[2][1] * M2[1][1] + M1[2][2] * M2[2][1];
   M[2][2] = M1[2][0] * M2[0][2] + M1[2][1] * M2[1][2] + M1[2][2] * M2[2][2];
}
//---------------------------------------------------------------------------
// 矩阵左乘列向量
//---------------------------------------------------------------------------
CVector CMatrix3::operator * (CVector &Vector)
{
   CVector Rst;
   Rst.X = M[0][0] * Vector.X + M[0][1] * Vector.Y + M[0][2] * Vector.Z;
   Rst.Y = M[1][0] * Vector.X + M[1][1] * Vector.Y + M[1][2] * Vector.Z;
   Rst.Z = M[2][0] * Vector.X + M[2][1] * Vector.Y + M[2][2] * Vector.Z;

   return Rst;
}
//---------------------------------------------------------------------------
// LeftMultiply()
//---------------------------------------------------------------------------
void CMatrix3::LeftMultiply(double TransM[3][3])
{
   CMatrix3 NM;

   NM.M[0][0] = TransM[0][0] * M[0][0] + TransM[0][1] * M[1][0] + TransM[0][2] * M[2][0];
   NM.M[0][1] = TransM[0][0] * M[0][1] + TransM[0][1] * M[1][1] + TransM[0][2] * M[2][1];
   NM.M[0][2] = TransM[0][0] * M[0][2] + TransM[0][1] * M[1][2] + TransM[0][2] * M[2][2];

   NM.M[1][0] = TransM[1][0] * M[0][0] + TransM[1][1] * M[1][0] + TransM[1][2] * M[2][0];
   NM.M[1][1] = TransM[1][0] * M[0][1] + TransM[1][1] * M[1][1] + TransM[1][2] * M[2][1];
   NM.M[1][2] = TransM[1][0] * M[0][2] + TransM[1][1] * M[1][2] + TransM[1][2] * M[2][2];

   NM.M[2][0] = TransM[2][0] * M[0][0] + TransM[2][1] * M[1][0] + TransM[2][2] * M[2][0];
   NM.M[2][1] = TransM[2][0] * M[0][1] + TransM[2][1] * M[1][1] + TransM[2][2] * M[2][1];
   NM.M[2][2] = TransM[2][0] * M[0][2] + TransM[2][1] * M[1][2] + TransM[2][2] * M[2][2];

   *this = NM;
}
//---------------------------------------------------------------------------
// 将角度归一化为 -360 ~ +360之间
//---------------------------------------------------------------------------
double NormalizeAngle(double Angle)
{
   return Angle - int(Angle / 360.0) * 360.0;
}