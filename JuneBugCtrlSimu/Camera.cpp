//---------------------------------------------------------------------------


#pragma hdrstop

#include "Camera.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
void CCamera::CalcCycleImage(float DAlpha)
{
   double SinTheta = sin(Degree2Rad(RY));
   double CosTheta = cos(Degree2Rad(RY));
   double SinPhi   = sin(Degree2Rad(RX));
   double CosPhi   = cos(Degree2Rad(RX));

   Image.clear();
   for(double alpha = 0; alpha < 360.0; alpha += DAlpha)
   {
      double CosAlpha = cos(Degree2Rad(alpha));
      double SinAlpha = sin(Degree2Rad(alpha));

      double Div = (-SinTheta * CosPhi * CosAlpha + SinPhi * SinAlpha) * Radius + CenterZ;

      double ImgX = L * (CosTheta * CosAlpha * Radius + CenterX) / Div;
      double ImgY = L * ((SinTheta * SinPhi * CosAlpha + CosPhi * SinAlpha) * Radius + CenterY) / Div;

      Image.push_back(C2dPoint(int(ImgX * PixelPerMM), int(ImgY * PixelPerMM)));
   }
}
//---------------------------------------------------------------------------
C2dPoint CCamera::CalcImagePoint(float Alpha)
{
   double SinTheta = sin(Degree2Rad(RY));
   double CosTheta = cos(Degree2Rad(RY));
   double SinPhi   = sin(Degree2Rad(RX));
   double CosPhi   = cos(Degree2Rad(RX));

   double CosAlpha = cos(Degree2Rad(Alpha));
   double SinAlpha = sin(Degree2Rad(Alpha));

   double Div = (-SinTheta * CosPhi * CosAlpha + SinPhi * SinAlpha) * Radius + CenterZ;

   double ImgX = L * (CosTheta * CosAlpha * Radius + CenterX) / Div;
   double ImgY = L * ((SinTheta * SinPhi * CosAlpha + CosPhi * SinAlpha) * Radius + CenterY) / Div;

   return C2dPoint(int(ImgX * PixelPerMM), int(ImgY * PixelPerMM));
}
//---------------------------------------------------------------------------
void CCamera::FindMaxXAlpha(void)
{
   C2dPoint P1 = CalcImagePoint(0.0);
   C2dPoint P2 = CalcImagePoint(0.1);

   for(__MaxXAlpha = 0.2; __MaxXAlpha <= 180.0; __MaxXAlpha += 0.1)
   {
      C2dPoint P3 = CalcImagePoint(__MaxXAlpha);
      if(P2.X >= P1.X && P3.X <= P2.X)
         break;
      else if(P2.X <= P1.X && P3.X >= P2.X)
      {
         __MaxXAlpha += 180.0;
         break;
      }
   }
}
