#pragma once

// CMSInterfacePropPage.h : CCMSInterfacePropPage ����ҳ���������


// CCMSInterfacePropPage : �й�ʵ�ֵ���Ϣ������� CMSInterfacePropPage.cpp��

class CCMSInterfacePropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCMSInterfacePropPage)
	DECLARE_OLECREATE_EX(CCMSInterfacePropPage)

// ���캯��
public:
	CCMSInterfacePropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_CMSINTERFACE };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

