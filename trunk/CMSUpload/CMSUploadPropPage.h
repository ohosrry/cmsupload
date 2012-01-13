#pragma once

// CMSUploadPropPage.h : CCMSUploadPropPage 属性页类的声明。


// CCMSUploadPropPage : 有关实现的信息，请参阅 CMSUploadPropPage.cpp。

class CCMSUploadPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCMSUploadPropPage)
	DECLARE_OLECREATE_EX(CCMSUploadPropPage)

// 构造函数
public:
	CCMSUploadPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_CMSUPLOAD };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};

