//---------------------------------------------------------------------------

#ifndef D3TypesH
#define D3TypesH
#include <math.h>
//---------------------------------------------------------------------------
// 向量
//---------------------------------------------------------------------------
struct CVector
{
public:
   double  X;
   double  Y;
   double  Z;
public:
   CVector(void) : X(0), Y(0), Z(0) {}
   CVector(double X, double Y, double Z) : X(X), Y(Y), Z(Z) {}
public:
   double Length(void){return sqrt(X * X + Y * Y + Z * Z);}
   void   Normalize(void);
public:
   // 向量相加、相减
   CVector operator + (CVector Vector)
   {
      return CVector(X + Vector.X, Y + Vector.Y, Z + Vector.Z);
   }
   CVector operator - (CVector Vector)
   {
      return CVector(X - Vector.X, Y - Vector.Y, Z - Vector.Z);
   }
   CVector operator / (CVector Vector)
   {
      return CVector(X / Vector.X, Y / Vector.Y, Z / Vector.Z);
   }
public:
   CVector operator * (double Ratio)
   {
      return CVector(X * Ratio, Y * Ratio, Z * Ratio);
   }
   double operator * (CVector Vector)
   {
      return X * Vector.X + Y * Vector.Y + Z * Vector.Z;
   }
   CVector operator ^ (CVector Vector)
   {
      return CVector(Y * Vector.Z - Z * Vector.Y,
                     Z * Vector.X - X * Vector.Z,
                     X * Vector.Y - Y * Vector.X);
   }
};
//---------------------------------------------------------------------------
// CMatrix3
//---------------------------------------------------------------------------
class CMatrix3
{
public:
   double M[3][3];      // 注意：先行后列
public:
   CMatrix3(void) {}
   CMatrix3(double M[3][3]);
public:
   CMatrix3 operator * (CMatrix3 &Matrix);
   CMatrix3 operator * (double Matrix[3][3]);
public:
   CVector  operator * (CVector &Vector);
public:
   void LeftMultiply(double Matrix[3][3]);
};
//---------------------------------------------------------------------------
// CPoint
//---------------------------------------------------------------------------
struct CPoint
{
public:
   double  X;
   double  Y;
   double  Z;
public:
   CPoint(void) : X(0), Y(0), Z(0) {}
   CPoint(double X, double Y, double Z) : X(X), Y(Y), Z(Z) {}
   CPoint(CVector &Vector) : X(Vector.X), Y(Vector.Y), Z(Vector.Z) {}
public:
   // 点相减生成向量
   CVector operator - (CPoint &Point)
   {
      return CVector(X - Point.X, Y - Point.Y, Z - Point.Z);
   }
public:
   // 点和向量相加、相减
   CPoint operator + (CVector &Vector)
   {
      return CPoint(X + Vector.X, Y + Vector.Y, Z + Vector.Z);
   }
   CPoint operator - (CVector &Vector)
   {
      return CPoint(X - Vector.X, Y - Vector.Y, Z - Vector.Z);
   }
public:
   CPoint operator / (CVector &Vector)
   {
      return CPoint(X / Vector.X, Y / Vector.Y, Z / Vector.Z);
   }
public:
   CPoint operator = (CVector &Vector)
   {
      X = Vector.X;
      Y = Vector.Y;
      Z = Vector.Z;

      return *this;
   }
};
//---------------------------------------------------------------------------
CVector MatrixMulVector(double M[3][3], CVector Vi);
void    MatrixMulMatrix(double M1[3][3], double M2[3][3], double M[3][3]);
double  NormalizeAngle(double Angle);
double  Deg2Rad(double Angle){return Angle * M_PI / 180.0;}
double  Rad2Deg(double Angle){return Angle * 180.0 / M_PI;}
#endif
