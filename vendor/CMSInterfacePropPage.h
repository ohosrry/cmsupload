#pragma once

// CMSInterfacePropPage.h : CCMSInterfacePropPage 属性页类的声明。


// CCMSInterfacePropPage : 有关实现的信息，请参阅 CMSInterfacePropPage.cpp。

class CCMSInterfacePropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCMSInterfacePropPage)
	DECLARE_OLECREATE_EX(CCMSInterfacePropPage)

// 构造函数
public:
	CCMSInterfacePropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_CMSINTERFACE };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

