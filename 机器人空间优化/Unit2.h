//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "WorkSpace.h"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
        vector<CXY> *__Space;
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
public:
        void DrawWorkspace(vector<CXY> &Space);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
