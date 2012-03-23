#pragma once


// CCPreview 对话框

class CCPreview : public CDialog
{
	DECLARE_DYNAMIC(CCPreview)

public:
	CCPreview(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCPreview();

// 对话框数据
	enum { IDD = IDD_FORM_PREVIEW };
    CString m_Pic_Path;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnInitDialog();
};
