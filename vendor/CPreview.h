#pragma once


// CCPreview �Ի���

class CCPreview : public CDialog
{
	DECLARE_DYNAMIC(CCPreview)
public:
	CCPreview(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCPreview();
// �Ի�������
	enum { IDD = IDD_FORM_PREVIEW };
    CString m_Pic_Path;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void OnPaint();
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnInitDialog();
};
