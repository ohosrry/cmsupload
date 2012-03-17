// CMSInterfacePropPage.cpp : CCMSInterfacePropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "CMSInterface.h"
#include "CMSInterfacePropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CCMSInterfacePropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CCMSInterfacePropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CCMSInterfacePropPage, "CMSINTERFACE.CMSInterfacePropPage.1",
	0x39256ed7, 0xee3f, 0x44ef, 0x99, 0xfd, 0x40, 0x90, 0xa7, 0xc8, 0x5d, 0x80)



// CCMSInterfacePropPage::CCMSInterfacePropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CCMSInterfacePropPage ��ϵͳע�����

BOOL CCMSInterfacePropPage::CCMSInterfacePropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CMSINTERFACE_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CCMSInterfacePropPage::CCMSInterfacePropPage - ���캯��

CCMSInterfacePropPage::CCMSInterfacePropPage() :
	COlePropertyPage(IDD, IDS_CMSINTERFACE_PPG_CAPTION)
{
}



// CCMSInterfacePropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CCMSInterfacePropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CCMSInterfacePropPage ��Ϣ�������
