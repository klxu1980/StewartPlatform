//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
   __Bitmap = new Graphics::TBitmap();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
   if(OpenPictureDialog1->Execute())
   {
      __Bitmap->LoadFromFile(OpenPictureDialog1->FileName);
      Image1->Canvas->Draw(0, 0, __Bitmap);
   }        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
   CBiImageContour Contour(__Bitmap->Canvas, __Bitmap->Width, __Bitmap->Height);
   for(unsigned int i = 0; i < Contour.Bound.size(); ++i)
   {
      int X = Contour.Bound[i].first;
      int Y = Contour.Bound[i].second;
      Image1->Canvas->Pixels[X][Y] = clRed;
   }        
}
//---------------------------------------------------------------------------
