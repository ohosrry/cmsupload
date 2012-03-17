// CMSInterfacePropPage.cpp : CCMSInterfacePropPage 属性页类的实现。

#include "stdafx.h"
#include "CMSInterface.h"
#include "CMSInterfacePropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CCMSInterfacePropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CCMSInterfacePropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CCMSInterfacePropPage, "CMSINTERFACE.CMSInterfacePropPage.1",
	0x39256ed7, 0xee3f, 0x44ef, 0x99, 0xfd, 0x40, 0x90, 0xa7, 0xc8, 0x5d, 0x80)



// CCMSInterfacePropPage::CCMSInterfacePropPageFactory::UpdateRegistry -
// 添加或移除 CCMSInterfacePropPage 的系统注册表项

BOOL CCMSInterfacePropPage::CCMSInterfacePropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CMSINTERFACE_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CCMSInterfacePropPage::CCMSInterfacePropPage - 构造函数

CCMSInterfacePropPage::CCMSInterfacePropPage() :
	COlePropertyPage(IDD, IDS_CMSINTERFACE_PPG_CAPTION)
{
}



// CCMSInterfacePropPage::DoDataExchange - 在页和属性间移动数据

void CCMSInterfacePropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CCMSInterfacePropPage 消息处理程序
