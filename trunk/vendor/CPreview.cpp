// CPreview.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMSInterface.h"
#include "CPreview.h"
#include "lib_cms.h"
#include <atlimage.h>
// CCPreview �Ի���

IMPLEMENT_DYNAMIC(CCPreview, CDialog)

CCPreview::CCPreview(CWnd* pParent /*=NULL*/)
	: CDialog(CCPreview::IDD, pParent)
{

}

CCPreview::~CCPreview()
{
}

void CCPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCPreview, CDialog)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()
BOOL CCPreview::OnInitDialog(){

	ShowWindow(SW_MAXIMIZE);
	return CDialog::OnInitDialog();
}

// CCPreview ��Ϣ�������

void CCPreview::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialog::OnLButtonDblClk(nFlags, point);
	EndDialog(0);
	//CDialog::OnClose();
	//CloseWindow();
}
void CCPreview::OnPaint()
{
   PAINTSTRUCT ps;
   BeginPaint(&ps);
   
   EndPaint(&ps);
}

BOOL CCPreview::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialog::OnEraseBkgnd(pDC);
    if(m_Pic_Path!=L"")
	{
		CDC l_Cdc;
		CImage l_image;
		CBitmap l_bmp,*lp_old_bmp;
		BITMAP l_bm;
		INT l_w,l_h;
		//CMSBOXW(m_Pic_Path);
		//CFile cf(m_Pic_Path,CFile::modeRead);
		//CMSBOXW(cf.GetFileName());
		//cf.Close();
		//if(!l_bmp.LoadBitmap(m_Pic_Path.AllocSysString()))
		//{   
		//	GetLastError();
		//	CString css;
		//	css.Format(L"%d",GetLastError());
		//	CMSBOXW(L"l_bmp.LoadBitmap failed"+css);
  //          ErrorExit(L"OnEraseBkgnd");
		//}
        
		HRESULT hr=l_image.Load(m_Pic_Path);
		if(FAILED(hr))
		{
		    CString css;
			css.Format(L"%d",GetLastError());
			CMSBOXW(L"l_image.Load failed"+css);
			return CDialog::OnEraseBkgnd(pDC);
		}
        l_w=l_image.GetWidth();
		l_h=l_image.GetHeight();
		HBITMAP hbmp=l_image.Detach();
		if(!l_bmp.Attach(hbmp))
		{
			CString css;
			css.Format(L"%d",GetLastError());
			CMSBOXW(L"l_bmp.Attach failed"+css);
			return CDialog::OnEraseBkgnd(pDC);
		}
        
		l_bmp.GetObject(sizeof(BITMAP),&l_bm);
        l_Cdc.CreateCompatibleDC(pDC);
        lp_old_bmp=(CBitmap*)l_Cdc.SelectObject(&l_bmp);
        CRect cr;
		GetClientRect(&cr);

		//SetWindowPos(NULL,cr.left,cr.right,l_w,l_h,0);
		
		pDC->TransparentBlt(0,0,cr.Width(),cr.Height(),&l_Cdc,0,0,l_w,l_h,RGB(255, 255, 255));
		l_Cdc.SelectObject(lp_old_bmp);
		l_Cdc.DeleteDC();
		

		// CMSBOXW(L"asdsad");
	}
   return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}
