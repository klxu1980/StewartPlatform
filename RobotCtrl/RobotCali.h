//---------------------------------------------------------------------------

#ifndef RobotCaliH
#define RobotCaliH
#include "SimplexOptimizer.h"
#include "Robot.h"
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
class CRobotCali : public CSimplexOptimizer
{
public:
   CRobot Robot;
public:
   struct CData
   {
      double Value[6];
   };
   vector<pair<CData, CData> > RawData;
private:
   double CostFunction(const double *x);
};
#endif
