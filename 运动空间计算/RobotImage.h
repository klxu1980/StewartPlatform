//---------------------------------------------------------------------------

#ifndef RobotImageH
#define RobotImageH
#include <Classes.hpp>
#include <gl\gl.h>
#include <gl\glu.h>
#include <vector>
#include "D3Types.h"
#include "Trace.h"
#include "Robot.h"
using namespace std;
//---------------------------------------------------------------------------
class CRobotImage
{
private:
   HDC      __hdc;          // ���ھ��
   HGLRC    __hrc;          // OpenGL���
   bool     __ProjMode;     // ͶӰ��ʽ
private:
   double  __XAngle;        // ������ʵ����ת�Ƕ�
   double  __YAngle;
   double  __ZAngle;
   double  __AxisLength;
private:
   int     __ScreenLeft;
   int     __ScreenTop;
   int     __ScreenWidth;
   int     __ScreenHeight;
private:
   double  __MiddleX;      // ����ԭ������Ļ�е�λ��
   double  __MiddleY;
private:
   CRobot  &__Robot;
private:
   void ResetProjection(void);          // ����ͶӰ
   void CreateClip(void);               // ��������
   void DrawBackground(void);           // ���Ʊ���
private:
   void DrawAxises(void);                                   // ����������
   void DrawXAxis(bool AtOrigin);                           // ����X��
   void DrawYAxis(bool AtOrigin);                           // ����Y��
   void DrawZAxis(bool AtOrigin);                           // ����Z��
   void DrawPlatform(double Platform[6][3], DWORD Color);   // ������(��)ƽ̨
   void DrawLinks(CRobot &Robot, DWORD Color);              // ��������
private:
   void RotateByXZUniversally(double XAngle, double ZAngle);
public:
   CRobotImage(CRobot &Robot);
   ~CRobotImage(void);
public:
   void Initialize(HDC hdc);                                 // ��ʼ����ͼ
   void Resize(int Left, int Top, int Width, int Height);    // �ı��ͼ�ߴ�
   void SetProjectionMode(bool ProjMode);                    // ����ͶӰģʽ
   void Repaint(void);                                       // �ػ�
public:
   void RotateAroundX(double Angle);        // ��X��ת��
   void RotateAroundY(double Angle);        // ��Y��ת��
   void RotateAroundZ(double Angle);        // ��Z��ת��
   void MoveScreen(double DeltaX, double DeltaY);
   void Zoom(double Factor);
};
#endif
