//---------------------------------------------------------------------------


#pragma hdrstop

#include "RobotImage.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CRobotImage::CRobotImage(CRobot &Robot)
 : __hdc(NULL),
   __XAngle(-90.0),
   __YAngle(0.0),
   __ZAngle(0.0),
   __Robot(Robot),
   __ProjMode(true),
   __MiddleX(0.5),
   __MiddleY(0.15),
   __AxisLength(10.0),
   __ScreenLeft(0),
   __ScreenTop(0),
   __ScreenWidth(1024),
   __ScreenHeight(768)
{
}
//---------------------------------------------------------------------------
// ~CRobotImage()
//---------------------------------------------------------------------------
CRobotImage::~CRobotImage(void)
{
   if(!__hdc)
      return;

   wglMakeCurrent(NULL, NULL);
   wglDeleteContext(__hrc);
}
//---------------------------------------------------------------------------
// Initialize()
//---------------------------------------------------------------------------
void CRobotImage::Initialize(HDC hdc)
{
   __hdc = hdc;

   // �������ظ�ʽ
   PIXELFORMATDESCRIPTOR pfd =
       {
          sizeof(PIXELFORMATDESCRIPTOR),
          1,
          PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
          PFD_TYPE_RGBA,
          24,
          0,0,0,0,0,0,
          0,0,
          0,0,0,0,0,
          32,
          0,
          0,
          PFD_MAIN_PLANE,
          0,
          0,0,
       };

   int PixelFormat = ChoosePixelFormat(hdc, &pfd);
   SetPixelFormat(hdc, PixelFormat, &pfd);

   // ������ͼ�豸
   if((__hrc = wglCreateContext(__hdc)) == NULL ||
      !wglMakeCurrent(__hdc, __hrc))
   {
      throw Exception("��ʼ��OpenGLʧ��");
   }

   // ��Ȳ���
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
//---------------------------------------------------------------------------
void CRobotImage::ResetProjection(void)
{
   // ����ͶӰ��ʽ
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   if(__ProjMode)       // ͸��ͶӰ
      glFrustum(-__AxisLength * __MiddleX,
                 __AxisLength * (1.0 - __MiddleX),
                -__AxisLength * __MiddleY,
                 __AxisLength * (1.0 - __MiddleY),
                 100.0f,
                 400.0f);
   else
      glOrtho(-__AxisLength * __MiddleX,
               __AxisLength * (1.0 - __MiddleX),
              -__AxisLength * __MiddleY,
               __AxisLength * (1.0 - __MiddleY),
              -100000,
               100000);

   // �Ӵ��任
   glViewport(__ScreenLeft, __ScreenTop, __ScreenWidth, __ScreenHeight);

   // �ػ�ͼ
   glMatrixMode(GL_MODELVIEW);
   Repaint();
}
//---------------------------------------------------------------------------
// Resize()
//---------------------------------------------------------------------------
void CRobotImage::Resize(int Left, int Top, int Width, int Height)
{
   __ScreenLeft   = Left;
   __ScreenTop    = Top;
   __ScreenWidth  = Width;
   __ScreenHeight = Height;

   ResetProjection();
}
//---------------------------------------------------------------------------
// Repaint()
//---------------------------------------------------------------------------
void CRobotImage::Repaint(void)
{
   // ƽ�Ƽ���ת�任
   glLoadIdentity();

   glTranslatef(0, 0, -200);    
   glRotated(__XAngle, 1.0, 0.0, 0.0);
   glRotated(__YAngle, 0.0, 1.0, 0.0);
   glRotated(__ZAngle, 0.0, 0.0, 1.0);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // ����ͼ��
   DrawBackground();                                    // ���Ʊ���
   DrawPlatform(__Robot.UpperPlatform, 0x0000FF);       // ������ƽ̨
   DrawPlatform(__Robot.LowerPlatform, 0xFF0000);       // ������ƽ̨
   DrawLinks(__Robot, 0xFFFFFF);                        // ��������

   // ����ǰ̨����
   SwapBuffers(__hdc);
}
//---------------------------------------------------------------------------
void CRobotImage::SetProjectionMode(bool ProjMode)
{
   __ProjMode = ProjMode;
   Repaint();
}
//---------------------------------------------------------------------------
// DrawBackground()
//---------------------------------------------------------------------------
void CRobotImage::DrawBackground(void)
{
   glLineWidth(3);
   
   // ����X��
   glColor3ub(20, 255, 0);
   glBegin(GL_LINES);
      glVertex3d(0.0, 0.0, 0.0);
      glVertex3d(__AxisLength * 0.48, 0.0, 0.0);
   glEnd();

   // ����Y��
   glColor3ub(255, 0, 0);
   glBegin(GL_LINES);
      glVertex3d(0.0, 0.0, 0.0);
      glVertex3d(0.0, __AxisLength * 0.48, 0.0);
   glEnd();

   // ����Z��
   glColor3ub(0, 0, 255);
   glBegin(GL_LINES);
      glVertex3d(0.0, 0.0, 0.0);
      glVertex3d(0.0, 0.0, __AxisLength * 0.48);
   glEnd();
}
//---------------------------------------------------------------------------
// RotateAroundX()
//---------------------------------------------------------------------------
void CRobotImage::RotateAroundX(double Angle)
{
   __XAngle += Angle;
   Repaint();
}
//---------------------------------------------------------------------------
// RotateAroundY()
//---------------------------------------------------------------------------
void CRobotImage::RotateAroundY(double Angle)
{
   __YAngle += Angle;
   Repaint();
}
//---------------------------------------------------------------------------
// RotateAroundZ()
//---------------------------------------------------------------------------
void CRobotImage::RotateAroundZ(double Angle)
{
   __ZAngle += Angle;
   Repaint();
}
//---------------------------------------------------------------------------
void CRobotImage::MoveScreen(double DeltaX, double DeltaY)
{
   __MiddleX += DeltaX;
   __MiddleY -= DeltaY;

   __MiddleX = max(0.0, __MiddleX);
   __MiddleX = min(1.0, __MiddleX);

   __MiddleY = max(0.0, __MiddleY);
   __MiddleY = min(1.0, __MiddleY);

   ResetProjection();
}
//---------------------------------------------------------------------------
void CRobotImage::Zoom(double Factor)
{
   __AxisLength /= Factor;
   ResetProjection();
}
//---------------------------------------------------------------------------
void CRobotImage::DrawPlatform(double Platform[6][3], DWORD Color)
{
   glLineWidth(3);
   glColor3ub(Color & 0x0FF, (Color >> 8) & 0x0FF, (Color >> 16) & 0x0FF);

   glBegin(GL_LINE_STRIP);
      for(int i = 0; i < 6; ++i)
         glVertex3d(Platform[i][0], Platform[i][1], Platform[i][2]);
      glVertex3d(Platform[0][0], Platform[0][1], Platform[0][2]);
   glEnd();
}
//---------------------------------------------------------------------------
void CRobotImage::DrawLinks(CRobot &Robot, DWORD Color)
{
   glLineWidth(3);
   glColor3ub(Color & 0x0FF, (Color >> 8) & 0x0FF, (Color >> 16) & 0x0FF);

   glBegin(GL_LINES);
      for(int i = 0; i < 6; ++i)
      {
         glVertex3d(Robot.Jacks[i].UpperJoint[0], Robot.Jacks[i].UpperJoint[1], Robot.Jacks[i].UpperJoint[2]);
         glVertex3d(Robot.Jacks[i].LowerJoint[0], Robot.Jacks[i].LowerJoint[1], Robot.Jacks[i].LowerJoint[2]);
      }
   glEnd();
}
