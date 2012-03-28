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
void CCUpStatus::DoCleanUp()
{
	m_Can_Exit=TRUE;
	map<CString,ST_STATUS>::iterator it=m_Status_Map.begin();
	g_Map_Lock.Lock();
    while(it!=m_Status_Map.end())
	{
        SAFE_DELETE(it->second.m_Progress);
		SAFE_DELETE(it->second.pre);
		SAFE_DELETE(it->second.next);
		++it;
	}
	m_Map.clear();
	m_Status_Map.clear();
	g_Map_Lock.Unlock();
	CDialog::OnClose();
}
BOOL CCUpStatus::OnInitDialog()
{   
	INT originX=250,originY=30;
	map<CString,ST_STATUS>::iterator it=m_Status_Map.begin();
	CRect cr1(10,10,200,30);
	/*m_Prog.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,cr1,this,0);
    m_Prog.SetPos(50);*/
	while(it!=m_Status_Map.end())
	{
		CRect cr(originX,originY,originX+200,originY+20);
		CRect pre(originX-250,originY,originX,originY+20);
		CRect next(originX+200,originY,originX+200+400,originY+20);
		//ClientToScreen(&cr);
		CString percent;
		CString l_Up_Text;
		l_Up_Text.Format(L"%s上传进度",it->first);
		percent.Format(L"%d%s",it->second.percent,L"%");
        BOOL ret=it->second.m_Progress->Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,cr,this,0);
		it->second.pre->Create(l_Up_Text,WS_VISIBLE|WS_CHILD,pre,this,0);
		it->second.next->Create(percent,WS_VISIBLE|WS_CHILD,next,this,0);
	    CFont cf;
		LOGFONT lfont={0};
		memset(&lfont, 0, sizeof(LOGFONT));
        lfont.lfHeight=3;
		_tcsncpy_s(lfont.lfFaceName, LF_FACESIZE, _T("Arial"), 3);  
        VERIFY(cf.CreateFontIndirect(&lfont));
		it->second.pre->SetFont(&cf);
		it->second.m_Progress->SetRange(0,100);
		it->second.m_Progress->SetPos(0);
		originY+=STATUS_LINE_SEP;
		//CMSBOX("OK");
		//CString ccs;
		//ccs.Format(L"%d",ret);
		//CMSBOXW(it->first);
		++it;
	}
	AfxBeginThread(&CCUpStatus::UpdateThread,this);
	return CDialog::OnInitDialog();
}

BOOL CCUpStatus::OnSetObjectRects(LPCRECT lpRectPos, LPCRECT lpRectClip)
{
	return TRUE;
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
        Sleep(200);
		status->DoUpdate();
		//status->Invalidate();
	}
    //CMSBOX("here");
	return 0;
}

void CCUpStatus::DoUpdate()
{
	map<CString,ST_STATUS>::iterator it_status=m_Status_Map.begin();
	g_Map_Lock.Lock();
	while(it_status!=m_Status_Map.end())
	{
  //      if(it_status->second.m_Progress->GetPos()==100)
		//{

		//	++it_status;
		//	continue;
		//}
		CString l_percent;
		//l_percent.Format(L"%d%s",it_status->second.percent,L"%");
		it_status->second.next->SetWindowText(it_status->second.s_percent);
		it_status->second.m_Progress->SetPos(it_status->second.percent);
		++it_status;
	}
	g_Map_Lock.Unlock();
	//RedrawWindow();

}

void CCUpStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCUpStatus, CDialog)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCUpStatus 消息处理程序

void CCUpStatus::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    //CloseWindow();
	CDialog::OnLButtonDblClk(nFlags, point);
	//m_Can_Exit=TRUE;
    //DoCleanUp();
	//CloseWindow();
	//DestroyWindow();
	SendMessage(WM_CLOSE);
}

void CCUpStatus::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//dc.SetTextColor(RGB(255,255,255));
	//dc.LineTo(CPoint(100,100));
	//CRect cr(100,200,100,200);
	/*dc.SetBkColor(RGB(255,255,255));
	dc.SetBkMode(TRANSPARENT);*/
	//INT originX=20,originY=50;
	//map<CString,CString>::iterator it=m_Map.begin();
	//map<CString,ST_STATUS>::iterator it_status=m_Status_Map.begin();
   // g_Map_Lock.Lock();
	//while(it!=m_Map.end())
	//{

 //      // dc.TextOut(originX,originY,it->second,it->second.GetLength());
	////	originY+=STATUS_LINE_SEP;
	//	++it;
	//}
	//while(it_status!=m_Status_Map.end())
	//{
 //      CString l_percent;
	//   l_percent.Format(L"%d%s",it_status->second.percent,L"%");
	//   it_status->second.next->SetWindowText(l_percent);
	//   it_status->second.m_Progress->SetPos(it_status->second.percent);
	//   ++it_status;
	//}
   // g_Map_Lock.Unlock();
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

void CCUpStatus::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DoCleanUp();
   // CMSBOX("CLOSE");
	//DoCleanUp();
	
}
