
// Mfc_WindowView.h : CMfc_WindowView 类的接口
//


#pragma once


class CMfc_WindowView : public CView
{
protected: // 仅从序列化创建
	CMfc_WindowView();
	DECLARE_DYNCREATE(CMfc_WindowView)

// 属性
public:
	CMfc_WindowDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMfc_WindowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Mfc_WindowView.cpp 中的调试版本
inline CMfc_WindowDoc* CMfc_WindowView::GetDocument() const
   { return reinterpret_cast<CMfc_WindowDoc*>(m_pDocument); }
#endif

