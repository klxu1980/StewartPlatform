//---------------------------------------------------------------------------

#ifndef MatrixH
#define MatrixH
//---------------------------------------------------------------------------
class CMatrix
{
private:
   double  *__Element;
   int      __RowSize;
   int      __ColSize;
public:
   CMatrix(int Row, int Col);
   ~CMatrix(void){delete []__Element;}
public:
   int      RowSize(void){return __RowSize;}
   int      ColSize(void){return __ColSize;}
public:
   double*  Begin(void){return __Element;}
   double*  End(void){return __Element + __RowSize * __ColSize;}
public:
   double&  operator () (int Row, int Col){return *(__Element + Row * __ColSize + Col);}
   void     operator *= (double Value);
   void     operator += (CMatrix &M);
   void     operator += (double Value);
   void     operator -= (CMatrix &M);
   double   operator  = (double Value);
public:
   void     Trans(CMatrix &M);
   void     AddVectorMultVector(CVector &VC, CVector &VR);
   void     Randomize(void);
public:
   void     Convolve(CMatrix &SrcM, CMatrix &Weights);    // ¼ÆËã¾ØÕó¾í»ý
public:
   void  Save(TStream *Stream);
   void  Load(TStream *Stream);
};
#endif
 