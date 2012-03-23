// CUpStatus.cpp : 实现文件
//

#include "stdafx.h"
#include "CMSInterface.h"
#include "CUpStatus.h"
#include "lib_cms.h"

// CCUpStatus 对话框

IMPLEMENT_DYNAMIC(CCUpStatus, CDialog)
CCUpStatus::CCUpStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CCUpStatus::IDD, pParent),m_Can_Exit(FALSE)
{

}

CCUpStatus::~CCUpStatus()
{
}
BOOL CCUpStatus::OnInitDialog()
{
	AfxBeginThread(&CCUpStatus::UpdateThread,this);
	return CDialog::OnInitDialog();
}

UINT CCUpStatus::UpdateThread(LPVOID lp)
{
CCUpStatus* status=(CCUpStatus*)lp;
if(NULL==status)
{
return 1UL;
}
	while(!status->m_Can_Exit)
	{
        Sleep(500);
		status->Invalidate();
	}
    
	return 0;
}

void CCUpStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCUpStatus, CDialog)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CCUpStatus 消息处理程序

void CCUpStatus::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    //CloseWindow();
	CDialog::OnLButtonDblClk(nFlags, point);
	m_Can_Exit=TRUE;
	m_Map.clear();
	EndDialog(0);
}

void CCUpStatus::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//dc.SetTextColor(RGB(255,255,255));
	//dc.LineTo(CPoint(100,100));
	//CRect cr(100,200,100,200);
	dc.SetBkColor(RGB(255,255,255));
	dc.SetBkMode(TRANSPARENT);
	INT originX=20,originY=50;
	map<CString,CString>::iterator it=m_Map.begin();
    g_Map_Lock.Lock();
	while(it!=m_Map.end())
	{
        dc.TextOut(originX,originY,it->second,it->second.GetLength());
		originY+=STATUS_LINE_SEP;
		++it;
	}
    g_Map_Lock.Unlock();
	//Invalidate();
    //ScreenToClient(&cr);
	//CString cs(L"CCCC");
    //INT ret;
	//dc.TextOut(100,100,cs,cs.GetLength());
	//ret=dc.DrawText(cs,-1,cr,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
    //cs.Format(L"%d",ret);
	//CMSBOXW(cs);
	//CMSBOX("asdasd");
//	Invalidate();
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}
