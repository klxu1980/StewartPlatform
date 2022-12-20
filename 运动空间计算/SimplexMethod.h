//---------------------------------------------------------------------------

#ifndef SimplexMethodH
#define SimplexMethodH
#include "nr.h"
using namespace std;
using namespace NR;
//---------------------------------------------------------------------------
void amoeba(Mat_IO_DP &p, Vec_IO_DP &y, const DP ftol, DP funk(Vec_I_DP &), int &nfunk);
#endif
