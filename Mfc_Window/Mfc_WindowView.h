
// Mfc_WindowView.h : CMfc_WindowView ��Ľӿ�
//


#pragma once


class CMfc_WindowView : public CView
{
protected: // �������л�����
	CMfc_WindowView();
	DECLARE_DYNCREATE(CMfc_WindowView)

// ����
public:
	CMfc_WindowDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMfc_WindowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Mfc_WindowView.cpp �еĵ��԰汾
inline CMfc_WindowDoc* CMfc_WindowView::GetDocument() const
   { return reinterpret_cast<CMfc_WindowDoc*>(m_pDocument); }
#endif

