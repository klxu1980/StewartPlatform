//---------------------------------------------------------------------------

#ifndef Space3DViewH
#define Space3DViewH
#include <Classes.hpp>
#include <gl\gl.h>
#include <gl\glu.h>
#include <vector>
#include <values.h>
#include "WorkSpace.h"
#include "CubeSpace.h"
using namespace std;
//---------------------------------------------------------------------------
#define SHOW_WHOLE_DIR     0
#define SHOW_POS_DIR       1
#define SHOW_NEG_DIR       -1
//---------------------------------------------------------------------------
class CSpace3DView
{
private:
   HDC         __hdc;          // ���ھ��
   HGLRC       __hrc;          // OpenGL���
   bool        __ProjMode;     // ͶӰ��ʽ
   CWorkSpace *__WorkSpace;    // �������˶��ռ�
   CCubeSpace *__CubeSpace;    // ������ռ�
   bool        __ShowCube;
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
   TColor  __BKColor;
   TColor  __SpaceCubeColor;
private:
   double  __MiddleX;      // ����ԭ������Ļ�е�λ��
   double  __MiddleY;
private:
   int     __MinZ;
   int     __MaxZ;
   float   __ZOffset;
private:
   int     __ShowHalfY;
   int     __ShowHalfX;
private:
   void ResetProjection(void);          // ����ͶӰ
   void CreateClip(void);               // ��������
   void DrawBackground(void);           // ���Ʊ���
private:
   void DrawAxises(void);                                   // ����������
   void DrawXAxis(bool AtOrigin);                           // ����X��
   void DrawYAxis(bool AtOrigin);                           // ����Y��
   void DrawZAxis(bool AtOrigin);                           // ����Z��
   void DrawWorkSpace(CWorkSpace *Space);
   void DrawCubeSpace(CCubeSpace *Space);
public:
   CSpace3DView(void);
   ~CSpace3DView(void);
public:
   void Initialize(HDC hdc);                                 // ��ʼ����ͼ
   void Resize(int Left, int Top, int Width, int Height);    // �ı��ͼ�ߴ�
   void SetProjectionMode(bool ProjMode);                    // ����ͶӰģʽ
   void Repaint(int Left, int Top, int Width, int Height);   // �ػ�
   void Repaint(void);
   void SetBKColor(TColor Color);
   void SetSpaceCubeColor(TColor Color);
public:
   void RotateAroundX(double Angle);        // ��X��ת��
   void RotateAroundY(double Angle);        // ��Y��ת��
   void RotateAroundZ(double Angle);        // ��Z��ת��
   void MoveScreen(double DeltaX, double DeltaY);
   void Zoom(double Factor);
public:
   void DrawSpace(CWorkSpace *Space, float ZOffset = 0);
   void SetZRange(int MinZ, int MaxZ);
public:
   void DrawCube(CCubeSpace *Space);
   void ShowCube(bool Show);
public:
   void ShowHalfY(int Dir);
   void ShowHalfX(int Dir);
};
#endif
