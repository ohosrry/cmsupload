// CMSUploadPropPage.cpp : CCMSUploadPropPage 属性页类的实现。

#include "stdafx.h"
#include "CMSUpload.h"
#include "CMSUploadPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CCMSUploadPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CCMSUploadPropPage, COlePropertyPage)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CCMSUploadPropPage, "CMSUPLOAD.CMSUploadPropPage.1",
	0x4429d7b0, 0x8ef5, 0x4a55, 0xbc, 0x89, 0x19, 0x99, 0xa0, 0xab, 0x8d, 0x4d)



// CCMSUploadPropPage::CCMSUploadPropPageFactory::UpdateRegistry -
// 添加或移除 CCMSUploadPropPage 的系统注册表项

BOOL CCMSUploadPropPage::CCMSUploadPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CMSUPLOAD_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CCMSUploadPropPage::CCMSUploadPropPage - 构造函数

CCMSUploadPropPage::CCMSUploadPropPage() :
	COlePropertyPage(IDD, IDS_CMSUPLOAD_PPG_CAPTION)
{
}



// CCMSUploadPropPage::DoDataExchange - 在页和属性间移动数据

void CCMSUploadPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CCMSUploadPropPage 消息处理程序

void CCMSUploadPropPage::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	COlePropertyPage::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
}
