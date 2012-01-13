#include "StdAfx.h"
#include "MButton.h"
IMPLEMENT_DYNCREATE(MButton, CButton)
BEGIN_MESSAGE_MAP(MButton, CButton)
    ON_WM_LBUTTONUP()
END_MESSAGE_MAP()
MButton::MButton(void)
{

}
void MButton::OnLButtonUp(UINT nFlags,CPoint point){
    AfxMessageBox(_T("HI OnLButtonUp"));
}
MButton::~MButton(void)
{


}
