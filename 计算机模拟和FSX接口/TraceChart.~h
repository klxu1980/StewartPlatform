//---------------------------------------------------------------------------

#ifndef TraceChartH
#define TraceChartH
#include <Classes.hpp>
#include <gl\gl.h>
#include <gl\glu.h>
#include <vector>
#include "D3Types.h"
#include "Trace.h"
#include "Robot.h"
using namespace std;
//---------------------------------------------------------------------------
class CTraceChart
{
private:
   HDC      __hdc;          // 窗口句柄
   HGLRC    __hrc;          // OpenGL句柄
   bool     __ProjMode;     // 投影方式
private:
   double  __XAngle;       // 坐标轴实际旋转角度
   double  __YAngle;
   double  __ZAngle;
   double  __AxisLength;
private:
   int     __ScreenLeft;
   int     __ScreenTop;
   int     __ScreenWidth;
   int     __ScreenHeight;
private:
   double  __MiddleX;      // 坐标原点在屏幕中的位置
   double  __MiddleY;
private:
   CRobot  &__Robot;
private:
   void ResetProjection(void);          // 重置投影
   void CreateClip(void);               // 产生剪切
   void DrawBackground(void);           // 绘制背景
private:
   void DrawAxises(void);               // 绘制坐标轴
   void DrawXAxis(bool AtOrigin);       // 绘制X轴
   void DrawYAxis(bool AtOrigin);       // 绘制Y轴
   void DrawZAxis(bool AtOrigin);       // 绘制Z轴
private:
   void RotateByXZUniversally(double XAngle, double ZAngle);
public:
   CTraceChart(CRobot &Robot);
   ~CTraceChart(void);
public:
   void Initialize(HDC hdc);
   void Resize(int Left, int Top, int Width, int Height);
   void Repaint(void);
   void SetProjectionMode(bool ProjMode);
public:
   void RotateAroundX(double Angle);        // 绕X轴转动
   void RotateAroundY(double Angle);        // 绕Y轴转动
   void RotateAroundZ(double Angle);        // 绕Z轴转动
   void MoveScreen(double DeltaX, double DeltaY);
   void Zoom(double Factor);
public:
   void DrawPlatform(double Platform[6][3], DWORD Color);
   void DrawLinks(CRobot &Robot, DWORD Color);
};
#endif
