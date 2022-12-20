//---------------------------------------------------------------------------


#pragma hdrstop

#include "Space3DView.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CSpace3DView::CSpace3DView(void)
 : __hdc(NULL),
   __XAngle(0.0),
   __YAngle(0.0),
   __ZAngle(0.0),
   __ProjMode(true),
   __MiddleX(0.5),
   __MiddleY(0.15),
   __AxisLength(10.0),
   __ScreenLeft(0),
   __ScreenTop(0),
   __ScreenWidth(1024),
   __ScreenHeight(768),
   __ShowHalfX(SHOW_WHOLE_DIR),
   __ShowHalfY(SHOW_WHOLE_DIR)
{
}
//---------------------------------------------------------------------------
// ~CSpace3DView()
//---------------------------------------------------------------------------
CSpace3DView::~CSpace3DView(void)
{
   if(!__hdc)
      return;

   wglMakeCurrent(NULL, NULL);
   wglDeleteContext(__hrc);
}
//---------------------------------------------------------------------------
// Initialize()
//---------------------------------------------------------------------------
void CSpace3DView::Initialize(HDC hdc)
{
   __hdc = hdc;

   // 设置像素格式
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

   // 建立绘图设备
   if((__hrc = wglCreateContext(__hdc)) == NULL ||
      !wglMakeCurrent(__hdc, __hrc))
   {
      throw Exception("初始化OpenGL失败");
   }

   // 深度测试
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
//---------------------------------------------------------------------------
void CSpace3DView::ResetProjection(void)
{
   // 设置投影方式
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   if(__ProjMode)       // 透视投影
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

   // 视窗变换
   glViewport(__ScreenLeft, __ScreenTop, __ScreenWidth, __ScreenHeight);

   // 重绘图
   glMatrixMode(GL_MODELVIEW);
   Repaint();
}
//---------------------------------------------------------------------------
// Resize()
//---------------------------------------------------------------------------
void CSpace3DView::Resize(int Left, int Top, int Width, int Height)
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
void CSpace3DView::Repaint(void)
{
   // 平移及旋转变换
   glLoadIdentity();

   glTranslatef(0, 0, -200);    
   glRotated(__ZAngle, 0.0, 0.0, 1.0);
   glRotated(__YAngle, 0.0, 1.0, 0.0);
   glRotated(__XAngle, 1.0, 0.0, 0.0);

   // 清除背景
   glClearColor((__BKColor & 0x0FF) / 255.0, ((__BKColor >> 8) & 0x0FF) / 255.0, ((__BKColor >> 16) & 0x0FF) / 255.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // 绘制图像
   DrawBackground();   // 绘制背景
   if(__WorkSpace)
      DrawWorkSpace(__WorkSpace);
   if(__CubeSpace)
      DrawCubeSpace(__CubeSpace);

   
   // 交换前台缓冲
   SwapBuffers(__hdc);
}
void CSpace3DView::Repaint(int Left, int Top, int Width, int Height)
{
   Resize(Left, Top, Width, Height);

   // 平移及旋转变换
   glLoadIdentity();

   glTranslatef(0, 0, -200);    
   glRotated(__ZAngle, 0.0, 0.0, 1.0);
   glRotated(__YAngle, 0.0, 1.0, 0.0);
   glRotated(__XAngle, 1.0, 0.0, 0.0);


   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // 绘制图像
   DrawBackground();   // 绘制背景
   if(__WorkSpace)
      DrawWorkSpace(__WorkSpace);
   if(__CubeSpace)
      DrawCubeSpace(__CubeSpace);

   
   // 交换前台缓冲
   SwapBuffers(__hdc);
}
//---------------------------------------------------------------------------
void CSpace3DView::SetProjectionMode(bool ProjMode)
{
   __ProjMode = ProjMode;
   Repaint();
}
//---------------------------------------------------------------------------
// DrawBackground()
//---------------------------------------------------------------------------
void CSpace3DView::DrawBackground(void)
{
   glLineWidth(3);
   
   // 绘制X轴
   glColor3ub(255, 0, 0);
   glBegin(GL_LINES);
      glVertex3d(0.0, 0.0, 0.0);
      glVertex3d(__AxisLength * 0.48, 0.0, 0.0);
   glEnd();

   // 绘制Y轴
   glColor3ub(0, 255, 0);
   glBegin(GL_LINES);
      glVertex3d(0.0, 0.0, 0.0);
      glVertex3d(0.0, __AxisLength * 0.48, 0.0);
   glEnd();

   // 绘制Z轴
   glColor3ub(0, 0, 255);
   glBegin(GL_LINES);
      glVertex3d(0.0, 0.0, 0.0);
      glVertex3d(0.0, 0.0, __AxisLength * 0.48);
   glEnd();
}
//---------------------------------------------------------------------------
// RotateAroundX()
//---------------------------------------------------------------------------
void CSpace3DView::RotateAroundX(double Angle)
{
   __XAngle += Angle;
   Repaint();
}
//---------------------------------------------------------------------------
// RotateAroundY()
//---------------------------------------------------------------------------
void CSpace3DView::RotateAroundY(double Angle)
{
   __YAngle += Angle;
   Repaint();
}
//---------------------------------------------------------------------------
// RotateAroundZ()
//---------------------------------------------------------------------------
void CSpace3DView::RotateAroundZ(double Angle)
{
   __ZAngle += Angle;
   Repaint();
}
//---------------------------------------------------------------------------
void CSpace3DView::MoveScreen(double DeltaX, double DeltaY)
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
void CSpace3DView::Zoom(double Factor)
{
   __AxisLength /= Factor;
   ResetProjection();
}
//---------------------------------------------------------------------------
void CSpace3DView::DrawWorkSpace(CWorkSpace *Space)
{
   glLineWidth(1);

   for(unsigned int i = 0; i < Space->BorderXYZ.size(); ++i)
   {
      vector<CXY> &XY = Space->BorderXYZ[i].Border;
      if(Space->BorderXYZ[i].Z < __MinZ || Space->BorderXYZ[i].Z > __MaxZ)
         continue;

      // 颜色渐变
      TColor Color1 = clBlue;
      TColor Color2 = clRed;

      int B = (Color1 & 0x0FF0000) + ((Color2 & 0x0FF0000) - (Color1 & 0x0FF0000)) * float(i) / Space->BorderXYZ.size();
      int G = (Color1 & 0x0FF00) + ((Color2 & 0x0FF00) - (Color1 & 0x0FF00)) * float(i) / Space->BorderXYZ.size();
      int R = (Color1 & 0x0FF) + ((Color2 & 0x0FF) - (Color1 & 0x0FF)) * float(i) / Space->BorderXYZ.size();
      glColor3ub(R, G >> 8, B >> 16);

      glBegin(GL_LINES);

         for(unsigned int m = 1; m < XY.size(); ++m)
         {
            if(__ShowHalfY * XY[m].Y >= 0 && __ShowHalfX * XY[m].X >= 0)
            {
               glVertex3d(XY[m-1].X * 0.01, XY[m-1].Y * 0.01, (Space->BorderXYZ[i].Z + __ZOffset)* 0.01);
               glVertex3d(XY[m].X * 0.01, XY[m].Y * 0.01, (Space->BorderXYZ[i].Z + __ZOffset)* 0.01);
            }
         }


      glEnd();


      /*
      glBegin(GL_LINE_STRIP);
         for(unsigned int m = 0; m < XY.size(); ++m)
            glVertex3d(XY[m].X * 0.01, XY[m].Y * 0.01, (Space->BorderXYZ[i].Z + __ZOffset)* 0.01);

         if(abs(XY.front().X - XY.back().X) / Space->Step <= 2 && abs(XY.front().Y - XY.back().Y) / Space->Step <= 2)
            glVertex3d(XY.front().X * 0.01, XY.front().Y * 0.01, (Space->BorderXYZ[i].Z + __ZOffset) * 0.01);
      glEnd();
      */
   }
}
//---------------------------------------------------------------------------
void CSpace3DView::DrawCubeSpace(CCubeSpace *Space)
{
   glLineWidth(2);
   glColor3ub(__SpaceCubeColor & 0xFF,
              (__SpaceCubeColor >> 8)   & 0xFF,
              (__SpaceCubeColor >> 16)  & 0xFF);

   double X1 = Space->X - Space->L * Space->Kx;
   double X2 = Space->X + Space->L * Space->Kx;
   double Y1 = Space->Y - Space->L * Space->Ky;
   double Y2 = Space->Y + Space->L * Space->Ky;
   double Z1 = Space->Z - Space->L * Space->Kz + __ZOffset;
   double Z2 = Space->Z + Space->L * Space->Kz + __ZOffset;

   glBegin(GL_LINE_STRIP);
      glVertex3d(X1 * 0.01, Y1 * 0.01, Z1 * 0.01);
      glVertex3d(X1 * 0.01, Y1 * 0.01, Z2 * 0.01);
      glVertex3d(X1 * 0.01, Y2 * 0.01, Z2 * 0.01);
      glVertex3d(X1 * 0.01, Y2 * 0.01, Z1 * 0.01);
      glVertex3d(X1 * 0.01, Y1 * 0.01, Z1 * 0.01);
   glEnd();

   glBegin(GL_LINE_STRIP);
      glVertex3d(X2 * 0.01, Y1 * 0.01, Z1 * 0.01);
      glVertex3d(X2 * 0.01, Y1 * 0.01, Z2 * 0.01);
      glVertex3d(X2 * 0.01, Y2 * 0.01, Z2 * 0.01);
      glVertex3d(X2 * 0.01, Y2 * 0.01, Z1 * 0.01);
      glVertex3d(X2 * 0.01, Y1 * 0.01, Z1 * 0.01);
   glEnd();

   glBegin(GL_LINE_STRIP);
      glVertex3d(X1 * 0.01, Y1 * 0.01, Z1 * 0.01);
      glVertex3d(X1 * 0.01, Y1 * 0.01, Z2 * 0.01);
      glVertex3d(X2 * 0.01, Y1 * 0.01, Z2 * 0.01);
      glVertex3d(X2 * 0.01, Y1 * 0.01, Z1 * 0.01);
      glVertex3d(X1 * 0.01, Y1 * 0.01, Z1 * 0.01);
   glEnd();

   glBegin(GL_LINE_STRIP);
      glVertex3d(X1 * 0.01, Y2 * 0.01, Z1 * 0.01);
      glVertex3d(X1 * 0.01, Y2 * 0.01, Z2 * 0.01);
      glVertex3d(X2 * 0.01, Y2 * 0.01, Z2 * 0.01);
      glVertex3d(X2 * 0.01, Y2 * 0.01, Z1 * 0.01);
      glVertex3d(X1 * 0.01, Y2 * 0.01, Z1 * 0.01);
   glEnd();
}
//---------------------------------------------------------------------------
void CSpace3DView::DrawSpace(CWorkSpace *Space, float ZOffset)
{
   __ZOffset = ZOffset;
   if(!Space->BorderXYZ.empty())
   {
      __WorkSpace = Space;
      __MinZ  = __WorkSpace->BorderXYZ.front().Z;
      __MaxZ  = __WorkSpace->BorderXYZ.back().Z;

      Repaint();
   }
}
//---------------------------------------------------------------------------
void CSpace3DView::SetZRange(int MinZ, int MaxZ)
{
   __MinZ = MinZ;
   __MaxZ = MaxZ;
   Repaint();
}
//---------------------------------------------------------------------------
void CSpace3DView::DrawCube(CCubeSpace *Space)
{
   __CubeSpace = Space;
   Repaint();
}
//---------------------------------------------------------------------------
void CSpace3DView::SetBKColor(TColor Color)
{
   __BKColor = Color;
   Repaint();
}
//---------------------------------------------------------------------------
void CSpace3DView::SetSpaceCubeColor(TColor Color)
{
   __SpaceCubeColor = Color;
   Repaint();
}
//---------------------------------------------------------------------------
void CSpace3DView::ShowCube(bool Show)
{
   __ShowCube = Show;
   Repaint();
}
//---------------------------------------------------------------------------
void CSpace3DView::ShowHalfY(int Dir)
{
   __ShowHalfY = Dir;
   Repaint();
}
//---------------------------------------------------------------------------
void CSpace3DView::ShowHalfX(int Dir)
{
   __ShowHalfX = Dir;
   Repaint();
}
