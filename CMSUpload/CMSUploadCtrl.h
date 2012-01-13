#pragma once
#include "MButton.h"
#include "MSTree.h"
#define HI_ONCLICK WM_USER+100
// CMSUploadCtrl.h : CCMSUploadCtrl ActiveX 控件类的声明。


// CCMSUploadCtrl : 有关实现的信息，请参阅 CMSUploadCtrl.cpp。
extern CCMSUploadApp theApp;
class CCMSUploadCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCMSUploadCtrl)

// 构造函数
public:
	CCMSUploadCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();
	virtual void OnMouseHover(UINT uint, CPoint cp);
	virtual void OnMouseMove(UINT uint, CPoint cp);
    virtual int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void FireClick();
	virtual void DoClick();
	virtual void OnClick(WPARAM wp,LPARAM lp);
	virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void MouseUp(SHORT Button, SHORT Shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	virtual void OnLButtonDblClk(UINT nFlags, CPoint point);
// 实现
protected:
	~CCMSUploadCtrl();

	DECLARE_OLECREATE_EX(CCMSUploadCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CCMSUploadCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CCMSUploadCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CCMSUploadCtrl)		// 类型名称和杂项状态

	// 子类控件支持
	BOOL IsSubclassedControl() sealed;
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		TB
	};
private:
MButton m_cb;
CStatic m_static; 
CMSTree m_tree;
CImageList m_image_list;
int cb_lock;
int static_lock;
HINSTANCE instance;
};

