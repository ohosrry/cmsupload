
// DlgProxy.cpp : ʵ���ļ�
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
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ������ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
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
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CMFCSampleDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMFCSampleDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFCSampleDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IMFCSample ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {79036F14-928F-4393-8915-A7DA2FCC0658}
static const IID IID_IMFCSample =
{ 0x79036F14, 0x928F, 0x4393, { 0x89, 0x15, 0xA7, 0xDA, 0x2F, 0xCC, 0x6, 0x58 } };

BEGIN_INTERFACE_MAP(CMFCSampleDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMFCSampleDlgAutoProxy, IID_IMFCSample, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {7101368D-BCCC-4519-B397-565559D64C2C}
IMPLEMENT_OLECREATE2(CMFCSampleDlgAutoProxy, "MFCSample.Application", 0x7101368d, 0xbccc, 0x4519, 0xb3, 0x97, 0x56, 0x55, 0x59, 0xd6, 0x4c, 0x2c)


// CMFCSampleDlgAutoProxy ��Ϣ�������
