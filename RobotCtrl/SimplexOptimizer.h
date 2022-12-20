//---------------------------------------------------------------------------

#ifndef SimplexOptimizerH
#define SimplexOptimizerH
//---------------------------------------------------------------------------
class VectorDP
{
private:
	int nn;	// size of array. upper index is nn-1
	double *v;
public:
	VectorDP(void) : nn(0), v(0) {}
	VectorDP(int n) : nn(n), v(new double[n]) {}
	VectorDP(const double &a, int n) : nn(n), v(new double[n])
        {
           for(int i = 0; i < n; i++)
              v[i] = a;
        }
	VectorDP(const double *a, int n) : nn(n), v(new double[n])
        {
           for(int i = 0; i < n; i++)
              v[i] = *a++;
        }
	VectorDP(const VectorDP &rhs) : nn(rhs.nn), v(new double[rhs.nn])
        {
           for(int i = 0; i < nn; i++)
              v[i] = rhs[i];
        }
	VectorDP & operator=(const VectorDP &rhs);	//assignment
	VectorDP & operator=(const double &a);	//assign a to every element
	inline double & operator[](const int i);	//i'th element
	inline const double & operator[](const int i) const;
	inline int size() const;
	~VectorDP();
};

VectorDP& VectorDP::operator=(const VectorDP &rhs)
{
	if (this != &rhs)
	{
		if (nn != rhs.nn) {
			if (v != 0) delete [] (v);
			nn=rhs.nn;
			v= new double[nn];
		}
		for (int i=0; i<nn; i++)
			v[i]=rhs[i];
	}
	return *this;
}

VectorDP& VectorDP::operator=(const double &a)	//assign a to every element
{
	for (int i=0; i<nn; i++)
		v[i]=a;
	return *this;
}

inline double& VectorDP::operator[](const int i)	//subscripting
{
	return v[i];
}

inline const double & VectorDP::operator[](const int i) const	//subscripting
{
	return v[i];
}

inline int VectorDP::size(void) const
{
	return nn;
}

VectorDP::~VectorDP(void)
{
	if (v != 0)
		delete[] (v);
}
//---------------------------------------------------------------------------
class MatrixDP
{
private:
	int nn;
	int mm;
	double **v;
public:
	MatrixDP(void) : nn(0), mm(0), v(0) {}
	MatrixDP(int n, int m) : nn(n), mm(m), v(new double*[n])
        {
           v[0] = new double[m*n];
           for (int i=1; i< n; i++)
              v[i] = v[i-1] + m;
        }
	MatrixDP(const double &a, int n, int m) : nn(n), mm(m), v(new double*[n])
        {
           int i,j;
           v[0] = new double[m*n];
	   for (i=1; i< n; i++)
              v[i] = v[i-1] + m;
	   for (i=0; i< n; i++)
              for (j=0; j<m; j++)
                 v[i][j] = a;
        }
	MatrixDP(const double *a, int n, int m) : nn(n), mm(m), v(new double*[n])
        {
           int i,j;
           v[0] = new double[m*n];
	   for (i=1; i< n; i++)
              v[i] = v[i-1] + m;
	   for (i=0; i< n; i++)
              for (j=0; j<m; j++)
                 v[i][j] = *a++;
        }
	MatrixDP(const MatrixDP &rhs) : nn(rhs.nn), mm(rhs.mm), v(new double*[nn])
        {
	   int i,j;
	   v[0] = new double[mm*nn];
	   for (i=1; i< nn; i++)
	      v[i] = v[i-1] + mm;
	   for (i=0; i< nn; i++)
	      for (j=0; j<mm; j++)
	         v[i][j] = rhs[i][j];
        }
	MatrixDP & operator=(const MatrixDP &rhs);	//assignment
	MatrixDP & operator=(const double &a);		//assign a to every element
	inline double* operator[](const int i);	//subscripting: pointer to row i
	inline const double* operator[](const int i) const;
	inline int nrows() const;
	inline int ncols() const;
	~MatrixDP();
};

MatrixDP& MatrixDP::operator=(const MatrixDP &rhs)
{
	if (this != &rhs) {
		int i,j;
		if (nn != rhs.nn || mm != rhs.mm) {
			if (v != 0) {
				delete[] (v[0]);
				delete[] (v);
			}
			nn=rhs.nn;
			mm=rhs.mm;
			v = new double*[nn];
			v[0] = new double[mm*nn];
		}
		for (i=1; i< nn; i++)
			v[i] = v[i-1] + mm;
		for (i=0; i< nn; i++)
			for (j=0; j<mm; j++)
				v[i][j] = rhs[i][j];
	}
	return *this;
}

MatrixDP & MatrixDP::operator=(const double &a)	//assign a to every element
{
	for (int i=0; i< nn; i++)
		for (int j=0; j<mm; j++)
			v[i][j] = a;
	return *this;
}

inline double* MatrixDP::operator[](const int i)	//subscripting: pointer to row i
{
	return v[i];
}

inline const double* MatrixDP::operator[](const int i) const
{
	return v[i];
}

inline int MatrixDP::nrows() const
{
	return nn;
}

inline int MatrixDP::ncols() const
{
	return mm;
}

MatrixDP::~MatrixDP()
{
	if (v != 0) {
		delete[] (v[0]);
		delete[] (v);
	}
}
//---------------------------------------------------------------------------
class CSimplexOptimizer
{
private:
   int  __MaxIterCnt;
public:
   int  IterCnt;
private:
   void   get_psum(MatrixDP &p, VectorDP &psum);
   bool   amoeba(MatrixDP &p, VectorDP &y, const double ftol, int &nfunk);
   double amotry(MatrixDP &p, VectorDP &y, VectorDP &psum, const int ihi, const double fac);
   void   SWAP(double &a, double &b){double t = a; a = b; b = t;}
protected:
   virtual double CostFunction(VectorDP &x);
   virtual double CostFunction(const double *x) = 0;
public:
   bool Calc(double *InitPoly, int Dim, double *Solution, int MaxIterCnt = 5000, const double ftol = 1.0e-10);
};
#endif
