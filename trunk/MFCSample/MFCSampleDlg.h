
// MFCSampleDlg.h : 头文件
//

#pragma once

class CMFCSampleDlgAutoProxy;


// CMFCSampleDlg 对话框
class CMFCSampleDlg : public CDialog
{
	DECLARE_DYNAMIC(CMFCSampleDlg);
	friend class CMFCSampleDlgAutoProxy;

// 构造
public:
	CMFCSampleDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CMFCSampleDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CMFCSampleDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
   
	virtual void OnOK();
	virtual void OnCancel(); 
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
private:
	CButton *cb;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};
