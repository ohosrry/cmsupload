
// MFCSampleDlg.h : ͷ�ļ�
//

#pragma once

class CMFCSampleDlgAutoProxy;


// CMFCSampleDlg �Ի���
class CMFCSampleDlg : public CDialog
{
	DECLARE_DYNAMIC(CMFCSampleDlg);
	friend class CMFCSampleDlgAutoProxy;

// ����
public:
	CMFCSampleDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CMFCSampleDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	CMFCSampleDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// ���ɵ���Ϣӳ�亯��
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
