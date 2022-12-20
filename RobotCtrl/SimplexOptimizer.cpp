//---------------------------------------------------------------------------


#pragma hdrstop

#include "SimplexOptimizer.h"
#include <math.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
#ifdef __BORLANDC__
//---------------------------------------------------------------------------
double CSimplexOptimizer::CostFunction(VectorDP &x)
{
   return CostFunction(&x[0]);
}
//---------------------------------------------------------------------------
bool CSimplexOptimizer::Calc(double *InitPoly, int Dim, double *Solution, int MaxIterCnt, const double ftol)
{
   // 定义单纯形多面体，以及多面体每个端点的代价
   MatrixDP p(Dim + 1, Dim);
   VectorDP y(Dim + 1);

   // 初始化单纯型多面体，计算每个端点的初始值
   for (int Row = 0; Row < Dim + 1; ++Row)
   {
      for(int Col = 0; Col < Dim; ++Col)
         p[Row][Col] = InitPoly[Row * Dim + Col];
      y[Row] = CostFunction(InitPoly + Row * Dim);
   }  

   // 单纯形优化
   __MaxIterCnt = MaxIterCnt;
   bool Rst = amoeba(p, y, ftol, IterCnt);

   // 拷贝计算结果
   for(int Col = 0; Col < Dim; ++Col)
      Solution[Col] = p[0][Col];

   return Rst;
}
//---------------------------------------------------------------------------
void CSimplexOptimizer::get_psum(MatrixDP &p, VectorDP &psum)
{
    int i,j;
    double sum;

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
// amotry()
//---------------------------------------------------------------------------
double CSimplexOptimizer::amotry(MatrixDP &p, VectorDP &y, VectorDP &psum, const int ihi, const double fac)
{
	int j;
	double fac1,fac2,ytry;

	int ndim=p.ncols();
	VectorDP ptry(ndim);
	fac1=(1.0-fac)/ndim;
	fac2=fac1-fac;
	for (j=0;j<ndim;j++)
		ptry[j]=psum[j]*fac1-p[ihi][j]*fac2;
	ytry=CostFunction(ptry);
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
// amoeba()
//---------------------------------------------------------------------------
bool CSimplexOptimizer::amoeba(MatrixDP &p, VectorDP &y, const double ftol, int &nfunk)
{
	const int NMAX = __MaxIterCnt;
	const double TINY  = 1.0e-10;
	int i,ihi,ilo,inhi,j;
	double rtol,ysave,ytry;

	int mpts=p.nrows();
	int ndim=p.ncols();
	VectorDP psum(ndim);
	nfunk=0;
	get_psum(p,psum);
	for (;;) {
		ilo=0;
		ihi = y[0]>y[1] ? (inhi=1,0) : (inhi=0,1);
		for (i=0;i<mpts;i++) {        double yi = y[i];   double y0 = y[ilo];
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
						y[i]=CostFunction(psum);
					}
				}
				nfunk += ndim;
				get_psum(p,psum);
			}
		} else --nfunk;
	}

        return true;
}
#endif
