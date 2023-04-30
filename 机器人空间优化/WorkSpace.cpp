//---------------------------------------------------------------------------


#pragma hdrstop

#include "WorkSpace.h"
#include <algorithms>
#include <Classes.hpp>
#include <values.h>
#include <stack>
#include <map>
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CWorkSpace::CWorkSpace(void)
 : __XMax(2000),
   __YMax(2000)
{
   __XYVisited = new bool[(__XMax * 2 + 1) * (__YMax * 2 + 1)];
}
//---------------------------------------------------------------------------
// GetWorkSpaceBorderXY()
// ����XYƽ���ϵı߽��ߣ���������Ϊ
// 1. �����ҵ���һ���ɴ�λ��
// 2. ͨ��FloodFill�������ӳ�ʼλ�ó��������������ɴ�ռ䡣���ռ�߽��洢��set�С�
// 3. FloodFill�ҳ��ı߽��ȱ��˳���ٶ���Щ�߽�����򣬵õ�����ı߽���
//---------------------------------------------------------------------------
void CWorkSpace::GetWorkSpaceBorderXY(int Z)
{
   // ��ʼ�������ռ�(����Ϊinfeasible)
   InitVisitMark();

   // ������Ҫö�����г�ʼ��
   BeginEnumInitXY(Z);

   // ����FloodFill�������ҳ����еı߽��
   // �ҳ���һ���ɴ����Ϊ����
   CXY InitPoint;
   set<CXY, XYLess> BorderSet;                  // ���б߽�㼯��
   while(FindNextInitXY(InitPoint) )
   {
      BorderSet.clear();
      FloodFillXYSpace(Z, InitPoint, BorderSet);    // FloodFill����XYƽ��ռ䣬�ҳ��߽��
      SortBorderXY(Z, BorderSet);                   // �Ա߽��������������д��BorderXYZ��
   }
}
//---------------------------------------------------------------------------
// FloodFillXYSpace()
// ע�⣺�߽���ɲ�����Լ���ĵ����
//---------------------------------------------------------------------------
void CWorkSpace::FloodFillXYSpace(int Z, CXY InitPos, set<CXY, XYLess> &BorderSet)
{
   stack<CXY> Stack;
   Stack.push(InitPos);
   while(!Stack.empty())
   {
      int X = Stack.top().X;
      int Y = Stack.top().Y;
      Stack.pop();

      XYVisited(X, Y) = true;
      VisitXYInFloodFill(X, Y);
      if(IsFeasible(X, Y, Z) )
      {
         // ������δ�����ڽӵ�ѹ���ջ
         if(!XYVisited(X - 1, Y) && X - 1 >= -__XMax)
            Stack.push(CXY(X - 1, Y));
         if(!XYVisited(X + 1, Y) && X + 1 <= __XMax)
            Stack.push(CXY(X + 1, Y));
         if(!XYVisited(X, Y - 1) && Y - 1 >= -__YMax)
            Stack.push(CXY(X, Y - 1));
         if(!XYVisited(X, Y + 1) && Y + 1 < __YMax)
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
void CWorkSpace::SortBorderXY(int Z, set<CXY, XYLess> &BorderSet)
{  
   // �Ա߽������
   int Dir[8][2] = { {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
   int CurDir = 0;
   while(!BorderSet.empty())
   {
      vector<CXY> BorderXY;

      bool AllVisited;
      set<CXY, XYLess>::iterator CurP = BorderSet.begin();

      do
      {
         BorderXY.push_back(CXY(CurP->X * Step, CurP->Y * Step) );
         BorderSet.erase(CurP);

         AllVisited = true;
         for(int i = 0; i < 8; ++i)
         {
            if(CurDir >= 8)
               CurDir = 0;
            else if(CurDir < 0)
               CurDir += 8;

            CXY XY(CurP->X + Dir[CurDir][0], CurP->Y + Dir[CurDir][1]);
            set<CXY, XYLess>::iterator NxtP = BorderSet.find(XY);

            if(NxtP != BorderSet.end())
            {
               CurP = NxtP;
               AllVisited  = false;
               CurDir -= 2;
               break;
            }
            ++CurDir;
         }
      }while(!AllVisited);
      BorderXYZ.push_back(CBorderXY(Z * Step, BorderXY));
   }
}
//---------------------------------------------------------------------------
void CWorkSpace::DrawSpaceBorderXY(Graphics::TBitmap *SpaceImg, int Z)
{  
   SpaceImg->Canvas->Brush->Color = clBlack;
   SpaceImg->Canvas->Pen->Color   = clWhite;
   SpaceImg->Canvas->FillRect(TRect(0, 0, SpaceImg->Width, SpaceImg->Height));

   int CX = SpaceImg->Width / 2;
   int CY = SpaceImg->Height / 2;
   for(unsigned int i = 0; i < BorderXYZ.size(); ++i)
   {
      if(BorderXYZ[i].Z == Z)
      {
         vector<CXY> &Border = BorderXYZ[i].Border;
         for(unsigned int m = 0; m < Border.size(); ++m)
            SpaceImg->Canvas->Pixels[CX + Border[m].X / Step][CY - Border[m].Y / Step] = clWhite;
      }
   }
}
//--------------------------------------------------------------------------
void CWorkSpace::DrawSpaceBorderXY(int Z, Graphics::TBitmap *SpaceImg, bool BorderOnly)
{
/*
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
*/
}
//---------------------------------------------------------------------------
void CWorkSpace::SaveBorder(TStream *Stream)
{
   // ���߽��д���ļ���
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
void CWorkSpace::LoadBorder(TStream *Stream)
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








