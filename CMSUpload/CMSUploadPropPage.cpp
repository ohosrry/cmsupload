// CMSUploadPropPage.cpp : CCMSUploadPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "CMSUpload.h"
#include "CMSUploadPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CCMSUploadPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CCMSUploadPropPage, COlePropertyPage)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CCMSUploadPropPage, "CMSUPLOAD.CMSUploadPropPage.1",
	0x4429d7b0, 0x8ef5, 0x4a55, 0xbc, 0x89, 0x19, 0x99, 0xa0, 0xab, 0x8d, 0x4d)



// CCMSUploadPropPage::CCMSUploadPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CCMSUploadPropPage ��ϵͳע�����

BOOL CCMSUploadPropPage::CCMSUploadPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CMSUPLOAD_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CCMSUploadPropPage::CCMSUploadPropPage - ���캯��

CCMSUploadPropPage::CCMSUploadPropPage() :
	COlePropertyPage(IDD, IDS_CMSUPLOAD_PPG_CAPTION)
{
}



// CCMSUploadPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CCMSUploadPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CCMSUploadPropPage ��Ϣ�������

void CCMSUploadPropPage::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	COlePropertyPage::OnActivate(nState, pWndOther, bMinimized);

	// TODO: �ڴ˴������Ϣ����������
}
