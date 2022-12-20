//----------------------------------------------------------------------------
#ifndef TRangeDlgH
#define TRangeDlgH
//----------------------------------------------------------------------------
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <vector>
using namespace std;
//----------------------------------------------------------------------------
class TRangeDlg : public TForm
{
__published:
	TButton *OKBtn;
        TChart *Chart1;
        TLineSeries *Series1;
private:
public:
	virtual __fastcall TRangeDlg(TComponent* AOwner);
public:
        void ShowRange(vector<pair<double, double> > &Values);
};
//----------------------------------------------------------------------------
extern PACKAGE TRangeDlg *RangeDlg;
//----------------------------------------------------------------------------
#endif    
