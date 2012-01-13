
// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCSample.h"
#include "DlgProxy.h"
#include "MFCSampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSampleDlgAutoProxy

IMPLEMENT_DYNCREATE(CMFCSampleDlgAutoProxy, CCmdTarget)

CMFCSampleDlgAutoProxy::CMFCSampleDlgAutoProxy()
{
	EnableAutomation();
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMFCSampleDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMFCSampleDlg)))
		{
			m_pDialog = reinterpret_cast<CMFCSampleDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMFCSampleDlgAutoProxy::~CMFCSampleDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	// 	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CMFCSampleDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMFCSampleDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFCSampleDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IMFCSample 的支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {79036F14-928F-4393-8915-A7DA2FCC0658}
static const IID IID_IMFCSample =
{ 0x79036F14, 0x928F, 0x4393, { 0x89, 0x15, 0xA7, 0xDA, 0x2F, 0xCC, 0x6, 0x58 } };

BEGIN_INTERFACE_MAP(CMFCSampleDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMFCSampleDlgAutoProxy, IID_IMFCSample, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {7101368D-BCCC-4519-B397-565559D64C2C}
IMPLEMENT_OLECREATE2(CMFCSampleDlgAutoProxy, "MFCSample.Application", 0x7101368d, 0xbccc, 0x4519, 0xb3, 0x97, 0x56, 0x55, 0x59, 0xd6, 0x4c, 0x2c)


// CMFCSampleDlgAutoProxy 消息处理程序
