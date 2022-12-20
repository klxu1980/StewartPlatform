//---------------------------------------------------------------------------


#pragma hdrstop

#include "Contour.h"
#include <algorithms>
#include <Classes.hpp>
#include <values.h>
#include <stack>
#include <map>
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CContour::CContour(void)
 : __SpaceXMax(1500),
   __SpaceYMax(1500)
{
   __SpaceMap = new char[(__SpaceXMax * 2 + 1) * (__SpaceYMax * 2 + 1)];
}
//---------------------------------------------------------------------------
// GetWorkSpaceBorderXY()
// 搜索XY平面上的边界线，基本方法为
// 1. 首先找到第一个可达位置
// 2. 通过FloodFill方法，从初始位置出发，搜索整个可达空间。将空间边界点存储在set中。
// 3. FloodFill找出的边界点缺乏顺序，再对这些边界点排序，得到有序的边界线
//---------------------------------------------------------------------------
void CContour::GetWorkSpaceBorderXY(int Z)
{
   InitWorkSpace();

   // 这里需要枚举所有初始点

   // 基于FloodFill方法，找出所有的边界点
   // 找出第一个可达点作为种子
   CXY InitPoint;
   if(FindInitPoint(InitPoint, Z) )
   {
      set<CXY, CXYLess> BorderSet;            // 所有边界点集合
      FloodFillXYSpace(Z, InitPoint, BorderSet);    // FloodFill整个XY平面空间，找出边界点
      SortBorderXY(Z, BorderSet);                   // 对边界点排序
   }
}
//---------------------------------------------------------------------------
// FloodFillXYSpace()
//---------------------------------------------------------------------------
void CContour::FloodFillXYSpace(int Z, CXY InitPos, set<CXY, CXYLess> &BorderSet)
{
   stack<CXY> Stack;
   Stack.push(InitPos);
   while(!Stack.empty())
   {
      int X = Stack.top().X;
      int Y = Stack.top().Y;
      Stack.pop();

      SpaceXY(X, Y) = true;
      if(IsFeasible(X, Y, Z) )
      {
         // 将其他未访问邻接点压入堆栈
         if(!SpaceXY(X - 1, Y) && X - 1 >= -__SpaceXMax)
            Stack.push(CXY(X - 1, Y));
         if(!SpaceXY(X + 1, Y) && X + 1 <= __SpaceXMax)
            Stack.push(CXY(X + 1, Y));
         if(!SpaceXY(X, Y - 1) && Y - 1 >= -__SpaceYMax)
            Stack.push(CXY(X, Y - 1));
         if(!SpaceXY(X, Y + 1) && Y + 1 < __SpaceYMax)
            Stack.push(CXY(X, Y + 1));
      }
      else
      {
         BorderSet.insert(CXY(X, Y));
      }
   }
}
//---------------------------------------------------------------------------
// SortBorderXY()
//---------------------------------------------------------------------------
void CContour::SortBorderXY(int Z, set<CXY, CXYLess> &BorderSet)
{
   // 对边界点排序
   int Dir[8][2] = { {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
   while(!BorderSet.empty())
   {
      vector<CXY> BorderXY;

      bool AllVisited;
      set<CXY, CXYLess>::iterator CurP = BorderSet.begin();

      do
      {
         BorderXY.push_back(CXY(CurP->X * XStep, CurP->Y * YStep) );
         BorderSet.erase(CurP);

         AllVisited = true;
         for(int i = 0; i < 8; ++i)
         {
            CXY XY(CurP->X + Dir[i][0], CurP->Y + Dir[i][1]);

            set<CXY, CXYLess>::iterator NxtP = BorderSet.find(XY);
            if(NxtP != BorderSet.end())
            {
               CurP = NxtP;
               AllVisited  = false;
               break;
            }
         }
      }while(!AllVisited);
      BorderXYZ.push_back(CBorderXY(Z * ZStep, BorderXY));
   }
}
//---------------------------------------------------------------------------
void CContour::DrawSpaceBorderXY(vector<CXY> &BorderXY, Graphics::TBitmap *SpaceImg)
{
   SpaceImg->Canvas->Brush->Color = clBlack;
   SpaceImg->Canvas->Pen->Color   = clWhite;
   SpaceImg->Canvas->FillRect(TRect(0, 0, SpaceImg->Width, SpaceImg->Height));

   if(BorderXY.empty())
      return;

   int X = BorderXY.front().X + SpaceImg->Width / 2;
   int Y = SpaceImg->Height / 2 - BorderXY.front().Y;
   SpaceImg->Canvas->MoveTo(X, Y);

   for(unsigned int i = 0; i < BorderXY.size(); ++i)
   {
      int X = BorderXY[i].X + SpaceImg->Width / 2;
      int Y = SpaceImg->Height / 2 - BorderXY[i].Y;
      SpaceImg->Canvas->LineTo(X, Y);
   }
}
//--------------------------------------------------------------------------
void CContour::DrawSpaceBorderXY(int Z, Graphics::TBitmap *SpaceImg, bool BorderOnly)
{
   for(unsigned int i = 0; i < BorderXYZ.size(); ++i)
      if(BorderXYZ[i].Z == Z)
      {
         DrawSpaceBorderXY(BorderXYZ[i].Border, SpaceImg);
         if(!BorderOnly)
         {
            SpaceImg->Canvas->Brush->Color = clWhite;
            SpaceImg->Canvas->FloodFill(SpaceImg->Width / 2, SpaceImg->Height / 2, clWhite, fsBorder);
         }

         break;
      }
}
//---------------------------------------------------------------------------
void CContour::SaveContour(TStream *Stream)
{  
   // 将边界点写入文件中
   int ZCnt = BorderXYZ.size();
   Stream->Write(&ZCnt, sizeof(ZCnt));

   for(unsigned int i = 0; i < BorderXYZ.size(); ++i)
   {
      int Z = BorderXYZ[i].Z;
      int Cnt = BorderXYZ[i].Border.size();
      Stream->Write(&Z, sizeof(Z));
      Stream->Write(&Cnt, sizeof(Cnt));

      vector<CXY> &XY = BorderXYZ[i].Border;
      Stream->Write(&XY.front(), XY.size() * sizeof(int) * 2);
   }
}
//---------------------------------------------------------------------------
void CContour::LoadContour(TStream *Stream)
{
   int ZCnt;
   Stream->Read(&ZCnt, sizeof(ZCnt));

   while(--ZCnt >= 0)
   {
      int   Z;
      int   Cnt;
      Stream->Read(&Z, sizeof(Z));
      Stream->Read(&Cnt, sizeof(Cnt));

      BorderXYZ.push_back(CBorderXY(Z));
      for(int i = 0; i < Cnt; ++i)
      {
         int X, Y;
         Stream->Read(&X, sizeof(X));
         Stream->Read(&Y, sizeof(Y));

         CXY P(X, Y);
         BorderXYZ.back().Border.push_back(P);
      }
   }
}








