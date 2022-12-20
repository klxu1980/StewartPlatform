//---------------------------------------------------------------------------


#pragma hdrstop

#include "SpaceFile.h"
#include <values.h>
#include <Classes.hpp>
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CSpaceFile::CSpaceFile(int Step)
 : CWorkSpace()
{
   this->Step = Step;
   SymAxis = SYM_BY_X;
}
//---------------------------------------------------------------------------
// LoadRobotFile()
// 从机器人的检测结果文件中加载运动空间数据
// 文件中坐标顺序为(X，Y，Z)
//---------------------------------------------------------------------------
void CSpaceFile::LoadRobotFile(AnsiString FileName)
{
   TStream *Stream = new TFileStream(FileName, fmOpenRead);
   char Buffer[256];

   int xyz[3];
   int id  = 0;
   int row = 0;
   AnsiString Str;
   for(Stream->Seek(0, soFromBeginning); Stream->Position < Stream->Size; )
   {
      int Cnt = Stream->Read(Buffer, 256);
      for(int i = 0; i < Cnt; ++i)
      {
         if(Buffer[i] == ' ' || Buffer[i] == '\n')
         {
            xyz[id++] = Str.ToInt();
            Str = "";

            if(Buffer[i] == '\n')
            {
               if(!row++)
                  Step = xyz[0];
               else
               {
                  // 搜索运动空间时，仅搜索 y >= 0 的坐标点，因此需要将 y < 0 的坐标点补齐
                  __Reachable.insert(CXYZ(xyz[0] / Step,  xyz[1] / Step, xyz[2] / Step) );
                  __Reachable.insert(CXYZ(xyz[0] / Step, -xyz[1] / Step, xyz[2] / Step) );

                  __MinZ = min(__MinZ, int(xyz[2] / Step));
                  __MaxZ = max(__MaxZ, int(xyz[2] / Step));
               }
               id = 0;
            }
         }
         else if(Buffer[i] == '-' || (Buffer[i] >= '0' && Buffer[i] <= '9'))
            Str += Buffer[i];
      }
   }

   delete Stream;

   // 获取运动空间
   BorderXYZ.clear();
   for(int Z = __MinZ; Z <= __MaxZ; ++Z)
      GetWorkSpaceBorderXY(Z);
}
//---------------------------------------------------------------------------
void CSpaceFile::GetXYLayer(CXYSet &Space, int Z)
{
   Space.clear();
   for(set<CXYZ, XYZLess>::iterator iter = __Reachable.upper_bound(CXYZ(MAXINT, MAXINT, Z - 1)); iter != __Reachable.end(); ++iter)
      if(iter->Z == Z)
         Space.insert(CXY(iter->X, iter->Y));
}
//---------------------------------------------------------------------------
void CSpaceFile::BeginEnumInitXY(int Z)
{
   GetXYLayer(__XYLayer, Z);
}
//---------------------------------------------------------------------------
bool CSpaceFile::FindNextInitXY(CXY &InitPoint)
{
   if(__XYLayer.empty())
      return false;

   InitPoint.X = __XYLayer.begin()->X;
   InitPoint.Y = __XYLayer.begin()->Y;
   return true;
}
//---------------------------------------------------------------------------
void CSpaceFile::VisitXYInFloodFill(int X, int Y)
{
   CXYSet::iterator iter = __XYLayer.find(CXY(X, Y) );
   if(iter != __XYLayer.end())
      __XYLayer.erase(iter);
}
//---------------------------------------------------------------------------
void CSpaceFile::SaveToFile(AnsiString FileName)
{
   TStream *Stream = new TFileStream(FileName, fmCreate);

   // 保存附加信息
   Stream->Write(&Step, sizeof(Step));

   // 保存边界点数据
   SaveBorder(Stream);

   // 保存可达点
   int Cnt = __Reachable.size();
   Stream->Write(&Cnt, sizeof(Cnt));
   for(set<CXYZ, XYZLess>::iterator Iter = __Reachable.begin(); Iter != __Reachable.end(); ++Iter)
      Stream->Write(&(*Iter), sizeof(*Iter));

   delete Stream;
}
//---------------------------------------------------------------------------
void CSpaceFile::LoadFromFile(AnsiString FileName)
{
   TStream *Stream = new TFileStream(FileName, fmOpenRead);
   __Reachable.clear();

   // 加载附加信息
   Stream->Read(&Step, sizeof(Step));

   // 加载边界点
   LoadBorder(Stream);

   // 加载所有可达点坐标
   int Cnt;
   Stream->Read(&Cnt, sizeof(Cnt));
   while(--Cnt >= 0)
   {
      CXYZ XYZ(0, 0, 0);
      Stream->Read(&XYZ, sizeof(CXYZ));
      __Reachable.insert(XYZ);
   }

   delete Stream;
}
//----------------------------------------------------------------------------
void CSpaceFile::GetXYSpace(vector<CXY> &Space, int Z)
{
   Z /= Step;
   for(set<CXYZ, XYZLess>::iterator iter = __Reachable.upper_bound(CXYZ(MAXINT, MAXINT, Z - 1)); iter != __Reachable.end(); ++iter)


   //for(set<CXYZ, XYZLess>::iterator iter = __Reachable.begin(); iter != __Reachable.end(); ++iter)
      if(iter->Z == Z)
         Space.push_back(CXY(iter->X, iter->Y));
}
