#pragma once

// CMSUploadPropPage.h : CCMSUploadPropPage ����ҳ���������


// CCMSUploadPropPage : �й�ʵ�ֵ���Ϣ������� CMSUploadPropPage.cpp��

class CCMSUploadPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCMSUploadPropPage)
	DECLARE_OLECREATE_EX(CCMSUploadPropPage)

// ���캯��
public:
	CCMSUploadPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_CMSUPLOAD };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
};

