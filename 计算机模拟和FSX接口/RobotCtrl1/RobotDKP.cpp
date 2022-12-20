//---------------------------------------------------------------------------


#pragma hdrstop

#include "RobotDKP.h"
#include <values.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
void CRobotDKP::EnumPostures(pair<double, double> XRange, pair<double, double> YRange, pair<double, double> ZRange,
                             pair<double, double> YawRange, pair<double, double> RollRange, pair<double, double> PitchRange)
{
   for(double X = XRange.first; X <= XRange.second; X += __LinearStep)
      for(double Y = YRange.first; Y <= YRange.second; Y += __LinearStep)
         for(double Z = ZRange.first; Z <= ZRange.second; Z += __LinearStep)
            for(double Yaw = YawRange.first; Yaw <= YawRange.second; Yaw += __RotaryStep)
               for(double Roll = RollRange.first; Roll <= RollRange.second; Roll += __RotaryStep)
                  for(double Pitch = PitchRange.first; Pitch <= PitchRange.second; Pitch += __RotaryStep)
                  {
                     if(Move(X, Y, Z, Yaw, Pitch, Roll) == msOk)
                     {
                        CPostureJacks PJ;
                        PJ.X     = X;
                        PJ.Y     = Y;
                        PJ.Z     = Z;
                        PJ.Yaw   = Yaw;
                        PJ.Pitch = Pitch;
                        PJ.Roll  = Roll;
                        PJ.JackLength[0] = Jacks[0].Length;
                        PJ.JackLength[1] = Jacks[1].Length;
                        PJ.JackLength[2] = Jacks[2].Length;
                        PJ.JackLength[3] = Jacks[3].Length;
                        PJ.JackLength[4] = Jacks[4].Length;
                        PJ.JackLength[5] = Jacks[5].Length;
                     }
                  }
}


