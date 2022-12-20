//---------------------------------------------------------------------------


#pragma hdrstop

#include "Matrix.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CMatrix::CMatrix(int Row, int Col)
 : __MVVector(Row)
{
   __RowSize = Row;
   __ColSize = Col;
   __Element = new double[Row * Col];
}
//---------------------------------------------------------------------------
void CMatrix::Randomize(void)
{
   for(int i = 0; i < __RowSize * __ColSize; ++i)
      __Element[i] = SampleNormal();//random(20000) * 0.0001 - 1.0;
}
//---------------------------------------------------------------------------
// 矩阵左乘向量
//---------------------------------------------------------------------------
CVector& CMatrix::operator * (CVector &Vector)
{
   #ifdef __CHECK_DIMENSION__
   if(__ColSize != Vector.Size())
      throw Exception("矩阵左乘向量时维度不匹配");
   #endif
   
   double *VDst = __MVVector.__Element;
   double *M    = __Element;

   for(int Row = 0; Row < __RowSize; ++Row, ++VDst)
   {
      *VDst = 0;

      double *V    = Vector.__Element;
      double *VEnd = Vector.__Element + Vector.__Size;
      for(; V != VEnd; ++V, ++M)
         *VDst += *M * *V;
   }

   return __MVVector;
}
//---------------------------------------------------------------------------
void CMatrix::Trans(CMatrix &M)
{
   #ifdef __CHECK_DIMENSION__
   if(__RowSize != M.__ColSize || __ColSize != M.__RowSize)
      throw Exception("矩阵转置时维度不匹配");
   #endif

   /*
   double *Dst = __Element;
   for(int Row = 0; Row < __RowSize; ++Row)
   {
      double *Src = M.__Element + Row;

      for(int Col = 0; Col < __ColSize; ++Col)
      {
         *Dst = *Src;
         ++Dst;
         Src += __RowSize;
      }
   }
   */

   for(int R = 0; R < __RowSize; ++R)
      for(int C = 0; C < __ColSize; ++C)
         *(__Element + R * __ColSize + C) = M(C, R);
}
//---------------------------------------------------------------------------
double CMatrix::operator = (double Value)
{
   double *Dst    = __Element;
   double *DstEnd = Dst + __RowSize * __ColSize;

   for(; Dst != DstEnd; ++Dst)
      *Dst = Value;

   return Value;
}
//---------------------------------------------------------------------------
void CMatrix::operator *= (double Value)
{
   double *Dst    = __Element;
   double *DstEnd = __Element + __RowSize * __ColSize;

   for(; Dst != DstEnd; ++Dst)
      *Dst *= Value;
}
//---------------------------------------------------------------------------
void CMatrix::operator += (CMatrix &M)
{
   #ifdef __CHECK_DIMENSION__
   if(__RowSize != M.__RowSize || __ColSize != M.__ColSize)
      throw Exception("矩阵相加时维度不匹配");
   #endif

   double *Src    = M.__Element;
   double *Dst    = __Element;
   double *DstEnd = __Element + __RowSize * __ColSize;

   for(; Dst != DstEnd; ++Src, ++Dst)
      *Dst += *Src;
}
//---------------------------------------------------------------------------
void CMatrix::operator += (double Value)
{
   double *Dst    = __Element;
   double *DstEnd = __Element + __RowSize * __ColSize;

   for(; Dst != DstEnd; ++Dst)
      *Dst += Value;
}
//---------------------------------------------------------------------------
void CMatrix::operator -= (CMatrix &M)
{
   #ifdef __CHECK_DIMENSION__
   if(__RowSize != M.__RowSize || __ColSize != M.__ColSize)
      throw Exception("矩阵相减时维度不匹配");
   #endif

   double *Src    = M.__Element;
   double *Dst    = __Element;
   double *DstEnd = __Element + __RowSize * __ColSize;

   for(; Dst != DstEnd; ++Src, ++Dst)
      *Dst -= *Src;
}
//---------------------------------------------------------------------------
void CMatrix::AddVectorMultVector(CVector &VC, CVector &VR)
{
   #ifdef __CHECK_DIMENSION__
   if(__RowSize != VC.__Size || __ColSize != VR.__Size)
      throw Exception("向量相乘时维度不匹配");
   #endif

   double *M = __Element;

   double *C    = VC.__Element;
   double *CEnd = VC.__Element + VC.__Size;
   for(; C != CEnd; ++C)
   {
      double *R    = VR.__Element;
      double *REnd = VR.__Element + VR.__Size;
      for(; R != REnd; ++R)
      {
         *M += *R * *C;
         ++M;
      }
   }
}
//---------------------------------------------------------------------------
void CMatrix::Save(TStream *Stream)
{
   Stream->Write(__Element, __RowSize * __ColSize * sizeof(double));
}
//---------------------------------------------------------------------------
void CMatrix::Load(TStream *Stream)
{
   Stream->Read(__Element, __RowSize * __ColSize * sizeof(double));
}
//---------------------------------------------------------------------------
// 二维卷积计算
// 对SrcM做卷积，结果保存在当前矩阵中
//---------------------------------------------------------------------------
void CMatrix::Convolve(CMatrix &SrcM, CMatrix &Weights)
{
   #ifdef __CHECK_DIMENSION__
   if(SrcM.__RowSize != __RowSize + Weights.__RowSize - 1 ||
      SrcM.__ColSize != __ColSize + Weights.__ColSize - 1)
   {
      throw Exception("矩阵卷积时维度不匹配");
   }
   #endif

   double *M    = __Element;
   double *MEnd = __Element + __RowSize * __ColSize;

   for(; M != MEnd; ++M)
   {
      unsigned int Dist = M - __Element;
      unsigned int Row  = Dist / __ColSize;
      unsigned int Col  = Dist % __ColSize;

      *M = 0;
      for(int r = 0; r < Weights.__RowSize; ++r)
         for(int c = 0; c < Weights.__ColSize; ++c)
            *M += SrcM(Row + r, Col + c) * Weights(r, c);
   }
}