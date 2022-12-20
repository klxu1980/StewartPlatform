//---------------------------------------------------------------------------

#ifndef CameraH
#define CameraH
#include <vector>
#include <math.h>
using namespace std;
//---------------------------------------------------------------------------
struct C3dPoint
{
public:
   float X;
   float Y;
   float Z;
public:
   C3dPoint(float X, float Y, float Z)
   : X(X), Y(Y), Z(Z) {}
};
struct C2dPoint
{
public:
   float X;
   float Y;
public:
   C2dPoint(float X, float Y)
   : X(X), Y(Y){}
};

class CCamera
{
public:
   float L;              // �������
   float PixelPerMM;     // �����ܶ�(1mm�߶��ϰ�������������)
public:
   float Radius;         // Բ�뾶
   float CenterX;        // Բ��������
   float CenterY;
   float CenterZ;
   float RX;             // Բƽ��ŷ����(��ת��)
   float RY;             // ������
private:
   float __MaxXAlpha;
public:
   vector<C2dPoint> Image;
private:  public:
   void FindMaxXAlpha(void);
public:
   CCamera(void) : L(15), PixelPerMM(300) {}
public:
   double    Degree2Rad(double Degree){return M_PI * Degree / 180.0;}
   C2dPoint  Trans3dTo2d(float Radius, float Alpha);
   C2dPoint  CalcImagePoint(float Alpha);
   void      CalcCycleImage(float DAlpha = 0.5);
};
#endif