//---------------------------------------------------------------------------
// L1Length()
//---------------------------------------------------------------------------
double CRobotDKP::L1Length(void)
{
/*
   double xi    = __UpperEurlar[0];
   double theta = __UpperEurlar[1];
   double phi   = __UpperEurlar[2];
   double x0    = __UpperPos[0];
   double y0    = __UpperPos[1];
   double z0    = __UpperPos[2];

   double Lt = __UpperArmLength;
   double lt = __UpperBaseLength;
   double Lb = __LowerArmLength;
   double lb = __LowerBaseLength;

   double Length = pow(cos(theta) * cos(xi) * Lt - cos(theta) * sin(xi) * lt + x0 - 0.5 * Lb - 0.5 * lb * sqrt(3.0), 2.0) +
                   pow((sin(theta) * sin(phi) * cos(xi) + cos(phi) * sin(xi)) * Lt + (-sin(theta) * sin(phi) * sin(xi) + cos(phi) * cos(xi)) * lt + y0 - 0.5 * Lb * sqrt(3.0) + 0.5 * lb, 2.0) +
                   pow((-sin(theta) * cos(phi) * cos(xi) + sin(phi) * sin(xi)) * Lt + (sin(theta) * cos(phi) * sin(xi) + sin(phi) * cos(xi)) * lt + z0, 2.0);

   return sqrt(Length);

*/
   //,    (cos(theta)*cos(xi)*(-1/2*Lt+1/2*lt*3^(1/2))-cos(theta)*sin(xi)*(1/2*Lt*3^(1/2)+1/2*lt)+x0-1/2*Lb+1/2*lb*3^(1/2))^2+((sin(theta)*sin(phi)*cos(xi)+cos(phi)*sin(xi))*(-1/2*Lt+1/2*lt*3^(1/2))+(-sin(theta)*sin(phi)*sin(xi)+cos(phi)*cos(xi))*(1/2*Lt*3^(1/2)+1/2*lt)+y0-1/2*Lb*3^(1/2)-1/2*lb)^2+((-sin(theta)*cos(phi)*cos(xi)+sin(phi)*sin(xi))*(-1/2*Lt+1/2*lt*3^(1/2))+(sin(theta)*cos(phi)*sin(xi)+sin(phi)*cos(xi))*(1/2*Lt*3^(1/2)+1/2*lt)+z0)^2,
}
//--------------------------------------------------------------------------
double CRobotDKP::ErrorFunc(double Pos[3], double Eurlar[3])
{
   if(Move(Pos[0], Pos[1], Pos[2], Eurlar[0], Eurlar[1], Eurlar[2]) == msOk)
   {
      double Diff = 0;
      for(int i = 0; i < 6; ++i)
         Diff += (__JackLength[i] - Jacks[i].Length) * (__JackLength[i] - Jacks[i].Length);

      return Diff;
   }
   else
      return MAXFLOAT;
}
DP CRobotDKP::ErrorFunc(Vec_I_DP &x)
{
   double Pos[3]    = {x[0], x[1], x[2]};
   double Eurlar[3] = {x[3], x[4], x[5]};

   return ErrorFunc(Pos, Eurlar);
}
double CRobotDKP::ErrorFunc(double PosGesture[6])
{
   double Pos[3]    = {PosGesture[0], PosGesture[1], PosGesture[2]};
   double Eurlar[3] = {PosGesture[3], PosGesture[4], PosGesture[5]};

   return ErrorFunc(Pos, Eurlar);
}
//---------------------------------------------------------------------------
// get_psum()
//---------------------------------------------------------------------------
void CRobotDKP::get_psum(Mat_I_DP &p, Vec_O_DP &psum)
{
    int i,j;
    DP sum;

    int mpts=p.nrows();
    int ndim=p.ncols();
    for (j=0;j<ndim;j++)
    {
        for (sum=0.0,i=0;i<mpts;i++)
            sum += p[i][j];
        psum[j]=sum;
    }
}
//---------------------------------------------------------------------------
// amoeba()
//---------------------------------------------------------------------------
bool CRobotDKP::amoeba(Mat_IO_DP &p, Vec_IO_DP &y, const DP ftol, int &nfunk)
{
	const int NMAX=5000;
	const DP TINY=1.0e-10;
	int i,ihi,ilo,inhi,j;
	DP rtol,ysave,ytry;

	int mpts=p.nrows();
	int ndim=p.ncols();
	Vec_DP psum(ndim);
	nfunk=0;
	get_psum(p,psum);
	for (;;) {
		ilo=0;
		ihi = y[0]>y[1] ? (inhi=1,0) : (inhi=0,1);
		for (i=0;i<mpts;i++) {
			if (y[i] <= y[ilo]) ilo=i;
			if (y[i] > y[ihi]) {
				inhi=ihi;
				ihi=i;
			} else if (y[i] > y[inhi] && i != ihi) inhi=i;
		}
		rtol=2.0*fabs(y[ihi]-y[ilo])/(fabs(y[ihi])+fabs(y[ilo])+TINY);
		if (rtol < ftol) {
			SWAP(y[0],y[ilo]);
			for (i=0;i<ndim;i++) SWAP(p[0][i],p[ilo][i]);
			break;
		}
		if (nfunk >= NMAX)
                   return false;
                   
		nfunk += 2;
		ytry=amotry(p,y,psum, ihi,-1.0);
		if (ytry <= y[ilo])
			ytry=amotry(p,y,psum,ihi,2.0);
		else if (ytry >= y[inhi]) {
			ysave=y[ihi];
			ytry=amotry(p,y,psum,ihi,0.5);
			if (ytry >= ysave) {
				for (i=0;i<mpts;i++) {
					if (i != ilo) {
						for (j=0;j<ndim;j++)
							p[i][j]=psum[j]=0.5*(p[i][j]+p[ilo][j]);
						y[i]=ErrorFunc(psum);
					}
				}
				nfunk += ndim;
				get_psum(p,psum);
			}
		} else --nfunk;
	}

        return true;
}
//---------------------------------------------------------------------------
// amotry()
//---------------------------------------------------------------------------
DP CRobotDKP::amotry(Mat_IO_DP &p, Vec_O_DP &y, Vec_IO_DP &psum, const int ihi, const DP fac)
{
	int j;
	DP fac1,fac2,ytry;

	int ndim=p.ncols();
	Vec_DP ptry(ndim);
	fac1=(1.0-fac)/ndim;
	fac2=fac1-fac;
	for (j=0;j<ndim;j++)
		ptry[j]=psum[j]*fac1-p[ihi][j]*fac2;
	ytry=ErrorFunc(ptry);
	if (ytry < y[ihi]) {
		y[ihi]=ytry;
		for (j=0;j<ndim;j++) {
			psum[j] += ptry[j]-p[ihi][j];
			p[ihi][j]=ptry[j];
		}
	}
	return ytry;
}
//---------------------------------------------------------------------------
// CalcUpperPlatform()
//---------------------------------------------------------------------------
bool CRobotDKP::CalcUpperPlatform(double JackLength[6])
{
   // 连杆给定长度
   for(int i = 0; i < 6; ++i)
      __JackLength[i] = JackLength[i] * 0.001;
      
   // 找出连杆长度最接近给定连杆长度的位姿
   double MinDiff = MAXFLOAT;
   CPostureJacks InitPost;
   for(vector<CPostureJacks>::iterator p = __PostJacks.begin(); p != __PostJacks.end(); ++p)
   {
      double Diff = p->JackDifference(JackLength);
      if(Diff < MinDiff)
      {
         MinDiff  = Diff;
         InitPost = *p;
      }
   }

   // 计算默认初始位置
   // 初始位置设置为机器人运动空间的中心位置
   double MidZ = (PlatformMinHeight() + PlatformMaxHeight()) * 0.5;
   double InitPoly1[7][6] = {{0, 0, MidZ, 0, 0, 0},
                             {1, 0, MidZ, 0, 0, 0},
                             {0, 1, MidZ, 0, 0, 0},
                             {0, 0, MidZ + 1, 0, 0, 0},
                             {0, 0, MidZ, 0.5, 0, 0},
                             {0, 0, MidZ, 0, 0.5, 0},
                             {0, 0, MidZ, 0, 0, 0.5}};

   // 存在初始位置
   double InitPoly2[7][6] = {{InitPost.X, InitPost.Y, InitPost.Z, InitPost.Yaw, InitPost.Pitch, InitPost.Roll},
                             {InitPost.X + __LinearStep, InitPost.Y, InitPost.Z, InitPost.Yaw, InitPost.Pitch, InitPost.Roll},
                             {InitPost.X, InitPost.Y + __LinearStep, InitPost.Z, InitPost.Yaw, InitPost.Pitch, InitPost.Roll},
                             {InitPost.X, InitPost.Y, InitPost.Z + __LinearStep, InitPost.Yaw, InitPost.Pitch, InitPost.Roll},
                             {InitPost.X, InitPost.Y, InitPost.Z, InitPost.Yaw + __RotaryStep, InitPost.Pitch, InitPost.Roll},
                             {InitPost.X, InitPost.Y, InitPost.Z, InitPost.Yaw, InitPost.Pitch + __RotaryStep, InitPost.Roll},
                             {InitPost.X, InitPost.Y, InitPost.Z, InitPost.Yaw, InitPost.Pitch, InitPost.Roll + __RotaryStep}};

   Mat_DP p(7, 6);    // 定义单纯型多面体，由7个端点构成，其中一行表示一个端子
   Vec_DP y(7);       // 单纯型多面体每个端子的cost

   // 初始化单纯型多面体，计算每个端点的初始值
   if(__PostJacks.empty())
   {
      for (int Row = 0; Row < 7; ++Row)
      {
         for(int Col = 0; Col < 6; ++Col)
            p[Row][Col] = InitPoly1[Row][Col];
         y[Row] = ErrorFunc(InitPoly1[Row]);
      }
   }
   else
   {
      for (int Row = 0; Row < 7; ++Row)
      {
         for(int Col = 0; Col < 6; ++Col)
            p[Row][Col] = InitPoly2[Row][Col];
         y[Row] = ErrorFunc(InitPoly2[Row]);
      }
   }

   // 调用阿米巴函数计算上平台位姿
   int FuncCnt;
   bool Rst = amoeba(p, y, 1.0e-10, FuncCnt);   // 注意：amoeba()中已经包含了ErrorFunc()

   // 拷贝计算结果
   for(int Col = 0; Col < 3; ++Col)
   {
      CalcPosition[Col] = p[0][Col];
      CalcEurlar[Col]   = p[0][Col + 3];
   }

   return Rst;
}

