#pragma once

#include "MButton.h"
#include "MSTree.h"
#include <vector>
#include "stdafx.h"
#define HI_ONCLICK WM_USER+100
// CMSUploadCtrl.h : CCMSUploadCtrl ActiveX �ؼ����������


// CCMSUploadCtrl : �й�ʵ�ֵ���Ϣ������� CMSUploadCtrl.cpp��
extern CCMSUploadApp theApp;


class CCMSUploadCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCMSUploadCtrl)

	// ���캯��
public:
	CCMSUploadCtrl();

	// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();
	virtual void OnMouseHover(UINT uint, CPoint cp);
	virtual void OnMouseMove(UINT uint, CPoint cp);
	virtual int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	//virtual void FireClick();
	virtual void DoClick();
    virtual void OnLButtonUp(UINT nFlags, CPoint point);
	//virtual void OnClick(USHORT ibutton);
	virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void MouseUp(SHORT Button, SHORT Shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	virtual void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void OnPaint();
	int InitPoints();
	void createStatic();
	vector<CRect> PointRects() const { return m_PointRects; }
	void PointRects(vector<CRect>& val) { this->m_PointRects = val; }
	afx_msg LRESULT ONProgress(WPARAM w,LPARAM l);
	// ʵ��
protected:
	~CCMSUploadCtrl();

	DECLARE_OLECREATE_EX(CCMSUploadCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CCMSUploadCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CCMSUploadCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CCMSUploadCtrl)		// �������ƺ�����״̬

	// ����ؼ�֧��
	BOOL IsSubclassedControl() sealed;
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

	// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

	// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

	// �¼�ӳ��
	DECLARE_EVENT_MAP()

	// ���Ⱥ��¼� ID
public:
	enum {
		TB,
		MCPR
	};
	vector<STIMAGE> m_Stimage;
private:
	MButton m_cb;
	CStatic m_static;
	CMSTree m_tree;
	CImageList m_image_list;
	CProgressCtrl m_cpr;
	CImage m_image;
	CImageList m_list;
	CPictureHolder m_picture;
    vector<CRect> m_PointRects;
	int cb_lock;
	int static_lock;
	HINSTANCE instance;
};

