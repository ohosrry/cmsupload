
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CMFCSampleDlg;


// CMFCSampleDlgAutoProxy ����Ŀ��

class CMFCSampleDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMFCSampleDlgAutoProxy)

	CMFCSampleDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CMFCSampleDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CMFCSampleDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMFCSampleDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

