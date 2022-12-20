//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TForm2::DrawWorkspace(vector<CXY> &Space)
{
   __Space = &Space;

   Image1->Canvas->Brush->Color = clBlack;
   Image1->Canvas->FillRect(TRect(0, 0, Image1->Width, Image1->Height));

   int CX = Image1->Width / 2;
   int CY = Image1->Height / 2;
   for(unsigned int i = 0; i < __Space->size(); ++i)
   {
      Image1->Canvas->Pixels[__Space->at(i).X + CX][__Space->at(i).Y + CY] = clWhite;
   }
}
void __fastcall TForm2::FormResize(TObject *Sender)
{
   return;

   if(__Space == NULL)
      return;

   Image1->Canvas->Brush->Color = clBlack;
   Image1->Canvas->FillRect(TRect(0, 0, Image1->Width, Image1->Height));

   int CX = Image1->Width / 2;
   int CY = Image1->Height / 2;
   for(unsigned int i = 0; i < __Space->size(); ++i)
   {
      Image1->Canvas->Pixels[__Space->at(i).X + CX][__Space->at(i).Y + CY] = clWhite;
   }
}
//---------------------------------------------------------------------------

