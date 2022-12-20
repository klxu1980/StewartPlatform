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
   HDC         __hdc;          // 窗口句柄
   HGLRC       __hrc;          // OpenGL句柄
   bool        __ProjMode;     // 投影方式
   CWorkSpace *__WorkSpace;    // 机器人运动空间
   CCubeSpace *__CubeSpace;    // 立方体空间
   bool        __ShowCube;
private:
   double  __XAngle;        // 坐标轴实际旋转角度
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
   double  __MiddleX;      // 坐标原点在屏幕中的位置
   double  __MiddleY;
private:
   int     __MinZ;
   int     __MaxZ;
   float   __ZOffset;
private:
   int     __ShowHalfY;
   int     __ShowHalfX;
private:
   void ResetProjection(void);          // 重置投影
   void CreateClip(void);               // 产生剪切
   void DrawBackground(void);           // 绘制背景
private:
   void DrawAxises(void);                                   // 绘制坐标轴
   void DrawXAxis(bool AtOrigin);                           // 绘制X轴
   void DrawYAxis(bool AtOrigin);                           // 绘制Y轴
   void DrawZAxis(bool AtOrigin);                           // 绘制Z轴
   void DrawWorkSpace(CWorkSpace *Space);
   void DrawCubeSpace(CCubeSpace *Space);
public:
   CSpace3DView(void);
   ~CSpace3DView(void);
public:
   void Initialize(HDC hdc);                                 // 初始化绘图
   void Resize(int Left, int Top, int Width, int Height);    // 改变绘图尺寸
   void SetProjectionMode(bool ProjMode);                    // 设置投影模式
   void Repaint(int Left, int Top, int Width, int Height);   // 重绘
   void Repaint(void);
   void SetBKColor(TColor Color);
   void SetSpaceCubeColor(TColor Color);
public:
   void RotateAroundX(double Angle);        // 绕X轴转动
   void RotateAroundY(double Angle);        // 绕Y轴转动
   void RotateAroundZ(double Angle);        // 绕Z轴转动
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
